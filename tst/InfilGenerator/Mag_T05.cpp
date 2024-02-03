#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "infilGenerator.hpp"
#include "OutfilData.hpp"
#include <sstream>
#include <string>

const int bufferSize = 1024;

class MagFieldOutfilTest : public MagFieldOutfil{
    public:
    // void callReadInputImpl(char *buffer, FILE *gg, std::string *inputFile){
        // readInputImpl(buffer, gg, inputFile);
    // }
    // void callReadSecondLine(char *buffer, std::string *inputFile, FILE *gg) {
    //     readSecondLine(buffer, inputFile, gg);
    // }
    using MagFieldOutfil::readInputImpl;
    using OutfilData::readSecondLine;
};

TEST(main_t05_mag, parseArguments){
    Arguments arguments;
    int argc = 4;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./tst/InfilGenerator/correctInput/mag.dat0_T05",
        (char*)"./tst/InfilGenerator/outfill/mag_out.dat0_T05",
        (char*)"mag"
    };

    arguments.parseArguments(argc, argv);

    EXPECT_EQ(arguments.inputFile, "./tst/InfilGenerator/correctInput/mag.dat0_T05");
    EXPECT_EQ(arguments.filenamePrefix, "./tst/InfilGenerator/outfill/mag_out.dat0_T05");
    EXPECT_EQ(arguments.infilKind, InfilKind::MAG_FIELD);
}

TEST(main_t05_mag, readInput){
    Arguments argumests;
    argumests.inputFile = "./tst/InfilGenerator/correctInput/mag.dat0_T05";

    std::unique_ptr<OutfilData> outfilData;
    outfilData = std::unique_ptr<OutfilData>(new MagFieldOutfil());
    MagFieldOutfil *magFieldOufil = dynamic_cast<MagFieldOutfil*>(outfilData.get());

    EXPECT_NO_THROW(outfilData->readInput(&(argumests.inputFile)));
}

TEST(main_t05_mag, readInputImpl){
    std::unique_ptr<OutfilData> outfilData(new MagFieldOutfilTest());
    MagFieldOutfilTest *magFieldOutfilTest = dynamic_cast<MagFieldOutfilTest*>(outfilData.get());

    char buffer[bufferSize];
    std::string inputFile = "./tst/InfilGenerator/correctInput/mag.dat0_T05";
    FILE *gg = fopen(inputFile.c_str(), "r");
    
    magFieldOutfilTest->readInputImpl(buffer, gg, &inputFile);

    fclose(gg);

    EXPECT_EQ(magFieldOutfilTest->date.getYear(), 2000);
    EXPECT_EQ(magFieldOutfilTest->date.getMonth(), 9);
    EXPECT_EQ(magFieldOutfilTest->date.getDay(), 8);
    EXPECT_EQ(magFieldOutfilTest->date.getHour(), 0);
    EXPECT_EQ(magFieldOutfilTest->endDate.getYear(), 2000);
    EXPECT_EQ(magFieldOutfilTest->endDate.getMonth(), 9);
    EXPECT_EQ(magFieldOutfilTest->endDate.getDay(), 10);
    EXPECT_EQ(magFieldOutfilTest->endDate.getHour(), 0);
    EXPECT_EQ(magFieldOutfilTest->intervalDur, 1);
    EXPECT_EQ(magFieldOutfilTest->numberOfHours, 49);
    
    EXPECT_FLOAT_EQ(magFieldOutfilTest->geoLoc.geolong, -90);
    EXPECT_FLOAT_EQ(magFieldOutfilTest->geoLoc.geolat, 0);
    EXPECT_FLOAT_EQ(magFieldOutfilTest->localLoc.longloc, 90);
    EXPECT_FLOAT_EQ(magFieldOutfilTest->localLoc.latloc, 360);
    EXPECT_FLOAT_EQ(magFieldOutfilTest->geoLoc.radius, 1);
    EXPECT_FLOAT_EQ(magFieldOutfilTest->latitudeStep, 1);
    EXPECT_FLOAT_EQ(magFieldOutfilTest->longitudeStep, 1);

    EXPECT_EQ(magFieldOutfilTest->magData.size(), 49);
    EXPECT_EQ(magFieldOutfilTest->tIndices.size(), 49);
}

