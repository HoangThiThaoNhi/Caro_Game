#include "Rewatch.h"

// Default constructor
Rewatch::Rewatch() {}

// Destructor
Rewatch::~Rewatch() {}

// lưu trữ lại các
void Rewatch::storeAccount()
{
    std::ifstream inputFile("DataPlayer.txt"); // Mở file chứa người chơi
    std::string line;                          // store a data line in file

    // lưu các tên tài khoản lại
    while (getline(inputFile, line))
    {
        Player tmp;
        std::istringstream ss(line);
        std::string account; // khi đọc sẽ chứa cả dấu : trong account
        int win, lose, draw;
        char delimiter; // đọc dấu phân cách

        // tách các thành phần
        ss >> account >> win >> delimiter >> lose >> delimiter >> draw;
        account = account.substr(0, account.size() - 1);
        tmp.setAccount(account);
        tmp.setWin(win);
        tmp.setLose(lose);
        tmp.setDraw(draw);
        mPlayers.push_back(tmp);
    }
    inputFile.close();
}

// Nhập tài khoản
bool Rewatch::enterAccount()
{
    std::cout << "Enter account: ";
    std::cin.ignore();
    std::getline(std::cin, mAccountRewatch); // Nhập trài khoản muốn xem lại

    // Kiểm tra tài khoản có tồn tại không
    for (Player &tmp : mPlayers)
    {
        if (tmp.getAccount() == mAccountRewatch)
        {
            mNumMatch = tmp.getWin() + tmp.getLose() + tmp.getDraw();
            return true;
        }
    }
    return false;
}

// Nhập trận muốn xem lại
bool Rewatch::enterMatchWantRewatch(int &selection)
{
    while (true)
    {
        std::cout << "Enter selection: ";
        std::cin >> selection;
        if (selection == 0)
            return false;
        if (selection < 0 || selection > mNumMatch)
        {
            std::cout << RED_CHERRY << "Invalid valid. Please re-enter!" << DEFAULT_COLOR << std::endl;
        }
        else
        {
            break;
        }
    }
    return true;
}

// lưu trữ dữ liệu trận đấu muốn xem lại
void Rewatch::storeDataMatchWantReWatch(int &selection)
{
    int pos = mDataRewatch[selection - 1].find(':'); // tìm dấu ngăn cách dữ liệu

    // Lưu trữ thông tin tài khoản đối thủ, lượt đánh, kết quả trận đấu
    std::string inforOpponent = mDataRewatch[selection - 1].substr(0, pos);
    std::string order;
    char delimiter; // dấu '-'
    std::istringstream ss1(inforOpponent);
    ss1 >> order >> mNameOppenent >> delimiter >> mTick >> delimiter >> mResult;

    // Lưu dữ liệu các nước đi
    std::string turnString = mDataRewatch[selection - 1].substr(pos + 1, mDataRewatch[selection - 1].size()); // chuỗi các nước di chuyển
    std::istringstream ss2(turnString);
    Move tmp;
    while (ss2 >> tmp.row >> tmp.column)
    {
        mTurns.push_back(tmp);
    }
}

// show các trận đã đánh
void Rewatch::showMatchFought()
{
    std::ifstream inputFile("RewatchData.txt"); // Mở file chứa dữ liệu các trận đánh
    std::string line;

    while (std::getline(inputFile, line))
    {
        if (line == (mAccountRewatch + ':'))
        {
            std::cout << RED_CHERRY << "0. Back to MENU" << DEFAULT_COLOR << std::endl;
            int num = 0;
            while (num < mNumMatch)
            {
                std::getline(inputFile, line);
                mDataRewatch.push_back(line);
                std::cout << line.substr(0, line.find('-') - 1) << std::endl;
                num++;
            }
        }
    }
    inputFile.close();
}

