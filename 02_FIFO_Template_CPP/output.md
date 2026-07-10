# FIFO Template Library - Test Report

## Mục đích

Báo cáo này ghi lại kết quả chạy unit test của FIFO Template. Mục tiêu là kiểm tra FIFO vẫn hoạt động như project trước khi thay kiểu dữ liệu cố định bằng `T`.

Các kiểu đã kiểm tra là `int`, `float`, `char` và `std::string`.

---

## TestConstructor

### Mục đích

Kiểm tra FIFO có được tạo đúng dung lượng và bắt đầu ở trạng thái rỗng hay không.

### Kịch bản kiểm thử

Tạo FIFO với bốn kiểu dữ liệu khác nhau, sau đó kiểm tra `Capacity()`, `Size()`, `IsEmpty()` và `IsFull()`.

### Kết quả thực thi

```text
========== TestConstructor ==========
[PASS] TestConstructor
```

### Nhận xét

Cả bốn FIFO đều khởi tạo đúng và chưa chứa phần tử nào.

---

## TestZeroCapacity

### Mục đích

Kiểm tra constructor không cho phép tạo FIFO không có chỗ chứa dữ liệu.

### Kịch bản kiểm thử

Tạo `FIFO<int>` với dung lượng bằng 0 và chờ `std::invalid_argument` được ném ra.

### Kết quả thực thi

```text
========== TestZeroCapacity ==========
[PASS] TestZeroCapacity
```

### Nhận xét

Kiểm tra capacity bằng 0 hoạt động đúng.

---

## TestPush

### Mục đích

Kiểm tra thêm dữ liệu vào FIFO và xử lý khi FIFO đầy.

### Kịch bản kiểm thử

Push dữ liệu kiểu `int`, `float`, `char` và `std::string`. Sau khi FIFO đầy, thử Push thêm một phần tử nữa.

### Kết quả thực thi

```text
========== TestPush ==========
[PASS] TestPush
```

### Nhận xét

Dữ liệu được thêm đúng với mọi kiểu đã test. Push thêm khi đầy trả về `false` như mong đợi.

---

## TestPop

### Mục đích

Kiểm tra phần tử được lấy ra đúng thứ tự đã đưa vào.

### Kịch bản kiểm thử

Push dữ liệu vào từng FIFO, Pop ra và so sánh với giá trị ban đầu. Cuối cùng thử Pop khi FIFO rỗng.

### Kết quả thực thi

```text
========== TestPop ==========
[PASS] TestPop
```

### Nhận xét

FIFO vẫn giữ đúng nguyên tắc vào trước ra trước. Pop khi rỗng trả về `false`.

---

## TestClear

### Mục đích

Kiểm tra `Clear()` có xóa toàn bộ dữ liệu và cho phép dùng lại FIFO hay không.

### Kịch bản kiểm thử

Thêm dữ liệu vào FIFO, gọi `Clear()`, kiểm tra trạng thái rỗng rồi Push dữ liệu mới.

### Kết quả thực thi

```text
========== TestClear ==========
[PASS] TestClear
```

### Nhận xét

Sau `Clear()`, FIFO trở về trạng thái rỗng và hoạt động bình thường ở lần dùng tiếp theo.

---

## TestWrapAround

### Mục đích

Kiểm tra circular buffer sau khi vị trí ghi hoặc đọc quay lại đầu buffer.

### Kịch bản kiểm thử

Làm đầy FIFO, Pop một vài phần tử, Push dữ liệu mới vào các ô vừa được giải phóng, rồi Pop toàn bộ phần tử còn lại.

### Kết quả thực thi

```text
========== TestWrapAround ==========
[PASS] TestWrapAround
```

### Nhận xét

Thứ tự dữ liệu vẫn chính xác sau khi wrap-around, nên thuật toán FIFO không bị ảnh hưởng bởi việc chuyển sang template.

---

## TestDebugPrint

### Mục đích

Quan sát trạng thái buffer khi FIFO chứa các kiểu dữ liệu khác nhau.

### Kịch bản kiểm thử

Thêm một phần tử vào FIFO `int`, `float`, `char` và `std::string`, sau đó gọi `DebugPrint()` cho từng FIFO.

### Kết quả thực thi

```text
========== TestDebugPrint ==========

========== FIFO DEBUG ==========
Capacity : 2
Size     : 1
Head     : 1
Tail     : 0

Index    :            0           1
Data     :           11           0
Head --> 1
Tail --> 0
===============================

========== FIFO DEBUG ==========
Capacity : 2
Size     : 1
Head     : 1
Tail     : 0

Index    :            0           1
Data     :          1.5           0
Head --> 1
Tail --> 0
===============================

========== FIFO DEBUG ==========
Capacity : 2
Size     : 1
Head     : 1
Tail     : 0

Index    :            0           1
Data     :            X
Head --> 1
Tail --> 0
===============================

========== FIFO DEBUG ==========
Capacity : 2
Size     : 1
Head     : 1
Tail     : 0

Index    :            0           1
Data     :         FIFO
Head --> 1
Tail --> 0
===============================
[PASS] TestDebugPrint
```

### Nhận xét

DebugPrint hiển thị đúng dữ liệu đã thêm. Ô còn lại của FIFO `char` và `std::string` trông như trống vì chúng đang giữ giá trị mặc định là `\0` và chuỗi rỗng.

---

## Tổng kết

Tất cả unit test đều pass. FIFO Template hoạt động đúng với bốn kiểu dữ liệu đã kiểm tra và vẫn giữ nguyên cơ chế circular buffer của project trước.
