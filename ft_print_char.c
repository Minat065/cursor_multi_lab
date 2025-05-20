/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Claude3.7 <cursor@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by Claude3.7         #+#    #+#             */
/*   Updated: 2023/01/01 00:00:00 by Claude3.7        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief %c変換指定子を処理する関数
 * 
 * @param args 可変引数リスト
 * @param count 現在までに出力された文字数へのポインタ
 * @return int 出力に成功した場合0、失敗した場合-1
 */
int	ft_print_char(va_list args, int *count)
{
	char	c;

	if (!count)
		return (-1);
	c = (char)va_arg(args, int);
	if (ft_putchar(c, count) == -1)
		return (-1);
	return (0);
} 