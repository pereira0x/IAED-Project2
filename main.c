/* José Pereira - ist1103252 */
#include "proj1.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* global variable: system date */
date system_date;
int main()
{
    airport airports[AIRPORT_MAX];
    flight flights[FLIGHT_MAX];
    system_date = setup_default_date(system_date);

    setup_airports(airports);
    setup_flights(flights);
    /* execute program until the user sends the 'q' command */
    while (handle_command(airports, flights, system_date))
    {
    }

    return 0;
}

/**
 * Handles command input.
 * Returns 1 if the program should continue after running the command.
 * Otherwise, returns 0.
 */
int handle_command(airport airports[], flight flights[], date system_date)
{
    char command = getchar();

    switch (command)
    {
    case 'a':
        handle_add_airport_command(airports);
        return 1;
    case 'l':
        handle_list_airports_command(airports);
        return 1;
    case 'v':
        handle_add_flight_command(airports, flights, system_date);
        return 1;
    case 'p':
        handle_list_flight_departure_command(airports, flights);
        return 1;
    case 'c':
        handle_list_flight_arrival_command(airports, flights);
        return 1;
    case 't':
        handle_forward_date_command();
        return 1;
    case 'q':
        /* stop the program */
        return 0;
    default:
        /* ignore undefined commands */
        return 1;
    }
}

/**
 * Handles the 'a' command.
 * Adds to the system a new airport with the specified id, country and
 * city.
 * input format: a <IDAirport> <country> <city>
 * output format: airport <IDAirport>
 */
void handle_add_airport_command(airport airports[])
{
    int value, counter = 0;
    char c, id[ID_LENGTH], country[COUNTRY_LENGTH], city[CITY_LENGTH];

    scanf("%s %s", id, country);
    c = getchar();
    /* Get the airport city, which can be more then just one word. */
    while ((c = getchar()) != '\n' && counter < CITY_LENGTH - 1)
    {
        city[counter] = c;
        counter++;
    }
    city[counter] = '\0';

    /* Add aiport to the airport system */
    value = add_airport(airports, id, country, city);

    switch (value)
    {
    case INVALID_AIPORT_ID:
        printf(ERROR_INVALID_AIPORT_ID);
        break;
    case TOO_MANY_AIPORTS_ID:
        printf(ERROR_TOO_MANY_AIPORTS);
        break;
    case DUPLICATE_AIRPORT_ID:
        printf(ERROR_DUPLICATE_AIRPORT);
        break;
    default:
        printf(ADD_AIRPORT_SUCCESSFULLY, id);
        break;
    }
}

/**
 * Handles the 'l' command.
 * Lists the airports.
 * input format: l [<IDAairport> <IDAirport> ...]
 * output format: <IDAirport> <city> <country> #flights
 * If no arguments are passed, list all airport in ID's alphabetically order.
 * If multiplate arguments are passed, list airport in order of input.
 */
void handle_list_airports_command(airport airports[])
{
    int counter, empty = 0;
    char c, id[ID_LENGTH];

    while ((c = getchar()) != '\n')
    {
        counter = 0;
        scanf("%s", id);
        /* Find the index of first undefinied airport */
        while (strcmp(airports[counter].id, id) && counter < AIRPORT_MAX - 1)
            counter++;
        /* If it reached the end of airports, it means there was no
        sucessful match */
        if (counter == AIRPORT_MAX - 1)
        {
            printf(ERROR_NO_SUCH_AIRPORT_ID, id);
            empty++;
            continue;
            ;
        }
        else
        {
            printf("%s %s %s %d\n", airports[counter].id,
                   airports[counter].city, airports[counter].country,
                   airports[counter].flights_quantity);
            empty++;
        }
    }
    /* If it's just the 'l' command without arguments, list all airports
    sorted by their id. */
    if (!empty)
    {
        sort_airports(airports);
        list_all_airports(airports);
    }
}

/**
 * Handles the 'v' command.
 * Adds a flight to the system or lists all flights.
 * input format: v [<code> <airport_departure> <airport_arrival>
 * <date_departure> <time_departure> <duration> <capacity>]
 * output format: <code> <airport_departure> <airport_arrival>
 * <date_departure> <time_departure>
 * If no arguments are passed, list all flights.
 */
