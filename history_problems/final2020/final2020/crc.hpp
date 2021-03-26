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

#ifndef _CRC_HPP_
#define	_CRC_HPP_

#define		CRC_POLY_4_10011		0x13


template<int N>
struct tag_crc_4_table
{
	constexpr	tag_crc_4_table ( ) : arr ( )
	{
		byte	crc	= 0;
		byte	c	= 0;

		for ( auto i=0; i != N; ++i )
		{
			crc	= 0;
			c	= i;

			for ( auto j=0; j != 4; ++j )
			{
				if ( (crc ^ c) & 0x01 )
					crc	= (crc >> 1) ^ CRC_POLY_4_10011;
				else
					crc	= crc >> 1;

				c	= c >> 1;
			}

//			arr[ i ]	= (i ^ CRC_POLY_4_10011) & 0x0F;
			arr[ i ]	= crc & 0x0F;
		}
	}

	byte	arr[ N ];
};

#endif // !_CRC_HPP_

