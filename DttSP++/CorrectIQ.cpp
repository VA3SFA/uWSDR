/* CorrectIQ.cpp

This routine restores quadrature between arms of an analytic signal
possibly distorted by ADC hardware.

This file is part of a program that implements a Software-Defined Radio.

Copyright (C) 2004, 2005, 2006 by Frank Brickle, AB2KT and Bob McGwier, N4HY
Copyright (C) 2006-2008,2013 by Jonathan Naylor, G4KLX

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

The authors can be reached by email at

ab2kt@arrl.net
or
rwmcgwier@comcast.net

or by paper mail at

The DTTS Microwave Society
6 Kathleen Place
Bridgewater, NJ 08807
*/

#include <wx/wx.h>

#include "CorrectIQ.h"

CCorrectIQ::CCorrectIQ(CXB* buf) :
m_buf(buf),
m_phase(0.0F),
m_gain(1.0F)
{
	wxASSERT(buf != NULL);
}

CCorrectIQ::~CCorrectIQ()
{
}

void CCorrectIQ::process()
{
	unsigned int n = CXBhave(m_buf);

	for (unsigned int i = 0; i < n; i++) {
		CXBimag(m_buf, i) += m_phase * CXBreal(m_buf, i);
		CXBreal(m_buf, i) *= m_gain;
	}
}

void CCorrectIQ::setPhase(float phase)
{
	m_phase = phase;
}

void CCorrectIQ::setGain(float gain)
{
	m_gain = gain;
}
