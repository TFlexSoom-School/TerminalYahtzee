/*
  Tristan Hilbert
  11/21/17
  Yahtzee Terminal UI using NCURSES
*/

#include "stdafx.h"
#define HEIGHT 300
#define WIDTH 400
#define START 100

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
	endwin()
}

void UI::start() {
	UI::wnd = newwin(HEIGHT, WIDTH, START, START); /*Hard Set Values EWWWWW*/
	box(UI::wnd, 0, 0);
	mvwprintw(UI::wnd, 0, 0, "|     |   _______  |     |   _______   _______   _______   _______");
	mvwprintw(UI::wnd, 1, 0, "|     |   |     |  |     |      |            |   |         |      ");
	mvwprintw(UI::wnd, 2, 0, "|_____|   |_____|  |_____|      |      ______|   |______   |______");
	mvwprintw(UI::wnd, 3, 0, "   |      |     |  |     |      |      |         |         |      ");
	mvwprintw(UI::wnd, 4, 0, "   |      |     |  |     |      |      |______   |______   |______");
	wrefresh(UI::wnd);
}

void UI::updatePrint() {
	mvwprintw(UI::wnd, 0, WIDTH - 250, "Player: %d", UI::current_turn + 1);
	for (int i = 0; i < 5; i++) {
		UI::printDice(UI::dice_array->getDice(i), i);
	}
	UI::printChart();
	wrefresh(UI::wnd);
}

void UI::printDice(int value, int index) {
	index = index *  + 15;
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
	mvwprintw(UI::wnd, 20, index, " ___ ");
	mvwprintw(UI::wnd, 21, index, "|%s|", diceVisuals[0]);
	mvwprintw(UI::wnd, 22, index, "|%s|", diceVisuals[1]);
	mvwprintw(UI::wnd, 23, index, "|%s|", diceVisuals[2]);
}

void UI::printChart() {
	mvwprintw(UI::wnd, 50, 50, " _____________________________________________ ");
	mvwprintw(UI::wnd, 51, 50, "|     1s     |   %s    |Small Straight|   %s    |", UI::playerValue(0), UI::playerValue(8));
	mvwprintw(UI::wnd, 52, 50, "|     2s     |   %s    |Large Straight|   %s    |", UI::playerValue(1), UI::playerValue(9));
	mvwprintw(UI::wnd, 53, 50, "|     3s     |   %s    | Full  House  |   %s    |", UI::playerValue(2), UI::playerValue(10));
	mvwprintw(UI::wnd, 54, 50, "|     4s     |   %s    | 3 of a Kind  |   %s    |", UI::playerValue(3), UI::playerValue(11));
	mvwprintw(UI::wnd, 55, 50, "|     5s     |   %s    | 4 of a Kind  |   %s    |", UI::playerValue(4), UI::playerValue(12));
	mvwprintw(UI::wnd, 56, 50, "|     6s     |   %s    |    YAHTZEE   |   %s    |", UI::playerValue(5), UI::playerValue(13));
	mvwprintw(UI::wnd, 57, 50, "|   Bonus    |   %s    |Bonus Yahtzee |   %s    |", UI::playerValue(6), UI::playerValue(14));
	mvwprintw(UI::wnd, 58, 50, "|------------|---------|--------------|---------|")
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
	mvwprintw(UI::wnd, 100, 20, "%s", message);
	wrefresh(UI::wnd);
}
int UI::getUserInput() {

}
bool UI::playAgain() {

}
void UI::end() {
	/*This will be used for something... I am sure*/
}