// #include "gtest/gtest.h"
// #include "gmock/gmock.h"
// #include <chrono>
// #include <string>
// #include <fstream>
// #include <iostream>
// #include "infilGenerator.hpp"

// class OutfilDataMock : public OutfilData{
//     public:
//         MOCK_METHOD2(writeDataMock, void(std::string *filenamePrefix, int index));
//         MOCK_METHOD3(readInputImpl, void(char *buffer, FILE *gg, std::string *inputFile));

//         void writeData(std::string *filenamePrefix, int index) override {}
// };

// TEST(infil_test, fillArrays_test){
// 	float lat[16];

//     fillArrays(lat);

//     EXPECT_FLOAT_EQ(lat[0], 75.638488);
//     EXPECT_FLOAT_EQ(lat[1], 64.992167);
//     EXPECT_FLOAT_EQ(lat[2], 57.538255);
//     EXPECT_FLOAT_EQ(lat[3], 51.375167);
//     EXPECT_FLOAT_EQ(lat[4], 45.951374);
//     EXPECT_FLOAT_EQ(lat[5], 41.0145);
//     EXPECT_FLOAT_EQ(lat[6], 36.423574);
//     EXPECT_FLOAT_EQ(lat[7], 32.089951);
//     EXPECT_FLOAT_EQ(lat[8], 27.953187);
//     EXPECT_FLOAT_EQ(lat[9], 23.969482);
//     EXPECT_FLOAT_EQ(lat[10], 20.10551);
//     EXPECT_FLOAT_EQ(lat[11], 16.334823);
//     EXPECT_FLOAT_EQ(lat[12], 12.635625);
//     EXPECT_FLOAT_EQ(lat[13], 8.989299);
//     EXPECT_FLOAT_EQ(lat[14], 5.379379);
//     EXPECT_FLOAT_EQ(lat[15], 1.790785);
// }

// TEST(infil_test, OutfilData_test){
//     OutfilDataMock data;

//     EXPECT_EQ(data.generateInfils, true);
// }

// TEST(infil_test, parseArguments_test){
//     Arguments arguments;

//     int argc = 2;
//     char* argv[2];

//     EXPECT_EXIT(arguments.parseArguments(argc, argv), ::testing::ExitedWithCode(1), ".*");
// }

// TEST(infil_test, parseArguments_test_1){
//     Arguments arguments;

//     int argc = 3;
//     char* argv[] = {
//         (char*)"./InfilGenerator",
//         (char*)"inputFile",
//         (char*)"filenamePrefix"
//     };

//     arguments.parseArguments(argc, argv);

//     EXPECT_EQ(arguments.inputFile, "inputFile");
//     EXPECT_EQ(arguments.filenamePrefix, "filenamePrefix");
//     EXPECT_EQ(arguments.infilKind, 0);
// }

// TEST(infil_test, parseArguments_test_2){
//     Arguments arguments;

//     int argc = 4;
//     char* argv[] = {
//         (char*)"./InfilGenerator",
//         (char*)"inputFile",
//         (char*)"filenamePrefix",
//         (char*)"sfaafs"
//     };

//     arguments.parseArguments(argc, argv);

//     EXPECT_EQ(arguments.inputFile, "inputFile");
//     EXPECT_EQ(arguments.filenamePrefix, "filenamePrefix");
//     EXPECT_EQ(arguments.infilKind, 0);
// }

// TEST(infil_test, parseArgments_test_3){
//     Arguments arguments;

//     int argc = 4;
//     char* argv[] = {
//         (char*)"./InfilGenerator",
//         (char*)"inputFile",
//         (char*)"filenamePrefix",
//         (char*)"trajectory"
//     };

//     arguments.parseArguments(argc, argv);

//     EXPECT_EQ(arguments.inputFile, "inputFile");
//     EXPECT_EQ(arguments.filenamePrefix, "filenamePrefix");
//     EXPECT_EQ(arguments.infilKind, 1);
// }

// TEST(infil_test, parseArgments_test_4){
//     Arguments arguments;

//     int argc = 4;
//     char* argv[] = {
//         (char*)"./InfilGenerator",
//         (char*)"inputFile",
//         (char*)"filenamePrefix",
//         (char*)"mag"
//     };

//     arguments.parseArguments(argc, argv);

