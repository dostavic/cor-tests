#include <stdio.h>
#include <stdio_ext.h>

#include "DataVectors.hpp"

DataVectors::DataVectors(InputPhysicalData *ipd) : throughputFunc(ipd->sd->yearDoy.rigidityStep * 10, ipd->sd->numberOfDirections, ipd->sd->yearDoy.rigidityStep, 100), ipd(ipd)
{
	for(unsigned int i = 0; i < ipd->sd->numberOfDirections; i++)
	{
		matrix.emplace_back();
		outfilData.emplace_back();
		buffer.emplace_back( new char[256] );
		for(int j=0;j<256;j++)
		{
			buffer[i][j] = '\0';
		}
		bandVector.emplace_back();
	}
	integr1O.resize(ipd->sd->numberOfDirections);
	for(int ii=0; ii < binNum;ii++)// do {sirka}
	{
		for (int jj=0; jj < binNum;jj++)// do {dlzka}
		{
			mapaasym[ii][jj] = 0;
			mapaend[ii][jj] = 0;
		}
	}
}

void DataVectors::createMaps()
{
	for(unsigned int i=0;i<matrix.size();i++)
	{
		for(unsigned int j=0;j<matrix.at(i).size();j++)
		{
			CoordinatesAndValues* current = &(matrix.at(i).at(j));
			// std::cout << "current: " << current->ilatend << "\n";
			//odignoruj intervaly <-90,-87.5> a <87.5,90>
			if((current->ilatend>=0)&&(current->ilatasym>=0)&&(current->ilatend<binNum)&&(current->ilatasym<binNum))
			{
				mapaend[current->ilatend][current->ilonend] += current->val;
				mapaasym[current->ilatasym][current->ilonasym] += current->val;
			}
		}
	}
}

void DataVectors::writeMaps()
{
	FILE *gg;
	gg = fopen(ipd->sd->map.c_str(), "w");
	if(gg!=NULL)
	{
		for(int ii=1;ii<=binNum;ii++)
		{
			for(int jj=1;jj<=binNum;jj++)
			{
				fprintf(gg, "%f %d %.10lf %.10lf\n", (ii*2.5)-90,(jj-1)*5,mapaend[ii-1][jj-1],mapaasym[ii-1][jj-1]);
			}
		}
		fclose(gg);
	}
}

#define OPTIMIZED_UNSAFE_READING //unsafe only 

void DataVectors::readOufil(const unsigned int index)
{
	std::string s = ipd->sd->outfilPrefix + "outfil_";
	s += std::to_string(index);
	char *buffer_ = buffer[index].get();
	int numLines = 0;
	FILE *aa = fopen(s.c_str(), "r");
	//__fsetlocking (aa, FSETLOCKING_BYCALLER);
#ifdef OPTIMIZED_UNSAFE_READING
	//__fsetlocking (aa, FSETLOCKING_BYCALLER);
	static const char colsToParseSize = 7;
	static const char colsToParse[colsToParseSize] = {1, 0, 0, 1, 1, 1, 1};
	static const char valsSize = 5;
	double vals[valsSize];
#else
	double rig_f = 0, lat_end_p_f = 0, lon_end_p_f = 0, lat_asym_f = 0, lon_asym_f = 0;
#endif
	if(aa!=NULL)
	{
		while(fgets(buffer_, 256, aa)!=NULL )
		{
			numLines++;
		}
	}
	else
	{
		std::cout<<"Could not open " << s << ", exiting!\n";
		exit(-1);
	}
	fseek(aa, 0, SEEK_SET);
	for (int k=0;k<12;k++)
	{
		if(fgets(buffer_, 256, aa)==NULL)
		{
			std::cout << "Too few lines" << numLines << ", exiting!\n";
			exit(-1);
		}
	}
	int footerLines = 3;
	int headerLines = 12;
	if(numLines == 13)
	{
		footerLines = 0;
	}
	std::vector<OutfilData>* currItem = &(outfilData[index]);
	const int bodyLines = numLines - headerLines - footerLines;
#ifdef OPTIMIZED_UNSAFE_READING
	currItem->reserve(bodyLines);
#endif
	for (int j = 0; j < bodyLines; j++)
	{
#ifdef OPTIMIZED_UNSAFE_READING
		char line[256];
		if(fgets (line, 256, aa))
		{
			char *saveptr1;
			char * pch = strtok_r (line, " ", &saveptr1);
			for(unsigned char i = 0, outIdx = 0; i < colsToParseSize; i++)
			{
				if(colsToParse[i])
				{
					vals[outIdx] = strtod(pch, NULL);
					outIdx++;
				}
				pch = strtok_r(NULL, " ", &saveptr1);
			}
		}
		currItem->emplace_back(vals[0],vals[1],vals[2],vals[3],vals[4]);
#else
		int ret = fscanf(aa, "%lf %*s %*s %lf %lf %lf %lf %*s %*s \n", &rig_f,&lat_end_p_f,&lon_end_p_f,&lat_asym_f,&lon_asym_f);
		if(ret != 5)
		{
			fprintf(stdout,"%lf %lf %lf %lf %lf \n", rig_f,  lat_end_p_f, lon_end_p_f, lat_asym_f, lon_asym_f);
			std::cout << numLines << " " << headerLines << " " << footerLines  << "\n";
			std::cout << j << " " << (j + headerLines) << "\n";
			std::cout<<"Invalid file structure, exiting! " << ret << "\n";
			exit(-1);
		}
		currItem->emplace_back(rig_f,lat_end_p_f,lon_end_p_f,lat_asym_f,lon_asym_f);
#endif
	}
	if(fgets(buffer_, 256, aa)==NULL)
	{
	}
	if(fscanf(aa, "%256[^\n]%*c", buffer_) == 0)
	{
		std::cout<<"Invalid file structure, exiting!\n";
		exit(-1);
	}
	fclose(aa);
}

