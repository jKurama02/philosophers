#include "philosopher.h"

void err_exit(char *err)
{
	printf("%s\n", err);
	exit(EXIT_FAILURE);
}

int	check_input(char **argv)
{
	int	i;
	int	k;

	i = 0;
	while(argv[++i])
	{
		k = 0;
		while(argv[i][k])
		{
			if(argv[i][k] == ' ' || argv[i][k] == '+')
				k++;
			else if (!(argv[i][k] >= 48 && argv[i][k] <= 57))
				return (1);
			k++;
		}
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_data data;

	if(argc == 5 || argc == 6)
	{
		if(check_input(argv))
			err_exit("Error check_input <3");
		if (init_input(&data, argc, argv))
		{
			err_exit("Error init_input <3");
		}
		else
		{
			printf("codio\n");
		}
		return 0;
	}
	else
		err_exit("Error number argument <3");
}

