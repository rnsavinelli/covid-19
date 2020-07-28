#include <iostream>
#include <string>

#include "coviddata.hpp"

struct coviddata
coviddataformat(vector<string> content)
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
