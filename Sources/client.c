
#include "client.h"
#include "sci.h"
#include "derivative.h"

// DEBUG
#include "leds.h"

#define PACKET_START     '<'
#define PACKET_END       '>'
#define PACKET_SEPARATOR '\0'

#define MAX_PACKET_SIZE  20
#define MAX_PACKET_COUNT 5
#define MAX_BUFFER_SIZE  (MAX_PACKET_SIZE * MAX_PACKET_COUNT)

// Error Detection
#define ERROR ( SCI_FE && SCI_NF )

// buffer for packet data
static char packetBuffer[MAX_BUFFER_SIZE];
static int idx = 0;

// Number of valid packets
static unsigned int packetCount = 0;
static unsigned int packetOffsets[MAX_PACKET_COUNT];

unsigned char client_isPacketAvailable(void)
{
	return packetCount > 0;
}

char * client_getNextPacket(void)
{
	//
	return packetBuffer + packetOffsets[0];
}

// Serial Communication Interface Interrupt Handler
interrupt VectorNumber_Vsci sci_handler(void)
{
	static unsigned char hasStart = 0;
	
	const char data = SCIDRL;

	// check for recieved data
	if(SCI_RDRF)
	{
		// check if recieved the start of a packet
		if(data == PACKET_START)
		{
			packetBuffer[idx] = data;
		
			hasStart = 1;
			packetOffsets[packetCount] = idx++;
			
			LED_OFF(LED1_MASK);
		}
		// check if at the end of a packet
		else if(data == PACKET_END)
		{
			// if already recieved the start of the packet
			if(hasStart)
			{
				packetBuffer[idx] = data;
				// full packet recieved
				packetCount++;
				hasStart = 0;
				
				// add a character to separate the packet and shift index one passed the separator
				packetBuffer[idx + 1] = PACKET_SEPARATOR;
				idx += 2;
			}
			else
			{
				// garbage data, do nothing
			}
		}
		// ordinary data
		else
		{
			// check if a packet has started
			if(hasStart)
			{
				packetBuffer[idx++] = data;
			}
			else
			{
				// garbage data, do nothing
				LED_ON(LED1_MASK);
			}
		}
		
		//
	}

	return;
}



