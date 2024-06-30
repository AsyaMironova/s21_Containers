#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include "../list/s21_list.h"

namespace s21 {
template <class T, class list_container = s21::list<T>>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 private:
  list_container list_ref;

 public:
  queue() : list_ref() {}
  queue(std::initializer_list<value_type> const &items) : list_ref(items) {}
  queue(const queue &q) : list_ref(q.list_ref) {}
  queue(queue &&q) : list_ref(q.list_ref) {}
  ~queue() {}
  queue &operator=(queue &&q) {
    while (!this->empty()) {
      this->pop();
    }
    this->list_ref = move(q.list_ref);
    return *this;
  }

  const_reference front() { return this->list_ref.front(); }
  const_reference back() { return this->list_ref.back(); }

  bool empty() { return this->list_ref.empty(); }
  size_type size() { return this->list_ref.size(); }

  void push(const_reference value) { return this->list_ref.push_back(value); }
  void pop() { return this->list_ref.pop_front(); }
  void swap(queue &other) { return this->list_ref.swap(other.list_ref); }

  template <typename... Args>
  void insert_many_back(Args&&... args) { return this->list_ref.insert_many_back(args...); }
};
}  // namespace s21

#endif  // S21_QUEUE_H