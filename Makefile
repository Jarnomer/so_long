# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/10 08:33:46 by jmertane          #+#    #+#              #
#    Updated: 2024/02/19 17:37:11 by jmertane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#    VARIABLES
# **************************************************************************** #

NAME := so_long

SOURCEDIR := sources
HEADERDIR := include
BUILDDIR  := build
BUILDLOG  := build.log

BONUSDIR  := ./bonus
BONUSFLAG := .bonus

LIBFTDIR  := ./libft
LIBFTBIN  := libft.a

MLXDIR    := ./mlx
MLXBIN    := libmlx42.a

TESTCASE  := ./$(NAME) maps/valid1.ber

# **************************************************************************** #
#    COMMANDS
# **************************************************************************** #

RM          := rm -rf
SCREENCLEAR := printf "\033c"

# **************************************************************************** #
#    COMPILATION
# **************************************************************************** #

CC         := cc
CFLAGS     := -Wall -Werror -Wextra
CPPFLAGS   := -c -MMD -MP
DEBUGFLAGS := -g -fsanitize=address
MAKEFLAGS  += --no-print-directory -j4
MLXFLAGS   = -ldl -lglfw -pthread -lm

# **************************************************************************** #
#    VALGRIND
# **************************************************************************** #

LEAKSLOG := leaks.log
VLGFLAGS := --leak-check=full \
            --show-leak-kinds=all \
            --track-origins=yes \
            --track-fds=yes \
            --trace-children=yes \
            --log-file=$(LEAKSLOG) \
            --verbose \
            --quiet

# **************************************************************************** #
#    SOURCES
# **************************************************************************** #

SOURCES := main \
           init \
           open \
           read \
           test \
           load \
           draw \
           play \
           free \
           error

SOURCES_BONUS := $(SOURCES) \
                 anim \
                 enemy \
                 ai

SOURCES := $(addsuffix .c, $(SOURCES))

SOURCES_BONUS := $(addsuffix _bonus.c, $(SOURCES_BONUS))

OBJECTS := $(addprefix $(BUILDDIR)/, $(SOURCES:.c=.o))

OBJECTS_BONUS = $(addprefix $(BUILDDIR)/, $(SOURCES_BONUS:.c=.o))

SOURCEDIR += $(addprefix $(BONUSDIR)/, $(SOURCEDIR))

INCS := $(addprefix -I, $(HEADERDIR) $(BONUSDIR)/$(HEADERDIR))
INCS += $(addprefix -I, $(LIBFTDIR)/$(HEADERDIR))
INCS += $(addprefix -I, $(MLXDIR)/$(HEADERDIR)/MLX42)

DEPS := $(OBJECTS:.o=.d) $(OBJECTS_BONUS:.o=.d)

vpath %.c $(SOURCEDIR)

# **************************************************************************** #
#    RULES
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $^ $(LIBFTDIR)/$(LIBFTBIN) \
	$(MLXFLAGS) $(MLXDIR)/$(BUILDDIR)/$(MLXBIN) -o $(NAME)
	printf "$(V)$(B)Binary:$(T)$(Y) $(NAME) $(T)\n"

bonus: $(BONUSFLAG)

$(BONUSFLAG): $(OBJECTS_BONUS)
	$(CC) $(CFLAGS) $^ $(LIBFTDIR)/$(LIBFTBIN) \
	$(MLXFLAGS) $(MLXDIR)/$(BUILDDIR)/$(MLXBIN) -o $(NAME)
	printf "$(V)$(B)Binary:$(T)$(Y) $(BONUSBIN) $(T)\n"
	@touch $(BONUSFLAG)

$(OBJECTS) $(OBJECTS_BONUS): $(LIBFTDIR)/$(LIBFTBIN)

# $(OBJECTS) $(OBJECTS_BONUS): $(MLXDIR)/$(BUILDDIR)/$(MLXBIN)

libft: $(LIBFTDIR)/$(LIBFTBIN)

$(LIBFTDIR)/$(LIBFTBIN): 
	@make -C $(LIBFTDIR) all

run: all
	$(SCREENCLEAR)
	$(TESTCASE)

re: fclean
	make all

reb: fclean
	make bonus

debug: CFLAGS += $(DEBUGFLAGS)
debug: re

mlx: $(MLXDIR)/$(BUILDDIR)/$(MLXBIN)

$(MLXDIR)/$(BUILDDIR)/$(MLXBIN):
ifeq ("$(wildcard $(MLXDIR))", "")
	@echo "$(G)$(B)$(MLXDIR)$(T)$(V) not found, commencing download.$(T)\n"
	@git clone https://github.com/codam-coding-college/MLX42.git $(MLXDIR)
else
	@echo "\n$(V)Skipping download, $(G)$(B)$(MLXDIR)$(T)$(V) exists.$(T)\n"
endif
	@cmake $(MLXDIR) -B $(MLXDIR)/$(BUILDDIR) && make -C $(MLXDIR)/$(BUILDDIR) -j4


# **************************************************************************** #
#    BUILD
# **************************************************************************** #

define build_cmd
$1/%.o: %.c | $(BUILDDIR)
	if ! $(CC) $(CFLAGS) $(CPPFLAGS) $(INCS) $$< -o $$@ 2> $(BUILDLOG); then \
		printf "$(R)$(B)\nError: \
		$(V)Unable to create object file: \
		$(R)$(B)$$@$(Y)\n\n"; \
		sed '$$d' $(BUILDLOG); exit 1 ; \
	else \
		printf "$(C)$(B)Object: $(G)$$@ $(T)\n"; \
	fi
endef

# **************************************************************************** #
#    CLEAN
# **************************************************************************** #

clean:
	@make -C $(LIBFTDIR) fclean
	$(call delete_cmd, $(BUILDDIR), $(BUILDLOG), $(LEAKSLOG))
	@$(RM) $(BONUSFLAG)

fclean: clean
	$(call delete_cmd, $(NAME) $(BONUSBIN))

define delete_cmd
	printf "$(R)$(B)Delete:$(T)$(Y)$1$2$3$4$5$(T)\n"
	$(RM) $1 $2 $3 $4 $5
endef

# **************************************************************************** #
#    COLORS
# **************************************************************************** #

T = \033[0m
B = \033[1m
G = \033[32m
V = \033[35m
C = \033[36m
Y = \033[33m
R = \033[31m

# **************************************************************************** #
#    UTILS
# **************************************************************************** #

-include $(DEPS)

$(BUILDDIR):
	mkdir -p $@

$(foreach build, $(BUILDDIR), $(eval $(call build_cmd, $(build))))

# **************************************************************************** #
#    PHONY
# **************************************************************************** #

.PHONY: all libft bonus re reb
.PHONY: debug leaks run nm mlx
.PHONY: clean fclean

.SILENT:
