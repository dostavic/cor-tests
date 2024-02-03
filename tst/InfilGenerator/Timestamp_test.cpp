#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <chrono>
#include <string>
#include <fstream>
#include <iostream>
#include "infilGenerator.hpp"
#include "Timestamp.hpp"

TEST(timestamp_test, mytimepoint){
    int year = -2022;
    int doy = 82;
    int hours = 13;

    Timestamp date(year, doy, hours);

    EXPECT_EXIT(date.fromYDH(year, doy, hours), ::testing::ExitedWithCode(255), ".*");
}

TEST(timestamp_test, mytimepoint_1){
    int year = 2022;
    int doy = -82;
    int hours = 13;

    Timestamp date(year, doy, hours);

    EXPECT_EXIT(date.fromYDH(year, doy, hours), ::testing::ExitedWithCode(255), ".*");
}

TEST(timestamp_test, mytimepoint_2){
    int year = 2022;
    int doy = 82;
    int hours = -13;

    Timestamp date(year, doy, hours);

    EXPECT_EXIT(date.fromYDH(year, doy, hours), ::testing::ExitedWithCode(255), ".*");
}

TEST(timestamp_test, mytimepoint_3){
    int year = 2022;
    int doy = 82;
    int hours = 25;

    Timestamp date(year, doy, hours);

    EXPECT_EXIT(date.fromYDH(year, doy, hours), ::testing::ExitedWithCode(255), ".*");
}

TEST(timestamp_test, mytimepoint_4){
    int year = 3000;
    int doy = 367;
    int hours = 5;

    Timestamp date(year, doy, hours);

    EXPECT_EXIT(date.fromYDH(year, doy, hours), ::testing::ExitedWithCode(255), ".*");
}

TEST(calculateHourDiff, test){
    Timestamp date("2023-04-07 10:00:00");
    Timestamp another("2023-04-07 12:00:00");

    EXPECT_EQ(date.calculateHourDiff(&another), 2);
}

TEST(calculateHourDiff, test_1){
    Timestamp date("2023-04-07 12:00:00");
    Timestamp another("2023-04-07 10:00:00");

    EXPECT_EQ(date.calculateHourDiff(&another), 2);
}

TEST(calculateHourDiff, test_2){
    Timestamp date("2023-04-07 10:00:00");
    Timestamp another("2023-04-07 10:00:00");

    EXPECT_EQ(date.calculateHourDiff(&another), 0);
}

TEST(calculateHourDiff, test_3){
    Timestamp date("2023-04-07 10:00:00");
    Timestamp another = NULL;

    EXPECT_EXIT(date.calculateHourDiff(&another), ::testing::ExitedWithCode(255), ".*");
}

TEST(addHour, test){
    Timestamp date("2023-04-07 10:00:00");
    date.addHours(2);

    EXPECT_EQ(date.getYear(), 2023);
    EXPECT_EQ(date.getMonth(), 4);
    EXPECT_EQ(date.getDay(), 7);
    EXPECT_EQ(date.getHour(), 12);
}

TEST(addHour, test_1){
    Timestamp date("2023-04-07 10:00:00");
    date.addHours(-2);

    EXPECT_EQ(date.getYear(), 2023);
    EXPECT_EQ(date.getMonth(), 4);
    EXPECT_EQ(date.getDay(), 7);
    EXPECT_EQ(date.getHour(), 8);
}

TEST(addHour, test_2){
    Timestamp date("2023-04-07 10:00:00");
    date.addHours(0);

    EXPECT_EQ(date.getYear(), 2023);
    EXPECT_EQ(date.getMonth(), 4);
    EXPECT_EQ(date.getDay(), 7);
    EXPECT_EQ(date.getHour(), 10);
}

TEST(addHour, test_3){
    Timestamp date("2023-04-07 10:00:00");
    date.addHours(96244);

    EXPECT_EQ(date.getYear(), 2034);
    EXPECT_EQ(date.getMonth(), 3);
    EXPECT_EQ(date.getDay(), 30);
    EXPECT_EQ(date.getHour(), 14);
}

TEST(addHour, test_4){
    Timestamp date("2023-04-07 00:00:00");
    date.addHours(-2);

    EXPECT_EQ(date.getYear(), 2023);
    EXPECT_EQ(date.getMonth(), 4);
    EXPECT_EQ(date.getDay(), 6);
    EXPECT_EQ(date.getHour(), 22);
}

TEST(addHour, test_5){
    Timestamp date("2024-02-28 00:00:00");
    date.addHours(24);

    EXPECT_EQ(date.getYear(), 2024);
    EXPECT_EQ(date.getMonth(), 2);
    EXPECT_EQ(date.getDay(), 29);
    EXPECT_EQ(date.getHour(), 0);
}

TEST(addHour, test_6){
    Timestamp date("2023-02-28 00:00:00");
    date.addHours(24);

    EXPECT_EQ(date.getYear(), 2023);
    EXPECT_EQ(date.getMonth(), 3);
    EXPECT_EQ(date.getDay(), 1);
    EXPECT_EQ(date.getHour(), 0);
}

TEST(addHour, test_7){
    Timestamp date("2023-12-31 00:00:00");
    date.addHours(24);

    EXPECT_EQ(date.getYear(), 2024);
    EXPECT_EQ(date.getMonth(), 1);
    EXPECT_EQ(date.getDay(), 1);
    EXPECT_EQ(date.getHour(), 0);
}