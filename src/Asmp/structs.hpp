#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

#include "utilities.hpp"
#include "ThroughputFunc.hpp"

const int binNum = 72;
const int yieldY = 24;

/**
 * @struct OutfilData
 * @author Daniel
 * @date 07/05/17
 * @file amsP.hpp
 * @brief Container struct holding data read from outfil.
 */
struct OutfilData
{
	double rig; /**< Rigidity value. */
	double lat_end_p; /**< Latitude of particle crossing magnetospause. */
	double lon_end_p; /**< Longitude of particle crossing magnetospause. */
	double lat_asym; /**< Latitude of asymptotic direction. */
	double lon_asym; /**< Longitude of asymptotic direction. */
	/**
	 * @brief Initializes all fields.
	 * @param r Rigidity value.
	 * @param la_e Latitude of particle crossing magnetospause.
	 * @param lo_e Longitude of particle crossing magnetospause.
	 * @param la_a Latitude of asymptotic direction.
	 * @param lo_a Longitude of asymptotic direction.
	 */
	OutfilData(double r,double la_e,double lo_e,double la_a,double lo_a) : rig(r),lat_end_p(la_e),lon_end_p(lo_e),lat_asym(la_a),lon_asym(lo_a)
	{
	}
};
/**
 * @class Band
 * @author Daniel
 * @date 10/02/18
 * @file amsP.hpp
 * @brief Container struct holding data used to draw rigidity spectra
 */
struct Band
{
	double start; /**< Start of band value. */
	double bandWidth; /**< Width of band to draw value. */
	/**
	 * @brief Constructor for field initialization.
	 * @param start Start of band value.
	 * @param bandWidth Width of band to draw value.
	 */
	Band(double start,double bandWidth) : start(start), bandWidth(bandWidth)
	{
	}
};
/**
 * @struct CoordinatesAndValues
 * @author Daniel
 * @date 07/05/17
 * @file amsP.hpp
 * @brief Container struct holding data calculated from data read from outfil.
 */
struct CoordinatesAndValues
{
	double val; /**< Value computed from rigidity. */
	int ilatend; /**< Latitude of particle crossing magnetospause rounded down to nearest integer in defined matrix. */
	int ilonend; /**< Longitude of particle crossing magnetospause rounded down to nearest integer in defined matrix. */
	int ilatasym; /**< Latitude of asymptotic direction rounded down to nearest integer in defined matrix. */
	int ilonasym; /**< Longitude of asymptotic direction rounded down to nearest integer in defined matrix. */
	/**
	 * @brief Initializes all fields.
	 * @param v Value computed from rigidity.
	 * @param lae Latitude of particle crossing magnetospause rounded down to nearest integer in defined matrix.
	 * @param loe Longitude of particle crossing magnetospause rounded down to nearest integer in defined matrix.
	 * @param laa Latitude of asymptotic direction rounded down to nearest integer in defined matrix.
	 * @param loa Longitude of asymptotic direction rounded down to nearest integer in defined matrix.
	 */
	CoordinatesAndValues(double v,int lae,int loe,int laa,int loa) : val(v),ilatend(lae),ilonend(loe),ilatasym(laa),ilonasym(loa)
	{
	}
};
/**
 * @struct InputOutfilData
 * @author Daniel
 * @date 09/02/19
 * @file amsP.hpp
 * @brief Struct that holds information about year and DOY of simulation, parsed and converted from outfil_1.
 */
struct InputOutfilData
{
	unsigned int year; /**< Year. */
	unsigned int doy; /**< Day of year. */
	unsigned int daysInYear; /**< Number of days in this year. */
	double rigidityStep; /**< Rigidity step read from outfile. */
	std::string exception_message_;
	/**
	 * @brief Initializes all fields base on input values.
	 * @param year Year of simulation.
	 * @param doy Doy of simulation.
	 * @param days Maximum number of days in year.
	 */
	InputOutfilData() : year(0), doy(0), daysInYear(365), rigidityStep(0.01)
	{
	}
	