TEST(main_t05_mag, readSecondLine){
    std::unique_ptr<OutfilData> outfilData(new MagFieldOutfilTest());
    MagFieldOutfilTest *magFieldOutfilTest = dynamic_cast<MagFieldOutfilTest*>(outfilData.get());

    char buffer[bufferSize];
    std::string inputFile = "./tst/InfilGenerator/correctInput/mag.dat0_T05_line_2";
    FILE *gg = fopen(inputFile.c_str(), "r");
    
    magFieldOutfilTest->readSecondLine(buffer, &inputFile, gg);

    fclose(gg);

    EXPECT_EQ(magFieldOutfilTest->generateInfils, true);
    EXPECT_EQ(magFieldOutfilTest->inputState, 0);
    EXPECT_EQ(magFieldOutfilTest->version, Version::T05_MAG);
    EXPECT_EQ(magFieldOutfilTest->numberOfDirections, 0);
    EXPECT_EQ(magFieldOutfilTest->optimalizationLevel, 0);
}

TEST(main_t05_mag, readParmodVector){
    std::unique_ptr<OutfilData> outfilData(new MagFieldOutfilTest());
    MagFieldOutfilTest *magFieldOutfilTest = dynamic_cast<MagFieldOutfilTest*>(outfilData.get());
    MagFieldOutfilTest *castData = dynamic_cast<MagFieldOutfilTest*>(outfilData.get());

    int parmodError = 0;
    castData->date = Timestamp("2000-09-08 00:00:00");
    castData->endDate = Timestamp("2000-09-10 00:00:00");
    castData->numberOfHours = 49;
    castData->intervalDur = 1;

    for(int i = 0; i < 49; i++)
        castData->magData.emplace_back();

    readParmodVector(castData, &parmodError);

    for(int i = 0; i < 49; i++){
        EXPECT_GE(castData->magData.at(i).byimf, 0);
        EXPECT_GE(castData->magData.at(i).bzimf, 0);
        EXPECT_GE(castData->magData.at(i).dst, 0);
        EXPECT_GE(castData->magData.at(i).mPars, 0);
        EXPECT_GE(castData->magData.at(i).pdyn, 0);
    }

    EXPECT_EQ(parmodError, 0);
}

TEST(main_t05_mag, readOMNIVector){
    std::unique_ptr<OutfilData> outfilData(new MagFieldOutfilTest());
    MagFieldOutfilTest *magFieldOutfilTest = dynamic_cast<MagFieldOutfilTest*>(outfilData.get());
    MagFieldOutfilTest *castData = dynamic_cast<MagFieldOutfilTest*>(outfilData.get());

    int omniError = 0;
    castData->date = Timestamp("2000-09-08 00:00:00");
    castData->endDate = Timestamp("2000-09-10 00:00:00");
    castData->numberOfHours = 49;
    castData->intervalDur = 1;

    for(int i = 0; i < 49; i++)
        castData->tIndices.emplace_back();

    EXPECT_EQ(castData->tIndices.size(), 49);

    readOMNIVector(castData, &omniError);
    // castData->tIndices = tIndices;
    for(int i = 0; i < 49; i++){
        EXPECT_GE(castData->tIndices.at(i).W1, 0);
        EXPECT_GE(castData->tIndices.at(i).W2, 0);
        EXPECT_GE(castData->tIndices.at(i).W3, 0);
        EXPECT_GE(castData->tIndices.at(i).W4, 0);
        EXPECT_GE(castData->tIndices.at(i).W5, 0);
        EXPECT_GE(castData->tIndices.at(i).W6, 0);
        EXPECT_EQ(castData->tIndices.at(i).success, LineState::FOUND);
    }

    EXPECT_EQ(omniError, 0);
}

