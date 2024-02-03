#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include "infilGenerator.hpp"
#include "OutfilData.hpp"
#include "Timestamp.hpp"

const int bufferSize = 1024;

class NormalOutfilTest : public NormalOutfil {
    public: 
    void callReadInputImpl(char *buffer, FILE *gg, std::string* inputFile) {
        readInputImpl(buffer, gg, inputFile);
    }
    void callReadSecondLine(char *buffer, std::string *inputFile, FILE *gg) {
        readSecondLine(buffer, inputFile, gg);
    }
};

// class TimestampTest : public  {
//     public:

//     int getHoursSinceEpoch() const {
//         return internalTime.hoursSinceEpoch;
//     }
// };

TEST(main, fillArrays){
    float lat[16];

    fillArrays(lat);

    EXPECT_FLOAT_EQ(lat[0], 75.638488);
    EXPECT_FLOAT_EQ(lat[1], 64.992167);
    EXPECT_FLOAT_EQ(lat[2], 57.538255);
    EXPECT_FLOAT_EQ(lat[3], 51.375167);
    EXPECT_FLOAT_EQ(lat[4], 45.951374);
    EXPECT_FLOAT_EQ(lat[5], 41.0145);
    EXPECT_FLOAT_EQ(lat[6], 36.423574);
    EXPECT_FLOAT_EQ(lat[7], 32.089951);
    EXPECT_FLOAT_EQ(lat[8], 27.953187);
    EXPECT_FLOAT_EQ(lat[9], 23.969482);
    EXPECT_FLOAT_EQ(lat[10], 20.10551);
    EXPECT_FLOAT_EQ(lat[11], 16.334823);
    EXPECT_FLOAT_EQ(lat[12], 12.635625);
    EXPECT_FLOAT_EQ(lat[13], 8.989299);
    EXPECT_FLOAT_EQ(lat[14], 5.379379);
    EXPECT_FLOAT_EQ(lat[15], 1.790785);
}

TEST(main, parseArguments){
    Arguments arguments;
    int argc = 3;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF",
        (char*)"./tst/InfilGenerator/outfill/caspoloha_out.dat0_IGRF"
    };

    arguments.parseArguments(argc, argv);

    EXPECT_EQ(arguments.inputFile, "./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF");
    EXPECT_EQ(arguments.filenamePrefix, "./tst/InfilGenerator/outfill/caspoloha_out.dat0_IGRF");
    EXPECT_EQ(arguments.infilKind, InfilKind::NORMAL);
}

TEST(main, normalOutfill){
    std::unique_ptr<OutfilData> oufilData(new NormalOutfil());

    EXPECT_NE(oufilData.get(), nullptr);
}

TEST(main, readInput){
    std::string inputFile = "./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF";
    std::unique_ptr<OutfilData> oufilData(new NormalOutfil());

    EXPECT_NO_THROW(oufilData->readInput(&(inputFile)));
}

// Неможливо
// TEST(main_oufilData, fromYDH){
//     unsigned year = 2010;
//     unsigned short doy = 1;
//     unsigned short hour = 0;

//     TimestampTest date(0);
//     date.fromYDH(year, doy, hour);

//     EXPECT_EQ(date.internalTime.hoursSinceEpoch, 200);
// }

TEST(main_outfilData, readInputImpl){
    std::unique_ptr <OutfilData> outfilData(new NormalOutfilTest());
    NormalOutfilTest *normalOutfilTest = dynamic_cast<NormalOutfilTest*>(outfilData.get());

    char buffer[bufferSize];
    std::string inputFile = "./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF";
    FILE *gg = fopen(inputFile.c_str(), "r");

    normalOutfilTest->callReadInputImpl(buffer, gg, &(inputFile));

    fclose(gg);

    EXPECT_EQ(normalOutfilTest->date.getYear(), 2010);
    EXPECT_EQ(normalOutfilTest->date.getDoy(), 1);
    EXPECT_EQ(normalOutfilTest->date.getHour(), 0);
    EXPECT_FLOAT_EQ(normalOutfilTest->geoLoc.geolat, -42);
    EXPECT_FLOAT_EQ(normalOutfilTest->geoLoc.geolong, 270);
    EXPECT_FLOAT_EQ(normalOutfilTest->geoLoc.radius, 1);
    EXPECT_FLOAT_EQ(normalOutfilTest->localLoc.longloc, 270);
    EXPECT_FLOAT_EQ(normalOutfilTest->localLoc.latloc, -42);
}

