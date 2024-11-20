.PHONY: all clean

all:
	@echo "Building all components..."
	make -C ./com
	make -C ./utils
	make -C ./seq
	make -C ./par

clean:
	@echo "Cleaning all components..."
	make -C ./seq clean
	make -C ./par clean
	make -C ./com clean
	make -C ./utils clean