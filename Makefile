
# Project Name
NAME = ft_irc

# Compiler and Flags
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 #-g -fsanitize=address

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc

# SRC Folder Subdirector

# External Libraries Directories

# Source and Object Files

SRCS := $(wildcard $(SRC_DIR)/*.cpp)



OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Libraries

# Colors for terminal prints
BLACK    = \033[30;1m
RED      = \033[0;31m
GREEN    = \033[32;1m
YELLOW   = \033[33;1m
BLUE     = \033[34;1m
PURPLE   = \033[35;1m
CYAN     = \033[36;1m
WHITE    = \033[37;1m
GRAY     = \033[90;1m
MAGENTA  = \033[0;95m
BOLD     = \033[1m
RESET    = \033[0m

# Rule to build everything
all: $(NAME)

# Rule to compile each source file into an object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling $(BLUE)$< $(YELLOW)to $(CYAN)$@$(RESET)"
	@$(CXX) $(CXXFLAGS) -I $(INC_DIR) -c $< -o $@

# Rule to link the object files and libraries into the final binary
$(NAME): $(OBJS)
	@echo "$(YELLOW)Linking objects to create binary $(GREEN)$(NAME)$(RESET)"
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)Compilation successful!$(RESET)"

clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		printf "$(RED)Cleaning up $(BLUE)object files$(RED) in $(YELLOW)$(NAME)$(RESET)\n"; \
		rm -rf $(OBJ_DIR); \
	fi

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		echo "$(YELLOW)Removing binary $(RED)$(NAME)$(RESET)"; \
		rm -rf $(NAME); \
	fi

re: fclean all

run: all
	@echo "$(YELLOW)Running $(GREEN)$(NAME)$(RESET)"
	@./$(NAME)

test: all
	@echo "$(YELLOW)Running tests...$(RESET)"
	@bash tests/test.sh

leaks: all
	@echo "$(YELLOW)Running leaks...$(RESET)"
	@leaks --atExit -- ./$(NAME)

.PHONY: all clean fclean test run leaks re 