#include "test.h"

#include <gtest/gtest.h>

TEST(VECTOR, Constructors) {
    s21::vector<int> s21_1;
    std::vector<int> std_1;
    EXPECT_TRUE(s21_1 == std_1);

    s21::vector<int> s21_2 = {};
    std::vector<int> std_2 = {};
    EXPECT_TRUE(s21_2 == std_2);

    s21::vector<int> s21_3 = {1, 2, 3};
    std::vector<int> std_3 = {1, 2, 3};
    EXPECT_TRUE(s21_3 == std_3);

    s21::vector<int> s21_4(s21_3);
    std::vector<int> std_4(std_3);
    EXPECT_TRUE(s21_4 == std_4);

    s21::vector<int> s21_5 = s21_3;
    std::vector<int> std_5 = std_3;
    EXPECT_TRUE(s21_5 == std_5);

    s21::vector<int> s21_6 = std::move(s21_3);
    std::vector<int> std_6 = std::move(std_3);
    EXPECT_TRUE(s21_6 == std_6);
    EXPECT_TRUE(s21_3 == std_3);

    s21::vector<int> s21_7 = {1, 2, 3};
    std::vector<int> std_7 = {1, 2, 3};
    s21::vector<int> s21_8(std::move(s21_7));
    std::vector<int> std_8(std::move(std_7));
    EXPECT_TRUE(s21_7 == std_7);
    EXPECT_TRUE(s21_8 == std_8);

    s21::vector<int> s21_9({1, 2, 3});
    std::vector<int> std_9({1, 2, 3});
    EXPECT_TRUE(s21_9 == std_9);

    s21::vector<s21::vector<int>> s21_10;
    std::vector<std::vector<int>> std_10;
    EXPECT_TRUE(s21_10 == std_10);

    s21::vector<s21::vector<int>> s21_11 = {};
    std::vector<std::vector<int>> std_11 = {};
    EXPECT_TRUE(s21_11 == std_11);

    s21::vector<s21::vector<int>> s21_12 = {{1, 2}, {1, 3}};
    std::vector<std::vector<int>> std_12 = {{1, 2}, {1, 3}};
    EXPECT_TRUE(s21_12 == std_12);

    s21::vector<s21::vector<int>> s21_13(s21_12);
    std::vector<std::vector<int>> std_13(std_12);
    EXPECT_TRUE(s21_13 == std_13);

    s21::vector<s21::vector<int>> s21_14(s21_12);
    std::vector<std::vector<int>> std_14(std_12);
    EXPECT_TRUE(s21_14 == std_14);

    s21::vector<s21::vector<int>> s21_15 = std::move(s21_12);
    std::vector<std::vector<int>> std_15 = std::move(std_12);
    EXPECT_TRUE(s21_15 == std_15);
    EXPECT_TRUE(s21_12 == std_12);

    s21::vector<s21::vector<int>> s21_16 = {{1, 2}, {1, 3}};
    std::vector<std::vector<int>> std_16 = {{1, 2}, {1, 3}};
    s21::vector<s21::vector<int>> s21_17(std::move(s21_16));
    std::vector<std::vector<int>> std_17(std::move(std_16));
    EXPECT_TRUE(s21_16 == std_16);
    EXPECT_TRUE(s21_17 == std_17);

    s21::vector<s21::vector<int>> s21_18({{1, 2}, {1, 3}});
    std::vector<std::vector<int>> std_18({{1, 2}, {1, 3}});
    EXPECT_TRUE(s21_18 == std_18);
}

