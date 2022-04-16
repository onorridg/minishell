/*#include <unistd.h>

int main(int ac, char **av)
{
    execve("/usr/bin/cd", av, NULL);
}*/

#include "minishell.h"
#include <sys/types.h> /* DIR */
#include <dirent.h> /* opendir, closedir*/
int main(void)
{
	char	dir[255];

	getcwd(dir, 255);
	printf("Path: %s\n", dir);
	chdir("/Users/onorridg");
	getcwd(dir, 255);
	printf("Path: %s\n", dir);
}