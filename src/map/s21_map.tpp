#include "s21_map.h"

namespace s21 {

template <typename Key, typename T>
map<Key, T>::map() : AVLTree<Key, T>::AVLTree() {}

template <typename Key, typename T>
map<Key, T>::map(
    std::initializer_list<typename map<Key, T>::value_type> const& items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    this->insert(*i);
  }
}

template <typename Key, typename T>
map<Key, T>::map(const map& m) : tree_(m.get_tree()) {}

template <typename Key, typename T>
typename map<Key, T>::mapped_type& map<Key, T>::at(const Key& key) {
  auto iter = AVLTree<Key, T>::find_key(key);
  if (iter == nullptr) {
    throw std::length_error("error blin");
  }
  return iter.iterator_->value_;
}

template <typename Key, typename T>
typename map<Key, T>::mapped_type& map<Key, T>::operator[](const Key& key) {
  auto iter = AVLTree<Key, T>::find_key(key);
  if (iter == nullptr) {
    auto ins_pair = insert(std::make_pair(key, T()));
    iter = ins_pair.first;
  }
  return iter.iterator_->value_;
}

template <typename Key, typename T>
typename map<Key, T>::mapped_type& map<Key, T>::operatorHelper(const Key& key,
                                                               int flag) {
  iterator i = this->begin();
  if (i != nullptr) {
    for (; i != this->end(); i++) {
      if (i.iterator_->key_ == key) {
        return i.iterator_->value_;
      }
    }
    if (flag) {
      auto res = insert(value_type(key, mapped_type()));
      return res.first->second;
    } else {
      throw std::invalid_argument("Key doesn't exist");
    }
  }
  static mapped_type default_value;
  return default_value;
}

template <typename Key, typename T>
map<Key, T>::~map() {}

template <typename Key, typename T>
map<Key, T> map<Key, T>::operator=(map<Key, T>&& m) {
  if (this != &m) {
    tree_ = std::move(m.tree_);
  }
  return *this;
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::begin() {
  return AVLTree<Key, T>::begin();
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::end() {
  if (AVLTree<Key, T>::root_ == nullptr) {
    return begin();
  }
  typename AVLTree<Key, T>::AVLTreeNode* last_node =
      AVLTree<Key, T>::max_node(AVLTree<Key, T>::root_);
  return last_node;
}

template <typename Key, typename T>
bool map<Key, T>::empty() {
  if (AVLTree<Key, T>::root_ == nullptr) {
    return true;
  }
  if (AVLTree<Key, T>::root_->size_ == 0) {
    return true;
  }
  return false;
}

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::size() {
  size_type result = 0;
  if (AVLTree<Key, T>::root_ != nullptr) {
    result = AVLTree<Key, T>::root_->size_;
  }
  return result;
}

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::max_size() {
  return pow(2, (64 - log(sizeof(T)) / log(2))) - 1;
}

template <typename Key, typename T>
void map<Key, T>::clear() {
  if (this->get_tree().get_root()) {
    for (iterator i = this->begin(); i != this->end(); i++) {
      this->erase(i);
    }
  }
}

template <typename Key, typename T>  // снести
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const value_type& value) {
  return insert(value.first, value.second);
}

template <typename Key, typename T>  // снести
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const Key& key, const T& obj) {
  return AVLTree<Key, T>::insert(key, obj);
}

template <typename Key, typename T>
bool map<Key, T>::check_duplicates(const value_type& value) {
  bool result = false;
  auto i = this->begin();
  for (; i != this->end() && result != true; i++) {
    if (i.iterator_->value_ == value.second) {
      result = true;
    }
  }
  return result;
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
    const key_type& key, const mapped_type& obj) {
  if (this->empty()) {
    return insert(std::make_pair(key, obj));
  } else {
    iterator i = this->begin();
    for (; i != this->end(); ++i) {
      if (i->first == key) {
        i->second = obj;
        return std::make_pair(i, false);
      }
    }
    return insert(std::make_pair(key, obj));
  }
}

template <typename Key, typename T>
void map<Key, T>::erase(typename map<Key, T>::iterator pos) {
  if (pos != nullptr) {
    *pos++;
    // typename AVLTree<Key, T>::AVLTreeNode* temp_node = new typename
    // AVLTree<Key, T>::AVLTreeNode(pos.iterator_->key_, pos.iterator_->value_,
    // pos.iterator_->parent_);
    AVLTree<Key, T>::root_ = AVLTree<Key, T>::remove_node(
        AVLTree<Key, T>::root_, pos.iterator_->key_);
  }
  AVLTree<Key, T>::root_->size_--;
}

template <typename Key, typename T>
void map<Key, T>::swap(map& other) {
  tree_.Swap(other.tree_);
}

template <typename Key, typename T>
void map<Key, T>::merge(map& other) {
  std::pair<typename map<Key, T>::iterator, bool> result;
  iterator iter = other.begin();
  while (iter != other.end()) {
    result = this->insert(iter.iterator_->key_, iter.iterator_->value_);
    if (result.second) other.erase(iter);
    iter++;
  }
}

template <typename Key, typename T>
bool map<Key, T>::contains(const Key& key) {
  bool result = false;
  for (iterator iter = this->begin(); iter != this->end() && result != true;
       iter++) {
    if (iter.iterator_->key_ == key) result = true;
  }
  return result;
}

template <typename Key, typename T>
const AVLTree<typename map<Key, T>::value_type, T>& map<Key, T>::get_tree()
    const {
  return tree_;
}

template <typename Key, typename T>
template <typename... Args>
std::vector<std::pair<typename map<Key, T>::iterator, bool>>
map<Key, T>::insert_many(Args&&... args) {
  std::vector<std::pair<iterator, bool>> to_return;
  for (const auto& iter : {args...}) {
    to_return = insert(iter);
  }
  return to_return;
}

}  // namespace s21
