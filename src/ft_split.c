/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenoit <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:39:55 by abenoit           #+#    #+#             */
/*   Updated: 2020/08/18 16:10:24 by abenoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t		wordlen(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		count++;
	}
	return (count);
}

static size_t		wordcount(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			i += wordlen(&s[i], c);
		}
		else
			i++;
	}
	return (count);
}

static char			*wordcpy(char *dst, const char *src, char c)
{
	int	i;

	i = 0;
	while (src[i] != c && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static char			**ft_free(char **ret, int j)
{
	int i;

	i = 0;
	while (i < j)
	{
		free(ret[i]);
		i++;
	}
	free(ret);
	return (NULL);
}

char				**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**ret;

	if (s == NULL)
		return (NULL);
	if (!(ret = malloc((wordcount(s, c) + 2) * sizeof(char*))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (!(ret[j] = malloc(((wordlen(&s[i], c) + 2)) * sizeof(char))))
				return (ft_free(ret, j));
			wordcpy(ret[j], &s[i], c);
			j++;
			i += wordlen(&s[i], c);
		}
		else
			i++;
	}
	ret[j] = NULL;
	return (ret);
}
