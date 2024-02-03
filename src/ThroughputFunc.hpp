#ifndef THROUGHPUTFUNC_HPP
#define THROUGHPUTFUNC_HPP
#include <vector>
#include <memory>

 
typedef float fPrecision; 
/**
 * @class ThroughputFunc
 * @author Daniel
 * @date 01/03/19
 * @file ThroughputFunc.hpp
 * @brief Class that places rigidities into bins and then creates file with throughput data.
 */
class ThroughputFunc
{
private:
	std::vector<std::unique_ptr<unsigned int[]>> throughputArray;
	fPrecision binWidth;
	unsigned int numberOfDirections;
	unsigned int maxRigidity;
	unsigned int numberOfBins;
	fPrecision deltaPerRigidity;
	fPrecision rigidityStep;
	unsigned int maxUnit;
	
	unsigned int multiplier;
	unsigned int maxRigMulti;
	unsigned int binWidthMulti;
	unsigned int minRig;
	/**
	 * @brief If calculationg more than one directions, fills all zero values above max with units.
	 */
	void fillZerothThroughput();
	/**
	 * @brief Computes index where zero values end and index where 1 values start.
	 * @param startIndex In/out parameter for start index.
	 * @param endIndex In/out parameter for end of non 100% index.
	 * @param arrayAddress Pointer to array to process.
	 */
	void getBorderIndices(unsigned int *startIndex, unsigned int *endIndex, fPrecision *arrayAddress);
public:
	ThroughputFunc(const fPrecision binWidth, const unsigned int numberOfDirections, const fPrecision rigidityStep, const unsigned int maxRigidity);
	~ThroughputFunc();
	
	/**
	 * @brief Places rigidity rig into right bin with direction index i.
	 * @param i Index of direction.
	 * @param rig Value of rigidity.
	 */
	void placeRigidity(const unsigned int i, fPrecision rig);
	
	/**
	 * @brief Writes file containing throughtput function for every direction and one for all directions together, each line one direction, final line all directions.
	 * @param outThroughput Pounter to string holding prefix of filename to write result to.
	 */
	void writeThroughputFunc(std::string *outThroughput);
};

#endif // THROUGHPUTFUNC_HPP
