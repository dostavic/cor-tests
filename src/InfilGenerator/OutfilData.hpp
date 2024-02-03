#ifndef OUTFILDATA_HPP
#define OUTFILDATA_HPP

#include <string>
#include <vector>
#include <cmath>

#include "Timestamp.hpp"

/**
 * @brief Enum containing model versions.
 */
enum Version : int16_t
{
	T96 = 0, /**< Version Tsyganenko 96. */
	T05 = 1, /**< Version Tsyganenko 05. */
	T96_LCR = 2, /**< Version Tsyganenko 96 lowest cut-off rigidity. */
	T05_LCR = 3, /**< Version Tsyganenko 05 lowest cut-off rigidity. */
	H = 4, /**< Historic version. */
	T96_MAG = 5, /**< Version Tsyganenko 96 magnetic model. */
	T05_MAG = 6, /**< Version Tsyganenko 05 magnetic model. */
	IGRF = 7, /**< Version IGRF magnetic model. */
	CALS10k_2 = 8, /**< Version CALS10k.2 internal historical magnetic model. */
};
/**
 * @brief Eneum containing type of infil to create.
 */
enum InfilKind : int16_t
{
	NORMAL, /**< Generate normal infil. */
	TRAJECTORY, /**< Generate infil for trajectory calculation. */
	MAG_FIELD /**< Generate infil for magnetic field simulation. */
};
class LineState : public Printable
{
public:
	enum Value : uint8_t
	{
		FOUND,
		NOT_FOUND,
		FAULTY,
	};
	LineState() = default;
	constexpr LineState(Value aFruit) : value(aFruit) { }

	constexpr bool operator==(LineState a) const { return value == a.value; }
	constexpr bool operator!=(LineState a) const { return value != a.value; }
	std::string toString()
	{ 
		std::string result;
		if(value == Value::FOUND)
		{
			result = std::string("FOUND");
		}
		else if(value == Value::NOT_FOUND)
		{
			result = std::string("NOT_FOUND");
		}
		else if(value == Value::FAULTY)
		{
			result = std::string("FAULTY");
		}
		return result;
	}
	void print() override
	{
		std::cout << toString() << "\n";
	}
private:
  Value value;
};

/**
 * @class RigidityData
 * @author Daniel
 * @date 25/02/19
 * @file OutfilData.hpp
 * @brief Struct holding rigidity start, end and step.
 */
struct RigidityData
{
	float rigstart, rigend, rigidityStep;
};
/**
 * @class GeographicLocation
 * @author Daniel
 * @date 25/02/19
 * @file OutfilData.hpp
 * @brief Geographic Latitude, longitude and altitude in Earth radii.
 */
struct GeographicLocation
{
	float radius, geolat, geolong;
};
/**
 * @class LocalLocation
 * @author Daniel
 * @date 25/02/19
 * @file OutfilData.hpp
 * @brief Local halfsphere converted to global coordinates,
 */
struct LocalLocation
{
	float latloc, longloc;
};

/**
 * @class MagnetosphereData
 * @author Daniel
 * @date 25/02/19
 * @file OutfilData.hpp
 * @brief Data describing magnetosphere for date specified in Timestamp.
 */
struct MagnetosphereData : public Printable
{
	int dst;
	float pdyn,byimf,bzimf;
	//LineState success;
	unsigned short mPars;
	MagnetosphereData()
	{
		//dst = pdyn = byimf = bzimf = 0;
		dst = 0;
		pdyn = 2;
		byimf = 0;
		bzimf = 0;
		//success = LineState::NOT_FOUND;
	}
	MagnetosphereData(int dst, float pdyn,float byimf,float bzimf, unsigned short mPars) : dst(dst), pdyn(pdyn),byimf(byimf), bzimf(bzimf), mPars(mPars) {}
	void print() override
	{
		std::cout << "MagnetosphereData: " << dst << " " << pdyn << " " << byimf << " " << bzimf << " " << mPars << "\n";
	}
};

