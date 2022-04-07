/* José Pereira - ist1103252 */
#include "proj1.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/**
 * Initialize the system date with default values.
 */
date setup_default_date(date system_date)
{
    system_date.day = STARTING_DATE_DAY;
    system_date.month = STARTING_DATE_MONTH;
    system_date.year = STARTING_DATE_YEAR;
    return system_date;
}

/**
 * Check if the date is valid.
 */
int check_dates(date checkme_date, date system_date)
{
    int year = checkme_date.year, month = checkme_date.month,
        day = checkme_date.day;
    int system_year = system_date.year, system_month = system_date.month,
        system_day = system_date.day;

    /* Check if date is in the accepted range */
    if (year > MAX_DATE_YEAR || year < MIN_DATE_YEAR)
        return INVALID_DATE_ID;

    /* Check same year dates */
    if (year == system_year)
    {
        if (month < system_month)
            return INVALID_DATE_ID;

        if (month == system_month)
            if (day < system_day)
                return INVALID_DATE_ID;
    }

    /* Check when date year is bigger then system year */
    if (year > system_year)
    {
        if (month > system_month)
            return INVALID_DATE_ID;
        if (month == system_month)
            if (day > system_day)
                return INVALID_DATE_ID;
    }
    return 0;
}

/**
 * Find the older date.
 */
int find_older_date(date date1, date date2, time time1, time time2)
{
    int year1 = date1.year, month1 = date1.month, day1 = date1.day;
    int year2 = date2.year, month2 = date2.month, day2 = date2.day;
    int hours1 = time1.hours, minutes1 = time1.minutes;
    int hours2 = time2.hours, minutes2 = time2.minutes;

    /* If the date 2 year is bigger than date 1 year */
    if (year2 > year1)
        return 0;
    /* If the date 2 year is lower than date 1 year */
    if (year2 < year1)
        return DATE2_IS_CLOSER;
    /* If the date 2 year is equal to date 1 year */
    if (year2 == year1)
    {
        if (month2 < month1)
            return DATE2_IS_CLOSER;
        else if (month2 == month1)
        {
            if (day2 < day1)
            {
                return DATE2_IS_CLOSER;
            }
            else if (day2 == day1)
            {
                if (hours2 < hours1)
                    return DATE2_IS_CLOSER;
                else if (hours2 == hours1)
                {
                    if (minutes2 < minutes1)
                        return DATE2_IS_CLOSER;
                    else
                        return 0;
                }
                else
                    return 0;
            }
            else
                return 0;
        }
        else
            return 0;
    }
    return 0;
}

/**
 * Add duration to time, get arrival time.
 */
time forward_time(time time_departure, time duration)
{
    int time_hours, time_minutes, duration_hours, duration_minutes;
    int time_arrival_hours = 0, time_arrival_minutes = 0;
    time time_arrival;
    time_hours = time_departure.hours, time_minutes = time_departure.minutes;
    duration_hours = duration.hours, duration_minutes = duration.minutes;

    /* Check if adding minutes will result in an hour passing by */
    if (time_minutes + duration_minutes > 59)
    {
        time_arrival_minutes = (time_minutes + duration_minutes) % 60;
        time_arrival_hours += 1;
    }
    else
        time_arrival_minutes = time_minutes + duration_minutes;

    /* Check if adding hours will result in a day passing by */
    if (time_hours + duration_hours > 23)
    {
        time_arrival_hours -= 24;
        time_arrival_hours += duration_hours + time_hours;
    }
    else
        time_arrival_hours += time_hours + duration_hours;

    /* Define time arrival attributes. */
    if (time_arrival_hours == 24)
        time_arrival_hours = 0;
    time_arrival.hours = time_arrival_hours;
    time_arrival.minutes = time_arrival_minutes;
    return time_arrival;
}

/**
 * Get the next day date.
 */
date forward_date(date date_departure)
{
    int year, month, day;
    date arrival;
    year = date_departure.year, month = date_departure.month;
    day = date_departure.day;

    /* If the next day is a new year */
    if (day == 31 && month == DEC)
    {
        arrival.year = year + 1, arrival.month = 1, arrival.day = 1;
        return arrival;
    }
    /* If the next day is a new month of a 31 days month. */
    else if (day == 31 && (month == JAN || month == MAR || month == MAY ||
                           month == JUL || month == AUG || month == OUT))
    {
        arrival.day = 1, arrival.month = month + 1, arrival.year = year;
        return arrival;
    }
    /* If the next day is a new month of a 30 days month. */
    else if (day == 30 && (month == APR || month == JUN || month == SEP ||
                           month == NOV))
    {
        arrival.day = 1, arrival.month = month + 1, arrival.year = year;
        return arrival;
    }
    /* If the next day is a new month of a 28 days month (february). */
    else if (day == 28 && month == FEB)
    {
        arrival.day = 1, arrival.month = month + 1, arrival.year = year;
        return arrival;
    }
    else
    {
        arrival.day = day + 1, arrival.month = month, arrival.year = year;
        return arrival;
    }
}