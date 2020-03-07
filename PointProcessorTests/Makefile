# Main program name
PROGRAM=../PointProcessorTest.exe

# Flags
CXX=gcc
OPTIMIZE=-O3
STD=-std=c18
GENDEPS=-MMD
WARN=-Wall -Wextra -Wpedantic
# IF DEBUG
DEFINES=_DEBUG
# Needed for ftruncate() for SharedMemory
DEFINES+=_XOPEN_SOURCE
DEFINES+=_XOPEN_SOURCE_EXTENDED 

# Link Flags
LFLAGS=$(OPTIMIZE) -lrt -lpthread

# Directories
DIRS=../PointProcessor/
BUILDDIR=../build/

# Sources
SRCS=PointProcessorTests.c
SRCS+=NamedMutexTest.c
SRCS+=PidTableTest.c

# Other Objects
OTHEROBJS+=NamedMutex.o
OTHEROBJS+=PidTable.o

# Include Directories
INC=$(foreach d,$(DIRS),-I$d)

# Compile Flags
CFLAGS=$(OPTIMIZE) $(WARN) $(GENDEPS) $(STD) $(INC) $(foreach d,$(DEFINES),-D$d)

# Compiled objects
OBJS=$(patsubst %,$(BUILDDIR)%,$(SRCS:.c=.o))
OBJS+=$(patsubst %,$(BUILDDIR)%,$(OTHEROBJS))

# Dependencies
DEPS=$(patsubst %,$(BUILDDIR)%,$(SRCS:.c=.d))

# Main program
$(PROGRAM): $(OBJS)
	$(CXX) $(LFLAGS) -o $@ $(filter %.o, $^)

# Compile C++ files (Base program)
$(BUILDDIR)%.o: %.c $(BUILDDIR)
	$(CXX) $(CFLAGS) -c -o $@ $<

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(TBUILDDIR):
	mkdir -p $(TBUILDDIR)

# Use dependency files (%.d)
-include $(DEPS)

# Clean up everything except source
clean:
	rm -rf $(PROGRAM) $(patsubst %,$(BUILDDIR)%,$(SRCS:.c=.o)) $(DEPS)

# Clean up build objects and dependency files
neat:
	rm -rf $(patsubst %,$(BUILDDIR)%,$(SRCS:.c=.o)) $(DEPS)
