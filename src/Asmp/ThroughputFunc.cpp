#include "ThroughputFunc.hpp"
#include <fstream>
#include <iostream>
#include <math.h>

ThroughputFunc::ThroughputFunc(const fPrecision binWidth, const unsigned int numberOfDirections, const fPrecision rigidityStep, const unsigned int maxRigidity)
: binWidth(binWidth), maxRigidity(maxRigidity), rigidityStep(rigidityStep)
{
	this->numberOfDirections = numberOfDirections == 366 ? numberOfDirections + 1 : numberOfDirections;
	deltaPerRigidity = rigidityStep/binWidth;
	numberOfBins = round(maxRigidity/binWidth);
	for(unsigned int i = 0; i < this->numberOfDirections; i++)
	{
		throughputArray.emplace_back(new unsigned int[numberOfBins]);
		for(unsigned int j = 0; j < numberOfBins; j++)
		{
			throughputArray[i][j] = 0;
		}
	}
	maxUnit = binWidth/rigidityStep;
	multiplier = std::round(1.0 / (fPrecision)rigidityStep);//(1.0 / (fPrecision)rigidityStep);
	maxRigMulti = maxRigidity * multiplier;
	binWidthMulti = binWidth * multiplier;
	minRig = 0;
}

void ThroughputFunc::placeRigidity(const unsigned int i, fPrecision rig)
{
	unsigned int rigidity = round( rig * (fPrecision)multiplier);
	if(rigidity <= maxRigMulti)
	{
		unsigned int j = round( (rigidity - minRig) / (fPrecision)binWidthMulti );
		if(j < numberOfBins)
		{
			throughputArray[i][j] += 1;
		}
	}
}
void ThroughputFunc::fillZerothThroughput()
{
	unsigned int *arrayAddress = throughputArray.at(0).get();
	int maxUnits = 0;
	int startU = 0;
	for(unsigned int j = 0; j < numberOfBins; j++)
	{
		if(arrayAddress[j] == maxUnit)
		{
			if(startU == 0)
			{
				startU = j;
			}
			maxUnits++;
		}
		else if(numberOfDirections > 1 && rigidityStep >= 0.1)
		{
			if(maxUnits < 7)
			{
				startU = 0;
			}
		}
	}
	for(unsigned int j = startU; j < numberOfBins; j++)
	{
		arrayAddress[j] = maxUnit;
	}
}
void ThroughputFunc::getBorderIndices(unsigned int *startIndex, unsigned int *endIndex, fPrecision *arrayAddress)
{
	for(unsigned int j = 0; j < numberOfBins; j++)
	{
		if(arrayAddress[j] > 0 && *startIndex == 0)
		{
			*startIndex = j == 0 ? 0 : j - 1;
		}
		float val = arrayAddress[numberOfBins - j - 1];
		if(((int)(val*1000000)) < 999999 && *endIndex==0)
		{
			*endIndex = numberOfBins - j;
		}
	}
}
void ThroughputFunc::writeThroughputFunc(std::string *outThroughput)
{
	std::ofstream myfile;
	fillZerothThroughput();
	std::unique_ptr<fPrecision[]> sumArray = std::unique_ptr<fPrecision[]>(new fPrecision[numberOfBins]);
	for(unsigned int j = 0; j < numberOfBins; j++)
	{
		sumArray[j] = 0;
	}
	for(unsigned int i = 0; i < throughputArray.size(); i++)
	{
		unsigned int *arrayAddress = throughputArray.at(i).get();
		for(unsigned int j = 0; j < numberOfBins; j++)
		{
			sumArray[j] += arrayAddress[j];
		}
	}
	fPrecision divider = numberOfDirections / deltaPerRigidity;
	for(unsigned int j = 0; j < numberOfBins; j++)
	{
		sumArray[j] /= divider;
	}
	myfile.open(*outThroughput);
	
	unsigned int startIndex = 0;
	unsigned int endIndex = 0;
	fPrecision *arrayAddress = sumArray.get();
	getBorderIndices(&startIndex, &endIndex, arrayAddress);
	myfile << startIndex << " " << endIndex << " " << binWidth << " " << maxRigidity << "\n";
	for(unsigned int j = 0; j < numberOfBins; j++)
	{
		myfile << arrayAddress[j] << " ";
	}
	myfile << "\n";
	if(throughputArray.size() > 1)
	{
		std::unique_ptr<fPrecision[]> zerothArray = std::unique_ptr<fPrecision[]>(new fPrecision[numberOfBins]);
		for(unsigned int i = 0; i < numberOfBins; i++)
		{
			zerothArray[i] = throughputArray.at(0)[i] * deltaPerRigidity;
		}
		startIndex = 0;
		endIndex = 0;
		arrayAddress = zerothArray.get();
		getBorderIndices(&startIndex, &endIndex, arrayAddress);
		myfile << startIndex << " " << endIndex << " " << binWidth << " " << maxRigidity << "\n";
		for(unsigned int j = 0; j < numberOfBins; j++)
		{
			myfile << arrayAddress[j] << " ";
		}
	}
	myfile << "\n";
	myfile.close();
}
ThroughputFunc::~ThroughputFunc()
{
}

