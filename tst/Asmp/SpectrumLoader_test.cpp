#include "gtest/gtest.h"
#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include <tgmath.h> 

#include "structs.hpp"
#include "SpectrumLoader.hpp"

TEST(struct_InputPhysicalData, test_initiliazition){
    int argc = 4;
	char* argv[] = {
		(char*)"./AmsP",
		(char*)"./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"null"
	};
	StaticData consts(argc, argv);

    InputPhysicalData inputPhysicaldata(&consts);

    EXPECT_DOUBLE_EQ(inputPhysicaldata.rigStepOrig, 0.01);
    EXPECT_FLOAT_EQ(inputPhysicaldata.variableBinWidth, 0.0);
    EXPECT_EQ(inputPhysicaldata.usingAMS, true);
}

TEST(struct_InputPhysicalData, test_initiliazition_1){
    int argc = 4;
	char* argv[] = {
		(char*)"./AmsP",
		(char*)"./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"null"
	};
	StaticData consts(argc, argv);

    InputPhysicalData inputPhysicaldata(&consts);

    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[0], 0.92);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[1], 0.98);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[2], 1.09);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[3], 1.26);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[4], 1.39);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[5], 1.32);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[6], 1.14);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[7], 0.928);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[8], 0.724);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[9], 0.511);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[10], 0.37);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[11], 0.241);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[12], 0.163);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[13], 0.102);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[14], 0.0614);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[15], 0.039);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[16], 0.0223);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[17], 0.0136);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[18], 0.00762);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[19], 0.00396);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[20], 0.0022);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[21], 0.00118);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[22], 0.000767);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[23], 0.000477);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[24], 0.000285);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[25], 0.000154);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[26], 7.93E-5);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[27], 4.48E-5);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[28], 2.6E-5);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[29], 1.4E-5);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binI[30], 8.5E-6);

    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[0] ,0.085);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[1] ,0.125);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[2] ,0.185);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[3] ,0.265);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[4] ,0.375);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[5] ,0.53);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[6] ,0.735);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[7] ,1);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[8] ,1.345);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[9] ,1.78);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[10], 2.32);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[11], 3);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[12], 3.845);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[13], 4.88);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[14], 6.155);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[15], 7.73);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[16], 9.665);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[17], 12.035);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[18], 14.945);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[19], 18.515);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[20], 22.885);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[21], 28.245);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[22], 34.815);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[23], 42.865);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[24], 52.73);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[25], 64.82);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[26], 79.635);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[27], 97.785);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[28], 120.025);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[29], 147.28);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binE[30], 180.675);

    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[0], 0.07);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[1], 0.10);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[2], 0.15);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[3], 0.22);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[4], 0.31);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[5], 0.44);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[6], 0.62);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[7], 0.85);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[8], 1.15);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[9], 1.54);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[10], 2.02);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[11], 2.62);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[12], 3.38);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[13], 4.31);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[14], 5.45);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[15], 6.86);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[16], 8.60);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[17], 10.73);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[18], 13.34);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[19], 16.55);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[20], 20.48);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[21], 25.29);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[22], 31.20);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[23], 38.43);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[24], 47.30);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[25], 58.16);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[26], 71.48);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[27], 87.79);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[28], 107.78);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[29], 132.27);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[30], 162.29);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.binB[31], 199.06);

    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[0] ,0.03);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[1] ,0.05);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[2] ,0.07);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[3] ,0.09);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[4] ,0.13);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[5] ,0.18);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[6] ,0.23);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[7] ,0.3);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[8] ,0.39);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[9] ,0.48);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[10], 0.6);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[11], 0.76);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[12], 0.93);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[13], 1.14);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[14], 1.41);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[15], 1.74);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[16], 2.13);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[17], 2.61);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[18], 3.21);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[19], 3.93);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[20], 4.81);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[21], 5.91);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[22], 7.23);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[23], 8.87);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[24], 10.86);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[25], 13.32);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[26], 16.31);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[27], 19.99);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[28], 24.49);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[29], 30.02);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binw[30], 36.77);

    EXPECT_DOUBLE_EQ(inputPhysicaldata.lat[0], 14.361512);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.lat[1], 25.007833);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.lat[2], 32.461745);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.lat[3], 38.624833);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.lat[4], 44.048626);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.lat[5], 48.985500);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.lat[6], 53.576426);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.lat[7], 57.910049);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.lat[8], 62.046813);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.lat[9], 66.030518);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.lat[10], 69.894490);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.lat[11], 73.665177);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.lat[12], 77.364375);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.lat[13], 81.010701);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.lat[14], 84.620621);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.lat[15], 88.209215);

    EXPECT_DOUBLE_EQ(inputPhysicaldata.yield[0][0], 7.983E-1);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.yield[1][0], -6.985E-3);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.yield[2][0], 3.593E-6);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.yield[3][0], -1.950E-9);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.yield[0][1], 2.859E+0);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.yield[1][1], 1.188E-2);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.yield[2][1], -1.516E-5);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.yield[3][1], 7.969E-9);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.yield[0][2], -2.060E+0);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.yield[1][2], -9.264E-3);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.yield[2][2], 1.522E-5);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.yield[3][2], -8.508E-9);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.yield[0][3], 5.654E-1);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.yield[1][3], 2.169E-3);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.yield[2][3], -4.214E-6);
    EXPECT_DOUBLE_EQ(inputPhysicaldata.yield[3][3], 2.491E-9);
}    

