#ifndef _DATA_H
#define _DATA_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "Player.h"
#include "Board.h"

class Data
{
public:
    Data();
    ~Data();
    bool checkExistPlayer(Player &player); // Kiểm người chơi đã tồn tại trong file DataPlayer.txt hay chưa
    void insertNewPlayToFile(std::string account);
    void storeDataToPlayer(Player &player, std::string data);                                                                          // Lưu dữ liệu từ file DataPlayer.txt vào trong player
    void storeDataToRewatch(std::vector<Move> &storeMove, Player &player1, Player &player2, std::string result1, std::string result2); // lưu trữ người chơi với nhau vào file rewatch
    void updatePlayerToFile(Player &player);                                                                                           // Cập nhập dữ liệu của 2 người chơi vào file data sau khi đánh xong trận
};

#endif