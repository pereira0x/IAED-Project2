/* José Pereira - ist1103252 */
#include "proj1.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/**
 * Sets the value of all aiports id to UNDEFINED_AIRPORT, and flights to 0,
 * this makes it easier to avoid unnecessary long iterations and finding which
 * indexs are actually definied airports.
 */
void setup_airports(airport airports[])
{
    int counter;
    for (counter = 0; counter < AIRPORT_MAX; counter++)
    {
        strcpy(airports[counter].id, UNDEFINED_AIRPORT);
    }
}

/**
 * Check if an airport id is a valid one.
 */
int verify_airport_id(char id[])
{
    int counter;
    for (counter = 0; counter < ID_LENGTH - 1; counter++)
    {
        /* Check if ID has anything else then uppercase chars. */
        if (islower(id[counter]) || !isalpha(id[counter]))
            return INVALID_AIPORT_ID;

        /* Check if ID has length 3 */
        if (strlen(id) != ID_LENGTH - 1)
            return INVALID_AIPORT_ID;
    }
    return 0;
}

/**
 * Adds an airport to the system.
 * Returns the ID that represents a new airport.
 * If the aiport id is invalid, returns INVALID_AIRPORT_ID.
 * If the airport already exists, returns DUPLICATE_AIRPORT_ID.
 * If the system has no more slots for new airports,
 * returns TOO_MANY_AIRPORTS_ID.
 */
int add_airport(airport airports[], char id[], char country[], char city[])
{
    int counter;

    /* Check if the airports's id is valid */
    switch (verify_airport_id(id))
    {
    case INVALID_AIPORT_ID:
        return INVALID_AIPORT_ID;
    default:
        break;
    }

    for (counter = 0; counter < AIRPORT_MAX; counter++)
    {
        /* Check if the ID already exists. */
        if (!(strcmp(airports[counter].id, id)))
            return DUPLICATE_AIRPORT_ID;

        /* Check if a slot is available for a new airport. */
        if (!(strcmp(airports[counter].id, UNDEFINED_AIRPORT)))
        {
            strcpy(airports[counter].id, id);
            strcpy(airports[counter].country, country);
            strcpy(airports[counter].city, city);
            airports[counter].flights_quantity = 0;
            return 0;
        }
    }

    /* If the function got here, it means there was no slots available */
    return TOO_MANY_AIPORTS_ID;
}

/**
 * Sorts the aiports by their ID, in alphabetical order.
 */
void sort_airports(airport airports[])
{
    int counter, counterAux;
    airport temp_airport;

    /* Loop through airports */
    for (counterAux = 0; counterAux < AIRPORT_MAX - 1; counterAux++)
    {
        if (!strcmp(airports[counterAux].id, UNDEFINED_AIRPORT))
            break;
        for (counter = 0; counter < AIRPORT_MAX - 1; counter++)
        {
            if (!strcmp(airports[counter].id, UNDEFINED_AIRPORT))
                break;
            /* Sort airports by alphabetical order of the ID */
            if (strcmp(airports[counter].id, airports[counter + 1].id) > 0)
            {
                temp_airport = airports[counter];
                airports[counter] = airports[counter + 1];
                airports[counter + 1] = temp_airport;
            }
        }
    }
}

/**
 * Lists all aiports in the system.
 */
void list_all_airports(airport airports[])
{
    int counter;
    for (counter = 0; counter < AIRPORT_MAX; counter++)
    {
        if (!strcmp(airports[counter].id, UNDEFINED_AIRPORT))
            break;
        printf("%s %s %s %d\n", airports[counter].id, airports[counter].city,
               airports[counter].country, airports[counter].flights_quantity);
    }
}

/**
 * Check if a airport of departure actually exists.
 */
int check_airport_departure_exist(airport airports[], char airport_departure[])
{
    int counter;
    for (counter = 0; counter < AIRPORT_MAX; counter++)
    {
        /* If it gets to UNDEFINED_AIRPORT, means it did not find the airport */
        if (!(strcmp(airports[counter].id, UNDEFINED_AIRPORT)))
            return NO_SUCH_AIRPORT_DEPARTURE_ID;

        /* Check if the ID exists. */
        if (!(strcmp(airports[counter].id, airport_departure)))
            break;
    }
    return 0;
}

/**
 * Check if a airport of arrival actually exists.
 */
int check_airport_arrival_exist(airport airports[], char airport_arrival[])
{
    int counter;
    for (counter = 0; counter < AIRPORT_MAX; counter++)
    {
        /* If it gets to UNDEFINED_AIRPORT, means it did not find the airport */
        if (!(strcmp(airports[counter].id, UNDEFINED_AIRPORT)))
            return NO_SUCH_AIRPORT_ARRIVAL_ID;

        /* Check if the ID exists. */
        if (!(strcmp(airports[counter].id, airport_arrival)))
            break;
    }
    return 0;
}