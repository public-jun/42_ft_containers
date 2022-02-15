#####################################
#	Program name				 	#
#####################################
NAME := containers

#####################################
#	Compile option				 	#
#####################################
CXX := clang++
#CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -pedantic
CXXFLAGS := -Wall -Wextra -Werror -pedantic

#####################################
#	Include header				 	#
#####################################
INCLUDE := -I./includes/containers -I./includes/utils
# INCLUDE :=

#####################################
#	Src							 	#
#####################################
srcsname := main.cpp
srcsdir := ./
srcs := $(addprefix $(srcsdir)/,$(srcsname))

#####################################
#	Test 						 	#
#####################################
testdir := ./testfiles
INCLUDE += -I./testfiles

#####################################
#	.o files					 	#
#####################################
objsdir := ./obj
objs := $(addprefix $(objsdir)/,$(srcsname:.cpp=.o))

#####################################
#	.d files					 	#
#####################################
depsdir := ./deps
depends := $(addprefix $(depsdir)/,$(srcsname:.cpp=.d))

#####################################
#	Output files				 	#
#####################################
build := $(objsdir) $(depsdir)

#####################################
#	Remove option				 	#
#####################################
RM := rm -rf

.PHONY: all
all: $(build) $(NAME)

# '-DTEST=1' call std::
$(NAME): $(objs)
	$(CXX) $(CXXFLAGS) -DTEST=1 $(INCLUDE) -o $(NAME) $(objs)

$(objs): $(srcs)
	$(CXX) $(CXXFLAGS) -DTEST=1 -c $< -MMD -MP -MF $(depends) $(INCLUDE) -o $@

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
