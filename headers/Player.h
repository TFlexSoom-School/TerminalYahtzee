/*
  Tristan Hilbert
  11/20/17
  Player class defining a single players scoring pad
  Should be turned into an object
*/

#ifndef PlayerClass
#define PlayerClass

class Player {
private:
	int * scoreArray;
	bool * finished;

	void checkFullyScored();

public:
	Player();
	~Player();
	bool score(int, int);
	int getScore(int);
	int getSum();
	bool isPlayerFinished();
	void reset();
};
#endif