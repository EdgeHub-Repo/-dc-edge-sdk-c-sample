.PHONY: all clean test

all: openvpn build

build: DatahubEdge.so.1.0.5
	gcc sample.c -ldl -g -o sample -std=c99

cJSON.o: cJSON.c
	gcc -c -fPIC -o cJSON.o cJSON.c

clean:
	rm -f sample recover.db3
	rm -rf ./sample.dSYM

test:
