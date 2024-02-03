
//cppcheck --enable=all infilGenerator.cpp
//g++ -std=c++11 infilGenerator.cpp -o infilGenerator -lpthread -O2 -Wall -Werror
//./infilGenerator caspoloha.dat infil T05 5

#include <iostream>
#include <cstdio>
#include <string> 
#include <fstream>
#include <thread>
#include <chrono>
#include "infilGenerator.hpp"
#include "geo_to_mag.hpp"
#include "OutfilData.hpp"

/*
#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>
TEST_CASE( "Hour diff is computed", "[hour difference]" ) {
	Timestamp first(1994,364,0);
	Timestamp last(1996,0,0);
	REQUIRE( first.calculateHoursToEndOfYear() == 24 );
	REQUIRE( first.calculateHourDiff(&last) == 8760 + 24 );
	REQUIRE( first.calculateHourDiff(&first) == 0 );
	REQUIRE( last.calculateHourDiff(&first) == 8760 + 24 );
	Timestamp first2(1995, 1, 0);
	Timestamp last2(1995, 2, 12);
	REQUIRE( first2.calculateHourDiff(&last2) == 12 + 24 );
	REQUIRE( last2.calculateHourDiff(&first2) == 12 + 24 );
}
TEST_CASE( "Date to hours to date", "[date conversions]" ) {
	Timestamp first(2,364,22);
	Timestamp last(first.hoursFromZero + first.hourOfYear);
	REQUIRE( first.rok == last.rok);
	REQUIRE( first.doy == last.doy);
	REQUIRE( first.hod == last.hod);
	REQUIRE( first.den == last.den);
	REQUIRE( first.mesiac == last.mesiac);
	REQUIRE( first.hoursFromZero == last.hoursFromZero);
	REQUIRE( first.hourOfYear == last.hourOfYear);
}
*/

#ifndef CATCH_CONFIG_MAIN
#define Pi 3.14159265358979
// ./infilGenerator ./caspoloha.dat ./Infils/ *trajectory*
// ./InfilGenerator ./mag.dat0 ./Infils/ mag
int main(int argc, char** argv)
{
	float lat[16];
	fillArrays(lat);
	int omniError, parmodError, index;
	std::unique_ptr<OutfilData> outfilData;
	Arguments arguments;
	arguments.parseArguments(argc, argv);
	if(arguments.infilKind == InfilKind::NORMAL)
	{
		outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
	} 
	else if(arguments.infilKind == InfilKind::TRAJECTORY)
	{
		
		outfilData = std::unique_ptr<OutfilData>(new TrajectoryOutfil());
	}
	else if(arguments.infilKind == InfilKind::MAG_FIELD)
	{
		
		outfilData = std::unique_ptr<OutfilData>(new MagFieldOutfil());
	}
	outfilData->readInput(&(arguments.inputFile));
	parmodError = 0;
	omniError = 0;
	if(arguments.infilKind != InfilKind::MAG_FIELD)
	{
		TrajectoryOutfil *castData = dynamic_cast<TrajectoryOutfil*>(outfilData.get());
		if(castData->version == Version::T96 || castData->version == Version::T96_LCR)// || castData->version == Version::H)//todo naozaj historickej verzii treba parmod?
		{
			readParmod(&(castData->date), &(castData->magData), &parmodError);
		}
		else if(castData->version == Version::T05 || castData->version == Version::T05_LCR)
		{
			std::thread rPara(readParmod, &(castData->date), &(castData->magData), &parmodError);
			readOMNI(&(castData->date), &(castData->tIndices), &omniError);
			rPara.join();
		}
	}
	else
	{
		MagFieldOutfil *castData = dynamic_cast<MagFieldOutfil*>(outfilData.get());
		//std::cout << "Number of hours: " << castData->numberOfHours << "\n";
		//T96_MAG  T05_MAG
		if(castData->version == IGRF)
		{
			
		}
		else if(castData->version == T96_MAG)//if version is t96 mag, we only need parmod
		{
			readParmodVector(castData, &parmodError);
		}
		else//do everything otherwise (T05 and everything else if anything else exists)
		{
			std::thread rPara(readParmodVector, castData, &parmodError);
			readOMNIVector(castData, &omniError);
			rPara.join();
		}
	}
	int errorCode = parmodError | omniError;
	//std::cout << errorCode << " "  << parmodError<< " "  << omniError << "\n";
	index = 1;
	if(arguments.infilKind == InfilKind::TRAJECTORY)
	{
		outfilData->writeData(&(arguments.filenamePrefix), 0);//when only one dir it has index 0
	}
	else if(arguments.infilKind == InfilKind::MAG_FIELD)
	{
		MagFieldOutfil *outfil = dynamic_cast<MagFieldOutfil *>(outfilData.get());
		//exit(-1);
		for(unsigned int i = 0; i < outfil->numberOfHours; i++)
		{
			outfil->writeData(&(arguments.filenamePrefix), i);
		}
		return errorCode;
	}
	else if(outfilData->numberOfDirections == 1 && outfilData->generateInfils)
	{
		outfilData->writeData(&(arguments.filenamePrefix), 0);//when only one dir it has index 0
	}
	else if(outfilData->generateInfils)
	{
		for (int ii=0;ii<16;ii++)
		{
			float lat1 = lat[ii] * (Pi/180);
			for(int jj=0;jj<36;jj++)
			{
				float longitude = ((jj)*10) * (Pi/180);
				NormalOutfil *outfil = dynamic_cast<NormalOutfil *>(outfilData.get());

				std::cout << "lat1: " << lat1 << std::endl;

				getLocalRotations(longitude, lat1, outfil->geoLoc.geolat, outfil->geoLoc.geolong, &(outfil->localLoc.latloc), &(outfil->localLoc.longloc));

				std::cout << &(outfil->localLoc.latloc) << " " << &(outfil->localLoc.longloc) << std::endl;

				outfil->writeData(&(arguments.filenamePrefix), index);
				//std::cout<<index<<" "<<outfilData.numberOfDirections <<"\n";
				if(index == outfil->numberOfDirections - 1)
				{
					//when multiple dirs, they start from one, after every one is calculated, make one with index 0 it will be vertical
					outfil->localLoc.latloc = outfil->geoLoc.geolat;
					outfil->localLoc.longloc = outfil->geoLoc.geolong;
					if(outfil->version != Version::H && outfil->version != Version::CALS10k_2)
					{
						optimizeRigidity(&(outfil->geoLoc), &(outfil->rigidityData), outfil->magData.dst);
					}
					outfil->writeData(&(arguments.filenamePrefix), 0);
					return errorCode;
				}
				index++;
			}
		}
	}
	return errorCode;
}
#endif