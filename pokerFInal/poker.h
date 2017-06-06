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
void handDatabase(data*ptr)
{

	FILE *inputFile = fopen("pokerdatabase.txt", "w");
	if (inputFile == NULL)
	{
		fprintf(stderr, "Can't open output file!\n");
	}
	/*int card1 = 0;
	int count = 0;
	for (int k = card1; k < 13; k++)
	{


	ptr->odds.da[count].card1 = card1;
	for (int p = card1; p < 13; p++)
	{

	ptr->odds.da[count].card2 = p;
	ptr->odds.da[count].card1 = card1;
	if (ptr->odds.da[count].card1 != ptr->odds.da[count].card2)
	{
	ptr->odds.da[count].played = 0;
	ptr->odds.da[count].won = 0;
	ptr->odds.da[count].offsuit = 0;
	count++;
	}
	}
	card1++;
	}
	card1 = 0;
	for (int k = card1; k < 13; k++)
	{


	ptr->odds.da[count].card1 = card1;
	for (int p = card1; p < 13; p++)
	{

	ptr->odds.da[count].card2 = p;
	ptr->odds.da[count].card1 = card1;
	if (ptr->odds.da[count].card1 != ptr->odds.da[count].card2)
	{
	ptr->odds.da[count].played = 0;
	ptr->odds.da[count].won = 0;
	ptr->odds.da[count].offsuit = 1;
	count++;
	}
	}
	card1++;
	}

	for (int pair = 0; pair < 13; pair++)
	{
	ptr->odds.da[count].card2 = pair;
	ptr->odds.da[count].card1 = pair;
	ptr->odds.da[count].played = 0;
	ptr->odds.da[count].won = 0;
	ptr->odds.da[count].offsuit = 2;
	count++;
	}*/

	for (int j = 0; j < 169; j++)
	{
		fprintf(inputFile, "%d %d %d %d %d\n", ptr->odds.da[j].card1, ptr->odds.da[j].card2, ptr->odds.da[j].offsuit, ptr->odds.da[j].played, ptr->odds.da[j].won);
		printf("%d %d %d %d %d\n", ptr->odds.da[j].card1, ptr->odds.da[j].card2, ptr->odds.da[j].offsuit, ptr->odds.da[j].played, ptr->odds.da[j].won);

	}
	fclose(inputFile);
}

//READS THE DATABASE FOR THE HAND TYPES AND PERCENTAGES
void readDatabase(data * ptr)
{
	ptr->odds.da = malloc(sizeof(starthand) * 180);
	FILE *outPutFile = fopen("pokerdatabase.txt", "r");
	if (outPutFile == NULL)
	{
		fprintf(stderr, "Can't open output file!\n");
	}

	for (int j = 0; j < 169; j++)
	{
		fscanf(outPutFile, "%d %d %d %d %d", &ptr->odds.da[j].card1, &ptr->odds.da[j].card2, &ptr->odds.da[j].offsuit, &ptr->odds.da[j].played, &ptr->odds.da[j].won);
	}
	/*for (int j = 0; j < 169; j++)
	{
	printf("%d %d %d %d %d\n", ptr->odds.da[j].card1, ptr->odds.da[j].card2, ptr->odds.da[j].offsuit, ptr->odds.da[j].played, ptr->odds.da[j].won);
	}*/
	
	fclose(outPutFile);

	for (int j = 0; j < 4; j++)
	{
		ptr->pData[j].pPlay = 0;
		ptr->pData[j].pFold = 0;
	}
	FILE *outPutPlayer = fopen("pokerplayerdata.txt", "r");
	if (outPutPlayer == NULL)
	{
		fprintf(stderr, "Can't open output file!\n");
	}

	for (int j = 0; j < 4; j++)
	{
		fscanf(outPutPlayer, "%d %d", ptr->pData[j].pPlay, ptr->pData[j].pFold);
	}

	fclose(outPutPlayer);

}

//RANDOMIZES BUTTON POSITION AND STARTS THE INITIAL CONDITIONS
layout startSetup()
{
	layout start1;
	int k = rand() % 4;
	//printf("%d K ", k);
	start1.dealer = k;
	start1.hand = 0;
	start1.play = 1;


	//printf("BUTTON IS %d", start1.dealer);
	return start1;
}

//MAKES SURE THERE ARE NO REPEAT CARDS
int compareHand(data * ptr, int player)
{




	int check = 0;
	for (int k = 0; k < 4; k++)
	{
		if (player != k)
		{
			if (ptr->player[k].card1 == ptr->player[player].card1)
			{
				if (ptr->player[k].suit1 == ptr->player[player].suit1)
				{
					check = 1;
				}
			}
			if (ptr->player[k].card1 == ptr->player[player].card2)
			{
				if (ptr->player[k].suit1 == ptr->player[player].suit2)
				{
					check = 1;
				}
			}
			if (ptr->player[k].card2 == ptr->player[player].card1)
			{
				if (ptr->player[k].suit2 == ptr->player[player].suit1)
				{
					check = 1;
				}
			}
			if (ptr->player[k].card2 == ptr->player[player].card2)
			{
				if (ptr->player[k].suit2 == ptr->player[player].suit2)
				{
					check = 1;
				}
			}
		}
	}

	if (ptr->player[player].card1 == ptr->player[player].card2)
	{
		if (ptr->player[player].suit1 == ptr->player[player].suit2)
		{
			check = 1;
		}
	}

	if (check == 1) return 1;
	if (check == 0) return 0;
}

//CALCS WHERE THE BUTTONS ARE
void calcButtons(data *ptr)
{
	if (ptr->buttons.dealer == 0)
	{
		ptr->buttons.sBlind = 1;
		ptr->buttons.bBlind = 2;
		ptr->moneyPlayer.raiseNum[0] = 0;
		ptr->moneyPlayer.raiseNum[1] = 1;
		ptr->moneyPlayer.raiseNum[2] = 2;
		ptr->moneyPlayer.raiseNum[3] = 3;

	}
	if (ptr->buttons.dealer == 1)
	{
		ptr->buttons.sBlind = 2;
		ptr->buttons.bBlind = 3;
		ptr->moneyPlayer.raiseNum[1] = 0;
		ptr->moneyPlayer.raiseNum[2] = 1;
		ptr->moneyPlayer.raiseNum[3] = 2;
		ptr->moneyPlayer.raiseNum[0] = 3;

	}
	if (ptr->buttons.dealer == 2)
	{
		ptr->buttons.sBlind = 3;
		ptr->buttons.bBlind = 0;
		ptr->moneyPlayer.raiseNum[2] = 0;
		ptr->moneyPlayer.raiseNum[3] = 1;
		ptr->moneyPlayer.raiseNum[0] = 2;
		ptr->moneyPlayer.raiseNum[1] = 3;

	}
	if (ptr->buttons.dealer == 3)
	{
		ptr->buttons.sBlind = 0;
		ptr->buttons.bBlind = 1;
		ptr->moneyPlayer.raiseNum[3] = 0;
		ptr->moneyPlayer.raiseNum[0] = 1;
		ptr->moneyPlayer.raiseNum[1] = 2;
		ptr->moneyPlayer.raiseNum[2] = 3;

	}
	playerLocation(ptr);
}
//INITIAL HANDDRAW FROM TABLE OPENING
data handDraw(layout * set)
{
	data mainData;
	mainData.buttons = (*set);
	mainData.loc[0] = 0;
	mainData.pftr = 0;
	for (int p = 0; p < MAXPLAYER; p++)
	{
		mainData.pData[p].pPlay = 0;
		mainData.pData[p].pFold = 0;
		mainData.pData[p].lostRiver = 0;
		mainData.pData[p].wins = 0;
	}
	mainData.buttons.hand = 0;
	for (int j = 0; j < MAXPLAYER; j++)
	{
		mainData.moneyPlayer.raiseNum[j] = j;
		mainData.moneyPlayer.rebuy[j] = 0;
	}
	char human = 'n';
	printf("do you want to play poker? y/n");
	scanf("%c", &human);
	if (human == 'y')
	{
	mainData.Human = 1;
	}
	
	clearBets(&mainData);
	calcButtons(&mainData);
	readDatabase(&mainData);

	for (int k = 0; k < 4; k++)
	{
		mainData.player[k].card1 = k + 100;
		mainData.player[k].card2 = k + 10;
		mainData.player[k].suit1 = k + 100;
		mainData.player[k].suit2 = k + 10;
		mainData.player[k].folded = 0;
	}


	if (set->dealer == 0)
	{
		int p = 1;
		do
		{
			mainData.player[p].card1 = rand() % 13;
			mainData.player[p].suit1 = rand() % 4;
		} while (compareHand(&mainData, p));
		p++;
		do
		{
			mainData.player[p].card1 = rand() % 13;
			mainData.player[p].suit1 = rand() % 4;
		} while (compareHand(&mainData, p));
		p++;
		do
		{
			mainData.player[p].card1 = rand() % 13;
			mainData.player[p].suit1 = rand() % 4;
		} while (compareHand(&mainData, p));
		p = 0;
		do
		{
			mainData.player[p].card1 = rand() % 13;
			mainData.player[p].suit1 = rand() % 4;
		} while (compareHand(&mainData, p));
	}
	if (set->dealer == 1)
	{
		int p = 2;
		do
		{
			mainData.player[p].card1 = rand() % 13;
			mainData.player[p].suit1 = rand() % 4;
		} while (compareHand(&mainData, p));
		p++;
		do {
			mainData.player[p].card1 = rand() % 13;
			mainData.player[p].suit1 = rand() % 4;
		} while (compareHand(&mainData, p));
		p = 0;
		do {
			mainData.player[p].card1 = rand() % 13;
			mainData.player[p].suit1 = rand() % 4;
		} while (compareHand(&mainData, p));
		p++;
		do
		{
			mainData.player[p].card1 = rand() % 13;
			mainData.player[p].suit1 = rand() % 4;
		} while (compareHand(&mainData, p));
	}
	if (set->dealer == 2)
	{
		int p = 3;
		do {
			mainData.player[p].card1 = rand() % 13;
			mainData.player[p].suit1 = rand() % 4;
		} while (compareHand(&mainData, p));
		p = 0;
		do {
			mainData.player[p].card1 = rand() % 13;
			mainData.player[p].suit1 = rand() % 4;
		} while (compareHand(&mainData, p));
		p++;
		do {
			mainData.player[p].card1 = rand() % 13;
			mainData.player[p].suit1 = rand() % 4;
		} while (compareHand(&mainData, p));
		p++;
		do {
			mainData.player[p].card1 = rand() % 13;
			mainData.player[p].suit1 = rand() % 4;
		} while (compareHand(&mainData, p));
	}
	if (set->dealer == 3)
	{
		int p = 0;
		do
		{
			mainData.player[p].card1 = rand() % 13;
			mainData.player[p].suit1 = rand() % 4;
		} while (compareHand(&mainData, p));
		p++;
		do {
			mainData.player[p].card1 = rand() % 13;
			mainData.player[p].suit1 = rand() % 4;
		} while (compareHand(&mainData, p));
		do {
			p++;
			mainData.player[p].card1 = rand() % 13;
			mainData.player[p].suit1 = rand() % 4;
		} while (compareHand(&mainData, p));
		p++;
		do
		{
			mainData.player[p].card1 = rand() % 13;
			mainData.player[p].suit1 = rand() % 4;
		} while (compareHand(&mainData, p));
	}
	if (set->dealer == 0)
	{
		int p = 1;
		do
		{
			mainData.player[p].card2 = rand() % 13;
			mainData.player[p].suit2 = rand() % 4;
		} while (compareHand(&mainData, p));
		p++;
		do
		{
			mainData.player[p].card2 = rand() % 13;
			mainData.player[p].suit2 = rand() % 4;
		} while (compareHand(&mainData, p));
		p++;
		do
		{
			mainData.player[p].card2 = rand() % 13;
			mainData.player[p].suit2 = rand() % 4;
		} while (compareHand(&mainData, p));
		p = 0;
		do
		{
			mainData.player[p].card2 = rand() % 13;
			mainData.player[p].suit2 = rand() % 4;
		} while (compareHand(&mainData, p));
	}
	if (set->dealer == 1)
	{
		int p = 2;
		do
		{
			mainData.player[p].card2 = rand() % 13;
			mainData.player[p].suit2 = rand() % 4;
		} while (compareHand(&mainData, p));
		p++;
		do {
			mainData.player[p].card2 = rand() % 13;
			mainData.player[p].suit2 = rand() % 4;
		} while (compareHand(&mainData, p));
		p = 0;
		do {
			mainData.player[p].card2 = rand() % 13;
			mainData.player[p].suit2 = rand() % 4;
		} while (compareHand(&mainData, p));
		p++;
		do
		{
			mainData.player[p].card2 = rand() % 13;
			mainData.player[p].suit2 = rand() % 4;
		} while (compareHand(&mainData, p));
	}
	if (set->dealer == 2)
	{
		int p = 3;
		do {
			mainData.player[p].card2 = rand() % 13;
			mainData.player[p].suit2 = rand() % 4;
		} while (compareHand(&mainData, p));
		p = 0;
		do {
			mainData.player[p].card2 = rand() % 13;
			mainData.player[p].suit2 = rand() % 4;
		} while (compareHand(&mainData, p));
		p++;
		do {
			mainData.player[p].card2 = rand() % 13;
			mainData.player[p].suit2 = rand() % 4;
		} while (compareHand(&mainData, p));
		p++;
		do {
			mainData.player[p].card2 = rand() % 13;
			mainData.player[p].suit2 = rand() % 4;
		} while (compareHand(&mainData, p));
	}
	if (set->dealer == 3)
	{
		int p = 0;
		do
		{
			mainData.player[p].card2 = rand() % 13;
			mainData.player[p].suit2 = rand() % 4;
		} while (compareHand(&mainData, p));
		p++;
		do {
			mainData.player[p].card2 = rand() % 13;
			mainData.player[p].suit2 = rand() % 4;
		} while (compareHand(&mainData, p));
		do {
			p++;
			mainData.player[p].card2 = rand() % 13;
			mainData.player[p].suit2 = rand() % 4;
		} while (compareHand(&mainData, p));
		p++;
		do
		{
			mainData.player[p].card2 = rand() % 13;
			mainData.player[p].suit2 = rand() % 4;
		} while (compareHand(&mainData, p));
	}

	return(mainData);
}

