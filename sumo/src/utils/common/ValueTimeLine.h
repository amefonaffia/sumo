/****************************************************************************/
/// @file    ValueTimeLine.h
/// @author  Christian Roessel
/// @date    Sept 2002
/// @version $Id$
///
// A list of time ranges with assigned values
/****************************************************************************/
// SUMO, Simulation of Urban MObility; see http://sumo.sourceforge.net/
// Copyright (C) 2001-2011 DLR (http://www.dlr.de/) and contributors
/****************************************************************************/
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; either version 2 of the License, or
//   (at your option) any later version.
//
/****************************************************************************/
#ifndef ValueTimeLine_h
#define ValueTimeLine_h


// ===========================================================================
// included modules
// ===========================================================================
#include <map>
#include <cassert>
#include <utility>
#include <utils/common/SUMOTime.h>

#ifdef _MSC_VER
#include <windows_config.h>
#else
#include <config.h>
#endif


// ===========================================================================
// class definitions
// ===========================================================================
/**
 * @class ValueTimeLine
 *
 * A time line being a sorted container of non-overlapping time-ranges
 * with assigned values. The container is sorted by the first value of the
 * time-range while being filled. Every new inserted time range
 * may overwrite or split one or multiple earlier intervals.
 */
template<typename T>
class ValueTimeLine {
public:
    /// @brief Constructor
    ValueTimeLine() { }

    /// @brief Destructor
    ~ValueTimeLine() { }

    /** @brief Adds a value for a time interval into the container.
     *
     * Make sure that begin >= 0 and begin < end.
     *
     * @param[in] begin the start time of the time range (inclusive)
     * @param[in] end the end time of the time range (exclusive)
     * @param[in] value the value to store
     */
    void add(SUMOReal begin, SUMOReal end, T value) {
        assert(begin >= 0);
        assert(begin < end);
        // inserting strictly before the first or after the last interval (includes empty case)
        if (myValues.upper_bound(begin) == myValues.end() ||
                myValues.upper_bound(end) == myValues.begin()) {
            myValues[begin] = std::make_pair(true, value);
            myValues[end] = std::make_pair(false, value);
            return;
        }
        // our end already has a value
        typename TimedValueMap::iterator endIt = myValues.find(end);
        if (endIt != myValues.end()) {
            myValues.erase(myValues.upper_bound(begin), endIt);
            myValues[begin] = std::make_pair(true, value);
            return;
        }
        // we have at least one entry strictly before our end
        endIt = myValues.lower_bound(end);
        --endIt;
        ValidValue oldEndValue = endIt->second;
        myValues.erase(myValues.upper_bound(begin), myValues.lower_bound(end));
        myValues[begin] = std::make_pair(true, value);
        myValues[end] = oldEndValue;
    }

    /** @brief Returns the value for the given time.
     *
     * There is no bounds checking applied! If there was no value
     *  set, the return value is undefined, the method may even segfault.
     *
     * @param[in] the time for which the value should be retrieved
     * @return the value for the time
     */
    T getValue(SUMOReal time) const {
        assert(myValues.size() != 0);
        typename TimedValueMap::const_iterator it = myValues.upper_bound(time);
        assert(it != myValues.begin());
        --it;
        return it->second.second;
    }

    /** @brief Returns whether a value for the given time is known.
     *
     * This method implements the bounds checking. It returns true
     *  if and only if an explicit value was set for the given time
     *  using add. Default values stemming from fillGaps are not
     *  considered valid.
     *
     * @param[in] the time for which the value should be retrieved
     * @return whether a valid value was set
     */
    bool describesTime(SUMOReal time) const {
        typename TimedValueMap::const_iterator afterIt = myValues.upper_bound(time);
        if (afterIt == myValues.begin()) {
            return false;
        }
        --afterIt;
        return afterIt->second.first;
    }

    /** @brief Returns the time point at which the value changes.
     *
     * If the two input parameters lie in two consecutive time
     *  intervals, this method returns the point at which the
     *  interval changes. In any other case -1 is returned.
     *
     * @param[in] low the time in the first interval
     * @param[in] high the time in the second interval
     * @return the split point
     */
    SUMOReal getSplitTime(SUMOReal low, SUMOReal high) const {
        typename TimedValueMap::const_iterator afterLow = myValues.upper_bound(low);
        typename TimedValueMap::const_iterator afterHigh = myValues.upper_bound(high);
        --afterHigh;
        if (afterLow == afterHigh) {
            return afterLow->first;
        }
        return -1;
    }

    /** @brief Sets a default value for all unset intervals.
     *
     * @param[in] value the value to store
     * @param[in] extendOverBoundaries whether the first/last value should be valid for later / earlier times as well
     */
    void fillGaps(T value, bool extendOverBoundaries = false) {
        for (typename TimedValueMap::iterator it = myValues.begin(); it != myValues.end(); ++it) {
            if (!it->second.first) {
                it->second.second = value;
            }
        }
        if (extendOverBoundaries && !myValues.empty()) {
            typename TimedValueMap::iterator it = --myValues.end();
            if (!it->second.first) {
                myValues.erase(it, myValues.end());
            }
            value = myValues.begin()->second.second;
        }
        myValues[-1] = std::make_pair(false, value);
    }

private:
    /// @brief Value of time line, indicating validity.
    typedef std::pair<bool, T> ValidValue;

    /// @brief Sorted map from start of intervals to values.
    typedef std::map<SUMOReal, ValidValue> TimedValueMap;

    /// @brief The list of time periods (with values)
    TimedValueMap myValues;

};


#endif

/****************************************************************************/
