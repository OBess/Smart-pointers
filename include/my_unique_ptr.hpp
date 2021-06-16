#pragma once
#ifndef MY_UNIQUE_PTR_HPP
#define MY_UNIQUE_PTR_HPP

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

   CObject& operator*() noexcept
   {
      return *m_ptr;
   }

   CObject* operator->() noexcept
   {
      return m_ptr;
   }

   // Auxiliary methods
   const CObject const* get() const noexcept
   {
      return m_ptr;
   }

   void reset(CObject* tmp) noexcept
   {
      delete m_ptr;
      tmp = m_ptr;
   }

private:
   CObject *m_ptr;
};

#endif //MY_UNIQUE_PTR_HPP