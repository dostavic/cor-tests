#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "infilGenerator.hpp"
#include "OutfilData.hpp"

#include <string>

const int bufferSize = 1024;

class TrajectoryOutfilTest : public TrajectoryOutfil{
    public:
    using TrajectoryOutfil::readInputImpl;
    using TrajectoryOutfil::readSecondLine;
};

TEST(main_t96_trajectory, parseArguments){
    Arguments arguments;
    int argc = 4;
    char *argv[] = {
        (char*)"InfilGenerator",
        (char*)"./tst/InfilGenerator/correctInput/trajectory.dat0_T96",
        (char*)"./tst/InfilGenerator/outfill/trajectory_out.dat0_T96",
        (char*)"trajectory"
    };

    arguments.parseArguments(argc, argv);

    EXPECT_EQ(arguments.inputFile, 
        "./tst/InfilGenerator/correctInput/trajectory.dat0_T96");
    EXPECT_EQ(arguments.filenamePrefix, 
        "./tst/InfilGenerator/outfill/trajectory_out.dat0_T96");
    EXPECT_EQ(arguments.infilKind, InfilKind::TRAJECTORY);
}

TEST(main_t96_trajectory, readInput){
    Arguments arguments;
    arguments.inputFile = "./tst/InfilGenerator/correctInput/trajectory.dat0_T96";

    std::unique_ptr<OutfilData> outfilData(new TrajectoryOutfilTest());
    TrajectoryOutfilTest *trajectoryOutfilTest = 
        dynamic_cast<TrajectoryOutfilTest*>(outfilData.get());

    EXPECT_NO_THROW(outfilData->readInput(&(arguments.inputFile)));
}

TEST(main_t96_trajectory, readInputImpl){
    std::unique_ptr<OutfilData> outfilData(new TrajectoryOutfilTest());
    TrajectoryOutfilTest *trajectoryOutfilTest = 
        dynamic_cast<TrajectoryOutfilTest*>(outfilData.get());
    
    char buffer[bufferSize];
    std::string inputFile = "./tst/InfilGenerator/correctInput/trajectory.dat0_T96";
    FILE *gg = fopen(inputFile.c_str(), "r");

    trajectoryOutfilTest->readInputImpl(buffer, gg, &inputFile);

    fclose(gg);

    EXPECT_EQ(trajectoryOutfilTest->date.getYear(), 2002);
    EXPECT_EQ(trajectoryOutfilTest->date.getDoy(), 165);
    EXPECT_EQ(trajectoryOutfilTest->date.getHour(), 5);
    EXPECT_EQ(trajectoryOutfilTest->date.getDay(), 14);
    EXPECT_EQ(trajectoryOutfilTest->date.getMonth(), 6);
    EXPECT_FLOAT_EQ(trajectoryOutfilTest->geoLoc.geolat, 5);
    EXPECT_FLOAT_EQ(trajectoryOutfilTest->geoLoc.geolong, 5);
    EXPECT_FLOAT_EQ(trajectoryOutfilTest->geoLoc.radius, 1);
    EXPECT_FLOAT_EQ(trajectoryOutfilTest->localLoc.latloc, 0);
    EXPECT_FLOAT_EQ(trajectoryOutfilTest->localLoc.longloc, 0);
    EXPECT_FLOAT_EQ(trajectoryOutfilTest->rigidityData.rigstart, 32.5);
    EXPECT_FLOAT_EQ(trajectoryOutfilTest->rigidityData.rigend, 32.5);
}

TEST(main_t96_trajectory, readSecondLine){
    std::unique_ptr<OutfilData> outfilData(new TrajectoryOutfilTest());
    TrajectoryOutfilTest *trajectoryOutfilTest = 
        dynamic_cast<TrajectoryOutfilTest*>(outfilData.get());
    
    char buffer[bufferSize];
    std::string inputFile = 
        "./tst/InfilGenerator/correctInput/trajectory.dat0_T96_line_2";
    FILE *gg = fopen(inputFile.c_str(), "r");

    trajectoryOutfilTest->readSecondLine(buffer, &inputFile, gg);

    fclose(gg);

    EXPECT_EQ(trajectoryOutfilTest->generateInfils, 1);
    EXPECT_EQ(trajectoryOutfilTest->inputState, 0);
    EXPECT_EQ(trajectoryOutfilTest->version, Version::T96);
    EXPECT_EQ(trajectoryOutfilTest->numberOfDirections, 0);
    EXPECT_FLOAT_EQ(trajectoryOutfilTest->rigidityData.rigidityStep, 0.01);
    EXPECT_EQ(trajectoryOutfilTest->optimalizationLevel, 0);
}

