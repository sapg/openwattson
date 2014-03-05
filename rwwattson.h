/* openwattson - rwwattson.h
 * Include file for the openwattson read and write functions
 * including the data conversion functions
 * version 0.1
 */
 
#ifndef _INCLUDE_RW_WATTSON_H_
#define _INCLUDE_RW_WATTSON_H_ 

#ifdef WIN32
#include "winwattson.h"
#endif

#ifndef WIN32
#include "linuxwattson.h"
#endif

#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAXRETRIES 5

#define REPLY_BUF_SIZE 20
            
typedef struct {
	char name[50];
	int port;
} hostdata;

struct config_type
{
	char   serial_device_name[50];
};

struct timestamp
{
	int minute;
	int hour;
	int day;
	int month;
	int year;
};


/* Wattson read functions */
int get_current_power_with_retry(WATTSON wattson);
int get_current_power(WATTSON wattson);


/* Generic functions */

void read_error_exit(void);

void write_error_exit(void);

void print_usage(void);

int get_configuration(struct config_type *, char *path);

WATTSON open_wattson(char *device);

void close_wattson(WATTSON ws);

unsigned char data_checksum(unsigned char *data, int number);

int initialize(WATTSON wattson);

/* Platform dependent functions */
int writeport(WATTSON fd, char *chars);
int readport(WATTSON fd, char *result);
int getbaud(WATTSON fd);
void mySleep(int microseconds);

#endif /* _INCLUDE_RWWATTSON_H_ */ 
