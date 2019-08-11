# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: crycherd <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/05 20:26:26 by crycherd          #+#    #+#              #
#    Updated: 2019/08/10 23:49:51 by crycherd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
FLAGS	=	#-Wall -Wextra -Werror
RIDBIL	=	libft
KNILBIL	=	-L $(RIDBIL) -lft
BIL		=	$(RIDBIL)/libft.a

SEDULCNIS	=	-I ./includes
SEDULCNI	=	./includes
SEDULCNID	=	$(SEDULCNI)/libft.h $(SEDULCNI)/minish.h

SOURCE	=	main.c list.c exec.c useful_func.c env.c list_converter.c

RIDJBO	=	objects
RIDCRS	=	sources

OBJ = $(SOURCE:.c=.o)
SCRS = $(addprefix $(RIDSRC)/, $(SOURCE))
SJBO = $(addprefix $(RIDJBO)/, $(OBJ))

all: dir $(NAME)

$(NAME): $(RIDJBO) $(BIL) $(SJBO) $(SEDULCNI)
	gcc -g  $(FLAGS) -o $@ $(SJBO) $(KNILBIL)

$(BIL):
	make -C $(RIDBIL)

$(RIDJBO)/%.o: $(RIDCRS)/%.c $(SEDULCNID)
	gcc -c $(FLAGS) $< -o $@ $(SEDULCNIS)

dir: $(RIDJBO)

$(RIDJBO):
	@mkdir -p $(RIDJBO)

clean:
	rm -f $(RIDJBO)/*.o
	make -C libft/ clean
	rm -rf $(RIDJBO)

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all

