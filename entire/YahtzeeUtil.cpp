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
 *Tristan Hilbert
 *getRandomNumber(int start, int end)
 *gets a random number based on start inclusive and end exclusive
 *Pre: Seed before using
 *Post: None
 *Return: int as described above.
 */
int getRandomNumber(int start, int end) {
   return (rand() % (end - start)) + start;
}

/*
 * Tristan Hilbert
 * int_to_string(int num, int length);
 * Recursivly formats an integer num to a int lenght size of string
 * 	spaces are added to the back side
 * precondition: none;
 * postcondition: none;
 * returns formatted string;
 */
std::string int_to_string(int num, int length) {
   if (num == 0 || length <= 0) {
      if(length > 0){
	 return  ' ' + int_to_string(num, length - 1);
      }else
	 return "";
   }
   char add = num%10 + '0';
   return int_to_string(num / 10, length - 1) + add;
}
