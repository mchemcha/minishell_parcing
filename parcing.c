/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemcha <mchemcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:21:52 by mchemcha          #+#    #+#             */
/*   Updated: 2024/07/01 21:37:31 by mchemcha         ###   ########.fr       */
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
void	remove_double_quotes(char *str) 
{
    char *src = str;
    char *dst = str;
    while (*src) {
        if (*src != '"') {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

void doubl_quotexpand(t_token *list, t_env *env)
{
	int i = 0;
	(void)env;
	
	while(list)
	{
		if(list->type == Doubl_QUOTE)
		{
			if(list->type == Doubl_QUOTE)
			{
				i++;
				while(list->str[i] != '\"')
				{
					list->str[i] *= (-1);
					i++;
				}
				remove_double_quotes(list->str);
			}
		}
		list = list->next;
	}
}
void	expend_list(t_token *list, t_env *env)
{
	int i;
	int j;
	int k;
	int e;
	char *str = NULL;
	char *valeur = NULL;
	char s[1000];
	char buff[1000];
	while (list)
	{
		i = 0;
		j = 0;
		k = 0;
		e = 0;
		if(list->type == Doubl_QUOTE || list->type == WORD || list->type == SIGN)
		{
			str = list->str;
			while(str[i])
			{
				k = 0;
				e = 0;
				if(str[i] == '$')
				{
					i++;
					while(str[i] && 
						((str[i] >= 'A' && str[i] <= 'Z' ) || (str[i] >= 'a' && str[i] <= 'z' ) || 
							(str[i] >= '0' && str[i] <= '9') || str[i] == '_' || str[i] != ' ' ) && str[i] != '$')
					{
						s[k] = str[i];
						i++;
						k++;
					}
					s[k] = '\0';
					char *s2 = ft_strdup(s);
					valeur = get_env(env,s2);
					while(valeur && valeur[e])
					{
						buff[j] = valeur[e];
						e++;
						j++;
					}
					free(s2);
					s2 = NULL;
					valeur = NULL;
				}
				else
				{
					buff[j] = str[i];
					i++;
					j++;
				}
			}
			buff[j] = '\0';
			list->str = strdup(buff);
		}
		list = list->next;
	} 
}



void parcing_check(char *read_line,t_env *env)
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
	tab = ft_split(str, ' ');
	while (tab[i])
	{
		tokenazer_line(tab[i], &list);
		i++;
	}
	check_error(list);
	doubl_quotexpand(list,env);
	print_stack(list);
	expend_list(list,env);
	puts("------>\n");
	print_stack(list);
	list = NULL;
}