// intensity.c
// Assignment 2, COMP1511 18s1: Intensity
//
// This program by Dheeraj Viswanadham (z5204820)
//
// Started: 18/04/2018 | Last edited: 14/05/2018
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

#define SUITS 4
#define BUFFALO 47

#define TENS_DIGIT 10

void print_player_name(void);
void choose_discards(void);
void choose_card_to_play(void);
void run_unit_tests(void);

// ADD PROTOTYPES FOR YOUR FUNCTIONS HERE

int first_digit(int number);
int last_digit(int number);
int legal_card(int current_card, int suit, int deck[], 
				int current_round[N_MAX_ROUNDS][N_PLAYERS]);
int card_same_suit(int deck[], int suit);
int played_calves(int prev_rounds[N_MAX_ROUNDS][N_PLAYERS]);
int void_is_true(int deck[], int total_voids);
int in_values(int insert_array[], int array_length, int element);
int card_select(int deck[], int suit, int total_cards, 
				int current_round[N_MAX_ROUNDS][N_PLAYERS]);
double discard_risk(int current_card, int suit, int deck[], int play_cards);
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

// Prints the AI name
void print_player_name(void) {
	printf("Alpha-B1\n");
}

// Chooses strategic discards based on scanned input from STDIN
void choose_discards() {
	// This bypasses any "newlines" i.e. '\n'
	getchar(); 
	
	int deck[N_CARDS_INITIAL_HAND] = {0};
	int count_deck = 0;
	int variable_i = 0;
	
	while(variable_i < N_CARDS_INITIAL_HAND) {
		scanf("%d", &deck[variable_i]);
		bypass_space(variable_i, N_CARDS_INITIAL_HAND);
		
		variable_i = (variable_i + 1);
	}
	
	int discarded[N_CARDS_DISCARDED] = {0};
	int variable_j = 0;
	
	while(variable_j < N_CARDS_DISCARDED) {
		int variable_x = 0;
		int risk_value_card_x = 0;
		double risk_value = 0;
		
		while(variable_x < N_CARDS_INITIAL_HAND) {
			if (risk_value <= discard_risk(deck[variable_x], 0, 
				deck, N_CARDS_DISCARDED) && 
				!in_values(discarded, N_CARDS_DISCARDED, deck[variable_x])) {
					
				risk_value = discard_risk(deck[variable_x], 0, 
								deck, N_CARDS_DISCARDED);
				risk_value_card_x = variable_x;
			}
			
			variable_x = (variable_x + 1);
		}
		
		discarded[variable_j] = deck[risk_value_card_x];
		printf("%d", discarded[variable_j]);
		
		if (variable_j == 2) {
			printf("\n");
		
		} else {
			printf(" ");
		}
		
		variable_j = (variable_j + 1);
	}
}

// Chooses the strategic card to play based on STDIN values
void choose_card_to_play(void) {
	int total_cards = 0;
	int cards_played_in_round = 0;
	int table_pos = 0;
	
	// SCANNING ALL INFORMATION:
	
	scanf("%d %d %d", &total_cards, &cards_played_in_round, &table_pos);
	
	int player_turn = (N_MAX_ROUNDS - total_cards);
	int deck[N_CARDS_INITIAL_HAND] = {0};
	int variable_i = 0;
	
	while(variable_i < total_cards) {
		scanf("%d", &deck[variable_i]);
		bypass_space(variable_i, total_cards);
		
		variable_i = (variable_i + 1);
	}
	
	int played[N_CARDS_INITIAL_HAND] = {0};
	int variable_j = 0;
	
	while(variable_j < cards_played_in_round) {
		scanf("%d", &played[variable_j]);
		bypass_space(variable_j, cards_played_in_round);
		
		variable_j = (variable_j + 1);
	}
	
	int current_round[N_MAX_ROUNDS][N_PLAYERS] = {{0}};
	int variable_y = 0;
	
	// If N_CARDS = 9, then we know it is the first turn and one previous round
	
	while(variable_y < player_turn) {
		scanf("%d %d %d %d", &current_round[variable_y][0], 
				&current_round[variable_y][1], &current_round[variable_y][2], 
				&current_round[variable_y][3]);
		
		variable_y = (variable_y + 1);
	}
	
	int discarded[N_CARDS_DISCARDED] = {0};
	int receivedDiscards[N_CARDS_DISCARDED] = {0};
	
	scanf("%d %d %d", &discarded[0], &discarded[1], &discarded[2]);
	scanf("%d %d %d", &receivedDiscards[0], &receivedDiscards[1], 
			&receivedDiscards[2]);
	
	int suit = first_digit(played[0]);
	
	// Outputting the best card to play in this round:
	
	int current_card = card_select(deck, suit, total_cards, current_round);
	
	printf("%d\n", current_card);
}

