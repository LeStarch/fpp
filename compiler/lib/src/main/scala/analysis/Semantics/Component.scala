package fpp.compiler.analysis

import fpp.compiler.ast._
import fpp.compiler.util._

/** An FPP component */
case class Component(
  /** The AST node defining the component */
  aNode: Ast.Annotated[AstNode[Ast.DefComponent]],
  /** The map from port names to port instances */
  portMap: Map[Name.Unqualified, PortInstance] = Map(),
  /** The map from special port kinds to special port instances */
  specialPortMap: Map[Ast.SpecPortInstance.SpecialKind, PortInstance.Special] = Map(),
  /** The map from command opcodes to commands */
  commandMap: Map[Command.Opcode, Command] = Map(),
  /** The next default opcode */
  defaultOpcode: Int = 0,
  // TODO
) {

  /** Add a port instance */
  def addPortInstance(instance: PortInstance): Result.Result[Component] =
    for {
      c <- updatePortMap(instance)
      c <- instance match {
        case special : PortInstance.Special => updateSpecialPortMap(special)
        case _ => Right(c)
      }
    }
    yield c

  /** Add a command */
  def addCommand(opcodeOpt: Option[Command.Opcode], command: Command): Result.Result[Component] = {
    val opcode = opcodeOpt.getOrElse(defaultOpcode)
    commandMap.get(opcode) match {
      case Some(prevCommand) =>
        val value = Analysis.displayIdValue(opcode)
        val loc = command.getLoc
        val prevLoc = prevCommand.getLoc
        Left(SemanticError.DuplicateOpcodeValue(value, loc, prevLoc))
      case None =>
        val commandMap = this.commandMap + (opcode -> command)
        val component = this.copy(commandMap = commandMap, defaultOpcode = opcode + 1)
        Right(component)
    }
  }

  /** Add a port instance to the port map */
  private def updatePortMap(instance: PortInstance): Result.Result[Component] = {
    val name = instance.getUnqualifiedName
    portMap.get(name) match {
      case Some(prevInstance) =>
        val loc = instance.getLoc
        val prevLoc = prevInstance.getLoc
        Left(SemanticError.DuplicatePortInstance(name, loc, prevLoc))
      case None => 
        val portMap = this.portMap + (name -> instance)
        val component = this.copy(portMap = portMap)
        Right(component)
    }
  }

  /** Add a port instance to the special port map */
  private def updateSpecialPortMap(instance: PortInstance.Special): Result.Result[Component] = {
    val kind = instance.specifier.kind
    specialPortMap.get(kind) match {
      case Some(prevInstance) =>
        val loc = instance.getLoc
        val prevLoc = prevInstance.getLoc
        Left(SemanticError.DuplicatePortInstance(kind.toString, loc, prevLoc))
      case None => 
        val specialPortMap = this.specialPortMap + (kind -> instance)
        val component = this.copy(specialPortMap = specialPortMap)
        Right(component)
    }
  }

}