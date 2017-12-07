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
	void updateResult();

public:
	Dice();
	~Dice();
	void rollDice();
	int getResult(int);
	int getSum();
	int holdDice(int);
	int unHoldAllDice();
	int getDice(int);
	bool getDice_held(int);
};

#endif
