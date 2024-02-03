#ifndef GEOTOMAG_HPP
#define GEOTOMAG_HPP
#include <string>
/**
 * @brief reads IGRF G and H data.
 * @param filePrefixH Pointer to string with path to file.
 * @param GreadHigh Pointer to output array with G.
 * @param HreadHigh Pointer to output array with H.
 */
void readGH(std::string *filePrefixH, double *GreadHigh, double *HreadHigh);
/**
 * @brief Computes constants based on IGRF data and date.
 * @param IYEAR Input year.
 * @param IDAY Input day.
 * @param CL0 Output conastant.
 * @param SL0 Output conastant.
 * @param CTSL Output conastant.
 * @param CTCL Output conastant.
 * @param ST0 Output conastant.
 * @param STCL Output conastant.
 * @param STSL Output conastant.
 * @param CT0 Output conastant.
 */
void RECALC_08(int IYEAR,int IDAY, double *CL0, double *SL0, double *CTSL, double *CTCL, double *ST0, double *STCL, double *STSL, double *CT0);
/**
 * @brief Converts geographic coordinates to dipole geomagnetic coordinates using IGRF data.
 * @param year Input year.
 * @param day Input Day.
 * @param fi Geographic latitude.
 * @param th Geographic longitude.
 * @param r Geographic distance from center of Earth.
 * @param thMag Geomagnetic latitude.
 * @param fiMag Geomagnetic longitude.
 * @param rMag Geomagnetic distance from center of Earth.
 */
void geoToMagCorrected(int year, int day,  float fi, float th, float r, float *thMag, float *fiMag, float *rMag);
/**
 * @brief Converts geographic coordinates to dipole geomagnetic coordinates using transformations.
 * @param year Input year.
 * @param day Input Day.
 * @param fi Geographic latitude.
 * @param th Geographic longitude.
 * @param thMag Geomagnetic latitude.
 * @param fiMag Geomagnetic longitude.
 */
void geoToMag(int year, int day, float geoLat, float geoLon, float *magLat, float *magLon);
#endif