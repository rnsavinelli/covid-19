#ifndef COVIDDATA_H_

#include <iostream>
#include <string>
#include <vector>

#define CSV_HEADER "Date_reported, Country_code, Country, WHO_region, New_cases, Cumulative_cases, New_deaths, Cumulative_deaths"
#define CSV_HEADER_FILTERED "Country, New_cases, Cumulative_cases, New_deaths, Cumulative_deaths"

#define COVID_DATA "database/WHO-COVID-19-global-data.csv"
#define COVID_DEATHS "dashboards/COVID-19-global-deaths.csv"
#define COVID_CASES "dashboards/COVID-19-global-cases.csv"

using namespace std;

/*struct date {
    unsigned int year;
    unsigned int moth;
    unsigned int day;
};*/

struct country {
    string code;
    string name;
    string region;
};

struct datacount {
    int newdata;
    long cumulativedata;
};

struct coviddata {
    //struct date date;
    string date;
    struct country country;
    struct datacount cases;
    struct datacount deaths;
};

enum DATA_HEADERS {
    DATE_REPORTED,
    COUNTRY_CODE,
    COUNTRY_NAME,
    WHO_REGION,
    NEW_CASES,
    CUMULATIVE_CASES,
    NEW_DEATHS,
    CUMULATIVE_DEATHS
};

/* RANKING CRITERIA */
enum RANKING_CRITERIA {
    CASES,
    DEATHS,
    BOTH
};

/* CSV HEADER FORMAT */
enum CSV_HEADER_FORMAT {
    NONE,
    FILTERED
};

struct coviddata
coviddataformat(vector<string> content);

#endif
