#include "shell.h"

/**
 * _realloc - allocate memory and set all values to 0
 * @ptr: Pointer to the memory previously allocated
 * @oldSize: Size previously allocated.
 * @newSize: New size to reallocate.
 * Return: Pointer to reallocated memory.
 */
void *_realloc(void *ptr, unsigned int oldSize, unsigned int newSize)
{
	void *newPtr;
	unsigned int i;

	if (newSize == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (newSize == oldSize)
		return (ptr);
	newPtr = malloc(newSize);
	if (newPtr == NULL)
		return (NULL);
	for (i = 0; i < oldSize && i < newSize; i++)
		*((char *)newPtr + i) = *((char *)ptr + i);
	free(ptr);
	return (newPtr);
}

/**
 * st_cat - Concatenate two strings.
 * @dest: String to be appended to.
 * @src: String to append.
 * Return: Concatenated string.
 */
char *st_cat(char *dest, char *src)
{
	int dest_len = 0;
	int src_len = 0;
	int j = 0;

	while (dest[dest_len] != '\0')
	{
		dest_len++;
	}
	while (src[src_len] != '\0')
	{
		src_len++;
	}
	dest = _realloc(dest, dest_len, dest_len + src_len + 1);
	while (src[j] != '\0')
	{
		dest[dest_len] = src[j];
		dest_len++;
		j++;
	}
	dest[dest_len] = '\0';
	return (dest);
}

