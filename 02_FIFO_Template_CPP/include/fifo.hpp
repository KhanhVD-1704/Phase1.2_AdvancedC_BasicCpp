#ifndef FIFO_HPP
#define FIFO_HPP

#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace fifo_library
{

template<typename T>
class FIFO
{
public:
    explicit FIFO(std::size_t capacity)
        : buffer_(capacity)
    {
        if (capacity == 0)
        {
            throw std::invalid_argument("FIFO capacity must be greater than zero.");
        }
    }

    bool Push(const T& data)
    {
        if (IsFull())
        {
            return false;
        }

        buffer_[head_] = data;
        head_ = (head_ + 1) % Capacity();
        ++count_;

        return true;
    }

    bool Pop(T& data)
    {
        if (IsEmpty())
        {
            return false;
        }

        data = buffer_[tail_];
        buffer_[tail_] = T{};
        tail_ = (tail_ + 1) % Capacity();
        --count_;

        return true;
    }

    bool IsEmpty() const
    {
        return count_ == 0;
    }

    bool IsFull() const
    {
        return count_ == Capacity();
    }

    std::size_t Size() const
    {
        return count_;
    }

    std::size_t Capacity() const
    {
        return buffer_.size();
    }

    void Clear()
    {
        std::fill(buffer_.begin(), buffer_.end(), T{});
        head_ = 0;
        tail_ = 0;
        count_ = 0;
    }

    void DebugPrint() const
    {
        std::cout << "\n========== FIFO DEBUG ==========" << '\n';
        std::cout << "Capacity : " << Capacity() << '\n';
        std::cout << "Size     : " << Size() << '\n';
        std::cout << "Head     : " << head_ << '\n';
        std::cout << "Tail     : " << tail_ << '\n';

        std::cout << "\nIndex    : ";
        for (std::size_t i = 0; i < Capacity(); ++i)
        {
            std::cout << std::setw(12) << i;
        }

        std::cout << "\nData     : ";
        for (std::size_t i = 0; i < Capacity(); ++i)
        {
            std::cout << std::setw(12) << buffer_[i];
        }

        std::cout << "\nHead --> " << head_ << '\n';
        std::cout << "Tail --> " << tail_ << '\n';
        std::cout << "===============================\n";
    }

private:
    std::vector<T> buffer_;
    std::size_t head_{0};
    std::size_t tail_{0};
    std::size_t count_{0};
};

} // namespace fifo_library

#endif // FIFO_HPP
