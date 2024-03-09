
# Project Name
NAME = ircserv

# Compiler and Flags
CXX = c++
CXXFLAGS =  -std=c++98 -Wall -Wextra  -g #-Werror  #-g -fsanitize=address

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc

# Variables
PASSWORD := 1234
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

test: all
	@echo "$(YELLOW)Running tests...$(RESET)"
	@bash tests/test.sh

leaks: all
	@echo "$(YELLOW)Running leaks...$(RESET)"
	@leaks --atExit -- ./$(NAME)

run:	all
	@UNUSED_PORT=1024; \
    while [ $$(netstat -t -a -n -l | awk '{print substr($$4, index($$4, ":")+1)}' | sort -n | grep -c $$UNUSED_PORT) -ne 0 ] && [ $$UNUSED_PORT -le 65534 ] ; do \
        ((UNUSED_PORT++)); \
    done; \
	if [ $$UNUSED_PORT -le 65534 ]; then \
    echo "Unused port found: $$UNUSED_PORT"; \
    ./$(NAME) $$UNUSED_PORT "$(PASSWORD)";	\
	else \
		echo "No available port found."; \
	fi;
	
.PHONY: all clean fclean test run leaks re 