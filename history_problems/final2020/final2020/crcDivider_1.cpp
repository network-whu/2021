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

bool CcrcDivider::calculateCRC ( )
{
	LPMINUEND	pMinuend;
	byte		yDiff;

	if ( m_pBitStream == nullptr )	return	false;

	if ( m_pPrevMinuend )	destroyMinuend ( m_pPrevMinuend );

	m_pPrevMinuend	= m_headerMinuend;
	m_headerMinuend	= nullptr;
	m_tailerMinuend	= nullptr;

	pMinuend	= m_pBitStream->createMinuend ( );
	while ( pMinuend )
	{
		addMinuend ( pMinuend );

		if ( pMinuend->isRemainder( ) )	break;

		yDiff	= pMinuend->doSubstraction ( );

		if ( 0 == yDiff )
		{
			pMinuend	= m_pBitStream->createMinuend ( );
			continue;
		}

		pMinuend	= m_pBitStream->extendDiff ( yDiff );
	}

	return	true;
}

void CcrcDivider::addMinuend ( LPMINUEND pMinuend )
{
	pMinuend->m_pNext	= nullptr;
	if ( nullptr == m_tailerMinuend )
	{
		m_headerMinuend	= pMinuend;
		m_tailerMinuend	= pMinuend;

		return;
	}

	m_tailerMinuend->m_pNext	= pMinuend;
	m_tailerMinuend				= pMinuend;
}

void CcrcDivider::destroyMinuend ( LPMINUEND pHeader )
{
	LPMINUEND	pMinuend;

	while ( pHeader )
	{
		pMinuend	= pHeader->m_pNext;

		delete	pHeader;

		pHeader	= pMinuend;
	}
}

void CcrcDivider::showInfo ( CString& strMsg )
{
	LPMINUEND	pMinuend;
	CString		strInfo;

	if ( nullptr == m_headerMinuend )	return;

	strMsg.Empty ( );

	// show minuend
	m_pBitStream->showBits ( strInfo );
	strMsg	= strInfo + _T ( "\r\n" );

	pMinuend	= m_headerMinuend;
	pMinuend->showSubstrahend ( strInfo );
//	pMinuend->show ( strInfo );
	strMsg	+= strInfo;

	pMinuend	= pMinuend->m_pNext;
	while ( pMinuend )
	{
		pMinuend->show ( strInfo );
		strMsg	+= strInfo;

		pMinuend	= pMinuend->m_pNext;
	}
}

byte CcrcDivider::getResult ( )
{
	return	m_tailerMinuend->m_yValue_lo;
}
