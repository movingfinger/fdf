/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_lower_letter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 22:38:54 by sako              #+#    #+#             */
/*   Updated: 2019/05/08 22:57:12 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		is_lower_letter(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}
