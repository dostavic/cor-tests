#include "geo_to_mag.hpp"
#include <math.h>
#include <iostream>
#include <fstream>
#include <filesystem>

#define PI  3.14159265358979
void printGH(const unsigned int igrfLen, float *G, float *H)
{
	for(unsigned int i = 0; i < igrfLen; i++)
	{
		if(i % 7 == 0)
		{
			std::cout<<"\n";
		}
		std::cout << G[i] << " ";
	}
	std::cout<<"\n";
	
	for(unsigned int i = 0; i < igrfLen; i++)
	{
		if(i % 7 == 0)
		{
			std::cout<<"\n";
		}
		std::cout << H[i] << " ";
	}
	std::cout<<"\n";
}
//pre geomagneticke sirky vacsie ako 60 stupnov a mensie ako -60 stupnov zacinajme vypocet od 0.01 tak ako odteraz
void geoToMag(int year, int day, float geoLat, float geoLon, float *magLat, float *magLon)
{
	const static double radToDeg = 180.0 / PI;
	const static double degToRad = PI / 180.0;
	//new coordinates of 'North geomagnetic pole' from http://wdc.kugi.kyoto-u.ac.jp/poles/polesexp.html 1900-2025 5 years intervals
	const static double north[] = 
	//{78.7,78.7,78.7,78.6,78.6,78.6,78.6,78.6,78.5,78.5,78.5,78.5,78.6,78.6,78.7,78.8,78.9,79.0,79.2,79.4,79.6,79.8,80.1,80.1,80.2,80.3,80.3,80.4,80.4,80.5,80.5,80.6,80.6};
	  {78.7,78.7,78.7,78.6,78.6,78.6,78.6,78.6,78.5,78.5,78.5,78.5,78.6,78.6,78.7,78.8,78.9,79.0,79.2,79.4,79.6,79.8,80.1,80.4,80.4,80.5,80.5,80.6,80.7,80.7,80.7,80.8,80.8,80.9};
	const static double west[] = 
	//{68.8,68.7,68.7,68.6,68.4,68.3,68.3,68.4,68.5,68.5,68.8,69.2,69.5,69.9,70.2,70.5,70.8,70.9,71.1,71.4,71.6,71.8,72.2,72.3,72.4,72.5,72.5,72.6,72.7,72.8,73.0,73.1,73.2};
	  {68.8,68.7,68.7,68.6,68.4,68.3,68.3,68.4,68.5,68.5,68.8,69.2,69.5,69.9,70.2,70.5,70.8,70.9,71.1,71.4,71.6,71.8,72.2,72.6,72.6,72.6,72.7,72.7,72.7,72.7,72.7,72.7,72.6,72.6};
	if(year > 2025 || year < 1900)
	{
		*magLat = geoLat;
		*magLon = geoLon;
		std::cout << "Input year is outside of range 1900 - 2025. Using geographic coordinates as geomagnetic.\n";
		return;
	}
	int index = floor( (year - 1900) / (float)5);
	if(year > 2015)
	{
		index = 23 + year - 2015;
	}
	int nextIndex = index + 1;
	if(year == 2025)
	{
		nextIndex = index;
	}
	float percent = (year % 5 + day / 365.25)/ 5;
	float complement = 1 - percent;	
	double fi = 90 - (geoLat);
	double th = geoLon;
	double al = 90 - (north[index] * percent + north[nextIndex] * complement);
	double be = (west[index] * percent + west[nextIndex] * complement);
	fi *= degToRad;
	th *= degToRad;
	al *= degToRad;
	be *= degToRad;
	float theta = acos(cos(al)*cos(fi)+sin(al)*sin(fi)*cos(th-be));//https://pdfs.semanticscholar.org/52ba/7aff82cdbd15c6410a3f0bf8a4b3119af26e.pdf
	float phi = asin(sin(fi)*sin(th-be)/sin(theta));
	*magLat = 90 - theta * radToDeg;
	*magLon = phi * radToDeg;
}
void readGH(std::string *filePrefixH, double *GreadHigh, double *HreadHigh)
{
	std::ifstream fileH(*filePrefixH);
	std::cout << *filePrefixH <<"\n";

	// std::filesystem::path currentPath = std::filesystem::current_path();
    // std::cout << "Curent path: " << currentPath.string() << std::endl;
	
	std::string gString;
	std::string nString;
	std::string mString;
	std::string valueString;
	int gCount = 1;
	int hCount = 2;
	int oldNvalG = 1;
	int oldNvalH = 1;
	int mIndexG = 0;
	int mIndexH = 0;
	while (fileH >> gString >> nString >> mString >> valueString)
	{
		// process pair (a,b)
		char gVal = gString[0];
		int nVal = std::stoi(nString);
		int mVal = std::stoi(mString);
		double value = std::stod(valueString);
		if(gVal == 'g')
		{
			if(nVal != oldNvalG)
			{
				mIndexG = 0;
				
				while(mIndexG != mVal)
				{
					gCount++;
					mIndexG++;
				}
			}
			GreadHigh[gCount] = value;
			gCount++;
			oldNvalG = nVal;
		}
		else
		{
			if(nVal != oldNvalH)
			{
				mIndexH = 0;
				
				while(mIndexH != mVal)
				{
					hCount++;
					mIndexH++;
				}
			}
			HreadHigh[hCount] = value;
			hCount++;
			oldNvalH = nVal;
		}
	}
}
void RECALC_08(int IYEAR,int IDAY, double *CL0, double *SL0, double *CTSL, double *CTCL, double *ST0, double *STCL, double *STSL, double *CT0)
{
	int year = IYEAR, day = IDAY;
	int yearLow = year, yearHigh = year + 5 - (year % 5);
	if(year % 5 != 0 && year > 1900)
	{
		yearLow = year - (year % 5);
	}
	
	std::string filePrefixH = "./IGRF/";
	filePrefixH = filePrefixH + "igrf_" + std::to_string(yearHigh) + ".dat";
	std::string filePrefixL = "./IGRF/";
	filePrefixL = filePrefixL + "igrf_" + std::to_string(yearLow) + ".dat";
	///
	const unsigned int igrfLen = 105;
	double GreadLow[igrfLen] = {}, HreadLow[igrfLen] = {};
	double GreadHigh[igrfLen] = {}, HreadHigh[igrfLen] = {};
	for(unsigned int i = 0; i < igrfLen; i++)
	{
		GreadLow[i] = 0;
		HreadLow[i] = 0;
		GreadHigh[i] = 0;
		HreadHigh[i] = 0;
	}
	
	readGH(&filePrefixH, GreadHigh, HreadHigh);
	readGH(&filePrefixL, GreadLow, HreadLow);
	double G[igrfLen], H[igrfLen];
	double F2 = ( year + (day - 1) / 365.25 - yearLow) / 5;
	double F1 = 1 - F2;
	for (unsigned int i = 0; i < igrfLen; i++)
	{
		G[i] = GreadLow[i]*F1+GreadHigh[i]*F2;
		H[i] = HreadLow[i]*F1+HreadHigh[i]*F2;
	}
	double S = 1;
	for(int n = 2; n <= 14; n++)
	{
		int mn = n * (n - 1) / 2 + 1 - 1;
		S = S * (double) (2 * n - 3) / (double) (n - 1);
		G[mn] *= S;
		H[mn] *= S;
		double P = S;
		for(int m = 2; m <= n; m++)
		{
			int AA = 1;
			if(m == 2)
			{
				AA = 2;
			}
			P = P * sqrt(AA * (double) (n - m + 1) / (double) (n + m - 2));
			int mnn = mn + m - 1 - 1;
			G[mnn] *= P;
			H[mnn] *= P;
		}
	}
	 
	double G_10 = - G[1];
	double G_11 = G[2];
	double H_11 = H[2];
	double SQ = G_11 * G_11 + H_11 * H_11;
	double SQQ = sqrt(SQ);
	double SQR = sqrt(G_10 * G_10 + SQ);
	*CT0 = G_10 / SQR;
	*ST0 = SQQ / SQR;
	
	*CL0 = (-G_11) / SQQ;
	*SL0 = (-H_11) / SQQ;
	*STCL = (*ST0) * (*CL0);
	*STSL = (*ST0) * (*SL0);
	*CTSL = (*CT0) * (*SL0);
	*CTCL = (*CT0) * (*CL0);
}


