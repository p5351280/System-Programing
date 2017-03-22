all:
	gcc -c -o fig3_4_100.o fig3_4_100.c
	gcc -o buffsize100 fig3_4_100.o error.c
	gcc -c -o fig3_4_4096.o fig3_4_4096.c
	gcc -o buffsize4096 fig3_4_4096.o error.c
	gcc -c -o fig3_4_8192.o fig3_4_8192.c
	gcc -o buffsize8192 fig3_4_8192.o error.c
	gcc -c -o fig3_4_16384.o fig3_4_16384.c
	gcc -o buffsize16384 fig3_4_16384.o error.c
	gcc -c -o fig3_4_4096_fsync.o fig3_4_4096_fsync.c
	gcc -o buffsize4096_fsync fig3_4_4096_fsync.o error.c
clear:
	rm -rf *.o
	rm -rf buffsize*
