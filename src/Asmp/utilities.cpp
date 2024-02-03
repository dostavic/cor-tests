#include "utilities.hpp"
#include <iterator>

void parseDataFromLine(std::string *line, std::string *filename, unsigned int *year, unsigned int *percent)
{
	std::string _year, _percent, timestamp;
	std::stringstream stream;
	stream << (*line);
	stream >> (*filename);
	stream >> timestamp;
	_year = timestamp.substr(0, 4);
	_percent = timestamp.substr(5, 7);
	*year = std::stoi(_year);
	*percent = std::stoi(_percent);
}

void fillArrays(std::vector<double> *binE_, double * binB, double * binw, std::vector<double> * binI_, double * lat, double yield[][4])
{
	//{intensities for M10 downward proton flux in  m^2(s sr MeV)^-1 }
	double binE[31];
	double binI[31];
	binI[0] = 0.92;
	binI[1] = 0.98;
	binI[2] = 1.09;
	binI[3] = 1.26;
	binI[4] = 1.39;
	binI[5] = 1.32;
	binI[6] = 1.14;
	binI[7] = 0.928;
	binI[8] = 0.724;
	binI[9] = 0.511;
	binI[10] = 0.37;
	binI[11] = 0.241;
	binI[12] = 0.163;
	binI[13] = 0.102;
	binI[14] = 0.0614;
	binI[15] = 0.039;
	binI[16] = 0.0223;
	binI[17] = 0.0136;
	binI[18] = 0.00762;
	binI[19] = 0.00396;
	binI[20] = 0.0022;
	binI[21] = 0.00118;
	binI[22] = 0.000767;
	binI[23] = 0.000477;
	binI[24] = 0.000285;
	binI[25] = 0.000154;
	binI[26] = 7.93E-5;
	binI[27] = 4.48E-5;
	binI[28] = 2.6E-5;
	binI[29] = 1.4E-5;
	binI[30] = 8.5E-6;
	
	binE[0] = (0.07+0.10)/2.0;       //{Kinetic energy of AMS bins in GeV}
	binE[1] = (0.10+0.15)/2.0;
	binE[2] = (0.15+0.22)/2.0;
	binE[3] = (0.22+0.31)/2.0;
	binE[4] = (0.31+0.44)/2.0;
	binE[5] = (0.44+0.62)/2.0;
	binE[6] = (0.62+0.85)/2.0;
	binE[7] = (0.85+1.15)/2.0;
	binE[8] = (1.15+1.54)/2.0;
	binE[9] = (1.54+2.02)/2.0;
	binE[10] = (2.02+2.62)/2.0;
	binE[11] = (2.62+3.38)/2.0;
	binE[12] = (3.38+4.31)/2.0;
	binE[13] = (4.31+5.45)/2.0;
	binE[14] = (5.45+6.86)/2.0;
	binE[15] = (6.86+8.60)/2.0;
	binE[16] = (8.60+10.73)/2.0;
	binE[17] = (10.73+13.34)/2.0;
	binE[18] = (13.34+16.55)/2.0;
	binE[19] = (16.55+20.48)/2.0;
	binE[20] = (20.48+25.29)/2.0;
	binE[21] = (25.29+31.20)/2.0;
	binE[22] = (31.20+38.43)/2.0;
	binE[23] = (38.43+47.30)/2.0;
	binE[24] = (47.30+58.16)/2.0;
	binE[25] = (58.16+71.48)/2.0;
	binE[26] = (71.48+87.79)/2.0;
	binE[27] = (87.79+107.78)/2.0;
	binE[28] = (107.78+132.27)/2.0;
	binE[29] = (132.27+162.29)/2.0;
	binE[30] = (162.29+199.06)/2.0;

	binB[0] = 0.07;       //{Kinetic energy of AMS bins BORDERS in GeV}
	binB[1] = 0.10;
	binB[2] = 0.15;
	binB[3] = 0.22;
	binB[4] = 0.31;
	binB[5] = 0.44;
	binB[6] = 0.62;
	binB[7] = 0.85;
	binB[8] = 1.15;
	binB[9] = 1.54;
	binB[10] = 2.02;
	binB[11] = 2.62;
	binB[12] = 3.38;
	binB[13] = 4.31;
	binB[14] = 5.45;
	binB[15] = 6.86;
	binB[16] = 8.60;
	binB[17] = 10.73;
	binB[18] = 13.34;
	binB[19] = 16.55;
	binB[20] = 20.48;
	binB[21] = 25.29;
	binB[22] = 31.20;
	binB[23] = 38.43;
	binB[24] = 47.30;
	binB[25] = 58.16;
	binB[26] = 71.48;
	binB[27] = 87.79;
	binB[28] = 107.78;
	binB[29] = 132.27;
	binB[30] = 162.29;
	binB[31] = 199.06;

	//{bin width}
	binw[0] = (-0.07+0.10);       
	binw[1] = (-0.10+0.15);
	binw[2] = (-0.15+0.22);
	binw[3] = (-0.22+0.31);
	binw[4] = (-0.31+0.44);
	binw[5] = (-0.44+0.62);
	binw[6] = (-0.62+0.85);
	binw[7] = (-0.85+1.15);
	binw[8] = (-1.15+1.54);
	binw[9] = (-1.54+2.02);
	binw[10] = (-2.02+2.62);
	binw[11] = (-2.62+3.38);
	binw[12] = (-3.38+4.31);
	binw[13] = (-4.31+5.45);
	binw[14] = (-5.45+6.86);
	binw[15] = (-6.86+8.60);
	binw[16] = (-8.60+10.73);
	binw[17] = (-10.73+13.34);
	binw[18] = (-13.34+16.55);
	binw[19] = (-16.55+20.48);
	binw[20] = (-20.48+25.29);
	binw[21] = (-25.29+31.20);
	binw[22] = (-31.20+38.43);
	binw[23] = (-38.43+47.30);
	binw[24] = (-47.30+58.16);
	binw[25] = (-58.16+71.48);
	binw[26] = (-71.48+87.79);
	binw[27] = (-87.79+107.78);
	binw[28] = (-107.78+132.27);
	binw[29] = (-132.27+162.29);
	binw[30] = (-162.29+199.06);

	lat[0] = 14.361512;       //{Kinetic energy of AMS bins in GeV}
	lat[1] = 25.007833;
	lat[2] = 32.461745;
	lat[3] = 38.624833;
	lat[4] = 44.048626;
	lat[5] = 48.985500;
	lat[6] = 53.576426;
	lat[7] = 57.910049;
	lat[8] = 62.046813;
	lat[9] = 66.030518;
	lat[10] = 69.894490;
	lat[11] = 73.665177;
	lat[12] = 77.364375;
	lat[13] = 81.010701;
	lat[14] = 84.620621;
	lat[15] = 88.209215;
	
	yield[0][0] = 7.983E-1;
	yield[1][0] = -6.985E-3;
	yield[2][0] = 3.593E-6;
	yield[3][0] = -1.950E-9;
	yield[0][1] = 2.859E+0;
	yield[1][1] = 1.188E-2;
	yield[2][1] = -1.516E-5;
	yield[3][1] = 7.969E-9;
	yield[0][2] = -2.060E+0;
	yield[1][2] = -9.264E-3;
	yield[2][2] = 1.522E-5;
	yield[3][2] = -8.508E-9;
	yield[0][3] = 5.654E-1;
	yield[1][3] = 2.169E-3;
	yield[2][3] = -4.214E-6;
	yield[3][3] = 2.491E-9;
	
	
	(*binI_) = std::vector<double>(std::begin(binI), std::end(binI));//->reserve(31);
	(*binE_) = std::vector<double>(std::begin(binE), std::end(binE));//->reserve(31);
}