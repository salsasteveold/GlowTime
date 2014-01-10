/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "`$INSTANCE_NAME`_PacketBuilder_v1_0.h"

// *** The API assumes packet_length parameter is reset to 0 when the packet has been processed outside of this function.***
//
// returns a non zero value when a complete packet has been received.
//
// Packet structure is as follows:
// byte[0] = packet ID, byte[1] = short form payload / long form payload length, byte[2-258] long form payload data
// packet ID:
//		PACKET_TYPE_0 = response test packet - no arguments passed afterwards, packet immediately completes upon reciept of this packet ID
//		PACKET_TYPE_1 = short packet - the next byte is a single, short form payload. packet completes upon reciept of the second byte
//		PACKET_TYPE_2 = long packet - the next byte indicates the length of the payload, not including the packet ID and length passed (example packet: [PACKET_TYPE_2 , 0x02, 0xFF, 0xAA])
//
// returns non zero value when a packet is complete ... example code is provided as comments below this function.

uint8 `$INSTANCE_NAME`_BuildPacket(uint8 snippet_buffer[], uint8 * snippet_length, uint8 packet_buffer[], uint8 * packet_length)
{
	uint8 packet_complete = 0; // flag to indicate that a complete packet has been constructed
	static uint8 state = 0; // state def: 0 - waiting for packet ID, 1 - waiting for length, 2 - waiting for data
	static uint16 terminal_count = 0; // when packet_length == terminal_count and state is state 2, we are complete
	
	packet_complete = 0; // ensure our flag is reset
	
	while(*snippet_length > 0 && packet_complete == 0) // deal with all bytes received. we either complete a packet, or exhaust our buffer.  note that if a packet is completed, the buffer may not be empty
	{
		// memmove(dest, source, bytes)
		memmove((void *) (packet_buffer + *packet_length), (void *) snippet_buffer, 1); // transfer one byte of the snippet_buffer to the array that will be passed back via the pointer
		(*packet_length)++; // increase the count of the data included in the packet bufer
		memmove((void *) snippet_buffer, (void *) (snippet_buffer + 1), *snippet_length - 1); // move the data down in the snippet_buffer [a,b,c,d] -> [b,c,d,d]
		(*snippet_length)--; // decrease the data in the snippet buffer that we need to process
		
		if(state == 0) // if we are waiting for a packet byte
		{
			if(packet_buffer[0] == `$INSTANCE_NAME`_PACKET_TYPE_0) // first byte in packet buffer (packet ID) is the test packet
			{
				packet_complete = 1; // all done
				state = 0; // reset state (all data has been received)
			}
			else if(packet_buffer[0] == `$INSTANCE_NAME`_PACKET_TYPE_1) // packet ID is the short packet.  We know the terminal count (2 bytes) jump to the "wait for the rest of data" state
			{
				state = 2;
				terminal_count = 2;
			}
			else if(packet_buffer[0] == `$INSTANCE_NAME`_PACKET_TYPE_2) // packet ID is the long form packet.  next byte is the length of bytes to be recieved, set terminal count to a safe value
			{
				state = 1;
				terminal_count = 3;
			}
			else // the byte was not a valid packet byte.  The snippet buffer discards the data and life goes on.
			{
				// no valid packet received.  discard
				(*packet_length) = 0;
			}
		}
		else if(state == 1) // we got the long form packet, grab the length of data to be received, add our packet ID and length to the length and store as the terminal count
		{
			terminal_count = packet_buffer[1] + 2; // set the final packet length (+2 including packet ID and length)
			if(terminal_count == 2)
			{
				state = 0;
				packet_complete = 1;
			}
			else
			{
				state = 2;
			}
		}
		else if(state == 2) // just waiting for data.  when our packet length is equal to our terminal count, flag a complete state
		{
			if(terminal_count == *packet_length)
			{
				packet_complete = 1;
				state = 0;
			}
		}
	}
	
	return packet_complete;
}

