# Main program name
PROGRAM=PointProcessor

$(PROGRAM):
	+$(MAKE) -C PointProcessor
	+$(MAKE) -C PointProcessorTests

# Clean up everything except source
clean:
	+$(MAKE) -C PointProcessor clean
	+$(MAKE) -C PointProcessorTests clean

# Clean up build objects and dependency files
neat:
	+$(MAKE) -C PointProcessor clean
	+$(MAKE) -C PointProcessorTests clean
