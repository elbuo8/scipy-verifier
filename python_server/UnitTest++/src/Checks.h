#ifndef UNITTEST_CHECKS_H
#define UNITTEST_CHECKS_H

#include "Config.h"
#include "TestResults.h"
#include "MemoryOutStream.h"

namespace UnitTest {


template< typename Value >
bool Check(Value const value)
{
    return !!value; // doing double negative to avoid silly VS warnings
}


template< typename Expected, typename Actual >
void CheckEqual(TestResults& results, Expected const& expected, Actual const& actual, TestDetails const& details)
{
    //if (!(expected == actual))
    //{
    /*THIS IS A CRIME BUT I'm IN A HURRY */
    bool verify = expected == actual;
        UnitTest::MemoryOutStream stream;
        stream << "" << expected << ":DELIMITER:" << actual << ":DELIMITER:" << verify;

        results.OnTestFailure(details, stream.GetText());
    //}
}

void CheckEqual(TestResults& results, char const* expected, char const* actual, TestDetails const& details);

void CheckEqual(TestResults& results, char* expected, char* actual, TestDetails const& details);

void CheckEqual(TestResults& results, char* expected, char const* actual, TestDetails const& details);

void CheckEqual(TestResults& results, char const* expected, char* actual, TestDetails const& details);

template< typename Expected, typename Actual, typename Tolerance >
bool AreClose(Expected const& expected, Actual const& actual, Tolerance const& tolerance)
{
    return (actual >= (expected - tolerance)) && (actual <= (expected + tolerance));
}

template< typename Expected, typename Actual, typename Tolerance >
void CheckClose(TestResults& results, Expected const& expected, Actual const& actual, Tolerance const& tolerance,
                TestDetails const& details)
{
    //if (!AreClose(expected, actual, tolerance))
    //{
    bool verify = AreClose(expected, actual, tolerance);
        UnitTest::MemoryOutStream stream;
        stream << "" << expected << ":DELIMITER:" << actual << ":DELIMITER:" << verify;

        results.OnTestFailure(details, stream.GetText());
    //}
}


template< typename Expected, typename Actual >
void CheckArrayEqual(TestResults& results, Expected const& expected, Actual const& actual,
                int const count, TestDetails const& details)
{
    bool equal = true;
    for (int i = 0; i < count; ++i)
        equal &= (expected[i] == actual[i]);

    //if (!equal)
    //{
    bool verify = equal;
        UnitTest::MemoryOutStream stream;
		stream << "[";

		for (int expectedIndex = 0; expectedIndex < count; ++expectedIndex)
            stream << expected[expectedIndex] << " ";

		stream << "]:DELIMITER:[";

		for (int actualIndex = 0; actualIndex < count; ++actualIndex)
            stream << actual[actualIndex] << " ";

		stream << "]:DELIMITER:" << verify;

        results.OnTestFailure(details, stream.GetText());
    //}
}

template< typename Expected, typename Actual, typename Tolerance >
bool ArrayAreClose(Expected const& expected, Actual const& actual, int const count, Tolerance const& tolerance)
{
    bool equal = true;
    for (int i = 0; i < count; ++i)
        equal &= AreClose(expected[i], actual[i], tolerance);
    return equal;
}

template< typename Expected, typename Actual, typename Tolerance >
void CheckArrayClose(TestResults& results, Expected const& expected, Actual const& actual,
                   int const count, Tolerance const& tolerance, TestDetails const& details)
{
    bool equal = ArrayAreClose(expected, actual, count, tolerance);

    //if (!equal)
    //{
        bool verify = equal;
        UnitTest::MemoryOutStream stream;

        stream << "[";
        for (int expectedIndex = 0; expectedIndex < count; ++expectedIndex)
            stream << expected[expectedIndex] << " ";
        stream << "]:DELIMITER:[";

		for (int actualIndex = 0; actualIndex < count; ++actualIndex)
            stream << actual[actualIndex] << " ";
        stream << "]:DELIMITER:" << verify;

        results.OnTestFailure(details, stream.GetText());
    //}
}

template< typename Expected, typename Actual, typename Tolerance >
void CheckArray2DClose(TestResults& results, Expected const& expected, Actual const& actual,
                   int const rows, int const columns, Tolerance const& tolerance, TestDetails const& details)
{
    bool equal = true;
    for (int i = 0; i < rows; ++i)
        equal &= ArrayAreClose(expected[i], actual[i], columns, tolerance);

    //if (!equal)
    //{
    bool verify = equal;
        UnitTest::MemoryOutStream stream;

        stream << "[";

		for (int expectedRow = 0; expectedRow < rows; ++expectedRow)
        {
            stream << "[";
            for (int expectedColumn = 0; expectedColumn < columns; ++expectedColumn)
                stream << expected[expectedRow][expectedColumn] << " ";
            stream << "]";
        }

		stream << "]:DELIMITER:[" << verify;

		for (int actualRow = 0; actualRow < rows; ++actualRow)
        {
            stream << "[";
            for (int actualColumn = 0; actualColumn < columns; ++actualColumn)
                stream << actual[actualRow][actualColumn] << " ";
            stream << "]";
        }

		stream << "]:DELIMITER:" << equal;

        results.OnTestFailure(details, stream.GetText());
    //}
}

}

#endif
