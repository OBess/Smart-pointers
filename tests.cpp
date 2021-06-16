// C++
#include <iostream>
#include <fstream>
#include <string>

// Custom
#include "include/cobject.hpp"

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
   Integer i(10);
   std::ofstream out("test.txt");

   std::cout << "Integer = " << i << std::endl;
   std::cout << "Enter new integer: ";
   std::cin >> i;
   std::cout << "Integer = " << i << std::endl;

   out << i;
   out.close();

   // 

   return EXIT_SUCCESS;
}