/*************************************************************
**Elizabeth May (mayel)
**04-29-2018
**cs362 - Assignment 3 - cardtest4.c
**Testing SMITHY
*****************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

/*************************************
* SMITHY 
* Action: +3 cards
* Cost: 4 
*"+X Card(s)" – the player immediately draws X number of cards from his
Deck. If there are not enough cards in his Deck, he draws as many as he
can, shuffles the Discard pile to form a new Deck, and then draws the
rest. If he still does not have enough cards left after forming a new Deck,
he just draws as many as he can.
* http://wiki.dominionstrategy.com/index.php/Smithy
**************************************/
	

void assertTrue(int expected, int actual){
	
	if(expected == actual){
		printf("TEST PASSED: expected = %d, actual = %d.\n", expected, actual);
		
	}else{
		
		printf("TEST FAILED: expected = %d, actual = %d.\n", expected, actual);
	}
}

void assertState(char *ttest, int expected, int actual){
	
	if(expected == actual){
		printf("  Check %s: Expected %d, Returned %d -- PASS\n", ttest, expected, actual);
		
	}else{
		
		printf("  Check %s: Expected %d, Returned %d -- FAIL\n", ttest, expected, actual);
	}
	
}


int main(){
	//for comparison purposes will need 3 potential states : begin, test, expected
	struct gameState testState, expState;
	int kingdoms[10] = {adventurer, council_room, 
				 gardens, ambassador, cutpurse, 
				 sea_hag, smithy, village, 
				 embargo, outpost};
	int seed = 10;
	int numPlayers = 2;
	
	int A = 0; //player A
	int B = 1; //player B
	
	//setup game
	initializeGame(numPlayers, kingdoms, seed, &testState);
	
	//set hand 
	int testHand[5] = {smithy, adventurer, cutpurse, copper, gold};
	int handPos = 0; //smithy is 1st in hand 
	int i;

	for (i = 0; i < testState.handCount[A]; i++)
    {
        testState.hand[A][i] = testHand[i];
    }
	
	//save copy of gameState for future comparison
	memcpy(&expState, &testState, sizeof(struct gameState));
	
	//start of game there are no action cards so pile should have at least 11 cards 
	
	int choice1 = 0, choice2 = 0, choice3 = 0; 
	int bonus = 0; 
	
	int result = cardEffect(smithy, choice1, choice2, choice3, &testState, handPos, &bonus);

	
	//TEST 1 - handcount should be 7 (5 initial +3 new - 1 discard )
	printf("\nConfirm HandCount has increased by 3 cards:\n");
	int expHandCount = expState.handCount[A] + 3 - 1; 
	assertTrue(expHandCount, testState.handCount[A]);
	
	printf("\nConfirm hand no longer includes played smithy card:");
	if(testState.hand[A][handPos] == smithy){
		printf("TEST FAILED - Hand still contains played Smithy.\n");
		//printHand(&testState);
	}
	else{
		printf("TEST PASSED - Played smithy card removed from hand.\n");
		//printHand(&testState);
	}
	
	//discard pile should include at least 1 card (smithy)

	printf("\nConfirm discard pile includes used smithy card:\n");
	printf("  DiscardCount +1 - ");
	int expDiscardCount = expState.discardCount[A] + 1; 
	assertTrue(expDiscardCount, testState.discardCount[A]);
	printf("  Latest Discard is Smithy - ");
	int expDiscard = expState.discard[A][expDiscardCount - 1];
	assertTrue(expDiscard, testState.discard[A][testState.discardCount[A]-1]);
	//printDiscard(&testState);
	
	//deck should have 3 less cards (but if the deck was shuffled this will change things )
	printf("\nConfirm deck should have 3 less cards after playing smithy (shuffle check later):\n");
	assertTrue((expState.deckCount[A]-3),testState.deckCount[A]);
	
	//no change in other piles like supply
	printf("\nConfirm action only effected current player and not any other part of the gameState:\n");
	
	assertState("numBuys", expState.numBuys, testState.numBuys);
	
	int token = treasure_map + 1;
	
//supplyCount[treasure_map+1] LOOP
	int supplyErrors = 0;

	for(i = 0; i < token; i++){
		if(expState.supplyCount[i] != testState.supplyCount[i]){
			supplyErrors++;
		}
	}
	if(supplyErrors == 0 ){
		printf("	Check supplyCount[]: expected & returned match - PASS \n");
	}
	else{
		printf("	Check supply[]: expected & returned different - FAIL \n");
	}
	
	assertState("other player deck[]", expState.deckCount[B], testState.deckCount[B]);
	assertState("other player hand[]", expState.handCount[B], testState.handCount[B]);
	
	if( expState.deckCount[B] != testState.deckCount[B]){
		printf("   Check otherPlayer deck[]: expected ");
	}
	

	
	return 0; 
	
	
	
}

