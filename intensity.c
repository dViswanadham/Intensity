// intensity.c
// Assignment 2, COMP1511 18s1: Intensity
//
// This program by Dheeraj Viswanadham (z5204820)
//
// Started: 18/04/2018 | Last edited: 13/05/2018
//
// Version 1.0.1: Minor changes to wording of comments.
// Version 1.0.0: Assignment released.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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

#define FALSE 0
#define TRUE 1

#define N_MAX_ROUNDS 10

#define SUITES 4
#define BUFFALO 47

void print_player_name(void);
void choose_discards(void);
void choose_card_to_play(void);
void run_unit_tests(void);

// ADD PROTOTYPES FOR YOUR FUNCTIONS HERE

int first_digit(int number);
int last_digit(int number);
int legal_card(int current_card, int suit, int deck[], int current_round[N_MAX_ROUNDS][N_PLAYERS]);
int card_same_suit(int deck[], int suit);
int played_calves(int prev_rounds[N_MAX_ROUNDS][N_PLAYERS]);
int void_is_true(int deck[], int amount_to_void);
int in_values(int array[], int length, int value);
int card_select(int deck[], int suit, int n_cards, int current_round[N_MAX_ROUNDS][N_PLAYERS]);
double discard_risk(int current_card, int suit, int deck[], int cards_to_play);
void bypass_space(int variable_i, int counter);

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

// Prints the player name
void print_player_name(void) {
    printf("Alpha-B1\n");
}

// Chooses discards based on its scanned in deck and whether
// the deck can be voided in some way
void choose_discards() {
	getchar(); // this bypasses any newlines
	
	int deck[N_CARDS_INITIAL_HAND] = {0};
	int hand_count = 0;
	int variable_i = 0;
	
	while(variable_i < N_CARDS_INITIAL_HAND) {
		scanf("%d", &deck[variable_i]);
		bypass_space(variable_i, N_CARDS_INITIAL_HAND);
		
		variable_i = (variable_i + 1);
	}
	
	int discards[N_CARDS_DISCARDED] = {0};
	int variable_j = 0;
	
	while(variable_j < N_CARDS_DISCARDED) {
		int variable_x = 0;
		double max_risk = 0;
		int max_risk_k = 0;
		
		while(variable_x < N_CARDS_INITIAL_HAND) {
			if (max_risk <= discard_risk(deck[variable_x], 0, deck, N_CARDS_DISCARDED) && !in_values(discards, N_CARDS_DISCARDED, deck[variable_x])) {
				max_risk = discard_risk(deck[variable_x], 0, deck, N_CARDS_DISCARDED);
				max_risk_k = variable_x;
			}
			
			variable_x = (variable_x + 1);
		}
		
		discards[variable_j] = deck[max_risk_k];
		printf("%d", discards[variable_j]);
		
		if (variable_j == 2) {
			printf("\n");
		
		} else {
			printf(" ");
		}
		
		variable_j = (variable_j + 1);
	}
}

// Scans in input values and chooses a strategic card to play
// based on those inputs
void choose_card_to_play(void) {
	int n_cards = 0;
	int cards_played = 0;
	int table_position = 0;
	
	// SCANNING ALL INFORMATION:
	
	scanf("%d %d %d", &n_cards, &cards_played, &table_position);
	
	int turn = (N_MAX_ROUNDS - n_cards);
	int deck[N_CARDS_INITIAL_HAND] = {0};
	int variable_i = 0;
	
	while(variable_i < n_cards) {
		scanf("%d", &deck[variable_i]);
		bypass_space(variable_i, n_cards);
		
		variable_i = (variable_i + 1);
	}
	
	int played[N_CARDS_INITIAL_HAND] = {0};
	int variable_j = 0;
	
	while(variable_j < cards_played) {
		scanf("%d", &played[variable_j]);
		bypass_space(variable_j, cards_played);
		
		variable_j = (variable_j + 1);
	}
	
	int current_round[N_MAX_ROUNDS][N_PLAYERS] = {{0}};
	int variable_y = 0;
	
	// If N_CARDS = 9, then we know it is the first turn and one previous round
	
	while(variable_y < turn) {
		scanf("%d %d %d %d", &current_round[variable_y][0], &current_round[variable_y][1], &current_round[variable_y][2], &current_round[variable_y][3]);
		
		variable_y = (variable_y + 1);
	}
	
	int discards[N_CARDS_DISCARDED] = {0};
	int receivedDiscards[N_CARDS_DISCARDED] = {0};
	
	scanf("%d %d %d", &discards[0], &discards[1], &discards[2]);
	scanf("%d %d %d", &receivedDiscards[0], &receivedDiscards[1], &receivedDiscards[2]);
	
	int suit = first_digit(played[0]);
	
	// Outputting the best card to play in this round:
	
	int current_card = card_select(deck, suit, n_cards, current_round);
	
	printf("%d\n", current_card);
}

