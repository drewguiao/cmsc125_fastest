typedef struct player_tag{
	char name[20];
	int score;
	struct player_tag *next;
	struct player_tag *prev;
}player;


void cleanTerminal(){
	system("clear");
}

void loadLeaderboards(player **p){
	player *newNode, *temp;
	char playerName[10];
	int playerScore;

	FILE *fp;
	fp = fopen("leaderboards.txt","r");
	if(fp == NULL){
		printf("leaderboards.txt not found!\n");
	}else{
		while(!feof(fp)){
			newNode = (player * )malloc(sizeof(player));
			fscanf(fp,"%s %d\n",playerName, &playerScore);

			strcpy(newNode->name,playerName);
			newNode->score = playerScore;

			// printf("Name: %s\n",newNode->name);
			// printf("Score: %d\n",newNode->score);

			if((*p) == NULL){
				(*p) = newNode;
				(*p)->next = (*p);
				(*p)->prev = (*p);
			}else{
				newNode->next = (*p);
				newNode->prev = (*p)->prev;
				(*p)->prev->next = newNode;
				(*p)->prev = newNode;

			}
		}
		fclose(fp);
	}
	
}


void viewLeaderboards(player **p){
	player *temp;
	temp = (*p);
	int index = 1;
	cleanTerminal();
	if((*p) == NULL){
		cleanTerminal();
		printf("Leaderboards is empty!\n");
	}else{
		printf("+-------------------------------+\n");
		printf("+          LEADERBOARDS         +\n");
		printf("+-------------------------------+\n");

		if(temp->next == temp){
			printf("+\t1.%s\t%d\t\t+\n",temp->name,temp->score);
		}else{
			while(temp->next != (*p)){
				printf("+\t%d.%s\t%d\t\t+\n",index,temp->name,temp->score);
				temp = temp->next;
				index++;
				if(temp->next == (*p)){
					printf("+\t%d.%s\t%d\t\t+\n",index,temp->name,temp->score);
				}
			}
		}
		printf("+-------------------------------+\n");
	}
	printf("Press any number then enter to go back ");

}


void addToLeaderboards(player **p, char *playerName, int playerScore){
	player *newNode, *temp, *tail;

	newNode = (player *)malloc(sizeof(player));
	strcpy(newNode->name,playerName);
	newNode->score = playerScore;

	if((*p) == NULL){
		(*p)=newNode;
		(*p)->prev=(*p);
		(*p)->next=(*p);
	}else{
		temp = (*p);
		tail = (*p)->prev;

		// insert at head
		if(newNode->score >= (*p)->score){
			(*p)->prev = newNode;
			tail->next = newNode;
			newNode->next = (*p);
			newNode->prev = tail;
			(*p) = newNode;
		}
		else{
			while(1){
				temp = temp->next;
				//insert after p (there is only 1 node)
				if((*p)->next == (*p) && newNode->score < (*p)->score){
					newNode->next = (*p);
					newNode->prev = (*p);
					(*p)->next = newNode;
					(*p)->prev = newNode;
					break;
				}
				
				//insert at middle (there are more than 1 node)
				if(newNode->score >= temp->score && newNode->score <= temp->prev->score){
					newNode->next = temp;
					newNode->prev = temp->prev;
					temp->prev->next = newNode;
					temp->prev= newNode;
					break;
				}

				//insert at tail
				if(temp->next == (*p) && newNode->score <= temp->score){
					newNode->next = (*p);
					newNode->prev = temp;
					temp->next = newNode;
					(*p)->prev = newNode;
					break;
				}

			}
		}
	}


}

void initializeRandomization(){
	srand(time(NULL));
}

void printMenu(){
	printf("Welcome to Fastest!\n");
	printf("=====================\n");
	printf("[1] Play game\n");
	printf("[2] View Instructions\n");
	printf("[3] View leaderboards\n");
	printf("[0] Quit game\n");
	printf("=====================\n");
	printf(">> ");
}


int getChoice(){
	int choice;
	scanf("%d",&choice);
	return choice;
}

void showInstructions(){
	printf("Just memorize the pattern and type it!\n");
	sleep(3);
	cleanTerminal();
}

