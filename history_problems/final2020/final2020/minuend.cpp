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
#include "minuend.h"
#include "utils.h"
#include "crc.hpp"

byte Cminuend::doSubstraction ( )
{
	return	m_yValue_lo	^ CRC_POLY_4_10011;
}

Cminuend::Cminuend ( )
{
	m_iSpace	= 0;
	m_iCnt		= 0;
	m_pNext		= nullptr;

	m_bRemainder	= false;
}

Cminuend::~Cminuend ( )
{

}

void Cminuend::show ( CString& strMsg )
{
	CString	strSpace;
	CString	strInfo;

	strSpace	= ::getSpace ( m_iSpace );

	strMsg.Empty ( );

	::showByte_s ( strInfo, m_yValue_lo, m_iCnt, 8 - m_iCnt );
	strMsg	+= strSpace + strInfo + _T ( "\r\n" );

	if ( !isRemainder ( ) )
	{
		::showSubtrahend ( strInfo, strSpace );
		strMsg	+= strInfo;
	}
}

void Cminuend::showSubstrahend ( CString& strMsg )
{
	CString	strSpace;

	strSpace	= ::getSpace ( m_iSpace );

	strMsg.Empty ( );

	::showSubtrahend ( strMsg, strSpace );
}

