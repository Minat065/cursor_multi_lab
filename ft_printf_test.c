#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include "ft_printf.h"

// 色のエスケープシーケンス
#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

// テスト結果を保存するファイル名
#define FT_PRINTF_OUTPUT "ft_printf_output.txt"
#define PRINTF_OUTPUT "printf_output.txt"

// テストをカウント
int test_count = 0;
int success_count = 0;

// 分類ごとのカウント
int s_tests = 0, s_success = 0;
int d_tests = 0, d_success = 0;
int x_tests = 0, x_success = 0;
int p_tests = 0, p_success = 0;

// 出力リダイレクト関数
void redirect_to_file(const char *filename) {
    freopen(filename, "w", stdout);
}

// 元の標準出力に戻す
void reset_stdout() {
    fclose(stdout);
    freopen("/dev/tty", "w", stdout);
}

// ファイルの内容を比較
int compare_files() {
    FILE *ft_file = fopen(FT_PRINTF_OUTPUT, "r");
    FILE *std_file = fopen(PRINTF_OUTPUT, "r");
    
    if (!ft_file || !std_file) {
        printf("Error opening output files\n");
        return 0;
    }
    
    char ft_buf[1024];
    char std_buf[1024];
    
    int is_same = 1;
    
    while (fgets(ft_buf, sizeof(ft_buf), ft_file) && fgets(std_buf, sizeof(std_buf), std_file)) {
        if (strcmp(ft_buf, std_buf) != 0) {
            is_same = 0;
            break;
        }
    }
    
    // ファイルの長さが異なる場合
    if (fgets(ft_buf, sizeof(ft_buf), ft_file) || fgets(std_buf, sizeof(std_buf), std_file)) {
        is_same = 0;
    }
    
    fclose(ft_file);
    fclose(std_file);
    
    return is_same;
}

// 戻り値の比較
void compare_return(const char *test_name, int ft_ret, int std_ret) {
    test_count++;
    
    if (ft_ret == std_ret) {
        success_count++;
        printf(GREEN "✓ %s: 戻り値一致 (%d)" RESET "\n", test_name, ft_ret);
        
        // テスト分類に応じてカウント
        if (strstr(test_name, "[s]")) s_success++;
        else if (strstr(test_name, "[d]")) d_success++;
        else if (strstr(test_name, "[x]")) x_success++;
        else if (strstr(test_name, "[p]")) p_success++;
    } else {
        printf(RED "✗ %s: 戻り値不一致 (ft_printf: %d, printf: %d)" RESET "\n", 
               test_name, ft_ret, std_ret);
    }
}

// 出力と戻り値のテスト
void test_printf(const char *test_name, const char *format, ...) {
    va_list args1, args2, args3, args4;
    int ft_ret, std_ret;
    
    // テスト分類に応じてカウント
    if (strstr(test_name, "[s]")) s_tests++;
    else if (strstr(test_name, "[d]")) d_tests++;
    else if (strstr(test_name, "[x]")) x_tests++;
    else if (strstr(test_name, "[p]")) p_tests++;
    
    // 引数の初期化
    va_start(args1, format);
    va_copy(args2, args1);
    va_copy(args3, args1);
    va_copy(args4, args1);
    
    // ft_printfの出力をファイルに保存
    redirect_to_file(FT_PRINTF_OUTPUT);
    ft_ret = vft_printf(format, args1);
    reset_stdout();
    
    // printfの出力をファイルに保存
    redirect_to_file(PRINTF_OUTPUT);
    std_ret = vprintf(format, args2);
    reset_stdout();
    
    // 出力を比較
    int output_match = compare_files();
    
    // 結果を表示
    if (output_match) {
        printf(GREEN "✓ %s: 出力一致" RESET "\n", test_name);
    } else {
        printf(RED "✗ %s: 出力不一致" RESET "\n", test_name);
        
        // 不一致の場合、両方の出力を表示
        printf("  ft_printf出力: ");
        redirect_to_file("/dev/tty");
        vft_printf(format, args3);
        reset_stdout();
        
        printf("\n  printf出力: ");
        redirect_to_file("/dev/tty");
        vprintf(format, args4);
        reset_stdout();
        printf("\n");
    }
    
    // 戻り値の比較
    compare_return(test_name, ft_ret, std_ret);
    
    va_end(args1);
    va_end(args2);
    va_end(args3);
    va_end(args4);
    
    printf("\n");
}

// 文字列のテスト
void test_string_format() {
    printf("===== 文字列（%%s）のテスト =====\n\n");
    
    // 基本テスト
    test_printf("[s] 基本的な文字列", "%s", "Hello, World!");
    test_printf("[s] 空の文字列", "%s", "");
    
    // NULL文字列
    test_printf("[s] NULL文字列", "%s", NULL);
    
    // 複数の文字列
    test_printf("[s] 複数の文字列", "%s %s %s", "One", "Two", "Three");
    
    // 特殊文字を含む文字列
    test_printf("[s] 特殊文字", "%s", "Special chars: \t\n\r\v\f");
    
    // 長い文字列
    char long_str[1000];
    memset(long_str, 'A', 999);
    long_str[999] = '\0';
    test_printf("[s] 長い文字列", "%s", long_str);
}

