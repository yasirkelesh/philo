/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoupper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademirci <ademirci@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 18:10:13 by ademirci          #+#    #+#             */
/*   Updated: 2022/08/28 18:11:16 by ademirci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strtoupper(const char *str)
{
	int		i;
	char	*upstr;

	i = -1;
	upstr = ft_strdup(str);
	while (upstr[++i])
		upstr[i] = ft_toupper(upstr[i]);
	return (upstr);
}
