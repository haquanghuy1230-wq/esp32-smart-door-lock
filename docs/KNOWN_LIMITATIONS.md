# Các điểm cần hoàn thiện

Nhận xét dưới đây dựa trên đọc mã Smarthome.rar, chưa phải kết quả thử lại trên thiết bị. Bản chuẩn bị chỉ thay cấu hình và phần giới thiệu dashboard, giữ logic gốc để người đọc đánh giá đúng phiên bản.

| Điểm | Bằng chứng trong mã | Ảnh hưởng / hướng sửa |
| --- | --- | --- |
| Phân quyền web chưa hoàn chỉnh | handleLogin chỉ trả chuỗi role; route điều khiển không kiểm tra session | Cần xác thực và kiểm tra quyền ở backend; ẩn menu chưa đủ |
| Client không kiểm tra mật khẩu | handleLogin trả client khi email khớp | Thiết kế quản lý tài khoản và kiểm tra credential |
| Mật khẩu nằm trong URL | login dùng GET query | Chuyển cách gửi và thiết kế kênh truyền/xác thực thích hợp |
| Mật khẩu keypad kiểm tra chuỗi con | inputPass.indexOf(password/adminPass) | Cần so khớp chính xác, xác nhận nhập và giới hạn lần sai |
| Phím 0 hủy nhập | password.cpp xử lý 0 trước nhánh số | Chưa nhập được mã có số 0; báo cáo có đoạn mô tả * để thoát |
| Trạng thái cửa chưa bám servo | openDoor không cập nhật doorState; handleClose không điều khiển servo | Gom điều khiển/trạng thái và bổ sung phản hồi vật lý khi cần |
| Gửi response hai lần | handleOpen có hai server.send | Một request cần một response, trạng thái cập nhật riêng |
| Đồng bộ fingerprint thiếu | lastFingerprintID không được cập nhật; keypad admin không gửi count mới | Đồng bộ sau mỗi thao tác/xác thực |
| Đổi mật khẩu chưa hoàn chỉnh | /changepass chỉ đặt cờ enteringPassword | Cần luồng nhập/xác nhận/lưu EEPROM |
| Vòng lặp bị chặn | openDoor dùng delay; addFingerprint có while chờ không timeout | Dùng state machine/timeout để giữ HTTP và radar responsive |
| Wi-Fi thiếu timeout | setup chờ kết nối vô hạn | Chưa có chế độ mất mạng hoạt động độc lập được kiểm chứng |
| Firebase gọi sớm và ít kiểm tra lỗi | setInt trước Firebase.begin; bỏ qua kết quả setString/setInt | Đổi trình tự, kiểm tra lỗi, retry có kiểm soát |
| OFF của đèn chưa là manual OFF | handleLight off đặt relayManual=false | Radar có thể bật ngay; nên có AUTO/ON/OFF rõ ràng |
| Rules/auth RTDB chưa đi kèm | Dashboard không Firebase Auth; archive không có rules | Chưa chứng minh được mô hình bảo vệ database |

Không diễn giải mô hình thành khóa cửa thương mại hoặc cơ chế xác thực đa yếu tố bắt buộc: hiện người dùng chọn vân tay **hoặc** mật khẩu. Không có số liệu chứng minh độ chính xác/độ trễ. Các tính năng nhật ký truy cập, RFID, PCB và điều khiển Internet là hướng phát triển.

Token Firebase và thông tin Wi-Fi gốc đã được loại khỏi bản công khai. Nếu token đã từng được chia sẻ ngoài phạm vi tin cậy, cần thu hồi/đổi token đó; việc xóa khỏi mã mới không vô hiệu hóa giá trị cũ.
