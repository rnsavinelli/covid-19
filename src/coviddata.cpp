/*
 * coviddata.cpp
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

#include <fstream>
#include <string>

#include "coviddata.hpp"

struct coviddata
covidDataFormat(vector<string> content)
{
    struct coviddata newdata;

    newdata.date = content[DATE_REPORTED];

    newdata.country.code = content[COUNTRY_CODE];
    newdata.country.name = content[COUNTRY_NAME];
    newdata.country.region = content[WHO_REGION];

    newdata.cases.newdata = atoi(content[NEW_CASES].c_str());
    newdata.cases.cumulativedata = atoi(content[CUMULATIVE_CASES].c_str());

    newdata.deaths.newdata = atoi(content[NEW_DEATHS].c_str());
    newdata.deaths.cumulativedata = atoi(content[CUMULATIVE_DEATHS].c_str());

    return newdata;
}

int
covidDataStore(const vector<struct coviddata> data, string dest, unsigned int header_format)
{
    cout << "Saving file to " << dest << "... ";
    ofstream file;

    file.open(dest, ios::trunc);
    if (!file.is_open()) {
        return ERROR;
    }

    switch(header_format) {
        default:
        case NONE:
            file << CSV_HEADER << endl;
            for(struct coviddata element : data) {
            file << element.date << "," << element.country.code << ","
                << element.country.name << "," << element.country.region << ","
                << element.cases.newdata << "," << element.cases.cumulativedata << ","
                << element.deaths.newdata << "," << element.deaths.cumulativedata
                << endl;
            }
            break;

        case FILTERED:
             file << CSV_HEADER_FILTERED << endl;
            for(struct coviddata element : data) {
                file << element.country.name << ","
                    << element.cases.cumulativedata << ","
                    << element.deaths.cumulativedata
                    << endl;
            }
            break;
    }

    file.close();
    cout << "saved." << endl;

    return 0;
}
