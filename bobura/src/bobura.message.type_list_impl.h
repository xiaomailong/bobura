/*! \file
    \brief The definition of bobura::message::type_list.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_TYPELISTIMPL_H)
#define BOBURA_MESSAGE_TYPELISTIMPL_H

#include <boost/mpl/pair.hpp>

#include <tetengo2.meta.assoc_list.h>

#include "bobura.message.about_dialog.h"
#include "bobura.message.diagram_picture_box.h"
#include "bobura.message.file_property_dialog.h"
#include "bobura.message.font_color_dialog.h"
#include "bobura.message.main_window.h"
#include "bobura.message.timetable_model.h"
#include "bobura.message.type_list.h"


namespace bobura { namespace message
{
    namespace timetable_model
    {
        /*!
            \brief The meta function for the type list of the timetable model messages.

            \tparam TimetableModel A timetable model type.
            \tparam DiagramView    A diagram view type.
            \tparam MainWindow     A main window type.
        */
        template <typename TimetableModel, typename DiagramView, typename MainWindow>
        class type_list
        {
        public:
            // types

            //! The type list for the timetable model.
            typedef
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::reset, reset<TimetableModel, DiagramView, MainWindow>>,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::changed, changed<TimetableModel, DiagramView, MainWindow>>,
                tetengo2::meta::assoc_list_end
                >>
                type;


        };
    }

    namespace main_window
    {
        /*!
            \brief The meta function for the type list of the main window messages.

            \tparam PopupMenu         A popup menu type.
            \tparam Command           A command type.
            \tparam Model             A model type.
            \tparam View              A view type.
            \tparam AbstractWindow    An abstract window type.
            \tparam DiagramPictureBox A diagram picture box type.
            \tparam ConfirmFileSave   A file save confirmation type.
        */
        template <
            typename PopupMenu,
            typename Command,
            typename Model,
            typename View,
            typename AbstractWindow,
            typename DiagramPictureBox,
            typename ConfirmFileSave
        >
        class type_list
        {
        public:
            // types

            //! The type list for the main window.
            typedef
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::popup_menu_selected, popup_menu_selected<PopupMenu, Command, Model>>,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<
                        type::menu_command_selected, menu_command_selected<Command, Model, AbstractWindow>
                    >,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::window_resized, window_resized<View, AbstractWindow, DiagramPictureBox>>,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::window_closing, window_closing<AbstractWindow, ConfirmFileSave>>,
                tetengo2::meta::assoc_list_end
                >>>>
                type;


        };
    }

    namespace diagram_picture_box
    {
        /*!
            \brief The meta function for the type list of the dialog picture box messages.

            \tparam PictureBox A picture box type.
            \tparam View       A view type.
            \tparam ViewZoom   A view zoom.
            \tparam Canvas     A canvas type.
        */
        template <typename PictureBox, typename View, typename ViewZoom, typename Canvas>
        class type_list
        {
        public:
            // types

            //! The type list for the diagram picture box.
            typedef
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::mouse_wheeled, mouse_wheeled<PictureBox, View, ViewZoom>>,
                tetengo2::meta::assoc_list<boost::mpl::pair<type::keyboard_key_down, keyboard_key_down<PictureBox>>,
                tetengo2::meta::assoc_list<boost::mpl::pair<type::paint_paint, paint_paint<Canvas, PictureBox, View>>,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::scroll_bar_scrolled, scroll_bar_scrolled<PictureBox>>,
                tetengo2::meta::assoc_list_end
                >>>>
                type;
        };
    }

    namespace file_property_dialog
    {
        /*!
            \brief The meta function for the type list of the file property dialog messages.

            \tparam Dialog A dialog type.
        */
        template <typename Dialog>
        class type_list
        {
        public:
            // types

            //! The type list for the file property dialog.
            typedef
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::ok_button_mouse_clicked, ok_button_mouse_clicked<Dialog>>,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::cancel_button_mouse_clicked, cancel_button_mouse_clicked<Dialog>>,
                tetengo2::meta::assoc_list_end
                >>
                type;


        };
    }

    namespace font_color_dialog
    {
        /*!
            \brief The meta function for the type list of the font and color dialog messages.

            \tparam Size    A size type.
            \tparam Dialog  A dialog type.
            \tparam ListBox A list box type.
        */
        template <typename Size, typename Dialog, typename ListBox>
        class type_list
        {
        public:
            // types

            //! The type list for the font and color dialog.
            typedef
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<
                        type::category_list_box_selection_changed, category_list_box_selection_changed<Size, ListBox>
                    >,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::ok_button_mouse_clicked, ok_button_mouse_clicked<Dialog>>,
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::cancel_button_mouse_clicked, cancel_button_mouse_clicked<Dialog>>,
                tetengo2::meta::assoc_list_end
                >>>
                type;


        };
    }

    namespace about_dialog
    {
        /*!
            \brief The meta function for the type list of the about dialog messages.

            \tparam Dialog A dialog type.
        */
        template <typename Dialog>
        class type_list
        {
        public:
            // types

            //! The type list for the about dialog.
            typedef
                tetengo2::meta::assoc_list<
                    boost::mpl::pair<type::ok_button_mouse_clicked, ok_button_mouse_clicked<Dialog>>,
                tetengo2::meta::assoc_list_end
                >
                type;


        };
    }


}}


#endif
