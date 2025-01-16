#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	int i;

	printf("Arguments (argv):\n");
	for (int i = 0; i < argc; i++)
		printf("argv[%d]: %s\n", i, argv[i]);
	i = 0;
	printf("Arguments (envp):\n");
	while (envp[i] != NULL)
	{
		printf("envp[%d]: %s\n", i, envp[i]);
		i++;
	}
	return (0);
}
