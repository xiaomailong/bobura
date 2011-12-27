/*! \file
    \brief Test of class tetengo2::gui::label.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

//#include <cstddef>
//#include <string>
//#include <utility>

#include <boost/test/unit_test.hpp>

#include "tetengo2.cpp11.h"
#include "tetengo2.detail.stub.alert.h"
#include "tetengo2.detail.stub.cursor.h"
#include "tetengo2.detail.stub.drawing.h"
#include "tetengo2.detail.stub.encoding.h"
#include "tetengo2.detail.stub.menu.h"
#include "tetengo2.detail.stub.message_handler.h"
#include "tetengo2.detail.stub.unit.h"
#include "tetengo2.detail.stub.widget.h"
#include "tetengo2.gui.abstract_window.h"
#include "tetengo2.gui.alert.h"
#include "tetengo2.gui.drawing.background.h"
#include "tetengo2.gui.drawing.color.h"
#include "tetengo2.gui.drawing.font.h"
#include "tetengo2.gui.drawing.picture.h"
#include "tetengo2.gui.drawing.widget_canvas.h"
#include "tetengo2.gui.menu.main_menu.h"
#include "tetengo2.gui.menu.menu.h"
#include "tetengo2.gui.menu_observer_set.h"
#include "tetengo2.gui.mouse_observer_set.h"
#include "tetengo2.gui.paint_observer_set.h"
#include "tetengo2.gui.system_cursor.h"
#include "tetengo2.gui.traits.abstract_window_traits.h"
#include "tetengo2.gui.traits.control_traits.h"
#include "tetengo2.gui.traits.label_traits.h"
#include "tetengo2.gui.traits.menu_traits.h"
#include "tetengo2.gui.traits.widget_traits.h"
#include "tetengo2.gui.traits.window_traits.h"
#include "tetengo2.gui.unit.em.h"
#include "tetengo2.gui.window.h"
#include "tetengo2.gui.window_observer_set.h"
#include "tetengo2.text.encoder.h"
#include "tetengo2.text.encoding.locale.h"

#include "tetengo2.gui.label.h"


namespace
{
    // types

    typedef tetengo2::detail::stub::encoding encoding_details_type;

    typedef
        tetengo2::text::encoding::locale<std::wstring, encoding_details_type>
        internal_encoding_type;

    typedef
        tetengo2::text::encoding::locale<std::wstring, encoding_details_type>
        ui_encoding_type;

    typedef
        tetengo2::text::encoder<internal_encoding_type, ui_encoding_type>
        ui_encoder_type;

    typedef
        tetengo2::text::encoding::locale<std::string, encoding_details_type>
        exception_encoding_type;

    typedef
        tetengo2::text::encoder<
            internal_encoding_type, exception_encoding_type
        >
        exception_encoder_type;

    typedef tetengo2::detail::stub::drawing drawing_details_type;

    typedef
        tetengo2::gui::drawing::font<
            std::wstring, std::size_t, drawing_details_type
        >
        font_type;

    typedef
        tetengo2::gui::drawing::picture<std::size_t, drawing_details_type>
        picture_type;

    typedef
        tetengo2::gui::drawing::background<drawing_details_type>
        background_type;

    typedef tetengo2::detail::stub::unit unit_details_type;

    typedef
        tetengo2::gui::unit::em<std::size_t, std::size_t, unit_details_type>
        unit_size_type;

    typedef std::pair<unit_size_type, unit_size_type> dimension_type;

    typedef
        tetengo2::gui::drawing::widget_canvas<
            std::size_t,
            std::wstring,
            dimension_type,
            ui_encoder_type,
            background_type,
            font_type,
            picture_type,
            drawing_details_type
        >
        canvas_type;

    typedef
        tetengo2::detail::stub::alert<std::string, ui_encoder_type>
        alert_details_type;

    typedef
        tetengo2::gui::alert<
            ui_encoder_type, exception_encoder_type, alert_details_type
        >
        alert_type;

    typedef
        tetengo2::gui::unit::em<
            std::ptrdiff_t, std::ptrdiff_t, unit_details_type
        >
        unit_difference_type;

    typedef
        std::pair<unit_difference_type, unit_difference_type> position_type;

    typedef
        tetengo2::gui::system_cursor<tetengo2::detail::stub::cursor>
        system_cursor_type;

    typedef
        tetengo2::gui::traits::widget_traits<
            canvas_type,
            alert_type,
            position_type,
            dimension_type,
            std::wstring,
            ui_encoder_type,
            background_type,
            font_type,
            system_cursor_type,
            tetengo2::gui::paint_observer_set<canvas_type>,
            tetengo2::gui::mouse_observer_set
        >
        widget_traits_type;

    typedef tetengo2::gui::drawing::color<unsigned char> color_type;

    typedef
        tetengo2::gui::traits::control_traits<widget_traits_type, color_type>
        control_traits_type;

    typedef
        tetengo2::gui::traits::label_traits<control_traits_type>
        label_traits_type;

    typedef tetengo2::detail::stub::widget widget_details_type;

    typedef
        tetengo2::detail::stub::message_handler<widget_details_type>
        message_handler_details_type;

    typedef
        tetengo2::gui::label<
            label_traits_type,
            widget_details_type,
            message_handler_details_type
        >
        label_type;

    typedef
        tetengo2::gui::traits::menu_traits<
            std::wstring,
            ui_encoder_type,
            tetengo2::gui::menu_observer_set
        >
        menu_traits_type;

    typedef tetengo2::detail::stub::menu menu_details_type;

    typedef
        tetengo2::gui::menu<menu_traits_type, menu_details_type> menu_type;

    typedef
        tetengo2::gui::main_menu<menu_traits_type, menu_details_type>
        main_menu_type;

    typedef
        tetengo2::gui::traits::abstract_window_traits<
            widget_traits_type,
            main_menu_type,
            tetengo2::gui::window_observer_set
        >
        abstract_window_traits_type;

    typedef
        tetengo2::gui::traits::window_traits<abstract_window_traits_type>
        window_traits_type;

    typedef
        tetengo2::gui::window<
            window_traits_type,
            widget_details_type,
            message_handler_details_type
        >
        window_type;


}


BOOST_AUTO_TEST_SUITE(test_tetengo2)
BOOST_AUTO_TEST_SUITE(gui)
BOOST_AUTO_TEST_SUITE(label)
    // test cases

    BOOST_AUTO_TEST_CASE(construction)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        const label_type label(parent);
    }

    BOOST_AUTO_TEST_CASE(fit_to_content)
    {
        BOOST_TEST_PASSPOINT();

        window_type parent;
        label_type label(parent);
        label.set_text(L"Tetengo");

        label.fit_to_content();

        const dimension_type dimension = label.dimension();

        const dimension_type answer_dimension =
            label.create_canvas()->calc_text_dimension(L"Tetengo");
        BOOST_CHECK(dimension == answer_dimension);
    }


BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
