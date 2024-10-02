NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
OBJDIR = ./bin
SRCDIR = ./src
SRC = start_dinner.c initialization.c routine.c thread_fork.c mutex.c clean_memory.c input_checker.c time.c death.c helper_function.c
OBJS = $(SRC:%.c=$(OBJDIR)/%.o)

# Compile source files into object files in the OBJDIR
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -Isrc -c $< -o $@

# Main target to build the executable
all: $(NAME)

# Link all object files to create the executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Clean empty directories in the OBJDIR
clean-empty-dirs:
	@if [ -d $(OBJDIR) ]; then find $(OBJDIR) -type d -empty -exec rmdir {} +; fi

# Clean all object files
clean:
	@rm -f $(OBJS)
	@$(MAKE) clean-empty-dirs

# Full clean including the executable
fclean: clean
	@rm -f $(NAME)
	@$(MAKE) clean-empty-dirs

# Rebuild the entire project
re: fclean all

.PHONY: all clean fclean re
# NAME = philo

# CC = cc
# # Add -fsanitize=address for LeakSanitizer and -g for debugging symbols
# CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=address -g
# OBJDIR = ./bin
# SRCDIR = ./src
# SRC = start_dinner.c initialization.c routine.c thread_fork.c mutex.c clean_memory.c input_checker.c time.c death.c helper_function.c
# OBJS = $(SRC:%.c=$(OBJDIR)/%.o)

# # Compile source files into object files in the OBJDIR
# $(OBJDIR)/%.o: $(SRCDIR)/%.c
# 	@mkdir -p $(dir $@)
# 	@$(CC) $(CFLAGS) -Isrc -c $< -o $@

# # Main target to build the executable
# all: $(NAME)

# # Link all object files to create the executable
# $(NAME): $(OBJS)
# 	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# # Clean empty directories in the OBJDIR
# clean-empty-dirs:
# 	@if [ -d $(OBJDIR) ]; then find $(OBJDIR) -type d -empty -exec rmdir {} +; fi

# # Clean all object files
# clean:
# 	@rm -f $(OBJS)
# 	@$(MAKE) clean-empty-dirs

# # Full clean including the executable
# fclean: clean
# 	@rm -f $(NAME)
# 	@$(MAKE) clean-empty-dirs

# # Rebuild the entire project
# re: fclean all

# .PHONY: all clean fclean re
