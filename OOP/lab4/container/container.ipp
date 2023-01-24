#pragma once
#include "container.h"
#include <deque>
#include <iostream>
#include <memory>
#include <tuple>

namespace my_vector {
using std::allocator;
using std::construct_at;
using std::destroy_n;
using std::move;
using std::swap;

template <class T, class Allocator>
void vector<T, Allocator>::destroy_and_alloc(size_t new_size,
                                             size_t prev_size) {
  if (prev_size != 0) {
    destroy_n(ptr, prev_size);
    alloc.deallocate(ptr, prev_size);
  }

  v_size = new_size;
  ptr = (v_size == 0) ? nullptr : alloc.allocate(v_size);
}

template <class T, class Allocator>
void vector<T, Allocator>::realloc(size_t new_size, size_t prev_size) {
  T *ptr1 = alloc.allocate(new_size);
  for (size_t i = 0; i < (new_size < prev_size ? new_size : prev_size); ++i) {
    construct_at(ptr1 + i, T(move(ptr[i])));
  }
  if (prev_size != 0) {
    alloc.deallocate(ptr, prev_size);
  }
  v_size = new_size;
  ptr = ptr1;
}

template <class T, class Allocator>
constexpr vector<T, Allocator>::vector(size_t size, const T &value,
                                       Allocator alloc)
    : v_size(size), alloc(alloc) {

  ptr = (size == 0) ? nullptr : alloc.allocate(size);

  for (size_t i = 0; i < size; ++i) {
    construct_at(ptr + i, value);
  }
}

template <class T, class Allocator>
constexpr vector<T, Allocator>::vector(const vector &other) {
  destroy_and_alloc(other.v_size, v_size);

  for (size_t i = 0; i < v_size; ++i) {
    construct_at(ptr + i, T(other.ptr[i]));
  }
}

template <class T, class Allocator>
constexpr vector<T, Allocator>::vector(vector &&other) {
  swap(v_size, other.v_size);
  swap(ptr, other.ptr);
}

template <class T, class Allocator>
constexpr vector<T, Allocator> &
vector<T, Allocator>::operator=(const vector &other) {
  destroy_and_alloc(other.v_size, v_size);

  for (size_t i = 0; i < v_size; ++i) {
    construct_at(ptr + i, T(other.ptr[i]));
  }
  return *this;
}

template <class T, class Allocator>
constexpr vector<T, Allocator> &
vector<T, Allocator>::operator=(vector &&other) {
  swap(ptr, other.ptr);
  swap(v_size, other.v_size);
  return *this;
}

template <class T, class Allocator>
constexpr T &vector<T, Allocator>::at(size_t pos) {
 
  if (pos >= v_size) {
    throw std::out_of_range("my_vector: at");
  }
  return ptr[pos];
}

template <class T, class Allocator>
constexpr T &vector<T, Allocator>::operator[](size_t pos) {
  return at(pos);
}

template <class T, class Allocator>
constexpr void vector<T, Allocator>::push_back(const T &value) {
  realloc(v_size + 1, v_size);
  construct_at(ptr + v_size - 1, T(value));
}
template <class T, class Allocator>
constexpr void vector<T, Allocator>::push_back(T &&value) {
  realloc(v_size + 1, v_size);
  construct_at(ptr + v_size - 1, T(move(value)));
}

template <class T, class Allocator>
constexpr void vector<T, Allocator>::pop_back() {
  if (v_size > 0) {
    realloc(v_size - 1, v_size);
  } else {
    throw std::out_of_range("my_vector: pop_back");
  }
}

template <class T, class Allocator> constexpr T &vector<T, Allocator>::front() {
  if (v_size < 1) {
    throw std::out_of_range("my_vector: front");
  }
  return ptr[0];
}

template <class T, class Allocator> constexpr T &vector<T, Allocator>::back() {
  if (v_size < 1) {
    throw std::out_of_range("my_vector: back");
  }
  return ptr[v_size - 1];
}

template <class T, class Allocator>
constexpr size_t vector<T, Allocator>::size() const {
  return v_size;
}

template <class T, class Allocator> vector<T, Allocator>::~vector() {
  if (v_size != 0) {
    destroy_n(ptr, v_size);
    alloc.deallocate(ptr, v_size);
  }
}

template <class T, class Allocator>
vector<T, Allocator>::iterator::iterator(pointer ptr) : m_ptr(ptr) {}

template <class T, class Allocator>
typename vector<T, Allocator>::iterator::reference
vector<T, Allocator>::iterator::operator*() {
  return *m_ptr;
}
template <class T, class Allocator>
typename vector<T, Allocator>::iterator::pointer
vector<T, Allocator>::iterator::operator->() {
  return m_ptr;
}
template <class T, class Allocator>
typename vector<T, Allocator>::iterator &
vector<T, Allocator>::iterator::operator++() {
  m_ptr++;
  return *this;
}
template <class T, class Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::iterator::operator++(int) {
  iterator tmp = *this;
  ++(*this);
  return tmp;
}

template <class T, class Allocator>
bool vector<T, Allocator>::iterator::operator==(const typename vector<T, Allocator>::iterator &a) {
  return a.m_ptr == m_ptr;
};
template <class T, class Allocator>
bool vector<T, Allocator>::iterator::operator!=(const typename vector<T, Allocator>::iterator &a) {
  return a.m_ptr != m_ptr;
};

template <class T, class Allocator>
constexpr typename vector<T, Allocator>::iterator
vector<T, Allocator>::begin() {
  return iterator(ptr);
}

template <class T, class Allocator>
constexpr typename vector<T, Allocator>::iterator vector<T, Allocator>::end() {
  return iterator(ptr + v_size);
}

} 

/*
  1)+  auto vec = vector<string>(10, "HI"); 
      vector<string>(vec);
  2)+  auto vec = vector<string>(10, "HI");
      vector<string>(move(vec));
  3)+  auto vec = vector<string>(10, "HI");
      vector<string> vec1;
      vec1 = vec;
  4)+  auto vec = vector<string>(10, "HI");
      vector<string> vec1;
      vec1 = move(vec);
  5)+  auto vec = vector<string>(4, "hihi");
      EXPECT_EQ(vec.at(0) == "hihi");
  6)+  