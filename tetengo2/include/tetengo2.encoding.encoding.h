/*! \file
    \brief The definition of tetengo2::encoding::encoding.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_ENCODING_ENCODING_H)
#define TETENGO2_ENCODING_ENCODING_H


namespace tetengo2 { namespace encoding
{
    /*!
        \brief The class for a encoding.
    */
    class encoding
    {
    public:
        // types

        //! The pivot type.
        typedef std::wstring pivot_type;


        // constructors and destructor

        /*!
            \brief Destroys the encoding based on a encoding.
        */
        ~encoding()
        throw ()
        {}


    protected:
        // constructors

        /*!
            \brief Creates an encoding based on a encoding.

            \param encoding_based_on A encoding based on.
        */
        encoding()
        {}


    };


}}


#endif
