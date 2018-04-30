/*************************************************************
**Elizabeth May (mayel)
**10-22-2017
**cs362 - Assignment 2 - cardtest3.c
**Testing Adventurer
*****************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

/**************************
ADVENTURER
Action: Reveal cards from your deck until you reveal 2 Treasure cards. Put those Treasure cards into your hand and discard the other revealed cards.
Cost: 6
http://wiki.dominionstrategy.com/index.php/Adventurer
******************************/


void assertTrue(int expected, int actual){
	
	if(expected == actual){
		printf("TEST PASSED: expected = %d, actual = %d.\n", expected, actual);
		
	}else{
		
		printf("TEST FAILED: expected = %d, actual = %d.\n", expected, actual);
	}
}

/************************
* ADVENTURE TEST
************************/

int main(){
	
	
	printf("Testing  ADVENTURER :\n"); 

  int k[10] = {adventurer, council_room, gardens, ambassador, cutpurse, remodel, smithy, village, embargo, outpost};
  
  struct gameState curState, prevState;
  int numPlayers = 4;
  int seed = 10;
  int discardCount = 1;
  int drawCount = 2;
  int choice1 = 0, choice2 = 0, choice3 = 0;
  int handPos = 4;
  int bonus;

  
	initializeGame(numPlayers, k, seed, &curState);
	/*set the fifth card in player 1's hand to be adventurer, top 3 cards in 
	 * player 1's deck to non-treasure cards, last 2 to be treasure, and save to prevState*/
	curState.hand[0][1] = adventurer; //make sure current hand is what we want to test
	curState.deck[0][1] = adventurer;
	
	//set other deck cards:
	curState.deck[0][3] = adventurer;
	curState.deck[0][2] = adventurer;
	curState.deck[0][4] = copper;
	curState.deck[0][0] = copper;
	
	//save game state for comparison 
	memcpy(&prevState, &curState, sizeof(struct gameState));
	
/*******
*Test 1 - 
*******/
	cardEffect(adventurer, choice1, choice2, choice3, &curState, handPos, &bonus);
	
	printf("Adventure Test 1: 1st player  hand count increased by 2 after adventurer played, expected hand size 6 (after discarding adventurer).\n");
	assertTrue(prevState.handCount[0] + drawCount - discardCount, curState.handCount[0]);
	
/*******
*Test 2 - 
*******/
	
	printf("TESTING player 1's deck count decreased by 2 drawn + 3 non-treasure after adventurer played, expected deck size 0.\n");
	assertTrue(prevState.deckCount[0] - drawCount - 3, curState.deckCount[0]);
/*******
*Test 3 - 
*******/	
	
	printf("TESTING the 2 cards added by adventurer were the bottom 2 cards of the previous deck.\n");
	//discard mechanic in dominion.c works by replacing the last card in hand with the discarded position, hence the ordering
	assertTrue(prevState.deck[0][0], curState.hand[0][4]);
	assertTrue(prevState.deck[0][1], curState.hand[0][5]);
	
/*******
*Test 4 - 
*******/
	printf("TESTING player 1's discard count increased by 3 after adventurer played, expected size 3.\n");
	assertTrue(prevState.discardCount[0] + 3, curState.discardCount[0]);
	printf("TESTING no changes in victory or kingdom card supplies.\n");
	
	int i; 
	for(i = curse; i < treasure_map; i++){
		assertTrue(prevState.supplyCount[i], curState.supplyCount[i]);
	}
	printf("TESTING no state changes occured in other players.\n\n");
	printf("TESTING each other player's discard count remained the same.\n");
	for(i = 1; i < 4; i++){
		assertTrue(prevState.discardCount[i], curState.discardCount[i]);
	}
	printf("TESTING each card in each other player's discard pile is the same.\n");
	
	int j;
	for(i = 1; i < 4; i++){
		for(j = 0; j < prevState.discardCount[i]; j++){
			assertTrue(prevState.discard[i][j], curState.discard[i][j]);
		}
	}
	printf("TESTING each other player's hand count remained the same.\n");
	for(i = 1; i < 4; i++){
		assertTrue(prevState.handCount[i], curState.handCount[i]);
	}
	printf("TESTING each card in each other player's hand is the same.\n");
	for(i = 1; i < 5; i++){
		for(j = 0; j < prevState.handCount[1]; j++){
			assertTrue(prevState.hand[1][j], curState.hand[1][j]);
		}
	}
	printf("TESTING each other player's deck count remained the same.\n");
	for(i = 1; i < 4; i++){
		assertTrue(prevState.deckCount[i], curState.deckCount[i]);
	}
	printf("TESTING each card in each other player's deck is the same.\n");
	for(i = 1; i < 4; i++){
		for(j = 0; j < prevState.deckCount[i]; j++){
			assertTrue(prevState.deck[i][j], curState.deck[i][j]);
		}
	}

  }

	return 0;
	

	
}