TEST(VECTOR, FrontBack) {
    const s21::vector<int> s21_1 = {1, 2, 3};
    const std::vector<int> std_1 = {1, 2, 3};
    EXPECT_TRUE(s21_1.front() == std_1.front());
    EXPECT_TRUE(s21_1.back() == std_1.back());

    s21::vector<int> s21_2 = {1, 2, 3};
    std::vector<int> std_2 = {1, 2, 3};
    s21_2.front() = 5;
    s21_2.back() = 6;
    std_2.front() = 5;
    std_2.back() = 6;
    EXPECT_TRUE(s21_2 == std_2);

    const s21::vector<s21::vector<int>> s21_3 = {
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const std::vector<std::vector<int>> std_3 = {
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_TRUE(s21_3.front() == std_3.front());
    EXPECT_TRUE(s21_3.back() == std_3.back());

    s21::vector<s21::vector<int>> s21_4 = {{1}, {4, 5, 6, 7}, {4, 5, 6, 7, 8}};
    std::vector<std::vector<int>> std_4 = {{1}, {4, 5, 6, 7}, {4, 5, 6, 7, 8}};
    s21_4.front() = {1, 2};
    s21_4.back() = {3, 4};
    std_4.front() = {1, 2};
    std_4.back() = {3, 4};
    EXPECT_TRUE(s21_4 == std_4);
}

TEST(VECTOR, EmptyMaxSize) {
    s21::vector<int> s21_1 = {1, 2, 3};
    std::vector<int> std_1 = {1, 2, 3};
    EXPECT_TRUE(s21_1.empty() == std_1.empty());
    EXPECT_TRUE(s21_1.max_size() == std_1.max_size());

    s21::vector<int> s21_2;
    std::vector<int> std_2;
    EXPECT_TRUE(s21_2.empty() == std_2.empty());

    s21::vector<s21::vector<int>> s21_3 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    std::vector<std::vector<int>> std_3 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_TRUE(s21_3.empty() == std_3.empty());
    EXPECT_TRUE(s21_3.max_size() == std_3.max_size());

    s21::vector<s21::vector<int>> s21_4;
    std::vector<std::vector<int>> std_4;
    EXPECT_TRUE(s21_4.empty() == std_4.empty());
}

TEST(VECTOR, Insert) {
    s21::vector<int> s21_1 = {1, 2, 3, 4, 5};
    std::vector<int> std_1 = {1, 2, 3, 4, 5};
    auto s21_it_1 = s21_1.cbegin();
    auto std_it_1 = std_1.cbegin();
    auto s21_it_2 = s21_1.insert(s21_it_1, 9);
    auto std_it_2 = std_1.insert(std_it_1, 9);
    EXPECT_TRUE(*s21_it_2 == *std_it_2);
    EXPECT_TRUE(s21_1 == std_1);
    s21_it_1 = s21_1.cbegin();
    std_it_1 = std_1.cbegin();
    for (int k = 0; k < 2; ++k) {
        ++s21_it_1;
        ++std_it_1;
    }
    const int y = 8;
    auto s21_it_3 = s21_1.insert(s21_it_1, y);
    auto std_it_3 = std_1.insert(std_it_1, y);
    EXPECT_TRUE(*s21_it_3 == *std_it_3);
    s21_it_1 = s21_1.cend();
    std_it_1 = std_1.cend();
    const int x = 7;
    auto s21_it_4 = s21_1.insert(s21_it_1, x);
    auto std_it_4 = std_1.insert(std_it_1, x);
    EXPECT_TRUE(*s21_it_4 == *std_it_4);
    EXPECT_TRUE(s21_1 == std_1);
    s21_it_1 = s21_1.cbegin();
    std_it_1 = std_1.cbegin();
    auto s21_it_9 = s21_1.insert(s21_it_1, 11);
    auto std_it_9 = std_1.insert(std_it_1, 11);
    EXPECT_TRUE(*s21_it_9 == *std_it_9);
    EXPECT_TRUE(s21_1 == std_1);

    s21::vector<s21::vector<int>> s21_2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    std::vector<std::vector<int>> std_2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    auto s21_it_5 = s21_2.cbegin();
    auto std_it_5 = std_2.cbegin();
    const s21::vector<int> s21_3 = {4, 5};
    const std::vector<int> std_3 = {4, 5};
    auto s21_it_6 = s21_2.insert(s21_it_5, s21_3);
    auto std_it_6 = std_2.insert(std_it_5, std_3);
    EXPECT_TRUE(*s21_it_6 == *std_it_6);
    s21_it_5 = s21_2.cbegin();
    std_it_5 = std_2.cbegin();
    for (int k = 0; k < 2; ++k) {
        ++s21_it_5;
        ++std_it_5;
    }
    auto s21_it_7 = s21_2.insert(s21_it_5, {1, 2});
    auto std_it_7 = std_2.insert(std_it_5, {1, 2});
    EXPECT_TRUE(*s21_it_7 == *std_it_7);
    s21_it_5 = s21_2.cend();
    std_it_5 = std_2.cend();
    auto s21_it_8 = s21_2.insert(s21_it_5, {3, 4});
    auto std_it_8 = std_2.insert(std_it_5, {3, 4});
    EXPECT_TRUE(*s21_it_8 == *std_it_8);
    EXPECT_TRUE(s21_2 == std_2);

    s21::vector<int> s21_4 = {1, 2, 3, 4, 5};
    std::vector<int> std_4 = {1, 2, 3, 4, 5};
    auto s21_it_10 = ++s21_4.cbegin();
    auto std_it_10 = ++std_4.cbegin();
    auto s21_it_11 = s21_4.insert(s21_it_10, 9, 20);
    auto std_it_11 = std_4.insert(std_it_10, 9, 20);
    EXPECT_TRUE(*s21_it_11 == *std_it_11);
    EXPECT_TRUE(s21_4 == std_4);

    s21::vector<int> s21_5 = {};
    std::vector<int> std_5 = {};
    auto s21_it_12 = s21_5.cend();
    auto std_it_12 = std_5.cend();
    auto s21_it_13 = s21_5.insert(s21_it_12, 9, 20);
    auto std_it_13 = std_5.insert(std_it_12, 9, 20);
    EXPECT_TRUE(*s21_it_13 == *std_it_13);
    EXPECT_TRUE(s21_5 == std_5);
}

TEST(Vector, AtSimple) {
    s21::vector<int> a = {1, 2, 3, 4, 5, 6};
    const s21::vector<int> b = {1, 2, 3, 4, 5, 6};

    EXPECT_EQ(a.at(0), 1);
    EXPECT_EQ(b.at(1), 2);

    EXPECT_EQ(a.at(0) = 10, 10);

    EXPECT_THROW(a.at(10), std::out_of_range);
    EXPECT_THROW(a.at(-1), std::out_of_range);

    EXPECT_THROW(a.at(10) = 20, std::out_of_range);
    EXPECT_THROW(a.at(-1) = 20, std::out_of_range);

    EXPECT_THROW(b.at(10), std::out_of_range);
    EXPECT_THROW(b.at(-1), std::out_of_range);
}

TEST(Vector, AtComplex) {
    s21::vector<int> aa = {1, 2, 3};
    s21::vector<int> ab = {4, 5, 6, 7};
    s21::vector<int> ac = {};
    s21::vector<s21::vector<int>> a = {aa, ab, ac};
    const s21::vector<s21::vector<int>> b = {aa, ab, ac};

    s21::vector<int>& el = a.at(0);
    s21::vector<int> d = {1, 2};
    el = d;
    EXPECT_EQ(el.size(), d.size());

    EXPECT_THROW(a.at(10), std::out_of_range);
    EXPECT_THROW(a.at(-1), std::out_of_range);

    EXPECT_THROW(a.at(10) = d, std::out_of_range);
    EXPECT_THROW(a.at(-1) = d, std::out_of_range);

    EXPECT_THROW(b.at(10), std::out_of_range);
    EXPECT_THROW(b.at(-1), std::out_of_range);
}

TEST(Vector, ShrinkToFitSimple) {
    s21::vector<int> a = {1, 2, 3, 4, 5, 6};
    std::vector<int> b = {1, 2, 3, 4, 5, 6};

    a.push_back(7);
    b.push_back(7);

    a.shrink_to_fit();
    b.shrink_to_fit();

    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(a.capacity(), b.capacity());
}

TEST(Vector, ShrinkToFitComplex) {
    s21::vector<s21::vector<int>> a = {{1, 2}, {3, 4}};
    std::vector<std::vector<int>> b = {{1, 2}, {3, 4}};

    a.push_back({5, 6});
    b.push_back({5, 6});

    a.shrink_to_fit();
    b.shrink_to_fit();

    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(a.capacity(), b.capacity());
}

TEST(Vector, Data) {
    s21::vector<s21::vector<int>> a;
    s21::vector<int> b;
    const s21::vector<s21::vector<int>> c;
    const s21::vector<int> d;

    EXPECT_EQ(a.data(), nullptr);
    EXPECT_EQ(b.data(), nullptr);
    EXPECT_EQ(c.data(), nullptr);
    EXPECT_EQ(d.data(), nullptr);
}

TEST(Vector, Reserve) {
    s21::vector<s21::vector<int>> a = {{1}, {2}, {3}, {4}};
    std::vector<std::vector<int>> b = {{1}, {2}, {3}, {4}};

    a.reserve(2);
    b.reserve(2);

    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(a.capacity(), b.capacity());

    a.reserve(6);
    b.reserve(6);

    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(a.capacity(), b.capacity());

    s21::vector<s21::vector<int>> c;
    std::vector<std::vector<int>> d;

    c.reserve(6);
    d.reserve(6);

    EXPECT_EQ(c.size(), d.size());
    EXPECT_EQ(c.capacity(), d.capacity());

    EXPECT_THROW(c.reserve(c.max_size() + 1), std::length_error);
}

TEST(Array, Size) {
    s21::array<int, 3> a = {1, 2, 3};

    size_t sz = 3;

    EXPECT_EQ(a.size(), sz);
}

TEST(Array, Empty) {
    s21::array<int, 3> a = {1, 2, 3};
    EXPECT_FALSE(a.empty());

    s21::array<int, 0> b;

    EXPECT_TRUE(b.empty());
}

TEST(Array, MaxSize) {
    s21::array<int, 10> a;
    std::array<int, 10> b;

    EXPECT_EQ(a.max_size(), b.max_size());
}

TEST(Array, Front) {
    s21::array<int, 2> a = {1, 2};
    std::array<int, 2> b = {1, 2};

    EXPECT_EQ(a.front(), b.front());

    int& c = a.front();
    c = 3;
    int& d = b.front();
    d = 3;

    EXPECT_EQ(a.front(), b.front());

    s21::array<s21::array<int, 3>, 2> e = {{{1, 2, 3}, {4, 5, 6}}};
    std::array<std::array<int, 3>, 2> f = {{{1, 2, 3}, {4, 5, 6}}};

    s21::array<int, 3> g = e.front();
    std::array<int, 3> h = f.front();

    g = {7, 8, 9};
    h = {7, 8, 9};

    EXPECT_EQ(g.front(), h.front());

    const s21::array<int, 2> m = {1, 2};
    const std::array<int, 2> n = {1, 2};

    EXPECT_EQ(m.front(), n.front());
}

TEST(Array, OperatorBrackets) {
    s21::array<int, 2> a = {1, 2};
    std::array<int, 2> b = {1, 2};
    a[0] = 2;
    b[0] = 2;
    EXPECT_EQ(a[0], b[0]);

    const s21::array<int, 2> e = {1, 2};
    const std::array<int, 2> f = {1, 2};
    const int& c = e[1];
    const int& d = f[1];
    EXPECT_EQ(c, d);
}

TEST(Array, At) {
    s21::array<int, 2> a = {1, 2};
    std::array<int, 2> b = {1, 2};
    a.at(0) = 2;
    b.at(0) = 2;
    EXPECT_EQ(a.at(0), b.at(0));
    EXPECT_THROW(a.at(5), std::out_of_range);

    const s21::array<int, 2> e = {1, 2};
    const std::array<int, 2> f = {1, 2};
    const int& c = e.at(1);
    const int& d = f.at(1);
    EXPECT_EQ(c, d);
    EXPECT_THROW(e.at(5), std::out_of_range);
}

TEST(Array, Back) {
    s21::array<int, 2> a = {1, 2};
    std::array<int, 2> b = {1, 2};

    EXPECT_EQ(a.back(), b.back());

    int& c = a.back();
    c = 3;
    int& d = b.back();
    d = 3;

    EXPECT_EQ(a.back(), b.back());

    s21::array<s21::array<int, 3>, 2> e = {{{1, 2, 3}, {4, 5, 6}}};
    std::array<std::array<int, 3>, 2> f = {{{1, 2, 3}, {4, 5, 6}}};

    s21::array<int, 3> g = e.back();
    std::array<int, 3> h = f.back();

    g = {7, 8, 9};
    h = {7, 8, 9};

    EXPECT_EQ(g.back(), h.back());

    const s21::array<int, 2> m = {1, 2};
    const std::array<int, 2> n = {1, 2};

    EXPECT_EQ(m.back(), n.back());
}

TEST(Array, Data) {
    s21::array<int, 2> a = {1, 2};
    std::array<int, 2> b = {1, 2};
    EXPECT_EQ(*(a.data()), *(b.data()));

    const s21::array<int, 2> c = {1, 2};
    const std::array<int, 2> d = {1, 2};
    EXPECT_EQ(*(c.data()), *(d.data()));
}

TEST(Array, Move) {
    s21::array<int, 2> a = {1, 2};
    std::array<int, 2> b = {1, 2};
    s21::array<int, 2> c = std::move(a);
    std::array<int, 2> d = std::move(b);

    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(c.size(), b.size());
    EXPECT_EQ(c.size(), d.size());
    EXPECT_EQ(a[0], b[0]);
    EXPECT_EQ(c[0], b[0]);
    EXPECT_EQ(c[0], d[0]);
}

TEST(Array, Fill) {
    s21::array<int, 2> a = {1, 2};
    std::array<int, 2> b = {1, 2};
    a.fill(3);
    b.fill(3);
    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(a[1], b[1]);
    EXPECT_EQ(a[1], 3);
}

TEST(Array, Swap) {
    s21::array<int, 2> a = {1, 2};
    s21::array<int, 2> b = {3, 4};
    std::array<int, 2> c = {1, 2};
    std::array<int, 2> d = {3, 4};
    a.swap(b);
    c.swap(d);
    EXPECT_EQ(d[1], b[1]);
    EXPECT_EQ(a[1], c[1]);
}

TEST(Array, Iterators) {
    s21::array<int, 3> a = {1, 2, 3};
    std::array<int, 3> b = {1, 2, 3};
    EXPECT_EQ(*a.begin(), *b.begin());
    EXPECT_EQ(*a.end(), *b.end());
    EXPECT_EQ(*a.cbegin(), *b.cbegin());
    EXPECT_EQ(*a.cend(), *b.cend());
}

TEST(Stack, AllFunctionsSimple) {
    s21::stack<int, s21::vector<int>> a;
    std::stack<int, std::vector<int>> b;

    for (int i = 0; i < 100; ++i) {
        a.push(i);
        a.push(std::move(i));
        b.push(i);
        b.push(std::move(i));
        EXPECT_EQ(a.top(), b.top());
        EXPECT_EQ(a.empty(), b.empty());
        EXPECT_EQ(a.size(), b.size());
    }

    a.top() = 10;
    b.top() = 10;
    EXPECT_EQ(a.top(), b.top());

    for (int i = 0; i < 100; ++i) {
        a.pop();
        b.pop();
        EXPECT_EQ(a.top(), b.top());
        EXPECT_EQ(a.empty(), b.empty());
        EXPECT_EQ(a.size(), b.size());
    }

    s21::stack<int, s21::vector<int>> c;
    std::stack<int, std::vector<int>> d;

    for (int i = 0; i < 100; ++i) {
        c.push(i);
        d.push(i);
    }

    c = a;
    d = b;

    EXPECT_EQ(c.top(), d.top());
    EXPECT_EQ(c.empty(), d.empty());
    EXPECT_EQ(c.size(), d.size());

    c = std::move(a);
    d = std::move(b);

    EXPECT_EQ(c.top(), d.top());
    EXPECT_EQ(c.empty(), d.empty());
    EXPECT_EQ(c.size(), d.size());

    s21::stack<int, s21::vector<int>> e(c);
    std::stack<int, std::vector<int>> f(d);

    EXPECT_EQ(e.top(), f.top());
    EXPECT_EQ(e.empty(), f.empty());
    EXPECT_EQ(e.size(), f.size());

    s21::stack<int, s21::vector<int>> m(std::move(e));
    std::stack<int, std::vector<int>> n(std::move(f));

    EXPECT_EQ(m.top(), n.top());
    EXPECT_EQ(m.empty(), n.empty());
    EXPECT_EQ(m.size(), n.size());

    a.swap(m);
    b.swap(n);

    EXPECT_EQ(a.top(), b.top());
    EXPECT_EQ(a.empty(), b.empty());
    EXPECT_EQ(a.size(), b.size());

    const s21::stack<int, s21::vector<int>> p = c;
    const std::stack<int, std::vector<int>> o = d;

    EXPECT_EQ(p.top(), o.top());
}

TEST(Stack, AllFunctionsComplex) {
    s21::stack<s21::vector<int>, s21::vector<s21::vector<int>>> a;
    std::stack<std::vector<int>, std::vector<std::vector<int>>> b;

    for (int i = 0; i < 100; ++i) {
        a.push({i});
        b.push({i});
        EXPECT_EQ(a.empty(), b.empty());
        EXPECT_EQ(a.size(), b.size());
    }

    for (int i = 0; i < 100; ++i) {
        a.pop();
        b.pop();
        EXPECT_EQ(a.empty(), b.empty());
        EXPECT_EQ(a.size(), b.size());
    }

    s21::stack<s21::vector<int>, s21::vector<s21::vector<int>>> c;
    std::stack<std::vector<int>, std::vector<std::vector<int>>> d;

    for (int i = 0; i < 100; ++i) {
        c.push({i});
        d.push({i});
    }

    c = a;
    d = b;

    EXPECT_EQ(c.empty(), d.empty());
    EXPECT_EQ(c.size(), d.size());

    c = std::move(a);
    d = std::move(b);

    EXPECT_EQ(c.empty(), d.empty());
    EXPECT_EQ(c.size(), d.size());

    s21::stack<s21::vector<int>, s21::vector<s21::vector<int>>> e(c);
    std::stack<std::vector<int>, std::vector<std::vector<int>>> f(d);

    EXPECT_EQ(e.empty(), f.empty());
    EXPECT_EQ(e.size(), f.size());

    s21::stack<s21::vector<int>, s21::vector<s21::vector<int>>> m(std::move(e));
    std::stack<std::vector<int>, std::vector<std::vector<int>>> n(std::move(f));

    EXPECT_EQ(m.empty(), n.empty());
    EXPECT_EQ(m.size(), n.size());

    a.swap(m);
    b.swap(n);

    EXPECT_EQ(a.empty(), b.empty());
    EXPECT_EQ(a.size(), b.size());
}

TEST(LIST, Constructors) {
    s21::list<int> s21_1;
    std::list<int> std_1;
    EXPECT_TRUE(s21_1 == std_1);

    s21::list<int> s21_2 = {};
    std::list<int> std_2 = {};
    EXPECT_TRUE(s21_2 == std_2);

    s21::list<int> s21_3 = {1, 2, 3};
    std::list<int> std_3 = {1, 2, 3};
    EXPECT_TRUE(s21_3 == std_3);

    s21::list<int> s21_4(s21_3);
    std::list<int> std_4(std_3);
    EXPECT_TRUE(s21_4 == std_4);

    s21::list<int> s21_5 = s21_3;
    std::list<int> std_5 = std_3;
    EXPECT_TRUE(s21_5 == std_5);

    s21::list<int> s21_6 = std::move(s21_3);
    std::list<int> std_6 = std::move(std_3);
    EXPECT_TRUE(s21_6 == std_6);
    EXPECT_TRUE(s21_3 == std_3);

    s21::list<int> s21_7 = {1, 2, 3};
    std::list<int> std_7 = {1, 2, 3};
    s21::list<int> s21_8(std::move(s21_7));
    std::list<int> std_8(std::move(std_7));
    EXPECT_TRUE(s21_7 == std_7);
    EXPECT_TRUE(s21_8 == std_8);

    s21::list<int> s21_9({1, 2, 3});
    std::list<int> std_9({1, 2, 3});
    EXPECT_TRUE(s21_9 == std_9);

    s21::list<s21::list<int>> s21_10;
    std::list<std::list<int>> std_10;
    EXPECT_TRUE(s21_10 == std_10);

    s21::list<s21::list<int>> s21_11 = {};
    std::list<std::list<int>> std_11 = {};
    EXPECT_TRUE(s21_11 == std_11);

    s21::list<s21::list<int>> s21_12 = {{1, 2}, {1, 3}};
    std::list<std::list<int>> std_12 = {{1, 2}, {1, 3}};
    EXPECT_TRUE(s21_12 == std_12);

    s21::list<s21::list<int>> s21_13(s21_12);
    std::list<std::list<int>> std_13(std_12);
    EXPECT_TRUE(s21_13 == std_13);

    s21::list<s21::list<int>> s21_14(s21_12);
    std::list<std::list<int>> std_14(std_12);
    EXPECT_TRUE(s21_14 == std_14);

    s21::list<s21::list<int>> s21_15 = std::move(s21_12);
    std::list<std::list<int>> std_15 = std::move(std_12);
    EXPECT_TRUE(s21_15 == std_15);
    EXPECT_TRUE(s21_12 == std_12);

    s21::list<s21::list<int>> s21_16 = {{1, 2}, {1, 3}};
    std::list<std::list<int>> std_16 = {{1, 2}, {1, 3}};
    s21::list<s21::list<int>> s21_17(std::move(s21_16));
    std::list<std::list<int>> std_17(std::move(std_16));
    EXPECT_TRUE(s21_16 == std_16);
    EXPECT_TRUE(s21_17 == std_17);

    s21::list<s21::list<int>> s21_18({{1, 2}, {1, 3}});
    std::list<std::list<int>> std_18({{1, 2}, {1, 3}});
    EXPECT_TRUE(s21_18 == std_18);
}

TEST(LIST, FrontBack) {
    const s21::list<int> s21_1 = {1, 2, 3};
    const std::list<int> std_1 = {1, 2, 3};
    EXPECT_TRUE(s21_1.front() == std_1.front());
    EXPECT_TRUE(s21_1.back() == std_1.back());

    s21::list<int> s21_2 = {1, 2, 3};
    std::list<int> std_2 = {1, 2, 3};
    s21_2.front() = 5;
    s21_2.back() = 6;
    std_2.front() = 5;
    std_2.back() = 6;
    EXPECT_TRUE(s21_2 == std_2);

    const s21::list<s21::list<int>> s21_3 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    const std::list<std::list<int>> std_3 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_TRUE(s21_3.front() == std_3.front());
    EXPECT_TRUE(s21_3.back() == std_3.back());

    s21::list<s21::list<int>> s21_4 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    std::list<std::list<int>> std_4 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    s21_4.front() = {1, 2};
    s21_4.back() = {3, 4};
    std_4.front() = {1, 2};
    std_4.back() = {3, 4};
    EXPECT_TRUE(s21_4 == std_4);
}

TEST(LIST, EmptyMaxSize) {
    s21::list<int> s21_1 = {1, 2, 3};
    std::list<int> std_1 = {1, 2, 3};
    EXPECT_TRUE(s21_1.empty() == std_1.empty());
    EXPECT_TRUE(s21_1.max_size() == std_1.max_size());

    s21::list<int> s21_2;
    std::list<int> std_2;
    EXPECT_TRUE(s21_2.empty() == std_2.empty());

    s21::list<s21::list<int>> s21_3 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    std::list<std::list<int>> std_3 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    EXPECT_TRUE(s21_3.empty() == std_3.empty());
    EXPECT_TRUE(s21_3.max_size() == std_3.max_size());

    s21::list<s21::list<int>> s21_4;
    std::list<std::list<int>> std_4;
    EXPECT_TRUE(s21_4.empty() == std_4.empty());
}

TEST(LIST, Insert) {
    s21::list<int> s21_1 = {1, 2, 3, 4, 5};
    std::list<int> std_1 = {1, 2, 3, 4, 5};
    auto s21_it_1 = s21_1.cbegin();
    auto std_it_1 = std_1.cbegin();
    auto s21_it_2 = s21_1.insert(s21_it_1, 9);
    auto std_it_2 = std_1.insert(std_it_1, 9);
    EXPECT_TRUE(*s21_it_2 == *std_it_2);
    for (int k = 0; k < 2; ++k) {
        ++s21_it_1;
        ++std_it_1;
    }
    const int y = 8;
    auto s21_it_3 = s21_1.insert(s21_it_1, y);
    auto std_it_3 = std_1.insert(std_it_1, y);
    EXPECT_TRUE(*s21_it_3 == *std_it_3);
    s21_it_1 = s21_1.cend();
    std_it_1 = std_1.cend();
    const int x = 7;
    auto s21_it_4 = s21_1.insert(s21_it_1, x);
    auto std_it_4 = std_1.insert(std_it_1, x);
    EXPECT_TRUE(*s21_it_4 == *std_it_4);
    EXPECT_TRUE(s21_1 == std_1);
    auto s21_it_9 = s21_1.insert(s21_it_1, 2, 11);
    auto std_it_9 = std_1.insert(std_it_1, 2, 11);
    EXPECT_TRUE(*s21_it_9 == *std_it_9);
    EXPECT_TRUE(s21_1 == std_1);

    s21::list<s21::list<int>> s21_2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    std::list<std::list<int>> std_2 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    auto s21_it_5 = s21_2.cbegin();
    auto std_it_5 = std_2.cbegin();
    const s21::list<int> s21_3 = {4, 5};
    const std::list<int> std_3 = {4, 5};
    auto s21_it_6 = s21_2.insert(s21_it_5, s21_3);
    auto std_it_6 = std_2.insert(std_it_5, std_3);
    EXPECT_TRUE(*s21_it_6 == *std_it_6);
    for (int k = 0; k < 2; ++k) {
        ++s21_it_5;
        ++std_it_5;
    }
    auto s21_it_7 = s21_2.insert(s21_it_5, {1, 2});
    auto std_it_7 = std_2.insert(std_it_5, {1, 2});
    EXPECT_TRUE(*s21_it_7 == *std_it_7);
    s21_it_5 = s21_2.cend();
    std_it_5 = std_2.cend();
    auto s21_it_8 = s21_2.insert(s21_it_5, {3, 4});
    auto std_it_8 = std_2.insert(std_it_5, {3, 4});
    EXPECT_TRUE(*s21_it_8 == *std_it_8);
    EXPECT_TRUE(s21_2 == std_2);
}

TEST(LIST, OperatorEq) {
    s21::list<int> s21_1 = {1, 2, 3};
    std::list<int> std_1 = {1, 2, 3};
    s21::list<int> s21_2 = {4, 5, 6, 7};
    std::list<int> std_2 = {4, 5, 6, 7};
    s21_1 = s21_2;
    std_1 = std_2;
    EXPECT_TRUE(s21_1 == std_1);

    s21::list<int> s21_3 = {1, 2, 3};
    std::list<int> std_3 = {1, 2, 3};
    s21::list<int> s21_4 = {4, 5, 6, 7};
    std::list<int> std_4 = {4, 5, 6, 7};
    s21_3 = std::move(s21_4);
    std_3 = std::move(std_4);
    EXPECT_TRUE(s21_3 == std_3);
    EXPECT_TRUE(s21_4 == std_4);

    s21::list<int> s21_5 = {1, 2, 3};
    std::list<int> std_5 = {1, 2, 3};
    s21::list<int> s21_6 = {};
    std::list<int> std_6 = {};
    s21_5 = s21_6;
    std_5 = std_6;
    EXPECT_TRUE(s21_5 == std_5);

    s21::list<int> s21_7 = {1, 2, 3};
    std::list<int> std_7 = {1, 2, 3};
    s21::list<int> s21_8 = {};
    std::list<int> std_8 = {};
    s21_7 = std::move(s21_8);
    std_7 = std::move(std_8);
    EXPECT_TRUE(s21_7 == std_7);
    EXPECT_TRUE(s21_8 == std_8);

    s21::list<int> s21_9 = {};
    std::list<int> std_9 = {};
    s21::list<int> s21_10 = {4, 5, 6, 7};
    std::list<int> std_10 = {4, 5, 6, 7};
    s21_9 = s21_10;
    std_9 = std_10;
    EXPECT_TRUE(s21_9 == std_9);

    s21::list<int> s21_11 = {};
    std::list<int> std_11 = {};
    s21::list<int> s21_12 = {4, 5, 6, 7};
    std::list<int> std_12 = {4, 5, 6, 7};
    s21_11 = std::move(s21_12);
    std_11 = std::move(std_12);
    EXPECT_TRUE(s21_11 == std_11);
    EXPECT_TRUE(s21_12 == std_12);

    s21::list<int> s21_13 = {};
    std::list<int> std_13 = {};
    s21::list<int> s21_14 = {};
    std::list<int> std_14 = {};
    s21_13 = s21_14;
    std_13 = std_14;
    EXPECT_TRUE(s21_13 == std_13);

    s21::list<int> s21_15 = {};
    std::list<int> std_15 = {};
    s21::list<int> s21_16 = {};
    std::list<int> std_16 = {};
    s21_15 = std::move(s21_16);
    std_15 = std::move(std_16);
    EXPECT_TRUE(s21_15 == std_15);
    EXPECT_TRUE(s21_16 == std_16);

    s21::list<s21::list<int>> s21_17 = {{1}, {2}, {3}};
    std::list<std::list<int>> std_17 = {{1}, {2}, {3}};
    s21::list<s21::list<int>> s21_18 = {{1}, {2}, {3}, {4}};
    std::list<std::list<int>> std_18 = {{1}, {2}, {3}, {4}};
    s21_17 = s21_18;
    std_17 = std_18;
    EXPECT_TRUE(s21_17 == std_17);
}

TEST(LIST, Erase) {
    s21::list<int> s21_1 = {1, 2, 3, 4, 5, 6, 7};
    std::list<int> std_1 = {1, 2, 3, 4, 5, 6, 7};
    auto s21_it_1 = s21_1.cbegin();
    auto std_it_1 = std_1.cbegin();
    auto s21_it_2 = s21_1.erase(s21_it_1);
    auto std_it_2 = std_1.erase(std_it_1);
    EXPECT_TRUE(*s21_it_2 == *std_it_2);
    for (int k = 0; k < 2; ++k) {
        ++s21_it_2;
        ++std_it_2;
    }
    auto s21_it_3 = s21_1.erase(s21_it_2);
    auto std_it_3 = std_1.erase(std_it_2);
    EXPECT_TRUE(*s21_it_3 == *std_it_3);
    s21_it_1 = --s21_1.cend();
    std_it_1 = --std_1.cend();
    auto s21_it_4 = s21_1.erase(s21_it_1);
    auto std_it_4 = std_1.erase(std_it_1);
    EXPECT_TRUE(*s21_it_4 == *std_it_4);
    EXPECT_TRUE(s21_1 == std_1);

    s21::list<s21::list<int>> s21_2 = {{1, 2}, {3, 4},  {5, 6},
                                       {7, 8}, {9, 10}, {11, 12}};
    std::list<std::list<int>> std_2 = {{1, 2}, {3, 4},  {5, 6},
                                       {7, 8}, {9, 10}, {11, 12}};
    auto s21_it_5 = s21_2.cbegin();
    auto std_it_5 = std_2.cbegin();
    auto s21_it_6 = s21_2.erase(s21_it_5);
    auto std_it_6 = std_2.erase(std_it_5);
    EXPECT_TRUE(*s21_it_6 == *std_it_6);
    for (int k = 0; k < 2; ++k) {
        ++s21_it_6;
        ++std_it_6;
    }
    auto s21_it_7 = s21_2.erase(s21_it_6);
    auto std_it_7 = std_2.erase(std_it_6);
    EXPECT_TRUE(*s21_it_7 == *std_it_7);
    s21_it_5 = --s21_2.cend();
    std_it_5 = --std_2.cend();
    EXPECT_TRUE(s21_2 == std_2);

    s21_1 = {1, 2, 3, 4, 5, 6, 7};
    std_1 = {1, 2, 3, 4, 5, 6, 7};
    auto s21_it_8 = s21_1.cbegin();
    auto std_it_8 = std_1.cbegin();
    auto s21_it_9 = s21_1.cbegin();
    auto std_it_9 = std_1.cbegin();
    for (int k = 0; k < 5; ++k) {
        ++s21_it_9;
        ++std_it_9;
        ++s21_it_8;
        ++std_it_8;
    }
    s21_it_9 = s21_1.erase(s21_it_8, s21_it_9);
    std_it_9 = std_1.erase(std_it_8, std_it_9);
    EXPECT_TRUE(*s21_it_9 == *std_it_9);
    EXPECT_TRUE(s21_1 == std_1);
}

TEST(LIST, PushPop) {
    s21::list<int> s21_1 = {1, 2, 3, 4, 5, 6, 7, 8};
    std::list<int> std_1 = {1, 2, 3, 4, 5, 6, 7, 8};
    s21_1.push_front(2);
    std_1.push_front(2);
    EXPECT_TRUE(s21_1 == std_1);
    const int x = 9;
    const int y = 9;
    s21_1.push_front(x);
    std_1.push_front(y);
    EXPECT_TRUE(s21_1 == std_1);
    s21_1.push_back(3);
    std_1.push_back(3);
    EXPECT_TRUE(s21_1 == std_1);
    const int m = 5;
    const int n = 5;
    s21_1.push_front(m);
    std_1.push_front(n);
    EXPECT_TRUE(s21_1 == std_1);
    for (size_t k = 0; k < s21_1.size() / 2; ++k) {
        s21_1.pop_back();
        std_1.pop_back();
        s21_1.pop_front();
        std_1.pop_front();
    }
    EXPECT_TRUE(s21_1 == std_1);

    s21::list<s21::list<int>> s21_2 = {{1}, {2, 3}, {3, 4, 5},
                                       {0}, {-2},   {2, 55}};
    std::list<std::list<int>> std_2 = {{1}, {2, 3}, {3, 4, 5},
                                       {0}, {-2},   {2, 55}};
    s21_2.push_front({1, 2});
    std_2.push_front({1, 2});
    EXPECT_TRUE(s21_2 == std_2);
    const s21::list<int> p = {9};
    const std::list<int> o = {9};
    s21_2.push_front(p);
    std_2.push_front(o);
    EXPECT_TRUE(s21_2 == std_2);
    s21_2.push_back({8, 9});
    std_2.push_back({8, 9});
    EXPECT_TRUE(s21_2 == std_2);
    const s21::list<int> s = {5};
    const std::list<int> r = {5};
    s21_2.push_front(s);
    std_2.push_front(r);
    EXPECT_TRUE(s21_2 == std_2);
    for (size_t k = 0; k < s21_2.size() / 2; ++k) {
        s21_2.pop_back();
        std_2.pop_back();
        s21_2.pop_front();
        std_2.pop_front();
    }
    EXPECT_TRUE(s21_2 == std_2);
}

TEST(LIST, Swap) {
    s21::list<int> s21_1 = {1, 2, 3};
    std::list<int> std_1 = {1, 2, 3};
    s21::list<int> s21_2 = {4, 5, 6, 7};
    std::list<int> std_2 = {4, 5, 6, 7};
    s21_1.swap(s21_2);
    std_1.swap(std_2);
    EXPECT_TRUE(s21_1 == std_1);
    EXPECT_TRUE(s21_2 == std_2);

    s21::list<int> s21_5 = {1, 2, 3};
    std::list<int> std_5 = {1, 2, 3};
    s21::list<int> s21_6 = {};
    std::list<int> std_6 = {};
    s21_5.swap(s21_6);
    std_5.swap(std_6);
    EXPECT_TRUE(s21_5 == std_5);
    EXPECT_TRUE(s21_6 == std_6);

    s21::list<int> s21_9 = {};
    std::list<int> std_9 = {};
    s21::list<int> s21_10 = {4, 5, 6, 7};
    std::list<int> std_10 = {4, 5, 6, 7};
    s21_9.swap(s21_10);
    std_9.swap(std_10);
    EXPECT_TRUE(s21_9 == std_9);
    EXPECT_TRUE(s21_10 == std_10);

    s21::list<int> s21_13 = {};
    std::list<int> std_13 = {};
    s21::list<int> s21_14 = {};
    std::list<int> std_14 = {};
    s21_13.swap(s21_14);
    std_13.swap(std_14);
    EXPECT_TRUE(s21_13 == std_13);
    EXPECT_TRUE(s21_14 == std_14);

    s21::list<s21::list<int>> s21_17 = {{1}, {2}, {3}};
    std::list<std::list<int>> std_17 = {{1}, {2}, {3}};
    s21::list<s21::list<int>> s21_18 = {{1}, {2}, {3}, {4}};
    std::list<std::list<int>> std_18 = {{1}, {2}, {3}, {4}};
    s21_17.swap(s21_18);
    std_17.swap(std_18);
    EXPECT_TRUE(s21_17 == std_17);
    EXPECT_TRUE(s21_18 == std_18);

    s21::list<s21::list<int>> s21_19 = {};
    std::list<std::list<int>> std_19 = {};
    s21::list<s21::list<int>> s21_20 = {};
    std::list<std::list<int>> std_20 = {};
    s21_19.swap(s21_20);
    std_19.swap(std_20);
    EXPECT_TRUE(s21_19 == std_19);
    EXPECT_TRUE(std_20 == std_20);
}

TEST(LIST, Resize) {
    s21::list<int> s21_1 = {1, 2, 3};
    std::list<int> std_1 = {1, 2, 3};
    s21_1.resize(s21_1.size());
    std_1.resize(std_1.size());
    EXPECT_TRUE(s21_1 == std_1);
    s21_1.resize(5, 7);
    std_1.resize(5, 7);
    EXPECT_TRUE(s21_1 == std_1);
    s21_1.resize(2, 2);
    std_1.resize(2, 2);
    EXPECT_TRUE(s21_1 == std_1);
    s21_1.resize(0, 3);
    std_1.resize(0, 3);
    EXPECT_TRUE(s21_1 == std_1);
    s21_1.resize(0, 4);
    std_1.resize(0, 4);
    EXPECT_TRUE(s21_1 == std_1);
    s21_1.resize(10);
    std_1.resize(10);
    EXPECT_TRUE(s21_1 == std_1);

    s21::list<s21::list<int>> s21_2 = {{1}, {2}, {3}, {4}};
    std::list<std::list<int>> std_2 = {{1}, {2}, {3}, {4}};
    s21_2.resize(s21_2.size());
    std_2.resize(std_2.size());
    EXPECT_TRUE(s21_2 == std_2);
    s21_2.resize(5, {7});
    std_2.resize(5, {7});
    EXPECT_TRUE(s21_2 == std_2);
    s21_2.resize(2, {2});
    std_2.resize(2, {2});
    EXPECT_TRUE(s21_2 == std_2);
    s21_2.resize(0, {3});
    std_2.resize(0, {3});
    EXPECT_TRUE(s21_2 == std_2);
    s21_2.resize(0, {4});
    std_2.resize(0, {4});
    EXPECT_TRUE(s21_2 == std_2);
    s21_2.resize(10);
    std_2.resize(10);
    EXPECT_TRUE(s21_2 == std_2);
}

TEST(LIST, Reverse) {
    s21::list<int> s21_1 = {1, 2, 3};
    std::list<int> std_1 = {1, 2, 3};
    s21_1.reverse();
    std_1.reverse();
    EXPECT_TRUE(s21_1 == std_1);
    s21_1 = {};
    std_1 = {};
    s21_1.reverse();
    std_1.reverse();
    EXPECT_TRUE(s21_1 == std_1);
    s21_1 = {1};
    std_1 = {1};
    s21_1.reverse();
    std_1.reverse();
    EXPECT_TRUE(s21_1 == std_1);

    s21::list<s21::list<int>> s21_2 = {{1}, {2}, {3}, {4}};
    std::list<std::list<int>> std_2 = {{1}, {2}, {3}, {4}};
    s21_2.reverse();
    std_2.reverse();
    EXPECT_TRUE(s21_2 == std_2);
    s21_2 = {};
    std_2 = {};
    s21_2.reverse();
    std_2.reverse();
    EXPECT_TRUE(s21_2 == std_2);
    s21_2 = {{1}};
    std_2 = {{1}};
    s21_2.reverse();
    std_2.reverse();
    EXPECT_TRUE(s21_2 == std_2);
}

TEST(LIST, Remove) {
    s21::list<int> s21_1 = {1, 2, 3};
    std::list<int> std_1 = {1, 2, 3};
    s21_1.remove(4);
    std_1.remove(4);
    EXPECT_TRUE(s21_1 == std_1);
    s21_1.remove(2);
    std_1.remove(2);
    EXPECT_TRUE(s21_1 == std_1);
    s21_1 = {};
    std_1 = {};
    s21_1.remove(4);
    std_1.remove(4);
    EXPECT_TRUE(s21_1 == std_1);
    s21_1 = {1, 1, 1, 2, 1, 3, 1, 1, 5};
    std_1 = {1, 1, 1, 2, 1, 3, 1, 1, 5};
    s21_1.remove(1);
    std_1.remove(1);
    EXPECT_TRUE(s21_1 == std_1);

    s21::list<s21::list<int>> s21_2 = {{1}, {2}, {3}};
    std::list<std::list<int>> std_2 = {{1}, {2}, {3}};
    s21_2.remove({4});
    std_2.remove({4});
    EXPECT_TRUE(s21_2 == std_2);
    s21_2.remove({2});
    std_2.remove({2});
    EXPECT_TRUE(s21_2 == std_2);
    s21_2 = {};
    std_2 = {};
    s21_2.remove({4});
    std_2.remove({4});
    EXPECT_TRUE(s21_2 == std_2);
    s21_2 = {{1}, {1}, {1}, {2}, {1}, {3}, {1}, {1}, {5}};
    std_2 = {{1}, {1}, {1}, {2}, {1}, {3}, {1}, {1}, {5}};
    s21_2.remove({1});
    std_2.remove({1});
    EXPECT_TRUE(s21_2 == std_2);
}

TEST(LIST, Unique) {
    s21::list<int> s21_1 = {1, 2, 3};
    std::list<int> std_1 = {1, 2, 3};
    s21_1.unique();
    std_1.unique();
    EXPECT_TRUE(s21_1 == std_1);
    s21_1 = {};
    std_1 = {};
    s21_1.unique();
    std_1.unique();
    EXPECT_TRUE(s21_1 == std_1);
    s21_1 = {1, 2, 2, 3, 3, 2, 1, 1, 2};
    std_1 = {1, 2, 2, 3, 3, 2, 1, 1, 2};
    s21_1.unique();
    std_1.unique();
    EXPECT_TRUE(s21_1 == std_1);

    s21::list<s21::list<int>> s21_2 = {{1}, {2}, {3}};
    std::list<std::list<int>> std_2 = {{1}, {2}, {3}};
    s21_2.unique();
    std_2.unique();
    EXPECT_TRUE(s21_2 == std_2);
    s21_2 = {};
    std_2 = {};
    s21_2.unique();
    std_2.unique();
    EXPECT_TRUE(s21_2 == std_2);
    s21_2 = {{1}, {2}, {2}, {3}, {3}, {2}, {1}, {1}, {2}, {2}};
    std_2 = {{1}, {2}, {2}, {3}, {3}, {2}, {1}, {1}, {2}, {2}};
    s21_2.unique();
    std_2.unique();
    EXPECT_TRUE(s21_2 == std_2);
}

TEST(LIST, Splice_First) {
    s21::list<int> s21_1 = {1, 2, 3};
    std::list<int> std_1 = {1, 2, 3};
    s21::list<int> s21_2 = {4, 5, 6};
    std::list<int> std_2 = {4, 5, 6};
    s21_1.splice(s21_1.cbegin(), s21_2);
    std_1.splice(std_1.cbegin(), std_2);
    EXPECT_TRUE(s21_1 == std_1);
    EXPECT_TRUE(s21_2 == std_2);

    s21::list<int> s21_3 = {1, 2, 3};
    std::list<int> std_3 = {1, 2, 3};
    s21_1.splice(++s21_1.cbegin(), std::move(s21_3));
    std_1.splice(++std_1.cbegin(), std::move(std_3));
    EXPECT_TRUE(s21_1 == std_1);
    EXPECT_TRUE(s21_3 == std_3);

    s21::list<int> s21_4 = {1, 2, 3};
    std::list<int> std_4 = {1, 2, 3};
    s21_1.splice(s21_1.cend(), s21_4);
    std_1.splice(std_1.cend(), std_4);
    EXPECT_TRUE(s21_1 == std_1);
    EXPECT_TRUE(s21_4 == std_4);

    s21::list<int> s21_5;
    std::list<int> std_5;
    s21_1.splice(s21_1.cend(), s21_5);
    std_1.splice(std_1.cend(), std_5);
    EXPECT_TRUE(s21_1 == std_1);
    EXPECT_TRUE(s21_5 == std_5);

    s21::list<int> s21_6;
    std::list<int> std_6;
    s21_6.splice(s21_1.cend(), s21_5);
    std_6.splice(std_1.cend(), std_5);
    EXPECT_TRUE(s21_6 == std_6);
    EXPECT_TRUE(s21_5 == std_5);
}

TEST(LIST, Splice_Second) {
    s21::list<int> s21_1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::list<int> std_1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto s21_first_1 = s21_1.cbegin();
    auto std_first_1 = std_1.cbegin();
    for (int i = 0; i < 5; ++i) {
        ++s21_first_1;
        ++std_first_1;
    }
    s21_1.splice(s21_1.cbegin(), s21_1, s21_first_1);
    std_1.splice(std_1.cbegin(), std_1, std_first_1);
    EXPECT_TRUE(s21_1 == std_1);

    s21_1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std_1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    s21_first_1 = s21_1.cbegin();
    std_first_1 = std_1.cbegin();
    s21_1.splice(s21_1.cend(), s21_1, s21_first_1);
    std_1.splice(std_1.cend(), std_1, std_first_1);
    EXPECT_TRUE(s21_1 == std_1);

    s21_1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std_1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    s21_first_1 = s21_1.cbegin();
    std_first_1 = std_1.cbegin();
    for (int i = 0; i < 5; ++i) {
        ++s21_first_1;
        ++std_first_1;
    }
    s21_1.splice(s21_1.cend(), s21_1, s21_first_1);
    std_1.splice(std_1.cend(), std_1, std_first_1);
    EXPECT_TRUE(s21_1 == std_1);

    s21::list<int> s21_2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::list<int> std_2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    s21::list<int> s21_3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::list<int> std_3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto s21_first_2 = s21_3.cbegin();
    auto std_first_2 = std_3.cbegin();
    for (int i = 0; i < 5; ++i) {
        ++s21_first_2;
        ++std_first_2;
    }
    s21_2.splice(s21_2.cbegin(), std::move(s21_3), s21_first_2);
    std_2.splice(std_2.cbegin(), std::move(std_3), std_first_2);
    EXPECT_TRUE(s21_2 == std_2);
    EXPECT_TRUE(s21_3 == std_3);

    s21_2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std_2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    s21_3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std_3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    s21_first_2 = s21_3.cbegin();
    std_first_2 = std_3.cbegin();
    s21_2.splice(s21_2.cend(), s21_3, s21_first_2);
    std_2.splice(std_2.cend(), std_3, std_first_2);
    EXPECT_TRUE(s21_2 == std_2);
    EXPECT_TRUE(s21_3 == std_3);
}

TEST(LIST, Splice_Third) {
    s21::list<int> s21_1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::list<int> std_1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto s21_first_1 = s21_1.cbegin();
    auto std_first_1 = std_1.cbegin();
    auto s21_last_1 = s21_1.cbegin();
    auto std_last_1 = std_1.cbegin();
    for (int i = 0; i < 5; ++i) {
        ++s21_last_1;
        ++std_last_1;

        if (i < 2) {
            ++s21_first_1;
            ++std_first_1;
        }
    }
    s21_1.splice(s21_1.cbegin(), s21_1, s21_first_1, s21_last_1);
    std_1.splice(std_1.cbegin(), std_1, std_first_1, std_last_1);
    EXPECT_TRUE(s21_1 == std_1);

    s21_1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std_1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    s21_first_1 = s21_1.cbegin();
    std_first_1 = std_1.cbegin();
    s21_last_1 = s21_1.cend();
    std_last_1 = std_1.cend();
    s21_1.splice(s21_1.cend(), s21_1, s21_first_1, s21_last_1);
    std_1.splice(std_1.cend(), std_1, std_first_1, std_last_1);
    EXPECT_TRUE(s21_1 == std_1);

    s21_1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std_1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    s21_first_1 = s21_1.cbegin();
    std_first_1 = std_1.cbegin();
    s21_last_1 = s21_1.cbegin();
    std_last_1 = std_1.cbegin();
    for (int i = 0; i < 5; ++i) {
        ++s21_last_1;
        ++std_last_1;

        if (i < 2) {
            ++s21_first_1;
            ++std_first_1;
        }
    }
    s21_1.splice(s21_1.cend(), s21_1, s21_first_1, s21_last_1);
    std_1.splice(std_1.cend(), std_1, std_first_1, std_last_1);
    EXPECT_TRUE(s21_1 == std_1);

    s21::list<int> s21_2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::list<int> std_2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    s21::list<int> s21_3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::list<int> std_3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto s21_first_2 = s21_3.cbegin();
    auto std_first_2 = std_3.cbegin();
    auto s21_last_2 = s21_3.cbegin();
    auto std_last_2 = std_3.cbegin();
    for (int i = 0; i < 5; ++i) {
        ++s21_last_2;
        ++std_last_2;

        if (i < 2) {
            ++s21_first_2;
            ++std_first_2;
        }
    }
    s21_2.splice(s21_2.cbegin(), std::move(s21_3), s21_first_2, s21_last_2);
    std_2.splice(std_2.cbegin(), std::move(std_3), std_first_2, std_last_2);
    EXPECT_TRUE(s21_2 == std_2);
    EXPECT_TRUE(s21_3 == std_3);

    s21_2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std_2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    s21_3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std_3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    s21_first_2 = s21_3.cbegin();
    std_first_2 = std_3.cbegin();
    s21_last_2 = s21_3.cend();
    std_last_2 = std_3.cend();
    s21_2.splice(s21_2.cend(), s21_3, s21_first_2, s21_last_2);
    std_2.splice(std_2.cend(), std_3, std_first_2, std_last_2);
    EXPECT_TRUE(s21_2 == std_2);
    EXPECT_TRUE(s21_3 == std_3);
}

TEST(LIST, Merge) {
    s21::list<int> s21_1;
    std::list<int> std_1;
    s21::list<int> s21_2 = {1, 2, 3};
    std::list<int> std_2 = {1, 2, 3};
    s21_1.merge(s21_2);
    std_1.merge(std_2);
    EXPECT_TRUE(s21_1 == std_1);
    EXPECT_TRUE(s21_2 == std_2);

    s21::list<int> s21_3;
    std::list<int> std_3;
    s21_3.merge(s21_2);
    std_3.merge(std_2);
    EXPECT_TRUE(s21_3 == std_3);
    EXPECT_TRUE(s21_2 == std_2);

    s21_1 = {1, 3, 3, 5, 9};
    std_1 = {1, 3, 3, 5, 9};
    s21_2 = {-10, -3, 2, 3, 4, 4, 7, 8, 10, 20};
    std_2 = {-10, -3, 2, 3, 4, 4, 7, 8, 10, 20};
    s21_1.merge(std::move(s21_2));
    std_1.merge(std::move(std_2));
    EXPECT_TRUE(s21_1 == std_1);
    EXPECT_TRUE(s21_2 == std_2);
}

TEST(LIST, Sort) {
    s21::list<int> s21_1 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    std::list<int> std_1 = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    s21_1.sort();
    std_1.sort();
    EXPECT_TRUE(s21_1 == std_1);

    s21_1 = {2, 1};
    std_1 = {2, 1};
    s21_1.sort();
    std_1.sort();
    EXPECT_TRUE(s21_1 == std_1);

    s21_1 = {1};
    std_1 = {1};
    s21_1.sort();
    std_1.sort();
    EXPECT_TRUE(s21_1 == std_1);

    s21_1 = {};
    std_1 = {};
    s21_1.sort();
    std_1.sort();
    EXPECT_TRUE(s21_1 == std_1);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
