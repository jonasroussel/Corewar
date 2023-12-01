#----------------#
#    Variables   #
#----------------#

# Base
INC				= includes
BIN_DIR			= bin
CFLAGS			= -Wall -Wextra -Werror
NCURSES			= -lncurses

# Global
G_NAME			= global
G_SRC_DIR		= g_src

G_SRC			= op.c \
				  vtoi.c \
				  fc.c \

G_SRC			:= $(addprefix $(G_SRC_DIR)/, $(G_SRC))
G_BIN			= $(subst $(G_SRC_DIR),$(BIN_DIR)/$(G_NAME),$(G_SRC:.c=.o))
G_INCLUDES		= $(INC)/op.h $(INC)/global.h

UNAME_S 		= $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	ESC			= \033
else
	ESC			= \e
endif
$(G_NAME)_MSG	= $(ISASMR)$(ESC)[90m[$(ESC)[91mGlobal$(ESC)[90m] 

# .h Checks
HC_NAME			= hcheck
HC_SRC			= $(G_SRC_DIR)/$(HC_NAME).c

# Assembly
ASM_NAME		= asm
ASM_SRC_DIR		= asm_src
ISASMR			= 

ASM_SRC			= asm.c \
		  		  assembly/compile.c \
				  assembly/infos.c \
				  io/debug.c \
				  io/reader.c \
				  io/writer.c \
				  memory/clean.c \
				  memory/init.c \
				  tools/dir.c \
				  tools/fs.c \
				  tools/getters.c \
				  tools/utils.c \
				  parsing/parser.c \
				  parsing/label.c \
				  parsing/command.c \
				  parsing/code/code.c \
				  parsing/code/label.c \
				  parsing/param/direct.c \
				  parsing/param/indirect.c \
				  parsing/param/label.c \
				  parsing/param/param.c \
				  parsing/param/register.c

ASM_SRC			:= $(addprefix $(ASM_SRC_DIR)/, $(ASM_SRC))
ASM_BIN			= $(subst $(ASM_SRC_DIR), $(BIN_DIR)/$(ASM_NAME), $(ASM_SRC:.c=.o))
ASM_INCLUDES	= $(INC)/asm.h $(G_INCLUDES)

$(ASM_NAME)_MSG	= $(ISASMR)$(ESC)[90m[$(ESC)[35m  ASM  $(ESC)[90m]

# Corewar
VM_NAME			= corewar
VM_SRC_DIR		= vm_src

VM_SRC			= corewar.c \
				  vm_init.c \
				  vm_run.c \
				  vm_helpers.c \
				  instructions/live.c \
				  instructions/load.c \
				  instructions/store.c \
				  instructions/operators.c \
				  instructions/zjmp.c \
				  instructions/forks.c \
				  instructions/aff.c \
				  instructions/g_inst_tab.c \
				  visu/visu.c \
				  visu/visu_infos.c \
				  visu/visu_utils.c \
				  visu/visu_memwrite.c
VM_SRC			:= $(addprefix $(VM_SRC_DIR)/, $(VM_SRC))
VM_BIN			= $(subst $(VM_SRC_DIR), $(BIN_DIR)/$(VM_NAME), $(VM_SRC:.c=.o))
VM_INCLUDES		= $(INC)/corewar.h $(G_INCLUDES)

$(VM_NAME)_MSG	= $(ESC)[90m[$(ESC)[36mCorewar$(ESC)[90m]

# Libft
LIBFT_DIR		= libft
LIBFT			= $(LIBFT_DIR)/libft.a
LIBFT_INC		= $(LIBFT_DIR)/include

# Utils
STOP			= 0
ERRORS			= 2> /dev/null

# Messages
MOD_MSG			= printf "$(ISASMR)$(ESC)[90m------------------.name.-------------------$(ESC)[39m\n$(ESC)[90m|            .status.            |$(ESC)[39m\n$(ESC)[90m----------------------------------------------$(ESC)[39m\n\n"
MOD_SUCCESS		= $(subst .status.,$(ESC)[32mCompilation Finished$(ESC)[90m,$(MOD_MSG))
MOD_FAILURE		= $(subst .status., $(ESC)[31mCompilation Failed$(ESC)[90m ,$(MOD_MSG))
F_SUCCESS		= printf " : $(ESC)[32mCompiled$(ESC)[0m\n"
F_FAILURE		= printf " :    $(ESC)[31mError$(ESC)[0m\n"
NOTHING			= echo "Nothing to be done!"
H_ERROR			= printf "\e[31mBAD VALUES IN OP.H\e[39m\n"

#----------------#
#      Rules     #
#----------------#

# Rule to make executables
define COMPILE_EXEC
@if gcc $^ $(NCURSES) -o $@ $(ERRORS); \
then $(subst .name.,$($@_MSG), $(MOD_SUCCESS)); \
else $(subst .name.,$($@_MSG), $(MOD_FAILURE)); exit $(STOP); fi;
endef

# Rule to make objects
define COMPILE_OBJS
@mkdir -p $(dir $@)
@printf "$($(word 2,$(subst /, ,$@))_MSG)\e[39m %-25s" "$(subst $(firstword $(subst /, ,$<))/,,$<)"
@if gcc $(CFLAGS) -I$(INC) -I$(LIBFT_INC) -c $< -o $@ $(ERRORS); then $(F_SUCCESS); else $(F_FAILURE); exit $(STOP); fi;
endef

# Make all
all: check_libft do

# Compile the libft
check_libft:
	@if ! $(MAKE) -q -C $(LIBFT_DIR) all --no-print-directory; \
	then $(MAKE) -C $(LIBFT_DIR) all --no-print-directory; \
	else if $(MAKE) -q do; then $(NOTHING); fi ; fi

do: $(G_NAME) $(ASM_NAME) $(VM_NAME)

# Make libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# Compile global sources
$(BIN_DIR)/$(G_NAME)/%.o: $(G_SRC_DIR)/%.c $(G_INCLUDES) $(HC_NAME)
	$(COMPILE_OBJS)
	@x=false; msg=true; for i in $(subst $(G_SRC_DIR)/,, $(G_SRC:.c=)); do \
	{ test -f "$(BIN_DIR)/$(G_NAME)/$$i.o" && test "$(BIN_DIR)/$(G_NAME)/$$i.o" -nt "$(G_SRC_DIR)/$$i.c" $(addprefix && test "$(BIN_DIR)/$(G_NAME)/$$i.o" -nt ,$(G_INCLUDES)); } || \
	{ if $$x; then x=false; else msg=false; fi; }; \
	if test $$i = $(subst $(G_SRC_DIR)/,, $(subst .c,, $<)); then x=true; fi; done; \
	if $$x; then if $$msg; then $(subst .name.,$(subst $() $(),-,$($(G_NAME)_MSG)), $(MOD_SUCCESS)); \
	else $(subst .name.,$(subst $() $(),-,$($(G_NAME)_MSG)), $(MOD_FAILURE)); exit $(STOP); fi; fi

# Compile asm sources
$(BIN_DIR)/$(ASM_NAME)/%.o: $(ASM_SRC_DIR)/%.c $(ASM_INCLUDES) $(HC_NAME)
	$(COMPILE_OBJS)

# Compile corewar sources
$(BIN_DIR)/$(VM_NAME)/%.o: $(VM_SRC_DIR)/%.c $(VM_INCLUDES) $(HC_NAME)
	$(COMPILE_OBJS)

# Make global
$(G_NAME): $(LIBFT) $(G_BIN)

# Make asm
$(ASM_NAME): $(LIBFT) $(G_BIN) $(ASM_BIN)
	$(COMPILE_EXEC)

# Make asmr
asmr:
	@$(MAKE) $(ASM_NAME) ISASMR="$(ESC)[2m"

# Make corewar
$(VM_NAME): $(LIBFT) $(G_BIN) $(VM_BIN)
	$(COMPILE_EXEC)

$(HC_NAME): $(INC)/op.h
	@gcc -o $@ -I $(INC) -I $(LIBFT_INC) $(HC_SRC)
	@if ! ./$(HC_NAME); then $(H_ERROR); rm -f $(HC_NAME); exit 1; fi;

# Cleaning
clean:
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@rm -rf $(BIN_DIR)
fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) lclean --no-print-directory
	@rm -f $(G_NAME) $(ASM_NAME) $(VM_NAME) $(HC_NAME)
reclean:
	@rm -rf $(BIN_DIR)
	@rm -f $(G_NAME) $(ASM_NAME) $(VM_NAME) $(HC_NAME)
clean_%:
	@rm -rf $(BIN_DIR)/$(subst clean_,,$@)

# Remaking
re: reclean all
re_%: clean_%
	@$(MAKE) $(subst re_,,$@)

# Force compilation of libft
libft:
	@$(MAKE) -C $(LIBFT_DIR) re --no-print-directory

.PHONY: libft
