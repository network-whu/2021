/****************************************************************************
* AILab                                                             WHU     *
* Artificial Intelligent toolbox                                  c ^ ^ s   *
*                                                                _   o  _   *
* Copyright(C) 2020                                                \/)\/    *
* Jicheng Hu @ Wuhan University                                   /\/|      *
* All rights reserved.                                               |      *
*                                                                    \      *
*                                                                           *
* This program is free software; you can redistribute it and/or modify      *
* it under the terms of the GNU General Public License as published by      *
* the Free Software Foundation; either version 2 of the License, or         *
* (at your option) any later version.                                       *
*                                                                           *
* This program is distributed in the hope that it will be useful,           *
* but WITHOUT ANY WARRANTY; without even the implied warranty of            *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
* GNU General Public License (http://www.gnu.org/licenses/gpl.txt)          *
* for more details.                                                         *
*                                                                           *
****************************************************************************/

#ifndef _BIT_STREAM_H_
#define	_BIT_STREAM_H_

#include "minuend.h"
class CbitStream
{
public:
	int		getBits ( byte& crc_reg, int numBits );
	int		getBits_1 ( byte& crc_reg, int numBits );	// the high bit of the returning bits is not zero
	void	showBits ( CString& strMsg );

	LPMINUEND	createMinuend ( );
	LPMINUEND	createZeroRemainder ( );
	LPMINUEND	extendDiff ( byte yDiff );	// extend the difference to be a minuend

	int		findLead ( );

	CbitStream ( byte* data, int iCntBits );
	~CbitStream ( );

	inline void	fluctuateBits ( int numBits )
	{
		m_iTotal_used_bits	+= numBits;
		m_iTotal_remain_bits-= numBits;

		m_iUsed_bits		+= numBits;
		m_iAvailable_bits	-= numBits;

		m_iShift	+= numBits;
	}

	inline void fluctuateBytes ( int numBits )
	{
		m_iTotal_used_bits	+= numBits;
		m_iTotal_remain_bits-= numBits;

		// shift to the next byte
		m_yCurrent	= *(++m_ptrCurrent);
		m_iTotal_used_bytes++;
		m_iTotal_remain_bytes--;

		m_iUsed_bits		= 0;
		m_iAvailable_bits	= min ( 8, m_iTotal_remain_bits );

		m_iShift	+= numBits;
	}

	int		m_iShift;

protected:
	byte*	m_ptrHandle;

	byte	m_yCurrent;

	int		m_iTotal_bits;
	int		m_iTotal_bytes;

	int		m_iTotal_used_bits;
	int		m_iTotal_used_bytes;
	int		m_iTotal_remain_bits;	// available bits in the stream
	int		m_iTotal_remain_bytes;	// available bytes in the stream

	int		m_iUsed_bits;		// used bits in the current byte
	int		m_iAvailable_bits;	// available bits in the current byte

	byte*	m_ptrCurrent;		// pointer to the current byte
};

#endif // !_BIT_STREAM_H_