void DataVectors::writeSpectraBands()
{
	FILE *zz;
	zz = fopen(ipd->sd->spectraBands.c_str(), "w");
	if(zz!=NULL)
	{
		for (unsigned int ii = 0; ii < bandVector.size();ii++)
		{
			for (unsigned int jj = 0; jj < bandVector[ii].size();jj++)
			{
				fprintf(zz, "%.2lf %.2lf ", bandVector[ii][jj].start, bandVector[ii][jj].bandWidth);
			}
			fprintf(zz, "\n");
		}
		fclose(zz);
	}
}

void DataVectors::writeIntegr2sum()
{
	FILE *zz;
	zz = fopen(ipd->sd->integr2sum.c_str(), "w");
	unsigned int numberOfDirections = ipd->sd->numberOfDirections;
	if(zz!=NULL)
	{
		float integr2 = 0;
		for (unsigned int ii = 0; ii < numberOfDirections; ii++)
		{
			integr2 += integr1O[ii];
		}
		if(numberOfDirections != 1)
		{
			integr2 = integr2/(numberOfDirections / (2 * M_PI));
		}
		fprintf(zz, "%f\n", integr2);
		fclose(zz);
	}
}

void DataVectors::writeCAY(double *lat)
{
	FILE *dd,*ff;
	ff = fopen(ipd->sd->cutOffRigPrefix.c_str(), "w");
	dd = fopen(ipd->sd->intensityYieldPrefix.c_str(), "w");
	int index = 1;
	int nOD = ipd->sd->numberOfDirections;
	if(nOD == 577)
	{
		if(dd!=NULL)
		{
			fprintf(dd, "%d %d %f\n", -1, -1, integr1O[index-1]);
		}
		if(ff!=NULL)
		{
			fprintf(ff, "%f %d %s\n", 0., 0, buffer[index-1].get());
		}
		index++;
	}
	for (int ii=0 ;ii < 16;ii++ )//do   {dat 16 ked sa dopocita}
	{
		for (int jj =0 ;jj < 36; jj++ )
		{ 
			if(dd!=NULL)
			{
				fprintf(dd, "%d %d %f\n", ii, jj, integr1O[index-1]);
			}
			if(ff!=NULL)
			{
				if(nOD == 1)
				{
					fprintf(ff, "%f %d %s\n", 0., 0, buffer[index-1].get());
				}
				else
				{
					fprintf(ff, "%f %d %s\n",lat[ii], jj  * 10 , buffer[index-1].get());
				}
			}
			if(index >= nOD)
			{
				break;
			}
			index++;
		}
		if(index >= nOD)
		{
			break;
		}
	}
	if(dd!=NULL)
	{
		fclose(dd);
	}
	if(ff!=NULL)
	{
		fclose(ff);
	}
}
double DataVectors::computeIntensity(const double rigLoc2)
{
	double intens2 = 0;
	double Tkin = sqrt((T0pow2)+(rigLoc2*rigLoc2))-T0;
	double delTkin = (sqrt((T0pow2)+((rigLoc2+ipd->rigStepOrig)*(rigLoc2+ipd->rigStepOrig))) - T0) - Tkin;  // {krok 0.01 GV v MeV-och}
	double pMeV = delTkin/0.001;
	if(ipd->variableBinWidth == 0.0 || ipd->usingAMS /*nenasiel rok a pouzivame AMS*/)
	{
		for (unsigned int k=0; k < ipd->binE.size() - 1;k++)
		{
			if ( (Tkin>ipd->binE.at(k)) && (Tkin<ipd->binE.at(k+1)) )
			{
				intens2 = ipd->binI[k] + ((ipd->binI[k+1]-ipd->binI[k]) * (Tkin - ipd->binE[k])/(ipd->binE[k+1]-ipd->binE[k]));
				break;
			}
		}
	}
	else
	{
		unsigned int k = trunc(rigLoc2 * ipd->variableBinWidth);
		intens2 = ipd->binI[k] + ((ipd->binI[k+1]-ipd->binI[k]) * (Tkin- ipd->binE[k])/(ipd->binE[k+1]-ipd->binE[k]));
	}
	return intens2*pMeV;//return
}
int inline truncLat(double lat)
{
	return (int) trunc((lat + 90) / 2.5) - 1;
}
int inline truncLon(double lon)
{
	return (int) trunc(lon / 5.0);
}
void DataVectors::processData(const unsigned int index)
{
	std::vector<OutfilData> *oufilLoc = &(outfilData[index]);
	std::cout  << "\n" << "Size oufiloc: " << oufilLoc->size() << "\n";

	double integr1 = 0;
	if(oufilLoc->size()>1)
	{
		double rigLoc = oufilLoc->at(0).rig;
		double rigidityStep = ipd->rigStepOrig;
		rigidityStep = rigidityStep + rigidityStep/100;
		double rigLocNext = oufilLoc->at(1).rig;
		double start = rigLoc, bandWidth = ipd->rigStepOrig;
		for(unsigned int idx = 0; idx < oufilLoc->size(); idx++)
		{
			OutfilData *currIdx = &(oufilLoc->at(idx));
			rigLoc = currIdx->rig;
			throughputFunc.placeRigidity(index, rigLoc);
			rigLocNext = (idx + 1)<oufilLoc->size() ? oufilLoc->at(idx+1).rig : std::numeric_limits<int>::min();
			if (( rigLocNext - rigLoc ) < rigidityStep)
			{
				bandWidth = rigLocNext - start;
			}
			else
			{
				bandVector[index].emplace_back(start, bandWidth);
				start = rigLocNext;
				bandWidth = ipd->rigStepOrig;

				// if(idx == 10)
					// std::cout << "BandWidth: " << bandWidth << "\n";
					
			}
			int ilatend = truncLat(currIdx->lat_end_p);
			int ilonend = truncLon(currIdx->lon_end_p);
			int ilatasym = truncLat(currIdx->lat_asym);
			int ilonasym = truncLon(currIdx->lon_asym);
			double intens2pMeV = computeIntensity(rigLoc);
			integr1 += intens2pMeV;
			matrix.at(index).emplace_back(intens2pMeV,ilatend,ilonend,ilatasym,ilonasym);
		}
		int floatToIntMult = (1 / ipd->rigStepOrig);
		for(int i = (rigLoc + ipd->rigStepOrig) * floatToIntMult; i <= 100 * floatToIntMult; i++)
		{
			integr1 += computeIntensity((double) i / floatToIntMult);
		}
		bandVector.at(index).emplace_back(start, ipd->rigStepOrig);
	}
	integr1O[index] = integr1;
	// for (int i = 0; i < bandVector.size(); ++i) {
    // Iterate over the inner vector
    	// for (int j = 0; j < bandVector[i].size(); ++j) {
        // Print the start and bandWidth values of the Band object
        	// std::cout << "Band " << i << "," << j << " start: " << bandVector[i][j].start << std::endl;
        	// std::cout << "Band " << i << "," << j << " bandWidth: " << bandVector[i][j].bandWidth << std::endl;
    	// }
	// }
}