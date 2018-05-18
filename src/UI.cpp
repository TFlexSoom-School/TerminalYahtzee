/*
   Tristan Hilbert
   11/21/17
   Yahtzee Terminal UI using NCURSES
   */

#include "UI.hpp"
#include "YahtzeeUtil.hpp"

#define HEIGHT 40
#define WIDTH 100
#define START 0

UI::UI(Player * player_array, int * numPlayers, Dice * dice_array, int * current_turn) {
   this->player_array = player_array;
   this->numPlayers = numPlayers;
   this->dice_array = dice_array;
   this->current_turn = current_turn;
   this->selectorRow = new int;
   this->selectorCol = new int;
   *this->selectorRow = 0;
   *this->selectorCol = 0;
   initscr();
   noecho();
   raw();
   keypad(stdscr, TRUE);
}

UI::~UI() {
   delete this->selectorRow;
   delete this->selectorCol;
   wborder(this->wnd, ' ',' ',' ',' ',' ',' ',' ',' ');
   delwin(this->wnd);
   endwin();
}

void UI::start() {
   this->wnd = newwin(HEIGHT, WIDTH, START, START); /*Hard Set Values EWWWWW*/
   keypad(this->wnd, TRUE);
   keypad(stdscr, FALSE);
   this->title();

   wrefresh(this->wnd);
}

void UI::title(){
   box(this->wnd, 0, 0);
   mvwprintw(this->wnd, 1, 1, "|     |   _______  |     |   _______   _______   _______   _______");
   mvwprintw(this->wnd, 2, 1, "|     |   |     |  |     |      |            |   |         |      ");
   mvwprintw(this->wnd, 3, 1, "|_____|   |_____|  |_____|      |      ______|   |______   |______");
   mvwprintw(this->wnd, 4, 1, "   |      |     |  |     |      |      |         |         |      ");
   mvwprintw(this->wnd, 5, 1, "   |      |     |  |     |      |      |______   |______   |______");

}

void UI::updatePrint() {
   wclear(this->wnd); /*Clear Existing Marks*/

   this->title(); /* Print Title */

   this->printPlayer(); /* Prints Top Left Player Label */

   for (int i = 1; i < 6; i++) {
      this->printDice(this->dice_array->getDice(i - 1), i); /* Print 5 Dice */
   }

   this->printButtons(); /* Print Buttons */

   this->printChart(); /* Print Score Chart */

   this->highlight(); /* Assign new Blinking Text based on User Input */

   wrefresh(this->wnd); /* Refresh screen with new marks */
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
   mvwprintw(this->wnd, 10, index, " ___ ");
   mvwprintw(this->wnd, 11, index, "|%s|", diceVisuals[0].c_str());
   mvwprintw(this->wnd, 12, index, "|%s|", diceVisuals[1].c_str());
   mvwprintw(this->wnd, 13, index, "|%s|", diceVisuals[2].c_str());
}

void UI::printPlayer(){ 
   mvwprintw(this->wnd, 1, WIDTH - 15, "Player: %d", *(this->current_turn) + 1);
}

void UI::printButtons(){
   mvwprintw(this->wnd, 9, 35, " ___   ___   _     _");
   mvwprintw(this->wnd, 10, 35, "| _ | |   | | |   | |");
   mvwprintw(this->wnd, 11, 35, "| U | | | | | |   | |");
   mvwprintw(this->wnd, 12, 35,"|  _| | | | | |_  | |_");
   mvwprintw(this->wnd, 13, 35,"|_|\\\\ |___| |___| |___|");
}

void UI::printChart() {
   mvwprintw(this->wnd, 20, 1, " ___________________________________________________ ");
   mvwprintw(this->wnd, 21, 1, "|     1s     |   %s    |Small Straight|   %s    |", this->playerValue(0).c_str(), this->playerValue(7).c_str());
   mvwprintw(this->wnd, 22, 1, "|     2s     |   %s    |Large Straight|   %s    |", this->playerValue(1).c_str(), this->playerValue(8).c_str());
   mvwprintw(this->wnd, 23, 1, "|     3s     |   %s    | Full  House  |   %s    |", this->playerValue(2).c_str(), this->playerValue(9).c_str());
   mvwprintw(this->wnd, 24, 1, "|     4s     |   %s    | 3 of a Kind  |   %s    |", this->playerValue(3).c_str(), this->playerValue(10).c_str());
   mvwprintw(this->wnd, 25, 1, "|     5s     |   %s    | 4 of a Kind  |   %s    |", this->playerValue(4).c_str(), this->playerValue(11).c_str());
   mvwprintw(this->wnd, 26, 1, "|     6s     |   %s    |    YAHTZEE   |   %s    |", this->playerValue(5).c_str(), this->playerValue(12).c_str());
   mvwprintw(this->wnd, 27, 1, "|   Bonus    |   %s    |    Chance    |   %s    |", this->playerValue(6).c_str(), this->playerValue(13).c_str());
   mvwprintw(this->wnd, 28, 1, "|------------|----------|Bonus Yahtzee |   %s    |", this->playerValue(14).c_str());
   mvwprintw(this->wnd, 29, 1, "                        |--------------|----------|");
}

