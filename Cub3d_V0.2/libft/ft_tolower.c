/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdela <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:52:52 by maabdela          #+#    #+#             */
/*   Updated: 2024/03/07 15:10:38 by maabdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
	DESCRIPTION :
	The function ft_tolower converts a given uppercase letter c to its
	lowercase equivalent.

	RETURN VALUE :
	The lowercase equivalent letter.
	The original character c if c is not an uppercase letter.	
*/

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}
