#ifndef S21_ARRAY_H
#define S21_ARRAY_H

#include <math.h>

#include <initializer_list>
#include <iostream>
#include <utility>

namespace s21 {

template <class T, std::size_t Size>
class ArrayIterator;

template <class T, std::size_t Size>
class ArrayConstIterator;

template <class T, std::size_t Size>
class array {
 private:
  size_t m_size = Size;
  T *arr;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ArrayIterator<T, Size>;
  using const_iterator = ArrayConstIterator<T, Size>;
  using size_type = size_t;

 private:
  void free_array();

 public:
  array() : m_size(Size), arr(nullptr) {}

  explicit array(size_type n) : array() {
    m_size = n;
    arr = n ? new T[n] : nullptr;
  }
  array(std::initializer_list<value_type> const &items);
  array(const array &a) : m_size(a.m_size), arr(a.arr){};
  array(array &&a) : m_size(a.m_size), arr(a.arr) {
    a.arr = nullptr;
    a.m_size = 0;
  }
  ~array() { free_array(); }
  array &operator=(array &&a) {
    if (this != &a) {
      free_array();
      m_size = a.m_size;
      arr = a.arr;
      a.arr = nullptr;
      a.m_size = 0;
    }
    return *this;
  };

  // методы для доступа к элементам класса
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();

  //  методы для итерирования по элементам класса
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  // методы для доступа к информации о наполнении контейнера
  bool empty();
  size_type size();
  size_type max_size();

  // методы для изменения контейнера
  void swap(array &other);
  void fill(const_reference value);
};

template <class T, std::size_t Size>
class ArrayIterator {
  friend class array<T, Size>;
  friend class ArrayConstIterator<T, Size>;

  using value_type = T;
  using pointer = T *;
  using reference = T &;

 public:
  ArrayIterator() { ptr_ = nullptr; }
  ArrayIterator(pointer ptr) { ptr_ = ptr; }

  value_type &operator*() const { return (*ptr_); }
  pointer operator->() { return ptr_; }

  ArrayIterator &operator++() {
    ptr_++;
    return *this;
  }

  ArrayIterator &operator--() {
    ptr_--;
    return *this;
  }

  ArrayIterator operator++(int) {
    ArrayIterator tmp = *this;
    ++(*this);
    return tmp;
  }

  ArrayIterator operator--(int) {
    ArrayIterator tmp = *this;
    --(*this);
    return tmp;
  }

  ArrayIterator operator+(const size_t value) {
    ArrayIterator tmp(this->ptr_ + value);
    return tmp;
  }

  ArrayIterator operator-(const size_t value) {
    ArrayIterator tmp(this->ptr_ - value);
    return tmp;
  }

  bool operator==(const ArrayIterator &other) { return ptr_ == other.ptr_; }

  bool operator!=(const ArrayIterator &other) { return ptr_ != other.ptr_; }

  operator ArrayConstIterator<T, Size>() const {
    return ArrayConstIterator<T, Size>(ptr_);
  }

 private:
  pointer ptr_;
};

template <class T, std::size_t Size>
class ArrayConstIterator {
  friend class array<T, Size>;
  friend class ArrayIterator<T, Size>;

  using value_type = T;
  using pointer = T *;
  using reference = T &;

 public:
  ArrayConstIterator() { ptr_ = nullptr; };
  ArrayConstIterator(pointer ptr) { ptr_ = ptr; };
  value_type operator*() const { return (*ptr_); }
  pointer operator->() { return ptr_; }

  ArrayConstIterator &operator++() {
    ptr_++;
    return *this;
  }

  ArrayConstIterator &operator--() {
    ptr_--;
    return *this;
  }

  ArrayConstIterator operator++(int) {
    ArrayConstIterator tmp = *this;
    ++(*this);
    return tmp;
  }

  ArrayConstIterator operator--(int) {
    ArrayConstIterator tmp = *this;
    --(*this);
    return tmp;
  }

  bool operator==(const ArrayConstIterator &other) {
    return ptr_ == other.ptr_;
  }

  bool operator!=(const ArrayConstIterator &other) {
    return ptr_ != other.ptr_;
  }

  operator ArrayIterator<T, Size>() const {
    return ArrayIterator<T, Size>(ptr_);
  }

 private:
  pointer ptr_;
};

}  // namespace s21

#include "s21_array.tpp"

#endif  // S21_Array_H