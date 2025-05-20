/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Claude3.7 <cursor@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by Claude3.7         #+#    #+#             */
/*   Updated: 2023/01/01 00:00:00 by Claude3.7        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>

int	main(void)
{
	int	ft_ret;
	int	org_ret;

	printf("===== %%c指定子のテスト =====\n");

	// 基本的な文字テスト
	printf("1. 基本的な文字:\n");
	ft_ret = ft_printf("ft_printf: %c\n", 'a');
	org_ret = printf("   printf: %c\n", 'a');
	printf("ft_ret: %d, org_ret: %d\n\n", ft_ret, org_ret);

	// 空白文字テスト
	printf("2. 空白文字:\n");
	ft_ret = ft_printf("ft_printf: '%c'\n", ' ');
	org_ret = printf("   printf: '%c'\n", ' ');
	printf("ft_ret: %d, org_ret: %d\n\n", ft_ret, org_ret);

	// 特殊文字テスト
	printf("3. 特殊文字:\n");
	ft_ret = ft_printf("ft_printf: %c%c%c\n", '!', '@', '#');
	org_ret = printf("   printf: %c%c%c\n", '!', '@', '#');
	printf("ft_ret: %d, org_ret: %d\n\n", ft_ret, org_ret);

	// 数値を文字として出力
	printf("4. 数値を文字として出力:\n");
	ft_ret = ft_printf("ft_printf: %c\n", 65);  // 'A'の文字コード
	org_ret = printf("   printf: %c\n", 65);
	printf("ft_ret: %d, org_ret: %d\n\n", ft_ret, org_ret);

	// NULL文字の扱い (表示されないが、カウントされるか確認)
	printf("5. NULL文字 (表示されないがカウントされるべき):\n");
	ft_ret = ft_printf("ft_printf: '%c'\n", 0);
	org_ret = printf("   printf: '%c'\n", 0);
	printf("ft_ret: %d, org_ret: %d\n\n", ft_ret, org_ret);

	// 複数指定子の組み合わせ
	printf("6. 複数指定子の組み合わせ:\n");
	ft_ret = ft_printf("ft_printf: %c %c %c\n", 'X', 'Y', 'Z');
	org_ret = printf("   printf: %c %c %c\n", 'X', 'Y', 'Z');
	printf("ft_ret: %d, org_ret: %d\n\n", ft_ret, org_ret);

	// %自体のエスケープ
	printf("7. %%自体のエスケープ:\n");
	ft_ret = ft_printf("ft_printf: 100%% 完了、文字: %c\n", 'C');
	org_ret = printf("   printf: 100%% 完了、文字: %c\n", 'C');
	printf("ft_ret: %d, org_ret: %d\n\n", ft_ret, org_ret);

	return (0);
} 