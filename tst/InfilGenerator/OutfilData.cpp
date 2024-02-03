#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include "infilGenerator.hpp"
#include "OutfilData.hpp"

TEST(outfil_test, readSecondLine){
    Arguments arguments;
    std::unique_ptr<OutfilData> outfilData;

    int argc = 3;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF_secondLineNull",
        (char*)"filenamePrefix"
    };

    arguments.parseArguments(argc, argv);
    outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
    NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());

    EXPECT_EXIT(outfilData->readInput(&(arguments.inputFile)), ::testing::ExitedWithCode(255), ".*");
}

TEST(outfil_test, readSecondLine_1){
    Arguments arguments;
    std::unique_ptr<OutfilData> outfilData;

    int argc = 3;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF_secondLine_<6",
        (char*)"filenamePrefix"
    };

    arguments.parseArguments(argc, argv);
    outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
    NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());

    EXPECT_EXIT(outfilData->readInput(&(arguments.inputFile)), ::testing::ExitedWithCode(255), ".*");
}

TEST(outfil_test, readSecondLine_2){
    Arguments arguments;
    std::unique_ptr<OutfilData> outfilData;

    int argc = 3;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF_secondLine_>6",
        (char*)"filenamePrefix"
    };

    arguments.parseArguments(argc, argv);
    outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
    NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());

    EXPECT_EXIT(outfilData->readInput(&(arguments.inputFile)), ::testing::ExitedWithCode(255), ".*");
}

TEST(outfil_test, readSecondLine_3){
    Arguments arguments;
    std::unique_ptr<OutfilData> outfilData;

    int argc = 3;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF_secondLine_>6",
        (char*)"filenamePrefix"
    };

    arguments.parseArguments(argc, argv);
    outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
    NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());

    EXPECT_EXIT(outfilData->readInput(&(arguments.inputFile)), ::testing::ExitedWithCode(255), ".*");
}

TEST(outfil_test, readSecondLine_4){
    Arguments arguments;
    std::unique_ptr<OutfilData> outfilData;

    int argc = 3;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF_secondLine_dStr",
        (char*)"filenamePrefix"
    };

    arguments.parseArguments(argc, argv);
    outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
    NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());

    EXPECT_EXIT(outfilData->readInput(&(arguments.inputFile)), ::testing::ExitedWithCode(255), ".*");
}

TEST(outfil_test, readSecondLine_5){
    Arguments arguments;
    std::unique_ptr<OutfilData> outfilData;

    int argc = 3;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF_secondLine_fStr",
        (char*)"filenamePrefix"
    };

    arguments.parseArguments(argc, argv);
    outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
    NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());

    EXPECT_EXIT(outfilData->readInput(&(arguments.inputFile)), ::testing::ExitedWithCode(255), ".*");
}

TEST(rigidityData, setRigidityData){
    Arguments arguments;
    std::unique_ptr<OutfilData> outfilData;

    int argc = 3;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF",
        (char*)"filenamePrefix"
    };

    arguments.parseArguments(argc, argv);
    outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
    NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());

    outfilData->readInput(&(arguments.inputFile));

    EXPECT_FLOAT_EQ(normalOutfil->rigidityData.rigidityStep, 0.1);
}

TEST(rigidityData, setRigidityData_1){
    Arguments arguments;
    std::unique_ptr<OutfilData> outfilData;

    int argc = 3;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF_minus_rigidity",
        (char*)"filenamePrefix"
    };

    arguments.parseArguments(argc, argv);
    outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
    NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());

    outfilData->readInput(&(arguments.inputFile));

    EXPECT_FLOAT_EQ(normalOutfil->rigidityData.rigidityStep, 0.1);
}

TEST(version_test, version){
    int inVersion = 0;

    Version version;
    
    version = (Version) inVersion;

    EXPECT_EQ(version, Version::T96);
}

TEST(version_test, version_1){
    int inVersion = 9;

    Version version;

    version = (Version) inVersion;

    EXPECT_EQ(version, NULL);
}

TEST(gererateInfils_test, generateInfils){
    Arguments arguments;
    std::unique_ptr<OutfilData> outfilData;

    int argc = 3;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF",
        (char*)"filenamePrefix"
    };

    arguments.parseArguments(argc, argv);
    outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
    NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());

    outfilData->readInput(&(arguments.inputFile));

    EXPECT_EQ(outfilData->generateInfils, true);
}

TEST(gererateInfils_test, generateInfils_1){
    Arguments arguments;
    std::unique_ptr<OutfilData> outfilData;

    int argc = 3;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF_generateInfils",
        (char*)"filenamePrefix"
    };

    arguments.parseArguments(argc, argv);
    outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
    NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());

    outfilData->readInput(&(arguments.inputFile));

    EXPECT_EQ(outfilData->generateInfils, false);
}

TEST(gererateInfils_test, generateInfils_2){
    Arguments arguments;
    std::unique_ptr<OutfilData> outfilData;

    int argc = 3;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF_generateInfils_1",
        (char*)"filenamePrefix"
    };

    arguments.parseArguments(argc, argv);
    outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
    NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());

    outfilData->readInput(&(arguments.inputFile));

    EXPECT_EQ(outfilData->generateInfils, false);
}

TEST(generateInfil_test, optimazeRigidity){
    Arguments arguments;
    std::unique_ptr<OutfilData> outfilData;

    int argc = 3;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF",
        (char*)"filenamePrefix"
    };

    arguments.parseArguments(argc, argv);
    outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
    NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());

    outfilData->readInput(&(arguments.inputFile));
    
    EXPECT_FLOAT_EQ(normalOutfil->rigidityData.rigstart, 5.9);
    EXPECT_FLOAT_EQ(normalOutfil->rigidityData.rigend, 14.75);
}

// TEST(generateInfil_test, optimazeRigidity){
//     Arguments arguments;
//     std::unique_ptr<OutfilData> outfilData;

//     int argc = 3;
//     char *argv[] = {
//         (char*)"./InfilGenerator",
//         (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF",
//         (char*)"filenamePrefix"
//     };

//     arguments.parseArguments(argc, argv);
//     outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
//     NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());

//     outfilData->readInput(&(arguments.inputFile));

//     EXPECT_FLOAT_EQ(normalOutfil->rigidityData.rigstart, 5.9);
//     EXPECT_FLOAT_EQ(normalOutfil->rigidityData.rigend, 14.75);
// }