/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemcha <mchemcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:16:14 by mchemcha          #+#    #+#             */
/*   Updated: 2024/07/06 19:11:55 by mchemcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstnew_list(int infile,int outfile,char **str)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (list == NULL)
		return (NULL);
	list->infile = infile;
	list->outfile = outfile;
    list->str = str;
	list->next = NULL;
	return (list);
}

t_list	*ft_lstlast_list(t_list *lst)
{
	t_list	*p;

	p = lst ;
	while (p != NULL && p -> next != NULL)
	{
		p = p -> next;
	}
	return (p);
}

void	ft_lstadd_back_list(t_list **lst, t_list *newlst)
{
	t_list	*p;

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
void print_list(t_list *list)
{
    t_list *str = list;
    printf("------------\n")
    while (str != NULL)
    {
        printf("cmds: ");
        if (str->cmds != NULL)
        {
            for (int i = 0; str->cmds[i] != NULL; i++)
            {
                printf("%s ", str->cmds[i]);
            }
        }
        printf("\ninfile: %d\n", str->infile);
        printf("outfile: %d\n", str->outfile);
        printf("-----------\n");
        str = str->next;
    }
}

void del(void *content)
{
	free(content);
}

// void	ft_lstdelone(t_list *lst, void (*del)(void*))
// {
// 	if (lst == NULL)
// 		return ;
// 	if (del != NULL)
// 	{
// 		if (lst->content != NULL)
// 			del(lst->content);
// 	}
// 	free (lst);
// }

int ft_lstsize(t_list *lst)
{
	t_list *i;
	int s;

	s = 0;
	i = lst;
	if (lst == NULL)
		return (0);
	while (i != NULL)
	{
		s += 1;
		i = i->next;
	}
	return (s);
}
int cont_word_list(t_token *list)
{
	int cont = 0;

	while (list)
	{
		if (list->type == PIPE) //|| (list->type >= 3 && list->type >= 6)
		{
			list = list->next;
			continue;
		}

		if (list->str)
			cont += ft_strlen(list->str);

		list = list->next;
	}
	return cont;
}

char **split_linked_pip(t_token *list)
{
	char **tab[400];
	int i, k, j;

	if (list == NULL)
		return (NULL);

	int num_words = cont_word_list(list);

	tab = (char **)calloc(num_words + 1, sizeof(char *));
	if (tab == NULL)
		return (NULL);

	i = 0;
	j = 0;
	while (list)
	{
		while (list && list->type == PIPE)
			list = list->next;

		if (list && list->str)
		{
			
			tab[i] = ft_strdup(list->str);
			if (tab[i] == NULL)
			{
				k = 0;
				while (k < i)
					free(tab[k++]);
				free(tab);
				return (NULL);
			}
			i++;
		}
		if (list)
			list = list->next;
	}

	tab[i] = NULL;

	return tab;
}

static int ft_arrylen(char **str) {
    int i = 0;
    while (str[i]) {
        i++;
    }
    return i;
}

char **ft_arrydup(char **s1) {
    char **str;
    size_t i = 0;
    size_t len = ft_arrylen(s1);

    str = (char **)malloc((len + 1) * sizeof(char *));
    if (!str) {
        return NULL;
    }
    
    while (s1[i]) {
        str[i] = ft_strdup(s1[i]);
        if (!str[i]) 
		{
            while (i > 0) {
                free(str[--i]);
            }
            free(str);
            return NULL;
        }
        i++;
    }
    str[i] = NULL;
    return str;
}

t_list	*split_liked_pip(t_token *list)
{
	t_list *list_cmd;
	
	
	while(list)
	{
		char *cmd[1000];
		int i = 0;
		int infile = -2;
		int outfile = -2;
		while(list && list->type != PIPE && list->str)
		{
			cmd[i] = list->str;
			i++;
		}
		cmd[i] = '\0';
		ft_lstadd_back_list(&list_cmd,ft_lstnew_list(infile,outfile,ft_arrydup(cmd)));
		list = list->next;
	}
	list_cmd = NULL;
	return(list_cmd);
	
}
