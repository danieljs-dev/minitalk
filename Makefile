BLACK       = \033[0;30m
RED         = \033[0;31m
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
BLUE        = \033[0;34m
MAGENTA     = \033[0;35m
CYAN        = \033[0;36m
WHITE       = \033[0;37m

define HEADER
███╗░░░███╗██╗███╗░░██╗██╗████████╗░█████╗░██╗░░░░░██╗░░██╗
████╗░████║██║████╗░██║██║╚══██╔══╝██╔══██╗██║░░░░░██║░██╔╝
██╔████╔██║██║██╔██╗██║██║░░░██║░░░███████║██║░░░░░█████═╝░
██║╚██╔╝██║██║██║╚████║██║░░░██║░░░██╔══██║██║░░░░░██╔═██╗░
██║░╚═╝░██║██║██║░╚███║██║░░░██║░░░██║░░██║███████╗██║░╚██╗
╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝░░░╚═╝░░░╚═╝░░╚═╝╚══════╝╚═╝░░╚═╝

$(GREEN)(dajesus- "https://github.com/danieljs-dev")$(RESET)

endef
export HEADER

SERVER = server
CLIENT = client

CC = cc
CFLAGS = -Wall -Werror -Wextra

SRCS_SERVER = server.c
SRCS_CLIENT = client.c

INCLUDES = -I libft/ -I .

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

LIBFT = libft/libft.a

all: $(LIBFT) $(SERVER) $(CLIENT) print_banner

$(SERVER): $(OBJS_SERVER) $(LIBFT)
	@${CC} ${CFLAGS} ${OBJS_SERVER} libft/libft.a -o ${SERVER}
	@clear
	@echo "\r\033[K$(CYAN)Server $(RED)is ready!$(RESET)"

$(CLIENT): $(OBJS_CLIENT) $(LIBFT)
	@${CC} ${CFLAGS} ${OBJS_CLIENT} libft/libft.a -o ${CLIENT}
	@clear
	@echo "\r\033[K$(CYAN)Client $(RED)is ready!$(RESET)"

%.o: %.C
	@$(CC) $(CFLAGS)  $(INCLUDES) -c $< -o $@

$(LIBFT):
	@${MAKE} -C ./libft --no-print-directory

print_banner:
	@clear
	@echo "$(YELLOW)$$HEADER$(RESET)"

clean:	
	@$(MAKE) clean -C ./libft --no-print-directory
	@rm -rf ${OBJS_SERVER} ${OBJS_CLIENT} ${OBJS_SERVER_BONUS} ${OBJS_CLIENT_BONUS}

fclean:	clean
	@$(MAKE) fclean -C ./libft --no-print-directory
	@rm -rf $(SERVER) $(CLIENT)

re:	fclean all


 .PHONY: all clean fclean re print_banner
