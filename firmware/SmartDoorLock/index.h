#ifndef INDEX_H
#define INDEX_H

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="vi">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>IoT Smart Home</title>

<!-- Firebase -->
<script src="https://www.gstatic.com/firebasejs/8.10.0/firebase-app.js"></script>
<script src="https://www.gstatic.com/firebasejs/8.10.0/firebase-database.js"></script>

<style>
* {
  box-sizing: border-box;
  font-family: Arial, Helvetica, sans-serif;
}

:root {
  --blue: #0a58ca;
  --white: #ffffff;
  --gray: #f4f4f4;
}

body {
  margin: 0;
  height: 100vh;
  background: var(--gray);
}

/* ================= LOGIN ================= */
.login-page {
  height: 100vh;
  display: flex;
  justify-content: center;
  align-items: center;
  background: var(--blue);
}

.login-box {
  background: var(--white);
  padding: 30px;
  width: 320px;
  border-radius: 14px;
}

.login-box h2 {
  margin-bottom: 20px;
  color: var(--blue);
  text-align: center;
}

.login-box input {
  width: 100%;
  padding: 10px;
  margin-bottom: 12px;
}

.login-box button {
  width: 100%;
  padding: 10px;
  background: var(--blue);
  color: #fff;
  border: none;
  font-weight: bold;
  cursor: pointer;
}

/* ================= MAIN ================= */
.main-page {
  display: none;
  height: 100vh;
}

.container {
  display: flex;
  height: 100%;
}

/* ================= SIDEBAR ================= */
.sidebar {
  width: 240px;
  background: var(--blue);
  padding: 20px 15px;
  display: flex;
  flex-direction: column;
}

.sidebar-logo {
  width: 140px;
  margin: 0 auto 25px;
}

.sidebar a {
  background: var(--white);
  margin-bottom: 12px;
  padding: 12px;
  border-radius: 12px;
  font-weight: bold;
  text-align: center;
  cursor: pointer;
}

/* ================= CONTENT ================= */
.content {
  flex: 1;
  display: flex;
  flex-direction: column;
}

/* ===== HEADER SCHOOL ===== */
.header-school {
  text-align: center;
  padding: 25px 20px 10px;
}

.header-school h2 {
  margin: 0;
  font-size: 20px;
  font-weight: bold;
}

/* ===== CENTER ===== */
.main-content {
  flex: 1;
  display: flex;
  justify-content: center;
  align-items: center;
  text-align: center;
}

.content-box {
  max-width: 900px;
  width: 100%;
}

/* ===== HOME ===== */
#homePage h1 {
  margin-bottom: 15px;
}

#homePage h3 {
  margin-top: 0;
  color: #555;
}

/* ===== STATUS ===== */
.status-wrapper {
  display: flex;
  justify-content: center;
  gap: 60px;
  margin-top: 30px;
}

.status-box {
  border: 2px solid var(--blue);
  border-radius: 16px;
  padding: 25px 35px;
  min-width: 220px;
}

.status-box h3 {
  margin-bottom: 15px;
}

.status-box p {
  margin-bottom: 10px;
  font-weight: bold;
}

.status-box button {
  width: 120px;
  padding: 10px;
  margin: 6px 0;
  cursor: pointer;
}

/* ===== COMMON ===== */
.hidden {
  display: none;
}
</style>
</head>

<body>

<!-- ================= LOGIN ================= -->
<div class="login-page" id="loginPage">
  <div class="login-box">
    <h2>Đăng nhập hệ thống</h2>
    <input id="email" placeholder="Email">
    <input id="password" type="password" placeholder="Password">
    <button onclick="login()">Đăng nhập</button>
  </div>
</div>

