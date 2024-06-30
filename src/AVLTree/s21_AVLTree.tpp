#include "s21_AVLTree.h"

template <typename Key, typename T>
AVLTree<Key, T>::AVLTree() : root_(nullptr) {}

template <typename Key, typename T>
AVLTree<Key, T>::~AVLTree() {
  clear();
}

template <typename Key, typename T>
AVLTree<Key, T>::AVLTree(const AVLTree &other)
    : root_(copy_tree(other.root_)) {}

template <typename Key, typename T>
typename AVLTree<Key, T>::AVLTreeNode *AVLTree<Key, T>::copy_tree(
    AVLTree<Key, T>::AVLTreeNode *node) {
  if (node == nullptr) {
    return nullptr;
  }

  AVLTree<Key, T>::AVLTreeNode *new_node =
      new AVLTree<Key, T>::AVLTreeNode(node->key_, node->value_, node);
  new_node->size_ = node->size_;
  new_node->parent_ = node->parent_;
  new_node->left_ = copy_tree(node->left_);
  new_node->right_ = copy_tree(node->right_);
  return new_node;
}

template <typename Key, typename T>
typename AVLTree<Key, T>::Iterator AVLTree<Key, T>::begin() {
  return Iterator(min_node(root_));
}

template <typename Key, typename T>
typename AVLTree<Key, T>::Iterator AVLTree<Key, T>::end() {
  if (root_ == nullptr) {
    return begin();
  }
  // AVLTreeNode *last_node = max_node(root_);
  // Iterator test(nullptr, last_node);
  return Iterator(max_node(root_));
}

template <typename Key, typename T>
void AVLTree<Key, T>::clear() {
  if (root_ != nullptr) clear_node(root_);
  root_ = nullptr;
}

template <typename Key, typename T>
std::pair<typename AVLTree<Key, T>::Iterator, bool> AVLTree<Key, T>::insert(
    const Key &key, const T &obj) {
  std::pair<Iterator, bool> return_value;
  if (root_ == nullptr) {
    root_ = new AVLTreeNode(key, obj);
    return_value.first = Iterator(root_);
    return_value.second = true;
    this->inserted_ = true;
  } else {
    bool check_insert = insert_with_balance(root_, key, obj);
    return_value.first = find_key(key);
    return_value.second = check_insert;
    this->inserted_ = check_insert;
  }
  upper_size();
  return return_value;
}

template <typename Key, typename T>
std::pair<typename AVLTree<Key, T>::Iterator, bool>
AVLTree<Key, T>::insert_node(AVLTree<Key, T>::AVLTreeNode *node) {
  const Key &key = node->key_;
  std::pair<Iterator, bool> return_value;
  if (root_ == nullptr) {
    root_ = new AVLTreeNode(key, key);
    return_value.first = Iterator(root_);
    return_value.second = true;
    this->inserted_ = true;
  } else {
    bool check_insert = insert_with_balance(root_, key, key);
    return_value.first = find_key(key);
    return_value.second = check_insert;
    this->inserted_ = check_insert;
  }
  return return_value;
}

template <typename Key, typename T>
typename AVLTree<Key, T>::iterator AVLTree<Key, T>::find_key(const Key &key) {
  AVLTreeNode *exact_node = recurs_find(root_, key);
  return Iterator(exact_node);
}

template <typename Key, typename T>
typename AVLTree<Key, T>::AVLTreeNode *AVLTree<Key, T>::Iterator::move_forward(
    AVLTree::AVLTreeNode *node) {
  if (node->right_ != nullptr) {
    return min_node(node->right_);
  }
  AVLTreeNode *parent = node->parent_;
  while (parent != nullptr && node == parent->right_) {
    node = parent;
    parent = parent->parent_;
  }
  return parent;
}

template <typename Key, typename T>
typename AVLTree<Key, T>::AVLTreeNode *AVLTree<Key, T>::Iterator::move_back(
    AVLTree::AVLTreeNode *node) {
  if (node->left_ != nullptr) {
    return max_node(node->left_);
  }
  AVLTreeNode *parent = node->parent_;
  while (parent != nullptr && node == parent->left_) {
    node = parent;
    parent = node->parent_;
  }
  return parent;
}

template <typename Key, typename T>
AVLTree<Key, T>::Iterator::Iterator()
    : iterator_(nullptr), past_iterator_(nullptr) {}

template <typename Key, typename T>
AVLTree<Key, T>::Iterator::Iterator(AVLTree::AVLTreeNode *node,
                                    AVLTree::AVLTreeNode *past_node)
    : iterator_(node), past_iterator_(past_node) {}

template <typename Key, typename T>
typename AVLTree<Key, T>::Iterator &AVLTree<Key, T>::Iterator::operator++() {
  AVLTreeNode *tmp;
  if (iterator_ != nullptr) {
    tmp = max_node(iterator_);
  }
  iterator_ = move_forward(iterator_);
  if (iterator_ == nullptr) {
    past_iterator_ = tmp;
  }
  return *this;
}

