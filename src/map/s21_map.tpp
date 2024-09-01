#ifndef S21_MAP_TPP_
#define S21_MAP_TPP_

#include "s21_map.h"

namespace s21 {

template <typename Key, typename Value>
struct map<Key, Value>::BaseNode {
    BaseNode* left;
    BaseNode* right;
    BaseNode* parent;
    int height;
    BaseNode();
};

template <typename Key, typename Value>
struct map<Key, Value>::Node : BaseNode {
    pair kv;
    Node(const pair& value);
};

template <typename Key, typename Value>
map<Key, Value>::BaseNode::BaseNode() : left(nullptr), right(nullptr), parent(this), height(1) {
    std::cout << "base node created" << std::endl;
}

template <typename Key, typename Value>
map<Key, Value>::Node::Node(const pair& value) : BaseNode(), kv(value) {}

template <typename Key, typename Value>
map<Key, Value>::map() noexcept : fake_node(new BaseNode()), leftmost(fake_node), size_(0) {
    std::cout << "map created" << std::endl;
}

template <typename Key, typename Value>
map<Key, Value>::map(const map& other) : fake_node(new BaseNode()), leftmost(fake_node), size_(0) {
    try {
        for (auto it = other.cbegin(); it != other.cend(); ++it) {
            insert(*it);
        }
    } catch(...) {
        delete_node(static_cast<Node*>(fake_node));
        throw;
    }
}

template <typename Key, typename Value>
map<Key, Value>::map(std::initializer_list<pair> init) : fake_node(new BaseNode()), leftmost(fake_node), size_(0) {
    try {
        for (const auto& elem : init) {
            insert(elem);
            // std::cout << "insert " << elem.first << std::endl;
        }
    } catch (...) {
        delete_node(static_cast<Node*>(fake_node));
        throw;
    }
}

template <typename Key, typename Value>
map<Key, Value>::map(map&& other) : fake_node(new BaseNode()), leftmost(fake_node), size_(other.size_) {
    if (other.size() > 0) {
        fake_node->left = other.fake_node->left;
        fake_node->left->parent = fake_node;
        leftmost = other.leftmost;

        other.fake_node->left = nullptr;
        other.leftmost = other.fake_node;
        other.size_ = 0;
    }
}

template <typename Key, typename Value>
map<Key, Value>::~map() noexcept {
    delete_node(static_cast<Node*>(fake_node));
}

template <typename Key, typename Value>
typename map<Key, Value>::iter map<Key, Value>::begin() noexcept {
    return iter(leftmost);
}

template <typename Key, typename Value>
typename map<Key, Value>::iter map<Key, Value>::end() noexcept {
    return iter(fake_node);
}

template <typename Key, typename Value>
typename map<Key, Value>::c_iter map<Key, Value>::cbegin() const noexcept {
    std::cout << "cbegin " << leftmost << std::endl;
    return c_iter(leftmost);
}

template <typename Key, typename Value>
typename map<Key, Value>::c_iter map<Key, Value>::cend() const noexcept {
    std::cout << "cend " << fake_node << std::endl;
    return c_iter(fake_node);
}

template <typename Key, typename Value>
bool map<Key, Value>::empty() const noexcept {
    return size() == 0;
}

template <typename Key, typename Value>
size_t map<Key, Value>::size() const noexcept {
    return size_;
}

template <typename Key, typename Value>
size_t map<Key, Value>::max_size() const noexcept {
    return std::numeric_limits<size_t>::max() / sizeof(Node);
}

template <typename Key, typename Value>
int map<Key, Value>::get_height(BaseNode* node) {
    return node ? node->height : 0;
}

template <typename Key, typename Value>
int map<Key, Value>::get_balance_factor(BaseNode* node) {
    return node ? get_height(node->left) - get_height(node->right) : 0;
}

template <typename Key, typename Value>
void map<Key, Value>::delete_node(Node* node) {
    if (node) {
        delete_node(static_cast<Node*>(node->left));
        delete_node(static_cast<Node*>(node->right));
        if (node == fake_node) {
            delete static_cast<BaseNode*>(node);
        } else {
            --size_;
            delete node;
        }
    }
}

template <typename Key, typename Value>
typename map<Key, Value>::BaseNode* map<Key, Value>::min_value_node(
    BaseNode* node) {
    BaseNode* current = node;

    while (current->left) {
        current = current->left;
    }

    return current;
}

template <typename Key, typename Value>
typename map<Key, Value>::BaseNode* map<Key, Value>::rotate_right(
    BaseNode* node) {
    BaseNode* new_root = node->left;
    BaseNode* right = new_root->right;

    new_root->right = node;
    node->left = right;

    new_root->parent = node->parent;

    if (new_root->parent == fake_node) {
        fake_node->left = new_root;
    }

    node->parent = new_root;
    if (right) {
        right->parent = node;
    }

    node->height = 1 + std::max(get_height(node->left), get_height(node->right));
    new_root->height = 1 + std::max(get_height(new_root->left), get_height(new_root->right));

    return new_root;
}

template <typename Key, typename Value>
typename map<Key, Value>::BaseNode* map<Key, Value>::rotate_left(
    BaseNode* node) {
    BaseNode* new_root = node->right;
    BaseNode* left = new_root->left;

    new_root->left = node;
    node->right = left;

    new_root->parent = node->parent;
    node->parent = new_root;
    if (left) {
        left->parent = node;
    }

    node->height = 1 + std::max(get_height(node->left), get_height(node->right));
    new_root->height = 1 + std::max(get_height(new_root->left), get_height(new_root->right));

    return new_root;
}

template <typename Key, typename Value>
std::pair<typename map<Key, Value>::BaseNode*, bool>
map<Key, Value>::insert_private(BaseNode* node, const pair& value) {
    bool inserted = false;

    if (node == nullptr) {
        node = new Node(value);
        ++size_;
        if (leftmost && value.first < static_cast<Node*>(leftmost)->kv.first) {
            leftmost = node;
        }
        return {node, true};
    } else if (value.first < static_cast<Node*>(node)->kv.first) {
        auto insert_res = insert_private(node->left, value);
        node->left = insert_res.first;
        inserted = insert_res.second;
        node->left->parent = node;
    } else if (value.first > static_cast<Node*>(node)->kv.first) {
        auto insert_res = insert_private(node->right, value);
        node->right = insert_res.first;
        inserted = insert_res.second;
        node->right->parent = node;
    } else {
        return {node, false};
    }

    node->height = std::max(get_height(node->left), get_height(node->right)) + 1;

    int balance_factor = get_balance_factor(node);

    if (balance_factor > 1 &&
        value.first < static_cast<Node*>(node->left)->kv.first) {
        node = rotate_right(node);
    }

    if (balance_factor < -1 &&
        value.first > static_cast<Node*>(node->right)->kv.first) {
        node = rotate_left(node);
    }

    if (balance_factor > 1 &&
        value.first > static_cast<Node*>(node->left)->kv.first) {
        node->left = rotate_left(node->left);
        node = rotate_right(node);
    }

    if (balance_factor < -1 &&
        value.first < static_cast<Node*>(node->right)->kv.first) {
        node->right = rotate_right(node->right);
        node = rotate_left(node);
    }

    if (node->parent == fake_node && fake_node->left != node) {
        fake_node->left = node;
    }

    return {node, inserted};
}

// template <typename Key, typename Value>
// typename AVL<T>::Node* AVL<T>::erase_private(Node* node, const T& value) {
//     if (!node) {
//         return node;
//     }

//     if (value < node->data) {
//         node->left = erase_private(node->left, value);
//     } else if (value > node->data) {
//         node->right = erase_private(node->right, value);
//     } else {
//         if (!node->left || !node->right) {
//             Node* tmp = node->left ? node->left : node->right;
//             delete node;
//             return tmp;
//         } else {
//             Node* tmp = min_value_node(node->right);
//             node->data = tmp->data;
//             node->right = erase_private(node->right, node->data);
//         }
//     }

//     node->height =
//         std::max(get_height(node->left), get_height(node->right)) + 1;

//     int balance_factor = get_balance_factor(node);

//     if (balance_factor > 1 && value < node->left->data) {
//         return rotate_right(node);
//     }

//     if (balance_factor < -1 && value > node->right->data) {
//         return rotate_left(node);
//     }

//     if (balance_factor > 1 && value > node->left->data) {
//         node->left = rotate_left(node->left);
//         return rotate_right(node);
//     }

//     if (balance_factor < -1 && value < node->right->data) {
//         node->right = rotate_right(node->right);
//         return rotate_left(node);
//     }

//     return node;
// }

// template <typename Key, typename Value>
// T* AVL<T>::search_private(Node* node, const T& value) const {
//     if (!node) return nullptr;

//     if (value < node->data)
//         return search_private(node->left, value);
//     else if (value > node->data)
//         return search_private(node->right, value);
//     else
//         return &node->data;
// }

template <typename Key, typename Value>
void map<Key, Value>::clear() noexcept {
    delete_node(fake_node->left);
}

template <typename Key, typename Value>
std::pair<typename map<Key, Value>::iter, bool> map<Key, Value>::insert(const pair& value) {
    auto insert_res = insert_private(fake_node->left, value);
    if (!fake_node->left) {
        fake_node->left = insert_res.first;
        fake_node->left->parent = fake_node;
        leftmost = fake_node->left;
    }

    return {MapIterator(insert_res.first), insert_res.second};
}

// template <typename Key, typename Value>
// void AVL<T>::erase(const T& value) {
//     head = erase_private(head, value);
// }

// template <typename Key, typename Value>
// T* AVL<T>::search(const T& value) const {
//     return search_private(head, value);
// }

}  // namespace s21

#endif  // S21_MAP_TPP_