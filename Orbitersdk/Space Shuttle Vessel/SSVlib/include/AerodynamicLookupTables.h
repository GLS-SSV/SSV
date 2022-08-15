/****************************************************************************
  This file is part of Space Shuttle Vessel

  Aero lookup tables definition


  Space Shuttle Vessel is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Space Shuttle Vessel is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Space Shuttle Vessel; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
  file SSV-LICENSE.txt for more details.

  **************************************************************************/
/******* SSV File Modification Notice *******
Date         Developer
2020/08/24   GLS
2021/01/20   GLS
2021/07/03   GLS
2021/08/03   GLS
2021/08/24   GLS
2022/08/05   GLS
********************************************/
#ifndef AERODYNAMICLOOKUPTABLES_H_F18DDB2B_9538_4f87_83D4_159A0E2E3D58
#define AERODYNAMICLOOKUPTABLES_H_F18DDB2B_9538_4f87_83D4_159A0E2E3D58
#pragma once

#include <vector>

namespace Aerodynamics
{

/**
 * 2D lookup tables for cl, cd and cm values.
 * For wing data, x corresponds to mach and y corresponds to AoA
 * For control surface data, x corresponds to AoA and y corresponds to deflection
 */
class TwoDLookup
{
	friend class ThreeDLookup;

	std::vector<double> xValues;
	std::vector< std::vector<double> > yValues;

	std::vector< std::vector<double> > liftLookupTable;
	std::vector< std::vector<double> > dragLookupTable;
	std::vector< std::vector<double> > momentLookupTable;

	unsigned int xLowerIndex, xUpperIndex, yLowerIndex, yUpperIndex;
public:
	TwoDLookup();
	virtual ~TwoDLookup();

	void GetValues(double x, double y, double& cl, double& cd, double& cm);

	static bool Compare(TwoDLookup& l1, TwoDLookup& l2);
protected:
	/**
	 * Adds data to lookup tables.
	 * Should only be used for horizontal aerodynamic data (side force instead of lift/drag coefficients)
	 * Note that this MUST be called in order of increasing mach value (i.e. 0.5 to 25.0)
	 */
	void AddHorizontalDataRange(double beta, const std::vector<double>& deflectionData, const std::vector<double>& sideForceData, const std::vector<double>& yawMomentData, const std::vector<double>& rollMomentData);
	/**
	 * Adds vertical data to lookup tables.
	 * Converts axial values to lift/drag coefficients
	 * Note that this MUST be called in order of increasing mach value (i.e. 0.5 to 25.0)
	 */
	void AddVerticalDataRange(double aoa, const std::vector<double>& deflectionData, const std::vector<double>& normalData, const std::vector<double>& axialData, const std::vector<double>& momentData);
private:
	/**
	 *
	 * @param data table of values
	 * @param x1 index of lower x value
	 * @param y1 index of lower y value corresponding to x1
	 * @param x2 index of upper x value; equal to x1+1
	 * @param y2 index of lower y value corresponding to x2; almost always equal to y1
	 */
	double Interpolate(const std::vector< std::vector<double> >& data, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, double x, double y) const;
};


/**
 * 3D lookup table for cl, cm and cd values
 * x corresponds to aoa, y corresponds to deflection, z corresponds to mach
 * Data file format:
 *      1st line: list of aerosurface deflection values (ordered smallest to largest)
 *      2nd line: mach, AOA
 *      3rd line: list of normal force coefficients (side force for horizontal data)
 *      4th line: list of axial force coefficients (yaw moment for horizontal data)
 *      5th line: list of pitch moment coefficients (roll moment for horizontal data)
 *      Repeat lines 2-5 for all mach/AOA combinations; data sets should be ordered first by increasing (constant mach), then increasing mach
 */
class ThreeDLookup
{
	std::vector<double> zValues;

	std::vector<TwoDLookup> lookupTables;

	unsigned int lowerZIndex;
public:
	ThreeDLookup();
	explicit ThreeDLookup(const char* dataFile, bool isHorizontalData = false);
	virtual ~ThreeDLookup();

	void Init(const char* dataFile, bool isHorizontalData = false);
	void Init(std::istream& data, bool isHorizontalData);

	/**
	 * Returns lift, drag and moment coefficients (side force, yaw moment and roll moment for horizontal table)
	 * For 4D table, input should be deflection, AOA, beta instead of mach, AOA, deflection
	 * @param mach Current Mach number
	 * @param aoa Angle of Attack in degrees
	 * @param deflection Deflection of relevant control surface, measured in appropriate units (usually degrees or %)
	 * @param cl Will be set to lift coefficient (side force for horizontal lookup)
	 * @param cd Will be set to drag coefficient (yaw moment for horizontal lookup)
	 * @param cm Will be set to pitch moment coefficient (roll moment for horizontal lookup)
	 */
	void GetValues(double mach, double aoa, double deflection, double& cl, double& cd, double& cm);

	static bool Compare(ThreeDLookup& l1, ThreeDLookup& l2);
protected:
	void AddHorizontalDataRange(double mach, double aoa, const std::vector<double>& deflectionData, const std::vector<double>& sideForceData, const std::vector<double>& yawMomentData, const std::vector<double>& rollMomentData);
	/**
	 * Adds vertical data to lookup table
	 * Converts axial values to lift/drag coefficients
	 */
	void AddVerticalDataRange(double mach, double aoa, const std::vector<double>& deflectionData, const std::vector<double>& normalData, const std::vector<double>& axialData, const std::vector<double>& momentData);
	/**
	 * Reads data in single line of csv file into vector
	 * @param line line containing double values delimited by commas
	 */
	//void ReadCSVLine(const std::string& line, std::vector<double>& data) const;
};

/**
 * 4D lookup table; used for horizontal data
 * Data file format:
 *      1st line: range of mach values
 *      2nd line: blank line
 *      3rd line: first mach value
 *      list of 3D lookup tables (with beta replacing aerosurface deflection); each 3D table contains data for one particular mach value; tables are separated by a blank line followed by a line containing the mach value corresponding to the table below
 *      Each 3D table has the form
 *           range of beta values
 *           aerosurface deflection,AOA
 *           lift of side force coefficients
 *           lift of yaw moment coefficients
 *           lift of roll moment coefficients
 *           ...
 */
class FourDLookup
{
	std::vector<double> machValues;
	std::vector<ThreeDLookup> lookupTables;
	unsigned int lowerIndex;
public:
	FourDLookup();
	//FourDLookup(const char* dataFile, bool isHorizontalData = false);
	virtual ~FourDLookup();

	void Init(const char* dataFile, bool isHorizontalData = false);
	//void Init(std::istream& data, bool isHorizontalData);

	/**
	 * Uses interpolation to get values from lookup table
	 * @param cl Will be set to side force coefficient (normal force for vertical lookup)
	 * @param cd Will be set to yaw moment coefficient (axial force for vertical lookup)
	 * @param cm Will be set to roll moment coefficient (pitch moment for vertical lookup)
	 */
	void GetValues(double mach, double aoa, double beta, double deflection, double& cl, double& cd, double& cm);
};

};

#endif