//     EXPECT_EQ(arguments.inputFile, "inputFile");
//     EXPECT_EQ(arguments.filenamePrefix, "filenamePrefix");
//     EXPECT_EQ(arguments.infilKind, 2);
// }

// TEST(infil_test, newOutfilNormal){
//     Arguments arguments;
//     std::unique_ptr<OutfilData> outfilData;

//     int argc = 3;
//     char* argv[] = {
//         (char*)"./InfilGenerator",
//         (char*)"inputFile",
//         (char*)"filenamePrefix"
//     };

//     arguments.parseArguments(argc, argv);
//     outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());

//     NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());

//     EXPECT_EQ(normalOutfil->date, 0);
//     EXPECT_EQ(normalOutfil->magData.dst, 0);
//     EXPECT_EQ(normalOutfil->magData.pdyn, 2);
//     EXPECT_EQ(normalOutfil->magData.byimf, 0);
//     EXPECT_EQ(normalOutfil->magData.bzimf, 0);

//     uint8_t check = 1;

//     EXPECT_EQ(normalOutfil->tIndices.success, LineState::NOT_FOUND);
//     EXPECT_EQ(normalOutfil->tIndices.W1, 0);
//     EXPECT_EQ(normalOutfil->tIndices.W2, 0);
//     EXPECT_EQ(normalOutfil->tIndices.W3, 0);
//     EXPECT_EQ(normalOutfil->tIndices.W4, 0);
//     EXPECT_EQ(normalOutfil->tIndices.W5, 0);
//     EXPECT_EQ(normalOutfil->tIndices.W6, 0);
// }

// TEST(infil_test, newTrajectoryOutfil){
//     Arguments arguments;
//     std::unique_ptr<OutfilData> outfilData;

//     int argc = 4;
//     char* argv[] = {
//         (char*)"./InfilGenerator",
//         (char*)"inputFile",
//         (char*)"filenamePrefix",
//         (char*)"trajectory"
//     };

//     arguments.parseArguments(argc, argv);
//     outfilData = std::unique_ptr<OutfilData>(new TrajectoryOutfil());
//     TrajectoryOutfil *trajectoryOutfil = dynamic_cast<TrajectoryOutfil*>(outfilData.get());

//     EXPECT_EQ(trajectoryOutfil->date, 0);
//     EXPECT_EQ(trajectoryOutfil->magData.dst, 0);
//     EXPECT_EQ(trajectoryOutfil->magData.pdyn, 2);
//     EXPECT_EQ(trajectoryOutfil->magData.byimf, 0);
//     EXPECT_EQ(trajectoryOutfil->magData.bzimf, 0);

//     EXPECT_EQ(trajectoryOutfil->tIndices.success, LineState::NOT_FOUND);
//     EXPECT_EQ(trajectoryOutfil->tIndices.W1, 0);
//     EXPECT_EQ(trajectoryOutfil->tIndices.W2, 0);
//     EXPECT_EQ(trajectoryOutfil->tIndices.W3, 0);
//     EXPECT_EQ(trajectoryOutfil->tIndices.W4, 0);
//     EXPECT_EQ(trajectoryOutfil->tIndices.W5, 0);
//     EXPECT_EQ(trajectoryOutfil->tIndices.W6, 0);
// }

// TEST(infil_test, newMagFieldOutfil){
//     Arguments arguments;
//     std::unique_ptr<OutfilData> outfilData;

//     int argc = 4;
//     char *argv[] = {
//         (char*)"./InfilGenerator",
//         (char*)"inputFile",
//         (char*)"filenamePrefix",
//         (char*)"mag"
//     };

//     arguments.parseArguments(argc, argv);
//     outfilData = std::unique_ptr<OutfilData>(new MagFieldOutfil());
//     MagFieldOutfil *magFieldOutfil = dynamic_cast<MagFieldOutfil*>(outfilData.get());

//     EXPECT_EQ(magFieldOutfil->date, 0);
//     EXPECT_EQ(magFieldOutfil->endDate, 0);
// }

// TEST(infil_test, readInput){
//     Arguments arguments;
//     std::unique_ptr<OutfilData> outfilData;

//     int argc = 3;
//     char *argv[] = {
//         (char*)"./InfilGenerator",
//         (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRFF",
//         (char*)"filenamePrefix",
//     };

//     arguments.parseArguments(argc, argv);
//     outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
//     NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());

//     // outfilData->readInput(&(arguments.inputFile));

