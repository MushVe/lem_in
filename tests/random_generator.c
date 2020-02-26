/**
 * Wrapper around rand which bound the value
 */
int	rand_wrapper(int lower, int upper)
{
	return rand() % (upper - lower + 1) + lower;
}

/**
 * Generate a random length string from an int array
 * storing rand ascii values
 */
char *random_string(char *rand_values, int rand_size, int str_size)
{
	if (rand_size != str_size)
		return (NULL);

	char *random_string = calloc(str_size + 1, 1);
	if (!random_string)
		return (NULL);

	memcpy(random_string, rand_values, str_size);

	return (random_string);
}
/**
 * Generate a variable length char array of random values
 * values can be bounded
 */
char *random_values(int array_size, int lower, int upper)
{
	char *rand_array = malloc(sizeof(char) * array_size);
	if (!rand_array)
		return (NULL);

	for (int i = 0; i < array_size; i++)
		rand_array[i] = (char)rand_wrapper(lower, upper);

	return (rand_array);
}