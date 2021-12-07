#include "minishell.h"

char    *check_til(char *str)
{
    char    *result;
    char    *home;

    if (str[1] != '/')
        return (str);
    home = env_get("HOME");
    if (!home)
        home = "";
    result = ft_strjoin(home, str + 1);
    free(str);
    return (result);
}

char    *ft_expander_til(t_token *token)
{
    char    *home;
    home = env_get("HOME");

    if (!home)
        home = "";
    if (!ft_strcmp(token->value, "~"))
        return (ft_strdup(home));
    return (check_til(token->value));
}