	/**
	 * @brief Reads rigidity step and input date from first outfil
	 * @param outfil_0 Pointer to source filename string.
	 */
	void init(std::string *outfil_0)
	{
		FILE *cc = fopen(outfil_0->c_str(), "r");
		//double rigidityStep = 0.0;
		if(cc!=NULL)
		{
			int numLines = 0;
			char buffer[256];
			while(fgets(buffer, 256, cc)!=NULL )
			{// Starting rigidity :   0.0100 GV Epsilon= 0.0100
				if(numLines == 7)
				{
					std::stringstream ss(buffer);
					std::string _year, _month, _day;
					ss >> _year;
					ss >> _year;
					ss >> _month;
					ss >> _day;
					int year_ = std::stoi(_year);
					int month = std::stoi(_month);
					int day = std::stoi(_day);
					try {
						boost::gregorian::date d(year_, month, day);
						doy = d.day_of_year();
						daysInYear = (((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0)) ? 366 : 365;
					}
					catch (std::out_of_range& e) {
						exception_message_ = e.what();
						//todo mozno tu pouzit DateTime z geomag alebo InfilGenerator
						std::cout << "Bad date: " << e.what() << std::endl;
					}
					year = year_;
				}
				if(numLines == 8)
				{
					std::stringstream ss(buffer);
					char s1[32];
					for(int i = 0; i <= 6; i++)
					{
						ss >> s1;
					}
					rigidityStep = std::stod(s1);
					std::cout << "Year: " << year << " doy: " << doy << " number of days: " << daysInYear << " rigidity step: " << rigidityStep << "\n";
					return;
				}
				numLines++;
			}
			fclose(cc);
		}
		else
		{
			std::cout<<"Could not open "<< (*outfil_0) <<" exiting!\n";
			exit(0);
		}
	}

	std::string get_exception_message() { return exception_message_; }
};

struct StaticData {
	unsigned int numberOfDirections;
	std::string outfilPrefix, outputFolder, cutOffRigPrefix, intensityYieldPrefix, map, integr2sum, spectraBands, outfil_0, postProcessingInput, mainFile;
	std::string throughputPath, rigEnergyFile;
	float variableBinWidth;
	float energyDivider, intensityDivider;
	bool dateRange;
	InputOutfilData yearDoy;
	StaticData(int argc, char** argv) 
	{
		if(argc==4)
		{
			outputFolder = argv[1];
			numberOfDirections = std::stoi(argv[2]);
			postProcessingInput = argv[3];
		}
		else
		{
			std::cout<<"Zly pocet argumentov, executable, i/o folder, number of directions, path to directory with spectra\n";
			exit(-1);
		}
		if(numberOfDirections == 576)
		{
			numberOfDirections = 577;
		}
		if(postProcessingInput != "null")
		{
			std::string fileName = postProcessingInput + "/_metadata.ini";
			boost::property_tree::ptree pt;
			boost::property_tree::ini_parser::read_ini(fileName, pt);
			mainFile = pt.get<std::string>("General.MainFile");//"main_file.dat";
			variableBinWidth = pt.get<float>("General.SpectrumRangeScaling");
			rigEnergyFile = postProcessingInput + pt.get<std::string>("General.RigEnergyCorespondence");
			energyDivider = pt.get<float>("General.EnergyDivider");
			intensityDivider = pt.get<float>("General.IntensityDivider");
			dateRange = pt.get<bool>("General.IsForSpecificDateRange");
		}
		else
		{
			energyDivider = 1;
			intensityDivider = 1;
			variableBinWidth = 0.0;
		}
		outfilPrefix = outputFolder;
		cutOffRigPrefix = outputFolder+"cut_off_rig.dat";
		intensityYieldPrefix = outputFolder+"intensity_yield.dat";
		map = outputFolder+"mapa_over_atm_4x.dat";
		integr2sum =  outputFolder+"integr2sum";
		spectraBands =  outputFolder+"spectraBands";
		outfil_0 = outputFolder+"outfil_0";
		throughputPath = outputFolder+"throughputs.dat";
		
		yearDoy.init(&outfil_0);
	}
	
};

#endif