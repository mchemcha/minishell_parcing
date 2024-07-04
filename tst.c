#include <stdio.h>
#include <stdlib.h>

char	*ft_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i = 0;
	
	while (s[i])
		i++;
	return (i);
}

void	ft_strcpy(char *dst, const char *src)
{
	while (*src)	
		*dst++ = *src++;
	*dst = '\0';
}

char	*ft_strdup(const char *src)
{
	size_t	len = ft_strlen(src) + 1;
	char	*dst = malloc(len);
	
	if (dst == NULL)
		return (NULL);
	ft_strcpy(dst, src);
	return (dst);
}

char *singlle(char *str)
{
	int i = 1;
	int j = 1;
	char s[100];
    int k = 1;
	
	while(str[i])
	{
		if(str[i] == '\"')
			break;
		i++;
	}
	printf("%c=>%d\n", str[i],i);
	s[k] = '\"';
	while(str[j] != str[i] && str[j])
    {
		printf("---->%c####%c\n",str[i], str[j]);
		printf("---->%d\n",i);
        s[k] = str[j]; 
        j++;
        k++;
	    printf("=> %c ==> %c\n",s[k],str[j]);
    }
    s[k] = '\"';
    s[k+1] = '\0';
    char *resulta = ft_strdup(s);
	printf("cc => %s\n",s);
    return(resulta);
	
}
int main()
{
    char *str = "\"maryem\"\'chemchaq\'";

    printf("resultat => %s \n",singlle(str));


}