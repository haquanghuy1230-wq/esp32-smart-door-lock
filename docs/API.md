# HTTP API và dữ liệu Firebase

Các route do ESP32 WebServer port 80 xử lý. Dashboard gửi GET cùng origin; dữ liệu trạng thái nhận từ Firebase. Chưa có session/token kiểm tra quyền trên route điều khiển.

| GET endpoint | Chức năng / lưu ý |
| --- | --- |
| `/` | Trả dashboard HTML nhúng |
| `/login?email=...&pass=...` | Admin kiểm tra mật khẩu; Client chỉ kiểm tra email |
| `/open` | Servo mở rồi tự đóng; handler gốc gọi server.send hai lần |
| `/close` | Cập nhật biến/Firebase CLOSED, chưa gọi servo.write |
| `/doorstate` | Trả OPEN / CLOSED từ biến phần mềm |
| `/light?state=on` | Bật relay và giữ chế độ thủ công |
| `/light?state=off` | Tắt relay rồi trả về tự động; radar có thể bật lại |
| `/ledstate` | Trả ON / OFF |
| `/addfp` | Đặt cờ thêm mẫu, tiếp tục nhập ID/chạm cảm biến tại thiết bị |
| `/deletefp` | Xóa mẫu, yêu cầu nhập ID trên keypad, có thao tác chờ |
| `/changepass` | Chỉ chuyển sang nhập mật khẩu; chưa lưu mật khẩu mới |

## Firebase RTDB

```json
{
  "door": { "state": "CLOSED" },
  "light": { "state": "OFF" },
  "fingerprint": { "count": 0, "last_id": -1 }
}
```

`door/state` có giá trị OPEN hoặc CLOSED; `light/state` có ON hoặc OFF. Vòng loop thử cập nhật theo khoảng 1000ms, nhưng các hàm delay/chờ có thể làm giãn chu kỳ. `fingerprint/count` lấy từ cảm biến khi khởi tạo và thao tác web thêm/xóa; thao tác quản trị bằng keypad chưa đồng bộ tương ứng. `last_id` hiện khởi tạo -1 và chưa được cập nhật sau xác thực; không phải lịch sử truy cập.

Dashboard lắng nghe `/door/state`, `/light/state`, `/fingerprint/count`. Không có Firebase listener nhận command ở ESP32 và chưa có cảm biến xác nhận cửa đóng vật lý.
