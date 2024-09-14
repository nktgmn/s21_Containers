#ifndef S21_MULTISET_ITERATORS_TPP_
#define S21_MULTISET_ITERATORS_TPP_

#include "../multiset/s21_multiset.h"

namespace s21 {

template <typename Key>
multiset<Key>::iter::SetIterator() noexcept : node(nullptr) {}

template <typename Key>
multiset<Key>::c_iter::ConstSetIterator() noexcept : node(nullptr) {}

template <typename Key>
multiset<Key>::iter::SetIterator(BaseNode* ptr) noexcept : node(ptr) {}

template <typename Key>
multiset<Key>::c_iter::ConstSetIterator(BaseNode* ptr) noexcept : node(ptr) {}

template <typename Key>
multiset<Key>::iter::SetIterator(Node* ptr) noexcept : node(ptr) {}

template <typename Key>
multiset<Key>::c_iter::ConstSetIterator(Node* ptr) noexcept : node(ptr) {}

template <typename Key>
multiset<Key>::iter::SetIterator(const iter& other) noexcept : node(other.node) {}

template <typename Key>
multiset<Key>::c_iter::ConstSetIterator(const c_iter& other) noexcept : node(other.node) {}

template <typename Key>
typename multiset<Key>::iter& multiset<Key>::iter::operator=(const iter& other) noexcept {
    if (this != &other) {
        node = other.node;
    }

    return *this;
}

template <typename Key>
typename multiset<Key>::c_iter& multiset<Key>::c_iter::operator=(const c_iter& other) noexcept {
    if (this != &other) {
        node = other.node;
    }

    return *this;
}

template <typename Key>
typename multiset<Key>::key& multiset<Key>::iter::operator*() noexcept {
    return static_cast<Node*>(node)->data;
}

template <typename Key>
const typename multiset<Key>::key& multiset<Key>::c_iter::operator*() noexcept {
    return static_cast<Node*>(node)->data;
}

template <typename Key>
typename multiset<Key>::iter& multiset<Key>::iter::operator++() noexcept {
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
typename multiset<Key>::c_iter& multiset<Key>::c_iter::operator++() noexcept {
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
typename multiset<Key>::iter& multiset<Key>::iter::operator--() noexcept {
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
typename multiset<Key>::c_iter& multiset<Key>::c_iter::operator--() noexcept {
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
bool multiset<Key>::iter::operator==(const iter& other) const noexcept {
    return node == other.node;
}

template <typename Key>
bool multiset<Key>::c_iter::operator==(const c_iter& other) const noexcept {
    return node == other.node;
}

template <typename Key>
bool multiset<Key>::iter::operator!=(const iter& other) const noexcept {
    return node != other.node;
}

template <typename Key>
bool multiset<Key>::c_iter::operator!=(const c_iter& other) const noexcept {
    return node != other.node;
}

}  // namespace s21

#endif  // S21_MULTISET_ITERATORS_TPP_
