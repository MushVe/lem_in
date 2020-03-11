#include <unistd.h>

int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr(char const *s)
{
	write(1, s, ft_strlen(s));
}

int main()
{
	ft_putstr("\
           ><\n\
         | __)  kya\n\
     .-^^| |\n\
  __|      |\n\
 <__.|_|-|_|\n");
}