/*! \file
    \brief The definition of bobura::timetable_model.

    Copyright (C) 2007-2015 kaoru

    $Id$
*/

#include <cassert>
#include <memory>
#include <stdexcept>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/filesystem.hpp>
#include <boost/optional.hpp>
#include <boost/predef.h>
#include <boost/throw_exception.hpp>

#include <tetengo2.h>
#include <tetengo2.gui.h>

#include <bobura/timetable_model.h>
#include <bobura/type_list.h>


namespace bobura
{
    template <
        typename Size,
        typename Difference,
        typename String,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    class timetable_model<Size, Difference, String, OperatingDistance, Speed, Font>::impl : private boost::noncopyable
    {
    public:
        // types

        using timetable_type = typename timetable_model::timetable_type;

        using observer_set_type = typename timetable_model::observer_set_type;


        // constructors and destructor

        impl()
        :
        m_p_timetable(tetengo2::stdalt::make_unique<timetable_type>()),
        m_path(),
        m_changed(false),
        m_observer_set()
        {
            set_timetable_observer_set();
        }


        // functions

        const timetable_type& timetable()
        const
        {
            assert(m_p_timetable);
            return *m_p_timetable;
        }

        timetable_type& timetable()
        {
            assert(m_p_timetable);
            return *m_p_timetable;
        }

        void reset_timetable()
        {
            reset_timetable_impl(tetengo2::stdalt::make_unique<timetable_type>(), boost::none);
        }

        void reset_timetable(std::unique_ptr<timetable_type> p_timetable)
        {
            reset_timetable_impl(std::move(p_timetable), boost::none);
        }

        void reset_timetable(std::unique_ptr<timetable_type> p_timetable, boost::filesystem::path path)
        {
            reset_timetable_impl(std::move(p_timetable), boost::make_optional(std::move(path)));
        }

        bool has_path()
        const
        {
            return static_cast<bool>(m_path);
        }

        const boost::filesystem::path& path()
        const
        {
            if (!has_path())
                BOOST_THROW_EXCEPTION(std::logic_error("This model does not have a path."));

            return *m_path;
        }

        void set_path(boost::filesystem::path path)
        {
            m_path = boost::make_optional(std::move(path));
            m_changed = false;

            m_observer_set.reset()();
        }

        bool changed()
        const
        {
            return m_changed;
        }

        void set_changed(const bool changed)
        {
            m_changed = changed;

            m_observer_set.changed()();
        }

        const observer_set_type& observer_set()
        const
        {
            return m_observer_set;
        }

        observer_set_type& observer_set()
        {
            return m_observer_set;
        }


    private:
        // variables

        std::unique_ptr<timetable_type> m_p_timetable;

        boost::optional<boost::filesystem::path> m_path;

        bool m_changed;

        observer_set_type m_observer_set;


        // functions

        void reset_timetable_impl(
            std::unique_ptr<timetable_type>            p_timetable,
            boost::optional<boost::filesystem::path>&& path
        )
        {
            if (!p_timetable)
                BOOST_THROW_EXCEPTION(std::invalid_argument("Timetable is nullptr."));

            m_p_timetable = std::move(p_timetable);
            m_path = std::forward<boost::optional<boost::filesystem::path>>(path);
            m_changed = false;

            set_timetable_observer_set();

            m_observer_set.reset()();
        }

        void set_timetable_observer_set()
        {
            m_p_timetable->observer_set().changed().connect([this]() { this->set_changed(true); });
        }


    };


    template <
        typename Size,
        typename Difference,
        typename String,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    timetable_model<Size, Difference, String, OperatingDistance, Speed, Font>::timetable_model()
    :
    m_p_impl(tetengo2::stdalt::make_unique<impl>())
    {}

    template <
        typename Size,
        typename Difference,
        typename String,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    timetable_model<Size, Difference, String, OperatingDistance, Speed, Font>::~timetable_model()
    TETENGO2_STDALT_NOEXCEPT
    {}

    template <
        typename Size,
        typename Difference,
        typename String,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    const typename timetable_model<Size, Difference, String, OperatingDistance, Speed, Font>::timetable_type&
    timetable_model<Size, Difference, String, OperatingDistance, Speed, Font>::timetable()
    const
    {
        return m_p_impl->timetable();
    }