//CLEARBETS AFTER EACH HAND OR AT EACH INTERVAL
void clearBets(data * ptr)
{
	ptr->raise = 0;
	for (int k = 0; k < MAXPLAYER; k++)
	{
		ptr->moneyPlayer.bets[k] = 0;
	}

	if (ptr->pftr == 0)
	{
		ptr->moneyPlayer.pot = 0;
		for (int j = 0; j < MAXPLAYER; j++)
		{
			ptr->player[j].folded = 0;
			ptr->foldCount = 0;
		}

	}
	for (int j = 0; j < MAXPLAYER; j++)
	{
		ptr->player[j].check = 0;
	}

	ptr->moneyPlayer.totalbet = 0;
	ptr->endBetting = 1;

	return;
}

//AFTER THE FIRST HAND REDRAW IS USED
void reDraw(data *ptr)
{
	ptr->pftr = 0;
	clearBets(ptr);
	calcButtons(ptr);
	for (int k = 0; k < 4; k++)
	{
		ptr->player[k].card1 = k + 100;
		ptr->player[k].card2 = k + 10;
		ptr->player[k].suit1 = k + 100;
		ptr->player[k].suit2 = k + 10;
		ptr->player[k].folded = 0;
	}


	if (ptr->buttons.dealer == 0)
	{
		int p = 1;
		do
		{
			ptr->player[p].card1 = rand() % 13;
			ptr->player[p].card2 = rand() % 13;
			ptr->player[p].suit1 = rand() % 4;
			ptr->player[p].suit2 = rand() % 4;
		} while (compareHand(ptr, p));
		p++;
		do
		{
			ptr->player[p].card1 = rand() % 13;
			ptr->player[p].card2 = rand() % 13;
			ptr->player[p].suit1 = rand() % 4;
			ptr->player[p].suit2 = rand() % 4;
		} while (compareHand(ptr, p));
		p++;
		do
		{
			ptr->player[p].card1 = rand() % 13;
			ptr->player[p].card2 = rand() % 13;
			ptr->player[p].suit1 = rand() % 4;
			ptr->player[p].suit2 = rand() % 4;
		} while (compareHand(ptr, p));
		p = 0;
		do
		{
			ptr->player[p].card1 = rand() % 13;
			ptr->player[p].card2 = rand() % 13;
			ptr->player[p].suit1 = rand() % 4;
			ptr->player[p].suit2 = rand() % 4;
		} while (compareHand(ptr, p));
	}
	if (ptr->buttons.dealer == 1)
	{
		int p = 2;
		do
		{
			ptr->player[p].card1 = rand() % 13;
			ptr->player[p].card2 = rand() % 13;
			ptr->player[p].suit1 = rand() % 4;
			ptr->player[p].suit2 = rand() % 4;
		} while (compareHand(ptr, p));
		p++;
		do {
			ptr->player[p].card1 = rand() % 13;
			ptr->player[p].card2 = rand() % 13;
			ptr->player[p].suit1 = rand() % 4;
			ptr->player[p].suit2 = rand() % 4;
		} while (compareHand(ptr, p));
		p = 0;
		do {
			ptr->player[p].card1 = rand() % 13;
			ptr->player[p].card2 = rand() % 13;
			ptr->player[p].suit1 = rand() % 4;
			ptr->player[p].suit2 = rand() % 4;
		} while (compareHand(ptr, p));
		p++;
		do
		{
			ptr->player[p].card1 = rand() % 13;
			ptr->player[p].card2 = rand() % 13;
			ptr->player[p].suit1 = rand() % 4;
			ptr->player[p].suit2 = rand() % 4;
		} while (compareHand(ptr, p));
	}
	if (ptr->buttons.dealer == 2)
	{
		int p = 3;
		do {
			ptr->player[p].card1 = rand() % 13;
			ptr->player[p].card2 = rand() % 13;
			ptr->player[p].suit1 = rand() % 4;
			ptr->player[p].suit2 = rand() % 4;
		} while (compareHand(ptr, p));
		p = 0;
		do {
			ptr->player[p].card1 = rand() % 13;
			ptr->player[p].card2 = rand() % 13;
			ptr->player[p].suit1 = rand() % 4;
			ptr->player[p].suit2 = rand() % 4;
		} while (compareHand(ptr, p));
		p++;
		do {
			ptr->player[p].card1 = rand() % 13;
			ptr->player[p].card2 = rand() % 13;
			ptr->player[p].suit1 = rand() % 4;
			ptr->player[p].suit2 = rand() % 4;
		} while (compareHand(ptr, p));
		p++;
		do {
			ptr->player[p].card1 = rand() % 13;
			ptr->player[p].card2 = rand() % 13;
			ptr->player[p].suit1 = rand() % 4;
			ptr->player[p].suit2 = rand() % 4;
		} while (compareHand(ptr, p));
	}
	if (ptr->buttons.dealer == 3)
	{
		int p = 0;
		do
		{
			ptr->player[p].card1 = rand() % 13;
			ptr->player[p].card2 = rand() % 13;
			ptr->player[p].suit1 = rand() % 4;
			ptr->player[p].suit2 = rand() % 4;
		} while (compareHand(ptr, p));
		p++;
		do
		{

			ptr->player[p].card1 = rand() % 13;
			ptr->player[p].card2 = rand() % 13;
			ptr->player[p].suit1 = rand() % 4;
			ptr->player[p].suit2 = rand() % 4;
		} while (compareHand(ptr, p));
		p++;
		do
		{
			ptr->player[p].card1 = rand() % 13;
			ptr->player[p].card2 = rand() % 13;
			ptr->player[p].suit1 = rand() % 4;
			ptr->player[p].suit2 = rand() % 4;
		} while (compareHand(ptr, p));
		p++;
		do
		{
			ptr->player[p].card1 = rand() % 13;
			ptr->player[p].card2 = rand() % 13;
			ptr->player[p].suit1 = rand() % 4;
			ptr->player[p].suit2 = rand() % 4;
		} while (compareHand(ptr, p));
	}
	return;
}

//PRINTFF DATA CHECK
void checkData(data *ptr, int local)
{
	if (local == 1)
	{
		for (int k = 0; k < 4; k++)
		{
			printf("\n%d card %d suit %d card %d suit PLAYER %d\n", ptr->player[k].card1, ptr->player[k].suit1, ptr->player[k].card2, ptr->player[k].suit2, k);
		}
		//printf("\n%d pot   %d player 1\n", ptr->moneyPlayer.pot, ptr->moneyPlayer.playerMoney[0]);
		return 0;
	}
	if (local == 2)
	{
		printf("\n%d TOTAL POT IS NOW", ptr->moneyPlayer.pot);
		for (int k = 0; k < 4; k++)
		{
			if (ptr->player[k].folded == 1)
			{
				printf("%d PLAYER HAS FOLDED", k);
			}
		}
	}
}

//COLLECTS THE BLINDS FOR THE HAND
data blinds(data * ptr)
{


	if (ptr->buttons.hand == 0)
	{
		ptr->moneyPlayer.playerMoney[1] = 20000;
		ptr->moneyPlayer.playerMoney[2] = 20000;
		ptr->moneyPlayer.playerMoney[3] = 20000;
		ptr->moneyPlayer.playerMoney[0] = 20000;
	}

	for (int k = 0; k < MAXPLAYER; k++)
	{
		if (ptr->moneyPlayer.playerMoney[k] < 5000)
		{
			printf("player %d REBUYS REBUY %d", k, ptr->moneyPlayer.rebuy[k]);
			ptr->moneyPlayer.rebuy[k] += 1;
			printf("\nplayer %d REBUYS REBUY %d", k, ptr->moneyPlayer.rebuy[k]);
			ptr->moneyPlayer.playerMoney[k] = 20000;
		}


	}


	int sBlind = 25;
	int bBlind = 50;
	ptr->moneyPlayer.pot = sBlind + bBlind;

	if (ptr->buttons.dealer == 0)
	{
		ptr->moneyPlayer.playerMoney[1] = ptr->moneyPlayer.playerMoney[1] - 25;
		ptr->moneyPlayer.playerMoney[2] = ptr->moneyPlayer.playerMoney[2] - 50;
		ptr->moneyPlayer.bets[1] = 25;
		ptr->moneyPlayer.bets[2] = 50;
		ptr->moneyPlayer.bets[3] = 0;
		ptr->moneyPlayer.bets[0] = 0;


	}
	if (ptr->buttons.dealer == 1)
	{
		ptr->moneyPlayer.playerMoney[2] = ptr->moneyPlayer.playerMoney[2] - 25;
		ptr->moneyPlayer.playerMoney[3] = ptr->moneyPlayer.playerMoney[3] - 50;
		ptr->moneyPlayer.bets[2] = 25;
		ptr->moneyPlayer.bets[3] = 50;
		ptr->moneyPlayer.bets[0] = 0;
		ptr->moneyPlayer.bets[1] = 0;
	}
	if (ptr->buttons.dealer == 2)
	{
		ptr->moneyPlayer.playerMoney[3] = ptr->moneyPlayer.playerMoney[3] - 25;
		ptr->moneyPlayer.playerMoney[0] = ptr->moneyPlayer.playerMoney[0] - 50;
		ptr->moneyPlayer.bets[3] = 25;
		ptr->moneyPlayer.bets[0] = 50;
		ptr->moneyPlayer.bets[1] = 0;
		ptr->moneyPlayer.bets[2] = 0;
	}
	if (ptr->buttons.dealer == 3)
	{
		ptr->moneyPlayer.playerMoney[0] = ptr->moneyPlayer.playerMoney[0] - 25;
		ptr->moneyPlayer.playerMoney[1] = ptr->moneyPlayer.playerMoney[1] - 50;
		ptr->moneyPlayer.bets[0] = 25;
		ptr->moneyPlayer.bets[1] = 50;
		ptr->moneyPlayer.bets[2] = 0;
		ptr->moneyPlayer.bets[3] = 0;
	}
	ptr->moneyPlayer.totalbet = 50;
	return(*ptr);



}

