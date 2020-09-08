# Main program name
PROGRAM=Test.exe

$(PROGRAM): PointLib.dll
	@$(MAKE) -C Tests

PointLib.dll: 
	@$(MAKE) -C PointLib

test: $(PROGRAM)
	./$(PROGRAM)

# Clean up everything except source
clean:
	@$(MAKE) -C PointLib clean
	@$(MAKE) -C Tests clean
	rmdir build/

# Clean up build objects and dependency files
neat:
	@$(MAKE) -C PointLib clean
	@$(MAKE) -C Tests clean
	rmdir build/