    template <
        typename Size,
        typename Difference,
        typename String,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    typename timetable_model<Size, Difference, String, OperatingDistance, Speed, Font>::timetable_type&
    timetable_model<Size, Difference, String, OperatingDistance, Speed, Font>::timetable()
    {
        return m_p_impl->timetable();
    }

    template <
        typename Size,
        typename Difference,
        typename String,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    void timetable_model<Size, Difference, String, OperatingDistance, Speed, Font>::reset_timetable()
    {
        m_p_impl->reset_timetable();
    }

    template <
        typename Size,
        typename Difference,
        typename String,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    void timetable_model<Size, Difference, String, OperatingDistance, Speed, Font>::reset_timetable(
        std::unique_ptr<timetable_type> p_timetable
    )
    {
        m_p_impl->reset_timetable(std::move(p_timetable));
    }

    template <
        typename Size,
        typename Difference,
        typename String,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    void timetable_model<Size, Difference, String, OperatingDistance, Speed, Font>::reset_timetable(
        std::unique_ptr<timetable_type> p_timetable,
        boost::filesystem::path         path
    )
    {
        m_p_impl->reset_timetable(std::move(p_timetable), std::move(path));
    }

    template <
        typename Size,
        typename Difference,
        typename String,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    bool timetable_model<Size, Difference, String, OperatingDistance, Speed, Font>::has_path()
    const
    {
        return m_p_impl->has_path();
    }

    template <
        typename Size,
        typename Difference,
        typename String,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    const boost::filesystem::path& timetable_model<Size, Difference, String, OperatingDistance, Speed, Font>::path()
    const
    {
        return m_p_impl->path();
    }

    template <
        typename Size,
        typename Difference,
        typename String,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    void timetable_model<Size, Difference, String, OperatingDistance, Speed, Font>::set_path(
        boost::filesystem::path path
    )
    {
        m_p_impl->set_path(std::move(path));
    }

    template <
        typename Size,
        typename Difference,
        typename String,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    bool timetable_model<Size, Difference, String, OperatingDistance, Speed, Font>::changed()
    const
    {
        return m_p_impl->changed();
    }

    template <
        typename Size,
        typename Difference,
        typename String,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    void timetable_model<Size, Difference, String, OperatingDistance, Speed, Font>::set_changed(const bool changed)
    {
        m_p_impl->set_changed(changed);
    }

    template <
        typename Size,
        typename Difference,
        typename String,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    const typename timetable_model<Size, Difference, String, OperatingDistance, Speed, Font>::observer_set_type&
    timetable_model<Size, Difference, String, OperatingDistance, Speed, Font>::observer_set()
    const
    {
        return m_p_impl->observer_set();
    }

    template <
        typename Size,
        typename Difference,
        typename String,
        typename OperatingDistance,
        typename Speed,
        typename Font
    >
    typename timetable_model<Size, Difference, String, OperatingDistance, Speed, Font>::observer_set_type&
    timetable_model<Size, Difference, String, OperatingDistance, Speed, Font>::observer_set()
    {
        return m_p_impl->observer_set();
    }


    namespace
    {
 #if BOOST_COMP_MSVC
       namespace application
        {
            using detail_type_list_type = type_list::detail_for_application;

            using common_type_list_type = type_list::common;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;

            using traits_type_list_type = type_list::traits<detail_type_list_type>;

        }
#endif

        namespace test
        {
            using detail_type_list_type = type_list::detail_for_test;

            using common_type_list_type = type_list::common;

            using ui_type_list_type = type_list::ui<detail_type_list_type>;

        }

    }

#if BOOST_COMP_MSVC
    template class timetable_model<
        typename application::common_type_list_type::size_type,
        typename application::common_type_list_type::difference_type,
        typename application::common_type_list_type::string_type,
        typename application::common_type_list_type::operating_distance_type,
        typename application::common_type_list_type::speed_type,
        typename application::ui_type_list_type::fast_font_type
    >;
#endif

    template class timetable_model<
        typename test::common_type_list_type::size_type,
        typename test::common_type_list_type::difference_type,
        typename test::common_type_list_type::string_type,
        typename test::common_type_list_type::operating_distance_type,
        typename test::common_type_list_type::speed_type,
        typename test::ui_type_list_type::font_type
    >;


}
