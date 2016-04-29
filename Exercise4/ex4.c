#include "linked_list.h"
#include "visible.h"
#include <stdlib.h>

//--------------------------------------//
//	main								//	
//--------------------------------------//
int main(int argc, char* argv[]) {

	int finish = 0;
	struct palNode* head = NULL;

	while (finish == 0) {
		//Print the menu
		int repeat = 1;
		int option = select_option();

		char file_name[256];
		char _number[256];
		char _position[256];
		char c;
		int number;
		int position;

		switch (option) {
		
		//1. Load palindromes from file
		case 1:
			printf("Enter the file name from which you want to read: ");
			scanf("%s", &file_name);

			//Clear the screen
			system("cls");

			head = load_palNode_list_from_file(file_name);

			printf("Press any key to continue ");
			c = my_get_char();

			break;

		//2. Print the numbers of the list
		case 2:
			//Clear the screen
			system("cls");

			print_numbers_of_list(head);

			printf("Press any key to continue ");
			c = my_get_char();

			break;

		//3. Check if palindrome is in the list
		case 3:
			printf("Enter the number for your new palindrome: ");
			scanf("%s", &_number);
			number = atoi(_number);

			//Clear the screen
			system("cls");

			struct palNode* node = find_palindrome_in_list(head, number);
			if (node == NULL) {
				printf("[ERROR] The number is not in the list\n");
			}
				
			else {
				printf("[DONE] The number is in the list\n");
			}

			printf("Press any key to continue ");
			c = my_get_char();

			break;

		//4. Show info of a number
		case 4:
			printf("Enter palindrome number which you want to see information: ");
			scanf("%s", &_number);
			number = atoi(_number);

			//Clear the screen
			system("cls");

			show_info_of_a_number(head, number);

			printf("Press any key to continue ");
			c = my_get_char();

			break;

		//5. Add a palindrome from keyboard
		case 5:
			printf("Enter the number for your new palindrome: ");
			scanf("%s", &_number);
			number = atoi(_number);

			printf("\nPS. Enter -1 for generate it randomly\n");
			printf("Enter the index at which you want the pointer start: ");
			scanf("%s", &_position);
			position = atoi(_position);

			//Clear the screen
			system("cls");

			head = add_palNode_from_keyboard(head, number, position);

			printf("Press any key to continue ");
			c = my_get_char();

			break;

		//6. Solve a palindrome
		case 6:
			printf("Enter the number of the palindrome you want to solve: ");
			scanf("%s", &_number);
			number = atoi(_number);

			//Clear the screen
			system("cls");

			head = solve_a_palindrome(head, number);

			printf("Press any key to continue ");
			c = my_get_char();

			break;

		//7. Remove a palindrome
		case 7:
			printf("Enter the palindrome number you want to remove: ");
			scanf("%s", &_number);
			number = atoi(_number);

			//Clear the screen
			system("cls");

			head = remove_a_palindrome(head, number);

			printf("Press any key to continue ");
			c = my_get_char();

			break;

		//8. Sort the palindromes by their number of movements to be solved
		case 8:
			//Clear the screen
			system("cls");

			number = get_length_of_list(head);
			head = sort_the_list(head, number);

			printf("Press any key to continue ");
			c = my_get_char();

			break;

		//9. Save the palindromes in a file
		case 9:
			printf("Enter the file name to which you want to write: ");
			scanf("%s", &file_name);

			//Clear the screen
			system("cls");

			write_to_file(file_name, head);

			printf("Press any key to continue ");
			c = my_get_char();

			break;

		//0. Exit the program
		case 0:
			finish = 1;
			break;
		}
	}

	return 0;

}