/*************************************************************
**Elizabeth May (mayel)
**04-29-2018
**cs362 - Assignment 3 - cardtest2.c
**Testing CUTPURSE
*****************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

/***************************
CUTPURSE
Action: +2 coins  Each other player discards a Copper (or reveals a hand with no Copper)
Cost: 4
http://wiki.dominionstrategy.com/index.php/Cutpurse

detailed action : +X – the player has X number of additional coins to spend in the Buy
phase. The player does not take additional Treasure cards for these coins.
*********************************/


int passCount = 0;
int failCount = 0;
int total = 0; 




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


    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 3;
    int thisPlayer = 0;
	struct gameState expState, testState;
	
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &testState);
	
	//set cutpurse as first card in players hand
	testState.hand[0][0] = cutpurse;
	//rest of hand does not matter for current player
	
	//set player #2 as having 2 coppers in hand
	testState.hand[1][0] = adventurer;
	testState.hand[1][1] = silver;
	testState.hand[1][2] = copper;
	testState.hand[1][3] = copper;
	testState.hand[1][4] = village;
	//set player #3 as having no coppers in hand
	testState.hand[2][0] = smithy;
	testState.hand[2][1] = silver;
	testState.hand[2][2] = gold;
	testState.hand[2][3] = silver;
	testState.hand[2][4] = mine;
	
	testState.whoseTurn = 0; //just in case
	
	
	
	printf("\n********************************************\n");
	printf("Card Test #2 - CUTPURSE");
	printf("\n********************************************\n");
	
	memcpy(&testState, &expState, sizeof(struct gameState));
	
	cardEffect(cutpurse, choice1, choice2, choice3, &testState, handpos, &bonus);
	
/*---------------------------------------
Test 1: Players coins should increase by 2 
----------------------------------------*/
	printf("\n CutPurse Test 1.1 - Player 1's coins should increase by 2:\n");
	assertState("coins", (expState.coins +2), testState.coins);
	
	
/*---------------------------------------
Test 2: Player 2 discard copper
----------------------------------------*/
	printf("\n CutPurse Test 1.2 - Player 2 should discard copper from hand:\n");		
	assertState("player #2 handCount", (expState.handCount[1] - 1), testState.handCount[1]);
	int i, copperCount;
	for(i =0; i < testState.handCount[1]; i++){
		if(testState.hand[1][i] == copper){
			copperCount++;
		} 
	}
	assertState("player #2 coppers in hand[]", 1, copperCount);
	assertState("player #2 discardCount", expState.discardCount[1] +1, testState.discardCount[1]);
	int discardLocation = expState.discardCount[1];
	if(testState.discard[1][discardLocation] != copper){
		printf("  Check discarded copper not other card - FAIL")
	}
	else{
		printf("  Check discarded copper not other card - PASS")
	}
		
/*---------------------------------------
Test 3: Player 3 reveal no coppers
----------------------------------------*/
	printf("\nCutPurse Test 1.3 - Player 3 reveal no coppers in hand:\n");		
	assertState("player #3 handCount[]", expState.handCount[2], testState.handCount[2]);
	int k; 
	copperCount = 0;
	for(k = 0; k < testState.handCount[2]; k++){
		if(testState.hand[2][k] == copper){
			copperCount++;
		}
	}
	assertState("player #3 coppers in hand", 0, copperCount);
	//printHand(&testState);
/*---------------------------------------
Test 4: Confirm GameState Correct
----------------------------------------*/
	printf("\nCardTest 1.4 - Confirm no other changes to GameStae:\n");		
	
	assertState("numBuys", expState.numBuys, testState.numBuys);
	
	int token = treasure_map + 1;
	int supplyErrors = 0;

	for(i = 0; i < token; i++){
		if(expState.supplyCount[i] != testState.supplyCount[i]){
			supplyErrors++;
		}
	}
	assertState("supplyCount[] Differences", 0, supplyErrors);
	if(supplyErrors > 0){
		printf("TestState:");
		//printSupply(&testState);
		printf("ExpState:");
		//printSupply(&expState);
	}
	int j;
	int deckErrors = 0;
	for(j = 0; j < numPlayers; j++){
		if(expState.deckCount[j] != testState.deckCount[j]){
			deckErrors++;
		}
	}
	assertState(" All Players DeckCount (No Errors)", 0, deckErrors);

	
	return 0;
}