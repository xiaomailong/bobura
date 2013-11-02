/*! \file
    \brief The definition of bobura::view::diagram::selection.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_SELECTION_H)
#define BOBURA_VIEW_DIAGRAM_SELECTION_H

#include <cassert>
#include <limits>
//#include <memory>
//#include <utility>

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>

#include <tetengo2.stdalt.h>


namespace bobura { namespace view { namespace diagram
{
     /*!
        \brief The class template for the diagram view selection.

        \tparam Station              A station type.
        \tparam Train                A train type.
        \tparam SelectionObserverSet A selection observer set type.
    */
    template <typename Station, typename Train, typename SelectionObserverSet>
    class selection : private boost::noncopyable
    {
    public:
        // types

        //! The station type.
        typedef Station station_type;

        //! The train type.
        typedef Train train_type;

        //! The stop index type.
        typedef typename train_type::stops_type::size_type stop_index_type;

        //! The selection observer set type.
        typedef SelectionObserverSet selection_observer_set_type;


        // constructors and destructor

        /*!
            \brief Creates a selection.
        */
        selection()
        :
        m_p_selected_station(nullptr),
        m_p_selected_train(nullptr),
        m_p_selection_observer_set(tetengo2::stdalt::make_unique<selection_observer_set_type>())
        {}

        /*!
            \brief Moves a selection.

            \param another Another selection.
        */
        selection(selection&& another)
        :
        m_p_selected_station(another.m_p_selected_station),
        m_p_selected_train(another.m_p_selected_train),
        m_p_selection_observer_set(std::move(another.m_p_selection_observer_set))
        {}


        // functions

        /*!
            \brief Checks whether the station is selected.

            \param station A station.

            \retval true  When the station is selected.
            \retval false Otherwise.
        */
        bool selected(const station_type& station)
        const
        {
            if (!m_p_selected_station)
                return false;

            return &station == m_p_selected_station;
        }

        /*!
            \brief Checks whether the train is selected.

            \param train                A train.
            \param departure_stop_index A departure stop index.
                                        Specity std::numeric_limits<stop_index_type>::max() to test whether any
                                        fragment is selected.
                                        Or specify boost::none to test whether a whole train is selected.

            \retval true  When the train is selected.
            \retval false Otherwise.
        */
        bool selected(const train_type& train, const boost::optional<stop_index_type>& departure_stop_index)
        const
        {
            if (!m_p_selected_train)
                return false;
            if (!departure_stop_index != !m_departure_stop_index)
                return false;
            if (!departure_stop_index)
            {
                assert(!m_departure_stop_index);
                return &train == m_p_selected_train;
            }
            return
                &train == m_p_selected_train &&
                (
                    *departure_stop_index == std::numeric_limits<stop_index_type>::max() ||
                    *departure_stop_index == *m_departure_stop_index
                );
        }

        /*!
            \brief Selects a station.

            \param station A station.
        */
        void select(const station_type& station)
        {
            unselect_all();

            m_p_selected_station = &station;

            m_p_selection_observer_set->station_selected()(station);
        }

        /*!
            \brief Selects a train.

            \param train                A train.
            \param down                 Set true when the train is downward. Otherwise the train is upward.
            \param departure_stop_index A departure stop index. Or specify boost::none when a whole train is selected.
        */
        void select(
            const train_type&                       train,
            const bool                              down,
            const boost::optional<stop_index_type>& departure_stop_index
        )
        {
            unselect_all();

            m_p_selected_train = &train;
            m_departure_stop_index = departure_stop_index;

            m_p_selection_observer_set->train_selected()(train, down, departure_stop_index);
        }

        /*!
            \brief Unselects all the items.
        */
        void unselect_all()
        {
            m_p_selected_station = nullptr;
            m_p_selected_train = nullptr;
            m_departure_stop_index = boost::none;

            m_p_selection_observer_set->all_unselected()();
        }

        /*!
            \brief Returns the selection observer set.

            \return The selection observer set.
        */
        const selection_observer_set_type& selection_observer_set()
        const
        {
            return *m_p_selection_observer_set;
        }

        /*!
            \brief Returns the selection observer set.

            \return The selection observer set.
        */
        selection_observer_set_type& selection_observer_set()
        {
            return *m_p_selection_observer_set;
        }


    private:
        // variables

        const station_type* m_p_selected_station;

        const train_type* m_p_selected_train;

        boost::optional<stop_index_type> m_departure_stop_index;

        std::unique_ptr<selection_observer_set_type> m_p_selection_observer_set;


    };


}}}


#endif
