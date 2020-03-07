# Main program name
PROGRAM=PointProcessorTest.exe

$(PROGRAM): PointProcessor.exe
	@$(MAKE) -C PointProcessorTests

PointProcessor.exe: 
	@$(MAKE) -C PointProcessor

test: $(PROGRAM)
	./$(PROGRAM)

# Clean up everything except source
clean:
	@$(MAKE) -C PointProcessor clean
	@$(MAKE) -C PointProcessorTests clean
	rmdir build/

# Clean up build objects and dependency files
neat:
	@$(MAKE) -C PointProcessor clean
	@$(MAKE) -C PointProcessorTests clean
	rmdir build/
