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

# Link Libraries
LNKLIBS=rt
LNKLIBS+=pthread
LNKLIBS+=pointlib

# Directories
DIRS=Points/
DIRS+=Points/Bool/
DIRS+=Points/Float/
DIRS+=Points/Int/
DIRS+=System/
INCDIRS=../
LIBDIRS=../
BUILDDIR=../build/Tests/

# Sources
SRCS=Tests.c
SRCS+=Points/PointIdTest.c
SRCS+=System/NamedMutexTest.c
SRCS+=System/SharedMemoryTest.c

# Link Flags
LFLAGS=$(OPTIMIZE) $(foreach l, $(LNKLIBS), -l$l) $(foreach d, $(LIBDIRS), -L$d) 

# Include Directories
INC=$(foreach d,$(INCDIRS),-I$d)

# Compile Flags
CFLAGS=$(OPTIMIZE) $(WARN) $(GENDEPS) $(STD) $(INC) $(foreach d,$(DEFINES),-D$d)

# Compiled objects
OBJS=$(patsubst %,$(BUILDDIR)%,$(SRCS:.c=.o))

# Dependencies
DEPS=$(patsubst %,$(BUILDDIR)%,$(SRCS:.c=.d))

# Main program
$(PROGRAM): $(OBJS)
	$(CXX) $(LFLAGS) -o $@ $(filter %.o, $^) $(LIB)

# Compile C++ files (Base program)
$(BUILDDIR)%.o: %.c $(BUILDDIR)
	$(CXX) $(CFLAGS) -c -o $@ $<

$(BUILDDIR):
	mkdir -p $(BUILDDIR)
	$(foreach d, $(DIRS), mkdir -p $(BUILDDIR)$d;)

# Use dependency files (%.d)
-include $(DEPS)

# Clean up everything except source
clean:
	rm -rf $(PROGRAM) $(BUILDDIR)

# Clean up build objects and dependency files
neat:
	rm -rf $(patsubst %,$(BUILDDIR)%,$(SRCS:.c=.o)) $(DEPS)
