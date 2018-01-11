/*
  Tristan Hilbert
  11/21/2017
  The class source code for the player piecie
  This will hold the scoring on a per player basis.
*/
#include "stdafx.h"


/*
 * Constructor 
 * Creates a player with a boolean on the heap
 * Creates a score chart on the heap which is a 15 length int array
 * 	Every score within the chart is initialized to -1
 */
Player::Player() {
   Player::finished = new bool;
   *Player::finished = false;
   Player::scoreArray = new int[15];
   for (int i = 0; i < 15; i++) {
      scoreArray[i] = -1;
   }
}

/*
 * Player Deconstructor
 * Frees up memory that was put on the heap.
 */
Player::~Player() {
   delete Player::finished;
   delete[] Player::scoreArray;
}

/*
 * score(int, int)
 * scores at the given index the given int score.
 *    the method will also automatically check if the player qualifies for bonuses
 * param: index of the score [0,14], number of points for the score
 * pre: index is [0,14]
 * post: A new score will be added if it is valid
 * return: if a new score added return true otherwise return false
 */
bool Player::score(int index, int score) {
   if (Player::scoreArray[index] == -1) {
      Player::scoreArray[index] = score;
      Player::checkFullyScored();
      Player::checkBonuses();
      return true;
   }
   return false;
}

/*
 * getScore(int)
 * returns the given score at the index
 * param: index of the desired score
 * pre: index is [0,14]
 * post: none
 * return: the score at the index
 */
int Player::getScore(int index) {
   return Player::scoreArray[index];
}

/*
 * getSum()
 * returns a total sum of all of this player's scores
 * param: None
 * pre: none
 * post none
 * return the current total score
 */
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

/*
 * checkFullyScored()
 * checks if every score index in the player's score array is scored
 * param: None
 * pre: none
 * post finished boolean becomes true if player is fully scored [0,14]
 * return None
 */
void Player::checkFullyScored() {
   for (int i = 0; i < 14; i++) { /* Everything but Bonus Yahtzee */
      if (Player::scoreArray[i] == -1)
	 return;
   }
   *Player::finished = true;
}


/*
 * isPlayerFinished()
 * Returns the value of the finished variable
 * param: None
 * pre: None
 * post: None
 * return the boolean value representing the player's finish state
 */
bool Player::isPlayerFinished() {
   return *Player::finished;
}

/*
 * checkBonuses()
 * Checks first if the player still needs the bonus square 
 *    and if it can score bonus yahtzee
 * param: None
 * pre: none
 * post Bonuses may be scored depending on prexisting scored
 * return None
 */
void Player::checkBonuses(){
   if(Player::scoreArray[6] == -1){
      Player::playerBONUS();
   }
   if(Player::scoreArray[12] == 0){
      Player::scoreArray[14] = 0; 
   }
}


/*
 * playerBonus()
 * If player has indexes [0,5] scored then it may add a 35 point bonus
 * 	The indexes above need to total 63 or more
 * param: None
 * pre: none
 * post: index 6 may be scored if [0,5] indexes are not -1
 * return: None
 */
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

/*
 * reset()
 * resets player score board back to -1 
 * param: None
 * pre: none
 * post: each index of player score array will be reinitialized to -1
 * return: None
 */
void Player::reset() {
   for (int i = 0; i < 15; i++) {
      Player::scoreArray[i] = -1;
   }
}

/*
 * exit()
 * Sets all of player score to 0 so player can immediately exit 
 * TODO perhaps make it only unitialized scores to allow for a final score or score board
 * param: None
 * pre: none
 * post: Player will be scored 0 and will be set to finished
 * return: None
 */
void Player::exit(){
   for(int i = 0; i < 15; i ++){
      Player::scoreArray[i] = 0;
      *Player::finished = true;
   }
}