template <typename Key, typename T>
typename AVLTree<Key, T>::Iterator AVLTree<Key, T>::Iterator::operator++(int) {
  Iterator temp = *this;
  operator++();
  return temp;
}

template <typename Key, typename T>
typename AVLTree<Key, T>::Iterator &AVLTree<Key, T>::Iterator::operator--() {
  if (iterator_ == nullptr && past_iterator_ != nullptr) {
    *this = past_iterator_;
    return *this;
  }
  iterator_ = move_back(iterator_);
  return *this;
}

template <typename Key, typename T>
typename AVLTree<Key, T>::Iterator AVLTree<Key, T>::Iterator::operator--(int) {
  Iterator temp = *this;
  operator--();
  return temp;
}

template <typename Key, typename T>
typename AVLTree<Key, T>::reference AVLTree<Key, T>::Iterator::operator*() {
  if (iterator_ == nullptr) {
    static T fake_value{};
    return fake_value;
  }
  return iterator_->value_;
}

template <typename Key, typename T>
bool AVLTree<Key, T>::Iterator::operator==(const AVLTree::Iterator &it) {
  return iterator_ == it.iterator_;
}

template <typename Key, typename Value>
AVLTree<Key, Value> &AVLTree<Key, Value>::operator=(AVLTree &&other) noexcept {
  if (this != &other) {
    root_ = other.root_;
    other.root_ = nullptr;
  }
  return *this;
}

template <typename Key, typename T>
bool AVLTree<Key, T>::Iterator::operator!=(const AVLTree::Iterator &it) {
  return iterator_ != it.iterator_;
}

template <typename Key, typename T>
T &AVLTree<Key, T>::Iterator::return_value() {
  if (iterator_ == nullptr) {
    static T fake_value{};
    return fake_value;
  }
  return iterator_->value_;
}

template <typename Key, typename T>
AVLTree<Key, T>::AVLTreeNode::AVLTreeNode(Key key, value_type value)
    : key_(key), value_(value) {}

template <typename Key, typename T>
AVLTree<Key, T>::AVLTreeNode::AVLTreeNode(Key key, value_type value,
                                          AVLTreeNode *node)
    : key_(key), value_(value), parent_(node) {}

template <typename Key, typename T>
void AVLTree<Key, T>::clear_node(AVLTreeNode *node) {
  if (node == nullptr) return;
  clear_node(node->left_);
  clear_node(node->right_);
  delete node;
}

template <typename Key, typename T>
int AVLTree<Key, T>::height(AVLTree::AVLTreeNode *node) {
  return node == nullptr ? -1 : node->height_;
}

template <typename Key, typename T>
int AVLTree<Key, T>::balance_factor(AVLTree::AVLTreeNode *node) {
  return node == nullptr ? 0 : height(node->right_) - height(node->left_);
}

template <typename Key, typename T>
void AVLTree<Key, T>::fix_height(AVLTree::AVLTreeNode *node) {
  node->height_ = std::max(height(node->left_), height(node->right_)) + 1;
}

template <typename Key, typename T>
void AVLTree<Key, T>::swap_value(AVLTree::AVLTreeNode *a,
                                 AVLTree::AVLTreeNode *b) {
  // AVLTree<Key, T>::key_type* temp_a_key = const_cast<AVLTree<Key,
  // T>::key_type*>(&a->key_); a->key_ = temp_b_key;

  std::swap(a->key_, b->key_);
  std::swap(a->value_, b->value_);
}

template <typename Key, typename T>
void AVLTree<Key, T>::upper_size() {
  if (this->root_ != nullptr) {
    this->root_->size_++;
  }
}

template <typename Key, typename T>
void AVLTree<Key, T>::right_rotation(AVLTree::AVLTreeNode *node) {
  AVLTreeNode *new_left = node->left_->left_;
  AVLTreeNode *new_right_right = node->right_;
  AVLTreeNode *new_right_left = node->left_->right_;

  swap_value(node, node->left_);
  node->right_ = node->left_;

  node->left_ = new_left;
  if (node->left_) {
    node->left_->parent_ = node;
  }

  node->right_->left_ = new_right_left;
  if (node->right_->left_) {
    node->right_->left_->parent_ = node->right_;
  }

  node->right_->right_ = new_right_right;
  if (node->right_->right_) {
    node->right_->right_->parent_ = node->right_;
  }

  fix_height(node->right_);
  fix_height(node);
}

template <typename Key, typename T>
void AVLTree<Key, T>::left_rotation(AVLTree::AVLTreeNode *node) {
  AVLTreeNode *new_right = node->right_->right_;
  AVLTreeNode *new_left_left = node->left_;
  AVLTreeNode *new_left_right = node->right_->left_;

  swap_value(node, node->right_);
  node->left_ = node->right_;

  node->right_ = new_right;
  if (node->right_) {
    node->right_->parent_ = node;
  }

  node->left_->right_ = new_left_right;
  if (node->left_->right_) {
    node->left_->right_->parent_ = node->left_;
  }

  node->left_->left_ = new_left_left;
  if (node->left_->left_) {
    node->left_->left_->parent_ = node->left_;
  }

  fix_height(node->left_);
  fix_height(node);
}

