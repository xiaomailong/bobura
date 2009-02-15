/*! \file
    \brief Test of class tetengo2::gui::dialog.

    Copyright (C) 2007-2009 kaoru

    $Id$
*/

#if !defined(TESTTETENGO2_GUI_WIN32_DIALOG_H)
#define TESTTETENGO2_GUI_WIN32_DIALOG_H

//#include <boost/test/unit_test.hpp> forward declaration
namespace boost { namespace unit_test {
    class test_suite;
}}


namespace test_tetengo2 { namespace gui { namespace win32
{
    class dialog
    {
    public:
        // static functions

        static boost::unit_test::test_suite* suite();

        static void construction();

        static void do_modal();


    };


}}}

#endif