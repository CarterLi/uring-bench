build: normal.c uring_batch.c uring_single.c
	gcc -o normal -O3 normal.c
	gcc -o batch -O3 -luring uring_batch.c
	gcc -o single -O3 -luring uring_single.c

bench: build
	hyperfine --warmup 3 './normal' './batch' './single'
