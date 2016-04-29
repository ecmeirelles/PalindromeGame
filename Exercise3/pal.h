#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "visible.h"

//--------------------------------------------------
// is_palindrome
//--------------------------------------------------

int is_palindrome(int* numbers, int size_number);

//--------------------------------------------------
// is_commands_allowed
//--------------------------------------------------

int is_command_allowed(char command[], int command_size);

//--------------------------------------------------
// set_movement
//--------------------------------------------------

char set_movement(int* numbers, int* temporary, int** position, int size_number, int** temp_position, int* temp_temporary);

//--------------------------------------------------
// process_movement
//--------------------------------------------------

void process_movement(int* numbers, int* temporary, int** position, int size_numbers, int* number_movements, int** temp_position,
	int* temp_temporary, int visible);

//--------------------------------------------------
// print_status
//--------------------------------------------------

void print_status(int* numbers, int size_number, int** position, int* number_movements);

//--------------------------------------------------
// game_palindrome
//--------------------------------------------------

void game_palindrome(int* numbers, int* temporary, int** position, int size_numbers, int* number_movements, int** temp_position,
	int* temp_temporary);

//--------------------------------------------------
// machine_game_palindrome
//--------------------------------------------------

void machine_game_palindrome(int palindrome_number, int number_size, char commands[], int command_size);