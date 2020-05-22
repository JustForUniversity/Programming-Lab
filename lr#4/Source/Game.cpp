#include <iostream>
#include "Header.h"

//#include <conio.h>


int main()
{
    char userChar;
    Game game;

    bool correct=false;

    do {
        std::cout << "Enter your char (X or O)  ";
        std::cin >> userChar;

        if (userChar == 'x' || userChar == 'X' ||   //Eng letters
            userChar == 'o' || userChar == 'O' ||   //Eng letters
            userChar == '0')                        //Just zero
            correct = true;
        system("cls");
    } while (!correct);

    game = initGame(userChar);

    while (!updateGame(&game)) {
        if (game.isUserTurn) userTurn(&game);
        else botTurn(&game);
        updateDisplay(game);
    }

    switch (game.status) {
    case Status::USER_WIN:  std::cout << "User Win!"<< std::endl; break;
    case Status::BOT_WIN:   std::cout << "Bot Win!" << std::endl; break;
    case Status::DRAW:      std::cout << "Draw!"    << std::endl; break;
    }

    return 0;
}