TEST(struct_InputPhysicalData, test_initiliazition_2){
    int argc = 4;
	char* argv[] = {
		(char*)"./AmsP",
		(char*)"./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"./tst/Asmp/PostProcessingSpectra/ForceField/"
	};
	StaticData consts(argc, argv);

    InputPhysicalData inputPhysicaldata(&consts);

    EXPECT_DOUBLE_EQ(inputPhysicaldata.rigStepOrig, 0.01);
    EXPECT_FLOAT_EQ(inputPhysicaldata.variableBinWidth, 10);
    EXPECT_EQ(inputPhysicaldata.usingAMS, false);
}

TEST(struct_InputPhysicalData, test_initiliazition_3){
    int argc = 4;
	char* argv[] = {
		(char*)"./AmsP",
		(char*)"./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"null"
	};
	StaticData consts(argc, argv);

    InputPhysicalData inputPhysicaldata(&consts);

    EXPECT_EQ(inputPhysicaldata.sLoader.bestFn, "");
    EXPECT_EQ(inputPhysicaldata.sLoader.secondBestFn, "");
    EXPECT_FLOAT_EQ(inputPhysicaldata.sLoader.multiplier, 0.f);
}

TEST(struct_InputPhysicalData_true, test_initiliazition_parse){
    std::ifstream infile("./tst/Asmp/PostProcessingSpectra_parser/ForceField/datum_vs_Fi.dat");
    std::string line, filename;
    unsigned int year, percent;
    std::getline(infile, line);
    parseDataFromLine(&line, &filename, &year, &percent);

    EXPECT_EQ(year, 2016);
    EXPECT_EQ(percent, 95);

    std::getline(infile, line);

    // parseDataFromLine(&line, &filename, &year, &percent);
    // EXPECT_EQ(year, -788);
    // EXPECT_EXIT(parseDataFromLine(&line, &filename, &year, &percent);, ::testing::ExitedWithCode(255), ".*");
    // EXPECT_EXIT(parseDataFromLine(&line, &filename, &year, &percent);, ::testing::ExitedWithCode(255), ".*");
    // EXPECT_EXIT(parseDataFromLine(&line, &filename, &year, &percent);, ::testing::ExitedWithCode(255), ".*");
    // EXPECT_EXIT(parseDataFromLine(&line, &filename, &year, &percent);, ::testing::ExitedWithCode(255), ".*");
}

TEST(struct_InputPhysicalData_true, test_initiliazition_parse_1){
    std::ifstream infile("./tst/Asmp/PostProcessingSpectra_parser/ForceField/datum_vs_Fi.dat");
    std::string line, filename;
    unsigned int year, percent;
    std::getline(infile, line);
    // parseDataFromLine(&line, &filename, &year, &percent);

    // EXPECT_EQ(year, 2016);
    // EXPECT_EQ(percent, 95);

    std::getline(infile, line);

    // parseDataFromLine(&line, &filename, &year, &percent);
    // EXPECT_EQ(year, -788);
    EXPECT_EXIT(parseDataFromLine(&line, &filename, &year, &percent);, ::testing::ExitedWithCode(255), ".*");
    EXPECT_EXIT(parseDataFromLine(&line, &filename, &year, &percent);, ::testing::ExitedWithCode(255), ".*");
    EXPECT_EXIT(parseDataFromLine(&line, &filename, &year, &percent);, ::testing::ExitedWithCode(255), ".*");
    EXPECT_EXIT(parseDataFromLine(&line, &filename, &year, &percent);, ::testing::ExitedWithCode(255), ".*");
}

TEST(struct_InputPhysicalData_true, test_initialization_getName){
    int argc = 4;
	char* argv[] = {
		(char*)"./AmsP",
		(char*)"./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"./tst/Asmp/PostProcessingSpectra/ForceField/"
	};
	StaticData consts(argc, argv);

    InputPhysicalData inputPhysicaldata(&consts);

    // inputPhysicaldata.sLoader.getInputFileName();

    EXPECT_EQ(inputPhysicaldata.sLoader.bestFn, "./tst/Asmp/PostProcessingSpectra/ForceField/1026.dat");
    EXPECT_EQ(inputPhysicaldata.sLoader.secondBestFn, "./tst/Asmp/PostProcessingSpectra/ForceField/840.dat");
}

TEST(struct_InputPhysicalData_true, test_initialization_getName_1){
    int argc = 4;
	char* argv[] = {
		(char*)"./AmsP",
		(char*)"./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"./tst/Asmp/PostProcessingSpectra_meshap/ForceField/"
	};
	StaticData consts(argc, argv);

    InputPhysicalData inputPhysicaldata(&consts);

    // inputPhysicaldata.sLoader.getInputFileName();

    EXPECT_EQ(inputPhysicaldata.sLoader.bestFn, "./tst/Asmp/PostProcessingSpectra_meshap/ForceField/1026.dat");
    EXPECT_EQ(inputPhysicaldata.sLoader.secondBestFn, "./tst/Asmp/PostProcessingSpectra_meshap/ForceField/840.dat");
}

