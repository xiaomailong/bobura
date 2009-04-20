/*! \file
    \brief The definition of tetengo2::messages.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TETENGO2_MESSAGES_H)
#define TETENGO2_MESSAGES_H

#include <locale>
#include <string>

namespace tetengo2
{
    /*!
        \brief The class template for messages.

        It is a customized locale facet for messages.

        \tparam String A string type.
    */
    template <typename String>
    class messages : public std::messages<typename String::value_type>
    {
    public:
        // constructors and destructor

        /*!
            \brief Creates messages.
        */
        messages()
        {}

        virtual ~messages()
        throw ()
        {}


    protected:
        // functions
        
        /*!
            \brief Opens a message catalog.

            \param catalog_name A catalog name.
            \param locale       A locale.

            \return The catalog value.
        */
        virtual catalog do_open(
            const std::string& catalog_name,
            const std::locale& locale
        )
        const
        {
            return 0;
        }
        
        /*!
            \brief Returns the localized message.

            \param catalog_id      A catalog ID.
            \param set             A message set ID.
            \param message         A message ID.
            \param default_message A default message.

            \return The localized message.
        */
        virtual string_type do_get(
            const catalog      catalog_id,
            const int          set,
            const int          message,
            const string_type& default_message
        )
        const
        {
            return default_message;
        }

        /*!
            \brief Closes the message catalog.

            \param catalog_id A catalog ID.
        */
        virtual void do_close(const catalog catalog_id)
        const
        {

        }


    };


}

#endif
