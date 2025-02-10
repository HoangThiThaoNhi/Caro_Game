#include "Match.h"

// Constructor default
Match::Match() {}

// Destructor
Match::~Match() {}

// Nhập thông tin người chơi khi mới vào trận  và xử lý dữ liệu -> in ra thông tin người chơi ra màn hình
void Match::enterAccountPlayerAndHandleData()
{
    std::string account1, account2;

    // Nhập tài khoản player1 sau đó xử lý dữ liệu
    std::cout << "Enter account player1: ";
    std::cin.ignore();
    std::getline(std::cin, account1);
    mPlayer1.setAccount(account1);

    // Kiểm tra xem người chơi tồn tại không
    if (mDataMatch.checkExistPlayer(mPlayer1))
    {
        // in ra thông tin người chơi nếu tài khoản đã tồn tại
        std::cout << "Account: " << RED_CHERRY << account1 << DEFAULT_COLOR
                  << " - Win: " << RED_CHERRY << mPlayer1.getWin() << DEFAULT_COLOR
                  << " - Lose: " << RED_CHERRY << mPlayer1.getLose() << DEFAULT_COLOR
                  << " - Draw: " << RED_CHERRY << mPlayer1.getDraw() << DEFAULT_COLOR << std::endl;
    }
    else
    {
        std::cout << "Account: " << RED_CHERRY << account1 << DEFAULT_COLOR << " is a new player" << std::endl; // in ra màn hình là người chơi mới
        mDataMatch.insertNewPlayToFile(account1);
    }

    // Nhập tài khoản player2 sau đó xử lý dữ liệu
    std::cout << "Enter account player2: ";
    std::getline(std::cin, account2);
    mPlayer2.setAccount(account2);
    if (mDataMatch.checkExistPlayer(mPlayer2))
    {
        // in ra thông tin người chơi nếu tài khoản đã tồn tại
        std::cout << "Account: " << RED_CHERRY << account2 << DEFAULT_COLOR
                  << " - Win: " << RED_CHERRY << mPlayer2.getWin() << DEFAULT_COLOR
                  << " - Lose: " << RED_CHERRY << mPlayer2.getLose() << DEFAULT_COLOR
                  << " - Draw: " << RED_CHERRY << mPlayer2.getDraw() << DEFAULT_COLOR << std::endl;
    }
    else
    {
        std::cout << "Account: " << RED_CHERRY << account2 << DEFAULT_COLOR << " is a new player" << std::endl; // in ra màn hình là người chơi mới
        mDataMatch.insertNewPlayToFile(account2);
    }
}

// Nhập dữ liệu di chuyển
void Match::enterValidMove(int playerTurn, std::vector<Move> &storeMove)
{
    char tick = (playerTurn == PLAYER_X) ? 'X' : 'O'; // kiểm tra là lượt 'X' hay là của 'O'
    Move turn;                                        // lưu giá trị nước đánh
    do
    {
        std::cout << "Player " << RED_CHERRY << playerTurn << "'s " << DEFAULT_COLOR << "turn: ";
        std::cin >> turn.row >> turn.column;
        if (!mBoard.isValidMove(turn.row, turn.column))
        {
            std::cout << RED_CHERRY << "Invalid turn. Please enter again!" << DEFAULT_COLOR << std::endl;
        }
    } while (!mBoard.isValidMove(turn.row, turn.column));
    mBoard.getNodes()[turn.row][turn.column] = tick;
    storeMove.push_back(turn); // Lưu lại nước đi
}

