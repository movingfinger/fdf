/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_upper_letter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 22:41:02 by sako              #+#    #+#             */
/*   Updated: 2019/05/08 22:57:17 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		is_upper_letter(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}