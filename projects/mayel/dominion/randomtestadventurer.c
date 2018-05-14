#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

int iterations = 10000;

void adventureSteps(){
	
	
}


void adventureTests( struct gameState *tState, player){
	
	int temphand[MAX_HAND];
	int cardDrawn;
	int bonus = 0;
	int drawntreasure = 0;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;

	int result;
	
	memcpy(&expState,testState,sizeof(struct gameState));
	
	result = cardEffect(adventurer, choice1, choice2, choice3, tState, 0, &bonus);
	
	if(result)
		

	
	
	//check treasure count
	
	//check shuffle
	
	//check deck counts 
	
	//check gameState variables
	
	//other players
	
	//
	
	return;

}


int main(){


    printf("***** RANDOM TEST - Adventurer*****\n");

    struct gameState testState;
	struct gameState expState;
	
    int treasure[] = {copper,silver,gold};
    int numTreasure;
    int playerN;
    


    int min = 3;
    
	srand(time(NULL));

	
	//top level loop is for number of test iterations
	//it calls function which actually tests card
 
	int i, k;
    for (i = 0; i < iterations; i++) {
      for (k = 0; k < sizeof(struct gameState); k++) {
        ((char*)&testState)[k] = floor(Random() * 256);
      }

	  
      player = floor(Random() * MAX_PLAYERS);
      testState.deckCount[player] = floor(Random() * ((MAX_DECK - min) + 1) + min);
      
	  numTreasure = floor(Random() * ((testState.deckCount[player] - min) + 1) + min);

     
	 
	  int j;
      for (j = 0; j < numTreasures; j++) {
        testState.deck[player][j] = treasure[rand() % 3];
      }
	  
      testState.discardCount[player] = 0;
      testState.handCount[player] = floor(Random() * ((MAX_HAND - min) + 1) + min);
	  
      testState.whoseTurn = player;
      
	  //random testing set up 
	  //call 
	  
	  adventureTest(&testState, playerN);
	  
	  
    }
	
	

	//set up what should happen to gameState
	 
	 
	 //compare 
	
    return 0;

}