void geoToMagCorrected(int year, int day,  float fi, float th, float r, float *thMag, float *fiMag, float *rMag)
{
	std::cout << "Start: " << "rMAg: " << *rMag << "\tthMag: " << *thMag << "\tfiMag: " << *fiMag << std::endl;
	double radToDeg = 180.0 / PI;
	double degToRad = PI / 180.0;
	fi = (90.0 - fi) * degToRad;
	th = (th) * degToRad;
	
	float XGEO = r * cos(th) * sin(fi);
	float YGEO = r * sin(th) * sin(fi);
	float ZGEO = r * cos(fi);
	
	double CL0, SL0, CTSL,CTCL, ST0, STCL, STSL, CT0;
	RECALC_08(year, day, &CL0, &SL0, &CTSL, &CTCL, &ST0, &STCL, &STSL, &CT0);
	float XMAG = XGEO * CTCL + YGEO * CTSL - ZGEO * ST0;
	float YMAG = YGEO * CL0 - XGEO * SL0;
	float ZMAG = XGEO * STCL + YGEO * STSL + ZGEO * CT0;
	
	*rMag = sqrt(XMAG * XMAG + YMAG * YMAG + ZMAG * ZMAG);
	*thMag = 90.0 - acos(ZMAG / (*rMag)) * radToDeg;
	*fiMag = atan(YMAG / XMAG) * radToDeg;
	if (XMAG>0 && YMAG<0) 
	{
		*fiMag += 360;
	}
	else if (XMAG < 0)
	{
		*fiMag += 180;
	}

	std::cout << "rMAg: " << *rMag << "\tthMag: " << *thMag << "\tfiMag: " << *fiMag << std::endl;
}
