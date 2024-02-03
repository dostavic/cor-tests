#include <iostream>
#include <math.h>

#include "OutfilData.hpp"
#include "infilGenerator.hpp"
#include "geo_to_mag.hpp"

void OutfilData::readSecondLine(char *buffer, std::string *inputFile, FILE *gg)
{
	int genInfils = 1;
	int state = 0;
	int inVersion = 0;
	float rigidityStep = 0.01;
	if(fgets(buffer,bufferSize,gg) == nullptr)
	{
		std::cout<<"Error reading "<<inputFile->c_str()<<" exiting\n";
		exit(-1);
	}
	if(sscanf(buffer,"%d %d %d %d %f %d", &genInfils, &state, &inVersion, &numberOfDirections, &(rigidityStep), &optimalizationLevel) != 6)
	{
		printf("Missing generate infils, state, version, rigidity step or number of directions in second line of %s!\n",inputFile->c_str());
		fclose(gg);
		exit(-1);
	}
	setRigidityStep(rigidityStep);
	inputState = state;
	version = (Version) inVersion;
	//std::cout << "!!! Version: "<<inVersion<<" !!!\n";
	generateInfils = genInfils;
	// std::cout << "CHECK SECOND!" << std::endl;
}
void OutfilData::setRigidityStep(float rigidityStep)
{
}
void TrajectoryOutfil::setRigidityStep(float rigidityStep) 
{
	this->rigidityData.rigidityStep = rigidityStep;
}
void TrajectoryOutfil::writeData(std::string *filenamePrefix, int index)
{
	std::string s3 = *filenamePrefix;
	s3 += '_';
	s3.append(std::to_string(index));
	FILE *bb = fopen(s3.c_str(), "w");
	if(bb!=NULL)
	{
		fprintf(bb,"%8.4f  -1.  %8.4f\n",rigidityData.rigstart,rigidityData.rigend);//0.01,200
		fprintf(bb,"%6.2f  %8.2f  %8.2f\n",geoLoc.radius,geoLoc.geolat,geoLoc.geolong);
		fprintf(bb,"         %8.2f  %8.2f\n",localLoc.latloc,localLoc.longloc);
		fprintf(bb," %4d%3d%3d%4d%3d 00 00\n",date.getYear(),date.getMonth(),date.getDay(),date.getDoy(),date.getHour());
		fprintf(bb,"   100   1   1%7.2f\n",rigidityData.rigidityStep);
		if(version != Version::IGRF)
		{
			if(version != Version::H && version != Version::CALS10k_2)
			{
				fprintf(bb,"%5d%7.2f%7.2f%7.2f\n",magData.dst,magData.pdyn,magData.byimf,magData.bzimf);
			}
			if(version == Version::T05 || version == Version::T05_LCR)
			{
				fprintf(bb,"%7.2f%7.2f%7.2f%7.2f%7.2f%7.2f\n",tIndices.W1,tIndices.W2,tIndices.W3,tIndices.W4,tIndices.W5,tIndices.W6);
			}
		}
		fprintf(bb,"-1.00\n");
		fclose(bb);
	}
}
void TrajectoryOutfil::readInputImpl(char *buffer,FILE *gg,std::string *inputFile)
{
	float rigidity;
	if(fgets(buffer,bufferSize,gg) == nullptr)
	{
		std::cout<<"Error reading "<<inputFile<<" exiting\n";
		exit(-1);
	}
	unsigned int year;
	unsigned short doy, hour;
	if(sscanf(buffer,"%d %hu %hu %f %f %f %f %f %f\n",&year,&doy,&hour,&geoLoc.geolat,&geoLoc.geolong,&geoLoc.radius,
	&localLoc.latloc, &localLoc.longloc, &rigidity)!=9)
	{
		printf("Wrong format of %s, for trajectory calculation\n",inputFile->c_str());
		fclose(gg);
		exit(-1);
	}
	date.fromYDH(year, doy, hour);
	readSecondLine(buffer, inputFile, gg);
	rigidityData.rigstart = rigidity;
	rigidityData.rigend = rigidity;
}
void NormalOutfil::readInputImpl(char *buffer,FILE *gg,std::string *inputFile)
{
	if(fgets(buffer,bufferSize,gg) == nullptr)
	{
		std::cout<<"Error reading "<<inputFile<<" exiting\n";
		exit(-1);
	}
	unsigned int year;
	unsigned short doy, hour;
	if(sscanf(buffer,"%d %hu %hu %f %f %f",&year,&doy,&hour,&geoLoc.geolat,&geoLoc.geolong,&geoLoc.radius)!=6)
	{
		printf("Wrong format of %s, for normal calculation\n",inputFile->c_str());
		fclose(gg);
		exit(-1);
	}
	date.fromYDH(year, doy, hour);
	readSecondLine(buffer, inputFile, gg);
	localLoc.latloc = geoLoc.geolat;
	localLoc.longloc = geoLoc.geolong;
	rigidityData.rigstart = 0.01;
	rigidityData.rigend = 100;
	if(numberOfDirections == 1 && (version != Version::H && version != Version::CALS10k_2))
	{
		optimizeRigidity(&(geoLoc), &(rigidityData), magData.dst);
	}
	else if(version != Version::H && version != Version::CALS10k_2)
	{
		float geomag_latitude = 0;
		float geomag_longitude = 0;
		float geoAltitude = 6371.185 * geoLoc.radius;
		float geomag_altitude = 0;
		std::cout << "geo_latitude: "<< (geoLoc.geolat) << " geo_longitude: " << (geoLoc.geolong) << "\n";
		geoToMagCorrected(date.getYear(), date.getDoy(), geoLoc.geolat, geoLoc.geolong, geoAltitude, &geomag_latitude, &geomag_longitude, &geomag_altitude);
		if(geomag_longitude > 180)
		{
			geomag_longitude -=360;
		}
		std::cout<<"geomag_latitude: "<<geomag_latitude<<" geomag_longitude: "<<geomag_longitude<<" geomag_altitude: "<<geomag_altitude<<"\n";
		if(optimalizationLevel == OptimizationLevel::O_LEVEL_1)
		{
			if(geomag_latitude<60 && geomag_latitude>-60)
			{
				setRigidityStart(geomag_latitude, geomag_longitude);
			}
		}
		else if(optimalizationLevel == OptimizationLevel::O_LEVEL_2)
		{
			if(geomag_latitude<60 && geomag_latitude>-60)
			{
				setRigidityStart2(geomag_latitude, geomag_longitude);
			}
		}
		else if(optimalizationLevel == OptimizationLevel::O_LEVEL_3)
		{
			if(geomag_latitude<60 && geomag_latitude>-60)
			{
				setRigidityStart2(geomag_latitude, geomag_longitude);
			}
		}
		rigidityData.rigstart = ((int)floor(rigidityData.rigstart * 100)) / (float)100;
		std::cout<<"rigstart: "<<rigidityData.rigstart<<"\n";
	}
}
void OutfilData::readInput(std::string *inputFile)
{
	FILE *gg = fopen(inputFile->c_str(), "r");
	if(gg!=NULL)
	{
		char buffer[bufferSize];
		readInputImpl(buffer,gg,inputFile);
		fclose(gg);
	}
	else
	{
		printf("Error opening file %s, terminating\n",inputFile->c_str());
		exit(4);
	}
}