TEST(struct_InputPhysicalData_true, test_initialization_getName_2){
    int argc = 4;
	char* argv[] = {
		(char*)"./AmsP",
		(char*)"./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"./tst/Asmp/PostProcessingSpectra/HistoricalHigh/"
	};
	StaticData consts(argc, argv);

    InputPhysicalData inputPhysicaldata(&consts);

    // inputPhysicaldata.sLoader.getInputFileName();

    EXPECT_EQ(inputPhysicaldata.sLoader.bestFn, "./tst/Asmp/PostProcessingSpectra/HistoricalHigh/290.dat");
    EXPECT_EQ(inputPhysicaldata.sLoader.secondBestFn, "./tst/Asmp/PostProcessingSpectra/HistoricalHigh/.dat");
    EXPECT_FLOAT_EQ(inputPhysicaldata.sLoader.multiplier, 0);
}

TEST(struct_InputPhysicalData_true, test_initialization_multiplier){
    int argc = 4;
	char* argv[] = {
		(char*)"./AmsP",
		(char*)"./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"./tst/Asmp/PostProcessingSpectra/ForceField/"
	};
	StaticData consts(argc, argv);

    InputPhysicalData inputPhysicaldata(&consts);

    EXPECT_FLOAT_EQ(inputPhysicaldata.sLoader.multiplier, 0.25);
}

TEST(struct_InputPhysicalData_true, test_initialization_best){
    int argc = 4;
	char* argv[] = {
		(char*)"./AmsP",
		(char*)"./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"./tst/Asmp/PostProcessingSpectra_notBest/HistoricalHigh/"
	};
	StaticData consts(argc, argv);

    InputPhysicalData inputPhysicaldata(&consts);

    EXPECT_EQ("Not found bestFn", inputPhysicaldata.sLoader.get_exception_message());
}

TEST(struct_InputPhysicalData_true, test_initialization_best_1){
    int argc = 4;
	char* argv[] = {
		(char*)"./AmsP",
		(char*)"./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"./tst/Asmp/PostProcessingSpectra_bat_null/HistoricalHigh/"
	};
	StaticData consts(argc, argv);

    InputPhysicalData inputPhysicaldata(&consts);

    EXPECT_EQ("Not found bestFn", inputPhysicaldata.sLoader.get_exception_message());
}

TEST(struct_InputPhysicalData_bin, test_initialization_bin_mul_0_e){
    int argc = 4;
	char* argv[] = {
		(char*)"./AmsP",
		(char*)"./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"./tst/Asmp/PostProcessingSpectra/HistoricalHigh/"
	};
	StaticData consts(argc, argv);

    InputPhysicalData inputPhysicaldata(&consts);

    EXPECT_FLOAT_EQ(inputPhysicaldata.binE[0], 0.0053140);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binE[1], 0.0210792);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binE[700], 69.1680164);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binE[1098], 108.9657456);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binE[1099], 109.0657405);
}

TEST(struct_InputPhysicalData_bin, test_initialization_bin_mul_0_i){
    int argc = 4;
	char* argv[] = {
		(char*)"./AmsP",
		(char*)"./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"./tst/Asmp/PostProcessingSpectra/HistoricalHigh/"
	};
	StaticData consts(argc, argv);

    InputPhysicalData inputPhysicaldata(&consts);

    EXPECT_FLOAT_EQ(inputPhysicaldata.binI[0], 0.219595615);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binI[1], 0.795989649);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binI[646], 0.00016166082);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binI[1098], 0.0000368060129081961);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binI[1099], 0.000036712494450712);
}

TEST(struct_InputPhysicalData_bin, test_initialization_bin_mul_e){
    int argc = 4;
	char* argv[] = {
		(char*)"./AmsP",
		(char*)"./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"./tst/Asmp/PostProcessingSpectra/ForceField/"
	};
	StaticData consts(argc, argv);

    InputPhysicalData inputPhysicaldata(&consts);
    
    // std::cout << "[0]: " << inputPhysicaldata.binE[0] << "\n";

    EXPECT_FLOAT_EQ(inputPhysicaldata.binE[0], 0.005314);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binE[1], 0.0210792);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binE[552], 54.3696973);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binE[1098], 108.9657456);
    EXPECT_FLOAT_EQ(inputPhysicaldata.binE[1099], 109.0657405);
}

TEST(struct_InputPhysicalData_bin, test_initialization_bin_mul_i){
    int argc = 4;
	char* argv[] = {
		(char*)"./AmsP",
		(char*)"./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"./tst/Asmp/PostProcessingSpectra/ForceField/"
	};
	StaticData consts(argc, argv);

    InputPhysicalData inputPhysicaldata(&consts);

    EXPECT_EQ(round(inputPhysicaldata.binI[0] * 1000) / 1000, 0.013);
}