// ADD YOUR FUNCTIONS HERE

// Returns the first digit (of the number of the card) i.e. 2 if card was 24
int first_digit(int number) {
	int first_num = 0;
	
	first_num = ((number % 100 - (last_digit(number)))/ TENS_DIGIT);
	
	return first_num;
}

// Returns the last digit (of the number of the card) i.e. 4 if card was 24
int last_digit(int number) {
	int last_num = 0;
	
	last_num = (number % TENS_DIGIT);
	
	return last_num;
}

// Determines if a card is legal to play based on current suit and player's hand
int legal_card(int current_card, int suit, int deck[], 
				int current_round[N_MAX_ROUNDS][N_PLAYERS]) {
	int trigger = FALSE;
	
	if (current_card >= 30 && current_card <= 39) {
		if (played_calves(current_round) && (first_digit(current_card) == suit 
			|| suit == 0 )) {
				
			trigger = TRUE;
			
		} else {
			if (card_same_suit(deck, suit)) {
				trigger = FALSE;
				
			} else {
				trigger = TRUE;
			}
		}
	}
	
	// Can play any card
	if (suit == 0) {
		trigger = TRUE;
	
	// Card is in suit
	} else if (first_digit(current_card) == suit) {
		trigger = TRUE;
		
	} else {
		// No other card you can legally play
		if (card_same_suit(deck, suit)) {
			trigger = FALSE;
			
		} else {
			trigger = TRUE;
		}
	}
	
	return trigger;
}

// Checks if a card has the same specified suit
int card_same_suit(int deck[], int suit) {
	int variable_i = 0;
	int trigger = FALSE;
	
	while(variable_i < N_CARDS_INITIAL_HAND) {
		if (first_digit(deck[variable_i]) == suit) {
			
			trigger = TRUE;
		}
		
		variable_i = (variable_i + 1);
	}
	
	return trigger;
}

// Checks if any calves have been previously played
int played_calves(int prev_rounds[N_MAX_ROUNDS][N_PLAYERS]) {
	int variable_i = 0;
	int trigger = FALSE;
	
	while(variable_i < N_MAX_ROUNDS) {
		int variable_j = 0;
		
		while(variable_j < N_PLAYERS) {
			if (prev_rounds[variable_i][variable_j] >= 30 && 
				prev_rounds[variable_i][variable_j] <= 39) {
				
				trigger = TRUE;
			}
			
			variable_j = (variable_j + 1);
		}
		
		variable_i = (variable_i + 1);
	}
	
	return trigger;
}

// Picks the cards to play in the current round
int card_select(int deck[], int suit, int total_cards, 
				int current_round[N_MAX_ROUNDS][N_PLAYERS]) {
	
	int points = 0;
	int card_x = 0;
	int variable_x = 0;
	
	while(variable_x < N_CARDS_INITIAL_HAND) {
		if (legal_card(deck[variable_x], suit, deck, current_round) && 
			deck[variable_x] != 0) {
			if (points < discard_risk(deck[variable_x], suit, deck, 1)) {
				
				points = discard_risk(deck[variable_x], suit, deck, 1);
				card_x = variable_x;
			}
		}
		
		variable_x = (variable_x + 1);
	}
	
	return deck[card_x];
}

// Determines which cards carry more risk and hence be discarded sooner
double discard_risk(int current_card, int suit, int deck[], int play_cards) {
	double hazard = 0;
	int exponent = 1;
	
	// Reasoning: the bigger the suit, then the bigger the risk
	if (suit) {
		exponent = suit;
	}
	
	if (first_digit(current_card) == suit) {
		hazard = 10;
	}
	
	hazard += (0.1 * last_digit(current_card));
	
	if (first_digit(current_card) == 3) {
		hazard *= 2;
		
	} else if (current_card >= BUFFALO) {
		hazard *= 5;
	}
	
	// Hold onto these cards because they act as a buffer against the Buffalo
	if (current_card >= 40 && current_card < BUFFALO) {
		hazard *= 0.01;
	}
	
	if(void_is_true(deck, play_cards)) {
		if (first_digit(current_card) == void_is_true(deck, play_cards) ) {
			hazard = 100;
		}
	}
	
	return (hazard * exponent);
}

