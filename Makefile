SERVER = server
CLIENT = client

CC = cc
CFLAGS = -Wall -Werror -Wextra

SRCS_SERVER = server.c
SRCS_CLIENT = client.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

LIBFT = libft/libft.a

all: $(SERVER) $(CLIENT)

$(SERVER) $(CLIENT): $(OBJS_SERVER) $(OBJS_CLIENT) $(LIBFT)
	${CC} ${CFLAGS} ${OBJS_CLIENT} libft/libft.a -o ${CLIENT}
	${CC} ${CFLAGS} ${OBJS_SERVER} libft/libft.a -o ${SERVER}

$(LIBFT):
	${MAKE} -C ./libft

clean:	
	$(MAKE) clean -C ./libft
	rm -rf ${OBJS_SERVER} ${OBJS_CLIENT} ${OBJS_SERVER_BONUS} ${OBJS_CLIENT_BONUS}

fclean:	clean
	$(MAKE) fclean -C ./libft
	rm -rf $(SERVER) $(CLIENT)

re:	fclean all