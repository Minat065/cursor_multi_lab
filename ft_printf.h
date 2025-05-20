/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Claude3.7 <cursor@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by Claude3.7         #+#    #+#             */
/*   Updated: 2023/01/01 00:00:00 by Claude3.7        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

/**
 * @brief 書式指定文字列に従って出力を行う関数
 * 
 * @param format 書式指定文字列
 * @param ... 可変個の引数
 * @return int 出力された文字数
 */
int	ft_printf(const char *format, ...);

/**
 * @brief 文字を出力する関数
 * 
 * @param c 出力する文字
 * @param count 現在までに出力された文字数へのポインタ
 * @return int 出力に成功した場合1、失敗した場合-1
 */
int	ft_putchar(char c, int *count);

/**
 * @brief %c変換指定子を処理する関数
 * 
 * @param args 可変引数リスト
 * @param count 現在までに出力された文字数へのポインタ
 * @return int 出力に成功した場合0、失敗した場合-1
 */
int	ft_print_char(va_list args, int *count);

#endif 