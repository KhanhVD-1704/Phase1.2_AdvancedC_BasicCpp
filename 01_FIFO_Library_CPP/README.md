# FIFO Library (C++)

Đây là project cài đặt cấu trúc dữ liệu FIFO (First In, First Out) bằng C++17. FIFO có thể hiểu đơn giản như một hàng đợi: phần tử được thêm vào trước sẽ được lấy ra trước.

Project dùng circular buffer để quản lý dữ liệu. Nhờ đó, sau khi Pop một phần tử, buffer có thể dùng lại vị trí cũ mà không cần dồn toàn bộ dữ liệu còn lại trong mảng.

Ví dụ, với FIFO có dung lượng 3:

```text
Push 1, 2, 3  -> [1, 2, 3]
Pop           -> lấy ra 1
Push 4        -> dùng lại vị trí cũ của 1
Pop lần lượt  -> 2, 3, 4
```

## Cấu trúc project

```text
01_FIFO_Library_CPP/
├── include/
│   └── fifo.hpp
├── src/
│   └── fifo.cpp
├── tests/
│   ├── unit_test_fifo.hpp
│   └── unit_test_fifo.cpp
├── main.cpp
├── README.md
└── output.md
```

- `include/fifo.hpp`: khai báo class `FIFO`.
- `src/fifo.cpp`: cài đặt các hàm của FIFO.
- `tests/`: các bài unit test.
- `main.cpp`: chạy toàn bộ test.
- `output.md`: báo cáo kết quả test.

## Cách FIFO hoạt động

FIFO lưu dữ liệu trong `std::vector<uint8_t>` và dùng ba biến để theo dõi trạng thái:

| Biến | Ý nghĩa |
|---|---|
| `head_` | Vị trí sẽ ghi dữ liệu tiếp theo. |
| `tail_` | Vị trí sẽ đọc dữ liệu tiếp theo. |
| `count_` | Số phần tử hiện đang có trong FIFO. |

Sau mỗi lần Push hoặc Pop, `head_` và `tail_` được cập nhật bằng phép chia dư `% Capacity()`. Vì vậy, khi chỉ số đi đến cuối buffer, nó sẽ quay lại đầu buffer.

`count_` giúp phân biệt hai trường hợp `head_ == tail_`: FIFO đang rỗng hoặc FIFO đang đầy.

## API

| Hàm | Dùng để làm gì? |
|---|---|
| `FIFO(capacity)` | Tạo FIFO với dung lượng cố định. `capacity` phải lớn hơn 0. |
| `Push(uint8_t data)` | Thêm dữ liệu vào FIFO. Trả `false` nếu FIFO đầy. |
| `Pop(uint8_t& data)` | Lấy dữ liệu vào trước ra trước. Trả `false` nếu FIFO rỗng. |
| `IsEmpty()` / `IsFull()` | Kiểm tra FIFO đang rỗng hay đầy. |
| `Size()` / `Capacity()` | Lấy số phần tử hiện có và dung lượng tối đa. |
| `Clear()` | Xóa dữ liệu trong FIFO và đưa chỉ số về trạng thái ban đầu. |
| `DebugPrint()` | In buffer, head, tail và size để tiện quan sát khi debug. |

Nếu tạo FIFO với dung lượng 0, constructor sẽ ném `std::invalid_argument`.

## Ví dụ sử dụng

```cpp
#include "fifo.hpp"

fifo_library::FIFO fifo(3);

fifo.Push(10);
fifo.Push(20);

uint8_t value = 0;

if (fifo.Pop(value))
{
    // value = 10
}
```

## Unit test

Project có các bài test cho những chức năng chính:

- `TestConstructor`: kiểm tra trạng thái FIFO sau khi khởi tạo.
- `TestZeroCapacity`: kiểm tra exception khi dung lượng bằng 0.
- `TestPush`: kiểm tra thêm dữ liệu và trường hợp FIFO đầy.
- `TestPop`: kiểm tra thứ tự dữ liệu và trường hợp FIFO rỗng.
- `TestClear`: kiểm tra xóa dữ liệu và tái sử dụng FIFO.
- `TestWrapAround`: kiểm tra circular buffer khi head/tail quay vòng.
- `TestDebugPrint`: hiển thị trạng thái FIFO để quan sát.

Chi tiết kết quả được ghi trong [output.md](output.md).

## Build và chạy

Mở terminal tại thư mục `01_FIFO_Library_CPP` và biên dịch bằng C++17:

```bash
g++ -std=c++17 \
    main.cpp \
    tests/unit_test_fifo.cpp \
    src/fifo.cpp \
    -Iinclude \
    -Itests \
    -o app
```

Chạy unit test:

```bash
./app
```

File `app` là file build cục bộ và đã được khai báo trong `.gitignore`, nên không cần đưa lên GitHub.
