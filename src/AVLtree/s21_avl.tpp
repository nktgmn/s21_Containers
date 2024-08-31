#ifndef S21_AVLTREE_TPP_
#define S21_AVLTREE_TPP_

#include "s21_avl.h"

namespace s21 {

template <typename T>
AVL<T>::AVL() : head(nullptr) {}

template <typename T>
AVL<T>::Node::Node(const T& value)
    : data(T(value)), left(nullptr), right(nullptr), height(1) {}

template <typename T>
AVL<T>::Node::~Node() {}

template <typename T>
AVL<T>::~AVL() {
    delete_node(head);
}

template <typename T>
void AVL<T>::delete_node(Node* node) {
    if (node) {
        delete_node(node->left);
        delete_node(node->right);
        delete node;
    }
}

template <typename T>
typename AVL<T>::Node* AVL<T>::insert_private(Node* node, const T& value) {
    if (node == nullptr) {
        return new Node(value);
    } else if (value < node->data) {
        node->left = insert_private(node->left, value);
    } else if (value > node->data) {
        node->right = insert_private(node->right, value);
    } else {
        return node;
    }

    node->height =
        std::max(get_height(node->left), get_height(node->right)) + 1;

    int balance_factor = get_balance_factor(node);

    if (balance_factor > 1 && value < node->left->data) {
        return rotate_right(node);
    }

    if (balance_factor < -1 && value > node->right->data) {
        return rotate_left(node);
    }

    if (balance_factor > 1 && value > node->left->data) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    if (balance_factor < -1 && value < node->right->data) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::rotate_right(Node* node) {
    Node* new_root = node->left;
    Node* right = new_root->right;

    new_root->right = node;
    node->left = right;

    node->height =
        1 + std::max(get_height(node->left), get_height(node->right));
    new_root->height =
        1 + std::max(get_height(new_root->left), get_height(new_root->right));

    return new_root;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::rotate_left(Node* node) {
    Node* new_root = node->right;
    Node* left = new_root->left;

    new_root->left = node;
    node->right = left;

    node->height =
        1 + std::max(get_height(node->left), get_height(node->right));
    new_root->height =
        1 + std::max(get_height(new_root->left), get_height(new_root->right));

    return new_root;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::min_value_node(Node* node) {
    Node* current = node;

    while (current->left) {
        current = current->left;
    }

    return current;
}

template <typename T>
T* AVL<T>::search_private(Node* node, const T& value) const {
    if (!node) return nullptr;

    if (value < node->data)
        return search_private(node->left, value);
    else if (value > node->data)
        return search_private(node->right, value);
    else
        return &node->data;
}

template <typename T>
typename AVL<T>::Node* AVL<T>::erase_private(Node* node, const T& value) {
    if (!node) {
        return node;
    }

    if (value < node->data) {
        node->left = erase_private(node->left, value);
    } else if (value > node->data) {
        node->right = erase_private(node->right, value);
    } else {
        if (!node->left || !node->right) {
            Node* tmp = node->left ? node->left : node->right;
            delete node;
            return tmp;
        } else {
            Node* tmp = min_value_node(node->right);
            node->data = tmp->data;
            node->right = erase_private(node->right, node->data);
        }
    }

    node->height =
        std::max(get_height(node->left), get_height(node->right)) + 1;

    int balance_factor = get_balance_factor(node);

    if (balance_factor > 1 && value < node->left->data) {
        return rotate_right(node);
    }

    if (balance_factor < -1 && value > node->right->data) {
        return rotate_left(node);
    }

    if (balance_factor > 1 && value > node->left->data) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    if (balance_factor < -1 && value < node->right->data) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    return node;
}

template <typename T>
void AVL<T>::insert(const T& value) {
    head = insert_private(head, value);
}

template <typename T>
void AVL<T>::erase(const T& value) {
    head = erase_private(head, value);
}

template <typename T>
T* AVL<T>::search(const T& value) const {
    return search_private(head, value);
}

template <typename T>
int AVL<T>::get_height(Node* node) {
    return node != nullptr ? node->height : 0;
}

template <typename T>
int AVL<T>::get_balance_factor(Node* node) {
    return node != nullptr ? get_height(node->left) - get_height(node->right)
                           : 0;
}

}  // namespace s21

#endif  // S21_AVLTREE_TPP_