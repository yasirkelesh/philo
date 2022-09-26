/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtolower.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 17:56:15 by ademirci          #+#    #+#             */
/*   Updated: 2022/08/28 18:03:22 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strtolower(const char *str)
{
	int		i;
	char	*lowstr;

	i = -1;
	lowstr = ft_strdup(str);
	while (lowstr[++i])
		lowstr[i] = ft_tolower(lowstr[i]);
	return (lowstr);
}
