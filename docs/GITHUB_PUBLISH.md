# Đưa dự án lên GitHub cá nhân

## Thông tin repository đề xuất

- Owner: `haquanghuy1230-wq`.
- Name: `esp32-smart-door-lock`.
- Description: `ESP32 electronic door lock with fingerprint and keypad authentication, Firebase RTDB integration, and a LAN web dashboard.`
- Topics: `esp32`, `arduino`, `iot`, `smart-lock`, `fingerprint`, `firebase`, `embedded-systems`, `smart-home`, `cpp`.

README đã ghi nhận cả hai thành viên và phân biệt báo cáo cục bộ với bản mở rộng. Chưa có thông tin phân công đủ để viết phần đóng góp riêng của Hà Quang Huy; bổ sung sau bằng nội dung đã xác nhận.

## Publish bằng Git

Đăng nhập GitHub trên trình duyệt, tạo repository trống tại tài khoản trên. Không khởi tạo thêm README, license hoặc .gitignore ở bước tạo vì đã có file local. Repository đã được tạo công khai và push lên https://github.com/haquanghuy1230-wq/esp32-smart-door-lock ngày 05/10/2026. Các bước bên dưới dùng khi cập nhật tiếp hoặc tạo lại từ bản sao.

PowerShell:

```powershell
Set-Location -LiteralPath 'C:\Users\Quang Huy\Desktop\esp32-smart-door-lock'
git status
git add .
git diff --cached --stat
git diff --cached
git commit -m "docs: present ESP32 smart door lock project and IoT extension"
git push -u origin main
```

Nếu Git chưa có tên/email, cấu hình danh tính commit của bạn trước khi commit; có thể dùng email noreply của GitHub. Khi push yêu cầu đăng nhập, hoàn tất xác thực GitHub bằng phương thức Git Credential Manager hỗ trợ trên máy.

Chỉ push thư mục `esp32-smart-door-lock`. Thư mục `esp32-smart-door-lock-preparation` chứa archive/mã gốc và chỉ dùng xử lý cục bộ, không upload.

## Sau khi đưa lên

Điền Description và Topics trong About, ghim repository trên profile. Có thể giới thiệu ngắn:

> Đồ án nhóm xây dựng mô hình khóa cửa điện tử trên ESP32: xác thực bằng AS608/keypad, quản lý vân tay, điều khiển servo và chiếu sáng theo hiện diện. Phiên bản mở rộng bổ sung dashboard web trong LAN và đồng bộ trạng thái Firebase. Repository gồm mã nguồn, sơ đồ kết nối, hướng dẫn cấu hình và các hạn chế cần hoàn thiện.

Mô tả tiếng Anh:

> An academic ESP32 door-lock prototype featuring fingerprint or keypad access, local fingerprint administration, servo actuation, and presence-based lighting. The IoT extension adds a LAN web dashboard and Firebase state synchronization. Developed by Ha Quang Huy and Nguyen Thanh Do.

Để thêm báo cáo PDF, đặt bản đã rà soát vào docs/reports và thêm liên kết README. .gitignore hiện bỏ qua PDF để tránh vô tình đưa báo cáo gốc lên; chỉ dùng git add -f cho đúng bản đã rà soát. Chưa chọn license vì đây là dự án nhóm; thống nhất với đồng tác giả trước khi cấp quyền sử dụng lại.
