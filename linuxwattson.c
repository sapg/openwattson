/*  openwattson  - Linux specific library functions
 *  This file contains the common functions that are unique to
 *  Linux. The entire file is ignored in case of Windows
 *  
 *  Version 0.1
 *  
 *  Control Wattson power meter
 *  
 *  Copyright 2010, Kary Främling, Jan Nyman
 *  This program is published under the GNU General Public license
 */

#ifndef WIN32
#define DEBUG 0

#include <errno.h>
#include <sys/file.h>
#include "rwwattson.h"

/********************************************************************
 * open_wattson, Linux version
 *
 * Input:   devicename (/dev/tty0, /dev/tty1 etc)
 * 
 * Returns: Handle to the Wattson (type WATTSON)
 *
 ********************************************************************/
WATTSON open_wattson(char *device)
{
	WATTSON wattson;
	struct termios adtio;
	int portstatus;

	//Setup serial port

	if ((wattson = open(device, O_RDWR | O_NOCTTY)) < 0)
	{
		printf("\nUnable to open serial device %s\n", device);
		exit(EXIT_FAILURE);
	}
	
	if ( flock(wattson, LOCK_EX) < 0 ) {
		perror("\nSerial device is locked by other program\n");
		exit(EXIT_FAILURE);
	}
	
	//We want full control of what is set and simply reset the entire adtio struct
	memset(&adtio, 0, sizeof(adtio));
	
	// Serial control options
	adtio.c_cflag &= ~PARENB;      // No parity
	adtio.c_cflag &= ~CSTOPB;      // One stop bit
	adtio.c_cflag &= ~CSIZE;       // Character size mask
	adtio.c_cflag |= CS8;          // Character size 8 bits
	adtio.c_cflag |= CREAD;        // Enable Receiver
	adtio.c_cflag &= ~HUPCL;       // No "hangup"
	adtio.c_cflag &= ~CRTSCTS;     // No flowcontrol
	adtio.c_cflag |= CLOCAL;       // Ignore modem control lines

	// Baudrate, for newer systems
	cfsetispeed(&adtio, BAUDRATE);
	cfsetospeed(&adtio, BAUDRATE);	
	
	// Serial local options: adtio.c_lflag
	// Raw input = clear ICANON, ECHO, ECHOE, and ISIG
	// Disable misc other local features = clear FLUSHO, NOFLSH, TOSTOP, PENDIN, and IEXTEN
	// So we actually clear all flags in adtio.c_lflag
	adtio.c_lflag = 0;

	// Serial input options: adtio.c_iflag
	// Disable parity check = clear INPCK, PARMRK, and ISTRIP 
	// Disable software flow control = clear IXON, IXOFF, and IXANY
	// Disable any translation of CR and LF = clear INLCR, IGNCR, and ICRNL	
	// Ignore break condition on input = set IGNBRK
	// Ignore parity errors just in case = set IGNPAR;
	// So we can clear all flags except IGNBRK and IGNPAR
	adtio.c_iflag = IGNBRK|IGNPAR;
	
	// Serial output options
	// Raw output should disable all other output options
	adtio.c_oflag &= ~OPOST;

	adtio.c_cc[VTIME] = 10;		// timer 1s
	adtio.c_cc[VMIN] = 0;		// blocking read until 1 char
	
	if (tcsetattr(wattson, TCSANOW, &adtio) < 0)
	{
		printf("Unable to initialize serial device");
		exit(0);
	}

	tcflush(wattson, TCIOFLUSH);

	// Set DTR low and RTS high and leave other ctrl lines untouched

	ioctl(wattson, TIOCMGET, &portstatus);	// get current port status
	portstatus &= ~TIOCM_DTR;
	portstatus |= TIOCM_RTS;
	ioctl(wattson, TIOCMSET, &portstatus);	// set current port status

	return wattson;
}

/********************************************************************
 * close_wattson, Linux version
 *
 * Input: Handle to the weatherstation (type WEATHERSTATION)
 *
 * Returns nothing
 *
 ********************************************************************/
void close_wattson(WATTSON wattson)
{
	close(wattson);
	return;
}

int writeport(int fd, char *chars) {
	int len = strlen(chars);
	chars[len] = 0x0d; // stick a <CR> after the command
	chars[len+1] = 0x00; // terminate the string properly
	int n = write(fd, chars, strlen(chars));
	if (n < 0) {
		fputs("write failed!\n", stderr);
		return -1;
	}
	return n;                                                                       	                                
}

int readport(int fd, char *result) {
	int iIn = read(fd, result, 254);
	result[iIn-1] = 0x00;
	if (iIn < 0) {
		if (errno == EAGAIN) {
			printf("SERIAL EAGAIN ERROR\n");
			return -1;
		} else {
			printf("SERIAL read error %d %s\n", errno, strerror(errno));
			return -1;
		}
	}                    
	return iIn;
}

int getbaud(int fd) {
	struct termios termAttr;
	int inputSpeed = -1;
	speed_t baudRate;
	tcgetattr(fd, &termAttr);
	/* Get the input speed.                              */
	baudRate = cfgetispeed(&termAttr);
	switch (baudRate) {
		case B0:      inputSpeed = 0; break;
		case B50:     inputSpeed = 50; break;
		case B110:    inputSpeed = 110; break;
		case B134:    inputSpeed = 134; break;
		case B150:    inputSpeed = 150; break;
		case B200:    inputSpeed = 200; break;
		case B300:    inputSpeed = 300; break;
		case B600:    inputSpeed = 600; break;
		case B1200:   inputSpeed = 1200; break;
		case B1800:   inputSpeed = 1800; break;
		case B2400:   inputSpeed = 2400; break;
		case B4800:   inputSpeed = 4800; break;
		case B9600:   inputSpeed = 9600; break;
		case B19200:  inputSpeed = 19200; break;
		case B38400:  inputSpeed = 38400; break;
	}
	return inputSpeed;
}

/********************************************************************
 * mySleep - Linux version
 * 
 * Inputs: Time in microseconds (integer)
 *
 * Returns: nothing
 *
 ********************************************************************/
void mySleep(int microseconds)
{
	usleep(microseconds);
}


#endif

