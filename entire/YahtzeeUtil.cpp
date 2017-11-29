#include "stdafx.h"
/*
* From Assignment 4
*
* twoPow(int power)
* returns two to the power of the parameter
* preconditions: power >= 0 for intended use
* postconditions: none
* return: 2^power
*/
int twoPow(int power) {
	if (power <= 0) {
		return 1;
	}

	return 2 * twoPow(power - 1);
}

/*
  Tristan Hilbert
  getRandomNumber(int start, int end)
  gets a random number based on start inclusive and end exclusive
  Pre: Seed before using
  Post: None
  Return: int as described above.
*/
int getRandomNumber(int start, int end) {
	return (rand() % (end - start)) + start;
}

std::string int_to_string(int num) {
	if (num == 0) {
		return "";
	}
	char add = num%10 + '0';
	return int_to_string(num / 10) + add;
}
