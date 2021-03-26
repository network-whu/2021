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
#include "crcDivider.h"
#include "bitStream.h"
#include "utils.h"
#include "crc.hpp"

CcrcDivider::CcrcDivider ( )
{
	m_pBitStream		= nullptr;
	m_pBitStream_prev	= nullptr;

	m_headerMinuend	= nullptr;
	m_tailerMinuend	= nullptr;

	m_pPrevMinuend	= nullptr;
}

CcrcDivider::~CcrcDivider ( )
{
	if ( m_pBitStream_prev != nullptr )	delete	m_pBitStream_prev;
	if ( m_pBitStream != nullptr )	delete	m_pBitStream;

	if ( m_pPrevMinuend )	destroyMinuend ( m_pPrevMinuend );
	if ( m_headerMinuend )	destroyMinuend ( m_headerMinuend );
}

void CcrcDivider::inputBits ( byte* ptrBits, int iCntBits )
{
	if ( m_pBitStream_prev != nullptr )	delete	m_pBitStream_prev;
	if ( m_pPrevMinuend )	destroyMinuend ( m_pPrevMinuend );

	m_pBitStream_prev	= m_pBitStream;
	m_pPrevMinuend		= m_headerMinuend;
	m_headerMinuend		= nullptr;
	m_tailerMinuend		= nullptr;

	m_pBitStream	= new CbitStream ( ptrBits, iCntBits );
}

byte CcrcDivider::calculateCRC ( CString& strMsg )
{
	int		iCnt;
	int		iGain, iMargin;
	byte	crc_reg, crc_4_show;
	CString	strInfo;
	CString	strSpace;

	crc_reg	= 0;
	if ( m_pBitStream == nullptr )
	{
		strMsg	= _T ( "Please first input the bit stream\r\n" );

		return	crc_reg;
	}

	strSpace.Empty ( );

	// show minuend
	m_pBitStream->showBits ( strInfo );
	strMsg	= strInfo + _T ( "\r\n" );

	iCnt	= 5;
	iGain	= m_pBitStream->getBits_1 ( crc_reg, iCnt );

//	int		iBreak	= 0;
	do
	{
		iMargin		= m_pBitStream->m_iShift - 5;
		strSpace	= getSpace ( iMargin );
		showSubtrahend ( strInfo, strSpace );
		strMsg	+= strInfo;

		crc_reg	^= CRC_POLY_4_10011;	// do substraction

		iCnt	= checkZero_8 ( crc_reg );
		if ( 8 == iCnt )
		{
			iCnt	= 5;
			iGain	= m_pBitStream->getBits_1 ( crc_reg, iCnt );
		}
		else
		{
			iCnt	= iCnt - 3;
			crc_reg	<<= iCnt;

			iGain	= m_pBitStream->getBits ( crc_reg, iCnt );
		}

		if ( iCnt == iGain )
			strSpace	+= getSpace ( iGain );
		else
			strSpace	= getSpace ( m_pBitStream->m_iShift - iGain );

		crc_4_show	= crc_reg << (3+(iCnt-iGain));
//		crc_4_show	= crc_reg;
//		::showBits_0 ( strInfo, &crc_4_show, 8 );
		::showByte ( strInfo, crc_4_show, 5 + iGain - iCnt );
		strMsg	+=  strSpace + strInfo + _T ( "\r\n" );

		if ( iCnt > iGain )
			crc_reg >>= (iCnt - iGain);

//		iBreak++;
//		if ( iBreak >2 )	break;
	} while ( iGain == iCnt );

	return	crc_reg;
}

void CcrcDivider::showSubtrahend ( CString& strEdit, CString& strSpace )
{
	strEdit.Empty ( );
	strEdit	+= (strSpace + _T ( "10011\r\n" ));
	strEdit	+= (strSpace + _T ( "-------\r\n" ));
}