void handle_add_flight_command(airport airports[], flight flights[],
                               date system_date)
{
    char c, code[FLIGHT_CODE], airport_departure[ID_LENGTH],
        airport_arrival[ID_LENGTH];
    int capacity, value, counter, empty = 0;
    int departure_day, departure_month, departure_year;
    int departure_hour, departure_minutes;
    int duration_hour, duration_minutes;
    date date_departure;
    time time_departure, duration;

    while ((c = getchar()) != '\n')
    {
        /* Get flight attributes. */
        scanf("%s %s %s %d-%d-%d %d:%d %d:%d %d", code, airport_departure,
              airport_arrival, &departure_day, &departure_month,
              &departure_year, &departure_hour, &departure_minutes,
              &duration_hour, &duration_minutes, &capacity);

        /* Define flight attributes .*/
        date_departure.day = departure_day;
        date_departure.month = departure_month;
        date_departure.year = departure_year;

        time_departure.hours = departure_hour;
        time_departure.minutes = departure_minutes;

        duration.hours = duration_hour;
        duration.minutes = duration_minutes;

        empty++;
    }

    /* If it's just the 'v' command without arguments, list all flights,
    in order of input. */
    if (!empty)
    {
        list_all_flights(flights);
        return;
    }

    /* Add flight to the airport system */
    value = add_flights(airports, flights, code, airport_departure, airport_arrival,
                        date_departure, time_departure, duration, capacity,
                        system_date);

    switch (value)
    {
    case INVALID_FLIGHT_CODE_ID:
        printf(ERROR_INVALID_FLIGHT_CODE);
        break;
    case TOO_MANY_AIPORTS_ID:
        printf(ERROR_TOO_MANY_FLIGTS);
        break;
    case INVALID_DURATION_ID:
        printf(ERROR_INVALID_DURATION);
        break;
    case INVALID_CAPACITY_ID:
        printf(ERROR_INVALID_CAPACITY);
        break;
    case INVALID_DATE_ID:
        printf(ERROR_INVALID_DATE);
        break;
    case NO_SUCH_AIRPORT_DEPARTURE_ID:
        printf(ERROR_NO_SUCH_AIRPORT_ID, airport_departure);
        break;
    case NO_SUCH_AIRPORT_ARRIVAL_ID:
        printf(ERROR_NO_SUCH_AIRPORT_ID, airport_arrival);
        break;
    case FLIGHT_ALREADY_EXISTS_ID:
        printf(ERROR_FLIGHT_ALREADY_EXISTS);
        break;
    default:
        /* Increment the number of flights in the departure airport. */
        for (counter = 0; counter < AIRPORT_MAX; counter++)
        {
            if (!(strcmp(airports[counter].id, airport_departure)))
            {
                airports[counter].flights_quantity += 1;
                break;
            }
        }
    }
}

/**
 * Handles the 'p' command.
 * Lists the flights with departure airport of IDairport.
 * input format: p <IDAirport>
 * output format: <code> <IDAirport Arrival> <date_departure> <time_departure>
 * If no arguments are passed, list all airport in ID's alphabetically order.
 * If multiplate arguments are passed, list airport in order of input.
 */
void handle_list_flight_departure_command(airport airports[], flight flights[])
{
    char airport_id[ID_LENGTH];

    scanf("%s", airport_id);
    switch (check_airport_departure_exist(airports, airport_id))
    {
    case NO_SUCH_AIRPORT_DEPARTURE_ID:
        printf(ERROR_NO_SUCH_AIRPORT_ID, airport_id);
        break;
    default:
        list_flights_sorted_departure(flights, airport_id);
        break;
    }
}

/**
 * Handles the 'c' command.
 * Lists the flights with arrival airport of IDairport.
 * input format: p <IDAirport>
 * output format: <code> <IDAirport departure> <date_arrival> <time_arrival>
 * If no arguments are passed, list all airport in ID's alphabetically order.
 * If multiplate arguments are passed, list airport in order of input.
 */
void handle_list_flight_arrival_command(airport airports[], flight flights[])
{
    char airport_id[ID_LENGTH];
    scanf("%s", airport_id);

    switch (check_airport_arrival_exist(airports, airport_id))
    {
    case NO_SUCH_AIRPORT_ARRIVAL_ID:
        printf(ERROR_NO_SUCH_AIRPORT_ID, airport_id);
        break;
    default:
        list_flights_sorted_arrival(flights, airport_id);
        break;
    }
}

/**
 * Handles the 't' command.
 * Forwards the system date.
 * input format: t <date>
 * output format: <date>
 */
void handle_forward_date_command()
{
    int day, month, year;
    date new_date;

    /* Get new date attributes */
    scanf("%d-%d-%d", &day, &month, &year);
    /* Define new date attributes */
    new_date.day = day;
    new_date.month = month;
    new_date.year = year;

    /* Check if new date is a valid date */
    switch (check_dates(new_date, system_date))
    {
    case INVALID_DATE_ID:
        printf(ERROR_INVALID_DATE);
        break;

    default:
        /* Change system date to the new date */
        system_date.day = new_date.day;
        system_date.month = new_date.month;
        system_date.year = new_date.year;
        printf("%02d-%02d-%04d\n", system_date.day, system_date.month,
               system_date.year);
        break;
    }
}
