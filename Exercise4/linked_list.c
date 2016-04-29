#include "linked_list.h"
#include "pal.h"

//--------------------------------------------------
// load_palNode_list_from_file 
//--------------------------------------------------
struct palNode* load_palNode_list_from_file(char file_name[]) {
	
	struct palNode* head = NULL;
	struct palNode* tail = NULL;
	struct palNode* new_node = NULL;
	int number_lines;
	int* number_words_per_line = NULL;
	
	char* text = read_entire_file_and_store_it_in_a_string(file_name);
	
	if (text == NULL) {
		printf("Please, double check the file name and type again\n");
		printf("Is '%s' the correct name of your file?\n\n", file_name);
	}
	
	else {
		char** word = NULL;
		char*** palindrome = parse_file_content(text, &number_lines, &number_words_per_line);

		for (int i = 0; i < number_lines; i++) {
			word = palindrome[i];

			new_node = (struct palNode*) malloc(sizeof(struct palNode));
			new_node->number = atoi(word[0]);
			new_node->pointer_index = atoi(word[1]);

			if (number_words_per_line[i] == 3) {
				new_node->solving_array = word[2];
				new_node->solved = 1;
			}

			else {
				new_node->solving_array = NULL;
				new_node->solved = 0;
			}

			if (head == NULL) {
				head = new_node;
			}

			else {
				tail = find_last_node(head);
				tail->next = new_node;
			}

			new_node->next = NULL;
		}

		printf("[DONE] File uploaded successfully\n");
	}

	return head;
}

//--------------------------------------------------
// print_numbers_of_list 
//--------------------------------------------------

void print_numbers_of_list(struct palNode* head) {
	struct palNode* current_node = head;
	int lenght = get_length_of_list(head);
	int index = 0;

	if (lenght == 0) {
		printf("[ERROR] List is empty\n");
	}

	else {
		printf("----- Lenght of the list: %d -----\n\n", lenght);

		current_node = head;
		while (current_node != NULL) {
			printf("Number [%d] = %d\n", index, current_node->number);
			index = index + 1;
			current_node = current_node->next;
		}

		printf("\n");
	}
}

//--------------------------------------------------
// find_palindrome_in_list 
//--------------------------------------------------

struct palNode* find_palindrome_in_list(struct palNode* head, int number) {
	struct palNode* current_node = head;
	int found = 0;

	while (current_node != NULL) {

		if (number == current_node->number) {
			found = 1;
			break;
		}

		current_node = current_node->next;
	}

	if (found == 0) {
		current_node = NULL;
	}

	return current_node;
}

//--------------------------------------------------
// show_info_of_a_number 
//--------------------------------------------------

void show_info_of_a_number(struct palNode* head, int number) {
	struct palNode* current_node = find_palindrome_in_list(head, number);
	int found = 0;

	if (current_node != NULL) {
		printf("----- Information -----\n\n");
		printf("Number: %d\n", current_node->number);
		printf("Pointer at index: %d\n", current_node->pointer_index);

		if (current_node->solved == 1) {
			printf("Solved in %d movements: %s\n\n", strlen(current_node->solving_array), current_node->solving_array);
		}

		else {
			printf("Unsolved\n\n");
		}
	}

	else {
		printf("[ERROR] The number is not in the list\n");
	}
}

//--------------------------------------------------
// add_palNode_from_keyboard 
//--------------------------------------------------

struct palNode* add_palNode_from_keyboard(struct palNode* head, int number, int position) {
	struct palNode* tail = find_last_node(head);
	struct palNode* new_node = (struct palNode*)malloc(sizeof(struct palNode));
	struct palNode* found = find_palindrome_in_list(head, number);
	int number_size = get_size_of_number(number);

	if ( found == NULL) {
		// For random purposes
		srand((unsigned int)time(NULL));

		if (position == -1) {
			position = generate_number(0, number_size);
		}

		new_node->number = number;
		new_node->pointer_index = position;
		new_node->solved = 0;
		new_node->solving_array = NULL;

		if (head == NULL) {
			head = new_node;
		}

		else {
			tail->next = new_node;
		}

		new_node->next = NULL;

		printf("[DONE] Number added successfully\n");
	}

	else {
		printf("[ERROR] The number already exists in the list\n");
	}

	return head;
}

//--------------------------------------------------
// solve_a_palindrome 
//--------------------------------------------------

struct palNode* solve_a_palindrome(struct palNode* head, int number) {
	int number_movements = 0;
	int number_size = get_size_of_number(number);
	int *position = NULL;
	int *temporary_array = (int *)malloc(256 * sizeof(int));
	struct palNode *selected_node = find_palindrome_in_list(head, number);
	
	if (selected_node != NULL) {
		if (selected_node->solving_array != NULL) {
			printf("[ERROR] Palindrome is already solved\n");
		}

		else {
			initialise_array(temporary_array, number_size, number);

			position = &temporary_array[0] + selected_node->pointer_index;
			char* solving_movements = get_solving_array(temporary_array, number_size, position, &number_movements);

			selected_node->solved = 1;
			selected_node->solving_array = solving_movements;
			printf("[DONE] Palindrome solved successfully\n");

			free(temporary_array);
		}
	}

