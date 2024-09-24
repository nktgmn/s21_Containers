#ifndef S21_VECTOR_TPP
#define S21_VECTOR_TPP

namespace s21 {

template <typename T>
vector<T>::vector() noexcept : data_(nullptr), size_(0), capacity_(0) {}

template <typename T>
vector<T>::vector(std::initializer_list<T> init)
    : data_(reinterpret_cast<T *>(new char[init.size() * sizeof(T)])),
      size_(init.size()),
      capacity_(init.size()) {
    size_t k = 0;
    try {
        for (const auto &elem : init) {
            new (data_ + k) T(elem);
            ++k;
        }

    } catch (...) {
        for (size_t i = 0; i < k; ++i) {
            (data_ + i)->~T();
        }
        delete[] reinterpret_cast<char *>(data_);
        throw;
    }
}

template <typename T>
vector<T>::vector(const vector &other)
    : data_(reinterpret_cast<T *>(new char[other.capacity() * sizeof(T)])),
      size_(other.size_),
      capacity_(other.capacity_) {
    initialize_memory(data_, capacity_);

    try {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    } catch (...) {
        for (size_t i = 0; i < capacity_; ++i) {
            (data_ + i)->~T();
        }
        delete[] reinterpret_cast<char *>(data_);
        throw;
    }
}

template <typename T>
vector<T>::vector(vector &&other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.size_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
}

template <typename T>
vector<T>::~vector() {
    for (size_t i = 0; i < capacity_; ++i) {
        (data_ + i)->~T();
    }
    delete[] reinterpret_cast<char *>(data_);
}

template <typename T>
vector<T> &vector<T>::operator=(const vector &other) {
    if (this != &other) {
        size_t new_cap =
            other.capacity_ > capacity_ ? other.capacity_ : capacity_;

        T *new_data = reinterpret_cast<T *>(new char[new_cap * sizeof(T)]);

        initialize_memory(new_data, new_cap);

        try {
            for (size_t i = 0; i < other.size_; ++i) {
                new_data[i] = other.data_[i];
            }
        } catch (...) {
            for (size_t i = 0; i < new_cap; ++i) {
                (new_data + i)->~T();
            }
            delete[] reinterpret_cast<char *>(new_data);
            throw;
        }

        for (size_t i = 0; i < capacity_; ++i) {
            (data_ + i)->~T();
        }
        delete[] reinterpret_cast<char *>(data_);

        data_ = new_data;
        capacity_ = new_cap;
        size_ = other.size_;
    }

    return *this;
}

template <typename T>
vector<T> &vector<T>::operator=(vector &&other) noexcept {
    if (this != &other) {
        for (size_t i = 0; i < capacity_; ++i) {
            (data_ + i)->~T();
        }
        delete[] reinterpret_cast<char *>(data_);

        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = other.data_;

        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
    }

    return *this;
}

template <typename T>
vector<T> &vector<T>::operator=(std::initializer_list<T> ilist) {
    size_t new_cap = ilist.size() > capacity_ ? ilist.size() : capacity_;

    T *new_data = reinterpret_cast<T *>(new char[new_cap * sizeof(T)]);

    initialize_memory(new_data, new_cap);

    size_t s = 0;
    try {
        for (const auto &elem : ilist) {
            new_data[s] = elem;
            ++s;
        }

    } catch (...) {
        for (size_t i = 0; i < new_cap; ++i) {
            (new_data + i)->~T();
        }
        delete[] reinterpret_cast<char *>(new_data);
        throw;
    }

    for (size_t i = 0; i < capacity_; ++i) {
        (data_ + i)->~T();
    }
    delete[] reinterpret_cast<char *>(data_);

    data_ = new_data;
    capacity_ = new_cap;
    size_ = ilist.size();

    return *this;
}

template <typename T>
T &vector<T>::at(size_t pos) {
    if (pos >= size_) {
        throw std::out_of_range("AtError: Index out of range");
    }

    return data_[pos];
}

template <typename T>
const T &vector<T>::at(size_t pos) const {
    if (pos >= size_) {
        throw std::out_of_range("AtError: Index out of range");
    }

    return data_[pos];
}

template <typename T>
T &vector<T>::operator[](size_t pos) {
    return data_[pos];
}

template <typename T>
const T &vector<T>::operator[](size_t pos) const {
    return data_[pos];
}

template <typename T>
T &vector<T>::front() {
    return *begin();
}

template <typename T>
const T &vector<T>::front() const {
    return *cbegin();
}

template <typename T>
T &vector<T>::back() {
    return *(--end());
}

template <typename T>
const T &vector<T>::back() const {
    return *(--cend());
}

template <typename T>
T *vector<T>::data() noexcept {
    return data_;
}

template <typename T>
const T *vector<T>::data() const noexcept {
    return data_;
}

template <typename T>
bool vector<T>::empty() const noexcept {
    return size_ == 0;
}

template <typename T>
size_t vector<T>::size() const noexcept {
    return size_;
}

template <typename T>
size_t vector<T>::max_size() const noexcept {
    return std::numeric_limits<size_t>::max() / sizeof(T);
}

template <typename T>
void vector<T>::reserve(size_t new_cap) {
    if (new_cap > max_size()) {
        throw std::length_error("ReserveError: New capacity is too large");
    } else if (new_cap > capacity_) {
        T *new_data = reinterpret_cast<T *>(new char[new_cap * sizeof(T)]);

        initialize_memory(new_data, new_cap);

        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }

        delete[] reinterpret_cast<char *>(data_);

        data_ = new_data;
        capacity_ = new_cap;
    }
}

