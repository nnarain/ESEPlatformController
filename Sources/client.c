
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
static unsigned int writeIdx = 0;
static unsigned int readIdx  = 0;;

// Number of valid packets
static unsigned int packetCount = 0;

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
	if(packetBuffer[readIdx] != PACKET_START)
	{
		return 0;
	}
	
	while(packetBuffer[readIdx] != PACKET_END)
	{
		packet[i++] = packetBuffer[nextIdx(&readIdx)];
	}
	
	// insert the packet end character 
	packet[i++] = packetBuffer[nextIdx(&readIdx)];
	packet[i] = '\0';
	
	return 1;
}

static unsigned int nextIdx(unsigned int * idx)
{
	unsigned int ret = *idx;
	*idx = (*idx + 1) % MAX_BUFFER_SIZE;
	return ret;
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
			packetBuffer[nextIdx(&writeIdx)] = data;
		
			hasStart = 1;
			
			LED_OFF(LED1_MASK);
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
				// garbage data, do nothing
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
				// garbage data, do nothing
				LED_ON(LED1_MASK);
			}
		}
		
		//
	}

	return;
}



