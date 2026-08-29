# ft-printf

A fonction that recreates the behavior of the origina lprintf (without the buffer management). 

>[!Caution]
>This version of ft_printf doesn't handle the flags from the original printf !

It handles the following conversion: 

| Conversion | Description |
| ---------- | ----------- |
| %d, %i | Prints a decimal in base 10 |
| %c | Prints a single character |
| %s | Prints a string |
| %p | Prints a void * argument in hexadecimal |
| %u | Prints an unsigned decimal in base 10 |
| %x | Prints a number in hexadecimal, lowercase format |
| %X | Prints a number in hexadecimal, uppercase format |
| %% | Prints a percent sign |

>[!Note]
>Libft is present in this projet, you can check [here](https://github.com/Ewan-lrx/00_libft) the libft projet.
