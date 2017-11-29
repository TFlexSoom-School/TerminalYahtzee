/*
  Tristan Hilbert
  11/21/17
  Yahtzee Terminal UI using NCURSES
*/

#include "stdafx.h"
#define HEIGHT 40
#define WIDTH 100
#define START 0

UI::UI(Player * player_array, int * numPlayers, Dice * dice_array, int * current_turn) {
	UI::player_array = player_array;
	UI::numPlayers = numPlayers;
	UI::dice_array = dice_array;
	UI::current_turn = current_turn;
	initscr();
	noecho();
	raw();
	keypad(stdscr, TRUE);
}

UI::~UI() {
	endwin();
}

void UI::start() {
	UI::wnd = newwin(HEIGHT, WIDTH, START, START); /*Hard Set Values EWWWWW*/
	box(UI::wnd, 0, 0);
	mvwprintw(UI::wnd, 1, 1, "|     |   _______  |     |   _______   _______   _______   _______");
	mvwprintw(UI::wnd, 2, 1, "|     |   |     |  |     |      |            |   |         |      ");
	mvwprintw(UI::wnd, 3, 1, "|_____|   |_____|  |_____|      |      ______|   |______   |______");
	mvwprintw(UI::wnd, 4, 1, "   |      |     |  |     |      |      |         |         |      ");
	mvwprintw(UI::wnd, 5, 1, "   |      |     |  |     |      |      |______   |______   |______");
	wrefresh(UI::wnd);
}

void UI::updatePrint() {
	mvwprintw(UI::wnd, 0, WIDTH - 5, "Player: %d", UI::current_turn + 1);
	for (int i = 0; i < 5; i++) {
		UI::printDice(UI::dice_array->getDice(i), i);
	}
	UI::printChart();
	wrefresh(UI::wnd);
}

void UI::printDice(int value, int index) {
	index = index * 5;
	std::string diceVisuals[3];
	switch (value) {
	case 1:
		diceVisuals[0] = "   ";
		diceVisuals[1] = " 0 ";
		diceVisuals[2] = "   ";
		break;
	case 2:
		diceVisuals[0] = "0  ";
		diceVisuals[1] = "   ";
		diceVisuals[2] = "  0";
		break;
	case 3:
		diceVisuals[0] = "0  ";
		diceVisuals[1] = " 0 ";
		diceVisuals[2] = "  0";
		break;
	case 4:
		diceVisuals[0] = "0 0";
		diceVisuals[1] = "   ";
		diceVisuals[2] = "0 0";
		break;
	case 5:
		diceVisuals[0] = "0 0";
		diceVisuals[1] = " 0 ";
		diceVisuals[2] = "0 0";
		break;
	case 6:
		diceVisuals[0] = "0 0";
		diceVisuals[1] = "0 0";
		diceVisuals[2] = "0 0";
		break;
	default:
		diceVisuals[0] = "   ";
		diceVisuals[1] = "   ";
		diceVisuals[2] = "   ";
		break;
	}
	mvwprintw(UI::wnd, 7, index, " ___ ");
	mvwprintw(UI::wnd, 8, index, "|%s|", diceVisuals[0].c_str());
	mvwprintw(UI::wnd, 9, index, "|%s|", diceVisuals[1].c_str());
	mvwprintw(UI::wnd, 10, index, "|%s|", diceVisuals[2].c_str());
}

void UI::printChart() {
	mvwprintw(UI::wnd, 15, 1, " _____________________________________________ ");
	mvwprintw(UI::wnd, 16, 1, "|     1s     |   %s    |Small Straight|   %s    |", UI::playerValue(0).c_str(), UI::playerValue(8).c_str());
	mvwprintw(UI::wnd, 17, 1, "|     2s     |   %s    |Large Straight|   %s    |", UI::playerValue(1).c_str(), UI::playerValue(9).c_str());
	mvwprintw(UI::wnd, 18, 1, "|     3s     |   %s    | Full  House  |   %s    |", UI::playerValue(2).c_str(), UI::playerValue(10).c_str());
	mvwprintw(UI::wnd, 19, 1, "|     4s     |   %s    | 3 of a Kind  |   %s    |", UI::playerValue(3).c_str(), UI::playerValue(11).c_str());
	mvwprintw(UI::wnd, 20, 1, "|     5s     |   %s    | 4 of a Kind  |   %s    |", UI::playerValue(4).c_str(), UI::playerValue(12).c_str());
	mvwprintw(UI::wnd, 21, 1, "|     6s     |   %s    |    YAHTZEE   |   %s    |", UI::playerValue(5).c_str(), UI::playerValue(13).c_str());
	mvwprintw(UI::wnd, 22, 1, "|   Bonus    |   %s    |Bonus Yahtzee |   %s    |", UI::playerValue(6).c_str(), UI::playerValue(14).c_str());
	mvwprintw(UI::wnd, 23, 1, "|------------|---------|--------------|---------|");
}

std::string UI::playerValue(int index) {
	int score = UI::player_array[*UI::current_turn].getScore(index);
	if (score == -1) {
		return "-1";
	}
	else {
		return int_to_string(score);
	}
}


void UI::Error(std::string message) {
	mvwprintw(UI::wnd, 100, 20, "%s", message.c_str());
	wrefresh(UI::wnd);
}
int UI::getUserInput() {

}
bool UI::playAgain() {

}
void UI::end() {
	/*This will be used for something... I am sure*/
}
