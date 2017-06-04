CC		=	g++
CFLAGS	=	-std=c++14 -W -Wall -Wextra -Werror

NAME	=	Chess

SRC		=	main.cpp	\
			Board.cpp	\
			Bishop.cpp	\
			King.cpp	\
			Knight.cpp	\
			Pawn.cpp	\
			Queen.cpp	\
			Rook.cpp	\
			Piece.cpp	\
			Coord.cpp	\
			Neuron.cpp	\
			ChessAI.cpp	\
			Population.cpp

OBJ		=	$(SRC:%.cpp=%.o)

RM		=	rm -f


$(NAME):
			$(CC) $(CFLAGS) $(SRC) -o $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

