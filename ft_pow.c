/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:46:03 by zouazrou          #+#    #+#             */
/*   Updated: 2025/01/16 17:47:15 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_pow(double base, int exponent)
{
	double	result;
	int		i;

	i = 0;
	result = 1.0;
	if (exponent < 0)
	{
		base = 1 / base;
		exponent = -exponent;
	}
	while (i < exponent)
	{
		result *= base;
		i++;
	}
	return (result);
}
