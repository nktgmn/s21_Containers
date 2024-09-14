#ifndef S21_SET_ITERATORS_TPP_
#define S21_SET_ITERATORS_TPP_

#include "../set/s21_set.h"

namespace s21 {

template <typename Key>
set<Key>::iter::SetIterator() noexcept : node(nullptr) {}

template <typename Key>
set<Key>::c_iter::ConstSetIterator() noexcept : node(nullptr) {}

template <typename Key>
set<Key>::iter::SetIterator(BaseNode* ptr) noexcept : node(ptr) {}

template <typename Key>
set<Key>::c_iter::ConstSetIterator(BaseNode* ptr) noexcept : node(ptr) {}

template <typename Key>
set<Key>::iter::SetIterator(Node* ptr) noexcept : node(ptr) {}

template <typename Key>
set<Key>::c_iter::ConstSetIterator(Node* ptr) noexcept : node(ptr) {}

template <typename Key>
set<Key>::iter::SetIterator(const iter& other) noexcept : node(other.node) {}

template <typename Key>
set<Key>::c_iter::ConstSetIterator(const c_iter& other) noexcept : node(other.node) {}

template <typename Key>
typename set<Key>::iter& set<Key>::iter::operator=(const iter& other) noexcept {
    if (this != &other) {
        node = other.node;
    }

    return *this;
}

template <typename Key>
typename set<Key>::c_iter& set<Key>::c_iter::operator=(const c_iter& other) noexcept {
    if (this != &other) {
        node = other.node;
    }

    return *this;
}

template <typename Key>
typename set<Key>::key& set<Key>::iter::operator*() noexcept {
    return static_cast<Node*>(node)->data;
}

template <typename Key>
const typename set<Key>::key& set<Key>::c_iter::operator*() noexcept {
    return static_cast<Node*>(node)->data;
}

template <typename Key>
typename set<Key>::iter& set<Key>::iter::operator++() noexcept {
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

template <typename Key>
typename set<Key>::c_iter& set<Key>::c_iter::operator++() noexcept {
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

template <typename Key>
typename set<Key>::iter& set<Key>::iter::operator--() noexcept {
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

template <typename Key>
typename set<Key>::c_iter& set<Key>::c_iter::operator--() noexcept {
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

template <typename Key>
bool set<Key>::iter::operator==(const iter& other) const noexcept {
    return node == other.node;
}

template <typename Key>
bool set<Key>::c_iter::operator==(const c_iter& other) const noexcept {
    return node == other.node;
}

template <typename Key>
bool set<Key>::iter::operator!=(const iter& other) const noexcept {
    return node != other.node;
}

template <typename Key>
bool set<Key>::c_iter::operator!=(const c_iter& other) const noexcept {
    return node != other.node;
}

}  // namespace s21

#endif  // S21_SET_ITERATORS_TPP_
