/******************************************************
Alexander Russo
CMPSC 201 – Fall 2016
Section 001
Purpose: This program calculates the d-value and Q-value for the angle measured
by a diffractometer as well as the intensity of the peak for the given material.
input: The input file name, the output file name, and the data to be used to calculate
the corresponding d-values and Q-values.
processing: The 2-theta angle and the intensity of the peak to determine the
d-values and Q-values. using the formulas d = wavelength / (2 * sin(theta)), and Q = 1/(sin(theta)^2).
Output: A file using the supplied output file name containing the calculated d-values and Q-values 
along with the original 2-theta and intensity values.
******************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

const double PI = 3.14159265358979323;
const double DEGREES_TO_RADIANS = PI / 180;
const double CU_WAVELENGTH = 1.54059;
const double CR_WAVELENGTH = 2.28973;
const double FE_WAVELENGTH = 1.93604;
const double CO_WAVELENGTH = 1.78900;
const double MO_WAVELENGTH = 0.70932;

int main() 
{
	bool run = true;
	while (run)
	{
		string inputFileName, outputFileName, sampleName, element;
		double twoTheta, intensity, wavelength, dValue, qValue;
		int numPeaks = 0;

		cout << "Please input a file name to import the data from." << endl;
		getline(cin, inputFileName);

		ifstream fileInputStream(inputFileName.append(".dat"));

		cout << "Please input a file name to output the calculated information to." << endl;
		getline(cin, outputFileName);

		ofstream fileOutputStream(outputFileName.append(".txt"));
		fileOutputStream << fixed;

		getline(fileInputStream, sampleName);
		getline(fileInputStream, element);

		if (element == "Cu")
			wavelength = CU_WAVELENGTH;
		else if (element == "Cr")
			wavelength = CR_WAVELENGTH;
		else if (element == "Fe")
			wavelength = FE_WAVELENGTH;
		else if (element == "Co")
			wavelength = CO_WAVELENGTH;
		else if (element == "Mo")
			wavelength = MO_WAVELENGTH;

		fileOutputStream << "For sample \"" << sampleName << "\" with anode of " << element << " and wavelength " << setprecision(5) << wavelength << " the values are:" << endl << endl;
		fileOutputStream << "\t2-theta\t\tIntensity\td values\tQ values" << endl;

		cout << fixed;
		while (fileInputStream >> twoTheta)
		{
			fileInputStream >> intensity;
			dValue = wavelength / (2 * sin((twoTheta * DEGREES_TO_RADIANS) / 2));	// Calculate d-value, d = wavelength / (2 * sin(theta))
			qValue = 1 / pow(sin((twoTheta * DEGREES_TO_RADIANS) / 2), 2);			// Calculate Q-value, Q = 1/sin(theta)^2
			
			// These integers are used to maintain the integrity of the significant figures as well as the document format.
			int thetaShift = 0, dShift = 0, qShift = 0;
			if (twoTheta > 100)	thetaShift++;
			if (dValue > 10)	dShift++;
			if (qValue > 10)	qShift++;

			fileOutputStream << "\t" << setprecision(4 - thetaShift) << twoTheta << "\t\t";
			fileOutputStream << setprecision(0) << intensity << "\t\t";
			fileOutputStream << setprecision(5 - dShift) << dValue << "\t\t";
			fileOutputStream << setprecision(6 - qShift) << qValue << endl;

			numPeaks++;
		}
		fileInputStream.close();
		fileOutputStream.close();
		cout << "There were " << numPeaks << " peaks in the file.\nWould you like to analyze data from another file (y/n)?" << endl;
		char input;
		cin >> input;
		
		while (input != 'y' && input != 'n')
		{
			cout << "You have input an invalid selection. Please select again. (y/n)" << endl;
			cin >> input;
		}

		if (input == 'n')
			run = false;
	}
	return 0;
}