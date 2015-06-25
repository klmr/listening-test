CXXFLAGS += -std=c++1y -pedantic -Wall -Wextra
LDFLAGS += -lsfml-system -lsfml-audio

target := soundtest

${target}:

.PHONY: clean
clean:
	${RM} *.o

.PHONY: cleanall
cleanall: clean
	${RM} ${target}
