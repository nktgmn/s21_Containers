#ifndef S21_VECTOR_TPP
#define S21_VECTOR_TPP

#include "s21_vector.h"

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
    : data_(reinterpret_cast<T *>(new char[other.size() * sizeof(T)])),
      size_(other.size_),
      capacity_(other.capacity_) {
    size_t k = 0;

    try {
        for (; k < size_; ++k) {
            new (data_ + k) T(other.data_[k]);
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
vector<T>::vector(vector &&other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.size_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
}

template <typename T>
vector<T>::~vector() {
    clear();
    delete[] reinterpret_cast<char *>(data_);
}

template <typename T>
vector<T> &vector<T>::operator=(const vector &other) {
    if (this != &other) {
        size_t k = 0;

        size_t new_cap = other.capacity_ > capacity_ ? other.capacity_ : capacity_;

        T *new_data = reinterpret_cast<T *>(new char[new_cap * sizeof(T)]);

        try {
            for (; k < other.size_; ++k) {
                new (new_data + k) T(other.data_[k]);
            }

        } catch (...) {
            for (size_t i = 0; i < k; ++i) {
                (new_data + i)->~T();
            }
            delete[] reinterpret_cast<char *>(new_data);
            throw;
        }

        clear();
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
        clear();
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
    size_t k = 0;

    size_t new_cap = ilist.size() > capacity_ ? ilist.size() : capacity_;

    T *new_data = reinterpret_cast<T *>(new char[new_cap * sizeof(T)]);

    try {
        for (const auto &elem : ilist) {
            new (new_data + k) T(elem);
            ++k;
        }

    } catch (...) {
        for (size_t i = 0; i < k; ++i) {
            (new_data + i)->~T();
        }
        delete[] reinterpret_cast<char *>(new_data);
        throw;
    }

    clear();
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
    if (empty()) {
        throw std::out_of_range("FrontError: vector is empty");
    }
    return data_[0];
}

template <typename T>
const T &vector<T>::front() const {
    if (empty()) {
        throw std::out_of_range("FrontError: vector is empty");
    }
    return data_[0];
}

template <typename T>
T &vector<T>::back() {
    if (empty()) {
        throw std::out_of_range("BackError: vector is empty");
    }
    return data_[size_ - 1];
}

template <typename T>
const T &vector<T>::back() const {
    if (empty()) {
        throw std::out_of_range("BackError: vector is empty");
    }
    return data_[size_ - 1];
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
        throw std::length_error("ReserveError: Large size for a new capacity");
    } else if (new_cap > capacity_) {
        T *new_data = reinterpret_cast<T *>(new char[new_cap * sizeof(T)]);

        size_t k = 0;

        for (; k < size_; ++k) {
            new (new_data + k) T(std::move(data_[k]));
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
typename vector<T>::Iterator vector<T>::insert(vector<T>::ConstIterator pos,
                                               const T &value) {
    return insert(pos, 1, value);
}

template <typename T>
typename vector<T>::Iterator vector<T>::insert(vector<T>::ConstIterator pos,
                                               T &&value) {
    size_t diff = 0;
    ConstIterator counter_pos = cbegin();
    while (counter_pos != pos) {
        ++diff;
        ++counter_pos;
    }

    if (size_ < capacity_) {
        for (size_t k = size_; k > diff; --k) {
            *(data_ + k) = std::move(*(data_ + k - 1));
        }

        *(data_ + diff) = std::move(value);

        ++size_;

    } else {
        size_t new_cap = capacity_ > 0 ? capacity_ * 2 : 1;

        T *old_data = data_;

        try {
            data_ = reinterpret_cast<T *>(new char[new_cap * sizeof(T)]);
        } catch (...) {
            data_ = old_data;
            throw;
        }

        *(data_ + diff) = std::move(value);

        for (size_t k = 0; k < size_ + 1; ++k) {
            if (k < diff) {
                *(data_ + k) = std::move(*(old_data + k));
            } else if (k > diff) {
                *(data_ + k) = std::move(*(old_data + k - 1));
            }
        }

        for (size_t k = 0; k < size_; ++k) {
            old_data[k].~T();
        }
        delete[] reinterpret_cast<char *>(old_data);
        capacity_ = new_cap;
        ++size_;
    }

    return Iterator(data_ + diff);
}

template <typename T>
typename vector<T>::Iterator vector<T>::insert(vector<T>::ConstIterator pos,
                                               size_t count, const T &value) {
    size_t diff = 0;
    ConstIterator counter_pos = cbegin();
    while (counter_pos != pos) {
        ++diff;
        ++counter_pos;
    }

    if (size_ + count <= capacity_) {
        for (size_t k = size_; k > diff; --k) {
            *(data_ + k) = std::move(*(data_ + k - 1));
        }

        try {
            *(data_ + diff) = value;
        } catch (...) {
            for (size_t k = size_; k > diff; --k) {
                *(data_ + k - 1) = std::move(*(data_ + k));
            }
            throw;
        }

        ++size_;

    } else {
        size_t new_cap;
        if (capacity_ == 0) {
            new_cap = count;
        } else if (size_ + count <= capacity_ * 2) {
            new_cap = capacity_ * 2;
        } else {
            new_cap = size_ + count;
        }

        T *old_data = data_;

        try {
            data_ = reinterpret_cast<T *>(new char[new_cap * sizeof(T)]);
        } catch (...) {
            data_ = old_data;
            throw;
        }

        size_t k = 0;
        try {
            for (; k < count; ++k) {
                *(data_ + diff + k) = value;
            }
        } catch (...) {
            for (size_t i = 0; i < k; ++i) {
                delete (data_ + diff + i);
            }
            delete[] reinterpret_cast<char *>(data_);
            data_ = old_data;
            throw;
        }

        for (size_t k = 0; k < size_ + count; ++k) {
            if (k < diff) {
                *(data_ + k) = std::move(*(old_data + k));
            } else if (k >= diff + count) {
                *(data_ + k) = std::move(*(old_data + k - count));
            }
        }

        for (size_t k = 0; k < size_; ++k) {
            old_data[k].~T();
        }
        delete[] reinterpret_cast<char *>(old_data);
        capacity_ = new_cap;
        size_ += count;
    }

    return Iterator(data_ + diff);
}

template <typename T>
typename vector<T>::Iterator vector<T>::erase(vector<T>::ConstIterator pos) {
    Iterator it = begin() + (pos - cbegin());

    if ((it < begin()) || (it >= end())) {
        throw std::out_of_range("EraseError: Iterator out of range");
    }

    if (it == end() - 1) {
        (*it).~T();
    }

    for (; it != end() - 1; ++it) {
        *it = std::move(*(it + 1));
    }
    --size_;

    return it;
}

template <typename T>
typename vector<T>::Iterator vector<T>::erase(vector<T>::ConstIterator first,
                                              vector<T>::ConstIterator last) {
    Iterator it_first = begin() + (first - cbegin());
    Iterator it_last = begin() + (last - cbegin());

    std::ptrdiff_t diff = last - first;

    if ((first < cbegin()) || (last > cend())) {
        throw std::out_of_range("EraseError: Iterators out of range");
    } else if (last <= first) {
        return it_last;
    }

    if (it_first == end() - 1) {
        (*it_first).~T();
    }

    for (; ((it_first != end() - 1) && (it_first < it_last)); ++it_first) {
        *it_first = std::move(*(it_first + diff));
    }

    size_ -= last - first;

    return it_first;
}

template <typename T>
void vector<T>::push_back(const T &value) {
    if (size_ < capacity_) {
        try {
            new (data_ + size_) T(value);
            ++size_;
        } catch (...) {
            throw;
        }
    } else {
        size_t new_cap = capacity_ > 0 ? capacity_ * 2 : 1;

        T *new_data = reinterpret_cast<T *>(new char[new_cap * sizeof(T)]);

        try {
            new (new_data + size_) T(value);
        } catch (...) {
            delete[] reinterpret_cast<char *>(new_data);
            throw;
        }

        for (size_t k = 0; k < size_; ++k) {
            new (new_data + k) T(std::move(data_[k]));
        }

        delete[] reinterpret_cast<char *>(data_);

        data_ = new_data;
        capacity_ = new_cap;
        ++size_;
    }
}

template <typename T>
void vector<T>::push_back(T &&value) {
    if (size_ < capacity_) {
        new (data_ + size_) T(std::move(value));
        ++size_;
    } else {
        size_t new_cap = capacity_ > 0 ? capacity_ * 2 : 1;

        T *new_data = reinterpret_cast<T *>(new char[new_cap * sizeof(T)]);

        new (new_data + size_) T(std::move(value));

        for (size_t k = 0; k < size_; ++k) {
            new (new_data + k) T(std::move(data_[k]));
        }

        delete[] reinterpret_cast<char *>(data_);

        data_ = new_data;
        capacity_ = new_cap;
        ++size_;
    }
}

template <typename T>
void vector<T>::clear() noexcept {
    while (!empty()) {
        --size_;
        data_[size_].~T();
    }
}

template <typename T>
void vector<T>::pop_back() noexcept {
    if (!empty()) {
        --size_;
        data_[size_].~T();
    }
}

template <typename T>
void vector<T>::resize(size_t count) {
    if (count > max_size()) {
        throw std::length_error("ReserveError: Large size for a new capacity");
    }

    if (count > capacity_) {
        size_t new_cap = capacity_ > 0 ? capacity_ * 2 : 1;

        new_cap = count > new_cap ? count : new_cap;

        T *new_data = reinterpret_cast<T *>(new char[new_cap * sizeof(T)]);

        size_t k = 0;

        try {
            for (; k < count - capacity_; ++k) {
                new (new_data + size_ + k) T();
            }
        } catch (...) {
            for (size_t j = 0; j < k; ++j) {
                new_data[size_ + j].~T();
            }
            delete[] reinterpret_cast<char *>(new_data);
            throw;
        }

        for (size_t i = 0; i < size_; ++i) {
            new (new_data + i) T(std::move(data_[i]));
        }

        delete[] reinterpret_cast<char *>(data_);

        data_ = new_data;
        capacity_ = new_cap;
        size_ = count;
    }

    size_t i = 0;
    try {
        while (size_ < count) {
            new (data_ + size_) T();
            ++size_;
            ++i;
        }
    } catch (...) {
        for (size_t j = 0; j < i; ++j) {
            data_[size_ - 1].~T();
            --size_;
        }
        throw;
    }

    while (size_ > count) {
        --size_;
        data_[size_].~T();
    }
}

template <typename T>
void vector<T>::resize(size_t count, const T &value) {
    if (count > max_size()) {
        throw std::length_error("ReserveError: Large size for a new capacity");
    }

    if (count > capacity_) {
        size_t new_cap = capacity_ > 0 ? capacity_ * 2 : 1;

        new_cap = count > new_cap ? count : new_cap;

        T *new_data = reinterpret_cast<T *>(new char[new_cap * sizeof(T)]);

        size_t k = 0;

        try {
            for (; k < count - capacity_; ++k) {
                new (new_data + size_ + k) T(value);
            }
        } catch (...) {
            for (size_t j = 0; j < k; ++j) {
                new_data[size_ + j].~T();
            }
            delete[] reinterpret_cast<char *>(new_data);
            throw;
        }

        for (size_t i = 0; i < size_; ++i) {
            new (new_data + i) T(std::move(data_[i]));
        }

        delete[] reinterpret_cast<char *>(data_);

        data_ = new_data;
        capacity_ = new_cap;
        size_ = count;
    }

    size_t i = 0;
    try {
        while (size_ < count) {
            new (data_ + size_) T(value);
            ++size_;
            ++i;
        }
    } catch (...) {
        for (size_t j = 0; j < i; ++j) {
            data_[size_ - 1].~T();
            --size_;
        }
        throw;
    }

    while (size_ > count) {
        --size_;
        data_[size_].~T();
    }
}

template <typename T>
void vector<T>::swap(vector &other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

template <typename T>
typename vector<T>::Iterator vector<T>::begin() noexcept {
    return Iterator(data_);
}

template <typename T>
typename vector<T>::Iterator vector<T>::end() noexcept {
    return Iterator(data_ + size_);
}

template <typename T>
typename vector<T>::ConstIterator vector<T>::cbegin() const noexcept {
    return ConstIterator(data_);
}

template <typename T>
typename vector<T>::ConstIterator vector<T>::cend() const noexcept {
    return ConstIterator(data_ + size_);
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

}  // namespace s21

#endif  // S21_VECTOR_TPP
