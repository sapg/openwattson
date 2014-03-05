/*  openwattson - logwattson.c
 *  
 *  Version 0.1
 *  
 *  Log data from Wattson energy monitor
 *  
 *  Copyright 2010, Kary Främling, Jan Nyman
 *  This program is published under the GNU General Public license
 */

#include "rwwattson.h"

/********************************************************************
 * print_usage prints a short user guide
 *
 * Input:   none
 * 
 * Output:  prints to stdout
 * 
 * Returns: exits program
 *
 ********************************************************************/
void print_usage(void)
{
	printf("\n");
	printf("logwattson - Read and interpret data from Wattson energy monitor\n");
	printf("and write it to a log file. Perfect for a cron driven task.\n");
	printf("Version %s (C)2010 Kary Främling, Jan Nyman.\n", VERSION);
	printf("This program is released under the GNU General Public License (GPL)\n\n");
	printf("Usage:\n");
	printf("Save current data to logfile: logwattson filename config_filename\n");
	exit(0);
}
 
/********** MAIN PROGRAM ************************************************
 *
 * This program reads current weather data from a Wattson energy monitor
 * and appends the data to a log file.
 *
 * Log file format:
 * Timestamp Date Time power
 *
 * Just run the program without parameters for usage instructions.
 *
 * It takes two parameters. The first is the log filename with path
 * The second is the config file name with path
 * If this parameter is omitted the program will look at the default paths
 * See the openwattson.conf-dist file for info
 *
 ***********************************************************************/
int main(int argc, char *argv[])
{
	WATTSON wattson;
	FILE *fileptr;
	char logline[3000] = "";
	char datestring[50];        //used to hold the date stamp for the log file
	int current_power; 
	struct config_type config;
	time_t basictime;

	get_configuration(&config, argv[2]);

	wattson = open_wattson(config.serial_device_name);

	/* Get log filename. */
	if (argc < 2 || argc > 3)
	{
		print_usage();
	}			

	fileptr = fopen(argv[1], "a+");
	if (fileptr == NULL)
	{
		printf("Cannot open file %s\n",argv[1]);
		exit(-1);
	}

	/* Read power value */
	current_power = get_current_power_with_retry(wattson);
	sprintf(logline,"%s%d ", logline, current_power);

	/* Get date and time for log file, place before all data in log line. */
	time(&basictime);
	strftime(datestring, sizeof(datestring), "%Y%m%d%H%M%S %Y-%b-%d %H:%M:%S",
	         localtime(&basictime));

	// Print out and leave

	// printf("%s %s\n",datestring, logline); //disabled to be used in cron job
	fprintf(fileptr,"%s %s\n",datestring, logline);

	close_wattson(wattson);
	
	fclose(fileptr);

	exit(0);
}

