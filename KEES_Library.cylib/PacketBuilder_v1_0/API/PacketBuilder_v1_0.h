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
#ifndef `$INSTANCE_NAME`_PACKET_BUILDER
#define `$INSTANCE_NAME`_PACKET_BUILDER

#include "cytypes.h"
#include "cyfitter.h"
#include <string.h>

#define `$INSTANCE_NAME`_PACKET_TYPE_0 '0'
#define `$INSTANCE_NAME`_PACKET_TYPE_1 '1'
#define `$INSTANCE_NAME`_PACKET_TYPE_2 '2'

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
// returns non zero value when a packet is complete ... example code is provided as comments below the function in the .c file

uint8 `$INSTANCE_NAME`_BuildPacket(uint8 snippet_buffer[], uint8 * snippet_length, uint8 packet_buffer[], uint8 * packet_length);

#endif // `$INSTANCE_NAME`_PACKET_BUILDER

//[] END OF FILE
