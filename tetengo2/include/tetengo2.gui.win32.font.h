/*! \file
    \brief The definition of tetengo2::gui::win32::font.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_FONT_H)
#define TETENGO2_GUI_WIN32_FONT_H

#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <vector>

//#include <boost/concept_check.hpp>
#include <boost/operators.hpp>
#include <boost/scoped_array.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>
#if !defined(min) && !defined(DOCUMENTATION)
#   define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#if !defined(max) && !defined(DOCUMENTATION)
#   define max(a, b) ((a) > (b) ? (a) : (b))
#endif
#include <gdiplus.h>
#undef min
#undef max

#include "concept_tetengo2.String.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a font for Win32 platforms.
 
        \tparam String A string type. It must conform to
                       concept_tetengo2::String<String>.
        \tparam Size   A size type. It must conform to
                       boost::UnsignedInteger<Size>.
   */
    template <typename String, typename Size>
    class font : public boost::equality_comparable<font<String, Size> >
    {
    private:
        // concept checks

        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));
        BOOST_CONCEPT_ASSERT((boost::UnsignedInteger<Size>));


    public:
        // types

        //! The string type.
        typedef String string_type;

        //! The size type.
        typedef Size size_type;

        //! The families type.
        typedef std::vector<string_type> families_type;


        // static functions

        /*!
            \brief Returns the dialog font.

            \return The dialog font.
        */
        static const font& dialog_font()
        {
            static const font singleton(make_dialog_font());
            return singleton;
        }

        /*!
            \brief Returns the installed font families.

            \return The installed font families.
        */
        static const families_type& installed_families()
        {
            static const families_type singleton(make_installed_families());
            return singleton;
        }


        // constructors and destructor

        /*!
            \brief Creates a font.

            When family is not installed, the family of the dialog font is set
            instead.

            \param family    A family.
            \param size      A size.
            \param bold      Whether this font is bold.
            \param italic    Whether this font is italic.
            \param underline Whether this font is underlined.
            \param strikeout Whether this font is striked out.
        */
        font(
            const string_type& family,
            const size_type    size,
            const bool         bold,
            const bool         italic,
            const bool         underline,
            const bool         strikeout
        )
        :
        m_family(select_family(family)),
        m_size(size),
        m_bold(bold),
        m_italic(italic),
        m_underline(underline),
        m_strikeout(strikeout)
        {}

        /*!
            \brief Copies a font.

            \param another Another font object.
        */
        font(const font& another)
        :
        m_family(another.m_family),
        m_size(another.m_size),
        m_bold(another.m_bold),
        m_italic(another.m_italic),
        m_underline(another.m_underline),
        m_strikeout(another.m_strikeout)
        {}

        /*!
            \brief Destroys the font.
        */
        virtual ~font()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another font object.

            \param another Another font object.
        */
        void swap(font& another)
        throw ()
        {
            m_family.swap(another.m_family);
            std::swap(m_size, another.m_size);
            std::swap(m_bold, another.m_bold);
            std::swap(m_italic, another.m_italic);
            std::swap(m_underline, another.m_underline);
            std::swap(m_strikeout, another.m_strikeout);
        }

        /*!
            \brief Assigns another font object.

            \param another Another font object.

            \return this object.
        */
        font& operator=(const font& another)
        {
            font(another).swap(*this);
            return *this;
        }

        /*!
            \brief Checks whether this is equal to anther font object.

            \param another Another font object.

            \retval true  When this is equal to another.
            \retval false Otherwise.
        */
        bool operator==(const font& another)
        const
        {
            return true;
        }

        /*!
            \brief Returns the family.

            \return The family.
        */
        const string_type& family()
        const
        {
            return m_family;
        }

        /*!
            \brief Returns the size.

            \return The size.
        */
        size_type size()
        const
        {
            return m_size;
        }

        /*!
            \brief Returns whether this font is bold.

            \retval true  This font is bold.
            \retval false Otherwise.
        */
        bool bold()
        const
        {
            return m_bold;
        }

        /*!
            \brief Returns whether this font is italic.

            \retval true  This font is italic.
            \retval false Otherwise.
        */
        bool italic()
        const
        {
            return m_italic;
        }

        /*!
            \brief Returns whether this font is underlined.

            \retval true  This font is underlined.
            \retval false Otherwise.
        */
        bool underline()
        const
        {
            return m_underline;
        }

        /*!
            \brief Returns whether this font is striked out.

            \retval true  This font is striked out.
            \retval false Otherwise.
        */
        bool strikeout()
        const
        {
            return m_strikeout;
        }


    private:
        // static functions

        static const font make_dialog_font()
        {
            const ::LOGFONTW log_font = get_message_font();

            assert(log_font.lfHeight < 0);
            assert(
                std::find(
                    installed_families().begin(),
                    installed_families().end(),
                    log_font.lfFaceName
                ) != installed_families().end()
            );
            return font(
                log_font.lfFaceName,
                -log_font.lfHeight,
                log_font.lfWeight >= FW_BOLD,
                log_font.lfItalic != 0,
                log_font.lfUnderline != 0,
                log_font.lfStrikeOut != 0
            );
        }

        static const ::LOGFONTW get_message_font()
        {
            ::NONCLIENTMETRICSW metrics;
            get_nonclient_metrics(metrics);

            return metrics.lfMessageFont;
        }

        static void get_nonclient_metrics(::NONCLIENTMETRICSW& metrics)
        {
            ::OSVERSIONINFOW os_version_info;
            os_version_info.dwOSVersionInfoSize = sizeof(::OSVERSIONINFOW);
            if (::GetVersionEx(&os_version_info) == 0)
                throw std::runtime_error("Can't get Windows version.");

            const ::UINT metrics_size = os_version_info.dwMajorVersion >= 6 ?
                sizeof(::NONCLIENTMETRICSW) :
                sizeof(::NONCLIENTMETRICSW) - sizeof(int);
            metrics.cbSize = metrics_size;
            if (
                ::SystemParametersInfoW(
                    SPI_GETNONCLIENTMETRICS,
                    metrics_size,
                    &metrics,
                    0
                ) == 0
            )
            {
                throw std::runtime_error("Can't get non-client metrics.");
            }
        }

        static const families_type make_installed_families()
        {
            const Gdiplus::InstalledFontCollection font_collection;
            const ::INT count = font_collection.GetFamilyCount();
            const boost::scoped_array<Gdiplus::FontFamily> p_families(
                new Gdiplus::FontFamily[count]
            );
            ::INT actual_count = 0;

            const Gdiplus::Status status =
                font_collection.GetFamilies(
                    count, p_families.get(), &actual_count
                );
            if (status != Gdiplus::Ok)
            {
                throw std::runtime_error(
                    "Can't get installed font families."
                );
            }

            families_type families;
            families.reserve(actual_count);
            for (::INT i = 0; i < actual_count; ++i)
            {
                wchar_t family_name[LF_FACESIZE];
                const Gdiplus::Status family_name_status =
                    p_families[i].GetFamilyName(family_name);
                if (family_name_status != Gdiplus::Ok)
                    throw std::runtime_error("Can't get font family name.");
                families.push_back(family_name);
            }
            return families;
        }

        const string_type select_family(const string_type& family)
        {
            if (
                std::find(
                    installed_families().begin(),
                    installed_families().end(),
                    family
                ) == installed_families().end()
            )
            {
                return dialog_font().family();
            }
        
            return family;
        }

        // variables

        string_type m_family;

        size_type m_size;

        bool m_bold;

        bool m_italic;

        bool m_underline;

        bool m_strikeout;


    };


}}}

namespace std
{
    /*!
        \brief Swaps two font objects.

        \tparam String A string type. It must conform to
                       concept_tetengo2::String<String>.
        \tparam Size   A size type. It must conform to
                       boost::UnsignedInteger<Size>.

        \param font1 A font object #1.
        \param font2 A font object #2.
    */
    template <typename String, typename Size>
    void swap(
        tetengo2::gui::win32::font<String, Size>& font1,
        tetengo2::gui::win32::font<String, Size>& font2
    )
    throw ()
    {
        BOOST_CONCEPT_ASSERT((concept_tetengo2::String<String>));
        BOOST_CONCEPT_ASSERT((boost::UnsignedInteger<Size>));

        font1.swap(font2);
    }


}

#endif