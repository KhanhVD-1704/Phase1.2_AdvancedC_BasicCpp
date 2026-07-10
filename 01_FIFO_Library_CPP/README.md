# FIFO Library (C++)

Project **FIFO Library** được xây dựng bằng ngôn ngữ **C++17** nhằm thực hành các kiến thức nền tảng về lập trình hướng đối tượng (Object-Oriented Programming), quản lý bộ nhớ bằng STL (`std::vector`), Circular Buffer và Unit Testing.

Thư viện cung cấp cấu trúc dữ liệu **First-In First-Out (FIFO)** với kích thước cố định. FIFO được triển khai bằng thuật toán **Circular Buffer**, giúp các thao tác thêm (`Push`) và lấy dữ liệu (`Pop`) đều có độ phức tạp **O(1)** mà không cần dịch chuyển dữ liệu trong bộ nhớ.

---

# Chức năng

- Khởi tạo FIFO với dung lượng cố định.
- Thêm dữ liệu vào FIFO (`Push`).
- Lấy dữ liệu ra khỏi FIFO (`Pop`).
- Kiểm tra FIFO rỗng (`IsEmpty`).
- Kiểm tra FIFO đầy (`IsFull`).
- Lấy số phần tử hiện tại (`Size`).
- Lấy dung lượng tối đa (`Capacity`).
- Xóa toàn bộ dữ liệu logic trong FIFO (`Clear`).
- Hiển thị trạng thái hiện tại của FIFO (`DebugPrint`).
- Kiểm thử các chức năng bằng Unit Test.

---

# Kiến thức áp dụng

- C++17
- Header Guard
- Namespace
- Class & Object
- Constructor
- Reference
- Const Correctness
- Exception Handling (`std::invalid_argument`)
- STL (`std::vector`)
- Circular Buffer
- Modular Programming
- Unit Testing (`assert`)
- GCC

---

# Cấu trúc project

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

# Kiến trúc chương trình

Project được chia thành các module độc lập nhằm tăng khả năng bảo trì và mở rộng.

```text
                 +-------------+
                 |  main.cpp   |
                 +------+------+
                        |
                        ▼
               +------------------+
               | RunAllTests()    |
               +------------------+
                        |
        +---------------+---------------+
        |               |               |
        ▼               ▼               ▼
 Constructor         Push/Pop      Wrap Around
        |               |               |
        +---------------+---------------+
                        |
                        ▼
                 FIFO Library
                        |
                        ▼
                    fifo.cpp
```

---

# Cấu trúc dữ liệu

FIFO được xây dựng dựa trên **Circular Buffer**.

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

Trong đó:

- **Head (`head_`)**: vị trí sẽ ghi dữ liệu tiếp theo.
- **Tail (`tail_`)**: vị trí sẽ đọc dữ liệu tiếp theo.
- **Count (`count_`)**: số phần tử hiện có trong FIFO.

Sau mỗi lần `Push()` hoặc `Pop()`, `head_` và `tail_` được cập nhật bằng phép chia dư (`%`) để tạo thành cơ chế quay vòng (**Wrap Around**).

Nhờ vậy, FIFO không cần dịch chuyển dữ liệu trong bộ nhớ sau mỗi lần `Pop()`, giúp các thao tác luôn đạt độ phức tạp **O(1)**.

---

# Luồng hoạt động

```text
                main()
                   │
                   ▼
             RunAllTests()
                   │
                   ▼
        Thực thi từng Test Case
                   │
        ┌──────────┼──────────┐
        ▼          ▼          ▼
 Constructor     Push        Pop
        │          │          │
        └──────────┼──────────┘
                   ▼
             Wrap Around
                   │
                   ▼
             DebugPrint()
                   │
                   ▼
          Hiển thị kết quả
```

---

# Cách chương trình hoạt động

1. Chương trình bắt đầu từ `main()` và gọi `RunAllTests()`.
2. `RunAllTests()` lần lượt thực thi các hàm kiểm thử của thư viện FIFO.
3. Mỗi test khởi tạo một đối tượng `FIFO` độc lập để đảm bảo các trường hợp kiểm thử không ảnh hưởng lẫn nhau.
4. Các thao tác `Push()` và `Pop()` được thực hiện trên Circular Buffer bằng cách cập nhật chỉ số `head_` và `tail_`.
5. Sau mỗi thao tác quan trọng, `DebugPrint()` được sử dụng để hiển thị trạng thái hiện tại của FIFO, giúp quan sát trực quan cách Circular Buffer hoạt động.
6. Các điều kiện được kiểm tra bằng `assert`. Nếu tất cả điều kiện đều đúng, chương trình hiển thị `[PASS]`; nếu có điều kiện sai, chương trình sẽ dừng ngay tại vị trí kiểm thử thất bại.

