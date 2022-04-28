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
	int pipe_fds[2];
	pipe(pipe_fds);

	int fd = open("test,txt", O_RDONLY | O_NONBLOCK);
	
}
