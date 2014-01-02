MAKEFLAGS := -j4 -s
BUILD_DIR := build
SRC_DIR := src

PREFIX := $(DESTDIR)/usr

SERVER_DIR := $(SRC_DIR)/server
SERVER_SRCS := $(shell find $(SERVER_DIR) -name "*.cc")
SERVER_OBJS := $(patsubst %.cc, $(BUILD_DIR)/%.o, $(SERVER_SRCS))

CLIENT_DIR := $(SRC_DIR)/client
CLIENT_SRCS := $(shell find $(CLIENT_DIR) -name "*.cc")
CLIENT_OBJS := $(patsubst %.cc, $(BUILD_DIR)/%.o, $(CLIENT_SRCS))

COMMON_DIR := $(SRC_DIR)/common
COMMON_SRCS := $(shell find $(COMMON_DIR) -name "*.cc")
COMMON_OBJS := $(patsubst %.cc, $(BUILD_DIR)/%.o, $(COMMON_SRCS))

DEPS := $(COMMON_OBJS:.o=.d) $(CLIENT_OBJS:.o=.d) $(SERVER_OBJS:.o=.d)
DEPS := $(sort $(DEPS))

TARGETS := udpgame_server udpgame_client

OUTPUT := $(TARGETS) $(BUILD_DIR)

WARN := -pedantic -Wall -Wextra -Wno-unused-parameter

PKGS := glew SDL_image sdl glu protobuf

LIBS := -lpthread -lm -lrt
LIBS += $(shell pkg-config --libs $(PKGS))

CXXFLAGS := -fno-exceptions
CXXFLAGS += $(shell pkg-config --cflags $(PKGS))
CXXFLAGS += $(CFLAGS) -I$(SRC_DIR) $(WARN) -std=c++11 -g

.PHONY: clean all proto install
.SUFFIXES: .cc .cpp

all: $(TARGETS)

$(BUILD_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.cc
	echo CXX $@
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

proto:
	cd src; \
	protoc --cpp_out=./ common/proto/udpgame.proto

udpgame_server: $(SERVER_OBJS) $(COMMON_OBJS)
	echo LN $@
	$(CXX) $^ -o $@ $(LIBS)

udpgame_client: $(CLIENT_OBJS) $(COMMON_OBJS)
	echo LN $@
	$(CXX) $^ -o $@ $(LIBS)

clean:
	$(RM) -r $(OUTPUT)

install: udpgame_client udpgame_server
	mkdir -p $(PREFIX)/bin
	install -m 0755 udpgame_client $(PREFIX)/bin
	install -m 0755 udpgame_server $(PREFIX)/bin
	mkdir -p $(PREFIX)/share/udpgame
	cp -r resources $(PREFIX)/share/udpgame

ifneq ($(MAKECMDGOALS), clean)
-include $(DEPS)
endif

