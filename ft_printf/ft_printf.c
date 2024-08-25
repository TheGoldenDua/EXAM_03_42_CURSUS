#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

char *ft_strchr(const char *str, int c)
{
    unsigned char *s;
    unsigned int i;

    i = 0;
    s = (unsigned char *)str;
    while(s[i] && s[i] != (unsigned char)c)
        i++;
    return ((char *)&s[i]);
}

void ft_putchar(int c, int *len)
{
    write(1, &c, 1);
    (*len)++;
}

void ft_putstr(const char *str, int *len)
{
    int i = 0;

    if(!str)
    {
        ft_putstr("(null)", len);
        return ;
    }
    while(str[i])
    {
        ft_putchar(str[i], len);
        i++;
    }
}

void ft_putnbr(int nb, int *len)
{
    if(nb == -2147483648)
        ft_putstr("-2147483648", len);
    else if(nb < 0)
    {
        ft_putchar('-', len);
        ft_putnbr(-nb, len);
    }
    else if(nb >= 10)
    {
        ft_putnbr(nb / 10, len);
        ft_putchar(nb % 10 + '0', len);
    }
    else
        ft_putchar(nb + '0', len);
}

void ft_puthex(unsigned int nb, int *len)
{
    char *base = "0123456789abcdef";

    if(nb >= 16)
        ft_puthex(nb / 16, len);
    ft_putchar(base[nb % 16], len);
}

void check_flag(int c, va_list args, int *len)
{
    if(c == 'd')
        ft_putnbr(va_arg(args, int), len);
    else if(c == 's')
        ft_putstr(va_arg(args, char *), len);
    else if(c == 'x')
        ft_puthex(va_arg(args, unsigned int), len);
    else
        *len = -1;
}

int ft_printf(const char *str, ... )
{
    int len = 0;
    int i = 0;
    va_list args;

    if(!str)
        return (-1);
    va_start(args, str);
    while(str[i])
    {
        if(str[i] == '%' && ft_strchr("sdx", str[i + 1]))
        {
            check_flag(str[i + 1], args, &len);
            if(len == -1)
	    {
		va_end(args);
                return (-1);
	    }
            i++;
        }
        else
            ft_putchar(str[i], &len);
        i++;
    }
    va_end(args);
    return (len);
}
