#include "SpectrumLoader.hpp"

SpectrumLoader::SpectrumLoader(StaticData *sd) : bestFn(""), secondBestFn(""), multiplier(0.f), sd(sd)
{
}

void SpectrumLoader::loadSpectrum(std::vector<double> *binE, std::vector<double> *binI)
{
	getInputFileName();
	const float energyDivider = sd->energyDivider;
	const float intensityDivider = sd->intensityDivider;
	//std::cout << energyDivider << " aaa " << intensityDivider << "\n";
	std::ifstream best(bestFn);
	float _energy, _intensity;
	binE->clear();
	binI->clear();
	std::string line;
	// int check = 0;
	while ( std::getline(best, line)) // load best fil spectrum
	{
		std::stringstream stream;
		stream << line;
		stream >> _energy >> _intensity;
		// if(check == 0)
			// std::cout << "_Energy: " << _energy << "\n_Intensity: " << _intensity << "\n";
		binE->emplace_back((_energy) / energyDivider);
		binI->emplace_back((_intensity) / intensityDivider);
		// check++;
	}
	if(multiplier != 0) // interpolate only if second best exists and isn't best fit
	{
		std::ifstream secondBest(secondBestFn);
		int idx = 0;
		const float complement = 1 - multiplier;
		while (std::getline(secondBest, line))
		{
			std::stringstream stream;
			stream << line;
			stream >> _energy >> _intensity;
			// lineary interpolate with values from second best
			binE->at(idx) = complement * binE->at(idx) + multiplier * ((_energy) / energyDivider);
			binI->at(idx) = complement * binI->at(idx) + multiplier * ((_intensity) / intensityDivider);
			idx++;
		}
	}
	else
	{
		std::cout << "Second best spectrum doesn't exist, using values from best fit.\n";
	}
}

void SpectrumLoader::getInputFileName()
{
	InputOutfilData *yearDoy = &(sd->yearDoy);
	std::string pathToData((sd->postProcessingInput) + (sd->mainFile));
	std::ifstream infile(pathToData);
	std::string line;
	bool yearExists = false, getNextLine = false;
	float simulationPercent = (float)yearDoy->doy / ((float)yearDoy->daysInYear / 100);
	float smallestDiff = 100;
	std::string bestFilename;
	std::string previous;
	std::stringstream previousLine;
	std::stringstream nextLine;
	unsigned int bestPercent = 0;
	unsigned int firstYear = 0;
	unsigned int lastYear = 0;
	if(sd->dateRange)
	{
		while (std::getline(infile, line))
		{
			std::string filename;
			unsigned int year, percent;
			parseDataFromLine(&line, &filename, &year, &percent);
			if(firstYear == 0)
			{
				lastYear = year;
			}
			firstYear = year;
			if(getNextLine)
			{
				nextLine.str(std::string());
				nextLine << line;
				getNextLine = false;
			}
			if(year == yearDoy->year)
			{
				yearExists = true;
				float diff = abs(float(percent - simulationPercent));
				if(diff < smallestDiff)
				{
					smallestDiff = diff;
					bestFilename = filename;
					bestPercent = percent;
					getNextLine = true;
					previousLine.str(std::string());
					previousLine << previous;
				}
			}
			previous = line;
		}
		if(!yearExists)
		{
			throw std::runtime_error("Spectrum with specified year (" + std::to_string(lastYear) + ") doesn't exist, using default AMS spectrum");
		}
	}
	else
	{
		while (std::getline(infile, line))
		{
			unsigned int year, percent;
			parseDataFromLine(&line, &bestFilename, &year, &percent);
		}
	}
	std::cout << "Best filename: " << bestFilename << " smallest diff: " << smallestDiff << "\n";
	std::string interpolateBest;
	float multiplier_ = 0;
	std::string lineToParse = ( (bestPercent < simulationPercent) ? previousLine.str() : nextLine.str() );
	std::cout << "Lines: " << previousLine.str() << " " <<nextLine.str()  << "\n";
	std::cout << "LineToParse: " << lineToParse << "\n";
	if(lineToParse.length() > 0)
	{
		unsigned int year, percent;
		parseDataFromLine(&lineToParse, &interpolateBest, &year, &percent);
		if(firstYear <= year && year <= lastYear)
		{
			float lineLenght;
			//helmod spektra su vacsie hodnoty ako AMS a nove - netreba delit 1000
			lineLenght = year == yearDoy->year ? (abs((float)bestPercent - percent)) : (100 - percent + bestPercent);

			std::cout << "bestPercent: " << bestPercent << "Percent: " << percent << "\n";
			std::cout << "MINUS (bestPercent - percent): " << bestPercent - percent << "\n";
			std::cout << "Float: " << float(bestPercent - percent) << "\n";

			std::cout << "lineLenght:: " << abs((float)bestPercent - percent) << "\n";
			// std::cout << "LineLenght: " << lineLenght;
			// std::cout << "Year == " << year << "yearDoy == " << yearDoy->year << "Best: " << bestPercent;
			multiplier_ = abs(float(simulationPercent - bestPercent)) / (lineLenght );
		}
	}
	bestFn = (sd->postProcessingInput) + bestFilename + ".dat";
	secondBestFn = (sd->postProcessingInput) + interpolateBest + ".dat";
	multiplier = multiplier_;
	std::cout << "Best: " << bestFn << " second best: " << secondBestFn << " mult: " << multiplier << "\n";
}

std::string SpectrumLoader::get_exception_message() { return exception_message_; }