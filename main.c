#include "includes/lem_in.h"

int main()
{
	int size = 0;
	char *line = NULL;
	char *storage = NULL;
	int **matrix = parser(&size, &line, &storage);

	// for (size_t i = 0; i < size; i++)
	// {
	// 	for (size_t j = 0; j < size; j++)
	// 	{
	// 		if (matrix[i][j] != 1)
	// 			printf(".");
	// 		else
	// 			printf("1");
	// 	}
	// 	printf("\n");
	// }
	ft_doublefree_int(matrix, size);
}