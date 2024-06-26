#ifndef MONTY_H
#define MONTY_H

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

extern stack_t *head;
typedef void (*op_func)(stack_t **, unsigned int);

void o_file(char *file_name);
int p_line(char *buffer, int line_number, int format);
void r_file(FILE *);
int len_chars(FILE *);
void f_fun(char *, char *, int, int);

stack_t *create_n(int n);
void free_n(void);
void p_stack(stack_t **, unsigned int);
void add_stack(stack_t **, unsigned int);
void add_queue(stack_t **, unsigned int);

void c_fun(op_func, char *, char *, int, int);

void p_top(stack_t **, unsigned int);
void po_top(stack_t **, unsigned int);
void nop(stack_t **, unsigned int);
void swap_n(stack_t **, unsigned int);

void add_n(stack_t **, unsigned int);
void sub_n(stack_t **, unsigned int);
void div_n(stack_t **, unsigned int);
void mul_n(stack_t **, unsigned int);
void mod_n(stack_t **, unsigned int);

void p_char(stack_t **, unsigned int);
void p_str(stack_t **, unsigned int);
void rotl(stack_t **, unsigned int);

void erro(int err_code, ...);
void m_erro(int err_code, ...);
void s_erro(int err_code, ...);
void rotr(stack_t **, unsigned int);


#endif