template <typename Key, typename T>
void AVLTree<Key, T>::balance(AVLTreeNode *node) {
  int balance = balance_factor(node);
  if (balance == -2) {
    if (balance_factor(node->left_) == 1) left_rotation(node->left_);
    right_rotation(node);
  } else if (balance == 2) {
    if (balance_factor(node->right_) == -1) right_rotation(node->right_);
    left_rotation(node);
  }
}

template <typename Key, typename T>
typename AVLTree<Key, T>::AVLTreeNode *AVLTree<Key, T>::min_node(
    AVLTree::AVLTreeNode *node) {
  if (node == nullptr) return nullptr;
  if (node->left_ == nullptr) return node;
  return min_node(node->left_);
}

template <typename Key, typename T>
typename AVLTree<Key, T>::AVLTreeNode *AVLTree<Key, T>::max_node(
    AVLTree::AVLTreeNode *node) {
  if (node == nullptr) return nullptr;
  if (node->right_ == nullptr) return node;
  return max_node(node->right_);
}

template <typename Key, typename T>
bool AVLTree<Key, T>::insert_with_balance(AVLTree::AVLTreeNode *node,
                                          const Key &key,
                                          const value_type &value) {
  bool check_insert = false;
  if (key < node->key_) {
    if (node->left_ == nullptr) {
      node->left_ = new AVLTreeNode(key, value, node);
      check_insert = true;
    } else {
      check_insert = insert_with_balance(node->left_, key, value);
    }
  } else if (key > node->key_) {
    if (node->right_ == nullptr) {
      node->right_ = new AVLTreeNode(key, value, node);
      check_insert = true;
    } else {
      check_insert = insert_with_balance(node->right_, key, value);
    }
  } else if (key == node->key_) {
    return check_insert;
  }
  fix_height(node);
  balance(node);
  return check_insert;
}

template <typename Key, typename T>
typename AVLTree<Key, T>::AVLTreeNode *AVLTree<Key, T>::recurs_find(
    AVLTree::AVLTreeNode *node, const Key &key) {
  if (node == nullptr || node->key_ == key) return node;
  if (key > node->key_) {
    return recurs_find(node->right_, key);
  } else {
    return recurs_find(node->left_, key);
  }
}

template <typename Key, typename T>
void AVLTree<Key, T>::Swap(AVLTree<Key, T> &other) {
  std::swap(root_, other.root_);
}

template <typename Key, typename T>
typename AVLTree<Key, T>::AVLTreeNode *AVLTree<Key, T>::get_root() {
  return root_;
}

template <typename Key, typename T>
typename AVLTree<Key, T>::AVLTreeNode *AVLTree<Key, T>::remove_node(
    AVLTree<Key, T>::AVLTreeNode *node, Key key) {
  if (node == nullptr) {
    return nullptr;
  }
  if (key < node->key_) {
    node->left_ = remove_node(node->left_, key);
  } else if (key > node->key_) {
    node->right_ = remove_node(node->right_, key);
  } else {
    if (node->left_ == nullptr || node->right_ == nullptr) {
      AVLTreeNode *node_right = node->right_;
      AVLTreeNode *node_left = node->left_;
      AVLTreeNode *node_parent = node->parent_;
      delete node;
      if (node_left == nullptr) {
        node = node_right;
      } else {
        node = node_left;
      }
      if (node != nullptr) {
        node->parent_ = node_parent;
      }
    } else {
      AVLTreeNode *min_in_right = min_node(node->right_);
      node->key_ = min_in_right->key_;
      node->value_ = min_in_right->value_;
      node->right_ = remove_node(node->right_, min_in_right->key_);
    }
  }
  if (node != nullptr) {
    fix_height(node);
    balance(node);
  }
  return node;
}

template <typename Key, typename T>
typename AVLTree<Key, T>::AVLTreeNode *AVLTree<Key, T>::search_for_set(
    Key key) {
  return search_node(root_, key);
}

template <typename Key, typename T>
typename AVLTree<Key, T>::AVLTreeNode *AVLTree<Key, T>::search_node(
    AVLTree<Key, T>::AVLTreeNode *node, Key key) {
  if (!node || node->key_ == key) {
    return node;
  }
  if (key < node->key_) {
    return search_node(node->left_, key);
  } else {
    return search_node(node->right_, key);
  }
}

template <typename Key, typename T>
bool AVLTree<Key, T>::get_inserted() {
  return this->inserted_;
}

template <typename Key, typename T>
size_t AVLTree<Key, T>::size(AVLTree<Key, T>::AVLTreeNode *node) {
  size_t left_size = size(node->left_);
  size_t right_size = size(node->right_);
  root_->size_ = 1 + left_size + right_size;
  return 1 + left_size + right_size;
}

template <typename Key, typename T>
size_t AVLTree<Key, T>::max_size() {
  return std::numeric_limits<size_type>::max() /
         sizeof(typename AVLTree<Key, T>::AVLTreeNode);
}