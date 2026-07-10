# FIFO Library - Unit Test Report

## Mục đích

Tài liệu này trình bày kết quả thực hiện các bài kiểm thử (Unit Test) đối với thư viện FIFO Library. Mỗi bài kiểm thử được xây dựng nhằm xác minh tính đúng đắn của từng chức năng, bao gồm khởi tạo FIFO, ghi dữ liệu, đọc dữ liệu, xóa dữ liệu, cơ chế Circular Buffer, hiển thị thông tin gỡ lỗi và kiểm tra quản lý bộ nhớ bằng Valgrind.

---

# TestConstructor

## Mục đích

Kiểm tra việc khởi tạo đối tượng FIFO với dung lượng xác định, xác nhận các thành phần của FIFO được thiết lập đúng trạng thái ban đầu trước khi sử dụng.

## Kịch bản kiểm thử

1. Khởi tạo FIFO với dung lượng 5 phần tử.
2. Kiểm tra dung lượng của FIFO.
3. Kiểm tra số lượng phần tử hiện có.
4. Kiểm tra vị trí của Head và Tail.
5. Hiển thị trạng thái FIFO bằng `DebugPrint()`.

## Kết quả thực thi

```text
========== TestConstructor ==========

========== FIFO DEBUG ==========
Capacity : 5
Size     : 0
Head     : 0
Tail     : 0

Index    :    0   1   2   3   4
Data     :    0   0   0   0   0
Head --> 0
Tail --> 0
===============================
[PASS] TestConstructor
```

## Nhận xét

* FIFO được khởi tạo với đúng dung lượng yêu cầu.
* Chưa có phần tử nào được lưu nên `Size = 0`.
* Hai con trỏ `Head` và `Tail` đều ở vị trí ban đầu.
* Buffer được khởi tạo với giá trị mặc định.
* Kết quả kiểm thử xác nhận quá trình khởi tạo FIFO hoạt động đúng.

---

# TestPush

## Mục đích

Kiểm tra chức năng ghi dữ liệu vào FIFO, xác nhận dữ liệu được lưu đúng vị trí, bộ đếm số phần tử được cập nhật chính xác và FIFO xử lý đúng khi đầy.

## Kịch bản kiểm thử

1. Khởi tạo FIFO có dung lượng 3 phần tử.
2. Thực hiện `Push(10)`.
3. Thực hiện `Push(20)`.
4. Thực hiện `Push(30)`.
5. Thực hiện thêm một lần `Push` khi FIFO đã đầy.

## Kết quả thực thi

```text
========== TestPush ==========

========== FIFO DEBUG ==========
Capacity : 3
Size     : 1
Head     : 1
Tail     : 0

Index    :    0   1   2
Data     :   10   0   0
Head --> 1
Tail --> 0
===============================

========== FIFO DEBUG ==========
Capacity : 3
Size     : 2
Head     : 2
Tail     : 0

Index    :    0   1   2
Data     :   10  20   0
Head --> 2
Tail --> 0
===============================

========== FIFO DEBUG ==========
Capacity : 3
Size     : 3
Head     : 0
Tail     : 0

Index    :    0   1   2
Data     :   10  20  30
Head --> 0
Tail --> 0
===============================

========== FIFO DEBUG ==========
Capacity : 3
Size     : 3
Head     : 0
Tail     : 0

Index    :    0   1   2
Data     :   10  20  30
Head --> 0
Tail --> 0
===============================
[PASS] TestPush
```

## Nhận xét

* Sau mỗi lần Push, dữ liệu được ghi thành công vào FIFO.
* Con trỏ `Head` dịch sang vị trí kế tiếp theo cơ chế Circular Buffer.
* `Size` tăng tương ứng với số phần tử được lưu.
* Khi FIFO đầy, lần Push tiếp theo bị từ chối và dữ liệu hiện có không bị thay đổi.
* Kết quả kiểm thử xác nhận chức năng Push hoạt động đúng theo thiết kế.

---

# TestPop

## Mục đích

Kiểm tra chức năng lấy dữ liệu ra khỏi FIFO, xác nhận dữ liệu được đọc đúng thứ tự FIFO, bộ đếm phần tử giảm chính xác và vùng nhớ được cập nhật sau khi Pop.

## Kịch bản kiểm thử

1. Khởi tạo FIFO dung lượng 3.
2. Push lần lượt các giá trị 10, 20 và 30.
3. Thực hiện Pop ba lần liên tiếp.
4. Quan sát sự thay đổi của Head, Tail, Size và nội dung buffer.

## Kết quả thực thi

```text
========== TestPop ==========

========== FIFO DEBUG ==========
Capacity : 3
Size     : 3
Head     : 0
Tail     : 0

Index    :    0   1   2
Data     :   10  20  30
Head --> 0
Tail --> 0
===============================

========== FIFO DEBUG ==========
Capacity : 3
Size     : 2
Head     : 0
Tail     : 1

Index    :    0   1   2
Data     :    0  20  30
Head --> 0
Tail --> 1
===============================

========== FIFO DEBUG ==========
Capacity : 3
Size     : 1
Head     : 0
Tail     : 2

Index    :    0   1   2
Data     :    0   0  30
Head --> 0
Tail --> 2
===============================

========== FIFO DEBUG ==========
Capacity : 3
Size     : 0
Head     : 0
Tail     : 0

Index    :    0   1   2
Data     :    0   0   0
Head --> 0
Tail --> 0
===============================
[PASS] TestPop
```

## Nhận xét

