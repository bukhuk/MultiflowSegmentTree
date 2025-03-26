#pragma once

#include <random>
#include <vector>
#include <limits>

#include "Test.h"
#include "Query.h"

std::mt19937 rnd(228);

template <typename T>
Test<T> GenerateTest(const size_t& array_size, const size_t& number_of_query) {
    std::vector<T> array(array_size);
    for (auto& element : array) {
        element = static_cast<T>(rnd() % (std::numeric_limits<T>::max() / array_size));
    }

    std::vector<Query<T>> query(number_of_query);
    for (auto& element : query) {
        element.type_ = static_cast<bool>(rnd() % 2);
        if (element.type_ == false) {
            element.position_ = static_cast<size_t>(rnd() % array_size);
            element.value_ = static_cast<T>(rnd() % (std::numeric_limits<T>::max() / array_size));
        } else {
            element.left_border_ = array_size - 1;
            element.right_border_ = 0;
            for (size_t i = 0; i < 2; i++) {
                element.left_border_ = std::min(element.left_border_, static_cast<size_t>(rnd() % array_size));
                element.right_border_ = std::max(element.right_border_, static_cast<size_t>(rnd() % array_size));
            }
            if (element.left_border_ > element.right_border_) {
                std::swap(element.left_border_, element.right_border_);
            }
        }
    }

    return Test(array_size, number_of_query, array, query);
}