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



Cfinal2020Dlg::Cfinal2020Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FINAL2020_DIALOG, pParent)
	, m_strID ( _T ( "2017302580010" ) )
	, m_strC ( _T ( "" ) )
	, m_strCheckSum ( _T ( "" ) )
	, m_iC_1 ( 0 )
	, m_iC_2 ( 0 )
	, m_fTime_1 ( 0 )
	, m_fTime_2 ( 0 )
	, m_strP_3 ( _T ( "" ) )
	, m_iSize_last_frag ( 0 )
	, m_i7_C_1 ( 0 )
	, m_i11_C_1 ( 0 )
	, m_strP6_1 ( _T ( "" ) )
	, m_strP6_2 ( _T ( "" ) )
	, m_strP7 ( _T ( "" ) )
	, m_strP8 ( _T ( "" ) )
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_strP7_addr[ 0 ]	= _T ( "1101 1001 1010 0***   0" );
	m_strP7_addr[ 1 ]	= _T ( "1101 1001 1010 010*   1" );
	m_strP7_addr[ 2 ]	= _T ( "1101 1001 1010 01**   2" );
	m_strP7_addr[ 3 ]	= _T ( "1101 1001 1010 1***   3" );
	m_strP7_addr[ 4 ]	= _T ( "1101 1001 1010 110*   4" );
	m_strP7_addr[ 5 ]	= _T ( "1101 1001 1010 11**   5" );
	m_strP7_addr[ 6 ]	= _T ( "1101 1001 1011 0***   6" );
	m_strP7_addr[ 7 ]	= _T ( "1101 1001 1011 010*   7" );
	m_strP7_addr[ 8 ]	= _T ( "1101 1001 1011 01**   8" );
	m_strP7_addr[ 9 ]	= _T ( "1101 1001 1011 1***   9" );
	m_strP7_addr[ 10 ]	= _T ( "otherwise            10" );

	m_iLen[ 0 ]	= 16;
	m_iLen[ 1 ]	= 18;
	m_iLen[ 2 ]	= 17;
	m_iLen[ 3 ]	= 16;
	m_iLen[ 4 ]	= 18;
	m_iLen[ 5 ]	= 17;
	m_iLen[ 6 ]	= 16;
	m_iLen[ 7 ]	= 18;
	m_iLen[ 8 ]	= 17;
	m_iLen[ 9 ]	= 16;

	for ( int i=0; i < 11; i++ )
	{
		m_strP7	+= m_strP7_addr[ i ] + _T("\r\n");
	}

	m_pDivider	= new CcrcDivider;
}

void Cfinal2020Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange ( pDX );
	DDX_Text ( pDX, IDC_EDIT_STUDENT_ID, m_strID );
	DDX_Control ( pDX, IDC_EDIT_STUDENT_ID, m_edStudentID );
	DDX_Text ( pDX, IDC_EDIT_C, m_strC );
	DDX_Text ( pDX, IDC_EDIT_C_3, m_strC );
	DDX_Text ( pDX, IDC_EDIT_CHECKSUM, m_strCheckSum );
	DDX_Text ( pDX, IDC_EDIT_C_1, m_iC_1 );
	DDV_MinMaxInt ( pDX, m_iC_1, 0, 255 );
	DDX_Text ( pDX, IDC_EDIT_C_2, m_iC_2 );
	DDV_MinMaxInt ( pDX, m_iC_2, 0, 255 );
	DDX_Text ( pDX, IDC_EDIT_TIME_1, m_fTime_1 );
	DDX_Text ( pDX, IDC_EDIT_TIME_2, m_fTime_2 );
	DDX_Text ( pDX, IDC_EDIT_P_3, m_strP_3 );
	DDX_Text ( pDX, IDC_EDIT_SIZE_LAST, m_iSize_last_frag );
	DDX_Text ( pDX, IDC_EDIT_7_C_1_0, m_i7_C_1 );
	DDX_Text ( pDX, IDC_EDIT_7_C_1_1, m_i7_C_1 );
	DDX_Text ( pDX, IDC_EDIT_11_C_1, m_i11_C_1 );
	DDX_Text ( pDX, IDC_EDIT_P6_1, m_strP6_1 );
	DDX_Text ( pDX, IDC_EDIT_P6_2, m_strP6_2 );
	DDX_Text ( pDX, IDC_EDIT_P7, m_strP7 );
	DDX_Text ( pDX, IDC_EDIT_P8, m_strP8 );
}

