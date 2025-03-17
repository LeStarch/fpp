// ======================================================================
// \title  StructWithAliasSerializableAc.cpp
// \author Generated by fpp-to-cpp
// \brief  cpp file for StructWithAlias struct
// ======================================================================

#include "Fw/Types/Assert.hpp"
#include "base/StructWithAliasSerializableAc.hpp"

// ----------------------------------------------------------------------
// Constructors
// ----------------------------------------------------------------------

StructWithAlias ::
  StructWithAlias() :
    Serializable(),
    m_x(0),
    m_y(m___fprime_ac_y_buffer, sizeof m___fprime_ac_y_buffer, Fw::String("")),
    m_z(A(0, 0, 0)),
    m_w(A(0, 0, 0))
{

}

StructWithAlias ::
  StructWithAlias(
      AliasPrim1 x,
      const Fw::StringBase& y,
      const AliasArray& z,
      const AliasAliasArray& w
  ) :
    Serializable(),
    m_x(x),
    m_y(m___fprime_ac_y_buffer, sizeof m___fprime_ac_y_buffer, y),
    m_z(z),
    m_w(w)
{

}

StructWithAlias ::
  StructWithAlias(const StructWithAlias& obj) :
    Serializable(),
    m_x(obj.m_x),
    m_y(m___fprime_ac_y_buffer, sizeof m___fprime_ac_y_buffer, obj.m_y),
    m_z(obj.m_z),
    m_w(obj.m_w)
{

}

// ----------------------------------------------------------------------
// Operators
// ----------------------------------------------------------------------

StructWithAlias& StructWithAlias ::
  operator=(const StructWithAlias& obj)
{
  if (this == &obj) {
    return *this;
  }

  set(obj.m_x, obj.m_y, obj.m_z, obj.m_w);
  return *this;
}

bool StructWithAlias ::
  operator==(const StructWithAlias& obj) const
{
  if (this == &obj) { return true; }
  return (
    (this->m_x == obj.m_x) &&
    (this->m_y == obj.m_y) &&
    (this->m_z == obj.m_z) &&
    (this->m_w == obj.m_w)
  );
}

bool StructWithAlias ::
  operator!=(const StructWithAlias& obj) const
{
  return !(*this == obj);
}

#ifdef BUILD_UT

std::ostream& operator<<(std::ostream& os, const StructWithAlias& obj) {
  Fw::String s;
  obj.toString(s);
  os << s.toChar();
  return os;
}

#endif

// ----------------------------------------------------------------------
// Member functions
// ----------------------------------------------------------------------

Fw::SerializeStatus StructWithAlias ::
  serialize(Fw::SerializeBufferBase& buffer) const
{
  Fw::SerializeStatus status;

  status = buffer.serialize(this->m_x);
  if (status != Fw::FW_SERIALIZE_OK) {
    return status;
  }
  status = buffer.serialize(this->m_y);
  if (status != Fw::FW_SERIALIZE_OK) {
    return status;
  }
  status = buffer.serialize(this->m_z);
  if (status != Fw::FW_SERIALIZE_OK) {
    return status;
  }
  status = buffer.serialize(this->m_w);
  if (status != Fw::FW_SERIALIZE_OK) {
    return status;
  }

  return status;
}

Fw::SerializeStatus StructWithAlias ::
  deserialize(Fw::SerializeBufferBase& buffer)
{
  Fw::SerializeStatus status;

  status = buffer.deserialize(this->m_x);
  if (status != Fw::FW_SERIALIZE_OK) {
    return status;
  }
  status = buffer.deserialize(this->m_y);
  if (status != Fw::FW_SERIALIZE_OK) {
    return status;
  }
  status = buffer.deserialize(this->m_z);
  if (status != Fw::FW_SERIALIZE_OK) {
    return status;
  }
  status = buffer.deserialize(this->m_w);
  if (status != Fw::FW_SERIALIZE_OK) {
    return status;
  }

  return status;
}

#if FW_SERIALIZABLE_TO_STRING

void StructWithAlias ::
  toString(Fw::StringBase& sb) const
{
  static const char* formatString =
    "( "
    "x = %s, "
    "y = %s, "
    "z = %s, "
    "w = %s"
    " )";

  // Declare strings to hold any serializable toString() arguments
  Fw::String zStr;
  Fw::String wStr;

  // Call toString for arrays and serializable types
  this->m_z.toString(zStr);
  this->m_w.toString(wStr);

  sb.format(
    formatString,
    this->m_x,
    this->m_y.toChar(),
    zStr.toChar(),
    wStr.toChar()
  );
}

#endif

// ----------------------------------------------------------------------
// Setter functions
// ----------------------------------------------------------------------

void StructWithAlias ::
  set(
      AliasPrim1 x,
      const Fw::StringBase& y,
      const AliasArray& z,
      const AliasAliasArray& w
  )
{
  this->m_x = x;
  this->m_y = y;
  this->m_z = z;
  this->m_w = w;
}

void StructWithAlias ::
  setx(AliasPrim1 x)
{
  this->m_x = x;
}

void StructWithAlias ::
  sety(const Fw::StringBase& y)
{
  this->m_y = y;
}

void StructWithAlias ::
  setz(const AliasArray& z)
{
  this->m_z = z;
}

void StructWithAlias ::
  setw(const AliasAliasArray& w)
{
  this->m_w = w;
}