std::string UI::playerValue(int index) {
   int score = this->player_array[*this->current_turn].getScore(index);
   if (score == -1) {
      return "   ";
   }else if (score == 0)
      return "  0";
   else {
      return int_to_string(score, 3); /* Num has to be > 0 */
   }
}


void UI::Error(std::string message) {
   mvwprintw(this->wnd, 35, 1, "%s", message.c_str());
   wrefresh(this->wnd);
}
int UI::getUserInput() {
   int c;
   do{ 
      c = wgetch(this->wnd);
      switch (c){
	 case KEY_UP:
	    this->move(0);
	    break;
	 case KEY_RIGHT:
	    this->move(1);
	    break;
	 case KEY_DOWN:
	    this->move(2);
	    break;
	 case KEY_LEFT:
	    this->move(3);
	    break;
	 case KEY_ENTER:
	 case 10:
	    return this->select();
	    break;
	 case KEY_F(1):
	 case KEY_BACKSPACE:
	 case 8:
	    return -1;
      }
      this->updatePrint();
   }while (true);
}

bool UI::playAgain() {
   this->updatePrint();
   int c;
   do{
      this->Error("Press Backspace to Quit");
      c = wgetch(this->wnd);
      if(c == KEY_BACKSPACE || c == 8)
	 return false;
      if(c == KEY_ENTER){
	 *this->current_turn = 0;
	 *this->selectorRow = 0;
	 return true;
      }
      if(c == KEY_LEFT && *this->current_turn > 0){
	 *this->current_turn --;
	 this->updatePrint();
      }
      if(c == KEY_RIGHT && *this->current_turn < *this->numPlayers){
	 *this->current_turn ++;
	 this->updatePrint();
      }
   }while (true);
}

void UI::move(int dir){
   switch(dir){
      case 0: /* Up */
	 if(*this->selectorRow > 0)
	    *this->selectorRow --;
	 break;
      case 1: /* Right */
	 if(*this->selectorRow >= 1){
	    if(*this->selectorCol != 1 )
	       *this->selectorCol ++;
	 }else if(*this->selectorRow == 0){
	    if(*this->selectorCol < 5)
	       *this->selectorCol ++;
	 }
	 break;
      case 2: /* Down */
	 if(*this->selectorRow <= 7){
	    *this->selectorRow ++;
	    if(*this->selectorCol > 1)
	       *this->selectorCol = 1;
	    if(*this->selectorRow == 7)
	       *this->selectorCol = 1;
	 }
	 break;
      case 3: /* Left */
	 if(*this->selectorCol > 0 && *this->selectorRow <= 6){
	    *this->selectorCol --;
	 }
	 break;
   }
   this->updatePrint(); 
}

int UI::select(){
   if(*this->selectorRow  == 0){
      if(*this->selectorCol == 5){
	 return 0;
      }else{
	 return 20 + (*this->selectorCol);
      }
   }else if(*this->selectorCol == 0){
      return *this->selectorRow;
   }else{
      return *this->selectorRow + 7;
   }   
}

void UI::highlight(){
   this->highlight_DiceWhite();
   this->highlight_blinkCurs(); /* This command should be last */
}

void UI::highlight_DiceWhite(){
   for(int i = 0; i < 5; i ++){
      if(this->dice_array->getDice_held(i + 1)){
	 for(int j = 0; j < 4; j ++)
	    mvwchgat(this->wnd, 10 + j, i * 5 + 5, 5, A_REVERSE, 1, NULL);
      }
   }
}

void UI::highlight_blinkCurs(){
   if(*this->selectorRow == 0){
      if(*this->selectorCol != 5){
	 for(int i = 0; i < 4; i ++){
	    if(this->dice_array -> getDice_held(*this->selectorCol + 1))
	       mvwchgat(this->wnd, 10 + i, (*this->selectorCol * 5) + 5, 5, A_BLINK | A_REVERSE, 1, NULL);
	    else
	       mvwchgat(this->wnd, 10 + i, (*this->selectorCol * 5) + 5, 5, A_BLINK, 1, NULL);
	 }
      }else{
	 for(int i = 0; i < 5; i ++){
	    mvwchgat(this->wnd, 9 + i, 35, 24, A_BLINK, 1, NULL);
	 }
      }
   }else if(*this->selectorRow >= 1){
      if(*this->selectorCol == 0){
	 mvwchgat(this->wnd, 20 + *this->selectorRow, 18, 3, A_BLINK, 1, NULL);
      }else if(*this->selectorCol == 1){
	 mvwchgat(this->wnd, 20 + *this->selectorRow, 45, 3, A_BLINK, 1, NULL);
      }
   }
}

void UI::end() {
   *this->selectorRow = -1;
}
