HTAB_STAT_MODS = htab_hash_function.o htab_init.o htab_size.o htab_bucket_count.o htab_resize.o htab_find.o htab_lookup_add.o htab_erase.o htab_for_each.o htab_clear.o htab_free.o error.o
HTAB_DYN_MODS = htab_hash_function_dyn.o htab_init_dyn.o htab_size_dyn.o htab_bucket_count_dyn.o htab_resize_dyn.o htab_find_dyn.o htab_lookup_add_dyn.o htab_erase_dyn.o htab_for_each_dyn.o htab_clear_dyn.o htab_free_dyn.o error_dyn.o
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -O2

all: libhtab.a libhtab.so tail wordcount wordcount-dynamic

tail: tail.c
	gcc $(CFLAGS) tail.c -o tail

wordcount-dynamic: libhtab.so wordcount.c io.c
	gcc $(CFLAGS) wordcount.c io.c -L. -lhtab -o wordcount-dynamic

wordcount: libhtab.a wordcount.c io.c
	gcc $(CFLAGS) -static wordcount.c io.c -L. -lhtab -o wordcount

libhtab.a: $(HTAB_STAT_MODS) 
	ar rc libhtab.a $(HTAB_STAT_MODS) && \
	ranlib libhtab.a

htab_hash_function.o: htab_hash_function.c
	gcc -c $(CFLAGS) htab_hash_function.c -o htab_hash_function.o

htab_init.o: htab_init.c
	gcc -c $(CFLAGS) htab_init.c -o htab_init.o

htab_size.o: htab_size.c
	gcc -c $(CFLAGS) htab_size.c -o htab_size.o

htab_bucket_count.o: htab_bucket_count.c
	gcc -c $(CFLAGS) htab_bucket_count.c -o htab_bucket_count.o

htab_resize.o: htab_resize.c
	gcc -c $(CFLAGS) htab_resize.c -o htab_resize.o

htab_find.o: htab_find.c
	gcc -c $(CFLAGS) htab_find.c -o htab_find.o

htab_lookup_add.o: htab_lookup_add.c
	gcc -c $(CFLAGS) htab_lookup_add.c -o htab_lookup_add.o

htab_erase.o: htab_erase.c
	gcc -c $(CFLAGS) htab_erase.c -o htab_erase.o

htab_for_each.o: htab_for_each.c
	gcc -c $(CFLAGS) htab_for_each.c -o htab_for_each.o

htab_clear.o: htab_clear.c
	gcc -c $(CFLAGS) htab_clear.c -o htab_clear.o

htab_free.o: htab_free.c
	gcc -c $(CFLAGS) htab_free.c -o htab_free.o

error.o: error.c
	gcc -c $(CFLAGS) error.c -o error.o


libhtab.so: $(HTAB_DYN_MODS)
	gcc -shared -fPIC $(HTAB_DYN_MODS) -o libhtab.so

htab_hash_function_dyn.o: htab_hash_function.c
	gcc -c -fPIC $(CFLAGS) htab_hash_function.c -o htab_hash_function_dyn.o

htab_init_dyn.o: htab_init.c
	gcc -c -fPIC $(CFLAGS) htab_init.c -o htab_init_dyn.o

htab_size_dyn.o: htab_size.c
	gcc -c -fPIC $(CFLAGS) htab_size.c -o htab_size_dyn.o

htab_bucket_count_dyn.o: htab_bucket_count.c
	gcc -c -fPIC $(CFLAGS) htab_bucket_count.c -o htab_bucket_count_dyn.o

htab_resize_dyn.o: htab_resize.c
	gcc -c -fPIC $(CFLAGS) htab_resize.c -o htab_resize_dyn.o

htab_find_dyn.o: htab_find.c
	gcc -c -fPIC $(CFLAGS) htab_find.c -o htab_find_dyn.o

htab_lookup_add_dyn.o: htab_lookup_add.c
	gcc -c -fPIC $(CFLAGS) htab_lookup_add.c -o htab_lookup_add_dyn.o

htab_erase_dyn.o: htab_erase.c
	gcc -c -fPIC $(CFLAGS) htab_erase.c -o htab_erase_dyn.o

htab_for_each_dyn.o: htab_for_each.c
	gcc -c -fPIC $(CFLAGS) htab_for_each.c -o htab_for_each_dyn.o

htab_clear_dyn.o: htab_clear.c
	gcc -c -fPIC $(CFLAGS) htab_clear.c -o htab_clear_dyn.o

htab_free_dyn.o: htab_free.c
	gcc -c -fPIC $(CFLAGS) htab_free.c -o htab_free_dyn.o

error_dyn.o: error.c
	gcc -c -fPIC $(CFLAGS) error.c -o error_dyn.o

clean:
	rm -rf *.o