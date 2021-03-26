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
#include "utils.h"

void showByte ( CString& strEdit, byte data, int iCntBits )
{
	strEdit.Empty ( );

	for ( auto i=7; i > (7 - iCntBits); i-- )
	{
		CString	strTemp;

		strTemp.Format ( _T ( "%d" ), (data >> i) & 0x01 );

		strEdit	+= strTemp;
	}
}

void showByte_s ( CString& strEdit, byte data, int iCntBits, int iShift )
{
	strEdit.Empty ( );

	data	= data << iShift;

	showByte ( strEdit, data, iCntBits );
}

void showByte_0 ( CString& strEdit, byte data, int iCntBits, int iShift )
{
	bool	bHead;
	byte	yBit;

	strEdit.Empty ( );

	bHead	= true;
	for ( auto i=7 - iShift; i > (7 - iCntBits - iShift); i-- )
	{
		CString	strTemp;

//		strTemp.Format ( _T ( "%d" ), (data >> i) & 0x01 );
		yBit	= (data >> i) & 0x01;

		if ( bHead && (0x00 == yBit) )
		{
			strTemp.Format ( _T ( " " ), yBit );
		}
		else
		{
			strTemp.Format ( _T ( "%d" ), yBit );

			bHead	= false;
		}

		strEdit	+= strTemp;
	}
}

void showBits ( CString& strEdit, byte* data, int iCntBits, int iShift )
{
	int		bytes, bitsRemainder;
	int		bytes2show;
	byte	yData;

	const byte* ptr	= data;

	strEdit.Empty ( );

	// how many bytes to be processed
	// if you wanna to modify the following block,
	// be carefull to make sure that you totally understand the implied logical
	bytes			= (iCntBits + 7) >> 3;
	bitsRemainder	= iCntBits & 0x07;
	bytes2show		= bytes;
	if ( bitsRemainder )	bytes2show	-= 1;

	if ( iShift != 0 )
	{
		yData	= *ptr;
		for ( auto i=7 - iShift; i > (7 - bitsRemainder - iShift); i-- )
		{
			CString	strTemp;

			strTemp.Format ( _T ( "%d" ), (yData >> i) & 0x01 );

			strEdit	+= strTemp;
		}

		return;
	}

	// read one byte each time
	for ( auto j=0; j < bytes2show; j++ )
	{

		yData	= *ptr++;

		for ( auto k=7; k >= 0; k-- )
		{
			CString	strTemp;

			strTemp.Format ( _T ( "%d" ), (yData >> k) & 0x01 );

			strEdit	+= strTemp;
		}
	}

	// process the remain bits
	yData	= *ptr;
	for ( auto i=7; i > (7 - bitsRemainder); i-- )
	{
		CString	strTemp;

		strTemp.Format ( _T ( "%d" ), (yData >> i) & 0x01 );

		strEdit	+= strTemp;
	}
}

void showBits_0 ( CString& strEdit, byte* data, int iCntBits )
{
	int				bytes, bitsRemainder;
	byte			yData;
	byte			yBit;
	bool			bHead;
	const byte* ptr	= data;

	strEdit.Empty ( );

	// how many bytes to be processed
	bytes			= (iCntBits + 7) >> 3;
	bitsRemainder	= iCntBits & 0x07;

	// read one byte each time
	bHead	= true;
	for ( auto j=0; j != bytes - 1; ++j )
	{
		yData	= *ptr++;

		for ( auto k=7; k >= 0; k-- )
		{
			CString	strTemp;

			yBit	= (yData >> k) & 0x01;

			if ( bHead && (0x00 == yBit) )
			{
				strTemp.Format ( _T ( " " ), yBit );
			}
			else
			{
				strTemp.Format ( _T ( "%d" ), yBit );

				bHead	= false;
			}

			strEdit	+= strTemp;
		}
	}

	// process the remain bits
	yData	= *ptr;
	for ( auto i=7; i > (7 - bitsRemainder); i-- )
	{
		CString	strTemp;

		yBit	= (yData >> i) & 0x01;

		if ( bHead && (0x00 == yBit) )
		{
			strTemp.Format ( _T ( " " ), yBit );
		}
		else
		{
			strTemp.Format ( _T ( "%d" ), yBit );

			bHead	= false;
		}

		strEdit	+= strTemp;
	}
}

int checkZero_4 ( byte data )
{
	//	if ( data & 128 )	return	0;
	if ( data & 64 )	return	0;
	if ( data & 32 )	return	1;
	if ( data & 16 )	return	2;

	return	3;
}

int checkZero_8 ( byte data )
{
	if ( data & 128 )	return	0;
	if ( data & 64 )	return	1;
	if ( data & 32 )	return	2;
	if ( data & 16 )	return	3;
	if ( data & 8 )		return	4;
	if ( data & 4 )		return	5;
	if ( data & 2 )		return	6;
	if ( data & 1 )		return	7;

	return	8;
}

CString getSpace ( int iShift )
{
	CString	strSpace;

	strSpace.Empty ( );
	for ( auto i=0; i < iShift; i++ )
	{
		strSpace	+= _T ( " " );
	}

	return	strSpace;
}

void showSubtrahend ( CString& strEdit, CString& strSpace )
{
	strEdit.Empty ( );
	strEdit	+= (strSpace + _T ( "10011\r\n" ));
	strEdit	+= (strSpace + _T ( "-------\r\n" ));
}