//// ***---------------  example code explanation: -------------------------***
////
//// this code uses a USBUART component as the com interface.  The packet structure is as follows:
////
//// a packet 0 (immeditate packet) was used as a sanity / com check.  if a packet 0 is received,
//// the code returns a '!' to indicate the com interface is functioning and confirms the com interface
//// is running as expected.
////
//// a packet 1 (short form packet) was used to send a single operation packet: when packet 1 is received
//// with a parameter of 0x00, write the servo position variables into the PWM.  this allows the servo location variables
//// to be updated seperately, then both servos can be written at the same time
////
//// a packet 2 (long form packet) was used to update two uint16 variables.  first, a long form packet was issued
//// with a length of 3 (left/right indicator byte and 2 bytes for the uint16 = 3 bytes total), then a 'l' (for "left") or a "r' (for "right")
//// was sent, followed by an unit16, sent MSB first.
////
//// the main loop polled to see if any data had come in on the USBUART.  if it had, it dispatched what it received to the packet builder
//// the packet builder was called until it emptied the RX buffer, then an if statement checked to see if a packet had been completed
//// if the packet builder indicated that a packet was complete, another if statement processed the packet, then reset packet_length
//// and packet_complete to indicate the packet had been processed.
////
//// note: I see now that there is a logic error in my code, if a packet had been completed, but the snippet buffer was not empty
//// the code my might miss packets since the packet length would not be reset until the snippet length reached zero
//// and the packet might be complete before the snippet length was actually at zero
////
//// ------------------ begin example code --------------------//
//
//#include <device.h>
//
//uint8 packet_buffer[32];
//uint8 packet_length=0;
//
//uint8 snippet_buffer[8];
//uint8 snippet_length = 0;
//
//char szBuffer[32];
//
//char szLCDBuf[18];
//
//void main()
//{
//	uint8 packet_complete;
//	uint16 Left_Servo = 36000;
//	uint16 Right_Servo = 36000;
//	
//    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
//	
//	PWM_Start();
//	PWM_WriteCompare1(Left_Servo);
//	PWM_WriteCompare2(Right_Servo);
//	
//	CyGlobalIntEnable;
//	
//	USBUART_Start(0, USBUART_5V_OPERATION);
//	while(!USBUART_bGetConfiguration()); /* Wait for Device to enumerate */
//	USBUART_CDC_Init();
//	
//
//    for(;;)
//    {
//		
//		if(USBUART_DataIsReady() > 0)
//		{
//			snippet_length = USBUART_GetCount();
//			
//			USBUART_GetAll(snippet_buffer);
//			
//			while(snippet_length > 0)
//			{
//				packet_complete = Com_BuildPacket(snippet_buffer, &snippet_length, packet_buffer, &packet_length);
//			}
//		}
//		
//		// process any completed packets
//		if(packet_complete)
//		{
//			if(packet_buffer[0] == Com_PACKET_TYPE_0)
//			{
//				// send back the reset reply
//				sprintf(szBuffer,"!");
//				USBUART_PutString(szBuffer);
//				while(USBUART_CDCIsReady() == 0);
//			}
//			else if(packet_buffer[0] == Com_PACKET_TYPE_1) // packet type 1 with parameter of "0" is the "write servo positions" command
//			{
//				if(packet_buffer[1] == 0)
//				{
//					PWM_WriteCompare1(Left_Servo);
//					PWM_WriteCompare2(Right_Servo);
//				}
//			}
//			else if(packet_buffer[0] == Com_PACKET_TYPE_2) // packet type 2 with parameter 'l' or 'r' for left or right indicate a 2 byte uint16 is attached
//			{
//				if(packet_buffer[2] == 'l')
//				{
//					Left_Servo = (((uint16) packet_buffer[3]) << 8) | packet_buffer[4];
//				}
//				else if(packet_buffer[2] == 'r')
//				{
//					Right_Servo = (((uint16) packet_buffer[3]) << 8) | packet_buffer[4];
//				}
//			}
//			
//			packet_length = 0; // make sure to reset the packet length!
//			packet_complete = 0; // and clear the packet complete flag, since we have finished processing the packet
//		}
//    }
//}

/* [] END OF FILE */
