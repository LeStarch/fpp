package fpp.compiler.tools

import fpp.compiler.analysis._
import fpp.compiler.ast._
import fpp.compiler.codegen._
import fpp.compiler.syntax._
import fpp.compiler.transform._
import fpp.compiler.util._
import scopt.OParser

object FPPToJson {

  case class Options(
    dir: Option[String] = None,
    files: List[File] = Nil,
    imports: List[File] = Nil,
  )

  def command(options: Options) = {
    val files = options.files.reverse match {
      case Nil => List(File.StdIn)
      case list => list
    }
    val analysis = Analysis(inputFileSet = options.files.toSet)
    for {
      tulFiles <- Result.map(files, Parser.parseFile (Parser.transUnit) (None) _)
      aTulFiles <- ResolveSpecInclude.transformList(
        analysis,
        tulFiles, 
        ResolveSpecInclude.transUnit
      )
      tulFiles <- Right(aTulFiles._2)
      tulImports <- Result.map(
        options.imports,
        Parser.parseFile (Parser.transUnit) (None) _
      )
      analysis <- CheckSemantics.tuList(analysis, tulFiles ++ tulImports)



      s <- ComputeCppFiles.visitList(
        CppWriterState(a),
        tulFiles,
        ComputeCppFiles.transUnit
      )
      _ <- options.names match {
        case Some(fileName) => writeCppFileNames(
          s.locationMap.toList.map(_._1), fileName
        )
        case None => Right(())
      }
      _ <- {
        val dir = options.dir match {
          case Some(dir1) => dir1
          case None => "."
        }
        val state = CppWriterState(
          a,
          dir,
          options.guardPrefix,
          options.pathPrefixes,
          options.defaultStringSize,
          Some(name)
        )
        CppWriter.tuList(state, tulFiles)
      }
    } yield ()
  }

  def main(args: Array[String]) = {
    Error.setTool(Tool(name))
    val options = OParser.parse(oparser, args, Options())
    for { result <- options } yield {
      command(result) match {
        case Left(error) => {
          error.print
          System.exit(1)
        }
        case _ => ()
      }
    }
    ()
  }

  val builder = OParser.builder[Options]

  val name = "fpp-to-json"

  val oparser = {
    import builder._
    OParser.sequence(
      programName(name),
      head(name, Version.v),
      help('h', "help").text("print this message and exit"),
      opt[String]('d', "directory")
        .valueName("<dir>")
        .action((d, c) => c.copy(dir = Some(d)))
        .text("output directory"),
      opt[Seq[String]]('i', "imports")
        .valueName("<file1>,<file2>...")
        .action((i, c) => c.copy(imports = i.toList.map(File.fromString(_))))
        .text("files to import"),
      arg[String]("file ...")
        .unbounded()
        .optional()
        .action((f, c) => c.copy(files = File.fromString(f) :: c.files))
        .text("files to translate"),
    )
  }

}
