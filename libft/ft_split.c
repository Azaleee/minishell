/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosmont <mosmont@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:56:53 by mosmont           #+#    #+#             */
/*   Updated: 2024/10/24 15:31:27 by mosmont          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"

// static int	count_words(char const *str, char c)
// {
// 	int		in_word;
// 	int		result;

// 	result = 0;
// 	in_word = 0;
// 	while (*str)
// 	{
// 		if ((*str != c) && in_word == 0)
// 		{
// 			in_word = 1;
// 			result++;
// 		}
// 		else if (*str == c)
// 			in_word = 0;
// 		str++;
// 	}
// 	return (result);
// }

// static char	*ft_strcpy_split(char const *start, char const *end)
// {
// 	int		len;
// 	char	*str;
// 	int		i;

// 	len = end - start;
// 	str = malloc((len + 1) * sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (i < len)
// 	{
// 		str[i] = start[i];
// 		i++;
// 	}
// 	str[len] = '\0';
// 	return (str);
// }

// static char	*allocate_str(
// 	char **tab,
// 	int len_tab,
// 	char const *start,
// 	char const *end
// 	)
// {
// 	char	*new_str;
// 	int		i;

// 	new_str = ft_strcpy_split(start, end);
// 	if (new_str == NULL)
// 	{
// 		i = 0;
// 		if (tab[0] == NULL)
// 			return (NULL);
// 		while (i < len_tab)
// 		{
// 			free(tab[i]);
// 			i++;
// 		}
// 		free(tab);
// 	}
// 	return (new_str);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char		**split_tab;
// 	int			i;
// 	char const	*start;
// 	char		*new_str;

// 	split_tab = malloc((count_words(s, c) + 1) * sizeof(char *));
// 	if (split_tab == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (*s)
// 	{
// 		while (*s && *s == c)
// 			s++;
// 		start = s;
// 		while (*s && *s != c)
// 			s++;
// 		if (start < s)
// 		{
// 			new_str = allocate_str(split_tab, i, start, s);
// 			if (new_str == NULL)
// 				return (NULL);
// 			split_tab[i++] = new_str;
// 		}
// 	}
// 	split_tab[i] = NULL;
// 	return (split_tab);
// }

#include "libft.h"

static int	count_words(char const *str, char c)
{
	int		in_word;
	int		result;

	result = 0;
	in_word = 0;
	while (*str)
	{
		if ((*str != c) && in_word == 0)
		{
			in_word = 1;
			result++;
		}
		else if (*str == c)
			in_word = 0;
		str++;
	}
	return (result);
}

static int	word_lenght(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	*free_tab(char **tab, int len_tab)
{
	int	i;

	i = 0;
	if (tab[0] == NULL)
		return (NULL);
	while (i < len_tab)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char		**split_tab;
	int			i;
	char		*new_str;
	int			nb_words;

	nb_words = count_words(s, c);
	split_tab = malloc((nb_words + 1) * sizeof(char *));
	if (split_tab == NULL)
		return (NULL);
	i = 0;
	while (i < nb_words)
	{
		while (*s == c)
			s++;
		new_str = ft_substr(s, 0, word_lenght(s, c));
		if (new_str == NULL)
			return (free_tab(split_tab, i));
		split_tab[i] = new_str;
		s += word_lenght(s, c);
		i++;
	}
	split_tab[i] = NULL;
	return (split_tab);
}

// int	main(void)
// {
// 	char	**result;
// 	int		i;
// 	int		j;

// 	result = ft_split("xxxxxxxxhello!", 'x');
// 	i = 0;
// 	j = 0;
// 	while (result[i] != NULL)
// 	{
// 		printf("%s   %d", result[i], count_words("hello", ' '));
// 		i++;
// 	}
// 	free(result);
// 	return (0);
// }