TEST(main_t05_mag, writeData){
    Arguments arguments;
    int argc = 4;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./tst/InfilGenerator/correctInput/mag.dat0_T05",
        (char*)"./tst/InfilGenerator/outfill/mag_out.dat0_T05",
        (char*)"mag"
    };

    arguments.parseArguments(argc, argv);
    std::unique_ptr<OutfilData> outfilData;
    outfilData = std::unique_ptr<OutfilData>(new MagFieldOutfilTest());
    MagFieldOutfilTest *magFieldOufilTest = dynamic_cast<MagFieldOutfilTest*>(outfilData.get());
    outfilData->readInput(&(arguments.inputFile));
    int parmodError = 0;
    int omniError = 0;
    MagFieldOutfilTest *castData = dynamic_cast<MagFieldOutfilTest*>(outfilData.get());
    readParmodVector(castData, &parmodError);
    readOMNIVector(castData, &omniError);
    MagFieldOutfilTest *outfil = dynamic_cast<MagFieldOutfilTest*>(outfilData.get());
    Timestamp date(outfil->date);

    for(unsigned int i = 0; i < outfil->numberOfHours; i++)
		outfil->writeData(&(arguments.filenamePrefix), i);

    for(int i = 0; i < 49; i++){
        std::stringstream ss;
        ss << i;
        std::string outputFile = "./tst/InfilGenerator/outfill/mag_out.dat0_T05_" + ss.str();
        FILE *f = fopen(outputFile.c_str(), "r");
        EXPECT_NE(f, nullptr);

        int res = 0;
        float radius, geolat, geolong;
        res = fscanf(f, "%f %f %f\n", &radius, &geolat, &geolong);
        EXPECT_EQ(res, 3);
        EXPECT_FLOAT_EQ(outfil->geoLoc.radius, radius);
        EXPECT_FLOAT_EQ(outfil->geoLoc.geolat, geolat);
        EXPECT_FLOAT_EQ(outfil->geoLoc.geolong, geolong);

        float latitudeStep, longitudeStep, latloc, longloc;
        res = fscanf(f, "%f %f %f %f\n", &latitudeStep, &longitudeStep, &latloc, &longloc);
        EXPECT_EQ(res, 4);
        EXPECT_FLOAT_EQ(outfil->latitudeStep, latitudeStep);
        EXPECT_FLOAT_EQ(outfil->longitudeStep, longitudeStep);
        EXPECT_FLOAT_EQ(outfil->localLoc.latloc, latloc);
        EXPECT_FLOAT_EQ(outfil->localLoc.longloc, longloc);

        int year, mounth, day, doy, hour;
        res = fscanf(f, "%d %d %d %d %d 00 00\n", &year, &mounth, &day, &doy, &hour);
        EXPECT_EQ(res, 5);
        EXPECT_EQ(date.getYear(), year);
        EXPECT_EQ(date.getMonth(), mounth);
        EXPECT_EQ(date.getDay(), day);
        EXPECT_EQ(date.getDoy(), doy);
        EXPECT_EQ(date.getHour(), hour);
        date.addHours(outfil->intervalDur);

        float pdyn, byimf, bzimf;
        int dst;
        res = fscanf(f, "%d %f %f %f\n", &dst, &pdyn, &byimf, &bzimf);
        EXPECT_EQ(res, 4);
        EXPECT_EQ(outfil->magData.at(i).dst, dst);
        EXPECT_FLOAT_EQ(outfil->magData.at(i).pdyn, pdyn);
        EXPECT_FLOAT_EQ(outfil->magData.at(i).byimf, byimf);
        EXPECT_FLOAT_EQ(outfil->magData.at(i).bzimf, bzimf);

        float W1, W2, W3, W4, W5, W6;
        res = fscanf(f, "%f %f %f %f %f %f\n", &W1, &W2, &W3, &W4, &W5, &W6);
        EXPECT_EQ(res, 6);
        EXPECT_FLOAT_EQ(outfil->tIndices.at(i).W1, W1);
        EXPECT_FLOAT_EQ(outfil->tIndices.at(i).W2, W2);
        EXPECT_FLOAT_EQ(outfil->tIndices.at(i).W3, W3);
        EXPECT_FLOAT_EQ(outfil->tIndices.at(i).W4, W4);
        EXPECT_FLOAT_EQ(outfil->tIndices.at(i).W5, W5);
        EXPECT_FLOAT_EQ(outfil->tIndices.at(i).W6, W6);

        res = fscanf(f, "-1.00\n");
        EXPECT_EQ(res, 0);

        fclose(f);
    }
}