template <typename T>
size_t vector<T>::capacity() const noexcept {
    return capacity_;
}

template <typename T>
void vector<T>::shrink_to_fit() {
    if (capacity_ > size_) {
        T *new_data = reinterpret_cast<T *>(new char[size_ * sizeof(T)]);

        for (size_t k = 0; k < size_; ++k) {
            new (new_data + k) T(std::move(data_[k]));
        }

        delete[] reinterpret_cast<char *>(data_);

        data_ = new_data;
        capacity_ = size_;
    }
}

template <typename T>
typename vector<T>::iter vector<T>::insert(c_iter pos, const T &value) {
    return insert(pos, 1, value);
}

template <typename T>
typename vector<T>::iter vector<T>::insert(c_iter pos, T &&value) {
    size_t diff = 0;
    c_iter counter_pos = cbegin();
    while (counter_pos != pos) {
        ++diff;
        ++counter_pos;
    }

    if (size_ + 1 <= capacity_) {
        for (size_t k = 0; k < size_ - diff; ++k) {
            *(data_ + size_ - k) = std::move(*(data_ + size_ - 1 - k));
        }

        *(data_ + diff) = std::move(value);

    } else {
        size_t new_cap = capacity_ > 0 ? capacity_ * 2 : 1;

        T *new_data = reinterpret_cast<T *>(new char[new_cap * sizeof(T)]);

        initialize_memory(new_data, new_cap);

        *(new_data + diff) = std::move(value);

        for (size_t k = 0; k < size_; ++k) {
            if (k < diff) {
                *(new_data + k) = std::move(*(data_ + k));
            } else {
                *(new_data + k + 1) = std::move(*(data_ + k));
            }
        }

        for (size_t k = 0; k < capacity_; ++k) {
            (data_ + k)->~T();
        }
        delete[] reinterpret_cast<char *>(data_);
        data_ = new_data;
        capacity_ = new_cap;
    }

    ++size_;

    return iter(data_ + diff);
}

template <typename T>
typename vector<T>::iter vector<T>::insert(c_iter pos, size_t count,
                                           const T &value) {
    size_t diff = 0;
    c_iter counter_pos = cbegin();
    while (counter_pos != pos) {
        ++diff;
        ++counter_pos;
    }

    vector<T> new_vec;
    for (size_t i = 0; i < count; ++i) {
        new_vec.push_back(value);
    }

    if (size_ + count <= capacity_) {
        for (size_t k = 0; k < size_ - diff; ++k) {
            *(data_ + size_ - 1 + count - k) =
                std::move(*(data_ + size_ - 1 - k));
        }

        for (size_t k = 0; k < count; ++k) {
            *(data_ + diff + k) = std::move(new_vec[k]);
        }

    } else {
        size_t new_cap = size_ + count;
        if (capacity_ == 0) {
            new_cap = count;
        } else if (size_ + count <= capacity_ * 2) {
            new_cap = capacity_ * 2;
        }

        T *new_data = reinterpret_cast<T *>(new char[new_cap * sizeof(T)]);

        initialize_memory(new_data, new_cap);

        for (size_t k = 0; k < count; ++k) {
            *(new_data + diff + k) = std::move(new_vec[k]);
        }

        for (size_t k = 0; k < size_; ++k) {
            if (k < diff) {
                *(new_data + k) = std::move(*(data_ + k));
            } else {
                *(new_data + k + count) = std::move(*(data_ + k));
            }
        }

        for (size_t k = 0; k < capacity_; ++k) {
            (data_ + k)->~T();
        }
        delete[] reinterpret_cast<char *>(data_);
        data_ = new_data;
        capacity_ = new_cap;
    }

    size_ += count;

    return iter(data_ + diff);
}

template <typename T>
typename vector<T>::iter vector<T>::erase(c_iter pos) {
    return iter(erase(pos, ++pos));
}

template <typename T>
typename vector<T>::iter vector<T>::erase(c_iter first, c_iter last) {
    iter it_return;
    iter it_last = begin() + (last - cbegin());

    if (first >= last) {
        it_return = it_last;
    } else {
        iter it_first = begin() + (first - cbegin());

        std::ptrdiff_t diff = last - first;

        it_return = iter(it_first);

        while ((it_first < it_last) && (it_last <= end())) {
            (*it_first).~T();
            ++it_first;
        }

        while (it_first < end()) {
            *(it_first - diff) = std::move(*it_first);
            ++it_first;
        }

        size_ -= diff;
    }

    return it_return;
}

