#ifndef _MATCH_H
#define _MATCH_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "Board.h"
#include "Player.h"
#include "Data.h"

// tạo trận đấu
class Match
{
private:
    Board mBoard;
    Player mPlayer1, mPlayer2;
    Data mDataMatch;

public:
    Match();
    ~Match();
    void enterAccountPlayerAndHandleData();                            // Nhập tài khoản người chơi khi vào trận và xử lý dữ liệu
    void enterValidMove(int playerTurn, std::vector<Move> &storeMove); // Nhập nước di chuyển
    void controlMatch();                                               // điều khiển trận đấu
    void gameCaroWithOther();
};

#endif