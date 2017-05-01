##
## Makefile for  in /home/sousa_v/rendu/cpp_arcade
##
## Made by Victor Sousa
## Login   <sousa_v@epitech.net>
##
## Started on  Mon Mar 13 22:42:09 2017 Victor Sousa
## Last update Mon May  1 00:22:28 2017 Sousa Victor
##

CPP		=	g++

NAME		=	neural_basic
NAME_GEN		=	generator

RM		=	rm -f

CPPFLAGS	+=	-std=c++11
CPPFLAGS	+=	-Werror -Wall -Wextra
CPPFLAGS	+=	-I./includes/

LDFLAGS		+=	-lm

SRCSDIR		=	sources

SRCS		=	$(SRCSDIR)/main.cpp	\
		$(SRCSDIR)/TrainingData.cpp	\
		$(SRCSDIR)/Network.cpp	\
		$(SRCSDIR)/Neuron.cpp
OBJS		=	$(SRCS:.cpp=.o)

GENSRCS		=	$(SRCSDIR)/generator.cpp
GEN_OBJS	=	$(GENSRCS:.cpp=.o)

all:		$(NAME) $(NAME_GEN)

$(NAME):	$(OBJS)
		@$(CPP) $(OBJS) $(LDFLAGS) -o $(NAME) && \
		printf "[\033[1;36mbuilt\033[0m] % 32s\n" $(NAME) | tr ' ' '.' || \
		printf "[\033[1;31mfailed\033[0m] % 31s\n" $(NAME) | tr ' ' '.'

$(NAME_GEN):	$(GEN_OBJS)
		@$(CPP) $(GEN_OBJS) $(LDFLAGS) -o $(NAME_GEN) && \
		printf "[\033[1;36mbuilt\033[0m] % 32s\n" $(NAME_GEN) | tr ' ' '.' || \
		printf "[\033[1;31mfailed\033[0m] % 31s\n" $(NAME_GEN) | tr ' ' '.'

.cpp.o:
		@$(CPP) $(CPPFLAGS) -c $< -o $@ && \
		printf "[\033[1;32mcompiled\033[0m] % 29s\n" $< | tr ' ' '.' || \
		printf "[\033[1;31mfailed\033[0m] % 31s\n" $< | tr ' ' '.'

clean:
		@$(RM) $(OBJS) && \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(OBJ) | tr ' ' '.' || \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(OBJ) | tr ' ' '.'
		@$(RM) $(GEN_OBJS) && \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(OBJ) | tr ' ' '.' || \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(OBJ) | tr ' ' '.'

fclean:		clean
		@$(RM) $(NAME)&& \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(NAME) | tr ' ' '.' || \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(NAME) | tr ' ' '.'
		@$(RM) $(NAME_GEN)&& \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(NAME_GEN) | tr ' ' '.' || \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(NAME_GEN) | tr ' ' '.'

re:		fclean all

.PHONY: re clean fclean all xor