TEST(main_t96_trajectory, readParmod){
    std::unique_ptr<OutfilData> outfilData(new TrajectoryOutfilTest());
    TrajectoryOutfilTest *trajectoryOutfilTest = 
        dynamic_cast<TrajectoryOutfilTest*>(outfilData.get());
    TrajectoryOutfilTest *castData = 
        dynamic_cast<TrajectoryOutfilTest*>(outfilData.get());

    int parmodError = 0;
    castData->date = Timestamp(2002, 165, 5);

    readParmod(&(castData->date), &(castData->magData), &parmodError);

    EXPECT_EQ(parmodError, 0);
    EXPECT_FLOAT_EQ(castData->magData.pdyn, 3.49);
    EXPECT_FLOAT_EQ(castData->magData.byimf, 0.1);
    EXPECT_FLOAT_EQ(castData->magData.bzimf, -1);
    EXPECT_FLOAT_EQ(castData->magData.dst, -20);
}

TEST(main_t96_trajectory, writeData){
    Arguments arguments;

    int argc = 4;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./tst/InfilGenerator/correctInput/trajectory.dat0_T96",
        (char*)"./tst/InfilGenerator/outfill/trajectory_out.dat0_T96",
        (char*)"trajectory"
    };

    arguments.parseArguments(argc, argv);

    std::unique_ptr<OutfilData> outfilData(new TrajectoryOutfilTest());
    TrajectoryOutfilTest *trajectoryOutfilTest = 
        dynamic_cast<TrajectoryOutfilTest*>(outfilData.get());

    outfilData->readInput(&(arguments.inputFile));

    int parmodError = 0;

    TrajectoryOutfilTest *castData = 
        dynamic_cast<TrajectoryOutfilTest*>(outfilData.get());

    readParmod(&(castData->date), &(castData->magData), &parmodError);
    outfilData->writeData(&(arguments.filenamePrefix), 0);

    FILE *f = fopen("./tst/InfilGenerator/outfill/trajectory_out.dat0_T96_0", "r");

    EXPECT_NE(f, nullptr);

    float rigstart, rigend;
    int res = fscanf(f, "%f -1. %f\n", &rigstart, &rigend);

    EXPECT_EQ(res, 2);
    EXPECT_FLOAT_EQ(rigstart, 32.5);
    EXPECT_FLOAT_EQ(rigend, 32.5);

    float radius, geolat, geolong;
    res = fscanf(f, "%f %f %f\n", &radius, &geolat, &geolong);

    EXPECT_EQ(res, 3);
    EXPECT_FLOAT_EQ(radius, 1);
    EXPECT_FLOAT_EQ(geolat, 5);
    EXPECT_FLOAT_EQ(geolong, 5);

    float latloc, longloc;
    res = fscanf(f, "%f %f\n", &latloc, &longloc);

    EXPECT_EQ(res, 2);
    EXPECT_FLOAT_EQ(latloc, 0);
    EXPECT_FLOAT_EQ(longloc, 0);

    int year, month, day, doy, hour;
    res = fscanf(f, "%d %d %d %d %d 00 00\n", &year, &month, &day, &doy, &hour);

    EXPECT_EQ(res, 5);
    EXPECT_EQ(year, 2002);
    EXPECT_EQ(month, 6);
    EXPECT_EQ(day, 14);
    EXPECT_EQ(doy, 165);
    EXPECT_EQ(hour, 5);

    float rigidityStep;
    res = fscanf(f, "100 1 1 %f\n", &rigidityStep);

    EXPECT_EQ(res, 1);
    EXPECT_FLOAT_EQ(rigidityStep, 0.01);

    float dst, pdyn, byimf, bzimf;
    res = fscanf(f, "%f %f %f %f\n", &dst, &pdyn, &byimf, &bzimf);

    EXPECT_EQ(res, 4);
    EXPECT_FLOAT_EQ(dst, -20);
    EXPECT_FLOAT_EQ(pdyn, 3.49);
    EXPECT_FLOAT_EQ(byimf, 0.1);
    EXPECT_FLOAT_EQ(bzimf, -1);

    res = fscanf(f, "-1.00\n");

    EXPECT_EQ(res, 0);

    fclose(f);
}