// ADD YOUR FUNCTIONS HERE

// Returns the first digit (of the number of the card) i.e. 2 if card was 24
int first_digit(int number) {
	int first_num;
	
	first_num = ((number % 100 - (last_digit(number)))/ 10);
	
	return first_num;
}

// Returns the last digit (of the number of the card) i.e. 4 if card was 24
int last_digit(int number) {
	int last_num;
	
	last_num = (number % 10);
	
	return last_num;
}

// Gets rid of any spaces at the end of input
void bypass_space(int variable_i, int counter) {
	if (variable_i != (counter - 1)) {
		scanf(" ");
	}
}

// determines if a given card is legal to play
// based on current suit (0 if no suit) and the players deck
int legal_card(int current_card, int suit, int deck[], int current_round[N_MAX_ROUNDS][N_PLAYERS]) {
	int trigger;
	
	if (current_card >= 30 && current_card <= 39) {
		if (played_calves(current_round) && ( first_digit(current_card) == suit || suit == 0 )) {
			trigger = TRUE;
			
		} else {
			if (card_same_suit(deck, suit)) {
				trigger = FALSE;
				
			} else {
				trigger = TRUE;
			}
		}
	}
	
	if (suit == 0) {
		// if it is your turn to make choice, you can pick any card
		trigger = TRUE;
		
	} else if (first_digit(current_card) == suit) {
		// If the card is in the suit
		trigger = TRUE;
		
	} else {
		// if there are no other cards in your deck that you can legally play
		if (card_same_suit(deck, suit)) {
			trigger = FALSE;
			
		} else {
			trigger = TRUE;
		}
	}
	
	return trigger;
}

// checks if your current had has a card with a particular suit
int card_same_suit(int deck[], int suit) {
	int variable_i = 0;
	
	while(variable_i < N_CARDS_INITIAL_HAND) {
		if (first_digit(deck[variable_i]) == suit) {
			
			return TRUE;
		}
		
		variable_i = (variable_i + 1);
	}
	
	return FALSE;
}

// Checks if the calf has already been played in prior rounds
int played_calves(int prev_rounds[N_MAX_ROUNDS][N_PLAYERS]) {
	int r = 0;
	
	while(r < N_MAX_ROUNDS) {
		int p = 0;
		
		while(p < N_PLAYERS) {
			if (30 <= prev_rounds[r][p] && prev_rounds[r][p] <= 39) {
				
				return TRUE;
			}
			
			p = (p + 1);
		}
		
		r = (r + 1);
	}
	
	return FALSE;
}

// Picks cards to play
int card_select(int deck[], int suit, int n_cards, int current_round[N_MAX_ROUNDS][N_PLAYERS]) {
	int best_score = 0;
	int best_card_k = 0;
	int variable_x = 0;
	
	while(variable_x < N_CARDS_INITIAL_HAND) {
		if (legal_card(deck[variable_x], suit, deck, current_round) && deck[variable_x] != 0) {
			if (best_score < discard_risk(deck[variable_x], suit, deck, 1)) {
				
				best_score = discard_risk(deck[variable_x], suit, deck, 1);
				best_card_k = variable_x;
			}
		}
		
		variable_x = (variable_x + 1);
	}
	
	return deck[best_card_k];
}

