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

TEST(main_t05, parseArguments){
    Arguments arguments;
    int argc = 3;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_T05",
        (char*)"./tst/InfilGenerator/outfill/caspoloha_out.dat0_T05"
    };

    arguments.parseArguments(argc, argv);

    EXPECT_EQ(arguments.inputFile, "./tst/InfilGenerator/correctInput/caspoloha.dat0_T05");
    EXPECT_EQ(arguments.filenamePrefix, "./tst/InfilGenerator/outfill/caspoloha_out.dat0_T05");
    EXPECT_EQ(arguments.infilKind, InfilKind::NORMAL);
}

TEST(main_outfilData_t05, readInputImpl){
    std::unique_ptr <OutfilData> outfilData(new NormalOutfilTest());
    NormalOutfilTest *normalOutfilTest = dynamic_cast<NormalOutfilTest*>(outfilData.get());

    char buffer[bufferSize];
    std::string inputFile = "./tst/InfilGenerator/correctInput/caspoloha.dat0_T05";
    FILE *gg = fopen(inputFile.c_str(), "r");

    normalOutfilTest->callReadInputImpl(buffer, gg, &(inputFile));

    fclose(gg);

    EXPECT_EQ(normalOutfilTest->date.getYear(), 2008);
    EXPECT_EQ(normalOutfilTest->date.getDoy(), 120);
    EXPECT_EQ(normalOutfilTest->date.getHour(), 13);
    EXPECT_FLOAT_EQ(normalOutfilTest->geoLoc.geolat, -43);
    EXPECT_FLOAT_EQ(normalOutfilTest->geoLoc.geolong, 210);
    EXPECT_FLOAT_EQ(normalOutfilTest->geoLoc.radius, 1);
    EXPECT_FLOAT_EQ(normalOutfilTest->localLoc.longloc, 210);
    EXPECT_FLOAT_EQ(normalOutfilTest->localLoc.latloc, -43);
}

TEST(main_oufilDat_t05, readSecondLine){
    std::unique_ptr <OutfilData> outfilData(new NormalOutfilTest());
    NormalOutfilTest *normalOutfilTest = dynamic_cast<NormalOutfilTest*>(outfilData.get());

    char buffer[bufferSize];
    std::string inputFile = "./tst/InfilGenerator/correctInput/caspoloha.dat0_T05_line_2";
    FILE *gg = fopen(inputFile.c_str(), "r");

    
    normalOutfilTest->callReadSecondLine(buffer, &(inputFile), gg);

    fclose(gg);

    EXPECT_EQ(normalOutfilTest->generateInfils, 1);
    EXPECT_EQ(normalOutfilTest->inputState, 80);
    EXPECT_EQ(normalOutfilTest->version, Version::T05);
    EXPECT_EQ(normalOutfilTest->numberOfDirections, 1);
    EXPECT_FLOAT_EQ(normalOutfilTest->rigidityData.rigidityStep, 0.1);
    EXPECT_EQ(normalOutfilTest->optimalizationLevel, 2);
}

TEST(main_oufilData_t05, optimizeRigidity){
    std::unique_ptr <OutfilData> outfilData(new NormalOutfilTest());
    NormalOutfilTest *normalOutfilTest = dynamic_cast<NormalOutfilTest*>(outfilData.get());

    normalOutfilTest->geoLoc.geolat = -43;
    normalOutfilTest->geoLoc.geolong = 210;
    normalOutfilTest->geoLoc.radius = 1;
    normalOutfilTest->magData.dst = 0;

    optimizeRigidity(&(normalOutfilTest->geoLoc), &(normalOutfilTest->rigidityData), normalOutfilTest->magData.dst);

    EXPECT_FLOAT_EQ(normalOutfilTest->rigidityData.rigstart, 3.3);
    EXPECT_FLOAT_EQ(normalOutfilTest->rigidityData.rigend, 10);
}

TEST(main_outfilData_t05, readParmod){
    std::unique_ptr <OutfilData> outfilData(new NormalOutfilTest());
    NormalOutfilTest *normalOutfilTest = dynamic_cast<NormalOutfilTest*>(outfilData.get());
    TrajectoryOutfil *castData = dynamic_cast<TrajectoryOutfil*>(outfilData.get());

    int parmodError = 0;
    castData->date = Timestamp(2008, 120, 13);

    readParmod(&(castData->date), &(castData->magData), &parmodError);

    EXPECT_EQ(parmodError, 0);
    EXPECT_FLOAT_EQ(castData->magData.pdyn, 3.49);
    EXPECT_FLOAT_EQ(castData->magData.byimf, 0.1);
    EXPECT_FLOAT_EQ(castData->magData.bzimf, -1);
    EXPECT_FLOAT_EQ(castData->magData.dst, -20);
}