//COORDINATES PREFLOP ACTION
void preFlop(data * ptr)
{
	calcButtons(ptr);
	ptr->raise = 0;
	ptr->endBetting = 1;
	ptr->buttons.raiseSpot = ptr->buttons.bBlind;
	do
	{
		switch (ptr->buttons.dealer) {
		case 0:
			//player 3 bets
			preFlopAction(ptr, 3);
			preFlopAction(ptr, 0);
			preFlopAction(ptr, 1);
			preFlopAction(ptr, 2);
			break;
		case 1:
			//player 0 bets
			preFlopAction(ptr, 0);
			preFlopAction(ptr, 1);
			preFlopAction(ptr, 2);
			preFlopAction(ptr, 3);
			break;
		case 2:
			//player 1 bets
			preFlopAction(ptr, 1);
			preFlopAction(ptr, 2);
			preFlopAction(ptr, 3);
			preFlopAction(ptr, 0);
			break;
		case 3:
			//player 2 leads
			preFlopAction(ptr, 2);
			preFlopAction(ptr, 3);
			preFlopAction(ptr, 0);
			preFlopAction(ptr, 1);
			break;
		default:
			printf("error in preFlop");
			break;
		}
	} while (ptr->endBetting == 1);
}

//DOES PREFLOP ACTION
void preFlopAction(data * ptr, int player)
{

	if (ptr->Human == 1 && player == 0)
	{
		playerDecision(ptr);
	}
	printf("\nTHE POT TOTAL IS %d\n", ptr->moneyPlayer.pot);
	if (ptr->buttons.raiseSpot == player)
	{
		printf("\nNOW FLOPPING\n");
		ptr->endBetting = 0;
		return;
	}

	if (ptr->endBetting == 0)
	{
		return;
	}
	if (ptr->player[player].folded == 1)
	{
		return;
	}
	int percent = roughPreFLOPoddCalc(ptr, player);
	printf("\n%d %PERCENT %d PLAYER\n", percent, player);
	if (percent <= 10)
	{
		fold(ptr, player);
		return;
	}
	if (percent > 10 && percent < 25)
	{
		checkCall(ptr, player);
		return;
	}
	if (percent >= 25)
	{
		bet(ptr, player, percent);

		return;
	}



	printf("ERROR IN PREFLOP ACTION");
}
void actionCalc(data *ptr)
{
	int p = 20;
	if (ptr->pftr == 1)
	{
		p = 0;
	}
	if (ptr->pftr == 2)
	{
		p = 1;
		clearBets(ptr);
	}
	if (ptr->pftr == 3)
	{
		p = 2;
		clearBets(ptr);
	}
	if (p == 20)
	{
		printf("ERROR IN ACTION CALC");
	}
	do
	{
		switch (ptr->buttons.dealer) {
		case 0:
			//player 3 bets
			(*action_ptr[p])(ptr, 1);
			(*action_ptr[p])(ptr, 2);
			(*action_ptr[p])(ptr, 3);
			(*action_ptr[p])(ptr, 0);
			break;
		case 1:
			//player 0 bets
			(*action_ptr[p])(ptr, 2);
			(*action_ptr[p])(ptr, 3);
			(*action_ptr[p])(ptr, 0);
			(*action_ptr[p])(ptr, 1);
			break;
		case 2:
			//player 1 bets
			(*action_ptr[p])(ptr, 3);
			(*action_ptr[p])(ptr, 0);
			(*action_ptr[p])(ptr, 1);
			(*action_ptr[p])(ptr, 2);
			break;
		case 3:
			//player 2 leads
			(*action_ptr[p])(ptr, 0);
			(*action_ptr[p])(ptr, 1);
			(*action_ptr[p])(ptr, 2);
			(*action_ptr[p])(ptr, 3);
			break;
		default:
			printf("error in Flop");
			break;
		}
	} while (ptr->endBetting == 1);



}

void flopAction(data*ptr, int player)
{
	if (ptr->player[player].folded == 1)
	{
		if (ptr->buttons.raiseSpot == player)
		{
			ptr->endBetting = 0;
		}
		return;
	}
	if (ptr->buttons.raiseSpot == player)
	{
		printf("NOW TURNING");
		ptr->endBetting = 0;
		return;
	}

	if (ptr->Human == 1 && ptr->player == 0)
	{
		playerDecision(ptr);
	}

	int oddFlop = roughFlopOdd(ptr, player);

	if (oddFlop >= 30)
	{
		bet(ptr, player, oddFlop);
		return;
	}
	int betRatio = ptr->moneyPlayer.totalbet / ptr->moneyPlayer.pot;

	if (oddFlop < 30 && oddFlop > 15 && betRatio < 2)
	{
		checkCall(ptr, player);
		return;
	}

	if (oddFlop < 30 && ptr->raise != 0)
	{
		fold(ptr, player);
		return;
	}



}

void playerDecision(data * ptr)
{
	char action;
	if (ptr->moneyPlayer.totalbet > 0)
	{
		printf("the bet is $%d", ptr->moneyPlayer.totalbet);
	}
	do
	{
	printf("Please type if you would like to Checkcall fold or raise: c/f/r\n", &action);
	scanf("%c", &action);
	}while(action != 'c' && action != 'f' && action != 'r');
		if (action == 'c')
		{
			checkCall(ptr, 0);
		}
		if (action == 'f')
		{
			fold(ptr, 0);
		}
		if (action == 'r')
		{
			raise(ptr, 0);
		}

}
int pairCalcOdds(data * ptr, int player)
{
	int pair1 = 15;
	int pair2 = 30;
	int trips = 40;
	for (int j = 0; j < 3; j++)
	{
		if (ptr->player[player].card1 == ptr->board.flop[j].card1)
		{
			pair1 = 1;
			for (int l = 2; l > j; l--)
			{
				if (ptr->player[player].card1 == ptr->board.flop[j].card1)
				{
					trips = 1;
				}
			}
		}
		if (ptr->player[player].card2 == ptr->board.flop[j].card1)
		{
			pair2 = 2;
			for (int h = 2; h > j; h--)
			{
				if (ptr->player[player].card1 == ptr->board.flop[j].card1)
				{
					trips = 1;
				}
			}
		}
	}
	if (trips == 1 && pair1 == 1 && pair2 == 1)
	{
		return 80;
	}
	if (trips == 1)
	{
		return 50;
	}
	if (pair1 == 1 && pair2 == 1)
	{
		return 40;
	}
	if (pair1 == 1 || pair2 == 1)
	{
		return 20;
	}
	return 0;

}
int straightCalcOdds(data *ptr, int player)
{
	int cardArray[5] = { ptr->player[player].card1,ptr->player[player].card2, ptr->board.flop[0].card1,ptr->board.flop[1].card1,ptr->board.flop[2].card1 };
	int temp;
	for (int t = 0; t < 4; t++)
	{
		for (int j = 0; j < 4 - t; j++)
		{
			if (cardArray[j] > cardArray[j + 1])
			{
				temp = cardArray[j];
				cardArray[j] = cardArray[j + 1];
				cardArray[j + 1] = temp;
			}
		}

	}
	int temp2 = 0;
	if (cardArray[0] == 0 && cardArray[4] == 12)
	{
		temp = cardArray[0];
		cardArray[0] = -1;
		for (int m = 1; m < 5; m++)
		{
			temp2 = cardArray[m];
			cardArray[m] = temp;
			temp = temp2;
			//	printf("!!!!!!!!!CHECKING STRAIGHT card value %d array num %d\n", straightCard[m], m);
		}
	}
	int sNum = 0;
	for (int p = 0; p < 4; p++)
	{
		if ((cardArray[p] + 1) != cardArray[p + 1])
		{
			break;
		}
		//printf("====%d==== StraightCard %d P ---- STRAIGHTCARD[P + 1]=%d", straightCard[p],p, straightCard[p + 1]);
		sNum++;
	}
	if (sNum == 4)
	{
		return 55;
	}
	if (sNum == 3)
	{
		return 30;
	}
	if (sNum == 2)
	{
		return 10;
	}


}

int flushCalcOdds(data *ptr, int player)
{
	int temp = 0;
	int suitArray[5] = { ptr->player[player].suit1,ptr->player[player].suit2, ptr->board.flop[0].suit1  ,ptr->board.flop[1].suit1  ,ptr->board.flop[2].suit1 };

	for (int t = 0; t < 4; t++)
	{
		for (int j = 0; j < 4 - t; j++)
		{
			if (suitArray[j] > suitArray[j + 1])
			{
				temp = suitArray[j];
				suitArray[j] = suitArray[j + 1];
				suitArray[j + 1] = temp;
			}
		}

	}
	int flag = 0;
	int count[2] = { 0, 0 };
	for (int j = 0; j < 4; j++)
	{
		if (suitArray[j] == suitArray[j + 1])
		{
			count[0]++;
			if (flag == 0)
			{
				flag == suitArray[j];
			}
			if (suitArray[j] != flag)
			{
				count[1]++;
			}

		}
	}
	int p = 1;
	if (count[0] > count[1])
	{
		p = 0;
	}
	if (count[p] >= 4)
	{
		return 60;
	}
	if (count[p] >= 3)
	{
		return 30;
	}
	if (count[p] >= 2)
	{
		return 5;
	}
	if (count[p] < 2)
	{
		return 0;
	}

}
int quadCalcOdds(data * ptr, int player)
{
	int topV = 20;
	int cardArray[5] = { ptr->player[player].card1,ptr->player[player].card2, ptr->board.flop[0].card1,ptr->board.flop[1].card1,ptr->board.flop[2].card1 };
	int fourKind = 0;
	for (int j = 0; j < 4; j++)
	{
		for (int p = j + 1; p < 5; p++)
		{
			if (cardArray[j] == cardArray[p])
			{
				for (int m = p + 1; m < 5; m++)
				{
					if (cardArray[j] == cardArray[m])
					{
						for (int t = m + 1; t < 5; t++)
						{
							//	printf("M = %d  T %d ", m, t);
							if (cardArray[j] == cardArray[t])
							{
								fourKind = 1;
							}
						}

					}
					if (fourKind == 1)
					{
						break;
					}
				}
			}
			if (fourKind == 1)
			{
				break;
			}
		}
		if (fourKind == 1)
		{
			break;
		}

		if (fourKind == 1)
		{
			return 90;
		}
		else {
			return 0;
		}
	}
}
void turnAction(data *ptr, int player)
{
	
	
	if (ptr->player[player].folded == 1)
	{
		if (ptr->buttons.raiseSpot == player)
		{
			ptr->endBetting = 0;
		}
		return;
	}
	
	

	if (ptr->buttons.raiseSpot == player)
	{
		printf("NOW RIVER");
		ptr->endBetting = 0;
		return;
	}

	if (ptr->Human == 1 && player == 0)
	{
		playerDecision(ptr);
	}

	int oddTurn = roughTurnOdd(ptr, player);

	if (oddTurn >= 30)
	{
		bet(ptr, player, oddTurn);
		return;
	}
	int betRatio = ptr->moneyPlayer.totalbet / ptr->moneyPlayer.pot;

	if (oddTurn < 30 && oddTurn > 15 && betRatio < 2)
	{
		checkCall(ptr, player);
		return;
	}

	if (oddTurn < 30 && ptr->raise != 0)
	{
		fold(ptr, player);
		return;
	}
}
void riverAction(data *ptr, int player)
{
	if (ptr->player[player].folded == 1)
	{
		if (ptr->buttons.raiseSpot == player)
		{
			ptr->endBetting = 0;
		}
		return;
	}

	if (ptr->buttons.raiseSpot == player)
	{
		printf("\nNOW HAND SHOW, WHO WINS!!!!\n");
		ptr->endBetting = 0;
		return;
	}

	if (ptr->Human == 1 && player == 0)
	{
		playerDecision(ptr);
	}

	int oddRiver = roughRiverOdd(ptr, player);

	if (oddRiver >= 40)
	{
		bet(ptr, player, oddRiver);
		return;
	}
	int betRatio = ptr->moneyPlayer.totalbet / ptr->moneyPlayer.pot;

	if (oddRiver < 40 && oddRiver > 15 && betRatio < 2)
	{
		checkCall(ptr, player);
		return;
	}

	if (oddRiver < 30 && ptr->raise != 0)
	{
		fold(ptr, player);
		return;
	}
}
//RANDOMGENERATES THE BOARD CARDS
void randGenBoard(data *ptr)
{
	int check = 0;
	int run = 1;
	if (ptr->pftr == 1)
	{
		run = 3;
	}
	if (ptr->pftr == 1)
	{
		for (int k = 0; k < run; k++)
		{
			ptr->board.flop[k].card1 = rand() % 13;
			ptr->board.flop[k].suit1 = rand() % 4;
			for (int p = 0; p < MAXPLAYER; p++)
			{

				if (ptr->board.flop[k].card1 == ptr->player[p].card1 && ptr->board.flop[k].suit1 == ptr->player[p].suit1)
				{
					check = 1;
					break;
				}
				if (ptr->board.flop[k].card1 == ptr->player[p].card2 && ptr->board.flop[k].suit1 == ptr->player[p].suit2)
				{
					check = 1;
					break;
				}
				if (ptr->board.flop[k - 1].card1 == ptr->board.flop[k].card1&& ptr->board.flop[k - 1].suit1 == ptr->board.flop[k - 1].suit1)
				{
					check = 1;
					break;
				}
				if (ptr->board.flop[k - 1].card1 == ptr->board.flop[k].card1 && ptr->board.flop[k].suit1 == ptr->board.flop[k - 1].suit1)
				{
					check = 1;
					break;
				}

			}
			if (check == 1)
			{
				check = 0;
				k--;
			}
		}
		printf("\n THE FLOP IS %d suit %d -- %d suit %d -- %d suit %d\t", ptr->board.flop[0].card1, ptr->board.flop[0].suit1, ptr->board.flop[1].card1, ptr->board.flop[1].suit1, ptr->board.flop[2].card1, ptr->board.flop[2].suit1);
	}
	if (ptr->pftr == 2)
	{
		run = 1;
		for (int k = 0; k < run; k++)
		{
			ptr->board.turn[k].card1 = rand() % 13;
			ptr->board.turn[k].suit1 = rand() % 4;

			for (int p = 0; p < MAXPLAYER; p++)
			{

				if (ptr->board.turn[k].card1 == ptr->player[p].card1 && ptr->board.turn[k].suit1 == ptr->player[p].suit1)
				{
					check = 1;
					break;
				}
				if (ptr->board.turn[k].card1 == ptr->player[p].card2 && ptr->board.turn[k].suit1 == ptr->player[p].suit2)
				{
					check = 1;
					break;
				}
				if (ptr->board.turn[k].card1 == ptr->board.flop[0].card1 && ptr->board.turn[k].suit1 == ptr->board.flop[0].suit1)
				{
					check = 1;
					break;
				}
				if (ptr->board.turn[k].card1 == ptr->board.flop[1].card1 && ptr->board.turn[k].suit1 == ptr->board.flop[1].suit1)
				{
					check = 1;
					break;
				}
				if (ptr->board.turn[k].card1 == ptr->board.flop[2].card1 && ptr->board.turn[k].suit1 == ptr->board.flop[2].suit1)
				{
					check = 1;
					break;
				}

			}
			if (check == 1)
			{
				check = 0;
				k--;
			}
		}
		printf("\tTHE TURN IS %d suit %d\n", ptr->board.turn[0].card1, ptr->board.turn[0].suit1);
	}
	if (ptr->pftr == 3)
	{
		run = 1;
		for (int k = 0; k < run; k++)
		{
			ptr->board.river[k].card1 = rand() % 13;
			ptr->board.river[k].suit1 = rand() % 4;
			for (int p = 0; p < MAXPLAYER; p++)
			{
				if (ptr->board.river[k].card1 == ptr->player[p].card1 && ptr->board.river[k].suit1 == ptr->player[p].suit1)
				{
					check = 1;
					break;
				}
				if (ptr->board.river[k].card1 == ptr->player[p].card2 && ptr->board.river[k].suit1 == ptr->player[p].suit2)
				{
					check = 1;
					break;
				}
				if (ptr->board.river[k].card1 == ptr->board.flop[0].card1 && ptr->board.river[k].suit1 == ptr->board.flop[0].suit1)
				{
					check = 1;
					break;
				}
				if (ptr->board.river[k].card1 == ptr->board.flop[1].card1 && ptr->board.river[k].suit1 == ptr->board.flop[1].suit1)
				{
					check = 1;
					break;
				}
				if (ptr->board.river[k].card1 == ptr->board.flop[2].card1 && ptr->board.river[k].suit1 == ptr->board.flop[2].suit1)
				{
					check = 1;
					break;
				}
				if (ptr->board.river[k].card1 == ptr->board.turn[0].card1 && ptr->board.river[k].suit1 == ptr->board.turn[0].suit1)
				{
					check = 1;
					break;
				}
			}
			if (check == 1)
			{
				check = 0;
				k--;
			}
		}
		printf("\tTHE RIVER IS %d suit %d\t", ptr->board.river[0].card1, ptr->board.river[0].suit1);
	}


}


