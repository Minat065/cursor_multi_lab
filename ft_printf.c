/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Claude3.7 <cursor@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by Claude3.7         #+#    #+#             */
/*   Updated: 2023/01/01 00:00:00 by Claude3.7        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @brief 書式指定子に応じた処理を行う関数
 * 
 * @param format 現在の書式指定子の位置
 * @param args 可変引数リスト
 * @param count 出力文字数へのポインタ
 * @return int 処理に成功した場合0、失敗した場合-1
 */
static int	ft_format_specifier(const char format, va_list args, int *count)
{
	int	result;

	result = 0;
	if (format == 'c')
		result = ft_print_char(args, count);
	else
	{
		/* 他の変換指定子の場合はここに実装を追加 */
		/* 現在は%cのみの実装なので、それ以外の場合は文字としてそのまま出力 */
		if (ft_putchar(format, count) == -1)
			return (-1);
	}
	return (result);
}

/**
 * @brief 書式指定文字列に従って出力を行う関数
 * 
 * @param format 書式指定文字列
 * @param ... 可変個の引数
 * @return int 出力された文字数、エラー時は-1
 */
int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		i;

	if (!format)
		return (-1);
	va_start(args, format);
	count = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (!format[i])
				break ;
			if (ft_format_specifier(format[i], args, &count) == -1)
			{
				va_end(args);
				return (-1);
			}
		}
		else if (ft_putchar(format[i], &count) == -1)
		{
			va_end(args);
			return (-1);
		}
		i++;
	}
	va_end(args);
	return (count);
} 