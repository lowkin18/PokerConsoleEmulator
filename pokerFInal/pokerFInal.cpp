// Pokerapplication.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <time.h>
#include "poker.h"


layout startSetup();
data handDraw(layout * set);
void checkData(data * ptr, int local);
data blinds(data * ptr);
void preFlop(data * ptr);
void buttonMove(data*ptr);
void reDraw(data *ptr);
void flopping(data *ptr);
void turn(data *ptr);
void river(data*ptr);
void findWinner(data *ptr);
void debug(data *ptr);
//HEAP MEMORY WIPE

void printFinalData(data * ptr);


int main()
{
	srand(time(NULL));
	layout begin = startSetup();
	data mainData = handDraw(&begin);
	int p = 0;
	char play = 'y';
	do
	{
		if (p == 1)
		{
			reDraw(&mainData);
		}
		blinds(&mainData);//sets blinds
		checkData(&mainData, 1);	//checks card data
		preFlop(&mainData);//preflop action
		flopping(&mainData);//flops 3 cards and then does the action
		turn(&mainData);//turns card and turn action
		river(&mainData);//river card then action
		findWinner(&mainData);//calculates the winner from whos still remaining
	//	checkData(&mainData, 2);//checks data at the end	
		buttonMove(&mainData);//takes hand info and stores in database
											 //getchar();
		p = 1;// sets the redraw condition
	} while (mainData.buttons.hand< 2000000);

	printf("game over");
	printFinalData(&mainData);
	getchar();
}




void printFinalData(data * ptr)
{
	for (int k = 0; k <4; k++)
	{
		int playRate = ptr->pData[k].pPlay / ptr->buttons.hand;
		printf("\nTHE PLAYER %d WON A TOTAL OF %d MONEY\t", k, ptr->moneyPlayer.playerMoney[k]);
		printf("\tThe player %d REBOUGHT %d TIMES", k, ptr->moneyPlayer.rebuy[k]);
		printf("THERE PLAY RATE WAS %d", playRate);
	}


}

void debug(data *ptr)
{
	for (int k = 0; k < 4; k++)
	{
		if (ptr->player[k].card1 == ptr->player[k].card2)
		{
			printf("we have a pair");
			getchar;
		}


	}


}

