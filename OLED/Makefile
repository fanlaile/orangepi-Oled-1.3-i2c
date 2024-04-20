CFLAGS= -Wall -O2
CC=/usr/bin/arm-linux-gnueabihf-gcc
STRIP=/usr/bin/arm-linux-gnueabihf-strip
 
test_18_oled: test_18_oled.o drv_oled.o
	$(CC) $(CFLAGS) -o test_18_oled test_18_oled.o drv_oled.o
	$(STRIP) -s test_18_oled
 
clean:
	rm -f test_18_oled test_18_oled.o drv_oled.o
