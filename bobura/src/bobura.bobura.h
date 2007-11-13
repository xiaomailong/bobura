/*! \file
    \brief The definition of bobura::bobura.

    Copyright (C) 2007 kaoru

    $Id$
*/

#if !defined(BOBURA_BOBURA_H)
#define BOBURA_BOBURA_H

#include <memory>

#include <boost/concept_check.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

#include <tetengo2.nothrow.h>
#include <tetengo2.gui.GuiFactoryConcept.h>

#include "bobura.message.main_window_paint_observer.h"
#include "bobura.message.main_window_window_observer.h"


namespace bobura
{
    /*!
        \brief The class template for a bobura application.

        \param GuiFactory      An abstract factory type to create platform
                               specific GUI components. It must conform to
                               tetengo2::gui::GuiFactoryConcept<GuiFactory>.
        \param MessageLoop     A generator type for the message loop. It must
                               conform to
                               boost::GeneratorConcept<MessageLoop, int>.
        \param QuitMessageLoop A unary functor type for quitting the message
                               loop. It must conform to
                               boost::UnaryFunctionConcept<QuitMessageLoop, void, int>.
    */
    template <
        typename GuiFactory,
        typename MessageLoop,
        typename QuitMessageLoop
    >
    class bobura : private boost::noncopyable
    {
    private:
        // concept checks

        BOOST_CLASS_REQUIRE(GuiFactory, tetengo2::gui, GuiFactoryConcept);
        BOOST_CLASS_REQUIRE2(MessageLoop, int, boost, GeneratorConcept);
        BOOST_CLASS_REQUIRE3(
            QuitMessageLoop, void, int, boost, UnaryFunctionConcept
        );


    public:
        // types

        //! The abstract factory type to create platform specific GUI
        //! components.
        typedef GuiFactory gui_factory_type;


        // constructors and destructor

        /*!
            \brief Creates a bobura application.

            \param p_gui_factory An auto pointer to a GUI factory.
        */
        bobura(std::auto_ptr<const gui_factory_type> p_gui_factory)
        :
        m_p_gui_factory(p_gui_factory)
        {}

        /*!
            \brief Destroys the bobura application.
        */
        ~bobura()
        TETENGO2_NOTHROW
        {}


        // functions

        /*!
            \brief Runs the main process of the application.

            \return The exit status code.
        */
        int run()
        const
        {
            const boost::scoped_ptr<window_type> p_main_window(
                m_p_gui_factory->create_window()
            );

            set_message_observers(p_main_window.get());
            p_main_window->set_text(L"ぼうぶら テストプログラム");
            p_main_window->set_visible(true);

            return message_loop_type()();
        }


    private:
        //types

        typedef typename gui_factory_type::window_type window_type;

        typedef typename window_type::canvas_type canvas_type;

        typedef
            typename window_type::window_observer_type
            window_observer_type;

        typedef
            typename window_type::paint_observer_type
            paint_observer_type;

        typedef MessageLoop message_loop_type;

        typedef QuitMessageLoop quit_message_loop_type;


        // variables

        const boost::scoped_ptr<const gui_factory_type> m_p_gui_factory;


        // functions

        void set_message_observers(window_type* const p_window)
        const
        {
            p_window->add_window_observer(
                std::auto_ptr<window_observer_type> (
                    new message::main_window_window_observer<
                        quit_message_loop_type
                    >(quit_message_loop_type())
                )
            );

            p_window->add_paint_observer(
                std::auto_ptr<paint_observer_type> (
                    new message::main_window_paint_observer<canvas_type>()
                )
            );
        }


    };


}

#endif
