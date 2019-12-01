/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free_end.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 16:16:05 by sako              #+#    #+#             */
/*   Updated: 2019/08/24 16:16:10 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free_end(const char *s1, char *s2)
{
	char	*temp;

	temp = ft_strjoin(s1, s2);
	if (s2)
		free(s2);
	return (temp);
}