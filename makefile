FLAGS = -Wall -Werror -std=c99
APP = fp_analyzer

all: $(APP)_f $(APP)_d

$(APP)_f: $(APP).c main.c
	gcc $(Flags) $^ -o $@

$(APP)_d: $(APP).c main.c
	gcc $(Flags) -D DOUBLE $^ -o $@

clean:
	rm -f fp_analyzer_f fp_analyzer_d
