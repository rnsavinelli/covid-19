#include <iostream>
#include <limits>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#define CSV_HEADER "Date_reported, Country_code, Country, WHO_region, New_cases, Cumulative_cases, New_deaths, Cumulative_deaths"
#define CSV_HEADER_FILTERED "Country, New_cases, Cumulative_cases, New_deaths, Cumulative_deaths"

#define DASHBOARDS_PREFIX "./dashboards/"

#define COVID_DATA "database/WHO-COVID-19-global-data.csv"
#define COVID_DEATHS "dashboards/COVID-19-global-deaths.csv"
#define COVID_CASES "dashboards/COVID-19-global-cases.csv"

#define UPDATE_DATABASE "./updatedatabase.sh"
#define GRAPH_DASHBOARD "./graph.sh"
#define CREATE_DIR "mkdir -p "

#define R_INSTALLED_ 1

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

enum FILTERING_CRITERIA {
    NONE,
    FILTERED
};

enum MENU_ITEMS {
    DASHBOARD,
    COUNTRYINFO,
    COUNTRYGRAPH
};

vector<string>
CSVlineparser(string line)
{
    vector<string> vec;
    string tmp;
    stringstream str_strm(line.c_str());

    while(getline(str_strm, tmp, ',')) {
        vec.push_back(tmp);
    }

    return vec;
}

struct coviddata
dataformat(vector<string> content)
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


void
savedata(vector<struct coviddata> &dest, struct coviddata src)
{
    dest.push_back(src);
}

int
retrievecountrylist(string file_name, vector<struct coviddata> &data)
{
    ifstream file;
    string line;

    file.open(file_name);

    cout << "Opening \"" << file_name << "\"" << "... ";
    if(!file.is_open()) {
        perror("file.open()");
        return ERROR;
    }
    cout << "done." << endl;

    cout << "Reading data... ";
    getline(file, line, '\n'); /* ignore header */

    getline(file, line, '\n');
    vector<string> rawdata = CSVlineparser(line);
    struct coviddata prevdata = dataformat(rawdata);

    while (getline(file, line, '\n')) {
        rawdata = CSVlineparser(line);
        struct coviddata newdata = dataformat(rawdata);

        if(newdata.country.name != prevdata.country.name) {
            savedata(data, prevdata);
        }

        prevdata = newdata;
    }
    cout << "done." << endl;

    file.close();

    return 0;
}

int
retrievecountry(string file_name, vector<struct coviddata> &data, string country)
{
  ifstream file;
  string line;

  file.open(file_name);

  cout << "Opening \"" << file_name << "\"" << "... ";
  if(!file.is_open()) {
    perror("file.open()");
    return ERROR;
  }
  cout << "done." << endl;

  cout << "Extracting data... ";
  getline(file, line, '\n'); /* ignore header */

  getline(file, line, '\n');
  vector<string> rawdata = CSVlineparser(line);
  struct coviddata prevdata = dataformat(rawdata);

  while (getline(file, line, '\n')) {
    rawdata = CSVlineparser(line);
    struct coviddata newdata = dataformat(rawdata);

    if((newdata.country.name == prevdata.country.name && newdata.country.name == country)
            || prevdata.country.name == country) {
      savedata(data, prevdata);
    }

    prevdata = newdata;
  }

  file.close();
  cout << "done." << endl;

  if(data.size() == 0)
      return -1;

  return 0;
}

vector<struct coviddata>
datarank(vector<struct coviddata> data, unsigned int criteria)
{
    cout << "Ranking data in accordance to criterion (" << criteria << ")... ";
    unsigned int i = 1;

    while(i < data.size()) {
        unsigned int j = i;

        switch(criteria) {
            default:
            case DEATHS:
                while(j > 0 && data[j-1].deaths.cumulativedata < data[j].deaths.cumulativedata) {
                    swap(data[j], data[j-1]);
                    j--;
                }
                i++;
                break;

          case CASES:
                while(j > 0 && data[j-1].cases.cumulativedata < data[j].cases.cumulativedata) {
                    swap(data[j], data[j-1]);
                    j--;
                }
                i++;
                break;
        }
    }
    cout << "done." << endl;

    return data;
}


