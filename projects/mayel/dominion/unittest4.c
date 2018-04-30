/*************************************************************
**Elizabeth May (mayel)
**4-29-2018
**cs362 - Assignment 3 - UnitTest4.c
** Testing : gainCard()
*****************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define gainOK 0;
#define gainBAD -1; 
 
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
	
}
int main(){
	
	
	//initialize game 
	struct gameState testState, expState, deckState, discardState; 
	
	int seed = 1000;
	int numPlayers = 2;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	initializeGame(numPlayers, k, seed, &testState);
	
	//copy testState to expState to confirm game state not changed other than how we want it
	
	printf("\n********************************************\n");
	printf("Unit Test #4 - gainCard()  ");
	printf("\n********************************************\n");
	
	int result; //test result 
	
	
/*-------------------------------------
Test 1: GainCard from Empty Supply (to Hand)
--------------------------------------*/
	printf("\n UnitTest 4.1 - GainCard to Hand, but Empty Supply\n");
	
	testState.supplyCount[gold] = 0;
	
	result = gainCard(gold, &testState, 2, 0);	
	
	if(result == 0){
		printf("Expected: -1 Error , Returned: OK - FAIL\n");
		failCount++;
	}
	else if(result == -1){
		printf("Expected: -1 Error, Returned: -1 Error - PASS\n");
		passCount++;
	}
	else{
		printf("Expected: -1 Error, Returned: Other - FAIL\n");
		failCount++;
	}
	

	
/*---------------------------------------
Test 2: GainCard from Full Supply (to Hand)
----------------------------------------*/
	printf("\UnitTest 4.2 - GainCard from Full Supply to Hand\n");
	
	testState.supplyCount[gold] = 5;
	memcpy(&testState, &expState, sizeof(struct gameState));
	
	result = gainCard(estate, &testState, 2, 0);	
	if(result == 0){
		printf("-- gainCard() function completed, now checking returned gameState...");
		
		assertState("supplyCount", expState.supplyCount[estate] -1, testState.supplyCount[estate]);
		assertState("handCOunt", expState.handCount[0] +1, testState.handCount[0]);
		assertState("other player hand", expState.handCount[1], testState.handCount[1]);
		
	}
	else{
		printf("Error moving card to hand - FAIL\n");
		failCount++;
	}

	 
	
/*--------------------------------------
Test 3: GainCard to Deck, Check Game State
---------------------------------------*/
	printf("\UnitTest 4.3 - GainCard to Deck, :\n");
	
	memcpy(&testState, &deckState, sizeof(struct gameState));
	result = gainCard(estate, &testState, 2, 1);
	if(result != 0){
		printf("Error moving card to deck - FAIL\n");
		failCount++;
	}
	else{
			assertState("deckCount", deckState.deckCount[1] +1, testState.deckCount[1]);
			assertState("supplyCount updated", deckState.supplyCount[estate] -1, testState.supplyCount[estate]);
			assertState("other player hand", deckState.handCount[0], testState.handCount[0]);
	}
/*-------------------------------------
Test 4: GainCard to Discard, Check Game State
--------------------------------------*/
	
	printf("\UnitTest 4.4 - GainCard to Discard\n");
	memcpy(&testState, &discardState, sizeof(struct gameState));
	result = gainCard(silver, &testState, 0, 1);
	if(result != 0){
		printf("Error moving card to discard - FAIL\n");
		failCount++;
	}
	else{
		printf("Checking gameState...\n");
		assertState("discardCount", discardState.discardCount[1] +1, testState.discardCount[1]);
		assertState("supplyCount updated", deckState.supplyCount[silver] -1, testState.supplyCount[silver]);
		
		assertState("discard[] now includes silver on top", silver, testState.discard[1][testState.discardCount[1]-1] );
		assertState("other player hand", deckState.handCount[0], testState.handCount[0]);
	}




/*-------------------------------------
Summary 
--------------------------------------*/	
	printf("\n---------------------------------------------------\n");
	printf("Unit Test #4 Summary:  gainCard() failed %d tests & passed %d tests.", failCount, passCount);
	
	
	return 0;
	
}