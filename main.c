#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include"functions.h"
#define arraySize 5



int main(){


	player *p;
	p=(player *)malloc(sizeof(player));
	p=NULL;


	loadLeaderboards(&p);
	char userArray[arraySize];
	char playerName[10];
	
	int comArray[arraySize];

	int playerRound = 1;
	int rawScore = 0;
	int baseScore = 5;
	int sleepTime = 5;
	int deadEndFlag = 0;
	int dogeFlag = 0;
	int dogeIndex;
	int dogeNum;

	initializeRandomization();
	
	while(1){
		if(deadEndFlag == 1 || dogeFlag == 1){
			resetValues(&playerRound,&rawScore,&baseScore,&sleepTime,&deadEndFlag,&dogeFlag);
		}
		printMenu();
		switch(getChoice()){
			case 1: cleanTerminal();
					//showInstructions();
					showCountdown();
					while(deadEndFlag != 1){
						cleanTerminal();
						switch(playerRound){
							case 6: printf("Now faster!\n");
									sleep(2);
									sleepTime--;
									baseScore = 10;
									break;
							case 11:printf("Even faster!\n");
									sleep(2);
									sleepTime--;
									baseScore = 15;
									break;
							case 16:printf("Can you still go?\n");
									sleep(2);
									sleepTime--;
									baseScore = 20;
									break;
							case 21:printf("Can you handle this?\n");
									sleep(2);
									sleepTime--;
									baseScore = 25;
									break;
						}
						printRoundAndScoreTab(playerRound,rawScore);
						randomizeArray(comArray,arraySize);
						printArray(comArray,arraySize);
						sleep(sleepTime);
						cleanTerminal();
						printRoundAndScoreTab(playerRound,rawScore);
						printf(">> ");
						scanf("%s",userArray);
						convertStringToInt(userArray,arraySize);
						if(checkArray(comArray,userArray,arraySize) == 1){
							//proceed to next round
							//printf("You got Round %d!\n",playerRound);
							playerRound++;
							addScore(&rawScore,baseScore);
							//sleep(1);
							cleanTerminal();
						}else{
							//end game and record stats
							deadEndFlag = 1;
							printf("You lose! You reached Round %d with %d points!\n",playerRound,rawScore);
							printf("Type your name: ");
							scanf("%s",playerName);
							printf("\n");
							addToLeaderboards(&p,playerName,rawScore);
							saveToFile(&p);
						}
					}
			break;
			case 2 : viewInstructions();
					if(getChoice()){
						cleanTerminal();
						continue;
					}
			break;
			case 3: viewLeaderboards(&p);
					if(getChoice()){
						cleanTerminal();
						continue;
					}
			break;
			case 777: cleanTerminal();
					printf("You are playing DOGE-MODE!!!!\n");
					sleep(2);
					showCountdown();
					while(dogeFlag != 1){

						cleanTerminal();
						switch(playerRound){
							case 6: printf("Now faster!\n");
									sleep(2);
									sleepTime--;
									baseScore = 10;
									break;
							case 11:printf("Even faster!\n");
									sleep(2);
									sleepTime--;
									baseScore = 15;
									break;
							case 16:printf("Can you still go?\n");
									sleep(2);
									sleepTime--;
									baseScore = 20;
									break;
							case 21:printf("Can you handle this?\n");
									sleep(2);
									sleepTime--;
									baseScore = 25;
									break;
						}
						printRoundAndScoreTab(playerRound,rawScore);
						randomizeArray(comArray,arraySize);
						printArray(comArray,arraySize);
						sleep(sleepTime);
						cleanTerminal();
						printRoundAndScoreTab(playerRound,rawScore);
						dogeIndex = rand()%5;
						printf("Enter character at Sequence[%d]: ",dogeIndex);
						scanf("%d",&dogeNum);
						
						if(checkElement(comArray,dogeNum,dogeIndex) == 1){
							//proceed to next round
							//printf("You got Round %d!\n",playerRound);
							playerRound++;
							addScore(&rawScore,baseScore);
							//sleep(1);
							cleanTerminal();
						}else{
							//end game and record stats
							dogeFlag = 1;
							printf("You lose! You reached Round %d with %d points!\n",playerRound,rawScore);
							printf("Type your name: ");
							scanf("%s",playerName);
							printf("\n");
						}
					}
			break;
			case 0: printf("Exiting the game!\n");
					exit(1);
			default: printf("Not a valid input!\n");
		}
	}

	freeList(&p);
}


