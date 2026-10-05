# Tóm tắt báo cáo Đồ án môn học 1

Nguồn: `DO_AN_1_final.docx`, đề tài **Thiết kế mô hình khóa cửa điện tử**, Hà Quang Huy và Nguyễn Thành Đô, hướng dẫn ThS. Lê Minh, bìa ghi 07/2026.

## Mục tiêu và phạm vi

Thiết kế mô hình thu nhỏ xác thực vân tay hoặc mật khẩu, quản lý mẫu vân tay, điều khiển servo, tự động chiếu sáng và phản hồi LCD/buzzer. Báo cáo giới hạn ở xử lý cục bộ, chưa tích hợp Internet trong phiên bản được mô tả.

## Nội dung

| Chương | Nội dung |
| --- | --- |
| 1 | Bối cảnh, mục tiêu, phạm vi và phương pháp nghiên cứu |
| 2 | Hệ thống nhúng, nhận diện vân tay, I2C/UART/GPIO |
| 3 | Yêu cầu, lựa chọn linh kiện, sơ đồ khối, kết nối và lưu đồ |
| 4 | Mô hình thực tế, vân tay đúng/sai, mật khẩu và Admin Mode |
| 5 | Kết luận, hướng mở rộng IoT và nâng cao bảo mật |

Báo cáo ghi nhận hoàn thiện mô hình và các chức năng cơ bản hoạt động trong thử nghiệm. Không có bảng đo tỷ lệ nhận diện, độ trễ hoặc kiểm thử dài hạn; repository không bổ sung số liệu suy đoán.

## Đối chiếu với phiên bản IoT

Smarthome.rar hiện thực thêm Wi-Fi, HTTP dashboard và ghi trạng thái Firebase. Đây là phần mở rộng so với báo cáo. Một số mô tả báo cáo khác mã IoT: radar có đoạn dùng UART nhưng code đọc OUT; báo cáo có đoạn thoát nhập bằng * nhưng code hiện dùng 0; trình tự hiển thị và phản hồi xác thực cũng có khác biệt. Các hướng dẫn sử dụng repository dựa theo mã IoT.

## Tài liệu công khai

Ảnh đã trích từ báo cáo để minh họa. DOCX gốc vẫn nằm trong thư mục ban đầu, chưa đưa vào repository vì chứa mã số sinh viên và trang biểu mẫu nhận xét. Khi bổ sung bản PDF công khai, nên rà soát thông tin cá nhân, nội dung biểu mẫu và thống nhất phiên bản trước khi upload. Bản tóm tắt này không thay thế báo cáo đầy đủ.
