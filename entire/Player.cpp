/*
  Tristan Hilbert
  11/21/2017
  The class source code for the player piecie
  This will hold the scoring on a per player basis.
*/
#include "stdafx.h"


Player::Player() {
	Player::finished = new bool;
	*Player::finished = true;
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
	for (int i = 0; i < 16; i++) {
		if (Player::scoreArray[i] == -1)
			return;
	}
	*Player::finished = false;
}

bool Player::isPlayerFinished() {
	return *Player::finished;
}

void Player::reset() {
	for (int i = 0; i < 15; i++) {
		Player::scoreArray[i] = -1;
	}
}
