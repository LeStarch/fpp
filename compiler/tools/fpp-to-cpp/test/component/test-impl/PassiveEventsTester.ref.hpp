// ======================================================================
// \title  PassiveEventsTester.hpp
// \author [user name]
// \brief  hpp file for PassiveEvents component test harness implementation class
// ======================================================================

#ifndef PassiveEventsTester_HPP
#define PassiveEventsTester_HPP

#include "PassiveEventsGTestBase.hpp"
#include "PassiveEvents.hpp"

class PassiveEventsTester final :
  public PassiveEventsGTestBase
{

  public:

    // ----------------------------------------------------------------------
    // Constants
    // ----------------------------------------------------------------------

    // Maximum size of histories storing events, telemetry, and port outputs
    static const FwSizeType MAX_HISTORY_SIZE = 10;

    // Instance ID supplied to the component instance under test
    static const FwEnumStoreType TEST_INSTANCE_ID = 0;

  public:

    // ----------------------------------------------------------------------
    // Construction and destruction
    // ----------------------------------------------------------------------

    //! Construct object PassiveEventsTester
    PassiveEventsTester();

    //! Destroy object PassiveEventsTester
    ~PassiveEventsTester();

  public:

    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    //! To do
    void toDo();

  private:

    // ----------------------------------------------------------------------
    // Helper functions
    // ----------------------------------------------------------------------

    //! Connect ports
    void connectPorts();

    //! Initialize components
    void initComponents();

  private:

    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The component under test
    PassiveEvents component;

};

#endif
