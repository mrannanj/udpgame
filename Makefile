MAKEFLAGS := -j4
BUILD_DIR := build
SRC_DIR := src

PREFIX := $(DESTDIR)/usr

SERVER_DIR := $(SRC_DIR)/server
SERVER_SRCS := $(shell find $(SERVER_DIR) -name "*.cc")
SERVER_OBJS := $(patsubst %.cc, $(BUILD_DIR)/%.o, $(SERVER_SRCS))

CLIENT_DIR := $(SRC_DIR)/client
CLIENT_SRCS := $(shell find $(CLIENT_DIR) -name "*.cc")
CLIENT_OBJS := $(patsubst %.cc, $(BUILD_DIR)/%.o, $(CLIENT_SRCS))

PROTO_SRC := $(SRC_DIR)/common/proto/udpgame.pb.cc
PROTO_OBJ := $(BUILD_DIR)/$(SRC_DIR)/common/proto/udpgame.pb.o

COMMON_DIR := $(SRC_DIR)/common
COMMON_SRCS := $(PROTO_SRC)
COMMON_SRCS += $(shell find $(COMMON_DIR) -name "*.cc")
COMMON_OBJS := $(patsubst %.cc, $(BUILD_DIR)/%.o, $(COMMON_SRCS))

DEPS := $(COMMON_OBJS:.o=.d) $(CLIENT_OBJS:.o=.d) $(SERVER_OBJS:.o=.d)
DEPS := $(sort $(DEPS))

TARGETS := udpgame_server udpgame_client

OUTPUT := $(TARGETS) $(BUILD_DIR)

PKGS := glew SDL_image sdl protobuf sfml-network

LDFLAGS := -lm $(shell pkg-config --libs $(PKGS))
LDFLAGS += -g -std=c++11

CXXFLAGS := -fno-exceptions
CXXFLAGS += $(shell pkg-config --cflags $(PKGS))
CXXFLAGS += -I$(SRC_DIR) -g -std=c++11

UNAME := $(shell uname -s)
ifeq ($(UNAME),Linux)
  WARN := -pedantic -Wall -Wextra -Wno-unused-parameter -Weffc++
  WARN += -Wnon-virtual-dtor -Wsign-compare -Werror
  #WARN += -Weverything -Wno-c++98-compat -Wno-padded -Wno-documentation
  CXXFLAGS += $(shell pkg-config --cflags glu)
  LDFLAGS += $(shell pkg-config --libs glu)
endif
ifeq ($(UNAME),Darwin)
  LDFLAGS += -framework GLUT -framework OpenGL -framework SFML
endif

.PHONY: clean all install env
.SUFFIXES: .cc .cpp

all: $(TARGETS)

env:
	@echo "CXX = $(CXX)"
	@echo "CXXFLAGS = $(CXXFLAGS)"
	@echo "LDFLAGS = $(LDFLAGS)"
	@echo "WARN = $(WARN)"
	$(CXX) --version

.SECONDARY:
$(SRC_DIR)/%.pb.h $(SRC_DIR)/%.pb.cc: $(SRC_DIR)/%.proto
	@echo "PROTOC $@ <- $<"
	@cd src; \
	 protoc --cpp_out=./ common/proto/udpgame.proto

$(PROTO_OBJ): $(SRC_DIR)/common/proto/udpgame.pb.cc
	@echo "CXX $@ <- $<"
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.cc $(PROTO_OBJ)
	@echo "CXX $@ <- $<"
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) $(WARN) -MMD -MP -c $< -o $@

udpgame_server: $(COMMON_OBJS) $(SERVER_OBJS)
	@echo "LN $@ <- $^"
	@$(CXX) -o $@ $^ $(LDFLAGS)

udpgame_client: $(COMMON_OBJS) $(CLIENT_OBJS)
	@echo "LN $@ <- $^"
	@$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) -r $(OUTPUT)
	$(RM) -r $(SRC_DIR)/common/proto/udpgame.pb.cc
	$(RM) -r $(SRC_DIR)/common/proto/udpgame.pb.h

install: udpgame_client udpgame_server
	mkdir -p $(PREFIX)/bin
	install -m 0755 udpgame_client $(PREFIX)/bin
	install -m 0755 udpgame_server $(PREFIX)/bin
	mkdir -p $(PREFIX)/share/udpgame
	cp -r resources $(PREFIX)/share/udpgame

ifneq ($(MAKECMDGOALS), clean)
-include $(DEPS)
endif

