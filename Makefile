TARGET = motora_challenge

CC = gcc
CFLAGS = -Wall -Wextra -g -I$(INC_DIR)


SRC_DIR = src
INC_DIR = include
BUILD_DIR = build
TEST_DIR = testes
TEST_OUTPUT_DIR = test_output

SRCS = $(wildcard $(SRC_DIR)/*.c)

OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))


all: dir $(TARGET)

dir:
	@mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJS)
	@echo "Linkando o executável..."
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Build concluído! Rode com: ./$(TARGET) ou make run"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compilando $<..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Limpando arquivos de build..."
	rm -rf $(BUILD_DIR) $(TARGET)

run: all
	@if [ -z "$(FILE)" ] || [ -z "$(ALGO)" ]; then \
		echo "Use: make run FILE=<arquivo> ALGO=<bfs|astar>"; \
		exit 1; \
	fi

	@if [ ! -f "$(FILE)" ]; then \
		echo "Error: file '$(FILE)' not found."; \
		exit 1; \
	fi

	./$(TARGET) $(FILE) $(ALGO)

test: all
	@if [ -z "$(ALGO)" ]; then \
		echo "Use: make test ALGO=<bfs|astar>"; \
		exit 1; \
	fi
	@echo "==============================="
	@echo "Tests Execution using $(ALGO)"
	@echo "==============================="

	@mkdir -p $(TEST_OUTPUT_DIR)

	@TOTAL_START=$$(date +%s%N); \
	for file in $(TEST_DIR)/*.txt; do \
		filename=$$(basename $$file .txt); \
		output="$(TEST_OUTPUT_DIR)/$${filename}_$(ALGO)_out.txt"; \
		echo "--------------------------------"; \
		echo "Test: $$file"; \
		START=$$(date +%s%N); \
		./$(TARGET) $$file $(ALGO) > $$output; \
		END=$$(date +%s%N); \
		ELAPSED=$$((($$END-$$START)/1000000)); \
		echo "Output saved on: $$output"; \
		echo "Time Elapsed: $$ELAPSED ms"; \
	done; \
	TOTAL_END=$$(date +%s%N); \
	TOTAL=$$((($$TOTAL_END-$$TOTAL_START)/1000000)); \
	echo "================================"; \
	echo "Total Test Time: $$TOTAL ms"

.PHONY: all dir clean run