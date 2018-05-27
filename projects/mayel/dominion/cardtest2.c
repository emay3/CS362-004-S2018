/*************************************************************
**Elizabeth May (mayel)
**04-29-2018
**cs362 - Assignment 2 - cardtest1.c 
** Testing SEA_HAG 
*****************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "seahag"

/**************************
SEA HAG
Action: Each other player discards the top card of their deck, then gains a Curse onto their deck.
Cost: 4
http://wiki.dominionstrategy.com/index.php/Sea_Hag
*****************************/


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


	struct gameState curState, testState;
	int k[10] = {adventurer, council_room, embargo, village, minion, mine,
        cutpurse, sea_hag, tribute, smithy};
	
    int newCards = 0;
    int xtraCoins = 0;
    int discarded = 1;
    int seed = 10;
    int numPlayers = 2;


    int failFlag = 0;
    int passedTests = 0;
    int totalTests = 0;
    int testHand[5] = {smithy, adventurer, minion, sea_hag, gold};
    int handPos = 3;
	int choice1 = 0, choice2 = 0, choice3 = 0;
	int bonus = 0;

    // initialized game
    initializeGame(numPlayers, k, seed, &curState);
    // load test hand
    int i;
   for (i = 0; i < curState.handCount[0]; i++)
    {
        curState.hand[0][i] = testHand[i];
    }

/********
* Test: 1: Gain two coins
**********/	

    printf("Sea Hag Action: All other players discard the top of their deck and a curse is placed on the top of their deck then discard Sea Hag - Card %d\n", sea_hag);
	
	// copy the game state to a test case
	memcpy(&testState, &curState, sizeof(struct gameState));
	cardEffect(sea_hag, choice1, choice2, choice3, &testState, handPos, &bonus);
	
	
/********
* Test: Deck count 
**********/
    totalTests++;

    int exp = curState.deckCount[0] + curState.discardCount[0] - newCards;
	int actl = testState.deckCount[0] + testState.discardCount[0];
	assertTrue(exp, actl);

/*********
* Test: Hand count - discarded
**********/

    totalTests++;
	assertTrue((curState.handCount[0] + newCards - discarded), testState.handCount)



/********
* Test: Played cards + 1
**********/

    totalTests++;
	assertTrue((curState.playedCardCount + numPlayers - 1 + discarded) , testState.playedCardCount );
	
/********
* Test: Played card is Minion
**********/

    printf("Played card: Previous = %d, Current = %d, Expected = %d", curState.playedCards[0], testState.playedCards[0], sea_hag);
    totalTests++;
	
	assertTrue( sea_hag , testState.playedCards[0]);
	
/********
* Test: Check coins -
**********/
    // Test: 
    printf("Coin count: Previous = %d, Current = %d, Expected = %d", curState.coins, testState.coins, curState.coins + xtraCoins);
    totalTests++;
	
	assertTrue((curState.coins + xtraCoins), testState.coins); 


    printf("Previous hand: ");
    for (i = 0; i < curState.handCount[0]; i++)
        printf("%d ", curState.hand[0][i]);
    printf("Current hand: ");
    for (i = 0; i < testState.handCount[0]; i++)
        printf("%d ", testState.hand[0][i]);
    printf("\n");
	
	
/********
* Test: State of play - no change in hand
**********/
    printf("Checking other players...\n");
    totalTests++;
	assertTrue(curState.handCount[1], testState.handCount[1])



/********
* Test: State of play - deckCount 
**********/	
    totalTests++;
	assertTrue((curState.deckCount[1] + curState.discardCount[1]), (testState.deckCount[1] + testState.discardCount[1]));
	
/********
* Test: Last Discard match
**********/	
   
	
/********
* Test: 
**********/	

	
/********
* Test: No change to victory and kingdom piles
**********/


/********
* Test: did Fail  
**********/	
    printf("Supply piles did not change");
	assertTrue(0, failFlag);
	

    printf("Tests Passed: %d out of %d\n", passedTests, totalTests);

	return 0;
	
}
