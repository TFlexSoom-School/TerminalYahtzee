// YahtzeeTerminal.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


/* Forward Declarations */

/* Function Prototypes */
int extractInts(char[]);
void Yahtzee(int);
bool scoreOrReroll(Player *, Dice *, UI *);
void startNewGame(Player *, int);
void destroyGame(Player *, Dice *, UI *);
bool playerStillPlaying(Player*);
bool allPlayersScored(Player *, int);
bool playAgain();
int twoPow(int);
int ofKind(Dice *, int);
int fullHouse(Dice *);
int smStraight(Dice *);
int lgStraight(Dice *);
int diceYahtzee(Dice *);
bool bonusYahtzee(Player *, Dice *);

/* Main Method */

int main(int argc, char * argv[]) {
   if (argc == 2) {
      int players = extractInts(argv[1]);
      if (players > 0) {
	 srand(time(NULL));
	 Yahtzee(players);
      }
      else {
	 std::cout << "Invalid Argument" << std::endl;
      }
   }
   else {
      std::cout << "You Yahta zee kiddin me!" << std::endl;
   }

   return 0;
}

/*
 * extract_Ints(char str[])
 * Extracts ints from message
 * preconditions: values are defined.
 * postconditions: none
 * return: the ints
 */
int extractInts(char str[]) {
   int returnValue = 0;
   for (int i = 0; i < strlen(str); i++) {
      if (str[i] >= '0' &&  str[i] <= '9') {
	 returnValue = returnValue * 10 + (str[i] - '0');
      }
      else {
	 return -1;
      }
   }
   return returnValue;
}

/*
 * Yahtzee(int players)
 * Main Runnable Method
 * preconditions: values is defined.
 * postconditions: none
 * return: nothing
 */
void Yahtzee(int numPlayers) {
   Player * players = new Player[numPlayers];
   Dice * dice = new Dice();
   int player = 0;
   UI * ui = new UI(players, &numPlayers, dice, &player);
   ui->start();

   do {
      startNewGame(players, numPlayers);
      do {
	 if (playerStillPlaying(&players[player]))
	    do {
	       dice->rollDice();
	    } while (!scoreOrReroll(&players[player], dice, ui));

	 player += (player >= numPlayers - 1 ? -1 * player : 1);
      } while (!(allPlayersScored(players, numPlayers)));
   } while (ui->playAgain());

   destroyGame(players, dice, ui);

}

void startNewGame(Player * players, int numPlayers) {
   for (int i = 0; i < numPlayers; i++) {
      players[i].reset();
   }
}


void destroyGame(Player * players, Dice * dice, UI * ui) {
   delete ui;
   delete[] players;
   delete dice;
}

bool playerStillPlaying(Player * playerPointer) {
   return !(playerPointer->isPlayerFinished());
}

bool scoreOrReroll(Player * player, Dice * dice, UI * ui) {
   do {
      ui->updatePrint();
      int argument = ui->getUserInput();
      switch (argument) {
	 case -1:
	    player -> exit();
	    return true;
	 case 0:
	    return false;
	 case 1:
	    player->score(0, dice->getResult(1));
	    return true;
	 case 2:
	    player->score(1, dice->getResult(2) * 2);
	    return true;
	 case 3:
	    player->score(2, dice->getResult(3) * 3);
	    return true;
	 case 4:
	    player->score(3, dice->getResult(4) * 4);
	    return true;
	 case 5:
	    player->score(4, dice->getResult(5) * 5);
	    return true;
	 case 6:
	    player->score(5, dice->getResult(6) * 6);
	    return true;
	 case 8:
	    player->score(7, ofKind(dice, 3));
	    return true;
	 case 9:
	    player->score(8, ofKind(dice, 4));
	    return true;
	 case 10:
	    player->score(9, fullHouse(dice));
	    return true;
	 case 11:
	    player->score(10, smStraight(dice));
	    return true;
	 case 12:
	    player->score(11, lgStraight(dice));
	    return true;
	 case 13:
	    player->score(12, diceYahtzee(dice));
	    return true;
	 case 14:
	    player->score(13, dice->getSum());
	    return true;
	 case 15:
	    if (bonusYahtzee(player, dice))
	       return true;
	    break;
	 case 20:
	    dice->holdDice(1);
	    break;
	 case 21:
	    dice->holdDice(2);
	    break;
	 case 22:
	    dice->holdDice(3);
	    break;
	 case 23:
	    dice->holdDice(4);
	    break;
	 case 24:
	    dice->holdDice(5);
	    break;
	 default:
	    ui->Error("Unknown Argument");
	    break;
      }
   } while (true);
}


