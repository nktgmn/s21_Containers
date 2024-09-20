#ifndef S21_MULTISET_TPP_
#define S21_MULTISET_TPP_

#include "s21_multiset.h"

namespace s21 {

template <typename Key>
struct multiset<Key>::BaseNode {
    BaseNode* left;
    BaseNode* right;
    BaseNode* parent;
    int height;
    BaseNode();
};

template <typename Key>
struct multiset<Key>::Node : BaseNode {
    key data;
    Node(const key& value);
    Node(key&& value);
};

template <typename Key>
multiset<Key>::BaseNode::BaseNode() : left(nullptr), right(nullptr), parent(this), height(1) {}

template <typename Key>
multiset<Key>::Node::Node(const key& value) : BaseNode(), data(value) {}

template <typename Key>
multiset<Key>::Node::Node(key&& value) : BaseNode(), data(value) {}

template <typename Key>
multiset<Key>::multiset() noexcept : fake_node(new BaseNode()), leftmost(fake_node), size_(0) {}

template <typename Key>
multiset<Key>::multiset(const multiset& other) : fake_node(new BaseNode()), leftmost(fake_node), size_(0) {
    try {
        for (auto it = other.cbegin(); it != other.cend(); ++it) {
            insert(*it);
        }
    } catch (...) {
        delete_node(static_cast<Node*>(fake_node->left));
        delete fake_node;
        throw;
    }
}

template <typename Key>
multiset<Key>::multiset(std::initializer_list<key> init) : fake_node(new BaseNode()), leftmost(fake_node), size_(0) {
    try {
        for (const auto& elem : init) {
            insert(elem);
        }
    } catch (...) {
        delete_node(static_cast<Node*>(fake_node->left));
        delete fake_node;
        throw;
    }
}

template <typename Key>
multiset<Key>::multiset(multiset&& other) : fake_node(new BaseNode()), leftmost(fake_node), size_(other.size_) {
    if (other.size() > 0) {
        fake_node->left = other.fake_node->left;
        fake_node->left->parent = fake_node;
        leftmost = other.leftmost;

        other.fake_node->left = nullptr;
        other.leftmost = other.fake_node;
        other.size_ = 0;
    }
}

template <typename Key>
multiset<Key>::~multiset() noexcept {
    delete_node(static_cast<Node*>(fake_node->left));
    delete fake_node;
}

template <typename Key>
multiset<Key>& multiset<Key>::operator=(const multiset& other) {
    if (this == &other) {
        return *this;
    }

    if (other.size() == 0) {
        clear();
    } else {
        multiset<Key> new_set(other);
        clear();

        fake_node->left = new_set.fake_node->left;
        fake_node->left->parent = fake_node;
        leftmost = new_set.leftmost;
        size_ = new_set.size();

        new_set.fake_node->left = nullptr;
        new_set.leftmost = new_set.fake_node;
        new_set.size_ = 0;
    }

    return *this;
}

template <typename Key>
multiset<Key>& multiset<Key>::operator=(multiset&& other) noexcept {
    clear();

    if (this != &other) {
        if (other.size() > 0) {
            fake_node->left = other.fake_node->left;
            fake_node->left->parent = fake_node;
            leftmost = other.leftmost;
            size_ = other.size();
        }
    }

    other.fake_node->left = nullptr;
    other.leftmost = other.fake_node;
    other.size_ = 0;

    return *this;
}

template <typename Key>
multiset<Key>& multiset<Key>::operator=(std::initializer_list<key> ilist) {
    if (ilist.size() > 0) {
        multiset<Key> new_set(ilist);

        clear();

        fake_node->left = new_set.fake_node->left;
        fake_node->left->parent = fake_node;
        leftmost = new_set.leftmost;
        size_ = new_set.size();

        new_set.fake_node->left = nullptr;
        new_set.leftmost = new_set.fake_node;
        new_set.size_ = 0;

    } else {
        clear();
    }

    return *this;
}

template <typename Key>
typename multiset<Key>::iter multiset<Key>::begin() noexcept {
    return iter(leftmost);
}

template <typename Key>
typename multiset<Key>::iter multiset<Key>::end() noexcept {
    return iter(fake_node);
}

template <typename Key>
typename multiset<Key>::c_iter multiset<Key>::cbegin() const noexcept {
    return c_iter(leftmost);
}

template <typename Key>
typename multiset<Key>::c_iter multiset<Key>::cend() const noexcept {
    return c_iter(fake_node);
}

template <typename Key>
bool multiset<Key>::empty() const noexcept {
    return size() == 0;
}

template <typename Key>
size_t multiset<Key>::size() const noexcept {
    return size_;
}

template <typename Key>
size_t multiset<Key>::max_size() const noexcept {
    return std::numeric_limits<size_t>::max() / (sizeof(Node));
}

template <typename Key>
int multiset<Key>::get_height(BaseNode* node) {
    return node ? node->height : 0;
}

template <typename Key>
int multiset<Key>::get_balance_factor(BaseNode* node) {
    return node != nullptr ? get_height(node->left) - get_height(node->right) : 0;
}

template <typename Key>
void multiset<Key>::delete_node(Node* node) {
    if (node) {
        delete_node(static_cast<Node*>(node->left));
        delete_node(static_cast<Node*>(node->right));
        --size_;
        node->~Node();
        delete[] reinterpret_cast<char*>(node);
    }
}

template <typename Key>
typename multiset<Key>::BaseNode* multiset<Key>::rebalance_node(BaseNode* node) {
    node->height = std::max(get_height(node->left), get_height(node->right)) + 1;

    int balance_factor = get_balance_factor(node);

    if (balance_factor > 1 && get_balance_factor(node->left) >= 0) {
        node = rotate_right(node);
    }

    if (balance_factor < -1 && get_balance_factor(node->right) <= 0) {
        node = rotate_left(node);
    }

    if (balance_factor > 1 && get_balance_factor(node->left) < 0) {
        node->left = rotate_left(node->left);
        node = rotate_right(node);
    }

    if (balance_factor < -1 && get_balance_factor(node->right) > 0) {
        node->right = rotate_right(node->right);
        node = rotate_left(node);
    }

    return node;
}

template <typename Key>
typename multiset<Key>::BaseNode* multiset<Key>::min_value_node(BaseNode* node) {
    BaseNode* current = node;

    while (current->left != nullptr) {
        current = current->left;
    }

    return current;
}

template <typename Key>
typename multiset<Key>::BaseNode* multiset<Key>::rotate_right(BaseNode* node) {
    BaseNode* new_root = node->left;
    BaseNode* right = new_root->right;

    new_root->right = node;
    node->left = right;

    new_root->parent = node->parent;

    if (node->parent->left == node) {
        node->parent->left = new_root;
    }

    if (node->parent->right == node) {
        node->parent->right = new_root;
    }

    node->parent = new_root;
    if (right) {
        right->parent = node;
    }

    node->height = 1 + std::max(get_height(node->left), get_height(node->right));
    new_root->height = 1 + std::max(get_height(new_root->left), get_height(new_root->right));

    return new_root;
}

template <typename Key>
typename multiset<Key>::BaseNode* multiset<Key>::rotate_left(BaseNode* node) {
    BaseNode* new_root = node->right;
    BaseNode* left = new_root->left;

    new_root->left = node;

    node->right = left;

    new_root->parent = node->parent;

    if (node->parent->left == node) {
        node->parent->left = new_root;
    }

    if (node->parent->right == node) {
        node->parent->right = new_root;
    }

    node->parent = new_root;

    if (left) {
        left->parent = node;
    }

    node->height = 1 + std::max(get_height(node->left), get_height(node->right));
    new_root->height = 1 + std::max(get_height(new_root->left), get_height(new_root->right));

    return new_root;
}

template <typename Key>
std::pair<typename multiset<Key>::BaseNode*, bool> multiset<Key>::insert_private(BaseNode* node, const key& value) {
    bool inserted = false;

    if (node == nullptr) {
        Node* new_node = reinterpret_cast<Node*>(new char[sizeof(Node)]);

        try {
            new (new_node) Node(value);
        } catch (...) {
            delete[] reinterpret_cast<char*>(new_node);
            throw;
        }

        node = new_node;

        ++size_;
        if (leftmost != fake_node && value < static_cast<Node*>(leftmost)->data) {
            leftmost = node;
        }
        return {node, true};
    } else if (value >= static_cast<Node*>(node)->data) {
        auto insert_res = insert_private(node->right, value);
        node->right = insert_res.first;
        inserted = insert_res.second;
        node->right->parent = node;
    } else {
        auto insert_res = insert_private(node->left, value);
        node->left = insert_res.first;
        inserted = insert_res.second;
        node->left->parent = node;
    }

    node = rebalance_node(node);

    return {node, inserted};
}

template <typename Key>
std::pair<typename multiset<Key>::BaseNode*, bool> multiset<Key>::insert_private(BaseNode* node, key&& value) {
    bool inserted = false;

    if (node == nullptr) {
        Node* new_node = reinterpret_cast<Node*>(new char[sizeof(Node)]);

        try {
            new (new_node) Node(std::move(value));
        } catch (...) {
            delete[] reinterpret_cast<char*>(new_node);
            throw;
        }

        node = new_node;
        ++size_;
        if (leftmost != fake_node && value < static_cast<Node*>(leftmost)->data) {
            leftmost = node;
        }
        return {node, true};
    } else if (value >= static_cast<Node*>(node)->data) {
        auto insert_res = insert_private(node->right, value);
        node->right = insert_res.first;
        inserted = insert_res.second;
        node->right->parent = node;
    } else {
        auto insert_res = insert_private(node->left, value);
        node->left = insert_res.first;
        inserted = insert_res.second;
        node->left->parent = node;
    }

    node = rebalance_node(node);

    return {node, inserted};
}

template <typename Key>
typename multiset<Key>::BaseNode* multiset<Key>::merge_insert(BaseNode* node, BaseNode* src_node, multiset& source) {
    if (node == nullptr) {
        source.erase_private(iter(src_node), false);

        node = src_node;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1;

        ++size_;
        if (leftmost != fake_node && static_cast<Node*>(src_node)->data < static_cast<Node*>(leftmost)->data) {
            leftmost = node;
        }
        return node;
    } else if (static_cast<Node*>(src_node)->data >= static_cast<Node*>(node)->data) {
        BaseNode* insert_res = merge_insert(node->right, src_node, source);
        node->right = insert_res;
        node->right->parent = node;
    } else {
        BaseNode* insert_res = merge_insert(node->left, src_node, source);
        node->left = insert_res;
        node->left->parent = node;
    }

    node = rebalance_node(node);

    return node;
}

template <typename Key>
void multiset<Key>::clear() noexcept {
    delete_node(static_cast<Node*>(fake_node->left));
    leftmost = fake_node;
    fake_node->left = nullptr;
}

template <typename Key>
std::pair<typename multiset<Key>::iter, bool> multiset<Key>::insert(const key& value) {
    auto insert_res = insert_private(fake_node->left, value);
    if (!fake_node->left) {
        fake_node->left = insert_res.first;
        fake_node->left->parent = fake_node;
        leftmost = fake_node->left;
    }

    return {iter(insert_res.first), insert_res.second};
}

template <typename Key>
std::pair<typename multiset<Key>::iter, bool> multiset<Key>::insert(key&& value) {
    auto insert_res = insert_private(fake_node->left, std::move(value));
    if (!fake_node->left) {
        fake_node->left = insert_res.first;
        fake_node->left->parent = fake_node;
        leftmost = fake_node->left;
    }

    return {iter(insert_res.first), insert_res.second};
}

template <typename Key>
typename multiset<Key>::iter multiset<Key>::erase_private(iter pos, bool del) {
    auto next = pos;
    ++next;

    Node* node = static_cast<Node*>(pos.node);
    BaseNode* tmp;

    if (node->left == nullptr || node->right == nullptr) {
        tmp = node->left ? node->left : node->right;

        if (node == leftmost) {
            leftmost = next.node;
        }

        if (tmp != nullptr) {
            tmp->parent = node->parent;
        }

        if (node->parent->left == node) {
            node->parent->left = tmp;
        }

        if (node->parent->right == node) {
            node->parent->right = tmp;
        }

        if (tmp == nullptr) {
            tmp = node->parent;
        }

    } else {
        tmp = min_value_node(node->right);
        BaseNode* reb_node = tmp->parent;

        if (tmp->right != nullptr && tmp->parent != node) {
            tmp->right->parent = tmp->parent;
            tmp->parent->left = tmp->right;
        } else if (tmp->parent != node) {
            tmp->parent->left = tmp->right;
        }

        tmp->parent = node->parent;

        if (node->parent->left == node) {
            node->parent->left = tmp;
        }

        if (node->parent->right == node) {
            node->parent->right = tmp;
        }

        tmp->left = node->left;
        node->left->parent = tmp;
        if (node->right != tmp) {
            tmp->right = node->right;
            node->right->parent = tmp;
        }

        while (reb_node != tmp && reb_node != node) {
            reb_node = rebalance_node(reb_node);
            reb_node = reb_node->parent;
        }
    }

    --size_;

    if (del == true) {
        node->~Node();
        delete[] reinterpret_cast<char*>(node);
    }

    while (tmp != fake_node) {
        tmp = rebalance_node(tmp);
        tmp = tmp->parent;
    }

    return iter(next);
}

template <typename Key>
typename multiset<Key>::iter multiset<Key>::erase(iter pos) {
    return erase_private(pos, true);
}

template <typename Key>
typename multiset<Key>::iter multiset<Key>::erase(c_iter pos) {
    return erase(iter(pos.node));
}

template <typename Key>
typename multiset<Key>::iter multiset<Key>::erase(c_iter first, c_iter last) {
    iter it_first(first.node);
    iter it_last(last.node);

    while (it_first != it_last) {
        it_first = erase(it_first);
    }

    return it_first;
}

template <typename Key>
size_t multiset<Key>::erase(const Key& key) {
    size_t res = 0;
    auto it = begin();

    while (it != end()) {
        if (*it == key) {
            it = erase(it);
            ++res;
        } else {
            ++it;
        }
    }

    return res;
}

template <typename Key>
void multiset<Key>::swap(multiset& other) noexcept {
    BaseNode* fake_node_tmp = other.fake_node;
    BaseNode* leftmost_tmp = other.leftmost;
    size_t size_tmp = other.size_;

    other.fake_node = fake_node;
    other.leftmost = leftmost;
    other.size_ = size_;

    fake_node = fake_node_tmp;
    leftmost = leftmost_tmp;
    size_ = size_tmp;
}

template <typename Key>
void multiset<Key>::merge(multiset& source) {
    if (this == &source) {
        return;
    }

    auto it = source.begin();
    auto next = source.begin();

    while (it != source.end()) {
        ++next;
        BaseNode* insert_res = merge_insert(fake_node->left, it.node, source);

        if (fake_node->left == nullptr) {
            fake_node->left = insert_res;
            fake_node->left->parent = fake_node;
            leftmost = fake_node->left;
        }

        it = next;
    }
}

template <typename Key>
size_t multiset<Key>::count(const Key& key) const {
    size_t res = 0;
    for (auto it = cbegin(); it != cend(); ++it) {
        if (*it == key) {
            res += 1;
        }
    }
    return res;
}

template <typename Key>
typename multiset<Key>::iter multiset<Key>::find(const Key& key) {
    auto it = begin();
    for (; it != end(); ++it) {
        if (*it == key) {
            return it;
        }
    }
    return it;
}

template <typename Key>
typename multiset<Key>::c_iter multiset<Key>::find(const Key& key) const {
    auto it = cbegin();
    for (; it != cend(); ++it) {
        if (*it == key) {
            return it;
        }
    }
    return it;
}

template <typename Key>
bool multiset<Key>::contains(const Key& key) const {
    auto it = cbegin();
    for (; it != cend(); ++it) {
        if (*it == key) {
            return true;
        }
    }
    return false;
}

template <typename Key>
std::pair<typename multiset<Key>::iter, typename multiset<Key>::iter> multiset<Key>::equal_range(const Key& key) {
    iter lower = lower_bound(key);
    iter upper = upper_bound(key);
    return {lower, upper};
}

template <typename Key>
std::pair<typename multiset<Key>::c_iter, typename multiset<Key>::c_iter> multiset<Key>::equal_range(const Key& key) const {
    c_iter lower = lower_bound(key);
    c_iter upper = upper_bound(key);
    return {lower, upper};
}

template <typename Key>
typename multiset<Key>::iter multiset<Key>::lower_bound(const Key& key) {
    auto it = begin();

    while ((*it < key) && (it != end())) {
        ++it;
    }

    return it;
}

template <typename Key>
typename multiset<Key>::c_iter multiset<Key>::lower_bound(const Key& key) const {
    auto it = cbegin();

    while ((*it < key) && (it != cend())) {
        ++it;
    }

    return it;
}

template <typename Key>
typename multiset<Key>::iter multiset<Key>::upper_bound(const Key& key) {
    auto it = begin();

    while ((*it <= key) && (it != end())) {
        ++it;
    }

    return it;
}

template <typename Key>
typename multiset<Key>::c_iter multiset<Key>::upper_bound(const Key& key) const {
    auto it = cbegin();

    while ((*it <= key) && (it != cend())) {
        ++it;
    }

    return it;
}

template <typename Key>
template <typename... Args>
std::vector<std::pair<typename multiset<Key>::iter, bool>> multiset<Key>::insert_many(Args&&... args) {
    std::vector<std::pair<iter, bool>> res;
    size_t args_count = sizeof...(Args);
    res.reserve(args_count);

    (res.push_back(insert(std::forward<Args>(args))), ...);

    return res;
}

}  // namespace s21

#endif  // S21_MULTISET_TPP_