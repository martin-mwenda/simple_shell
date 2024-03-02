#include "shell.h"

/**
 * print_list - _print linked list
 * @head: The head of the linked list.
 * Return: The size of the linked list.
 */
size_t print_list(myli_t *head)
{
	myli_t *current_node = head;
	int count = 0;
	int length = 0;

	if (head == NULL)
		return (0);
	while (current_node != NULL)
	{
		if (current_node->var == NULL)
		{
			write(STDOUT_FILENO, "(nil)", 5);
			write(STDOUT_FILENO, "\n", 1);
		}
		else
		{
			length = 0;
			while ((current_node->var)[length] != '\0')
				length++;
			write(STDOUT_FILENO, current_node->var, length);
			write(STDOUT_FILENO, "\n", 1);
		}
		current_node = current_node->next;
		count++;
	}
	return (count);
}

/**
 * add_endde - add node to end of linked list
 * @head: pointer to head of linked list
 * @str: data to new node
 * Return: pointer to new linked list
 */
myli_t *add_endde(myli_t **head, char *str)
{
	myli_t *new;
	myli_t *holder;

	if (head == NULL || str == NULL)
		return (NULL);
	new = malloc(sizeof(list_t));
	if (new == NULL)
		return (NULL);
	new->var = dup_s(str);
	new->next = NULL;
	holder = *head;
	if (holder != NULL)
	{
		while (holder->next != NULL)
		{
			holder = holder->next;
		}
		holder->next = new;
	}
	else
	{
		*head = new;
	}
	return (*head);
}

/**
 * del_node_index - removing node at index
 * @head: input head address
 * @index: input index
 * Return: 1 if success, -1 if fail
 */
int del_node_index(myli_t **head, int index)
{
	myli_t *n_head;
	myli_t *holder;
	int count = 0;

	if (*head == NULL)
		return (-1);
	if (index == 0)
	{
		holder = (*head)->next;
		free((*head)->var);
		free(*head);
		*head = holder;
		return (1);
	}
	count = 1;
	n_head = *head;
	while (count < index)
	{
		if (n_head == NULL)
		return (-1);
		n_head = n_head->next;
		count++;
	}
	holder = n_head->next;
	n_head->next = holder->next;
	free(holder->var);
	free(holder);
	return (1);
}

/**
 * fr_linkl - frees linked list
 * @list: linked list
 */
void fr_linkl(myli_t *list)
{
	myli_t *holder;

	while (list != NULL)
	{
		holder = list;
		list = list->next;
		free(holder->var);
		free(holder);
	}
}

