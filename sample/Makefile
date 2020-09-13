CC = arm-linux-gnueabi-g++
MOC = ../qt/tools/moc

SOURCE_DIR = src
BUILD_DIR = build
DIST_DIR = dist
SOURCES = $(wildcard $(SOURCE_DIR)/*.cpp)
EXECUTABLE = build/sample
MOC_HEADERS = src/app.h src/PageWithIconAndText.h src/ChartPage.h

CPPFLAGS = -Wall -marm -std=c++11
INC_DIRS = -I../include
LIBS = -L../lib/ -lqjson -lcurl -lLog -llfoundation -lpulse-simple -lpulse \
  -lQtDBus -lQtXml  -lQtGui -lQtNetwork -lQtCore -lpthread -Wl,-rpath-link=../lib/ -Wl,-rpath-link=../lib/pulseaudio

# Change postfixes
MOC_SOURCES = $(patsubst $(SOURCE_DIR)/%.h,$(BUILD_DIR)/%.moc.cpp,$(MOC_HEADERS))
OBJECTS = $(patsubst $(SOURCE_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES)) \
  $(patsubst $(BUILD_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(MOC_SOURCES))

all: $(EXECUTABLE)

package: $(EXECUTABLE) 
	bash ../scripts/package.sh ./

$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ $(LIBS) -o $@

# Generate object files, rule to change postfix
$(BUILD_DIR)/%.o : $(SOURCE_DIR)/%.cpp
	$(CC) $(CPPFLAGS) $(INC_DIRS) -c $< -o $@

$(BUILD_DIR)/%.o : $(BUILD_DIR)/%.cpp
	$(CC) $(CPPFLAGS) $(INC_DIRS) -c $< -o $@

# Generate cc from h via Qt's Meta Object Compiler, rule to change postfix
$(BUILD_DIR)/%.moc.cpp : $(SOURCE_DIR)/%.h
	$(MOC) $(INC_DIRS) $< -o $@

.PHONY: clean

clean:
	rm -r $(BUILD_DIR)/*
	rm -r $(DIST_DIR)/*
