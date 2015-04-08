
/**
	Responsible for communicating to and from the host
	
	@author Natesh Narain
*/

#ifndef CLIENT_H
#define CLIENT_H

/**
*/
unsigned char client_isPacketAvailable(void);

/***/
char * client_getNextPacket(void);

#endif
