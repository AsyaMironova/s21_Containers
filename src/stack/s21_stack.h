#ifndef S21_STACK_H
#define S21_STACK_H

#include "../list/s21_list.h"

namespace s21 {
template <class T, class list_container = s21::list<T>>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 private:
  list_container list_ref;

 public:
  stack() : list_ref() {}
  stack(std::initializer_list<value_type> const &items) : list_ref(items) {}
  stack(const stack &s) : list_ref(s.list_ref) {}
  stack(stack &&s) : list_ref(s.list_ref) {}
  ~stack() {}
  stack &operator=(stack &&q) {
    while (!this->empty()) {
      this->pop();
    }
    this->list_ref = std::move(q.list_ref);
    return *this;
  }

  const_reference top() {
    if (this->list_ref.empty()) {
      throw std::out_of_range("stack is out of range");
    }
    return this->list_ref.back();
  }

  bool empty() { return this->list_ref.empty(); }
  size_type size() { return this->list_ref.size(); }

  void push(const_reference value) { this->list_ref.push_back(value); }
  void pop() {
    if (list_ref.empty()) {
      throw length_error("stack is empty");
    }
    this->list_ref.pop_back();
  }
  void swap(stack &other) { this->list_ref.swap(other.list_ref); }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    return this->list_ref.insert_many_front(args...);
  }
};
}  // namespace s21

#endif  // S21_STACK_H