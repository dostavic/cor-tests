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
    void callSetRigidityStep(float rigidityStep){
        setRigidityStep(rigidityStep);
    }
};

class MagFieldOutfilTest : public MagFieldOutfil{
    public:
    using MagFieldOutfil::readInputImpl;
};

class TrajectoryOutfilTest : public TrajectoryOutfil{
    public:
    using TrajectoryOutfil::readInputImpl;
};

TEST(readInput, no_file_normal){
    std::string inputFile = "sdfsd";
    std::unique_ptr<OutfilData> outfilData(new NormalOutfil());

    EXPECT_EXIT(outfilData->readInput(&(inputFile)), ::testing::ExitedWithCode(4), ".*");
}

TEST(readInput, no_file_trajectory){
    std::string inputFile = "sdfsd";
    std::unique_ptr<OutfilData> outfilData(new TrajectoryOutfil());

    EXPECT_EXIT(outfilData->readInput(&(inputFile)), ::testing::ExitedWithCode(4), ".*");
}

TEST(readInput, no_file_mag){
    std::string inputFile = "sdfsd";
    std::unique_ptr<OutfilData> outfilData(new MagFieldOutfil());

    EXPECT_EXIT(outfilData->readInput(&(inputFile)), ::testing::ExitedWithCode(4), ".*");
}

TEST(readInputImpl, normal_no_file){
    std::unique_ptr <OutfilData> outfilData(new NormalOutfilTest());
    NormalOutfilTest *normalOutfilTest = dynamic_cast<NormalOutfilTest*>(outfilData.get());

    char buffer[bufferSize];
    std::string inputFile = "sasddas";
    FILE *gg = NULL;

    EXPECT_EXIT(normalOutfilTest->callReadInputImpl(buffer, gg, &(inputFile)), ::testing::ExitedWithCode(255), ".*");
}

TEST(readInputImpl, normal_file){
    std::unique_ptr <OutfilData> outfilData(new NormalOutfilTest());
    NormalOutfilTest *normalOutfilTest = dynamic_cast<NormalOutfilTest*>(outfilData.get());

    char buffer[bufferSize];
    std::string inputFile = "./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF";
    FILE *gg = fopen(inputFile.c_str(), "r");

    EXPECT_NO_THROW(normalOutfilTest->callReadInputImpl(buffer, gg, &(inputFile)));

    fclose(gg);
}

TEST(readInputImpl, normal_count_5){
    std::unique_ptr <OutfilData> outfilData(new NormalOutfilTest());
    NormalOutfilTest *normalOutfilTest = dynamic_cast<NormalOutfilTest*>(outfilData.get());

    char buffer[bufferSize];
    std::string inputFile = "./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF_error_5";
    FILE *gg = fopen(inputFile.c_str(), "r");

    EXPECT_EXIT(normalOutfilTest->callReadInputImpl(buffer, gg, &(inputFile)), ::testing::ExitedWithCode(255), ".*");
}

TEST(readInputImpl, normal_count_7){
    std::unique_ptr <OutfilData> outfilData(new NormalOutfilTest());
    NormalOutfilTest *normalOutfilTest = dynamic_cast<NormalOutfilTest*>(outfilData.get());

    char buffer[bufferSize];
    std::string inputFile = "./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF_error_7";
    FILE *gg = fopen(inputFile.c_str(), "r");

    EXPECT_EXIT(normalOutfilTest->callReadInputImpl(buffer, gg, &(inputFile)), ::testing::ExitedWithCode(255), ".*");
}

TEST(readInputImpl, normal_error_agr){
    std::unique_ptr <OutfilData> outfilData(new NormalOutfilTest());
    NormalOutfilTest *normalOutfilTest = dynamic_cast<NormalOutfilTest*>(outfilData.get());

    char buffer[bufferSize];
    std::string inputFile = "./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF_error";
    FILE *gg = fopen(inputFile.c_str(), "r");

    EXPECT_EXIT(normalOutfilTest->callReadInputImpl(buffer, gg, &(inputFile)), ::testing::ExitedWithCode(255), ".*");
}

TEST(readSecondLine, normal_no_file){
    std::unique_ptr <OutfilData> outfilData(new NormalOutfilTest());
    NormalOutfilTest *normalOutfilTest = dynamic_cast<NormalOutfilTest*>(outfilData.get());

    char buffer[bufferSize];
    std::string inputFile = "sdsfd";
    FILE *gg = NULL;

    EXPECT_EXIT(normalOutfilTest->callReadSecondLine(buffer, &(inputFile), gg), ::testing::ExitedWithCode(255), ".*");
}