/**
 * @class T05Indices
 * @author Daniel
 * @date 25/02/19
 * @file OutfilData.hpp
 * @brief Indices for Tsyganenko05 model of external magnetic field.
 */
struct T05Indices : public Printable
{
	float W1,W2,W3,W4,W5,W6;
	LineState success;
	T05Indices()
	{
		W1 = W2 = W3 = W4 = W5 = W6 = 0;
		success = LineState::NOT_FOUND;
	}
	T05Indices(float W1,float W2,float W3,float W4,float W5,float W6, LineState success)
	: W1(W1), W2(W2), W3(W3), W4(W4), W5(W5), W6(W6), success(success) {}
	void print() override
	{
		std::cout << "T05Indices: " << W1 << " " << W2 << " " << W3 << " " << W4 << " " << W5 << " " << W6 << " " << success.toString() << "\n";
	}
	bool hasZero()
	{
		//todo mozno pocitat pocet nul a oznamovat kolko chyba
		return W1 == 0 && W2 == 0 && W3 == 0 && W4 == 0 && W5 == 0 && W6 == 0;
	}
};

/**
 * @class OutfilData
 * @author Daniel
 * @date 25/02/19
 * @file OutfilData.hpp
 * @brief Container with other data.
 */
struct OutfilData
{
public:
	GeographicLocation geoLoc;
	LocalLocation localLoc;
	bool generateInfils = true;
	int inputState, optimalizationLevel, numberOfDirections;
	Version version;
	/**
	 * @brief Writes infil.
	 * @param filenamePrefix Filename prefix 'infil_'.
	 * @param index Index of infil.
	 */
	virtual void writeData(std::string *filenamePrefix, int index) = 0;
	/**
	 * @brief Reads input file.
	 * @param inputFile Path to input file.
	 * @param infilKind Type of calculation (normal, trajectory).
	 */
	void readInput(std::string *inputFile);
protected:
	/**
	 * @brief Reads second line of input file.
	 * @param buffer Pointer to buffer.
	 * @param inputFile Name to input file.
	 * @param gg Pointer to open file.
	 */
	void readSecondLine(char *buffer, std::string *inputFile, FILE *gg);
	virtual void setRigidityStep(float rigidityStep);
	virtual void readInputImpl(char *buffer, FILE *gg, std::string *inputFile) = 0;
	const int bufferSize = 1024;
};

struct TrajectoryOutfil : public OutfilData
{
	Timestamp date;
	RigidityData rigidityData;
	MagnetosphereData magData;
	T05Indices tIndices;
	TrajectoryOutfil() : date(0) {} ;
	/**
	 * @brief Writes infil.
	 * @param filenamePrefix Filename prefix 'infil_'.
	 * @param index Index of infil.
	 */
	void writeData(std::string *filenamePrefix, int index) override;
protected:
	void setRigidityStep(float rigidityStep) override;
	void readInputImpl(char *buffer, FILE *gg, std::string *inputFile) override;
};
struct NormalOutfil : public TrajectoryOutfil
{
private:
	/**
	 * @brief Uses polynome of 4th order to get safe starting rigidity for all directions.
	 */
	void setRigidityStart(float geomag_latitude, float geomag_longitude);
	/**
	 * @brief Uses polynome of 6th order to get safe starting rigidity for all directions.
	 */
	void setRigidityStart2(float geomag_latitude, float geomag_longitude);
protected:
	void readInputImpl(char *buffer, FILE *gg, std::string *inputFile) override;
};
struct MagFieldOutfil : public OutfilData
{
	unsigned int intervalEnd;
	unsigned int intervalDur;
	float latitudeStep;
	float longitudeStep;
	std::vector<MagnetosphereData> magData;
	std::vector<T05Indices> tIndices;
	Timestamp date;
	Timestamp endDate;
	MagFieldOutfil() : date(0), endDate(0) { };
	unsigned int numberOfHours;
	void writeData(std::string *filenamePrefix, int index) override;
protected:
	void readInputImpl(char *buffer, FILE *gg, std::string *inputFile) override;
};
#endif