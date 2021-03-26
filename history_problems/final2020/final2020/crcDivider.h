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

#ifndef _CRC_DIVIDER_H_
#define	_CRC_DIVIDER_H_

#include "minuend.h"

class CbitStream;
class CcrcDivider
{
public:
	CbitStream *	m_pBitStream;
	CbitStream *	m_pBitStream_prev;

	byte	calculateCRC ( CString& strMsg );
	bool	calculateCRC ( );
	byte	getResult ( );

	void	showInfo ( CString& strMsg );

	void	inputBits ( byte* ptrBits, int iCntBits );

	CcrcDivider ( );
	~CcrcDivider ( );

protected:
	void	showSubtrahend ( CString& strEdit, CString& strSpace );
	void	destroyMinuend ( LPMINUEND pHeader );
	void	addMinuend ( LPMINUEND pMinuend	);

	LPMINUEND	m_headerMinuend;
	LPMINUEND	m_tailerMinuend;

	LPMINUEND	m_pPrevMinuend;
};


#endif // !_CRC_DIVIDER_H_

