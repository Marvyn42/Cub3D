/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <mamaquig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 18:03:14 by agautier          #+#    #+#             */
/*   Updated: 2021/01/28 17:20:53 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find_sep(char s, char *charset)
{
	int i_sep;

	i_sep = 0;
	while (charset[i_sep] != '\0')
	{
		if (charset[i_sep] == s)
			return (1);
		i_sep++;
	}
	return (0);
}

static int	ft_word_count(char *str, char *charset)
{
	int i_str;
	int word_count;

	i_str = 0;
	word_count = 0;
	while (str[i_str])
	{
		while (str[i_str])
		{
			if (ft_find_sep(str[i_str], charset) == 0)
			{
				word_count++;
				break ;
			}
			i_str++;
		}
		while (str[i_str])
		{
			if (ft_find_sep(str[i_str], charset) == 1)
				break ;
			i_str++;
		}
	}
	return (word_count);
}

static int	*ft_len_count(int *words_len, char *str, char *charset)
{
	int	i_len;
	int i_str;

	i_len = 0;
	i_str = 0;
	while (str[i_str] != '\0')
	{
		while (str[i_str] != '\0')
		{
			if (ft_find_sep(str[i_str], charset) == 0)
				break ;
			i_str++;
		}
		while (str[i_str] != '\0')
		{
			if (ft_find_sep(str[i_str], charset) == 1)
				break ;
			i_str++;
			words_len[i_len]++;
		}
		i_len++;
	}
	return (words_len);
}

static int	fill_tab(char ***tab, int *words_len, char *str, char *charset)
{
	int		d1;
	int		d2;
	int		i_str;
	int		word_count;

	d1 = 0;
	i_str = 0;
	word_count = ft_word_count(str, charset);
	while (d1 < word_count && str[i_str])
	{
		if (!((*tab)[d1] = malloc((words_len[d1] + 1) * sizeof(char) + 1)))
			return (0);
		while (ft_find_sep(str[i_str], charset))
			i_str++;
		d2 = 0;
		while (str[i_str] && ft_find_sep(str[i_str], charset) == 0)
			(*tab)[d1][d2++] = str[i_str++];
		(*tab)[d1][d2++] = '\0';
		d1++;
	}
	(d1 != 0) ? (*tab)[d1 - 1][d2] = '\0' : 0;
	(*tab)[d1] = 0;
	return (1);
}

char		**ft_split_charset(char *str, char *charset)
{
	char	**tab;
	int		words_count;
	int		words_len[ft_word_count(str, charset)];
	int		split;
	int		i;

	if (!str)
		return (0);
	words_count = ft_word_count(str, charset);
	if (!(tab = malloc((words_count + 1) * sizeof(char*))))
		return (0);
	i = 0;
	while (i < words_count)
		words_len[i++] = 0;
	ft_len_count(words_len, str, charset);
	split = fill_tab(&tab, words_len, str, charset);
	if (split)
		return (tab);
	return (0);
}
