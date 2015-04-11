
/**
	Responsible for communicating to and from the host
	
	@author Natesh Narain
*/

#ifndef CLIENT_H
#define CLIENT_H

/**
*/
unsigned char client_isPacketAvailable(void);

/**
	Load the next packet into the specified buffer
	
	@return 1 on success, 0 on failure
*/
int client_getNextPacket(char * packet);

/**
	Parse the command from the packet
*/
int client_parsePacketCommand(char * packet, char * cmd);

int client_parsePacketArguments(char * packet, char * fmt, ...);

#endif
