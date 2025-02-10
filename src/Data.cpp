#include "Data.h"

// Constructor default
Data::Data() {}

// Destructor
Data::~Data() {}

// Kiểm người chơi đã tồn tại trong file DataPlayer.txt hay chưa
bool Data::checkExistPlayer(Player &player)
{
    std::ifstream fileData("DataPlayer.txt"); // đọc file chứa dữ liệu người chơi
    std::string dataInLine;                   // chứa dữ liệu 1 dòng trong file

    // đọc từng dòng trong file cho tới khi không còn dòng nào
    while (std::getline(fileData, dataInLine))
    {
        int pos = dataInLine.find(':');

        // Kiểm tra xem tài khoản có tồn tại
        if (dataInLine.substr(0, pos) == player.getAccount())
        {
            storeDataToPlayer(player, dataInLine); // lưu dữ liệu WIN/LOSE/DRAW vào Player1
            fileData.close();
            return true;
        }
    }
    // Không tìm thấy tài khoản -> truyền vào ""
    storeDataToPlayer(player, "");
    fileData.close();
    return false;
}

void Data::insertNewPlayToFile(std::string account)
{
    std::ofstream fileData("DataPlayer.txt", std::ios::app); // mở và ghi vào cuối file
    std::ofstream rewatch("RewatchData.txt", std::ios::app);
    rewatch << account << ":" << std::endl;        // ghi tài khoản vào file để xem lại các trận đấu
    fileData << account << ": 0/0/0" << std::endl; // Thêm thông tin người chơi mới vào file
    fileData.close();
    rewatch.close();
}

// Lưu dữ liệu từ file DataPlayer.txt vào trong player
void Data::storeDataToPlayer(Player &player, std::string data)
{
    // Kiểm tra dữ liệu có tồn tại không
    if (data != "")
    {
        int pos = data.find(':');                                                    // tìm vị trí ':' trong chuỗi có dạng ACCOUT: WIN/LOSE/DRAW
        std::string matchInfor = data.substr(pos + 2, data.length() - pos - 1);      // lấy ra chuỗi WIN/LOSE/DRAW
        int pos1 = matchInfor.find('/');                                             // tìm vị trí dấu / đầu tiên
        int numWin = stoi(matchInfor.substr(0, pos1));                               // số trận thắng
        int pos2 = matchInfor.find('/', pos1 + 1);                                   // tìm vị trí dấu / thứ 2
        int numLose = stoi(matchInfor.substr(pos1 + 1, pos2 - pos1));                // số trận thua
        int numDraw = stoi(matchInfor.substr(pos2 + 1, matchInfor.length() - pos2)); // số trận hòa
        player.setWin(numWin);
        player.setLose(numLose);
        player.setDraw(numDraw);
    }
    else
    {
        // nếu người chơi chưa tồn tại thì khởi tạo tất cả = 0
        player.setWin(0);
        player.setLose(0);
        player.setLose(0);
    }
}

// Lưu dữ liệu sau trận đánh vào file ReWatchData.txt
void Data::storeDataToRewatch(std::vector<Move> &storeMove, Player &player1, Player &player2, std::string result1, std::string result2)
{
    std::ifstream inputFile("RewatchData.txt");
    std::ofstream tempFile("temp.txt"); // lưu dữ liệu mới nhất
    std::string line;
    while (std::getline(inputFile, line))
    {
        tempFile << line << std::endl;
        // tìm tài khoản cần ghi lại trận đấu
        if ((player1.getAccount() + ":") == line)
        {
            int orderMatch = player1.getWin() + player1.getLose() + player1.getDraw(); // lấy số thứ tự trận đã đánh tính cả trận vừa đánh
            // ghi lại các trận trước đó
            for (int i = 1; i <= orderMatch - 1; i++)
            {
                std::getline(inputFile, line);
                tempFile << line << std::endl;
            }
            // Ghi dữ liệu trận vừa đánh
            tempFile << orderMatch << ". " << player2.getAccount() << " - O - " << result2 << ":";
            for (Move &i : storeMove)
            {
                tempFile << " " << i.row << " " << i.column;
            }
            tempFile << std::endl;
        }
        else if ((player2.getAccount() + ":") == line)
        {
            int orderMatch = player2.getWin() + player2.getLose() + player2.getDraw(); // lấy số thứ tự trận đã đánh
            // ghi lại các trận trước đó
            for (int i = 1; i <= orderMatch - 1; i++)
            {
                std::getline(inputFile, line);
                tempFile << line << std::endl;
            }
            // Ghi dữ liệu trận vừa đánh
            tempFile << orderMatch << ". " << player1.getAccount() << " - X - " << result1 << ":";
            for (Move &i : storeMove)
            {
                tempFile << " " << i.row << " " << i.column;
            }
            tempFile << std::endl;
        }
    }

    inputFile.close();
    tempFile.close();

    std::string filePath = "RewatchData.txt"; // đường dẫn tới file
    remove(filePath.c_str());                 // Thay thế file gốc = file tạm thời
    rename("temp.txt", filePath.c_str());     // Đổi tên về file gốc
}

// Cập nhập trận thắng thua của người chơi khi kết thúc ván
void Data::updatePlayerToFile(Player &player)
{
    std::ifstream inputFile("DataPlayer.txt");
    std::ofstream tempFile("temp.txt"); // file ghi dữ liệu cập nhập từ file DataPlayer.txt
    std::string line;                   // lưu dữ một dòng trong file
    while (std::getline(inputFile, line))
    {
        std::istringstream ss(line);
        std::string account; // khi đọc sẽ chứa cả dấu : trong account
        int win, lose, draw;
        char delimiter; // đọc dấu phân cách

        // tách các thành phần
        ss >> account >> win >> delimiter >> lose >> delimiter >> draw;
        if ((player.getAccount() + ':') == account)
        {
            win = player.getWin();
            lose = player.getLose();
            draw = player.getDraw();
        }
        tempFile << account << " " << win << "/" << lose << "/" << draw << std::endl;
    }

    inputFile.close();
    tempFile.close();

    std::string filePath = "DataPlayer.txt"; // đường dẫn tới file
    remove(filePath.c_str());                // Thay thế file gốc = file tạm thời
    rename("temp.txt", filePath.c_str());    // Đổi tên về file gốc
}