// Determines the risk of a card when choosing discards
// Higher risk cards should be discarded sooner
double discard_risk(int current_card, int suit, int deck[], int cards_to_play) {
	double risk = 0;
	int multiplier = 1;
	
	// larger suits tend to be riskier
	if (suit) {
		multiplier = suit;
	}
	
	// if we are dealing with the current suit - it is a larger risk.
	// (most of the time we are)
	
	if (first_digit(current_card) == suit) {
		risk = 10;
	}
	
	risk += 0.1 * last_digit(current_card);
	
	if (first_digit(current_card) == 3) {
		risk *= 2;
		
	} else if (current_card >= BUFFALO) {
		risk *= 5;
	}
	
	// We want to hold onto these cards because they act as a buffer against
	// a BUFFALO
	if (current_card >= 40 && current_card < BUFFALO) {
		risk *= 0.01;
	}
	
	if(void_is_true(deck, cards_to_play)) {
		if (first_digit(current_card) == void_is_true(deck, cards_to_play) ) {
			risk = 100; // make sure we void this suit if we can.
		}
	}
	
	return risk * multiplier;
}

// Returns the highest suit if we can void it at discard
int void_is_true(int deck[], int amount_to_void) {
	int suit_tally[SUITES] = {0};
	int variable_i = 0;
	
	while(variable_i < N_CARDS_INITIAL_HAND) {
		if (deck[variable_i] != 0) {
			suit_tally[ first_digit(deck[variable_i]) - 1 ] += 1;
		}
		
		variable_i = (variable_i + 1);
	}

	int variable_x = 0;
	int lowest = 4;
	int lowest_k = 0;
	
	while(variable_x < SUITES) {
		// If we can void the suit at this time
		if (suit_tally[variable_x] <= amount_to_void && suit_tally[variable_x] != 0) {
			if (lowest > suit_tally[variable_x]) {
				// Find the lowest amount of suit we can void
				// i.e. if we have 44 46 49 13 19, at discard
				// we can void both 4 suit and 1 suit.
				// We should void 1 suit first and then use the extra void
				lowest = suit_tally[variable_x];
				lowest_k = (variable_x + 1);
			}
		}
		
		variable_x = (variable_x + 1);
	}
	
	return lowest_k;
}

// checks if a particular value is in an array
int in_values(int array[], int length, int value) {
	int variable_i = 0;
	
	while(variable_i < length) {
		if (value == array[variable_i]) {
			
			return TRUE;
		}
		
		variable_i = (variable_i + 1);
	}
	
	return FALSE;
}

// ADD A COMMENT HERE EXPLAINING YOUR OVERALL TESTING STRATEGY

/*
===== TESTING STRATEGY =====
0. First Number
1. Last Number
2. Calf Played
3. Has card w/ suit
4. Can void
5. STDIN_values
============================
*/

void run_unit_tests(void) {
    // Testing the first-digit of the number function outputs correctly
	assert(first_digit(10) == 1);
	assert(first_digit(21) == 2);
	assert(first_digit(39) == 3);
	assert(first_digit(46) == 4);
	
	// Testing the last-digit of the number function outputs correctly
	assert(last_digit(10) == 0);
	assert(last_digit(21) == 1);
	assert(last_digit(39) == 9);
	assert(last_digit(46) == 6);
	
	// Testing whether the function correctly outputs if a calf has been played
	int calf_in_round[N_MAX_ROUNDS][N_PLAYERS] = {
		{11, 13, 15, 17},
		{33, 35, 37, 39},
		{0}
	};
	
	int calf_not_in_round[N_MAX_ROUNDS][N_PLAYERS] = {
		{12, 14, 16, 18},
		{42, 44, 46, 48},
		{0}
	};
	
	assert(played_calves(calf_in_round) == TRUE);
	assert(played_calves(calf_not_in_round) == FALSE);
	
	// Testing whether the first digit of the card is the same as the suit
	int current_hand[N_CARDS_INITIAL_HAND] = {11,12,13,14,15,16,17,18,19,20};
	
	assert(card_same_suit(current_hand, 1) == TRUE);
	assert(card_same_suit(current_hand, 4) == FALSE);
	
	// Testing the best card to play for the void function (highest suit)
	int current_hand_void_three[5] = {11, 12, 13, 22, 23};
	
	assert(void_is_true(current_hand, 1) == 2);
	assert(void_is_true(current_hand_void_three, 3) == 2);
	assert(void_is_true(current_hand_void_three, 1) == 0);
	
	// Testing the "in" values i.e. if the card is in my deck or not
	assert(in_values(current_hand, N_CARDS_INITIAL_HAND, 12) == TRUE);
	assert(in_values(current_hand, N_CARDS_INITIAL_HAND, 42) == FALSE);
}
