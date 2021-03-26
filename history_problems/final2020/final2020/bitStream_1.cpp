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

LPMINUEND CbitStream::extendDiff ( byte yDiff )
{
	int			iSpace, iCnt;
	int			iDesiredBits, iNumBits, iBitsGot;
	byte		yValue		= 0;
	LPMINUEND	pMinuend	= nullptr;

	iCnt		= checkZero_8 ( yDiff );
	iNumBits	= 8 - iCnt;
	iSpace		= m_iTotal_used_bits - iNumBits;
	iDesiredBits= 5 - iNumBits;	//iCnt - 3;	// 5 - (8 - iCnt);

	pMinuend	= new MINUEND;
	pMinuend->m_iSpace	= iSpace;

	iBitsGot	= getBits ( yValue, iDesiredBits );

	if ( iBitsGot < iDesiredBits )
	{
		yValue	>>= (iDesiredBits - iBitsGot);
		pMinuend->setRemainder ( );

		pMinuend->m_yValue_lo	= (yDiff << iBitsGot) + yValue;
		pMinuend->m_iCnt		= iNumBits + iBitsGot;

		return	pMinuend;
	}

	pMinuend->m_yValue_lo	= yValue + (yDiff << iBitsGot);
	pMinuend->m_iCnt		= 5;

	return	pMinuend;
}

LPMINUEND CbitStream::createMinuend ( )
{
	int			iLead;	// position of the lead guy
	int			iCnt;
	byte		yValue		= 0;
	LPMINUEND	pMinuend	= nullptr;

	iLead	= findLead ( );
	if ( -1 == iLead )
	{
		return	createZeroRemainder ( );
	}

	pMinuend	= new MINUEND;

	pMinuend->m_iSpace	= iLead - 1;

	// set the remained 4 bits
	iCnt	= getBits ( yValue, 4 );
	if ( iCnt < 4 )
	{
		yValue	>>= (4 - iCnt);

		pMinuend->setRemainder ( );

		pMinuend->m_yValue_lo	= (1 << iCnt) + yValue;
		pMinuend->m_iCnt		= 1 + iCnt;

		return	pMinuend;
	}

	pMinuend->m_yValue_lo	= 16 + yValue;	// set the highest bit
	pMinuend->m_iCnt		= 5;

	return	pMinuend;
}

LPMINUEND CbitStream::createZeroRemainder ( )
{
	LPMINUEND	pMinuend	= nullptr;

	pMinuend	= new MINUEND;

	pMinuend->m_iSpace		= m_iTotal_bits - 1;
	pMinuend->m_yValue_lo	= 0;
	pMinuend->m_yValue_hi	= 0;
	pMinuend->m_iCnt		= 1;
	pMinuend->setRemainder ( );

	return	pMinuend;
}
