BUILD_DIR := ./build
OBJ_DIR   := $(BUILD_DIR)/objects
APP_DIR   := $(BUILD_DIR)/app
SRC       := $(shell find src -name "*.c")
OBJ       := $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(SRC))

CFLAGS    := -g -MMD -MP

build: $(APP_DIR)/program

$(APP_DIR)/program: $(OBJ)
	@mkdir -p $(APP_DIR)
	cc -o $@ -g $(OBJ)

$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(@D)
	cc $(CFLAGS) -o $@ -c $<

run: build
	./$(APP_DIR)/program ./input/01
	./$(APP_DIR)/program ./input/02
	./$(APP_DIR)/program ./input/03
	./$(APP_DIR)/program ./input/04
	./$(APP_DIR)/program ./input/05

clean:
	rm -r $(BUILD_DIR)

.PHONY: build clean run

-include $(OBJ:.o=.d)