sigmod : main.o bloom_filter.o skip_list.o skip_up_list.o vacine_table.o
	gcc -o sigmod main.o bloom_filter.o skip_list.o skip_up_list.o vacine_table.o -lm

main.o : main.c bloom_filter.h
	gcc -c main.c

bloom_filter.o : bloom_filter.c bloom_filter.h
	gcc -c bloom_filter.c

skip_list.o : skip_list.c skip_list.h
		gcc -c skip_list.c

skip_up_list.o : skip_up_list.c skip_list.h
		gcc -c skip_up_list.c

vacine_table.o : vacine_table.c skip_list.h 
		gcc -c vacine_table.c



run:
	./sigmod $(ARGS)
