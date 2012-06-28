CXX := g++

BUILD_DIR := build
SRC_DIR := src

SERVER_DIR := $(SRC_DIR)/server
SERVER_SRCS := $(shell find $(SERVER_DIR) -name "*.cpp")
SERVER_OBJS := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SERVER_SRCS))

TARGETS := server

OUTPUT := $(TARGETS) $(BUILD_DIR)

WARNINGS := -W -Wall -Wextra -pedantic -Wshadow -Wpointer-arith \
	-Wwrite-strings -Wmissing-declarations -Wredundant-decls -Winline \
	-Wconversion -Wcast-qual -Wcast-align -Wunused -Wundef \
	-Wsign-compare -Wold-style-cast -Woverloaded-virtual \
	-Wsign-promo -Wsynth -fno-exceptions -fno-rtti -fcheck-new

LIBS :=
IDIRS := -I$(SRC)
CFLAGS := $(CFLAGS) $(IDIRS) $(WARNINGS) -Werror -std=c++0x

.PHONY: dirs clean all

all: dirs $(TARGETS)

$(BUILD_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo CXX $@
	@$(CXX) $(CFLAGS) -MMD -MP -MT "$*.d $*.o" -c $< -o $@

server: $(SERVER_OBJS)
	@echo LN $@
	@$(CXX) $^ -o $@ $(LIBS)

clean:
	@$(RM) -r $(OUTPUT)

dirs:
	@mkdir -p $(patsubst %, $(BUILD_DIR)/%, $(shell find $(SRC_DIR) -type d))

