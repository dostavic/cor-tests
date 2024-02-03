#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

const double z = 1033;
const double logZ = log(z);
const double T0 = 0.938; //{protonova pokojova energia v GeV}
const double T0pow2 = T0*T0;
 
/**
 * @brief Reads data from line "_filename _year._percent ___" and stores _filename value filename,  _year value in year and _percent value in percent.
 * @param line Pointer to string holding line data.
 * @param filename Name of file with this line.
 * @param year Year for this line.
 * @param percent Part of year in percent for this file.
 */
void parseDataFromLine(std::string *line, std::string *filename, unsigned int *year, unsigned int *percent);
/**
 * @brief Fills given arrays with specific values.
 * @param binE Pointer to vector to fill.
 * @param binB Pointer to array to fill.
 * @param binw Pointer to array to fill.
 * @param binI Pointer to vector to fill.
 * @param lat Pointer to array of latitudes to fill.
 */
void fillArrays(std::vector<double> *binE, double * binB, double * binw, std::vector<double> * binI, double * lat, double yield[][4]);

#endif