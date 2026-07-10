# FIFO Library (C++)

FIFO Library là một thư viện được xây dựng bằng **C++17** nhằm thực hành các kiến thức về lập trình hướng đối tượng, STL (`std::vector`), Circular Buffer và Unit Testing.

Thư viện cài đặt cấu trúc dữ liệu **First-In First-Out (FIFO)** với kích thước cố định. Thuật toán **Circular Buffer** được sử dụng để đảm bảo các thao tác thêm (`Push`) và lấy dữ liệu (`Pop`) luôn có độ phức tạp **O(1)** mà không cần dịch chuyển dữ liệu trong bộ nhớ.

---

# Features

- Fixed-size FIFO Queue
- Push dữ liệu vào FIFO
- Pop dữ liệu khỏi FIFO
- Kiểm tra FIFO rỗng (`IsEmpty`)
- Kiểm tra FIFO đầy (`IsFull`)
- Lấy kích thước hiện tại (`Size`)
- Lấy dung lượng tối đa (`Capacity`)
- Reset FIFO (`Clear`)
- Debug trạng thái FIFO (`DebugPrint`)
- Unit Test
- Memory Leak Check bằng Valgrind

---

# Technologies

- C++17
- Object-Oriented Programming
- STL (`std::vector`)
- Circular Buffer
- Exception Handling
- Modular Programming
- Unit Testing (`assert`)
- GCC
- Valgrind

---

# Project Structure

```text
01_FIFO_Library_CPP/
├── include/
│   └── fifo.hpp
│
├── src/
│   └── fifo.cpp
│
├── tests/
│   ├── unit_test_fifo.hpp
│   └── unit_test_fifo.cpp
│
├── main.cpp
└── README.md
```

---

# Software Architecture

```text
                +-------------+
                |  main.cpp   |
                +------+------+
                       |
                       ▼
             +-----------------+
             | Unit Test Suite |
             +--------+--------+
                      |
          +-----------+-----------+
          |                       |
          ▼                       ▼
      FIFO API              DebugPrint()
          |
          ▼
    Circular Buffer
          |
          ▼
     std::vector
```

Kiến trúc chương trình được chia thành các module độc lập.

- **main.cpp**: Điểm bắt đầu chương trình.
- **Unit Test Suite**: Kiểm thử toàn bộ API của FIFO.
- **FIFO API**: Cung cấp các thao tác Push, Pop, Clear,...
- **Circular Buffer**: Cài đặt thuật toán FIFO.
- **std::vector**: Quản lý bộ nhớ theo cơ chế RAII.

---

# Circular Buffer Design

FIFO sử dụng **Circular Buffer** để tránh việc phải dịch chuyển dữ liệu sau mỗi lần `Pop()`.

```text
             Circular Buffer

        +-----+-----+-----+-----+-----+
Index : |  0  |  1  |  2  |  3  |  4  |
        +-----+-----+-----+-----+-----+
Data  : | 10  | 20  | 30  |     |     |
        +-----+-----+-----+-----+-----+
            ↑                 ↑
          Tail              Head
```

Các thành phần chính:

| Thành phần | Ý nghĩa |
|------------|----------|
| `buffer_` | Bộ nhớ lưu dữ liệu |
| `head_` | Vị trí sẽ ghi dữ liệu tiếp theo |
| `tail_` | Vị trí sẽ đọc dữ liệu tiếp theo |
| `count_` | Số phần tử hiện có trong FIFO |

Sau mỗi lần `Push()` hoặc `Pop()`, `head_` và `tail_` được cập nhật bằng phép chia dư (`%`) để tạo thành cơ chế **Wrap Around**.

Nhờ vậy:

- Không cần dịch chuyển dữ liệu.
- Giảm chi phí xử lý.
- Push và Pop luôn có độ phức tạp **O(1)**.

---

# API Overview

| API | Mô tả |
|------|--------|
| `FIFO(capacity)` | Khởi tạo FIFO |
| `Push(data)` | Thêm dữ liệu |
| `Pop(data)` | Lấy dữ liệu |
| `IsEmpty()` | Kiểm tra FIFO rỗng |
| `IsFull()` | Kiểm tra FIFO đầy |
| `Size()` | Lấy số phần tử hiện có |
| `Capacity()` | Lấy dung lượng tối đa |
| `Clear()` | Đặt lại FIFO |
| `DebugPrint()` | Hiển thị trạng thái FIFO |

---

# Unit Test

Project sử dụng `assert` để kiểm thử toàn bộ các chức năng chính.

| Test Case | Nội dung kiểm thử | Kết quả mong đợi |
|------------|------------------|------------------|
| **TestConstructor** | Khởi tạo FIFO | FIFO được tạo đúng dung lượng |
| **TestPush** | Thêm dữ liệu | Push thành công, FIFO đầy sẽ trả về `false` |
| **TestPop** | Lấy dữ liệu | Dữ liệu lấy ra đúng thứ tự FIFO |
| **TestClear** | Reset FIFO | FIFO trở về trạng thái rỗng |
| **TestWrapAround** | Kiểm tra Circular Buffer | FIFO vẫn hoạt động đúng sau khi Wrap Around |

Sau khi thực thi chương trình:

```text
========== FIFO UNIT TEST ==========

[PASS] TestConstructor
[PASS] TestPush
[PASS] TestPop
[PASS] TestClear
[PASS] TestWrapAround

====================================
 ALL UNIT TESTS PASSED
====================================
```

Điều này chứng minh toàn bộ các API của thư viện hoạt động đúng theo thiết kế.

---

# Memory Leak Check

Kiểm tra chương trình bằng **Valgrind**.

```bash
valgrind --leak-check=full ./app
```

Kết quả:

```text
HEAP SUMMARY:

All heap blocks were freed -- no leaks are possible

ERROR SUMMARY: 0 errors
```

Điều này xác nhận:

- Không xảy ra Memory Leak.
- Không có Memory Error.
- Toàn bộ bộ nhớ được giải phóng đúng cách.

---

# Build & Run

## Clone Project

```bash
git clone https://github.com/KhanhVD-1704/01_FIFO_Library_CPP.git
```

```bash
cd 01_FIFO_Library_CPP
```

## Build

```bash
g++ -std=c++17 \
main.cpp \
tests/unit_test_fifo.cpp \
src/fifo.cpp \
-Iinclude \
-Itests \
-o app
```

## Run

```bash
./app
```

---
