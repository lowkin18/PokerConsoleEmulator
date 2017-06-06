#pragma once
#pragma once


#include <math.h>
#include <stdio.h>

#define MAXPLAYER 4

//card object not in use
typedef struct
{
	int card1;
	int suit1;
}card;



typedef struct
{
	card card1;
	card card2;
	card card3;
	card card4;
	card card5;
	int Value[5];
	int handType;
	int winner;

}endHand;

typedef struct
{
	int card1;
	int card2;
	int offsuit;
	int played;
	int won;

}starthand;

typedef struct
{
	int pPlay;
	int pFold;
	int wins;
	int lostRiver;

}pData;
typedef struct
{
	int *flopOdds[MAXPLAYER];
	int turnOdds[MAXPLAYER];
	int *riverOdds[MAXPLAYER];
	starthand *da;
}dataStat;

typedef struct
{
	int card1;
	int	card2;
	int suit1;
	int suit2;
	int folded; //1 is folded
	int check;
	char cardS1[25]; //string for console output
	char cardS2[25]; //string for console output
}hand;

typedef struct
{
	card flop[3];
	card turn[1];
	card river[1];
}board;

typedef struct
{
	int dealer;
	int hand;
	int bBlind;
	int sBlind;
	int raiseSpot;
	int play;
}layout;


typedef struct
{
	int pot;//POT TOTAL
	int playerMoney[MAXPLAYER];//there total money
	int bets[MAXPLAYER];//how much they have bet this round
	int totalbet;//total bet to call
	int rebuy[MAXPLAYER];//how many times they rebuy
	int raiseNum[MAXPLAYER];//there location on the table
	int pftrBets[4];

}money;


typedef struct
{
	layout buttons; //Button locations
	hand player[MAXPLAYER]; //player hands and flags
	money moneyPlayer; //Player money and table money
	board board; //BOARD CARDS
	dataStat odds; //ODDS
	int foldCount;// if all players fold then go to river for data.
	int loc[MAXPLAYER];//location of player
	int raise;// calculates if theres a raise and syncs with players
	int pftr; // PREFLOP FLOP TURN RIVER
	int Human; //if human plays FLAG
	int humanAction;
	int endBetting;//for the loop Action calc to end
	endHand finHand[MAXPLAYER]; // ending hand calcs
	pData pData[MAXPLAYER]; //player data table
	endHand bestHand[MAXPLAYER]; //there best ending hand
	int winner;

}data;


//function DECLARATIONS FOR HEADER
void playerLocation(data * ptr);


int compareHand(data * ptr, int player);
void checkCall(data *ptr, int player);
void bet(data *ptr, int player, int percent);
void fold(data *ptr, int player);
void raise(data *ptr, int player);
void clearBets(data * ptr);
void randGenBoard(data *ptr);
void handDatabase(data * ptr);
void readDatabase(data * ptr);
void checkValue(data *ptr, int player);
void handValue(data *ptr, int player);
void valueCompare(data *ptr);


//CHECK WINNING HANDS
void checkFlush(data *ptr, int player);
void checkStraight(data *ptr, int player);
void check4kind(data *ptr, int player);
void checkFull(data *ptr, int player);
void highCard(data *ptr, int player);
int checkTie(data *ptr, int winner);
void giveWinnerMoney(data *ptr, int winner);
void calcButtons(data *ptr);

void changeHandStrength(data * ptr, int * val, int player);
void playerBestHand(data *ptr, int player);

//PLAYER ACTIONS ON THE STREETS
void preFlopAction(data * ptr, int player);
void flopAction(data*ptr, int player);
void turnAction(data *ptr, int player);
void riverAction(data *ptr, int player);
void humanAction(data * ptr);
int straightCalcOdds(data *ptr, int player);
int pairCalcOdds(data * ptr, int player);

void(*action_ptr[3])(data *ptr, int player) = { flopAction,turnAction,riverAction };
//ODD CALCS ROUGH
int roughFlopOdd(data * ptr, int player);
int roughPreFLOPoddCalc(data * ptr, int player);
int roughTurnOdd(data *ptr, int player);
void turnOddCalc(data *ptr, int player);
int *bestHandFinder(data*ptr, int p);
int roughRiverOdd(data*ptr, int player);

//TURN ODD CALCS
int quadTurnOdds(data * ptr, int player);
int straightTurnOdds(data *ptr, int player);
int flushTurnOdds(data *ptr, int player);
int pairTurnOdds(data * ptr, int player);
void bestHandFinderTurn(data *ptr, int player);
//void debug(data *ptr, int p);
//data stuff
void HandCalcData(data * ptr, int player);

//PLAYER FUNCTIONS
void playerDecision(data * ptr);

/*void debug(data *ptr, int p)
{

if (ptr->moneyPlayer.rebuy[1]>1000)
{
printf("THIS CODE IS FUCKING BREAKING HERE %d NUM GIVEN %d", ptr->pftr, p);
printf("\nTHE VALUE OF %d", ptr->moneyPlayer.rebuy[1]);
getchar();
}

}*/
// WRITES TO THE DATABASE WITH NEWLY AQUIRED DATA
