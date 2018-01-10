/*
  Tristan Hilbert
  11/20/17
  Yahtzee Dice Object
  Should keep track of 5 dice along with how many times each int appears in the set.
  Object Code
*/

#ifndef DiceClass
#define DiceClass


class Dice {
private:
	int * dice_array;
	int * dice_results;
	int * heldDice;
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

	//Unholds all the dice. To be used after a turn
	int unHoldAllDice();

	//Get the given result of a die
	int getDice(int);

	//Get the if a dice is being held
	bool getDice_held(int);
};

#endif
