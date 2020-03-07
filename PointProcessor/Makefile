# Main program name
PROGRAM=../PointProcessor.exe

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
SRCS=PointProcessor.c
SRCS+=NamedMutex.c
SRCS+=PidTable.c

# Include Directories
INC=$(foreach d,$(DIRS),-I$d)

# Compile Flags
CFLAGS=$(OPTIMIZE) $(WARN) $(GENDEPS) $(STD) $(INC) $(foreach d,$(DEFINES),-D$d)

# Compiled objects
OBJS=$(patsubst %,$(BUILDDIR)%,$(SRCS:.c=.o))

# Dependencies
DEPS=$(patsubst %,$(BUILDDIR)%,$(SRCS:.c=.d))

# Main program
$(PROGRAM): $(OBJS)
	$(CXX) $(LFLAGS) -o $@ $(filter %.o, $^)

# Compile C++ files
$(BUILDDIR)%.o: %.c $(BUILDDIR)
	$(CXX) $(CFLAGS) -c -o $@ $<

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Use dependency files (%.d)
-include $(DEPS)

# Clean up everything except source
clean:
	rm -rf $(PROGRAM) $(OBJS) $(DEPS)

# Clean up build objects and dependency files
neat:
	rm -rf $(OBJS) $(DEPS)
