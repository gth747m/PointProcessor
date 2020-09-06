# Main program name
PROGRAM=../Test.exe

# Flags
CXX=gcc
#OPTIMIZE=-O3
OPTIMIZE=-ggdb
STD=-std=c18
GENDEPS=-MMD
WARN=-Wall -Wextra -Wpedantic -Wno-discarded-qualifiers
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
SRCS=Tests.c
SRCS+=Data.c
SRCS+=NamedMutexTest.c
SRCS+=PidTableTest.c
SRCS+=SharedMemoryTest.c

# Other Objects
OTHEROBJS+=Data.o
OTHEROBJS+=NamedMutex.o
OTHEROBJS+=PidTable.o
OTHEROBJS+=SharedMemory.o

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

# Use dependency files (%.d)
-include $(DEPS)

# Clean up everything except source
clean:
	rm -rf $(PROGRAM) $(patsubst %,$(BUILDDIR)%,$(SRCS:.c=.o)) $(DEPS)

# Clean up build objects and dependency files
neat:
	rm -rf $(patsubst %,$(BUILDDIR)%,$(SRCS:.c=.o)) $(DEPS)
