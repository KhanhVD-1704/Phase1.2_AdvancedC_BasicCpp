# FIFO Template Library (C++)

Đây là phần tiếp theo của bài FIFO cơ bản. Ở project trước, FIFO chỉ lưu được `uint8_t`. Project này giữ nguyên cách hoạt động của FIFO, chỉ thay phần kiểu dữ liệu cố định bằng C++ template để có thể dùng lại với nhiều kiểu khác nhau.

Ví dụ, thay vì phải có nhiều class cho số nguyên, số thực hay chuỗi, ta chỉ cần một class:

```cpp
template<typename T>
class FIFO;
```

Sau đó chọn kiểu dữ liệu khi khai báo FIFO.

## FIFO thường và FIFO Template

| FIFO ở project trước | FIFO ở project này |
|---|---|
| Chỉ lưu `uint8_t` | Lưu được kiểu `T` do người dùng chọn |
| `std::vector<uint8_t>` | `std::vector<T>` |
| `Push(uint8_t data)` | `Push(const T& data)` |
| `Pop(uint8_t& data)` | `Pop(T& data)` |
| Circular buffer | Circular buffer, không thay đổi thuật toán |

Nhờ template, compiler sẽ tạo đúng phiên bản FIFO cần dùng. Ví dụ `FIFO<int>` và `FIFO<std::string>` là hai phiên bản khác nhau của cùng một class template, vẫn đảm bảo kiểm tra kiểu dữ liệu khi biên dịch.

## Cấu trúc project

```text
02_FIFO_Template_CPP/
├── include/
│   └── fifo.hpp
├── src/
│   └── fifo.cpp
├── tests/
│   ├── unit_test_fifo.hpp
│   └── unit_test_fifo.cpp
├── main.cpp
├── Makefile
├── README.md
└── output.md
```

Phần cài đặt `FIFO<T>` nằm trong `include/fifo.hpp`. Đây là cách làm thông thường với template trong C++: khi dùng `FIFO<T>`, compiler cần thấy cả phần khai báo lẫn phần cài đặt để tạo code cho kiểu `T` đó. Thư mục `src` vẫn được giữ lại để cấu trúc project nhất quán với phần trước.

## Các hàm có sẵn

| Hàm | Dùng để làm gì? |
|---|---|
| `FIFO<T>(capacity)` | Tạo FIFO có dung lượng cố định. Dung lượng 0 sẽ ném `std::invalid_argument`. |
| `Push(const T& data)` | Thêm dữ liệu vào cuối hàng đợi. Trả `false` nếu FIFO đã đầy. |
| `Pop(T& data)` | Lấy phần tử vào trước ra trước. Trả `false` nếu FIFO rỗng. |
| `IsEmpty()` / `IsFull()` | Kiểm tra FIFO đang rỗng hay đầy. |
| `Size()` / `Capacity()` | Lấy số phần tử hiện có và dung lượng tối đa. |
| `Clear()` | Xóa dữ liệu đang có, đưa FIFO về trạng thái ban đầu. |
| `DebugPrint()` | In trạng thái buffer để tiện quan sát khi học và debug. |

## Ví dụ sử dụng

```cpp
#include "fifo.hpp"
#include <string>

fifo_library::FIFO<int> numbers(3);
numbers.Push(10);
numbers.Push(20);

int value = 0;
if (numbers.Pop(value))
{
    // value = 10
}

fifo_library::FIFO<float> temperatures(2);
temperatures.Push(36.5F);

fifo_library::FIFO<char> commands(2);
commands.Push('A');

fifo_library::FIFO<std::string> messages(2);
messages.Push("ready");
```

`DebugPrint()` cần kiểu `T` có thể in bằng `std::cout`. Các kiểu đang được test trong project (`int`, `float`, `char`, `std::string`) đều dùng được.

## Unit test

Project vẫn có các bài test của FIFO cơ bản: khởi tạo, Push, Pop, Clear, wrap-around và DebugPrint. Ngoài ra có test cho trường hợp tạo FIFO với dung lượng bằng 0.

Các test được chạy với:

- `FIFO<int>`
- `FIFO<float>`
- `FIFO<char>`
- `FIFO<std::string>`

Kết quả chạy test được ghi trong [output.md](output.md).

## Build và chạy

Mở terminal tại thư mục `02_FIFO_Template_CPP` và build project:

```bash
make
```

Chạy unit test:

```bash
make test
```

Xóa kết quả build:

```bash
make clean
```

File `app` đã nằm trong `.gitignore`, nên không cần đưa file này lên GitHub.
