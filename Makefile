all:
	gcc -g bouncer.c process_pkt.c linkedList.c processICMP.c comparisionFunctions.c checksum.c -o bouncer -lpcap -Wall

clean:
	rm -f *.o bouncer
