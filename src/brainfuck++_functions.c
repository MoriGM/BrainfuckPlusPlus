#include <stdlib.h>

#include "brainfuck++.h"

extern struct CODE_POS **code_pos;
extern int code_pos_count;

struct CODE_POS* get_code_pos(int number)
{
	for (int i = 0; i < code_pos_count;i++)
		if (code_pos[i]->number == number)
			return code_pos[i];
	return NULL;
}

int exists_code_pos(int number)
{
	return get_code_pos(number) != NULL;
}

int remove_code_pos(int number)
{
	for (int i = 0;i < code_pos_count;i++)
	{
		if (code_pos[i]->number == number)
		{
			number = code_pos[i]->pos;
			code_pos[i] = code_pos[(code_pos_count - 1)];
			code_pos[(code_pos_count--)] = NULL;
			return number;
		}
	}
	
	return -1;
}
