
# To use this makefile, do the following:
# 1. Update $(SRCS) to reflect the list of files you want to compile
# 2. Set $(OBJDIR) to the directory in which you want the intermediate files to be placed (and 
#    make sure the directory exists)
# 3. Change $(EXEC) to be the name you want for your executable

SRCS = graph.cpp graph_utils.cpp graph_order.cpp
CFLAGS = 
LDFLAGS = 
EXEC = graph

# You can leave this stuff alone for the most part; it sets the right C++ standard, tells the
# compiler to print output nicely, and prints some useful warning messages

CC = g++ 
STD = -std=c++0x
FORMAT = -fno-pretty-templates
WARNINGS = -Wempty-body -Wall -Wno-sign-compare
DEBUGFLAGS = -gstabs -pg
OPTFLAGS = -O2
OBJDIR = obj
OBJS = $(addprefix $(OBJDIR)/,$(SRCS:.cpp=.o))
DOBJS = $(addprefix $(OBJDIR)/,$(SRCS:.cpp=.debug))
EXECD = $(EXEC)_d

.DEFAULT_GOAL := $(EXEC)
.PHONY: all clean debug test

$(OBJDIR)/%.o : %.cpp $(OBJDIR)/%.d
	@echo; echo "Compiling $@"; echo "---"
	@$(CC) $(STD) $(WARNINGS) $(FORMAT) -o $@ $(CFLAGS) $(OPTFLAGS) -c $<

$(OBJDIR)/%.debug : %.cpp $(OBJDIR)/%.d
	@echo; echo "Compiling debug version: $@"; echo "---"
	@$(CC) $(STD) $(WARNINGS) $(FORMAT) -o $@ $(CFLAGS) $(DEBUGFLAGS) -c $<

# Use the -MM option for g++ or gcc to automatically determine dependency structure for $(SRCS).
# This will get stuck into a $(OBJDIR)/<sourcename>.d file, which the object files depend on.  Then,
# whenever any file in the dependency structure changes, we'll rebuild and remake.  Slick!
$(OBJDIR)/%.d : %.cpp 
	@$(SHELL) -ec "$(CC) $(STD) -MM $(CFLAGS) $< | \
		sed 's/\($*\)\.o[ :]*/$(OBJDIR)\/\1.o $(OBJDIR)\/\1.debug : /g' > $@; [ -s $@ ] || rm -f $@"

all: $(EXEC) $(EXECD)

debug: $(EXECD)

$(EXEC): $(OBJS)
	@echo; echo "Making lib$(EXEC).a"
	@ar rcs lib$(EXEC).a $(OBJDIR)/*.o
	@echo "Done."

$(EXECD): $(DOBJS)
	@echo; echo "Making lib$(EXECD).a"
	@ar rcs lib$(EXECD).a $(OBJDIR)/*.debug
	@echo "Done."

clean:
	-rm lib$(EXEC).a lib$(EXECD).a $(OBJDIR)/*.d $(OBJDIR)/*.debug $(OBJDIR)/*.o gmon.out graph_test;

TESTSRC = graph_test.cpp
test: $(EXECD)
	$(CC) $(STD) $(FORMAT) -o graph_test -gstabs -pg $(TESTSRC) -L. -lgraph_d

include $(addprefix $(OBJDIR)/,$(SRCS:.cpp=.d))
