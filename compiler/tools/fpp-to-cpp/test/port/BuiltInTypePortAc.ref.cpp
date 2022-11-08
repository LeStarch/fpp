// ======================================================================
// \title  BuiltInTypePortAc.cpp
// \author Generated by fpp-to-cpp
// \brief  cpp file for BuiltInType port
// ======================================================================

#include "BuiltInTypePortAc.hpp"
#include "Fw/Types/Assert.hpp"
#include "Fw/Types/StringUtils.hpp"

namespace {

  // ----------------------------------------------------------------------
  // Port _buffer class
  // ----------------------------------------------------------------------

  class BuiltInTypePortBuffer : public Fw::SerializeBufferBase {

    public:

      NATIVE_UINT_TYPE getBuffCapacity() const {
        return InputBuiltInTypePort::SERIALIZED_SIZE;
      }

      U8* getBuffAddr() {
        return m_buff;
      }

      const U8* getBuffAddr() const {
        return m_buff;
      }

    private:

      U8 m_buff[InputBuiltInTypePort::SERIALIZED_SIZE];

  };

}

// ----------------------------------------------------------------------
// Input Port Member functions
// ----------------------------------------------------------------------

InputBuiltInTypePort ::
  InputBuiltInTypePort() :
    Fw::InputPortBase(),
    m_func(nullptr)
{

}

void InputBuiltInTypePort ::
  init()
{
  Fw::InputPortBase::init();
}

void InputBuiltInTypePort ::
  addCallComp(
      Fw::PassiveComponentBase* callComp,
      CompFuncPtr funcPtr
  )
{
  FW_ASSERT(callComp);
  FW_ASSERT(funcPtr);

  this->m_comp = callComp;
  this->m_func = funcPtr;
  this->m_connObj = callComp;
}

void InputBuiltInTypePort ::
  invoke(
      FwOpcodeType t,
      FwOpcodeType& tRef
  )
{
#if FW_PORT_TRACING == 1
  this->trace();
#endif

  FW_ASSERT(this->m_comp);
  FW_ASSERT(this->m_func);

  return this->m_func(this->m_comp, this->m_portNum, t, tRef);
}

#if FW_PORT_SERIALIZATION == 1

Fw::SerializeStatus InputBuiltInTypePort ::
  invokeSerial(Fw::SerializeBufferBase& _buffer)
{
  Fw::SerializeStatus _status;

#if FW_PORT_SERIALIZATION == 1
  this->trace();
#endif

  FW_ASSERT(this->m_comp);
  FW_ASSERT(this->m_func);

  FwOpcodeType t;
  _status = _buffer.deserialize(t);
  if (_status != Fw::FW_SERIALIZE_OK) {
    return _status;
  }

  FwOpcodeType tRef;
  _status = _buffer.deserialize(tRef);
  if (_status != Fw::FW_SERIALIZE_OK) {
    return _status;
  }

  this->m_func(this->m_comp, this->m_portNum, t, tRef);

  return Fw::FW_SERIALIZE_OK;
}

#endif

// ----------------------------------------------------------------------
// Output Port Member functions
// ----------------------------------------------------------------------

OutputBuiltInTypePort ::
  OutputBuiltInTypePort() :
    Fw::OutputPortBase(),
    m_port(nullptr)
{

}

void OutputBuiltInTypePort ::
  init()
{
  Fw::OutputPortBase::init();
}

void OutputBuiltInTypePort ::
  addCallPort(InputBuiltInTypePort* callPort)
{
  FW_ASSERT(callPort);

  this->m_port = callPort;
  this->m_connObj = callPort;

#if FW_PORT_SERIALIZATION == 1
  this->m_serPort = nullptr;
#endif
}

void OutputBuiltInTypePort ::
  invoke(
      FwOpcodeType t,
      FwOpcodeType& tRef
  )
{
#if FW_PORT_TRACING == 1
  this->trace();
#endif

#if FW_PORT_SERIALIZATION
  FW_ASSERT(this->m_port || this->m_serPort);
#else
  FW_ASSERT(this->m_port);
#endif
  if (this->m_port) {
    this->m_port->invoke(t, tRef);
#if FW_PORT_SERIALIZATION
  } else if (this->m_serPort) {
    Fw::SerializeStatus _status;
    BuiltInTypePortBuffer _buffer;

    _status = _buffer.serialize(t);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK, static_cast<FwAssertArgType>(_status));

    _status = _buffer.serialize(tRef);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK, static_cast<FwAssertArgType>(_status));

    _status = this->m_serPort->invokeSerial(_buffer);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK, static_cast<FwAssertArgType>(_status));
  }
#else
  }
#endif
}
