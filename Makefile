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

NAME		:=	so_long
BONUSBIN	:=	so_long
DEBUGBIN	:=	so_long
OBJSDIR		:=	build/
DEPSDIR		:=	.deps/
BONUSDIR	:=	bonus/
LIBFTDIR	:=	libft/
LIBFT		:=	libft/libft.a
ERRORTXT	:=	error.txt
BONUSEXT	:=	_bonus
BONUSFLG	:=	.bonus
DEBUGFLG	:=	.debug

MLXDIR		:=	mlx/
LIBMLX		:=	mlx/build/libmlx42.a

RM			:=	rm -rf
AR			:=	ar -rcs
CC			:=	cc
CFLAGS		:=	-Wall -Werror -Wextra
DEBUGFLAGS	=	-g -fsanitize=address
DEPFLAGS	=	-c -MT $@ -MMD -MP -MF $(DEPSDIR)$*.d
MLXFLAGS	=	-ldl -lglfw -pthread -lm
SCREENCLR	:=	printf "\033c"
SLEEP		:=	sleep .20

FILES		:=	main \
				init \
				open \
				read \
				test \
				load \
				draw \
				play \
				free \
				error

BONUS		:=	anim \
				enemy \
				ai

HEADERS		:=	so_long \
				textures \
				styles \
				error \

SRCS		:=	$(addsuffix .c, $(FILES))
SRCS		+=	$(addsuffix .h, $(HEADERS))
SRCS_BNS	:=	$(addsuffix $(BONUSEXT).c, $(FILES) $(BONUS))
SRCS_BNS	+=	$(addsuffix $(BONUSEXT).h, $(HEADERS))
SRCS_BNS	:=	$(addprefix $(BONUSDIR), $(SRCS_BNS))
SRCS_DEBUG	:=	$(SRCS)

OBJS		=	$(patsubst %.c, $(OBJSDIR)%.o, $(SRCS))
OBJS_BNS	=	$(patsubst %.c, $(OBJSDIR)%.o, $(SRCS_BNS))
OBJS_DEBUG	=	$(patsubst %.c, $(OBJSDIR)%.o, $(SRCS_DEBUG))
DEPS		=	$(patsubst %.c, $(DEPSDIR)%.d, $(SRCS) $(SRCS_BNS))

