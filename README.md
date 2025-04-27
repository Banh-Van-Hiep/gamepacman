1. PACMAN
  Thử nghiệm game: https://drive.google.com/file/d/17jG84l2Elz8p1WN2pnVVYySOd1QXHabd/view?usp=sharing
2. Giới thiệu game
  Pac-Man Clone là một trò chơi thuộc thể loại arcade cổ điển. Đắm mình vào mê cung đầy thử thách, bạn sẽ điều 
  khiển nhân vật Pac-Man ăn thức ăn và né tránh các Ghosts. Hãy cố gắng hết sức để sống sót, thu thập các vật phẩm sức 
  mạnh (Power-ups) để tăng tốc hoặc gia tăng mạng sống, đồng thời hoàn thành mục tiêu tiêu diệt 
  Ghosts hoặc ăn hết thức ăn để chiến thắng!

3. Về source code game:
  3.1 main.cpp 
    trong game Pac-Man Clone là điểm bắt đầu của chương trình. Nó thực hiện những nhiệm vụ chính sau:
    Khởi tạo game: Tạo cửa sổ, tài nguyên và trạng thái ban đầu.
    Vòng lặp chính: Xử lý sự kiện, cập nhật trạng thái của Pac-Man, Ghosts, và thức ăn, sau đó vẽ lên màn hình.
    Kiểm tra kết thúc: Xác định điều kiện thắng/thua.
    Dọn dẹp: Giải phóng tài nguyên khi game kết thúc.
    Code đảm bảo mọi logic của game được thực thi tuần tự trong một vòng lặp duy nhất.
  3.2 thongsochung.h:
    Đây là file tiêu đề chứa các khai báo thông số chung cho trò chơi:
    Kích thước bản đồ, số lượng Ghosts, và các tài nguyên game (âm thanh, hình ảnh).
    Class Game: Định nghĩa các phương thức chính như khởi tạo, xử lý sự kiện, cập nhật, vẽ màn 
    hình, và dọn dẹp tài nguyên.ỗ trợ quản lý Pac-Man, Ghosts, Foods, và UI (như điểm số, mạng sống).
  3.3 macode.cpp
    File triển khai logic chính:
    Khởi tạo game: Tải tài nguyên như Pac-Man, Ghosts, thức ăn, âm thanh.
    Xử lý sự kiện: Quản lý di chuyển Pac-Man, kích hoạt bom, thoát game.
    Cập nhật và vẽ: Điều chỉnh trạng thái game và hiển thị lên màn hình.
    Quản lý bom, reset, dọn dẹp: Xử lý logic bom, đặt lại trạng thái game, và giải phóng tài nguyên.
  3.4ghost.h và ghost.cpp
    ghost.h: Định nghĩa lớp Ghost, quản lý các hành vi và thuộc tính của Ghosts.
    Các phương thức chính:
    khoitaoghost: Khởi tạo vị trí và khung hình Ghost.
    capnhatvitri: Cập nhật vị trí Ghost dựa trên Pac-Man.
    ve: Vẽ Ghost lên màn hình.
    winORlost: Xử lý logic khi Ghost va chạm Pac-Man.
    ghost.cpp: Cài đặt chi tiết các phương thức trong ghost.h.
    Ghost di chuyển theo Pac-Man, tránh chướng ngại vật, và tương tác với Pac-Man (thắng/thua).
    Điều chỉnh tốc độ Ghost dựa trên số lượng thức ăn còn lại.
  foods.h và foods.cpp
    foods.h:
    Định nghĩa lớp Foods với các phương thức:
    khoitaofoods: Khởi tạo danh sách thức ăn dựa trên bản đồ.
    draw: Vẽ thức ăn lên màn hình.
    checkeating: Kiểm tra và xử lý khi Pac-Man ăn thức ăn.
    winORlost: Kiểm tra điều kiện thắng (ăn gần hết thức ăn).
    foods.cpp:
    Cài đặt chi tiết các phương thức:
    Khởi tạo: Xây dựng danh sách vị trí thức ăn từ bản đồ game.
    Vẽ thức ăn: Hiển thị từng thức ăn trên màn hình.
    Xử lý ăn: Tăng điểm và xóa thức ăn khi Pac-Man ăn.
    Kiểm tra thắng/thua: Thắng khi số thức ăn còn lại dưới 0.
  3.5 sucmanh.h và sucmanh.cpp
    sucmanh.h
    Định nghĩa lớp SucManh với các phương thức:
    capNhat: Cập nhật trạng thái hiển thị và thời gian tồn tại của sức mạnh.
    ve: Hiển thị sức mạnh trên màn hình.
    xuLyAn: Xử lý khi Pac-Man ăn sức mạnh.
    dangHienThi: Kiểm tra xem sức mạnh có đang hiển thị không.
    daAn: Kiểm tra xem sức mạnh đã bị ăn chưa.
    datLai: Đặt lại trạng thái sức mạnh.
    sucmanh.cpp
    Hiển thị sức mạnh: Sinh ngẫu nhiên vị trí trên bản đồ (nơi không có vật cản).
    Cập nhật trạng thái: Ẩn hoặc tái kích hoạt sức mạnh sau thời gian nhất định.
    Xử lý ăn: Khi Pac-Man ăn sức mạnh, kích hoạt hiệu ứng và tăng tốc trong một khoảng thời gian.
    Đặt lại: Đưa trạng thái sức mạnh về mặc định khi cần.
