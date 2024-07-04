/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemcha <mchemcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:50:28 by mchemcha          #+#    #+#             */
/*   Updated: 2024/07/04 18:07:39 by mchemcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lstnew(int type,char *str )
{
	t_token	*list;

	list = (t_token *)malloc(sizeof(t_token));
	if (list == NULL)
		return (NULL);
	list->type = type;
    list->str = str;
	list -> next = NULL;
	return (list);
}

t_token	*ft_lstlast(t_token *lst)
{
	t_token	*p;

	p = lst ;
	while (p != NULL && p -> next != NULL)
	{
		p = p -> next;
	}
	return (p);
}

void	ft_lstadd_back(t_token **lst, t_token *newlst)
{
	t_token	*p;

	if (lst == NULL || newlst == NULL)
		return ;
	if (*lst == NULL)
		*lst = newlst;
	else
	{
		p = ft_lstlast(*lst);
		p -> next = newlst;
	}
}
void print_stack(t_token *list)
{
    while(list != NULL)
    {
    	printf("%s==>%d;\n", list->str, list->type);
    	list = list->next;
    }
}

void print_stack2(t_env *list)
{
	puts("dkhalt");
    while(list != NULL)
    {
    	printf("%s==>%s;\n", list->key, list->value);
    	list = list->next;
    }
}


void singlle(char *str,t_token **head)
{
	head = NULL;

    char *start = str;
    char *end;
    while (*start != '\0') {
        if (*start == '"' || *start == '\'') {
            char quote = *start;
            start++;
            end = strchr(start, quote);
            if (end != NULL) 
			{
                char word[50];
                int len = end - start + 2;
                strncpy(word, start - 1, len);
                word[len] = '\0';
				ft_lstadd_back(head, ft_lstnew(Doubl_QUOTE,word));
                start = end + 1;
            } else {
                break;
            }
        } else {
            start++;
        }
	}
}

void tokenazer_line(char *str, t_token **list)
{
    int i = 0;
    if(str[i] == '|')
		ft_lstadd_back(list, ft_lstnew(PIPE,str));
    else if(!ft_strncmp("<<" , str, 2))
		ft_lstadd_back(list, ft_lstnew(HEREDOC,str));
    else if(!ft_strncmp(">>" , str, 2))
		ft_lstadd_back(list, ft_lstnew(APPEND,str));
    else if(str[i] == ' ')
		ft_lstadd_back(list, ft_lstnew(WSPACE,str));
    else if(str[i] == '<')
		ft_lstadd_back(list, ft_lstnew(REDR_IN,str));
    else if(str[i] == '>')
		ft_lstadd_back(list, ft_lstnew(REDR_OUT,str));
    else if(str[i] == '$')
		ft_lstadd_back(list, ft_lstnew(SIGN,str));
    else if(str[i] == '\'')
		// singlle(str,list);
		ft_lstadd_back(list, ft_lstnew(Singl_QUOTE,str));
    else if(str[i] == '\"')
		ft_lstadd_back(list, ft_lstnew(Doubl_QUOTE,str));
	else 
		ft_lstadd_back(list, ft_lstnew(WORD,str));
}