//FLOPS THE BOARD AND STORES THE DATA
void flopping(data * ptr)
{
	ptr->pftr = 1;
	randGenBoard(ptr);
	clearBets(ptr);
	ptr->buttons.raiseSpot = ptr->buttons.dealer;
	ptr->moneyPlayer.totalbet = 0;
	if (ptr->foldCount < 3)
	{
		actionCalc(ptr);
	}
}

//TURNS THE CARD AND STORES THE DATA
void turn(data *ptr)
{
	ptr->pftr = 2;
	randGenBoard(ptr);
	clearBets(ptr);
	ptr->buttons.raiseSpot = ptr->buttons.dealer;
	ptr->moneyPlayer.pftrBets[ptr->pftr - 1] = ptr->moneyPlayer.totalbet;
	ptr->moneyPlayer.totalbet = 0;
	if (ptr->foldCount < 3)
	{
		actionCalc(ptr);
	}
}

//TURNS THE RIVER AND STORES THE DATA
void river(data *ptr)
{
	ptr->pftr = 3;
	randGenBoard(ptr);
	clearBets(ptr);
	ptr->buttons.raiseSpot = ptr->buttons.dealer;
	ptr->moneyPlayer.pftrBets[ptr->pftr - 1] = ptr->moneyPlayer.totalbet;
	ptr->moneyPlayer.totalbet = 0;
	if (ptr->foldCount < 3)
	{
		actionCalc(ptr);
	}
}

void humanAction(data * ptr)
{
	if (ptr->pftr == 0)
	{
		printf("you where dealt %d suit %d and %d suit %d", ptr->player[0].card1, ptr->player[0].suit1, ptr->player[0].card2, ptr->player[0].suit2);
	}
}
//FOLDS THE PLAYER
void fold(data*ptr, int player)
{
	if (ptr->moneyPlayer.totalbet == ptr->moneyPlayer.bets[player])
	{
		checkCall(ptr, player);
		return;
	}
	if (ptr->pftr == 0)
	{
		ptr->pData[player].pFold++;
		ptr->pData[player].pPlay--;
	}
	ptr->player[player].folded = 1;
	ptr->foldCount++;
	printf("\tPLAYER %d FOLDS\n", player);
}

//CHECKS OR CALLS
void checkCall(data*ptr, int player)
{
	if (ptr->moneyPlayer.totalbet == ptr->moneyPlayer.bets[player])
	{
		printf("PLAYER %d CHECKS", player);
	}
	//printf("\tTOTALBET == %d\t", ptr->moneyPlayer.totalbet);
	if (ptr->moneyPlayer.totalbet > ptr->moneyPlayer.bets[player])
	{
		ptr->moneyPlayer.playerMoney[player] -= ptr->moneyPlayer.totalbet - ptr->moneyPlayer.bets[player];
		ptr->moneyPlayer.pot += ptr->moneyPlayer.totalbet - ptr->moneyPlayer.bets[player];
		ptr->moneyPlayer.bets[player] = ptr->moneyPlayer.totalbet;
		printf("\n PLAYER %d CALLS BET = %d\n\t%d NEW POT", player, ptr->moneyPlayer.bets[player], ptr->moneyPlayer.pot);
		ptr->player[player].check = ptr->raise;
		if (ptr->pftr == 0)
		{
			ptr->pData[player].pPlay++;

		}
	}
}

//RAISES OR BETS
void bet(data*ptr, int player, int percent)
{
	if (ptr->raise != 0 && percent > 50)
	{
		if (ptr->raise < 3)
		{
			raise(ptr, player);
		}
	}

	if (ptr->raise == 0 || ptr->raise > 3)
	{
		ptr->moneyPlayer.bets[player] += (2 * ptr->moneyPlayer.pot);
		ptr->moneyPlayer.totalbet = ptr->moneyPlayer.bets[player];
		ptr->moneyPlayer.playerMoney[player] -= ptr->moneyPlayer.totalbet;
		ptr->moneyPlayer.pot += ptr->moneyPlayer.totalbet;
		ptr->raise += 1;
		ptr->buttons.raiseSpot = player;
		printf("player %d bets %d", player, ptr->moneyPlayer.totalbet);
	}
}

void raise(data*ptr, int player)
{
	int humanBet;
	int dif;
	int k = 0;
	if (ptr->Human == 1 && player == 0)
	{
		do
		{	
			if (k != 0)
			{
				printf("You need to bet 2x the the original bet");
			}
			printf("What would you like to bet?");
			scanf("%d", &humanBet);
		
		} while (humanBet > 2 * ptr->moneyPlayer.totalbet);
		ptr->moneyPlayer.playerMoney[0] -=	humanBet - ptr->moneyPlayer.totalbet;
		ptr->raise += 1;
		ptr->buttons.raiseSpot = 0;
		ptr->moneyPlayer.totalbet = humanBet - ptr->moneyPlayer.totalbet;
		ptr->moneyPlayer.pot += ptr->moneyPlayer.totalbet;
	}
	if (ptr->Human == 0 || player != 0)
	{
		ptr->moneyPlayer.totalbet = ptr->moneyPlayer.pot;
		ptr->moneyPlayer.playerMoney[player] -= ptr->moneyPlayer.totalbet;
		ptr->raise += 1;
		ptr->moneyPlayer.pot += ptr->moneyPlayer.totalbet;
		ptr->buttons.raiseSpot = player;
		ptr->moneyPlayer.bets[player] = ptr->moneyPlayer.totalbet;
	}
}

//DETERMINES PLAYER LOCATION
void playerLocation(data * ptr)
{
	for (int k = 0; k < 4; k++)
	{
		ptr->loc[k] = ptr->moneyPlayer.raiseNum[k];
	}

}

