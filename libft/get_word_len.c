/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 22:46:06 by sako              #+#    #+#             */
/*   Updated: 2019/05/05 22:53:05 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		get_word_len(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s == c)
		s++;
	while (*s != c && *s != '\0')
	{
		s++;
		len++;
	}
	return (len);
}