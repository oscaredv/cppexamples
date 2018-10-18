TIDY_FLAGS = -quiet -checks='boost-*,bugprone-*,cert-*,clang-analyzer-*,cppcoreguidelines-*,hicpp-*,misc-*,modernize-*,performance-*,readability-*'

MACROS_has_include := $(shell export PATH=$(PATH); $(CXX) -E -dM has_include.cpp)

CPP := $(wildcard *.cpp)
BIN := $(subst .cpp,.out,$(CPP))
DEPS := $(subst .cpp,.d,$(CPP))

LIBS +=
LIBS_filesystem = -lstdc++fs
LIBS_thread = -lpthread
ifneq ($(findstring __HAS_CRYPTOPP__,$(MACROS_has_include)),)
LIBS_has_include = -lcryptopp
endif

CXXFLAGS += -Wall -Wextra -Werror -Wnon-virtual-dtor -pedantic
CXXFLAGS += -std=c++17
CXXFLAGS += -g
CXXFLAGS += -MMD -MP

.PHONY: all
all: $(BIN)

.PHONY: clean
clean:
	$(RM) $(BIN)
	$(RM) $(DEPS)

%.out: %.cpp Makefile
ifneq (,$(TIDY_FLAGS))
	@echo "clang-tidy $<"
	@clang-tidy $(TIDY_FLAGS) $< -- $(CXXFLAGS)
endif
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS) $(LIBS_$(basename $@))

-include $(DEPS)
