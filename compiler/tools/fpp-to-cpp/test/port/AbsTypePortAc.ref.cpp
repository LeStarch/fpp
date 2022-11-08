// ======================================================================
// \title  AbsTypePortAc.cpp
// \author Generated by fpp-to-cpp
// \brief  cpp file for AbsType port
// ======================================================================

#include "AbsTypePortAc.hpp"
#include "Fw/Types/Assert.hpp"
#include "Fw/Types/StringUtils.hpp"

namespace {

  // ----------------------------------------------------------------------
  // Port _buffer class
  // ----------------------------------------------------------------------

  class AbsTypePortBuffer : public Fw::SerializeBufferBase {

    public:

      NATIVE_UINT_TYPE getBuffCapacity() const {
        return InputAbsTypePort::SERIALIZED_SIZE;
      }

      U8* getBuffAddr() {
        return m_buff;
      }

      const U8* getBuffAddr() const {
        return m_buff;
      }

    private:

      U8 m_buff[InputAbsTypePort::SERIALIZED_SIZE];

  };

}

// ----------------------------------------------------------------------
// Input Port Member functions
// ----------------------------------------------------------------------

InputAbsTypePort ::
  InputAbsTypePort() :
    Fw::InputPortBase(),
    m_func(nullptr)
{

}

void InputAbsTypePort ::
  init()
{
  Fw::InputPortBase::init();
}

void InputAbsTypePort ::
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

void InputAbsTypePort ::
  invoke(
      const T& t,
      T& tRef
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

Fw::SerializeStatus InputAbsTypePort ::
  invokeSerial(Fw::SerializeBufferBase& _buffer)
{
  Fw::SerializeStatus _status;

#if FW_PORT_SERIALIZATION == 1
  this->trace();
#endif

  FW_ASSERT(this->m_comp);
  FW_ASSERT(this->m_func);

  T t;
  _status = _buffer.deserialize(t);
  if (_status != Fw::FW_SERIALIZE_OK) {
    return _status;
  }

  T tRef;
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

OutputAbsTypePort ::
  OutputAbsTypePort() :
    Fw::OutputPortBase(),
    m_port(nullptr)
{

}

void OutputAbsTypePort ::
  init()
{
  Fw::OutputPortBase::init();
}

void OutputAbsTypePort ::
  addCallPort(InputAbsTypePort* callPort)
{
  FW_ASSERT(callPort);

  this->m_port = callPort;
  this->m_connObj = callPort;

#if FW_PORT_SERIALIZATION == 1
  this->m_serPort = nullptr;
#endif
}

void OutputAbsTypePort ::
  invoke(
      const T& t,
      T& tRef
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
    AbsTypePortBuffer _buffer;

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
