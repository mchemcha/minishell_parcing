/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemcha <mchemcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:21:52 by mchemcha          #+#    #+#             */
/*   Updated: 2024/06/26 21:22:50 by mchemcha         ###   ########.fr       */
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
			while ((*str)[i] && (*str)[i] != '\n')
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

void	syntax_error(char *str, char *read_line)
{
	if (!ft_strncmp(read_line, str, 4))
	{
		printf("%s\n", str);
		exit(0);
	}
}

char	*space(char *str)
{
	char	s[100000];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '>' && str[i + 1] == '>')
			|| (str[i] == '<' && str[i + 1] == '<'))
		{
			s[j] = ' ';
			j++;
			s[j] = str[i];
			j++;
			i++;
			s[j] = str[i];
			j++;
			s[j] = ' ';
			j++;
		}
		else if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		{
			s[j] = ' ';
			j++;
			s[j] = str[i];
			j++;
			s[j] = ' ';
			j++;
		}
		else
		{
			s[j] = str[i];
			j++;
		}
		i++;
	}
	s[j] = '\0';
	return (ft_strdup(s));
}

void	check_error(t_token *list)
{
	if (list->type == 2 || ft_lstlast(list)->type == 2
		|| (ft_lstlast(list)->type >= 3 && ft_lstlast(list)->type <= 6))
	{
		printf ("Syntax Error\n");
		return;
	}
	while (list != NULL && list->next)
	{
		if (list->next && ((list->type == 2 && list->next->type == 2)
			|| ((list->type >= 5 && list->type <= 6)
			&& !(list->next->type == 9))))
		{
			printf("Syntax Error \n");
			break;
		}
		else if (list->next && (list->type >= 3 && list->type <= 6)
			&& (list->next->type >= 2 && list->next->type <= 6))
		{
			printf("Syntax Error\n");
			break;
		}
		list = list->next;
	}
}

int expend_check(char *str)
{
	int i = 0;
	
	if((str[1] >= 'a' && str[1] <='z') || (str[1] >= 'A' && str[1] <='Z') || str[1] == '_')
		return(1);
	while(str[i])
		i++;
	if((str[1] >= 'a' && str[1] <='z') || (str[1] >= 'A' && str[1] <='Z') || str[1] == '_' || (str[i] >= '0' && str[i] <= '9'))
		return(1);
	return(0);

}

void doubl_quotexpand(t_token *list, t_env *env)
{
	char *str;
	int i = 1;
	char *s[1000];
	
	while(list)
	{
		if(list->type == Doubl_QUOTE || list->type == WORD)
		{
			str = list->str;
			if(list->type == Doubl_QUOTE)
			{
				while(str[i] != '\"')
				{
					str[i] *= (-1);
					i++;
				}
			}
			expend(str, env, s);
		}
		list = list->next;
	}
}
// void expend(char *str, t_env *env, char *s)
// {
// 	int i = 0;

// 	while(str[i])
// 	{
// 		if(str[i] == '$')
// 		{
// 			i++;
// 			get_env(env, str);
// 		}
// 	}
// }

void parcing_check(char *read_line)
{
	char *str;
	char **tab;
	int i;
	t_token *list = NULL;
	i = 0;
	add_history(read_line);
	double_quot_error(read_line);
	betwen_quote(&read_line);
	str = space(read_line);
	// printf("{%s}\n", str);
	tab = ft_split(str, ' ');
	while (tab[i])
	{
		tokenazer_line(tab[i], &list);
		i++;
	}
	check_error(list);
	print_stack(list);
	doubl_quotexpand(list);
	print_stack(list);
	list = NULL;
}