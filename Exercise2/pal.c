#include "pal.h"
#include <string.h>

//Global variables to represent the booleans
int TRUE = 1;
int FALSE = 0;

//--------------------------------------------------
// is_palindrome
//--------------------------------------------------

int is_palindrome(int* numbers, int size_number) {
	// Method local variables
	int last_index = size_number - 1;

	// This loop finishes in the 3rd iteraction because this is the middle of the array
	for (int i = 0; i < size_number; i++) {
		// If one number is different from its correspondent, then it isn't a palindrome
		if (*(numbers + i) != *(numbers + last_index)) {
			return FALSE;
		}
		// Decrement the last index to make a comparison in loop
		last_index--;
	}

	return TRUE;
}

//--------------------------------------------------
// ask_for_command
//--------------------------------------------------

char ask_for_command(char command[], int command_size) {
	// Method local attributes
	int correct = FALSE;
	int allowed = 0;
	char commands_allowed[] = { 'a','d','w','x', 'h', 'k', 'u', 'm' };
	char movement;

	// Verify if the commands predetermined are the same as the mandatory ones
	for (int i = 0; i < command_size; i++) {
		for (int k = 0; k < command_size; k++) {
			if (command[i] == commands_allowed[k]) {
				// Each time that a command is founded in the commands_allowed, 1 is added to allowed
				allowed = allowed + 1;
				break;
			}
		}
	}

	// If some of the commands are not the same, 'allowed' will be different from 8
	if (allowed != 8) {
		printf("[!] Valid commands are");
		for (int j = 0; j < command_size; j++) {
			printf(" [%c]", commands_allowed[j]);
		}
		
		movement = '!';
	}

	else {
		// As long as the user don't press the correct command, loop continues
		while (correct == FALSE) {
			// Asking for the command. Using a method from visible.h library
			printf("NEW MOVEMENT - Enter a valid command by keyword: \n");
			printf("Valid commands");
			for (int j = 0; j < command_size; j++) {
				printf(" [%c]", commands_allowed[j]);
			}
			printf(": ");

			movement = my_get_char();
			// Putting the command to lower case to verify if it's correct in a easier way
			movement = tolower(movement);

			// Allow the user to enter just the valid commands
			if (movement == 'a' || movement == 'd' || movement == 'w' || movement == 'x' || movement == 'h' || movement == 'u'
				|| movement == 'k' || movement == 'm') {
				correct = TRUE;
			}

		} // End of while
	}

	return movement;
}

//--------------------------------------------------
// process_movement
//--------------------------------------------------

