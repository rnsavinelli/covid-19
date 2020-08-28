/*
 * coviddata.hpp
 *
 * Copyright 2020 Roberto Nicolás Savinelli <rnsavinelli@est.frba.utn.edu.ar>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */

#ifndef COVIDDATA_H_
#define COVIDDATA_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#define CSV_HEADER "Date_reported, Country_code, Country, WHO_region, New_cases, Cumulative_cases, New_deaths, Cumulative_deaths"
#define CSV_HEADER_FILTERED "Country, Cumulative_cases, Cumulative_deaths"

#define COVID_DATA "database/WHO-COVID-19-global-data.csv"

#define ERROR -1

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

enum RANKING_CRITERIA {
    CASES,
    DEATHS,
    BOTH
};

enum CSV_HEADER_FORMAT {
    FILTERED,
    NONE
};

struct coviddata
covidDataFormat(vector<string> content);

int
covidDataStore(const vector<struct coviddata> data, string dest, unsigned int header_format);

#endif
