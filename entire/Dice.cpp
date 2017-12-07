/*
  Tristan Hilbert
  11/20/2017
  Dice class definitions for methos and such
  This class provides the ability to carry 5 random numbers
*/

#include "stdafx.h"
#ifndef ROLLS
#define ROLLS 3
#endif

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

Dice::~Dice() {
	delete[] Dice::dice_array;
	delete[] Dice::dice_results;
	delete Dice::heldDice;
	delete Dice::numberOfRolls;
}

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

int Dice::getResult(int index) {
   return Dice::dice_results[index - 1];
}

void Dice::updateResult() {
   for (int i = 0; i < 6; i++) {
      Dice::dice_results[i] = 0;
   }
   for (int i = 0; i < 5; i++) {
      Dice::dice_results[dice_array[i] - 1] ++;
   }
}

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
