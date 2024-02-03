#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include "infilGenerator.hpp"
#include "OutfilData.hpp"

#define Pi 3.14159265358979
#define pipol Pi/2.0

// parseArguments нема необхіжності провіряти
// readInput нема необхідності провіряти
// протестувати readInputImpl normal
/*тестувати Normal, 2 напрямки IGRF
  відрізняється numberOfDirections
  застряг в geo_to_mag
  напевно напишу тести на основну функціональність
  а потім тести суто на функції
  я забув завантажити дані для IGFR та результати були nan
  в readGH можуть виникти помилки з stoi та stod, але файли є константами
  протестувати окремо getLocalRotations - до результатів неможливо добратись*/ 

TEST(normal_2_IGRF, numberOfDirections){
    Arguments arguments;
    std::unique_ptr<OutfilData> outfilData;

    int argc = 3;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF_directions_2",
        (char*)"./tst/InfilGenerator/outfill/trajectory_1_IGRF"
    };

    arguments.parseArguments(argc, argv);
    outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
    NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());
    outfilData->readInput(&(arguments.inputFile));
    
    EXPECT_EQ(normalOutfil->numberOfDirections, 2);
}

TEST(normal_2_IGRF, geomag_test){
    Arguments arguments;
    std::unique_ptr<OutfilData> outfilData;

    int argc = 3;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF_directions_2",
        (char*)"./tst/InfilGenerator/outfill/trajectory_1_IGRF"
    };

    arguments.parseArguments(argc, argv);
    outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
    NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());
    outfilData->readInput(&(arguments.inputFile));

    EXPECT_FLOAT_EQ(normalOutfil->geoLoc.geolat, -42);
    EXPECT_FLOAT_EQ(normalOutfil->geoLoc.geolong, 270);

    EXPECT_FLOAT_EQ(normalOutfil->rigidityData.rigstart, 3.19);
}

TEST(normal_2_IGRF, write_test){
    Arguments arguments;
    std::unique_ptr<OutfilData> outfilData;

    int argc = 3;
    char *argv[] = {
        (char*)"./InfilGenerator",
        (char*)"./tst/InfilGenerator/correctInput/caspoloha.dat0_IGRF_directions_2",
        (char*)"./tst/InfilGenerator/outfill/trajectory_1_IGRF"
    };

    arguments.parseArguments(argc, argv);
    outfilData = std::unique_ptr<OutfilData>(new NormalOutfil());
    NormalOutfil *normalOutfil = dynamic_cast<NormalOutfil*>(outfilData.get());
    outfilData->readInput(&(arguments.inputFile));
}

TEST(infilGenerator_test, getLocalRotations){
    float longitude = 0, lat1 = 0, geolat = 0, geolong = 0;
    float latloc = 0;
    float longloc = 0;

    getLocalRotations(longitude, lat1, geolat, geolong, &latloc, &longloc);

    EXPECT_FLOAT_EQ(latloc, 0);
    EXPECT_FLOAT_EQ(longloc, 270);
}

