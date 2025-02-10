#include "MatchBot.h"

// Định nghĩa mảng tấn công và phòng thủ
int attackScore[10] = {0, 3, 24, 192, 1536, 12288, 98304, 531441, 4782969, 500000000};
int defendScore[10] = {0, 2, 18, 140, 800, 8000, 70569, 350000, 30000000, 300000000};

// Default constructor
MatchBot::MatchBot() {}

// Destructor
MatchBot::~MatchBot() {}

// in thông tin lượt đánh
void MatchBot::printInforTurn()
{
    if (mOrderTurn == PLAYER_X)
    {
        std::cout << std::setw(12) << " " << RED_CHERRY << "PLAYER - X" << DEFAULT_COLOR << std::setw(11) << " ";
        std::cout << "|" << std::setw(10) << " " << RED_CHERRY << "BOT - O" << DEFAULT_COLOR << std::endl;
    }
    else if (mOrderTurn == PLAYER_O)
    {
        std::cout << std::setw(11) << " " << RED_CHERRY << "BOT - X" << DEFAULT_COLOR << std::setw(10) << " ";
        std::cout << "|" << std::setw(10) << " " << RED_CHERRY << "PLAYER - O" << DEFAULT_COLOR << std::endl;
    }
}

void MatchBot::enterMode()
{
    std::cout << RED_CHERRY << "1.Easy " << DEFAULT_COLOR << "mode" << std::endl;
    std::cout << RED_CHERRY << "2.Normal " << DEFAULT_COLOR << "mode" << std::endl;
    std::cout << RED_CHERRY << "3.Hard " << DEFAULT_COLOR << "mode" << std::endl;
    std::cout << RED_CHERRY << "4.Back " << DEFAULT_COLOR << "to MAIN MENU" << std::endl;
    std::cout << "Enter number to choice: ";
    while (true)
    {
        std::cin >> mMode;
        if (mMode >= 1 && mMode <= 4)
        {
            break;
        }
        else
        {
            std::cout << RED_CHERRY << "Invalid enter. Please enter again!" << DEFAULT_COLOR << std::endl;
            std::cout << "Enter number to choice: ";
        }
    }
}

void MatchBot::enterOrderPlayerTurn() // Chọn lượt đánh
{
    std::cout << "Playing order:  " << RED_CHERRY << "1 - X" << DEFAULT_COLOR << " && " << RED_CHERRY << "2 - O" << DEFAULT_COLOR << std::endl;
    std::cout << "Choose playing order(" << RED_CHERRY << "1" << DEFAULT_COLOR << " or " << RED_CHERRY << "2" << DEFAULT_COLOR << "): ";
    while (true)
    {
        std::cin >> mOrderTurn;
        if (mOrderTurn == PLAYER_X || mOrderTurn == PLAYER_O)
        {
            break;
        }
        else
        {
            std::cout << RED_CHERRY << "Invalid enter. Please enter again!" << DEFAULT_COLOR << std::endl;
            std::cout << "Choose playing order" << RED_CHERRY << "(1 or 2): " << DEFAULT_COLOR;
        }
    }
}

void MatchBot::enterValidMove(Move &turn)
{
    char tick = (mOrderTurn == PLAYER_X) ? 'X' : 'O'; // lưu dấu đánh của người chơi
    do
    {
        std::cout << "Player turn: ";
        std::cin >> turn.row >> turn.column;
        if (!mBoard.isValidMove(turn.row, turn.column))
        {
            std::cout << RED_CHERRY << "Invalid turn.Please enter again!" << DEFAULT_COLOR << std::endl;
        }
    } while (!mBoard.isValidMove(turn.row, turn.column));
    mBoard.getNodes()[turn.row][turn.column] = tick; // cập nhập bàn cờ với nước đi vừa nhập
}

