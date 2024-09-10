#ifndef S21_MAP_ITERATORS_TPP_
#define S21_MAP_ITERATORS_TPP_

#include "../map/s21_map.h"

namespace s21 {

template <typename Key, typename Value>
map<Key, Value>::iter::MapIterator() noexcept : node(nullptr) {}

template <typename Key, typename Value>
map<Key, Value>::c_iter::ConstMapIterator() noexcept : node(nullptr) {}

template <typename Key, typename Value>
map<Key, Value>::iter::MapIterator(BaseNode* ptr) noexcept : node(ptr) {}

template <typename Key, typename Value>
map<Key, Value>::c_iter::ConstMapIterator(BaseNode* ptr) noexcept : node(ptr) {}

template <typename Key, typename Value>
map<Key, Value>::iter::MapIterator(Node* ptr) noexcept : node(ptr) {}

template <typename Key, typename Value>
map<Key, Value>::c_iter::ConstMapIterator(Node* ptr) noexcept : node(ptr) {}

template <typename Key, typename Value>
map<Key, Value>::iter::MapIterator(const iter& other) noexcept : node(other.node) {}

template <typename Key, typename Value>
map<Key, Value>::c_iter::ConstMapIterator(const c_iter& other) noexcept : node(other.node) {}

template <typename Key, typename Value>
typename map<Key, Value>::iter& map<Key, Value>::iter::operator=(const iter& other) noexcept {
    if (this != &other) {
        node = other.node;
    }

    return *this;
}

template <typename Key, typename Value>
typename map<Key, Value>::c_iter& map<Key, Value>::c_iter::operator=(const c_iter& other) noexcept {
    if (this != &other) {
        node = other.node;
    }

    return *this;
}

template <typename Key, typename Value>
typename map<Key, Value>::pair& map<Key, Value>::iter::operator*() noexcept {
    return static_cast<Node*>(node)->kv;
}

template <typename Key, typename Value>
const typename map<Key, Value>::pair& map<Key, Value>::c_iter::operator*() noexcept {
    return static_cast<Node*>(node)->kv;
}

template <typename Key, typename Value>
typename map<Key, Value>::iter& map<Key, Value>::iter::operator++() noexcept {
    if (node->right) {
        node = node->right;
        while (node->left) {
            node = node->left;
        }
    } else {
        BaseNode* parent = node->parent;
        while (parent && node == parent->right) {
            node = parent;
            parent = parent->parent;
        }
        node = parent;
    }

    return *this;
}

template <typename Key, typename Value>
typename map<Key, Value>::c_iter& map<Key, Value>::c_iter::operator++() noexcept {
    if (node->right) {
        node = node->right;
        while (node->left) {
            node = node->left;
        }
    } else {
        BaseNode* parent = node->parent;
        while (parent && node == parent->right) {
            node = parent;
            parent = parent->parent;
        }
        node = parent;
    }

    return *this;
}

template <typename Key, typename Value>
typename map<Key, Value>::iter& map<Key, Value>::iter::operator--() noexcept {
    if (node->left) {
        node = node->left;
        while (node->right) {
            node = node->right;
        }
    } else {
        BaseNode* parent = node->parent;
        while (parent && node == parent->left) {
            node = parent;
            parent = parent->parent;
        }
        node = parent;
    }

    return *this;
}

template <typename Key, typename Value>
typename map<Key, Value>::c_iter& map<Key, Value>::c_iter::operator--() noexcept {
    if (node->left) {
        node = node->left;
        while (node->right) {
            node = node->right;
        }
    } else {
        BaseNode* parent = node->parent;
        while (parent && node == parent->left) {
            node = parent;
            parent = parent->parent;
        }
        node = parent;
    }

    return *this;
}

template <typename Key, typename Value>
bool map<Key, Value>::iter::operator==(const iter& other) const noexcept {
    return node == other.node;
}

template <typename Key, typename Value>
bool map<Key, Value>::c_iter::operator==(const c_iter& other) const noexcept {
    return node == other.node;
}

template <typename Key, typename Value>
bool map<Key, Value>::iter::operator!=(const iter& other) const noexcept {
    return node != other.node;
}

template <typename Key, typename Value>
bool map<Key, Value>::c_iter::operator!=(const c_iter& other) const noexcept {
    return node != other.node;
}

}  // namespace s21

#endif  // S21_MAP_ITERATORS_TPP_
