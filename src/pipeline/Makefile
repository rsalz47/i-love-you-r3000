CC=g++
CFLAGS=-std=c++19.

pipeline-driver: fetch_stage.cpp decode_stage.cpp execute_stage.cpp memory_stage.cpp writeback_stage.cpp ../mem/cache.cpp ../mem/memory.cpp
	$(CC) -o pipeline-driver \
    driver.cpp \
    fetch_stage.cpp \
    decode_stage.cpp \
	execute_stage.cpp \
	memory_stage.cpp \
	writeback_stage.cpp \
	../mem/cache.cpp \
    ../mem/memory.cpp

clean: 
	rm ./driver