---

# Các API chính

## `FIFO(std::size_t capacity)`

Khởi tạo một FIFO với dung lượng cố định.

**Tham số**

- `capacity`: Dung lượng tối đa của FIFO.

**Ngoại lệ**

- `std::invalid_argument` nếu `capacity == 0`.

---

## `bool Push(uint8_t data)`

Thêm một phần tử vào FIFO.

**Tham số**

- `data`: Giá trị cần thêm.

**Giá trị trả về**

- `true`: Thêm thành công.
- `false`: FIFO đã đầy.

---

## `bool Pop(uint8_t& data)`

Lấy phần tử đầu tiên ra khỏi FIFO.

**Tham số**

- `data`: Biến nhận dữ liệu.

**Giá trị trả về**

- `true`: Lấy dữ liệu thành công.
- `false`: FIFO rỗng.

---

## `bool IsEmpty()`

Kiểm tra FIFO có rỗng hay không.

**Giá trị trả về**

- `true`: FIFO rỗng.
- `false`: FIFO còn dữ liệu.

---

## `bool IsFull()`

Kiểm tra FIFO đã đầy hay chưa.

**Giá trị trả về**

- `true`: FIFO đầy.
- `false`: FIFO còn chỗ trống.

---

## `std::size_t Size()`

Trả về số phần tử hiện có trong FIFO.

---

## `std::size_t Capacity()`

Trả về dung lượng tối đa của FIFO.

---

## `void Clear()`

Đặt lại FIFO về trạng thái rỗng.

Lưu ý: Hàm chỉ đặt lại các chỉ số (`head_`, `tail_`, `count_`) mà không giải phóng bộ nhớ của `std::vector`.

---

## `void DebugPrint()`

Hiển thị trạng thái hiện tại của FIFO.

Thông tin hiển thị gồm:

- Capacity
- Size
- Head
- Tail
- Nội dung của Circular Buffer

Hàm này được xây dựng nhằm hỗ trợ học tập và kiểm thử thuật toán Circular Buffer.

---

# Giao diện chương trình

```text
========== FIFO UNIT TEST ==========

[PASS] TestConstructor
[PASS] TestPush
[PASS] TestPop
[PASS] TestClear
[PASS] TestWrapAround
[PASS] TestDebugPrint

====================================
 ALL UNIT TESTS PASSED
====================================
```

---

# Yêu cầu môi trường

- Ubuntu 22.04 hoặc mới hơn
- GCC
- Valgrind

## Cài đặt môi trường

```bash
sudo apt update
sudo apt install git build-essential valgrind
```

Kiểm tra trình biên dịch:

```bash
g++ --version
```

---

# Clone project

```bash
git clone https://github.com/KhanhVD-1704/01_FIFO_Library_CPP.git
```

Di chuyển vào thư mục project:

```bash
cd 01_FIFO_Library_CPP
```

---

# Build project

```bash
g++ -std=c++17 \
main.cpp \
tests/unit_test_fifo.cpp \
src/fifo.cpp \
-Iinclude \
-Itests \
-o app
```

---

# Chạy chương trình

```bash
./app
```

---

# Kiểm tra Memory Leak

Chạy Valgrind:

```bash
valgrind --leak-check=full ./app
```

Kết quả mong muốn:

```text
HEAP SUMMARY:
All heap blocks were freed -- no leaks are possible

ERROR SUMMARY: 0 errors
```

Điều này xác nhận chương trình không bị rò rỉ bộ nhớ và toàn bộ tài nguyên được giải phóng đúng cách.

---

# Kiến thức đạt được

Thông qua project này có thể thực hành:

- Thiết kế chương trình theo nhiều module.
- Xây dựng thư viện C++ sử dụng Class.
- Làm việc với Constructor và Member Function.
- Quản lý bộ nhớ bằng `std::vector`.
- Triển khai thuật toán Circular Buffer.
- Xử lý ngoại lệ bằng `std::invalid_argument`.
- Xây dựng Unit Test bằng `assert`.
- Kiểm tra Memory Leak bằng Valgrind.
- Biên dịch chương trình theo chuẩn C++17 bằng GCC.

---

# Hướng phát triển

Có thể mở rộng project bằng các chức năng:

- Xây dựng Generic FIFO sử dụng Template.
- Hỗ trợ Iterator để duyệt dữ liệu.
- Tích hợp GoogleTest.
- Sử dụng CMake để quản lý quá trình build.
- Tích hợp GitHub Actions để kiểm thử tự động.
- Phát triển Thread-safe FIFO cho môi trường đa luồng.