// Tính điểm tấn công dọc
int MatchBot::attackVertical(int row, int column, int mode)
{
    char tickPlayer = (mOrderTurn == PLAYER_X) ? 'X' : 'O'; // lưu dấu đánh của người chơi
    char tickBot = (tickPlayer == 'X') ? 'O' : 'X';         // lưu dấu đánh của bot
    int point = 0;                                          // tính điểm
    int ally = 0;                                           // đếm số đồng minh
    int enemy = 0;                                          // đếm số quan địch
    for (int count = 1; count < 6 && row + count < SIZE_BOARD; count++)
    {
        if (mBoard.getNodes()[row + count][column] == tickBot)
            ally++;
        else if (mBoard.getNodes()[row + count][column] == tickPlayer)
        {
            enemy++;
            break;
        }
        else
        { // Chưa đánh
            break;
        }
    }

    for (int count = 1; count < 6 && row - count >= 0; count++)
    {
        if (mBoard.getNodes()[row - count][column] == tickBot)
            ally++;
        else if (mBoard.getNodes()[row - count][column] == tickPlayer)
        {
            enemy++;
            break;
        }
        else
        { // Chưa đánh
            break;
        }
    }

    // Tính điểm
    if (mode == 1)
    {
        if (enemy == 2) // chặn 2 đầu
            return 0;
        point -= defendScore[enemy + 1] * 2;
        point += attackScore[ally];
    }
    else if (mode == 2)   
    {
        if (enemy == 2) // chặn 2 đầu
            return 0;
        point -= defendScore[enemy];
        point += attackScore[ally] * 2;
    }
    else if (mode == 3)
    {
        point = attackScore[ally];
        if (ally == 4)
            point = attackScore[9]; // Có 4 quân ta thì ưu tiên đánh
        if (enemy == 2)             // bị chặn 2 đầu
            return 0;
        else if (enemy == 1)
            point /= 2; // Bị chặn 1 đầu ->giảm điểm
    }

    return point;
}

// tính điểm tấn công ngang
int MatchBot::attackHorizontal(int row, int column, int mode)
{
    char tickPlayer = (mOrderTurn == PLAYER_X) ? 'X' : 'O'; // lưu dấu đánh của người chơi
    char tickBot = (tickPlayer == 'X') ? 'O' : 'X';         // lưu dấu đánh của bot
    int point = 0;                                          // tính điểm
    int ally = 0;                                           // đếm số đồng minh
    int enemy = 0;                                          // đếm số quan địch
    for (int count = 1; count < 6 && column + count < SIZE_BOARD; count++)
    {
        if (mBoard.getNodes()[row][column + count] == tickBot)
            ally++;
        else if (mBoard.getNodes()[row][column + count] == tickPlayer)
        {
            enemy++;
            break;
        }
        else
        { // Chưa đánh
            break;
        }
    }

    for (int count = 1; count < 6 && column - count >= 0; count++)
    {
        if (mBoard.getNodes()[row][column - count] == tickBot)
            ally++;
        else if (mBoard.getNodes()[row][column - count] == tickPlayer)
        {
            enemy++;
            break;
        }
        else
        { // Chưa đánh
            break;
        }
    }

    // Tính điểm
    if (mode == 1)
    {
        if (enemy == 2) // chặn 2 đầu
            return 0;
        point -= defendScore[enemy + 1] * 2;
        point += attackScore[ally];
    }
    else if (mode == 2)
    {
        if (enemy == 2) // chặn 2 đầu
            return 0;
        point -= defendScore[enemy];
        point += attackScore[ally] * 2;
    }
    else if (mode == 3)
    {
        point = attackScore[ally];
        if (ally == 4)
            point = attackScore[9]; // Có 4 quân ta thì ưu tiên đánh
        if (enemy == 2)             // bị chặn 2 đầu
            return 0;
        else if (enemy == 1)
            point /= 2; // Bị chặn 1 đầu ->giảm điểm
    }

    return point;
}

