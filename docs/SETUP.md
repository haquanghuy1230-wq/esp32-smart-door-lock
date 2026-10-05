# Cài đặt và cấu hình

## Môi trường

Mã nguồn dùng Arduino framework. Archive gốc không ghi phiên bản dependency; danh sách dưới đây được xác định từ các lệnh `#include`, chưa phải cấu hình build đã kiểm chứng.

| Dependency | Header |
| --- | --- |
| Arduino core cho ESP32 (Espressif) | WiFi.h, WebServer.h, Wire.h, EEPROM.h, HardwareSerial.h |
| Adafruit Fingerprint Sensor Library | Adafruit_Fingerprint.h |
| Keypad | Keypad.h |
| ESP32Servo | ESP32Servo.h |
| LiquidCrystal_I2C, chọn bản hỗ trợ init() và backlight() | LiquidCrystal_I2C.h |
| Firebase ESP32 Client của Mobizt, API cũ | FirebaseESP32.h |

Cài Arduino ESP32 theo [hướng dẫn Espressif](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html). Chọn board phù hợp với ESP32 DevKit V1 và cổng serial thực tế. Thư viện [Firebase-ESP32](https://github.com/mobizt/Firebase-ESP32) đã được tác giả đánh dấu deprecated; chuyển sang FirebaseClient cần sửa API, không chỉ thay header.

## Cấu hình riêng

Trong thư mục sketch, sao chép `config.example.h` thành `config.local.h` và điền Wi-Fi, Firebase URL/token, tài khoản Admin và mã keypad. `config.local.h` được bỏ qua bởi Git. Hai mã số trong file mẫu chỉ dùng minh họa; hãy đổi chúng. Firmware hiện coi phím 0 là hủy nên chưa hỗ trợ mã có số 0.

Nếu EEPROM đã có mật khẩu, giá trị lưu sẽ được ưu tiên hơn `DOOR_DEFAULT_PASSWORD`. Đổi macro không tự cập nhật EEPROM; mã gốc có hàm savePassword nhưng chưa có luồng thay mật khẩu hoàn chỉnh.

Trong `index.h`, thay `YOUR_FIREBASE_WEB_API_KEY` và `YOUR_PROJECT` bằng cấu hình web của Firebase project của bạn. Cấu hình web được gửi tới trình duyệt; tuyệt đối không đặt legacy token vào HTML. Legacy token chỉ điền trong file cấu hình riêng của ESP32.

## Firebase

Mã firmware sử dụng `config.signer.tokens.legacy_token`. Dashboard chỉ khởi tạo Firebase app/database, chưa đăng nhập Firebase Authentication. Vì vậy cơ chế bảo vệ RTDB cần được thiết kế thêm: nếu rules yêu cầu `auth`, listener hiện tại sẽ bị từ chối. Không dùng rules công khai đọc/ghi cho dữ liệu hoặc hệ thống cửa thật. Repository không kèm rules mở hoặc token cũ.

## Nạp và mở dashboard

1. Mở `SmartDoorLock.ino` trong thư mục cùng tên, cài dependency và chọn board/cổng.
2. Verify/Compile. Khi thành công, ghi lại phiên bản IDE, core và từng thư viện đã dùng.
3. Upload; mở Serial Monitor 115200 baud.
4. Firmware chờ Wi-Fi kết nối; IP được in ra Serial và LCD. Trình duyệt phải truy cập IP này trong mạng LAN.
5. Truy cập `http://<IP-ESP32>/`. Dùng Admin email/password của `config.local.h`. Client demo trong mã là `client1@example.com` đến `client3@example.com`; handler hiện không kiểm tra mật khẩu client.

Dashboard nằm trong `index.h`, được ESP32 phục vụ trực tiếp. Không cần hosting riêng hay upload filesystem; thư mục data/logo.png trong archive không được firmware tham chiếu, nên không đưa vào bản công khai. Logo trên dashboard gốc dùng URL ngoài.

## Trạng thái xác minh

Bản chuẩn bị repository đã được rà soát cấu trúc và thông tin cấu hình; chưa biên dịch và chưa chạy phần cứng. Cần thực hiện checklist ở [DEMO.md](DEMO.md) trước khi ghi kết quả kiểm thử mới.
