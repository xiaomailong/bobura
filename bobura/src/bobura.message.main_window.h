/*! \file
    \brief The definition of bobura::message::main_window.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_MAINWINDOW_H)
#define BOBURA_MESSAGE_MAINWINDOW_H

#include <functional>
#include <utility>

#include <boost/scoped_ptr.hpp>

#include <tetengo2.generator.h>
#include <tetengo2.text.h>


namespace bobura { namespace message { namespace main_window
{
    /*!
        \brief The class for a menu observer of the main window.
        
        \tparam Command A command type.
    */
    template <typename Command>
    class menu : public tetengo2::generator<void>
    {
    public:
        // types

        //! The command type.
        typedef Command command_type;


        // constructors and destructor

        /*!
            \brief Creates a menu observer of the main window.

            \param command A command.
        */
        explicit menu(const command_type& command)
        :
        m_command(command)
        {}


        // functions

        /*!
            \brief Called when the menu is selected.
        */
        void operator()()
        const
        {
            m_command();
        }


    private:
        // variables

        command_type m_command;


    };


    /*!
        \brief The class template for a paint observer of the main window.
        
        \tparam Canvas        A canvas type.
        \tparam Position      A position type.
        \tparam PictureReader A picture reader type.
    */
    template <typename Canvas, typename Position, typename PictureReader>
    class paint : public std::unary_function<Canvas, void>
    {
    public:
        // types

        //! The canvas type.
        typedef Canvas canvas_type;

        //! The position type.
        typedef Position position_type;

        //! The picture reader type.
        typedef PictureReader picture_reader_type;


        // functions

        /*!
            \brief Called when the canvas needs to be repainted.

            \param canvas A canvas.
        */
        void operator()(canvas_type& canvas)
        const
        {
#if defined(_MSC_VER)
            picture_reader_type reader;
            const boost::scoped_ptr<typename canvas_type::picture_type>
            p_pic2(reader.read(L"D:\\kumakuma.jpg"));
            canvas.paint_picture(*p_pic2, position_type(0, 0));
#endif

            const font_type& dialog_font = font_type::dialog_font();
            canvas.draw_text(dialog_font.family(), position_type(2, 2));

#if defined(_MSC_VER)
            canvas.set_font(
                font_type(
                    string_type(TETENGO2_TEXT("みかちゃん")),
                    64,
                    false,
                    true,
                    true,
                    false
                )
            );
            canvas.draw_text(
                string_type(TETENGO2_TEXT("あいうえお")), position_type(4, 4)
            );
#endif

            const typename canvas_type::picture_type pic(
                std::make_pair(128, 96), canvas
            );
            canvas.paint_picture(pic, position_type(4, 8));
            canvas.paint_picture(pic, position_type(6, 12));
        }


    private:
        // types

        typedef typename canvas_type::string_type string_type;

        typedef typename canvas_type::font_type font_type;


    };


}}}


#endif
