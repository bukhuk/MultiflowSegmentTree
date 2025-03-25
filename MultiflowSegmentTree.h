#pragma once

#include <cstddef>
#include <iterator>
#include <algorithm>
#include <vector>
#include <initializer_list>

#include <thread>

template <typename T>
class MultiflowSegmentTree {
public:
    MultiflowSegmentTree() {}
    MultiflowSegmentTree(size_t array_size, T value = 0) :
            array_size_{array_size},
            array_{new T[array_size_]},
            tree_data_{new T[array_size_ << 2]} {

        std::fill(array_, std::next(array_, array_size_), value);
        build(1, 0, array_size_ - 1);
    }
    MultiflowSegmentTree(std::vector<T> init_vector) :
            array_size_{init_vector.size()},
            array_{new T[array_size_]},
            tree_data_{new T[array_size_ << 2]} {

        for (size_t i = 0; i < array_size_; i++) {
            *std::next(array_, i) = init_vector[i];
        }
        build(1, 0, array_size_ - 1);
    }
    MultiflowSegmentTree(std::initializer_list<T> init_list) :
            array_size_{init_list.size()},
            array_{new T[array_size_]},
            tree_data_{new T[array_size_ << 2]} {

        for (size_t i = 0; i < array_size_; i++) {
            *std::next(array_, i) = init_list[i];
        }
        build(1, 0, array_size_ - 1);
    }

    void Update(size_t position, size_t value) {
        Update(1, 0, array_size_ - 1, position, value);
    }

    T GetSegment(size_t need_left_border, size_t need_right_border) {
        return GetSegment(1, 0, array_size_ - 1, need_left_border, need_right_border);
    }

private:

    void build(size_t vertex, size_t left_border, size_t right_border) {
        if (left_border == right_border) {
            *std::next(tree_data_, vertex) = *std::next(array_, left_border);
            return;
        }
        size_t median_border = (left_border + right_border) >> 1;
        if (vertex == 1) {
            std::thread tread_for_left_subtree([&]() {
                build(vertex << 1, left_border, median_border);
            });
            build(vertex << 1 | 1, median_border + 1, right_border);
            tread_for_left_subtree.join();
        } else {
            build(vertex << 1, left_border, median_border);
            build(vertex << 1 | 1, median_border + 1, right_border);
        }
        *std::next(tree_data_, vertex) =
                *std::next(tree_data_, vertex << 1) +
                *std::next(tree_data_, vertex << 1 | 1);
    }

    void Update(size_t vertex, size_t left_border, size_t right_border, size_t position, size_t value) {
        if (left_border == right_border) {
            *std::next(array_, left_border) = value;
            *std::next(tree_data_, vertex) = value;
            return;
        }
        size_t median_border = (left_border + right_border) >> 1;
        if (position <= median_border) {
            Update(vertex << 1, left_border, median_border, position, value);
        } else {
            Update(vertex << 1 | 1, median_border + 1, right_border, position, value);
        }
        *std::next(tree_data_, vertex) =
                *std::next(tree_data_, vertex << 1) +
                *std::next(tree_data_, vertex << 1 | 1);
    }

    T GetSegment(size_t vertex, size_t left_border, size_t right_border,
                 size_t need_left_border, size_t need_right_border) {
        if (need_left_border > need_right_border) {
            return 0;
        }
        if (need_left_border == left_border && need_right_border == right_border) {
            return *std::next(tree_data_, vertex);
        }
        size_t median_border = (left_border + right_border) >> 1;

        if (vertex == 1) {
            T result_for_left_subtree = 0;
            std::thread thread_for_left_subtree([&]() {
                result_for_left_subtree = GetSegment(vertex << 1, left_border, median_border,
                                                     need_left_border, std::min(median_border, need_right_border));
            });
            T result_for_right_subtree = GetSegment(vertex << 1 | 1, median_border + 1, right_border,
                                  std::max(median_border + 1, need_left_border), need_right_border);
            thread_for_left_subtree.join();
            return result_for_left_subtree + result_for_right_subtree;
        } else {
            return
                GetSegment(vertex << 1, left_border, median_border,
                           need_left_border, std::min(median_border, need_right_border)) +
                GetSegment(vertex << 1 | 1, median_border + 1, right_border,
                           std::max(median_border + 1, need_left_border), need_right_border);
        }
    }

    size_t array_size_;
    T* array_;
    T* tree_data_;
};