BEGIN_MESSAGE_MAP(Cfinal2020Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_UPDATE ( IDC_EDIT_STUDENT_ID, &Cfinal2020Dlg::OnEnUpdateEditStudentId )
	ON_EN_KILLFOCUS ( IDC_EDIT_STUDENT_ID, &Cfinal2020Dlg::OnEnKillfocusEditStudentId )
END_MESSAGE_MAP()


// Cfinal2020Dlg message handlers

BOOL Cfinal2020Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Cfinal2020Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Cfinal2020Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cfinal2020Dlg::OnEnUpdateEditStudentId ( )
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.

	// TODO:  Add your control notification handler code here
}


void Cfinal2020Dlg::OnEnKillfocusEditStudentId ( )
{
	UpdateData ( );

	calculate_C ( );
	calculate_Checksum ( );
	solveP_2 ( );
	solveP_3 ( );
	solveP_4 ( );
	solveP_5 ( );
	solveP_6 ( );
	solveP_7 ( );
	solveP_8 ( );
	solveP_9 ( );

	UpdateData ( FALSE );
}

void Cfinal2020Dlg::calculate_C ( )
{
	int				i, k;
	int				iID;
	unsigned short	sID;
	unsigned short	sFull, sHalf;
	unsigned short	sRemainder[ 16 ];
	CString			strID;

	strID	= m_strID.Right ( 6 );

	iID	= _ttoi ( strID );

	sID	= (unsigned short) iID;

	m_sID	= sID;

	m_iC_1	= LOBYTE ( sID );
	m_iC_2	= HIBYTE ( sID );

	k		= 0;
	sFull	= sID;
	while ( sFull != 0 )
	{
		sHalf	= sFull / 2;

		sRemainder [ k++ ]	= sFull - sHalf * 2;

		sFull	= sFull / 2;
	}

	m_strC.Empty ( );
	for ( i=k - 1; i >= 0; i-- )
	{
		CString	strTemp;

		strTemp.Format ( _T ( "%d" ), sRemainder[ i ] );

		m_strC	+= strTemp;

		if ( 0 == (i % 4) )
			m_strC	+= _T ( " " );
	}
}

void Cfinal2020Dlg::calculate_Checksum ( )
{
	int				i, k;
	int				iID;
	unsigned short	sID;
	unsigned short	sD;
	unsigned short	sFull, sHalf;
	unsigned short	sRemainder[ 16 ];
	CString			strID;

	sD	= 57345;	// 1110 0000 0000 0001

	strID	= m_strID.Right ( 6 );

	iID	= _ttoi ( strID );

	sID	= (unsigned short) iID;

	// initialize the checksum
	m_iChecksum	= sID;

	m_iChecksum	+= sD;

	// wrap around
	if ( m_iChecksum >> 16 )
		m_iChecksum	= (m_iChecksum & 0xffff) + (m_iChecksum >> 16);

	memset ( sRemainder, 0, sizeof ( sRemainder ) );

	k		= 0;
	sFull	= (unsigned short) m_iChecksum;
	sFull	= ~sFull;
	while ( sFull != 0 )
	{
		sHalf	= sFull / 2;

		sRemainder[ k++ ]	= sFull - sHalf * 2;

		sFull	= sFull / 2;
	}

	m_strCheckSum.Empty ( );
	for ( i=15; i >= 0; i-- )
	{
		CString	strTemp;

		strTemp.Format ( _T ( "%d" ), sRemainder[ i ] );

		m_strCheckSum	+= strTemp;

		if ( 0 == (i % 4) )
			m_strCheckSum	+= _T ( " " );
	}
}