//CALCULATES THE ODDS
int roughPreFLOPoddCalc(data * ptr, int player)
{


	int  percent = 0;
	if (ptr->loc[player] == 0)
	{
		percent = 15;
		if (ptr->player[player].card1 == ptr->player[player].card2)
		{
			if (ptr->player[player].card1 > 6)
			{
				percent = percent + 10;
				if (ptr->player[player].card1 > 8)
				{

					percent = percent + 10;
				}
				if (ptr->player[player].card1 > 10)
				{
					percent = percent + 20;
				}
			}

		}
		if ((ptr->player[player].card1 - ptr->player[player].card2 <= 3))
		{
			percent += 5;
		}
		if (ptr->player[player].card1 > 10)
		{
			percent += 3;
			if (ptr->player[player].card1 > 11)
			{
				percent += 3;
			}
		}
		if (ptr->player[player].card2 > 10)
		{
			percent += 3;
			if (ptr->player[player].card2 > 11)
			{
				percent += 3;
			}
		}
		if (ptr->player[player].suit1 == ptr->player[player].suit1)
		{
			percent += 5;
		}

	}
	if (ptr->loc[player] == 1)
	{
		percent = 0;
		if (ptr->player[player].card1 == ptr->player[player].card2)
		{
			if (ptr->player[player].card1 > 6)
			{
				percent = percent + 10;
				if (ptr->player[player].card1 > 8)
				{

					percent = percent + 10;
				}
				if (ptr->player[player].card1 > 10)
				{
					percent = percent + 20;
				}
			}

		}
		if ((ptr->player[player].card1 - ptr->player[player].card2 <= 3))
		{
			percent += 5;
		}
		if (ptr->player[player].card1 > 10)
		{
			percent += 3;
			if (ptr->player[player].card1 > 11)
			{
				percent += 3;
			}
		}
		if (ptr->player[player].card2 > 10)
		{
			percent += 3;
			if (ptr->player[player].card2 > 11)
			{
				percent += 3;
			}
		}
		if (ptr->player[player].suit1 == ptr->player[player].suit1)
		{
			percent += 5;
		}

	}
	if (ptr->loc[player] == 2)
	{
		percent = 5;
		if (ptr->player[player].card1 == ptr->player[player].card2)
		{
			if (ptr->player[player].card1 > 6)
			{
				percent = percent + 10;
				if (ptr->player[player].card1 > 8)
				{

					percent = percent + 10;
				}
				if (ptr->player[player].card1 > 10)
				{
					percent = percent + 20;
				}
			}

		}
		if ((ptr->player[player].card1 - ptr->player[player].card2 <= 3))
		{
			percent += 5;
		}
		if (ptr->player[player].card1 > 10)
		{
			percent += 3;
			if (ptr->player[player].card1 > 11)
			{
				percent += 3;
			}
		}
		if (ptr->player[player].card2 > 10)
		{
			percent += 3;
			if (ptr->player[player].card2 > 11)
			{
				percent += 3;
			}
		}
		if (ptr->player[player].suit1 == ptr->player[player].suit1)
		{
			percent += 5;
		}

	}
	if (ptr->loc[player] == 3)
	{
		percent = 5;
		if (ptr->player[player].card1 == ptr->player[player].card2)
		{
			if (ptr->player[player].card1 > 6)
			{
				percent = percent + 10;
				if (ptr->player[player].card1 > 8)
				{

					percent = percent + 10;
				}
				if (ptr->player[player].card1 > 10)
				{
					percent = percent + 20;
				}
			}

		}
		if ((ptr->player[player].card1 - ptr->player[player].card2 <= 3))
		{
			percent += 5;
		}
		if (ptr->player[player].card1 > 10)
		{
			percent += 3;
			if (ptr->player[player].card1 > 11)
			{
				percent += 3;
			}
		}
		if (ptr->player[player].card2 > 10)
		{
			percent += 3;
			if (ptr->player[player].card2 > 11)
			{
				percent += 3;
			}
		}
		if (ptr->player[player].suit1 == ptr->player[player].suit1)
		{
			percent += 5;
		}

	}
	return percent;
}
int roughFlopOdd(data * ptr, int player)
{
	int quadCalc = 0;
	int valueFlush = 0;
	int valuePair = 0;
	int valStraight = 0;
	int temp = 0;

	quadCalc = quadCalcOdds(ptr, player);
	if (quadCalc < 89)
	{
		valuePair = pairCalcOdds(ptr, player);
	}

	if (valuePair < 70 || quadCalc < 89)
	{
		valueFlush = flushCalcOdds(ptr, player);

	}
	if (valuePair < 89)
	{
		int valStraight = straightCalcOdds(ptr, player);
	}

	int percentArray[4] = { quadCalc, valueFlush,valuePair, valStraight };


	for (int t = 0; t < 4; t++)
	{
		for (int j = 0; j < 3 - t; j++)
		{
			if (percentArray[j] > percentArray[j + 1])
			{
				temp = percentArray[j];
				percentArray[j] = percentArray[j + 1];
				percentArray[j + 1] = temp;
			}
		}

	}
	temp = 0;
	for (int k = 0; k < 3; k++)
	{
		temp += k / 10;

	}
	int odds = temp + percentArray[3];

	if (ptr->loc[player] == 3)
	{
		odds += 5;
	}
	if (ptr->loc[player] == 0)
	{
		odds += 15;
	}
	printf("\nTHE ODDS ARE %d FOR PLAYER %d\n", odds, player);
	return odds;

}
int roughTurnOdd(data *ptr, int player)
{
	bestHandFinderTurn(ptr, player);
	return ptr->odds.turnOdds[player];
}
int roughRiverOdd(data *ptr, int player)
{
	ptr->odds.riverOdds[player] = malloc(sizeof(int) * 5);
	ptr->odds.riverOdds[player] = bestHandFinder(ptr, player);

	ptr->odds.riverOdds[player][0] /= 10;
	int k = ptr->odds.riverOdds[player][0];
	printf("K == %d", k);
	return k;
}

void turnOddCalc(data *ptr, int player)
{
	int flushOdds = 0;
	int quadOdds = 0;
	int straightOdds = 0;
	int pairOdds = 0;
	pairOdds = pairTurnOdds(ptr, player);
	straightOdds = straightTurnOdds(ptr, player);
	quadOdds = quadTurnOdds(ptr, player);
	flushOdds = flushTurnOdds(ptr, player);

	int temp = 0;
	int oddArray[4] = { pairOdds,straightOdds,quadOdds,flushOdds };
	for (int k = 0; k < 3; k++)
	{
		for (int j = 0; j < 4 - k - 1; j++)
		{
			if (oddArray[j] > oddArray[j + 1])
			{
				temp = oddArray[j];
				oddArray[j] = oddArray[j + 1];
				oddArray[j + 1] = temp;
			}

		}
	}

	if (ptr->odds.turnOdds[player] < oddArray[3])
	{
		ptr->odds.turnOdds[player] = oddArray[3];
	}

}
int pairTurnOdds(data * ptr, int player)
{
	int pair1 = 15;
	int pair2 = 30;
	int trips = 40;
	for (int j = 0; j < 4; j++)
	{
		if (ptr->player[player].card1 == ptr->board.flop[j].card1)
		{
			pair1 = 1;
			for (int l = 2; l > j; l--)
			{
				if (ptr->player[player].card1 == ptr->board.flop[j].card1)
				{
					trips = 1;
				}
			}
		}
		if (ptr->player[player].card2 == ptr->board.flop[j].card1)
		{
			pair2 = 2;
			for (int h = 2; h > j; h--)
			{
				if (ptr->player[player].card1 == ptr->board.flop[j].card1)
				{
					trips = 1;
				}
			}
		}
	}
	if (trips == 1 && pair1 == 1 && pair2 == 1)
	{
		return 80;
	}
	if (trips == 1)
	{
		return 50;
	}
	if (pair1 == 1 && pair2 == 1)
	{
		return 40;
	}
	if (pair1 == 1 || pair2 == 1)
	{
		return 20;
	}
	return 0;

}
int straightTurnOdds(data *ptr, int player)
{
	int cardArray[5] = { ptr->player[player].card1,ptr->player[player].card2, ptr->board.flop[0].card1,ptr->board.flop[1].card1,ptr->board.flop[2].card1 };
	int temp;
	for (int t = 0; t < 4; t++)
	{
		for (int j = 0; j < 4 - t; j++)
		{
			if (cardArray[j] > cardArray[j + 1])
			{
				temp = cardArray[j];
				cardArray[j] = cardArray[j + 1];
				cardArray[j + 1] = temp;
			}
		}

	}
	int temp2 = 0;
	if (cardArray[0] == 0 && cardArray[4] == 12)
	{
		temp = cardArray[0];
		cardArray[0] = -1;
		for (int m = 1; m < 5; m++)
		{
			temp2 = cardArray[m];
			cardArray[m] = temp;
			temp = temp2;
			//	printf("!!!!!!!!!CHECKING STRAIGHT card value %d array num %d\n", straightCard[m], m);
		}
	}
	int sNum = 0;
	for (int p = 0; p < 4; p++)
	{
		if ((cardArray[p] + 1) != cardArray[p + 1])
		{
			break;
		}
		//printf("====%d==== StraightCard %d P ---- STRAIGHTCARD[P + 1]=%d", straightCard[p],p, straightCard[p + 1]);
		sNum++;
	}
	if (sNum == 4)
	{
		return 55;
	}
	if (sNum == 3)
	{
		return 30;
	}
	if (sNum == 2)
	{
		return 10;
	}


}

int flushTurnOdds(data *ptr, int player)
{
	int temp = 0;
	int suitArray[5] = { ptr->player[player].suit1,ptr->player[player].suit2, ptr->board.flop[0].suit1  ,ptr->board.flop[1].suit1  ,ptr->board.flop[2].suit1 };

	for (int t = 0; t < 4; t++)
	{
		for (int j = 0; j < 4 - t; j++)
		{
			if (suitArray[j] > suitArray[j + 1])
			{
				temp = suitArray[j];
				suitArray[j] = suitArray[j + 1];
				suitArray[j + 1] = temp;
			}
		}

	}
	int flag = 0;
	int count[2] = { 0, 0 };
	for (int j = 0; j < 4; j++)
	{
		if (suitArray[j] == suitArray[j + 1])
		{
			count[0]++;
			if (flag == 0)
			{
				flag == suitArray[j];
			}
			if (suitArray[j] != flag)
			{
				count[1]++;
			}

		}
	}
	int p = 1;
	if (count[0] > count[1])
	{
		p = 0;
	}
	if (count[p] >= 4)
	{
		return 60;
	}
	if (count[p] >= 3)
	{
		return 30;
	}
	if (count[p] >= 2)
	{
		return 5;
	}
	if (count[p] < 2)
	{
		return 0;
	}

}
int quadTurnOdds(data * ptr, int player)
{
	int topV = 20;
	int cardArray[5] = { ptr->player[player].card1,ptr->player[player].card2, ptr->board.flop[0].card1,ptr->board.flop[1].card1,ptr->board.flop[2].card1 };
	int fourKind = 0;
	for (int j = 0; j < 4; j++)
	{
		for (int p = j + 1; p < 5; p++)
		{
			if (cardArray[j] == cardArray[p])
			{
				for (int m = p + 1; m < 5; m++)
				{
					if (cardArray[j] == cardArray[m])
					{
						for (int t = m + 1; t < 5; t++)
						{
							//	printf("M = %d  T %d ", m, t);
							if (cardArray[j] == cardArray[t])
							{
								fourKind = 1;
							}
						}

					}
					if (fourKind == 1)
					{
						break;
					}
				}
			}
			if (fourKind == 1)
			{
				break;
			}
		}
		if (fourKind == 1)
		{
			break;
		}

		if (fourKind == 1)
		{
			return 90;
		}
		else {
			return 0;
		}
	}
}

