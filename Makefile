BUILD_DIR := ./build
OBJ_DIR   := $(BUILD_DIR)/objects
APP_DIR   := $(BUILD_DIR)/app
ASM_DIR   := $(BUILD_DIR)/asm
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

	@mkdir -p $(ASM_DIR)

	./$(APP_DIR)/program ./input/01
	as -o $(ASM_DIR)/out.o $(ASM_DIR)/out.s
	gcc -o $(ASM_DIR)/out $(ASM_DIR)/out.o
	./$(ASM_DIR)/out

clean:
	rm -r $(BUILD_DIR)

.PHONY: build clean run

-include $(OBJ:.o=.d)