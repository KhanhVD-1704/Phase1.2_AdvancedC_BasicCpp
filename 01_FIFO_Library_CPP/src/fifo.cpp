#include "fifo.hpp"
#include "algorithm"
#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace fifo_library
{

FIFO::FIFO(std::size_t capacity)
    : buffer_(capacity)
{
    if (capacity == 0)
    {
        throw std::invalid_argument("FIFO capacity must be greater than zero.");
    }
}

std::size_t FIFO::Capacity() const
{
    return buffer_.size();
}

std::size_t FIFO::Size() const
{
    return count_;
}

bool FIFO::IsEmpty() const
{
    return count_ == 0;
}

bool FIFO::IsFull() const
{
    return count_ == Capacity();
}

void FIFO::Clear()
{
    std::fill(buffer_.begin(), buffer_.end(), 0U);
    head_ = 0;
    tail_ = 0;
    count_ = 0;
}

bool FIFO::Push(uint8_t data)
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

bool FIFO::Pop(uint8_t& data)
{
    if (IsEmpty())
    {
        return false;
    }

    data = buffer_[tail_];

    buffer_[tail_] = 0U;
    tail_ = (tail_ + 1) % Capacity();

    --count_;

    return true;
}



void FIFO::DebugPrint() const
{
    std::cout << "\n========== FIFO DEBUG ==========\n";

    std::cout << "Capacity : " << Capacity() << '\n';
    std::cout << "Size     : " << Size() << '\n';
    std::cout << "Head     : " << head_ << '\n';
    std::cout << "Tail     : " << tail_ << '\n';

    std::cout << "\nIndex    : ";
    for (std::size_t i = 0; i < Capacity(); ++i)
    {
        std::cout << std::setw(4) << i;
    }

    std::cout << "\nData     : ";
    for (std::size_t i = 0; i < Capacity(); ++i)
    {
        std::cout << std::setw(4)
                  << static_cast<int>(buffer_[i]);
    }

    std::cout << "\n";

    std::cout << "Head --> " << head_ << '\n';
    std::cout << "Tail --> " << tail_ << '\n';

    std::cout << "===============================\n";
}

} // namespace fifo_library