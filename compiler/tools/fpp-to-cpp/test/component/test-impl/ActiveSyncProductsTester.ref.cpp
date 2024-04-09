// ======================================================================
// \title  ActiveSyncProductsTester.cpp
// \author [user name]
// \brief  cpp file for ActiveSyncProducts component test harness implementation class
// ======================================================================

#include "ActiveSyncProductsTester.hpp"

// ----------------------------------------------------------------------
// Construction and destruction
// ----------------------------------------------------------------------

ActiveSyncProductsTester ::
  ActiveSyncProductsTester() :
    ActiveSyncProductsGTestBase("ActiveSyncProductsTester", ActiveSyncProductsTester::MAX_HISTORY_SIZE),
    component("ActiveSyncProducts")
{
  this->initComponents();
  this->connectPorts();
}

ActiveSyncProductsTester ::
  ~ActiveSyncProductsTester()
{

}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void ActiveSyncProductsTester ::
  toDo()
{
  // TODO
}

// ----------------------------------------------------------------------
// Handlers for typed from ports
// ----------------------------------------------------------------------

void ActiveSyncProductsTester ::
  from_noArgsOut_handler(FwIndexType portNum)
{
  this->pushFromPortEntry_noArgsOut();
}

U32 ActiveSyncProductsTester ::
  from_noArgsReturnOut_handler(FwIndexType portNum)
{
  this->pushFromPortEntry_noArgsReturnOut();
  return 0;
}

void ActiveSyncProductsTester ::
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

F32 ActiveSyncProductsTester ::
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
