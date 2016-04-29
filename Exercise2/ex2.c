#include "pal.h"

int main() {
	int palindrome_number = 1234567890;
	int number_size = 10;
	char commands[] = { 'a','d','w','x', 'h', 'k', 'u', 'm' };
	int commands_size = 8;

	user_game_palindrome(palindrome_number, number_size, commands, commands_size);

	return 0;
}