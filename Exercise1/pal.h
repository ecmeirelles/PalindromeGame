#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "visible.h"

//--------------------------------------------------
// is_palindrome
//--------------------------------------------------

int is_palindrome(int numbers[]);

//--------------------------------------------------
// ask_for_command
//--------------------------------------------------

char ask_for_command();

//--------------------------------------------------
// process_movement
//--------------------------------------------------

void process_movement(int numbers[], int* pointer, char character);

//--------------------------------------------------
// print_status
//--------------------------------------------------

void print_status(int numbers[], int* pointer, int number_moviments);

//--------------------------------------------------
// user_game_palindrome
//--------------------------------------------------

void user_game_palindrome(int palindrome_number);