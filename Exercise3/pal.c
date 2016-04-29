#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "visible.h"
#include "pal.h"

//Global variables
int TRUE = 1;
int FALSE = 0;

int INITIAL_MOVEMENT = 0;
int INITIAL_POSITION = 0;

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
// is_commands_allowed
//--------------------------------------------------

int is_command_allowed(char command[], int command_size) {
	int allowed = 0;
	int correct;
	char commands_allowed[] = { 'a','d','w','x' };

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
	if (allowed != 4) {
		printf("[!] Valid commands are");
		for (int j = 0; j < command_size; j++) {
			printf(" [%c]", commands_allowed[j]);
		}
		correct = FALSE;
	}

	else {
		correct = TRUE;
	}

	return correct;
}

//--------------------------------------------------
// set_movement
//--------------------------------------------------

char set_movement(int* numbers, int* temporary, int** position, int size_number, int** temp_position, int* temp_temporary) {
	char movement;
	int distance = *position - numbers;
	int size = size_number - 1;
	int middle = size / 2;
	int bigger_different_distance = -1;

	// Verify if the number is a palindrome
	if (is_palindrome(numbers, size_number) == TRUE) {
		movement = '*';
	}

	else {
		temporary = numbers + (size_number - (distance + 1));

		/* If the number to which position is pointing is different from the number to which temporary is pointing, the
		game returns the appropriate command */
		if (**position != *temporary) {
			// If the number to which temporary is poiting is bigger than 5, then the best solution is to increase it
			if (**position < *temporary) {
				movement = 'w';
			}
			// Otherwise, the best solution is to decrease it
			else {
				movement = 'x';
			}
		}

		/* If the number to which position is pointing is the same as the number to which temporary is pointing, the
		game returns a command to go to the next position */
		else {
			for (int i = middle; i >= 0; --i) {
				*temp_position = numbers + i;
				temp_temporary = numbers + (size - i);
				if (**temp_position != *temp_temporary) {
					if (middle > bigger_different_distance) {
						bigger_different_distance = i;
					}
				} //end if
			} //end for

			if (bigger_different_distance > distance) {
				movement = 'd';
			}

			else {
				movement = 'a';
			}
		}
	} // end of else

	return movement;
}

//--------------------------------------------------
// process_movement
//--------------------------------------------------

