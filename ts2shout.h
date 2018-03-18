/* dvb_defaults.h

   Copyright (C) Nicholas Humfrey 2006, Dave Chapman 2002
   reworked to be ts2shout.h
   (C) Carsten Gross <carsten@siski.de> 2018


   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
   Or, point your browser to http://www.gnu.org/copyleft/gpl.html

*/

#ifndef _DVB_SHOUT_H
#define _DVB_SHOUT_H

#include <stdint.h>

#include "mpa_header.h"


// Use by gethostname()
#ifndef HOST_NAME_MAX
#ifdef _POSIX_HOST_NAME_MAX
#define HOST_NAME_MAX	_POSIX_HOST_NAME_MAX
#else
#define HOST_NAME_MAX	(256)
#endif
#endif

#ifndef DOMAIN_NAME_MAX
#define DOMAIN_NAME_MAX	(1024)
#endif

// The size of MPEG2 TS packets
#define TS_PACKET_SIZE			188

// There seems to be a limit of 32 simultaneous filters in the driver
#define MAX_CHANNEL_COUNT		32

// Maximum allowed PID value
#define MAX_PID_COUNT			8192

// Standard string buffer size
#define STR_BUF_SIZE			1025

// Maximum allowed PID value
#define RTP_MPEG_AUDIO_PT		14

/* Shoutcast Interval to next metadata */
#define SHOUTCAST_METAINT		8192

/*
	Macros for accessing MPEG-2 TS packet headers
*/
#define TS_PACKET_SYNC_BYTE(b)		(b[0])
#define TS_PACKET_TRANS_ERROR(b)	((b[1]&0x80)>>7)
#define TS_PACKET_PAYLOAD_START(b)	((b[1]&0x40)>>6)
#define TS_PACKET_PRIORITY(b)		((b[1]&0x20)>>4)
#define TS_PACKET_PID(b)			(((b[1]&0x1F)<<8) | b[2])

#define TS_PACKET_SCRAMBLING(b)		((b[3]&0xC0)>>6)
#define TS_PACKET_ADAPTATION(b)		((b[3]&0x30)>>4)
#define TS_PACKET_CONT_COUNT(b)		((b[3]&0x0F)>>0)
#define TS_PACKET_ADAPT_LEN(b)		(b[4])

/* 
	Macros for access MPEG-2 EIT packets
	http://www.etsi.org/deliver/etsi_en/300400_300499/300468/01.14.01_60/en_300468v011401p.pdf 
	Page 28
*/
#define EIT_PACKET_TABLEID(b)		(b[0])
#define EIT_SECTION_LENGTH(b) (uint16_t)(((b[1] & 0x0f)<<8)|b[2])
#define EIT_SERVICE_ID(b)			(uint32_t)((b[3]<<8) | b[4])
#define EIT_SECTION_NUMBER(b)		(b[6])
#define EIT_LAST_SECTION_NUMBER(b)	(b[7])
#define EIT_TRANSPORT_STREAM_ID(b)	(uint32_t)(b[8]<<8 | b[9])
/* original network +2 Byte */
#define EIT_PACKET_LAST_TABLEID(b)		(b[13])
#define EIT_PACKET_EVENTSP(b)		(b + 14)

/* Macros for accessing the Eventinformation */
#define EIT_EVENT_EVENTID(b)		(uint32_t)((b[0]<<8) | ( b[1]))
#define EIT_EVENT_STARTTIME_TIME(b)	(uint32_t)(b[4]<<16 | b[5]<<8 | b[6])
#define EIT_EVENT_STARTTIME_DATE(b) (uint32_t)(b[2]<<8 | b[3])
#define EIT_EVENT_DURATION(b)			(uint32_t)(b[7]<<16 | b[8]<<8 | b[9])
#define EIT_EVENT_RUNNING_STATUS(b)	((b[10] & 0xe0)>>5)
#define EIT_EVENT_LOOPLENGTH(b)		(uint32_t)(b[10]&0x0f<<16 | b[11]<<8 | b[12])
#define EIT_EVENT_DESCRIPTORP(b)	(b + 12)

