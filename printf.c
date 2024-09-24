#include <stdarg.h>
#include <unistd.h>

/**
 * _printf - Custom implementation of printf
 * @format: A string that contains directives and conversion specifiers
 * Return: The number of characters printed (excluding the null byte)
 */
int _printf(const char *format, ...)
{
    va_list args;
    int i = 0, count = 0;
    char c, *str;

    if (!format)
        return (-1);

    va_start(args, format);

    while (format[i] != '\0')
    {
        if (format[i] == '%')
        {
            i++;
            if (format[i] == 'c')  // Handle character
            {
                c = va_arg(args, int);
                count += write(1, &c, 1);
            }
            else if (format[i] == 's')  // Handle string
            {
                str = va_arg(args, char *);
                if (str == NULL)
                    str = "(null)";
                while (*str)
                    count += write(1, str++, 1);
            }
            else if (format[i] == '%')  // Handle %
            {
                count += write(1, "%", 1);
            }
            else  // Unsupported specifier
            {
                count += write(1, &format[i], 1);
            }
        }
        else
        {
            count += write(1, &format[i], 1);  // Handle normal characters
        }
        i++;
    }

    va_end(args);
    return (count);
}
