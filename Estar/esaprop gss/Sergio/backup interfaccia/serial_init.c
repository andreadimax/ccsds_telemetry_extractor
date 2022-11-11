#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <stdlib.h>
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <sys/ioctl.h>
#include <paths.h>
#include <sysexits.h>
#include <sys/param.h>
#include <sys/select.h>
#include <sys/time.h>
#include <time.h>


#define SERIAL_PORT "/dev/ttyUSB0"  //porta seriale per radiomodem
#define SERIAL_PORT1 "/dev/ttyUSB1"  //porta seriale per radiomodem


int serial_init(void)
{
	printf("OPEN SERIAL HARDLINE\n");
	static struct termios serialAttrs;
	struct termios  options;
	int handshake;
	int serial_descriptor;

	serial_descriptor = open(SERIAL_PORT, O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK);
	
	if (serial_descriptor < 0)
		fprintf (stdout, "Bad opening of SERIAL HARDLINE\n");
	//writelog("Setting TIOCEXCL", ioctl(serial_descriptor, TIOCEXCL));
	//writelog("Setting F_SETFL", fcntl(serial_descriptor, F_SETFL, 0));
    	
	tcgetattr(serial_descriptor, &serialAttrs);

	options = serialAttrs;
	/*
	printf("old cflag=%08o\n", serialAttrs.c_cflag);
        printf("old oflag=%08o\n", serialAttrs.c_oflag);
        printf("old iflag=%08o\n", serialAttrs.c_iflag);
        printf("old lflag=%08o\n", serialAttrs.c_lflag);
        printf("old line=%03o\n", serialAttrs.c_line);
*/
	tcflush(serial_descriptor, TCIFLUSH);
        tcflush(serial_descriptor, TCOFLUSH);
	
	cfmakeraw(&serialAttrs);
//	serialAttrs.c_cflag &= ~CSIZE;
	
	serialAttrs.c_cflag |= CS8; // | CREAD | CLOCAL
	//serialAttrs.c_cflag &= ~(HUPCL|PARENB|PARODD|CLOCAL);
	//serialAttrs.c_lflag = 0;
	serialAttrs.c_lflag &= ~(ICANON|IEXTEN|ECHO);
	//serialAttrs.c_lflag |= ECHO;
	serialAttrs.c_iflag = 0; //&= ~ICRNL
	
    
    	cfsetspeed(&serialAttrs, B9600);   // Set baud
    	tcsetattr(serial_descriptor, TCSANOW, &serialAttrs);
/*
	printf("new cflag=%08o\n", serialAttrs.c_cflag);
        printf("new oflag=%08o\n", serialAttrs.c_oflag);
        printf("new iflag=%08o\n", serialAttrs.c_iflag);
        printf("new lflag=%08o\n", serialAttrs.c_lflag);
        printf("new line=%03o\n", serialAttrs.c_line);
*/	
	printf("SERIAL HARDLINE OPENED\n");
	printf("%d\n", serial_descriptor);

	return(serial_descriptor);
}


int serial_init2(void)
{
	printf("OPEN TNC SERIAL PORT\n");
	static struct termios serialAttrs;
	struct termios  options;
	int handshake;
	int serial_descriptor;

	serial_descriptor = open(SERIAL_PORT1, O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK);
	
	if (serial_descriptor < 0)
		fprintf (stdout, "la seriale non si apre\n");
	//writelog("Setting TIOCEXCL", ioctl(serial_descriptor, TIOCEXCL));
	//writelog("Setting F_SETFL", fcntl(serial_descriptor, F_SETFL, 0));
    	
	tcgetattr(serial_descriptor, &serialAttrs);

	options = serialAttrs;
	/*
	printf("old cflag=%08o\n", serialAttrs.c_cflag);
        printf("old oflag=%08o\n", serialAttrs.c_oflag);
        printf("old iflag=%08o\n", serialAttrs.c_iflag);
        printf("old lflag=%08o\n", serialAttrs.c_lflag);
        printf("old line=%03o\n", serialAttrs.c_line);
*/

	tcflush(serial_descriptor, TCIFLUSH);
        tcflush(serial_descriptor, TCOFLUSH);
	
	cfmakeraw(&serialAttrs);
//	serialAttrs.c_cflag &= ~CSIZE;
	
	serialAttrs.c_cflag |= CS8; // | CREAD | CLOCAL
	//serialAttrs.c_cflag &= ~(HUPCL|PARENB|PARODD|CLOCAL);
	//serialAttrs.c_lflag = 0;
	serialAttrs.c_lflag &= ~(ICANON|IEXTEN|ECHO);
	//serialAttrs.c_lflag |= ECHO;
	serialAttrs.c_iflag = 0; //&= ~ICRNL
	
    
    	cfsetspeed(&serialAttrs, B38400);   // Set baud
    	tcsetattr(serial_descriptor, TCSANOW, &serialAttrs);
/*
	printf("new cflag=%08o\n", serialAttrs.c_cflag);
        printf("new oflag=%08o\n", serialAttrs.c_oflag);
        printf("new iflag=%08o\n", serialAttrs.c_iflag);
        printf("new lflag=%08o\n", serialAttrs.c_lflag);
        printf("new line=%03o\n", serialAttrs.c_line);
*/	
	printf("TNC SERIAL PORT OPENED\n");
	printf("%d\n", serial_descriptor);


	return(serial_descriptor);
}

