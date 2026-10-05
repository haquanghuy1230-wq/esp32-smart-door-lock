# Kịch bản demo và kiểm tra

Đây là checklist đề xuất, chưa đánh dấu là đã chạy. Ảnh báo cáo chỉ minh họa kết quả của bản cục bộ.

| Bước | Thao tác | Cần ghi nhận |
| --- | --- | --- |
| 1 | Cấp nguồn, khởi tạo, kết nối Wi-Fi | LCD, serial IP, trạng thái boot |
| 2 | Đưa người vào/rời vùng radar | Relay và trạng thái đèn |
| 3 | Quét mẫu đã đăng ký | LCD ID, servo mở 3s rồi đóng |
| 4 | Quét mẫu chưa đăng ký | Unknown Finger, cửa giữ khóa |
| 5 | Nhấn #, nhập mật khẩu riêng | Servo mở; dùng 0 để hủy theo mã hiện tại |
| 6 | Nhập mã Admin, chọn 1/2 | Thêm/xóa ID 1–127, hai lần quét khi thêm |
| 7 | Mở dashboard từ LAN | Admin/Client, trạng thái, lệnh cửa/đèn |
| 8 | So sánh LCD/servo với Firebase | Ghi sai lệch trạng thái nếu xuất hiện |
| 9 | Thử mất Wi-Fi / lỗi cảm biến | Ghi hành vi và thời gian phục hồi, không giả định đã hỗ trợ |

## Video giới thiệu 60–90 giây

1. Giới thiệu tên đề tài, hai thành viên và mục tiêu (10s).
2. Cận cảnh phần cứng; vân tay đúng/sai và mật khẩu (25s).
3. Radar điều khiển đèn, Admin thêm/xóa mẫu (15s).
4. Dashboard LAN và Firebase trạng thái, ghi rõ đây là phần mở rộng (20s).
5. Nêu một hạn chế hiện tại và hướng phát triển (10s).

Che mật khẩu, token, thông tin mạng khi quay. Chỉ đưa video và ảnh dashboard thật sau khi kiểm tra; repository chưa có screenshot Firebase/dashboard đang hoạt động.