void process_movement(int* numbers, int* temporary, int** position, int size_numbers, int* number_movements, int** temp_position,
	int* temp_temporary, int visible) {
	// Method local variable
	int game_over = FALSE;
	char character;
	char key;

	// If visible is set as true, then all printfs are shown to interact with the user
	if (visible == TRUE) {
		printf("Press any key to see the movements one-by-one: ");
		key = my_get_char();
	}

	character = set_movement(numbers, temporary, position, size_numbers, temp_position, temp_temporary);

	while (game_over == FALSE) {
		switch (character) {
			// In case of the command is 'w'
		case 'w':
			// If the number to which the pointer is pointing is a 9, the game asks for another command
			if ((**position) == 9) {
				// If visible is set as true, then all printfs are shown to interact with the user
				if (visible == TRUE) {
					system("cls");
					printf("[!] This is the maximum number allowed. Command not possible, please try again. \n");
					print_status(numbers, size_numbers, position, number_movements);
					printf("Press any key to see the movements one-by-one: ");
					key = my_get_char();
				}
				character = set_movement(numbers, temporary, position, size_numbers, temp_position, temp_temporary);
			}
			// Otherwise, 1 is added to the number to which the pointer is pointing
			else {
				(**position) = (**position) + 1;
				*number_movements = (*number_movements) + 1;
				// If visible is set as true, then all printfs are shown to interact with the user
				if (visible == TRUE) {
					system("cls");
					print_status(numbers, size_numbers, position, number_movements);
					printf("Press any key to see the movements one-by-one: ");
					key = my_get_char();
				}
				character = set_movement(numbers, temporary, position, size_numbers, temp_position, temp_temporary);
			}
			break;

			// In case of the command is 'a'
		case 'a':
			// If the pointer is pointing to the first position of the array, the game asks for another command
			if (*position == numbers) {
				// If visible is set as true, then all printfs are shown to interact with the user
				if (visible == TRUE) {
					system("cls");
					printf("[!] You are in the very left border. Command not possible, please try again. \n");
					print_status(numbers, size_numbers, position, number_movements);
					printf("Press any key to see the movements one-by-one: ");
					key = my_get_char();
				}
				character = set_movement(numbers, temporary, position, size_numbers, temp_position, temp_temporary);
			}
			// Otherwise, the pointer points to the previous position os the array
			else {
				temporary = temporary--;
				position = &temporary;
				*number_movements = (*number_movements) + 1;
				// If visible is set as true, then all printfs are shown to interact with the user
				if (visible == TRUE) {
					system("cls");
					print_status(numbers, size_numbers, position, number_movements);
					printf("Press any key to see the movements one-by-one: ");
					key = my_get_char();
				}
				character = set_movement(numbers, temporary, position, size_numbers, temp_position, temp_temporary);
			}
			break;

			// In case of the command is 'x'
		case 'x':
			// If the number to which the pointer is pointing is a 0, the game asks for another command
			if ((**position) == 0) {
				// If visible is set as true, then all printfs are shown to interact with the user
				if (visible == TRUE) {
					system("cls");
					printf("[!] This is the minimum number allowed. Command not possible, please try again. \n");
					print_status(numbers, size_numbers, position, number_movements);
					printf("Press any key to see the movements one-by-one: ");
					key = my_get_char();
				}
				character = set_movement(numbers, temporary, position, size_numbers, temp_position, temp_temporary);
			}
			// Otherwise, 1 is removed to the number to which the pointer is pointing
			else {
				(**position) = (**position) - 1;
				*number_movements = (*number_movements) + 1;
				// If visible is set as true, then all printfs are shown to interact with the user
				if (visible == TRUE) {
					system("cls");
					print_status(numbers, size_numbers, position, number_movements);
					printf("Press any key to see the movements one-by-one: ");
					key = my_get_char();
				}
				character = set_movement(numbers, temporary, position, size_numbers, temp_position, temp_temporary);
			}
			break;

			// In case of the command is 'd'
		case 'd':
			// If the pointer is pointing to the last position of the array, the game asks for another command
			if (*position == numbers + (size_numbers - 1)) {
				// If visible is set as true, then all printfs are shown to interact with the user
				if (visible == TRUE) {
					system("cls");
					printf("[!] You are in the very right border. Command not possible, please try again. \n");
					print_status(numbers, size_numbers, position, number_movements);
					printf("Press any key to see the movements one-by-one: ");
					key = my_get_char();
				}
				character = set_movement(numbers, temporary, position, size_numbers, temp_position, temp_temporary);
			}
			// Otherwise, the pointer points to the next position of the array
			else {
				temporary = temporary++;
				position = &temporary;
				*number_movements = (*number_movements) + 1;
				// If visible is set as true, then all printfs are shown to interact with the user
				if (visible == TRUE) {
					system("cls");
					print_status(numbers, size_numbers, position, number_movements);
					printf("Press any key to see the movements one-by-one: ");
					key = my_get_char();
				}
				character = set_movement(numbers, temporary, position, size_numbers, temp_position, temp_temporary);
			}
			break;

			// In case of the number is a pallindrome
		case '*':
			game_over = TRUE;
			break;

		} // End of switch
	} // End of while

	  /* Game_over set as true means that the game was solved AND
	     If visible is set as true, then all printfs are shown to interact with the user */
	if (game_over == TRUE && visible == TRUE) {

		printf("\n----------------------------------\n");
		printf(" ------------ SOLVED ------------ \n");
		printf("----------------------------------");
	}
}

