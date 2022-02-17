#####################################
#	Program name				 	#
#####################################
NAME := container

#####################################
#	Compile option				 	#
#####################################
CXX := clang++
#CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -pedantic
CXXFLAGS := -Wall -Wextra -Werror

#####################################
#	Include header				 	#
#####################################
INCLUDE := -I./includes/containers -I./includes/utils
# INCLUDE :=

#####################################
#	Src							 	#
#####################################
srcsname := main.cpp
srcsdir := .
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
#	build files					 	#
#####################################
build := $(objsdir) $(depsdir)

#####################################
#	result files				 	#
#####################################
result := ./result
ft_out := $(result)/ft_out
ft_err := $(result)/ft_err
std_out := $(result)/std_out
std_err := $(result)/std_err

#####################################
#	Remove option				 	#
#####################################
RM := rm -rf

.PHONY: all
all: $(build) $(NAME)

$(build):
	mkdir -p $(build)

$(objs): $(srcs)
	$(CXX) $(CXXFLAGS) -DTEST=1 -c $< -MMD -MP -MF $(depends) $(INCLUDE) -o $@

# '-DTEST=1' call std::
$(NAME): $(objs)
	$(CXX) $(CXXFLAGS) -DTEST=1 $(INCLUDE) -o $(NAME) $(objs)

test: $(result)
	$(CXX) $(CXXFLAGS) -DTEST=0 $(srcs)  $(INCLUDE) -o $(NAME)
	@./$(NAME) > $(ft_out) 2>$(ft_err)
	$(CXX) $(CXXFLAGS) -DTEST=1 $(srcs)  $(INCLUDE) -o $(NAME)
	@./$(NAME) > $(std_out) 2>$(std_err)
	diff out_ft out_std ||:
	@echo "---ft_err---"
	@cat $(ft_err)
	@echo "---std_err---"
	@cat $(std_err)

ft: $(result)
	$(CXX) $(CXXFLAGS) -DTEST=0 $(srcs)  $(INCLUDE) -o $(NAME)
	# @./$(NAME) > $(ft_out) 2>$(ft_err) ||:
	# @cat $(ft_out)
	# @cat $(ft_err)

std: $(result)
	$(CXX) $(CXXFLAGS) -DTEST=1 $(srcs)  $(INCLUDE) -o $(NAME)
	@./$(NAME) > $(std_out) 2>$(std_err) ||:
	@cat $(std_out)
	@cat $(std_err)

$(result):
	mkdir -p $(result)

.PHONY: clean
clean:
	$(RM) *.dSYM
	$(RM) $(build)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME) $(result)

.PHONY: re
re: fclean all

-include $(depends)
