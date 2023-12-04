CPPFLAGS += -Wall -Wextra -Werror -Wpedantic -Wconversion
CPPFLAGS += -g3 -fpic

CXXFLAGS = -std=c++20

BUILD_DIR = build

.PHONY: all clean flash

all: bins

# Collect all sources
SRC_DIR = src
CPP_SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

SOURCES = $(CPP_SOURCES)

# List of object files in the build folder
SOURCES_BASE = $(basename $(SOURCES))
BIN_FILES = $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%, $(SOURCES_BASE))

bins: $(BIN_FILES)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	clang++ $(CPPFLAGS) $(CXXFLAGS) -o $@ $< 

clean:
	rm -rf $(BUILD_DIR)
