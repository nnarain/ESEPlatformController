
/**
	Responsible for communicating to and from the host
	
	@author Natesh Narain
*/

#ifndef CLIENT_H
#define CLIENT_H

/* Commands */

#define PING      "P"
#define ECHO      "E"
#define SYNC      "Z"
#define SERVO     "S"
#define STEP      "ST"
#define MTR_SPEED "MS"
#define MTR_DIR   "MD"

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

/**
	Block until the Host sends a sync packet
*/
void client_syncHost(void);

/**
	Send a packet to the host
	
	@param id
		The packet type
		
	@param fmt
		formatted data
*/
void client_sendToHost(char * id, const char * fmt, ...);

/**
	Send a ping packet to the host
*/
void client_ping(void);

/**
*/
void client_echo(char * msg);

/**
    Check for communication Error
*/
int client_comError(void);

#endif
