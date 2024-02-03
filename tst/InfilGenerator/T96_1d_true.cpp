#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "infilGenerator.hpp"
#include "OutfilData.hpp"

const int bufferSize = 1024;

class NormalOutfilTest : public NormalOutfil{
    public:
    void callReadInputImpl(char *buffer, FILE *gg, std::string* inputFile) {
        readInputImpl(buffer, gg, inputFile);
    }
    void callReadSecondLine(char *buffer, std::string *inputFile, FILE *gg) {
        readSecondLine(buffer, inputFile, gg);
    }
};

TEST(main_t96, parseArguments){
    Arguments arguments;
    int argc = 3;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_T96",
        (char*)"./tst/InfilGenerator/outfill/caspoloha_out.dat0_T96"
    };

    arguments.parseArguments(argc, argv);

    EXPECT_EQ(arguments.inputFile, "./tst/InfilGenerator/correctInput/caspoloha.dat0_T96");
    EXPECT_EQ(arguments.filenamePrefix, "./tst/InfilGenerator/outfill/caspoloha_out.dat0_T96");
    EXPECT_EQ(arguments.infilKind, InfilKind::NORMAL);
}

TEST(main_outfilData_t96, readInput){
    Arguments arguments;
    arguments.inputFile = "./tst/InfilGenerator/correctInput/caspoloha.dat0_T96";

    std::unique_ptr<OutfilData> outfilData;
    outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
    NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());

    EXPECT_NO_THROW(outfilData->readInput(&(arguments.inputFile)));
}

TEST(main_outfilData_t96, readInputImpl){
    std::unique_ptr <OutfilData> outfilData(new NormalOutfilTest());
    NormalOutfilTest *normalOutfilTest = dynamic_cast<NormalOutfilTest*>(outfilData.get());

    char buffer[bufferSize];
    std::string inputFile = "./tst/InfilGenerator/correctInput/caspoloha.dat0_T96";
    FILE *gg = fopen(inputFile.c_str(), "r");

    normalOutfilTest->callReadInputImpl(buffer, gg, &(inputFile));

    fclose(gg);

    EXPECT_EQ(normalOutfilTest->date.getYear(), 2010);
    EXPECT_EQ(normalOutfilTest->date.getDoy(), 1);
    EXPECT_EQ(normalOutfilTest->date.getHour(), 0);
    EXPECT_FLOAT_EQ(normalOutfilTest->geoLoc.geolat, -42);
    EXPECT_FLOAT_EQ(normalOutfilTest->geoLoc.geolong, 270);
    EXPECT_FLOAT_EQ(normalOutfilTest->geoLoc.radius, 1);
    EXPECT_FLOAT_EQ(normalOutfilTest->localLoc.latloc, -42);
    EXPECT_FLOAT_EQ(normalOutfilTest->localLoc.longloc, 270);
}

TEST(main_outfilData_t96, readSecondLine){
    std::unique_ptr <OutfilData> outfilData(new NormalOutfilTest());
    NormalOutfilTest *normalOutfilTest = dynamic_cast<NormalOutfilTest*>(outfilData.get());

    char buffer[bufferSize];
    std::string inputFile = "./tst/InfilGenerator/correctInput/caspoloha.dat0_T96_line_2";
    FILE *gg = fopen(inputFile.c_str(), "r");

    normalOutfilTest->callReadSecondLine(buffer, &(inputFile), gg);

    fclose(gg);

    EXPECT_EQ(outfilData->generateInfils, true);
    EXPECT_EQ(outfilData->inputState, 80);
    EXPECT_EQ(outfilData->version, Version::T96);
    EXPECT_EQ(outfilData->numberOfDirections, 1);
    EXPECT_FLOAT_EQ(normalOutfilTest->rigidityData.rigidityStep, 0.1);
    EXPECT_EQ(outfilData->optimalizationLevel, 2);
}

TEST(main_outfilData_t96, optimizeRigidity){
    std::unique_ptr <OutfilData> outfilData(new NormalOutfilTest());
    NormalOutfilTest *normalOutfilTest = dynamic_cast<NormalOutfilTest*>(outfilData.get());

    normalOutfilTest->geoLoc.geolat = -42;
    normalOutfilTest->geoLoc.geolong = 270;
    normalOutfilTest->geoLoc.radius = 1;
    normalOutfilTest->magData.dst = 0;

    optimizeRigidity(&(normalOutfilTest->geoLoc), &(normalOutfilTest->rigidityData), normalOutfilTest->magData.dst);

    EXPECT_FLOAT_EQ(normalOutfilTest->rigidityData.rigstart, 5.9);
    EXPECT_FLOAT_EQ(normalOutfilTest->rigidityData.rigend, 14.75);
}