4. Cách chơi: Người chơi nhấn 4 phím mũi tên trên màn hình để di chuyển và chạy khỏi sự truy đuổi của
   Ghost (quái vật), đồng thời cố gắng ăn hết tất cả thục ăn trên bản đồ. Người chơi có thể kích hoạt bom(phím h)
   để đẩy Ghost về giữa bản đồ (chỉ khi trong bán kính bom và thời gian hồi bom đã về 0). Sau mỗi lần không
   có thời gian nhất định, sẽ có 2 viên sức mạnh xuất hiện, với chức năng tăng mạng và tăng tốc chạy cho
   Pac-Man (nếu không ăn, viên sức mạnh sẽ biến mất). Lưu ý, mỗi khi Ghost giết được Pac-Man, Ghost sẽ tăngtốc chạy.
5. Bắt đầu game:
   ![enter](https://github.com/user-attachments/assets/c14ed913-95c9-49fc-a72d-1aa1706dc7b1)

   nhấn phím Enter để tiếp tục.
6. Các thành phần trong game:
   
   ![pacman](https://github.com/user-attachments/assets/2773cd18-1a8d-4f9a-9f00-ee32ebd14345)    nhân vật Pac-Man
   
   ![ghosts](https://github.com/user-attachments/assets/5ca26446-51a1-4d10-a08b-a37683c3be80)    các con ma (Ghosts)

   2 loại vật phẩm tăng sức mạnh: thêm mạng và tăng tốc độ di chuyển
   
   ![tangmang](https://github.com/user-attachments/assets/fcb2bcb1-ca37-47be-89f6-8e7a846d6c6b)
   ![tangtoc](https://github.com/user-attachments/assets/38ff6553-f063-4b77-8d20-37eb88fc6b4f)

   ảnh viên thức ăn
   
   ![food](https://github.com/user-attachments/assets/d7149fb8-7f46-41f5-ab69-92596c868607)   

   Đây là bộ cục chính của game.
     1: Điểm, 2: Mạng, 3: Thời gian hồi bom, 4: Tường.

   ![Screenshot 2025-04-25 180853](https://github.com/user-attachments/assets/ee4efa50-05be-4701-911f-e53813af7506)

  Chiến thắng và thất bại
    Bạn sẽ chiến thắng nếu ăn được hết thục ăn trên bản đồ.
    ![win](https://github.com/user-attachments/assets/f201ae33-0daa-416a-bf6e-e08a1c3e66e5)
    
   (Bấm 'Restart' để chơi tiếp hoặc bấm 'Continue' để quay về.)

   Bạn sẽ thua nếu để Ghost giết hết số mạng bạn có.
   ![lose](https://github.com/user-attachments/assets/f1ded3fa-2cf2-41c5-acf1-7c6335b52987)

   (Bấm 'Continue' để chơi tiếp hoặc 'Menu' để quay về.
   


    



  
   







