// Tính điểm tấn công chéo ngược
int MatchBot::attackDiagonalReverse(int row, int column, int mode)
{
    char tickPlayer = (mOrderTurn == PLAYER_X) ? 'X' : 'O'; // lưu dấu đánh của người chơi
    char tickBot = (tickPlayer == 'X') ? 'O' : 'X';         // lưu dấu đánh của bot
    int point = 0;                                          // tính điểm
    int ally = 0;                                           // đếm số đồng minh
    int enemy = 0;                                          // đếm số quan địch
    for (int count = 1; count < 6 && row - count >= 0 && column + count < SIZE_BOARD; count++)
    {
        if (mBoard.getNodes()[row - count][column + count] == tickBot)
            ally++;
        else if (mBoard.getNodes()[row - count][column + count] == tickPlayer)
        {
            enemy++;
            break;
        }
        else
        { // Chưa đánh
            break;
        }
    }

    for (int count = 1; count < 6 && row + count < SIZE_BOARD && column - count >= 0; count++)
    {
        if (mBoard.getNodes()[row + count][column - count] == tickBot)
            ally++;
        else if (mBoard.getNodes()[row + count][column - count] == tickPlayer)
        {
            enemy++;
            break;
        }
        else
        { // Chưa đánh
            break;
        }
    }

    // Tính điểm
    if (mode == 1)
    {
        if (enemy == 2) // chặn 2 đầu
            return 0;
        point -= defendScore[enemy + 1] * 2;
        point += attackScore[ally];
    }
    else if (mode == 2)
    {
        if (enemy == 2) // chặn 2 đầu
            return 0;
        point -= defendScore[enemy];
        point += attackScore[ally] * 2;
    }
    else if (mode == 3)
    {
        point = attackScore[ally];
        if (ally == 4)
            point = attackScore[9]; // Có 4 quân ta thì ưu tiên đánh
        if (enemy == 2)             // bị chặn 2 đầu
            return 0;
        else if (enemy == 1)
            point /= 2; // Bị chặn 1 đầu ->giảm điểm
    }

    return point;
}

// tính điểm tấn công chéo xuôi
int MatchBot::attackDiagonalForward(int row, int column, int mode)
{
    char tickPlayer = (mOrderTurn == PLAYER_X) ? 'X' : 'O'; // lưu dấu đánh của người chơi
    char tickBot = (tickPlayer == 'X') ? 'O' : 'X';         // lưu dấu đánh của bot
    int point = 0;                                          // tính điểm
    int ally = 0;                                           // đếm số đồng minh
    int enemy = 0;                                          // đếm số quan địch
    for (int count = 1; count < 6 && row + count < SIZE_BOARD && column + count < SIZE_BOARD; count++)
    {
        if (mBoard.getNodes()[row + count][column + count] == tickBot)
            ally++;
        else if (mBoard.getNodes()[row + count][column + count] == tickPlayer)
        {
            enemy++;
            break;
        }
        else
        { // Chưa đánh
            break;
        }
    }

    for (int count = 1; count < 6 && row - count >= 0 && column - count >= 0; count++)
    {
        if (mBoard.getNodes()[row - count][column - count] == tickBot)
            ally++;
        else if (mBoard.getNodes()[row - count][column - count] == tickPlayer)
        {
            enemy++;
            break;
        }
        else
        { // khoang trang
            break;
        }
    }

    // Tính điểm
    if (mode == 1)
    {
        if (enemy == 2) // chặn 2 đầu
            return 0;
        point -= defendScore[enemy + 1] * 2;
        point += attackScore[ally];
    }
    else if (mode == 2)
    {
        if (enemy == 2) // chặn 2 đầu
            return 0;
        point -= defendScore[enemy];
        point += attackScore[ally] * 2;
    }
    else if (mode == 3)
    {
        point = attackScore[ally];
        if (ally == 4)
            point = attackScore[9]; // Có 4 quân ta thì ưu tiên đánh
        if (enemy == 2)             // bị chặn 2 đầu
            return 0;
        else if (enemy == 1) // Bị chặn 1 đầu ->giảm điểm
            point /= 2;
    }

    return point;
}

