#include <stdarg.h>
#include <unistd.h>

static int ft_putchar(char c)
{
    return write(1, &c, 1);
}

static int ft_putstr(char *str)
{
    int i;

    i = 0;
    if (!str)
        return ft_putstr("(null)");
    while (str[i])
    {
        ft_putchar(str[i]);
        i++;
    }
    return (i);
}

static int ft_putnbr(int n)
{
    int len;

    len = 0;
    if (n == -2147483648)
        return ft_putstr("-2147483648");
    if (n < 0)
    {
        len += ft_putchar('-');
        n = -n;
    }
    if (n >= 10)
        len += ft_putnbr(n / 10);
    len += ft_putchar(n % 10 + '0');
    return (len);
}

static int ft_puthex(unsigned long n, int uppercase)
{
    int len;
    char *base;

    len = 0;
    if (uppercase)
        base = "0123456789ABCDEF";
    else
        base = "0123456789abcdef";
    if (n >= 16)
        len += ft_puthex(n / 16, uppercase);
    len += ft_putchar(base[n % 16]);
    return (len);
}

static int ft_putptr(void *ptr)
{
    unsigned long address;
    int len;

    if (ptr == NULL)
        return ft_putstr("(nil)");
        
    address = (unsigned long)ptr;
    len = ft_putstr("0x");
    len += ft_puthex(address, 0);
    
    return (len);
}

static int ft_format_handler(const char c, va_list args)
{
    if (c == 's')
        return ft_putstr(va_arg(args, char *));
    else if (c == 'd')
        return ft_putnbr(va_arg(args, int));
    else if (c == 'x')
        return ft_puthex(va_arg(args, unsigned int), 0);
    else if (c == 'X')
        return ft_puthex(va_arg(args, unsigned int), 1);
    else if (c == 'p')
        return ft_putptr(va_arg(args, void *));
    else if (c == '%')
        return ft_putchar('%');
    else
        return -1;  // 未対応の指定子
}

int vft_printf(const char *format, va_list args)
{
    int i;
    int count;
    int ret;

    i = 0;
    count = 0;
    while (format[i])
    {
        if (format[i] == '%')
        {
            i++;
            if (!format[i])
                return -1;  // フォーマット文字列の最後が%
            
            ret = ft_format_handler(format[i], args);
            if (ret == -1)
                return -1;  // エラーの場合-1を返す
            count += ret;
        }
        else
            count += ft_putchar(format[i]);
        i++;
    }
    return (count);
}

int ft_printf(const char *format, ...)
{
    va_list args;
    int count;

    va_start(args, format);
    count = vft_printf(format, args);
    va_end(args);
    return (count);
} 