void bestHandFinderTurn(data *ptr, int player)
{
	for (int j = 0; j < 2; j++)
	{
		for (int k = j + 1; k < 4; k++)
		{
			ptr->finHand[player].card1.card1 = 10;
			ptr->finHand[player].card1.suit1 = 10;
			ptr->finHand[player].card2.card1 = 11;
			ptr->finHand[player].card2.suit1 = 11;
			ptr->finHand[player].card3.card1 = j;
			ptr->finHand[player].card3.suit1 = j;
			ptr->finHand[player].card4.card1 = j + 1;
			ptr->finHand[player].card4.suit1 = j + 1;
			ptr->finHand[player].card5.card1 = k;
			ptr->finHand[player].card5.suit1 = k;
			handValue(ptr, player);
		}
	}

	ptr->finHand[player].card1.card1 = 10;
	ptr->finHand[player].card1.suit1 = 10;
	ptr->finHand[player].card2.card1 = 0;
	ptr->finHand[player].card2.suit1 = 0;
	ptr->finHand[player].card3.card1 = 1;
	ptr->finHand[player].card3.suit1 = 1;
	ptr->finHand[player].card4.card1 = 2;
	ptr->finHand[player].card4.suit1 = 2;
	ptr->finHand[player].card5.card1 = 3;
	ptr->finHand[player].card5.suit1 = 3;
	handValue(ptr, player);



	ptr->finHand[player].card1.card1 = 0;
	ptr->finHand[player].card1.suit1 = 0;
	ptr->finHand[player].card2.card1 = 11;
	ptr->finHand[player].card2.suit1 = 11;
	ptr->finHand[player].card3.card1 = 1;
	ptr->finHand[player].card3.suit1 = 1;
	ptr->finHand[player].card4.card1 = 2;
	ptr->finHand[player].card4.suit1 = 2;
	ptr->finHand[player].card5.card1 = 3;
	ptr->finHand[player].card5.suit1 = 3;
	handValue(ptr, player);


	return ptr->odds.turnOdds[player];
}
int *bestHandFinder(data*ptr, int p)
{
	ptr->finHand[p].card1.card1 = 10;
	ptr->finHand[p].card1.suit1 = 10;
	ptr->finHand[p].card2.card1 = 11;
	ptr->finHand[p].card2.suit1 = 11;
	int count = 0;

	for (int k = 0; k < 3; k++)
	{
		for (int j = k + 1; j < 4; j++)
		{
			for (int m = j + 1; m < 5; m++)
			{
				ptr->finHand[p].card1.card1 = 10;
				ptr->finHand[p].card1.suit1 = 10;
				ptr->finHand[p].card2.card1 = 11;
				ptr->finHand[p].card2.suit1 = 11;
				ptr->finHand[p].card3.card1 = k;
				ptr->finHand[p].card3.suit1 = k;
				ptr->finHand[p].card4.card1 = j;
				ptr->finHand[p].card4.suit1 = j;
				ptr->finHand[p].card5.card1 = m;
				ptr->finHand[p].card5.suit1 = m;
				handValue(ptr, p);
				//PASS TO CHECK VALUE FUNCTION
				//printf("\nPLAYER -- %dCARD 1--%d \t CARD 2--%d\t CARD 3--%d\t CARD4--%d\t CARD5--%d\n", p, ptr->finHand[p].card1.card1, ptr->finHand[p].card2.card1, ptr->finHand[p].card3.card1, ptr->finHand[p].card4.card1, ptr->finHand[p].card5.card1);
			}
		}
		count++;
	}
	ptr->finHand[p].card1.card1 = 10;
	ptr->finHand[p].card1.suit1 = 10;
	for (int k = 0; k < 2; k++)
	{
		for (int j = k + 1; j < 3; j++)
		{
			for (int m = j + 1; m < 4; m++)
			{
				for (int n = m + 1; n < 5; n++)
				{
					ptr->finHand[p].card1.card1 = 10;
					ptr->finHand[p].card1.suit1 = 10;
					ptr->finHand[p].card2.card1 = k;
					ptr->finHand[p].card2.suit1 = k;
					ptr->finHand[p].card3.card1 = j;
					ptr->finHand[p].card3.suit1 = j;
					ptr->finHand[p].card4.card1 = m;
					ptr->finHand[p].card4.suit1 = m;
					ptr->finHand[p].card5.card1 = n;
					ptr->finHand[p].card5.suit1 = n;
					handValue(ptr, p);
					//	printf("\nPLAYER -- %dCARD 1--%d \t CARD 2--%d\t CARD 3--%d\t CARD4--%d\t CARD5--%d\n", p, ptr->finHand[p].card1.card1, ptr->finHand[p].card2.card1, ptr->finHand[p].card3.card1, ptr->finHand[p].card4.card1, ptr->finHand[p].card5.card1);
				}
			}
		}


	}
	ptr->finHand[p].card2.card1 = 11;
	ptr->finHand[p].card2.suit1 = 11;
	for (int k = 0; k < 2; k++)
	{
		for (int j = k + 1; j < 3; j++)
		{
			for (int m = j + 1; m < 4; m++)
			{
				for (int n = m + 1; n < 5; n++)
				{
					ptr->finHand[p].card2.card1 = 11;
					ptr->finHand[p].card2.suit1 = 11;
					ptr->finHand[p].card1.card1 = k;
					ptr->finHand[p].card1.suit1 = k;
					ptr->finHand[p].card3.card1 = j;
					ptr->finHand[p].card3.suit1 = j;
					ptr->finHand[p].card4.card1 = m;
					ptr->finHand[p].card4.suit1 = m;
					ptr->finHand[p].card5.card1 = n;
					ptr->finHand[p].card5.suit1 = n;
					handValue(ptr, p);
					//	printf("\nPLAYER -- %dCARD 1--%d \t CARD 2--%d\t CARD 3--%d\t CARD4--%d\t CARD5--%d\n", p, ptr->finHand[p].card1.card1, ptr->finHand[p].card2.card1, ptr->finHand[p].card3.card1, ptr->finHand[p].card4.card1, ptr->finHand[p].card5.card1);
				}
			}
		}


	}
	ptr->finHand[p].card1.card1 = 0;
	ptr->finHand[p].card1.card1 = 0;
	ptr->finHand[p].card2.card1 = 1;
	ptr->finHand[p].card2.suit1 = 1;
	ptr->finHand[p].card3.card1 = 2;
	ptr->finHand[p].card3.suit1 = 2;
	ptr->finHand[p].card4.card1 = 3;
	ptr->finHand[p].card4.suit1 = 3;
	ptr->finHand[p].card5.card1 = 4;
	ptr->finHand[p].card5.suit1 = 4;
	handValue(ptr, p);

	return ptr->finHand[p].Value;
}
//CALCULATES WHO IS STILL IN THE HAND AND WON
//GOES THROUGH ALL POSSIBLE HAND COMBINATIONS
void findWinner(data *ptr)
{
	for (int k = 0; k < MAXPLAYER; k++)
	{
		for (int m = 0; m < 5; m++)
		{
			ptr->finHand[k].Value[m] = 0;
		}
	}
	for (int p = 0; p < MAXPLAYER; p++)
	{
		if (ptr->player[p].folded == 0)
		{
			ptr->finHand[p].card1.card1 = 10;
			ptr->finHand[p].card1.suit1 = 10;
			ptr->finHand[p].card2.card1 = 11;
			ptr->finHand[p].card2.suit1 = 11;
			int count = 0;

			for (int k = 0; k < 3; k++)
			{
				for (int j = k + 1; j < 4; j++)
				{
					for (int m = j + 1; m < 5; m++)
					{
						ptr->finHand[p].card1.card1 = 10;
						ptr->finHand[p].card1.suit1 = 10;
						ptr->finHand[p].card2.card1 = 11;
						ptr->finHand[p].card2.suit1 = 11;
						ptr->finHand[p].card3.card1 = k;
						ptr->finHand[p].card3.suit1 = k;
						ptr->finHand[p].card4.card1 = j;
						ptr->finHand[p].card4.suit1 = j;
						ptr->finHand[p].card5.card1 = m;
						ptr->finHand[p].card5.suit1 = m;
						handValue(ptr, p);
						//PASS TO CHECK VALUE FUNCTION
						//printf("\nPLAYER -- %dCARD 1--%d \t CARD 2--%d\t CARD 3--%d\t CARD4--%d\t CARD5--%d\n", p, ptr->finHand[p].card1.card1, ptr->finHand[p].card2.card1, ptr->finHand[p].card3.card1, ptr->finHand[p].card4.card1, ptr->finHand[p].card5.card1);
					}
				}
				count++;
			}
			ptr->finHand[p].card1.card1 = 10;
			ptr->finHand[p].card1.suit1 = 10;
			for (int k = 0; k < 2; k++)
			{
				for (int j = k + 1; j < 3; j++)
				{
					for (int m = j + 1; m < 4; m++)
					{
						for (int n = m + 1; n < 5; n++)
						{
							ptr->finHand[p].card1.card1 = 10;
							ptr->finHand[p].card1.suit1 = 10;
							ptr->finHand[p].card2.card1 = k;
							ptr->finHand[p].card2.suit1 = k;
							ptr->finHand[p].card3.card1 = j;
							ptr->finHand[p].card3.suit1 = j;
							ptr->finHand[p].card4.card1 = m;
							ptr->finHand[p].card4.suit1 = m;
							ptr->finHand[p].card5.card1 = n;
							ptr->finHand[p].card5.suit1 = n;
							handValue(ptr, p);
							//	printf("\nPLAYER -- %dCARD 1--%d \t CARD 2--%d\t CARD 3--%d\t CARD4--%d\t CARD5--%d\n", p, ptr->finHand[p].card1.card1, ptr->finHand[p].card2.card1, ptr->finHand[p].card3.card1, ptr->finHand[p].card4.card1, ptr->finHand[p].card5.card1);
						}
					}
				}


			}
			ptr->finHand[p].card2.card1 = 11;
			ptr->finHand[p].card2.suit1 = 11;
			for (int k = 0; k < 2; k++)
			{
				for (int j = k + 1; j < 3; j++)
				{
					for (int m = j + 1; m < 4; m++)
					{
						for (int n = m + 1; n < 5; n++)
						{
							ptr->finHand[p].card2.card1 = 11;
							ptr->finHand[p].card2.suit1 = 11;
							ptr->finHand[p].card1.card1 = k;
							ptr->finHand[p].card1.suit1 = k;
							ptr->finHand[p].card3.card1 = j;
							ptr->finHand[p].card3.suit1 = j;
							ptr->finHand[p].card4.card1 = m;
							ptr->finHand[p].card4.suit1 = m;
							ptr->finHand[p].card5.card1 = n;
							ptr->finHand[p].card5.suit1 = n;
							handValue(ptr, p);
							//	printf("\nPLAYER -- %dCARD 1--%d \t CARD 2--%d\t CARD 3--%d\t CARD4--%d\t CARD5--%d\n", p, ptr->finHand[p].card1.card1, ptr->finHand[p].card2.card1, ptr->finHand[p].card3.card1, ptr->finHand[p].card4.card1, ptr->finHand[p].card5.card1);
						}
					}
				}


			}
			ptr->finHand[p].card1.card1 = 0;
			ptr->finHand[p].card1.card1 = 0;
			ptr->finHand[p].card2.card1 = 1;
			ptr->finHand[p].card2.suit1 = 1;
			ptr->finHand[p].card3.card1 = 2;
			ptr->finHand[p].card3.suit1 = 2;
			ptr->finHand[p].card4.card1 = 3;
			ptr->finHand[p].card4.suit1 = 3;
			ptr->finHand[p].card5.card1 = 4;
			ptr->finHand[p].card5.suit1 = 4;
			//printf("\nPLAYER -- %dCARD 1--%d \t CARD 2--%d\t CARD 3--%d\t CARD4--%d\t CARD5--%d\n", p, ptr->finHand[p].card1.card1, ptr->finHand[p].card2.card1, ptr->finHand[p].card3.card1, ptr->finHand[p].card4.card1, ptr->finHand[p].card5.card1);
			handValue(ptr, p);
		}

	}
	valueCompare(ptr);//FINDS THE WINNER AFTER VALUES CALCULATED
}

void handValue(data *ptr, int player)
{
	int p = player;
	int check1 = 0;
	int check2 = 0;
	int check3 = 0;
	int check4 = 0;
	int check5 = 0;
	if (ptr->finHand[player].card1.card1 == 1 && ptr->finHand[player].card2.card1 == 2 && ptr->finHand[player].card3.card1 == 3 && ptr->finHand[player].card4.card1 == 4 && ptr->finHand[player].card5.card1 == 5)
	{
		//printf("FLAGGED ALL EQUAL");
	}
	//printf("\n%d  = %d = %d = %d = %d = ", ptr->finHand[player].card1.card1, ptr->finHand[player].card2.card1, ptr->finHand[player].card3.card1, ptr->finHand[player].card4.card1, ptr->finHand[player].card5.card1);
	//printf("\n%d  = %d = %d = %d = %d = ", ptr->finHand[player].card1.suit1, ptr->finHand[player].card2.suit1, ptr->finHand[player].card3.suit1, ptr->finHand[player].card4.suit1, ptr->finHand[player].card5.suit1);
	if (ptr->finHand[player].card1.card1 == 10)
	{
		ptr->finHand[player].card1.card1 = ptr->player[player].card1;
		ptr->finHand[player].card1.suit1 = ptr->player[player].suit1;
		check1 = 1;
	}
	if (ptr->finHand[player].card1.card1 == 0 && check1 == 0)
	{
		ptr->finHand[player].card1.card1 = ptr->board.flop[0].card1;
		ptr->finHand[player].card1.suit1 = ptr->board.flop[0].suit1;
		check1 = 1;
	}
	if (ptr->finHand[player].card1.card1 == 1 && check1 == 0)
	{
		ptr->finHand[player].card1.card1 = ptr->board.flop[1].card1;
		ptr->finHand[player].card1.suit1 = ptr->board.flop[1].suit1;
		check1 = 1;
	}
	if (ptr->finHand[player].card2.card1 == 11 && check2 == 0)
	{
		ptr->finHand[player].card2.card1 = ptr->player[player].card2;
		ptr->finHand[player].card2.suit1 = ptr->player[player].suit2;
		check2 = 1;
	}
	if (ptr->finHand[player].card2.card1 == 0 && check2 == 0)
	{
		ptr->finHand[player].card2.card1 = ptr->board.flop[0].card1;
		ptr->finHand[player].card2.suit1 = ptr->board.flop[0].suit1;
		check2 = 1;
	}
	if (ptr->finHand[player].card2.card1 == 1 && check2 == 0)
	{
		ptr->finHand[player].card2.card1 = ptr->board.flop[1].card1;
		ptr->finHand[player].card2.suit1 = ptr->board.flop[1].suit1;
		check2 = 1;
	}

	if (ptr->finHand[player].card3.card1 == 0)
	{
		ptr->finHand[player].card3.card1 = ptr->board.flop[0].card1;
		ptr->finHand[player].card3.suit1 = ptr->board.flop[0].suit1;
		check3 = 1;
	}
	if (ptr->finHand[player].card3.card1 == 1 && check3 == 0)
	{
		ptr->finHand[player].card3.card1 = ptr->board.flop[1].card1;
		ptr->finHand[player].card3.suit1 = ptr->board.flop[1].suit1;
		check3 = 1;
	}
	if (ptr->finHand[player].card3.card1 == 2 && check3 == 0)
	{
		ptr->finHand[player].card3.card1 = ptr->board.flop[2].card1;
		ptr->finHand[player].card3.suit1 = ptr->board.flop[2].suit1;
		check3 = 1;
	}
	if (ptr->finHand[player].card4.card1 == 1)
	{
		ptr->finHand[player].card4.card1 = ptr->board.flop[1].card1;
		ptr->finHand[player].card4.suit1 = ptr->board.flop[1].suit1;
		check4 = 1;
	}
	if (ptr->finHand[player].card4.card1 == 2 && check4 == 0)
	{
		ptr->finHand[player].card4.card1 = ptr->board.flop[2].card1;
		ptr->finHand[player].card4.suit1 = ptr->board.flop[2].suit1;
		check4 = 1;
	}
	if (ptr->finHand[player].card4.card1 == 3 && check4 == 0)
	{
		ptr->finHand[player].card4.card1 = ptr->board.turn[0].card1;
		ptr->finHand[player].card4.suit1 = ptr->board.turn[0].suit1;
		check4 = 1;
	}
	if (ptr->finHand[player].card5.card1 == 2)
	{
		ptr->finHand[player].card5.card1 = ptr->board.flop[2].card1;
		ptr->finHand[player].card5.suit1 = ptr->board.flop[2].suit1;
		check5 = 1;
	}
	if (ptr->finHand[player].card5.card1 == 3 && check5 == 0)
	{
		ptr->finHand[player].card5.card1 = ptr->board.turn[0].card1;
		ptr->finHand[player].card5.suit1 = ptr->board.turn[0].suit1;
		check5 = 1;
	}
	if (ptr->finHand[player].card5.card1 == 4 && check5 == 0)
	{
		ptr->finHand[player].card5.card1 = ptr->board.river[0].card1;
		ptr->finHand[player].card5.suit1 = ptr->board.river[0].suit1;
		check5 = 1;
	}
	//printf("\n%d CARD1  %d CARD2  %d CARD3 %d CARD4 %d CARD5", ptr->finHand[player].card1.card1, ptr->finHand[player].card2.card1, ptr->finHand[player].card3.card1, ptr->finHand[player].card4.card1, ptr->finHand[player].card5.card1);
	//printf("\n%d SUIT1  %d SUIT2  %d SUIT3 %d SUIT4 %d SUIT5", ptr->finHand[player].card1.suit1, ptr->finHand[player].card2.suit1, ptr->finHand[player].card3.suit1, ptr->finHand[player].card4.suit1, ptr->finHand[player].card5.suit1);
	//printf("\n %d %d %d\t %d\t %d", ptr->board.flop[0].card1, ptr->board.flop[1].card1, ptr->board.flop[2].card1, ptr->board.turn[0].card1, ptr->board.river[0].card1);
	if (ptr->pftr == 2)
	{
		turnOddCalc(ptr, player);
	}
	if (ptr->pftr == 3)
	{
		checkValue(ptr, player);
	}
	//printf("\nPLAYER -- %d ---- CARD 1--%d \t CARD 2--%d\t CARD 3--%d\t CARD4--%d\t CARD5--%d\n", p, ptr->finHand[p].card1.card1, ptr->finHand[p].card2.card1, ptr->finHand[p].card3.card1, ptr->finHand[p].card4.card1, ptr->finHand[p].card5.card1);

	/*for (int p = 0; p < 5; p++)
	{
	//	printf("\nTHE VALUE OF THE VALUE[%d] = %d\n ", p,ptr->finHand[player].Value[p]);
	}*/
}

