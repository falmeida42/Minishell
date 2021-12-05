#include "minishell.h"

char    *expand_til(char *str)
{
    char    *result;
    char    *home;

    home = env_get("HOME");
    result = ft_strjoin(home, str + 1);
    return (result);
}

char    *check_til(char *str)
{
    int i;

    if (!ft_contains('~', str))
        return (str);
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '~')
        {
            if (str[i + 1] == '/')
                return (expand_til(str));
        }
        i++;
    }
    return (str);
}

char    *til_text(char *str)
{
    char    *home;
    home = env_get("HOME");
    
    if (!ft_strcmp(str, "~"))
    {
        free(str);
        return (ft_strdup(home));
    }
    else
        return (check_til(str));
}

char    *ft_expander_til(t_token *token)
{
    if (token->type == TOKEN_TEXT)
        return (til_text(token->value));
    else
        return (token->value);
}