TEST(main_oufilData, readSecondLine){
    std::unique_ptr <OutfilData> outfilData(new NormalOutfilTest());
    NormalOutfilTest *normalOutfilTest = dynamic_cast<NormalOutfilTest*>(outfilData.get());

    char buffer[bufferSize];
    std::string inputFile = "./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF_2_line";
    FILE *gg = fopen(inputFile.c_str(), "r");

    
    normalOutfilTest->callReadSecondLine(buffer, &(inputFile), gg);

    fclose(gg);

    EXPECT_EQ(normalOutfilTest->generateInfils, 1);
    EXPECT_EQ(normalOutfilTest->inputState, 80);
    EXPECT_EQ(normalOutfilTest->version, Version::IGRF);
    EXPECT_EQ(normalOutfilTest->numberOfDirections, 1);
    EXPECT_FLOAT_EQ(normalOutfilTest->rigidityData.rigidityStep, 0.1);
    EXPECT_EQ(normalOutfilTest->optimalizationLevel, 2);
}

TEST(main_oufilData, optimizeRigidity){
    std::unique_ptr <OutfilData> outfilData(new NormalOutfilTest());
    NormalOutfilTest *normalOutfilTest = dynamic_cast<NormalOutfilTest*>(outfilData.get());

    normalOutfilTest->geoLoc.geolat = -42;
    normalOutfilTest->geoLoc.geolong = 270;
    normalOutfilTest->geoLoc.radius = 1;
    normalOutfilTest->magData.dst = 0;

    optimizeRigidity(&(normalOutfilTest->geoLoc), &(normalOutfilTest->rigidityData), normalOutfilTest->magData.dst);

    EXPECT_FLOAT_EQ(normalOutfilTest->rigidityData.rigstart, 5.9);
    EXPECT_FLOAT_EQ(normalOutfilTest->rigidityData.rigend, 14.75);
}

TEST(main_outfilData, writeData_normal){
    Arguments arguments;
    std::unique_ptr<OutfilData> outfilData;

    int argc = 3;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF",
        (char*)"./tst/InfilGenerator/outfill/filenamePrefix"
    };

    arguments.parseArguments(argc, argv);
    outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
    NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());
    outfilData->readInput(&(arguments.inputFile));
    outfilData->writeData(&(arguments.filenamePrefix), 0);

    FILE *f = fopen("./tst/InfilGenerator/outfill/filenamePrefix_0", "r");
    EXPECT_NE(f, nullptr);

    float one, two, three;
    int one_0, two_0, three_0, four_0, five_0;

    int res = fscanf(f, "%f -1. %f\n", &one, &two);
    EXPECT_EQ(res, 2);
    EXPECT_FLOAT_EQ(one, 5.9);
    EXPECT_FLOAT_EQ(two, 14.75);

    res = fscanf(f, "%f %f %f\n", &one, &two, &three);
    EXPECT_EQ(res, 3);
    EXPECT_FLOAT_EQ(one, 1.0);
    EXPECT_FLOAT_EQ(two, -42);
    EXPECT_FLOAT_EQ(three, 270);

    res = fscanf(f, "%f %f\n", &one, &two);
    EXPECT_EQ(res, 2);
    EXPECT_FLOAT_EQ(one, -42);
    EXPECT_FLOAT_EQ(two, 270);

    res = fscanf(f, "%d %d %d %d %d 00 00\n", &one_0, &two_0, &three_0, &four_0, &five_0);
    EXPECT_FLOAT_EQ(res, 5);
    EXPECT_FLOAT_EQ(one_0, 2010);
    EXPECT_FLOAT_EQ(two_0, 1);
    EXPECT_FLOAT_EQ(three_0, 1);
    EXPECT_FLOAT_EQ(four_0, 1);
    EXPECT_FLOAT_EQ(five_0, 0);
}