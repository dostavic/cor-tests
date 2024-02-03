#include <cstdio>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <cstring>
#include <deque>
#include <queue>
#include <filesystem>

#include "infilGenerator.hpp"

#define Pi 3.14159265358979
#define pipol Pi/2.0

void getLocalRotations(float longitude, float lat1, float geolat, float geolong, float *latloc, float *longloc)
{
	float a11,a12,a13,a21,a22,a23,a31,a32,a33,theta,psi,phi,x1,x2,y1,y2,z1,z2;
	//lat,longitude - uhly v lokalnej sustave - rotacia v lokalnej sustave}
	x1 = cos(longitude)*sin(pipol-lat1);//90 - lat1 pretoze v sferickych suradniciach je latitude colatitude}
	y1 = sin(longitude)*sin(pipol-lat1);  //http://mathworld.wolfram.com/SphericalCoordinates.html}
	z1 = cos(pipol-lat1);

	std::cout << x1 << std::endl << y1 << std::endl << z1 << std::endl;

	//Rotacia sustavy, na severnom pole nezrotovana - rotacia celej sustavy okolo Zeme}
	theta = (90-geolat)*(Pi/180);    //otocenie na sirku 36.10}  { Norikura  36.10    137.55  }
	phi = 0.0*(Pi/180);
	psi = (90-geolong)*(Pi/180);   //pokus 4}
	//Euler angles: http://mathworld.wolfram.com/EulerAngles.html}
	a11 = (cos(psi)*cos(phi)) - (cos(theta)*sin(phi)*sin(psi));
	a12 = (cos(psi)*sin(phi)) + (cos(theta)*cos(phi)*sin(psi));
	a13 = sin(psi)*sin(theta);

	a21 = (-sin(psi)*cos(phi)) - (cos(theta)*sin(phi)*cos(psi));
	a22 = (-sin(psi)*sin(phi)) + (cos(theta)*cos(phi)*cos(psi));
	a23 = cos(psi)*sin(theta);

	a31 = sin(theta)*sin(phi);
	a32 = -sin(theta)*cos(phi);
	a33 = cos(theta);
	//http://mathworld.wolfram.com/RotationMatrix.html}
	x2 = (x1*a11) + (y1*a12) + (z1*a13);
	y2 = (x1*a21) + (y1*a22) + (z1*a23);
	z2 = (x1*a31) + (y1*a32) + (z1*a33);
	*longloc = atan(y2/x2)*(180/Pi);    //Revizia 4. }
	*latloc  = acos(z2/1)*(180/Pi);     //Revizia 4. }
	//arctan problem - http://hyperphysics.phy-astr.gsu.edu/hbase/ttrig.html}
	if ((x2<0)&&(y2>0)) *longloc += 180;   //II quadrant}
	if ((x2<0)&&(y2<0)) *longloc += 180;   //III quadrant}
	if ((x2>0)&&(y2<0)) *longloc += 360;   //IV quadrant}

	*latloc = 90 - (*latloc);    //revizia 5.}
}
void readOMNIVector(MagFieldOutfil *castData , int *error)
{
	Timestamp *date = &(castData->date);
	Timestamp *endDate = &(castData->endDate);
	std::vector<T05Indices> *tIndices = &(castData->tIndices);
	const unsigned int numberOfHours = castData->numberOfHours;
	FILE * hh = fopen("OMNI_W1_W6.dat", "r");
	*error = 0;
	std::vector<OmniLine> lines;
	if(hh!=NULL)
	{
		T05Indices tempI;
		unsigned int year;
		unsigned short doy, hour;
		Timestamp tempDate(year, doy, hour);
		while(fscanf(hh, "%d %hu %hu %f %f %f %f %f %f",&year,&doy,&hour,&(tempI.W1),&(tempI.W2),&(tempI.W3),&(tempI.W4),&(tempI.W5),&(tempI.W6)) != EOF)
		{
			tempDate.fromYDH(year, doy, hour);
			if(tempDate > *endDate)
			{
				break;
			}
			if(tempDate >= *date)
			{
				for(Timestamp iterDate = (castData->date); iterDate <= (castData->endDate); iterDate.addHours(castData->intervalDur))
				{
					if(iterDate == tempDate)
					{
						lines.emplace_back(tempDate.getYear(), tempDate.getDoy(), tempDate.getHour(), tempI);
					}
				}
			}
		}
		fclose(hh);
	}
	else
	{
		printf("Error opening file 'OMNI_W1_W6.dat', terminating\n");
		exit(7);
	}
	//std::cout << "Lines size: " << lines.size() << "\n";
	Timestamp tempDate = (castData->date);
	for(unsigned int j = 0; j < numberOfHours; j++)
	{
		for(unsigned int i = 0; i < lines.size(); i++)
		{
			Timestamp *iterDate = &(lines[i].date);
			if(*iterDate == tempDate)
			{
				lines[i].indices.success = LineState::FOUND;
				tIndices->at(j) = lines[i].indices;
			}
		}
		tempDate.addHours(castData->intervalDur);
	}
	for(unsigned int i = 0; i < numberOfHours; i++)
	{
		if(tIndices->at(i).success == LineState::NOT_FOUND || tIndices->at(i).hasZero())
		{
			*error |= State::W_INDICES;
		}
		//tIndices->at(i).print();
	}

	// for(int i = 0; i < 49; i++)
	// 	tIndices->at(i).print();
	// std::cout << "Error" << *error << std::endl;
}

