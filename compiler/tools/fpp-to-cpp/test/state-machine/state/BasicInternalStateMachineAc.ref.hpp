// ======================================================================
// \title  BasicInternalStateMachineAc.hpp
// \author Generated by fpp-to-cpp
// \brief  hpp file for BasicInternal state machine
// ======================================================================

#ifndef FppTest_SmState_BasicInternalStateMachineAc_HPP
#define FppTest_SmState_BasicInternalStateMachineAc_HPP

#include <FpConfig.hpp>

#include "Fw/Types/ExternalString.hpp"
#include "Fw/Types/Serializable.hpp"
#include "Fw/Types/String.hpp"

namespace FppTest {

  namespace SmState {

    //! A basic state machine with an internal transition
    class BasicInternalStateMachineBase {

      public:

        // ----------------------------------------------------------------------
        // Types
        // ----------------------------------------------------------------------

        //! The state type
        enum class State : FwEnumStoreType {
          //! The uninitialized state
          __FPRIME_AC_UNINITIALIZED,
          //! State S
          S,
        };

        //! The signal type
        enum class Signal : FwEnumStoreType {
          //! The initial transition
          __FPRIME_AC_INITIAL_TRANSITION,
          //! Signal s
          s,
        };

      PROTECTED:

        // ----------------------------------------------------------------------
        // Constructors and Destructors
        // ----------------------------------------------------------------------

        //! Constructor
        BasicInternalStateMachineBase();

        //! Destructor
        virtual ~BasicInternalStateMachineBase();

      protected:

        // ----------------------------------------------------------------------
        // Initialization
        // ----------------------------------------------------------------------

        //! Initialize the state machine
        void initBase(
            const FwEnumStoreType id //!< The state machine ID
        );

      public:

        // ----------------------------------------------------------------------
        // Getter functions
        // ----------------------------------------------------------------------

        //! Get the state
        BasicInternalStateMachineBase::State getState() const;

      public:

        // ----------------------------------------------------------------------
        // Send signal functions
        // ----------------------------------------------------------------------

        //! Signal s
        void sendSignal_s();

      PROTECTED:

        // ----------------------------------------------------------------------
        // Actions
        // ----------------------------------------------------------------------

        //! Action a
        virtual void action_a(
            Signal signal //!< The signal
        ) = 0;

      PRIVATE:

        // ----------------------------------------------------------------------
        // State and junction entry
        // ----------------------------------------------------------------------

        //! Enter state S
        void enter_S(
            Signal signal //!< The signal
        );

      PROTECTED:

        // ----------------------------------------------------------------------
        // Member variables
        // ----------------------------------------------------------------------

        //! The state machine ID
        FwEnumStoreType m_id = 0;

        //! The state
        State m_state = State::__FPRIME_AC_UNINITIALIZED;

    };

  }

}

#endif