//FINDS THE VALUE OF THE HAND THE PLAYER HAS
void checkValue(data * ptr, int player)
{
	ptr->finHand[player].handType = 0;
	if (ptr->finHand[player].Value[0] < 900)
	{
		checkFlush(ptr, player);
	}
	if (ptr->finHand[player].Value[0] < 500 || ptr->finHand[player].handType == 6)
	{
		checkStraight(ptr, player);
	}
	if (ptr->finHand[player].Value[0] < 800 && ptr->finHand[player].handType != 5)
	{
		check4kind(ptr, player);
	}
	if (ptr->finHand[player].Value[0] < 700 && ptr->finHand[player].handType != 5 && ptr->finHand[player].handType != 6)
	{
		checkFull(ptr, player);
	}
	if (ptr->finHand[player].Value[0] < 100)
	{
		highCard(ptr, player);
	}

}
//CHECKS FOR FLUSH STORES VALUE
void checkFlush(data *ptr, int player)
{
	int suitArray[5] = { ptr->finHand[player].card1.suit1,ptr->finHand[player].card2.suit1, ptr->finHand[player].card3.suit1 ,ptr->finHand[player].card4.suit1 ,ptr->finHand[player].card5.suit1 };
	int cardArray[5] = { ptr->finHand[player].card1.card1,ptr->finHand[player].card2.card1, ptr->finHand[player].card3.card1 ,ptr->finHand[player].card4.card1 ,ptr->finHand[player].card5.card1 };
	int value[5] = { 0,0,0,0,0 };
	int flushNum = 0;
	for (int j = 0; j < 5; j++)
	{
		if (suitArray[0] != suitArray[j])
		{
			break;
		}
		//printf("\tSUIT == %d", suitArray[j]);
		flushNum++;
		if (flushNum == 5)
		{
			value[0] = 500;
			int highCard = 0;
			for (int p = 0; p < 5; p++)
			{
				if (highCard < cardArray[p])
				{
					highCard = cardArray[p];
				}
			}
			value[0] += highCard;
			break;
		}

	}
	int temp;
	for (int t = 0; t < 4; t++)
	{
		for (int j = 0; j < 4 - t; j++)
		{
			if (cardArray[j] < cardArray[j + 1])
			{
				temp = cardArray[j];
				cardArray[j] = cardArray[j + 1];
				cardArray[j + 1] = temp;
			}
		}

	}
	for (int p = 1; p < 5; p++)
	{
		value[p] = cardArray[p];
		//printf("%d value %d P", value[p], p);
	}

	if (value[0] > 0)
	{
		changeHandStrength(ptr, value, player);
	}
}
//CHECKS FOR STRAIGHT
void checkStraight(data *ptr, int player)
{
	int topV = 20;
	int cardArray[5] = { ptr->finHand[player].card1.card1,ptr->finHand[player].card2.card1, ptr->finHand[player].card3.card1 ,ptr->finHand[player].card4.card1 ,ptr->finHand[player].card5.card1 };
	int value[5] = { 0,0,0,0,0 };
	int straight = 0;
	int straightCard[5];
	for (int k = 0; k < 5; k++)
	{
		straightCard[k] = cardArray[k];
	}
	int temp = 0;
	for (int t = 0; t < 4; t++)
	{
		for (int j = 0; j < 4 - t; j++)
		{
			if (straightCard[j] > straightCard[j + 1])
			{
				temp = straightCard[j];
				straightCard[j] = straightCard[j + 1];
				straightCard[j + 1] = temp;
			}
		}

	}
	int temp2 = 0;
	if (straightCard[0] == 0 && straightCard[4] == 12)
	{
		temp = straightCard[0];
		straightCard[0] = -1;
		for (int m = 1; m < 5; m++)
		{
			temp2 = straightCard[m];
			straightCard[m] = temp;
			temp = temp2;
			//	printf("!!!!!!!!!CHECKING STRAIGHT card value %d array num %d\n", straightCard[m], m);
		}
	}
	int sNum = 0;
	for (int p = 0; p < 4; p++)
	{
		if ((straightCard[p] + 1) != straightCard[p + 1])
		{
			break;
		}
		//printf("====%d==== StraightCard %d P ---- STRAIGHTCARD[P + 1]=%d", straightCard[p],p, straightCard[p + 1]);
		sNum++;

		if (sNum == 4)
		{
			if (ptr->finHand[player].handType != 6)
			{
				value[0] = 400 + straightCard[4];
				//	printf("\n\n\n\n\n\n\n\n\\n STTTRRAIGNGNTNNTNTS");
				straight = 1;
			}
			if (ptr->finHand[player].handType == 6)
			{
				value[0] = 800 + cardArray[4];
				ptr->finHand[player].handType = 9;
			}
		}
	}
	if (straight == 1)
	{
		if (value[0] > ptr->finHand[player].Value[0])
		{
			ptr->finHand[player].handType = 5;
			changeHandStrength(ptr, value, player);
		}
	}

}
//CHECKS FOR 4kind
void check4kind(data *ptr, int player)
{
	int topV = 20;
	int cardArray[5] = { ptr->finHand[player].card1.card1,ptr->finHand[player].card2.card1, ptr->finHand[player].card3.card1 ,ptr->finHand[player].card4.card1 ,ptr->finHand[player].card5.card1 };
	int value[5] = { 0,0,0,0,0 };
	int fourKind = 0;
	for (int j = 0; j < 4; j++)
	{
		for (int p = j + 1; p < 5; p++)
		{
			if (cardArray[j] == cardArray[p])
			{
				for (int m = p + 1; m < 5; m++)
				{
					if (cardArray[j] == cardArray[m])
					{
						for (int t = m + 1; t < 5; t++)
						{
							//	printf("M = %d  T %d ", m, t);
							if (cardArray[j] == cardArray[t])
							{
								fourKind = 1;
								for (int r = 0; r < 4; r++)
								{
									if (cardArray[r] != cardArray[j])
									{
										value[0] = 100 * 7 + cardArray[j];
										value[1] = cardArray[r];
										break;
									}

								}
							}
						}

					}
					if (fourKind == 1)
					{
						break;
					}
				}
			}
			if (fourKind == 1)
			{
				break;
			}
		}
		if (fourKind == 1)
		{
			break;
		}
		if (value[0] >= ptr->finHand[player].Value[0])
		{
			if (value[1] > ptr->finHand[player].Value[1])
			{
				changeHandStrength(ptr, value, player);
			}
		}
	}
}