void viewInstructions(){
	cleanTerminal();
	printf("+-------------------------------+\n");
	printf("+          INSTRUCTIONS         +\n");
	printf("+-------------------------------+\n");
	printf("+ For every round, you will be  +\n");
	printf("+   given a random sequence of  +\n");
	printf("+   numbers. You should be able +\n");
	printf("+   to memorize the sequence    +\n");
	printf("+   under a definite time.      +\n");
	printf("+                               +\n");
	printf("+ Then, you are to type the     +\n");
	printf("+   sequence. If correct, you   +\n");
	printf("+   proceed to the next round.  +\n");
	printf("+   Else, you lose.\t\t+\n");
	printf("+                               +\n");
	printf("+ Time allotted to display the  +\n");
	printf("+   sequence decreases as you   +\n");
	printf("+   progress. Good luck and     +\n");
	printf("+   have fun! -GM\t\t+\n");
	printf("+-------------------------------+\n");
	printf("Press any number then enter to go back ");
}


void showCountdown(){
	printf("Starting in 3..\n");
	sleep(1);
	cleanTerminal();
	printf("Starting in 3..2..\n");
	sleep(1);
	cleanTerminal();
	printf("Starting in 3..2..1..\n");
	sleep(1);

}

void printRoundAndScoreTab(int playerRound, int rawScore){
	printf("+---------------+---------------+\n");
	printf("+ Round %d\t+ Score  %d\t+\n",playerRound,rawScore);
	printf("+---------------+---------------+\n");

}


void randomizeArray(int *comArray, int arraySize){
	int i = 0;

	for(i = 0 ; i < arraySize ; i++ ){	
		*(comArray + i) = rand()%9;
	}
}

void printArray(int *comArray, int arraySize){
	int i = 0;
	printf(">> ");
	for(i = 0 ; i < arraySize ; i++){
		printf("%d",comArray[i]);
	}
	printf("\n");
}

void convertStringToInt(char *a, int arraySize){
	int i;
	for(i=0;i<5;i++){
		switch(*(a+i)){
			case '1' : *(a+i) = 1;
			break;
			case '2' : *(a+i) = 2;
			break;
			case '3' : *(a+i) = 3;
			break;
			case '4' : *(a+i) = 4;
			break;
			case '5' : *(a+i) = 5;
			break;
			case '6' : *(a+i) = 6;
			break;
			case '7' : *(a+i) = 7;
			break;
			case '8' : *(a+i) = 8;
			break;
			case '9' : *(a+i) = 9;
			break;
			case '0' : *(a+i) = 0;
			break;
		}
	}
}

int checkArray(int *comArray, char *userArray, int arraySize){
	int i;

	for(i = 0 ; i < arraySize ; i++){
		if(comArray[i] != userArray[i]){
			return 2;
		}
	}
	return 1;
}

int checkElement(int *comArray, int dogeNum, int dogeIndex){

	if(comArray[dogeIndex] != dogeNum) return 2;
	else return 1;

}


void addScore(int *rawScore, int baseScore){
	*rawScore = *rawScore + baseScore;
}


void saveToFile(player **p){
	player *temp;
	FILE *fp;
	if((*p)==NULL){
		fp=fopen("leaderboards.txt","w");
		getc(fp)==-1;
		fclose(fp);
		//return;
	}
	fp=fopen("leaderboards.txt", "w");
	temp=(*p);
		while(temp->next!=(*p)){
			fprintf(fp, "%s ", temp->name);
			fprintf(fp, "%d\n", temp->score);
			temp=temp->next;
		}//end of while
		if(temp->next=(*p)){
			fprintf(fp, "%s ", temp->name);
			fprintf(fp, "%d\n", temp->score);
		}//end of if
	fclose(fp);
}

void freeList(player **p){
	player *ptr;
	if((*p) == NULL){
		printf("List is empty!\n");
	}else{
		ptr=(*p)->prev;
		(*p)->prev=ptr->prev;
		ptr->prev->next=(*p);
		free(ptr);
	}
}

void resetValues(int *playerRound, int *rawScore, int *baseScore, int *sleepTime, int *deadEndFlag, int *dogeFlag){
	*playerRound = 1;
	*rawScore = 0;
	*baseScore = 5;
	*sleepTime = 5;
	*deadEndFlag = 0;
	*dogeFlag = 0;
}

