#####################################
#	Program name				 	#
#####################################
NAME_STL := stl_container
NAME_FT := ft_container

#####################################
#	Compile option				 	#
#####################################
CXX := clang++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98

#####################################
#	Include header				 	#
#####################################
INCLUDE := -I./includes/containers -I./includes/utils

#####################################
#	Src							 	#
#####################################
srcsname := main.cpp
srcsdir := ./testfiles
srcs := $(addprefix $(srcsdir)/,$(srcsname))

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

.PHONY: clean
clean:
	$(RM) *.dSYM
	$(RM) $(build)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME_STL) $(NAME_FT) tester *exe

.PHONY: re
re: fclean all

################# google test ####################

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
	-g -fsanitize=address -fsanitize=undefined -fsanitize=leak \
	-I$(gtestdir) $(INCLUDE) -lpthread -o tester

.PHONY: gtest
gtest: $(gtest) fclean
	$(test_compile)
	./tester
# ./tester # --gtest_filter=Vector.other

.PHONY: cleangtest
cleangtest:
	$(RM) $(gtestdir)

#################### my test #######################

mytest_compile = $(CXX) $(CXXFLAGS) \
	gtest/testlib_main.cpp \
	$(INCLUDE) -lpthread

.PHONY: mytest
mytest:
	$(mytest_compile) -o ./mytest_exe
	./mytest_exe

.PHONY: mytest_stl
mytest_stl:
	$(mytest_compile) -DSTL=1 -o ./mytest_stl_exe
	./mytest_stl_exe

################# my bench ####################

.PHONY: mybench
mybench:
	$(CXX) $(CXXFLAGS) -O0 \
	./mybenchmark/bench.cpp \
	$(INCLUDE) \
	-o mybench_exe

-include $(DEPS_STL) $(DEPS_FT)
