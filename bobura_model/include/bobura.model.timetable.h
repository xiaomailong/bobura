/*! \file
    \brief The definition of bobura::model::timetable.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLE_H)
#define BOBURA_MODEL_TIMETABLE_H

#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/operators.hpp>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>
#include <boost/utility.hpp>

#include <tetengo2.cpp11.h>


namespace bobura { namespace model
{
    /*!
        \brief The class template for a timetable.

        \tparam String          A string type.
        \tparam StationLocation A station location type.
        \tparam StationInterval A station interval type.
        \tparam Train           A train type.
        \tparam ObserverSet     An observer set type.
    */
    template <
        typename String,
        typename StationLocation,
        typename StationInterval,
        typename Train,
        typename ObserverSet
    >
    class timetable :
        private boost::equality_comparable<timetable<String, StationLocation, StationInterval, Train, ObserverSet>>
    {
    public:
        // types

        //! The string type.
        typedef String string_type;

        //! The station location type.
        typedef StationLocation station_location_type;

        //! The station locations type.
        typedef std::vector<station_location_type> station_locations_type;

        //! The station interval type.
        typedef StationInterval station_interval_type;

        //! The station intervals type.
        typedef std::vector<station_interval_type> station_intervals_type;

        //! The train type.
        typedef Train train_type;

        //! The trains type.
        typedef std::vector<train_type> trains_type;

        //! The observer set type.
        typedef ObserverSet observer_set_type;


        // constructors and destructor

        /*!
            \brief Creates a timetalble.
        */
        timetable()
        :
        m_title(),
        m_station_locations(),
        m_down_trains(),
        m_up_trains(),
        m_observer_set()
        {}

        /*!
            \brief Creates a timetalble.

            \tparam InputIterator An input iterator for station locations.

            \param station_location_first The first iterator among station locations.
            \param station_location_last  The last iterator among station locations.
        */
        template <typename InputIterator>
        timetable(const InputIterator station_location_first, const InputIterator station_location_last)
        :
        m_title(),
        m_station_locations(station_location_first, station_location_last),
        m_down_trains(),
        m_up_trains(),
        m_observer_set()
        {}


        // functions

        /*!
            \brief Checks whether this is equal to another timetable.

            \param one     One timetable.
            \param another Another timetable.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const timetable& one, const timetable& another)
        {
            return
                one.m_station_locations == another.m_station_locations &&
                one.m_down_trains == another.m_down_trains &&
                one.m_up_trains == another.m_up_trains;
        }

        /*!
            \brief Returns the title.

            \return The title.
        */
        const string_type& title()
        const
        {
            return m_title;
        }

        /*!
            \brief Sets a title.

            \tparam S A string type.

            \param title A title.
        */
        template <typename S>
        void set_title(S&& title)
        {
            m_title = std::forward<S>(title);

            m_observer_set.changed()();
        }

        /*!
            \brief Returns the station locations.

            \return The station locations.
        */
        const station_locations_type& station_locations()
        const
        {
            return m_station_locations;
        }

        /*!
            \brief Inserts a station location.

            After the insertion, the station locations must be sequenced in ascending order.

            It also inserts a stop to the every train with uninitialized arrival and departure time and an empty
            platform, so that the count of the station locations coincides with the one of the every train stop.

            \tparam SL A station location type.

            \param position         A position where a station location is inserted.
            \param station_location A station location.

            \throw std::invalid_argument When the station locations are not sequenced in ascending order after the
                                         insertion.
        */
        template <typename SL>
        void insert_station_location(
            const typename station_locations_type::const_iterator position,
            SL&&                                                  station_location
        )
        {
            if (!can_insert_to(position, station_location))
                BOOST_THROW_EXCEPTION(std::invalid_argument("The insertion position is invalid."));

            const difference_type offset =
                std::distance<typename station_locations_type::const_iterator>(m_station_locations.begin(), position);

            m_station_locations.insert(to_mutable(position, m_station_locations), std::forward<SL>(station_location));

            std::for_each(
                m_down_trains.begin(),
                m_down_trains.end(),
                TETENGO2_CPP11_BIND(insert_train_stop, tetengo2::cpp11::placeholders_1(), offset)
            );
            std::for_each(
                m_up_trains.begin(),
                m_up_trains.end(),
                TETENGO2_CPP11_BIND(insert_train_stop, tetengo2::cpp11::placeholders_1(), offset)
            );

            m_observer_set.changed()();
        }

        /*!
            \brief Erases the station locations.

            It also erases stops from the every train, so that the count of the station locations coincides with the
            one of the every train stop.

            \param first A first iterator among the erased station locations.
            \param last  A last iterator among the erased station locations.
        */
        void erase_station_locations(
            const typename station_locations_type::const_iterator first,
            const typename station_locations_type::const_iterator last
        )
        {
            const difference_type first_offset =
                std::distance<typename station_locations_type::const_iterator>(m_station_locations.begin(), first);
            const difference_type last_offset =
                std::distance<typename station_locations_type::const_iterator>(m_station_locations.begin(), last);

            m_station_locations.erase(to_mutable(first, m_station_locations), to_mutable(last, m_station_locations));

            std::for_each(
                m_down_trains.begin(),
                m_down_trains.end(),
                TETENGO2_CPP11_BIND(erase_train_stops, tetengo2::cpp11::placeholders_1(), first_offset, last_offset)
            );
            std::for_each(
                m_up_trains.begin(),
                m_up_trains.end(),
                TETENGO2_CPP11_BIND(erase_train_stops, tetengo2::cpp11::placeholders_1(), first_offset, last_offset)
            );

            m_observer_set.changed()();
        }

        /*!
            \brief Returns the station intervals.

            \return The station intervals.
        */
        station_intervals_type station_intervals()
        const
        {
            if (m_station_locations.empty())
                return station_intervals_type(m_station_locations.size(), 3);

            const station_intervals_type down_intervals = down_station_intervals();
            const station_intervals_type up_intervals = up_station_intervals();

            station_intervals_type intervals;
            intervals.reserve(m_station_locations.size());
            std::transform(
                down_intervals.begin(),
                down_intervals.end(),
                up_intervals.begin(),
                std::back_inserter(intervals),
                select_station_interval
            );

            return intervals;
        }

        /*!
            \brief Returns the down trains.

            \return The down trains
        */
        const trains_type& down_trains()
        const
        {
            return m_down_trains;
        }

        /*!
            \brief Returns the up trains.

            \return The up trains
        */
        const trains_type& up_trains()
        const
        {
            return m_up_trains;
        }

        /*!
            \brief Inserts a down train.

            The count of train stops must coincide with the one of the station locations.

            \tparam T A train type.

            \param position A position where a down train is inserted.
            \param train    A down train.

            \throw std::invalid_argument When the count of the stops of a train does not coincide with the one of the
                                         station locations.
        */
        template <typename T>
        void insert_down_train(const typename trains_type::const_iterator position, T&& train)
        {
            insert_train_impl(m_down_trains, position, std::forward<T>(train));
        }

        /*!
            \brief Inserts a up train.

            The count of train stops must coincide with the one of the station locations.

            \tparam T A train type.

            \param position A position where a up train is inserted.
            \param train    A up train.

            \throw std::invalid_argument When the count of the stops of a train does not coincide with the one of the
                                         station locations.
        */
        template <typename T>
        void insert_up_train(const typename trains_type::const_iterator position, T&& train)
        {
            insert_train_impl(m_up_trains, position, std::forward<T>(train));
        }

        /*!
            \brief Erases the down trains.

            \param first A first iterator among the erased trains.
            \param last  A last iterator among the erased trains.
        */
        void erase_down_trains(
            const typename trains_type::const_iterator first,
            const typename trains_type::const_iterator last
        )
        {
            erase_trains_impl(m_down_trains, first, last);
        }

        /*!
            \brief Erases the up trains.

            \param first A first iterator among the erased trains.
            \param last  A last iterator among the erased trains.
        */
        void erase_up_trains(
            const typename trains_type::const_iterator first,
            const typename trains_type::const_iterator last
        )
        {
            erase_trains_impl(m_up_trains, first, last);
        }

        /*!
            \brief Returns the observer set.

            \return The observer set.
        */
        const observer_set_type& observer_set()
        const
        {
            return m_observer_set;
        }

        /*!
            \brief Returns the observer set.

            \return The observer set.
        */
        observer_set_type& observer_set()
        {
            return m_observer_set;
        }


    private:
        // types

        typedef typename train_type::stops_type::difference_type difference_type;

        typedef typename train_type::stop_type stop_type;

        typedef typename stop_type::time_type time_type;

        typedef typename time_type::time_span_type time_span_type;


        // static functions

        static void insert_train_stop(train_type& train, const difference_type offset)
        {
            train.insert_stop(
                train.stops().begin() + offset,
                typename train_type::stop_type(
                    train_type::stop_type::time_type::uninitialized(),
                    train_type::stop_type::time_type::uninitialized(),
                    typename train_type::stop_type::platform_type()
                )
            );
        }

        static void erase_train_stops(
            train_type&           train,
            const difference_type first_offset,
            const difference_type last_offset
        )
        {
            train.erase_stops(train.stops().begin() + first_offset, train.stops().begin() + last_offset);
        }

        template <typename Container>
        static typename Container::iterator to_mutable(
            const typename Container::const_iterator const_iter,
            Container&                               container
        )
        {
            typename Container::iterator mutable_iter = container.begin();
            std::advance(
                mutable_iter, std::distance<typename Container::const_iterator>(container.begin(), const_iter)
            );
            return mutable_iter;
        }

        static const station_interval_type& whole_day()
        {
            static const station_interval_type singleton =
                to_station_interval(time_span_type(time_span_type::seconds_of_whole_day()));
            return singleton;
        }

        static station_interval_type select_station_interval(
            const station_interval_type& interval1,
            const station_interval_type& interval2
        )
        {

            const station_interval_type selected = std::min(interval1, interval2);
            return selected < whole_day() ? selected : selected - whole_day();
        }

        static station_interval_type to_station_interval(
            const time_span_type&                            time_span,
            const typename station_intervals_type::size_type denominator = 1
        )
        {
            return station_interval_type(time_span.seconds(), 60 * denominator);
        }


        // variables

        string_type m_title;

        station_locations_type m_station_locations;

        trains_type m_down_trains;

        trains_type m_up_trains;

        observer_set_type m_observer_set;


        // functions

        bool can_insert_to(
            const typename station_locations_type::const_iterator position,
            const station_location_type&                          station_location
        )
        const
        {
            if (position != m_station_locations.begin() && !boost::prior(position)->before(station_location))
                return false;

            if (position != m_station_locations.end() && !station_location.before(*position))
                return false;

            return true;
        }

        template <typename T>
        void insert_train_impl(trains_type& trains, const typename trains_type::const_iterator position, T&& train)
        {
            if (train.stops().size() != m_station_locations.size())
            {
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument(
                        "The count of the train stops does not coincide with the one of the station locations."
                    )
                );
            }

            trains.insert(to_mutable(position, trains), std::forward<T>(train));

            m_observer_set.changed()();
        }

        void erase_trains_impl(
            trains_type&                               trains,
            const typename trains_type::const_iterator first,
            const typename trains_type::const_iterator last
        )
        {
            trains.erase(to_mutable(first, trains), to_mutable(last, trains));

            m_observer_set.changed()();
        }

        station_intervals_type down_station_intervals()
        const
        {
            station_intervals_type intervals(m_station_locations.size(), 3 + whole_day());

            for (typename station_intervals_type::size_type from = 0; from < intervals.size(); ++from)
            {
                if (!shortest_travel_time(m_down_trains, from, from))
                    continue;

                for (typename station_intervals_type::size_type to = from + 1; to < intervals.size(); ++to)
                {
                    const boost::optional<time_span_type> travel_time = shortest_travel_time(m_down_trains, from, to);
                    if (travel_time)
                    {
                        for (typename station_intervals_type::size_type i = from; i < to; ++i)
                        {
                            intervals[i] = to_station_interval(*travel_time, to - from);
                            if (to - from > 1)
                                intervals[i] += whole_day();
                        }
                        break;
                    }
                }
            }

            return intervals;
        }

        station_intervals_type up_station_intervals()
        const
        {
            station_intervals_type intervals(m_station_locations.size(), 3 + whole_day());

            for (typename station_intervals_type::size_type from = 0; from < intervals.size(); ++from)
            {
                if (!shortest_travel_time(m_up_trains, from, from))
                    continue;

                for (typename station_intervals_type::size_type to = from + 1; to < intervals.size(); ++to)
                {
                    const boost::optional<time_span_type> travel_time = shortest_travel_time(m_up_trains, to, from);
                    if (travel_time)
                    {
                        for (typename station_intervals_type::size_type i = from; i < to; ++i)
                        {
                            intervals[i] = to_station_interval(*travel_time, to - from);
                            if (to - from > 1)
                                intervals[i] += whole_day();
                        }
                        break;
                    }
                }
            }

            return intervals;
        }

        boost::optional<time_span_type> shortest_travel_time(
            const trains_type&                               trains,
            const typename station_intervals_type::size_type from,
            const typename station_intervals_type::size_type to
        )
        const
        {
            if (trains.empty())
                return boost::none;

            boost::optional<time_span_type> travel_time = calculate_travel_time(trains[0], from, to);
            for (typename trains_type::size_type i = 1; i < trains.size(); ++i)
            {
                const boost::optional<time_span_type> new_travel_time = calculate_travel_time(trains[i], from, to);
                if (!new_travel_time)
                    continue;

                if (!travel_time || *new_travel_time < *travel_time)
                    travel_time = *new_travel_time;
            }

            return travel_time ? boost::make_optional(*travel_time) : boost::none;
        }

        boost::optional<time_span_type> calculate_travel_time(
            const train_type&                                train, 
            const typename station_intervals_type::size_type from,
            const typename station_intervals_type::size_type to
        )
        const
        {
            const stop_type& from_stop = train.stops()[from];
            const time_type from_time =
                from_stop.departure() != time_type::uninitialized() ? from_stop.departure() : from_stop.arrival();
            if (from_time == time_type::uninitialized())
                return boost::none;

            const stop_type& to_stop = train.stops()[to];
            const time_type to_time =
                to_stop.arrival() != time_type::uninitialized() ? to_stop.arrival() : to_stop.departure();
            if (to_time == time_type::uninitialized())
                return boost::none;

            return boost::make_optional(to_time - from_time);
        }


    };


}}


#endif
