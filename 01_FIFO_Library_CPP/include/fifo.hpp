// Header Guard
#ifndef FIFO_HPP
#define FIFO_HPP

// Standard Library
#include <cstddef>
#include <cstdint>
#include <vector>

namespace fifo_library
{

class FIFO
{
public:

    explicit FIFO(std::size_t capacity);

    bool Push(uint8_t data);

    bool Pop(uint8_t& data);

    bool IsEmpty() const;

    bool IsFull() const;

    std::size_t Size() const;

    std::size_t Capacity() const;

    void Clear();

    void DebugPrint() const;

private:
    // Storage buffer
    std::vector<uint8_t> buffer_;

    // Circular buffer write index
    std::size_t head_{0};

    // Circular buffer read index
    std::size_t tail_{0};

    // Number of stored elements
    std::size_t count_{0};
};

} // namespace fifo_library

#endif // FIFO_HPP