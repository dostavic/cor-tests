#include <gtest/gtest.h>
#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include <tgmath.h>
#include <stdio.h>
#include <cstdio>

#include "structs.hpp"
#include "SpectrumLoader.hpp"
#include "DataVectors.hpp"

TEST(struct_DataVerctors, test_intialization){
    int argc = 4;
    char* argv[] = {
		(char*)"./AmsP",
		(char*)"./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"null"
	};
    StaticData consts(argc, argv);
    InputPhysicalData inputPhysicalData(&consts);

    DataVectors dVectors(&inputPhysicalData);

    // ipd.sd.yearDoy.rigidityStep * 10
    // ipd.sd.numberOfDirections
    // ipd.sd.yearDoy.rigidityStep
    // 100 - maxRigidity
    
    EXPECT_EQ(dVectors.ipd->sd->yearDoy.rigidityStep, 0.01);
    EXPECT_EQ(dVectors.ipd->variableBinWidth, 0.0);
}

TEST(struct_DataVerctors, test_initialization_1){
    int argc = 4;
    char* argv[] = {
		(char*)"./AmsP",
		(char*)"./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"null"
	};
    StaticData consts(argc, argv);
    InputPhysicalData inputPhysicalData(&consts);

    DataVectors dVectors(&inputPhysicalData);

    EXPECT_EQ(dVectors.matrix.size(), dVectors.ipd->sd->numberOfDirections);
    EXPECT_EQ(dVectors.outfilData.size(), dVectors.ipd->sd->numberOfDirections);
    
    for(int i = 0; i < dVectors.ipd->sd->numberOfDirections; i++){
        for(int j = 0; j < 256; j++)
            EXPECT_EQ(dVectors.buffer[i][j], '\0');
    }

    EXPECT_EQ(dVectors.bandVector.size(), dVectors.ipd->sd->numberOfDirections);
    EXPECT_EQ(dVectors.integr1O.size(), dVectors.ipd->sd->numberOfDirections);
    
    for(int i = 0; i < 72; i++){
        for(int j = 0; j < 72; j++){
            EXPECT_EQ(dVectors.mapaasym[i][j], 0);
            EXPECT_EQ(dVectors.mapaend[i][j], 0);
        }
    }
}

TEST(struct_DataVectors_function, test_readOutfil){
    int argc = 4;
    
    char* argv[] = {
		(char*)"./AmsP",
		(char*)"./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"null"
	};
    StaticData consts(argc, argv);
    InputPhysicalData inputPhysicalData(&consts);

    DataVectors dVectors(&inputPhysicalData);
    
    EXPECT_EXIT(dVectors.readOufil(1), ::testing::ExitedWithCode(255), ".*");
}

TEST(struct_DataVectors_function, test_readOutfil_1){
    int argc = 4;
    
    char* argv[] = {
		(char*)"./AmsP",
		(char*)"./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0_11lines/",
		(char*)"1",
		(char*)"null"
	};
    StaticData consts(argc, argv);
    InputPhysicalData inputPhysicalData(&consts);

    DataVectors dVectors(&inputPhysicalData);
    
    EXPECT_EXIT(dVectors.readOufil(0), ::testing::ExitedWithCode(255), ".*");
}

TEST(struct_DataVectors_function, test_readOutfil_2){
    int argc = 4;
    
    char* argv[] = {
		(char*)"./AmsP",
		(char*)"./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0_256/",
		(char*)"1",
		(char*)"null"
	};
    StaticData consts(argc, argv);
    InputPhysicalData inputPhysicalData(&consts);

    DataVectors dVectors(&inputPhysicalData);
    
    EXPECT_EXIT(dVectors.readOufil(0), ::testing::ExitedWithCode(255), ".*");
}

TEST(struct_DataVectors_function, test_processData){
    int argc = 4;
    
    char* argv[] = {
		(char*)"./AmsP",
		(char*)"./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"null"
	};
    StaticData consts(argc, argv);
    InputPhysicalData inputPhysicalData(&consts);

    DataVectors dVectors(&inputPhysicalData);
    dVectors.readOufil(0);
    dVectors.processData(0);

    EXPECT_EQ(dVectors.bandVector[0][0].start, 5.18);
    EXPECT_EQ(dVectors.bandVector[0][0].bandWidth, 0.01);

    EXPECT_EQ(dVectors.bandVector[0][1].start, 5.26);
    EXPECT_FLOAT_EQ(dVectors.bandVector[0][1].bandWidth, 0.01);

    // dVectors.readOufil(0);
    // dVectors.processData(1);

    // EXPECT_EQ(dVectors.bandVector[0][1].start, 5.26);
    // EXPECT_EQ(dVectors.bandVector[0][1].bandWidth, 0.01);

    // dVectors.readOufil(2);
    // dVectors.processData(2);

    // EXPECT_EQ(dVectors.bandVector[0][2].start, 0);
    // EXPECT_EQ(dVectors.bandVector[0][2].bandWidth, 0);
}

TEST(struct_DataVectors_function, test_createMaps){
    int argc = 4;
    
    char* argv[] = {
		(char*)"./AmsP",
		(char*)"./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"null"
	};
    StaticData consts(argc, argv);
    InputPhysicalData inputPhysicalData(&consts);

    DataVectors dVectors(&inputPhysicalData);
    dVectors.readOufil(0);
    dVectors.processData(0);

    dVectors.matrix.at(0).at(0).ilatasym = -1;
    dVectors.createMaps();

    for(int i = 0; i < dVectors.matrix.size(); i++){
        for(int j = 0; j < dVectors.matrix.at(i).size(); j++){
            EXPECT_GE(dVectors.mapaasym[i][j], 0);
            EXPECT_GE(dVectors.mapaend[i][j], 0);
        }
    }
}