int
datastore(const vector<struct coviddata> data, string dest, unsigned int format)
{
    cout << "Saving file to " << dest << "... ";
    ofstream file;

    file.open(dest, ios::trunc);
    if (!file.is_open()) {
        return ERROR;
    }

    switch(format) {
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
                    << element.cases.newdata << "," << element.cases.cumulativedata
                    << element.deaths.newdata << "," << element.deaths.cumulativedata
                    << endl;
            }
            break;
    }

    file.close();
    cout << "saved." << endl;

    return 0;
}

string ReplaceAll(string str, const string& from, const string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

int
main(void)
{
    vector<struct coviddata> data;
    vector<struct coviddata> ranked;
    char answer;
    int menu;

    cout << "covid-tool v1.0 Global COVID-19 Dashboard and Graph Generator." << endl
         << "Copyright (c) 2020 R Nicolás Savinelli <rsavinelli@est.frba.utn.edu.ar>"
         << endl << endl;

    cout << "Do you want to retrieve the latest global database? [Y/n]: ";
    cin  >> answer;
    if (answer == 'y' || answer == 'Y') {
        system(UPDATE_DATABASE);
        cout << "Database is up-to-date." << endl;
    }

    cout << endl << ":: Menu:" << endl
        << "   (" << DASHBOARD << ") Create global dashboard" << endl
        << "   (" << COUNTRYINFO << ") Retrieve country information" << endl
#if R_INSTALLED_
        << "   (" << COUNTRYGRAPH << ") Graph country information"
#endif
        << endl;
    cout << endl << "Option: ";
    cin >> menu;

    int criteria = BOTH;
    int format = NONE;

    switch(menu) {
        case DASHBOARD:
            cout << endl << ":: Dashboards criteria:" << endl
                << "   (" << CASES << ") CASES" << endl
                << "   (" << DEATHS << ") DEATHS" << endl
                << "   (" << BOTH << ") BOTH" << endl;
            cout << endl << "Criteria (default = " << BOTH << "): ";
            cin >> criteria;

            cout << endl << ":: Formatting available:" << endl
                << "   (" << NONE << ") " << CSV_HEADER << endl
                << "   (" << FILTERED << ") " << CSV_HEADER_FILTERED << endl;
            cout << endl << "Format (default = " << NONE << "): ";
            cin >> format;
            cout << endl;

            retrievecountrylist(COVID_DATA, data);
            switch(criteria) {
                default:
                case DEATHS:
                    ranked = datarank(data, DEATHS);
                    datastore(ranked, COVID_DEATHS, format);
                    if(criteria == DEATHS)
                        break;

                case CASES:
                    ranked = datarank(data, CASES);
                    datastore(ranked, COVID_CASES, format);
                    break;
            }
            break;

#if R_INSTALLED_
        case COUNTRYGRAPH:
            system(GRAPH_DASHBOARD);
            break;
#endif

        case COUNTRYINFO:
            string country = "";

            cout << endl << "From which country do you want to retrieve information?";
            cout << endl << "Answer: ";
            cin.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );
            getline(cin, country);

            if(retrievecountry(COVID_DATA, data, country) == -1) {
                cout << "Error: country not found." << endl
                     << "Warning: Country search is case sensitive." << endl;
                break;
            }

            country = ReplaceAll(country, " ", "_");

            string cmd = CREATE_DIR;
            cmd += " ";
            cmd += DASHBOARDS_PREFIX + country + "/";
            system(cmd.c_str());

            string file = "dashboards/" + country + "/" + "dashboard.csv";
            datastore(data, file, NONE);
            break;
    }

    return 0;
}
