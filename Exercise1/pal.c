#include "pal.h"
#include <string.h>

//Global variables to represent the booleans
int TRUE = 1;
int FALSE = 0;

//--------------------------------------------------
// is_palindrome
//--------------------------------------------------

int is_palindrome(int numbers[]) {
	// BEGIN and END are the first and the last index of the array, respectively
	int begin, end = 5;

	// This loop finishes in the 3rd iteraction because this is the middle of the array
	for (begin = 0; begin < 3; begin++) {
		// If one number is different from its correspondent, then it isn't a palindrome
		if (numbers[begin] != numbers[end]) {
			return FALSE;
		}
		// Decrement the last index to make a comparison in loop
		end--;
	}

	return TRUE;
}

//--------------------------------------------------
// ask_for_command
//--------------------------------------------------

char ask_for_command() {
	// Method local attributes
	int correct = FALSE;
	char command;

	// As long as the user don't press the correct command, loop continues
	while (correct == FALSE) {
		// Asking for the command. Using a method from visible.h library
		printf("NEW MOVEMENT - Enter a valid command by keyword: \n");
		printf("Valid commands [w] [a] [d] [x]: ");
		command = my_get_char();
		// Putting the command to lower case to verify if it's correct in a easier way
		command = tolower(command);

		// If the command is one of the predetermined characters, then correct is set as true and loop ends
		if (command == 'a' || command == 'd' || command == 'w' || command == 'x') {
			correct = TRUE;
		}
	} // End of while

	return command;
}

//--------------------------------------------------
// process_movement
//--------------------------------------------------

void process_movement(int numbers[], int* pointer, char character) {
	// Method local variable
	int game_over = FALSE;
	int number_movements = 0;

	while (game_over == FALSE) {
		switch (character) {
			// In case of the command is 'w'
		case 'w':
			// If the number at which the pointer is pointing is a 9, the game asks for another command
			if ((*pointer) == 9) {
				system("cls");
				printf("[!] This is the maximum number allowed. Command not possible, please try again. \n");
				print_status(numbers, pointer, number_movements);
				character = ask_for_command();
			}
			// Otherwise, 1 is added to the number at which the pointer is pointing
			else {
				(*pointer) = (*pointer) + 1;
				number_movements = number_movements + 1;
				system("cls");
				print_status(numbers, pointer, number_movements);
				// Verify is the new number is a palindrome
				if (is_palindrome(numbers) == TRUE) {
					game_over = TRUE;
					break;
				}
				// If it isn't, then the games asks for more commands
				else {
					character = ask_for_command();
				}
			}
			break;
			// In case of the command is 'a'
		case 'a':
			// If the pointer is pointing to the first position of the array, the game asks for another command
			if (pointer == numbers) {
				system("cls");
				printf("[!] You are in the very left border. Command not possible, please try again. \n");
				print_status(numbers, pointer, number_movements);
				character = ask_for_command();
			}
			// Otherwise, the pointer points to the previous position os the array
			else {
				pointer = pointer--;
				number_movements = number_movements + 1;
				system("cls");
				print_status(numbers, pointer, number_movements);
				// Verify is the new number is a palindrome
				if (is_palindrome(numbers) == TRUE) {
					game_over = TRUE;
					break;
				}
				// If it isn't, then the games asks for more commands
				else {
					character = ask_for_command();
				}
			}
			break;
			// In case of the command is 'x'
		case 'x':
			// If the number at which the pointer is pointing is a 0, the game asks for another command
			if ((*pointer) == 0) {
				system("cls");
				printf("[!] This is the minimum number allowed. Command not possible, please try again. \n");
				print_status(numbers, pointer, number_movements);
				character = ask_for_command();
			}
			// Otherwise, 1 is removed to the number at which the pointer is pointing
			else {
				(*pointer) = (*pointer) - 1;
				number_movements = number_movements + 1;
				system("cls");
				print_status(numbers, pointer, number_movements);
				// Verify is the new number is a palindrome
				if (is_palindrome(numbers) == TRUE) {
					game_over = TRUE;
					break;
				}
				// If it isn't, then the games asks for more commands
				else {
					character = ask_for_command();
				}
			}
			break;
			// In case of the command is 'd'
		case 'd':
			// If the pointer is pointing to the last position of the array, the game asks for another command
			if (pointer == numbers + 5) {
				system("cls");
				printf("[!] You are in the very right border. Command not possible, please try again. \n");
				print_status(numbers, pointer, number_movements);
				character = ask_for_command();
			}
			// Otherwise, the pointer points to the next position os the array
			else {
				pointer = pointer++;
				number_movements = number_movements + 1;
				system("cls");
				print_status(numbers, pointer, number_movements);
				// Verify is the new number is a palindrome
				if (is_palindrome(numbers) == TRUE) {
					game_over = TRUE;
					break;
				}
				// If it isn't, then the games asks for more commands
				else {
					character = ask_for_command();
				}
			}
			break;
		} // End of switch
	} // End of while

	if (game_over == TRUE) {
		printf("\n----------------------------------\n");
		printf(" ------------ SOLVED ------------ \n");
		printf("----------------------------------");
	}
}

//--------------------------------------------------
// print_status
//--------------------------------------------------

void print_status(int numbers[], int* pointer, int number_movements) {
	// Method local variables
	int number_spaces = pointer - &numbers[0];
	char first_space[21] = { "         " };
	char space[3] = {"  "};

	printf("\n---------- GAME STATUS ----------\n");
	// Showing the number
	printf("\nNumber = { ");
	for (int i = 0; i < 6; i++) {
		printf("%d ", numbers[i]);
	}
	printf("}\n");

	// Showing where the user is in the array
	// Adding space to first_space
	strcat_s(first_space, 21, space);
	if (pointer == numbers) {
		printf("%s^", first_space);
	}

	else {
		strcat_s(first_space, 21, space);
		printf("%s", first_space);
		// Keep adding spaces considering the distance between the first and the current position
		for (int j = 1; j < number_spaces; j++) {
			printf("%s", space);
		}
		printf("^");
	}
	
	//Showing number of movements
	printf("\nNumber of movements: %d.\n", number_movements);
}

//--------------------------------------------------
// user_game_palindrome
//--------------------------------------------------

void user_game_palindrome(int palindrome_number) {
	int palindrome_array[6];
	int* position;
	char movement;

	// Tranform the integer number into an array of integers
	for (int i = 5; i >= 0; --i) {
		palindrome_array[i] = palindrome_number % 10;
		palindrome_number = palindrome_number / 10;
	}

	// Pointing to the first element of the array
	position = palindrome_array;
	// Printing the first status of the game
	system("cls");
	print_status(palindrome_array, position, 0);

	movement = ask_for_command();
	process_movement(palindrome_array, position, movement);
}