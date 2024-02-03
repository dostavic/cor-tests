#ifndef DATAVECTORS_HPP
#define DATAVECTORS_HPP

#include "structs.hpp"
#include "SpectrumLoader.hpp"

struct DataVectors
{
	std::vector<std::vector<CoordinatesAndValues>> matrix;
	std::vector<std::vector<OutfilData>> outfilData;
	std::vector<std::vector<Band>> bandVector;
	std::vector<std::unique_ptr<char[]>> buffer;
	double mapaend[binNum][binNum];
	double mapaasym[binNum][binNum];
	//StaticData *sd;
	std::vector<double> integr1O;
	ThroughputFunc throughputFunc;
	InputPhysicalData *ipd;
	DataVectors(/*StaticData *sd, */InputPhysicalData *ipd);
	/**
	 * @brief Creates maps of asymptotic directions and magnetospheric crossings into a text file by filling a map matrix.
	 */
	void createMaps();
	/**
	 * @brief Writes maps of asymptotic directions and magnetospheric crossings into a text file.
	 */
	void writeMaps();
	/**
	 * @brief Reads relevant information from outfil with number index and fills output parameters.
	 * @param index Input parameter. Index of outfil to be read.
	 */
	void readOufil(const unsigned int index);
	/**
	 * @brief Write file containing bands of spectra from outfils to file, format: one line = one outfil, odd number = start of band, even number = width of band
	 */
	void writeSpectraBands();
	/**
	 * @brief Calculate and write value of cosmic ray intensity to file.
	 */
	void writeIntegr2sum();
	/**
	 * @brief Write cut-off rigidities and intensity yields.
	 * @param lat Array of latitudes.
	 */
	void writeCAY(double *lat);
	
	/**
	 * @brief Function to process data from outfil with index index.
	 * @param index Index of outfil to be processed.
	 */
	void processData(const unsigned int index);
private:
	inline double computeIntensity(double rigLoc2);
};

#endif // DATAVECTORS_HPP
