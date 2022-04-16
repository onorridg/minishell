// readline, rl_clear_history, rl_on_new_line,
// rl_replace_line, rl_redisplay

#include <unistd.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>               
# define BEGIN(x,y) "\001\033["#x";"#y"m\002"
# define CLOSE "\001\033[0m\002"        
extern void rl_clear_history(void);


int main(void)
{
	char *str;
	rl_outstream = stderr;
	while (1)
	{
		str = readline(BEGIN(49, 31)"root@mac:# "CLOSE);
		if (!str)
		{	
			write(1, "exit\n", 5);
			break;
		}
		add_history(str);
		free(str);
	}
}