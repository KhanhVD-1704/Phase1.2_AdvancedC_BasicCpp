# FIFO Library - Test Report

## Mục đích

Báo cáo này ghi lại kết quả unit test của FIFO Library. Các test tập trung vào thao tác Push, Pop, Clear và cơ chế circular buffer.

---

## TestConstructor

### Mục đích

Kiểm tra FIFO được tạo đúng dung lượng và bắt đầu ở trạng thái rỗng.

### Kịch bản kiểm thử

Tạo FIFO có dung lượng 5, sau đó kiểm tra `Capacity()`, `Size()`, `IsEmpty()` và `IsFull()`.

### Kết quả thực thi

```text
========== TestConstructor ==========
[PASS] TestConstructor
```

### Nhận xét

FIFO khởi tạo đúng dung lượng, chưa có dữ liệu và chưa đầy.

---

## TestZeroCapacity

### Mục đích

Kiểm tra constructor không cho phép tạo FIFO có dung lượng bằng 0.

### Kịch bản kiểm thử

Tạo `FIFO(0)` và kiểm tra exception `std::invalid_argument`.

### Kết quả thực thi

```text
========== TestZeroCapacity ==========
[PASS] TestZeroCapacity
```

### Nhận xét

Constructor xử lý đúng trường hợp capacity không hợp lệ.

---

## TestPush

### Mục đích

Kiểm tra thêm dữ liệu vào FIFO và xử lý khi FIFO đầy.

### Kịch bản kiểm thử

Push ba giá trị `10`, `20`, `30` vào FIFO dung lượng 3, sau đó thử Push thêm `40`.

### Kết quả thực thi

```text
========== TestPush ==========
[PASS] TestPush
```

### Nhận xét

Ba giá trị đầu được thêm thành công. FIFO báo đầy và từ chối phần tử thứ tư bằng cách trả về `false`.

---

## TestPop

### Mục đích

Kiểm tra dữ liệu được lấy ra theo đúng thứ tự vào trước ra trước.

### Kịch bản kiểm thử

Push `10`, `20`, `30`, sau đó Pop liên tiếp và thử Pop thêm khi FIFO đã rỗng.

### Kết quả thực thi

```text
========== TestPop ==========
[PASS] TestPop
```

### Nhận xét

Các giá trị được lấy ra theo thứ tự `10 -> 20 -> 30`. Pop khi FIFO rỗng trả về `false`.

---

## TestClear

### Mục đích

Kiểm tra `Clear()` xóa dữ liệu và đưa FIFO về trạng thái ban đầu.

### Kịch bản kiểm thử

Thêm ba phần tử, gọi `Clear()`, sau đó kiểm tra `Size()` và `IsEmpty()`.

### Kết quả thực thi

```text
========== TestClear ==========
[PASS] TestClear
```

### Nhận xét

Sau `Clear()`, FIFO rỗng và sẵn sàng được sử dụng lại.

---

## TestWrapAround

### Mục đích

Kiểm tra circular buffer khi vị trí ghi và đọc quay lại đầu buffer.

### Kịch bản kiểm thử

Làm đầy FIFO dung lượng 3 bằng `1`, `2`, `3`; Pop hai phần tử; Push `4`, `5`; sau đó Pop toàn bộ dữ liệu còn lại.

### Kết quả thực thi

```text
========== TestWrapAround ==========
[PASS] TestWrapAround
```

### Nhận xét

FIFO trả về đúng thứ tự `3 -> 4 -> 5` sau khi wrap-around. Không cần dịch chuyển dữ liệu trong buffer.

---

## TestDebugPrint

### Mục đích

Quan sát trạng thái buffer, `head_` và `tail_` khi FIFO đang có dữ liệu.

### Kịch bản kiểm thử

Tạo FIFO dung lượng 5, Push `11`, `22`, `33`, sau đó gọi `DebugPrint()`.

### Kết quả thực thi

```text
========== TestDebugPrint ==========

========== FIFO DEBUG ==========
Capacity : 5
Size     : 3
Head     : 3
Tail     : 0

Index    :    0   1   2   3   4
Data     :   11  22  33   0   0
Head --> 3
Tail --> 0
===============================
[PASS] TestDebugPrint
```

### Nhận xét

Trạng thái hiển thị khớp với ba dữ liệu đã Push. `head_` đang trỏ đến vị trí ghi tiếp theo, còn `tail_` vẫn ở phần tử đầu tiên.

---

## Tổng kết

Tất cả unit test đều pass. FIFO hoạt động đúng với dung lượng cố định, xử lý được trạng thái đầy/rỗng và giữ đúng thứ tự dữ liệu khi circular buffer quay vòng.