F			=	=================================================
B			=	\033[1m		# bold
T			=	\033[0m		# reset
G			=	\033[32m	# green
V			=	\033[35m	# violet
C			=	\033[36m	# cyan
R			=	\033[31m	# red
Y			=	\033[33m	# yellow

all: $(NAME)

$(NAME): $(LIBMLX) $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $^ $(LIBFT) $(MLXFLAGS) $(LIBMLX) -o $@
	@echo "$(G)$(B)\n$(F)$(C)\nFINISHED!$(T)\n" && $(SLEEP)
	@echo "$(V)Compiled $(G)$(CNTR)$(V) object file(s).$(T)\n"
	@echo "$(V)Using compiler $(G)$(CC)$(V) with flags: $(G)$(CFLAGS)$(T)\n"
	@echo "$(V)Using minilibx flags: $(G)$(MLXFLAGS)$(T)\n"
	@echo "$(V)Successfully compiled binary: $(G)$(B)$2$(T)\n"

bonus: $(BONUSFLG)

$(BONUSFLG): $(LIBMLX) $(OBJS_BNS) $(LIBFT)
	@$(CC) $(CFLAGS) $^ $(LIBFT) $(MLXFLAGS) $(LIBMLX) -o $(BONUSBIN)
	@echo "$(G)$(B)\n$(F)$(C)\nFINISHED!$(T)\n" && $(SLEEP) && touch $@
	@echo "$(V)Compiled $(G)$(CNTR)$(V) object file(s).$(T)\n"
	@echo "$(V)Using compiler $(G)$(CC)$(V) with flags: $(G)$(CFLAGS)$(T)\n"
	@echo "$(V)Using minilibx flags: $(G)$(MLXFLAGS)$(T)\n"
	@echo "$(V)Successfully compiled binary: $(G)$(B)$(BONUSBIN)$(T)\n"

debug: $(DEBUGFLG)

$(DEBUGFLG): $(LIBMLX) $(OBJS_DEBUG) $(LIBFT)
	@$(CC) $(CFLAGS) $(DEBUGFLAGS) $^ $(LIBFT) $(MLXFLAGS) $(LIBMLX) -o $(DEBUGBIN)
	@echo "$(G)$(B)\n$(F)$(C)\nFINISHED!$(T)\n" && $(SLEEP) && touch $@
	@echo "$(V)Compiled $(G)$(CNTR)$(V) object file(s).$(T)\n"
	@echo "$(V)Using compiler $(G)$(CC)$(V) with flags: $(G)$(CFLAGS) $(DEBUGFLAGS)$(T)\n"
	@echo "$(V)Using minilibx flags: $(G)$(MLXFLAGS)$(T)\n"
	@echo "$(V)Successfully compiled binary: $(G)$(B)$2$(T)\n"

$(OBJSDIR)%.o: %.c | $(OBJSDIR) $(DEPSDIR)
	@if ! $(CC) $(CFLAGS) $(DEPFLAGS) $< -o $@ 2> $(ERRORTXT); then \
		echo "$(R)$(B)\nMAKEFILE TERMINATED!\n$(F)$(T)\n"; \
		echo "$(V)Unable to create object file: $(R)$(B)$@$(T)\n"; \
		echo "$(R)$(B)ERROR\t>>>>>>>>$(T)$(Y)\n"; sed '$$d' $(ERRORTXT); \
		echo "$(R)$(B)\n$(F)\nExiting...$(T)\n"; exit 1 ; fi
	@if [ $(CNTR) ]; then \
		$(eval CNTR=$(shell echo $$(($(CNTR)+1)))) \
		echo "$(T)$(V) $<$(T)\t$(C)>>>>>>>>\t$(G)$(B)$@$(T)"; else \
		echo "$(C)$(B)MAKE START!$(T)\n$(G)$(B)$(F)$(T)\n"; \
		echo "$(T)$(V) $<$(T)\t$(C)>>>>>>>>\t$(G)$(B)$@$(T)"; fi

$(LIBMLX):
ifeq ("$(wildcard $(MLXDIR))", "")
	@echo "$(G)$(B)$(MLXDIR)$(T)$(V) not found, commencing download.$(T)\n"
	@git clone https://github.com/codam-coding-college/MLX42.git $(MLXDIR)
else
	@echo "\n$(V)Skipping download, $(G)$(B)$(MLXDIR)$(T)$(V) exists.$(T)\n"
endif
	@echo "\n$(V)Building $(G)$(B)MLX42$(T)$(V) binary...$(T)\n"
	@cmake $(MLXDIR) -B $(MLXDIR)/build && make -C $(MLXDIR)/build -j4

$(LIBFT): force
	@make --quiet -C $(LIBFTDIR) all

force:
	@true

clean:
	@$(SCREENCLR) && echo "$(C)$(B)\nCLEAN START!\n$(G)$(F)$(T)\n"
	@echo "$(V)Removing object and dependency file(s) for $(G)$(B)$(LIBFTDIR)$(T)\n"
	@echo "$(V)Removing object and dependency file(s) for $(G)$(B)$(MLXDIR)$(T)\n"
	@echo "$(V)Removing object and dependency file(s) for $(G)$(B)$(NAME)$(T)\n"
	@$(RM) $(OBJSDIR) $(DEPSDIR) $(ERRORTXT) $(BONUSFLG) $(DEBUGFLG)
	@make --quiet -C $(LIBFTDIR) clean
	@echo "$(G)$(B)$(F)$(C)\nFINISHED!$(T)\n" && $(SLEEP)

fclean: clean
	@echo "$(C)$(B)\nFCLEAN START!\n$(G)$(F)$(T)\n"
	@echo "$(V)Removing all binary file(s) for $(G)$(B)$(LIBFTDIR)$(T)\n"
	@echo "$(V)Removing all binary file(s) for $(G)$(B)$(MLXDIR)$(T)\n"
	@echo "$(V)Removing all binary file(s) for $(G)$(B)$(NAME)$(T)"
	@$(RM) $(NAME) $(BONUSBIN) $(DEBUGBIN)
	@make --quiet -C $(LIBFTDIR) fclean && $(RM) $(MLXDIR)/build
	@echo "$(G)$(B)\n$(F)$(C)\nFINISHED!$(T)" && $(SLEEP)

re: fclean all

reb: fclean bonus

nm:
	@norminette $(SRCS) $(SRCS_BNS)

$(OBJSDIR) $(DEPSDIR):
	@mkdir -p $@/$(BONUSDIR)

$(DEPS):
	include $(wildcard $(DEPS))

.PHONY: all libft force bonus debug clean fclean re reb
