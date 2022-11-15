/***************************************
* Satellite Test
*
*
************************************/
#include "pch.h"
#include "CppUnitTest.h"
#include "../simulator.h"
#include "SatelliteTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SatelliteTestVS
{
	TEST_CLASS(SimulatorTest)
	{
	public:
		/*
		// Tolerance of floating point approximation
		const double tolerance = 100.0;

		const double GRAVITY_TEST_TIME = 10;
		const double GRAVITY_DISTANCE = 40000000.0;

		// utility funciton because floating point numbers are approximations
		bool closeEnough(double value, double test, double tolerence) const
		{
			double difference = value - test;
			return (difference >= -tolerence) && (difference <= tolerence);
		}
		*/

		TEST_METHOD(SatelliteTesting)
		{
		}

		// Break Apart
		// Easy/Simple - up to Simulator, if Hubble, break into Hubble
		// However, this seems complicated, has to know which is what, more difficult to add new types of Satellites

		// Harder/more Object based - Satellite has Parts, Simulator will ask for Parts and add those
		


		TEST_METHOD(BreakApart)
		{
			TestSatellite().breakApart();

		}

		TEST_METHOD(TestName2)
		{}

		TEST_METHOD(TestName3)
		{}
	};
}