#define EIT_DESCRIPTOR_TAG(b)		(b[0]) 
#define EIT_DESCRIPTOR_LENGTH(b)	(b[1])
/* #define EIT_DESCRIPTOR_STREAM_CONTENT(b)	(b[2] & 0xf)
#define EIT_DESCRIPTOR_COMPONENT_TYPE(b) (b[3])
#define EIT_DESCRIPTOR_COMPONENT_TAG(b) (b[4])
*/
/* 3 Byte Language code */
#define EIT_SIZE_DESCRIPTOR_HEADER	6
#define EIT_DESCRIPTOR_LANG(b)		(b + 2)
#define EIT_NAME_LENGTH(b)			(b[5])
#define EIT_NAME_CONTENT(b)			(b + 6)

/* Macros for accessing PAT frames */

#define PAT_TABLE_ID(b) (b[0])
#define PAT_SECTION_LENGTH(b) (uint16_t)((b[1] & 0xf)<<8 | b[2])
#define PAT_TRANSPORT_STREAM_ID(b) (uint16_t)(b[3]<<8 | b[4])
#define PAT_SECTION_NUMBER(b) (b[6])
#define PAT_LAST_SECTION_NUMBER(b) (b[7])
#define PAT_PROGRAMME_START(b) (b + 8) 
#define PAT_PROGRAMME_PMT(b) ((uint16_t)( (b[2]&0x1f) <<8 | b[3]))

/* Macros for accessing PMT frames */
#define PMT_TABLE_ID(b) (b[0])
#define PMT_SECTION_LENGTH(b) (uint16_t)((b[1] & 0xf)<<8 | b[2])
#define PMT_PROGRAM_NUMBER(b) (uint16_t)(b[3]<<8 | b[4])
#define PMT_SECTION_NUMBER(b) (b[6])
#define PMT_LAST_SECTION_NUMBER(b) (b[7])
#define PMT_PCR_PID(b) ((uint16_t)( (b[8]&0x1f) <<8 | b[9]))
#define PMT_PROGRAMME_INFO_LENGTH(b) ((uint16_t)( (b[10]&0x0f) <<8 | b[11]))
#define PMT_DESCRIPTOR(b) (b + 12)
#define PMT_STREAM_TYPE(b) (b[0])
#define PMT_PID(b) ((uint16_t)((b[1] & 0x1f)<<8 | b[2]))
#define PMT_INFO_LENGTH(b) ((uint16_t)((b[3] & 0x0f)<<8 | b[4]))

/* Macros for accessing SDT frames */
/* Everything before can be reused from PMT macros */
#define SDT_ORIGINAL_NETWORK_ID(b) (uint16_t)(b[8]<<8 | b[9])
/* b[11] future use */
#define SDT_FIRST_DESCRIPTOR(b) (b + 11)
#define SDT_DESCRIPTOR_SERVICE_ID(b)	(uint16_t)(b[0]<<8 | b[1])
#define SDT_DESCRIPTOR_RUNNING(b)       ((b[3] & 0xc0)>>5)
#define SDT_DESCRIPTOR_LOOP_LENGTH(b)   (uint16_t)((b[3] & 0x0f)<<8 | b[4])
#define SDT_DESCRIPTOR_CONTENT(b)		(b + 5)
/* Descriptor of the SDT */
/* DC = DESCRIPTOR_CONTENT */
#define SDT_DC_TAG(b) (b[0])
#define SDT_DC_LENGTH(b) (b[1])
#define SDT_DC_SERVICE_TYPE(b) (b[2])
#define SDT_DC_PROVIDER_NAME_LENGTH(b) (b[3])
#define SDT_DC_PROVIDER_NAME(b) (b+4)

/* Macros for accessing MPEG-2 PES packet headers */
#define PES_PACKET_SYNC_BYTE1(b)	(b[0])
#define PES_PACKET_SYNC_BYTE2(b)	(b[1])
#define PES_PACKET_SYNC_BYTE3(b)	(b[2])
#define PES_PACKET_STREAM_ID(b)		(b[3])
#define PES_PACKET_LEN(b)			((b[4] << 8) | b[5])

#define PES_PACKET_SYNC_CODE(b)		((b[6] & 0xC0) >> 6)
#define PES_PACKET_SCRAMBLED(b)		((b[6] & 0x30) >> 4)
#define PES_PACKET_PRIORITY(b)		((b[6] & 0x08) >> 3)
#define PES_PACKET_ALIGNMENT(b)		((b[6] & 0x04) >> 2)
#define PES_PACKET_COPYRIGHT(b)		((b[6] & 0x02) >> 1)
#define PES_PACKET_ORIGINAL(b)		((b[6] & 0x01) >> 0)