TEST(main_outfilData_t05, readOMNI){
    std::unique_ptr <OutfilData> outfilData(new NormalOutfilTest());
    NormalOutfilTest *normalOutfilTest = dynamic_cast<NormalOutfilTest*>(outfilData.get());
    TrajectoryOutfil *castData = dynamic_cast<TrajectoryOutfil*>(outfilData.get());

    int omniError = 0;
    castData->date = Timestamp(2008, 120, 13);

    readOMNI(&(castData->date), &(castData->tIndices), &omniError);

    EXPECT_FLOAT_EQ(castData->tIndices.W1, 0.15);
    EXPECT_FLOAT_EQ(castData->tIndices.W2, 0.16);
    EXPECT_FLOAT_EQ(castData->tIndices.W3, 0.19);
    EXPECT_FLOAT_EQ(castData->tIndices.W4, 0.11);
    EXPECT_FLOAT_EQ(castData->tIndices.W5, 0.34);
    EXPECT_FLOAT_EQ(castData->tIndices.W6, 0.22);
    EXPECT_EQ(castData->tIndices.success, LineState::NOT_FOUND);
    EXPECT_EQ(omniError, 0);
}

TEST(main_outfilData_t05, writeData_mag){
    Arguments arguments;
    std::unique_ptr<OutfilData> outfilData;

    int argc = 3;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_T05",
        (char*)"./tst/InfilGenerator/outfill/caspoloha_out.dat0_T05"
    };

    arguments.parseArguments(argc, argv);
    outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
    NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());
    outfilData->readInput(&(arguments.inputFile));
    int parmodError  = 0;
    int omniError = 0;
    TrajectoryOutfil *castData = dynamic_cast<TrajectoryOutfil*>(outfilData.get());
    readParmod(&(castData->date), &(castData->magData), &parmodError);
    readOMNI(&(castData->date), &(castData->tIndices), &omniError);
    outfilData->writeData(&(arguments.filenamePrefix), 0);

    FILE *f = fopen("./tst/InfilGenerator/outfill/caspoloha_out.dat0_T05_0", "r");
    EXPECT_NE(f, nullptr);

    float one, two, three, four, five, six;
    int one_0, two_0, three_0, four_0, five_0;

    int res = fscanf(f, "%f -1. %f\n", &one, &two);
    EXPECT_EQ(res, 2);
    EXPECT_FLOAT_EQ(one, 3.3);
    EXPECT_FLOAT_EQ(two, 10);

    res = fscanf(f, "%f %f %f\n", &one, &two, &three);
    EXPECT_EQ(res, 3);
    EXPECT_FLOAT_EQ(one, 1.0);
    EXPECT_FLOAT_EQ(two, -43);
    EXPECT_FLOAT_EQ(three, 210);

    res = fscanf(f, "%f %f\n", &one, &two);
    EXPECT_EQ(res, 2);
    EXPECT_FLOAT_EQ(one, -43);
    EXPECT_FLOAT_EQ(two, 210);

    res = fscanf(f, "%d %d %d %d %d 00 00\n", &one_0, &two_0, &three_0, &four_0, &five_0);
    EXPECT_FLOAT_EQ(res, 5);
    EXPECT_FLOAT_EQ(one_0, 2008);
    EXPECT_FLOAT_EQ(two_0, 4);
    EXPECT_FLOAT_EQ(three_0, 29);
    EXPECT_FLOAT_EQ(four_0, 120);
    EXPECT_FLOAT_EQ(five_0, 13);

    res = fscanf(f, "100 1 1 %f\n", &one);
    EXPECT_EQ(res, 1);
    EXPECT_FLOAT_EQ(one, 0.1);

    res = fscanf(f, "%f %f %f %f\n", &one, &two, &three, &four);
    EXPECT_EQ(res, 4);
    EXPECT_FLOAT_EQ(one, -20);
    EXPECT_FLOAT_EQ(two, 3.49);
    EXPECT_FLOAT_EQ(three, 0.1);
    EXPECT_FLOAT_EQ(four, -1);

    res = fscanf(f, "%f %f %f %f %f %f\n", &one, &two, &three, &four, &five, &six);
    EXPECT_EQ(res, 6);
    EXPECT_FLOAT_EQ(one, 0.15);
    EXPECT_FLOAT_EQ(two, 0.16);
    EXPECT_FLOAT_EQ(three, 0.19);
    EXPECT_FLOAT_EQ(four, 0.11);
    EXPECT_FLOAT_EQ(five, 0.34);
    EXPECT_FLOAT_EQ(six, 0.22);

    res = fscanf(f, "-1.00\n");
    EXPECT_EQ(res, 0);

    fclose(f);
}