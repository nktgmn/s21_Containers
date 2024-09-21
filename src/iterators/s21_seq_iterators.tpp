#ifndef S21_SEQ_ITERATORS_TPP
#define S21_SEQ_ITERATORS_TPP

namespace s21 {

template <typename T>
SequenceIterator<T>::SequenceIterator() noexcept : ptr_(nullptr) {}

template <typename T>
ConstSequenceIterator<T>::ConstSequenceIterator() noexcept : ptr_(nullptr) {}

template <typename T>
SequenceIterator<T>::SequenceIterator(T* ptr) noexcept : ptr_(ptr) {}

template <typename T>
ConstSequenceIterator<T>::ConstSequenceIterator(const T* ptr) noexcept
    : ptr_(ptr) {}

template <typename T>
SequenceIterator<T>::SequenceIterator(const SequenceIterator& other) noexcept
    : ptr_(other.ptr_) {}

template <typename T>
ConstSequenceIterator<T>::ConstSequenceIterator(
    const ConstSequenceIterator& other) noexcept
    : ptr_(other.ptr_) {}

template <typename T>
SequenceIterator<T>::~SequenceIterator() noexcept {}

template <typename T>
ConstSequenceIterator<T>::~ConstSequenceIterator() noexcept {}

template <typename T>
SequenceIterator<T>& SequenceIterator<T>::operator=(const SequenceIterator& other) {
    ptr_ = other.ptr_;
    return *this;
}

template <typename T>
ConstSequenceIterator<T>& ConstSequenceIterator<T>::operator=(const ConstSequenceIterator& other) {
    ptr_ = other.ptr_;
    return *this;
}

template <typename T>
T& SequenceIterator<T>::operator*() noexcept {
    return *ptr_;
}

template <typename T>
const T& ConstSequenceIterator<T>::operator*() const noexcept {
    return *ptr_;
}

template <typename T>
SequenceIterator<T>& SequenceIterator<T>::operator++() noexcept {
    ++ptr_;
    return *this;
}

template <typename T>
ConstSequenceIterator<T>& ConstSequenceIterator<T>::operator++() noexcept {
    ++ptr_;
    return *this;
}

template <typename T>
SequenceIterator<T> SequenceIterator<T>::operator++(int) noexcept {
    SequenceIterator tmp(ptr_);
    ++ptr_;
    return tmp;
}

template <typename T>
ConstSequenceIterator<T> ConstSequenceIterator<T>::operator++(int) noexcept {
    ConstSequenceIterator tmp(ptr_);
    ++ptr_;
    return tmp;
}

template <typename T>
SequenceIterator<T>& SequenceIterator<T>::operator--() noexcept {
    --ptr_;
    return *this;
}

template <typename T>
ConstSequenceIterator<T>& ConstSequenceIterator<T>::operator--() noexcept {
    --ptr_;
    return *this;
}

template <typename T>
SequenceIterator<T> SequenceIterator<T>::operator--(int) noexcept {
    SequenceIterator tmp(ptr_);
    --ptr_;
    return tmp;
}

template <typename T>
ConstSequenceIterator<T> ConstSequenceIterator<T>::operator--(int) noexcept {
    ConstSequenceIterator tmp(ptr_);
    --ptr_;
    return tmp;
}

template <typename T>
SequenceIterator<T>& SequenceIterator<T>::operator+=(
    std::ptrdiff_t diff) noexcept {
    ptr_ += diff;
    return *this;
}

template <typename T>
ConstSequenceIterator<T>& ConstSequenceIterator<T>::operator+=(
    std::ptrdiff_t diff) noexcept {
    ptr_ += diff;
    return *this;
}

template <typename T>
SequenceIterator<T>& SequenceIterator<T>::operator-=(
    std::ptrdiff_t diff) noexcept {
    ptr_ -= diff;
    return *this;
}

template <typename T>
ConstSequenceIterator<T>& ConstSequenceIterator<T>::operator-=(
    std::ptrdiff_t diff) noexcept {
    ptr_ -= diff;
    return *this;
}

template <typename T>
SequenceIterator<T> SequenceIterator<T>::operator+(
    std::ptrdiff_t diff) noexcept {
    SequenceIterator tmp(ptr_);
    tmp += diff;
    return tmp;
}

template <typename T>
ConstSequenceIterator<T> ConstSequenceIterator<T>::operator+(
    std::ptrdiff_t diff) noexcept {
    ConstSequenceIterator tmp(ptr_);
    tmp += diff;
    return tmp;
}

template <typename T>
SequenceIterator<T> SequenceIterator<T>::operator-(
    std::ptrdiff_t diff) noexcept {
    SequenceIterator tmp(ptr_);
    tmp -= diff;
    return tmp;
}

template <typename T>
ConstSequenceIterator<T> ConstSequenceIterator<T>::operator-(
    std::ptrdiff_t diff) noexcept {
    ConstSequenceIterator tmp(ptr_);
    tmp -= diff;
    return tmp;
}

template <typename T>
std::ptrdiff_t SequenceIterator<T>::operator-(
    const SequenceIterator<T>& other) noexcept {
    std::ptrdiff_t diff = ptr_ - other.ptr_;
    return diff;
}

template <typename T>
std::ptrdiff_t ConstSequenceIterator<T>::operator-(
    const ConstSequenceIterator<T>& other) noexcept {
    std::ptrdiff_t diff = ptr_ - other.ptr_;
    return diff;
}

template <typename T>
bool SequenceIterator<T>::operator==(
    const SequenceIterator<T>& other) const noexcept {
    return ptr_ == other.ptr_;
}

template <typename T>
bool ConstSequenceIterator<T>::operator==(
    const ConstSequenceIterator<T>& other) const noexcept {
    return ptr_ == other.ptr_;
}

template <typename T>
bool SequenceIterator<T>::operator!=(
    const SequenceIterator<T>& other) const noexcept {
    return ptr_ != other.ptr_;
}

template <typename T>
bool ConstSequenceIterator<T>::operator!=(
    const ConstSequenceIterator<T>& other) const noexcept {
    return ptr_ != other.ptr_;
}

template <typename T>
bool SequenceIterator<T>::operator>(
    const SequenceIterator<T>& other) const noexcept {
    return ptr_ > other.ptr_;
}

template <typename T>
bool ConstSequenceIterator<T>::operator>(
    const ConstSequenceIterator<T>& other) const noexcept {
    return ptr_ > other.ptr_;
}

template <typename T>
bool SequenceIterator<T>::operator<(
    const SequenceIterator<T>& other) const noexcept {
    return ptr_ < other.ptr_;
}

template <typename T>
bool ConstSequenceIterator<T>::operator<(
    const ConstSequenceIterator<T>& other) const noexcept {
    return ptr_ < other.ptr_;
}

template <typename T>
bool SequenceIterator<T>::operator>=(
    const SequenceIterator<T>& other) const noexcept {
    return ptr_ >= other.ptr_;
}

template <typename T>
bool ConstSequenceIterator<T>::operator>=(
    const ConstSequenceIterator<T>& other) const noexcept {
    return ptr_ >= other.ptr_;
}

template <typename T>
bool SequenceIterator<T>::operator<=(
    const SequenceIterator<T>& other) const noexcept {
    return ptr_ <= other.ptr_;
}

template <typename T>
bool ConstSequenceIterator<T>::operator<=(
    const ConstSequenceIterator<T>& other) const noexcept {
    return ptr_ <= other.ptr_;
}

}  // namespace s21

#endif  // S21_SEQ_ITERATORS_TPP