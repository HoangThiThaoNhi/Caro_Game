#include "Guide.h"

void guide()
{
    system("cls"); // clear màn hình
    std::cout << "\033[93m" << "*------GUIDE------*" << "\033[0m" << std::endl;
    std::cout << "1. You have a 15 x 15 square chessboard" << std::endl;
    std::cout << "2. Enter the row and column positions in the console to make a move" << std::endl;
    std::cout << "3.If there are 5 consecutive X or O pieces in a row, column, or diagonal then you win" << std::endl;
    std::cout << "4.If your 5 pieces are blocked at both ends by the opponent's pieces, it does not count as a win" << std::endl;
    std::cout << "Press " << "\033[31m" << "ESC " << "\033[0m" << "to back MENU" << std::endl;
    while (true)
    {
        char input = getch(); // đọc 1 ký tự từ bàn phím
        if (input == 27)

            break;
    }
}