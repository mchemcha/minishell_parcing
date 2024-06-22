/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemcha <mchemcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:12:59 by mchemcha          #+#    #+#             */
/*   Updated: 2024/06/22 20:51:25 by mchemcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int main()
// {
//     char *str;
//     char **tab;
//     int i;
//     t_token *list = NULL;

//     char *read_line;
//     while(1)
//     {
//         i = 0;
//         read_line = readline("minishell : ");
//         add_history(read_line);
//         double_quot_error(read_line);
//         betwen_quote(&read_line);
//         str = space(read_line);
//         // printf("%s\n",str);
//         tab = ft_split(str, ' ');
//         while(tab[i])
//         {
//             tokenazer_line(tab[i], &list);
//             i++;
//         }
//         print_stack(list);
//         list = NULL;
//     }
// }

int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    char *read_line;
    while(1)
    {
        read_line = readline("minishell : ");
        add_history(read_line);
        parcing_check(read_line);
    }
}