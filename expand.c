/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemcha <mchemcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:32:10 by mchemcha          #+#    #+#             */
/*   Updated: 2024/07/04 21:22:40 by mchemcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
void	remove_singl_quotes(char *str) 
{
    char *src = str;
    char *dst = str;
    while (*src) {
        if (*src != '\'') {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

// void doubl_quotexpand(t_token *list, t_env *env)
// {
// 	int i ;
//     (void)env;

//     while (list)
//     {
//         char *str = list->str;
//         if (list->type == Doubl_QUOTE)
//         {
//             i = 0;

//             if (str[i] == '\"')
//             {
//                 i++;
//                 while (str[i] && str[i] != '\"')
//                 {
//                     str[i] *= (-1);
//                     i++;
//                 }
//                 if (str[i] == '\"')
//                 {
//                     remove_double_quotes(str);
//                 }
//             }
//         }
//         list = list->next;
//     }
// }

void doubl_quotexpand(t_token *list, t_env *env)
{
	int i = 0;
	char *str;
	(void)env;
	
	while(list)
	{
		str = list->str;
			if(list->type == Doubl_QUOTE)
			{
				i = 0;
				if(str[i] == '\"')
					i++;
				while(str[i] && str[i] != '\"')
				{
					str[i] *= (-1);
					i++;
				}
				remove_double_quotes(str);
			}
		list = list->next;
	}
}

void singl_quotexpand(t_token *list)
{
	int i = 0;
	char *str;
	
	while(list)
	{
		str = list->str;
			if(list->type == Singl_QUOTE)
			{
				i = 0;
				if(str[i] == '\'')
					i++;
				while(str[i] && str[i] != '\'')
				{
					str[i] *= (-1);
					i++;
				}
				remove_singl_quotes(str);
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
					if(str[i] == '$')	
						return;
					while(str[i] && (ft_isalnum((int)str[i]) || str[i] == '_' ))//&& str[i] != '$' && str[i] != '\'') || str[i] != ' ' )
					{
						s[k] = str[i];
						i++;
						k++;
						if(!(ft_isalnum((int)str[i]) || str[i] == '_'))
							break;
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
void	singel_quote(t_token *list)
{
	int i;
	int j;
	char *str = NULL;
	char buff[1000];
	while (list)
	{
		i = 0;
		j = 0;
		if(list->type == Singl_QUOTE)
		{
			str = list->str;
			while(str[i])
			{
					buff[j] = str[i];
					i++;
					j++;
			}
			buff[j] = '\0';
			list->str = strdup(buff);
		}
		list = list->next;
	} 
}