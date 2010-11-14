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
//  Credits:
//  -------------------------
//  This file is based on Anti-Grain Geometry version 2.4 examples' code.
//  Anti-Grain Geometry (AGG) is copyright (C) 2002-2005 Maxim Shemanarev 
//  (http://www.antigrain.com). AGG 2.4 is distributed under BSD license.
//
//---------------------------------------------------------------------------------------

#include "lomse_font_storage.h"

using namespace agg;

namespace lomse
{

// FontStorage implementation
//---------------------------------------------------------------------------------------

FontStorage::FontStorage()
    : m_fontEngine()
    , m_fontCacheManager(m_fontEngine)
    , m_fontHeight(14.0)
    , m_fontWidth(14.0)
    , m_fHinting(false)
    , m_fValidFont(false)
    , m_fKerning(true)
    , m_fFlip_y(true)
    , m_fontCacheType(k_raster_font_cache)
{
    //AWARE:
    //Apple Computer, Inc., owns three patents that are related to the
    //hinting process of glyph outlines within TrueType fonts. Hinting (also named
    //grid-fitting) is used to enhance the quality of glyphs at small bitmap sizes.
    //Therefore, you can not use hinting unless you are authorized (you purchased
    //a license from Apple, or because you are in a country where the patents do
    //not apply, etc.). Nevertheless lenmus font doesn't include hinting information
    //and, so, previous flag value doesn't matter. But its value is important
    //if I finally use FreeType for all fonts.

    //font settings
    m_fontEngine.gamma(agg::gamma_none());
    m_fontEngine.hinting(m_fHinting);
    m_fontEngine.flip_y(m_fFlip_y);

    //load a default font
    set_font("lmbasic2.ttf", 24.0); //timesi.ttf", 18.0);
}

//---------------------------------------------------------------------------------------
FontStorage::~FontStorage()
{
}

//---------------------------------------------------------------------------------------
bool FontStorage::set_font(const char* fontFullName, double height, EFontCacheType type)
{
    m_fValidFont = false;
    agg::glyph_rendering gren = agg::glyph_ren_agg_gray8;
    if(! m_fontEngine.load_font(fontFullName, 0, gren))
        return !m_fValidFont;    //error

    //set curren values for renderization
    m_fontCacheType = type;
    set_font_size(height);

    ////un-comment this to rotate/skew/translate the text
    ////agg::trans_affine mtx;
    ////mtx *= agg::trans_affine_rotation(agg::deg2rad(-4.0));
    //////mtx *= agg::trans_affine_skewing(-0.4, 0);
    //////mtx *= agg::trans_affine_translation(1, 0);
    ////m_fontEngine.transform(mtx);

    m_fValidFont = true;
    return !m_fValidFont;
}

//---------------------------------------------------------------------------------------
void FontStorage::set_font_size(double rPoints)
{
    m_fontHeight = rPoints;
    m_fontWidth = rPoints;
    m_fontEngine.height(m_fontHeight);
    m_fontEngine.width(m_fontWidth);
}

//---------------------------------------------------------------------------------------
void FontStorage::set_font_height(double rPoints)
{
    m_fontHeight = rPoints;
    m_fontEngine.height(rPoints);
}

//---------------------------------------------------------------------------------------
void FontStorage::set_font_width(double rPoints)
{
    m_fontWidth = rPoints;
    m_fontEngine.width(rPoints);
}

////---------------------------------------------------------------------------------------
//int FontStorage::draw_text(double x, double y, const std::string& str, double scale)
//{
//    //returns the number of chars drawn
//
//   if (!is_font_valid())
//        return 0;
//
//    //set scaling factor
//    agg::trans_affine mtx;
//    mtx *= agg::trans_affine_scaling(scale);
//    m_fontEngine.transform(mtx);
//
//    //convert to utf-32
//    const char* utf8str = str.c_str();
//    std::vector<unsigned int> utf32result;
//    utf8::utf8to32(utf8str, utf8str + strlen(utf8str), std::back_inserter(utf32result));
//
//    //loop to render glyphs
//    int num_glyphs = 0;
//    std::vector<unsigned int>::iterator it;
//    for (it = utf32result.begin(); it != utf32result.end(); ++it)
//    {
//        const agg::glyph_cache* glyph = get_glyph_cache(*it);
//        if(glyph)
//        {
//            if(m_fKerning)
//                add_kerning(&x, &y);
//
//            init_adaptors(glyph, x, y);
//
//            //render the glyph using method agg::glyph_ren_agg_gray8
//            m_pRenderer->render(m_fontCacheManager.gray8_adaptor(),
//                              m_fontCacheManager.gray8_scanline() );
//
//            // increment pen position
//            x += glyph->advance_x;
//            ++num_glyphs;
//        }
//    }
//    return num_glyphs;
//}


}   //namespace lomse
