#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "visible.h"

//--------------------------------------------------
// is_palindrome
//--------------------------------------------------

int is_palindrome(int* numbers, int size_number);

//--------------------------------------------------
// ask_for_command
//--------------------------------------------------

char ask_for_command(char command[], int command_size);

//--------------------------------------------------
// process_movement
//--------------------------------------------------

void process_movement(int* numbers, int* temporary, int** position, char commands[], int commands_size, int size_numbers, int number_movements, char character);

//--------------------------------------------------
// print_status
//--------------------------------------------------

void print_status(int* numbers, int size_number, int** position, int number_movements);

//--------------------------------------------------
// user_game_palindrome
//--------------------------------------------------

void user_game_palindrome(int palindrome_number, int number_size, char commands[], int command_size);