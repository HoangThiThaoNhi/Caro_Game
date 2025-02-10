#include "SearchPlayer.h"

void enterPlayerAccount(std::string &account)
{
    system("cls"); // Clear màn hình
    std::cout << "\033[93m" << "*------PLAYER'S INFORMATION------*" << "\033[0m" << std::endl;
    std::cout << "Enter the account you want to search: ";
    std::cin >> account;
}

void searchAccount(std::string &account)
{
    std::ifstream fileData("DataPlayer.txt"); // đọc file chứa dữ liệu người chơi
    std::string dataInLine;                   // chứa dữ liệu 1 dòng trong file
    Player searchPlayer;                      // người chơi cần tìm kiếm
    Player sameSearchPlayer;                  // người chơi có kết quả tìm kiếm trận thắng gần nhất với người cần tìm kiếm

    bool haveAccount = false;
    // đọc từng dòng trong file cho tới khi không còn dòng nào
    while (std::getline(fileData, dataInLine))
    {
        int pos = dataInLine.find(':');
        // Kiểm tra xem tài khoản có tồn tại
        if (dataInLine.substr(0, pos) == account)
        {
            std::string dataMatch = dataInLine.substr(pos + 2, dataInLine.size() - 1);
            std::istringstream ss(dataMatch);
            int numWin, numLose, numDraw;
            char delimiter; // đọc dấu phân cách

            // tách các thành phần
            ss >> numWin >> delimiter >> numLose >> delimiter >> numDraw;

            // set các giá trị vào player
            searchPlayer.setAccount(account);
            searchPlayer.setWin(numWin);
            searchPlayer.setLose(numLose);
            searchPlayer.setDraw(numDraw);

            std::cout << "Account: " << "\033[31m" << account << "\033[0m"
                      << " - Win: " << "\033[31m" << numWin << "\033[0m"
                      << " - Lose: " << "\033[31m" << numLose << "\033[0m"
                      << " - Draw: " << "\033[31m" << numDraw << "\033[0m" << std::endl;

            haveAccount = true;
            break;
        }
    }
    if (haveAccount == false)
    {
        std::cout << "Accout " << "\033[31m" << account << "\033[0m" << " does not exist!" << std::endl;
        return;
    }

    // Chuyển con trỏ về đầu file
    int min = 100;
    fileData.seekg(0, std::ios::beg);
    while (std::getline(fileData, dataInLine))
    {
        int pos = dataInLine.find(':');
        // Kiểm tra xem tài khoản có tồn tại
        if (dataInLine.substr(0, pos) != account)
        {
            std::string dataMatch = dataInLine.substr(pos + 2, dataInLine.size() - 1);
            std::istringstream ss(dataMatch);
            int numWin, numLose, numDraw;
            char delimiter; // đọc dấu phân cách

            // tách các thành phần
            ss >> numWin >> delimiter >> numLose >> delimiter >> numDraw;

            // tính tỷ lệ
            float rate;
            if (numWin != 0)
            {
                rate = (float)numWin / (numWin + numDraw + numLose) * 100;
            }
            else
            {
                rate = 0;
            }

            if (min > abs(rate - searchPlayer.getWinRate()))
            {
                // set các giá trị vào player
                sameSearchPlayer.setAccount(dataInLine.substr(0, pos));
                sameSearchPlayer.setWin(numWin);
                sameSearchPlayer.setLose(numLose);
                sameSearchPlayer.setDraw(numDraw);
                min = abs(rate - searchPlayer.getWinRate());
            }
        }
    }

    std::cout << "\033[31m" << "The player with the closest win rate:" << "\033[0m" << std::endl;
    std::cout << "Account: " << "\033[31m" << sameSearchPlayer.getAccount() << "\033[0m"
              << " - Win: " << "\033[31m" << sameSearchPlayer.getWin() << "\033[0m"
              << " - Lose: " << "\033[31m" << sameSearchPlayer.getLose() << "\033[0m"
              << " - Draw: " << "\033[31m" << sameSearchPlayer.getDraw() << "\033[0m" << std::endl;
}