
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct s_shell
{
	char *line;
}				t_shell;

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	int		i;
	int		j;

	dst = (char *) malloc(strlen(s1) + strlen(s2) + 1);
	if (!dst || !s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] != '\0')
	{
		dst[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		dst[i] = s2[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	j;

	if (!s)
		return (0);
	if (strlen(s) < start)
	{
		sub = (char *)malloc(sizeof(char) * 1);
		if (!sub)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	if (len > strlen(s) - start)
		len = strlen(s) - start;
	sub = (char *)malloc(len + 1);
	if (!sub)
		return (NULL);
	i = start;
	j = 0;
	while (i < strlen(s) && j < len)
		sub[j++] = s[i++];
	sub[j] = '\0';
	return (sub);
}

void	mod(t_shell *sh, char *tmp)
{
	tmp = sh->line;
	printf("mod before: %s\n", tmp);
	while (*tmp)
		tmp++;
	printf("mod after: %s\n", tmp); 
}

void	expand(t_shell *shell, char *line, int i)
{
	char	*newline;
	char	*left;
	char	*right;
	
	newline = ft_substr(line, 0, i);
	left = ft_strjoin(newline, " ");
	free(newline);
	right = ft_substr(line, i, strlen(line) - i);
	newline = ft_strjoin(left, right);
	free(shell->line);
	shell->line = strdup(newline);
	free(newline);
	free(left);
	free(right);
}

void	check_expand(t_shell *shell, char *line2)
{
	int		squote;
	int		dquote;

	squote = 0;
	dquote = 0;
	while (*line2)
	{
		if (*line2 == '"' && !squote)
			dquote = !dquote;
		else if (*line2 == '\'' && !dquote)
			squote = !squote;
		if (!squote && !dquote && (strchr("|<>", *line2)))
		{
			if (!strchr(" |<>", *(line2 - 1)))
			{
				expand(shell, shell->line, line2 - shell->line);
				//line2 = shell->line;
			}
			else if (!strchr(" |<>", *(line2 + 1)))
			{
				expand(shell, shell->line, line2 - shell->line + 1);
				line2 = line2 - 1;
			}
		}
		line2++;
	}
}

int	main(void)
{
	t_shell	sh;

	sh.line = strdup("<<1 env|grep path|wc -l >3 >>2 <4");
	char	*tmp = sh.line;
	printf("main before: %s\n", sh.line); 

	check_expand(&sh, sh.line);
	printf("main after: %s\n", sh.line);

	free(sh.line);
}