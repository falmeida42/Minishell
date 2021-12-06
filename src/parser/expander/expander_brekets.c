#include "minishell.h"

int brekets_space(char *str){
    
    if (ft_contains(' ', str))
        return (1);
    else
        return (0);
}

char    *cmp_brekets(char *str)
{    
    if (brekets_space(str))
    {
        g_mini.parse_error = "bad substitution";
        return (ft_strdup(""));
    }
    if (env_get(str) == NULL)
        return (ft_strdup(""));
    else
    {
        return (ft_strdup(env_get(str)));
    }
}

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