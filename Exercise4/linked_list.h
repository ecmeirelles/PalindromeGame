#include "pal.h"
#include "visible.h"
#include <stdlib.h>
#include <string.h>

//--------------------------------------------------
// struct palNode definition 
//--------------------------------------------------

struct palNode {
	int number;
	int pointer_index;
	char* solving_array;
	int solved;
	struct palNode* next;
};

//--------------------------------------------------
// load_palNode_list_from_file 
//--------------------------------------------------
struct palNode* load_palNode_list_from_file(char file_name[]);

//--------------------------------------------------
// print_numbers_of_list 
//--------------------------------------------------

void print_numbers_of_list(struct palNode* head);

//--------------------------------------------------
// find_palindrome_in_list 
//--------------------------------------------------

struct palNode* find_palindrome_in_list(struct palNode* head, int number);

//--------------------------------------------------
// show_info_of_a_number 
//--------------------------------------------------

void show_info_of_a_number(struct palNode* head, int number);

//--------------------------------------------------
// add_palNode_from_keyboard 
//--------------------------------------------------

struct palNode* add_palNode_from_keyboard(struct palNode* head, int number, int position);

//--------------------------------------------------
// solve_palindrome_of_node 
//--------------------------------------------------

char* solve_palindrome_of_node(struct palNode* current_node);

//--------------------------------------------------
// solve_a_palindrome 
//--------------------------------------------------

struct palNode* solve_a_palindrome(struct palNode* head, int number);

//--------------------------------------------------
// find_previous_node 
//--------------------------------------------------

struct palNode* find_previous_node(struct palNode* head, struct palNode* pointAtMe);

//--------------------------------------------------
// find_last_node 
//--------------------------------------------------

struct palNode* find_last_node(struct palNode* head);

//--------------------------------------------------
// remove_a_palindrome 
//--------------------------------------------------

struct palNode* remove_a_palindrome(struct palNode* head, int number);

//--------------------------------------------------
// get_length_of_list 
//--------------------------------------------------

int get_length_of_list(struct palNode* head);

//--------------------------------------------------
// get_size_of_number
//--------------------------------------------------

int get_size_of_number(int number);

//--------------------------------------------------
// sort_the_list 
//--------------------------------------------------

struct palNode* sort_the_list(struct palNode* head, int length);

//--------------------------------------------------
// write_to_file 
//--------------------------------------------------

void write_to_file(char file_name[], struct palNode* head);