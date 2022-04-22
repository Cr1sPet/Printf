# FT_PRINTF

[SUBJECT](subject/en.subject.pdf "ft_printf subject")

* The aim of this project is to recode printf.

The following transformations were implemented:

* **%c** Prints a single character.
* **%s** Prints a string (as defined by the common C convention).
* **%p** The void * pointer argument has to be printed in hexadecimal format.
* **%d** Prints a decimal (base 10) number.
* **%i** Prints an integer in base 10.
* **%u** Prints an unsigned decimal (base 10) number.
* **%x** Prints a number in hexadecimal (base 16) lowercase format.
* **%X** Prints a number in hexadecimal (base 16) uppercase format.
* **%%** Prints a percent sign.

All combinations of the following flags have been implemented :
 * ’-0.’, ’# +’


### Clone project
```
git clone git@github.com:CrsPet/my_printf.git
```
<!-- ### How to use
```
cd my_printf
make
ARG="input numbers"; ./push_swap $ARG // get instructions to sort
ARG="input numbers"; ./push_swap $ARG | wc -l // number of instructions
ARG="input numbers"; ./push_swap $ARG | ./checker $ARG // "ОК" if stack sorted, else "KO", on error prints "Error!"

make clean to clean all object files.
make fclean to clean libftprintf.a and all object files.
make re to recompile this project.

*input numbers - random sequence of unique int (integer)

```
--- -->
The project is written in strict accordance with [Norminette codestyle](https://github.com/42School/norminette)

