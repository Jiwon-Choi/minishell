#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	char *res;

	res = NULL;
	while (*envp)
	{
		if (strncmp(*envp, "aUSER", strlen("aUSER")) == 0)
			res = getenv(*envp);
		envp++;
	}
	printf("%s\n", res);
	return (0);
}
