#include "minishell.h"

char    *ft_brekets_error(char *str)
{
    int i;
    int j;

    i = 0;
    while (str[i] != '{')
    {
        i++;
    }
    j = i;
    while (str[j] != '}')
    {
        j++;
    }
    return(ft_substr(str, i, j - (i - 1)));
    
}

char	*ft_expand_brekets(char *str)
{
    if (str[1] != '{')
        return(ft_brekets_error(str));
    else
        return(cmp_brekets(ft_substr(str, 2, ft_strlen(str) - 3)));
}