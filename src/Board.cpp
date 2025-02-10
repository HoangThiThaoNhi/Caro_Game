#include "Board.h"

// constructor
Board::Board() : mRow(SIZE_BOARD), mColumn(SIZE_BOARD)
{
    mNodes.resize(mRow, std::vector<char>(mColumn, ' ')); // thay đổi kích thước mNodes thành mRow hàng và mỗi hàng chứa mColum phần tử với giá trị là ' '
}

Board::~Board() {}

// in ra bảng với màu vàng và in đỏ với nước đi vừa đánh
void Board::printBoard(int currentRow, int currentColumn)
{
    // in ra số thứ tự cột
    std::cout << "   ";
    for (int i = 0; i < SIZE_BOARD; i++)
    {
        if (i >= 10)
            std::cout << "  " << i;
        else
            std::cout << "  " << i << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < mRow; i++)
    {
        // in ra ngăn cách
        std::cout << YELLOW << "   |";
        for (int m = 0; m < SIZE_BOARD; m++)
        {
            std::cout << "---|";
        }
        std::cout << DEFAULT_COLOR << std::endl;

        // In chỉ số hàng và các giá trị trong hàng
        if (i < 10)
            std::cout << i << "  ";
        else
            std::cout << i << " ";
        for (int j = 0; j < mColumn; j++)
        {
            if (i == currentRow && j == currentColumn)
            {
                std::cout << YELLOW << "| " << RED_CHERRY << mNodes[i][j] << YELLOW << " "; // in ra ô vừa đánh với màu đỏ
            }
            else
            {
                std::cout << YELLOW << "| " << mNodes[i][j] << " "; // in ra giá trị của mỗi ô
            }
        }
        std::cout << "|" << std::endl;
    }

    // In hàng ngăn cách cuối cùng
    std::cout << YELLOW << "   |";
    for (int m = 0; m < SIZE_BOARD; m++)
    {
        std::cout << "---|";
    }
    std::cout << DEFAULT_COLOR << std::endl;
}

// trả về vector mNodes để có thể truy cập vào vector
std::vector<std::vector<char>> &Board::getNodes()
{
    return mNodes;
}

bool Board::checkWin(int playerTurn)
{
    char tick = (playerTurn == PLAYER_X) ? 'X' : 'O'; // kiểm tra là 'X' hay 'O'
    char tickOpponent = (tick == 'X') ? 'O' : 'X';    // lấy ngược lại
    
    // Check hàng ngang và dọc
    for (int i = 0; i < SIZE_BOARD; i++)
    {
        for (int j = 0; j < SIZE_BOARD - 4; j++)
        {
            // Kiểm tra hàng ngang
            if (mNodes[i][j] == tick &&
                mNodes[i][j + 1] == tick &&
                mNodes[i][j + 2] == tick &&
                mNodes[i][j + 3] == tick &&
                mNodes[i][j + 4] == tick &&
                (j == 0 || mNodes[i][j - 1] != tickOpponent || // Chặn 2 đầu
                 j + 4 == SIZE_BOARD - 1 || mNodes[i][j + 5] != tickOpponent))
            {
                return true;
            }

            // Kiểm tra hàng dọc
            if (mNodes[j][i] == tick &&
                mNodes[j + 1][i] == tick &&
                mNodes[j + 2][i] == tick &&
                mNodes[j + 3][i] == tick &&
                mNodes[j + 4][i] == tick &&
                (j == 0 || mNodes[j - 1][i] != tickOpponent || // Chặn 2 đầu
                 j + 4 == SIZE_BOARD - 1 || mNodes[j + 5][i] != tickOpponent))
            {
                return true;
            }
        }
    }

    // Kiểm tra đường chéo chính và đường chéo phụ
    for (int i = 0; i < SIZE_BOARD - 4; i++)
    {
        for (int j = 0; j < SIZE_BOARD - 4; j++)
        {
            // Kiểm tra đường chéo chính
            if (mNodes[i][j] == tick &&
                mNodes[i + 1][j + 1] == tick &&
                mNodes[i + 2][j + 2] == tick &&
                mNodes[i + 3][j + 3] == tick &&
                mNodes[i + 4][j + 4] == tick &&
                ((i == 0 || j == 0) || mNodes[i - 1][j - 1] != tickOpponent || // Chặn 2 đầu
                 i + 4 == SIZE_BOARD - 1 || j + 4 == SIZE_BOARD - 1 || mNodes[i + 5][j + 5] != tickOpponent))
            {
                return true;
            }

            // Kiểm tra đường chéo phụ
            if (mNodes[i][SIZE_BOARD - 1 - j] == tick &&
                mNodes[i + 1][SIZE_BOARD - 2 - j] == tick &&
                mNodes[i + 2][SIZE_BOARD - 3 - j] == tick &&
                mNodes[i + 3][SIZE_BOARD - 4 - j] == tick &&
                mNodes[i + 4][SIZE_BOARD - 5 - j] == tick &&
                ((i == 0 || j == 0) || mNodes[i - 1][SIZE_BOARD - j] != tickOpponent || // Chặn 2 đầu
                 i + 4 == SIZE_BOARD - 1 || SIZE_BOARD - 4 - j == SIZE_BOARD - 1 || mNodes[i + 5][SIZE_BOARD - 6 - j] != tickOpponent))
            {
                return true;
            }
        }
    }

    return false;
}

// Kiểm tra Board đã được đánh hết chưa
bool Board::checkFullBoard()
{
    for (int i = 0; i < SIZE_BOARD; i++)
    {
        for (int j = 0; j < SIZE_BOARD; j++)
        {
            if (mNodes[i][j] == ' ')
            {
                return false;
            }
        }
    }
    return true;
}

// Hàm kiểm tra vị trí có hợp lệ không
bool Board::isValidMove(int row, int col)
{
    return (row >= 0 && row < SIZE_BOARD && col >= 0 && col < SIZE_BOARD && mNodes[row][col] == ' ');
}