* Các phần tử được lấy ra theo đúng thứ tự **10 → 20 → 30**.
* Sau mỗi lần Pop, `Tail` dịch sang vị trí kế tiếp.
* `Size` giảm tương ứng với số phần tử còn lại trong FIFO.
* Các ô đã Pop được đưa về giá trị 0 để thuận tiện cho việc kiểm tra và gỡ lỗi.
* Sau lần Pop cuối cùng, FIFO trở về trạng thái rỗng.

---

# TestClear

## Mục đích

Kiểm tra chức năng xóa toàn bộ dữ liệu trong FIFO và đưa FIFO trở về trạng thái ban đầu.

## Kịch bản kiểm thử

1. Khởi tạo FIFO.
2. Push ba phần tử vào FIFO.
3. Gọi hàm `Clear()`.
4. Kiểm tra trạng thái FIFO sau khi xóa.

## Kết quả thực thi

```text
========== TestClear ==========

========== FIFO DEBUG ==========
Capacity : 5
Size     : 3
Head     : 3
Tail     : 0

Index    :    0   1   2   3   4
Data     :   10  20  30   0   0
Head --> 3
Tail --> 0
===============================

========== FIFO DEBUG ==========
Capacity : 5
Size     : 0
Head     : 0
Tail     : 0

Index    :    0   1   2   3   4
Data     :    0   0   0   0   0
Head --> 0
Tail --> 0
===============================
[PASS] TestClear
```

## Nhận xét

* Toàn bộ dữ liệu trong buffer được xóa.
* `Size` trở về 0.
* `Head` và `Tail` được đặt lại vị trí ban đầu.
* FIFO sẵn sàng cho một chu kỳ sử dụng mới.
* Chức năng Clear hoạt động đúng theo thiết kế.

---

# TestWrapAround

## Mục đích

Kiểm tra cơ chế Circular Buffer, xác nhận FIFO có thể tái sử dụng vùng nhớ đã được giải phóng mà không cần dịch chuyển dữ liệu trong mảng.

## Kịch bản kiểm thử

1. Khởi tạo FIFO dung lượng 3.
2. Push các giá trị 1, 2 và 3.
3. Pop hai phần tử đầu.
4. Push tiếp hai phần tử 4 và 5.
5. Pop toàn bộ dữ liệu còn lại.

## Kết quả thực thi

```text
========== TestWrapAround ==========

========== FIFO DEBUG ==========
Capacity : 3
Size     : 3
Head     : 0
Tail     : 0

Index    :    0   1   2
Data     :    1   2   3
Head --> 0
Tail --> 0
===============================

========== FIFO DEBUG ==========
Capacity : 3
Size     : 1
Head     : 0
Tail     : 2

Index    :    0   1   2
Data     :    0   0   3
Head --> 0
Tail --> 2
===============================

========== FIFO DEBUG ==========
Capacity : 3
Size     : 3
Head     : 2
Tail     : 2

Index    :    0   1   2
Data     :    4   5   3
Head --> 2
Tail --> 2
===============================

========== FIFO DEBUG ==========
Capacity : 3
Size     : 0
Head     : 2
Tail     : 2

Index    :    0   1   2
Data     :    0   0   0
Head --> 2
Tail --> 2
===============================
[PASS] TestWrapAround
```

## Nhận xét

* Sau khi Pop, các vị trí đầu của buffer được giải phóng.
* Hai lần Push tiếp theo ghi dữ liệu vào các vị trí vừa được giải phóng.
* Không xảy ra việc dịch chuyển dữ liệu trong mảng.
* Cơ chế Circular Buffer hoạt động chính xác, giúp sử dụng hiệu quả vùng nhớ.

---

# TestDebugPrint

## Mục đích

Kiểm tra chức năng hiển thị trạng thái nội bộ của FIFO nhằm hỗ trợ kiểm thử và gỡ lỗi.

## Kịch bản kiểm thử

1. Khởi tạo FIFO.
2. Push ba phần tử 11, 22 và 33.
3. Gọi `DebugPrint()`.

## Kết quả thực thi

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

## Nhận xét

* Toàn bộ thông tin quan trọng của FIFO được hiển thị đầy đủ.
* Dữ liệu trong buffer phản ánh đúng trạng thái thực tế.
* Chức năng DebugPrint hỗ trợ hiệu quả cho quá trình kiểm thử và gỡ lỗi.

---

# Valgrind Memory Check

## Mục đích

Kiểm tra việc cấp phát và giải phóng bộ nhớ động của chương trình nhằm phát hiện rò rỉ bộ nhớ hoặc truy cập bộ nhớ không hợp lệ.

## Kịch bản kiểm thử

1. Chạy toàn bộ Unit Test.
2. Thực thi chương trình dưới Valgrind với tùy chọn `--leak-check=full`.
3. Kiểm tra báo cáo bộ nhớ sau khi chương trình kết thúc.

## Kết quả thực thi

```text
HEAP SUMMARY:
    in use at exit: 0 bytes in 0 blocks
    total heap usage: 8 allocs, 8 frees

All heap blocks were freed -- no leaks are possible

ERROR SUMMARY: 0 errors from 0 contexts
```

## Nhận xét

* Không phát hiện rò rỉ bộ nhớ.
* Không phát hiện truy cập bộ nhớ không hợp lệ.
* Toàn bộ vùng nhớ được giải phóng chính xác trước khi chương trình kết thúc.
* Kết quả xác nhận FIFO Library quản lý tài nguyên bộ nhớ an toàn và ổn định.

---

# Tổng kết

Toàn bộ các bài kiểm thử đều hoàn thành thành công.

* Tất cả Unit Test đều **PASS**.
* Các chức năng của FIFO hoạt động đúng theo thiết kế.
* Cơ chế Circular Buffer hoạt động chính xác.
* Chương trình không phát sinh lỗi bộ nhớ hoặc rò rỉ bộ nhớ khi kiểm tra bằng Valgrind.