void process_movement(int* numbers, int* temporary, int** position, char commands[], int commands_size, int size_numbers,  
	int number_movements, char character) {
	// Method local variable
	int game_over = FALSE;
	int problem = FALSE;

	while (game_over == FALSE && problem == FALSE) {
		switch (character) {
			// In case of the command is 'w'
			case 'w':
				// If the number at which the pointer is pointing is a 9, the game asks for another command
				if ((**position) == 9) {
					system("cls");
					printf("[!] This is the maximum number allowed. Command not possible, please try again. \n");
					print_status(numbers, size_numbers, position, number_movements);
					character = ask_for_command(commands, commands_size);
				}
				// Otherwise, 1 is added to the number at which the pointer is pointing
				else {
					(**position) = (**position) + 1;
					number_movements = number_movements + 1;
					system("cls");
					print_status(numbers, size_numbers, position, number_movements);
					// Verify if the new number is a palindrome
					if (is_palindrome(numbers, size_numbers) == TRUE) {
						game_over = TRUE;
						break;
					}
					// If it isn't, then the games asks for more commands
					else {
						character = ask_for_command(commands, commands_size);
					}
				}
			break;

			// In case of the command is 'a'
			case 'a':
				// If the pointer is pointing to the first position of the array, the game asks for another command
				if (*position == numbers) {
					system("cls");
					printf("[!] You are in the very left border. Command not possible, please try again. \n");
					print_status(numbers, size_numbers, position, number_movements);
					character = ask_for_command(commands, commands_size);
				}
				// Otherwise, the pointer points to the previous position os the array
				else {
					temporary = temporary--;
					position = &temporary;
					number_movements = number_movements + 1;
					system("cls");
					print_status(numbers, size_numbers, position, number_movements);
					// Verify is the new number is a palindrome
					if (is_palindrome(numbers, size_numbers) == TRUE) {
						game_over = TRUE;
						break;
					}
					// If it isn't, then the games asks for more commands
					else {
						character = ask_for_command(commands, commands_size);
					}
				}
			break;

			// In case of the command is 'x'
			case 'x':
				// If the number at which the pointer is pointing is a 0, the game asks for another command
				if ((**position) == 0) {
					system("cls");
					printf("[!] This is the minimum number allowed. Command not possible, please try again. \n");
					print_status(numbers, size_numbers, position, number_movements);
					character = ask_for_command(commands, commands_size);
				}
				// Otherwise, 1 is removed to the number at which the pointer is pointing
				else {
					(**position) = (**position) - 1;
					number_movements = number_movements + 1;
					system("cls");
					print_status(numbers, size_numbers, position, number_movements);
					// Verify is the new number is a palindrome
					if (is_palindrome(numbers, size_numbers) == TRUE) {
						game_over = TRUE;
						break;
					}
					// If it isn't, then the games asks for more commands
					else {
						character = ask_for_command(commands, commands_size);
					}
				}
			break;

			// In case of the command is 'd'
			case 'd':
				// If the pointer is pointing to the last position of the array, the game asks for another command
				if (*position == numbers + (size_numbers - 1)) {
					system("cls");
					printf("[!] You are in the very right border. Command not possible, please try again. \n");
					print_status(numbers, size_numbers, position, number_movements);
					character = ask_for_command(commands, commands_size);
				}
				// Otherwise, the pointer points to the next position of the array
				else {
					temporary = temporary++;
					position = &temporary;
					number_movements = number_movements + 1;
					system("cls");
					print_status(numbers, size_numbers, position, number_movements);
					// Verify is the new number is a palindrome
					if (is_palindrome(numbers, size_numbers) == TRUE) {
						game_over = TRUE;
						break;
					}
					// If it isn't, then the games asks for more commands
					else {
						character = ask_for_command(commands, commands_size);
					}
				}
			break;

			// In case of the command is 'h'
			case 'h':
				// If the pointer is pointing to the first position of the array, the game asks for another command
				if (*position == numbers) {
					system("cls");
					printf("[!] You are in the very left border. Command not possible, please try again. \n");
					print_status(numbers, size_numbers, position, number_movements);
					character = ask_for_command(commands, commands_size);
				}
				// Otherwise, the pointer points to the very left position of the array
				else {
					temporary = numbers;
					position = &temporary;
					number_movements = number_movements + 1;
					system("cls");
					print_status(numbers, size_numbers, position, number_movements);
					// Verify is the new number is a palindrome
					if (is_palindrome(numbers, size_numbers) == TRUE) {
						game_over = TRUE;
						break;
					}
					// If it isn't, then the games asks for more commands
					else {
						character = ask_for_command(commands, commands_size);
					}
				}
			break;

			// In case of the command is 'k'
			case 'k':
				// If the pointer is pointing to the last position of the array, the game asks for another command
				if (*position == numbers + (size_numbers - 1)) {
					system("cls");
					printf("[!] You are in the very right border. Command not possible, please try again. \n");
					print_status(numbers, size_numbers, position, number_movements);
					character = ask_for_command(commands, commands_size);
				}
				// Otherwise, the pointer points to the very right position of the array
				else {
					temporary = temporary + (size_numbers - 1);
					position = &temporary;
					number_movements = number_movements + 1;
					system("cls");
					print_status(numbers, size_numbers, position, number_movements);
					// Verify is the new number is a palindrome
					if (is_palindrome(numbers, size_numbers) == TRUE) {
						game_over = TRUE;
						break;
					}
					// If it isn't, then the games asks for more commands
					else {
						character = ask_for_command(commands, commands_size);
					}
				}
			break;

			// In case of the command is 'u'
			case 'u':
				// If the number at which the pointer is pointing is a 9, the game asks for another command
				if ((**position) == 9) {
					system("cls");
					printf("[!] This number is already 9. Command not possible, please try again. \n");
					print_status(numbers, size_numbers, position, number_movements);
					character = ask_for_command(commands, commands_size);
				}
				// Otherwise, 1 is added to the number at which the pointer is pointing until it becomes 9
				else {
					while ((**position) < 9) {
						(**position) = (**position) + 1;
					}
					number_movements = number_movements + 1;
					system("cls");
					print_status(numbers, size_numbers, position, number_movements);
					// Verify if the new number is a palindrome
					if (is_palindrome(numbers, size_numbers) == TRUE) {
						game_over = TRUE;
						break;
					}
					// If it isn't, then the games asks for more commands
					else {
						character = ask_for_command(commands, commands_size);
					}
				}
			break;

			// In case of the command is 'm'
			case 'm':
				// If the number at which the pointer is pointing is a 0, the game asks for another command
				if ((**position) == 0) {
					system("cls");
					printf("[!] This number is already 0. Command not possible, please try again. \n");
					print_status(numbers, size_numbers, position, number_movements);
					character = ask_for_command(commands, commands_size);
				}
				// Otherwise, 1 is removed to the number at which the pointer is pointing until it becomes 0
				else {
					while ((**position) > 0) {
						(**position) = (**position) - 1;
					}
					number_movements = number_movements + 1;
					system("cls");
					print_status(numbers, size_numbers, position, number_movements);
					// Verify if the new number is a palindrome
					if (is_palindrome(numbers, size_numbers) == TRUE) {
						game_over = TRUE;
						break;
					}
					// If it isn't, then the games asks for more commands
					else {
						character = ask_for_command(commands, commands_size);
					}
				}
			break;

			// In case of some command is different from the mandatory ones
			case '!':
				printf(".\n    The commands are not compatible, please fix it.\n");
				problem = TRUE;
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

void print_status(int* numbers, int size_number, int** position, int number_movements) {
	// Method local variables
	int number_spaces = *position - numbers;
	char first_space[21] = { "         " };
	char space[3] = {"  "};

	printf("\n---------- GAME STATUS ----------\n");
	// Showing the number
	printf("\nNumber = { ");
	for (int i = 0; i < size_number; i++) {
		printf("%d ", *(numbers + i));
	}
	printf("}\n");

	// Showing where the user is in the array
	// Adding space to first_space
	strcat_s(first_space, 21, space);
	if (*position == numbers) {
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

void user_game_palindrome(int palindrome_number, int number_size, char commands[], int command_size) {
	// Method local variables
	int* palindrome = (int *)malloc(sizeof(int) * number_size);
	int* temporary = palindrome;
	int** position = &temporary;
	char movement;
	
	// If the size of the number is above 2, then it is not possible to play the game
	if (number_size < 2) {
		printf("[!] You cannot play with numbers above two digits.\n");
	}

	else {
		// Tranform the integer number into an array of integers
		for (int i = (number_size - 1); i >= 0; --i) {
			*(palindrome + i) = palindrome_number % 10;
			palindrome_number = palindrome_number / 10;
		}

		// Verify if the number of commands is different from the number of mandatory commands
		if (command_size != 8) {
			printf("[!] There are 8 mandatory commands. The size is not compatible, please fix it.\n");
		}

		else {
			// Printing the first status of the game
			system("cls");
			print_status(palindrome, number_size, position, 0);

			movement = ask_for_command(commands, command_size);
			process_movement(palindrome, temporary, position, commands, command_size, number_size, 0, movement);
		}
	}

	free(palindrome);
}