/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemcha <mchemcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:12:59 by mchemcha          #+#    #+#             */
/*   Updated: 2024/06/27 20:15:53 by mchemcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av,char **env)
{
	char	*read_line;
	
	(void)ac;
	(void)av;
	t_env	*bult = NULL ;
	
	eeeenv(&bult, env);
	print_stack2(bult);
	char *str = get_env(bult, "USER");
	printf("\n\n====> %s <====\n\n", str);
	while(1)
	{
		read_line = readline("minishell: ");
		if (!read_line)
		{
			printf("\n");
			continue;
		}
		if (strcmp(read_line, "") != 0)
		{
			add_history(read_line);
			parcing_check(read_line, bult);
		}
		free(read_line);
	}
	return 0;
}