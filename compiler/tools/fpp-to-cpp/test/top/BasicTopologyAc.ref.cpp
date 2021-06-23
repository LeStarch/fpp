// ====================================================================== 
// \title  BasicTopologyAc.cpp
// \author Generated by fpp-to-cpp
// \brief  cpp file for Basic topology
//
// \copyright
// Copyright (c) 2021 California Institute of Technology.
// U.S. Government sponsorship acknowledged.
// All rights reserved.
// ======================================================================

#include "BasicTopologyAc.hpp"

namespace M {

  namespace {

    // ----------------------------------------------------------------------
    // Component configuration objects
    // ----------------------------------------------------------------------

    namespace ConfigObjects {

      namespace active2 {
        U32 x = 0;
      }

    }

    // ----------------------------------------------------------------------
    // Component instances
    // ----------------------------------------------------------------------

    // active1
    Active active1(FW_OPTIONAL_NAME("active1"));

    // active2
    Active active1();

    // passive1
    Passive passive1(FW_OPTIONAL_NAME("passive1"));

    // ----------------------------------------------------------------------
    // Private functions
    // ----------------------------------------------------------------------

    // Initialize components
    void initComponents(const TopologyState& state) {
      active1.init(QueueSizes::active1, InstanceIDs::active1);
      active2.initSpecial();
      passive1.init(InstanceIDs::passive1);
    }

    // Configure components
    void configComponents(const TopologyState& state) {
      active2.config();
    }

    // Set component base IDs
    void setBaseIds() {
      active1.setidBase(0x100);
      active2.setidBase(0x200);
      passive1.setidBase(0x300);
    }

    // Connect components
    void connectComponents() {

      // C
      passive1.set_p_OutputPort(
        0,
        active1_get_p_InputPort(0)
      );

    }

    // Start tasks
    void startTasks(const TopologyState& state) {
      active1.start(
        TaskIDs::active1,
        Priorities::active1,
        StackSizes::active1
      );
      active2.startSpecial();
    }

    // Stop tasks
    void stopTasks(const TopologyState& state) {
      active1.exit();
      active2.stopSpecial();
    }

    // Free threads
    void freeThreads(const TopologyState& state) {
      active1.ActiveComponentBase::join(NULL);
      active2.freeSpecial();
    }

  }

}
