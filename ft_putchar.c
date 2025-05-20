/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Claude3.7 <cursor@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by Claude3.7         #+#    #+#             */
/*   Updated: 2023/01/01 00:00:00 by Claude3.7        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief 文字を出力する関数
 * 
 * @param c 出力する文字
 * @param count 現在までに出力された文字数へのポインタ
 * @return int 出力に成功した場合1、失敗した場合-1
 */
int	ft_putchar(char c, int *count)
{
	ssize_t	result;

	if (!count)
		return (-1);
	result = write(1, &c, 1);
	if (result == -1)
		return (-1);
	(*count)++;
	return (1);
} 