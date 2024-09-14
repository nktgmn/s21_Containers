#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <initializer_list>

#include "../iterators/s21_seq_iterators.h"

namespace s21 {

template <typename T>
class vector {
   public:
    using iter = SequenceIterator<T>;
    using c_iter = ConstSequenceIterator<T>;

    vector() noexcept;
    vector(const vector &other);
    vector(std::initializer_list<T> init);
    vector(vector &&other) noexcept;
    ~vector();

    vector &operator=(const vector &other);
    vector &operator=(vector &&other) noexcept;
    vector &operator=(std::initializer_list<T> ilist);

    T &at(size_t pos);
    const T &at(size_t pos) const;
    T &operator[](size_t pos);
    const T &operator[](size_t pos) const;
    T &front();
    const T &front() const;
    T &back();
    const T &back() const;
    T *data() noexcept;
    const T *data() const noexcept;

    bool empty() const noexcept;
    size_t size() const noexcept;
    size_t max_size() const noexcept;
    void reserve(size_t new_cap);
    size_t capacity() const noexcept;
    void shrink_to_fit();

    void clear() noexcept;
    iter insert(c_iter pos, const T &value);
    iter insert(c_iter pos, T &&value);
    iter insert(c_iter pos, size_t count, const T &value);
    iter erase(c_iter pos);
    iter erase(c_iter first, c_iter last);
    void push_back(const T &value);
    void push_back(T &&value);
    void pop_back() noexcept;
    void resize(size_t count);
    void resize(size_t count, const T &value);
    void swap(vector &other) noexcept;

    iter begin() noexcept;
    iter end() noexcept;
    c_iter cbegin() const noexcept;
    c_iter cend() const noexcept;

    template <typename... Args>
    iter insert_many(c_iter pos, Args&&... args);

    template <typename... Args>
    void insert_many_back(Args&&... args);

   private:
    T *data_;
    size_t size_;
    size_t capacity_;
};

template <typename T>
bool operator==(const vector<T> &left, const vector<T> &right);

template <typename T>
bool operator!=(const vector<T> &left, const vector<T> &right);

}  // namespace s21

#include "../iterators/s21_seq_iterators.tpp"

#endif  // S21_VECTOR_H
