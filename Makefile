NAME := containers
CXX := clang++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -pedantic

INCLUDE := -I./includes

srcsname := main.cpp
srcsdir := ./
srcs := $(addprefix $(srcsdir)/,$(srcsname))


objsdir := ./obj
objs := $(addprefix $(objsdir)/,$(srcsname:.cpp=.o))

depsdir := ./deps
depends := $(addprefix $(depsdir)/,$(srcsname:.cpp=.d))

build := $(objsdir) $(depsdir)

RM := rm -rf

.PHONY: all
all: $(build) $(NAME)

$(NAME): $(objs)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $(NAME) $(objs)

$(objs): $(srcs)
	$(CXX) $(CXXFLAGS) -c $< -MMD -MP -MF $(depends) $(INCLUDE) -o $@

$(build):
	mkdir -p $(build)

.PHONY: clean
clean:
	$(RM) *.dSYM
	$(RM) $(build)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all

-include $(depends)
