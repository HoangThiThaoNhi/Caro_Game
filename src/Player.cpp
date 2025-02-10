#include "Player.h"

// Constructor
Player::Player() : mAccount(""), mWin(0), mLose(0), mDraw(0) {}

// Destructor
Player::~Player() {}

void Player::setAccount(std::string account)
{
    mAccount = account;
}

void Player::setWin(int win)
{
    mWin = win;
}

void Player::setLose(int lose)
{
    mLose = lose;
}

void Player::setDraw(int draw)
{
    mDraw = draw;
}

std::string Player::getAccount()
{
    return mAccount;
}

int Player::getWin()
{
    return mWin;
}

int Player::getLose()
{
    return mLose;
}

int Player::getDraw()
{
    return mDraw;
}

float Player::getWinRate()
{
    if (mWin != 0)
    {
        return (float)mWin / (mWin + mLose + mDraw) * 100;
    }
    else
    {
        return 0;
    }
}