// 整数のテスト
void test_decimal_format() {
    printf("===== 整数（%%d）のテスト =====\n\n");
    
    // 基本テスト
    test_printf("[d] 基本的な整数", "%d", 42);
    test_printf("[d] ゼロ", "%d", 0);
    
    // 負の数
    test_printf("[d] 負の数", "%d", -42);
    
    // 最大値・最小値
    test_printf("[d] INT_MAX", "%d", INT_MAX);
    test_printf("[d] INT_MIN", "%d", INT_MIN);
    
    // 複数の整数
    test_printf("[d] 複数の整数", "%d %d %d", 1, 2, 3);
    
    // 複合フォーマット
    test_printf("[d] 文字列と整数の組み合わせ", "Number: %d", 42);
    test_printf("[d] 複数の型", "Number: %d, String: %s", 42, "test");
}

// 16進数のテスト
void test_hex_format() {
    printf("===== 16進数（%%x）のテスト =====\n\n");
    
    // 基本テスト
    test_printf("[x] 基本的な16進数", "%x", 0x42);
    test_printf("[x] ゼロ", "%x", 0);
    
    // 大きな数値
    test_printf("[x] 大きな数値", "%x", 0xABCDEF);
    
    // 最大値
    test_printf("[x] UINT_MAX", "%x", UINT_MAX);
    
    // 複数の16進数
    test_printf("[x] 複数の16進数", "%x %x %x", 0x10, 0x20, 0x30);
    
    // 負の数（符号なし整数として扱われる）
    test_printf("[x] 負の数", "%x", -1);
    
    // 大文字16進数
    test_printf("[x] 大文字16進数", "%X", 0xabcdef);
}

// ポインタのテスト
void test_pointer_format() {
    printf("===== ポインタ（%%p）のテスト =====\n\n");
    
    // 基本テスト
    int num = 42;
    test_printf("[p] 変数へのポインタ", "%p", &num);
    
    // NULL
    test_printf("[p] NULLポインタ", "%p", NULL);
    
    // 様々な型へのポインタ
    char c = 'A';
    float f = 3.14f;
    char *str = "test";
    
    test_printf("[p] char へのポインタ", "%p", &c);
    test_printf("[p] float へのポインタ", "%p", &f);
    test_printf("[p] char* へのポインタ", "%p", &str);
    test_printf("[p] 文字列リテラルへのポインタ", "%p", "test");
    
    // メモリアドレスの値
    test_printf("[p] 数値からのポインタ", "%p", (void*)0x12345678);
    
    // malloc()したメモリへのポインタ
    void *ptr = malloc(10);
    test_printf("[p] mallocメモリへのポインタ", "%p", ptr);
    free(ptr);
}

// 複合テスト
void test_combined_formats() {
    printf("===== 複合フォーマットのテスト =====\n\n");
    
    test_printf("[複合] 文字列と数値", "String: %s, Number: %d", "test", 42);
    test_printf("[複合] 全タイプ", "String: %s, Decimal: %d, Hex: %x, Pointer: %p", 
                "test", 42, 0xABC, &test_combined_formats);
    
    // パーセント記号
    test_printf("[複合] パーセント記号", "100%% complete");
    
    // 連続した同じフォーマット
    test_printf("[複合] 連続した同じフォーマット", "%d%d%d", 1, 2, 3);
    
    // 順序を混ぜる
    test_printf("[複合] 混合順序", "%x %s %d %p", 0xABC, "test", 42, &test_combined_formats);
}

// 異常系テスト
void test_edge_cases() {
    printf("===== 異常系テスト =====\n\n");
    
    // フォーマット文字列が空
    test_printf("[異常] 空のフォーマット", "");
    
    // フォーマット指定子のみ
    test_printf("[異常] 指定子のみ", "%s", "");
    
    // 対応していないフォーマット指定子
    // 注意: 未対応の指定子はft_printfで実装されていない可能性があります
    test_printf("[異常] 未対応の指定子", "%z");
    
    // 連続した%
    test_printf("[異常] 連続した%", "%%%%%%%%%%");
    
    // フォーマット文字列の最後が%
    test_printf("[異常] 最後が%", "Test%");
}

int main() {
    printf("ft_printfのテストを開始します\n\n");
    
    // 文字列テスト
    test_string_format();
    
    // 整数テスト
    test_decimal_format();
    
    // 16進数テスト
    test_hex_format();
    
    // ポインタテスト
    test_pointer_format();
    
    // 複合テスト
    test_combined_formats();
    
    // 異常系テスト
    test_edge_cases();
    
    // 結果サマリー
    printf("\n===== テスト結果サマリー =====\n");
    printf("総テスト数: %d, 成功: %d, 失敗: %d（成功率: %.1f%%）\n", 
           test_count, success_count, test_count - success_count, 
           (float)success_count / test_count * 100);
    
    printf("\n分類別結果:\n");
    printf("  文字列(%%s): %d/%d (%.1f%%)\n", s_success, s_tests, 
           s_tests > 0 ? (float)s_success / s_tests * 100 : 0);
    printf("  整数(%%d): %d/%d (%.1f%%)\n", d_success, d_tests, 
           d_tests > 0 ? (float)d_success / d_tests * 100 : 0);
    printf("  16進数(%%x): %d/%d (%.1f%%)\n", x_success, x_tests, 
           x_tests > 0 ? (float)x_success / x_tests * 100 : 0);
    printf("  ポインタ(%%p): %d/%d (%.1f%%)\n", p_success, p_tests, 
           p_tests > 0 ? (float)p_success / p_tests * 100 : 0);
    
    // 一時ファイルの削除
    remove(FT_PRINTF_OUTPUT);
    remove(PRINTF_OUTPUT);
    
    return 0;
} 