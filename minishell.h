/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemcha <mchemcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:13:12 by mchemcha          #+#    #+#             */
/*   Updated: 2024/06/22 20:57:46 by mchemcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include <stdio.h>
#include <stdbool.h>
# include <fcntl.h>
# include <stdlib.h> 
# include <unistd.h>
# include <limits.h>
# include <errno.h>
# include <string.h>
#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum s_type
{
	WSPACE = 1,
	PIPE = 2,
	REDR_IN = 3,//<
	REDR_OUT = 4,//>
	APPEND = 5,//>>
	HEREDOC = 6,//<<
	SIGN = 7,//$
	EXIT = 8,//$?
	WORD = 9,//
	Singl_QUOTE = 10,//
	Doubl_QUOTE = 11//

} t_type;
typedef struct s_token {
	int				type;
	char			*str;
	struct s_token	*next;
}	t_token;

typedef struct s_list
{
	char			**cmds;
	int				infile;
	int				outfile;
	struct s_list	*next;
}	t_list;

void	betwen_quote(char **str);
int		double_quot_error(const char *str);
int		pip_syntax(char *str);
void	syntax_error(char *str,char *read_line);
char	*space(char *str);
void	parcing_check(char *str);
char	*ft_strdup( char *s1);
int		ft_strncmp( char *s1,  char *s2, size_t n);
size_t	ft_strlen( char *str);
char	**ft_split(char  *s, char c);
void	tokenazer_line(char *str, t_token **list);
void	print_stack(t_token *list);
t_token	*ft_lstnew(int type,char *str );
t_token	*ft_lstlast(t_token *lst);
void	ft_lstadd_back(t_token **lst, t_token *newlst);

#endif