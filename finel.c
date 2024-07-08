/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemcha <mchemcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:16:14 by mchemcha          #+#    #+#             */
/*   Updated: 2024/07/07 21:20:18 by mchemcha         ###   ########.fr       */
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
    list->cmds = str;
	list->next = NULL;
	return (list);
}

t_list	*ft_lstlast_list(t_list *lst)
{
	t_list	*p;

	p = lst ;
	while (p != NULL && p -> next != NULL)
		p = p -> next;
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
		p = ft_lstlast_list(*lst);
		p -> next = newlst;
	}
}

void print_list_cmd(t_list *list)
{
    t_list *str = list;
    printf("------------\n");
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

int open_file(char *str)
{
    int fd;

    fd = open(str, O_RDWR,O_CREAT);
    if (fd == -1) 
    {
        puts("EROR\n");
        return 1;
    }
    return (fd);
}

// t_token *rederaction_handle(t_token *list)
// {
//     while (list)
//     {
//         if(list->type == REDR_OUT)
//         {
            
//         }
//     }
// }
// if(list->type == REDR_OUT)
//             {
//                 list = list->next;
//                 outfile = open_file(list->str);
//                 list = list->next; 
//             }
t_list *split_liked_pip(t_token *list)
{
    t_list *list_cmd = NULL;
    
    while (list )
    {
        char *cmd[1000];
        int i = 0;
        int infile = -2;
        int outfile = -2;
        
        while (list && list->type != PIPE && list->str)
        {
            cmd[i] = ft_strdup(list->str);
            i++;
            if(list->type == REDR_OUT)
            {
                list = list->next;
                outfile = open_file(list->str);
                printf("==>%s = %d<==\n", list->str,outfile);
            }
            list = list->next;                                              
        }
        cmd[i] = NULL;
        t_list *new_node = ft_lstnew_list(infile, outfile, ft_arrydup(cmd));
        ft_lstadd_back_list(&list_cmd, new_node);
        if (!list)
			break;
    	list = list->next;
        close(outfile);
    }
    return list_cmd;
}

