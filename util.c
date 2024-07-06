/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchemcha <mchemcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:43:42 by mchemcha          #+#    #+#             */
/*   Updated: 2024/07/06 18:35:30 by mchemcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

size_t	ft_strlen( char *str)
{
	size_t	i;
	size_t	s;

	i = 0;
	s = 0;
	while (str[i])
	{
		s = s + 1;
		i++;
	}
	return (s);
}

char	*ft_strdup( char *s1)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)malloc (ft_strlen(s1) + 1);
	if (!str)
	{
		return (NULL);
	}
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

int	ft_strncmp( char *s1,  char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n
		&& ((unsigned char)s1[i] != '\0' || (unsigned char)s2[i] != '\0'))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*ft_substr(char  *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	i = 0;
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = s[i + start];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	**erreur(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static int	cont_word(char const *str, char c)
{
	int	i;
	int	cont;
	int	pp;

	i = 0;
	cont = 0;
	while (str[i])
	{
		pp = 0;
		while (str[i] == c && str[i])
			i++;
		while (str[i] != c && str[i])
		{
			i++;
			pp = 1;
		}
		if (pp)
			cont += 1;
	}
	return (cont);
}

char	**ft_split(char *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = -1;
	j = 0;
	if (!s)
		return (NULL);
	tab = (char **)calloc((cont_word(s, c) + 1) * sizeof(char *), 1);
	while (tab == NULL)
		return (NULL);
	while (++k < cont_word(s, c))
	{
		while (s[i] == c && s[i])
			i++;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		tab[k] = ft_substr(s, j, i - j);
		if (!tab[k])
			return (erreur(tab));
	}
	return (tab);
}

char	*ft_substr2(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ss;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len >= ft_strlen(&s[start]))
		len = ft_strlen(&s[start]);
	ss = malloc((len + 1) * sizeof(char));
	if (!ss)
		return (NULL);
	while (i < len)
	{
		ss[i] = s[start];
		i++;
		start++;
	}
	ss[i] = 0;
	return (ss);
}

void	ft_strcpy(char *dst, t_token *list)
{
	int i;
	int j = 0;
	
	while (src[i])	
	{
		dst[j] = src[i];
		j++;
		i++;
	}
	*dst = ' ';
}