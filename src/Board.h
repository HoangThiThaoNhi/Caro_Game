#ifndef _BOARD_H
#define _BOARD_H

#include <iostream>
#include <vector>

// Khai báo các mã màu
const std::string DEFAULT_COLOR = "\033[0m";
const std::string YELLOW = "\033[93m";
const std::string RED_CHERRY = "\033[31m";

// Size của board
const int SIZE_BOARD = 15;

// Lượt đánh
const int PLAYER_X = 1;
const int PLAYER_O = 2;

// Kiểu dữ liệu cho giá trị nước đi
typedef struct
{
    int row;
    int column;
} Move;

class Board
{
private:
    int mRow;
    int mColumn;
    std::vector<std::vector<char>> mNodes; // 1 mảng 2 chiều chứa các node, mỗi node ứng với 1 ô trống trong Board

public:
    Board();
    ~Board();
    void printBoard(int currentRow, int currentColumn); // in ra bảng với màu vàng và tô màu đỏ nước vừa đánh
    std::vector<std::vector<char>> &getNodes();         // trả về vector mNodes để có thể truy cập vào vector
    bool checkWin(int playerTurn);                      // Kiểm tra điều kiện thắng
    bool checkFullBoard();                              // kiểm tra board đã đánh hết chưa
    bool isValidMove(int row, int col);
};

#endif
