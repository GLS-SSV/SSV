/******* SSV File Modification Notice *******
Date         Developer
2020/03/29   GLS
2020/06/21   GLS
2020/08/24   GLS
2021/08/24   GLS
2022/08/05   GLS
2022/09/29   GLS
2022/09/30   GLS
********************************************/
#include <fstream>
#include <string>
#include <sstream>
#include <cassert>
#include <AerodynamicLookupTables.h>
#include <MathSSV.h>
#include <UtilsSSV.h>

namespace Aerodynamics
{

TwoDLookup::TwoDLookup()
: xLowerIndex(0), yLowerIndex(0), xUpperIndex(1), yUpperIndex(1)
{
}

TwoDLookup::~TwoDLookup()
{
}

void TwoDLookup::AddHorizontalDataRange(double beta, const std::vector<double>& deflectionData, const std::vector<double>& sideForceData, const std::vector<double>& yawMomentData, const std::vector<double>& rollMomentData)
{
	assert(deflectionData.size() == sideForceData.size());
	assert(deflectionData.size() == yawMomentData.size());
	assert(deflectionData.size() == rollMomentData.size());

	xValues.push_back(beta);
	yValues.push_back(deflectionData);
	liftLookupTable.push_back(sideForceData);
	dragLookupTable.push_back(yawMomentData);
	momentLookupTable.push_back(rollMomentData);
}

void TwoDLookup::AddVerticalDataRange(double x, const std::vector<double>& yData, const std::vector<double>& normalData, const std::vector<double>& axialData, const std::vector<double>& momentData)
{
	xValues.push_back(x);
	yValues.push_back(yData);
	liftLookupTable.push_back(normalData);
	dragLookupTable.push_back(axialData);
	momentLookupTable.push_back(momentData);

	for(unsigned int i=0;i<normalData.size();i++) {
		VECTOR3 axial = _V(-axialData[i], normalData[i], 0.0);
		VECTOR3 ld = RotateVectorZ(axial, x);
		dragLookupTable[dragLookupTable.size()-1][i] = -ld.x;
		liftLookupTable[liftLookupTable.size()-1][i] = ld.y;
	}
}

void TwoDLookup::GetValues(double x, double y, double& cl, double& cd, double& cm)
{
	if(x<xValues[xLowerIndex] || x>xValues[xUpperIndex])
		xLowerIndex = GetLowerIndex(xValues, x);
	xUpperIndex = xLowerIndex+1;

	if (yValues[0].size() == 1)
	{
		// for single deflection (parameter y) table
		yLowerIndex = 0;
		yUpperIndex = 0;
	}
	else
	{
		if(y<yValues[xLowerIndex][yLowerIndex] || y>yValues[xLowerIndex][yUpperIndex])
			yLowerIndex = GetLowerIndex(yValues[xLowerIndex], y);
		yUpperIndex = yLowerIndex + 1;
	}

	cl = Interpolate(liftLookupTable, xLowerIndex, yLowerIndex, xUpperIndex, yUpperIndex, x, y);
	cd = Interpolate(dragLookupTable, xLowerIndex, yLowerIndex, xUpperIndex, yUpperIndex, x, y);
	cm = Interpolate(momentLookupTable, xLowerIndex, yLowerIndex, xUpperIndex, yUpperIndex, x, y);
}

double TwoDLookup::Interpolate(const std::vector<std::vector<double> > &data, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, double x, double y) const
{
	if ((y1 == 0.0) && (y2 == 0.0))
	{
		// for single deflection (parameter y) table
		return linterp( xValues[x1], data[x1][0], xValues[x2], data[x2][0], x );
	}
	else
	{
		double a = linterp(yValues[x1][y1], data[x1][y1], yValues[x1][y2], data[x1][y2], y);
		double b = linterp(yValues[x2][y1], data[x2][y1], yValues[x2][y2], data[x2][y2], y);
		return linterp(xValues[x1], a, xValues[x2], b, x);
	}
}

bool TwoDLookup::Compare(TwoDLookup& l1, TwoDLookup& l2)
{
	for(unsigned int i=0;i<l1.liftLookupTable.size();i++) {
		for(unsigned int j=0;j<l1.liftLookupTable[i].size();j++) {
			if(!Eq(l1.liftLookupTable[i][j], l2.liftLookupTable[i][j])) return false;
			if(!Eq(l1.dragLookupTable[i][j], l2.dragLookupTable[i][j])) return false;
			if(!Eq(l1.momentLookupTable[i][j], l2.momentLookupTable[i][j])) return false;
		}
	}
	return true;
}

ThreeDLookup::ThreeDLookup()
: lowerZIndex(0)
{
}

ThreeDLookup::ThreeDLookup(const char* dataFile, bool isHorizontalData)
: lowerZIndex(0)
{
	Init(dataFile, isHorizontalData);
}

ThreeDLookup::~ThreeDLookup()
{
}

void ThreeDLookup::Init(const char* dataFile, bool isHorizontalData)
{
	std::ifstream dataIn(dataFile);
	oapiWriteLogV( "Loading aerodynamic data from file: %s", (char*)dataFile );
	if(!dataIn.fail()) { // file was opened; read data
		Init(dataIn, isHorizontalData);
		dataIn.close();
	}
	else {
		throw std::exception( "Could not find aerodynamic data file" );
	}

	/*for(unsigned int i=0;i<lookupTables[0].liftLookupTable.size();i++) {
		std::ostringstream stream1;
		std::ostringstream stream2;
		stream1 << zValues[0] << " " << lookupTables[0].xValues[i];
		stream2 << zValues[0] << " "<< lookupTables[0].xValues[i];
		for(unsigned int j=0;j<lookupTables[0].liftLookupTable[i].size();j++) {
			stream1 << " " << lookupTables[0].liftLookupTable[i][j];
			stream2 << " " << lookupTables[0].dragLookupTable[i][j];
		}
		oapiWriteLog((char*)stream1.str().c_str());
		oapiWriteLog((char*)stream2.str().c_str());
	}*/

}

void ThreeDLookup::Init(std::istream& data, bool isHorizontalData)
{
	std::string line;
	// read deflection range
	std::vector<double> deflectionRange;
	std::getline(data, line);
	ReadCSVLine(line, deflectionRange);

	unsigned int lineCount = 2; // counter in case file is invalid
	double lastMach = -100.0;
	double lastAOA = -100.0;
	std::vector<double> normalData;
	std::vector<double> axialData;
	std::vector<double> momentData;
	std::vector<double> machAoaValues;
	while(data.good()) {
		std::getline(data, line);
		ReadCSVLine(line, machAoaValues);
		std::getline(data, line);
		ReadCSVLine(line, normalData);
		std::getline(data, line);
		ReadCSVLine(line, axialData);
		std::getline(data, line);
		ReadCSVLine(line, momentData);

		// make sure block of data is valid
		bool countError = ( (machAoaValues.size() != 2) ||
							( normalData.size() != deflectionRange.size()) ||
							( axialData.size() != deflectionRange.size() ) ||
							( momentData.size() != deflectionRange.size()) );
		if(countError) {
			std::ostringstream message;
			message << "ERROR: Invalid aerodynamic data file " << std::endl;
			message << "Data block at line " << lineCount;
			oapiWriteLog((char*)message.str().c_str());
			oapiWriteLog((char*)line.c_str());
			break;
		}
		else { // check that data is added in correct order
			if((Eq(lastMach, machAoaValues[0], 0.0001) && machAoaValues[1]<lastAOA) || machAoaValues[0]<lastMach) {
				std::ostringstream message;
				message << "ERROR: Incorrect data order " << std::endl;
				message << "Mach: " << machAoaValues[0] << " AOA: " << machAoaValues[1] << std::endl;
				message << "Data block at line " << lineCount;
				oapiWriteLog((char*)message.str().c_str());
				break;
			}
		}
		lastMach = machAoaValues[0];
		lastAOA = machAoaValues[1];

		if(isHorizontalData) {
			AddHorizontalDataRange(machAoaValues[0], machAoaValues[1], deflectionRange, normalData, axialData, momentData);
		}
		else {
			AddVerticalDataRange(machAoaValues[0], machAoaValues[1], deflectionRange, normalData, axialData, momentData);
		}
		lineCount+=4;
	}
}

void ThreeDLookup::GetValues(double mach, double aoa, double deflection, double &cl, double &cd, double &cm)
{
	double cl1, cl2;
	double cd1, cd2;
	double cm1, cm2;

	if(mach<zValues[lowerZIndex] || mach>zValues[lowerZIndex+1])
		lowerZIndex = GetLowerIndex(zValues, mach);
	unsigned int upperZIndex = lowerZIndex+1;

	lookupTables[lowerZIndex].GetValues(aoa, deflection, cl1, cd1, cm1);
	lookupTables[upperZIndex].GetValues(aoa, deflection, cl2, cd2, cm2);

	cl = linterp(zValues[lowerZIndex], cl1, zValues[upperZIndex], cl2, mach);
	cd = linterp(zValues[lowerZIndex], cd1, zValues[upperZIndex], cd2, mach);
	cm = linterp(zValues[lowerZIndex], cm1, zValues[upperZIndex], cm2, mach);
}

void ThreeDLookup::AddHorizontalDataRange(double mach, double aoa, const std::vector<double>& deflectionData, const std::vector<double>& sideForceData, const std::vector<double>& yawMomentData, const std::vector<double>& rollMomentData)
{
	if(zValues.empty() || zValues[zValues.size()-1]!=mach) {
		zValues.push_back(mach);
		lookupTables.push_back(TwoDLookup());
	}

	lookupTables[lookupTables.size()-1].AddHorizontalDataRange(aoa, deflectionData, sideForceData, yawMomentData, rollMomentData);
}

void ThreeDLookup::AddVerticalDataRange(double mach, double aoa, const std::vector<double>& deflectionData, const std::vector<double>& normalData, const std::vector<double>& axialData, const std::vector<double>& momentData)
{
	if(zValues.empty() || zValues[zValues.size()-1]!=mach) {
		zValues.push_back(mach);
		lookupTables.push_back(TwoDLookup());
	}

	lookupTables[lookupTables.size()-1].AddVerticalDataRange(aoa, deflectionData, normalData, axialData, momentData);
}

/*void ThreeDLookup::ReadCSVLine(const std::string &line, std::vector<double> &data) const
{
	data.clear(); // empty vector before adding data
	std::istringstream inputStream(line);
	while(!inputStream.eof()) {
		double value;
		inputStream>>value;
		data.push_back(value);
		inputStream.ignore(1, ',');
	}
}*/

bool ThreeDLookup::Compare(ThreeDLookup& l1, ThreeDLookup& l2)
{
	if(l1.zValues.size() != l2.zValues.size()) return false;

	for(unsigned int i=0;i<l1.lookupTables.size();i++) {
		if(!TwoDLookup::Compare(l1.lookupTables[i], l2.lookupTables[i]))
			return false;
	}
	return true;
}

FourDLookup::FourDLookup()
: lowerIndex(0)
{
}

FourDLookup::~FourDLookup()
{
}

void FourDLookup::Init(const char* dataFile, bool isHorizontalData)
{
	std::ifstream data(dataFile);
	if(!data.fail()) { // file was opened; read data
		oapiWriteLogV( "Loading aerodynamic data from file: %s", (char*)dataFile );
		//Init(dataIn, isHorizontalData);

		std::string line;
		// read deflection range
		std::getline(data, line);
		ReadCSVLine(line, machValues);
		// ignore next 2 lines (blank line, followed by first deflection value)
		std::getline(data, line);
		std::getline(data, line);

		unsigned int lineCount = 1;
		bool emptyTable = true;
		std::stringstream ThreeDTable;
		while(data.good()) {
			std::getline(data, line);
			++lineCount;
			if(line.length() == 0) { // empty line; create new table
				lookupTables.push_back(ThreeDLookup());
				lookupTables.back().Init(ThreeDTable, isHorizontalData);
				// clear string and reset flags
				ThreeDTable.str(std::string());
				ThreeDTable.clear();
				emptyTable = true;
				// log progress
				std::ostringstream message;
				message << "Read 3D table block ending at " << lineCount-1 << std::endl;
				oapiWriteLog((char*)message.str().c_str());
				// ignore next line (only used to make editing table easier)
				if(data.good()) std::getline(data, line);
			}
			else {
				//ThreeDTable << line << std::endl;
				if(!emptyTable) ThreeDTable << std::endl;
				ThreeDTable << line;
				emptyTable = false;
			}
		}
		if(ThreeDTable.str().length() > 0) { // create new table for last data block
			lookupTables.push_back(ThreeDLookup());
			lookupTables.back().Init(ThreeDTable, isHorizontalData);
		}

		data.close();
	}
	else {
		oapiWriteLogV( "ERROR: Could not find aerodynamic data file: %s", (char*)dataFile );
	}

	/*for(unsigned int i=0;i<lookupTables[0].liftLookupTable.size();i++) {
		std::ostringstream stream1;
		std::ostringstream stream2;
		stream1 << zValues[0] << " " << lookupTables[0].xValues[i];
		stream2 << zValues[0] << " "<< lookupTables[0].xValues[i];
		for(unsigned int j=0;j<lookupTables[0].liftLookupTable[i].size();j++) {
			stream1 << " " << lookupTables[0].liftLookupTable[i][j];
			stream2 << " " << lookupTables[0].dragLookupTable[i][j];
		}
		oapiWriteLog((char*)stream1.str().c_str());
		oapiWriteLog((char*)stream2.str().c_str());
	}*/
}

void FourDLookup::GetValues(double mach, double aoa, double beta, double deflection, double& cl, double& cd, double& cm)
{
	double cl1, cl2;
	double cd1, cd2;
	double cm1, cm2;

	if(mach<machValues[lowerIndex] || mach>machValues[lowerIndex+1])
		lowerIndex = GetLowerIndex(machValues, mach);
	unsigned int upperIndex = lowerIndex+1;

	lookupTables[lowerIndex].GetValues(deflection, aoa, beta, cl1, cd1, cm1);
	lookupTables[upperIndex].GetValues(deflection, aoa, beta, cl2, cd2, cm2);

	cl = linterp(machValues[lowerIndex], cl1, machValues[upperIndex], cl2, mach);
	cd = linterp(machValues[lowerIndex], cd1, machValues[upperIndex], cd2, mach);
	cm = linterp(machValues[lowerIndex], cm1, machValues[upperIndex], cm2, mach);

}

}