void Match::controlMatch()
{
    int playerTurn = PLAYER_X; // khởi tạo lượt đánh đầu tiên của X
    std::vector<Move> storeMove;
    while (true)
    {
        std::cout << std::setw(8) << " " << "Player1 " << RED_CHERRY << mPlayer1.getAccount() << DEFAULT_COLOR << " - X" << std::setw(8) << " ";
        std::cout << "|" << std::setw(8) << " " << "Player2 " << RED_CHERRY << mPlayer2.getAccount() << DEFAULT_COLOR << " - O" << std::endl;
        if (storeMove.size() == 0)
        {
            mBoard.printBoard(0, 0); // in ra bàn cờ ban đầu
        }
        else
        {
            mBoard.printBoard(storeMove[storeMove.size() - 1].row, storeMove[storeMove.size() - 1].column); // in ra board với nước đi mới đánh được tô màu
        }

        enterValidMove(playerTurn, storeMove);
        system("cls"); // Clear màn hình

        // Check Result
        if (mBoard.checkWin(playerTurn))
        {
            std::cout << std::setw(8) << " " << "Player1 " << RED_CHERRY << mPlayer1.getAccount() << DEFAULT_COLOR << " - X" << std::setw(8) << " ";
            std::cout << "|" << std::setw(8) << " " << "Player2 " << RED_CHERRY << mPlayer2.getAccount() << DEFAULT_COLOR << " - O" << std::endl;
            mBoard.printBoard(storeMove[storeMove.size() - 1].row, storeMove[storeMove.size() - 1].column); // in ra board
            std::cout << RED_CHERRY << "Player" << playerTurn << " '";
            if (playerTurn == PLAYER_X)
            {
                std::cout << mPlayer1.getAccount() << "' is a winer" << DEFAULT_COLOR << std::endl;
                mPlayer1.setWin(mPlayer1.getWin() + 1);   // tăng số trận thắng hiện tại lên 1
                mPlayer2.setLose(mPlayer2.getLose() + 1); // tăng số trận thua hiện tại lên 1
                mDataMatch.updatePlayerToFile(mPlayer1);
                mDataMatch.updatePlayerToFile(mPlayer2);
                mDataMatch.storeDataToRewatch(storeMove, mPlayer1, mPlayer2, "WIN", "LOSE");
            }
            else if (playerTurn == PLAYER_O)
            {
                std::cout << mPlayer2.getAccount() << "' is a winer" << DEFAULT_COLOR << std::endl;
                mPlayer1.setLose(mPlayer1.getLose() + 1); // tăng số trận thua hiện tại lên 1
                mPlayer2.setWin(mPlayer2.getWin() + 1);   // tăng số trận thắng hiện tại lên 1
                mDataMatch.updatePlayerToFile(mPlayer1);
                mDataMatch.updatePlayerToFile(mPlayer2);
                mDataMatch.storeDataToRewatch(storeMove, mPlayer1, mPlayer2, "LOSE", "WIN");
            }
            break;
        }
        else if (mBoard.checkFullBoard())
        {
            std::cout << std::setw(8) << " " << "Player1 " << RED_CHERRY << mPlayer1.getAccount() << DEFAULT_COLOR << " - X" << std::setw(8) << " ";
            std::cout << "|" << std::setw(8) << " " << "Player2 " << RED_CHERRY << mPlayer2.getAccount() << DEFAULT_COLOR << " - O" << std::endl;
            mBoard.printBoard(0, 0); // in ra board
            std::cout << RED_CHERRY << "---GAME DRAW---" << DEFAULT_COLOR << std::endl;
            mPlayer1.setWin(mPlayer1.getDraw() + 1); // tăng số trận hòa hiện tại lên 1
            mPlayer2.setWin(mPlayer2.getDraw() + 1);
            mDataMatch.updatePlayerToFile(mPlayer1);
            mDataMatch.updatePlayerToFile(mPlayer2);
            mDataMatch.storeDataToRewatch(storeMove, mPlayer1, mPlayer2, "DRAW", "DRAW");
            break;
        }
        playerTurn = (playerTurn == PLAYER_X) ? PLAYER_O : PLAYER_X; // đổi lượt
    }
}

void Match::gameCaroWithOther()
{
    system("cls"); // Clear màn hình
    std::cout << YELLOW << "*------PLAY WITH OTHER PLAYER------*" << DEFAULT_COLOR << std::endl;
    enterAccountPlayerAndHandleData(); // nhập người chơi
    int selection;
    do
    {
        controlMatch();
        std::cout << "1. Replay" << std::endl;
        std::cout << "2. Back to MENU" << std::endl;
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
