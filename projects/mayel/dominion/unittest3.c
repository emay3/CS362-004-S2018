/*************************************************************
**Elizabeth May (mayel)
**4-29-2018
**cs362 - Assignment 3 - UnitTest3.c
** Testing : drawCard()
*****************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>



//global variables 

int passCount = 0;
int failCount = 0;
int total = 0; 



void assertTrue(int expected, int actual){
	
	if(expected == actual ){
		//printf("PASS ");
		printf("Expected: %s, Actual: %s - PASS\n", X, Y );
		passCount++;
		return;
	}
	else{
		//printf("FAIL ");
		printf("Expected: %d , Actual: %d - FAIL\n", X, Y);
		failCount++;
		return;
	}
}

void assertState(char *ttest, int expected, int actual){
	
	if(expected == actual){
		printf("  Check %s: Expected %d, Returned %d -- PASS\n", ttest, expected, actual);
		passCount++;
		return;
		
	}else{
		
		printf("  Check %s: Expected %d, Returned %d -- FAIL\n", ttest, expected, actual);
		failCount++;
		return;
	}
	
int main(){
	
	
	//initialize game 
	struct gameState testState, expState; 
	
	int seed = 1000;
	int numPlayers = 2;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	initializeGame(numPlayers, k, seed, &testState);
	
	memcpy(&testState, &expState, sizeof(struct gameState));
	
	//copy testState to expState to confirm game state not changed other than how we want it
	
	printf("\n********************************************\n");
	printf("Unit Test #3 - drawCard()");
	printf("\n********************************************\n");
	
	int result; //test result 
	
	//int drawCard(int player, struct gameState *state)
	
/*---------------------------------------
Test 1: Draw Card w/ Full Deck (Begin of Game)
----------------------------------------*/
	printf("\UnitTest 3.1 - DrawCard() w/ Full Deck\n");
	
	result = drawCard(0, &testState);
	//int drawCard(int player, struct gameState *state);	
	
	if(result == 0){
		printf("drawCard() function complete, testing game state...\n");
		
		assertState("handCount", expState.handCount[0] + 1, testState.handCount[0]);
		assertState("deckCount", expState.deckCOunt[0] -1, testState.deckCount[0]);
		
		int loc = expState.deckCount[0];
		int loc2 = testState.handCount[0];
		assertState("correct top card moved", expState.deck[0][loc-1], testState.hand[0][loc2 -1]);
		
		passCount++;
	}
	else{
		
		printf("Error - Could not draw card from full deck - FAIL");
		failCount++;
	}

/*-------------------------------------
Test 2: Draw Card w/ Empty Deck 
--------------------------------------*/
	printf("\nUnitTest 3.2 - Draw Card from Empty Deck - Shuffle \n");
	
int i;
int discardAdd = testState.discardCount[0];

//adding a few new cards to the discard to make sure discard has stuff to move
testState.discard[0][discardAdd] = silver;
testState.discard[0][discardAdd +1] = minion; 
testState.discard[0][discardAdd +2] = copper;

for(i = 0; i < testState.deckCount[0]; i++){
	testState.deck[0][i] = -1;
}
testState.deckCount[0] = 0;
	

	result = drawCard(0, &testState);
	assertState("handCount", expState.
	
/*--------------------------------------
Test 3: Both Deck & Discard Pile Are Empty
---------------------------------------*/
	
	printf("\nScenario 3.3 - Both Deck & Discard Piles Are Empty:\n");
	testState.deckCount[0] = 0;
	testState.discardCount[0] = 0; 
	
	result = drawCard(0, &testState);
	

	assertTrue( -1, result);

/*-------------------------------------
Test 4: Confirm Other Player (2) not changed
--------------------------------------*/
	
	printf("\nUnitTest 3.4 - Confirm Other Player (2) not changed\n");
	
	assertState("player2 handCount", expState.handCount[1], testState.handCount[1]);
	assertState("Player2 deckCount", expState.deckCount[1], testState.deckCount[1]);
	assertState("player2 discardCount", expState.discardCount[1], testState.discardCount[1]);
	
	
	
/*-------------------------------------
Summary 
--------------------------------------*/	
	printf("\n---------------------------------------------------\n");
	printf("Unit Test #3 Summary: drawCard() failed %d tests & passed %d tests.", failCount, passCount);
	
	
	return 0;
	
}
