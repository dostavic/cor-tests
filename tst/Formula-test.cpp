#include "gtest/gtest.h"
#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include "structs.hpp"

TEST(struct, test_argv_1){
	int argc = 1;
	char** argv;

	EXPECT_EXIT(StaticData sd(argc, argv), ::testing::ExitedWithCode(255), ".*");
}

TEST(struct, test_initialization){
	int argc = 4;
	char* argv[] = {
		(char*)"./AmsP",
		(char*)"./tst/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"null"
	};

	StaticData sd(argc, argv);

	EXPECT_EQ(sd.outputFolder, "./tst/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/");
	EXPECT_EQ(sd.numberOfDirections, 1);
	EXPECT_EQ(sd.postProcessingInput, "null");
}

TEST(struct, test_initialization_1){
	int argc = 4;
	char* argv[] = {
		(char*)"./AmsP",
		(char*)"./tst/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"sad",
		(char*)"null"
	};

	EXPECT_EXIT(StaticData sd(argc, argv), ::testing::ExitedWithCode(255), ".*");
}

TEST(struct, test_initialization_2){
	int argc = 4;
	char* argv[] = {
		(char*)"./AmsP",
		(char*)"./tst/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"null"
	};

	StaticData sd(argc, argv);

	argv[2] = (char*)"576";

	StaticData sd_1(argc, argv);

	EXPECT_EQ(sd.numberOfDirections, 1);
	EXPECT_EQ(sd_1.numberOfDirections, 577);
}

TEST(struct, test_initialization_3){
	int argc = 4;
	char* argv[] = {
		(char*)"./Amsp",
		(char*)"./tst/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"0",
		(char*)"null"
	};

	EXPECT_EXIT(StaticData sd(argc, argv), ::testing::ExitedWithCode(255), ".*");
}

TEST(struct, test_initialization_4){
	int argc = 4;
	char* argv[] = {
		(char*)"./Amsp",
		(char*)"./tst/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"null"
	};

	StaticData sd(argc, argv);

	EXPECT_EQ(sd.energyDivider, 1);
	EXPECT_EQ(sd.intensityDivider, 1);
	EXPECT_EQ(sd.variableBinWidth, 0.0);
}

TEST(struct, test_initialization_5){
	int argc = 4;
	char* argv[] = {
		(char*)"./Amsp",
		(char*)"./tst/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"null"
	};

	StaticData sd(argc, argv);
	
	EXPECT_EQ(sd.outfilPrefix, "./tst/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/");
	EXPECT_EQ(sd.cutOffRigPrefix, "./tst/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/cut_off_rig.dat");
	EXPECT_EQ(sd.intensityYieldPrefix, "./tst/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/intensity_yield.dat");
	EXPECT_EQ(sd.map, "./tst/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/mapa_over_atm_4x.dat");
	EXPECT_EQ(sd.integr2sum, "./tst/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/integr2sum");
	EXPECT_EQ(sd.spectraBands, "./tst/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/spectraBands");
	EXPECT_EQ(sd.outfil_0, "./tst/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/outfil_0");
	EXPECT_EQ(sd.throughputPath, "./tst/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/throughputs.dat");
}

TEST(struct, test_initialization_6){
	int argc = 4;
	char* argv[] = {
		(char*)"./Amsp",
		(char*)"./tst/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"./tst/PostProcessingSpectra/ForceField/"
	};

	StaticData sd(argc, argv);

	EXPECT_EQ(sd.mainFile, "datum_vs_Fi.dat");
	EXPECT_EQ(sd.variableBinWidth, 10.0);
	EXPECT_EQ(sd.rigEnergyFile, "./tst/PostProcessingSpectra/ForceField/rig_to_energy.dat");
	EXPECT_EQ(sd.energyDivider, 1);
	EXPECT_EQ(sd.intensityDivider, 1000);
	EXPECT_EQ(sd.dateRange, true);
}

TEST(struct, test_initialization_7){
	int argc = 4;
	char* argv[] = {
		(char*)"./Amsp",
		(char*)"./tst/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"./tst/PostProcessingSpectra_metadata/ForceField/"
	};

	EXPECT_EXIT(StaticData sd(argc, argv), ::testing::ExitedWithCode(255), ".*");
}

TEST(struct, test_initialization_8){
	int argc = 4;
	char* argv[] = {
		(char*)"./Amsp",
		(char*)"./tst/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"./tst/PostProcessingSpectra_main_file/ForceField/"
	};

	EXPECT_EXIT(StaticData sd(argc, argv), ::testing::ExitedWithCode(255), ".*");
}

