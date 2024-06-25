/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemcha <mchemcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:12:59 by mchemcha          #+#    #+#             */
/*   Updated: 2024/06/24 14:20:43 by mchemcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av)
{
	char	*read_line;
	
	(void)ac;
	(void)av;
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
			parcing_check(read_line);
		}
		free(read_line);
	}
	return 0;
}