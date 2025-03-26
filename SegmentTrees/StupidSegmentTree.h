#pragma once

#include <cstddef>
#include <iterator>
#include <algorithm>
#include <vector>
#include <initializer_list>

template <typename T>
class StupidSegmentTree {
public:
    StupidSegmentTree() = default;
    explicit StupidSegmentTree(const size_t& array_size, const T value = 0) :
            array_size_{array_size},
            array_{new T[array_size_]} {

        std::fill(array_, std::next(array_, array_size_), value);
    }
    explicit StupidSegmentTree(const std::vector<T>& init_vector) :
            array_size_{init_vector.size()},
            array_{new T[array_size_]} {

        for (size_t i = 0; i < array_size_; i++) {
            *std::next(array_, i) = init_vector[i];
        }
    }
    StupidSegmentTree(const std::initializer_list<T>& init_list) :
            array_size_{init_list.size()},
            array_{new T[array_size_]} {

        for (size_t i = 0; i < array_size_; i++) {
            *std::next(array_, i) = init_list[i];
        }
    }

    void Update(const size_t& position, const T& value) {
        *std::next(array_, position) = value;
    }

    T GetSegment(const size_t& need_left_border, const size_t& need_right_border) {
        T result = 0;
        for (size_t i = need_left_border; i <= need_right_border; i++) {
            result += *std::next(array_, i);
        }
        return result;
    }

private:

    size_t array_size_ = 0;
    T* array_ = nullptr;
};