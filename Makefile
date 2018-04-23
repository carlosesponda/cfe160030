CXX = g++
CXXFLAGS = -Wall -g 
CPPFLAGS = -I/scratch/perkins/include
LDFLAGS = -L/scratch/perkins/lib
LDLIBS = -lcdk -lcurses 
#
PROJECTNAME = Program6
EXEC = program6
SRCS= cdkexample.cc 
OBJS = $(SRCS:cc=o)
CURDIRNAME:= $(shell basename 'pwd')
MKBKUPNAME := ~/Unix/backups/$(PROJECTNAME).tar.gz

all: $(EXEC)
clean:
	rm -f $(OBJS) *.P *~ \#*

tarball:
	make clean  
	tar zcfv $(PROJECTNAME).tar.gz ../$(CURDIRNAME)
Makefile: $(SRCS:.cc=.d)

# Pattern for .d files.
%.d:%.cc
	@echo Updating .d Dependency File
	@set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

#  This is a rule to link the files.  Pretty standard
$(EXEC): $(OBJS) 
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)
-include $(SRCS:.cc=.d)

# Backup Target
backup:	clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME).tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!
