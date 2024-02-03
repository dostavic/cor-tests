// #include "gtest/gtest.h"
// #include "gmock/gmock.h"
// #include <chrono>
// #include <string>
// #include <fstream>
// #include <iostream>
// #include "infilGenerator.hpp"
// #include "OutfilData.hpp"

// TEST(write_test, normal_IGRF){
//     Arguments arguments;
//     std::unique_ptr<OutfilData> outfilData;

//     int argc = 3;
//     char *argv[] = {
//         (char*)"./InfilGenerator",
//         (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF",
//         (char*)"./tst/InfilGenerator/outfill/filenamePrefix"
//     };

//     arguments.parseArguments(argc, argv);
//     outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
//     NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());
//     outfilData->readInput(&(arguments.inputFile));
//     outfilData->writeData(&(arguments.filenamePrefix), 0);

//     FILE *f = fopen("./tst/InfilGenerator/outfill/filenamePrefix_0", "r");
//     EXPECT_NE(f, nullptr);

//     float one, two, three;
//     int one_0, two_0, three_0, four_0, five_0;

//     int res = fscanf(f, "%f -1. %f\n", &one, &two);
//     EXPECT_EQ(res, 2);
//     EXPECT_FLOAT_EQ(one, 5.9);
//     EXPECT_FLOAT_EQ(two, 14.75);

//     res = fscanf(f, "%f %f %f\n", &one, &two, &three);
//     EXPECT_EQ(res, 3);
//     EXPECT_FLOAT_EQ(one, 1.0);
//     EXPECT_FLOAT_EQ(two, -42);
//     EXPECT_FLOAT_EQ(three, 270);

//     res = fscanf(f, "%f %f\n", &one, &two);
//     EXPECT_EQ(res, 2);
//     EXPECT_FLOAT_EQ(one, -42);
//     EXPECT_FLOAT_EQ(two, 270);

//     res = fscanf(f, "%d %d %d %d %d 00 00\n", &one_0, &two_0, &three_0, &four_0, &five_0);
//     EXPECT_FLOAT_EQ(res, 5);
//     EXPECT_FLOAT_EQ(one_0, 2010);
//     EXPECT_FLOAT_EQ(two_0, 1);
//     EXPECT_FLOAT_EQ(three_0, 1);
//     EXPECT_FLOAT_EQ(four_0, 1);
//     EXPECT_FLOAT_EQ(five_0, 0);
// }

// TEST(write_test, normal_IGRF_date){
//     Arguments arguments;
//     std::unique_ptr<OutfilData> outfilData;

//     int argc = 3;
//     char *argv[] = {
//         (char*)"./InfilGenerator",
//         (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF_1",
//         (char*)"./tst/InfilGenerator/outfill/filenamePrefix_1"
//     };

//     arguments.parseArguments(argc, argv);
//     outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
//     NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());
//     outfilData->readInput(&(arguments.inputFile));
//     outfilData->writeData(&(arguments.filenamePrefix), 0);

//     FILE *f = fopen("./tst/InfilGenerator/outfill/filenamePrefix_1_0", "r");
//     EXPECT_NE(f, nullptr);

//     float one, two, three;
//     int one_0, two_0, three_0, four_0, five_0;

//     int res = fscanf(f, "%f -1. %f\n", &one, &two);
//     EXPECT_EQ(res, 2);
//     EXPECT_FLOAT_EQ(one, 5.9);
//     EXPECT_FLOAT_EQ(two, 14.75);

//     res = fscanf(f, "%f %f %f\n", &one, &two, &three);
//     EXPECT_EQ(res, 3);
//     EXPECT_FLOAT_EQ(one, 1.0);
//     EXPECT_FLOAT_EQ(two, -42);
//     EXPECT_FLOAT_EQ(three, 270);

//     res = fscanf(f, "%f %f\n", &one, &two);
//     EXPECT_EQ(res, 2);
//     EXPECT_FLOAT_EQ(one, -42);
//     EXPECT_FLOAT_EQ(two, 270);

//     res = fscanf(f, "%d %d %d %d %d 00 00\n", &one_0, &two_0, &three_0, &four_0, &five_0);
//     EXPECT_FLOAT_EQ(res, 5);
//     EXPECT_FLOAT_EQ(one_0, 2010);
//     EXPECT_FLOAT_EQ(two_0, 6);
//     EXPECT_FLOAT_EQ(three_0, 30);
//     EXPECT_FLOAT_EQ(four_0, 181);
//     EXPECT_FLOAT_EQ(five_0, 12);
// }