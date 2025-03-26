#pragma once

#include <cstddef>

template <typename T>
struct Query {
    bool type_;
    size_t left_border_;
    size_t right_border_;
    size_t position_;
    T value_;
};