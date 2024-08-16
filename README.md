# Run Bro! - Khoi Nguyen Code

## Giới thiệu bản thân:
- Họ tên: Nguyễn Tấn Khôi
- MSSV: 22025526
- Lớp: INT2215 70

## Video demo :

## Giới thiệu game
**Run Bro!** Hãy chạy thật nhanh để không bị những cái gai sắc nhọn đến từ phía bên trái của bạn đâm vào. Trong lúc cố gắng chạy để thoát khỏi những cái gai, bạn sẽ đối mặt với quái vật và các cạm bẫy nguy hiểm, đòi hỏi sự khéo léo và chiến lược để vượt qua.

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

## 0. Cách tải game

### 0.a Cách 1: Không bao gồm code
Tải game (được nén thành `.zip`) tại link sau: [link tải game](#)  
Giải nén game vào một thư mục và bật `Run_Bro.exe` lên để chơi. Cách này tiết kiệm bộ nhớ và thời gian tải.

### 0.b Cách 2: Bao gồm code và có thể biên dịch
1. Clone repo này về máy hoặc chọn **Code** -> **Download ZIP**.
2. Yêu cầu có **Visual Studio 2022 Community** và gói C++ cần thiết.
3. Mở file `Run_Bro.sln` để tự động mở dự án trong Visual Studio.
4. Chọn **Local Windows Debugger** để khởi động game (chọn **Debug**, **x64**).

## 1. Bắt đầu game
Chờ một chút để menu hiện ra, click vào nút có biểu tượng "Play" để bắt đầu chơi game. Bấm vào nút có biểu tượng "Exit" nếu muốn thoát game.

## 2. Các thành phần trong game
- **Player:** Hình ảnh nhân vật chính.
- **Monster:** Hình ảnh quái vật.
- **Score:** Điểm số hiện tại.
- **Best score:** Điểm cao nhất bạn đạt được.
- **Tile map:** Kỹ thuật tilemap dùng để tạo phần level cho bản đồ.
- **Nút restart:** Dùng để chơi lại ván mới.
- **Nút exit:** Dùng để thoát trò chơi.

## 3. Cách chơi
Bạn cần phải cố gắng chạy và vượt quá các chướng ngại vật trên đường, đánh bại hoặc cố gắng né các con quái vật trên đường đi để có thể chạy tiếp về phía trước và thoát khỏi đống gai chết chóc đang đuổi theo bạn.

**Điều khiển:**
- **Di chuyển:** ↑ (Lên), ↓ (Xuống), ← (Trái), → (Phải)
- **Chém:** SPACE
- **Tạm dừng:** Esc

**Đồ họa:** Tự vẽ từ tileset trên [Itch.io](https://incolgames.itch.io/dungeon-platformer-tile-set-pixel-art).

## 4. Chiến thắng
Trong game này, mục tiêu của người chơi không phải là đạt đến một đích cụ thể hay chiến thắng mà là cố gắng đạt được số điểm cao nhất có thể. Game thuộc thể loại endless runner, nghĩa là nhân vật sẽ tiếp tục chạy qua các bản đồ và đối mặt với những thử thách không ngừng nghỉ. Điểm số sẽ được tính dựa trên khoảng cách mà người chơi đã chạy được và số quái vật đã tiêu diệt. Khi nhân vật gặp phải chướng ngại vật hoặc bị quái vật hạ gục, trò chơi sẽ kết thúc và điểm số cao nhất sẽ được ghi lại. Người chơi có thể thử lại nhiều lần để phá vỡ kỷ lục của chính mình.

## 5. Về source code
- **Folder `Run_Bro`:** Chứa toàn bộ mã nguồn của game, bao gồm các file `.cpp` và `.h`.
- **Folder `library`:** Chứa thư viện SDL2 cần thiết để phát triển game.
- **.gitattributes và .gitignore:** Giúp quản lý phiên bản của dự án khi sử dụng Git.
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

