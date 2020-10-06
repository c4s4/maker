# Parent build files at https://github.com/c4s4/make

include ~/.make/help.mk
include ~/.make/color.mk
include ~/.make/clean.mk

SRC_DIR = src

bin: clean # Generate binary
	$(title)
	mkdir -p $(BUILD_DIR)
	cc -c -o $(BUILD_DIR)/parser.o $(SRC_DIR)/parser.c
	cc -c -o $(BUILD_DIR)/targets.o $(SRC_DIR)/targets.c
	cc -o $(BUILD_DIR)/make-targets $(BUILD_DIR)/*.o

run: bin # Run programme
	$(title)
	$(BUILD_DIR)/make-targets
