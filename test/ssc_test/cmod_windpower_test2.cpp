#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include "simulation_test_info.h"
#include "computeModuleTest.h"

// first test must be contain all possible inputs
std::vector<SimulationTestTable*> windIntgTests;

/**
* windPowerTestDeclaration creates a SimulationTestTable out of a pair of TestInfo and TestResult structs
* The new SimulationTestTable is added to allWindIntegrationTests, to be instantiated as computeModuleTests
*/

class testDeclaration {
	SimulationTestTable* test;
public:
	testDeclaration(std::vector<SimulationTestTable*>& allTests, const char* cmodName, const char* testName, TestInfo* I, size_t nInfo, TestResult* R, int nRes) {
		if (allTests.size() > 0 && nInfo < allTests[0]->getNumInfo()) {
			test = new SimulationTestTable(*allTests[0]);
			test->name = testName;
			modifyTestInfo(allTests[0], test);
			allTests.push_back(test);
		}
		else {
			test = new SimulationTestTable(cmodName, testName, I, (int)nInfo, R, nRes);
			allTests.push_back(test);
		}
	}
	~testDeclaration() {
		delete test;
	}
};

//class windpowerTestDeclaration {
//	SimulationTestTable* test;
//public:
//	windpowerTestDeclaration(const char* testName, TestInfo* I, size_t nInfo, TestResult* R, int nRes) {
//		if (allWindIntegrationTests.size() > 0 && nInfo < allWindIntegrationTests[0]->getNumInfo()) {
//			test = new SimulationTestTable(*allWindIntegrationTests[0]);
//			modifyTestInfo(allWindIntegrationTests[0], test);
//		}
//		else {
//			test = new SimulationTestTable("windpower", I, (int)nInfo, R, nRes);
//			allWindIntegrationTests.push_back(test);
//		}
//	}
//	~windpowerTestDeclaration() {
//		delete test;
//	}
//};


// Set up wind resource file paths
char hourly[150];
int a = sprintf(hourly, "%s/test/input_docs/wind.srw", std::getenv("SSCDIR"));
char thirtyMin[150];
int b = sprintf(thirtyMin, "%s/test/input_docs/wind_30m.srw", std::getenv("SSCDIR"));
char leapYear[150];
int c = sprintf(leapYear, "%s/test/input_docs/wind_leapYear.srw", std::getenv("SSCDIR"));

// Set up turbine power curve
const char* powercurve_windspeed = "0, 0.25, 0.5, 0.75, 1, 1.25, 1.5, 1.75, 2, 2.25, 2.5, 2.75, 3, 3.25, 3.5, 3.75, 4, 4.25, 4.5, 4.75, 5, 5.25, 5.5, 5.75, 6, 6.25, 6.5, 6.75, 7, 7.25, 7.5, 7.75, 8, 8.25, 8.5, 8.75, 9, 9.25, 9.5, 9.75, 10, 10.25, 10.5, 10.75, 11, 11.25, 11.5, 11.75, 12, 12.25, 12.5, 12.75, 13, 13.25, 13.5, 13.75, 14, 14.25, 14.5, 14.75, 15, 15.25, 15.5, 15.75, 16, 16.25, 16.5, 16.75, 17, 17.25, 17.5, 17.75, 18, 18.25, 18.5, 18.75, 19, 19.25, 19.5, 19.75, 20, 20.25, 20.5, 20.75, 21, 21.25, 21.5, 21.75, 22, 22.25, 22.5, 22.75, 23, 23.25, 23.5, 23.75, 24, 24.25, 24.5, 24.75, 25, 25.25, 25.5, 25.75, 26, 26.25, 26.5, 26.75, 27, 27.25, 27.5, 27.75, 28, 28.25, 28.5, 28.75, 29, 29.25, 29.5, 29.75, 30, 30.25, 30.5, 30.75, 31, 31.25, 31.5, 31.75, 32, 32.25, 32.5, 32.75, 33, 33.25, 33.5, 33.75, 34, 34.25, 34.5, 34.75, 35, 35.25, 35.5, 35.75, 36, 36.25, 36.5, 36.75, 37, 37.25, 37.5, 37.75, 38, 38.25, 38.5, 38.75, 39, 39.25, 39.5, 39.75, 40 ";
const char* powercurve_powerout = "0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 21.320, 33.510, 45.690, 65.210, 79.830, 104.25, 128.660, 157.970, 187.270, 216.580, 250.780, 292.320, 333.850, 375.400, 426.720, 475.600, 534.270, 597.810, 656.490, 724.940, 798.290, 871.630, 940.080, 1010, 1060, 1130, 1190, 1240, 1290, 1330, 1370, 1390, 1410, 1430, 1440, 1460, 1470, 1475, 1480, 1485, 1490, 1495, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ";
const char* xcoord = "0, 616, 1232, 1848, 2464, 3080, 3696, 4312, 308, 924, 1540, 2156, 2772, 3388, 4004, 4620, 0, 616, 1232, 1848, 2464, 3080, 3696, 4312, 308, 924, 1540, 2156, 2772, 3388, 4004, 4620 ";
const char* ycoord = "0, 0, 0, 0, 0, 0, 0, 0, 616, 616, 616, 616, 616, 616, 616, 616, 1232, 1232, 1232, 1232, 1232, 1232, 1232, 1232, 1848, 1848, 1848, 1848, 1848, 1848, 1848, 1848";