// Returns the highest suit if we are able to void it during our choose_discards
int void_is_true(int deck[], int total_voids) {
	int num_of_suits[SUITS] = {0};
	int variable_i = 0;
	
	while(variable_i < N_CARDS_INITIAL_HAND) {
		if (deck[variable_i] != 0) {
			num_of_suits[ first_digit(deck[variable_i]) - 1 ] += 1;
		}
		
		variable_i = (variable_i + 1);
	}
	
	int variable_x = 0;
	int original_num_suits = SUITS;
	int new_num_suits = 0;
	
	while(variable_x < SUITS) {
		if (num_of_suits[variable_x] <= total_voids && 
			num_of_suits[variable_x] != 0) {
				
			if (original_num_suits > num_of_suits[variable_x]) {
				
				original_num_suits = num_of_suits[variable_x];
				new_num_suits = (variable_x + 1);
			}
		}
		
		variable_x = (variable_x + 1);
	}
	
	return new_num_suits;
}

// Checks if a particular value is in an array
int in_values(int insert_array[], int array_length, int element) {
	int variable_i = 0;
	int trigger = FALSE;
	
	while(variable_i < array_length) {
		if (element == insert_array[variable_i]) {
			
			trigger = TRUE;
		}
		
		variable_i = (variable_i + 1);
	}
	
	return trigger;
}

// Gets rid of any spaces at the end of input
void bypass_space(int variable_i, int counter) {
	if (variable_i != (counter - 1)) {
		scanf(" ");
	}
}

// ADD A COMMENT HERE EXPLAINING YOUR OVERALL TESTING STRATEGY

// Discard 48,49 in the very beginning (as they carry high risk.
// If you have a calf (30 - 39) / buffalo (47) and you cannot play a card with 
// the same first digit then you can play a calf/buffalo.
// If player 0 or any other player with the same valid first digit 
// (except "3" for the calves) as player 0 has played a higher second digit 
// than any of the cards in the first digit range that you have, then play your
// lowest second digit (if you have any) else play a calf or buffalo 
// (if you have any) and if you don't have them just play another card
// within the largest digit range and put down the lowest one.
//
// For the unit tests strategy:
// 1) Test that function values returned for first and last digits are correct
// 2) Test if a calf has been played before or not
// 3) Test that the suits function works
// 4) Test that the void_deck function works 
// 5) Test that the specified cards are in the deck or not

void run_unit_tests(void) {
	// (1A) Testing the first-digit of the number function outputs correctly
	assert(first_digit(10) == 1);
	assert(first_digit(24) == 2);
	assert(first_digit(36) == 3);
	assert(first_digit(45) == 4);
	
	// (1B) Testing the last-digit of the number function outputs correctly
	assert(last_digit(11) == 1);
	assert(last_digit(23) == 3);
	assert(last_digit(37) == 7);
	assert(last_digit(42) == 2);
	
	// (2) Testing whether function correctly outputs if a calf has been played
	int calf_in_round[N_MAX_ROUNDS][N_PLAYERS] = 
	{{11, 13, 15, 17}, {33, 35, 37, 39}, {0}};
	
	int calf_not_in_round[N_MAX_ROUNDS][N_PLAYERS] = 
	{{12, 14, 16, 18}, {42, 44, 46, 48}, {0}};
	
	assert(played_calves(calf_in_round) == TRUE);
	assert(played_calves(calf_not_in_round) == FALSE);
	
	// (3) Testing whether the first digit of the card is the same as the suit
	int current_hand[N_CARDS_INITIAL_HAND] = {10,12,13,14,15,16,17,18,19,20};
	
	assert(card_same_suit(current_hand, 1) == TRUE);
	assert(card_same_suit(current_hand, 3) == FALSE);
	
	// (4) Testing the best card to play for the void function (highest suit)
	int current_hand_void_three[5] = {11, 12, 13, 22, 23};
	
	assert(void_is_true(current_hand, 1) == 2);
	assert(void_is_true(current_hand_void_three, 3) == 2);
	assert(void_is_true(current_hand_void_three, 1) == 0);
	
	// (5) Testing the "in" values i.e. if the card is in the deck or not
	assert(in_values(current_hand, N_CARDS_INITIAL_HAND, 12) == TRUE);
	assert(in_values(current_hand, N_CARDS_INITIAL_HAND, 35) == FALSE);
}
