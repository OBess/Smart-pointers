#pragma once

// Custom
#include "cobject.hpp"

struct controlBlock
{
   size_t counter = 1;
};

class MyShared_ptr
{
public:
   // Constructors
   MyShared_ptr() noexcept : m_ptr(nullptr), m_controlBlock(new controlBlock) {}
   MyShared_ptr(std::nullptr_t) noexcept : m_ptr(nullptr), m_controlBlock(new controlBlock) {}
   explicit MyShared_ptr(CObject *ptr) noexcept : m_ptr(ptr), m_controlBlock(new controlBlock) {}

   explicit MyShared_ptr(MyShared_ptr &&other) : m_ptr(other.m_ptr), m_controlBlock(other.m_controlBlock)
   {
      m_ptr = other.m_ptr;
      m_controlBlock = other.m_controlBlock;
      other.m_ptr = nullptr;
      other.m_controlBlock = nullptr;
   };
   explicit MyShared_ptr(MyShared_ptr &other) noexcept : m_ptr(other.m_ptr), m_controlBlock(other.m_controlBlock)
   {
      ++m_controlBlock->counter;
   }

   // Destructor
   ~MyShared_ptr() noexcept
   {
      --m_controlBlock->counter;
      if (m_controlBlock->counter == 0)
      {
         delete m_ptr;
         delete m_controlBlock;
      }
   }

   // Operators
   MyShared_ptr &operator=(std::nullptr_t) noexcept
   {
      delete m_ptr;
      m_ptr = nullptr;
      return *this;
   }

   MyShared_ptr &operator=(MyShared_ptr &&other)
   {

      return *this;
   }

   MyShared_ptr &operator=(const MyShared_ptr &other) noexcept
   {
      
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
      
   }

   size_t counter() const noexcept
   {
      return m_controlBlock->counter;
   }

private:
   CObject *m_ptr;

   controlBlock *m_controlBlock;
};