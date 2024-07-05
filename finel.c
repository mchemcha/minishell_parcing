/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemcha <mchemcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:16:14 by mchemcha          #+#    #+#             */
/*   Updated: 2024/07/05 21:08:44 by mchemcha         ###   ########.fr       */
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
	list -> next = NULL;
	return (list);
}

// t_list	*ft_lstlast_list(t_list *lst)
// {
// 	t_list	*p;

// 	p = lst ;
// 	while (p != NULL && p -> next != NULL)
// 	{
// 		p = p -> next;
// 	}
// 	return (p);
// }

// void	ft_lstadd_back_list(t_list **lst, t_list *newlst)
// {
// 	t_list	*p;

// 	if (lst == NULL || newlst == NULL)
// 		return ;
// 	if (*lst == NULL)
// 		*lst = newlst;
// 	else
// 	{
// 		p = ft_lstlast(*lst);
// 		p -> next = newlst;
// 	}
// }
// void print_list(t_list *list)
// {
//     t_list *str = list;
//     printf("------------\n")
//     while (str != NULL)
//     {
//         printf("cmds: ");
//         if (str->cmds != NULL)
//         {
//             for (int i = 0; str->cmds[i] != NULL; i++)
//             {
//                 printf("%s ", str->cmds[i]);
//             }
//         }
//         printf("\ninfile: %d\n", str->infile);
//         printf("outfile: %d\n", str->outfile);
//         printf("-----------\n");
//         str = str->next;
//     }
// }
void comds_tabl(t_token *token,char ***tab)
{
    int i = 0 ;
    int j = 0 ;
    char str[100000];
    char *s;

    while(token)
    {
        while(token->type != PIPE && token->next)
        {
            i = 0;
            while(token->str[i] && token)
            {
               str[j] = token->str[i];
               i++;
               j++; 
            }
            str[j] = ' ';
            j++;
            token = token->next;
        }
        str[j] = '\0';
        s = ft_strdup(str);
        token = token->next;
    }
    printf("-->%s<--\n",str);
    *tab = ft_split(s,' ');
}

void execution_list(t_token *token, t_list **list)
{
    int i = 0;
    
}