/*  openwattson - fetchwattson.c
 *  
 *  Version 0.1
 *  
 *  Control Wattson Power meter
 *  
 *  Copyright 2010, Kary Främling, Jan Nyman
 *  This program is published under the GNU General Public license
 */

#include "rwwattson.h"
 
/********** MAIN PROGRAM ************************************************
 *
 *
 * It takes one parameter which is the config file name with path
 * If this parameter is omitted the program will look at the default paths
 * See the openwattson.conf-dist file for info
 *
 ***********************************************************************/
int main(int argc, char *argv[])
{
	WATTSON wattson;
	char logline[100] = "";
	char datestring[50];     //used to hold the date stamp for the log file
	struct config_type config;
	int current_power;
	time_t basictime;

	get_configuration(&config, argv[1]);

	wattson = open_wattson(config.serial_device_name);

	/* READ CURRENT POWER CONSUMPTION */
	
	current_power = get_current_power_with_retry(wattson);
	sprintf(logline, "%sPower %d\n", logline, current_power);

	/* GET DATE AND TIME FOR LOG FILE, PLACE BEFORE ALL DATA IN LOG LINE */
	
	time(&basictime);
	strftime(datestring,sizeof(datestring),"Date %Y-%b-%d\nTime %H:%M:%S\n",
	         localtime(&basictime));

	// Print out and leave

	printf("%s%s", datestring, logline);

	close_wattson(wattson);

	return(0);
}

