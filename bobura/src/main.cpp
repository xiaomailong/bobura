/*! \file
    \brief The definition of the main function.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

//#include <cassert>
//#include <cstddef>
//#include <exception>
//#include <locale>
//#include <stdexcept>
//#include <string>
//#include <vector>

//#include <boost/filesystem.hpp>
//#include <boost/program_options.hpp>
//#include <boost/scoped_array.hpp>
//#include <boost/mpl/at.hpp>
//#include <boost/throw_exception.hpp>
//#include <boost/exception/all.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <windows.h>

//#include <tetengo2.text.h>

#include "bobura.type_list.h"


namespace
{
    std::string locale_info(const ::LCID id, const ::LCTYPE type)
    {
        const int length = ::GetLocaleInfoA(id, type, NULL, 0);
        if (length == 0)
        {
            BOOST_THROW_EXCEPTION(
                std::runtime_error("Can't get locale info.")
            );
        }

        boost::scoped_array<char> p_info(new char[length]);
        ::GetLocaleInfoA(id, type, p_info.get(), length);

        return std::string(p_info.get());
    }

    std::string ui_locale_name()
    {
        const ::LANGID language_id = ::GetUserDefaultLangID();
        const ::LCID locale_id = MAKELCID(language_id, SORT_DEFAULT);

        return locale_info(locale_id, LOCALE_SENGLANGUAGE) +
            "_" +
            locale_info(locale_id, LOCALE_SENGCOUNTRY);
    }

    template <typename Path>
    void set_locale(const Path& base_path)
    {
        const std::locale global_locale(
            std::locale(""),
            new typename boost::mpl::at<
                bobura::bobura_type_list, bobura::type::messages_facet
            >::type(
                base_path / TETENGO2_TEXT("messages"),
                std::locale(ui_locale_name().c_str())
            )
        );

        std::locale::global(global_locale);
    }

    template <typename CommandLineArgumentInputIterator>
    int run_application(
        CommandLineArgumentInputIterator command_line_argument_first,
        CommandLineArgumentInputIterator command_line_argument_last
    )
    {
        const typename boost::mpl::at<
            bobura::bobura_type_list, bobura::type::settings
        >::type settings(
            command_line_argument_first, command_line_argument_last
        );

        return typename boost::mpl::at<
            bobura::bobura_type_list, bobura::type::application
        >::type(settings).run();
    }


}


/*!
    \brief The entry point of the application.

    \param hInstance     Not used.
    \param hPrevInstance Not used.
    \param lpCmdLine     Not used.
    \param nCmdShow      Not used.

    \return The exit status code.
*/
int WINAPI wWinMain(
    const ::HINSTANCE hInstance,
    const ::HINSTANCE hPrevInstance,
    const ::LPWSTR    lpCmdLine,
    const int         nCmdShow
)
throw ()
{
    try
    {
        const std::vector<std::wstring> command_line_arguments =
            boost::program_options::split_winmain(::GetCommandLineW());
        assert(!command_line_arguments.empty());

        set_locale(
            boost::filesystem::wpath(command_line_arguments[0]).parent_path()
        );

        return ::run_application(
            command_line_arguments.begin(), command_line_arguments.end()
        );
    }
    catch (const boost::exception& e)
    {
        boost::mpl::at<
            bobura::bobura_type_list, bobura::type::alert
        >::type()(e);
        return 1;
    }
    catch (const std::exception& e)
    {
        boost::mpl::at<
            bobura::bobura_type_list, bobura::type::alert
        >::type()(e);
        return 1;
    }
    catch (...)
    {
        boost::mpl::at<
            bobura::bobura_type_list, bobura::type::alert
        >::type()();
        return 2;
    }
}
