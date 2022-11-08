// ======================================================================
// \title  PrimitivePortAc.hpp
// \author Generated by fpp-to-cpp
// \brief  hpp file for Primitive port
// ======================================================================

#ifndef PrimitivePortAc_HPP
#define PrimitivePortAc_HPP

#include "FpConfig.hpp"
#include "Fw/Cmd/CmdArgBuffer.hpp"
#include "Fw/Comp/PassiveComponentBase.hpp"
#include "Fw/Port/InputPortBase.hpp"
#include "Fw/Port/OutputPortBase.hpp"
#include "Fw/Types/Serializable.hpp"
#include "Fw/Types/StringType.hpp"
#include "cstdio"
#include "cstring"

//! Input Primitive port
//! A port with primitive parameters
class InputPrimitivePort :
  public Fw::InputPortBase
{

  public:

    // ----------------------------------------------------------------------
    // Constants
    // ----------------------------------------------------------------------

    enum {
      //! The size of the serial representations of the port arguments
      SERIALIZED_SIZE =
        sizeof(U32) +
        sizeof(U32) +
        sizeof(F32) +
        sizeof(F32) +
        sizeof(U8) +
        sizeof(U8)
    };

  public:

    // ----------------------------------------------------------------------
    // Types
    // ----------------------------------------------------------------------

    //! The port callback function type
    typedef void (*CompFuncPtr)(
      Fw::PassiveComponentBase* callComp,
      NATIVE_INT_TYPE portNum,
      U32 u32,
      U32& u32Ref,
      F32 f32,
      F32& f32Ref,
      bool b,
      bool& bRef
    );

  public:

    // ----------------------------------------------------------------------
    // Input Port Member functions
    // ----------------------------------------------------------------------

    //! Constructor
    InputPrimitivePort();

    //! Initialization function
    void init();

    //! Register a component
    void addCallComp(
        Fw::PassiveComponentBase* callComp, //!< The containing component
        CompFuncPtr funcPtr //!< The port callback function
    );

    //! Invoke a port interface
    void invoke(
        U32 u32,
        U32& u32Ref,
        F32 f32,
        F32& f32Ref,
        bool b,
        bool& bRef
    );

  private:

#if FW_PORT_SERIALIZATION == 1

    //! Invoke the port with serialized arguments
    Fw::SerializeStatus invokeSerial(Fw::SerializeBufferBase& _buffer);

#endif

  private:

    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The pointer to the port callback function
    CompFuncPtr m_func;

};

//! Output Primitive port
//! A port with primitive parameters
class OutputPrimitivePort :
  public Fw::OutputPortBase
{

  public:

    // ----------------------------------------------------------------------
    // Output Port Member functions
    // ----------------------------------------------------------------------

    //! Constructor
    OutputPrimitivePort();

    //! Initialization function
    void init();

    //! Register an input port
    void addCallPort(
        InputPrimitivePort* callPort //!< The input port
    );

    //! Invoke a port interface
    void invoke(
        U32 u32,
        U32& u32Ref,
        F32 f32,
        F32& f32Ref,
        bool b,
        bool& bRef
    );

  private:

    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The pointer to the input port
    InputPrimitivePort* m_port;

};

#endif
