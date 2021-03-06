// C++
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

// Custom
#include "include/cobject.hpp"
#include "include/my_unique_ptr.hpp"
#include "include/my_shared_ptr.hpp"

// CObject testing
class Integer : public CObject
{
public:
   Integer(int value = 0) : m_value(value)
   {
   }

   std::string toString() const noexcept override
   {
      return std::to_string(m_value);
   }

   int value() const noexcept
   {
      return m_value;
   }

   bool operator==(const Integer &other) const noexcept
   {
      return m_value == other.m_value;
   }

private:
   void input(std::basic_istream<char> &in) override
   {
      in >> m_value;
   }

   int m_value;
};

int main()
{
   // CObject testing
   {
      Integer i(10), i2;
      std::ifstream in("Test/integer.txt");
      std::ofstream out("Test/test.txt");

      std::cout << "Integer = " << i << std::endl;
      in >> i2;
      std::cout << "Integer = " << i2 << std::endl;
      out << int(i == i2);
      out.close();
   }

   // MyUnique_ptr testing
   {
      MyUnique_ptr ptr;
      assert(ptr == nullptr);
   }
   {
      MyUnique_ptr ptr(nullptr);
      assert(ptr == nullptr);
   }
   {
      MyUnique_ptr ptr(new Integer(12));
      assert(dynamic_cast<const Integer *>(ptr.get())->value() == 12);
      ptr.reset(new Integer(3));
      assert(dynamic_cast<const Integer *>(ptr.get())->value() == 3);
      assert(ptr->toString() == "3");
   }
   {
      Integer *i = new Integer(2);
      MyUnique_ptr ptr(i);
      assert(dynamic_cast<const Integer *>(ptr.get())->value() == 2);
      assert(*i == *dynamic_cast<const Integer *>(ptr.get()));
   }
   {
      Integer *i = new Integer(2);
      MyUnique_ptr ptr(i);
      MyUnique_ptr ptr1(std::move(ptr));
      assert(ptr == nullptr);
      assert(dynamic_cast<const Integer *>(ptr1.get())->value() == 2);
   }

   // MyShared_ptr testing
   {
      MyShared_ptr ptr;
      assert(ptr == nullptr);
   }
   {
      MyShared_ptr ptr(nullptr);
      assert(ptr == nullptr);
   }
   {
      MyShared_ptr ptr(new Integer(12));
      ptr = nullptr;
      assert(ptr == nullptr);
   }
   {
      MyShared_ptr ptr(new Integer(12));
      MyShared_ptr ptr1(ptr);
      assert(dynamic_cast<const Integer *>(ptr.get())->value() == 12);
      ptr.reset(new Integer(3));
      assert(dynamic_cast<const Integer *>(ptr1.get())->value() == 12);
      assert(dynamic_cast<const Integer *>(ptr.get())->value() == 3);
      assert(ptr->toString() == "3");
   }
   {
      Integer *i = new Integer(2);
      MyShared_ptr ptr(i);
      assert(dynamic_cast<const Integer *>(ptr.get())->value() == 2);
      assert(*i == *dynamic_cast<const Integer *>(ptr.get()));
   }
   {
      Integer *i = new Integer(2);
      MyShared_ptr ptr(i);
      MyShared_ptr ptr1(ptr);
      MyShared_ptr ptr2(ptr1);
      assert(!(ptr == nullptr));
      assert(dynamic_cast<const Integer *>(ptr.get())->value() == 2);
      assert(dynamic_cast<const Integer *>(ptr1.get())->value() == 2);
      assert(ptr.counter() == 3);

      ptr.~MyShared_ptr();
      assert(dynamic_cast<const Integer *>(ptr1.get())->value() == 2);
      assert(ptr1.counter() == 2);
   }

   return EXIT_SUCCESS;
}