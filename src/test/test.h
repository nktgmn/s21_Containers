#ifndef S21_TEST_H_
#define S21_TEST_H_

#include <gtest/gtest.h>

#include <array>
#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../AVLtree/s21_avl.tpp"
#include "../array/s21_array.tpp"
#include "../list/s21_list.tpp"
#include "../queue/s21_queue.tpp"
#include "../stack/s21_stack.tpp"
#include "../vector/s21_vector.tpp"

template <typename T, typename N>
bool operator==(const s21::list<T>& s21_lst, const std::list<N>& lst);

template <typename T, typename N>
bool operator!=(const s21::list<T>& s21_lst, const std::list<N>& lst);

template <typename T, typename N>
bool operator==(const s21::vector<T>& s21_vec, const std::vector<N>& vec);

template <typename T, typename N>
bool operator!=(const s21::vector<T>& s21_vec, const std::vector<N>& vec);

template <typename T, typename S, size_t N>
bool operator==(const s21::array<T, N>& s21_array,
                const std::array<S, N>& array);

template <typename T, typename S, size_t N>
bool operator!=(const s21::array<T, N>& s21_array,
                const std::array<S, N>& array);

template <typename T, typename N>
bool operator==(const s21::list<T>& s21_lst, const std::list<N>& lst) {
    bool res = true;

    auto s21_it_beg = s21_lst.cbegin();
    auto s21_it_end = s21_lst.cend();
    auto it_beg = lst.cbegin();
    auto it_end = lst.cend();

    while (s21_it_beg != s21_it_end) {
        if (*s21_it_beg != *it_beg) {
            res = false;
            break;
        }
        ++s21_it_beg;
        ++it_beg;
    }

    if (it_beg != it_end) {
        res = false;
    }

    return res;
}

template <typename T, typename N>
bool operator!=(const s21::list<T>& s21_lst, const std::list<N>& lst) {
    return !(s21_lst == lst);
}

template <typename T, typename N>
bool operator==(const s21::vector<T>& s21_vec, const std::vector<N>& vec) {
    bool res = true;

    auto s21_it_beg = s21_vec.cbegin();
    auto s21_it_end = s21_vec.cend();
    auto it_beg = vec.cbegin();
    auto it_end = vec.cend();

    while (s21_it_beg != s21_it_end) {
        if (*s21_it_beg != *it_beg) {
            res = false;
            break;
        }
        ++s21_it_beg;
        ++it_beg;
    }

    if (it_beg != it_end) {
        res = false;
    }

    if ((s21_vec.size() != vec.size()) ||
        (s21_vec.capacity() != vec.capacity())) {
        res = false;
    }

    return res;
}

template <typename T, typename N>
bool operator!=(const s21::vector<T>& s21_vec, const std::vector<N>& vec) {
    return !(s21_vec == vec);
}

template <typename T, typename S, size_t N>
bool operator==(const s21::array<T, N>& s21_array,
                const std::array<S, N>& array) {
    bool res = true;

    for (size_t i = 0; i < N; ++i) {
        if (s21_array[i] != array[i]) {
            res = false;
        }
    }

    return res;
}

template <typename T, typename S, size_t N>
bool operator!=(const s21::array<T, N>& s21_array,
                const std::array<S, N>& array) {
    return !(s21_array == array);
}

#endif  // S21_TEST_H_
