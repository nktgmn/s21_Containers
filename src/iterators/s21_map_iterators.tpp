#ifndef S21_MAP_ITERATORS_TPP
#define S21_MAP_ITERATORS_TPP

#include "../map/s21_map.h"

namespace s21 {

template <typename Key, typename Value>
map<Key, Value>::iterator::MapIterator() noexcept : node(nullptr) {}

template <typename Key, typename Value>
map<Key, Value>::iterator::MapIterator(BaseNode* ptr) noexcept : node(ptr) {}

template <typename Key, typename Value>
map<Key, Value>::iterator::MapIterator(Node* ptr) noexcept : node(ptr) {}

template <typename Key, typename Value>
map<Key, Value>::iterator::MapIterator(const iterator& other) noexcept
    : node(other.node) {}

template <typename Key, typename Value>
typename map<Key, Value>::iterator& map<Key, Value>::iterator::operator=(
    const iterator& other) noexcept {
    if (this != &other) {
        node = other.node;
    }

    return *this;
}

template <typename Key, typename Value>
typename map<Key, Value>::pair&
map<Key, Value>::iterator::operator*() noexcept {
    return static_cast<Node*>(node)->kv;
}

template <typename Key, typename Value>
typename map<Key, Value>::iterator&
map<Key, Value>::iterator::operator++() noexcept {
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
typename map<Key, Value>::iterator&
map<Key, Value>::iterator::operator--() noexcept {
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
bool map<Key, Value>::iterator::operator==(
    const iterator& other) const noexcept {
    return node == other.node;
}

template <typename Key, typename Value>
bool map<Key, Value>::iterator::operator!=(
    const iterator& other) const noexcept {
    return node != other.node;
}

}  // namespace s21

#endif  // S21_MAP_ITERATORS_TPP