void skipLine(FILE *ee)
{
	static char fakeInput[500];
	if(fgets(fakeInput, 500, ee) == NULL)
	{
		exit(1);
	}
}
void readParmodVector(MagFieldOutfil *castData , int *error)
{
	Timestamp *date = &(castData->date);
	Timestamp *endDate = &(castData->endDate);
	std::vector<MagnetosphereData> *magVector = &(castData->magData);
	const unsigned int numberOfHours = castData->numberOfHours;
	FILE * ee = fopen("parmod_new.dat", "r");
	skipLine(ee);
	*error = 0;
	std::vector<ParmodLine> lines;
	lines.reserve(numberOfHours);
	if(ee!=NULL)
	{
		MagnetosphereData magData;
		Timestamp tempDate(0);
		unsigned int year;
		unsigned short doy, hour, month, day;
		//year;month;day;hour;doy;By;Bz;Pdyn;dst;bitwise or of missing columns before interpolation (4;8;2;16)
		while(fscanf(ee,"%d %hu %hu %hu %hu %f %f %f %d %hu",&year,&month,&day,&hour,&doy,&(magData.byimf),&(magData.bzimf),&(magData.pdyn),&(magData.dst),&(magData.mPars))!=EOF)
		{
			tempDate.fromYDH(year, doy, hour);
			if(tempDate > *endDate)
			{
				break;
			}
			if(tempDate >= *date)
			{
				for(Timestamp iterDate = (castData->date); iterDate <= (castData->endDate); iterDate.addHours(castData->intervalDur))
				{
					if(iterDate == tempDate)
					{
						lines.emplace_back(tempDate.getYear(), tempDate.getDoy(), tempDate.getHour(), magData);
					}
				}
			}
		}
		fclose(ee);
	}
	else
	{
		printf("Error opening file 'parmod_new.dat', terminating\n");
		exit(6);
	}
	for(unsigned int i = 0; i < lines.size(); i++)
	{
		*error |= lines[i].magData.mPars;
		magVector->at(i) = lines[i].magData;
	}

	// for(int i = 0; i < 49; i++)
	// 	magVector->at(i).print();
	// std::cout << "Error" << *error << std::endl;
}
void readOMNI(Timestamp *date, T05Indices *indices,int *error)
{
	FILE * hh = fopen("OMNI_W1_W6.dat", "r");
	int YEAR,DOY2,HR;
	bool succes = false;
	*error = 0;
	if(hh!=NULL)
	{
		while(fscanf(hh, "%d %d %d %f %f %f %f %f %f",&YEAR,&DOY2,&HR,&(indices->W1),&(indices->W2),&(indices->W3),&(indices->W4),&(indices->W5),&(indices->W6)) != EOF)
		{
			if ( (YEAR == date->getYear()) && (date->getDoy() == DOY2) && (date->getHour() == HR) )
			{
				succes = true;
				break;
			}
		}
		fclose(hh);
	}
	else
	{
		printf("Error opening file 'OMNI_W1_W6.dat', terminating\n");
		exit(7);
	}
	if(succes==false)
	{
		indices->W1 = 0;
		indices->W2 = 0;
		indices->W3 = 0;
		indices->W4 = 0;
		indices->W5 = 0;
		indices->W6 = 0;
		*error |= State::W_INDICES;
	}
	if(indices->W1 == 0 || indices->W2 == 0 || indices->W3 == 0 || indices->W4 == 0 || indices->W5 == 0 || indices->W6 == 0)
	{
		*error |= State::W_INDICES;
	}

	indices->print();
}
void readParmod(Timestamp *date,MagnetosphereData *magData,int *error)
{
	FILE * ee = fopen("parmod_new.dat", "r");
	skipLine(ee);
	int YEAR,HR,DOY2;
	//bool succes = false;
	*error = 0;
	magData->pdyn = 0;
	magData->byimf = 0;
	magData->bzimf = 0;
	magData->dst = 0;
	if(ee!=NULL)
	{
		unsigned short month,day;
		//while(fscanf(ee,"%d %hu %hu %hu %hu %f %f %f %d %d",&year,&month,&day,&hour,&doy,&(magData.byimf),&(magData.bzimf),&(magData.pdyn),&(magData.dst),&(magData.mPars))!=EOF)
		while(fscanf(ee,"%d %hu %hu %d %d %f %f %f %d %hu",&YEAR,&(month),&(day),&HR,&DOY2,&(magData->byimf),&(magData->bzimf),&(magData->pdyn),&(magData->dst),&(magData->mPars))!=EOF)
		{
			if ((YEAR == date->getYear()) && (date->getDoy() == DOY2) && (date->getHour() == HR))
			{
				*error |= magData->mPars;
				break;
			}
		}
		std::cout << "Month diff: " << month - date->getMonth() << " day diff: " << day - date->getDay() << " !!!\n";
		std::cout << "Error: " << *error << std::endl;
		fclose(ee);
	}
	else
	{
		printf("Error opening file 'parmod_new.dat', terminating\n");
		exit(6);
	}
}

