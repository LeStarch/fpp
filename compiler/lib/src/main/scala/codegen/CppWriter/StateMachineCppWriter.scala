package fpp.compiler.codegen

import fpp.compiler.analysis._
import fpp.compiler.ast._

/** Writes out C++ for struct definitions */
case class StateMachineCppWriter(
  s: CppWriterState,
  aNode: Ast.Annotated[AstNode[Ast.DefStateMachine]]
) extends CppWriterUtils {

  private val node = aNode._2

  private val data = node.data

  private val symbol = Symbol.StateMachine(aNode)

  private val stateMachine: StateMachine = s.a.stateMachineMap(symbol)

  private val name = s.getName(symbol)

  private val className = s"${name}StateMachineBase"

  private val fileName = ComputeCppFiles.FileNames.getStateMachine(
    name,
    StateMachine.Kind.Internal
  )

  private val namespaceIdentList = s.getNamespaceIdentList(symbol)

  private val typeCppWriter = TypeCppWriter(s)

  private val astMembers = data.members.get

  private val uninitStateName = "__FPRIME_AC_UNINITIALIZED"

  private val leafStates = StateMachine.getLeafStates(symbol)

  private val commentedLeafStateNames =
    leafStates.toList.map(
      state => {
        val comment = AnnotationCppWriter.asStringOpt(state).map(lines).
          getOrElse(Nil).map(CppDocWriter.addCommentPrefix ("//!") _)
        val ident = CppWriterState.identFromQualifiedSmSymbolName(
          stateMachine.sma,
          StateMachineSymbol.State(state)
        )
        (comment, ident)
      }
    ).sortBy(_._2)

  private val actionSymbols =
    StateMachine.getActions(aNode._2.data).map(StateMachineSymbol.Action(_))

  private val actionParamName = "__fprime_ac_param"

  def write: CppDoc = {
    val includeGuard = s.includeGuardFromQualifiedName(symbol, fileName)
    CppWriter.createCppDoc(
      s"$name state machine",
      fileName,
      includeGuard,
      getMembers,
      s.toolName
    )
  }

  private def getMembers: List[CppDoc.Member] = {
    val hppIncludes = getHppIncludes
    val cppIncludes = getCppIncludes
    val cls = classMember(
      AnnotationCppWriter.asStringOpt(aNode),
      className,
      None,
      getClassMembers
    )
    hppIncludes :: cppIncludes :: wrapInNamespaces(namespaceIdentList, List(cls))
  }

  private def getHppIncludes: CppDoc.Member = {
    val symbolHeaders = {
      val Right(a) = UsedSymbols.defStateMachineAnnotatedNode(s.a, aNode)
      s.writeIncludeDirectives(a.usedSymbolSet)
    }
    val userHeaders = List.concat(
      standardUserHppHeaders,
      symbolHeaders
    ).sorted
    val headerLines = List.concat(
      addBlankPrefix(standardSystemHppHeaders.map(line)),
      addBlankPrefix(userHeaders.map(line))
    )
    linesMember(headerLines)
  }

  private def getCppIncludes: CppDoc.Member = {
    val userHeaders = List.concat(
      standardUserCppHeaders,
      List(s"${s.getRelativePath(fileName)}.hpp").map(CppWriter.headerString)
    ).sorted
    val headerLines = List.concat(
      addBlankPrefix(standardSystemCppHeaders.map(line)),
      addBlankPrefix(userHeaders.map(line))
    )
    linesMember(headerLines, CppDoc.Lines.Cpp)
  }

  private def getClassMembers: List[CppDoc.Class.Member] =
    List.concat(
      getTypeMembers,
      getConstructorDestructorMembers,
      getInitMembers,
      getActionMembers,
      getEntryMembers,
      getVariableMembers
    )

  private def getTypeMembers: List[CppDoc.Class.Member] = {
    val pairs = (lines("//! The uninitialized state"), uninitStateName) ::
      commentedLeafStateNames
    val enumLines = pairs.flatMap {
      case (comment, name) => List.concat(comment, lines(s"$name,"))
    }
    val memberLines = List.concat(
      CppDocWriter.writeDoxygenComment("//! The state type"),
      wrapInEnumClass("State", enumLines, Some("FwEnumStoreType"))
    )
    addAccessTagAndComment(
      "PROTECTED",
      "Types",
      List(linesClassMember(memberLines)),
      CppDoc.Lines.Hpp
    )
  }

  private def getConstructorDestructorMembers: List[CppDoc.Class.Member] =
    addAccessTagAndComment(
      "PROTECTED",
      "Constructors and Destructors",
      List(
        constructorClassMember(
          Some("Constructor"),
          Nil,
          Nil,
          Nil
        ),
        destructorClassMember(
          Some("Destructor"),
          Nil,
          CppDoc.Class.Destructor.Virtual
        )
      )
    )

  private def getInitMembers: List[CppDoc.Class.Member] =
    addAccessTagAndComment(
      "public",
      "Initialization",
      List(linesClassMember(lines("\n// TODO"), CppDoc.Lines.Both))
    )

  private def getActionFnName(sym: StateMachineSymbol.Action): String =
    s"action_${sym.getUnqualifiedName}"

  private def getActionFnParams(sym: StateMachineSymbol.Action):
  List[CppDoc.Function.Param] = sym.node._2.data.typeName match {
    case Some(node) =>
      val paramCppType = {
        val paramType = s.a.typeMap(node.id)
        typeCppWriter.write(paramType)
      }
      List(
        CppDoc.Function.Param(
          CppDoc.Type(paramCppType),
          actionParamName,
          Some("The action parameter")
        )
      )
    case None => Nil
  }

  private def getActionMember(sym: StateMachineSymbol.Action):
  CppDoc.Class.Member.Function = {
    functionClassMember(
      Some(s"Action ${sym.getUnqualifiedName}"),
      getActionFnName(sym),
      getActionFnParams(sym),
      CppDoc.Type("void"),
      Nil,
      CppDoc.Function.PureVirtual
    )
  }

  private def getActionMembers: List[CppDoc.Class.Member] =
    addAccessTagAndComment(
      "PROTECTED",
      "Actions",
      actionSymbols.map(getActionMember),
      CppDoc.Lines.Hpp
    )

  private def getEntryMembers: List[CppDoc.Class.Member] =
    addAccessTagAndComment(
      "PRIVATE",
      "State and junction entry",
      List(linesClassMember(lines("\n// TODO"), CppDoc.Lines.Both))
    )

  private def getVariableMembers: List[CppDoc.Class.Member] =
    addAccessTagAndComment(
      "PROTECTED",
      "Member variables",
      List(
        linesClassMember(
          Line.blank ::
          lines(
            s"""|//! The state machine ID
                |FwEnumStoreType m_id = 0;
                |
                |//! The state
                |State m_state = State::$uninitStateName;"""

          )
        )
      ),
      CppDoc.Lines.Hpp
    )

}
