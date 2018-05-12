// intensity.c
// Assignment 2, COMP1511 18s1: Intensity
//
// This program by Dheeraj Viswanadham (z5204820)
//
// Started: 18/04/2018 | Last edited: 07/05/2018
//
// Version 1.0.1: Minor changes to wording of comments.
// Version 1.0.0: Assignment released.

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// SOME USEFUL #defines - YOU WILL NEED MORE

#define ACTION_PLAYER_NAME    0
#define ACTION_DISCARD        1
#define ACTION_PLAY_CARD      2
#define ACTION_UNIT_TESTS     3

#define N_CARDS              40
#define N_CARDS_INITIAL_HAND 10
#define N_PLAYERS             4
#define N_CARDS_DISCARDED     3

#define CARD_MIN             10
#define CARD_MAX             49


// ADD EXTRA #defines HERE
#define MAX_FIRST_DIGIT_RANGE 10
#define BUFFALO 47
#define CARDS_TRANSITIONED 3

void print_player_name(void);
void choose_discards(void);
void choose_card_to_play(void);
void run_unit_tests(void);

// ADD PROTOTYPES FOR YOUR FUNCTIONS HERE

int first_digit_one(int deck[N_CARDS_INITIAL_HAND], int ones_deck[MAX_FIRST_DIGIT_RANGE]);
int first_digit_two(int deck[N_CARDS_INITIAL_HAND], int twos_deck[MAX_FIRST_DIGIT_RANGE]);
int count_calves_deck(int deck[N_CARDS_INITIAL_HAND], int calves_deck[MAX_FIRST_DIGIT_RANGE]);
int first_digit_four(int deck[N_CARDS_INITIAL_HAND], int fours_deck[MAX_FIRST_DIGIT_RANGE]);


// You should not need to change this main function

int main(void) {

	int which_action = 0;
	scanf("%d", &which_action);
	if (which_action == ACTION_PLAYER_NAME) {
		print_player_name();
	} else if (which_action == ACTION_DISCARD) {
		choose_discards();
	} else if (which_action == ACTION_PLAY_CARD) {
		choose_card_to_play();
	} else {
		run_unit_tests();
	}
	
	return 0;
}

void print_player_name(void) {
	printf("A2.V1\n");
}