void MagFieldOutfil::readInputImpl(char *buffer, FILE *gg, std::string *inputFile)
{
	std::cout << "Check: " << std::endl;
	if(fgets(buffer,bufferSize,gg) == nullptr)
	{
		std::cout<<"Error reading "<<inputFile<<" exiting\n";
		exit(-1);
	}
	char inputDateStart[50], inputTimeStart[50],inputDateEnd[50], inputTimeEnd[50];
	if(sscanf(buffer,"%s %s %s %s %d %f %f %f %f %f %f %f\n",inputDateStart,inputTimeStart,inputDateEnd,inputTimeEnd,&intervalDur,
	&geoLoc.geolong,&geoLoc.geolat, &localLoc.longloc, &localLoc.latloc, &geoLoc.radius, &latitudeStep, &longitudeStep)!=12)
	{
		printf("Wrong format of %s, for geomagnetic field calculation\n",inputFile->c_str());
		fclose(gg);
		exit(-1);
	}
	
	date = Timestamp(std::string(inputDateStart) + " " + std::string(inputTimeStart));
	endDate = Timestamp(std::string(inputDateEnd)+ " " + std::string(inputTimeEnd));
	intervalDur = intervalDur == 0 ? 1 : intervalDur;
	numberOfHours = round(date.calculateHourDiff(&endDate) / intervalDur) + 1;
	//numberOfHours = numberOfHours == 0 ? 1 : numberOfHours;
	
	date.print();
	

	endDate.print();
	magData.reserve(numberOfHours);
	tIndices.reserve(numberOfHours);
	for(unsigned int i = 0; i < numberOfHours; i++)
	{
		magData.emplace_back();
		tIndices.emplace_back();
	}

	readSecondLine(buffer, inputFile, gg);
}
void MagFieldOutfil::writeData(std::string *filenamePrefix, int index)
{
	std::string s3 = *filenamePrefix;
	s3 += '_';
	s3.append(std::to_string(index));
	FILE *bb = fopen(s3.c_str(), "w");
	if(bb!=NULL)
	{
		fprintf(bb,"%6.2f  %8.2f  %8.2f\n", geoLoc.radius, geoLoc.geolat, geoLoc.geolong);
		fprintf(bb,"%8.2f  %8.2f  %8.2f  %8.2f \n", latitudeStep, longitudeStep, localLoc.latloc, localLoc.longloc);
		fprintf(bb," %4d%3d%3d%4d%3d 00 00\n", date.getYear(), date.getMonth(), date.getDay(), date.getDoy(), date.getHour());
		fprintf(bb,"%5d%7.2f%7.2f%7.2f\n", magData[index].dst, magData[index].pdyn, magData[index].byimf, magData[index].bzimf);
		if(version == Version::T05_MAG)
		{
			fprintf(bb,"%7.2f%7.2f%7.2f%7.2f%7.2f%7.2f\n", tIndices[index].W1, tIndices[index].W2, tIndices[index].W3, tIndices[index].W4, tIndices[index].W5, tIndices[index].W6);
		}
		fprintf(bb,"-1.00\n");
		fclose(bb);
	}
	date.addHours(intervalDur);
}
void NormalOutfil::setRigidityStart(float geomag_latitude, float geomag_longitude)
{
	float g2 = geomag_latitude * geomag_latitude;
	float g3 = g2 * geomag_latitude;
	float g4 = g3 * geomag_latitude;
	rigidityData.rigstart = 0.8 * ( 7.87294 - (0.01169*geomag_latitude) - (0.0034*g2) + (2.46528E-6*g3) + (4.06013E-7*g4) );
}
void NormalOutfil::setRigidityStart2(float geomag_latitude, float geomag_longitude)
{
	unsigned int sp = 7;
	// todo nacitavanie cez subor ked sa budem velmi nudit
	double rd[sp][sp] =
	{
		{ 8.00048, 0.0319041, -0.00384024, -2.37672e-05, 8.14932e-07, 4.02665e-09, -8.25768e-11 },
		{ -0.0234847, 0.00138020, 5.93152e-05, -8.15613e-07, -3.53251e-08, 1.23705e-10, 5.84289e-12 },
		{ 0.000283218, 1.84477e-05, -5.47243e-07, -1.20369e-08, 3.01153e-10, 2.00359e-12, -4.79948e-14 },
		{ 2.49792e-06, -7.87612e-08, -6.87237e-09, 2.80982e-11, 4.14785e-12, -2.12780e-15, -6.84510e-16 },
		{ -9.67720e-09, -1.74323e-09, 2.39109e-11, 1.21017e-12, -1.51892e-14, -2.07666e-16, 2.57530e-18 },
		{ -6.34175e-11, 6.01657e-13, 1.78682e-13, 4.47183e-16, -1.08510e-16, -1.61469e-19, 1.79092e-20 },
		{ 1.97459e-13, 3.59245e-14, -4.93049e-16, -2.63905e-17, 3.08951e-19, 4.66524e-21, -5.17728e-23 },
	};
	rigidityData.rigstart = 0;
	for(unsigned int i = 0; i < sp; i++)
	{
		for(unsigned int j = 0; j < sp; j++)
		{
			rigidityData.rigstart += rd[i][j] * pow(geomag_latitude, j) * pow(geomag_longitude, i);
		}
	}
	rigidityData.rigstart *= 0.7;
}