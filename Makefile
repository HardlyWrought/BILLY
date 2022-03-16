# -*- Makefile -*-

CC = gcc

CFLAGS = -g -Wextra -Wall -Werror

RM = rm



all:
	make text_clean; make snow_stem; make text_train

clean_all:
	make clean_text_data; make clean_text_clean; make clean_snow_stem; make clean_text_train 

	

text_train: text_train_main.o text_train.o text_clean.o text_data.o
	$(CC) $(CFLAGS) -o bin/text_train obj/text_train_main.o obj/text_train.o obj/text_clean.o obj/text_data.o -lsqlite3

clean_text_train:
	$(RM) bin/text_train obj/text_train.o obj/text_train_main.o

text_train_main.o: src/text_train_main.c src/text_train.h src/text_clean.c src/text_clean.h src/text_data.c src/text_data.h
	$(CC) $(CFLAGS) -o obj/text_train_main.o -c src/text_train_main.c

text_train.o: src/text_train.c src/text_train.h src/text_clean.c src/text_clean.h src/text_data.c src/text_data.h
	$(CC) $(CFLAGS) -o obj/text_train.o -c src/text_train.c



snow_stem: snow_stem_main.o snow_stem.o text_clean.o text_data.o
	$(CC) $(CFLAGS) -o bin/snow_stem obj/snow_stem_main.o obj/snow_stem.o obj/text_clean.o obj/text_data.o

clean_snow_stem:
	$(RM) bin/snow_stem obj/snow_stem.o obj/snow_stem_main.o

snow_stem_main.o: src/snow_stem_main.c src/snow_stem.h src/text_clean.c src/text_clean.h src/text_data.c src/text_data.h
	$(CC) $(CFLAGS) -o obj/snow_stem_main.o -c src/snow_stem_main.c

snow_stem.o: src/snow_stem.c src/snow_stem.h src/text_clean.c src/text_clean.h src/text_data.c src/text_data.h
	$(CC) $(CFLAGS) -o obj/snow_stem.o -c src/snow_stem.c



text_clean: text_clean_main.o text_clean.o text_data.o
	$(CC) $(CFLAGS) -o bin/text_clean obj/text_clean_main.o obj/text_clean.o obj/text_data.o

clean_text_clean:
	$(RM) bin/text_clean obj/text_clean.o obj/text_clean_main.o

text_clean_main.o: src/text_clean_main.c src/text_clean.c src/text_clean.h src/text_data.c src/text_data.h
	$(CC) $(CFLAGS) -o obj/text_clean_main.o -c src/text_clean_main.c

text_clean.o: src/text_clean.c src/text_clean.h src/text_data.c src/text_data.h
	$(CC) $(CFLAGS) -o obj/text_clean.o -c src/text_clean.c



clean_text_data:
	$(RM) obj/text_data.o

text_data.o: src/text_data.c src/text_data.h
	$(CC) $(CFLAGS) -o obj/text_data.o -c src/text_data.c 
