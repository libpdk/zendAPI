// Copyright 2017-2018 zzu_softboy <zzu_softboy@163.com>
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Created by softboy on 2017/08/09.

#include "zapi/ds/DoubleVariant.h"
#include "zapi/ds/NumericVariant.h"
#include "zapi/ds/ArrayItemProxy.h"

namespace zapi
{
namespace ds
{

DoubleVariant::DoubleVariant()
   : Variant(0.0)
{}

DoubleVariant::DoubleVariant(std::int8_t value)
   : Variant(static_cast<double>(value))
{}

DoubleVariant::DoubleVariant(std::int16_t value)
   : Variant(static_cast<double>(value))
{}

DoubleVariant::DoubleVariant(std::int32_t value)
   : Variant(static_cast<double>(value))
{}

DoubleVariant::DoubleVariant(std::int64_t value)
   : Variant(static_cast<double>(value))
{}

DoubleVariant::DoubleVariant(double value)
   : Variant(value)
{}

DoubleVariant::DoubleVariant(zval &other, bool isRef)
   : DoubleVariant(&other, isRef)
{}

DoubleVariant::DoubleVariant(zval &&other, bool isRef)
   : DoubleVariant(&other, isRef)
{}

DoubleVariant::DoubleVariant(zval *other, bool isRef)
{
   zval *self = getZvalPtr();
   if (nullptr != other) {
      if (isRef && Z_TYPE_P(other) == IS_DOUBLE) {
         ZVAL_MAKE_REF(other);
         zend_reference *ref = Z_REF_P(other);
         ++GC_REFCOUNT(ref);
         ZVAL_REF(self, ref);
      } else {
         ZVAL_DUP(self, other);
         convert_to_double(self);
      }
   } else {
      ZVAL_DOUBLE(self, 0);
   }
}

DoubleVariant::DoubleVariant(const DoubleVariant &other)
   : Variant(other)
{}

DoubleVariant::DoubleVariant(DoubleVariant &&other) ZAPI_DECL_NOEXCEPT
   : Variant(std::move(other))
{}

DoubleVariant::DoubleVariant(const Variant &other)
{
   zval *self = getZvalPtr();
   zval *from = const_cast<zval *>(other.getZvalPtr());
   if (other.getType() == Type::Double) {
      ZVAL_DOUBLE(self, zval_get_double(from));
   } else {
      zval temp;
      ZVAL_DUP(&temp, from);
      convert_to_double(&temp);
      ZVAL_COPY_VALUE(self, &temp);
   }
}

DoubleVariant::DoubleVariant(Variant &&other)
   : Variant(std::move(other))
{
   if (getType() != Type::Double) {
      convert_to_double(getZvalPtr());
   }
}

bool DoubleVariant::toBool() const ZAPI_DECL_NOEXCEPT
{
   return toDouble();
}

DoubleVariant::operator double() const
{
   return toDouble();
}

double DoubleVariant::toDouble() const ZAPI_DECL_NOEXCEPT
{
   return zval_get_double(const_cast<zval *>(getZvalPtr()));
}

DoubleVariant &DoubleVariant::operator =(std::int8_t other)
{
   ZVAL_DOUBLE(getZvalPtr(), static_cast<double>(other));
   return *this;
}

DoubleVariant &DoubleVariant::operator =(std::int16_t other)
{
   ZVAL_DOUBLE(getZvalPtr(), static_cast<double>(other));
   return *this;
}

DoubleVariant &DoubleVariant::operator =(std::int32_t other)
{
   ZVAL_DOUBLE(getZvalPtr(), static_cast<double>(other));
   return *this;
}

DoubleVariant &DoubleVariant::operator =(std::int64_t other)
{
   ZVAL_DOUBLE(getZvalPtr(), static_cast<double>(other));
   return *this;
}

DoubleVariant &DoubleVariant::operator =(double other)
{
   ZVAL_DOUBLE(getZvalPtr(), other);
   return *this;
}

DoubleVariant &DoubleVariant::operator =(const DoubleVariant &other)
{
   assert(this != &other);
   ZVAL_DOUBLE(getZvalPtr(), other.toDouble());
   return *this;
}

DoubleVariant::DoubleVariant(DoubleVariant &other, bool isRef)
{
   zval *self = getZvalPtr();
   if (!isRef) {
      ZVAL_DOUBLE(self, other.toDouble());
   } else {
      zval *source = other.getUnDerefZvalPtr();
      ZVAL_MAKE_REF(source);
      ZVAL_COPY(self, source);
   }
}

DoubleVariant &DoubleVariant::operator =(const Variant &other)
{
   zval *self = getZvalPtr();
   zval *from = const_cast<zval *>(other.getZvalPtr());
   if (other.getType() == Type::Double) {
      ZVAL_DOUBLE(self, zval_get_double(from));
   } else {
      zval temp;
      ZVAL_DUP(&temp, from);
      convert_to_double(&temp);
      ZVAL_COPY_VALUE(self, &temp);
   }
   return *this;
}

DoubleVariant &DoubleVariant::operator =(const NumericVariant &other)
{
   ZVAL_DOUBLE(getZvalPtr(), static_cast<double>(other.toLong()));
   return *this;
}

DoubleVariant &DoubleVariant::operator =(ArrayItemProxy &&other)
{
   return operator =(other.toDoubleVariant());
}

DoubleVariant::~DoubleVariant() ZAPI_DECL_NOEXCEPT
{}

DoubleVariant &DoubleVariant::operator +=(const DoubleVariant &value) ZAPI_DECL_NOEXCEPT
{
   ZVAL_DOUBLE(getZvalPtr(), toDouble() + value.toDouble());
   return *this;
}

DoubleVariant &DoubleVariant::operator -=(const DoubleVariant &value) ZAPI_DECL_NOEXCEPT
{
   ZVAL_DOUBLE(getZvalPtr(), toDouble() + value.toDouble());
   return *this;
}

DoubleVariant &DoubleVariant::operator *=(const DoubleVariant &value) ZAPI_DECL_NOEXCEPT
{
   ZVAL_DOUBLE(getZvalPtr(), toDouble() + value.toDouble());
   return *this;
}

DoubleVariant &DoubleVariant::operator /=(const DoubleVariant &value) ZAPI_DECL_NOEXCEPT
{
   ZVAL_DOUBLE(getZvalPtr(), toDouble() + value.toDouble());
   return *this;
}

DoubleVariant &DoubleVariant::operator %=(const DoubleVariant &value) ZAPI_DECL_NOEXCEPT
{
   ZVAL_DOUBLE(getZvalPtr(), std::fmod(toDouble(), value.toDouble()));
   return *this;
}

bool operator ==(const DoubleVariant &lhs, const DoubleVariant &rhs) ZAPI_DECL_NOEXCEPT
{
   return (lhs.toDouble() - rhs.toDouble()) == 0;
}

bool operator !=(const DoubleVariant &lhs, const DoubleVariant &rhs) ZAPI_DECL_NOEXCEPT
{
   return (lhs.toDouble() - rhs.toDouble()) != 0;
}

bool operator <(const DoubleVariant &lhs, const DoubleVariant &rhs) ZAPI_DECL_NOEXCEPT
{
   return (lhs.toDouble() - rhs.toDouble()) < 0;
}

bool operator <=(const DoubleVariant &lhs, const DoubleVariant &rhs) ZAPI_DECL_NOEXCEPT
{
   return (lhs.toDouble() - rhs.toDouble()) <= 0;
}

bool operator >(const DoubleVariant &lhs, const DoubleVariant &rhs) ZAPI_DECL_NOEXCEPT
{
   return (lhs.toDouble() - rhs.toDouble()) > 0;
}

bool operator >=(const DoubleVariant &lhs, const DoubleVariant &rhs) ZAPI_DECL_NOEXCEPT
{
   return (lhs.toDouble() - rhs.toDouble()) >= 0;
}

double operator +(const DoubleVariant &lhs, const DoubleVariant &rhs) ZAPI_DECL_NOEXCEPT
{
   return lhs.toDouble() + rhs.toDouble();
}

double operator -(const DoubleVariant &lhs, const DoubleVariant &rhs) ZAPI_DECL_NOEXCEPT
{
   return lhs.toDouble() - rhs.toDouble();
}

double operator *(const DoubleVariant &lhs, const DoubleVariant &rhs) ZAPI_DECL_NOEXCEPT
{
   return lhs.toDouble() * rhs.toDouble();
}

double operator /(const DoubleVariant &lhs, const DoubleVariant &rhs) ZAPI_DECL_NOEXCEPT
{
   return lhs.toDouble() / rhs.toDouble();
}

double operator %(const DoubleVariant &lhs, const DoubleVariant &rhs) ZAPI_DECL_NOEXCEPT
{
   return std::fmod(lhs.toDouble(), rhs.toDouble());
}

double operator +(const DoubleVariant &lhs, const NumericVariant &rhs) ZAPI_DECL_NOEXCEPT
{
   return lhs.toDouble() + rhs.toLong();
}

double operator -(const DoubleVariant &lhs, const NumericVariant &rhs) ZAPI_DECL_NOEXCEPT
{
   return lhs.toDouble() - rhs.toLong();
}

double operator *(const DoubleVariant &lhs, const NumericVariant &rhs) ZAPI_DECL_NOEXCEPT
{
   return lhs.toDouble() * rhs.toLong();
}

double operator /(const DoubleVariant &lhs, const NumericVariant &rhs) ZAPI_DECL_NOEXCEPT
{
   return lhs.toDouble() / rhs.toLong();
}

double operator %(const DoubleVariant &lhs, const NumericVariant &rhs) ZAPI_DECL_NOEXCEPT
{
   return std::fmod(lhs.toDouble(), static_cast<double>(rhs.toLong()));
}

double operator +(const NumericVariant &lhs, const DoubleVariant &rhs) ZAPI_DECL_NOEXCEPT
{
   return lhs.toLong() + rhs.toDouble();
}

double operator -(const NumericVariant &lhs, const DoubleVariant &rhs) ZAPI_DECL_NOEXCEPT
{
   return lhs.toLong() - rhs.toDouble();
}

double operator *(const NumericVariant &lhs, const DoubleVariant &rhs) ZAPI_DECL_NOEXCEPT
{
   return lhs.toLong() * rhs.toDouble();
}

double operator /(const NumericVariant &lhs, const DoubleVariant &rhs) ZAPI_DECL_NOEXCEPT
{
   return lhs.toLong() / rhs.toDouble();
}

double operator %(const NumericVariant &lhs, const DoubleVariant &rhs) ZAPI_DECL_NOEXCEPT
{
   return std::fmod(static_cast<double>(lhs.toLong()), rhs.toDouble());
}

} // ds
} // zapi

