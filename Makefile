NAME := containers
CXX := clang++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -pedantic -MMD -MP

INCLUDE := -I./includes

srcs := main.cpp

objs := $(srcs:.cpp=.o)
depends := $(srcs:.cpp=.d)

RM := rm -rf

.PHONY: all
all: $(NAME)

$(NAME): $(objs)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $(NAME) $(objs)

# .cpp.o:
# 	$(CXX) $(CXXFLAGS) $(INCLUDE) -c  -o $@  $<

-include $(depends)
.PHONY: clean
clean:
	$(RM) *.dSYM
	$(RM) $(objs) $(depends)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all
