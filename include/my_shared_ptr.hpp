#pragma once

// Custom
#include "cobject.hpp"

class MyShared_ptr
{
public:
   // Constructors
   MyShared_ptr() noexcept : m_ptr(nullptr), m_counter(new size_t(0)) {}
   MyShared_ptr(std::nullptr_t) noexcept : m_ptr(nullptr), m_counter(new size_t(0)) {}
   explicit MyShared_ptr(CObject *ptr) noexcept : m_ptr(ptr), m_counter(new size_t(1)) {}

   explicit MyShared_ptr(MyShared_ptr &&) = delete;
   explicit MyShared_ptr(MyShared_ptr &other) noexcept : m_ptr(other.m_ptr), m_counter(other.m_counter)
   {
      ++(*m_counter);
   }

   // Destructor
   ~MyShared_ptr() noexcept
   {
      --(*m_counter);
      if (*m_counter == 0)
      {
         delete m_ptr;
         delete m_counter;
      }
   }

   // Operators
   MyShared_ptr &operator=(std::nullptr_t) noexcept
   {
      delete m_ptr;
      m_ptr = nullptr;
      return *this;
   }

   MyShared_ptr &operator=(MyShared_ptr &&) = delete;
   MyShared_ptr &operator=(MyShared_ptr &other) noexcept
   {
      m_ptr = other.m_ptr;
      m_counter = other.m_counter;
      ++(*m_counter);

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
   bool operator==(const MyShared_ptr &other) const noexcept
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

   size_t counter() const noexcept
   {
      return *m_counter;
   }

private:
   CObject *m_ptr;

   size_t *m_counter;
};