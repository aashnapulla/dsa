#include "digipin.h"
// Implement your code here

using namespace std;

// SOME HELPER FUNCTIONS DECLATIONS, WHICH MAY HELP YOU IMPLEMENT THE TASK

// Digipin symbols grid
array<array<char, 4>, 4> GRID = {{{'F', 'C', '9', '8'},
                                  {'J', '3', '2', '7'},
                                  {'K', '4', '5', '6'},
                                  {'L', 'M', 'P', 'T'}}};

// function to get the grid index corresponding to a Digipin symbols
pair<int, int> symbolToRC(char s)
{
    for (int r = 0; r < 4; ++r)
        for (int c = 0; c < 4; ++c)
            if (GRID[r][c] == s)
                return {r, c};
    return {0, 0};
}

void applyGridlineRules(double &lat, double &lon,
                        double latMin, double latMax,
                        double lonMin, double lonMax)
{
    // To handle coordinates coinciding with DIGIPIN Grid Lines
    // shift by 1e-12 in the correct direction according to the specification;

}

// TASK IS TO IMPLEMENT THE FOLLOWING TWO FUNCTIONS

string Digipin::encode(double lat, double lon)
{
    // Implement to get Digipin from latitude and longitude values
    double lamin = LAT_MIN;
    double lamax = LAT_MAX;
    double lonmin = LON_MIN;
    double lonmax = LON_MAX;
    int r =0;
    int c=0;
    string code;

    for (int j=0; j<10; j++){
        double range = (lonmax- lonmin)/4;
        
        for (int i=0; i<4; i++){
            if (lon < (lonmin + (i+1)*range)){
                c = i;
                break;
            }
        }
        for (int i=0; i<4; i++){
            if (lat > (lamax - (i+1)*range)){
                r = i;
                break;
            }
        }
        if (lat == lamax){
            r=0;
        }
        if (lat == lamin){
            r = 3;
        }
        if (lon == lonmin){
            c=0;
        }
        if (lon == lonmax){
            c = 3;
        }

        code+= GRID[r][c];

        lamax = lamax- range*(r);
        lonmin = lonmin + range*(c);
        lamin = lamax - range;
        lonmax = lonmin + range;

    }

  return code;
}

pair<double, double> Digipin::decode(string &code)
{

    // Implement to get the center of the bounding box
  double latCenter = 0;
  double lonCenter = 0;
  double lamin = LAT_MIN;
  double lamax = LAT_MAX;
  double lonmin = LON_MIN;
  double lonmax = LON_MAX;
  
  if (code.length()!=10){
    return {-1,-1};
  }
  for (char c:code){
    double range = (lonmax- lonmin)/4;
    pair<int, int> i = symbolToRC(c);
    lamax = lamax- range*(i.first);
    lonmin = lonmin + range*(i.second);
    lamin = lamax - range;
    lonmax = lonmin + range;
  }

  latCenter = (lamin + lamax)/2;
  lonCenter = (lonmin + lonmax)/2;

  return {latCenter, lonCenter}; // Return center of the cell
}
