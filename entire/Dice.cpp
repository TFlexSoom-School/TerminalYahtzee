/*
  Tristan Hilbert
  11/20/2017
  Dice class definitions for methos and such
  This class provides the ability to carry 5 random numbers
*/

/* Header File that includes all headerfiles */
#include "stdafx.h"

/* Feel free to change the number of rolls with this macro */
#ifndef ROLLS
#define ROLLS 3
#endif

/* 
 * Dice Object Constructor
 * A Dice object contains an array of 5 integers 1-6 for dice.
 *    contains an array of of 6 integers 1-5 as a dice counter.
 *    contains two integers for the which dice to hold and how many rolls have been made.
 * Post condition: Two arrays will be created on the heap all initialized to zero.
 * 	Two integer variables will also be created.
 */
Dice::Dice() {
	Dice::dice_array = new int[5];
	Dice::dice_results = new int[6];
	for (int i = 0; i < 5; i++) {
		Dice::dice_array[i] = 0;
		Dice::dice_results[i] = 0;
	}
	Dice::dice_results[5] = 0;
	Dice::heldDice = new int;
	*Dice::heldDice = 0;
	Dice::numberOfRolls = new int;
	*Dice::numberOfRolls = 0;
}

/* 
 * Dice Object Deconstructor
 * Frees all memory allocated from Dice Object
 */
Dice::~Dice() {
	delete[] Dice::dice_array;
	delete[] Dice::dice_results;
	delete Dice::heldDice;
	delete Dice::numberOfRolls;
}

/*
 * rollDice()
 * Rolls the dice array and collects results on dice object
 * Will also increment Dice rolled. If dice rolled is > ROLLS then method will not run
 * param: None
 * pre: None (Preferablly dice rolled is < ROLLs)
 * post: Based on dice held the two arrays will potentiall have new values
 * 	similar to a roll in Yahtzee
 * return: None
 */
void Dice::rollDice() {
   if(*Dice::numberOfRolls < ROLLS){
      int numCheck;
      for (int i = 0; i < 5; i++) {
	 numCheck = twoPow(i);
	 if (((*Dice::heldDice) / numCheck) % 2 == 0) {
	    Dice::dice_array[i] = getRandomNumber(1,7);
	 }
      }
      Dice::updateResult();
      (*Dice::numberOfRolls) ++;
   }
}


/*
 * getResult(int)
 * Gets the result on the requested number rolled [1,6]
 * param: index [1,6]
 * pre: None
 * post: None
 * return: integer value representing how many of that number has been rolled
 */
int Dice::getResult(int index) {
   return Dice::dice_results[index - 1];
}

/*
 * updateResult()
 * private function to keep the results on track with the dice during roll
 * param: None
 * pre: None
 * post: Result array will have corresponding values to dice as defined
 * return: None
 */
void Dice::updateResult() {
   for (int i = 0; i < 6; i++) {
      Dice::dice_results[i] = 0;
   }
   for (int i = 0; i < 5; i++) {
      Dice::dice_results[dice_array[i] - 1] ++;
   }
}

/*
 * g
 * Gets the result on the requested number rolled [1,6]
 * param: index [1,6]
 * pre: None
 * post: None
 * return: integer value representing how many of that number has been rolled
 */
int Dice::getSum() {
   return Dice::dice_array[0] + Dice::dice_array[1] + Dice::dice_array[2] + Dice::dice_array[3] + Dice::dice_array[4];
}

int Dice::holdDice(int i) {
   i = twoPow(i - 1);
   if (((*Dice::heldDice) / i) % 2 == 1) {
      (*Dice::heldDice) -= i;
      return 0;
   }
   else {
      (*Dice::heldDice) += i;
      return 1;
   }
}

int Dice::unHoldAllDice(){
   int i = *Dice::heldDice;
   *Dice::heldDice = 0;
   *Dice::numberOfRolls = 0;
   return i;
}

int Dice::getDice(int index) {
   return Dice::dice_array[index];
}

bool Dice::getDice_held(int index){
   index = twoPow(index - 1);
   if (((*Dice::heldDice) / index) % 2 == 1) 
      return true;
   else
      return false;
}
