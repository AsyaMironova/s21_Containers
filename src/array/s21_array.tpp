#include "s21_array.h"

namespace s21 {

template <class value_type, std::size_t Size>
array<value_type, Size>::array(std::initializer_list<value_type> const& items) {
  arr = new value_type[items.size()];
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    arr[i] = *it;
    i++;
  }
  m_size = items.size();
};

template <class value_type, std::size_t Size>
void array<value_type, Size>::free_array() {
  if (arr != nullptr) {
    delete[] arr;
    arr = nullptr;
    m_size = 0;
  }
}

template <class value_type, std::size_t Size>
typename array<value_type, Size>::reference array<value_type, Size>::at(
    size_type pos) {
  if (m_size <= pos) {
    throw std::out_of_range("InvalidIndexError: Index is out of range");
  }
  return arr[pos];
}

template <class value_type, std::size_t Size>
typename array<value_type, Size>::reference array<value_type, Size>::operator[](
    size_type pos) {
  if (m_size <= pos) {
    throw std::out_of_range("InvalidIndexError: Index is out of range");
  }
  return arr[pos];
}

template <class value_type, std::size_t Size>
typename array<value_type, Size>::const_reference
array<value_type, Size>::front() {
  if (m_size <= 0) {
    throw std::out_of_range("InvalidIndexError: Index is out of range");
  }
  return arr[0];
}

template <class value_type, std::size_t Size>
typename array<value_type, Size>::const_reference
array<value_type, Size>::back() {
  if (m_size <= 0) {
    throw std::out_of_range("InvalidIndexError: Index is out of range");
  }
  return arr[m_size - 1];
}

template <class value_type, std::size_t Size>
typename array<value_type, Size>::iterator array<value_type, Size>::data() {
  return arr;
}

template <class value_type, std::size_t Size>
typename array<value_type, Size>::iterator array<value_type, Size>::begin() {
  return iterator(arr);
}

template <class value_type, std::size_t Size>
typename array<value_type, Size>::iterator array<value_type, Size>::end() {
  return iterator(arr + m_size);
}

template <class value_type, std::size_t Size>
typename array<value_type, Size>::const_iterator
array<value_type, Size>::begin() const {
  return const_iterator(arr);
}

template <class value_type, std::size_t Size>
typename array<value_type, Size>::const_iterator array<value_type, Size>::end()
    const {
  return const_iterator(arr + m_size);
}

template <typename T, std::size_t Size>
bool array<T, Size>::empty() {
  return (m_size == 0) ? true : false;
}

template <class value_type, std::size_t Size>
typename array<value_type, Size>::size_type array<value_type, Size>::size() {
  return m_size;
}

template <class value_type, std::size_t Size>
typename array<value_type, Size>::size_type
array<value_type, Size>::max_size() {
  size_t result = pow(2, (64 - log(sizeof(value_type)) / log(2))) - 1;
  return result;
}

template <class value_type, std::size_t Size>
void array<value_type, Size>::swap(array& other) {
  std::swap(other.m_size, m_size);
  std::swap(other.arr, arr);
}

template <class value_type, std::size_t Size>
void array<value_type, Size>::fill(const_reference value) {
  for (size_type i = 0; i < m_size; i++) {
    arr[i] = value;
  }
}

// template class array<int>;
}  // namespace s21
