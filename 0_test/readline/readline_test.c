// readline, rl_clear_history, rl_on_new_line,
// rl_replace_line, rl_redisplay

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>	/* errno */
#include <stdio.h>
#include <string.h> /* strerror */
#include <fcntl.h>

int main(int ac, char **av)
{	
	//if (command->command_parts[1])
	chdir(av[1]);
	//printf("%s\n", strerror(errno));
	int i;
	i = 0;
	char ch[1];
	errno = 255;
	write(1, strerror(errno), strlen(strerror(errno)));
	write(1, "\n", 1);
	//execve("../../minishell", NULL, NULL);
}
