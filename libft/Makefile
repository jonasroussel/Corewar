# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jroussel <jroussel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/04 16:42:14 by jroussel          #+#    #+#              #
#    Updated: 2018/12/18 16:43:17 by jroussel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = libft.a
INC_DIR = include
SRC_DIR = src
BIN_DIR = bin
FLAGS   = -Wall -Wextra -Werror
UNAME_S 		:= $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	ESC				:= \033
else
	ESC				:= \e
endif

SRC     = ft_memset.c \
          ft_memput.c \
          ft_bzero.c \
          ft_memcpy.c \
          ft_memccpy.c \
          ft_memchr.c \
          ft_memcmp.c \
          ft_memalloc.c \
          ft_memdel.c \
          ft_strlen.c \
          ft_strdup.c \
          ft_strcpy.c \
          ft_strncpy.c \
          ft_strcat.c \
          ft_strncat.c \
          ft_strchr.c \
          ft_strrchr.c \
          ft_strstr.c \
          ft_strnstr.c \
          ft_strcmp.c \
          ft_strncmp.c \
          ft_strnew.c \
          ft_strdel.c \
          ft_strclr.c \
          ft_striter.c \
          ft_strsub.c \
          ft_strjoin.c \
          ft_strtrim.c \
          ft_strsplit.c \
          ft_strsplitdel.c \
          ft_strupper.c \
          ft_strlower.c \
          ft_strcap.c \
          ft_strreplace.c \
          ft_lstnew.c \
          ft_lstdel.c \
          ft_lstlen.c \
          ft_lstadd.c \
          ft_lstaddi.c \
          ft_lstpush.c \
          ft_lstremove.c \
          ft_lstctn.c \
          ft_lstget.c \
          ft_lstiter.c \
		  ft_printf.c \
          ft_isblank.c \
          ft_islower.c \
          ft_isupper.c \
          ft_isalpha.c \
          ft_isdigit.c \
          ft_isalnum.c \
          ft_isascii.c \
          ft_isnl.c \
          ft_isprint.c \
	  	  ft_isnumber.c \
		  ft_equal.c \
          ft_pow.c \
          ft_atol.c \
          ft_ltoa.c \
          ft_ultoa_base.c \
          ft_ultoa.c \
          ft_toupper.c \
          ft_tolower.c \
          ft_gnl.c \
		  printf/pf_buffer.c \
          printf/pf_color.c \
          printf/pf_convert.c \
          printf/pf_format.c \
          printf/pf_output.c \
          printf/pf_parse.c \
          printf/pf_unicode.c \
          printf/pf_util.c \
          printf/pf_vars.c \
          printf/pf_func_s.c \
          printf/pf_func_ss.c \
          printf/pf_func_p.c \
          printf/pf_func_d.c \
          printf/pf_func_dd.c \
          printf/pf_func_i.c \
          printf/pf_func_o.c \
          printf/pf_func_oo.c \
          printf/pf_func_u.c \
          printf/pf_func_uu.c \
          printf/pf_func_x.c \
          printf/pf_func_xx.c \
          printf/pf_func_c.c \
          printf/pf_func_cc.c \
          printf/pf_func_percent.c \
          printf/pf_func_n.c \
          printf/pf_func_w.c \
          printf/pf_func_b.c

SRC    := $(addprefix $(SRC_DIR)/,$(SRC))
BIN     = $(subst $(SRC_DIR),$(BIN_DIR),$(SRC:.c=.o))

ISASMR  =
STOP	= 0

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BIN_DIR) 2> /dev/null
	@mkdir -p $(BIN_DIR)/printf 2> /dev/null
	@gcc $(FLAGS) -I$(INC_DIR) -o $@ -c $< && printf "$(ISASMR)$(ESC)[90m[$(ESC)[33m Libft $(ESC)[90m]$(ESC)[39m %-25s : $(ESC)[32mCompiled$(ESC)[0m\n" $(subst $(SRC_DIR)/,,$<) || { printf "$(ESC)[90m[$(ESC)[33m Libft $(ESC)[90m]$(ESC)[39m %-25s : $(ESC)[31mError$(ESC)[0m\n" $(subst $(SRC_DIR)/,,$<); exit $(STOP); }

$(NAME): $(BIN)
	@ar rc $(NAME) $(BIN) && ranlib $(NAME) && chmod +x $(NAME) && printf "$(ISASMR)$(ESC)[90m------------------[ $(ESC)[33mLibft $(ESC)[90m]-------------------$(ESC)[39m\n$(ESC)[90m|            $(ESC)[32mCompilation Finished$(ESC)[90m            |$(ESC)[39m\n$(ESC)[90m----------------------------------------------$(ESC)[39m\n\n" || { printf "$(ESC)[90m------------------[ $(ESC)[33mLibft $(ESC)[90m]------------------$(ESC)[39m\n$(ESC)[90m|             $(ESC)[31mCompilation Failed$(ESC)[90m            |$(ESC)[39m\n$(ESC)[90m---------------------------------------------$(ESC)[39m\n\n"; exit $(STOP); }

all: $(NAME)
clean:
	@rm -rf $(BIN_DIR)
lclean:
	@rm -f $(NAME)
fclean: clean lclean
re: fclean all