TEST(readSecondLine, normal_sccanf_5){
    std::unique_ptr <OutfilData> outfilData(new NormalOutfilTest());
    NormalOutfilTest *normalOutfilTest = dynamic_cast<NormalOutfilTest*>(outfilData.get());

    char buffer[bufferSize];
    std::string inputFile = "./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF_error_5s";
    FILE *gg = fopen(inputFile.c_str(), "r");

    EXPECT_EXIT(normalOutfilTest->callReadSecondLine(buffer, &(inputFile), gg), ::testing::ExitedWithCode(255), ".*");
}

TEST(readSecondLine, normal_sscanf_7){
    std::unique_ptr <OutfilData> outfilData(new NormalOutfilTest());
    NormalOutfilTest *normalOutfilTest = dynamic_cast<NormalOutfilTest*>(outfilData.get());

    char buffer[bufferSize];
    std::string inputFile = "./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF_error_7s";
    FILE *gg = fopen(inputFile.c_str(), "r");

    EXPECT_EXIT(normalOutfilTest->callReadSecondLine(buffer, &(inputFile), gg), ::testing::ExitedWithCode(255), ".*");
}

TEST(readSecondLine, normal_sscanf_error_agr){
    std::unique_ptr <OutfilData> outfilData(new NormalOutfilTest());
    NormalOutfilTest *normalOutfilTest = dynamic_cast<NormalOutfilTest*>(outfilData.get());

    char buffer[bufferSize];
    std::string inputFile = "./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF_error_agrS";
    FILE *gg = fopen(inputFile.c_str(), "r");

    EXPECT_EXIT(normalOutfilTest->callReadSecondLine(buffer, &(inputFile), gg), ::testing::ExitedWithCode(255), ".*");
}

TEST(setRigidityStep, normal){
    std::unique_ptr <OutfilData> outfilData(new NormalOutfilTest());
    NormalOutfilTest *normalOutfilTest = dynamic_cast<NormalOutfilTest*>(outfilData.get());

    normalOutfilTest->callSetRigidityStep(-0.1);

    EXPECT_FLOAT_EQ(normalOutfilTest->rigidityData.rigidityStep, 0.1);
}

TEST(setRigidityStep, normal_null){
    std::unique_ptr <OutfilData> outfilData(new NormalOutfilTest());
    NormalOutfilTest *normalOutfilTest = dynamic_cast<NormalOutfilTest*>(outfilData.get());

    normalOutfilTest->callSetRigidityStep(NULL);

    EXPECT_FLOAT_EQ(normalOutfilTest->rigidityData.rigidityStep, 0.1);
}

TEST(version, error){
    std::unique_ptr <OutfilData> outfilData(new NormalOutfilTest());
    NormalOutfilTest *normalOutfilTest = dynamic_cast<NormalOutfilTest*>(outfilData.get());

    normalOutfilTest->version = (Version) -1;

    EXPECT_EQ(normalOutfilTest->version, NULL);
}

TEST(readInputImpl_mag, file){
    std::unique_ptr <OutfilData> outfilData(new MagFieldOutfilTest());
    MagFieldOutfilTest *magFieldOutfilTest = dynamic_cast<MagFieldOutfilTest*>(outfilData.get());

    char buffer[bufferSize];
    std::string inputFile = "./tst/InfilGenerator/correctInput/mag.dat0_T05";
    FILE *gg = fopen(inputFile.c_str(), "r");

    EXPECT_NO_THROW(magFieldOutfilTest->readInputImpl(buffer, gg, &(inputFile)));

    fclose(gg);
}

TEST(readInputImpl_mag, fgets){
    std::unique_ptr <OutfilData> outfilData(new MagFieldOutfilTest());
    MagFieldOutfilTest *magFieldOutfilTest = dynamic_cast<MagFieldOutfilTest*>(outfilData.get());

    char buffer[bufferSize];
    std::string inputFile = "./tst/InfilGenerator/correctInput/mag.dat0_T05";
    FILE *gg = NULL;

    EXPECT_EXIT(magFieldOutfilTest->readInputImpl(buffer, gg, &(inputFile)), ::testing::ExitedWithCode(255), ".*");
}

TEST(readInputImpl_mag, sscanf_m12){
    std::unique_ptr <OutfilData> outfilData(new MagFieldOutfilTest());
    MagFieldOutfilTest *magFieldOutfilTest = dynamic_cast<MagFieldOutfilTest*>(outfilData.get());

    char buffer[bufferSize];
    std::string inputFile = "./tst/InfilGenerator/correctInput/mag.dat0_T05_m12";
    FILE *gg = fopen(inputFile.c_str(), "r");

    EXPECT_EXIT(magFieldOutfilTest->readInputImpl(buffer, gg, &inputFile), ::testing::ExitedWithCode(255), ".*");
}

