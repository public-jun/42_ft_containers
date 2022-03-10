#####################################
#	Program name				 	#
#####################################
NAME_STL := stl_container
NAME_FT := ft_container

#####################################
#	Compile option				 	#
#####################################
CXX := clang++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -pedantic -g
# CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -pedantic -g -fsanitize=leak,undefined,address
# CXXFLAGS := -Wall -Wextra -Werror
# CXXFLAGS := -Wall -Wextra -g -std=c++98

#####################################
#	Include header				 	#
#####################################
INCLUDE := -I./includes/containers -I./includes/utils
# INCLUDE :=

#####################################
#	Src							 	#
#####################################
srcsname := main.cpp \
			test_vector.cpp \
			test_algorithm.cpp
srcsdir := ./testfiles
srcs := $(addprefix $(srcsdir)/,$(srcsname))

#####################################
#	Test 						 	#
#####################################
INCLUDE += -I./testfiles

#####################################
#	.o files					 	#
#####################################
OBJDIR_STL := ./obj_stl
OBJS_STL := $(addprefix $(OBJDIR_STL)/,$(srcsname:.cpp=.o))

OBJDIR_FT := ./obj_ft
OBJS_FT := $(addprefix $(OBJDIR_FT)/,$(srcsname:.cpp=.o))

#####################################
#	.d files					 	#
#####################################
DEPSDIR_STL := ./deps_stl
DEPS_STL := $(addprefix $(DEPSDIR_STL)/,$(srcsname:.cpp=.d))
DEPFLAG_STL = -MT $@ -MMD -MP -MF $(DEPSDIR_STL)/$*.d

DEPSDIR_FT := ./deps_ft
DEPS_FT := $(addprefix $(DEPSDIR_FT)/,$(srcsname:.cpp=.d))
DEPFLAG_FT = -MT $@ -MMD -MP -MF $(DEPSDIR_FT)/$*.d

#####################################
#	build files					 	#
#####################################
build := $(OBJDIR_STL) $(DEPSDIR_STL) $(OBJDIR_FT) $(DEPSDIR_FT)

#####################################
#	result files				 	#
#####################################
result := ./result
ft_out := $(result)/ft_out
ft_err := $(result)/ft_err
stl_out := $(result)/stl_out
stl_err := $(result)/stl_err

#####################################
#	Remove option				 	#
#####################################
RM := rm -rf


.PHONY: all
all: $(build) $(NAME_STL) $(NAME_FT)

$(build):
	mkdir -p $(build)

$(NAME_STL): $(OBJS_STL)
	$(CXX) $(CXXFLAGS) -DTEST=1 $(INCLUDE) -o $(NAME_STL) $(OBJS_STL)

$(NAME_FT): $(OBJS_FT)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $(NAME_FT) $(OBJS_FT)

$(OBJDIR_STL)/%.o: $(srcsdir)/%.cpp  | $(DEPSDIR_STL)
	$(CXX) $(CXXFLAGS) $(DEPFLAG_STL) -DTEST=1 -c ./$< $(INCLUDE) -o $@

$(OBJDIR_FT)/%.o: $(srcsdir)/%.cpp  | $(DEPSDIR_FT)
	$(CXX) $(CXXFLAGS) $(DEPFLAG_FT) -c ./$< $(INCLUDE) -o $@



ft: $(result) $(NAME_FT)
	@./$(NAME_FT) > $(ft_out) 2>$(ft_err) ||:
	@cat $(ft_out)
	@cat $(ft_err)

stl: $(result) $(NAME_STL)
	@./$(NAME_STL) > $(stl_out) 2>$(stl_err) ||:
	@cat $(stl_out)
	@cat $(stl_err)

$(result):
	mkdir -p $(result)

.PHONY: clean
clean:
	$(RM) *.dSYM
	$(RM) $(build)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME_STL) $(NAME_FT) $(result) tester $(gtestdir)

.PHONY: re
re: fclean all

test: $(result) $(NAME_FT) $(NAME_STL)
	@./$(NAME_FT) > $(ft_out) 2>$(ft_err)
	@./$(NAME_STL) > $(stl_out) 2>$(stl_err)
	diff $(ft_out) $(stl_out) ||:
	@echo "---ft_err---"
	@cat $(ft_err)
	@echo "---stl_err---"
	@cat $(stl_err)

gtestdir =    ./test
gtest    =    $(gtestdir)/gtest $(gtestdir)/googletest-release-1.11.0
testdir  = ./gtest

$(gtest):
	mkdir -p $(dir ../test)
	curl -OL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.tar.gz
	tar -xvzf release-1.11.0.tar.gz googletest-release-1.11.0
	$(RM) -rf release-1.11.0.tar.gz
	python googletest-release-1.11.0/googletest/scripts/fuse_gtest_files.py $(gtestdir)
	mv googletest-release-1.11.0 $(gtestdir)

test_compile = clang++ -std=c++11 \
	$(testdir)/gtest.cpp $(gtestdir)/googletest-release-1.11.0/googletest/src/gtest_main.cc $(gtestdir)/gtest/gtest-all.cc \
	-I$(gtestdir) -I$(INCLUDE) -lpthread -o tester

.PHONY: gtest
gtest: $(gtest) fclean
	$(test_compile)
	./tester # --gtest_filter=Vector.other

-include $(DEPS_STL) $(DEPS_FT)