TEST(struct_DataVectors_function, test_writeCAY_ff){
    int argc = 4;
    
    char* argv[] = {
		(char*)"./AmsP",
		(char*)"./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"null"
	};
    StaticData consts(argc, argv);
    InputPhysicalData inputPhysicalData(&consts);

    DataVectors dVectors(&inputPhysicalData);
    dVectors.readOufil(0);
    dVectors.processData(0);

    dVectors.createMaps();
    dVectors.writeCAY(inputPhysicalData.lat);

    FILE *f = fopen("./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/cut_off_rig.dat", "r");

    EXPECT_NE(f, nullptr);

    float one;
    int two;
    float three;
    float four;
    float five;

    int res = fscanf(f, "%f %d %f %f %f\n", &one, &two, &three, &four, &five);
    fclose(f);

    EXPECT_EQ(res, 5);
    EXPECT_EQ(one, 0);
    EXPECT_EQ(two, 0);
    EXPECT_FLOAT_EQ(three, 5.18);
    EXPECT_FLOAT_EQ(four, 6.08);
    EXPECT_FLOAT_EQ(five, 5.84);
}

TEST(struct_DataVectors_function, test_writeCAY_dd){
    int argc = 4;
    
    char* argv[] = {
		(char*)"./AmsP",
		(char*)"./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"null"
	};
    StaticData consts(argc, argv);
    InputPhysicalData inputPhysicalData(&consts);

    DataVectors dVectors(&inputPhysicalData);
    dVectors.readOufil(0);
    dVectors.processData(0);

    dVectors.createMaps();
    dVectors.writeCAY(inputPhysicalData.lat);

    FILE *d = fopen("./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/intensity_yield.dat", "r");

    EXPECT_NE(d, nullptr);

    int one;
    int two;
    float three;

    int res = fscanf(d, "%d %d %f\n", &one, &two, &three);
    fclose(d);

    EXPECT_EQ(one, 0);
    EXPECT_EQ(two, 0);
    EXPECT_FLOAT_EQ(three, 373.022212);
}

TEST(struct_DataVectors_function, test_writeMaps){
    int argc = 4;
    
    char* argv[] = {
		(char*)"./AmsP",
		(char*)"./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"null"
	};
    StaticData consts(argc, argv);
    InputPhysicalData inputPhysicalData(&consts);

    DataVectors dVectors(&inputPhysicalData);
    dVectors.readOufil(0);
    dVectors.processData(0);

    dVectors.createMaps();
    dVectors.writeCAY(inputPhysicalData.lat);
    dVectors.writeMaps();

    FILE *g = fopen("./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/mapa_over_atm_4x.dat", "r");

    EXPECT_NE(g, nullptr);

    float one, two, three, four;

    for(int i = 1; i <= 72; i++){
        for(int j = 1; j <= 72; j++){
            int res = fscanf(g, "%f %f %f %f\n", &one, &two, &three, &four);
            EXPECT_EQ(res, 4);

            float one_1 = i * 2.5 - 90;
            float two_1 = (j - 1) * 5;
            float three_1 = dVectors.mapaend[i - 1][j - 1];
            float four_1 = dVectors.mapaasym[i - 1][j - 1];

            EXPECT_FLOAT_EQ(one, one_1);
            EXPECT_FLOAT_EQ(two, two_1);
            EXPECT_FLOAT_EQ(three, three_1);
            EXPECT_FLOAT_EQ(four, four_1);
        }
    }
    fclose(g);
}

TEST(struct_DataVectors_function, test_writeSpectraBands){
    int argc = 4;
    
    char* argv[] = {
		(char*)"./AmsP",
		(char*)"./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"null"
	};
    StaticData consts(argc, argv);
    InputPhysicalData inputPhysicalData(&consts);

    DataVectors dVectors(&inputPhysicalData);
    dVectors.readOufil(0);
    dVectors.processData(0);

    dVectors.createMaps();
    dVectors.writeCAY(inputPhysicalData.lat);
    dVectors.writeMaps();
    dVectors.writeSpectraBands();

    FILE *z = fopen("./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/spectraBands", "r");

    EXPECT_NE(z, nullptr);

    float one, two;

    for(int i = 0; i < dVectors.bandVector.size(); i++){
        for(int j = 0; j < dVectors.bandVector[i].size(); j++){
            int res = fscanf(z, "%f %f ", &one, &two);

            EXPECT_EQ(res, 2);
            EXPECT_FLOAT_EQ(one, dVectors.bandVector[i][j].start);
            EXPECT_FLOAT_EQ(two, dVectors.bandVector[i][j].bandWidth);
        }
    }
    fclose(z);
}

TEST(struct_DataVectors_function, test_writeIntegr2sum){
    int argc = 4;
    
    char* argv[] = {
		(char*)"./AmsP",
		(char*)"./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"null"
	};
    StaticData consts(argc, argv);
    InputPhysicalData inputPhysicalData(&consts);

    DataVectors dVectors(&inputPhysicalData);
    dVectors.readOufil(0);
    dVectors.processData(0);

    dVectors.createMaps();
    // dVectors.writeCAY(inputPhysicalData.lat);
    // dVectors.writeMaps();
    // dVectors.writeSpectraBands();
    dVectors.writeIntegr2sum();

    FILE *z = fopen("./tst/Asmp/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/integr2sum", "r");

    EXPECT_NE(z, nullptr);

    float one;

    int res = fscanf(z, "%f\n", &one);
    fclose(z);

    EXPECT_EQ(res, 1);
    EXPECT_FLOAT_EQ(one, dVectors.integr1O[0]);
}