void choose_discards() {
	int cards_discarded[N_CARDS_DISCARDED] = {0};
	int total_discards = 0;
	
	int ones_deck[MAX_FIRST_DIGIT_RANGE] = {0};   	//
	int number_of_ones_deck = 0;  	// - For ones_deck
	int total_ones_deck = 0;    	//
	

	int twos_deck[MAX_FIRST_DIGIT_RANGE] = {0};   	//
	int number_of_twos_deck = 0;  	// - For twos_deck
	int total_twos_deck = 0;    	//
	
	int calves_deck[MAX_FIRST_DIGIT_RANGE] = {0}; 	//
	int number_of_calves_deck = 0;	// - For calves_deck
	int total_calves_deck = 0;  	//
	
	int fours_deck[MAX_FIRST_DIGIT_RANGE] = {0};  	//
	int number_of_fours_deck = 0; 	// - For fours_deck
	int total_fours_deck = 0;   	//
	
	int count_suits = 4;
	int minimum_num = 9;
	
	int deck_of_cards[N_CARDS_INITIAL_HAND];
	int count_cards = 0;
	
	while (count_cards < N_CARDS_INITIAL_HAND) {
		scanf("%d", &deck_of_cards[count_cards]); // Scans each card from stdin into AI's deck

		count_cards = count_cards + 1;
	}
	
	count_cards = 0;
	
	total_ones_deck = first_digit_one(deck_of_cards, ones_deck);
	total_twos_deck = first_digit_two(deck_of_cards, twos_deck);
	total_calves_deck = count_calves_deck(deck_of_cards, calves_deck);
	total_fours_deck = first_digit_four(deck_of_cards, fours_deck);
	
	while(total_discards < 3) {
		if (total_fours_deck > 3) {
			
			count_cards = 49;
			number_of_fours_deck = 0;
			
			while(40 <= count_cards && count_cards != BUFFALO && total_discards < 3
				  && total_fours_deck > 3) { // Want to keep buffalo
				
				if (fours_deck[number_of_fours_deck] == count_cards) { // Discarding high cards, starting at 49
				
					cards_discarded[total_discards] = fours_deck[number_of_fours_deck];
					fours_deck[number_of_fours_deck] = 0; // Ensures no double counting
					number_of_fours_deck++;
					total_discards++;
				}
				
				count_cards = count_cards - 1;
			}
			
		} else if (total_calves_deck > 3) {
			
			count_cards = 39;
			number_of_calves_deck = 0;
			
			while(30 <= count_cards && total_discards < 3 && total_calves_deck > 3) {
				if (calves_deck[number_of_calves_deck] == count_cards) {
					
					cards_discarded[total_discards] = calves_deck[number_of_calves_deck];
					calves_deck[number_of_calves_deck] = 0;
					number_of_calves_deck++;
					total_discards++;
				}
				
				count_cards = count_cards - 1;
			}
			
		} else if (total_twos_deck > 3) {
			
			count_cards = 29;
			number_of_twos_deck = 0;
			
			while(20 <= count_cards && total_discards < 3 && total_twos_deck > 3) {
				if (twos_deck[number_of_twos_deck] == count_cards) {
					
					cards_discarded[total_discards] = twos_deck[number_of_twos_deck];
					twos_deck[number_of_twos_deck] = 0;
					number_of_twos_deck++;
					total_discards++;
				}
				
				count_cards = count_cards - 1;
			}
			
		} else if (total_ones_deck > 3) {
			
			count_cards = 19;
			number_of_ones_deck = 0;
			
			while(10 <= count_cards && total_discards < 3 && total_ones_deck > 3) {
				if (ones_deck[number_of_ones_deck] == count_cards) {
					
					cards_discarded[total_discards] = ones_deck[number_of_ones_deck];
					ones_deck[number_of_ones_deck] = 0;
					number_of_ones_deck++;
					total_discards++;
				}
				
				count_cards = count_cards - 1;
			}
			
		} else {
			if (count_suits == 4) {
				
				count_cards = 49; 
				number_of_fours_deck = 0;
				
				while(45 <= count_cards && count_cards != BUFFALO
					  && total_discards < 3 && count_suits == 4) { // Want to keep buffalo
					
					if (fours_deck[number_of_fours_deck] == count_cards) { // Discarding high cards, starting at 49
					
						cards_discarded[total_discards] = fours_deck[number_of_fours_deck];
						fours_deck[number_of_fours_deck] = 0; // Ensures no double counting
						number_of_fours_deck++;
						total_discards++;
					}
					
					if(count_cards == 45) {
						
						count_suits = count_suits - 1;
					}
					
					count_cards = count_cards - 1;
				}
			}
			
			if (count_suits == 3) {
				
				count_cards = 39;
				number_of_calves_deck = 0;
				
				while(30 + minimum_num <= count_cards && total_discards < 3
					  && count_suits == 3) {
					
					if (calves_deck[number_of_calves_deck] == count_cards) {
						
						cards_discarded[total_discards] = calves_deck[number_of_calves_deck];
						calves_deck[number_of_calves_deck] = 0;
						number_of_calves_deck++;
						total_discards++;
					}
					
					if (count_cards == 30 + minimum_num) {
						
						count_suits = count_suits - 1;
					}
					
					count_cards = count_cards - 1;
				}
			}
			
			if (count_suits == 2) {
				
				count_cards = 29;
				number_of_twos_deck = 0;
				
				while(20 + minimum_num <= count_cards && total_discards < 3
					  && count_suits == 2){
					
					if (twos_deck[number_of_twos_deck] == count_cards) {
						
						cards_discarded[total_discards] = twos_deck[number_of_twos_deck];
						twos_deck[number_of_twos_deck] = 0;
						number_of_twos_deck++;
						total_discards++;
					}
					
					if (count_cards == 20 + minimum_num) {
						
						count_suits = count_suits - 1;
					}
					
					count_cards = count_cards - 1;
				}
			}
			
			if (count_suits == 1){
				
				count_cards = 19;
				number_of_ones_deck = 0;
				
				while(10 + minimum_num <= count_cards && total_discards < 3
					  && count_suits == 1) {
					
					if (ones_deck[number_of_ones_deck] == count_cards) {
						
						cards_discarded[total_discards] = ones_deck[number_of_ones_deck];
						ones_deck[number_of_ones_deck] = 0;
						number_of_ones_deck++;
						total_discards++;
					}
					
					if(count_cards == 10 + minimum_num){
						
						count_suits = count_suits - 1;
					}
					
					count_cards = count_cards - 1;
				}
			}
			
			minimum_num = minimum_num - 1;
		}
		
		count_suits = 4;
	}
	
	count_cards = 0;
	
	printf("%d %d %d\n", cards_discarded[0], cards_discarded[1], cards_discarded[2]);
}

	// ADD CODE TO READ THE CARDS OF YOUR HAND INTO AN ARRAY USING SCANF
	// ADD CODE TO READ THE CARDS PLAYED THIS ROUND INTO AN ARRAY USING SCANF
	// ADD CODE TO READ THE CARDS PREVIOUSLY PLAYED THIS ROUND INTO AN ARRAY USING SCANF
	// THEN ADD YOUR CODE HERE TO CHOOSE AND PRINT THE CARD YOU WISH TO PLAY

	// NOTE: THE PROVIDED CODE DOES NOT MAKE A LEGAL MOVE. YOU MUST CHANGE IT TO
	// PLAY A CARD FROM YOUR HAND.

