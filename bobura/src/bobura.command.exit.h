/*! \file
    \brief The definition of bobura::command::exit.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_EXIT_H)
#define BOBURA_COMMAND_EXIT_H

#include <memory>

#include <tetengo2.h>

#include "bobura.command.command_base.h"


namespace bobura { namespace command
{
    /*!
        \brief The class for an exit command.
    */
    class exit : public command_base
    {
    public:
        // types

        //! The base type.
        using base_type = command_base;


        // constructors and destructor

        /*!
            \brief Creates an exit command.
        */
        exit();

        /*!
            \brief Destroys the exit command.
        */
        virtual ~exit()
        TETENGO2_STDALT_NOEXCEPT;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual void execute_impl(model_type& model, abstract_window_type& parent)
        const override;


    };


}}


#endif