#define PES_PACKET_PTS_DTS(b)		((b[7] & 0xC0) >> 6)
#define PES_PACKET_ESCR(b)			((b[7] & 0x20) >> 5)
#define PES_PACKET_ESR(b)			((b[7] & 0x10) >> 4)
#define PES_PACKET_DSM_TRICK(b)		((b[7] & 0x8) >> 3)
#define PES_PACKET_ADD_COPY(b)		((b[7] & 0x4) >> 2)
#define PES_PACKET_CRC(b)			((b[7] & 0x2) >> 1)
#define PES_PACKET_EXTEN(b)			((b[7] & 0x1) >> 0)
#define PES_PACKET_HEAD_LEN(b)		(b[8])

#define PES_PACKET_PTS(b)		((uint32_t)((b[9] & 0x0E) << 29) | \
					 (uint32_t)(b[10] << 22) | \
					 (uint32_t)((b[11] & 0xFE) << 14) | \
					 (uint32_t)(b[12] << 7) | \
					 (uint32_t)(b[13] >> 1))

#define PES_PACKET_DTS(b)		((uint32_t)((b[14] & 0x0E) << 29) | \
					 (uint32_t)(b[15] << 22) | \
					 (uint32_t)((b[16] & 0xFE) << 14) | \
					 (uint32_t)(b[17] << 7) | \
					 (uint32_t)(b[18] >> 1))

#define FOREACH_CHANNEL_TYPE(CHANNEL_TYPE) \
        CHANNEL_TYPE(CHANNEL_TYPE_PAT)  \
        CHANNEL_TYPE(CHANNEL_TYPE_SDT)  \
        CHANNEL_TYPE(CHANNEL_TYPE_EIT)  \
        CHANNEL_TYPE(CHANNEL_TYPE_PMT)  \
		CHANNEL_TYPE(CHANNEL_TYPE_PAYLOAD) \

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,


typedef enum {
	FOREACH_CHANNEL_TYPE(GENERATE_ENUM)
} enum_channel_type;

/* Structure containing single channel */
typedef struct dvbshout_channel_s {

	int num;				// channel number
	int fd;					// demux file descriptor
	int pid;				// Packet Identifier of audio stream

	enum_channel_type channel_type;	// Channel Type (MPEG / PMT / whatever) 
	
	// Metadata about the channel
	char name[STR_BUF_SIZE];	// channel name
	char genre[STR_BUF_SIZE];	// genre
	char description[STR_BUF_SIZE];	// description
	char url[STR_BUF_SIZE];		// Informational URL
	char title[STR_BUF_SIZE];   // Current title information (for shoutcast StreamTitle)

	int continuity_count;	// TS packet continuity counter
	int pes_stream_id;		// PES stream ID
	size_t pes_remaining;	// Number of bytes remaining in current PES packet
	unsigned long pes_ts;	// Timestamp for current PES packet
	
	char is_public;				// announce existance?
	char mount[STR_BUF_SIZE];	// mount point

	mpa_header_t mpah;		// Parsed MPEG audio header
	int synced;				// Have MPA sync?
	
	uint32_t  bytes_written_nt; // Bytes written (count the 8192 Bytes to next StreamTitle inside shoutcast)
	uint8_t * buf;			// MPEG Audio Buffer (with 4 nulls bytes)
	uint8_t * buf_ptr;		// Pointer to start of audio data
	uint32_t buf_size;		// Usable size of MPEG Audio Buffer
	uint32_t buf_used;		// Amount of buffer used

	int rtp_mtu;					// Maxium Transmission Unit (of payload)
	unsigned long rtp_ts;			// RTP Session Timestamp
	
	int frames_per_packet;			// Number of MPEG audio frames per packet
	int payload_size;				// Size of the payload
	

} dvbshout_channel_t;

/* crc32.c */
uint32_t crc32 (unsigned char *data, int len); 

/* In dvbshout.c */
void output_logmessage(const char *fmt, ... ); 
extern int channel_count;
extern dvbshout_channel_t *channel_map[MAX_PID_COUNT];
extern dvbshout_channel_t *channels[MAX_CHANNEL_COUNT];

/* In pes.c */
unsigned char* parse_pes( unsigned char* buf, int size, size_t *payload_size, dvbshout_channel_t *chan);

/* In parse_config.c */
void init_structures();
int add_channel(enum_channel_type channel_type, int pid); 


#endif