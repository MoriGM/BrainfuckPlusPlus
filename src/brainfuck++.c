#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "brainfuck++.h"

struct CODE_MAP **code_maps;
int code_map_count;

struct CODE_COMMAND **code_commands;
int code_command_count;

int8_t ram[MAX_RAM_SIZE];
short ram_pointer;

char* code_file;
int code_pointer;

int stack[MAX_STACK_SIZE];
int stack_pointer;

struct CODE_POS **code_pos;
int code_pos_count;


int main(int argc, char** argv)
{
	if (argc == 2)
	{
		init_stack();
		init_ram();
		init_codes();
		init_commands();
		init_code_pos();
		init_file(argv[1]);
		start_programm();
	}
	else
		printf("%s <file>\n", argv[0]);
	return EXIT_SUCCESS;
}

void init_stack()
{
	stack_pointer = 0;
	for (int i = 0; i < MAX_STACK_SIZE;i++)
		stack[i] = 0;
}

void init_ram()
{
	ram_pointer = 0;
	for (int i = 0;i < MAX_RAM_SIZE;i++)
		ram[i] = 0;
}

void init_codes()
{
	code_maps = malloc(sizeof(struct CODE_MAP) * 1000);
	code_map_count = 0;

	add_code(&code_plus, '+');
	add_code(&code_minus, '-');
	add_code(&code_first_ram, '0');
	add_code(&code_left, '<');
	add_code(&code_right, '>');
	add_code(&code_loop, '[');
	add_code(&code_loop, ']');
	add_code(&code_print, '.');
	add_code(&code_scan, ',');
	add_code(&code_ram_clean, 'c');
	add_code(&code_command, 'i');
}

void init_commands()
{
	code_commands = malloc(sizeof(struct CODE_COMMAND) * 127);
	code_command_count = 0;

	add_command(&command_multiply, COMMAND_MULTIPLY);
	add_command(&command_divided, COMMAND_DIVIDED);
	add_command(&command_random, COMMAND_RANDOM);
	add_command(&command_newline, COMMAND_NEWLINE);
	add_command(&command_inc_ten, COMMAND_INC_TEN);
	add_command(&command_save_pos, COMMAND_SAVE_POS);
	add_command(&command_load_pos, COMMAND_LOAD_POS);
}

void init_code_pos()
{
	code_pos_count = 0;
	code_pos = malloc(sizeof(struct CODE_POS*) * 128);
}

void start_programm()
{
	code_pointer = 0;
	do
	{
		char code = code_file[code_pointer++];
		call_code(code);
	} while(code_pointer < strlen(code_file));
}

void init_file(char* text)
{
	FILE* file = fopen(text, "r");
	if (file == NULL)
	{
		printf("File %s not found\n", text);
		exit(EXIT_SUCCESS);
		return;
	}
	code_file = malloc(sizeof(char) * 10000);
	int code_len = 0;
	do
	{
		char c;
		fscanf(file, "%c", &c);
		if (feof(file))
			break;
		if (allowed_code(c))
			code_file[code_len++] = c;
	} 
	while(!feof(file));
	code_file[code_len] = '\0';
}

void add_code(void(*code)(), char text)
{
	code_maps[code_map_count] = malloc(sizeof(struct CODE_MAP));
	code_maps[code_map_count]->code = code;
	code_maps[code_map_count]->text = text;
	code_map_count = code_map_count + 1;
}

void add_command(void(*command)(),int8_t op)
{
	code_commands[code_command_count] = malloc(sizeof(struct CODE_COMMAND));
	code_commands[code_command_count]->command = command;
	code_commands[code_command_count]->op = op;
	code_command_count = code_command_count + 1;
}

void call_code(char code)
{
	for (int i = 0;i < code_map_count;i++)
		if (code_maps[i]->text == code)
			code_maps[i]->code();
}

void call_command(int8_t op)
{
	for (int i = 0;i < code_command_count;i++)
		if (code_commands[i]->op == op)
			code_commands[i]->command();
}


int allowed_command(int8_t op)
{
	for (int i = 0;i < code_command_count;i++)
		if (code_commands[i]->op == op)
			return 1;
	return 0;
}

int allowed_code(char c)
{
	for (int i = 0;i < code_map_count;i++)
		if (c == code_maps[i]->text)
			return 1;
	return 0;
}

void code_plus()
{
	ram[RP] = ram[RP] + 1;
}

void code_minus()
{
	ram[RP] = ram[RP] - 1;
}

void code_first_ram()
{
	ram_pointer = 0;
}
void code_left()
{
	if (RP > 0)
		RP = RP - 1;
}

void code_right()
{
	if (RP < MAX_RAM_SIZE)
		RP = RP + 1;
}

void code_loop()
{
	int _code_pos = 1, _last_code_pos = code_pointer;
	do
	{
		_code_pos += 1;
	} 
	while(code_file[code_pointer + _code_pos] != ']');

	while (ram[RP] != 0)
	{
		for (int i = 0;i < _code_pos;i++)
		{
			code_pointer = _last_code_pos + i;
			call_code(code_file[code_pointer]);
		}
	}
	code_pointer = _last_code_pos + _code_pos + 1;
}

void code_print()
{
	printf("%c", ram[RP]);
}

void code_scan()
{
	char c;
	scanf("%c", &c);
	ram[RP] = c;
}

void code_ram_clean()
{
	ram[RP] = 0;
}

void code_command()
{
	if (allowed_command(ram[RP]))
		call_command(ram[RP]);
}

void command_multiply()
{
	ram[RP + 1] = ram[RP + 1] * ram[RP + 2];
}

void command_divided()
{
	int div = ram[RP + 1] / ram[RP + 2];
	ram[RP + 2] = ram[RP + 1] % ram[RP + 2];
	ram[RP + 1] = div;
}

void command_random()
{
	srand(time(NULL));
	ram[RP + 1] = (rand() & 0xFF);
}

void command_newline()
{
	printf("\n");
}

void command_inc_ten()
{
	ram[RP + 1] = ram[RP + 1] + 10;
}

void command_save_pos()
{
	if (!exists_code_pos(ram[RP + 1]))
	{
		struct CODE_POS *cp = malloc(sizeof(struct CODE_POS));
		cp->pos = code_pointer;
		cp->number = ram[RP + 1];
		code_pos[code_pos_count++] = cp;
	}
	else
		get_code_pos(ram[RP + 1])->pos = code_pointer;
}

void command_load_pos()
{
	if (exists_code_pos(ram[RP + 1]))
		code_pointer = remove_code_pos(ram[RP + 1]);
}
