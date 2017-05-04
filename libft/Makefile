NAME		:= libft.a

CC			:=	gcc
CFLAGS		+= -Wall -Wextra -Werror
CFLAGS		+= -I includes

CHR			:=	ft_putchar_fd ft_putchar
DNARR		:=	dnarr_init dnarr_kill dnarr_man
FT_CTYPE	:=	ft_isalnum ft_isalpha ft_isascii	\
				ft_isdigit ft_isprint ft_isspace	\
				ft_tolower ft_toupper
FT_MATH		:=	ft_isinf ft_isnan ft_pow
FT_PRINTF_H :=	ft_pf_chr_conv ft_pf_float_conv ft_pf_fmt_parse \
				ft_pf_handle_spec ft_pf_num_conv ft_pf_bonus ft_pf_handlers \
				ft_pf_str_conv ft_pf_wstr_conv ft_pf_xou_conv
FT_PRINTF	:=	ft_printf ft_printf_more
FT_SORT 	:=	ft_qsort
FT_STDLIB	:=	ft_atoi ft_realloc
FT_STRING	:=	ft_bzero ft_memccpy ft_memchr ft_memcmp ft_memcpy		\
				ft_memmove ft_memset ft_strcat ft_strchr ft_strcmp		\
				ft_strcpy ft_strdup ft_strlcat ft_strlen ft_strncat		\
				ft_strncmp ft_strncpy ft_strndup ft_strnstr ft_strrchr	\
				ft_strstr
FT_VECTOR	:=	ft_cvector
GNL			:=	get_next_line
LST			:=	ft_lstadd ft_lstdelnode ft_lstdel ft_lstdelone ft_lstiter	\
				ft_lstmap ft_lstnew ft_printlst
MEM			:=	ft_free_rows ft_memalloc ft_memdel ft_recalloc ft_swap
NBR			:=	ft_imaxtoa ft_is_sort ft_itoa_base ft_itoa ft_nblen \
				ft_putnbr_fd ft_putnbr ft_range ft_uimaxtoa_base
STR			:=	ft_countwords ft_findchr ft_free_map ft_insrt_to_str 		\
				ft_putendl_fd ft_putendl ft_putstr_fd ft_putstr ft_strclr	\
				ft_strdel ft_strequ ft_striter ft_striteri ft_strjoin		\
				ft_strmap ft_strmapi ft_strnequ ft_strnew ft_strrev			\
				ft_strsplit ft_strsub ft_strtrim

FILES		:=	$(addprefix chr/, $(CHR))				\
				$(addprefix dnarr/, $(DNARR))			\
				$(addprefix ft_ctype/, $(FT_CTYPE))		\
				$(addprefix ft_math/, $(FT_MATH))		\
				$(addprefix ft_printf/, $(FT_PRINTF_H))	\
				$(addprefix ft_printf/, $(FT_PRINTF))	\
				$(addprefix sort/, $(FT_SORT))		\
				$(addprefix ft_stdlib/, $(FT_STDLIB))	\
				$(addprefix ft_string/, $(FT_STRING))	\
				$(addprefix vector/, $(FT_VECTOR))	\
				$(addprefix gnl/, $(GNL))				\
				$(addprefix lst/, $(LST))				\
				$(addprefix mem/, $(MEM))				\
				$(addprefix nbr/, $(NBR))				\
				$(addprefix str/, $(STR))				\

SRC			:=	$(addprefix src/, $(addsuffix .c, $(FILES)))
OBJ			:=	$(SRC:.c=.o)

.PHONY = all clean fclean re

all: $(NAME)

$(OBJ): %.o: %.c
	@$(CC) -c $(CFLAGS) $< -o $@

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "\033[32mCompiled Library\033[0m"

clean:
	@rm -f $(OBJ)
	@echo "\033[32mRemoved Object Files\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[32mRemoved Library\033[0m"

re: fclean all