// tính điểm phòng thủ dọc
int MatchBot::defendVertical(int row, int column, int mode)
{
    char tickPlayer = (mOrderTurn == PLAYER_X) ? 'X' : 'O'; // lưu dấu đánh của người chơi
    char tickBot = (tickPlayer == 'X') ? 'O' : 'X';         // lưu dấu đánh của bot
    int point = 0;                                          // tính điểm
    int ally = 0;                                           // đếm số đồng minh
    int enemy = 0;                                          // đếm số quan địch
    for (int count = 1; count < 6 && row + count < SIZE_BOARD; count++)
    {
        if (mBoard.getNodes()[row + count][column] == tickBot)
        {
            ally++;
            break;
        }
        else if (mBoard.getNodes()[row + count][column] == tickPlayer)
        {
            enemy++;
        }
        else
        { // Chưa đánh
            break;
        }
    }

    for (int count = 1; count < 6 && row - count >= 0; count++)
    {
        if (mBoard.getNodes()[row - count][column] == tickBot)
        {
            ally++;
            break;
        }
        else if (mBoard.getNodes()[row - count][column] == tickPlayer)
        {
            enemy++;
        }
        else
        { // Chưa đánh
            break;
        }
    }

    // Tính điểm
    if (mode == 1 || mode == 2)
    {
        if (ally == 2)
            return 0;
        point += defendScore[enemy];
    }
    else if (mode == 3)
    {
        point = defendScore[enemy];
        if (enemy == 4)
            point = defendScore[9]; // Có 4 quân địch->ưu tiên chặn
        if (ally == 2)              // đã chặn 2 đầu
            return 0;
        else if (ally == 1)
            point /= 2; // Bị chặn2 đầu ->giảm điểm
    }

    return point;
}

// tính điểm phòng thủ ngang
int MatchBot::defendHorizontal(int row, int column, int mode)
{
    char tickPlayer = (mOrderTurn == PLAYER_X) ? 'X' : 'O'; // lưu dấu đánh của người chơi
    char tickBot = (tickPlayer == 'X') ? 'O' : 'X';         // lưu dấu đánh của bot
    int point = 0;                                          // tính điểm
    int ally = 0;                                           // đếm số đồng minh
    int enemy = 0;                                          // đếm số quan địch
    for (int count = 1; count < 6 && column + count < SIZE_BOARD; count++)
    {
        if (mBoard.getNodes()[row][column + count] == tickBot)
        {
            ally++;
            break;
        }
        else if (mBoard.getNodes()[row][column + count] == tickPlayer)
        {
            enemy++;
        }
        else
        { // Chưa đánh
            break;
        }
    }

    for (int count = 1; count < 6 && column - count >= 0; count++)
    {
        if (mBoard.getNodes()[row][column - count] == tickBot)
        {
            ally++;
            break;
        }
        else if (mBoard.getNodes()[row][column - count] == tickPlayer)
        {
            enemy++;
        }
        else
        { // Chưa đánh
            break;
        }
    }

    // Tính điểm
    if (mode == 1 || mode == 2)
    {
        if (ally == 2)
            return 0;
        point += defendScore[enemy];
    }
    else if (mode == 3)
    {
        point = defendScore[enemy];
        if (enemy == 4)
            point = defendScore[9]; // Có 4 quân địch->ưu tiên chặn
        if (ally == 2)              // đã chặn 2 đầu
            return 0;
        else if (ally == 1)
            point /= 2; // Bị chặn2 đầu ->giảm điểm
    }

    return point;
}

