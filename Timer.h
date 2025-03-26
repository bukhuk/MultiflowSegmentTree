#pragma once

#include <chrono>

class Timer {
   public:

    Timer() = default;
    Timer(const std::chrono::time_point<std::chrono::system_clock>& start) : start_{start} {}

    Timer(const Timer& other) : start_{other.start_} {}
    Timer operator=(const Timer& other) {
        start_ = other.start_;
        return *this;
    }

    void SetStart() {
        start_ = std::chrono::system_clock::now();
    }

    double GetTime() {
        std::chrono::time_point<std::chrono::system_clock> time_now = std::chrono::system_clock::now();
        return static_cast<double>(
                std::chrono::duration_cast<std::chrono::milliseconds>(time_now - start_).count()) / static_cast<double>(1000);
    }

   private:

    std::chrono::time_point<std::chrono::system_clock> start_ = std::chrono::system_clock::now();
};