template <typename T, int MaxLen, typename Container=std::deque<T>>
class FixedQueue : public std::queue<T, Container> 
{
public:
	void push(const T& value) 
	{
		if (this->size() == MaxLen) 
		{
			this->c.pop_front();
		}
		std::queue<T, Container>::push(value);
    }
	
	T at(int idx)
	{
		return this->c.at(idx);
	}
	
	constexpr static unsigned int getMaxLen()
	{
		return MaxLen;
	}
	constexpr static int getLastIdx()
	{
		return MaxLen - 1;
	}
};

struct CoordinateVal
{
	float lat,lon,val, diff;
	CoordinateVal(float lat,float lon,float val,float diff) : lat(lat), lon(lon), val(val), diff(diff) {}
	
	void print()
	{
		std::cout << lat << " " << lon << " " << val <<  " " << diff << "\n";
	}
};

void optimizeRigidity(GeographicLocation *geoLoc, RigidityData *rigData, int dst)
{
	float *rigstart = &(rigData->rigstart);
	float *rigend = &(rigData->rigend);
	float geolat = geoLoc->geolat;
	float geolong = geoLoc->geolong;
	float radius = geoLoc->radius;
	//std::cout << geolat << " " << geolong << " " << radius << "\n";

	// std::filesystem::path currentPath = std::filesystem::current_path();
    // std::cout << "Curent path: " << currentPath.string() << std::endl;


	FILE * ff = fopen("vertical_rig_r_1_06.dat", "r");
	FixedQueue<CoordinateVal, 2> pointsQueue;

	for(unsigned i = 0; i < pointsQueue.getMaxLen(); i++)
	{
		pointsQueue.push(CoordinateVal(-100, 0, 0, 100));
	}

	// std::cout << "Hloo1" << std::endl;
	// 	for(int i = 0; i < pointsQueue.getMaxLen(); i++)
	// 		pointsQueue.at(i).print();

	if(ff!=NULL)
	{
		float lat2,lon2,rig2;
		while(fscanf(ff, "%f %f %f",&lat2,&lon2,&rig2) != EOF)
		{
			float diflat,diflon,diff;
			diflat = fabs(lat2-geolat);
			diflon = fabs(lon2-geolong);
			diff = sqrt((diflat*diflat)+(diflon*diflon));
			if (diff <= pointsQueue.at(pointsQueue.getLastIdx()).diff)
			{
				float rigRound = round((0.9*rig2)*10.0)/10.0;
				pointsQueue.push(CoordinateVal(lat2, lon2, rigRound, diff));

				// std::cout << "Hloo2" << std::endl;
				// for(int i = 0; i < pointsQueue.getMaxLen(); i++)
				// 	pointsQueue.at(i).print();
			}
		}
		fclose(ff);
		
		// std::cout << "Hloo" << std::endl;
		// for(int i = 0; i < pointsQueue.getMaxLen(); i++)
		// 	pointsQueue.at(i).print();
			
	}
	else
	{
		printf("Error opening file 'vertical_rig_r_1_06.dat', terminating\n");
		exit(5);
	}
	
	if(pointsQueue.at(0).lat == -100)
	{
		*rigstart = pointsQueue.at(1).val;
	}
	else if(pointsQueue.at(1).lat == -100)
	{
		*rigstart = pointsQueue.at(0).val;
	}
	else
	{
		*rigstart = (pointsQueue.at(0).val < pointsQueue.at(1).val) ? pointsQueue.at(0).val : pointsQueue.at(1).val;
		// std::cout << "Rigstart: " << *rigstart << std::endl;
	}
	
	if(dst < -100)// ked je velka burka, rigidita je zle odhadnuta, toto je docastne riesenie
	{
		*rigstart = (*rigstart) / 2;
	}
	
	(*rigend) = 2.5*(*rigstart);
	
	if(dst < -100)// ked je velka burka, rigidita je zle odhadnuta, toto je docastne riesenie
	{
		(*rigend) = 5*(*rigstart);
	}
	
	if ((*rigend)>20)
	{
		(*rigend)=20;
	}
	if (abs(geolat)>50)
	{
		(*rigstart) = 0.01;
		(*rigend) = 10;
	}
	if ((*rigend)<10)
	{
		(*rigend) = 10;
	}
	if (radius>1.01) 
	{
		*rigstart = (*rigstart)*0.64;
		(*rigstart) = round((*rigstart)*100)/100;
	}
	if (radius>1.3) 
	{
		(*rigstart) = 0.01;
	}
	std::cout << (*rigstart) << " "<< (*rigend) << "\n";
}
void Arguments::parseArguments(int argc, char** argv)
{
	if(argc >= 3)
	{
		inputFile = argv[1];
		filenamePrefix = argv[2];
		
		if(argc == 4)
		{
			if(strcmp(argv[3],"trajectory") == 0)
			{
				infilKind = InfilKind::TRAJECTORY;
			}else if(strcmp(argv[3],"mag") == 0)
			{
				infilKind = InfilKind::MAG_FIELD;
			}
		}
	}
	else
	{
		printf("Too few arguments, usage executable inputFile filePrefix calculationKind\n");
		printf("inputFile - file that will be used as input for this program, it has to have specific format based on calculationKind parameter\n");
		printf("filePrefix - prefix that will be prepended to the output of this program, all directories in the path have to exist\n");
		printf("calculationKind - blank for default, 'trajectory' for trajectory calculation or 'mag' for magnetic field calculation\n");
		exit(1);
	}
}
void fillArrays(float * lat)
{
	lat[0] = 90.0 - 14.361512;     //sirka od roviny na Zemi, tj. 14.361512 je zenitovy uhol
	lat[1] = 90.0 - 25.007833;
	lat[2] = 90.0 - 32.461745;
	lat[3] = 90.0 - 38.624833;
	lat[4] = 90.0 - 44.048626;
	lat[5] = 90.0 - 48.985500;
	lat[6] = 90.0 - 53.576426;
	lat[7] = 90.0 - 57.910049;
	lat[8] = 90.0 - 62.046813;
	lat[9] = 90.0 - 66.030518;
	lat[10] = 90.0 - 69.894490;
	lat[11] = 90.0 - 73.665177;
	lat[12] = 90.0 - 77.364375;
	lat[13] = 90.0 - 81.010701;
	lat[14] = 90.0 - 84.620621;
	lat[15] = 90.0 - 88.209215;
}