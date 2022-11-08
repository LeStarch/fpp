// ======================================================================
// \title  KwdNamePortAc.cpp
// \author Generated by fpp-to-cpp
// \brief  cpp file for KwdName port
// ======================================================================

#include "Fw/Types/Assert.hpp"
#include "Fw/Types/StringUtils.hpp"
#include "KwdNamePortAc.hpp"

namespace {

  // ----------------------------------------------------------------------
  // Port _buffer class
  // ----------------------------------------------------------------------

  class KwdNamePortBuffer : public Fw::SerializeBufferBase {

    public:

      NATIVE_UINT_TYPE getBuffCapacity() const {
        return InputKwdNamePort::SERIALIZED_SIZE;
      }

      U8* getBuffAddr() {
        return m_buff;
      }

      const U8* getBuffAddr() const {
        return m_buff;
      }

    private:

      U8 m_buff[InputKwdNamePort::SERIALIZED_SIZE];

  };

}

// ----------------------------------------------------------------------
// Input Port Member functions
// ----------------------------------------------------------------------

InputKwdNamePort ::
  InputKwdNamePort() :
    Fw::InputPortBase(),
    m_func(nullptr)
{

}

void InputKwdNamePort ::
  init()
{
  Fw::InputPortBase::init();
}

void InputKwdNamePort ::
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

void InputKwdNamePort ::
  invoke(U32& time)
{
#if FW_PORT_TRACING == 1
  this->trace();
#endif

  FW_ASSERT(this->m_comp);
  FW_ASSERT(this->m_func);

  return this->m_func(this->m_comp, this->m_portNum, time);
}

#if FW_PORT_SERIALIZATION == 1

Fw::SerializeStatus InputKwdNamePort ::
  invokeSerial(Fw::SerializeBufferBase& _buffer)
{
  Fw::SerializeStatus _status;

#if FW_PORT_SERIALIZATION == 1
  this->trace();
#endif

  FW_ASSERT(this->m_comp);
  FW_ASSERT(this->m_func);

  U32 time;
  _status = _buffer.deserialize(time);
  if (_status != Fw::FW_SERIALIZE_OK) {
    return _status;
  }

  this->m_func(this->m_comp, this->m_portNum, time);

  return Fw::FW_SERIALIZE_OK;
}

#endif

// ----------------------------------------------------------------------
// Output Port Member functions
// ----------------------------------------------------------------------

OutputKwdNamePort ::
  OutputKwdNamePort() :
    Fw::OutputPortBase(),
    m_port(nullptr)
{

}

void OutputKwdNamePort ::
  init()
{
  Fw::OutputPortBase::init();
}

void OutputKwdNamePort ::
  addCallPort(InputKwdNamePort* callPort)
{
  FW_ASSERT(callPort);

  this->m_port = callPort;
  this->m_connObj = callPort;

#if FW_PORT_SERIALIZATION == 1
  this->m_serPort = nullptr;
#endif
}

void OutputKwdNamePort ::
  invoke(U32& time)
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
    this->m_port->invoke(time);
#if FW_PORT_SERIALIZATION
  } else if (this->m_serPort) {
    Fw::SerializeStatus _status;
    KwdNamePortBuffer _buffer;

    _status = _buffer.serialize(time);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK, static_cast<FwAssertArgType>(_status));

    _status = this->m_serPort->invokeSerial(_buffer);
    FW_ASSERT(_status == Fw::FW_SERIALIZE_OK, static_cast<FwAssertArgType>(_status));
  }
#else
  }
#endif
}
