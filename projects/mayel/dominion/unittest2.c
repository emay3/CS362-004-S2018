/*************************************************************
**Elizabeth May (mayel)
**4-29-2018
**cs362 - Assignment 3 - unittest2.c
** Testing : isGameOver()
*****************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


#define IS_OVER 1
#define NOT_OVER 0 
 
//global variables 

int passCount = 0;
int failCount = 0;
int total = 0; 



void assertTrue(int expected, int actual){
	
	/*
	if(expected == 1){ X = "Game Over";}
	else{ X = "Game Not Over"; }
	if(actual == 1){ Y = "Game Over"; }
	else{ Y = "Game Not Over"; }
	*/
	if(expected == actual ){
		//printf("PASS ");
		printf("Expected: %d, Actual: %d - PASS\n", expected, actual);
		passCount++;
		return;
	}
	else{
		//printf("FAIL ");
		printf("Expected: %d , Actual: %d - FAIL\n", expected, actual);
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
	struct gameState testState, expState; 
	
	int seed = 1000;
	int numPlayers = 2;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	initializeGame(numPlayers, k, seed, &testState);
	memcpy(&testState, &expState, sizeof(struct gameState));
	//copy testState to expState to confirm game state not changed other than how we want it
	
	printf("\n********************************************\n");
	printf("Unit Test #2 - isGameOver()");
	printf("\n********************************************\n");
	
	int result; //test result 
	
/*---------------------------------------
Test 1: Game just began & is not over
----------------------------------------*/
	printf("\nUnitTest 2.1 - Game has just started:\n");
	
	result = isGameOver(&testState);	
	
	assertTrue(NOT_OVER, result);


/*-------------------------------------
Test 2: GameState is Not Changed
		isGameOver does effect anything
--------------------------------------*/
	printf("\nUnitTest 2.2 - isGameOver() does not change gameState, only checks it: \n");
	
	assertState("handCount(s)", expState.handCount[0], testState.handCount[0]);
	assertState("deckCounts(s)", expState.deckCount[1], testState.deckCount[1]);
	
	int token = treasure_map + 1;
	int supplyErrors = 0;
	int i;
	for(i = 0; i < token; i++){
		if(expState.supplyCount[i] != testState.supplyCount[i]){
			supplyErrors++;
		}
	}
	assertState("supplyCount[] Differences", 0, supplyErrors);
	assertState("whoseTurn", expState.whoseTurn, testState.whoseTurn);
	
	
	
/*--------------------------------------
Test 3: Province pile is only empty pile
---------------------------------------*/
	
	//make changes to testState so 0 province cards
	testState.supplyCount[province] = 0;
	
	
	printf("\nUnitTest 2.3 - Zero Province Cards:\n");
	result = isGameOver(&testState);
	assertTrue(IS_OVER, result);

/*-------------------------------------
Test 4: 3 Supply Piles are Empty (simple)
--------------------------------------*/
	//province back to full 
	testState.supplyCount[province] = 8; 

	//make 3 suply piles zero the beg mid end
	testState.supplyCount[duchy] = 0;
	testState.supplyCount[copper] = 0;
	testState.supplyCount[curse] = 0; 
	
	
	printf("\nUnitTest 2.4 - 3 Supply Piles Empty:\n");
	result = isGameOver(&testState);
	assertTrue(IS_OVER, result);


/*-------------------------------------
Test 5: Supply has 2 empty piles & Province pile 1 card away from empty
--------------------------------------*/
	
	//make changes 
	testState.supplyCount[duchy] = 8;
	testState.supplyCount[copper] = 8;
	testState.supplyCount[curse] = 6;
	testState.supplyCount[province] = 1;
	testState.supplyCount[estate]= 0;
	testState.supplyCount[silver] = 0;
	
	
	printf("\nUnitTest 2.5 - Supply has 2 empty piles & Province pile is 1 card away from empty:\n");
	result = isGameOver(&testState);
	assertTrue(NOT_OVER, result);


	 
	printf("\n---------------------------------------------------\n");
	printf("Unit Test #2 Summary: isGameOver failed %d tests & passed %d tests.", failCount, passCount);
	
	
	return 0;
	
}
