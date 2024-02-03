#include <chrono>

#include "utilities.hpp"
#include "ThroughputFunc.hpp"



#include "structs.hpp"
#include "DataVectors.hpp"

//cppcheck --enable=all amsP.cpp
//g++ -std=c++11 amsP.cpp -o amsP -fopenmp -O2 -Wall -Werror
// ./amsP ./1998_158_12_-34.43_19.23_1.00_577_0.01_T05/ 577 ./PostProcessingSpectra/ main_file.dat

int main(int argc, char** argv)
{
	auto start_time = std::chrono::high_resolution_clock::now();
	StaticData consts(argc, argv);
	InputPhysicalData inputPhysicaldata(&consts);
	DataVectors dVectors(&inputPhysicaldata);
	auto end_time0 = std::chrono::high_resolution_clock::now();
	double chronoResult = (double)std::chrono::duration_cast<std::chrono::milliseconds>(end_time0 - start_time).count();
	std::cout << "Initialization took: " << chronoResult << "\n";
	#pragma omp parallel
	{
		#pragma omp for nowait schedule(dynamic, 1)
		for(unsigned int i = 0; i < consts.numberOfDirections; i++)
		{
			dVectors.readOufil(i);
		}
	}
	auto end_time1 = std::chrono::high_resolution_clock::now();///////
	chronoResult = (double)std::chrono::duration_cast<std::chrono::milliseconds>(end_time1 - end_time0).count();
	std::cout << "File reading took: " << chronoResult << "\n";
	#pragma omp parallel
	{
		#pragma omp for nowait schedule(static)
		for (unsigned int index = 0; index < consts.numberOfDirections; index++ )//do   {dat 16 ked sa dopocita}
		{
			dVectors.processData(index);
		}
	}
	auto end_timeP = std::chrono::high_resolution_clock::now();
	chronoResult = (double)std::chrono::duration_cast<std::chrono::milliseconds>(end_timeP - end_time1).count();
	std::cout << "Parallel computing took: " << chronoResult << "\n";
	dVectors.createMaps();
	auto end_timeS = std::chrono::high_resolution_clock::now();
	chronoResult = (double)std::chrono::duration_cast<std::chrono::milliseconds>(end_timeS - end_timeP).count();
	std::cout << "Serial computing took: " << chronoResult << "\n";
	auto end_time2 = std::chrono::high_resolution_clock::now();
	//chronoResult = (double)std::chrono::duration_cast<std::chrono::milliseconds>(end_time2 - end_time1).count();
	dVectors.writeCAY(inputPhysicaldata.lat);
	dVectors.writeMaps();
	dVectors.writeSpectraBands();
	dVectors.writeIntegr2sum();
	dVectors.throughputFunc.writeThroughputFunc(&consts.throughputPath);
	auto end_time3 = std::chrono::high_resolution_clock::now();
	chronoResult = (double)std::chrono::duration_cast<std::chrono::milliseconds>(end_time3 - end_time2).count();
	std::cout << "Writing files took: " << chronoResult << "\n";
	auto end_time = std::chrono::high_resolution_clock::now();
	chronoResult = (double)std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
	std::cout << "Everything took: " << chronoResult << "\n";
	return 0;
}
