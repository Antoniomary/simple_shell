#include "shell.h"

/**
 * main - entry point to a custom shell program.
 * @ac: argument count at command line.
 * @av: argument vector at command line.
 *
 * Return: a poistive integer (0 - 255).
 */
int main(int ac __attribute__((unused)), char **av)
{
	list info = {0, 0, 0, NULL, 0, NULL, 0, NULL, 0, 0, NULL, NULL};
	char loop = true, *line = NULL, *cmd = NULL, *save = NULL, sep = NUL;

	sh_start_up(&info, av);

	signal(SIGINT, sig_hand); /* handle CTRL + C */
	while (loop) /* infinite loop */
	{
		if (info.sh_mode == INT_MODE) /* i.e interactive mode */
			display_prompt(); /* prints prompt to enter command */

		line = read_line(&info); /* gets the input of the user */
		if (remove_comment(line) == 0) /* remove comment from user input */
			continue;
		if (syntax_error_check(&info, line) == ERROR)
			continue;

		/* tokenize based on semi-colon delimiters */
		cmd = strcmd_and_sep(line, ";", &sep, &save);
		while (cmd && !info.exit)
		{
			/* tokenize based on logical and & logical or */
			cmd = strcmd_and_sep(cmd, "&|", &sep, NULL);
			while (cmd)
			{
				info.argv = token_input(&info, cmd); /* tokenize args */
				if (!info.argv)
				{
					info.exit = true;
					break;
				}
				/*dequote(ptr);*/
				if (is_all_var_def(&info))
					define_user_var(&info);
				else
				{
					sort_var_from_cmd(&info);
					substitute_var_alias(&info);
					execute_cmd(&info);
				}
				update_exitstatus_var(&info);
				free(info.argv);

				if ((sep == AND && info.exit_status) || (sep == OR && !info.exit_status))
					break;
				cmd = strcmd_and_sep(NULL, "&|", &sep, NULL);
			}
			cmd = strcmd_and_sep(!save ? "\0" : save, ";", &sep, &save);
		}

		free(line);
		loop = (info.exit == true) ? false : true;
	}

	free_env_alias_vars(&info);

	return (info.exit_status);
}
