#ifndef S21_ARRAY_TPP
#define S21_ARRAY_TPP

#include "s21_array.h"

namespace s21 {

template <typename T, std::size_t N>
array<T, N>::array() noexcept {}

template <typename T, std::size_t N>
array<T, N>::array(const array& other) {
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
}

template <typename T, std::size_t N>
array<T, N>::array(std::initializer_list<T> init) {
    size_t k = 0;

    for (const auto& elem : init) {
        data_[k] = elem;
        ++k;
    }
}

template <typename T, std::size_t N>
array<T, N>::array(array&& other) noexcept {
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = std::move(other.data_[i]);
    }
}

template <typename T, std::size_t N>
array<T, N>& array<T, N>::operator=(const array& other) noexcept {
    if (this != &other) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    return *this;
}

template <typename T, std::size_t N>
T& array<T, N>::at(size_t pos) {
    if (pos >= size_) {
        throw std::out_of_range("AtError: vector is empty");
    }
    return data_[pos];
}

template <typename T, std::size_t N>
const T& array<T, N>::at(size_t pos) const {
    if (pos >= size_) {
        throw std::out_of_range("AtError: vector is empty");
    }
    return data_[pos];
}

template <typename T, std::size_t N>
T& array<T, N>::operator[](size_t pos) {
    return data_[pos];
}

template <typename T, std::size_t N>
const T& array<T, N>::operator[](size_t pos) const {
    return data_[pos];
}

template <typename T, std::size_t N>
T& array<T, N>::front() {
    return data_[0];
}

template <typename T, std::size_t N>
const T& array<T, N>::front() const {
    return data_[0];
}

template <typename T, std::size_t N>
T& array<T, N>::back() {
    return data_[size_ - 1];
}

template <typename T, std::size_t N>
const T& array<T, N>::back() const {
    return data_[size_ - 1];
}

template <typename T, std::size_t N>
T* array<T, N>::data() noexcept {
    return data_;
}

template <typename T, std::size_t N>
const T* array<T, N>::data() const noexcept {
    return data_;
}

template <typename T, std::size_t N>
bool array<T, N>::empty() const noexcept {
    return size_ == 0;
}

template <typename T, std::size_t N>
size_t array<T, N>::size() const noexcept {
    return size_;
}

template <typename T, std::size_t N>
size_t array<T, N>::max_size() const noexcept {
    return size_;
}

template <typename T, std::size_t N>
void array<T, N>::fill(const T& value) {
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = value;
    }
}

template <typename T, std::size_t N>
void array<T, N>::swap(array& other) noexcept {
    for (size_t i = 0; i < size_; ++i) {
        std::swap(data_[i], other.data_[i]);
    }
}

template <typename T, std::size_t N>
typename array<T, N>::Iterator array<T, N>::begin() noexcept {
    return Iterator(data_);
}

template <typename T, std::size_t N>
typename array<T, N>::Iterator array<T, N>::end() noexcept {
    return Iterator(data_ + size_);
}

template <typename T, std::size_t N>
typename array<T, N>::ConstIterator array<T, N>::cbegin() const noexcept {
    return ConstIterator(data_);
}

template <typename T, std::size_t N>
typename array<T, N>::ConstIterator array<T, N>::cend() const noexcept {
    return ConstIterator(data_ + size_);
}

}  // namespace s21

#endif  // S21_ARRAY_TPP