/*! \file
    \brief The definition of bobura::command::train_kind.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_TRAINKIND_H)
#define BOBURA_COMMAND_TRAINKIND_H

#include <memory>

#include <boost/mpl/at.hpp>

#include <tetengo2.h>

#include <bobura/basic_type_list.h>
#include <bobura/command/command_base.h>
#include <bobura/model/train_kind.h>
#include <bobura/train_kind_dialog.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for a train kind command.

        \tparam Traits A traits type.
    */
    template <typename Traits>
    class train_kind : public command_base<Traits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The base type.
        using base_type = command_base<traits_type>;

        //! The train kind dialog type.
        using train_kind_dialog_type =
            train_kind_dialog<
                boost::mpl::at<common_type_list, type::size>::type,
                boost::mpl::at<ui_type_list, type::ui::dialog>::type,
                bobura::model::train_kind<boost::mpl::at<common_type_list, type::string>::type>,
                boost::mpl::at<ui_type_list, type::ui::fast_font>::type,
                boost::mpl::at<ui_type_list, type::ui::color>::type,
                boost::mpl::at<locale_type_list, type::locale::message_catalog>::type
            >;

        //! The dialog base type.
        using dialog_base_type = train_kind_dialog_type::base_type;

        //! The message catalog type.
        using message_catalog_type = train_kind_dialog_type::message_catalog_type;


        // constructors and destructor

        /*!
            \brief Create a train kind command.

            \param message_catalog A message catalog.
        */
        explicit train_kind(const message_catalog_type& message_catalog);

        /*!
            \brief Destroys a train kind command.
        */
        virtual ~train_kind()
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
