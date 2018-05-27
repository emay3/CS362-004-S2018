/*************************************************************
**Elizabeth May (mayel)
**4-29-2018
**cs362 - Assignment 3 - UnitTest3.c
** Testing : drawCard()
*****************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
 
//global variables 

int passCount = 0;
int failCount = 0;
int total = 0; 


/*
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
*/


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
}
	
int main(){
	
	
	//initialize game 
	struct gameState testState, expState, otherState; 
	
	int seed = 1000;
	int numPlayers = 2;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	initializeGame(numPlayers, k, seed, &testState);
	
	memcpy(&expState, &testState, sizeof(struct gameState));
	
	//copy testState to expState to confirm game state not changed other than how we want it
	
	printf("\n********************************************\n");
	printf("Unit Test #3 - drawCard()");
	printf("\n********************************************\n");
	
	int result; //test result 
	
	//int drawCard(int player, struct gameState *state)
	
/*---------------------------------------
Test 1: Draw Card w/ Full Deck (Begin of Game)
----------------------------------------*/
	printf("\nUnitTest 3.1 - DrawCard() w/ Full Deck\n");
	
	result = drawCard(0, &testState);
	//int drawCard(int player, struct gameState *state);	
	
	//if(result == 0){
		//printf("drawCard() function complete, testing game state...\n");
		assertState("result", 0, result);		

		assertState("handCount", expState.handCount[0] + 1, testState.handCount[0]);
		assertState("deckCount", expState.deckCount[0] -1, testState.deckCount[0]);
		assertState("discardCount", expState.discardCount[0], testState.discardCount[0]);
		
		int loc = expState.deckCount[0];
		int loc2 = testState.handCount[0];
		assertState("correct top card moved", expState.deck[0][loc-1], testState.hand[0][loc2 -1]);
	
	int tE = expState.deckCount[0] + expState.handCount[0] + expState.discardCount[0];
	int tT = testState.deckCount[0]+ testState.handCount[0] + testState.discardCount[0];
	
	assertState("total cards discard+hand+deck", tE, tT); 	

/*-------------------------------------
Test 2: Draw Card w/ Empty Deck 
--------------------------------------*/
	printf("\nUnitTest 3.2 - Draw Card from Empty Deck - Shuffle \n");
	
	int i;
	int discardAdd = testState.discardCount[0];
	printf("\n Print hand,deck,discard before drawcard: \n");


		
	//adding a few new cards to the discard to make sure discard has stuff to move
	testState.discard[0][discardAdd] = silver;
	testState.discard[0][discardAdd +1] = minion; 
	testState.discard[0][discardAdd +2] = copper;

	int expDeck = testState.discardCount[0] + 3;
	testState.discardCount[0] = expDeck; //correcting the discard count that i adjusted 
	

	//empty deck, count & cards 
	for(i = 0; i < testState.deckCount[0]; i++){
		testState.deck[0][i] = -1;
	}
	testState.deckCount[0] = 0;

	 memcpy(&otherState, &testState, sizeof(struct gameState));


        printDeck(0, &testState);
        printHand(0, &testState);
        printDiscard(0, &testState);

	//expect discard to be shuffled and zero
	//otherState.discardCount[0] = 0;

	result = drawCard(0, &testState);

	assertState("result", 0, result);
	assertState("handCount", otherState.handCount[0]+1, testState.handCount[0]);
	assertState("deckCount", expDeck-1, testState.deckCount[0]);
	assertState("discardCount", 0, testState.discardCount[0]);

	
	int totalCardsE = otherState.handCount[0] + otherState.deckCount[0] + otherState.discardCount[0];
	int totalCardsT = testState.handCount[0] + testState.deckCount[0] + testState.discardCount[0];

	
	
	assertState("total discard+hand+deck", totalCardsE, totalCardsT);
	printf("\n exp hand count: %d, deck: %d, discard: %d \n", otherState.handCount[0], otherState.deckCount[0], otherState.discardCount[0]);	

	
	printf("\n Print after drawCard() :\n");
	printDeck(0, &testState);
	printHand(0, &testState);
	printDiscard(0, &testState);	

/*--------------------------------------
Test 3: Both Deck & Discard Pile Are Empty
---------------------------------------*/
	
	printf("\nScenario 3.3 - Both Deck & Discard Piles Are Empty:\n");
	testState.deckCount[0] = 0;
	testState.discardCount[0] = 0; 
	
	result = drawCard(0, &testState);
	
	assertState("result error", -1, result);
	
	//assertTrue( -1, result);

/*-------------------------------------
Test 4: Confirm Other Player (2) not changed
--------------------------------------*/
	
	printf("\nUnitTest 3.4 - Confirm  Other Player (2) & State not changed\n");
	
	assertState("player2 handCount", expState.handCount[1], testState.handCount[1]);
	assertState("Player2 deckCount", expState.deckCount[1], testState.deckCount[1]);
	assertState("player2 discardCount", expState.discardCount[1], testState.discardCount[1]);
	//assertState("supplyCount", expState.supplyCount, testState.supplyCount);
	assertState("whoseTurn", expState.whoseTurn, testState.whoseTurn);
	assertState("numActions", expState.numActions, testState.numActions);
	
	
	
/*-------------------------------------
Summary 
--------------------------------------*/	
	printf("\n---------------------------------------------------\n");
	printf("Unit Test #3 Summary: drawCard() failed %d tests & passed %d tests.", failCount, passCount);
	
	
	return 0;
	
}
