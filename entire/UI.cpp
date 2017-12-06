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
   UI::selectorRow = new int;
   UI::selectorCol = new int;
   (*UI::selectorRow) = 0;
   (*UI::selectorCol) = 0;
   initscr();
   noecho();
   raw();
   keypad(stdscr, TRUE);
}

UI::~UI() {
   delete UI::selectorRow;
   delete UI::selectorCol;
   wborder(UI::wnd, ' ',' ',' ',' ',' ',' ',' ',' ');
   delwin(UI::wnd);
   endwin();
}

void UI::start() {
   UI::wnd = newwin(HEIGHT, WIDTH, START, START); /*Hard Set Values EWWWWW*/
   keypad(UI::wnd, TRUE);
   keypad(stdscr, FALSE);
   UI::title();
   
   wrefresh(UI::wnd);
}

void UI::title(){
   box(UI::wnd, 0, 0);
   mvwprintw(UI::wnd, 1, 1, "|     |   _______  |     |   _______   _______   _______   _______");
   mvwprintw(UI::wnd, 2, 1, "|     |   |     |  |     |      |            |   |         |      ");
   mvwprintw(UI::wnd, 3, 1, "|_____|   |_____|  |_____|      |      ______|   |______   |______");
   mvwprintw(UI::wnd, 4, 1, "   |      |     |  |     |      |      |         |         |      ");
   mvwprintw(UI::wnd, 5, 1, "   |      |     |  |     |      |      |______   |______   |______");
   
}

void UI::updatePrint() {
   wclear(UI::wnd);
   UI::title();
   mvwprintw(UI::wnd, 1, WIDTH - 15, "Player: %d", *(UI::current_turn) + 1);
   for (int i = 1; i < 6; i++) {
      UI::printDice(UI::dice_array->getDice(i - 1), i);
   }
   UI::printChart();
   UI::highlight();

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
   mvwprintw(UI::wnd, 23, 1, "|------------|--------|--------------|--------|");
}

std::string UI::playerValue(int index) {
   int score = UI::player_array[*UI::current_turn].getScore(index);
   if (score == -1) {
      return "0";
   }
   else {
      return int_to_string(score);
   }
}


void UI::Error(std::string message) {
   mvwprintw(UI::wnd, 25, 1, "%s", message.c_str());
   wrefresh(UI::wnd);
}
int UI::getUserInput() {
   int c;
   do{ 
      c = wgetch(UI::wnd);
      switch (c){
	 case KEY_UP:
	    UI::move(0);
	    break;
	 case KEY_RIGHT:
	    UI::move(1);
	    break;
	 case KEY_DOWN:
	    UI::move(2);
	    break;
	 case KEY_LEFT:
	    UI::move(3);
	    break;
	 case KEY_ENTER:
	 case 10:
	    return UI::select();
	    break;
	 case KEY_BACKSPACE:
	 case 8:
	    return -1;
      }
      UI::updatePrint();
   }while (true);
}

bool UI::playAgain() {
   /* Print Again???? */
   int c;
   UI::Error("Would you like to play again?");
   do{
      c = wgetch(UI::wnd);
      if(c == KEY_BACKSPACE || c == 8);
	 return false;
      if(c == KEY_ENTER)
	 return true;
   }while (true);
}

void UI::move(int dir){
   switch(dir){
      case 0:
	 if((*UI::selectorRow) > 0)
	    (*UI::selectorRow) --;
	 break;
      case 1:
	 if((*UI::selectorRow) == 1){
	    if((*UI::selectorCol) != 1 )
	       (*UI::selectorCol) ++;
	 }else if((*UI::selectorRow) == 0){
	    if((*UI::selectorCol) < 4)
	       (*UI::selectorCol) ++;
	 }
	 break;
      case 2:
	 if((*UI::selectorRow) < 6){
	    (*UI::selectorRow) ++;
	    if((*UI::selectorCol) > 1)
	       (*UI::selectorCol) = 1;
	 }
	 break;
      case 3:
	 if((*UI::selectorRow) > 0){
	    (*UI::selectorCol) --;
	 }
	 break;
   }
   UI::updatePrint(); 
}

int UI::select(){
   return 0;   
}

void UI::highlight(){
   if((*UI::selectorRow) == 0){
      for(int i = 0; i < 4; i ++){
	 mvwchgat(UI::wnd, 7 + i, ((*UI::selectorCol) * 5) + 5, 5, A_BLINK, 1, NULL);
      }
   }else if((*UI::selectorRow) >= 1){
      if((*UI::selectorCol) == 0){
	 mvwchgat(UI::wnd, 15 + (*UI::selectorRow), 18, 2, A_BLINK, 1, NULL);
      }else if((*UI::selectorCol) == 1){
	 mvwchgat(UI::wnd, 15 + (*UI::selectorRow), 43, 2, A_BLINK, 1, NULL);
      }
   }
}

void UI::end() {
   /*This will be used for something... I am sure*/
}