void Cfinal2020Dlg::solveP_2 ( )
{
	m_fTime_1	= (float)(512 * m_iC_1 / 10000.);
	m_fTime_2	= (float) (512 * m_iC_2 / 10000.);
}

void Cfinal2020Dlg::solveP_3 ( )
{
	m_strP_3	= _T ( "cs.whu.edu.cn/student ? " );

	m_strP_3	+= m_strID;
}

void Cfinal2020Dlg::solveP_4 ( )
{
	m_iSize_last_frag	= 360 + m_iC_1;
}

void Cfinal2020Dlg::solveP_5 ( )
{
	m_i7_C_1	= 7 + m_iC_1;
	m_i11_C_1	= 11 + m_iC_1;
}

void Cfinal2020Dlg::solveP_6 ( )
{
	byte *	ptrHandle;
	byte	crc_result;
	CString	strMsg;

	ptrHandle	= (byte*) malloc ( 2 );

	memcpy ( ptrHandle, &m_sID, 1 );
	memset ( ptrHandle + 1, 0, 1 );	// set the crc bits to be 0

//	::showBits ( strMsg, ptrHandle, 12 );
//	m_strP6_1	= strMsg + _T ( "\r\ncheck\r\n" );

	m_pDivider->inputBits ( ptrHandle, 12 );

	if ( !m_pDivider->calculateCRC ( ) )	return;

	// show the procedure info
	m_pDivider->showInfo ( strMsg );
	m_strP6_1	= strMsg;

	// get crc result
	crc_result	= m_pDivider->getResult ( );

	// show the result
	*(ptrHandle + 1)	= crc_result << 4;
	::showBits ( strMsg, ptrHandle, 12 );
	m_strP6_1	+= strMsg;

	// flip the first bit
	*ptrHandle	= (*ptrHandle) ^ 128;

	// calculating the crc
	m_pDivider->inputBits ( ptrHandle, 12 );
	if ( !m_pDivider->calculateCRC ( ) )	return;

	// show the procedure info
	m_pDivider->showInfo ( strMsg );
	m_strP6_2	= strMsg;

	// done
	free ( ptrHandle );

	return;

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

void Cfinal2020Dlg::solveP_8 ( )
{
	CString			strID;
	int				iID;
	unsigned short	sID;

	strID	= m_strID.Right ( 6 );

	iID	= _ttoi ( strID );

	sID	= (unsigned short) iID;

	m_strP8.Format ( _T ( "M3 = %X" ), sID );
}

void Cfinal2020Dlg::solveP_9 ( )
{
}


byte Cfinal2020Dlg::crc_check_4 ( const byte* data, int length )
{
	byte		crc_reg;
	const byte*	ptr;

	constexpr auto	crc_table	= tag_crc_4_table<16> ( );

	static_assert(!crc_table.arr[0], "crc_table error");

	crc_reg	= 0x00;
	ptr		= data;

	if ( ptr != nullptr ) for ( auto i=0; i != length; ++i )
	{
		byte	seg_hi, seg_lo;

		seg_hi	= (*ptr) >> 4;
		seg_lo	= (*ptr++) & 0x0F;

		crc_reg	= (crc_reg >> 4) ^ crc_table.arr[ (crc_reg ^ seg_hi) & 0x0F ];
		crc_reg	= (crc_reg >> 4) ^ crc_table.arr[ (crc_reg ^ seg_lo) & 0x0F ];
	}

	return	crc_reg;
}

byte Cfinal2020Dlg::crc_check_4_direct ( byte* data, int iNum_bits )
{
	int		bytes, bitsRemainder;
	int		iShift;
	int		iCnt;
	byte	crc_reg, crc_4_show;
	byte	seg_hi, seg_lo;
	byte *	ptr;
	CString	strMsg;
	CString	strSpace;

	if ( data == nullptr )	return	0;
	if ( iNum_bits == 0 )	return	0;

	showBits ( strMsg, data, iNum_bits );
	m_strP6_2	= strMsg + _T ( "\r\n" );

	bytes			= (iNum_bits + 7) / 8;
	bitsRemainder	= iNum_bits % 8;

	crc_reg	= 0x00;
	ptr		= data;

	iCnt	= 4;
	seg_hi	= (*ptr) >> 4;
	strSpace.Empty ( );
	for ( auto i=0; i != bytes; ++i )
	{
		seg_lo	= (*ptr++) & 0x0F;

		iShift	= 5;
		crc_reg	^= seg_hi;	// read in the high-segment of 4 bits
		for ( auto j=0; j != 4; ++j )
		{
			// add one more bit from source
			crc_reg	<<= 1;
			crc_reg	+= (((1 << (3 - j)) & seg_lo) >> (3 - j));

			iCnt++;

			if ( crc_reg & 0x10 )
			{	// the high bit is ONE (4 bits altogether)
				// processing XOR substraction
				m_strP6_2	+= (strSpace + _T ( "10011\r\n" ));
				m_strP6_2	+= (strSpace + _T ( "-------\r\n " ));

				crc_reg	^= CRC_POLY_4_10011;	// do substraction

				crc_4_show	= crc_reg << 3;

				if ( iCnt < iNum_bits )
				{
					showBits_0 ( strMsg, &crc_4_show, 5 );
					m_strP6_2	+= (strSpace + strMsg);

					// add some bits from source
					int	iMove_down_bits	= checkZero_4 ( crc_4_show );
					byte	data	= seg_lo << 4;
					if ( iMove_down_bits < 4 )
						showBits ( strMsg, ptr, iMove_down_bits + 1, iShift );
					else
						showBits ( strMsg, ptr, 4, iShift );

					m_strP6_2	+= (strMsg + _T ( "\r\n" ));
				}
				else
				{
					showBits_0 ( strMsg, &crc_4_show, 4 );
					m_strP6_2	+= (strSpace + strMsg);

					m_strP6_2	+= _T ( "\r\n" );
				}
			}

			iShift++;
			strSpace	+= _T ( " " );
		}

		// new seg_hi, the line below should NOT be moved to the above for-chunk
		seg_hi	= (*ptr) >> 4;

		crc_reg	^= seg_lo;
		for ( auto j=0; j != 4; ++j )
		{
			if ( crc_reg & 0x08 )
			{
				m_strP6_2	+= (strSpace + _T ( "10011\r\n" ));
				m_strP6_2	+= (strSpace + _T ( "-------\r\n " ));

				crc_reg	<<= 1;
				crc_reg	^= CRC_POLY_4_10011;

				crc_4_show	= crc_reg << 4;
				showBits_0 ( strMsg, &crc_4_show, 4 );
				m_strP6_2	+= (strSpace + strMsg);
				// add some bits from source
				int	iMove_down_bits	= checkZero_4 ( crc_4_show );
				byte	data	= seg_hi << 4;
				if ( iMove_down_bits < 4 )
					showBits ( strMsg, ptr, iMove_down_bits + 1 );
				else
					showBits ( strMsg, ptr, 4 );

				m_strP6_2	+= (strMsg + _T ( "\r\n" ));
			}
			else
				crc_reg	<<= 1;

			strSpace	+= _T ( " " );
		}
	}

	return	crc_reg;
}

byte* Cfinal2020Dlg::crc_create_4_direct_old ( const byte* data, int length )
{
	int		bytes, bitsRemainder;
	int		iShift;
	byte	crc_reg, crc_4_show;
	byte* ptr;
	byte* ptrHandle	= nullptr;
	CString	strMsg;
	CString	strSpace;

	if ( data == nullptr )	return	nullptr;
	if ( length == 0 )	return	nullptr;

	bytes			= length + 1;	// we create the sending data, so need one more byte
	bitsRemainder	= 4;			// (actually 4 extra bits needed)

	ptrHandle	= (byte*) malloc ( bytes );

	memcpy ( ptrHandle, data, length );
	memset ( ptrHandle + length, 0, 1 );	// set the crc bits to be 0

	showBits ( strMsg, ptrHandle, length * 8 + 4 );
	m_strP6_1	= strMsg + _T ( "\r\n" );

	byte	seg_hi, seg_lo;

	crc_reg	= 0x00;
	ptr		= ptrHandle;

	seg_hi	= (*ptr) >> 4;
	strSpace.Empty ( );
	for ( auto i=0; i != length; ++i )
	{
		seg_lo	= (*ptr) & 0x0F;

		iShift	= 0;
		crc_reg	^= seg_hi;
		for ( auto j=0; j != 4; ++j )
		{
			if ( crc_reg & 0x08 )
			{
				m_strP6_1	+= (strSpace + _T ( "10011\r\n" ));
				m_strP6_1	+= (strSpace + _T ( "-------\r\n " ));

				crc_reg	<<= 1;
				crc_reg	^= CRC_POLY_4_10011;

				crc_4_show	= crc_reg << 4;
				showBits_0 ( strMsg, &crc_4_show, 4 );
				m_strP6_1	+= (strSpace + strMsg);
				// add some bits from source
				int	iMove_down_bits	= checkZero_4 ( crc_4_show );
				byte	data	= seg_lo << 4;
				if ( iMove_down_bits < 4 )
					showBits ( strMsg, ptr, iMove_down_bits + 1, iShift );
				else
					showBits ( strMsg, ptr, 4, iShift );

				m_strP6_1	+= (strMsg + _T ( "\r\n" ));
			}
			else
				crc_reg	<<= 1;

			iShift++;
			strSpace	+= _T ( " " );
		}

		// new seg_hi, the line below should NOT be moved to the above for-chunk
		seg_hi	= (*++ptr) >> 4;

		crc_reg	^= seg_lo;
		for ( auto j=0; j != 4; ++j )
		{
			if ( crc_reg & 0x08 )
			{
				m_strP6_1	+= (strSpace + _T ( "10011\r\n" ));
				m_strP6_1	+= (strSpace + _T ( "-------\r\n " ));

				crc_reg	<<= 1;
				crc_reg	^= CRC_POLY_4_10011;

				crc_4_show	= crc_reg << 4;
				showBits_0 ( strMsg, &crc_4_show, 4 );
				m_strP6_1	+= (strSpace + strMsg);
				// add some bits from source
				int	iMove_down_bits	= checkZero_4 ( crc_4_show );
				byte	data	= seg_hi << 4;
				if ( iMove_down_bits < 4 )
					showBits ( strMsg, ptr, iMove_down_bits + 1, iShift );
				else
					showBits ( strMsg, ptr, 4, iShift );

				m_strP6_1	+= (strMsg + _T ( "\r\n" ));
			}
			else
				crc_reg	<<= 1;

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


byte* Cfinal2020Dlg::crc_create_4_direct_new ( const byte* data, int length )
{
	int		bytes, bitsRemainder;
	int		iShift;
	int		iCnt, iTotal;
	byte	crc_reg, crc_4_show;
	byte* ptr;
	byte* ptrHandle	= nullptr;
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

	showBits ( strMsg, ptrHandle, length * 8 + 4 );
	m_strP6_1	= strMsg + _T ( "\r\n" );

	byte	seg_hi, seg_lo;

	crc_reg	= 0x00;
	ptr		= ptrHandle;

	iCnt	= 4;
	seg_hi	= (*ptr) >> 4;
	crc_reg	^= seg_hi;	// read in the high-segment of 4 bits

	strSpace.Empty ( );
	for ( auto i=0; i != length; ++i )
	{
		seg_lo	= (*ptr) & 0x0F;

		iShift	= 5;
		for ( auto j=0; j != 4; ++j )
		{
			// add one more bit from source
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

				if ( iCnt < (iTotal - 1) )
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

				if ( iCnt < (iTotal - 1) )
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

void Cfinal2020Dlg::showSubtrahend ( CString& strEdit, CString& strSpace )
{
	strEdit	+= (strSpace + _T ( "10011\r\n" ));
	strEdit	+= (strSpace + _T ( "-------\r\n" ));
}

BOOL Cfinal2020Dlg::DestroyWindow ( )
{
	delete	m_pDivider;

	return CDialogEx::DestroyWindow ( );
}
