// ======================================================================
// \title  BasicGuardTestEnumStateMachineAc.cpp
// \author Generated by fpp-to-cpp
// \brief  cpp file for BasicGuardTestEnum state machine
// ======================================================================

#include "Fw/Types/Assert.hpp"
#include "state/BasicGuardTestEnumStateMachineAc.hpp"

namespace FppTest {

  namespace SmState {

    // ----------------------------------------------------------------------
    // Constructors and Destructors
    // ----------------------------------------------------------------------

    BasicGuardTestEnumStateMachineBase ::
      BasicGuardTestEnumStateMachineBase()
    {

    }

    BasicGuardTestEnumStateMachineBase ::
      ~BasicGuardTestEnumStateMachineBase()
    {

    }

    // ----------------------------------------------------------------------
    // Initialization
    // ----------------------------------------------------------------------

    void BasicGuardTestEnumStateMachineBase ::
      initBase(const FwEnumStoreType id)
    {
      this->m_id = id;
      this->enter_S(Signal::__FPRIME_AC_INITIAL_TRANSITION);
    }

    // ----------------------------------------------------------------------
    // Getter functions
    // ----------------------------------------------------------------------

    BasicGuardTestEnumStateMachineBase::State BasicGuardTestEnumStateMachineBase ::
      getState() const
    {
      return this->m_state;
    }

    // ----------------------------------------------------------------------
    // Send signal functions
    // ----------------------------------------------------------------------

    void BasicGuardTestEnumStateMachineBase ::
      sendSignal_s(const FppTest::SmHarness::TestEnum& value)
    {
      switch (this->m_state) {
        case State::S:
          if (this->guard_g(Signal::s, value)) {
            this->action_a(Signal::s, value);
            this->enter_T(Signal::s);
          }
          break;
        case State::T:
          break;
        default:
          FW_ASSERT(0, static_cast<FwAssertArgType>(this->m_state));
          break;
      }
    }

    // ----------------------------------------------------------------------
    // State and junction entry
    // ----------------------------------------------------------------------

    void BasicGuardTestEnumStateMachineBase ::
      enter_T(Signal signal)
    {
      this->m_state = State::T;
    }

    void BasicGuardTestEnumStateMachineBase ::
      enter_S(Signal signal)
    {
      this->m_state = State::S;
    }

  }

}
