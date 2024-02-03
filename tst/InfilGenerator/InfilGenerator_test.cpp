#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include <deque>
#include <queue>
#include "infilGenerator.hpp"

template <typename T, int MaxLen, typename Container=std::deque<T>>
class FixedQueue : public std::queue<T, Container> 
{
public:
	void push(const T& value) 
	{
		if (this->size() == MaxLen) 
		{
			this->c.pop_front();
		}
		std::queue<T, Container>::push(value);
    }
	
	T at(int idx)
	{
		return this->c.at(idx);
	}
	
	constexpr static unsigned int getMaxLen()
	{
		return MaxLen;
	}
	constexpr static int getLastIdx()
	{
		return MaxLen - 1;
	}
};

struct CoordinateVal
{
	float lat,lon,val, diff;
	CoordinateVal(float lat,float lon,float val,float diff) : lat(lat), lon(lon), val(val), diff(diff) {}
	
	void print()
	{
		std::cout << lat << " " << lon << " " << val <<  " " << diff << "\n";
	}
};

TEST(parseArguments, argc_0){
    Arguments arguments;
    int argc = 0;
    char *argv[] = {};

    EXPECT_EXIT(arguments.parseArguments(argc, argv), ::testing::ExitedWithCode(1), ".*");
}

TEST(parseArguments, argc_3){
    Arguments arguments;
    int argc = 3;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./inputFile",
        (char*)"./filenamePrefix"
    };

    arguments.parseArguments(argc, argv);

    EXPECT_EQ(arguments.inputFile, "./inputFile");
    EXPECT_EQ(arguments.filenamePrefix, "./filenamePrefix");
    EXPECT_EQ(arguments.infilKind, InfilKind::NORMAL);
}

TEST(parseArguments, argc_4_trajectory){
    Arguments arguments;
    int argc = 4;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./inputFile",
        (char*)"./filenamePrefix",
        (char*)"trajectory"
    };

    arguments.parseArguments(argc, argv);

    EXPECT_EQ(arguments.inputFile, "./inputFile");
    EXPECT_EQ(arguments.filenamePrefix, "./filenamePrefix");
    EXPECT_EQ(arguments.infilKind, InfilKind::TRAJECTORY);
}

TEST(parseArguments, argc_4_mag){
    Arguments arguments;
    int argc = 4;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./inputFile",
        (char*)"./filenamePrefix",
        (char*)"mag"
    };

    arguments.parseArguments(argc, argv);

    EXPECT_EQ(arguments.inputFile, "./inputFile");
    EXPECT_EQ(arguments.filenamePrefix, "./filenamePrefix");
    EXPECT_EQ(arguments.infilKind, InfilKind::MAG_FIELD);
}

TEST(parseArguments, argc_4_none){
    Arguments arguments;
    int argc = 4;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./inputFile",
        (char*)"./filenamePrefix",
        (char*)"msfdfs"
    };

    arguments.parseArguments(argc, argv);

    EXPECT_EQ(arguments.inputFile, "./inputFile");
    EXPECT_EQ(arguments.filenamePrefix, "./filenamePrefix");
    EXPECT_EQ(arguments.infilKind, InfilKind::NORMAL);
}

TEST(getMaxLen, test){
    FixedQueue<CoordinateVal, 2> pointsQueue;

    EXPECT_EQ(pointsQueue.getMaxLen(), 2);
}

TEST(push, test){
    FixedQueue<CoordinateVal, 2> pointsQueue;

    pointsQueue.push(CoordinateVal(-100, 0, 0, 100));
    // -100 0 0 100

    EXPECT_FLOAT_EQ(pointsQueue.at(0).lat, -100);
    EXPECT_FLOAT_EQ(pointsQueue.at(0).lon, 0);
    EXPECT_FLOAT_EQ(pointsQueue.at(0).val, 0);
    EXPECT_FLOAT_EQ(pointsQueue.at(0).diff, 100);

    pointsQueue.push(CoordinateVal(-20, 1, 1, 20));
    // -100 0 0 100
    // -20 1 1 20

    EXPECT_FLOAT_EQ(pointsQueue.at(1).lat, -20);
    EXPECT_FLOAT_EQ(pointsQueue.at(1).lon, 1);
    EXPECT_FLOAT_EQ(pointsQueue.at(1).val, 1);
    EXPECT_FLOAT_EQ(pointsQueue.at(1).diff, 20);

    pointsQueue.push(CoordinateVal(-40, 2, 2, 40));
    // -20 1 1 20
    // -40 2 2 40

    EXPECT_FLOAT_EQ(pointsQueue.at(1).lat, -40);
    EXPECT_FLOAT_EQ(pointsQueue.at(1).lon, 2);
    EXPECT_FLOAT_EQ(pointsQueue.at(1).val, 2);
    EXPECT_FLOAT_EQ(pointsQueue.at(1).diff, 40);

    EXPECT_FLOAT_EQ(pointsQueue.at(0).lat, -20);
    EXPECT_FLOAT_EQ(pointsQueue.at(0).lon, 1);
    EXPECT_FLOAT_EQ(pointsQueue.at(0).val, 1);
    EXPECT_FLOAT_EQ(pointsQueue.at(0).diff, 20);
}

// TEST(skipLine, test){
//     FILE * ee = fopen("parmod_new.dat", "r");

//     skipLine(ee);

//     fclose(ee);
// }

