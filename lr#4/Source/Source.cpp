#pragma once
#include <iostream>
#include "Header.h"
#include <ctime>
#include <conio.h>


Game initGame(char userChar) {
	Game game;
	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			game.board[i][j] = ' ';
		}
	}

	game.isUserTurn = time(0) % 2;

	switch (userChar) {
	case 'X':	//Eng letter
		game.userChar = 'X';
		break;

	case 'x':	//Eng letter
		game.userChar = 'X';
		break;

	case 'O':	//Eng letter
		game.userChar = 'O';
		break;

	case 'o':	//Eng letter
		game.userChar = 'O';
		break;

	case '0':	//Just zero
		game.userChar = 'O';
		break;
	}
	


	if (game.userChar == 'X') game.botChar = 'O';
	else game.botChar = 'X';

	game.status = Status::PLAY;

	return game;
}


void updateDisplay(const Game game) {
	char display[8][16]{
	"    a   b   c  ",
	"  -------------",
	"1 |   |   |   |",
	"  -------------",
	"2 |   |   |   |",
	"  -------------",
	"3 |   |   |   |",
	"  -------------"
	};

	system("cls");

	for (int i = 2; i < 8; i += 2) {
		for (int j = 4; j < 16; j += 4) {
			display[i][j] = game.board[(i / 2) - 1][(j / 4) - 1];
		}
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 16; j++) {
			std::cout << display[i][j];
		}
		std::cout << std::endl;
	}
}


void botTurn(Game* game) {
	int counter_X = 0, counter_O = 0;

	if (game->board[1][1] == ' ') {
		game->board[1][1] = game->botChar;
		return;
	}

	//Пробежка по строкам
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
				if (game->board[i][j] == 'X') counter_X++;
				if (game->board[i][j] == 'O') counter_O++;
		}
		if (counter_O > 1 or counter_X > 1) {
			for (int j = 0; j < 3; j++) {
				if (game->board[i][j] == ' ') {
					game->board[i][j] = game->botChar;
					return;
				}
			}
		}
		counter_O = 0; counter_X = 0;
	}

	//Пробежка по столбцам
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (game->board[j][i] == 'X') counter_X++;
			if (game->board[j][i] == 'O') counter_O++;
		}
		if (counter_O > 1 or counter_X > 1) {
			for (int j = 0; j < 3; j++) {
				if (game->board[j][i] == ' ') {
					game->board[j][i] = game->botChar;
					return;
				}
			}
		}
		counter_O = 0; counter_X = 0;
	}
	
	//Пробежка по главной диагонали
	for (int i = 0; i < 3; i++) {
		if (game->board[i][i] == 'X') counter_X++;
		if (game->board[i][i] == 'O') counter_O++;
	}
	if (counter_O > 1 or counter_X > 1) {
		for (int i = 0; i < 3; i++) {
			if (game->board[i][i] == ' ') {
				game->board[i][i] = game->botChar;
				return;
			}
		}
	}else{ counter_O = 0; counter_X = 0; }

	//Пробежка по побочной диагонали
	for (int i = 0; i < 3; i++) {
		if (game->board[i][2 - i] == 'X') counter_X++;
		if (game->board[i][2 - i] == 'O') counter_O++;
	}
	if (counter_O > 1 or counter_X > 1) {
		for (int i = 0; i < 3; i++) {
			if (game->board[i][2 - i] == ' ') {
				game->board[i][2 - i] = game->botChar;
				return;
			}
		}
	}

	//Просто рандомно тыкнуть
	srand(time(0));
	while (true) {
		int i = rand() % 3; int j = rand() % 3;
		if (game->board[i][j] == ' ') {
			game->board[i][j] = game->botChar;
			return;
		}
	}
}


