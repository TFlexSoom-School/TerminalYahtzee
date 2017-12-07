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
   wclear(UI::wnd); /*Clear Existing Marks*/

   UI::title(); /* Print Title */

   UI::printPlayer(); /* Prints Top Left Player Label */

   for (int i = 1; i < 6; i++) {
      UI::printDice(UI::dice_array->getDice(i - 1), i); /* Print 5 Dice */
   }

   UI::printButtons(); /* Print Buttons */

   UI::printChart(); /* Print Score Chart */

   UI::highlight(); /* Assign new Blinking Text based on User Input */

   wrefresh(UI::wnd); /* Refresh screen with new marks */
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
   mvwprintw(UI::wnd, 10, index, " ___ ");
   mvwprintw(UI::wnd, 11, index, "|%s|", diceVisuals[0].c_str());
   mvwprintw(UI::wnd, 12, index, "|%s|", diceVisuals[1].c_str());
   mvwprintw(UI::wnd, 13, index, "|%s|", diceVisuals[2].c_str());
}

void UI::printPlayer(){ 
   mvwprintw(UI::wnd, 1, WIDTH - 15, "Player: %d", *(UI::current_turn) + 1);
}

void UI::printButtons(){
   mvwprintw(UI::wnd, 9, 35, " ___   ___   _     _");
   mvwprintw(UI::wnd, 10, 35, "| _ | |   | | |   | |");
   mvwprintw(UI::wnd, 11, 35, "| U | | | | | |   | |");
   mvwprintw(UI::wnd, 12, 35,"|  _| | | | | |_  | |_");
   mvwprintw(UI::wnd, 13, 35,"|_|\\\\ |___| |___| |___|");
}

void UI::printChart() {
   mvwprintw(UI::wnd, 20, 1, " ___________________________________________________ ");
   mvwprintw(UI::wnd, 21, 1, "|     1s     |   %s    |Small Straight|   %s    |", UI::playerValue(0).c_str(), UI::playerValue(7).c_str());
   mvwprintw(UI::wnd, 22, 1, "|     2s     |   %s    |Large Straight|   %s    |", UI::playerValue(1).c_str(), UI::playerValue(8).c_str());
   mvwprintw(UI::wnd, 23, 1, "|     3s     |   %s    | Full  House  |   %s    |", UI::playerValue(2).c_str(), UI::playerValue(9).c_str());
   mvwprintw(UI::wnd, 24, 1, "|     4s     |   %s    | 3 of a Kind  |   %s    |", UI::playerValue(3).c_str(), UI::playerValue(10).c_str());
   mvwprintw(UI::wnd, 25, 1, "|     5s     |   %s    | 4 of a Kind  |   %s    |", UI::playerValue(4).c_str(), UI::playerValue(11).c_str());
   mvwprintw(UI::wnd, 26, 1, "|     6s     |   %s    |    YAHTZEE   |   %s    |", UI::playerValue(5).c_str(), UI::playerValue(12).c_str());
   mvwprintw(UI::wnd, 27, 1, "|   Bonus    |   %s    |Bonus Yahtzee |   %s    |", UI::playerValue(6).c_str(), UI::playerValue(13).c_str());
   mvwprintw(UI::wnd, 28, 1, "|------------|----------|--------------|----------|");
}

std::string UI::playerValue(int index) {
   int score = UI::player_array[*UI::current_turn].getScore(index);
   if (score == -1) {
      return "   ";
   }
   else {
      return int_to_string(score, 3);
   }
}


void UI::Error(std::string message) {
   mvwprintw(UI::wnd, 35, 1, "%s", message.c_str());
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
	 case KEY_F(1):
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
      case 0: /* Up */
	 if((*UI::selectorRow) > 0)
	    (*UI::selectorRow) --;
	 break;
      case 1: /* Right */
	 if((*UI::selectorRow) >= 1){
	    if((*UI::selectorCol) != 1 )
	       (*UI::selectorCol) ++;
	 }else if((*UI::selectorRow) == 0){
	    if((*UI::selectorCol) < 5)
	       (*UI::selectorCol) ++;
	 }
	 break;
      case 2: /* Down */
	 if((*UI::selectorRow) <= 6){
	    (*UI::selectorRow) ++;
	    if((*UI::selectorCol) > 1)
	       (*UI::selectorCol) = 1;
	    if((*UI::selectorRow) == 7)
	       (*UI::selectorCol) = 1;
	 }
	 break;
      case 3: /* Left */
	 if((*UI::selectorCol) > 0 && (*UI::selectorRow <= 6)){
	    (*UI::selectorCol) --;
	 }
	 break;
   }
   UI::updatePrint(); 
}

int UI::select(){
  if(*UI::selectorRow  == 0){
     if(*UI::selectorCol == 5){
        return 0;
     }else{
        return 20 + (*UI::selectorCol);
     }
  }else if(*UI::selectorCol == 0){
     return (*UI::selectorRow);
  }else{
     return (*UI::selectorRow) + 7;
  }   
}

void UI::highlight(){
   UI::highlight_DiceWhite();
   UI::highlight_blinkCurs(); /* This command should be last */
}

void UI::highlight_DiceWhite(){
   for(int i = 0; i < 5; i ++){
      if(UI::dice_array -> getDice_held(i + 1)){
         for(int j = 0; j < 4; j ++)
	    mvwchgat(UI::wnd, 10 + j, i * 5 + 5, 5, A_REVERSE, 1, NULL);
      }
   }
}

void UI::highlight_blinkCurs(){
   if((*UI::selectorRow) == 0){
      if((*UI::selectorCol) != 5){
	 for(int i = 0; i < 4; i ++){
	    if(UI::dice_array -> getDice_held((*UI::selectorCol) + 1))
	       mvwchgat(UI::wnd, 10 + i, ((*UI::selectorCol) * 5) + 5, 5, A_BLINK | A_REVERSE, 1, NULL);
	    else
	       mvwchgat(UI::wnd, 10 + i, ((*UI::selectorCol) * 5) + 5, 5, A_BLINK, 1, NULL);
	 }
      }else{
	 for(int i = 0; i < 5; i ++){
	    mvwchgat(UI::wnd, 9 + i, 35, 24, A_BLINK, 1, NULL);
	 }
      }
   }else if((*UI::selectorRow) >= 1){
      if((*UI::selectorCol) == 0){
	 mvwchgat(UI::wnd, 20 + (*UI::selectorRow), 18, 3, A_BLINK, 1, NULL);
      }else if((*UI::selectorCol) == 1){
	 mvwchgat(UI::wnd, 20 + (*UI::selectorRow), 45, 3, A_BLINK, 1, NULL);
      }
   }
}

void UI::end() {
   /*This will be used for something... I am sure*/
}
