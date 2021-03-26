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

// final2020Dlg.h : header file
//

#pragma once


// Cfinal2020Dlg dialog
class CcrcDivider;
class Cfinal2020Dlg : public CDialogEx
{
// Construction
public:
	Cfinal2020Dlg(CWnd* pParent = nullptr);	// standard constructor

	CcrcDivider *	m_pDivider;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FINAL2020_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

protected:
	CString	m_strPrev_ID;

	int		m_iChecksum;

	void	calculate_C ( );
	void	calculate_Checksum ( );
	void	solveP_2 ( );
	void	solveP_3 ( );
	void	solveP_4 ( );
	void	solveP_5 ( );
	void	solveP_6 ( );
	void	solveP_6_old ( );
	void	solveP_7 ( );
	void	solveP_8 ( );
	void	solveP_9 ( );

	byte	crc_check_4 ( const byte* data, int length );
	byte *	crc_create_4_direct ( const byte* data, int length );
	byte *	crc_create_4_direct_new ( const byte* data, int length );
	byte *	crc_create_4_direct_old ( const byte* data, int length );
	byte	crc_check_4_direct ( byte* data, int iNum_bits );

	void	showSubtrahend ( CString& strEdit, CString& strSpace );

// Implementation
protected:
	HICON m_hIcon;

	CString	m_strP7_addr[ 11 ];
	int		m_iLen [ 10 ];

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CString	m_strID;
	CEdit	m_edStudentID;
	CString	m_strC;
	CString m_strCheckSum;
	unsigned short	m_sID;

	int		m_iC_1;
	int		m_iC_2;
	float	m_fTime_1;
	float	m_fTime_2;

	CString m_strP_3;

	int		m_iSize_last_frag;

	int		m_i7_C_1;
	int		m_i11_C_1;

	CString m_strP6_1;
	CString m_strP6_2;

	CString m_strP7;

	afx_msg void OnEnUpdateEditStudentId ( );
	afx_msg void OnEnKillfocusEditStudentId ( );
	virtual BOOL DestroyWindow ( );
	CString m_strP8;
};
