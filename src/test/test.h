#ifndef S21_TEST_H_
#define S21_TEST_H_

#include <gtest/gtest.h>

#include <array>
#include <list>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#include "../s21_containers.h"
#include "../s21_containersplus.h"

template <typename T, typename N>
bool operator==(const s21::list<T>& s21_lst, const std::list<N>& lst);

template <typename T, typename N>
bool operator!=(const s21::list<T>& s21_lst, const std::list<N>& lst);

template <typename T, typename N>
bool operator==(const s21::vector<T>& s21_vec, const std::vector<N>& vec);

template <typename T, typename N>
bool operator!=(const s21::vector<T>& s21_vec, const std::vector<N>& vec);

template <typename T, typename S, size_t N>
bool operator==(const s21::array<T, N>& s21_array, const std::array<S, N>& array);

template <typename T, typename S, size_t N>
bool operator!=(const s21::array<T, N>& s21_array, const std::array<S, N>& array);

template <typename K, typename V>
bool operator==(const s21::map<K, V>& s21_map, const std::map<K, V>& map);

template <typename K, typename V>
bool operator!=(const s21::map<K, V>& s21_map, const std::map<K, V>& map);

template <typename K>
bool operator==(const s21::set<K>& s21_set, const std::set<K>& set);

template <typename K>
bool operator!=(const s21::set<K>& s21_set, const std::set<K>& set);

template <typename K>
bool operator==(const s21::multiset<K>& s21_multiset, const std::multiset<K>& multiset);

template <typename K>
bool operator!=(const s21::multiset<K>& s21_multiset, const std::multiset<K>& multiset);

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
bool operator==(const s21::array<T, N>& s21_array, const std::array<S, N>& array) {
    bool res = true;

    for (size_t i = 0; i < N; ++i) {
        if (s21_array[i] != array[i]) {
            res = false;
        }
    }

    return res;
}

template <typename T, typename S, size_t N>
bool operator!=(const s21::array<T, N>& s21_array, const std::array<S, N>& array) {
    return !(s21_array == array);
}

template <typename K, typename V>
bool operator==(const s21::map<K, V>& s21_map, const std::map<K, V>& map) {
    bool res = true;

    auto s21_it_beg = s21_map.cbegin();
    auto s21_it_end = s21_map.cend();
    auto it_beg = map.cbegin();
    auto it_end = map.cend();

    while (s21_it_beg != s21_it_end) {
        if (((*s21_it_beg).first != (*it_beg).first) || ((*s21_it_beg).second != (*it_beg).second)) {
            res = false;
            break;
        }
        ++s21_it_beg;
        ++it_beg;
    }

    if (it_beg != it_end) {
        res = false;
    }

    if ((s21_map.size() != map.size()) || (s21_map.max_size() != map.max_size()) || (s21_map.empty() != map.empty())) {
        res = false;
    }

    return res;
}

template <typename K, typename V>
bool operator!=(const s21::map<K, V>& s21_map, const std::map<K, V>& map) {
    return !(s21_map == map);
}

template <typename K>
bool operator==(const s21::set<K>& s21_set, const std::set<K>& set) {
    bool res = true;

    auto s21_it_beg = s21_set.cbegin();
    auto s21_it_end = s21_set.cend();
    auto it_beg = set.cbegin();
    auto it_end = set.cend();

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

    if ((s21_set.size() != set.size()) || (s21_set.max_size() != set.max_size()) || (s21_set.empty() != set.empty())) {
        res = false;
    }

    return res;
}

template <typename K>
bool operator!=(const s21::set<K>& s21_set, const std::set<K>& set) {
    return !(s21_set == set);
}

template <typename K>
bool operator==(const s21::multiset<K>& s21_multiset, const std::multiset<K>& multiset) {
    bool res = true;

    auto s21_it_beg = s21_multiset.cbegin();
    auto s21_it_end = s21_multiset.cend();
    auto it_beg = multiset.cbegin();
    auto it_end = multiset.cend();

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

    if ((s21_multiset.size() != multiset.size()) || (s21_multiset.max_size() != multiset.max_size()) || (s21_multiset.empty() != multiset.empty())) {
        res = false;
    }

    return res;
}

template <typename K>
bool operator!=(const s21::multiset<K>& s21_multiset, const std::multiset<K>& multiset) {
    return !(s21_multiset == multiset);
}

#endif  // S21_TEST_H_
