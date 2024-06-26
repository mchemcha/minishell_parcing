/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemcha <mchemcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:11:16 by mchemcha          #+#    #+#             */
/*   Updated: 2024/06/26 21:05:48 by mchemcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_egal(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}
void	add_back_env(t_env **head, t_env *new)
{
	t_env	*node;

	node = *head;
	if ((*head) == NULL)
	{
		(*head) = new;
		return ;
	}
		while (node->next)
			node = node->next;
		node->next = new;
}

t_env	*lst_new_env1(char *str ,char *s)
{
	t_env	*new; 
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = str;
	new->value = s;
	new->next = NULL;
	return (new);
}

void	eeeenv(t_env **head, char **env)
{
	int	i;
	char *k = NULL;
	char *v = NULL;

	i = 0;
	while (env[i])
	{
		int y = check_egal(env[i]);
		if (y != -1)
		{
			k  = ft_substr2(env[i], 0, y);
			v = ft_substr2(env[i], 0, ft_strlen(env[i]) - y - 1);
		}
		else
		{
			k = env[i];
			v = NULL;
		}
		add_back_env(head, lst_new_env1(k, v));
		i++;
	}
}
char *get_env(t_env *obj,char *str)
{	
	while (obj)
	{
		if (ft_strcmp(obj->key, str) == 0)
			return(obj->value);
		obj = obj->next;
	}
	return(NULL);
}

