/*! \file
    \brief The definition of stub_tetengo2::encoding::utf8.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_ENCODING_UTF8_H)
#define STUBTETENGO2_ENCODING_UTF8_H

//#include <string>

#include "tetengo2.encoding.encoding.h"


namespace tetengo2 { namespace encoding
{
    class utf8 : public encoding
    {
    private:
    public:
        // types

        typedef std::string string_type;

        typedef string_type::value_type string_char_type;


        // constructors and destructor

        utf8()
        {}


        // functions

        string_type from_pivot(const pivot_type& pivot)
        const
        {
            return string_type();
        }

        pivot_type to_pivot(const string_type& string)
        const
        {
            return pivot_type();
        }


    };


}}


#endif
