/*! \file
    \brief The definition of bobura::command::horizontally_zoom_out.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_HORIZONTALLYZOOMOUT_H)
#define BOBURA_COMMAND_HORIZONTALLYZOOMOUT_H

#include <memory>

#include <tetengo2.h>

#include <bobura/command/command_base.h>
#include <bobura/diagram_view.h>


namespace bobura { namespace command
{
    /*!
        \brief The class template for a horizontal zoom-out command.

        \tparam Traits            A traits type.
        \tparam CommandSetTraits  A command set traits type.
        \tparam MainWindowTraits  A main window traits type.
        \tparam DiagramViewTraits A diagram view traits type.
    */
    template <typename Traits, typename CommandSetTraits, typename MainWindowTraits, typename DiagramViewTraits>
    class horizontally_zoom_out : public command_base<Traits>
    {
    public:
        // types

        //! The traits type.
        using traits_type = Traits;

        //! The command set traits type.
        using command_set_traits_type = CommandSetTraits;

        //! The main window traits type.
        using main_window_traits_type = MainWindowTraits;

        //! The diagram view traits type.
        using diagram_view_traits_type = DiagramViewTraits;

        //! The base type.
        using base_type = command_base<traits_type>;

        //! The abstract window type.
        using abstract_window_type = typename base_type::abstract_window_type;

        //! The model type.
        using model_type = typename base_type::model_type;

        //! The diagram view type.
        using diagram_view_type = diagram_view<diagram_view_traits_type>;


        // constructors and destructor

        /*!
            \brief Creates a horizontal zoom-out command.

            \param diagram_view A diagram view.
        */
        explicit horizontally_zoom_out(diagram_view_type& diagram_view);

        /*!
            \brief Destroys the horizontal zoom-out command.
        */
        virtual ~horizontally_zoom_out()
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
