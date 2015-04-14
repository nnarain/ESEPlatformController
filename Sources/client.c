
/**
	Host Communication 
	
	@author Natesh Narain
*/

#include "client.h"
#include "sci.h"
#include "derivative.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

// DEBUG
#include "leds.h"

#define PACKET_START     '<'
#define PACKET_END       '>'

#define MAX_PACKET_SIZE  20
#define MAX_PACKET_COUNT 10
#define MAX_BUFFER_SIZE  (MAX_PACKET_SIZE * MAX_PACKET_COUNT)

// Error Detection
#define ERROR ( SCI_FE && SCI_NF )

// buffer for packet data
static char packetBuffer[MAX_BUFFER_SIZE];

// indices to keep track of the current read and write position
static unsigned int writeIdx = 0;
static unsigned int readIdx  = 0;;

// Number of valid packets
static volatile unsigned int packetCount = 0;

// communication error flag
static volatile int comError = 0;

/* Private Prototypes */

#pragma INLINE
static unsigned int nextIdx(unsigned int * idx);

unsigned char client_isPacketAvailable(void)
{
	return packetCount > 0;
}

int client_getNextPacket(char * packet)
{
	unsigned int i = 0;

	// check if starting with a valid packet
	if(packetBuffer[nextIdx(&readIdx)] != PACKET_START)
	{
		return 0;
	}
	
	while(packetBuffer[readIdx] != PACKET_END)
	{
		packet[i++] = packetBuffer[nextIdx(&readIdx)];
	}
	
	// insert the packet end character and complete with a null
//	packet[i++] = packetBuffer[nextIdx(&readIdx)];
    readIdx ++;
	packet[i++] = '\0';
	
	packetCount--;
	
	return 1;
}

int client_parsePacketCommand(char * packet, char * cmd)
{
	// NOTE: the format %[A-Z] could not be use so I expanded it manually
	return sscanf(packet, "%[ABCDEFGHIJKLMNOPQRSTUVWXYZ]", cmd);
}

int client_parsePacketArguments(char * packet, char * fmt, ...)
{
	va_list args;
	char format[50];
	int ret;
	
	// build the format string
	(void)sprintf(format, "%%*s %s", fmt);
	
	// parse the arguments using built format
	va_start(args, fmt);
	ret = vsscanf(packet, format, args);
	va_end(args);
	
	// return number of successful conversions
	return ret;
}

void client_syncHost()
{
	char packet[MAX_PACKET_SIZE];
	char cmd[5];
	int synced;
	
	synced = 0;
	
	while(!synced)
	{
		// wait for a packet from the host
		while(!client_isPacketAvailable());
		
		// read the packet
		(void)client_getNextPacket(packet);
		
		//
		if(client_parsePacketCommand(packet, cmd))
		{
			if(strcmp(cmd, SYNC) == 0)
			{
				synced = 1;
			}
		}
	}
}

void client_sendToHost(char * cmd, const char * fmt, ...)
{
	va_list args;
	char packet[MAX_PACKET_SIZE];
	char format[20];
	
	// build format
	if(fmt)
	{
		(void)sprintf(format, "<%s %s>", cmd, fmt);
	}
	else
	{
		(void)sprintf(format, "<%s>", cmd);
	}
	
	// populate packet arguments
	va_start(args, fmt);
	(void)vsprintf(packet, format, args);
	va_end(args);
	
	// write to the serial port
	sci_puts(packet);
}

void client_ping(void)
{
	client_sendToHost(PING, NULL, NULL);
}

void client_echo(char * msg)
{
    client_sendToHost(ECHO, "%s", msg);
}

int client_comError(void)
{
    int ret = comError;
    if(comError)
        comError = 0;
    return ret;
}

#pragma INLINE
static unsigned int nextIdx(unsigned int * idx)
{
	unsigned int ret = *idx;
	*idx = (*idx + 1) % MAX_BUFFER_SIZE;
	return ret;
}

// Serial Communication Interface Interrupt Handler
interrupt VectorNumber_Vsci void sci_handler(void)
{
	static unsigned char hasStart = 0;
	
	const char data = SCIDRL;

	// check for recieved data
	if(SCI_RDRF)
	{
		// check if recieved the start of a packet
		if(data == PACKET_START)
		{
			packetBuffer[nextIdx(&writeIdx)] = data;
		
			hasStart = 1;
		}
		// check if at the end of a packet
		else if(data == PACKET_END)
		{
			// if already recieved the start of the packet
			if(hasStart)
			{
				packetBuffer[nextIdx(&writeIdx)] = data;
				// full packet recieved
				packetCount++;
				hasStart = 0;
			}
			else
			{
				// garbage data, set error flag
				comError = 1;
			}
		}
		// ordinary data
		else
		{
			// check if a packet has started
			if(hasStart)
			{
				packetBuffer[nextIdx(&writeIdx)] = data;
			}
			else
			{
				// garbage data, set error flag
				comError = 1;
			}
		}
		
		//
	}

	return;
}



