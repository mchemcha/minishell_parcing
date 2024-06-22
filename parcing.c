/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemcha <mchemcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 19:21:52 by mchemcha          #+#    #+#             */
/*   Updated: 2024/06/22 21:18:17 by mchemcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void betwen_quote(char **str)
{
    int i = 0;
    while((*str)[i])
    {
        if((*str)[i] == '"')
        {
            i++;
            while((*str)[i] &&  (*str)[i] != '"')
            {
                (*str)[i] *= (-1);
                i++;
            }
        }
        if((*str)[i] == '\'')
        {
            i++;
            while((*str)[i] &&  (*str)[i] != '\n')
            {
                (*str)[i] *= (-1);
                i++;
            }
        }
        i++;   
    }
}

int double_quot_error(const char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '"' )
        {
            i++;
            while (str[i] && str[i] != '"')
                i++;
            if (str[i] == '\0')
                return (printf("Syntax Error\n") ,1); 
        }
        if ( str[i] == '\'')
        {
            i++;
            while (str[i] && str[i] != '\'')
                i++;
            if (str[i] == '\0')
                return (printf("Syntax Error\n") ,1); 
        }
        i++;
    }
    return 0; 
}



int pip_syntax(char *str)
{
    int i = 0 ;
    if(str[1] == '|')
    {
        printf("Syntax Error\n");
        return(0);
    }
    else
    {
        while(str[i])
            i++;
        if(str[i-2] == '|')
        {
            printf("Syntax Error\n");
            return(0);
        }
    }
    return(1);
}
void syntax_error(char *str,char *read_line)
{
    if(!ft_strncmp(read_line, str, 4))
        {
            printf("%s\n",str);
            exit(0);
        }
}

char *space(char *str)
{
    char s[100000];
    int i = 0;
    int j = 0;
    
    while(str[i])
    {
        if(str[i] == '|')
        {
            s[j] = ' ';
            j++;
            s[j] = str[i];
            j++;
            i++;
            s[j] = ' ';
            j++;
        }
        if((str[i] == '>' && str[i+1] == '<') || (str[i] == '<' && str[i+1] == '>'))
        {
            printf("syntax Error\n");
            break;
        }
        else if( (str[i] == '>' && str[i+1] == '>') || (str[i] == '<' && str[i+1] == '<') )
        {
            s[j] = ' ';
            j++;
            s[j] = str[i];
            j++;
            i++;
            s[j] = str[i];
            j++;
            s[j] = ' ';
            i++;
            if(str[i] == '>' || str[i] == '<')
            {
                printf("syntax Error\n");
                break;
            }
        }
        else if( str[i] == '>' || str[i] == '<')
        {
            s[j] = ' ';
            j++;
            s[j] = str[i];
            j++;
            s[j] = ' ';
        }
        else
            s[j] = str[i];
        i++;
        j++;
    }
    s[j] = '\0';
    return(ft_strdup(s));
}
void check_error(t_token *list)
{
    if(list->type == 2)
        pirntf("Syntax Error \n");
    if(ft_lstlast())    
}
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
    // printf("%s\n",str);
    tab = ft_split(str, ' ');
    while(tab[i])
    {
        tokenazer_line(tab[i], &list);
        i++;
    }
    print_stack(list);
    list = NULL;
}
  