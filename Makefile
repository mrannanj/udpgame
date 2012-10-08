BUILD_DIR := build
SRC_DIR := src

SERVER_DIR := $(SRC_DIR)/server
SERVER_SRCS := $(shell find $(SERVER_DIR) -name "*.cc")
SERVER_OBJS := $(patsubst %.cc, $(BUILD_DIR)/%.o, $(SERVER_SRCS))

CLIENT_DIR := $(SRC_DIR)/client
CLIENT_SRCS := $(shell find $(CLIENT_DIR) -name "*.cc")
CLIENT_OBJS := $(patsubst %.cc, $(BUILD_DIR)/%.o, $(CLIENT_SRCS))

COMMON_DIR := $(SRC_DIR)/common
COMMON_SRCS := $(shell find $(COMMON_DIR) -name "*.cc")
COMMON_OBJS := $(patsubst %.cc, $(BUILD_DIR)/%.o, $(COMMON_SRCS))

TARGETS := server client

OUTPUT := $(TARGETS) $(BUILD_DIR)

ifeq ($(CXX), g++)
	WARN := -Wall -Wextra
else ifeq ($(CXX), clang++)
	WARN := -Weverything -Wno-padded -Wno-missing-noreturn
	WARN := -Wno-global-constructors -Wno-exit-time-destructors
endif

WARN += -pedantic -Wno-unused-parameter

PKGS := glew SDL_image sdl glu

LIBS := -lpthread -lm -lrt
LIBS += $(shell pkg-config --libs $(PKGS))

CFLAGS := -fno-exceptions -fno-rtti
CFLAGS += $(shell pkg-config --cflags $(PKGS))
CFLAGS += $(CFLAGS) -I$(SRC_DIR) $(WARN) -Werror -std=c++0x -g

.PHONY: dirs clean all

all: dirs $(TARGETS)

$(BUILD_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.cc
	@echo CXX $@
	@$(CXX) $(CFLAGS) -MMD -MP -MT "$*.d $*.o" -c $< -o $@

server: $(SERVER_OBJS) $(COMMON_OBJS)
	@echo LN $@
	@$(CXX) $^ -o $@ $(LIBS)

client: $(CLIENT_OBJS) $(COMMON_OBJS)
	@echo LN $@
	@$(CXX) $^ -o $@ $(LIBS)

clean:
	@$(RM) -r $(OUTPUT)

dirs:
	@mkdir -p $(patsubst %, $(BUILD_DIR)/%, $(shell find $(SRC_DIR) -type d))

