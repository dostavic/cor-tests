#ifndef INFILGENERATOR_HPP
#define INFILGENERATOR_HPP

#include "OutfilData.hpp"

/// Enum of possible states
enum State : int
{
	NO_ERROR = 0,					///< 0 No error/null.
	W_INDICES = 1 << 0,				///< 1 Missing W1..6 indexes.
	PDYN = 1 << 1,					///< 2 Missing Solar wind preassure pdyn.
	IMF_Y = 1 << 2,					///< 4 Missing Interplanetary magnetic field y-component.
	IMF_Z = 1 << 3,					///< 8 Missing Interplanetary magnetic field z-component.
	DST = 1 << 4,					///< 16 Missing Geomagnetic index DST.
	UNUSED_ERROR_STATE_1 = 1 << 5,	///< 32 First unused error code
	UNUSED_ERROR_STATE_2 = 1 << 6,	///< 64 No numeric value higher that this is an error code.
	PROCESSING = 'P',				///< 80 Code for data that is being processed.
	WAITING = 'W',					///< 87 Code for data that is waiting to be processed.
	READY = 'R',					///< 82 Code for data that is ready and no errors occured durind calculation.
	REPROCESS = 83,					///< 83 Code for data that is waiting to be post processed again.
};
enum OptimizationLevel : int
{
	O_LEVEL_0 = 0, /**< No optimization. */
	O_LEVEL_1 = 1, /**< First level of optimization. */
	O_LEVEL_2 = 2, /**< Second level of optimization. */
	O_LEVEL_3 = 3, /**< Third level of optimization. */
};

/**
 * @brief Returns local coordinates.
 * @param longitude Longitude,
 * @param lat1 Latitude.
 * @param geolat Geographic latitude.
 * @param geolong Geographic longitude.
 * @param latloc Output local latitude.
 * @param longloc Output local longitude.
 */
void getLocalRotations(float longitude, float lat1, float geolat, float geolong, float *latloc, float *longloc);
/**
 * @brief Fills array with specific values and produces coded error.
 * @param lat Pointer to array to fill.
 */
void fillArrays(float * lat);

/**
 * @brief Reads OMNI file. If there is no entry that satisfies query, sets every output paramter to zero.
 * @param date Input date.
 * @param indices Indices for T05 version.
 * @param error Output error binary field.
 */
void readOMNI(Timestamp *date, T05Indices *indices,int *error);

/**
 * @brief Reads Parmod file. If there is no entry that satisfies query, returns everything as zero.
 * @param date Input date.
 * @param magData Output magnetosphere data.
 * @param error Output error binary field.
 */
void readParmod(Timestamp *date,MagnetosphereData *magData,int *error);

struct OmniLine : public Printable
{
	Timestamp date;
	T05Indices indices;
	OmniLine(int year, int doy, int hour, T05Indices indices) : date(year,doy,hour), indices(indices) {}
	void print() override
	{
		date.print();
		indices.print();
	}
};

struct ParmodLine : public Printable
{
	Timestamp date;
	MagnetosphereData magData;
	ParmodLine(int year, int doy, int hour, MagnetosphereData magData) : date(year,doy,hour), magData(magData)
	{
	}
	void print() override
	{
		date.print();
		magData.print();
	}
};
void readOMNIVector(MagFieldOutfil *castData , int *error);
void readParmodVector(MagFieldOutfil *castData , int *error);

/**
 * @brief Optimizes starting and ending cutoff rigidity for vertical direction.
 * @param geoLoc Geographic location.
 * @param rigData Rigidity data.
 */
void optimizeRigidity(GeographicLocation *geoLoc, RigidityData *rigData, int dst);


/**
 * @class Arguments
 * @author Daniel
 * @date 25/02/19
 * @file infilGenerator.hpp
 * @brief Class that parses and holds command line arguments.
 */
struct Arguments
{
	std::string inputFile;
	std::string filenamePrefix = "infil";
	InfilKind infilKind = InfilKind::NORMAL;
	/**
	 * @brief Parse arguments from command line.
	 * @param argc Number of arguments.
	 * @param argv Pointer to array with arguments.
	 */
	void parseArguments(int argc, char** argv);
};

#endif