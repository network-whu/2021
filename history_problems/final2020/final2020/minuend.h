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

#pragma once

typedef	class Cminuend	MINUEND, *LPMINUEND;
class Cminuend
{
public:
	int		m_iSpace;
	int		m_iCnt;		// bits count

	bool	isRemainder ( ) { return m_bRemainder; }
	void	setRemainder ( ) { m_bRemainder = true; }

	void	show ( CString& strMsg );
	void	showSubstrahend ( CString& strMsg );

	byte	doSubstraction ( );

	byte	m_yValue_lo;
	byte	m_yValue_hi;

	LPMINUEND	m_pNext;

	Cminuend ( );
	~Cminuend ( );

protected:
	bool	m_bRemainder;
};

