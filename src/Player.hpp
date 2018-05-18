/*
  Tristan Hilbert
  11/20/17
  Player class defining a single players scoring pad
  Should be turned into an object
*/

#ifndef __PLAYER_HPP
#define __PLAYER_HPP
/*
 * A Player represents a singular player with 15 score slots
 *    This game is meant to be Yahtzee
 * The player's methods consist mainly of:
 *    scoring
 *    checking scores
 *    checking for bonuses
 *    has boolean for whehter the player is fully scored 
 */
class Player {
   private:
      // 15 integer score array
      int * scoreArray;
      // Boolean to represent whether a player is finished
      bool * finished;

      //Private method that is called when score is called.
      void checkFullyScored();
      //Private methods that are also called during score that check
      //   for automaic scoring
      void checkBonuses();
      void playerBONUS();

   public:

      //Constructor
      Player();

      //Deconstructor
      ~Player();

      //Scores the requested index with the requested score [0,14
      bool score(int, int);
      
      //Gets the requested score from the requested index [0,14]
      int getScore(int);

      //Gets the sum of the player's score array
      int getSum();

      //Returns if the player is finished scoring and can no longer validly score
      bool isPlayerFinished();
      
      //Resets the player back to a beggining state
      void reset();

      //Preps the player to immediately exit without total
      void exit();
};
#endif


