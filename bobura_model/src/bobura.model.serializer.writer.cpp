/*! \file
    \brief The definition of bobura::model::serializer::writer.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <boost/filesystem.hpp>
#include <boost/predef.h>
#include <boost/utility.hpp>

#include <tetengo2.h>

#include <bobura/model/serializer/writer.h>
#include <bobura/type_list.h>


namespace bobura { namespace model { namespace serializer
{
    template <
        typename Size,
        typename Difference,
        typename String,
        typename OutputStream,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    writer<Size, Difference, String, OutputStream, OperatingDistance, Speed, Font>::~writer()
    TETENGO2_STDALT_NOEXCEPT
    {}

    template <
        typename Size,
        typename Difference,
        typename String,
        typename OutputStream,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    boost::filesystem::path writer<Size, Difference, String, OutputStream, OperatingDistance, Speed, Font>::extension()
    const
    {
        return extension_impl();
    }

    template <
        typename Size,
        typename Difference,
        typename String,
        typename OutputStream,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    bool writer<Size, Difference, String, OutputStream, OperatingDistance, Speed, Font>::selects(
        const boost::filesystem::path& path
    )
    const
    {
        return selects_impl(path);
    }

    template <
        typename Size,
        typename Difference,
        typename String,
        typename OutputStream,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    void writer<Size, Difference, String, OutputStream, OperatingDistance, Speed, Font>::write(
        const timetable_type& timetable,
        output_stream_type&   output_stream
    )
    {
        write_impl(timetable, output_stream);
    }

    template <
        typename Size,
        typename Difference,
        typename String,
        typename OutputStream,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    writer<Size, Difference, String, OutputStream, OperatingDistance, Speed, Font>::writer()
    {}

    template <
        typename Size,
        typename Difference,
        typename String,
        typename OutputStream,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    bool writer<Size, Difference, String, OutputStream, OperatingDistance, Speed, Font>::selects_impl(
        const boost::filesystem::path& path
    )
    const
    {
        using path_string_type = typename boost::filesystem::path::string_type;

        const auto path_string = path.native();
        const auto extension_string = extension_impl().native();
        if (path_string.length() < extension_string.length())
            return false;
            
        const path_string_type path_extension_string{
            boost::prior(path_string.end(), extension_string.length()), path_string.end()
        };

        return path_extension_string == extension_string;
    }


    namespace
    {
 #if BOOST_COMP_MSVC
       namespace application
        {
            using detail_type_list_type = type_list::detail_for_application;

            using common_type_list_type = type_list::common;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;

        }
#endif

        namespace test
        {
            using detail_type_list_type = type_list::detail_for_test;

            using common_type_list_type = type_list::common;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;

        }

    }

#if BOOST_COMP_MSVC
    template class writer<
        typename application::common_type_list_type::size_type,
        typename application::common_type_list_type::difference_type,
        typename application::common_type_list_type::string_type,
        typename application::common_type_list_type::output_stream_type,
        typename application::common_type_list_type::operating_distance_type,
        typename application::common_type_list_type::speed_type,
        typename application::ui_type_list_type::fast_font_type
    >;
#endif

    template class writer<
        typename test::common_type_list_type::size_type,
        typename test::common_type_list_type::difference_type,
        typename test::common_type_list_type::string_type,
        typename test::common_type_list_type::output_stream_type,
        typename test::common_type_list_type::operating_distance_type,
        typename test::common_type_list_type::speed_type,
        typename test::ui_type_list_type::font_type
    >;


}}}