//     EXPECT_EXIT(outfilData->readInput(&(arguments.inputFile)), ::testing::ExitedWithCode(4), ".*");
//     // EXPECT_EXIT(StaticData sd(argc, argv), ::testing::ExitedWithCode(255), ".*");
// }

// TEST(infil_test, readInputImpl){
//     Arguments arguments;
//     std::unique_ptr<OutfilData> outfilData;

//     int argc = 3;
//     char *argv[] = {
//         (char*)"./InfilGenerator",
//         (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF_null",
//         (char*)"filenamePrefix"
//     };

//     arguments.parseArguments(argc, argv);
//     outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
//     NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());

//     EXPECT_EXIT(outfilData->readInput(&(arguments.inputFile)), ::testing::ExitedWithCode(255), ".*");
// }

// TEST(infil_test, readInputImpl_sscanf){
//     Arguments arguments;
//     std::unique_ptr<OutfilData> outfilData;

//     int argc = 3;
//     char *argv[] = {
//         (char*)"./InfilGenerator",
//         (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF_add",
//         (char*)"filenamePrefix"
//     };

//     arguments.parseArguments(argc, argv);
//     outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
//     NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());
    
//     EXPECT_EXIT(outfilData->readInput(&(arguments.inputFile)), ::testing::ExitedWithCode(255), ".*");
// }

// TEST(infil_test, readInputImpl_sscanf_1){
//     Arguments arguments;
//     std::unique_ptr<OutfilData> outfilData;

//     int argc = 3;
//     char *argv[] = {
//         (char*)"./InfilGenerator",
//         (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF_minus",
//         (char*)"filenamePrefix"
//     };

//     arguments.parseArguments(argc, argv);
//     outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
//     NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());
    
//     EXPECT_EXIT(outfilData->readInput(&(arguments.inputFile)), ::testing::ExitedWithCode(255), ".*");
// }

// TEST(infil_test, readInputImpl_sscanf_2){
//     Arguments arguments;
//     std::unique_ptr<OutfilData> outfilData;

//     int argc = 3;
//     char *argv[] = {
//         (char*)"./InfilGenerator",
//         (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF_errorYear",
//         (char*)"filenamePrefix"
//     };

//     arguments.parseArguments(argc, argv);
//     outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
//     NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());
    
//     EXPECT_EXIT(outfilData->readInput(&(arguments.inputFile)), ::testing::ExitedWithCode(255), ".*");
// }

// TEST(infil_test, readInputImpl_sscanf_3){
//     Arguments arguments;
//     std::unique_ptr<OutfilData> outfilData;

//     int argc = 3;
//     char *argv[] = {
//         (char*)"./InfilGenerator",
//         (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF_errorDoy",
//         (char*)"filenamePrefix"
//     };

//     arguments.parseArguments(argc, argv);
//     outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
//     NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());
    
//     EXPECT_EXIT(outfilData->readInput(&(arguments.inputFile)), ::testing::ExitedWithCode(255), ".*");
// }

// TEST(infil_test, readInputImpl_sscanf_4){
//     Arguments arguments;
//     std::unique_ptr<OutfilData> outfilData;

//     int argc = 3;
//     char *argv[] = {
//         (char*)"./InfilGenerator",
//         (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF_errorHour",
//         (char*)"filenamePrefix"
//     };

//     arguments.parseArguments(argc, argv);
//     outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
//     NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());
    
//     EXPECT_EXIT(outfilData->readInput(&(arguments.inputFile)), ::testing::ExitedWithCode(255), ".*");
// }

// TEST(infil_test, readInputImpl_sscanf_5){
//     Arguments arguments;
//     std::unique_ptr<OutfilData> outfilData;

//     int argc = 3;
//     char *argv[] = {
//         (char*)"./InfilGenerator",
//         (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF_errorGeolat",
//         (char*)"filenamePrefix"
//     };

//     arguments.parseArguments(argc, argv);
//     outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
//     NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());
    
//     EXPECT_EXIT(outfilData->readInput(&(arguments.inputFile)), ::testing::ExitedWithCode(255), ".*");
// }

// TEST(infil_test, readInputImpl_1){
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

//     EXPECT_FLOAT_EQ(normalOutfil->geoLoc.geolat, -42);
//     EXPECT_FLOAT_EQ(normalOutfil->geoLoc.geolong, 270);
//     EXPECT_FLOAT_EQ(normalOutfil->geoLoc.radius, 1);
// }