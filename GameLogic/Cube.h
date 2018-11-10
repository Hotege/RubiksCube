//
// Created by dl on 2018/11/2.
//

#ifndef RUBIK_SCUBE_CUBE_H
#define RUBIK_SCUBE_CUBE_H


#include <vector>

struct POSITION
{
	int x, y, z;
};

struct v4
{
	float x, y, z, w;
};

#define ROTATE_FUNC(color) \
	void Rotate##color##CW(); \
	void Rotate##color##CCW();

class Cube
{
public:
	Cube();

	std::vector<v4> GetTriangles();
	std::vector<v4> GetColors();
	std::vector<v4> GetCenters();
	std::vector<v4> GetNormals();
	std::vector<unsigned int> GetIndices();

	ROTATE_FUNC(Red);
	ROTATE_FUNC(Green);
	ROTATE_FUNC(Yellow);
	ROTATE_FUNC(Orange);
	ROTATE_FUNC(Blue);
	ROTATE_FUNC(White);

	void Disrupt(const unsigned int& nTimes = 100);

private:
	// center
	// 001 100 010 00-1 -100 0-10
	v4 center[6];
	// corner
	// 111 11-1 -11-1 -111
	// 1-11 1-1-1 -1-1-1 -1-11
	v4 corner[8][3];
	// edge
	v4 edge[12][2];
};


#endif //RUBIK_SCUBE_CUBE_H
