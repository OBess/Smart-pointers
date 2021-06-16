#pragma once

// Custom
#include "cobject.hpp"

class MyUnique_ptr
{
public:
   // Constructors
   MyUnique_ptr() noexcept : m_ptr(nullptr) {}
   MyUnique_ptr(std::nullptr_t) noexcept : m_ptr(nullptr) {}
   explicit MyUnique_ptr(CObject *ptr) noexcept : m_ptr(std::move(ptr)) {}

   explicit MyUnique_ptr(const MyUnique_ptr &) = delete;
   explicit MyUnique_ptr(MyUnique_ptr &&other) noexcept : m_ptr(other.m_ptr)
   {
      other.m_ptr = nullptr;
   }

   // Destructor
   ~MyUnique_ptr() noexcept
   {
      delete this->m_ptr;
   }

   // Operators
   MyUnique_ptr &operator=(std::nullptr_t) noexcept
   {
      delete m_ptr;
      m_ptr = nullptr;
      return *this;
   }

   MyUnique_ptr &operator=(const MyUnique_ptr &) = delete;
   MyUnique_ptr &operator=(MyUnique_ptr &&other) noexcept
   {
      delete m_ptr;

      m_ptr = other.m_ptr;
      other.m_ptr = nullptr;

      return *this;
   }

   CObject &operator*() noexcept
   {
      return *m_ptr;
   }

   CObject *operator->() noexcept
   {
      return m_ptr;
   }

   // Auxiliary opeartors
   bool operator==(const MyUnique_ptr &other) const noexcept
   {
      return other.m_ptr == m_ptr;
   }

   bool operator==(std::nullptr_t) const noexcept
   {
      return m_ptr == nullptr;
   }

   // Auxiliary methods
   const CObject *get() const noexcept
   {
      return m_ptr;
   }

   void reset(CObject *tmp) noexcept
   {
      delete m_ptr;
      m_ptr = tmp;
   }

private:
   CObject *m_ptr;
};