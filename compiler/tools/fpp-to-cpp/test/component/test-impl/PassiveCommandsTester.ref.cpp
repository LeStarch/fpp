// ======================================================================
// \title  PassiveCommandsTester.cpp
// \author [user name]
// \brief  cpp file for PassiveCommands component test harness implementation class
// ======================================================================

#include "PassiveCommandsTester.hpp"

// ----------------------------------------------------------------------
// Construction and destruction
// ----------------------------------------------------------------------

PassiveCommandsTester ::
  PassiveCommandsTester() :
    PassiveCommandsGTestBase("PassiveCommandsTester", PassiveCommandsTester::MAX_HISTORY_SIZE),
    component("PassiveCommands")
{
  this->initComponents();
  this->connectPorts();
}

PassiveCommandsTester ::
  ~PassiveCommandsTester()
{

}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void PassiveCommandsTester ::
  toDo()
{
  // TODO
}

// ----------------------------------------------------------------------
// Handlers for typed from ports
// ----------------------------------------------------------------------

void PassiveCommandsTester ::
  from_noArgsOut_handler(FwIndexType portNum)
{
  this->pushFromPortEntry_noArgsOut();
}

U32 PassiveCommandsTester ::
  from_noArgsReturnOut_handler(FwIndexType portNum)
{
  this->pushFromPortEntry_noArgsReturnOut();
  return 0;
}

void PassiveCommandsTester ::
  from_typedOut_handler(
      FwIndexType portNum,
      U32 u32,
      F32 f32,
      bool b,
      const Ports::TypedPortStrings::StringSize80& str1,
      const E& e,
      const A& a,
      const S& s
  )
{
  this->pushFromPortEntry_typedOut(u32, f32, b, str1, e, a, s);
}

F32 PassiveCommandsTester ::
  from_typedReturnOut_handler(
      FwIndexType portNum,
      U32 u32,
      F32 f32,
      bool b,
      const Ports::TypedReturnPortStrings::StringSize80& str2,
      const E& e,
      const A& a,
      const S& s
  )
{
  this->pushFromPortEntry_typedReturnOut(u32, f32, b, str2, e, a, s);
  return 0.0f;
}
