/* Include file for the openwattson Linux specific functions
 */
 
#ifndef _INCLUDE_LINUX_WATTSON_H_
#define _INCLUDE_LINUX_WATTSON_H_ 

#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <sys/ioctl.h>
#include <sys/signal.h>
#include <sys/types.h>

#define BAUDRATE B19200
#define DEFAULT_SERIAL_DEVICE "/dev/ttyS0"
typedef int WATTSON;

#endif /* _INCLUDE_LINUXWATTSON_H_ */

