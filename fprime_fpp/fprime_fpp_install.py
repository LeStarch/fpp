""" install.py:

Installs the FPP tool suite based on the version of this installer package. It will use FPP_DOWNLOAD_CACHE environment
variable to pull up previously downloaded items for users that wish to install offline.
"""
import atexit
import os
import platform
import shutil
import subprocess
import sys
import tarfile
import tempfile
import urllib.request
import urllib.error

from pathlib import Path
from typing import Iterable
from contextlib import contextmanager


def clean_at_exit(file_or_directory):
    """Register file or for cleanup at exit

    In order to be a nice citizen and ensure that the system does not break when rerunning pieces of the system this
    will clean-up files when the process is exiting.
    """

    def clean(path):
        """Clean up the path"""
        print(f"-- INFO  -- Removing: {path}")
        if os.path.isfile(path):
            os.remove(path)
        else:
            shutil.rmtree(path, ignore_errors=True)

    atexit.register(clean, file_or_directory)


def setup_version():
    """Setup the version information for the fpp tools that will be installed

    There are two cases that we care about with respect to the version:

    1. Building locally (e.g. pip install ., or python3 setup.py sdist): read version from the scm (e.g. git).
    2. Installing from existing package: read version from existing version file
    """
    try:
        from .fpp_version_info import FPP_TOOLS_VERSION
    except ImportError:
        process = subprocess.run(["git", "describe", "--tag", "--always"], stdout=subprocess.PIPE, text=True)
        if process.returncode != 0:
            print(f"-- ERROR -- Cannot build locally wihtout git and git repository")
            sys.exit(1)
        scm_version = process.stdout.strip()

        # Write-version file for package completeness
        version_path = Path(__file__).parent / "fpp_version_info.py"
        clean_at_exit(version_path)
        with open(version_path, "w") as file_handle:
            file_handle.write(f"FPP_TOOLS_VERSION=\"{scm_version}\"\n")
        # Now the import should work as expected
        from .fpp_version_info import FPP_TOOLS_VERSION
    return FPP_TOOLS_VERSION


__FPP_TOOLS_VERSION__ = setup_version()
WORKING_DIR = Path(tempfile.gettempdir()) / "__FPP_WORKING_DIR__"
FPP_ARTIFACT_PREFIX = "native-fpp"
FPP_COMPRESSION_EXT = ".tar.gz"
GITHUB_URL = os.environ.get("FPP_TOOLS_REPO", "https://github.com/LeStarch/fpp")
GITHUB_RELEASE_URL = "{GITHUB_URL}/releases/download/{version}/{artifact_string}"
SBT_URL = "https://github.com/sbt/sbt/releases/download/v1.6.2/sbt-1.6.2.tgz"


@contextmanager
def safe_chdir(path):
    """Safely change directory, returning when done."""
    origin = os.getcwd()
    try:
        os.chdir(path)
        yield
    finally:
        os.chdir(origin)


def get_artifact_string(version: str) -> str:
    """Gets the platform string for the package. e.g. Darwin-x86_64"""
    return f"{ FPP_ARTIFACT_PREFIX }-{ platform.system() }-{ platform.machine() }{ FPP_COMPRESSION_EXT }"


def wget(url: str):
    """wget functionality to fetch a URL"""
    print(f"-- INFO  -- Fetching FPP tools at { url }", file=sys.stderr)
    try:
        urllib.request.urlretrieve(url, Path(url).name)
    except urllib.error.HTTPError as error:
        print(
            f"-- WARN  -- Failed to retrieve { url } with error: { error }",
            file=sys.stderr,
        )
        raise


def github_release_download(version: str):
    """Attempts to get FPP via the FPP release"""
    try:
        release_url = GITHUB_RELEASE_URL.format(
            GITHUB_URL=GITHUB_URL,
            version=version,
            artifact_string=get_artifact_string(version),
        )
        wget(release_url)
    except urllib.error.HTTPError as error:
        retry_likely = "404" not in str(error)
        retry_error = f"Retrying will likely resolve the problem."
        # Check if this is a real error or not available error
        if retry_likely:
            print(f"-- INFO  -- { retry_error }", file=sys.stderr)
            sys.exit(-1)


