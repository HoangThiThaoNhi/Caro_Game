#ifndef _PLAYER_H
#define _PLAYER_H

#include <iostream>

class Player
{
private:
    std::string mAccount; // tên tài khoản
    int mWin;             // số trận thắng
    int mLose;            // số trận thua
    int mDraw;            // số trận hòa
public:
    Player();
    ~Player();
    void setAccount(std::string account);
    void setWin(int win);   // tăng số trận thắng lên 1
    void setLose(int lose); // tăng số trận thua lên 1
    void setDraw(int draw); // tăng số trận hòa lên 1
    std::string getAccount();
    int getWin();
    int getLose();
    int getDraw();
    float getWinRate();
};

#endif