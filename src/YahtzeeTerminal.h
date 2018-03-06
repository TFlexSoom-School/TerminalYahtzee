
#ifndef TERMINAL
#define TERMINAL

/* Function Prototypes */
int extractInts(char[]);
void Yahtzee(int);
bool scoreOrReroll(Player *, Dice *, UI *);
void startNewGame(Player *, int);
void destroyGame(Player *, Dice *, UI *);
bool playerStillPlaying(Player*);
bool allPlayersScored(Player *, int);
bool playAgain();
int twoPow(int);
int ofKind(Dice *, int);
int fullHouse(Dice *);
int smStraight(Dice *);
int lgStraight(Dice *);
int diceYahtzee(Dice *);
bool bonusYahtzee(Player *, Dice *);

#endif