//--------------------------------------------------
// print_status
//--------------------------------------------------

void print_status(int* numbers, int size_number, int** position, int* number_movements) {
	// Method local variables
	int number_spaces = *position - numbers;
	char first_space[21] = { "         " };
	char space[3] = { "  " };

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
	printf("\nNumber of movements: %d.\n", *number_movements);
}

//--------------------------------------------------
// game_palindrome
//--------------------------------------------------

void game_palindrome(int* numbers, int* temporary, int** position, int size_numbers, int* number_movements, int** temp_position,
	int* temp_temporary) {

	set_movement(numbers, temporary, position, size_numbers, temp_position, temp_temporary);
	// Visible is set as false to do not show the steps to the user
	process_movement(numbers, temporary, position, size_numbers, number_movements, temp_position, temp_temporary, FALSE);
}

//--------------------------------------------------
// machine_game_palindrome
//--------------------------------------------------

void machine_game_palindrome(int palindrome_number, int number_size, char commands[], int command_size) {
	// Method local variables. There are one invisible and one visible for each main variable
	int number_movements_invisible = INITIAL_MOVEMENT;
	int* movements_invisible = &number_movements_invisible;

	int number_movements_visible = INITIAL_MOVEMENT;
	int* movements_visible = &number_movements_visible;
	// Creating a space in the memory to the number
	int* palindrome_invisible = (int *)malloc(sizeof(int) * number_size);
	int* temporary_invisible = palindrome_invisible + INITIAL_POSITION;
	int** position_invisible = &temporary_invisible;
	// Creating another space in the memory to the number
	int* palindrome_visible = (int *)malloc(sizeof(int) * number_size);
	int* temporary_visible = palindrome_visible + INITIAL_POSITION;
	int** position_visible = &temporary_visible;

	// Both invisible and visible needs to point to the first position
	int** temp_position_invisible = &palindrome_invisible;
	int* temp_temporary_invisible = palindrome_invisible;

	int** temp_position_visible = &palindrome_visible;
	int* temp_temporary_visible = palindrome_visible;

	// If the size of the number is above 2, then it is not possible to play the game
	if (number_size < 2) {
		printf("[!] You cannot play with numbers above two digits.\n");
	}

	else {
		// Tranform the integer number into an array of integers
		for (int i = (number_size - 1); i >= 0; --i) {
			*(palindrome_invisible + i) = palindrome_number % 10;
			palindrome_number = palindrome_number / 10;
		}
		// Making the visible array the same as the invisible one
		for (int j = 0; j < number_size; j++) {
			*(palindrome_visible + j) = *(palindrome_invisible + j);
		}

		// Verify if the number of commands is different from the number of mandatory commands
		if (command_size != 4) {
			printf("[!] There are 4 mandatory commands. The size is not compatible, please fix it.\n");
		}

		else if (is_command_allowed(commands, command_size) == FALSE) {
			printf(".\n    The commands are not compatible, please fix it.\n");
		}

		else {
			// Analysing in background how many movements it is needed to solve the game optimally
			game_palindrome(palindrome_invisible, temporary_invisible, position_invisible, number_size, movements_invisible,
				temp_position_invisible, temp_temporary_invisible);

			system("cls");
			// Printing the first status of the game
			print_status(palindrome_visible, number_size, position_visible, movements_visible);
			// Printing how many movements it was necessary to solve the game optimally
			printf("------------------------------------\n");
			printf("Solved optimally in %d movements\n", *movements_invisible);
			printf("------------------------------------\n");
			// Running the game interactively, showing step-by-step
			process_movement(palindrome_visible, temporary_visible, position_visible, number_size, movements_visible, temp_position_visible,
				temp_temporary_visible, TRUE);
		} // end else
	} // end else

	free(palindrome_invisible);
	free(palindrome_visible);
}