#include "visible.h"

//--------------------------------------------------
// generate_number
//--------------------------------------------------

int generate_number(int initial_number, int final_number) {
	int number = (rand() % (final_number - initial_number)) + initial_number;

	return number;
}
/* Note: Do not forget to include the following instruction at the beginning of your main() method:
srand(time(NULL));
*/

//--------------------------------------------------
// my_getchar
//--------------------------------------------------

char my_get_char() {
	char my_char;
	int b = 0;
	char dummy_char;

	my_char = getchar();

	while (b == 0) {
		dummy_char = getchar();
		if (dummy_char == '\n')
			b = 1;
	}

	return my_char;
}

//--------------------------------------//
//	split_a_string_by_pattern			//	
//--------------------------------------//
char** split_a_string_by_pattern(char string[], char* pattern, int* number_items) {
	//0. The variable we are going to return
	char** items = NULL;

	//1. At the beginning we have not processed any word, thus:
	//current_word = 0 and current_char = 0 (at the beginning of string).
	unsigned int current_char = 0;
	(*number_items) = 0;

	//2. While we have not processed the entire string
	while (current_char < strlen(string)) {
		//2.1. We make a copy of string to work with it. 
		char* my_auxiliar_string = (char*)malloc((strlen(string) + 1) * sizeof(char));
		strcpy(my_auxiliar_string, &string[current_char]);

		//2.2. We look for the next blank space
		char* p = strstr(my_auxiliar_string, pattern);

		//2.3. We check for the next blank space, to measure the length of the next word of string
		int dist;
		if (p != NULL) {
			//If there is such a blank space, we measure the distance to the start of the string to measure the length of the word.
			dist = p - &my_auxiliar_string[0];
		}
		else {
			//If there is not such a blank space, we take the length of the string as the length of the word.
			dist = strlen(my_auxiliar_string);
		}

		//2.4. We asign the word to our array of words
		char* q = (char*)malloc((dist + 1) * sizeof(char));
		strncpy(q, my_auxiliar_string, dist);
		q[dist] = '\0';

		//EXTRA1. We increase the number of words in our array of words
		char** new_items = (char**)realloc(items, ((*number_items) + 1) * sizeof(char*));
		if (new_items != NULL) {
			items = new_items;
			items[(*number_items)] = q; //We make words[(*num_words)] to point to q.
		}

		//2.5. We update the number of words processed and the next_char we are pointing at in string.
		(*number_items) = (*number_items) + 1;
		current_char = current_char + (dist + 1);

	}

	return items;

}

//--------------------------------------//
//	parse_file_content					//	
//--------------------------------------//
char*** parse_file_content(char string[], int* number_lines, int** number_words_per_line) {
	char*** f_content = NULL;

	//1. Split the string into lines
	(*number_lines) = 0;
	char** lines = split_a_string_by_pattern(string, "\n", number_lines);

	//2. Create the variable 'content' to host the lines of the file a
	f_content = (char***)malloc((*number_lines) * sizeof(char**));
	int* f_words_per_line = (int*)malloc((*number_lines) * sizeof(int*));

	//4. For each line of the file, split it into words and add it to content
	for (int i = 0; i < (*number_lines); i++) {
		f_content[i] = split_a_string_by_pattern(lines[i], "\t", &f_words_per_line[i]);
	}

	//5. Make num_words_per_line to point to f_words_per_line
	(*number_words_per_line) = &f_words_per_line[0];

	return f_content;

}

//---------------------------------------------//
//	read_entire_file_and_store_it_in_a_string  //	
//---------------------------------------------//
char* read_entire_file_and_store_it_in_a_string(char name[]) {
	//1. We create a string of size 1
	int length = 0;
	char* s = (char*)malloc((length + 1) * sizeof(char));

	//2. We open the file for reading and set our loop control variable
	FILE* ifp = fopen(name, "r");
	int finish = 0;

	if (ifp == NULL) {
		printf("[ERROR] File couldn't be found\n");
		s = NULL;

		free(s);
	}

	else {
		//3. While we haven't parsed the entire file
		while (finish == 0) {

			//3.1. We read a new character from the file
			char c = getc(ifp);

			//3.2. If the character is not EOF we add the character to s and adjust the size of s with realloc
			if (c != EOF) {
				s[length] = c;
				length = length + 1;
				char* new_s = (char*)realloc(s, (length + 1) * sizeof(char));
				if (new_s != NULL)
					s = new_s;
			}
			//3.3. If the character is EOF we conclude the parsing and set the end character to our string
			else {
				finish = 1;
				s[length] = '\0';
			}
		}
	}

	return s;

}

//--------------------------------------------------
// select_option
//--------------------------------------------------

int select_option() {
	char _option[30];
	int option;

	//Clean the screen
	system("cls");

	printf("--------------------------------------------------------------------\n");
	printf("			         MENU\n");
	printf("--------------------------------------------------------------------\n");
	printf("1. Load palindromes from file\n");
	printf("2. Print the numbers of the list\n");
	printf("3. Check if palindrome is in the list\n");
	printf("4. Show info of a number\n");
	printf("5. Add a palindrome from keyboard\n");
	printf("6. Solve a palindrome\n");
	printf("7. Remove a palindrome\n");
	printf("8. Sort the palindromes by their number of movements to be solved\n");
	printf("9. Write the list to a file\n");
	printf("0. Exit\n");

	int repeat = 1;

	while (repeat == 1) {
		printf("\nSelect your option: ");
		scanf("%s", &_option);
		option = atoi(_option);

		if ((option >= 0) && (option <= 9))
			repeat = 0;
	}

	return option;
}