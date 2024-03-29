#include "monty.h"

/**
 * o_file - opens a file
 *
 * @file_name: the file namepath
 * Return: void
 */
void o_file(char *file_name)
{
	FILE *fd = fopen(file_name, "r");

	if (file_name == NULL || fd == NULL)
		erro(2, file_name);

	r_file(fd);
	fclose(fd);
}

/**
 * r_file - reads a file
 *
 * @fd: pointer to file descriptor
 * Return: void
 */
void r_file(FILE *fd)
{
	int l_number, format = 0;
	char *buff = NULL;
	size_t leng = 0;

	for (l_number = 1; getline(&buff, &leng, fd) != -1; l_number++)
	{
		format = p_line(buff, l_number, format);
	}
	free(buff);
}

/**
 * p_line - Separates each line into tokens to determine
 * which function to call
 *
 * @buffer: line from the file
 * @line_number: line number
 * @format:  storage format. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 *
 * Return: Returns 0 if the opcode is stack. 1 if queue.
 */
int p_line(char *buffer, int line_number, int format)
{
	char *opcode, *value;
	const char *delim = "\n ";

	if (buffer == NULL)
		erro(4);

	opcode = strtok(buffer, delim);
	if (opcode == NULL)
		return (format);
	value = strtok(NULL, delim);

	if (strcmp(opcode, "stack") == 0)
		return (0);
	if (strcmp(opcode, "queue") == 0)
		return (1);

	f_fun(opcode, value, line_number, format);
	return (format);
}

/**
 * f_fun - find the appropriate function for the opcode
 *
 * @opcode: opcode
 * @value: argument of opcode
 * @format:  storage format. If 0 Nodes will be entered as a stack.
 * @ln: line number
 * if 1 nodes will be entered as a queue.
 *
 * Return: void
 */
void f_fun(char *opcode, char *value, int ln, int format)
{
	int i;
	int flag;

	instruction_t func_list[] = {
		{"push", add_stack},
		{"pall", p_stack},
		{"pint", p_top},
		{"pop", po_top},
		{"nop", nop},
		{"swap", swap_n},
		{"add", add_n},
		{"sub", sub_n},
		{"div", div_n},
		{"mul", mul_n},
		{"mod", mod_n},
		{"pchar", p_char},
		{"pstr", p_str},
		{"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL}
	};

	if (opcode[0] == '#')
		return;

	for (flag = 1, i = 0; func_list[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, func_list[i].opcode) == 0)
		{
			c_fun(func_list[i].f, opcode, value, ln, format);
			flag = 0;
		}
	}
	if (flag == 1)
		erro(3, ln, opcode);
}

/**
 * c_fun - Calls the required function.
 *
 * @func: Pointer to the function that is about to be called.
 * @op: string representing the opcode.
 * @val: string representing a numeric value.
 * @ln: line numeber for the instruction.
 * @format: Format specifier. If 0 Nodes will be entered as a stack.
 * if 1 nodes will be entered as a queue.
 */
void c_fun(op_func func, char *op, char *val, int ln, int format)
{
	stack_t *node;
	int flag;
	int i;

	flag = 1;
	if (strcmp(op, "push") == 0)
	{
		if (val != NULL && val[0] == '-')
		{
			val = val + 1;
			flag = -1;
		}
		if (val == NULL)
			erro(5, ln);
		for (i = 0; val[i] != '\0'; i++)
		{
			if (isdigit(val[i]) == 0)
				erro(5, ln);
		}
		node = create_n(atoi(val) * flag);
		if (format == 0)
			func(&node, ln);
		if (format == 1)
			add_queue(&node, ln);
	}
	else
		func(&head, ln);
}
