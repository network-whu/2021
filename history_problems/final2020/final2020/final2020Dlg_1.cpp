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

// final2020Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "final2020.h"
#include "final2020Dlg.h"
#include "afxdialogex.h"

#include "crc.hpp"
#include "crcDivider.h"
#include "utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cfinal2020Dlg dialog

void Cfinal2020Dlg::solveP_6_old ( )
{
	byte* ptrHandle;
	byte	crc_result;
	CString	strMsg;

	ptrHandle	= (byte*) malloc ( 2 );

	memcpy ( ptrHandle, &m_sID, 1 );
	memset ( ptrHandle + 1, 0, 1 );	// set the crc bits to be 0

//	::showBits ( strMsg, ptrHandle, 16 );
//	m_strP6_1	= strMsg + _T ( "\r\ncheck\r\n" );

	m_pDivider->inputBits ( ptrHandle, 12 );

	crc_result	= m_pDivider->calculateCRC ( strMsg );

	m_strP6_1	= strMsg + _T ( "\r\n" );

	*(ptrHandle + 1)	= crc_result << 4;

	::showBits ( strMsg, ptrHandle, 12 );

	m_strP6_1	+= strMsg;

	// flip the first bit
	*ptrHandle	= (*ptrHandle) ^ 128;

	m_pDivider->inputBits ( ptrHandle, 12 );

	crc_result	= m_pDivider->calculateCRC ( strMsg );

	m_strP6_2	= strMsg + _T ( "\r\n" );

	//	::showBits ( strMsg, &crc_result, 8 );
	::showBits ( strMsg, ptrHandle, 12 );

	m_strP6_2	+= strMsg;

	free ( ptrHandle );

	//	//int		iNum_bits_src, iNum_bits_dst;
	//	//int		iCnt_bytes_src;
	//	//int		iNum_bits_remainder;
	//	byte	crc;
	//	//byte	err;
	//	byte *	ptrBits_with_crc;
	//
	////	crc	= crc_check_4 ( (byte*)&m_sID, 1 );
	//
	//	ptrBits_with_crc	= crc_create_4_direct ( (byte*) &m_sID, 1 );
	//
	////	err	= 1027;
	//
	//	// flip the first bit
	//	*ptrBits_with_crc	= (*ptrBits_with_crc) ^ 128;
	//
	//	crc	= crc_check_4_direct ( ptrBits_with_crc, 12 );

	//	if ( ptrBits_with_crc != nullptr )	free ( ptrBits_with_crc );
}


