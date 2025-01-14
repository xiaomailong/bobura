/*! \file
    \brief The definition of bobura::model::serializer::reader.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_READER_H)
#define BOBURA_MODEL_SERIALIZER_READER_H

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2.h>

#include <bobura/model/timetable.h>


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a reader.

        \tparam Size              A size type.
        \tparam Difference        A difference type.
        \tparam String            A string type.
        \tparam ForwardIterator   A forward iterator type.
        \tparam OperatingDistance An operating distance type.
        \tparam Speed             A speed type.
        \tparam Font              A font type.
    */
    template <
        typename Size,
        typename Difference,
        typename String,
        typename ForwardIterator,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    class reader : private boost::noncopyable
    {
    public:
        // types

        //! The size type.
        using size_type = Size;

        //! The difference type.
        using difference_type = Difference;

        //! The string type.
        using string_type = String;

        //! The iterator type.
        using iterator = ForwardIterator;

        //! The operating distance type.
        using operating_distance_type = OperatingDistance;

        //! The speed type.
        using speed_type = Speed;

        //! The font type.
        using font_type = Font;

        //! The timetable type.
        using timetable_type =
            timetable<size_type, difference_type, string_type, operating_distance_type, speed_type, font_type>;

        //! The error type.
        enum class error_type
        {
            none,        //!< No error.
            canceled,    //!< Canceled.
            corrupted,   //!< Corrupted data.
            unsupported, //!< Unsupported format.
        };


        // constructors and destructor

        /*!
            \brief Destroys the reader.
        */
        virtual ~reader()
        TETENGO2_STDALT_NOEXCEPT;


        // functions

        /*!
            \brief Checks whether this reader selects a file type.

            \param first The first position of an input.
            \param last  The last position of an input.

            \retval true  When this reader selects the file type.
            \retval false Otherwise.
        */
        bool selects(iterator first, iterator last);

        /*!
            \brief Reads a timetable.

            When it cannot read a timetable, it returns nullptr.

            \param first The first position of an input.
            \param last  The last position of an input.
            \param error The error. (For output)

            \return A unique pointer to a timetable.
        */
        std::unique_ptr<timetable_type> read(iterator first, iterator last, error_type& error);


    protected:
        // constructors

        /*!
            \brief Creates a reader.
        */
        reader();


    private:
        // virtual functions

        virtual bool selects_impl(iterator first, iterator last)
        = 0;

        virtual std::unique_ptr<timetable_type> read_impl(iterator first, iterator last, error_type& error)
        = 0;


    };


}}}


#endif
