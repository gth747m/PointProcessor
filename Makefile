# Main program name
PROGRAM=PointProcessor.exe

# Flags
#CXX=gcc
CXX=clang
DEBUG=-ggdb
OPTIMIZE=-O3
STD=-std=c18
GENDEPS=-MMD
WARN=-Wall -Wextra -Wpedantic
DEFINES=_DEBUG

# Link Flags
LFLAGS=$(OPTIMIZE) -lrt -lpthread

# Directories
DIRS=PointProcessor/
BDIR=build/

# Sources
SRCS=PointProcessor.c
SRCS+=NamedMutex.c
SRCS+=PidTable.c
SRCS+=SharedMemory.c

# Resources
RCS=pids.txt

# Include Directories
INC=$(foreach d,$(DIRS),-I$d)

# Compile Flags
#CFLAGS=$(WARN) $(GENDEPS) $(STD) $(DEBUG) $(INC)
CFLAGS=$(OPTIMIZE) $(WARN) $(GENDEPS) $(STD) $(INC) $(foreach d,$(DEFINES),-D$d)

# Compiled objects
#TMPOBJS=$(SRCS:.c=.o)
OBJS=$(patsubst %,$(BDIR)%,$(SRCS:.c=.o))

# Dependencies
#TMPDEPS=$(SRCS:.c=.d)
DEPS=$(patsubst %,$(BDIR)%,$(SRCS:.c=.d))

# Main program
$(PROGRAM): $(OBJS) $(RESOURCES)
	cp -p $(DIRS)$(RCS) $(RCS)
	$(CXX) $(LFLAGS) -o $@ $(filter %.o, $^)

# Compile C++ files
build/%.o: PointProcessor/%.c $(BDIR)
	$(CXX) $(CFLAGS) -c -o $@ $<

$(BDIR):
	mkdir -p $(BDIR)

# Use dependency files (%.d)
-include $(DEPS)

# Clean up everything except source
clean:
	rm -rf $(PROGRAM) $(BDIR) $(RCS)

# Clean up build objects and dependency files
neat:
	rm -rf $(BDIR) $(RCS)

