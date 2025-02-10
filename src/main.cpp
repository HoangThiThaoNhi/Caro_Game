#include <iostream>
#include "Player.h"
#include "Board.h"
#include "Match.h"
#include "Data.h"
#include "MatchBot.h"
#include "Rewatch.h"
#include "SearchPlayer.h"
#include "Guide.h"

int main()
{
    while (true)
    {
        std::cout << YELLOW << "*------MAIN MENU------*" << DEFAULT_COLOR << std::endl;
        std::cout << RED_CHERRY << "1.Play " << DEFAULT_COLOR << "with Other Player" << std::endl;
        std::cout << RED_CHERRY << "2.Play " << DEFAULT_COLOR << "with BOT" << std::endl;
        std::cout << RED_CHERRY << "3.Rewatch" << DEFAULT_COLOR << std::endl;
        std::cout << RED_CHERRY << "4.Play's " << DEFAULT_COLOR << "Information" << std::endl;
        std::cout << RED_CHERRY << "5.Guild" << DEFAULT_COLOR << std::endl;
        std::cout << RED_CHERRY << "6.Exit" << DEFAULT_COLOR << std::endl;
        std::cout << "Enter number to choice: ";
        int choice;
        std::cin >> choice;
        switch (choice)
        {
        case 1:
        {
            Match match;
            match.gameCaroWithOther();
            system("cls"); // Clear màn hình
            break;
        }
        case 2:
        {
            MatchBot match;
            match.game();
            system("cls"); // Clear màn hình
            break;
        }
        case 3:
        {
            Rewatch matchPlayed;
            if (matchPlayed.rewatch() == true)
                system("cls"); // Clear màn hình nếu tài khoản tồn tại
            break;
        }
        case 4:
        {
            std::string account;
            enterPlayerAccount(account);
            searchAccount(account);
            break;
        }
        case 5:
            guide();
            system("cls"); // Clear màn hình
            break;
        case 6:
            std::cout << RED_CHERRY << "Exit program!" << DEFAULT_COLOR << std::endl;
            return 0;
        default:
            std::cout << RED_CHERRY << "Invalid choice. Please re-enter" << DEFAULT_COLOR << std::endl;
            break;
        }
    }

    return 0;
}