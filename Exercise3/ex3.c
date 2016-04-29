#include "pal.h"

int main() {

	int palindrome_number = 15423670;
	int number_size = 8;
	char commands[] = { 'a','d','w','x' };
	int commands_size = 4;

	machine_game_palindrome(palindrome_number, number_size, commands, commands_size);

	return 0;
}