.PHONY: all clean

all:
	@echo "Building all components..."
	make -C ./com
	make -C ./seq

run: all
	make -C ./seq run

clean:
	@echo "Cleaning all components..."
	make -C ./com clean
	make -C ./seq clean