void choose_card_to_play(void) {
	int count_cards = 0;
	int length_of_hand = 0;
	int previous_plays = 0;
	int table_position = 0;
	int discards[CARDS_TRANSITIONED];
	int new_cards[CARDS_TRANSITIONED];
	
	scanf("%d", &length_of_hand); //Scans 1st integer, Length of Hand.
	
	int deck[length_of_hand];
	int num_of_cards_played = ((N_CARDS_INITIAL_HAND - length_of_hand) * N_PLAYERS);
	int num_of_rounds_played[num_of_cards_played];
//-----------------------------------------------------------------------------
//SCANNING ALL INFORMATION:
//-----------------------------------------------------------------------------
	
	scanf("%d", &previous_plays); //Scans 2nd integer, the number of cards previously played.
	
	scanf("%d", &table_position); //Scans 3rd integer, the player's position.
	
	int cards_played_in_round[table_position];
	
	while (count_cards < length_of_hand) { //Scans 4th set, the Player's deck.
		scanf("%d", &deck[count_cards]);
		count_cards++;
	}
	
	count_cards = 0;
	
	while(count_cards < previous_plays) { //Scans 5th set, cards played previously in the round.
		scanf("%d", &cards_played_in_round[count_cards]);
		count_cards++;
	}
	
	count_cards = 0;
	
	while(count_cards < num_of_cards_played) { //Scans 6th set, cards played in previous games.
		scanf("%d", &num_of_rounds_played[count_cards]);
		count_cards++;
	}
	
	count_cards = 0;
	
	while(count_cards < N_CARDS_DISCARDED){ //Scans 7th set, cards discards at beginning of game.
		scanf("%d", &discards[count_cards]);
	}
	
	count_cards = 0;
	
	while(count_cards < 3){ //Scans 8th set, the cards given to the player at the start of the game.
		scanf("%d", &new_cards[count_cards]);
	}
	
//-----------------------------------------------------------------------------
//PLAYING THE GAME:
//-----------------------------------------------------------------------------
	int maxCard = deck_of_cards[0];
	int first_digit;
	int n;
	
	if (table_position != 0) {
		for(n = 1, n < length_of_hand, n++) {
			if ((deck_of_cards[n] > cards_played_in_round[0]) && (deck_of_cards[n] < cards_played_in_round[0][0]) {
				if (deck_of_cards[n] > maxCard) {
					maxCard = deck_of_cards[n];
					printf("%d", maxCard);
				
				} else if ((deck_of_cards[n] < cards_played_in_round[0]) && (deck_of_cards[n] = ???))
					
	}
	
	if (table_position == 0) {
		
	}
	
	
	
	
	
	
	printf("42\n"); // Change return value
}


// ADD A COMMENT HERE EXPLAINING YOUR OVERALL TESTING STRATEGY

void run_unit_tests(void) {
	// PUT YOUR UNIT TESTS HERE
}


// ADD YOUR FUNCTIONS HERE

int first_digit_one(int deck[N_CARDS_INITIAL_HAND], int ones_deck[MAX_FIRST_DIGIT_RANGE]) {
	int count_cards = 0;
	int number_of_ones_deck = 0;
	
	while (count_cards < N_CARDS_INITIAL_HAND) {
		if (10 <= deck[count_cards] && deck[count_cards] <= 19 ) { // Sorts into ones_deck
			ones_deck[number_of_ones_deck] = deck[count_cards];
			number_of_ones_deck = number_of_ones_deck + 1;
		}
		
		count_cards = count_cards + 1;
	}
	
	return number_of_ones_deck;
}

int first_digit_two(int deck[N_CARDS_INITIAL_HAND],int twos_deck[10]) {
	int count_cards = 0;
	int number_of_twos_deck = 0;
	
	while (count_cards < N_CARDS_INITIAL_HAND) {
		if (20 <= deck[count_cards] && deck[count_cards] <= 29 ) { // Sorts into twos_deck
			twos_deck[number_of_twos_deck] = deck[count_cards];
			number_of_twos_deck = number_of_twos_deck + 1;
		}
		
		count_cards = count_cards + 1;
	}
	
	return number_of_twos_deck;
}

int count_calves_deck(int deck[N_CARDS_INITIAL_HAND], int calves_deck[10]) {
	int count_cards = 0;
	int number_of_calves_deck = 0;
	
	while (count_cards < N_CARDS_INITIAL_HAND) {
		if (30 <= deck[count_cards] && deck[count_cards] <= 39 ) { // Sorts into calves_deck
			calves_deck[number_of_calves_deck] = deck[count_cards];
			number_of_calves_deck = number_of_calves_deck + 1;
		}
		
		count_cards = count_cards + 1;
	}
	
	return number_of_calves_deck;
}

int first_digit_four(int deck[N_CARDS_INITIAL_HAND], int fours_deck[10]) {
	int count_cards = 0;
	int number_of_fours_deck = 0;
	
	while (count_cards < N_CARDS_INITIAL_HAND) {
		if (40 <= deck[count_cards] && deck[count_cards] <= 49 ) { // Sorts into fours_deck
			fours_deck[number_of_fours_deck] = deck[count_cards];
			number_of_fours_deck = number_of_fours_deck + 1;
		}
		
		count_cards = count_cards + 1;
	}
	
	return number_of_fours_deck;
}
