#ifndef BRAINFUCKPP_H
#define BRAINFUCKPP_H

#include <stdint.h>

#define MAX_RAM_SIZE 1024
#define MAX_STACK_SIZE 128
#define RP ram_pointer


#define COMMAND_MULTIPLY 10
#define COMMAND_DIVIDED 11
#define COMMAND_RANDOM 12
#define COMMAND_NEWLINE 13
#define COMMAND_INC_TEN 14
#define COMMAND_SAVE_POS 15
#define COMMAND_LOAD_POS 16


struct CODE_MAP
{
	void(*code)();
	char text;
};

struct CODE_COMMAND
{
	void(*command)();
	int8_t op;
};

struct CODE_POS
{
	uint32_t pos;
	int8_t number;
};


struct CODE_POS* get_code_pos(int number);
int exists_code_pos(int number);
int remove_code_pos(int number);

void init_stack();
void init_ram();
void init_codes();
void init_commands();
void init_code_pos();
void init_file(char* text);

void start_programm();
void stop_programm(void);

void add_code(void(*code)(), char text);
void add_command(void(*command)(),int8_t op);

void call_code(char code);
void call_command(int8_t op);

int allowed_code(char c);
int allowed_command(int8_t op);

void code_plus();
void code_minus();
void code_first_ram();
void code_left();
void code_right();
void code_loop();
void code_print();
void code_scan();
void code_ram_clean();
void code_command();


void command_multiply();
void command_divided();
void command_random();
void command_newline();
void command_inc_ten();
void command_save_pos();
void command_load_pos();


#endif
