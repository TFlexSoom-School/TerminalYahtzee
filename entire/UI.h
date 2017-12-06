/*
  Tristan Hilbert
  11/21/17
  UI for Yahtzee using Curses
*/
#pragma once
#include "stdafx.h"


class UI {
private:
	Player * player_array;
	int * numPlayers;
	Dice * dice_array;
	int * current_turn;
	WINDOW * wnd;
	int * selectorRow;
	int * selectorCol;

public:
	UI(Player *,int *, Dice *, int *);
	~UI();
	void start();
	void title();
	void updatePrint();
	void Error(std::string);
	int getUserInput();
	bool playAgain();
	void end();
	void printChart();
	void printDice(int, int);
	std::string playerValue(int);
	void move(int);
        int select();
        void highlight();	
};
