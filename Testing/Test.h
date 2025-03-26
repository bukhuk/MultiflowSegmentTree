#pragma once

#include <cstddef>
#include <vector>

#include "Query.h"

template <typename T>
struct Test {
   public:

    Test() = default;

    Test(const size_t& array_size, const size_t& number_of_query, const std::vector<T>& array, const std::vector<T>& query) :
        array_size_{array_size},
        number_of_query_{number_of_query},
        array_{array},
        query_{query} {
    }

    size_t Size() const {
        return array_size_;
    }

    size_t NumberOfQuery() {
        return number_of_query_;
    }

   private:

    size_t array_size_;
    size_t number_of_query_;

    std::vector<T> array_;
    std::vector<Query<T>> query_;
};