TEST(main_infilGenerator_t96, readParmod){
    std::unique_ptr <OutfilData> outfilData(new NormalOutfilTest());
    NormalOutfilTest *normalOutfilTest = dynamic_cast<NormalOutfilTest*>(outfilData.get());
    TrajectoryOutfil *castData = dynamic_cast<TrajectoryOutfil*>(outfilData.get());

    int parmodError = 0;
    castData->date = Timestamp(2010, 1, 0);

    readParmod(&(castData->date), &(castData->magData), &parmodError);

    EXPECT_EQ(parmodError, 0);
    EXPECT_FLOAT_EQ(castData->magData.pdyn, 3.49);
    EXPECT_FLOAT_EQ(castData->magData.byimf, 0.1);
    EXPECT_FLOAT_EQ(castData->magData.bzimf, -1);
    EXPECT_FLOAT_EQ(castData->magData.dst, -20);
}

TEST(main_outfilData_t96, writeData){
    Arguments arguments;
    std::unique_ptr<OutfilData> outfilData;

    int argc = 3;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_T96",
        (char*)"./tst/InfilGenerator/outfill/caspoloha_out.dat0_T96"
    };

    arguments.parseArguments(argc, argv);
    outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
    NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());
    outfilData->readInput(&(arguments.inputFile));
    int parmodError  = 0;
    TrajectoryOutfil *castData = dynamic_cast<TrajectoryOutfil*>(outfilData.get());
    readParmod(&(castData->date), &(castData->magData), &parmodError);
    outfilData->writeData(&(arguments.filenamePrefix), 0);

    FILE *f = fopen("./tst/InfilGenerator/outfill/caspoloha_out.dat0_T96_0", "r");
    EXPECT_NE(f, nullptr);

    float rigstart, rigend;
    int res = fscanf(f, "%f -1. %f\n", &rigstart, &rigend);
    EXPECT_EQ(res, 2);
    EXPECT_FLOAT_EQ(rigstart, 5.9);
    EXPECT_FLOAT_EQ(rigend, 14.75);

    float radius, geolat, geolong;
    res = fscanf(f, "%f %f %f\n", &radius, &geolat, &geolong);
    EXPECT_EQ(res, 3);
    EXPECT_FLOAT_EQ(radius, 1);
    EXPECT_FLOAT_EQ(geolat, -42);
    EXPECT_FLOAT_EQ(geolong, 270);

    float latloc, longloc;
    res = fscanf(f, "%f %f\n", &latloc, &longloc);
    EXPECT_EQ(res, 2);
    EXPECT_FLOAT_EQ(latloc, -42);
    EXPECT_FLOAT_EQ(longloc, 270);

    int year, month, day, doy, hour;
    res = fscanf(f, "%d %d %d %d %d 00 00\n", &year, &month, &day, &doy, &hour);
    EXPECT_EQ(res, 5);
    EXPECT_EQ(year, 2010);
    EXPECT_EQ(month, 1);
    EXPECT_EQ(day, 1);
    EXPECT_EQ(doy, 1);
    EXPECT_EQ(hour, 0);

    float rigidityStep;
    res = fscanf(f, "100 1 1 %f\n", &rigidityStep);
    EXPECT_EQ(res, 1);
    EXPECT_FLOAT_EQ(rigidityStep, 0.1);

    float dst, pdyn, byimf, bzinmf;
    res = fscanf(f, "%f %f %f %f\n", &dst, &pdyn, &byimf, &bzinmf);
    EXPECT_EQ(res, 4);
    EXPECT_FLOAT_EQ(dst, -20);
    EXPECT_FLOAT_EQ(pdyn, 3.49);
    EXPECT_FLOAT_EQ(byimf, 0.1);
    EXPECT_FLOAT_EQ(bzinmf, -1);

    res = fscanf(f, "-1.00\n");
    EXPECT_EQ(res, 0);

    fclose(f);
}