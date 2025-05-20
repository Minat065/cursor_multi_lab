/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flag_parser.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Claude                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:00:00 by Claude            #+#    #+#             */
/*   Updated: 2023/12/01 12:00:00 by Claude           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** フラグ解析関数: 与えられた書式文字列のフラグを解析し、t_format構造体に設定する
** 対応するフラグ:
** - '-': 左寄せ
** - '0': 0埋め
** - '*': 幅や精度を可変引数から取得
** - '.': 精度指定
**
** @param format 解析する書式文字列のポインタ
** @param fmt フラグ情報を格納する構造体
** @param args 可変引数リスト
** @return 解析後の書式文字列の位置
*/
const char	*parse_flags(const char *format, t_format *fmt, va_list args)
{
	fmt->left_align = 0;
	fmt->zero_padding = 0;
	fmt->width = 0;
	fmt->precision = -1;

	// フラグの解析
	while (*format == '-' || *format == '0' || *format == '*' || *format == '.')
	{
		if (*format == '-')
			fmt->left_align = 1;
		else if (*format == '0')
			fmt->zero_padding = 1;
		else if (*format == '*')
		{
			fmt->width = va_arg(args, int);
			if (fmt->width < 0)
			{
				fmt->left_align = 1;
				fmt->width = -fmt->width;
			}
		}
		else if (*format == '.')
		{
			format++;
			if (*format == '*')
			{
				fmt->precision = va_arg(args, int);
				format++;
			}
			else
			{
				fmt->precision = 0;
				while (*format >= '0' && *format <= '9')
				{
					fmt->precision = fmt->precision * 10 + (*format - '0');
					format++;
				}
				format--; // 数字の後ろの文字に戻る
			}
		}
		format++;
	}

	// 左寄せフラグがある場合、0埋めフラグは無効になる
	if (fmt->left_align)
		fmt->zero_padding = 0;

	// 数字フラグの解析 (幅の指定)
	if (*format >= '0' && *format <= '9')
	{
		fmt->width = 0;
		while (*format >= '0' && *format <= '9')
		{
			fmt->width = fmt->width * 10 + (*format - '0');
			format++;
		}
	}

	return (format);
}

/* 
** 警告：この実装には以下の潜在的な問題があります：
** 1. 幅や精度の数値が整数の最大値を超える場合の処理が不足しています
** 2. フラグの組み合わせによっては予期しない動作をする可能性があります
** 3. t_format構造体の完全な定義が必要です
** 4. 実際のft_printf.hヘッダーファイルが必要です
**
** テスト推奨ケース：
** - 基本的なフラグ: "%0d", "%-10s", "%.5f"
** - 複合フラグ: "%-0.10d", "%*.*d"
** - エッジケース: "%..5d", "%--5s", "%0-5d"
*/ 