<!-- ================= MAIN ================= -->
<div class="main-page" id="mainPage">
  <div class="container">

    <!-- SIDEBAR -->
    <div class="sidebar">
      <img src="https://i.postimg.cc/LXXGM3XC/1logo.png" class="sidebar-logo">
      <a onclick="showPage('home')">Trang chủ</a>
      <a onclick="showPage('status')">Trạng thái</a>
      <a id="setupMenu" onclick="showPage('setup')">Thiết lập</a>
      <a onclick="logout()">Đăng xuất</a>
    </div>

    <!-- CONTENT -->
    <div class="content">

      <!-- SCHOOL -->
      <div class="header-school">
        <h2>HO CHI MINH CITY UNIVERSITY OF TECHNOLOGY AND ENGINEERING</h2>
      </div>

      <!-- CENTER -->
      <div class="main-content">
        <div class="content-box">

          <!-- HOME -->
          <div id="homePage">
            <h1>KHÓA CỬA ĐIỆN TỬ ESP32</h1>
            <h3>Vân tay · Keypad · Firebase · Dashboard</h3>
            <p><b>Thực hiện:</b> Hà Quang Huy &amp; Nguyễn Thành Đô</p>
            <p>Mô hình học tập và thử nghiệm</p>
          </div>

          <!-- STATUS -->
          <div id="statusPage" class="hidden">
            <h2>Trạng thái hệ thống</h2>

            <div class="status-wrapper">

              <!-- DOOR -->
              <div class="status-box">
                <h3>🚪 CỬA</h3>
                <p>Trạng thái: <span id="doorState">---</span></p>
                <button onclick="openDoor()">Mở cửa</button><br>
                <button onclick="closeDoor()">Đóng cửa</button>
              </div>

              <!-- LIGHT -->
              <div class="status-box">
                <h3>💡 ĐÈN</h3>
                <p>Trạng thái: <span id="ledState">---</span></p>
                <button onclick="toggleLight('on')">Bật đèn</button><br>
                <button onclick="toggleLight('off')">Tắt đèn</button>
              </div>

            </div>
          </div>

          <!-- SETUP -->
          <div id="setupPage" class="hidden">
            <h2>Thiết lập (Admin)</h2>
            <p>Số vân tay đã đăng ký: <b id="fpCount">---</b></p>
            <button onclick="addFP()">Thêm vân tay</button>
            <button onclick="deleteFP()">Xóa vân tay</button>
          </div>

        </div>
      </div>

    </div>
  </div>
</div>

<script>
firebase.initializeApp({
  apiKey: "YOUR_FIREBASE_WEB_API_KEY",
  databaseURL: "https://YOUR_PROJECT-default-rtdb.firebaseio.com"
});

const db = firebase.database();
let userRole = "";

function login() {
  fetch(`/login?email=${email.value}&pass=${password.value}`)
    .then(r => r.text())
    .then(role => {
      if (role !== "admin" && role !== "client") {
        alert("Sai thông tin đăng nhập");
        return;
      }
      userRole = role;
      loginPage.style.display = "none";
      mainPage.style.display = "block";
      if (userRole === "client") setupMenu.style.display = "none";
      startRealtime();
    });
}

function startRealtime() {
  db.ref("/door/state").on("value", s => doorState.innerText = s.val());
  db.ref("/light/state").on("value", s => ledState.innerText = s.val());
  db.ref("/fingerprint/count").on("value", s => {
    if (fpCount) fpCount.innerText = s.val();
  });
}

function showPage(p) {
  ["homePage","statusPage","setupPage"].forEach(id =>
    document.getElementById(id).classList.add("hidden")
  );
  if (p === "home") homePage.classList.remove("hidden");
  if (p === "status") statusPage.classList.remove("hidden");
  if (p === "setup") setupPage.classList.remove("hidden");
}

function logout() { location.reload(); }

function openDoor() { fetch("/open"); }
function closeDoor() { fetch("/close"); }
function toggleLight(s) { fetch(`/light?state=${s}`); }
function addFP() { fetch("/addfp"); }
function deleteFP() { fetch("/deletefp"); }
</script>

</body>
</html>
)rawliteral";

#endif
