
/**
	Responsible for communicating to and from the host
	
	@author Natesh Narain
*/

#ifndef CLIENT_H
#define CLIENT_H

/**
	Checks if a packet is available in the packet buffer
	
	@return 1 for available packet, 0 otherwise
*/
unsigned char client_isPacketAvailable(void);

/**
	Load the next packet into the specified buffer
	
	@return 1 on success, 0 on failure
*/
int client_getNextPacket(char * packet);

/**
	Parse the command from the packet
	
	@return 0 on failure, 1 on success
*/
int client_parsePacketCommand(char * packet, char * cmd);

/**
	Parse the arguments from the packet into a variable argument list
	
	@param packet
		packet source string
		
	@param fmt
		format of arguments i.e "%d %d" for 2 int arguments
		
	@return number of successful conversions
*/
int client_parsePacketArguments(char * packet, char * fmt, ...);

#endif