template <typename T>
void vector<T>::push_back(const T &value) {
    if (size_ < capacity_) {
        new (data_ + size_) T(value);
    } else {
        size_t new_cap = capacity_ > 0 ? capacity_ * 2 : 1;

        T *new_data = reinterpret_cast<T *>(new char[new_cap * sizeof(T)]);

        initialize_memory(new_data, new_cap);

        try {
            *(new_data + size_) = value;
        } catch (...) {
            for (size_t i = 0; i < new_cap; ++i) {
                (new_data + i)->~T();
            }
            delete[] reinterpret_cast<char *>(new_data);
            throw;
        }

        for (size_t k = 0; k < size_; ++k) {
            *(new_data + k) = std::move(data_[k]);
        }

        delete[] reinterpret_cast<char *>(data_);

        data_ = new_data;
        capacity_ = new_cap;
    }

    ++size_;
}

template <typename T>
void vector<T>::push_back(T &&value) {
    if (size_ < capacity_) {
        new (data_ + size_) T(std::move(value));
    } else {
        size_t new_cap = capacity_ > 0 ? capacity_ * 2 : 1;

        T *new_data = reinterpret_cast<T *>(new char[new_cap * sizeof(T)]);

        initialize_memory(new_data, new_cap);

        *(new_data + size_) = std::move(value);

        for (size_t k = 0; k < size_; ++k) {
            *(new_data + k) = std::move(data_[k]);
        }

        delete[] reinterpret_cast<char *>(data_);

        data_ = new_data;
        capacity_ = new_cap;
    }

    ++size_;
}

template <typename T>
void vector<T>::clear() noexcept {
    size_ = 0;
}

template <typename T>
void vector<T>::pop_back() noexcept {
    --size_;
}

template <typename T>
void vector<T>::resize(size_t count) {
    resize(count, T());
}

template <typename T>
void vector<T>::resize(size_t count, const T &value) {
    std::cout << "starting resize " << count << std::endl;

    if (count > max_size()) {
        throw std::length_error("ResizeError: New capacity is too large");
    }

    vector<T> new_vec;
    for (size_t i = 0; count > size_ && i < count - size_; ++i) {
        new_vec.push_back(value);
    }

    if (count > capacity_) {
        size_t new_cap = count > capacity_ * 2 ? count : capacity_ * 2;

        T *new_data = reinterpret_cast<T *>(new char[new_cap * sizeof(T)]);

        initialize_memory(new_data, new_cap);

        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move(data_[i]);
        }

        delete[] reinterpret_cast<char *>(data_);

        data_ = new_data;
        capacity_ = new_cap;
    }

    size_t k = 0;
    while (size_ < count) {
        data_[size_] = std::move(new_vec[k]);
        ++size_;
        ++k;
        std::cout << k << std::endl;
    }

    if (size_ > count) {
        size_ = count;

    }
}

template <typename T>
void vector<T>::swap(vector &other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

template <typename T>
typename vector<T>::iter vector<T>::begin() noexcept {
    return iter(data_);
}

template <typename T>
typename vector<T>::iter vector<T>::end() noexcept {
    return iter(data_ + size_);
}

template <typename T>
typename vector<T>::c_iter vector<T>::cbegin() const noexcept {
    return c_iter(data_);
}

template <typename T>
typename vector<T>::c_iter vector<T>::cend() const noexcept {
    return c_iter(data_ + size_);
}

template <typename T>
bool operator==(const s21::vector<T> &left, const s21::vector<T> &right) {
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

    if ((left.size() != right.size()) ||
        (left.capacity() != right.capacity())) {
        res = false;
    }

    return res;
}

template <typename T>
bool operator!=(const vector<T> &left, const vector<T> &right) {
    return !(left == right);
}

template <typename T>
template <typename... Args>
typename vector<T>::iter vector<T>::insert_many(c_iter pos, Args &&...args) {
    std::ptrdiff_t index = pos - cbegin();

    reserve(size() + sizeof...(Args));

    c_iter insert_pos = cbegin() + index;
    (insert(insert_pos, std::forward<Args>(args)), ...);

    return begin() + index;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
    (push_back(std::forward<Args>(args)), ...);
}

template <typename T>
void vector<T>::initialize_memory(T *data, size_t sz) {
    size_t k = 0;
    try {
        for (; k < sz; ++k) {
            new (data + k) T();
        }
    } catch (...) {
        for (size_t i = 0; i < k; ++i) {
            (data + i)->~T();
        }
        delete[] reinterpret_cast<char *>(data);
        throw;
    }
}

}  // namespace s21

#endif  // S21_VECTOR_TPP