// Default Test Info

TestInfo windpowerDefaultInfo[] = {
/*	SSC Var Name							Data Type			Test Values				Length,Width */
	{"wind_resource_filename",				STR,				hourly							},
	{"wind_resource_shear",					NUM,				"0.14"								},
	{"wind_resource_turbulence_coeff",		NUM,				"0.1"								},
	{"system_capacity",						NUM,				"48000"								},
	{"wind_resource_model_choice",			NUM,				"0"									},
	{"weibull_reference_height",			NUM,				"50"								},
	{"weibull_k_factor",					NUM,				"2"									},
	{"weibull_wind_speed",					NUM,				"7.25"								},
	{"wind_turbine_rotor_diameter",			NUM,				"77"								},
	{"wind_turbine_powercurve_windspeeds",	ARR,				powercurve_windspeed,	161			},
	{"wind_turbine_powercurve_powerout",	ARR,				powercurve_powerout,	161			},
	{"wind_turbine_hub_ht",					NUM,				"80"								},
	{"wind_turbine_max_cp",					NUM,				"0.450"								},
	{"wind_farm_xCoordinates",				ARR,				xcoord,					32			},
	{"wind_farm_yCoordinates",				ARR,				ycoord,					32			},
	{"wind_farm_losses_percent",			NUM,				"0"									},
	{"wind_farm_wake_model",				NUM,				"0"									},
	{"adjust:constant",						NUM,				"0"									 }
};

TestResult windpowerDefaultResult[] = {
/*	SSC Var Name							Test Type			Test Result				Error Bound % */
	{"annual_energy",						NR,					33224154.,				.1},
	{"monthly_energy[0]",					NR,					2.8218e6,				.1},
	{"monthly_energy[11]",					NR,					2.8218e6,				.1}
};

//SimulationTestTable windpowerTestDefault("windpower", &windpowerDefaultInfo[0], 18, &windpowerDefaultResult[0], 3);
testDeclaration defaultTest(windIntgTests, "windpower", "default", &windpowerDefaultInfo[0], 18, &windpowerDefaultResult[0], 3);

TestInfo windpowerLeapYearInfo[] = {
/*	SSC Var Name							Data Type			Test Values				Length,Width */
	{ "wind_resource_filename",				STR,				leapYear }
};

testDeclaration leapYearTest(windIntgTests, "windpower", "leapYear", &windpowerLeapYearInfo[0], 1, &windpowerDefaultResult[0], 3);



INSTANTIATE_TEST_CASE_P(Testin, computeModuleTest, testing::ValuesIn(windIntgTests));