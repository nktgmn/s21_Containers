#ifndef S21_LIST_ITERATORS_TPP
#define S21_LIST_ITERATORS_TPP

namespace s21 {

template <typename T>
list<T>::ListIterator::ListIterator() noexcept : ptr_(nullptr) {}

template <typename T>
list<T>::ListConstIterator::ListConstIterator() noexcept : ptr_(nullptr) {}

template <typename T>
list<T>::ListIterator::ListIterator(Node* ptr) noexcept
    : ptr_(const_cast<Node*>(ptr)) {}

template <typename T>
list<T>::ListIterator::ListIterator(const Node* ptr) noexcept
    : ptr_(const_cast<Node*>(ptr)) {}

template <typename T>
list<T>::ListIterator::ListIterator(const ListIterator& other) noexcept
    : ptr_(other.ptr_) {}

template <typename T>
list<T>::ListConstIterator::ListConstIterator(
    const ListConstIterator& other) noexcept
    : ptr_(other.ptr_) {}

template <typename T>
list<T>::ListConstIterator::ListConstIterator(
    const ListIterator& other) noexcept
    : ptr_(other.ptr_) {}

template <typename T>
list<T>::ListConstIterator::ListConstIterator(const Node* ptr) noexcept
    : ptr_(ptr) {}

template <typename T>
typename list<T>::ListIterator& list<T>::ListIterator::operator=(
    const ListIterator& other) {
    if (this != &other) {
        ptr_ = other.ptr_;
    }
    return *this;
}

template <typename T>
typename list<T>::ListConstIterator& list<T>::ListConstIterator::operator=(
    const ListConstIterator& other) {
    if (this != &other) {
        ptr_ = other.ptr_;
    }
    return *this;
}

template <typename T>
T& list<T>::ListIterator::operator*() noexcept {
    return ptr_->value;
}

template <typename T>
const T& list<T>::ListConstIterator::operator*() const noexcept {
    return ptr_->value;
}

template <typename T>
typename list<T>::ListIterator& list<T>::ListIterator::operator++() noexcept {
    ptr_ = static_cast<Node*>(ptr_->next);
    return *this;
}

template <typename T>
typename list<T>::ListConstIterator&
list<T>::ListConstIterator::operator++() noexcept {
    ptr_ = static_cast<const Node*>(ptr_->next);
    return *this;
}

template <typename T>
typename list<T>::ListIterator& list<T>::ListIterator::operator--() noexcept {
    ptr_ = static_cast<Node*>(ptr_->prev);
    return *this;
}

template <typename T>
typename list<T>::ListConstIterator&
list<T>::ListConstIterator::operator--() noexcept {
    ptr_ = static_cast<const Node*>(ptr_->prev);
    return *this;
}

template <typename T>
bool list<T>::ListIterator::operator==(
    const ListIterator& other) const noexcept {
    return ptr_ == other.ptr_;
}

template <typename T>
bool list<T>::ListConstIterator::operator==(
    const ListConstIterator& other) const noexcept {
    return ptr_ == other.ptr_;
}

template <typename T>
bool list<T>::ListIterator::operator!=(
    const ListIterator& other) const noexcept {
    return ptr_ != other.ptr_;
}

template <typename T>
bool list<T>::ListConstIterator::operator!=(
    const ListConstIterator& other) const noexcept {
    return ptr_ != other.ptr_;
}

}  // namespace s21

#endif  // S21_LIST_ITERATORS_TPP