void userTurn(Game* game) {

	Direction direction = Direction::NONE;
	int i = 1, j = 1;
	char ch = '\t';

	switch (game->board[i][j]) {
	case ' ': 
		game->board[i][j] = '_';
		break;

	case 'X':
		game->board[i][j] = 'x';
		break;

	case 'O': 
		game->board[i][j] = 'o';
		break;
	}

	updateDisplay(*game);

	switch (game->board[i][j]) {
	case '_': 
		game->board[i][j] = ' ';
		break;

	case 'x': 
		game->board[i][j] = 'X';
		break;

	case 'o': 
		game->board[i][j] = 'O';
		break;
	}
	

	while (true) {

		//!_kbhit();
		ch = _getch();

		{
			if (ch == 'W' || ch == 'w')			/*Eng letters*/
				direction = Direction::UP;
			else if (ch == 'S' || ch == 's') 	/*Eng letters*/
				direction = Direction::DOWN;
			else if (ch == 'A' || ch == 'a') 	/*Eng letters*/
				direction = Direction::LEFT;
			else if (ch == 'D' || ch == 'd') 	/*Eng letters*/
				direction = Direction::RIGHT;
			else direction = Direction::NONE;
		}

		switch (direction) {
		case Direction::UP:
			if (i - 1 >= 0) i --;
			break;

		case Direction::LEFT:
			if (j - 1 >= 0) j --;
			break;

		case Direction::DOWN:
			if (i + 1 < 3) i ++;
			break;

		case Direction::RIGHT:
			if (j + 1 < 3) j ++;
			break; 

		case Direction::NONE:	break;
		}

		switch (game->board[i][j]) {
		case ' ': 
			game->board[i][j] = '_';
			break;
		
		case 'X': 
			game->board[i][j] = 'x';
			break;
		
		case 'O': 
			game->board[i][j] = 'o';
			break;
		}

		if (ch == ' ' and game->board[i][j] == '_') {
			game->board[i][j] = game->userChar;
			return;
		}

		updateDisplay(*game);

		switch (game->board[i][j]) {
		case '_': 
			game->board[i][j] = ' ';
			break; 
		
		case 'x': 
			game->board[i][j] = 'X';
			break;
		
		case 'o': 
			game->board[i][j] = 'O';
			break;
		}
	}
}


bool updateGame(Game* game) {
	int counter_X = 0, counter_O = 0;

	//Пробежка по строкам
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (game->board[i][j] == 'X') counter_X++;
			if (game->board[i][j] == 'O') counter_O++;
		}
		if (counter_O > 2 or counter_X > 2) {
			if (game->board[i][0] == game->userChar) 
				game->status = Status::USER_WIN;
			else 
				game->status = Status::BOT_WIN;
			return true;
		}
		counter_O = 0; counter_X = 0;
	}

	//Пробежка по столбцам
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (game->board[j][i] == 'X') counter_X++;
			if (game->board[j][i] == 'O') counter_O++;
		}
		if (counter_O > 2 or counter_X > 2) {
			if (game->board[0][i] == game->userChar) 
				game->status = Status::USER_WIN;
			else 
				game->status = Status::BOT_WIN;
			return true;
		}
		counter_O = 0; counter_X = 0;
	}

	//Пробежка по главной диагонали
	for (int i = 0; i < 3; i++) {
		if (game->board[i][i] == 'X') counter_X++;
		if (game->board[i][i] == 'O') counter_O++;
	}
	if (counter_O > 2 or counter_X > 2) {
		if (game->board[1][1] == game->userChar) 
			game->status = Status::USER_WIN;
		else game->status = Status::BOT_WIN;
		return true;
	}
	else { counter_O = 0; counter_X = 0; }

	//Пробежка по побочной диагонали
	for (int i = 0; i < 3; i++) {
		if (game->board[i][2 - i] == 'X') counter_X++;
		if (game->board[i][2 - i] == 'O') counter_O++;
	}
	if (counter_O > 2 or counter_X > 2) {
		if (game->board[1][1] == game->userChar) 
			game->status = Status::USER_WIN;
		else 
			game->status = Status::BOT_WIN;
		return true;
	}
	else { counter_O = 0; counter_X = 0; }

	//Проверка на DRAW
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (game->board[i][j] == 'X') counter_X++;
			if (game->board[i][j] == 'O') counter_O++;
		}
	}
	if (counter_O + counter_X == 9) {
		game->status = Status::DRAW;
		return true;
	}
	else {
		game->isUserTurn = !game->isUserTurn;
	}

	return false;
}