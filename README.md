# Phase 1.2 - Advanced C & Basic C++

Repository này lưu các bài thực hành trong phần Advanced C và Basic C++. Mỗi project được tách riêng để dễ theo dõi phần mã nguồn, unit test và tài liệu.

## Danh sách project

| Project | Nội dung |
|---|---|
| [01_FIFO_Library_CPP](01_FIFO_Library_CPP) | Cài đặt FIFO cố định bằng C++17 và circular buffer. FIFO lưu dữ liệu kiểu `uint8_t`. |
| [02_FIFO_Template_CPP](02_FIFO_Template_CPP) | Refactor FIFO thành class template để dùng được với `int`, `float`, `char` và `std::string`. |

Mỗi project đều có README riêng, mã nguồn trong `include/` và `src/`, cùng unit test trong `tests/`.

## Cách xem project

Mở README trong từng thư mục để xem mục tiêu, API, ví dụ sử dụng và lệnh build:

- [Project 01 - FIFO Library](01_FIFO_Library_CPP/README.md)
- [Project 02 - FIFO Template Library](02_FIFO_Template_CPP/README.md)
