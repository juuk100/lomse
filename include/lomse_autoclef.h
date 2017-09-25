//---------------------------------------------------------------------------------------
// This file is part of the Lomse library.
// Lomse is copyrighted work (c) 2010-2017. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice, this
//      list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright notice, this
//      list of conditions and the following disclaimer in the documentation and/or
//      other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
// SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
// TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
// BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.
//
// For any comment, suggestion or feature request, please contact the manager of
// the project at cecilios@users.sourceforge.net
//---------------------------------------------------------------------------------------

#ifndef __LOMSE_AUTOCLEF_H__
#define __LOMSE_AUTOCLEF_H__

#include "lomse_pitch.h"

#include <vector>
#include <string>
using namespace std;

namespace lomse
{

//forward declarations
class ImoScore;
class ImoStaffObj;
class StaffObjsCursor;

//---------------------------------------------------------------------------------------
//Class AutoClef implements the algorithm for fixing malformed MusicXML files that
//do not specify clef (see issue #68).
//
//The following rules are used:
// - if an score part has pitched notes but the clef is missing, a clef will be inserted.
//   It will be a G or an F4 clef depending on notes pitch range
//
class AutoClef
{
protected:
    ImoScore* m_pScore;
    StaffObjsCursor* m_pCursor;

    vector<bool> m_fNeedsClef;      //true if staff i needs clef
    vector<ImoStaffObj*> m_pAt;     //first staffobj in the staff i
    vector<FPitch> m_maxPitch;      //max pitch in staff i
    vector<FPitch> m_minPitch;      //min pitch in staff i
    vector<int> m_numNotes;         //number of accounted notes in staff i

public:
    AutoClef(ImoScore* pScore);
    virtual ~AutoClef();

    void do_autoclef();


protected:
    void find_staves_needing_clef();
    void add_clefs();
    void add_clef(int idx);
    string decide_clef(int idx, int iStaff);

};


}   //namespace lomse

#endif      //__LOMSE_AUTOCLEF_H__