// in ra bảng với thông tin tổng quan
void Rewatch::printInformationMatchRewatch(int currentRow, int currenColumn)
{
    if (mTick == "O")
    {
        std::cout << std::setw(8) << " " << "Player1 " << RED_CHERRY << mAccountRewatch << DEFAULT_COLOR << " - X" << std::setw(8) << " ";
        std::cout << "|" << std::setw(8) << " " << "Player2 " << RED_CHERRY << mNameOppenent << DEFAULT_COLOR << " - O" << std::endl;
    }
    else
    {
        std::cout << std::setw(8) << " " << "Player1 " << RED_CHERRY << mNameOppenent << DEFAULT_COLOR << " - X" << std::setw(8) << " ";
        std::cout << "|" << std::setw(8) << " " << "Player2 " << RED_CHERRY << mAccountRewatch << DEFAULT_COLOR << " - O" << std::endl;
    }
    mBoard.printBoard(currentRow, currenColumn);
    std::cout << "Press " << RED_CHERRY << "ENTER " << DEFAULT_COLOR << "to watch next turn" << std::endl;
    std::cout << "Press " << RED_CHERRY << "BACKSPACE " << DEFAULT_COLOR << "to watch previous turn" << std::endl;
    std::cout << "Press " << RED_CHERRY << "ESC " << DEFAULT_COLOR << "to end watching" << std::endl;
}

bool Rewatch::rewatch()
{
    storeAccount();
    system("cls"); // Clear màn hình
    std::cout << YELLOW << "*------REWATCH------*" << DEFAULT_COLOR << std::endl;
    if (enterAccount() == false)
    {
        std::cout << RED_CHERRY << "Not exist account!" << DEFAULT_COLOR << std::endl;
        return false; // để in ra người chơi không tồn tại trong main
    }
    int selection;
    std::cout << RED_CHERRY << "Matches took place" << DEFAULT_COLOR << std::endl;
    showMatchFought();

    // Nhập trận đấu muốn xem lại nếu = 0 thì kết thúc chương trình
    if (enterMatchWantRewatch(selection) == false)
    {
        return true;
    }

    // lưu trữ thông tin trận đấu muốn xem lại
    storeDataMatchWantReWatch(selection);

    int currentWatchTurn = 0; // Nước đi hiện tại đang xem
    system("cls");            // Clear màn hình

    // Hiển thị bàn cờ khi chưa đánh
    printInformationMatchRewatch(0, 0);
    while (true)
    {
        char input = getch(); // đọc 1 ký tự từ bàn phím
        if (input == '\r')
        { // Ấn Enter
            if (currentWatchTurn < static_cast<int>(mTurns.size()))
            {
                system("cls"); // Clear màn hình
                mBoard.getNodes()[mTurns[currentWatchTurn].row][mTurns[currentWatchTurn].column] = (currentWatchTurn % 2 == 0) ? 'X' : 'O';
                printInformationMatchRewatch(mTurns[currentWatchTurn].row, mTurns[currentWatchTurn].column);
                currentWatchTurn++; // tăng nước đi lên kế tiếp
                if (currentWatchTurn == static_cast<int>(mTurns.size()))
                {
                    if (mResult == "WIN")
                    {
                        std::cout << RED_CHERRY << mNameOppenent << " is a winner" << DEFAULT_COLOR << std::endl;
                    }
                    else
                    {
                        std::cout << RED_CHERRY << mAccountRewatch << " is a winner" << DEFAULT_COLOR << std::endl;
                    }
                }
            }
        }
        else if (input == '\b')
        { // Ấn Backspace
            if (currentWatchTurn > 0)
            {
                system("cls");      // Clear màn hình
                currentWatchTurn--; // nước đi trước
                mBoard.getNodes()[mTurns[currentWatchTurn].row][mTurns[currentWatchTurn].column] = ' ';
                printInformationMatchRewatch(mTurns[currentWatchTurn].row, mTurns[currentWatchTurn].column);
            }
        }
        else if (input == 27) // Ấn Esc
        {
            return true;
        }
    }
}