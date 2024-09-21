#ifndef S21_LIST_TPP
#define S21_LIST_TPP

#include "../iterators/s21_list_iterators.tpp"

namespace s21 {

template <typename T>
list<T>::list() noexcept : fake_node({&fake_node, &fake_node}), size_(0) {}

template <typename T>
list<T>::list(const list& other)
    : fake_node({&fake_node, &fake_node}), size_(0) {
    try {
        for (ListConstIterator it_other = other.cbegin();
             it_other != other.cend(); ++it_other) {
            push_back(*it_other);
        }
    } catch (...) {
        clear();
        throw;
    }
}

template <typename T>
list<T>::list(std::initializer_list<T> init)
    : fake_node({&fake_node, &fake_node}), size_(0) {
    try {
        for (const auto& elem : init) {
            push_back(elem);
        }

    } catch (...) {
        clear();
        throw;
    }
}

template <typename T>
list<T>::list(list&& other) noexcept
    : fake_node({&fake_node, &fake_node}), size_(other.size()) {
    if (size() > 0) {
        fake_node.next = other.begin().ptr_;
        other.begin().ptr_->prev = &fake_node;

        fake_node.prev = (--other.end()).ptr_;
        (--other.end()).ptr_->next = &fake_node;
    }

    other.fake_node.next = &(other.fake_node);
    other.fake_node.prev = &(other.fake_node);
    other.size_ = 0;
}

template <typename T>
list<T>::~list() noexcept {
    clear();
}

template <typename T>
list<T>& list<T>::operator=(const list& other) {
    if (this != &other) {
        if (other.size() > 0) {
            s21::list<T> new_list(other);

            clear();

            size_ = other.size();

            fake_node.next = new_list.begin().ptr_;
            new_list.begin().ptr_->prev = static_cast<Node*>(&fake_node);

            fake_node.prev = (--new_list.end()).ptr_;
            (--new_list.end()).ptr_->next = static_cast<Node*>(&fake_node);

            new_list.fake_node.next = &(new_list.fake_node);
            new_list.fake_node.prev = &(new_list.fake_node);
            new_list.size_ = 0;
        } else {
            clear();
        }
    }

    return *this;
}

template <typename T>
list<T>& list<T>::operator=(list&& other) noexcept {
    if (this != &other) {
        clear();

        if (other.size() > 0) {
            size_ = other.size();

            fake_node.next = other.begin().ptr_;
            other.begin().ptr_->prev = &fake_node;

            fake_node.prev = (--other.end()).ptr_;
            (--other.end()).ptr_->next = &fake_node;

            other.fake_node.next = &(other.fake_node);
            other.fake_node.prev = &(other.fake_node);
            other.size_ = 0;
        }
    }

    return *this;
}

template <typename T>
list<T>& list<T>::operator=(std::initializer_list<T> ilist) {
    if (ilist.size() > 0) {
        s21::list<T> new_list(ilist);

        clear();

        size_ = ilist.size();

        fake_node.next = new_list.begin().ptr_;
        new_list.begin().ptr_->prev = static_cast<Node*>(&fake_node);

        fake_node.prev = (--new_list.end()).ptr_;
        (--new_list.end()).ptr_->next = static_cast<Node*>(&fake_node);

        new_list.fake_node.next = &(new_list.fake_node);
        new_list.fake_node.prev = &(new_list.fake_node);
        new_list.size_ = 0;
    } else {
        clear();
    }

    return *this;
}

template <typename T>
T& list<T>::front() {
    return *begin();
}

template <typename T>
const T& list<T>::front() const {
    return *cbegin();
}

template <typename T>
T& list<T>::back() {
    return *(--end());
}

template <typename T>
const T& list<T>::back() const {
    return *(--cend());
}

template <typename T>
typename list<T>::ListIterator list<T>::end() {
    return ListIterator(static_cast<Node*>(&fake_node));
}

template <typename T>
typename list<T>::ListIterator list<T>::begin() {
    return ListIterator(static_cast<Node*>(fake_node.next));
}

template <typename T>
typename list<T>::ListConstIterator list<T>::cend() const {
    return ListConstIterator(static_cast<const Node*>(&fake_node));
}

template <typename T>
typename list<T>::ListConstIterator list<T>::cbegin() const {
    return ListConstIterator(static_cast<const Node*>(fake_node.next));
}

template <typename T>
bool list<T>::empty() const noexcept {
    return size_ == 0;
}

template <typename T>
size_t list<T>::size() const noexcept {
    return size_;
}

template <typename T>
size_t list<T>::max_size() const noexcept {
    return std::numeric_limits<size_t>::max() / (sizeof(Node));
}

template <typename T>
void list<T>::clear() noexcept {
    Node* node = static_cast<Node*>(fake_node.next);
    Node* next = nullptr;
    for (size_t i = 0; i < size(); ++i) {
        next = static_cast<Node*>(node->next);
        delete node;
        node = next;
    }
    fake_node.prev = &fake_node;
    fake_node.next = &fake_node;
    size_ = 0;
}

template <typename T>
typename list<T>::ListIterator list<T>::insert(ListConstIterator pos,
                                               const T& value) {
    Node* new_node = new Node();

    new_node->value = value;
    new_node->next = const_cast<Node*>(pos.ptr_);
    new_node->prev = pos.ptr_->prev;

    const_cast<Node*>(pos.ptr_)->prev = new_node;
    new_node->prev->next = new_node;

    ListIterator it = ListIterator(new_node);

    ++size_;

    return it;
}

template <typename T>
typename list<T>::ListIterator list<T>::insert(ListConstIterator pos,
                                               size_t count, const T& value) {
    list<T> new_list;

    try {
        for (size_t k = 0; k < count; ++k) {
            new_list.push_back(value);
        }
    } catch (...) {
        new_list.clear();
        throw;
    }

    ListIterator it((--pos).ptr_);

    splice(++pos, new_list);

    return ++it;
}

template <typename T>
typename list<T>::ListIterator list<T>::insert(ListConstIterator pos,
                                               T&& value) {
    Node* new_node = new Node();

    new_node->value = std::move(value);
    new_node->next = const_cast<Node*>(pos.ptr_);
    new_node->prev = pos.ptr_->prev;

    const_cast<Node*>(pos.ptr_)->prev = new_node;
    new_node->prev->next = new_node;

    ListIterator it = ListIterator(new_node);

    ++size_;

    return it;
}

template <typename T>
typename list<T>::ListIterator list<T>::erase(ListConstIterator pos) {
    ListIterator it(static_cast<Node*>(pos.ptr_->next));

    it.ptr_->prev = pos.ptr_->prev;
    pos.ptr_->prev->next = it.ptr_;

    delete pos.ptr_;

    --size_;

    return it;
}

template <typename T>
typename list<T>::ListIterator list<T>::erase(ListConstIterator first,
                                              ListConstIterator last) {
    while (first != last) {
        first = erase(first);
    }

    return ListIterator(first.ptr_);
}

template <typename T>
void list<T>::push_back(const T& value) {
    Node* new_node = new Node();

    try {
        new_node->value = value;
    } catch (...) {
        delete new_node;
    }

    new_node->next = &fake_node;
    new_node->prev = fake_node.prev;
    fake_node.prev->next = new_node;

    fake_node.prev = new_node;
    if (size_ == 0) {
        fake_node.next = new_node;
    }

    ++size_;
}

template <typename T>
void list<T>::push_back(T&& value) {
    Node* new_node = new Node();

    new_node->value = std::move(value);

    new_node->next = &fake_node;
    new_node->prev = fake_node.prev;
    fake_node.prev->next = new_node;

    fake_node.prev = new_node;
    if (size_ == 0) {
        fake_node.next = new_node;
    }

    ++size_;
}

template <typename T>
void list<T>::pop_back() {
    Node* last = static_cast<Node*>(fake_node.prev);

    last->prev->next = &fake_node;

    fake_node.prev = last->prev;

    delete last;

    --size_;
}

template <typename T>
void list<T>::push_front(const T& value) {
    Node* new_node = new Node();

    try {
        new_node->value = value;
    } catch (...) {
        delete new_node;
    }

    new_node->next = fake_node.next;
    new_node->prev = &fake_node;

    fake_node.next = new_node;

    new_node->next->prev = new_node;

    ++size_;
}

template <typename T>
void list<T>::push_front(T&& value) {
    Node* new_node = new Node();

    new_node->value = std::move(value);

    new_node->next = fake_node.next;
    new_node->prev = &fake_node;

    fake_node.next = new_node;

    new_node->next->prev = new_node;

    ++size_;
}

template <typename T>
void list<T>::pop_front() {
    Node* first = static_cast<Node*>(fake_node.next);

    fake_node.next = first->next;

    delete first;

    --size_;
}

template <typename T>
void list<T>::resize(size_t count, const T& value) {
    if (count == 0) {
        clear();
    } else if (count > size_) {
        s21::list<T> new_list;

        try {
            for (size_t i = 0; i < count - size_; ++i) {
                new_list.push_back(value);
            }
        } catch (...) {
            new_list.clear();
            throw;
        }

        fake_node.prev->next = new_list.begin().ptr_;
        new_list.begin().ptr_->prev = static_cast<Node*>(fake_node.prev);

        (--new_list.end()).ptr_->next = &fake_node;
        fake_node.prev = (--new_list.end()).ptr_;

        new_list.fake_node.next = &new_list.fake_node;
        new_list.fake_node.prev = &new_list.fake_node;
        new_list.size_ = 0;

        size_ = count;

    } else if (count < size_) {
        size_t k = 0;
        ListIterator last;
        ListIterator it = begin();

        while (it != end()) {
            if (k == count - 1) {
                last = it;
                ++it;
            } else if (k >= count) {
                it = erase(it);
            } else {
                ++it;
            }
            ++k;
        }

        fake_node.prev = last.ptr_;
        last.ptr_->next = &fake_node;

        size_ = count;
    }
}

template <typename T>
void list<T>::resize(size_t count) {
    resize(count, T());
}

template <typename T>
void list<T>::swap(list& other) noexcept {
    Node* beg = begin().ptr_;
    Node* last = (--end()).ptr_;
    Node* beg_other = other.begin().ptr_;
    Node* last_other = (--other.end()).ptr_;
    size_t other_sz = other.size();

    if (size() > 0) {
        beg->prev = &(other.fake_node);
        last->next = &(other.fake_node);
        other.fake_node.next = beg;
        other.fake_node.prev = last;
    } else {
        other.fake_node.next = &(other.fake_node);
        other.fake_node.prev = &(other.fake_node);
    }

    if (other.size() > 0) {
        beg_other->prev = &fake_node;
        last_other->next = &fake_node;
        fake_node.next = beg_other;
        fake_node.prev = last_other;
    } else {
        fake_node.next = &fake_node;
        fake_node.prev = &fake_node;
    }

    other.size_ = size();
    size_ = other_sz;
}

template <typename T>
void list<T>::merge(list& other) {
    if (this != &other) {
        ListConstIterator it_self = cbegin();
        while ((other.size() > 0) && (it_self != cend())) {
            ListConstIterator it_other = other.cbegin();

            while ((*it_self > *it_other) && (it_other != other.cend())) {
                ++it_other;
            }

            if (it_other != other.cbegin()) {
                splice(it_self, other, other.cbegin(), it_other);
            }

            ++it_self;
        }

        if (other.size() > 0) {
            splice(cend(), other);
        }
    }
}

template <typename T>
void list<T>::merge(list&& other) {
    if (this != &other) {
        ListConstIterator it_self = cbegin();
        while ((other.size() > 0) && (it_self != cend())) {
            ListConstIterator it_other = other.cbegin();

            while ((*it_self > *it_other) && (it_other != other.cend())) {
                ++it_other;
            }

            if (it_other != other.cbegin()) {
                splice(it_self, other, other.cbegin(), it_other);
            }

            ++it_self;
        }

        if (other.size() > 0) {
            splice(cend(), other);
        }
    }
}

template <typename T>
void list<T>::splice(ListConstIterator pos, list& other) {
    if (other.size() > 0) {
        ListIterator it = begin();
        ListIterator end = other.end();

        for (; it.ptr_ != pos.ptr_; ++it) {
        }

        ListIterator it_pos(it);

        --it;

        it.ptr_->next = other.begin().ptr_;
        other.begin().ptr_->prev = it.ptr_;

        --end;

        end.ptr_->next = it_pos.ptr_;
        it_pos.ptr_->prev = end.ptr_;

        size_ = size_ + other.size_;

        other.fake_node.next = &other.fake_node;
        other.fake_node.prev = &other.fake_node;
        other.size_ = 0;
    }
}

template <typename T>
void list<T>::splice(ListConstIterator pos, list&& other) {
    if (other.size() > 0) {
        ListIterator it = begin();
        ListIterator end = other.end();

        for (; it.ptr_ != pos.ptr_; ++it) {
        }

        ListIterator it_pos(it);

        --it;

        it.ptr_->next = other.begin().ptr_;
        other.begin().ptr_->prev = it.ptr_;

        --end;

        end.ptr_->next = it_pos.ptr_;
        it_pos.ptr_->prev = end.ptr_;

        size_ = size_ + other.size_;

        other.fake_node.next = &other.fake_node;
        other.fake_node.prev = &other.fake_node;
        other.size_ = 0;
    }
}

template <typename T>
void list<T>::splice(ListConstIterator pos, list& other, ListConstIterator it) {
    splice(pos, other, it, ++it);
}

template <typename T>
void list<T>::splice(ListConstIterator pos, list&& other,
                     ListConstIterator it) {
    splice(pos, other, it, ++it);
}

template <typename T>
void list<T>::splice(ListConstIterator pos, list& other,
                     ListConstIterator first, ListConstIterator last) {
    if (pos != last) {
        size_t k = 0;

        if (this != &other) {
            ListConstIterator frst(first);
            while (frst != last) {
                ++frst;
                ++k;
            }
        }

        ListIterator it = begin();
        for (; it.ptr_ != pos.ptr_; ++it) {
        }
        ListIterator before_pos(--it);
        ListIterator at_pos(++it);

        it = other.begin();
        for (; it.ptr_ != first.ptr_; ++it) {
        }
        ListIterator before_first(--it);
        ListIterator at_first(++it);

        it = other.begin();
        for (; it.ptr_ != last.ptr_; ++it) {
        }
        ListIterator before_last(--it);
        ListIterator at_last(++it);

        before_pos.ptr_->next = at_first.ptr_;
        at_first.ptr_->prev = before_pos.ptr_;

        before_last.ptr_->next = at_pos.ptr_;
        at_pos.ptr_->prev = before_last.ptr_;

        before_first.ptr_->next = at_last.ptr_;
        at_last.ptr_->prev = before_first.ptr_;

        if (this != &other) {
            size_ += k;
            other.size_ -= k;
        }
    }
}

template <typename T>
void list<T>::splice(ListConstIterator pos, list&& other,
                     ListConstIterator first, ListConstIterator last) {
    if (pos != last) {
        size_t k = 0;

        if (this != &other) {
            while (first != last) {
                ++first;
                ++k;
            }

            for (size_t i = 0; i < k; ++i) {
                --first;
            }
        }

        ListIterator it = begin();
        for (; it.ptr_ != pos.ptr_; ++it) {
        }
        ListIterator before_pos(--it);
        ListIterator at_pos(++it);

        it = other.begin();
        for (; it.ptr_ != first.ptr_; ++it) {
        }
        ListIterator before_first(--it);
        ListIterator at_first(++it);

        it = other.begin();
        for (; it.ptr_ != last.ptr_; ++it) {
        }
        ListIterator before_last(--it);
        ListIterator at_last(++it);

        before_pos.ptr_->next = at_first.ptr_;
        at_first.ptr_->prev = before_pos.ptr_;

        before_last.ptr_->next = at_pos.ptr_;
        at_pos.ptr_->prev = before_last.ptr_;

        before_first.ptr_->next = at_last.ptr_;
        at_last.ptr_->prev = before_first.ptr_;

        if (this != &other) {
            size_ += k;
            other.size_ -= k;
        }
    }
}

template <typename T>
void list<T>::remove(const T& value) {
    for (ListIterator it = begin(); it != end(); ++it) {
        if (*it == value) {
            it = erase(it);
            --it;
        }
    }
}

template <typename T>
void list<T>::reverse() {
    Node* node = static_cast<Node*>(fake_node.prev);
    for (size_t i = 0; i < size(); ++i) {
        Node* next = static_cast<Node*>(node->prev);
        node->prev = node->next;
        node->next = next;

        node = next;
    }

    if (!empty()) {
        BaseNode* next = fake_node.next;
        fake_node.next = fake_node.prev;
        fake_node.prev = next;
    }
}

template <typename T>
void list<T>::unique() {
    ListConstIterator it = ++cbegin();

    while (it != cend()) {
        const T& prev_value = *(--it);
        ++it;

        if (*it == prev_value) {
            it = erase(it);
        } else {
            ++it;
        }
    }
}

template <typename T>
void list<T>::sort() {
    size_t new_size = 0;

    ListIterator other_begin = begin();
    for (; new_size < size() / 2; ++new_size) {
        ++other_begin;
    }

    ListIterator self_end(other_begin);
    --self_end;

    list<T> other;
    other.size_ = size_ - new_size;
    if (other.size() > 0) {
        other_begin.ptr_->prev = &other.fake_node;
        other.fake_node.next = other_begin.ptr_;
        (--end()).ptr_->next = &other.fake_node;
        other.fake_node.prev = (--end()).ptr_;
    }

    self_end.ptr_->next = &fake_node;
    fake_node.prev = self_end.ptr_;
    size_ = new_size;

    if (size() > 1) {
        this->sort();
    }

    if (other.size() > 1) {
        other.sort();
    }

    merge(other);
}

template <typename T>
template <typename... Args>
typename list<T>::ListIterator list<T>::insert_many(ListConstIterator pos,
                                                    Args&&... args) {
    (insert(pos, std::forward<Args>(args)), ...);
    return ListIterator(pos.ptr_);
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args&&... args) {
    (push_back(std::forward<Args>(args)), ...);
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args&&... args) {
    (push_front(std::forward<Args>(args)), ...);
}

template <typename T>
bool operator==(const list<T>& left, const list<T>& right) {
    bool res = true;

    auto left_it = left.cbegin();
    auto right_it = right.cbegin();

    while (left_it != left.cend()) {
        if (*left_it != *right_it) {
            res = false;
            break;
        }
        ++left_it;
        ++right_it;
    }

    if (right_it != right.cend()) {
        res = false;
    }

    return res;
}

template <typename T>
bool operator!=(const list<T>& left, const list<T>& right) {
    return !(left == right);
}

}  // namespace s21

#endif  // S21_LIST_TPP
