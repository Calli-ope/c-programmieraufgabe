.PHONY: all clean

all:
	@echo "Building all components..."
	make -C ./com
	make -C ./par

run: all
	make -C ./par run

clean:
	@echo "Cleaning all components..."
	make -C ./com clean
	make -C ./par clean
