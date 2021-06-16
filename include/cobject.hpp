#pragma once

// C++
#include <iostream>

class CObject
{
public:
   CObject() noexcept = default;
   virtual ~CObject() noexcept = default;

   friend std::basic_ostream<char> &operator<<(std::basic_ostream<char> &os, const CObject &object)
   {
      os << object.output();
      return os;
   }

   friend std::basic_istream<char> &operator>>(std::basic_istream<char> &in, CObject &object)
   {
      object.input(in);
      return in;
   }

   virtual std::string toString() const noexcept = 0;

protected:
   virtual void input(std::basic_istream<char> &in) = 0;

private:
   std::string output() const noexcept
   {
      return this->toString();
   }
};