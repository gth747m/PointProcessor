# Main program name
PROGRAM=../libpointlib.so

# Flags
CXX=gcc
#OPTIMIZE=-O3
OPTIMIZE=-ggdb
PIC=-fPIC
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
DIRS=Points/
DIRS+=Points/Bool/
DIRS+=Points/Float/
DIRS+=Points/Int/
DIRS+=System/
INCDIRS=../
BUILDDIR=../build/PointLib/

# Sources
SRCS=Points/PointId.c
SRCS+=Points/Float/FloatPoint.c
SRCS+=Points/Int/IntPoint.c
SRCS+=Points/Bool/BoolPoint.c
SRCS+=Points/Bool/BoolInput.c
SRCS+=Data.c
SRCS+=dllmain.c
SRCS+=System/NamedMutex.c
SRCS+=System/SharedMemory.c

# Include Directories
INC=$(foreach d,$(INCDIRS),-I$d)

# Compile Flags
CFLAGS=$(OPTIMIZE) $(WARN) $(GENDEPS) $(STD) $(INC) $(foreach d,$(DEFINES),-D$d) $(PIC)

# Compiled objects
OBJS=$(patsubst %,$(BUILDDIR)%,$(SRCS:.c=.o))

# Dependencies
DEPS=$(patsubst %,$(BUILDDIR)%,$(SRCS:.c=.d))

# Main program
$(PROGRAM): $(OBJS)
	$(CXX) -shared $(LFLAGS) -o $@ $(filter %.o, $^)

# Compile C++ files
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
	rm -rf $(OBJS) $(DEPS)
