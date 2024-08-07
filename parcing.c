/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemcha <mchemcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:21:52 by mchemcha          #+#    #+#             */
/*   Updated: 2024/07/07 19:43:05 by mchemcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	betwen_quote(char	**str)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '"')
		{
			i++;
			while ((*str)[i] && (*str)[i] != '"')
			{
				(*str)[i] *= (-1);
				i++;
			}
		}
		if ((*str)[i] == '\'')
		{
			i++;
			while ((*str)[i] && (*str)[i] != '\'')
			{
				(*str)[i] *= (-1);
				i++;
			}
		}
		i++;
	}
}

int	double_quot_error(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
			if (str[i] == '\0')
				return (printf("Syntax Error\n"), 1);
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] == '\0')
				return (printf("Syntax Error\n"), 1);
		}
		i++;
	}
	return (0);
}

int	pip_syntax(char *str)
{
	int	i;

	i = 0;
	if (str[1] == '|')
	{
		printf("Syntax Error\n");
		return (0);
	}
	else
	{
		while (str[i])
			i++;
		if (str[i - 2] == '|')
		{
			printf("Syntax Error\n");
			return (0);
		}
	}
	return (1);
}

int	check_error(t_token *list)
{
	if (list->type == 2 || ft_lstlast(list)->type == 2
		|| (ft_lstlast(list)->type >= 3 && ft_lstlast(list)->type <= 6))
		return(printf ("Syntax Error\n"),1);
	while (list != NULL && list->next)
	{
		if (list->next && ((list->type == 2 && list->next->type == 2)
			|| ((list->type >= 5 && list->type <= 6)
			&& !(list->next->type == 9))))
			return(printf ("Syntax Error\n"),1);
		else if (list->next && (list->type >= 3 && list->type <= 6)
			&& (list->next->type >= 2 && list->next->type <= 6))
			return(printf ("Syntax Error\n"),1);
		list = list->next;
	}
	return(0);
}

void parcing_check(char *read_line,t_env *env)
{
	char *str;
	char **tab;
	int i;
	t_token *list = NULL;
	i = 0;
	add_history(read_line);
	if(double_quot_error(read_line) != 0)
		return;
	betwen_quote(&read_line);
	str = space(read_line);
	// printf("--->space = |%s|<----", str);
	tab = ft_split(str, ' ');
	while (tab[i])
	{
		tokenazer_line(tab[i], &list);
		i++;
	}
	if(check_error(list) != 0)
		return;
	doubl_quotexpand(list,env);
	expend_list(list,env);
	singl_quotexpand(list);
	singel_quote(list);
	// puts("------>\n");
	// print_stack(list);
	t_list *cmd_list = split_liked_pip(list);
	puts("------>\n");
	print_list_cmd(cmd_list);
	list = NULL;
}