/*
 * int ofKind(int diceResults[], int arg){
 * displays if the requested set amount is found
 * preconditions: Values are defined
 * postconditions: none
 * return: returns the sum of the dice if the set is found
 */
int ofKind(Dice * dice, int arg) {
   int containsSet = 0;
   for (int i = 1; i < 7; i++) {
      if (containsSet < dice->getResult(arg))
	 containsSet = dice->getResult(arg);
   }
   if (containsSet >= arg)
      return dice->getSum();
   return 0;
}

/*
 * int fullHouse(int diceResults[]){
 * Checks if the player has a full house
 * preconditions: Values are defined
 * postconditions: None
 * return: 25 points if player has full house
 */
int fullHouse(Dice * dice) {
   if (ofKind(dice, 3)) {
      for (int i = 1; i < 7; i++) {
	 if (dice->getResult(i) == 2) {
	    return 25;
	 }
      }
   }
   return 0;
}

/*
 * int smStraight(int diceResults[]){
 * checks for 1234 2345 3456
 * preconditions: Values are defined
 * postconditions: None
 * return: 30 points if found
 */
int smStraight(Dice * dice) {
   if ((dice->getResult(1) && dice->getResult(2)) && (dice->getResult(3) && dice->getResult(4)))
      return 30;
   else if ((dice->getResult(2) && dice->getResult(3)) && (dice->getResult(4) && dice->getResult(5)))
      return 30;
   else if ((dice->getResult(3) && dice->getResult(4)) && (dice->getResult(5) && dice->getResult(6)))
      return 30;
}

/*
 * int lgStraight(int diceResults[]){
 * Checks if the player has a large straight
 * preconditions: Values are defined
 * postconditions: None
 * return: 40 points if large straight is found
 */
int lgStraight(Dice * dice) {
   bool allDifferent = true;
   for (int i = 1; i < 7; i++) {
      if (dice->getResult(i) >= 2) {
	 allDifferent = false;
      }
   }
   if (allDifferent && (dice->getResult(1) != dice->getResult(6))) {
      return 40;
   }
   return 0;
}

/*
 * int diceYahtzee(int diceResults[]){
 * Starts a new Game
 * preconditions: Values are defined
 * postconditions: None
 * return: 50 points if the player has yahtzee
 */
int diceYahtzee(Dice * dice) {
   bool theYahtzee = false;
   for (int i = 1; i < 7; i++) {
      if (dice->getResult(i) == 5)
	 theYahtzee = true;
   }
   return theYahtzee ? 50 : 0;
}

/*
 * bool bonusYahtzee(int diceResults[], int yahtzeeScore, int * bonus){
 * Checks if player can and will be scoring a bonus yahtzee today
 * preconditions: Values are defined bonus represents bonus on score chart
 * postconditions: bonus will add on 100 points if yahtzee if found
 * return: whether scoring happened
 */
bool bonusYahtzee(Player * player, Dice * dice) {

   if (player->getScore(14) != 50)
      return false;
   int score = diceYahtzee(dice);
   if (score != 0) {
      if (player->getScore(14) == -1) {
	 player->score(14, 0);
      }
      player->score(14, player->getScore(14) + 2 * score);
      return true;
   }
   else {
      return false;
   }
}

/*
 * bool allPlayersScored(int ** playerCharts, int players){
 * Checks if all players are scored
 * preconditions: Values are defined
 * postconditions: If players is not already shown as fully scored he will then
 * return: if any player was shown unscored
 */
bool allPlayersScored(Player * players, int numPlayers) {
   for (int i = 0; i < numPlayers; i++) {
      if (!(players[i].isPlayerFinished()))
	 return false;
   }
   return true;
}