	else {
		printf("[ERROR] The number is not in the list\n");
	}
	
	return head;
}

//--------------------------------------------------
// find_previous_node 
//--------------------------------------------------

struct palNode* find_previous_node(struct palNode* head, struct palNode* pointAtMe) {
	struct palNode *current_node = head;
	struct palNode *previous_node = NULL;

	while (current_node != NULL) {
		if (current_node->next == pointAtMe) {
			previous_node = current_node;
			break;
		}

		current_node = current_node->next;
	}

	return previous_node;
}

//--------------------------------------------------
// find_last_node 
//--------------------------------------------------

struct palNode* find_last_node(struct palNode* head) {
	struct palNode *current_node = head;
	struct palNode *tail = NULL;

	while (current_node != NULL) {
		if (current_node->next == NULL) {
			tail = current_node;
		}
		current_node = current_node->next;
	}

	return tail;
}

//--------------------------------------------------
// remove_a_palindrome 
//--------------------------------------------------

struct palNode* remove_a_palindrome(struct palNode* head, int number) {
	struct palNode *current_node = find_palindrome_in_list(head, number);
	struct palNode *previous_node = find_previous_node(head, current_node);

	if (current_node != NULL) {
		if (current_node == head) {
			head = current_node->next;
		}

		else {
			previous_node->next = current_node->next;
		}

		free(current_node);
		printf("[DONE] Palindrome removed successfully\n");
	}

	else {
		printf("[ERROR] The number is not in the list\n");
	}

	return head;
}

//--------------------------------------------------
// get_length_of_list 
//--------------------------------------------------

int get_length_of_list(struct palNode* head) {
	struct palNode* current_node = head;
	int lenght = 0;

	while (current_node != NULL) {
		lenght = lenght + 1;
		current_node = current_node->next;
	}

	return lenght;
}

//--------------------------------------------------
// get_size_of_number
//--------------------------------------------------

int get_size_of_number(int number) {
	char number_as_string[256];
	int size;

	sprintf(number_as_string, "%d", number);
	size = strlen(number_as_string);

	return size;
}

//--------------------------------------------------
// sort_the_list 
//--------------------------------------------------

struct palNode* sort_the_list(struct palNode* head, int length) {
	struct palNode *current_node = head;
	struct palNode *temporary_node = NULL;
	int current_number_movements = 0;
	int next_number_movements = 0;

	if (length == 0) {
		printf("[ERROR] No need to sort. List is empty\n");
	}

	else if (length == 1) {
		printf("[ERROR] No need to sort. List has just one element\n");
	}

	else {
		for (int i = 0; i < length - 1; i++) {
			while (current_node->next != NULL) {
				if (current_node->solving_array != NULL && current_node->next->solving_array != NULL) {
					current_number_movements = strlen(current_node->solving_array);
					next_number_movements = strlen(current_node->next->solving_array);
				}

				else {
					if (current_node->solving_array == NULL && current_node->next->solving_array == NULL) {
						current_number_movements = 1000000;
						next_number_movements = 1000000;
					}

					else if (current_node->solving_array == NULL) {
						current_number_movements = 1000000;
						next_number_movements = strlen(current_node->next->solving_array);
					}

					else if (current_node->next->solving_array == NULL) {
						current_number_movements = strlen(current_node->solving_array);
						next_number_movements = 1000000;
					}

				}

				if (current_number_movements > next_number_movements) {
					temporary_node = current_node;
					current_node = current_node->next;

					if (find_previous_node(head, temporary_node) != NULL) {
						find_previous_node(head, temporary_node)->next = current_node;
					}

					else {
						head = current_node;
					}

					temporary_node->next = current_node->next;
					current_node->next = temporary_node;
				}

				current_node = current_node->next;
			}

			current_node = head;

		}

		printf("[DONE] List sorted successfully\n");
	}

	return head;
}

//--------------------------------------------------
// write_to_file 
//--------------------------------------------------

void write_to_file(char file_name[], struct palNode* head) {
	struct palNode *current_node = head;
	
	if (head == NULL) {
		printf("[ERROR] List is empty. No elements to write\n");
	}

	else {
		FILE *database = fopen(file_name, "w");

		if (database == NULL) {
			printf("[ERROR] File couldn't be open\n");
		}

		else {
			while (current_node != NULL) {
				if (current_node->solving_array != NULL) {
					fprintf(database, "%d\t %d\t %s\n", current_node->number, current_node->pointer_index, current_node->solving_array);
				}

				else {
					fprintf(database, "%d\t %d\n", current_node->number, current_node->pointer_index);
				}

				current_node = current_node->next;
			}

			fclose(database);
			printf("[DONE] List writen in '%s' successfully\n", file_name);
		}
	}
}