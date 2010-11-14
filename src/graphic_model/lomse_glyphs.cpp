//---------------------------------------------------------------------------------------
//  This file is part of the Lomse library.
//  Copyright (c) 2010 Lomse project
//
//  Lomse is free software; you can redistribute it and/or modify it under the
//  terms of the GNU General Public License as published by the Free Software Foundation,
//  either version 3 of the License, or (at your option) any later version.
//
//  Lomse is distributed in the hope that it will be useful, but WITHOUT ANY
//  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
//  PARTICULAR PURPOSE.  See the GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License along
//  with Lomse; if not, see <http://www.gnu.org/licenses/>.
//  
//  For any comment, suggestion or feature request, please contact the manager of
//  the project at cecilios@users.sourceforge.net
//
//---------------------------------------------------------------------------------------

#include "lomse_glyphs.h"


namespace lomse
{

// offset:  the y-axis offset from paper cursor position so that shape get correctly
//          positioned over a five-lines staff (units: tenths of inter-line space)
// shift:   the y-axis offset from bitmap rectangle to the selection rectangle origin
//          (units: tenths of inter-line space)
// height:  the height of the selection rectangle
//          units: tenths (tenths of inter-line space)

//---------------------------------------------------------------------------------------
GlyphData::GlyphData(const unsigned int glyph, int yOffset, int yShift, int selHeight,
                     int top, int bottom, int xPos, int yPos, int width, int height,
                     int xDrag, int yDrag)
    : GlyphChar(glyph)
    , GlyphOffset(yOffset)
    , Top(top)
    , Bottom(bottom)
{
    // Table data is in FUnits. As 1 line (10 tenths) is 512 FU, it is simple
    // to convert table data into tenths: just divide FU by 51.2
	thxPos = Tenths(xPos) / 51.2f;
	thyPos = Tenths(yPos) / 51.2f;
	thWidth = Tenths(width) / 51.2f;
	thHeight = Tenths(height) / 51.2f;
	txDrag = Tenths(xDrag) / 51.2f;
	tyDrag = Tenths(yDrag) / 51.2f;

	if (yShift == 0 && selHeight == 0)
    {
        //not specified. Use full glyph rectangle
		SelRectShift = (int)(((3072.0 -(float)(height + yPos)) / 51.2) + 0.5);
		SelRectHeight = (int)(((float)(height) / 51.2) + 0.5);
	}
	else
    {
        //use specified rectangle
		SelRectHeight = selHeight;
		SelRectShift = yShift; 
	}
}

//---------------------------------------------------------------------------------------
//the glyphs table
//IMPORTANT: The table inicialization values MUST be ordered following the
//           enum EGlyphIndex, defined in lomse_glyphs.h
//---------------------------------------------------------------------------------------
const GlyphData aGlyphsInfo[] =
{
// notheads
	//                                                      ----- FUnits ------------      -- FUnits--
    //                       sel rectangle                  Position    Size                drag point
    //       Glyph   offset  shift   height                 x       y   width   height      x       y
    GlyphData('O',  10,     55,     10,   0,      0,      0,      0,      0,      0,      0,      0 ),    // "Half note"
    GlyphData('P',  10,     55,     10,   0,      0,      0,      0,      0,      0,      0,      0 ),    // "Quarter note notehead"
    GlyphData('L',  10,     55,     10,   0,      0,      0,      0,      0,      0,      0,      0 ),    // "Cross notehead"

//notes with stem and flag, in single char
	//                                                           ----- FUnits ------------      -- FUnits--
    //                            sel rectangle                  Position    Size                drag point
    //            Glyph   offset  shift   height                 x       y   width   height      x       y
    GlyphData('\uF04B',   0,      0,      0,   0,      0,      0,   -369,    960,    738,    480,    369 ),    // "Longa note"
    GlyphData('\uF04D',   0,      0,      0,   0,      0,      0,   -283,   1182,    567,    591,    283 ),    // "Breve note"
    GlyphData('\uF04E',  10,      0,      0,   0,      0,      0,   -282,   1010,    566,    505,    283 ),    // "Whole note"
    GlyphData('\uF086',   0,      0,      0,   0,      0,      0,  -1847,    709,   2127,    354,    279 ),    // "Half note, stem down"
    GlyphData('\uF087',   0,      0,      0,   0,      0,      0,   -279,    709,   2171,    354,   1923 ),    // "Half note, stem up"
    GlyphData('\uF088',   0,      0,      0,   0,      0,      0,  -1779,    640,   2027,    320,    248 ),    // "Quarter note, stem down"
    GlyphData('\uF089',   0,      0,      0,   0,      0,      0,   -248,    640,   2027,    320,   1779 ),    // "Quarter note, stem up"
    GlyphData('\uF08A',   0,      0,      0,   0,      0,      0,  -1782,    640,   2030,    320,    248 ),    // "Eight note, flag bottom"
    GlyphData('\uF08B',   0,      0,      0,   0,      0,      0,   -248,   1068,   2027,    320,   1779 ),    // "Eight note, flag top"
    GlyphData('\uF08C',   0,      0,      0,   0,      0,      0,  -1779,    640,   2027,    320,    248 ),    // "16th note, flag bottom"
    GlyphData('\uF08D',   0,      0,      0,   0,      0,      0,   -248,   1070,   2027,    320,   1779 ),    // "16th note, flag top"
    GlyphData('\uF08E',   0,      0,      0,   0,      0,      0,  -2241,    640,   2489,    320,    248 ),    // "32nd note, flag bottom"
    GlyphData('\uF08F',   0,      0,      0,   0,      0,      0,   -248,   1071,   2439,    320,   2191 ),    // "32nd note, flag top"
    GlyphData('\uF090',   0,      0,      0,   0,      0,      0,  -2508,    640,   2756,    320,    248 ),    // "64th note, flag bottom"
    GlyphData('\uF091',   0,      0,      0,   0,      0,      0,   -248,   1067,   2954,    320,   2706 ),    // "64th note, flag top")),
    GlyphData('\uF092',   0,      0,      0,   0,      0,      0,  -2735,    640,   2983,    320,    248 ),    // "128th note, flag bottom"
    GlyphData('\uF093',   0,      0,      0,   0,      0,      0,   -248,   1067,   3189,    320,   2941 ),    // "128th note, flag top")),
    GlyphData('\uF094',   0,      0,      0,   0,      0,      0,  -3132,    640,   3380,    320,    248 ),    // "256th note, flag bottom"
    GlyphData('\uF095',   0,      0,      0,   0,      0,      0,   -248,   1093,   3578,    320,   3330 ),    // "256th note, flag top")),

// rests
	//                                                      ----- FUnits ------------      -- FUnits--
    //                       sel rectangle                  Position    Size                drag point
    //       Glyph   offset  shift   height                 x       y   width   height      x       y
    GlyphData('}', -20,      0,     0,    0,      0,      0,    512,    288,   1024,    144,      0 ),    // "Longa rest"     //larga
    GlyphData('|', -20,      0,     0,    0,      0,      0,   1024,    307,    512,    154,      0 ),    // "Breve rest"    //breve, cuadrada
    GlyphData('{', -20,      0,     0,    0,      0,      0,   1280,    720,    256,    360,      0 ),    // "Whole rest"    //whole redonda
    GlyphData('z', -20,      0,     0,    0,      0,      0,   1024,    720,    256,    360,      0 ),    // "Half rest"     //half blanca
    GlyphData('y', -20,      0,     0,    0,      0,      0,    343,    510,   1362,    205,    975 ),    // "Quarter rest"  //quarter negra
    GlyphData('x', -20,      0,     0,    0,      0,      0,    512,    480,    888,    240,    700 ),    // "Eight rest"    //eighth corchea
    GlyphData('w', -20,      0,     0,    0,      0,      0,      0,    618,   1368,    309,    684 ),    // "16th rest"     //16th semicorchea
    GlyphData('v', -20,      0,     0,    0,      0,      0,      0,    726,   1848,    363,    924 ),    // "32nd rest"     //32nd fusa
    GlyphData('u', -20,      0,     0,    0,      0,      0,   -450,    792,   2322,    396,    936 ),    // "64th rest"     //64th semifusa
    GlyphData('t', -20,      0,     0,    0,      0,      0,   -512,    828,   2802,    414,   1145 ),    // "128th rest"    //128th garrapatea
    GlyphData('s', -20,      0,     0,    0,      0,      0,   -924,    924,   3288,    462,   1182 ),    // "256th rest"    //256th semigarrapatea

//flags for notes.
    //  shift and height info is no needed
    //
	//                                                      ----- FUnits ------------      -- FUnits--
    //                       sel rectangle                  Position    Size                drag point
    //       Glyph   offset  shift   height                 x       y   width   height      x       y
    GlyphData('o', -20,      1,     29,  2956, 1570,      0,      0,      0,      0,      0,      0 ),    // "Eight note flag down"
    GlyphData('n', -20,     10,     30,  2606, 1310,      0,   1024,    621,   1539,      0,      0 ),    // "16th note flag down"
    GlyphData('m', -20,     11,     39,  2586,  912,      0,    512,    618,   1994,      0,      0 ),    // "32nd note flag down"
    GlyphData('l', -20,     16,     44,  2435,  545,      0,      0,    621,   2250,      0,      0 ),    // "64th note flag down"
    GlyphData('k', -20,     12,     48,  2437,  180,      0,     -3,    621,   2483,      0,      0 ),    // "128th note flag down"
    GlyphData('j', -20,     14,     56,  2434, -180,      0,   -512,    621,   2875,      0,      0 ),    // "256th note flag down"
    GlyphData('f', -60,     50,     30,   508, -1043,   -70,  -1027,    498,   1540,      0,      0 ),    // "Eight note flag up"
    GlyphData('e', -60,     40,     35,   890, -945,    -69,   -779,    499,   1795,      0,      0 ),    // "16th note flag up"
    GlyphData('d', -60,     30,     43,  1120, -727,    -69,   -661,    498,   2197,      0,      0 ),    // "32nd note flag up"
    GlyphData('c', -60,     20,     53,  1541, -770,    -69,   -663,    497,   2711,      0,      0 ),    // "64th note flag up")),
    GlyphData('b', -60,     15,     58,  1901, -756,    -69,   -628,    496,   2945,      0,      0 ),    // "128th note flag up"
    GlyphData('a', -60,     10,     65,  2280, -766,    -69,   -766,    523,   3332,      0,      0 ),    // "256th note flag up")),

//accidentals
	//                                                      ----- FUnits ------------      -- FUnits--
    //                       sel rectangle                  Position    Size                drag point
    //       Glyph   offset  shift   height                 x       y   width   height      x       y
    GlyphData('\'', 10,     45,     30,   0,      0,      0,      0,      0,      0,      0,      0 ),    // "Natural accidental"
    GlyphData('#',  10,     45,     30,   0,      0,      0,      0,      0,      0,      0,      0 ),    // "Sharp accidental"
    GlyphData('%',  10,     40,     27,   0,      0,      0,      0,      0,      0,      0,      0 ),    // "Flat accidental"
    GlyphData('$',  10,     54,     11,   0,      0,      0,      0,      0,      0,      0,      0 ),    // "Double sharp accidental"
    GlyphData('&',  10,     40,     27,   0,      0,      0,      0,      0,      0,      0,      0 ),    // "Double flat accidental"


//clefs
	//                                                      ----- FUnits ------------      -- FUnits--
    //                       sel rectangle                  Position    Size                drag point
    //       Glyph   offset  shift   height                 x       y   width   height      x       y
    GlyphData('A', -20,      0,      0,   0,      0,      0,   -853,   1243,   3606,    621,   1377 ),    // "G clef"
    GlyphData('B', -20,      0,      0,   0,      0,      0,    324,   1451,   1728,    725,   1026 ),    // "F clef"
    GlyphData('D', -20,     20,     35,   0,      0,      0,      0,      0,      0,      0,      0 ),    // "F clef ottava alta"
    GlyphData('E', -20,     20,     35,   0,      0,      0,      0,      0,      0,      0,      0 ),    // "F clef ottava bassa"
    GlyphData('C', -20,      0,      0,   0,      0,      0,      0,   1393,   2050,    681,   1025 ),    // "C clef"
    GlyphData('G', -19,     20,     35,   0,      0,      0,      0,      0,      0,      0,      0 ),    // "Percussion clef, block"

//numbers for time signatures
	//                                                      ----- FUnits ------------      -- FUnits--
    //                       sel rectangle                  Position    Size                drag point
    //       Glyph   offset  shift   height                 x       y   width   height      x       y
    GlyphData('0', -20,      0,      0,   0,      0,      0,     37,    702,    950,      0,      0 ),    // "Number 0"
    GlyphData('1', -20,      0,      0,   0,      0,      0,     37,    612,    950,      0,      0 ),    // "Number 1"
    GlyphData('2', -20,      0,      0,   0,      0,      0,     37,    702,    950,      0,      0 ),    // "Number 2"
    GlyphData('3', -20,      0,      0,   0,      0,      0,     37,    636,    950,      0,      0 ),    // "Number 3"
    GlyphData('4', -20,      0,      0,   0,      0,      0,     37,    762,    950,      0,      0 ),    // "Number 4"
    GlyphData('5', -20,      0,      0,   0,      0,      0,     37,    666,    950,      0,      0 ),    // "Number 5"
    GlyphData('6', -20,      0,      0,   0,      0,      0,     37,    654,    950,      0,      0 ),    // "Number 6"
    GlyphData('7', -20,      0,      0,   0,      0,      0,     37,    696,    950,      0,      0 ),    // "Number 7"
    GlyphData('8', -20,      0,      0,   0,      0,      0,     37,    714,    950,      0,      0 ),    // "Number 8"
    GlyphData('9', -20,      0,      0,   0,      0,      0,     37,    648,    950,      0,      0 ),    // "Number 9"

//other for time signatures
    GlyphData('>',   0,      0,      0,   0,      0,      0,     37,    702,    950,      0,      0 ),    //GLYPH_COMMON_TIME,
    GlyphData('?',   0,      0,      0,   0,      0,      0,     37,    702,    950,      0,      0 ),    //GLYPH_CUT_TIME,

//signs
	//                                                      ----- FUnits ------------      -- FUnits--
    //                       sel rectangle                  Position    Size                drag point
    //       Glyph   offset  shift   height                 x       y   width   height      x       y
    GlyphData('.', -60,     58,     5,   121,  -112,      0,      0,      0,      0,      0,      0 ),    // "Dot (for dotted notes)"
    GlyphData('_',   0,     33,    31,  1403,  -201,      0,      0,      0,      0,      0,      0 ),    // "small quarter note up (for metronome marks)"
    GlyphData('`',   0,     33,    31,  1403,  -201,      0,      0,      0,      0,      0,      0 ),    // "small dotted quarter note up"
    GlyphData(']',   0,     32,    32,  1432,  -205,      0,      0,      0,      0,      0,      0 ),    // "small eighth note up"
    GlyphData('^',   0,     32,    32,  1432,  -205,      0,      0,      0,      0,      0,      0 ),    // "small dotted eighth note up"
    GlyphData('[',   0,      5,    32,   143,  -113,      0,      0,      0,      0,      0,      0 ),    // "small equal sign"

    GlyphData(':',   0,      0,      0,   0,      0,      0,      0,    469,    854,      0,      0 ),    // "V breath-mark"
    GlyphData('+',   0,      0,      0,   0,      0,      0,      0,      0,      0,      0,      0 ),    // "Da Capo sign"
    GlyphData('*',   0,      0,      0,   0,      0,      0,      0,      0,      0,      0,      0 ),    // "Dal Segno sign"
    GlyphData('-',   0,      0,      0,   0,      0,      0,      0,      0,      0,      0,      0 ),    // "Coda sign"
    GlyphData(',',   0,      0,      0,   0,      0,      0,      0,      0,      0,      0,      0 ),    // "Segno sign"
    GlyphData('>',   0,      0,      0,   0,      0,      0,      0,      0,      0,      0,      0 ),    // "Octava sign"
    GlyphData(';',   0,      0,      0,   0,      0,      5,      8,   1359,    778,      0,      0 ),    // "Fermata over (arch)"
    GlyphData('<',   0,      0,      0,   0,      0,      0,   -796,   1359,    781,      0,      0 ),    // "Fermata under (arch)"

//figured bass. Numbers and other symbols
	//                                                           ----- FUnits ------------      -- FUnits--
    //                            sel rectangle                  Position    Size                drag point
    //            Glyph   offset  shift   height                 x       y   width   height      x       y
    GlyphData('\uF09F',   0,      0,      0,   0,      0,      0,      0,      0,      0,      0,      0 ),    // "Figured bass. Number 0"
    GlyphData('\uF096',   0,      0,      0,   0,      0,      0,      0,      0,      0,      0,      0 ),    // "Figured bass. Number 1"
    GlyphData('\uF097',   0,      0,      0,   0,      0,      0,      0,      0,      0,      0,      0 ),    // "Figured bass. Number 2"
    GlyphData('\uF098',   0,      0,      0,   0,      0,      0,      0,      0,      0,      0,      0 ),    // "Figured bass. Number 3"
    GlyphData('\uF099',   0,      0,      0,   0,      0,      0,      0,      0,      0,      0,      0 ),    // "Figured bass. Number 4"
    GlyphData('\uF09A',   0,      0,      0,   0,      0,      0,      0,      0,      0,      0,      0 ),    // "Figured bass. Number 5"
    GlyphData('\uF09B',   0,      0,      0,   0,      0,      0,      0,      0,      0,      0,      0 ),    // "Figured bass. Number 6"
    GlyphData('\uF09C',   0,      0,      0,   0,      0,      0,      0,      0,    664,      0,      0 ),    // "Figured bass. Number 7"
    GlyphData('\uF09D',   0,      0,      0,   0,      0,      0,      0,      0,      0,      0,      0 ),    // "Figured bass. Number 8"
    GlyphData('\uF09E',   0,      0,      0,   0,      0,      0,      0,      0,      0,      0,      0 ),    // "Figured bass. Number 9"
    GlyphData('\uF0A0',   0,      0,      0,   0,      0,      0,      0,      0,      0,      0,      0 ),    // "Figured bass. Sharp symbol"
    GlyphData('\uF0A1',   0,      0,      0,   0,      0,      0,      0,      0,      0,      0,      0 ),    //GLYPH_FIGURED_BASS_FLAT,                //Flat symbol
    GlyphData('\uF0A2',   0,      0,      0,   0,      0,      0,      0,      0,      0,      0,      0 ),    //GLYPH_FIGURED_BASS_NATURAL,             //Natural symbol
    GlyphData('\uF0AB',   0,      0,      0,   0,      0,      0,      0,      0,      0,      0,      0 ),    //GLYPH_FIGURED_BASS_PLUS,                // +
    GlyphData('\uF0AC',   0,      0,      0,   0,      0,      0,      0,      0,      0,      0,      0 ),    //GLYPH_FIGURED_BASS_MINUS,               // -
    GlyphData('\uF0A8',   0,      0,      0,   0,      0,      0,      0,      0,      0,      0,      0 ),    //GLYPH_FIGURED_BASS_OPEN_PARENTHESIS,    // (
    GlyphData('\uF0A3',   0,      0,      0,   0,      0,      0,      0,      0,      0,      0,      0 ),    //GLYPH_FIGURED_BASS_CLOSE_PARENTHESIS,   // )
    GlyphData('\uF0AA',   0,      0,      0,   0,      0,      0,      0,      0,      0,      0,      0 ),    //GLYPH_FIGURED_BASS_7_STRIKED,           // 7 with overlayered /
};

//em=2048
//ascender=3072
//descender=-1024
//tenths = 512

//512 FUnits = 10 tenths   -->  t = FU*10/512

//offset = -20 for objects pre-positioned on staff
//shift = ascender - top

//A,  G_CLEF, 0, 1243, 2753, -864,    <offset_to_2nd_line=0>
//shift = 3072- 2753 FU = 319FU = 6,26t = 6         (5,73)
//height = (2743 - -864)FU = 3607FU = 70,45 = 71    (6,71)

//B,  F_CLEF, 0, 1451, 2053, 324      <offset_to_4th_line=0>
//shift = 3072- 2053 FU = 1019FU = 19,90t = 20      (20,35)
//height = (2053 - 324)FU = 1729FU = 33,76 = 34     (20,34)

//C,  C_CLEF, 0, 1394, 2050, 0        <offset_to_3rd_line=0>
//shift = 3072- 2050 FU = 1022FU = 19,96t = 20      (20,40)
//height = (2050 - 0)FU = 2050FU = 40,03 = 40       (20,40)

//DOT, '.',0, 227, 121, -112
//shift = 3072- 121 FU = 2951FU = 57,63 = 58
//height = (121 + 112)FU = 233FU = 4,55 = 5

//small quarter note up (for metronome marks)
//       xPos   yPos    width   height  Height+yPos
//  '_', 0      -201    481     1604    1403
//shift = 3072 - 1403 = 1669 FU = 1669*10/512 = 32,60 = 33
//height = 1604; FU = 1604/51,2 = 31,33 = 31

// see: lenmus/fonts/font_metrics.xml



}  //namespace lomse
