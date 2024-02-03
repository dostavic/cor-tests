#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "geo_to_mag.hpp"
#include "infilGenerator.hpp"

#include <string>
#include <fstream>

#define Pi 3.14159265358979

TEST(readGGTest, successRead){
    std::string filePrefixH = "testfile.txt";
    double GreadHigh[10] = {};
    double HreadHigh[10] = {};
    std::ofstream testfile(filePrefixH);

    if(testfile.is_open()){
        testfile << "g 1 0 -31543\n"
                 << "g 1 1 -2298\n"
                 << "h 1 1 5922\n"
                 << "g 2 0 -677\n"
                 << "g 2 1 2905\n"
                 << "h 2 1 -1061\n"
                 << "g 2 2 924\n";
        testfile.close();
    }

    readGH(&filePrefixH, GreadHigh, HreadHigh);

    EXPECT_DOUBLE_EQ(GreadHigh[0], 0);
    EXPECT_DOUBLE_EQ(GreadHigh[1], -31543);    
    EXPECT_DOUBLE_EQ(GreadHigh[2], -2298);
    EXPECT_DOUBLE_EQ(HreadHigh[0], 0);
    EXPECT_DOUBLE_EQ(HreadHigh[1], 0);
    EXPECT_DOUBLE_EQ(HreadHigh[2], 5922);
    EXPECT_DOUBLE_EQ(GreadHigh[3], -677);
    EXPECT_DOUBLE_EQ(GreadHigh[4], 2905);
    EXPECT_DOUBLE_EQ(HreadHigh[3], 0);
    EXPECT_DOUBLE_EQ(HreadHigh[4], -1061);
    EXPECT_DOUBLE_EQ(GreadHigh[5], 924);
}

TEST(readGGTest, FileNotFound){
    std::string filePrefixH = "non_existing_file.txt";
    double GreadHigh[10] = {};
    double HreadHigh[10] = {};

    EXPECT_THROW(readGH(&filePrefixH, GreadHigh, HreadHigh), std::runtime_error);
}

TEST(readGGTest, InvalidFileFormat){
    std::string filePrefixH = "invalid_format_file.txt";
    double GreadHigh[10] = {};
    double HreadHigh[10] = {};
    std::ofstream testfile(filePrefixH);

    if(testfile.is_open()){
        testfile << "g 1 0 -31543\n"
                 << "g 1 1 -2298\n"
                 << "h 1 1 5922\n"
                 << "g 2 0 -677\n"
                 << "g 2 a 2905\n"
                 << "h 2 1 -1061\n"
                 << "g 2 2 924\n";
        testfile.close();
    }

    EXPECT_THROW(readGH(&filePrefixH, GreadHigh, HreadHigh), std::invalid_argument);
}

TEST(readGGTest, InvalidFirstSymbol){
    std::string filePrefixH = "invalidFirstSymbol.txt";
    double GreadHigh[10] = {};
    double HreadHigh[10] = {};
    std::ofstream file(filePrefixH);

    if(file.is_open()){
        file << "1 0 -31543\n";

        file.close();
    }

    EXPECT_THROW(readGH(&filePrefixH, GreadHigh, HreadHigh), std::invalid_argument);
}


// потрібна перевірка на рік
TEST(RECALC_08, test){
    int year = 2010, day = 1;
    double CL0, SL0, CTSL, CTCL, ST0, STCL, STSL, CT0;

    RECALC_08(year, day, &CL0, &SL0, &CTSL, &CTCL, &ST0, &STCL, &STSL, &CT0);

    EXPECT_DOUBLE_EQ(CL0, 0.30551927718368854);
    EXPECT_DOUBLE_EQ(SL0, -0.9521858911311154);
    EXPECT_DOUBLE_EQ(CTSL, -0.93776624931695274);
    EXPECT_DOUBLE_EQ(CTCL, 0.3008925770977659);
    EXPECT_DOUBLE_EQ(ST0, 0.17337277378377469);
    EXPECT_DOUBLE_EQ(STCL, 0.052968724529749989);
    EXPECT_DOUBLE_EQ(STSL, -0.16508310910317678);
    EXPECT_DOUBLE_EQ(CT0, 0.98485627444339319);
}

TEST(getLocalRotations, test){
    float longitude = ((0) * 10) * (Pi / 180);
    float lat[16];

    fillArrays(lat);

    float lat1 = lat[0] * (Pi / 180);
    float geolat = -42;
    float geolong = 270;
    float latloc = -42;
    float longloc = 270;

    getLocalRotations(longitude, lat1, geolat, geolong, &(latloc), &(longloc));

    EXPECT_FLOAT_EQ(latloc, -40.407562);
    EXPECT_FLOAT_EQ(longloc, 250.98932);
}

TEST(getToMagCorrected, test){
    int year = 2010, day = 1;
    float geolat = -42;
    float geolong = 270;
    float geoAltitude = 6371.185 * 1;
    float geomag_latitude = 0;
    float geomag_longitude = 0;
    float geomag_altitude = 0;

    geoToMagCorrected(year, day, geolat, geolong, geoAltitude, 
        &geomag_latitude, &geomag_longitude, &geomag_altitude);
    
    EXPECT_FLOAT_EQ(geomag_latitude, -32.433273);
    EXPECT_FLOAT_EQ(geomag_longitude, 344.3949);
    EXPECT_FLOAT_EQ(geomag_altitude, 6371.1851);
}