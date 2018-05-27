#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>


void assertSupply(struct gameState *exp, struct gameState *test);
void assertState(char **ttest, int expected, int actual);
void randomizeGame(struct gameState *g, int seed);


int passCount = 0; 
int failCount = 0;

int main(){
	
	printf("\n***********RandomTester Adventure Card *************\n");
	
	int ITERATIONS_LIMIT = 2000;

	int test; 
	int iteration = 0;
	int next = 0;
	int seed = 1000;
	
	
	struct gameState testState, expState;
	int position; 
	int player; 
	int numPlayers; 
	
	srand(time(NULL));
	

	for(iteration = 0; iteration < ITERATIONS_LIMIT; iteration++){
		
		printf("\nIteration %d :\n", iteration+1);
		//since this is a loop we need to reset game states each time;
		memset(&testState, 23, sizeof(struct gameState));
		memset(&expState, 23, sizeof(struct gameState));
		//random number of players

		//establish random game state
		randomizeGame(&testState, seed);
		
		//save a few quick grab variabls
		numPlayers = testState.numPlayers; 
		player = testState.whoseTurn; 
		
		//make sure unique to tested card is put in play position
		position = rand() % (testState.handCount[player]);
		game.hand[player][position] = adventurer; 
		
		//copy starting point for comparison
		memcpy(&expState, &testState, sizeof(struct gameState));
		
		
		int result;
		int choice1, choice2, choice3 = 0;
		
		//TEST 
		
		result = cardEffect(adventurer, choice1, choice2, choice3, &testState, position, 0);
		
		//test 1: cardEffect returned without error
		assertState("cardEffect adventure returned", 0, result);
		//test 2: current player has 2 new cards in hand 
		assertState("current player has 2 new cards in handCount[]", expState.handCount[player]+2, testState.handCount[player]);
		
		//test 3: check those 2 new cards are treasure cards only 
		int x = testState.handCount[player];
		int t1 = testState.hand[player][x-1];
		int t2 = testState.hand[player][x-2];
		if(t1 == gold || t1 == silver || t1 == copper){
			assertState(" newly gained card[1] is treasure", 4, 4);
		}
		else{
			assertState("newly gained card[1] is treasure", 4, t1);
		}
		if(t2 == gold || t2 == silver || t2 == copper){
			assertState("newly gained card[2] is treasure", 4, 4);
		}
		else{
			assertState("newly gained card[2] is treasure", 4, t2);
		}
		
		
		
		//test 4: player discarded adventure card
		int d = testState.discardCount[player];
		assertState("current player discarded played adventurer card", adventurer, testState.discard[player][d]);
		
		//test 5: no cards have gone missing from deck, hand, discard piles
		int cardsE = expState.handCount[player] + expState.deckCount[player] + expState.discardCount[player]; 
		int cardsT = testState.handCount[player] + testState.deckCount[player] + testState.discardCount[player]; 
		assertState("current player deck+hand+discard same", cardsE, cardsT);
		
		//test 6: other player
		char buffer[25];
		int p; //whose turn should be player 0 so start at 1  
		for( p = 1; p < = numPlayers; p++){
			
			memset(buffer, '\0', sizeof(buffer));
			sprintf(buffer, "player %d handCount[]", p);
			assertState(buffer, expState.handCount[p], testState.handCount[p]);
			
			memset(buffer, '\0', sizeof(buffer));
			sprintf(buffer, "player %d deckCount[]", p);
			assertState(buffer, expState.deckCount[p], testState.deckCount[p]);
			
			memset(buffer, '\0', sizeof(buffer));
			sprintf(buffer, "player %d discardCount[]", p);
			assertState(buffer, expState.discardCount[p], testState.discardCount[p]);
			
		}
		
		//test 7: supply has not changed
		assertSupply(&expState, &testState);

	}
	
	printf("\n********* Adventurer RandomTest Summary: ***********");
	printf("\n Adventure card completed %d tests.", iteration);
	printf("\n Total passing tests = %d", passCount);
	printf("\n Total failed tests = %d", failCount);
	printf("\n*****************************************************\n");


return 0;

}

void assertSupply(struct gameState *exp, struct gameState *test){
	
	int i;
	char sc[30]; 
	for(i = 0; i < treasure_map+1; i++){
		
		memset(sc, 0, sizeof(sc));
		sprintf(sc, "supply count [ %d ]", i);
		assertState(sc, exp->supplyCount[i], test->supplyCount[i]);
	}
	
}

void assertState(char **ttest, int expected, int actual){

	if(expected == actual){
		//should only print failures for random tester or too much info. 
		//printf("  Check %s: Expected %d, Returned %d -- PASS\n", ttest, expected, actual);
		 passCount++;
	}
	else{
		printf("Checked %s: Expected %d, Returned %d -- FAIL\n", ttest, expected, actual);
		failCount++;
	}

}

void randomizeGame(struct gameState *g, int seed){

	int numPlayers;
	int kingdomCards[10] = {adventurer, council_room, feast, village, smithy, baron, great_hall, mine, remodel, gardens};
	
	
	numPlayers = rand() %3 + 2; 

	initializeGame(numPlayers, kingdomCards, seed, g);
	

	//for each player set random player hands, decks, discard etc.
	
	int p;
	for(p = 0; p < numPlayers; p++){
		
		//set deck
		g->deckCount[p] = rand() % 26 + 5;
		int card; 
		for(card = 0; card < g->deckCount[p]; card++){
			g->deck[p][card] = kingdomCards[ rand() % 10];
			//switch out with treasure card occassionally
			if(rand() % 5 == 1){
				g->deck[p][card] = rand() % 3 + 4; 
			}
		}
	
		//set hand
		g->handCount[p] = rand() % 8 + 3; 
		for(card = 0; card < g->handCount[p]; card++){
			g->hand[p][card] = kingdomCards[rand() % 10];
			if(rand() % 5 == 2){
				g->hand[p][card] = rand() % 3 + 4; 
			}
		}
		
		//set discard
		g->discardCount[p] = rand() % 8 + 3; 
		for(card = 0; card < g->discardCount[p]; card++){
			g->discard[p][card] = kingdomCards[rand() % 10];
			if(rand() % 5 == 3){
				g->discard[p][card] = rand() % 3 + 4; 
			}
		}

	}//end each player loop
	
}