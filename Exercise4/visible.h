#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>

//--------------------------------------------------
// generate_number
//--------------------------------------------------
/*
Generates a random number in the interval (initial_number, final_number)
Note: Do not forget to include the following instruction at the beginning of your main() method:
srand(time(NULL));
*/

int generate_number(int initial_number, int final_number);

//--------------------------------------------------
// my_getchar
//--------------------------------------------------

char my_get_char();

//--------------------------------------//
//	split_a_string_by_pattern			//	
//--------------------------------------//

char** split_a_string_by_pattern(char string[], char* pattern, int* number_items);

//--------------------------------------//
//	parse_file_content					//	
//--------------------------------------//

char*** parse_file_content(char string[], int* number_lines, int** number_words_per_line);

//---------------------------------------------//
//	read_entire_file_and_store_it_in_a_string  //	
//---------------------------------------------//

char* read_entire_file_and_store_it_in_a_string(char name[]);

//--------------------------------------------------
// select_option
//--------------------------------------------------

int select_option();