# Run Bro! - Khoi Nguyen Code

## Giới thiệu bản thân:
- Họ tên: Nguyễn Tấn Khôi
- MSSV: 22025526
- Lớp: INT2215 70

## Video demo :  

## Mục lục
- [Giới thiệu game](#giới-thiệu-game)
0. [Cách tải game](#0-cách-tải-game)
   - [0.a Cách 1: Không bao gồm code](#0a-cách-1-không-bao-gồm-code)
   - [0.b Cách 2: Bao gồm code và có thể biên dịch](#0b-cách-2-bao-gồm-code-và-có-thể-biên-dịch)
1. [Bắt đầu game](#1-bắt-đầu-game)
2. [Các thành phần trong game](#2-các-thành-phần-trong-game)
3. [Cách chơi](#3-cách-chơi)
4. [Chiến thắng](#4-chiến-thắng)
5. [Về source code](#5-về-source-code)
6. [Nguồn tham khảo](#6-nguồn-tham-khảo)
7. [Hướng phát triển](#7-hướng-phát-triển)

## Giới thiệu game
**Run Bro!** Hãy chạy thật nhanh để không bị những cái gai sắc nhọn đến từ phía bên trái của bạn đâm vào. Trong lúc cố gắng chạy để thoát khỏi những cái gai, bạn sẽ đối mặt với quái vật và các cạm bẫy nguy hiểm, đòi hỏi sự khéo léo và chiến lược để vượt qua.

## 0. Cách tải game

### 0.a Cách 1: Không bao gồm code
Tải game (được nén thành `.zip`) tại link sau: [[link tải game](https://github.com/khoinguyencode/Run_Bro/releases/tag/Run_Bro)]  
Giải nén game vào một thư mục và bật `Run_Bro.exe` lên để chơi. Cách này tiết kiệm bộ nhớ và thời gian tải.

### 0.b Cách 2: Bao gồm code và có thể biên dịch
Bước 1. Clone repo này về máy hoặc chọn **Code** -> **Download ZIP**.

![Screenshot 2024-08-16 211340](https://github.com/user-attachments/assets/6652e23c-f6d0-493a-9a0f-ab78f1dcd102)

Bước 2. Yêu cầu có **Visual Studio 2022 Community** và gói C++ cần thiết.  
Bước 3. Mở file `Run_Bro.sln` để tự động mở dự án trong Visual Studio.  
Bước 4. Chọn **Local Windows Debugger** để khởi động game (chọn **Debug**, **x64**).

## 1. Bắt đầu game
Chờ một chút để menu hiện ra, click vào nút có biểu tượng "Play" để bắt đầu chơi game. Bấm vào nút có biểu tượng "Exit" nếu muốn thoát game.
![Screenshot 2024-08-17 093725](https://github.com/user-attachments/assets/69b280eb-55f3-4d14-b194-88a2d4ee12ba)

## 2. Các thành phần trong game
- **Player** ![nhanvat](https://github.com/user-attachments/assets/f45c3bb2-56a1-4574-b5d1-7271f9791608) : người chơi
- **Monster** ![2](https://github.com/user-attachments/assets/e8d87b5e-ffaa-4407-b6ea-711e9a1f6480) : quái vật
- **Score** ![Screenshot 2024-08-17 095604](https://github.com/user-attachments/assets/b7d1e882-7748-4883-ab5a-6d17c8ee49cd) : điểm số trong lượt chơi hiện tại
- **Best score** ![Screenshot 2024-08-17 095557](https://github.com/user-attachments/assets/c586a3b1-e93f-489c-a4cc-d94591fc6a7f) : điểm số cao nhất mà người chơi đạt được
- **Nút play**![play](https://github.com/user-attachments/assets/b80d7835-b807-4a28-b108-3ee6caefe7f4) : bắt đầu trò chơi
- **Nút restart** ![restart](https://github.com/user-attachments/assets/b52efa15-56e2-4112-915f-949ecf50ab56) : dùng để chơi lại ván mới.
- **Nút exit**![quit](https://github.com/user-attachments/assets/07eb7e3d-298a-42b6-a4f7-39315961874e) : dùng để thoát trò chơi
- **Tile map:**: kĩ thuật tile map được sử dụng để vẽ map (vẽ các tile tường và nền)
![Screenshot 2024-08-17 095738](https://github.com/user-attachments/assets/58c26a16-96ba-40a2-b77c-75b357791d99)
- **Bố cục game cơ bản**
![Screenshot 2024-08-17 095624](https://github.com/user-attachments/assets/dfa09062-15a5-4b60-8484-530dc31712f7)

## 3. Cách chơi
Bạn cần phải cố gắng chạy và vượt quá các chướng ngại vật trên đường, đánh bại hoặc cố gắng né các con quái vật trên đường đi để có thể chạy tiếp về phía trước và thoát khỏi đống gai chết chóc đang đuổi theo bạn.

**Điều khiển:**
- **Di chuyển:** ↑ (Nhảy), ← (Chạy sang trái), → (Chạy sang phải)
- **Chém:** SPACE
- **Tạm dừng:** Esc

**Đồ họa:** Tự vẽ từ tileset trên [Itch.io](https://incolgames.itch.io/dungeon-platformer-tile-set-pixel-art).

## 4. Chiến thắng
Trong game này, mục tiêu của người chơi không phải là đạt đến một đích cụ thể hay chiến thắng mà là cố gắng đạt được số điểm cao nhất có thể. Game thuộc thể loại endless runner, nghĩa là nhân vật sẽ tiếp tục chạy qua các bản đồ và đối mặt với những thử thách không ngừng nghỉ. Điểm số sẽ được tính dựa trên khoảng cách mà người chơi đã chạy được và số quái vật đã tiêu diệt. Khi nhân vật gặp phải chướng ngại vật hoặc bị quái vật hạ gục, trò chơi sẽ kết thúc và điểm số cao nhất sẽ được ghi lại. Người chơi có thể thử lại nhiều lần để phá vỡ kỷ lục của chính mình.

## 5. Về source code
- **Folder `Run_Bro`:** Chứa toàn bộ mã nguồn của game, bao gồm các file `.cpp` và `.h`.
- **Folder `library`:** Chứa thư viện SDL2 cần thiết để phát triển game.
- **README.md:** Chứa thông tin mô tả về dự án, cách thiết lập và hướng dẫn sử dụng.
- **Run_Bro.sln:** File solution của Visual Studio, dùng để mở và quản lý dự án game.

## 6. Nguồn tham khảo
- Game được lấy ý tưởng từ game **Contra** và **Geometry Dash**.
- Tham khảo từ [Lazy Foo](http://lazyfoo.net/tutorials/SDL/) (sử dụng các hàm như `checkCollision`, `openFont`, `setTileType`, `time`).
- Cách chia file entity, renderwindow trên [YouTube](https://www.youtube.com/playlist?list=PL2RPjWnJduNmXHRYwdtublIPdlqocBoLS).
- Nhân vật, quái, tileset, music, và sfx trên trang itch io
- Cách vẽ map và thêm quái vật: [YouTube](https://www.youtube.com/watch?v=rLWlnPwR1uI&list=PL-K0viiuJ2RctP5nlJlqmHGeh66-GOZR_&index=14).

## 7. Hướng phát triển
- Tối ưu hóa game hơn.
- Tạo ra nhiều loại quái vật hơn.
- Vẽ map rộng và chi tiết hơn.
- Thêm chế độ chơi để người chơi có nhiều lựa chọn.

