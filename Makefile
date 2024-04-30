NAME = MARVELS

CC = g++
CFLAG = 

RM = rm
RMFLAG = 

INCLUDES = ./include/rapidjson

SRCS_DIR = ./srcs
SRCS = 	$(SRCS_DIR)/new_main.cpp \
		# $(SRCS_DIR)/controller.cpp \
		# $(SRCS_DIR)/learning_module.cpp \
		# $(SRCS_DIR)/neuron.cpp

OBJS = $(SRCS:.cpp=.o)

all : $(NAME)

%.o : %.cpp
	$(CC) $(CFLAG) -I$(INCLUDES) -o $@ -c $<

$(NAME) : $(OBJS)
	$(CC) $(CFLAG) -o $@ $^

clean :
	$(RM) $(RMFLAG) $(OBJS)

fclean : clean
	$(RM) $(RMFLAG) $(NAME)

re : fclean all

.PHONY : all clean fclean re