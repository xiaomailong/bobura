/*! \file
    \brief The definition of stub_tetengo2::gui::drawing::picture.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(STUBTETENGO2_GUI_DRAWING_PICTURE_H)
#define STUBTETENGO2_GUI_DRAWING_PICTURE_H

#include <utility>

#include <boost/noncopyable.hpp>


namespace stub_tetengo2 { namespace gui { namespace drawing
{
    template <typename Size>
    class picture : private boost::noncopyable
    {
    public:
        // types

        typedef Size size_type;

        typedef std::pair<size_type, size_type> dimension_type;


        // constructors and destructor

        template <typename Dimension, typename Canvas>
        picture(const Dimension& dimension, const Canvas& canvas)
        {}


    };


}}}


#endif
