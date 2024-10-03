/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_digit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:52:52 by maabdela          #+#    #+#             */
/*   Updated: 2024/04/07 15:09:02 by maabdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

bool	no_digit(char *str)
{
	int		i;
	bool	found_no_digit;

	i = 0;
	found_no_digit = true;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1)
			found_no_digit = false;
		i++;
	}
	return (found_no_digit);
}
