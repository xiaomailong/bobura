/*! \file
    \brief The definition of bobura::model::serializer::json_writer.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_JSONWRITER_H)
#define BOBURA_MODEL_SERIALIZER_JSONWRITER_H

#include <boost/algorithm/string.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.text.h>

#include "bobura.model.serializer.writer.h"
#include "bobura.model.station_info.grade.h"


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a JSON writer.

        \tparam Timetable           A timetable type.
        \tparam StationGradeTypeSet A station grade type set.
        \tparam OutputStream        A output stream type.
        \tparam Encoder             An encoder type.
    */
    template <
        typename Timetable,
        typename StationGradeTypeSet,
        typename OutputStream,
        typename Encoder
    >
    class json_writer : public writer<OutputStream, Timetable>
    {
    public:
        // types

        //! The timetable type.
        typedef Timetable timetable_type;

        //! The station grade type set type.
        typedef StationGradeTypeSet station_grade_type_set_type;

        //! The output stream type.
        typedef OutputStream output_stream_type;

        //! The base type.
        typedef writer<output_stream_type, timetable_type> base_type;

        //! The encoder type.
        typedef Encoder encoder_type;


        // constructors and destructor

        /*!
            \brief Creates a JSON writer.
        */
        json_writer()
        :
        base_type()
        {}

        /*!
            \brief Destroys the json_writer.
        */
        virtual ~json_writer()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        // types

        typedef typename timetable_type::string_type string_type;

        typedef typename string_type::value_type char_type;

        typedef typename string_type::size_type size_type;


        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }

        static const string_type& comma()
        {
            static const string_type singleton(TETENGO2_TEXT(","));
            return singleton;
        }

        static const string_type& array_begin()
        {
            static const string_type singleton(TETENGO2_TEXT("["));
            return singleton;
        }

        static const string_type& array_end()
        {
            static const string_type singleton(TETENGO2_TEXT("]"));
            return singleton;
        }

        static const string_type& object_begin()
        {
            static const string_type singleton(TETENGO2_TEXT("{"));
            return singleton;
        }

        static const string_type& object_end()
        {
            static const string_type singleton(TETENGO2_TEXT("}"));
            return singleton;
        }

        static const string_type quote(const string_type& string)
        {
            static const string_type quotation_symbol(TETENGO2_TEXT("\""));
            return quotation_symbol + string + quotation_symbol;
        }

        static void new_line(
            const size_type     level,
            output_stream_type& output_stream
        )
        {
            output_stream << std::endl;
            output_stream <<
                string_type(level * 4, char_type(TETENGO2_TEXT(' ')));
        }

        static void write_object_entry(
            const string_type&  key,
            const string_type&  value,
            const size_type     level,
            output_stream_type& output_stream
        )
        {
            output_stream <<
                quote(key) <<
                string_type(TETENGO2_TEXT(": ")) <<
                quote(value);
        }

        static void write_header(
            const timetable_type& timetable,
            const size_type       level,
            output_stream_type&   output_stream
        )
        {
            output_stream << object_begin();

            new_line(level + 1, output_stream);
            write_object_entry(
                string_type(TETENGO2_TEXT("title")),
                timetable.title(),
                level + 1,
                output_stream
            );

            new_line(level, output_stream);
            output_stream << object_end();
        }

        static void write_station_locations(
            const timetable_type& timetable,
            const size_type       level,
            output_stream_type&   output_stream
        )
        {
            output_stream << array_begin();

            output_stream << array_end();
        }

        static void write_down_trains(
            const timetable_type& timetable,
            const size_type       level,
            output_stream_type&   output_stream
        )
        {
            output_stream << array_begin();

            output_stream << array_end();
        }

        static void write_up_trains(
            const timetable_type& timetable,
            const size_type       level,
            output_stream_type&   output_stream
        )
        {
            output_stream << array_begin();

            output_stream << array_end();
        }


        // virtual functions

        virtual void write_impl(
            const timetable_type& timetable,
            output_stream_type&   output_stream
        )
        {
            output_stream << array_begin();

            new_line(1, output_stream);
            write_header(timetable, 1, output_stream);
            output_stream << comma();

            new_line(1, output_stream);
            write_station_locations(timetable, 1, output_stream);
            output_stream << comma();

            new_line(1, output_stream);
            write_down_trains(timetable, 1, output_stream);
            output_stream << comma();

            new_line(1, output_stream);
            write_up_trains(timetable, 1, output_stream);

            new_line(0, output_stream);
            output_stream << array_end();

            new_line(0, output_stream);
        }


    };


}}}


#endif
