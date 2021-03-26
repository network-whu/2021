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

#include "pch.h"
#include "bitStream.h"
#include "utils.h"

CbitStream::CbitStream ( byte* data, int iCntBits )
{
	assert ( data != nullptr );

	m_iTotal_bits		= iCntBits;
	m_iTotal_bytes		= (iCntBits + 7) >> 3;

	m_iTotal_used_bits	= 0;
	m_iTotal_used_bytes	= 0;

	m_iTotal_remain_bits	= m_iTotal_bits;
	m_iTotal_remain_bytes	= m_iTotal_bytes;

	m_ptrHandle	= (byte*) malloc ( m_iTotal_bytes );

	memcpy ( m_ptrHandle, data, m_iTotal_bytes );

	m_ptrCurrent	= m_ptrHandle;

	m_yCurrent			= *m_ptrCurrent;
	m_iUsed_bits		= 0;
	m_iAvailable_bits	= 8;

	m_iShift	= 0;
}

CbitStream::~CbitStream ( )
{
	free ( m_ptrHandle );
}

int CbitStream::getBits ( byte& crc_reg, int numBits )
{
	byte	yCur;
	int		iAvailable_bits;

	if ( 0 == m_iTotal_remain_bits )	return	0;

	assert ( numBits < 8 );

	yCur	= m_yCurrent << m_iUsed_bits;

	// exactly done with the current byte
	if ( m_iAvailable_bits == numBits )
	{
		yCur >>= (8 - numBits);

		crc_reg	+= yCur;

		fluctuateBytes ( numBits );

		return	numBits;
	}

	// this byte is enough
	if ( m_iAvailable_bits > numBits )
	{
		yCur >>= (8 - numBits);

		crc_reg	+= yCur;

		fluctuateBits ( numBits );

		return	numBits;
	}

	// all the available bits from the current byte is not enough
	//	1) take all the available_bits in this byte
	yCur >>= (8 - m_iAvailable_bits);
	yCur <<= (numBits - m_iAvailable_bits);

	crc_reg	+= yCur;

	iAvailable_bits	= m_iAvailable_bits;	// m_iAvailable_bits will be modified in the following line
	fluctuateBytes ( m_iAvailable_bits );

	//	2) take the remain bits from the next byte
	return	iAvailable_bits + getBits ( crc_reg, numBits - iAvailable_bits );

	//if ( m_iTotal_remain_bits < numBits )
	//{
	//	if ( m_iAvailable_bits == m_iTotal_remain_bits )
	//	{
	//		yCur >>= (8 - m_iAvailable_bits);

	//		crc_reg	+= yCur;

	//		iAvailable_bits	= m_iAvailable_bits;	// m_iAvailable_bits will be modified in the following line
	//		fluctuateBytes ( m_iAvailable_bits );

	//		return	iAvailable_bits;
	//	}

	//	return	m_iTotal_remain_bits;
	//}

	//// not enough in the current byte
	//// get all the available bits in this byte
	//iAvailable_bits	= m_iAvailable_bits;

	//yCur >>= (8 -  numBits );

	//crc_reg	+= yCur;

	//fluctuateBytes ( iAvailable_bits );

	//// and get the remain bits of numBits - iAvailable_bits from the next byte
	//return	iAvailable_bits + getBits ( crc_reg, numBits - iAvailable_bits );
}

int CbitStream::getBits_1 ( byte& crc_reg, int numBits )
{
	byte	yCur;
	int		iCnt;

	yCur	= m_yCurrent << m_iUsed_bits;

	// skip all the zero bits from the current position
	iCnt	= ::checkZero_8 ( yCur );

	// there is a bug here!
	// if almost all the input bits is zero only the last couples are not
	// then available_bits may be less than iCnt
//	assert ( iCnt <= m_iAvailable_bits );
	if ( iCnt > m_iAvailable_bits )
	{
		// the remain bits are zero
		fluctuateBits ( m_iAvailable_bits );

		if ( 0 == m_iTotal_remain_bits )
		{
			return	0;
		}

		fluctuateBytes ( 0 );

		return	getBits_1 ( crc_reg, numBits );
	}

	fluctuateBits ( iCnt );

	// if all the available bits are 0
	if ( 0 == m_iAvailable_bits )
	{
		// no more left
		if ( 0 == m_iTotal_remain_bits )	return	0;

		fluctuateBytes ( 0 );

		return	getBits_1 ( crc_reg, numBits );
	}

	// get the available bits
	return	getBits ( crc_reg, numBits );
}

void CbitStream::showBits ( CString& strMsg )
{
	::showBits ( strMsg, m_ptrHandle, m_iTotal_bits );
}

int CbitStream::findLead ( )
{
	byte	yCur;
	int		iCnt;

	// if not found
	if ( m_iTotal_remain_bits <= 0 )	return	-1;

	yCur	= m_yCurrent << m_iUsed_bits;

	// there is no ONE remained in this byte
	if ( 0 == yCur )
	{
		// the remain bits are zero in the current byte
		fluctuateBytes ( m_iAvailable_bits );	// shift to the next byte

		return	findLead ( );
	}

	// the desired one is in this byte
	iCnt	= ::checkZero_8 ( yCur );
	assert ( iCnt < m_iAvailable_bits );

	fluctuateBits ( iCnt + 1 );	// the found lead can no longer be accessible

	return	m_iTotal_used_bits;
}