// tính điểm phòng thủ chéo ngược
int MatchBot::defendDiagonalReverse(int row, int column, int mode)
{
    char tickPlayer = (mOrderTurn == PLAYER_X) ? 'X' : 'O'; // lưu dấu đánh của người chơi
    char tickBot = (tickPlayer == 'X') ? 'O' : 'X';         // lưu dấu đánh của bot
    int point = 0;                                          // tính điểm
    int ally = 0;                                           // đếm số đồng minh
    int enemy = 0;                                          // đếm số quan địch
    for (int count = 1; count < 6 && row - count >= 0 && column + count < SIZE_BOARD; count++)
    {
        if (mBoard.getNodes()[row - count][column + count] == tickBot)
        {
            ally++;
            break;
        }
        else if (mBoard.getNodes()[row - count][column + count] == tickPlayer)
        {
            enemy++;
        }
        else
        { // Chưa đánh
            break;
        }
    }

    for (int count = 1; count < 6 && row + count < SIZE_BOARD && column - count >= 0; count++)
    {
        if (mBoard.getNodes()[row + count][column - count] == tickBot)
        {
            ally++;
            break;
        }
        else if (mBoard.getNodes()[row + count][column - count] == tickPlayer)
        {
            enemy++;
        }
        else
        { // Chưa đánh
            break;
        }
    }

    // Tính điểm
    if (mode == 1 || mode == 2)
    {
        if (ally == 2)
            return 0;
        point += defendScore[enemy];
    }
    else if (mode == 3)
    {
        point = defendScore[enemy];
        if (enemy == 4)
            point = defendScore[9]; // Có 4 quân địch->ưu tiên chặn
        if (ally == 2)              // đã chặn 2 đầu
            return 0;
        else if (ally == 1)
            point /= 2; // Bị chặn2 đầu ->giảm điểm
    }

    return point;
}

int MatchBot::defendDiagonalForward(int row, int column, int mode)
{
    char tickPlayer = (mOrderTurn == PLAYER_X) ? 'X' : 'O'; // lưu dấu đánh của người chơi
    char tickBot = (tickPlayer == 'X') ? 'O' : 'X';         // lưu dấu đánh của bot
    int point = 0;                                          // tính điểm
    int ally = 0;                                           // đếm số đồng minh
    int enemy = 0;                                          // đếm số quan địch
    for (int count = 1; count < 6 && row + count < SIZE_BOARD && column + count < SIZE_BOARD; count++)
    {
        if (mBoard.getNodes()[row + count][column + count] == tickBot)
        {
            ally++;
            break;
        }
        else if (mBoard.getNodes()[row + count][column + count] == tickPlayer)
        {
            enemy++;
        }
        else
        { // Chưa đánh
            break;
        }
    }

    for (int count = 1; count < 6 && row - count >= 0 && column - count >= 0; count++)
    {
        if (mBoard.getNodes()[row - count][column - count] == tickBot)
        {
            ally++;
            break;
        }
        else if (mBoard.getNodes()[row - count][column - count] == tickPlayer)
        {
            enemy++;
        }
        else
        { // Chưa đánh
            break;
        }
    }

    // Tính điểm
    if (mode == 1 || mode == 2)
    {
        if (ally == 2)
            return 0;
        point += defendScore[enemy];
    }
    else if (mode == 3)
    {
        point = defendScore[enemy];
        if (enemy == 4)
            point = defendScore[9]; // Có 4 quân địch->ưu tiên chặn
        if (ally == 2)              // đã chặn 2 đầu
            return 0;
        else if (ally == 1)
            point /= 2; // Bị chặn2 đầu ->giảm điểm
    }

    return point;
}

Move MatchBot::findBestMove(int mode)
{
    Move tmp;
    int pointMax = -defendScore[9];
    for (int i = 0; i < SIZE_BOARD; i++)
    {
        for (int j = 0; j < SIZE_BOARD; j++)
        {
            if (mBoard.getNodes()[i][j] == ' ')
            {
                if (mode == 1 || mode == 2)
                {
                    int pointAttack = attackVertical(i, j, mode) + attackHorizontal(i, j, mode) + attackDiagonalForward(i, j, mode) + attackDiagonalReverse(i, j, mode);
                    int pointDefend = defendVertical(i, j, mode) + defendHorizontal(i, j, mode) + defendDiagonalForward(i, j, mode) + defendDiagonalReverse(i, j, mode);
                    int pointTmp = (pointAttack > pointDefend) ? pointAttack : pointDefend; // chọn điểm lớn hơn
                    if (pointMax < pointTmp)
                    {
                        pointMax = pointTmp;
                        tmp = {i, j};
                    }
                }
                else if (mode == 3)
                {
                    // Lấy ngẫu nhiên khi 2 điểm bằng nhau
                    int r = rand() % 2;
                    int pointAttack = attackVertical(i, j, mode) + attackHorizontal(i, j, mode) + attackDiagonalForward(i, j, mode) + attackDiagonalReverse(i, j, mode);
                    int pointDefend = defendVertical(i, j, mode) + defendHorizontal(i, j, mode) + defendDiagonalForward(i, j, mode) + defendDiagonalReverse(i, j, mode);
                    int pointTmp = pointAttack + pointDefend;
                    if (pointMax < pointTmp || (pointMax == pointTmp && r == 0))
                    {
                        pointMax = pointTmp;
                        tmp = {i, j};
                    }
                }
            }
        }
    }
    return tmp;
}

