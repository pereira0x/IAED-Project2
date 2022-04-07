#ifndef MAIN_H
#define MAIN_H

/* constants */
#define ID_LENGTH 4
#define COUNTRY_LENGTH 31
#define CITY_LENGTH 51
#define AIRPORT_MAX 40

#define UNDEFINED_AIRPORT "zzz"

#define INVALID_AIPORT_ID -1
#define TOO_MANY_AIPORTS_ID -2
#define DUPLICATE_AIRPORT_ID -3

#define ERROR_INVALID_AIPORT_ID "invalid airport ID\n"
#define ERROR_TOO_MANY_AIPORTS "too many airports\n"
#define ERROR_DUPLICATE_AIRPORT "duplicate airport\n"
#define ADD_AIRPORT_SUCCESSFULLY "airport %s\n"

#define ERROR_NO_SUCH_AIRPORT_ID "%s: no such airport ID\n"

#define FLIGHT_CODE 7
#define FLIGHT_MAX 30000
#define UNDEFINED_FLIGHT "zzzzzz"
#define DATE_LENGTH 11
#define TIME_LENGTH 6
#define MAX_DURATION 12

#define INVALID_FLIGHT_CODE_ID -1
#define TOO_MANY_FLIGHTS_ID -2
#define INVALID_DURATION_ID -3
#define INVALID_CAPACITY_ID -4
#define INVALID_DATE_ID -5
#define NO_SUCH_AIRPORT_DEPARTURE_ID -6
#define NO_SUCH_AIRPORT_ARRIVAL_ID -7
#define FLIGHT_ALREADY_EXISTS_ID -8

#define ERROR_INVALID_FLIGHT_CODE "invalid flight code\n"
#define ERROR_FLIGHT_ALREADY_EXISTS "flight already exists\n"
#define ERROR_TOO_MANY_FLIGTS "too many flights\n"
#define ERROR_INVALID_DATE "invalid date\n"
#define ERROR_INVALID_DURATION "invalid duration\n"
#define ERROR_INVALID_CAPACITY "invalid capacity\n"

#define STARTING_DATE_DAY 1
#define STARTING_DATE_MONTH 1
#define STARTING_DATE_YEAR 2022

#define MAX_DATE_YEAR 2023
#define MIN_DATE_YEAR 2022

#define MIN_CAPACITY 10
#define MAX_CAPACITY 100

#define DATE2_IS_CLOSER -1

#define JAN 1
#define FEB 2
#define MAR 3
#define APR 4
#define MAY 5
#define JUN 6
#define JUL 7
#define AUG 8
#define SEP 9
#define OUT 10
#define NOV 11
#define DEC 12

/* structs */
typedef struct
{
    char id[ID_LENGTH];
    char country[COUNTRY_LENGTH];
    char city[CITY_LENGTH];
    int flights_quantity;
} airport;

typedef struct
{
    int hours;
    int minutes;
} time;

typedef struct
{
    int day;
    int month;
    int year;
} date;

typedef struct
{
    char code[FLIGHT_CODE];
    char airport_departure[ID_LENGTH];
    char airport_arrival[ID_LENGTH];
    date date_departure;
    time time_departure;
    time duration;
    int capacity;
} flight;

/* proj.c */
int handle_command(airport airports[], flight flights[], date system_date);
void handle_add_airport_command(airport airports[]);
void handle_list_airports_command(airport airports[]);
void handle_add_flight_command(airport airports[], flight flights[],
                               date system_date);
void handle_list_flight_departure_command(airport airports[], flight flights[]);
void handle_list_flight_arrival_command(airport airports[], flight flights[]);
void handle_forward_date_command();

/* airport.c */
void setup_airports(airport airports[]);
int add_airport(airport airports[], char id[], char country[], char city[]);
void sort_airports(airport airports[]);
void list_all_airports(airport airports[]);
int check_airport_departure_exist(airport airports[], char airport_departure[]);
int check_airport_arrival_exist(airport airports[], char airport_arrival[]);

/* date.c */
date setup_default_date(date system_date);
int check_dates(date departure_date, date system_date);
int find_older_date(date date1, date date2, time time1, time time2);
time forward_time(time time_departure, time duration);
date forward_date(date date_departure);

/* flights.c */
void setup_flights(flight flights[]);
int check_flight_code(char code[]);
int check_same_day_flights(flight flights[], char code[], date date_departure);
int check_duration(time duration);
int check_capacity(int capacity);
int add_flights(airport airports[], flight flights[], char code[],
                char airport_departure[],
                char airport_arrival[], date date_departure,
                time time_departure, time duration, int capacity,
                date system_date);
void sort_flights(flight flights[], int len);
void list_all_flights(flight flights[]);
void list_flights_sorted_departure(flight flights[], char airport_id[]);
void list_flights_sorted_arrival(flight flights[], char airport_id[]);

#endif