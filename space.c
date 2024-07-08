/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemcha <mchemcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:54:57 by mchemcha          #+#    #+#             */
/*   Updated: 2024/07/07 18:57:05 by mchemcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*space(char *str)
// {
// 	char	s[100000];
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		if ((str[i] == '>' && str[i + 1] == '>')
// 			|| (str[i] == '<' && str[i + 1] == '<'))
// 		{
// 			s[j] = ' ';
// 			j++;
// 			s[j] = str[i];
// 			j++;
// 			i++;
// 			s[j] = str[i];
// 			j++;
// 			s[j] = ' ';
// 			j++;
// 		}
// 		else if (str[i] == '|' || str[i] == '>' || str[i] == '<')
// 		{
// 			s[j] = ' ';
// 			j++;
// 			s[j] = str[i];
// 			j++;
// 			s[j] = ' ';
// 			j++;
// 		}
// 		else if(str[i] == '\"')
// 		{
// 			s[j] = ' ';
// 			j++;
// 			s[j] = str[i];
// 			i++;
// 			j++;
// 			while(str[i] && (str[i] != '\"'))
// 			{
// 				s[j] = str[i];
// 				j++;	
// 				i++;
// 			}
// 			s[j] = str[i];
// 			j++;
// 			s[j] = ' ';
// 			j++;
// 		}
// 		else if( str[i] == '\'')
// 		{
// 			s[j] = ' ';
// 			j++;
// 			s[j] = str[i];
// 			i++;
// 			j++;
// 			while(str[i] && (str[i] != '\''))
// 			{
// 				s[j] = str[i];
// 				j++;	
// 				i++;
// 			}
// 			s[j] = str[i];
// 			j++;
// 			s[j] = ' ';
// 			j++;
// 		}
// 		else
// 		{
// 			s[j] = str[i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	s[j] = '\0';
// 	return (ft_strdup(s));
// }

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
			s[j++] = ' ';
			s[j++] = str[i++];
			s[j++] = str[i];
			s[j++] = ' ';
		}
		else if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		{
			s[j++] = ' ';
			s[j++] = str[i];
			s[j++] = ' ';
		}
		else if (str[i] == '\"' || str[i] == '\'')
		{
			s[j++] = ' ';
			char quote = str[i];
			s[j++] = str[i++];
			while (str[i] && str[i] != quote)
				s[j++] = str[i++];
			s[j++] = str[i];
			s[j++] = ' ';
		}
		else
			s[j++] = str[i];
		i++;
	}
	s[j] = '\0';
	return (ft_strdup(s));
}
