# Caro Game

Caro Game (Tic-Tac-Toe) là một trò chơi phổ biến giữa hai người chơi, trong đó mỗi người cố gắng xếp 3 dấu (X hoặc O) liên tiếp theo một hàng, một cột hoặc đường chéo. Dự án này là một phiên bản trò chơi Caro được triển khai bằng C++, hỗ trợ chế độ chơi 2 người đối kháng hoặc với máy.

## 📜 Mục tiêu dự án

- Phát triển một trò chơi Caro đơn giản nhưng đầy đủ chức năng với giao diện dòng lệnh (CLI).
- Học và áp dụng các kiến thức về lập trình hướng đối tượng (OOP) trong C++.
- Xây dựng một phần mềm có thể mở rộng và dễ dàng bảo trì.

## 🚀 Tính năng chính

- **Chế độ chơi 2 người**: Người chơi có thể chơi đối kháng với nhau.
- **Giao diện dòng lệnh đơn giản**: Hiển thị bảng trò chơi rõ ràng và dễ hiểu.
- **Kiểm tra kết quả tự động**: Phát hiện người chiến thắng hoặc khi trò chơi kết thúc hòa.
- **Quản lý trò chơi thông minh**: Kiểm tra các trạng thái của bảng, giúp người chơi có trải nghiệm thú vị và không bị gián đoạn.

## 📋 Yêu cầu hệ thống

- **Hệ điều hành**: Windows, Linux, macOS
- **Trình biên dịch**: GCC, Clang hoặc bất kỳ trình biên dịch C++ nào.
- **Công cụ phát triển**: Visual Studio Code, Code::Blocks hoặc bất kỳ IDE hỗ trợ C++.

## 🔧 Hướng dẫn cài đặt

### 1. Clone dự án về máy

```bash
git clone https://github.com/HoangThiThaoNhi/Caro_Game.git

### 2. Biên dịch mã nguồn
Sau khi tải về, sử dụng trình biên dịch C++ của bạn để biên dịch dự án. Nếu sử dụng GCC, bạn có thể biên dịch mã nguồn bằng lệnh:

bash
Sao chép
Chỉnh sửa
g++ -o CaroGame main.cpp Board.cpp Data.cpp
Nếu bạn sử dụng IDE như Visual Studio Code hoặc Code::Blocks, chỉ cần mở thư mục dự án và biên dịch như bình thường.

3. Chạy trò chơi
Sau khi biên dịch thành công, bạn có thể chạy trò chơi từ dòng lệnh (terminal):

bash
Sao chép
Chỉnh sửa
./CaroGame
4. Cách chơi
Chế độ 2 người: Người chơi thay phiên nhau chọn ô trống trên bảng để đặt dấu X hoặc O.
Chế độ chơi với máy: Bạn sẽ chơi với máy tính, cố gắng chiến thắng trong trò chơi.
Bạn sẽ được yêu cầu nhập chỉ số hàng và cột để đặt dấu X hoặc O trên bảng.