void MatchBot::game()
{
    int selection; // lựa chọn khi kết thúc trò chơi
    do
    {
        system("cls"); // xóa màn hình
        std::cout << YELLOW << "*------PLAY WITH BOT------*" << DEFAULT_COLOR << std::endl;
        enterMode(); // chọn chế độ chơi
        if (mMode == 4)
            return;             // quay về Menu
        system("cls");          // xóa màn hình
        enterOrderPlayerTurn(); // chọn thứ tự chơi
        system("cls");          // xóa màn hình
        if (mOrderTurn == PLAYER_O)
        {
            mBoard.getNodes()[SIZE_BOARD / 2][SIZE_BOARD / 2] = 'X'; // nếu người chơi đánh sau thì bot đánh vào giữa bàn
            printInforTurn();
            mBoard.printBoard(SIZE_BOARD / 2, SIZE_BOARD / 2); // in ra bàn cờ đầu tiên với Bot đã đánh nước đầu
        }
        else
        {
            printInforTurn();
            mBoard.printBoard(0, 0); // in ra bàn cờ chưa có gì
        }

        while (true)
        {
            Move turnPlayer; // lưu nước đánh hiện tại
            enterValidMove(turnPlayer);
            system("cls"); // xóa màn hình
            printInforTurn();
            mBoard.printBoard(turnPlayer.row, turnPlayer.column);
            if (mBoard.checkWin(mOrderTurn))
            {
                std::cout << RED_CHERRY << "Player is a winner" << DEFAULT_COLOR << std::endl;
                break;
            }
            else if (mBoard.checkFullBoard())
            {
                std::cout << RED_CHERRY << "---GAME DRAW---" << DEFAULT_COLOR << std::endl;
                break;
            }

            Move turnBot = findBestMove(mMode);
            mBoard.getNodes()[turnBot.row][turnBot.column] = (mOrderTurn == PLAYER_X) ? 'O' : 'X';
            system("cls"); // xóa màn hình
            printInforTurn();
            mBoard.printBoard(turnBot.row, turnBot.column);
            int orderBotTurn = (mOrderTurn == PLAYER_X) ? PLAYER_O : PLAYER_X; // Lấy lượt đánh của Bot
            if (mBoard.checkWin(orderBotTurn))
            {
                std::cout << RED_CHERRY << "BOT is a winner" << DEFAULT_COLOR << std::endl;
                break;
            }
            else if (mBoard.checkFullBoard())
            {
                std::cout << RED_CHERRY << "---GAME DRAW---" << DEFAULT_COLOR << std::endl;
                break;
            }
        }

        // Hỏi người chơi muốn chơi lại không
        std::cout << RED_CHERRY << "1. Replay" << DEFAULT_COLOR << std::endl;
        std::cout << RED_CHERRY << "2. Back " << DEFAULT_COLOR << "to MAIN MENU" << std::endl;
        while (true)
        {
            std::cout << "Enter selection: ";
            std::cin >> selection;
            if (selection != 1 && selection != 2)
            {
                std::cout << RED_CHERRY << "Invalid enter value" << DEFAULT_COLOR << std::endl;
            }
            else
            {
                // Cho các giá trị về ' '
                for (int i = 0; i < SIZE_BOARD; i++)
                {
                    for (int j = 0; j < SIZE_BOARD; j++)
                    {
                        mBoard.getNodes()[i][j] = ' ';
                    }
                }
                break;
            }
        }
    } while (selection == 1);
}