TEST(struct, test_initialization_9){
	int argc = 4;
	char* argv[] = {
		(char*)"./Amsp",
		(char*)"./tst/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"./tst/PostProcessingSpectra_spectrm_range_scaling/ForceField/"
	};

	EXPECT_EXIT(StaticData sd(argc, argv), ::testing::ExitedWithCode(255), ".*");
}

TEST(struct, test_initialization_10){
	int argc = 4;
	char* argv[] = {
		(char*)"./Amsp",
		(char*)"./tst/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"./tst/PostProcessingSpectra_RigEnergyCorespondence/ForceField/"
	};

	EXPECT_EXIT(StaticData sd(argc, argv), ::testing::ExitedWithCode(255), ".*");
}

TEST(struct, test_initialization_11){
	int argc = 4;
	char* argv[] = {
		(char*)"./Amsp",
		(char*)"./tst/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"./tst/PostProcessingSpectra_energyDivider/ForceField/"
	};

	EXPECT_EXIT(StaticData sd(argc, argv), ::testing::ExitedWithCode(255), ".*");
}

TEST(struct, test_initialization_12){
	int argc = 4;
	char* argv[] = {
		(char*)"./Amsp",
		(char*)"./tst/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"./tst/PostProcessingSpectra_intensityDivider/ForceField/"
	};

	EXPECT_EXIT(StaticData sd(argc, argv), ::testing::ExitedWithCode(255), ".*");
}

TEST(struct, test_initialization_13){
	int argc = 4;
	char* argv[] = {
		(char*)"./Amsp",
		(char*)"./tst/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/",
		(char*)"1",
		(char*)"./tst/PostProcessingSpectra_dateRange/ForceField/"
	};

	EXPECT_EXIT(StaticData sd(argc, argv), ::testing::ExitedWithCode(255), ".*");
}

TEST(struct_1, test_initialization){
	std::string outfil_0 = "NULL";

	InputOutfilData yearDoy;

	EXPECT_EXIT(yearDoy.init(&outfil_0), ::testing::ExitedWithCode(0), ".*");
}

TEST(struct_1, test_initialization_1){
	std::string outfil_0 = "./tst/2003_326_23_41.90_12.47_1.00_1_0.01_1_0/outfil_0";

	InputOutfilData yearDoy;
	yearDoy.init(&outfil_0);

	EXPECT_EQ(yearDoy.year, 2003);
	EXPECT_EQ(yearDoy.doy, 326);
	EXPECT_EQ(yearDoy.daysInYear, 365);
	EXPECT_EQ(yearDoy.rigidityStep, 0.01);
}

TEST(struct_1, test_initialization_2){
	std::string outfil_0 = "./tst/test_outfil/outfil_0";

	InputOutfilData yearDoy;
	yearDoy.init(&outfil_0);

	EXPECT_EQ(yearDoy.year, 2012);
	EXPECT_EQ(yearDoy.doy, 73);
	EXPECT_EQ(yearDoy.daysInYear, 366);
	EXPECT_EQ(yearDoy.rigidityStep, 0.01);
}

TEST(struct_1, test_initialization_3){
	std::string outfil_0 = "./tst/test_outfil/outfil_01";

	InputOutfilData yearDoy;

	EXPECT_NO_THROW(yearDoy.init(&outfil_0));
	EXPECT_EQ("Day of month is not valid for year", yearDoy.get_exception_message());
}

TEST(struct_1, test_initialization_4){
	std::string outfil_0 = "./tst/test_outfil/outfil_0_year";

	InputOutfilData yearDoy;
	yearDoy.init(&outfil_0);
	// EXPECT_NO_THROW(yearDoy.init(&outfil_0));
	EXPECT_EQ("Year is out of valid range: 1400..9999", yearDoy.get_exception_message());
}

TEST(struct_1, test_initialization_5){
	std::string outfil_0 = "./tst/test_outfil/outfil_0__";

	InputOutfilData yearDoy;
	yearDoy.init(&outfil_0);
	// EXPECT_ANY_THROW(yearDoy.init(&outfil_0));
	EXPECT_EQ("Year is out of valid range: 1400..9999", yearDoy.get_exception_message());
}

TEST(struct_1, test_initialization_6){
	std::string outfil_0 = "./tst/test_outfil/outfil_0_none";

	InputOutfilData yearDoy;

	// EXPECT_EXIT(yearDoy.init(&outfil_0), ::testing::ExitedWithCode(255), ".*");
	EXPECT_EQ("Year is out of valid range: 1400..9999", yearDoy.get_exception_message());
}