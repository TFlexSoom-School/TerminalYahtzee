/*
  Tristan Hilbert
  11/20/2017
  Dice class definitions for methos and such
  This class provides the ability to carry 5 random numbers
*/

#include "Dice.hpp"
#include "YahtzeeUtil.hpp"
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
	this->dice_array = new int[5];
	this->dice_results = new int[6];
	for (int i = 0; i < 5; i++) {
		Dice::dice_array[i] = 0;
		Dice::dice_results[i] = 0;
	}
	this->dice_results[5] = 0;
	this->heldDice = new int;
	(*this->heldDice) = 0;
	this->numberOfRolls = new int;
	(*this->numberOfRolls) = 0;
}

/* 
 * Dice Object Deconstructor
 * Frees all memory allocated from Dice Object
 */
Dice::~Dice() {
	delete[] this->dice_array;
	delete[] this->dice_results;
	delete this->heldDice;
	delete this->numberOfRolls;
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
   if(*this->numberOfRolls < ROLLS){
      int numCheck;
      for (int i = 0; i < 5; i++) {
	 numCheck = twoPow(i);
	 if (((*this->heldDice) / numCheck) % 2 == 0) {
	    this->dice_array[i] = getRandomNumber(1,7);
	 }
      }
      this->updateResult();
      (*this->numberOfRolls) ++;
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
   return this->dice_results[index - 1];
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
      this->dice_results[i] = 0;
   }
   for (int i = 0; i < 5; i++) {
      this->dice_results[dice_array[i] - 1] ++;
   }
}

/*
 * getSum() 
 * Returns the sum of all dice  
 * param: none
 * pre: dice have been rolled
 * post: None
 * return: the integer representing the she sum of the dice.
 */
int Dice::getSum() {
   return this->dice_array[0] + 
          this->dice_array[1] + 
          this->dice_array[2] + 
          this->dice_array[3] + 
          this->dice_array[4];
}

/*
 * holdDice(int) 
 * holds dice [1-5] or unholds it if already held 
 * param: dice argument int index [1-5]
 * pre: None
 * post: the indexed dice will be held or unheld depending on the argument
 * return: 0 if dice is unheld and 1 if the dice is now held
 */
int Dice::holdDice(int i) {
   i = twoPow(i - 1);
   if ((*this->heldDice / i) % 2 == 1) {
      *this->heldDice -= i;
      return 0;
   }
   else {
      *this->heldDice += i;
      return 1;
   }
}

/*
 * unHoldAllDice() 
 * A function to be used after a turn is done. 
 *    It unholds all dice to get a fresh roll
 *    It also changes the number of rolls back to 0  
 * param: None
 * pre: None
 * post: held Dice variable will return to 0
 * return: the heldDice variable value before it was returned to 0
 */
int Dice::unHoldAllDice(){
   int i = *this->heldDice;
   *this->heldDice = 0;
   *this->numberOfRolls = 0;
   return i;
}

/*
 * getDice(int) 
 * Returns the value of the given dice [0-4]  
 * param: none
 * pre: dice have been rolled
 * post: None
 * return: the integer representing the she sum of the dice.
 */

int Dice::getDice(int index) {
   return this->dice_array[index];
}

/*
 * getDice_held(int) 
 * Returns if the given dice [1-5] is held 
 * param: the dice index [1-5]
 * pre: None
 * post: None
 * return: he integer representing the she sum of the dice.
 */
bool Dice::getDice_held(int index){
   index = twoPow(index - 1);
   if ((*this->heldDice / index) % 2 == 1) 
      return true;
   else
      return false;
}
