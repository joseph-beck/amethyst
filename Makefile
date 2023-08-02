BUILD_DIR 	:= ./build
OBJ_DIR 	:= $(BUILD_DIR)/objects
APP_DIR 	:= $(BUILD_DIR)/app
SRC			:= $(shell find src -name "*.c")

build: $(SRC)
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)
	cc -o $(APP_DIR)/program -g $(SRC)

run:
	./$(APP_DIR)/program ./input/01
	./$(APP_DIR)/program ./input/02
	./$(APP_DIR)/program ./input/03
	./$(APP_DIR)/program ./input/04
	./$(APP_DIR)/program ./input/05

clean:
	rm -r build/app

.PHONY: build clean run