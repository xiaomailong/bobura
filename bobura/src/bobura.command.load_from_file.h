/*! \file
    \brief The definition of bobura::command::load_from_file.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_LOADFROMFILE_H)
#define BOBURA_COMMAND_LOADFROMFILE_H

#include "bobura.command.command_base.h"


namespace bobura { namespace command
{
    /*!
        \brief The class for a load-from-file command.
    */
    class load_from_file : public command_base
    {
    public:
        // types

        //! The base type.
        typedef command_base base_type;

        //! The file loading type.
        typedef boost::mpl::at<load_save_type_list, type::load_save::load_from_file>::type load_from_file_type;


        // constructors and destructor

        /*!
            \brief Creates a load-from-file command.

            \param load_from_file A file loading.
        */
        explicit load_from_file(const load_from_file_type& load_from_file);

        /*!
            \brief Destroys the load-from-file command.
        */
        ~load_from_file();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // virtual functions

        virtual bool enabled_impl(const model_type& model)
        const;

        /*!
            \brief Executes the command.

            \param model  A model.
            \param parent A parent window.
        */
        virtual void execute_impl(model_type& model, abstract_window_type& parent)
        const;


    };


}}


#endif
