#include "s21_list.h"

namespace s21 {

template <typename T>
void list<T>::set_size_node() {
  size_node_->value_ = size();
  size_node_->next_ = head_;
  size_node_->prev_ = tail_;
  if (head_) {
    head_->prev_ = size_node_;
  }
  if (tail_) {
    tail_->next_ = size_node_;
  }
}

template <typename T>
void list<T>::delete_size_node() {
  // delete size_node_;
}

template <typename T>
list<T>::list()
    : size_(0), head_(nullptr), tail_(nullptr), size_node_(nullptr) {
  size_node_ = new node(size_);
  set_size_node();
}

template <typename T>
list<T>::list(size_type n)
    : size_(0), head_(nullptr), tail_(nullptr), size_node_(nullptr) {
  if (n <= 0) {
    throw length_error("size of list should be more then 0");
  }
  size_node_ = new node(size_);
  for (size_type i = 0; i < n; i++) {
    push_back(0);
  }
  set_size_node();
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const& items)
    : size_(0), head_(nullptr), tail_(nullptr), size_node_(nullptr) {
  if (items.size() < 0) {
    throw length_error("size of list should be more then 0");
  }
  size_node_ = new node(size_);
  for (const_reference i : items) {
    push_back(i);
  }
  set_size_node();
}

template <typename T>
list<T>::list(const list& l)
    : size_(0), head_(nullptr), tail_(nullptr), size_node_(nullptr) {
  node* l_curr_node = l.head_;

  for (size_type i = 0; i < l.size_; i++) {
    push_back(l_curr_node->value_);
    l_curr_node = l_curr_node->next_;
  }
}

template <typename T>
list<T>::list(list&& l)
    : size_(0), head_(nullptr), tail_(nullptr), size_node_(nullptr) {
  node* l_curr_node = l.head_;
  clear();
  for (size_type i = 0; i < l.size_; i++) {
    push_back(l_curr_node->value_);
    l_curr_node = l_curr_node->next_;
  }
  l.size_ = 0;
  l.head_ = l.tail_ = nullptr;
}

template <typename T>
list<T>::~list() {
  clear();
  delete size_node_;
}

template <typename T>
list<T>& list<T>::operator=(list&& l) {
  while (!empty()) {
    pop_back();
  }
  node* l_curr_node = l.head_;
  for (size_type i = 0; i < l.size_; i++) {
    push_back(l_curr_node->value_);
    l_curr_node = l_curr_node->next_;
  }
  return *this;
}

template <typename T>
typename list<T>::const_reference list<T>::front() {
  return head_->value_;
}

template <typename T>
typename list<T>::const_reference list<T>::back() {
  return tail_->value_;
}

template <typename T>
typename list<T>::iterator list<T>::begin() {
  return head_ ? iterator(head_) : iterator(size_node_);
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  return iterator(size_node_);
}

template <typename T>
bool list<T>::empty() {
  return (this->head_ == nullptr);
}

template <typename T>
typename list<T>::size_type list<T>::size() {
  return size_;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() {
  return numeric_limits<size_type>::max() / sizeof(node);
}

template <typename T>
void list<T>::clear() {
  while (!empty()) {
    pop_back();
  }
}

template <typename T>
typename list<T>::node* list<T>::get_at(list<T>::value_type index) {
  node* temp = head_;
  value_type temp_node_index = 0;
  if (temp != nullptr) {
    while (temp_node_index != index) {
      temp = temp->next_;
      temp_node_index++;
    }
  }
  return temp;
}

template <typename T>
typename list<T>::node* list<T>::operator[](list<T>::value_type index) {
  return get_at(index);
}

template <typename T>
typename list<T>::iterator list<T>::insert(list<T>::iterator pos,
                                           list<T>::const_reference value) {
  node* new_node = new node(value);
  node* current = pos.ptr_;
  node* prev = current->prev_;
  if (empty()) {
    new_node->next_ = size_node_;
    new_node->prev_ = size_node_;
    head_ = new_node;
    tail_ = new_node;
  } else {
    if (current == head_) {
      head_ = new_node;
    } else if (current == size_node_) {
      tail_ = new_node;
    }
    prev->next_ = new_node;
    new_node->prev_ = prev;
    new_node->next_ = current;
    current->prev_ = new_node;
  }
  size_++;
  set_size_node();
  return iterator(new_node);
}

template <typename T>
void list<T>::erase(list<T>::iterator pos) {
  node* current = pos.ptr_;
  if (empty() || current == size_node_) {
    throw invalid_argument("invalid argument");
  }
  if (current == head_) {
    if (current->next_ != size_node_ && current->next_) {
      head_ = current->next_;
    } else {
      head_ = size_node_;
    }
  } else if (current == tail_) {
    if (current->prev_ != size_node_ && current->prev_) {
      tail_ = current->prev_;
    } else {
      tail_ = size_node_;
    }
  }
  current->prev_->next_ = current->next_;
  current->next_->prev_ = current->prev_;
  delete current;
  size_--;
  set_size_node();
}

template <typename T>
void list<T>::push_back(list<T>::const_reference value) {
  node* new_tail = new node(value);
  if (empty()) {
    head_ = new_tail;
    tail_ = new_tail;
  } else {
    new_tail->prev_ = tail_;
    tail_->next_ = new_tail;
    tail_ = new_tail;
  }
  size_++;
};

template <typename T>
void list<T>::pop_back() {
  if (empty()) {
    throw length_error("list is empty");
  }
  node* last_node = tail_;
  if (size_ == 1) {
    head_ = nullptr;
    tail_ = nullptr;
  } else {
    tail_ = last_node->prev_;
    tail_->next_ = nullptr;
  }
  delete last_node;
  size_--;
}

template <typename T>
void list<T>::push_front(list<T>::const_reference value) {
  node* new_head = new node(value);
  if (empty()) {
    head_ = new_head;
    tail_ = new_head;
  }
  new_head->next_ = head_;
  head_->prev_ = new_head->prev_;
  head_ = new_head;
  size_++;
}

template <typename T>
void list<T>::pop_front() {
  if (empty()) {
    throw length_error("list is empty");
  }
  node* first_node = head_;
  if (size_ == 1) {
    head_ = nullptr;
    tail_ = nullptr;
  } else {
    head_ = first_node->next_;
    head_->prev_ = nullptr;
  }
  delete first_node;
  size_--;
}

template <typename T>
void list<T>::swap(list<T>& other) {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
  std::swap(size_node_, other.size_node_);
};

template <typename T>
void list<T>::merge(list<T>& other) {
  if (!other.empty()) {
    iterator this_iterator = this->begin();
    iterator other_iterator = other.begin();
    while (this_iterator != this->end()) {
      if (other_iterator != other.end()) {
        if (this_iterator.ptr_->value_ >= other_iterator.ptr_->value_) {
          this->insert(this_iterator, other_iterator.ptr_->value_);
          other_iterator++;
        } else {
          this_iterator++;
        }
      }
    }
    while (other_iterator != other.end()) {
      this->insert(this_iterator, other_iterator.ptr_->value_);
      other_iterator++;
    }
    other.clear();
  }
};

template <typename T>
void list<T>::splice(list<T>::const_iterator pos, list<T>& other) {
  if (!other.empty()) {
    for (iterator i = other.begin(); i != other.end(); i++) {
      this->insert(pos, *i);
    }
  }
  other.clear();
}

template <typename T>
void list<T>::reverse() {
  if (!this->empty()) {
    node* current = head_;
    node* prev = NULL;
    node* next = NULL;
    while (current != size_node_) {
      next = current->next_;
      current->next_ = prev;
      prev = current;
      current = next;
    }
    head_ = prev;
  }
}

template <typename T>
void list<T>::unique() {
  if (!this->empty()) {
    for (iterator iter = this->begin(); iter != this->end(); iter++) {
      if (iter.ptr_->value_ == iter.ptr_->prev_->value_) {
        this->erase(iter - 1);
      }
    }
  }
}

template <typename T>
typename list<T>::node* list<T>::merge_nodes(list<T>::node* left_part,
                                             list<T>::node* right_part) {
  node* result = nullptr;
  if (left_part == nullptr) {
    return right_part;
  } else if (right_part == nullptr) {
    return left_part;
  }
  if (left_part->value_ > right_part->value_) {
    result = right_part;
    result->next_ = merge_nodes(left_part, right_part->next_);
  } else {
    result = left_part;
    result->next_ = merge_nodes(left_part->next_, right_part);
  }
  return result;
}

template <typename value_type>
void list<value_type>::sort() {
  if (size_ > 1) {
    quick_sort(begin(), --end());
  }
}

template <typename value_type>
void list<value_type>::quick_sort(iterator first, iterator last) {
  if (first == last || first == size_node_ || last == size_node_ ||
      first == tail_) {
    return;
  }
  iterator pivot = partition(first, last);
  quick_sort(first, --pivot);
  quick_sort(++pivot, last);
}

template <typename value_type>
typename list<value_type>::iterator list<value_type>::partition(iterator first,
                                                                iterator last) {
  value_type pivot_value = last.ptr_->value_;
  iterator i = first;

  for (iterator j = first; j != last; ++j) {
    if (j.ptr_->value_ <= pivot_value) {
      std::swap(i.ptr_->value_, j.ptr_->value_);
      i++;
    }
  }

  std::swap(i.ptr_->value_, last.ptr_->value_);

  return i;
}

template <typename T>
list<T>::listIterator::listIterator() {}

template <typename T>
list<T>::listIterator::listIterator(typename list<T>::node* ptr) : ptr_(ptr) {}

template <typename T>
typename list<T>::listIterator& list<T>::listIterator::operator++() {
  ptr_ = ptr_->next_;
  return *this;
}

template <typename T>
typename list<T>::listIterator list<T>::listIterator::operator++(int) {
  ++(*this);
  return *this;
}

template <typename T>
typename list<T>::listIterator& list<T>::listIterator::operator--() {
  ptr_ = ptr_->prev_;
  return *this;
}

template <typename T>
typename list<T>::listIterator list<T>::listIterator::operator--(int) {
  --(*this);
  return *this;
}

template <typename T>
typename list<T>::listIterator list<T>::listIterator::operator-(
    list<T>::size_type value) {
  node* temp = ptr_;
  for (size_type i = 0; i < value; i++) {
    temp = temp->prev_;
  }
  listIterator result(temp);
  return result;
}

template <typename T>
typename list<T>::value_type list<T>::listIterator::operator*() const {
  return ptr_->value_;
}

template <typename T>
typename list<T>::value_type list<T>::listIterator::operator->() const {
  return &ptr_->value_;
}

template <typename T>
bool list<T>::listIterator::operator==(list<T>::listIterator other) {
  return (this->ptr_ == other.ptr_);
}

template <typename T>
bool list<T>::listIterator::operator!=(list<T>::listIterator other) {
  return (this->ptr_ != other.ptr_);
}

template <typename T>
list<T>::listConstIterator::listConstIterator(listIterator other)
    : listIterator(other) {}

template <typename T>
typename list<T>::const_reference list<T>::listConstIterator::operator*() {
  return listIterator::operator*();
}

template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args&&... args) {
  for (const auto& iter : {args...}) {
    insert(pos, iter);
  }
  return pos;
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args&&... args) {
  insert_many(begin(), args...);
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args&&... args) {
  for (const auto& iter : {args...}) {
    push_front(iter);
  }
}
};  // namespace s21