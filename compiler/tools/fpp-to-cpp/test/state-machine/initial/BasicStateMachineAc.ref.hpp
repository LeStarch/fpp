// ======================================================================
// \title  BasicStateMachineAc.hpp
// \author Generated by fpp-to-cpp
// \brief  hpp file for Basic state machine
// ======================================================================

#ifndef FppTest_SmInitial_BasicStateMachineAc_HPP
#define FppTest_SmInitial_BasicStateMachineAc_HPP

#include <FpConfig.hpp>

#include "Fw/Types/ExternalString.hpp"
#include "Fw/Types/Serializable.hpp"
#include "Fw/Types/String.hpp"

namespace FppTest {

  namespace SmInitial {

    //! A basic state machine
    class BasicStateMachineBase {

      PROTECTED:

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
        };

      PROTECTED:

        // ----------------------------------------------------------------------
        // Constructors and Destructors
        // ----------------------------------------------------------------------

        //! Constructor
        BasicStateMachineBase();

        //! Destructor
        virtual ~BasicStateMachineBase();

      public:

        // ----------------------------------------------------------------------
        // Initialization
        // ----------------------------------------------------------------------

        //! Initialize the state machine
        void init(
            const FwEnumStoreType id //!< The state machine ID
        );

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
