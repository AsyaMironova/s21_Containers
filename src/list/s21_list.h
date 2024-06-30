#ifndef S21_LIST_H
#define S21_LIST_H

#include <initializer_list>
#include <iostream>

using namespace std;

namespace s21 {
template <class T>
class list {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

 private:
  struct node {
    value_type value_;
    node* next_;
    node* prev_;
    node(const value_type& value)
        : value_(value), next_(nullptr), prev_(nullptr) {}
  };
  size_type size_ = 0;
  node* head_ = nullptr;
  node* tail_ = nullptr;
  node* size_node_ = nullptr;

 public:
  class listIterator {
   private:
    node* ptr_ = nullptr;
    friend class list<value_type>;

   public:
    listIterator();
    listIterator(node* ptr);
    listIterator& operator++();    // prefix
    listIterator operator++(int);  // postfix
    listIterator& operator--();
    listIterator operator--(int);
    listIterator operator-(size_type value);
    value_type operator*() const;
    value_type operator->() const;
    bool operator==(listIterator other);
    bool operator!=(listIterator other);
  };

  class listConstIterator : public listIterator {
   public:
    listConstIterator(listIterator other);
    const_reference operator*();
  };

  using iterator = listIterator;
  using const_iterator = listConstIterator;

 public:
  void set_size_node();
  list();
  list(size_type n);
  list(std::initializer_list<value_type> const& items);
  list(const list& l);
  list(list&& l);
  ~list();
  list& operator=(list&& l);
  const_reference front();
  const_reference back();
  iterator begin();
  iterator end();
  bool empty();
  size_type size();
  size_type max_size();
  void clear();
  node* get_at(value_type index);
  node* operator[](value_type index);
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list& other);
  void merge(list& other);
  void splice(const_iterator pos, list& other);
  void reverse();
  void unique();
  void sort();
  void quick_sort(iterator first, iterator last);
  iterator partition(iterator first, iterator last);
  node* merge_nodes(node* left_part, node* right_part);
  void delete_size_node();

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);
  template <typename... Args>
  void insert_many_front(Args&&... args);
};
}  // namespace s21

#include "s21_list.tpp"

#endif  // S21_LIST_H