def prepare_cache_dir(cache_directory: Path, version: str) -> Path:
    """Prepare the cache directory for the installation artifact

    Returns:
        Path to install if the cache directory is ready, None if not (usually no artifacts available)
    """
    artifact = cache_directory / get_artifact_string(version)
    if not artifact.exists():
        return None
    # Decompress tarfile in preparation for installation
    output_dir = Path(str(artifact).replace(".tar.gz", ""))
    with tarfile.open(artifact) as archive:
        archive.extractall(".")
    return output_dir


def install_fpp(working_dir: Path) -> Path:
    """Installs FPP of the specified version"""
    version = __FPP_TOOLS_VERSION__
    cache_directory = Path(os.environ.get("FPP_DOWNLOAD_CACHE", working_dir))

    # Put everything in the current working directory
    with safe_chdir(working_dir):
        # Cache directory not supplied, must download the artifacts.
        if working_dir == cache_directory:
            github_release_download(version)

        # Check cache/download directory for artifact.
        tools_install_directory = prepare_cache_dir(cache_directory, version)
        if not tools_install_directory:
            print(
                "-- WARN  -- Cached/released tools not found. Falling back to git clone."
            )
            tools_install_directory = install_fpp_via_git(cache_directory, version)
        return tools_install_directory


def install_fpp_via_git(installation_directory: Path, version: str):
    """Installs FPP from git

    Should FPP not be available as a published version, this will clone the FPP repo, checkout, and build the FPP tools
    for the given version. This requires the following tools to exist on the system: git, sh, java, and sbt. These tools
    will be checked and then the process will run and intall into the specified directory.

    Args:
        installation_directory: directory to install into
        version: FPP tools version to install
    """

    tools = ["git", "sh", "java"]
    for tool in tools:
        if not shutil.which(tool):
            print(f"-- ERROR -- {tool} must exist on PATH")
            sys.exit(-1)
    with tempfile.TemporaryDirectory() as tools_directory:
        os.chdir(tools_directory)
        wget(SBT_URL)
        with tarfile.open(os.path.basename(SBT_URL)) as archive:
            archive.extractall(".")
        sbt_path = Path(tools_directory) / "sbt" / "bin"
        subprocess_environment = os.environ.copy()
        subprocess_environment["PATH"] = f"{ sbt_path }:{ os.environ.get('PATH') }"
        with tempfile.TemporaryDirectory() as build_directory:
            steps = [
                ["git", "clone", GITHUB_URL, str(build_directory)],
                ["git", "checkout", version],
                [
                    os.path.join(build_directory, "compiler", "install"),
                    str(installation_directory),
                ],
            ]
            for step in steps:
                print(f"-- INFO  -- Running { ' '.join(step) }")
                completed = subprocess.run(step, cwd=build_directory, env=subprocess_environment)
                if completed.returncode != 0:
                    print(f"-- ERROR -- Failed to run { ' '.join(step) }")
                    sys.exit(-1)

    return installation_directory


def iterate_fpp_tools(working_dir: Path) -> Iterable[Path]:
    """Iterates through FPP tools"""
    untar_possibility = working_dir / get_artifact_string(
        __FPP_TOOLS_VERSION__
    ).replace(".tar.gz", "")
    if not any(os.scandir(working_dir)):
        working_dir = install_fpp(working_dir)
    elif untar_possibility.exists() and any(os.scandir(untar_possibility)):
        working_dir = untar_possibility
    return working_dir.iterdir()


@contextmanager
def clean_install_fpp():
    """Cleanly installs FPP in subdirectory, cleaning when finished"""
    WORKING_DIR.mkdir(exist_ok=True)

    def lazy_loader():
        """Prevents the download of FPP items until actually enumerated"""
        for item in iterate_fpp_tools(WORKING_DIR):
            yield item

    yield lazy_loader()
