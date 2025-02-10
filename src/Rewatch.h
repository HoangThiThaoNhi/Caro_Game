#ifndef _REWATCH_H
#define _REWATCH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <iomanip>
#include <vector>
#include <string>
#include "Player.h"
#include "Board.h"

class Rewatch
{
private:
    Board mBoard;
    std::vector<Player> mPlayers;                      // lưu thông tin các người chơi
    std::vector<std::string> mDataRewatch;             // lưu dữ liệu các trận đã đánh của tài khoản đã nhập
    std::vector<Move> mTurns;                          // chứa các nước di chuyển dưới dạng Move
    std::string mAccountRewatch;                       // tên tài khoản muốn xem lại
    std::string mOrder, mNameOppenent, mTick, mResult; // lưu lại thông tin đối thủ, lượt đánh và kết quả
    int mNumMatch;                                     // tổng số trận người chơi đó đã đánh

public:
    Rewatch();
    ~Rewatch();
    void storeAccount();                                                 // lưu trữ lại các tài khoản đã tồn tại trong file Data để xử lý
    bool enterAccount();                                                 // nhập tài khoản và show các trận đã đánh
    bool enterMatchWantRewatch(int &selection);                          // nhập trận muốn xem lại
    void storeDataMatchWantReWatch(int &selection);                      // lưu trữ dữ liệu trận đấu muốn xem lại
    void showMatchFought();                                              // show các trận đã đánh
    void printInformationMatchRewatch(int currentRow, int currenColumn); // in ra bảng với thông tin tổng quan
    bool rewatch();
};

#endif