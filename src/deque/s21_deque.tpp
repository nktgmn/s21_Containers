#ifndef S21_DEQUE_TPP
#define S21_DEQUE_TPP

#include "s21_deque.h"

namespace s21 {

template <typename T>
deque<T>::deque() noexcept {}

template <typename T>
deque<T>::deque(const deque& other)
    : ptrs_size(other.ptrs_size),
      i_begin(other.i_begin),
      j_begin(other.j_begin),
      i_end(other.i_end),
      j_end(other.j_end) {
    if (ptrs_size > 0) {
        ptrs = new T*[ptrs_size];
    }

    size_t k = 0;

    try {
        for (; k < ptrs_size; ++k) {
            ptrs[k] = reinterpret_cast<T*>(new char[N * sizeof(T)]);
        }
    } catch (...) {
        for (size_t i = 0; i < k; ++i) {
            delete[] reinterpret_cast<char*>(ptrs[i]);
        }
        delete[] ptrs;
        throw;
    }

    k = 0;

    try {
        for (; k < other.size(); ++k) {
            size_t row = k / N + i_begin;
            new (ptrs[k / N] + k % N) T(other.ptrs[k / N][k % N]);
        }
    } catch (...) {
        for (size_t i = 0; i < k; ++i) {
            (ptrs[i / N] + i % N)->~T();
        }

        for (size_t i = 0; i < ptrs_size; ++i) {
            delete[] reinterpret_cast<char*>(ptrs[i]);
        }
        delete[] ptrs;
        throw;
    }
}

template <typename T>
deque<T>::deque(std::initializer_list<T> init)
    : ptrs_size((init.size() + N - 1) / N),
      i_end(ptrs_size - 1),
      j_end(init.size() % N) {
    if (ptrs_size > 0) {
        ptrs = new T*[ptrs_size];
    }

    size_t k = 0;

    try {
        for (; k < ptrs_size; ++k) {
            ptrs[k] = reinterpret_cast<T*>(new char[N * sizeof(T)]);
        }
    } catch (...) {
        for (size_t i = 0; i < k; ++i) {
            delete[] reinterpret_cast<char*>(ptrs[i]);
        }
        delete[] ptrs;
        throw;
    }

    k = 0;

    try {
        for (const auto& elem : init) {
            new (ptrs[k / N] + k % N) T(elem);
            ++k;
        }
    } catch (...) {
        for (size_t i = 0; i < k; ++i) {
            (ptrs[i / N] + i % N)->~T();
        }

        for (size_t i = 0; i < ptrs_size; ++i) {
            delete[] reinterpret_cast<char*>(ptrs[i]);
        }
        delete[] ptrs;
        throw;
    }
}

template <typename T>
deque<T>::~deque() noexcept {
    clear();
}

template <typename T>
bool deque<T>::empty() const noexcept {
    return (size() == 0);
}

template <typename T>
size_t deque<T>::size() const noexcept {
    size_t size = i_end * N + j_end - j_begin;

    if (j_end == 0) {
        size += 32;
    }

    if (ptrs == nullptr) {
        size = 0;
    }

    return size;
}

template <typename T>
size_t deque<T>::max_size() const noexcept {
    return std::numeric_limits<size_t>::max() / sizeof(T);
}

template <typename T>
void deque<T>::clear() noexcept {
    if (size()) {
        for (size_t i = j_begin; i < N; ++i) {
            ptrs[0][i].~T();
        }

        for (size_t i = 1; i < i_end; ++i) {
            for (size_t k = 0; k < N; ++k) {
                ptrs[i][k].~T();
            }
        }

        for (size_t i = 0; i < j_end && i_end >= 1; ++i) {
            ptrs[i_end][i].~T();
        }

        for (size_t i = 0; i < ptrs_size; ++i) {
            delete[] reinterpret_cast<char*>(ptrs[i]);
        }

        delete[] ptrs;
        ptrs = nullptr;
        i_end = 0;
        j_begin = 0;
        j_end = 0;
    }
}

template <typename T>
void deque<T>::push_back(const T& value) {
    if (((i_end == ptrs_size - 1) && (j_end == 0)) || (ptrs_size == 0)) {
        size_t new_ptrs_size = ptrs_size > 0 ? ptrs_size * 2 : 1;
        T** new_ptrs = new T*[new_ptrs_size];

        size_t k = ptrs_size;

        try {
            for (; k < new_ptrs_size; ++k) {
                new_ptrs[k] = reinterpret_cast<T*>(new char[N * sizeof(T)]);
            }
        } catch (...) {
            for (size_t i = ptrs_size; i < k; ++i) {
                delete[] reinterpret_cast<char*>(new_ptrs[i]);
            }
            delete[] new_ptrs;
            throw;
        }

        try {
            new (new_ptrs[ptrs_size]) T(value);
        } catch (...) {
            for (size_t i = ptrs_size; i < new_ptrs_size; ++i) {
                delete[] reinterpret_cast<char*>(new_ptrs[i]);
            }
            delete[] new_ptrs;
            throw;
        }

        for (size_t i = 0; i < ptrs_size; ++i) {
            new_ptrs[i] = ptrs[i];
        }

        delete[] ptrs;
        ptrs = new_ptrs;

        if (ptrs_size > 0) {
            ++i_end;
        }

        ptrs_size = new_ptrs_size;

    } else {
        if (j_end == 0) {
            ++i_end;
        }

        try {
            new (ptrs[i_end] + j_end) T(value);
        } catch (...) {
            if (j_end == 0) {
                --i_end;
            }
        }
    }

    j_end = (j_end + 1) % N;
}

template <typename T>
void deque<T>::push_back(T&& value) {
    if (((i_end == ptrs_size - 1) && (j_end == 0)) || (ptrs_size == 0)) {
        size_t new_ptrs_size = ptrs_size > 0 ? ptrs_size * 2 : 1;
        T** new_ptrs = new T*[new_ptrs_size];

        size_t k = ptrs_size;

        try {
            for (; k < new_ptrs_size; ++k) {
                new_ptrs[k] = reinterpret_cast<T*>(new char[N * sizeof(T)]);
            }
        } catch (...) {
            for (size_t i = ptrs_size; i < k; ++i) {
                delete[] reinterpret_cast<char*>(new_ptrs[i]);
            }
            delete[] new_ptrs;
            throw;
        }

        new (new_ptrs[ptrs_size]) T(std::move(value));

        for (size_t i = 0; i < ptrs_size; ++i) {
            new_ptrs[i] = ptrs[i];
        }

        delete[] ptrs;
        ptrs = new_ptrs;

        if (ptrs_size > 0) {
            ++i_end;
        }

        ptrs_size = new_ptrs_size;

    } else {
        if (j_end == 0) {
            ++i_end;
        }

        new (ptrs[i_end] + j_end) T(std::move(value));
    }

    j_end = (j_end + 1) % N;
}

}  // namespace s21

#endif  // S21_DEQUE_TPP