byte* Cfinal2020Dlg::crc_create_4_direct ( const byte* data, int length )
{
	int		bytes, bitsRemainder;
	int		iShift;
	int		iCnt, iTotal;
	byte	crc_reg, crc_4_show;
	byte	seg_hi, seg_lo;
	byte *	ptr;
	byte *	ptrHandle	= nullptr;
	CString	strMsg;
	CString	strSpace;

	if ( data == nullptr )	return	nullptr;
	if ( length == 0 )	return	nullptr;

	iTotal			= length * 8 + 4;
	bytes			= length + 1;	// we create the sending data, so need one more byte
	bitsRemainder	= 4;			// (actually 4 extra bits needed)

	ptrHandle	= (byte*) malloc ( bytes );

	memcpy ( ptrHandle, data, length );
	memset ( ptrHandle + length, 0, 1 );	// set the crc bits to be 0

	// show minuend
	::showBits ( strMsg, ptrHandle, length * 8 + 4 );
	m_strP6_1	= strMsg + _T ( "\r\n" );

	ptr		= ptrHandle;
	seg_hi	= (*ptr) >> 4;
	crc_reg	= seg_hi;	// read in the high-segment of 4 bits
	iCnt	= 4;		// 4 bits has been sent into crc_reg

	strSpace.Empty ( );
	for ( auto i=0; i != length; ++i )
	{
		seg_lo	= (*ptr) & 0x0F;

		iShift	= 5;
		for ( auto j=0; j != 4; ++j )
		{
			// get one more bit
			crc_reg	<<= 1;
			crc_reg	+= (((1 << (3 - j)) & seg_lo) >> (3 - j));

			iCnt++;

			if ( iCnt == iTotal )
			{
				if ( crc_reg & 0x10 )
				{
					showSubtrahend ( m_strP6_1, strSpace );

					crc_reg	^= CRC_POLY_4_10011;	// do substraction

					crc_4_show	= crc_reg << 3;

					showBits_0 ( strMsg, &crc_4_show, 5 );
					m_strP6_1	+= (strSpace + strMsg);

					m_strP6_1	+= _T ( "\r\n" );
				}

				break;
			}
			else if ( crc_reg & 0x10 )
			{	// the high bit is ONE (4 bits altogether)
				// processing XOR substraction

				showSubtrahend ( m_strP6_1, strSpace );

				crc_reg	^= CRC_POLY_4_10011;	// do substraction

				crc_4_show	= crc_reg << 3;

				if ( iCnt < (iTotal-1) )
				{
					showBits_0 ( strMsg, &crc_4_show, 5 );
					m_strP6_1	+= (strSpace + strMsg);

					// add some bits from source
					int	iMove_down_bits	= checkZero_4 ( crc_4_show );
					if ( iMove_down_bits < 4 )
						showBits ( strMsg, ptr, iMove_down_bits + 1, iShift );
					else
						showBits ( strMsg, ptr, 4, iShift );

					m_strP6_1	+= (strMsg + _T ( "\r\n" ));
				}
				else
				{
					showBits_0 ( strMsg, &crc_4_show, 4 );
					m_strP6_1	+= (strSpace + strMsg);

					m_strP6_1	+= _T ( "\r\n" );
				}
			}

			iShift++;
			strSpace	+= _T ( " " );
		}

		if ( iCnt == iTotal )
			break;

		// new seg_hi, the line below should NOT be moved to the above for-chunk
		seg_hi	= (*++ptr) >> 4;

		iShift	= 0;
		for ( auto j=0; j != 4; ++j )
		{
			// add one more bit from source
			crc_reg	<<= 1;
			crc_reg	+= (((1 << (3 - j)) & seg_hi) >> (3 - j));

			iCnt++;

			if ( iCnt == iTotal )
			{
				if ( crc_reg & 0x10 )
				{
					showSubtrahend ( m_strP6_1, strSpace );

					crc_reg	^= CRC_POLY_4_10011;	// do substraction

					crc_4_show	= crc_reg << 3;

					showBits_0 ( strMsg, &crc_4_show, 5 );
					m_strP6_1	+= (strSpace + strMsg);

					// add some bits from source
					//int	iMove_down_bits	= checkZero ( crc_4_show );
					//if ( iMove_down_bits < 4 )
					//	showBits ( strMsg, ptr, iMove_down_bits + 1, iShift );
					//else
					//	showBits ( strMsg, ptr, 4, iShift );

					//m_strP6_1	+= (strMsg + _T ( "\r\n" ));

					m_strP6_1	+= _T ( "\r\n" );
				}

				break;
			}
			else if ( crc_reg & 0x10 )
			{	// the high bit is ONE (4 bits altogether)
				// processing XOR substraction
				showSubtrahend ( m_strP6_1, strSpace );

				crc_reg	^= CRC_POLY_4_10011;	// do substraction

				crc_4_show	= crc_reg << 3;

				if ( iCnt < (iTotal-1) )
				{
					showBits_0 ( strMsg, &crc_4_show, 5 );
					m_strP6_1	+= (strSpace + strMsg);

					// add some bits from source
					int	iMove_down_bits	= checkZero_4 ( crc_4_show );
					if ( iMove_down_bits < 4 )
						showBits ( strMsg, ptr, iMove_down_bits + 1, iShift );
					else
						showBits ( strMsg, ptr, 4, iShift );

					m_strP6_1	+= (strMsg + _T ( "\r\n" ));
				}
				else
				{
					showBits_0 ( strMsg, &crc_4_show, 5 );
					m_strP6_1	+= (strSpace + strMsg);

					// add some bits from source
					int	iMove_down_bits	= 1;
					if ( iMove_down_bits < 4 )
						showBits ( strMsg, ptr, iMove_down_bits, iShift );
					else
						showBits ( strMsg, ptr, 4, iShift );

					m_strP6_1	+= (strMsg + _T ( "\r\n" ));
				}
			}

			iShift++;
			strSpace	+= _T ( " " );
		}

		//		strSpace	+= _T ( "    " );
	}

	*(ptrHandle + length)	= crc_reg << 4;

	showBits ( strMsg, ptrHandle, length * 8 + 4 );

	m_strP6_1	+= strMsg;

	return	ptrHandle;
}

void Cfinal2020Dlg::solveP_7 ( )
{
	int		iPos;
	int		iIndexMax	= -1;
	int		iMaxMatch	= -1;
	bool	bMatch[ 10 ];

	// longest prefix matching
	for ( int i=0; i < 10; i++ )
	{
		iPos	= m_strC.Find ( m_strP7_addr[ i ].Left ( m_iLen[ i ] ) );
		if ( iPos != 0 )
		{
			bMatch[ i ]	= false;
			continue;
		}

		iPos		= m_iLen[ i ];
		bMatch[ i ]	= true;
		if ( iMaxMatch < iPos )
		{
			iMaxMatch	= iPos;
			iIndexMax	= i;
		}
	}

	// show the result
	m_strP7.Empty ( );
	for ( int i=0; i < 10; i++ )
	{
		if ( !bMatch[ i ] )
		{
			m_strP7	+= m_strP7_addr[ i ] + _T ( "\r\n" );
			continue;
		}

		if ( iIndexMax == i )
			m_strP7	+= m_strP7_addr[ i ] + _T ( "<===\r\n" );
		else
			m_strP7	+= m_strP7_addr[ i ] + _T ( "<---\r\n" );
	}

	if ( -1 == iMaxMatch )
		m_strP7	+= m_strP7_addr[ 10 ] + _T ( "<===\r\n" );
	else
		m_strP7	+= m_strP7_addr[ 10 ] + _T ( "\r\n" );
}



