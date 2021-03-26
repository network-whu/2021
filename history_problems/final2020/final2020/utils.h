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

void	showByte ( CString& strEdit, byte data, int iCntBits );
void	showByte_s ( CString& strEdit, byte data, int iCntBits, int iShift=0 );
void	showByte_0 ( CString& strEdit, byte data, int iCntBits, int iShift=0 );
void	showBits ( CString& strEdit, byte* data, int iCntBits, int iShift=0 );
void	showBits_0 ( CString& strEdit, byte* data, int iCntBits );
void	showSubtrahend ( CString& strEdit, CString& strSpace );
int		checkZero_4 ( byte data );
int		checkZero_8 ( byte data );
CString	getSpace ( int iShift );


