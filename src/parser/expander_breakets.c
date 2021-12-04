#include "minishell.h"

char    *cmp_breakets(char *str)
{
    if (env_get(str) == NULL)
        return (ft_strdup(""));
    else
    {
        return (ft_strdup(env_get(str)));
    }
}

char	*expand_breakets(char *str, int i)
{
	char	*result;
    int     j;
    
    j = i;
    if (!ft_contains('}', str))
        return(ft_strdup("bad substitution\n"));
    while (str[j] != '\0')
    {
        if (str[j] == '}')
            result = cmp_breakets(ft_substr(str, i, j - i));
        else
            result = ft_strdup(str);
        j++;
    }
    return (result);
}