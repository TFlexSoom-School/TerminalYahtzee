/*
  Tristan Hilbert
  11/20/17
  Yahtzee Dice Object
  Should keep track of 5 dice along with how many times each int appears in the set.
  Object Code
*/

#ifndef __DICE_HPP
#define __DICE_HPP

/*
 * A Dice object represents five dice
 * These dice can be easily rolled up to 3 times
 * A macro ROLLS can be redefined to up the maximum number of rolls
 * This object is meant for yahtzee so the dice results can be easily accessed
 *     and the dice held is a binary number of five digits 00000 that is converted
 *     decimal
 *
 */
class Dice {
   private:
	   //Integers of dice each index represents a dice [0,4]
	   int * dice_array;
	   //Integers of how many of each dice value you rolled [0,5]
	   //   The values will be [0,5] five being a yahtzee that was rolled
	   int * dice_results;

	   //Decimal integer that must be convereted to and from binary to access and changed
	   //   The value represents a five digit binary to show which dice are held.
	   int * heldDice;

	   //An incremented variable that will stop if the dice tries to roll more than ROLLS macro
	   int * numberOfRolls;

	   //Private method to be used during roll
	   void updateResult();

   public:
	   //Dice Constructor
	   Dice();

	   //Dice Deconstructor
	   ~Dice();

	   //Roll the dice object
	   void rollDice();

	   //Get the given result of the dice
	   int getResult(int);

	   //Return the sum of all the dice in this object
	   int getSum();

	   //Hold or unHold the given dice object
	   int holdDice(int);

	   //Unholds all the dice. 
	   //Also sets numberOfRolls back to 0
	   //To be used after a turn
	   int unHoldAllDice();

	   //Get the given result of a die
	   int getDice(int);

	   //Get the if a dice is being held
	   bool getDice_held(int);
};

#endif