//CHECKS for FullHouse,TWOpair, Threes,Pair
void checkFull(data *ptr, int player)
{
	int topV = 20;
	int cardArray[5] = { ptr->finHand[player].card1.card1,ptr->finHand[player].card2.card1, ptr->finHand[player].card3.card1 ,ptr->finHand[player].card4.card1 ,ptr->finHand[player].card5.card1 };
	int value[5] = { 0,0,0,0,0 };

	int pair1 = 20;
	int pair2 = 30;
	int pair3 = 40;
	int largePair = 0;
	int smPair = 0;
	int three = 0;
	int fullHouse = 0;
	int check = 0;
	int count = 0;
	for (int j = 0; j < 4; j++)
	{
		for (int k = j + 1; k < 5; k++)
		{
			if (cardArray[j] == cardArray[k])
			{
				if (cardArray[j] == pair3)
				{
					break;
				}
				if (check == 1 && cardArray[j] != pair1)
				{
					pair2 = cardArray[j];
					value[0] = 200 + largePair;
					if (pair3 != 40 && pair1 != 20)
					{
						fullHouse = 1;
						value[0] = 7 * 100 + pair3;
						if (pair1 == pair3)
						{
							value[1] = pair2;
						}
						if (pair2 == pair3)
						{
							value[1] = pair1;
						}
					}
				}
				if (pair1 == 20)
				{
					value[0] = 100;
					pair1 = cardArray[j];
					if (pair3 != 40 && pair2 != 30)
					{
						fullHouse = 1;
						value[0] = 7 * 100 + pair3;
						if (pair1 == pair3)
						{
							value[1] = pair2;
						}
						if (pair2 == pair3)
						{
							value[1] = pair1;
						}
					}
				}
				check = 1;
				for (int m = k + 1; m < 5; m++)
				{
					if (pair3 == cardArray[j])
					{
						printf("error BROKEN LOOP");
						break;
					}
					if (cardArray[j] == cardArray[m])
					{
						pair3 = cardArray[j];
						value[0] = 300 + cardArray[j];
						break;
					}
					if (pair3 != 40)
					{
						break;
					}
				}

			}
		}

	}

	if (pair1 != 20 && pair2 != 30)
	{
		if (pair1 > pair2)
		{
			largePair = pair1;
			smPair = pair2;
		}
		if (pair2 > pair1)
		{
			largePair = pair2;
			smPair = pair1;

		}
	}
	if (pair1 != 20 && pair2 != 30 && pair3 != 40)
	{
		value[0] = 600 + pair3;
		//printf("FULLHOUSE\n");
		if (pair1 == pair3)
		{
			value[1] = pair2;
		}
		else {
			value[1] = pair1;
		}
	}

	if (pair2 == 30 && pair3 != 40 && pair1 != 20)
	{
		int card[5];
		value[0] = 300 + pair3;
		for (int k = 0; k < 5; k++)
		{
			card[k] = cardArray[k];
		}
		for (int t = 0; t < 5; t++)
		{
			for (int j = 0; j < 5 - t; j++)
			{
				if (card[j] < card[j + 1])
				{
					int temp = card[j];
					card[j] = card[j + 1];
					card[j + 1] = temp;
				}
			}
		}
		count = 1;
		for (int p = 0; p < 5; p++)
		{
			if (card[p] != pair3 && card[p] != pair1)
			{
				value[count] = card[p];
			}
			if (card[p] == pair3 && card[p] == pair1)
			{
				count--;
			}
			count++;
		}
	}

	if (pair2 != 30 && pair3 == 40 && pair1 != 20)
	{
		int card[5];
		value[0] = 200 + largePair;
		value[1] = smPair;
		for (int k = 0; k < 5; k++)
		{
			card[k] = cardArray[k];
		}
		for (int t = 0; t < 5; t++)
		{
			for (int j = 0; j < 5 - t; j++)
			{
				if (card[j] < card[j + 1])
				{
					int temp = card[j];
					card[j] = card[j + 1];
					card[j + 1] = temp;
				}
			}
		}
		count = 2;
		for (int p = 0; p < 5; p++)
		{
			if (card[p] != pair1 && card[p] != pair2)
			{
				value[count] = card[p];
			}
			if (card[p] == pair1 || card[p] == pair2)
			{
				count--;
			}
			count++;
		}

	}
	if (pair2 == 30 && pair3 == 40 && pair1 != 20)
	{
		int card[5];
		value[0] = 100 + pair1;
		for (int k = 0; k < 5; k++)
		{
			card[k] = cardArray[k];
		}
		for (int t = 0; t < 5; t++)
		{
			for (int j = 0; j < 5 - t; j++)
			{
				if (card[j] < card[j + 1])
				{
					int temp = card[j];
					card[j] = card[j + 1];
					card[j + 1] = temp;
				}
			}
		}
		count = 1;
		for (int p = 0; p < 5; p++)
		{
			if (card[p] != pair1)
			{
				value[count] = card[p];
			}
			if (card[p] == pair1)
			{
				count--;
			}
			count++;
		}

	}
	if (value[0] >= ptr->finHand[player].Value[0])
	{
		changeHandStrength(ptr, value, player);
	}
}
//Checks for HIGHCARD
void highCard(data *ptr, int player)
{
	int topV = 20;
	int cardArray[5] = { ptr->finHand[player].card1.card1,ptr->finHand[player].card2.card1, ptr->finHand[player].card3.card1,ptr->finHand[player].card4.card1,ptr->finHand[player].card5.card1 };
	int value[5] = { 0,0,0,0,0 };
	int temp;
	int card[5];
	for (int k = 0; k < 5; k++)
	{
		card[k] = cardArray[k];
	}
	for (int t = 0; t < 5; t++)
	{
		for (int j = 0; j < 5 - t; j++)
		{
			if (card[j] < card[j + 1])
			{
				temp = card[j];
				card[j] = card[j + 1];
				card[j + 1] = temp;
			}
		}
	}
	for (int j = 0; j < 5; j++)
	{
		value[j] = card[j];
	}
	if (value[0] >= ptr->finHand[player].Value[0])
	{
		changeHandStrength(ptr, value, player);
	}
}

void changeHandStrength(data * ptr, int * val, int player)
{
	int topV = 20;
	if (val[0] == ptr->finHand[player].Value[0])
	{
		if (val[1] > ptr->finHand[player].Value[1])
		{
			topV = 1;
		}
		if (val[1] == ptr->finHand[player].Value[1])
		{
			if (val[2] > ptr->finHand[player].Value[2])
			{
				topV = 1;
			}
			if (val[2] == ptr->finHand[player].Value[1])
			{
				if (val[3] > ptr->finHand[player].Value[3])
				{
					topV = 1;
				}
				if (val[3] == ptr->finHand[player].Value[3])
				{
					if (val[4] > ptr->finHand[player].Value[4])
					{
						topV = 1;
					}
					if (val[4] == ptr->finHand[player].Value[4])
					{
						topV = 0;
						if (val[2] > ptr->finHand[player].Value[2])
						{
							topV = 1;
						}
					}
				}

			}
		}
	}

	if (val[0] > ptr->finHand[player].Value[0] || topV == 1)
	{
		for (int p = 0; p < 5; p++)
		{
			ptr->finHand[player].Value[p] = val[p];


		}
		printf("\nVALUE CHANGED");
		playerBestHand(ptr, player);
	}



}


void playerBestHand(data *ptr, int player)
{
	ptr->bestHand[player].card1.card1 = ptr->finHand[player].card1.card1;
	ptr->bestHand[player].card2.card1 = ptr->finHand[player].card2.card1;
	ptr->bestHand[player].card3.card1 = ptr->finHand[player].card3.card1;
	ptr->bestHand[player].card4.card1 = ptr->finHand[player].card4.card1;
	ptr->bestHand[player].card5.card1 = ptr->finHand[player].card5.card1;
	ptr->bestHand[player].card1.suit1 = ptr->finHand[player].card1.suit1;
	ptr->bestHand[player].card2.suit1 = ptr->finHand[player].card2.suit1;
	ptr->bestHand[player].card3.suit1 = ptr->finHand[player].card3.suit1;
	ptr->bestHand[player].card4.suit1 = ptr->finHand[player].card4.suit1;
	ptr->bestHand[player].card5.suit1 = ptr->finHand[player].card5.suit1;
}
//COMPARES HAND VALUES AND FINDS WINNER
void valueCompare(data *ptr)
{

	int tiePlayer1 = 100;
	int tiePlayer2 = 100;
	int tieCheck = 0;
	for (int m = 0; m < 4; m++)
	{
		for (int h = 0; h < 5; h++)
		{
			printf("\nPLAYER %d VALUE[%d] == %d", m, h, ptr->finHand[m].Value[h]);
		}
		printf("FOLDED = %d", ptr->player[m].folded);
	}

	if (ptr->player[0].folded == 1 && ptr->player[1].folded == 1 && ptr->player[2].folded == 1 && ptr->player[3].folded == 1)
	{
		printf("EVERYONE FOLDED ERROR IN THE GAME!");
		return 0;
	}
	int check1 = 20;
	int check2 = 20;
	int winner = 10;
	int count = 0;
	int kCheck = 0;
	for (int j = 0; j < 3; j++)
	{
		check1 = 0;
		for (int k = 3; k > j; k--)
		{
			check2 = 20;
			if (ptr->player[j].folded == 1)
			{
				break;
			}
			for (int p = 0; p < 5; p++)
			{
				if (ptr->player[k].folded == 1)
				{
					check1++;
					winner = j;
					break;
				}

				if (ptr->finHand[j].Value[p] > ptr->finHand[k].Value[p])
				{
					check1++;
					winner = j;
					break;
				}
				if (ptr->finHand[j].Value[p] < ptr->finHand[k].Value[p])
				{
					winner = k;
					check2 = 1;
					break;
				}
				if (ptr->finHand[j].Value[p] == ptr->finHand[k].Value[p])
				{
					count++;
					if (count == 5)
					{
						printf("\nTIE FLAGGED");
						tiePlayer1 = k;
						tiePlayer2 = j;
					}
				}

			}
			if (check2 == 1)
			{
				break;
			}
		}
		if (check1 == 3 - j)
		{
			break;
		}
	}
	if (count == 5 && (winner == tiePlayer1 || winner == tiePlayer2))
	{
		tieCheck = checkTie(ptr, winner);
		printf("checking for tie");
	}
	if (winner == 10)
	{
		winner = 3;
	}
	if (tieCheck == 0)
	{
		giveWinnerMoney(ptr, winner);
	}

	if (tieCheck == 0)
	{
		for (int k = 0; k < MAXPLAYER; k++)
		{
			if (ptr->player[k].folded == 0)
			{
				HandCalcData(ptr, k);
			}
		}
	}
}


void giveWinnerMoney(data *ptr, int winner)
{
	ptr->winner = winner;
	ptr->pData[winner].wins++;
	ptr->moneyPlayer.playerMoney[winner] += ptr->moneyPlayer.pot;
	printf("\nPLAYER %d WON %d MONEY!!!!", winner, ptr->moneyPlayer.pot);
	printf("BEST HAND == CARD %d SUIT %d", ptr->bestHand[winner].card1.card1, ptr->bestHand[winner].card1.suit1);
	printf("\tCARD %d SUIT %d", ptr->bestHand[winner].card2.card1, ptr->bestHand[winner].card2.suit1);
	printf("\tCARD %d SUIT %d", ptr->bestHand[winner].card3.card1, ptr->bestHand[winner].card3.suit1);
	printf("\tCARD %d SUIT %d", ptr->bestHand[winner].card4.card1, ptr->bestHand[winner].card4.suit1);
	printf("\tCARD %d SUIT %d", ptr->bestHand[winner].card5.card1, ptr->bestHand[winner].card5.suit1);
	for (int p = 0; p < 4; p++)
	{

		printf("\nBEST HAND == CARD %d SUIT %d", ptr->bestHand[p].card1.card1, ptr->bestHand[p].card1.suit1);
		printf("\tCARD %d SUIT %d", ptr->bestHand[p].card2.card1, ptr->bestHand[p].card2.suit1);
		printf("\tCARD %d SUIT %d", ptr->bestHand[p].card3.card1, ptr->bestHand[p].card3.suit1);
		printf("\tCARD %d SUIT %d", ptr->bestHand[p].card4.card1, ptr->bestHand[p].card4.suit1);
		printf("\tCARD %d SUIT %d", ptr->bestHand[p].card5.card1, ptr->bestHand[p].card5.suit1);
		if (ptr->player[p].folded == 0)
		{
			ptr->pData[p].lostRiver++;
		}
		ptr->pData[p].pPlay++;

	}
}

//CHECKS FOR A TIE
int checkTie(data *ptr, int winner)
{

	int tie[4] = { 0,0,0,0 };
	for (int p = 0; p < 4; p++)
	{
		for (int k = p + 1; k < 4; k++)
		{
			int count = 0;
			for (int r = 0; r < 5; r++)
			{
				if (ptr->finHand[p].Value[r] == ptr->finHand[k].Value[r])
				{
					count++;
					if (count == 5)
					{
						if (winner == k)
						{
							tie[k] = 1;
						}
						if (winner == p)
						{
							tie[p] = 1;
						}
					}
				}
			}
		}

	}

	int count = 1;
	for (int g = 0; g < 4; g++)
	{
		if (tie[g] == 1)
		{
			count++;
		}
	}

	int pots = ptr->moneyPlayer.pot / count;
	for (int j = 0; j < 4; j++)
	{
		if (tie[j] == 1)
		{
			ptr->moneyPlayer.playerMoney[j] += pots;
		}
	}
	if (count == 1)
	{
		return 0;
	}
	if (count > 1)
	{
		return 1;
	}
}
//STORES THE DATA
void buttonMove(data *ptr)
{
	ptr->buttons.dealer++;
	if (ptr->buttons.dealer > 3)
	{
		ptr->buttons.dealer = 0;
	}
	//ptr2->handHistory[ptr->buttons.hand] = *ptr;

	printf("\nBUTTON LOCATION IS %d\n", ptr->buttons.dealer);
	ptr->buttons.hand++;
	printf("\nHAND NUMBER IS %d\n", ptr->buttons.hand);

	if (ptr->buttons.hand%10000 == 0)
	{
		handDatabase(ptr);
	}
	return;
}

void HandCalcData(data * ptr, int player)
{
	int card1 = ptr->player[player].card1;
	int card2 = ptr->player[player].card2;
	ptr->player[player].suit1;
	ptr->player[player].suit2;
	int count = 1000;
	int offsuit = 0;
	int temp;

	if(ptr->player[player].card1 > ptr->player[player].card2)
	{
		temp = card1;
		card1 = card2;
		card2 = temp;
	}

	if (ptr->player[player].suit1 == ptr->player[player].suit2)
	{
		offsuit = 1;
	}
	if (ptr->player[player].card1 == ptr->player[player].card2)
	{
		offsuit = 2;
	}

	for (int k = 0; k<169; k++)
	{
		if (ptr->odds.da[k].card1 == card1)
		{
			if (ptr->odds.da[k].card2 == card2)
			{
				if (ptr->odds.da[k].offsuit == offsuit)
				{
					count = k;
					break;
				}
			}

		}
		if (count != 1000)
		{
			break;
		}
	}

	if (player == ptr->winner)
	{
		ptr->odds.da[count].won++;
	}

	ptr->odds.da[count].played++;

}