// TEST(readInputImpl_mag, sscanf_s){
//     std::unique_ptr <OutfilData> outfilData(new MagFieldOutfilTest());
//     MagFieldOutfilTest *magFieldOutfilTest = dynamic_cast<MagFieldOutfilTest*>(outfilData.get());

//     char buffer[bufferSize];
//     std::string inputFile = "./tst/InfilGenerator/correctInput/mag.dat0_T05_s";
//     FILE *gg = fopen(inputFile.c_str(), "r");

//     EXPECT_EXIT(magFieldOutfilTest->readInputImpl(buffer, gg, &inputFile), ::testing::ExitedWithCode(255), ".*");
// }

TEST(readInputImpl_mag, sscanf_v12){
    std::unique_ptr <OutfilData> outfilData(new MagFieldOutfilTest());
    MagFieldOutfilTest *magFieldOutfilTest = dynamic_cast<MagFieldOutfilTest*>(outfilData.get());

    char buffer[bufferSize];
    std::string inputFile = "./tst/InfilGenerator/correctInput/mag.dat0_T05_v12";
    FILE *gg = fopen(inputFile.c_str(), "r");

    EXPECT_EXIT(magFieldOutfilTest->readInputImpl(buffer, gg, &inputFile), ::testing::ExitedWithCode(255), ".*");
}

TEST(readInputImpl_trajectory, normal_no_file){
    std::unique_ptr <OutfilData> outfilData(new TrajectoryOutfilTest());
    TrajectoryOutfilTest *trajectoryOutfilTest = dynamic_cast<TrajectoryOutfilTest*>(outfilData.get());

    char buffer[bufferSize];
    std::string inputFile = "sasddas";
    FILE *gg = NULL;

    EXPECT_EXIT(trajectoryOutfilTest->readInputImpl(buffer, gg, &(inputFile)), ::testing::ExitedWithCode(255), ".*");
}

TEST(readInputImpl_trajectory, normal_file){
    std::unique_ptr <OutfilData> outfilData(new TrajectoryOutfilTest());
    TrajectoryOutfilTest *trajectoryOutfilTest = dynamic_cast<TrajectoryOutfilTest*>(outfilData.get());

    char buffer[bufferSize];
    std::string inputFile = "./tst/InfilGenerator/correctInput/trajectory.dat0_IGRF";
    FILE *gg = fopen(inputFile.c_str(), "r");

    EXPECT_NO_THROW(trajectoryOutfilTest->readInputImpl(buffer, gg, &(inputFile)));

    fclose(gg);
}

TEST(readInputImpl_trajectory, normal_count_8){
    std::unique_ptr <OutfilData> outfilData(new TrajectoryOutfilTest());
    TrajectoryOutfilTest *trajectoryOutfilTest = dynamic_cast<TrajectoryOutfilTest*>(outfilData.get());

    char buffer[bufferSize];
    std::string inputFile = "./tst/InfilGenerator/correctInput/trajectory.dat0_IGRF_errro_8";
    FILE *gg = fopen(inputFile.c_str(), "r");

    EXPECT_EXIT(trajectoryOutfilTest->readInputImpl(buffer, gg, &(inputFile)), ::testing::ExitedWithCode(255), ".*");
}

TEST(readInputImpl_trajectory, normal_count_10){
    std::unique_ptr <OutfilData> outfilData(new TrajectoryOutfilTest());
    TrajectoryOutfilTest *trajectoryOutfilTest = dynamic_cast<TrajectoryOutfilTest*>(outfilData.get());

    char buffer[bufferSize];
    std::string inputFile = "./tst/InfilGenerator/correctInput/trajectory.dat0_IGRF_errro_10";
    FILE *gg = fopen(inputFile.c_str(), "r");

    EXPECT_EXIT(trajectoryOutfilTest->readInputImpl(buffer, gg, &(inputFile)), ::testing::ExitedWithCode(255), ".*");
}

TEST(version_test_1, version){
    int inVersion = 0;

    Version version;
    
    version = (Version) inVersion;

    EXPECT_EQ(version, Version::T96);
}

TEST(version_test_1, version_1){
    int inVersion = 9;

    Version version;

    version = (Version) inVersion;

    EXPECT_EQ(version, NULL);
}