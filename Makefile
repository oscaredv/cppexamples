#TIDY_FLAGS = -checks='boost-*,bugprone-*,cert-*,clang-analyzer-*,cppcoreguidelines-*,hicpp-*,misc-*,modernize-*,performance-*,readability-*'

CPP := $(wildcard *.cpp)
BIN := $(subst .cpp,.out,$(CPP))
DEPS := $(subst .cpp,.d,$(CPP))

LIBS +=
LIBS_thread = -lpthread

CXXFLAGS += -Wall -Wextra -Werror -g -MMD -MP

.PHONY: all
all: $(BIN)

.PHONY: clean
clean:
	$(RM) $(BIN)
	$(RM) $(DEPS)

%.out: %.cpp Makefile
ifneq (,$(TIDY_FLAGS))
	clang-tidy $(TIDY_FLAGS) $< -- $(CXXFLAGS)
endif
	$(CXX) $(CXXFLAGS) -o $@ $< $(LIBS) $(LIBS_$(basename $@))

-include $(DEPS)