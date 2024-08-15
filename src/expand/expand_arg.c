/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lumarque <lumarque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 02:25:27 by lumarque          #+#    #+#             */
/*   Updated: 2024/08/15 02:26:11 by lumarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	point_to_exp_tilde(int point, char *tmp, char **line)
{
	if (!tmp[1] || ft_strchr(NOT_EXP, tmp[1])) // Se tmp[1] não existir (fim da string) ou estiver em NOT_EXP (lista de caracteres não permitidos), expande o til para o valor da variável de ambiente HOME usando a função expand. Exemplo: echo - ou echo - > file1. Outro exemplo é echo ~john. Neste caso, tmp[1] é o caractere j. Porém, j não é um caso especial válido para expansão de tilde (apenas + e - são tratados). Como não é um caso válido, a função expande o tilde para o valor da variável de ambiente HOME.
		return (expand(getenv("HOME"), point, point + 1, line));
	else if (tmp[1] == '+' && (!tmp[2] || ft_strchr(NOT_EXP, tmp[2])))// Se tmp[1] for igual a '+' e tmp[2] não existir ou estiver na string NOT_EXP, a função retorna o resultado da função expand com "PWD" como argumento. Exemplo: echo ~+ é disso exemplo. tmp[1] é + e tmp[2] não existe quando a til (~) é seguida por um + e não há mais caracteres após o +. Por exemplo, na string "echo ~ +", tmp[0] seria ~, tmp[1] seria + e tmp[2] não existiria. 
		return (expand(getenv("PWD"), point, point + 2, line));
	else if (tmp[1] == '-' && (!tmp[2] || ft_strchr(NOT_EXP, tmp[2])))// Se tmp[1] for igual a '-' e tmp[2] não existir ou estiver na string NOT_EXP, a função retorna o resultado da função expand com "OLDPWD" como argumento. Linha de comando original: echo ~-. Neste caso, tmp[1] é o sinal de subtração (-) e tmp[2] não existe (fim da string). O sinal de - indica que o tilde deve ser expandido para o diretório de trabalho atual (PWD), e dps anda para o diretório anterior a esse. A função chama expand para substituir o tilde pelo caminho do diretório de trabalho atual.
		return (expand(getenv("OLDPWD"), point, point + 2,
				line));
	return (0); // Se nenhuma dessas condições for atendida, a função retorna 0.
}

static int	expand_tilde(char **line)
{
	char	quote;
	char	*tmp;

	quote = 0;
	tmp = *line;
	while (*tmp)
	{
		if (!quote && (*tmp == '"' || *tmp == '\''))
			quote = *tmp;
		else if (quote == *tmp)
			quote = 0;
		if (*tmp == '~' && !quote
			&& (tmp == *line || ft_strchr(SPACES, *(tmp - 1)))) // Se o caratere atual for um ~ e não estiver dentro de aspas, e se estivermos no início da string ou se o caractere anterior for um espaço, então expandimos.
			if (point_to_exp_tilde(tmp - *line, tmp, line)) // 
				tmp = *line;
		if (*tmp)
			tmp++;
	}
	return (0);
}

static int	point_to_expand_env(int point, char *tmp, char **line)
{
	char	*key;
	int		len;

	if (tmp[1] == '?')
		return (expand_free(ft_itoa(g_exit), point, point + 2, line));
	else if (tmp[1]) // este if é para o caso de ser um $ seguido de um caractere que não é um espaço, por exemplo o caso específico echo "|$123USER|" "|$_123USER123|" '"|$_123USER123|"' "|$_123USER?123|" que tem de dar output |23USER| || "|$_123USER123|" |?123|, ou seja, não expande se for número (com exceção do primeiro) e expande se for _. O terceiro exemplo está dentro de aspas, logo apenas printa o que está dentro de aspas.
	{
		len = 1;
		while (ft_isalpha(tmp[len]) || tmp[len] == '_')
			len++;
		len += (ft_isalnum(tmp[len]) > 0);
		while (len > 2 && (ft_isalnum(tmp[len]) || tmp[len] == '_'))
			len++;
		key = ft_substr(tmp, 1, len - 1);
		expand(getenv(key), point, point + len, line);
		return (free(key), 1);
	}
	return (0);
}

static void	env_expand(char *tmp, char **line)
{
	char	quote;

	quote = 0;
	while (*(++tmp))
	{
		if (!quote && (*tmp == '"' || *tmp == '\''))
			quote = *tmp;
		else if (quote == *tmp)
			quote = 0;
		if (*tmp == '$' && !ft_strchr(NOT_EXP, *(tmp + 1)) && quote != '\''
			&& !(quote && ft_strchr("\"'", *(tmp + 1)))) // Se o caractere atual for um $ e o próximo não for um espaço, e não estiver dentro de aspas simples (uma vez que as aspas duplas expandem), e se o próximo caractere não for uma aspa, então expandimos.
		{
			if (point_to_expand_env(tmp - *line, tmp, line))
			{
				tmp = *line - 1;
				quote = 0;
			}
		}
	}
}

void	expand_arg(t_shell *shell, char **arg)
{
	(void)shell;
	expand_tilde(arg);
	env_expand(*arg - 1, arg);
}
