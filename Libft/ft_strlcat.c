/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmarrued <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:38:20 by cmarrued          #+#    #+#             */
/*   Updated: 2024/12/19 15:38:21 by cmarrued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t nb)
{
	size_t	dest_ln;
	size_t	src_ln;
	size_t	i;

	dest_ln = ft_strlen(dest);
	src_ln = ft_strlen(src);
	i = 0;
	if (dest_ln >= nb)
		return (nb + src_ln);
	while (((dest_ln + i + 1) < nb) && src[i] != '\0')
	{
		dest[dest_ln + i] = src[i];
		i++;
	}
	dest[dest_ln + i] = '\0';
	return (dest_ln + src_ln);
}
/*
#include <stdio.h>
int	main(void)
{
	char	dest[] = "hola buenos dias";
	char	src[] = "adios";	
	
	printf("longitud r:%zu\n", ft_strlcat(dest, src, 20));
	printf("%s\n", dest);
	return (0);
}*/
