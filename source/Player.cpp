/*
  Tristan Hilbert
  11/21/2017
  The class source code for the player piecie
  This will hold the scoring on a per player basis.
*/
#include "stdafx.h"


Player::Player() {
	Player::finished = new bool;
	*Player::finished = false;
	Player::scoreArray = new int[15];
	for (int i = 0; i < 15; i++) {
		scoreArray[i] = -1;
	}
}

Player::~Player() {
	delete[] Player::scoreArray;
}

bool Player::score(int index, int score) {
	if (Player::scoreArray[index] == -1) {
		Player::scoreArray[index] = score;
		Player::checkFullyScored();
		Player::checkBonuses();
		return true;
	}
	return false;
}

int Player::getScore(int index) {
   return Player::scoreArray[index];
}

int Player::getSum() {
   int returnValue = 0;
   int iterator = 0;
   for (int i = 0; i < 15; i++) {
      iterator = Player::scoreArray[i];
      if (iterator != -1) {
	 returnValue += iterator;
      }
   }
   return returnValue;
}

void Player::checkFullyScored() {
   for (int i = 0; i < 14; i++) { /* Everything but Bonus Yahtzee */
      if (Player::scoreArray[i] == -1)
	 return;
   }
   *Player::finished = true;
}

bool Player::isPlayerFinished() {
   return *Player::finished;
}

void Player::checkBonuses(){
   if(Player::scoreArray[6] == -1){
      Player::playerBONUS();
   }
   if(Player::scoreArray[12] == 0){
      Player::scoreArray[14] = 0; 
   }
}


void Player::playerBONUS(){ 
   int running = 0;
   for(int i = 0; i < 6; i ++){
      if(Player::scoreArray[i] == -1){
	 running = -1;
	 break;
      }else{
         running += Player::scoreArray[i];
      }
   }
   if(running != -1){
      Player::scoreArray[6] = running >= 63 ? 35 : 0;
   }
}

void Player::reset() {
   for (int i = 0; i < 15; i++) {
      Player::scoreArray[i] = -1;
   }
}

void Player::exit(){
   for(int i = 0; i < 15; i ++){
      Player::scoreArray[i] = 0;
      *Player::finished = true;
   }
}
