#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "OutfilData.hpp"
#include "infilGenerator.hpp"

#include <string>

const int bufferSize = 1024;

class TrajectoryOutfilTest : public TrajectoryOutfil{
    public:
    using TrajectoryOutfil::readInputImpl;
    using TrajectoryOutfil::readSecondLine;
};

TEST(main_igrf_trajectory, parseArgments){
    Arguments arguments;
    int argc = 4;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./tst/InfilGenerator/correctInput/trajectory.dat0_IGRF",
        (char*)"./tst/InfilGenerator/outfill/trajectory_out.dat0_IGRF",
        (char*)"trajectory"
    };

    arguments.parseArguments(argc, argv);

    EXPECT_EQ(arguments.inputFile, 
        "./tst/InfilGenerator/correctInput/trajectory.dat0_IGRF");
    EXPECT_EQ(arguments.filenamePrefix, 
        "./tst/InfilGenerator/outfill/trajectory_out.dat0_IGRF");
    EXPECT_EQ(arguments.infilKind, InfilKind::TRAJECTORY);
}

TEST(main_igrf_trajectory, readInput){
    Arguments arguments;
    arguments.inputFile = "./tst/InfilGenerator/correctInput/trajectory.dat0_IGRF";
    std::unique_ptr<OutfilData> outfilData(new TrajectoryOutfil());
    TrajectoryOutfil *trajectoryOutfil = 
        dynamic_cast<TrajectoryOutfil*>(outfilData.get());
    
    EXPECT_NO_THROW(outfilData->readInput(&(arguments.inputFile)));
}

TEST(main_igrf_trajectory, readInputImpl){
    std::unique_ptr<OutfilData> outfilData(new TrajectoryOutfilTest());
    TrajectoryOutfilTest *trajectoryOutfilTest = 
        dynamic_cast<TrajectoryOutfilTest*>(outfilData.get());
    char buffer[bufferSize];
    std::string inputFile = "./tst/InfilGenerator/correctInput/trajectory.dat0_IGRF";
    FILE *gg = fopen(inputFile.c_str(), "r");

    trajectoryOutfilTest->readInputImpl(buffer, gg, &inputFile);

    fclose(gg);

    EXPECT_EQ(trajectoryOutfilTest->date.getYear(), 2002);
    EXPECT_EQ(trajectoryOutfilTest->date.getDoy(), 165);
    EXPECT_EQ(trajectoryOutfilTest->date.getHour(), 5);
    EXPECT_FLOAT_EQ(trajectoryOutfilTest->geoLoc.geolat, 5);
    EXPECT_FLOAT_EQ(trajectoryOutfilTest->geoLoc.geolong, 5);
    EXPECT_FLOAT_EQ(trajectoryOutfilTest->geoLoc.radius, 1);
    EXPECT_FLOAT_EQ(trajectoryOutfilTest->localLoc.latloc, 0);
    EXPECT_FLOAT_EQ(trajectoryOutfilTest->localLoc.longloc, 0);
    EXPECT_FLOAT_EQ(trajectoryOutfilTest->rigidityData.rigstart, 32.5);
    EXPECT_FLOAT_EQ(trajectoryOutfilTest->rigidityData.rigend, 32.5);
    EXPECT_EQ(trajectoryOutfilTest->date.getDay(), 14);
    EXPECT_EQ(trajectoryOutfilTest->date.getMonth(), 6);
}

TEST(main_igrf_trajectory, readSecondLine){
    std::unique_ptr<OutfilData> outfilData(new TrajectoryOutfilTest());
    TrajectoryOutfilTest *trajectoryOutfilTest = 
        dynamic_cast<TrajectoryOutfilTest*>(outfilData.get());
    char buffer[bufferSize];
    std::string inputFile = 
        "./tst/InfilGenerator/correctInput/trajectory.dat0_IGRF_line_2";
    FILE *gg = fopen(inputFile.c_str(), "r");

    trajectoryOutfilTest->readSecondLine(buffer, &inputFile, gg);

    fclose(gg);

    EXPECT_EQ(trajectoryOutfilTest->generateInfils, 1);
    EXPECT_EQ(trajectoryOutfilTest->inputState, 0);
    EXPECT_EQ(trajectoryOutfilTest->version, Version::IGRF);
    EXPECT_EQ(trajectoryOutfilTest->numberOfDirections, 0);
    EXPECT_FLOAT_EQ(trajectoryOutfilTest->rigidityData.rigidityStep, 0.01);
    EXPECT_EQ(trajectoryOutfilTest->optimalizationLevel, 0);
}

TEST(main_igrf_trajectory, writeData){
    Arguments argumets;
    int argc = 4;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./tst/InfilGenerator/correctInput/trajectory.dat0_IGRF",
        (char*)"./tst/InfilGenerator/outfill/trajectory_out.dat0_IGRF"
    };

    argumets.parseArguments(argc, argv);

    std::unique_ptr<OutfilData> outfilData(new TrajectoryOutfilTest());
    TrajectoryOutfilTest *trajectoryOutfilTest = 
        dynamic_cast<TrajectoryOutfilTest*>(outfilData.get());

    outfilData->readInput(&(argumets.inputFile));
    outfilData->writeData(&(argumets.filenamePrefix), 0);

    FILE *f =fopen("./tst/InfilGenerator/outfill/trajectory_out.dat0_IGRF_0", "r");

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

    EXPECT_FLOAT_EQ(rigidityStep, 0.01);

    res = fscanf(f, "-1.00\n");

    EXPECT_EQ(res, 0);

    fclose(f);
}