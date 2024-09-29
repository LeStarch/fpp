// ======================================================================
// \title  StateToChildStateMachineAc.cpp
// \author Generated by fpp-to-cpp
// \brief  cpp file for StateToChild state machine
// ======================================================================

#include "Fw/Types/Assert.hpp"
#include "state/StateToChildStateMachineAc.hpp"

namespace FppTest {

  namespace SmState {

    // ----------------------------------------------------------------------
    // Constructors and Destructors
    // ----------------------------------------------------------------------

    StateToChildStateMachineBase ::
      StateToChildStateMachineBase()
    {

    }

    StateToChildStateMachineBase ::
      ~StateToChildStateMachineBase()
    {

    }

    // ----------------------------------------------------------------------
    // Initialization
    // ----------------------------------------------------------------------

    void StateToChildStateMachineBase ::
      init(const FwEnumStoreType id)
    {
      this->m_id = id;
      this->enter_S1(Signal::__FPRIME_AC_INITIAL_TRANSITION);
    }

    // ----------------------------------------------------------------------
    // Send signal functions
    // ----------------------------------------------------------------------

    void StateToChildStateMachineBase ::
      sendSignal_S1_to_S2()
    {
      switch (this->m_state) {
        case State::S1_S2:
          this->action_exitS2(Signal::S1_to_S2);
          this->action_a(Signal::S1_to_S2);
          this->enter_S1_S2(Signal::S1_to_S2);
          break;
        case State::S1_S3:
          this->action_exitS3(Signal::S1_to_S2);
          this->action_a(Signal::S1_to_S2);
          this->enter_S1_S2(Signal::S1_to_S2);
          break;
        default:
          FW_ASSERT(0, static_cast<FwAssertArgType>(this->m_state));
          break;
      }
    }

    void StateToChildStateMachineBase ::
      sendSignal_S2_to_S3()
    {
      switch (this->m_state) {
        case State::S1_S2:
          this->action_exitS2(Signal::S2_to_S3);
          this->enter_S1_S3(Signal::S2_to_S3);
          break;
        case State::S1_S3:
          break;
        default:
          FW_ASSERT(0, static_cast<FwAssertArgType>(this->m_state));
          break;
      }
    }

    // ----------------------------------------------------------------------
    // State and junction entry
    // ----------------------------------------------------------------------

    void StateToChildStateMachineBase ::
      enter_S1(Signal signal)
    {
      this->enter_S1_S2(signal);
    }

    void StateToChildStateMachineBase ::
      enter_S1_S2(Signal signal)
    {
      this->action_enterS2(signal);
      this->m_state = State::S1_S2;
    }

    void StateToChildStateMachineBase ::
      enter_S1_S3(Signal signal)
    {
      this->action_enterS3(signal);
      this->m_state = State::S1_S3;
    }

  }

}
