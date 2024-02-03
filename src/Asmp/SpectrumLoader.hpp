#ifndef SPECTRUMLOADER_HPP
#define SPECTRUMLOADER_HPP

#include <string>

#include "structs.hpp"
#include "utilities.hpp"

/**
 * @struct SpectrumLoader
 * @author Daniel
 * @date 12/02/19
 * @file amsP.hpp
 * @brief Struct that holds filenames of best and second best datafiles and distance from best data to second best in interval 0 - 1.
 */
struct SpectrumLoader
{
	std::string bestFn; /**< Best data. */
	std::string secondBestFn; /**< Second best data. */
	float multiplier; /**< Point of inrepolation between best and second best data, interval 0 - 1. */
	StaticData *sd;
	std::string exception_message_;
	/**
	 * @brief Initializes all fields base on input values.
	 * @param sd Pointer to static data.
	 */
	SpectrumLoader(StaticData *sd);
	void print()
	{
		std::cout << bestFn << " " << secondBestFn << " " << multiplier << "\n";
	}
	/**
	 * @brief Reads input data from file and initializes arrays pointed to with read values.
	 * @param binE Output parameter. Pointer to energy array.
	 * @param binI Output parameter. Pointer to intensity array.
	 */
	void loadSpectrum(std::vector<double> *binE, std::vector<double> *binI);
	std::string get_exception_message();
private:
	/**
	 * @brief Searches for best fit of input date in catalogue based on main file data, fills filenameMultiplier with filenames and interpolation line.
	 */
	void getInputFileName();
};

struct InputPhysicalData {
	double rigStepOrig;
	float variableBinWidth;
	bool usingAMS;
	std::vector<double> binI;
	std::vector<double> binE;
	double binB[32];
	double binw[31];
	double lat[16];
	static const int yieldSizeX = 4;
	static const int yieldSizeY = 4;
	double yield[yieldSizeX][yieldSizeY];
	SpectrumLoader sLoader;
	StaticData *sd;
	InputPhysicalData(StaticData *sd) : rigStepOrig(sd->yearDoy.rigidityStep), variableBinWidth(sd->variableBinWidth), usingAMS(sd->postProcessingInput == "null"), sLoader(sd), sd(sd)
	{
		fillArrays(&binE, binB, binw, &binI, lat, yield);
		try
		{
			if(!usingAMS)
			{
				sLoader.loadSpectrum(&binE, &binI);
			}
		}
		catch (std::exception &e)
		{
			usingAMS = true;
			std::cout<<e.what()<<"\n";
		}
	}
};

#endif // SPECTRUMLOADER_HPP
