//
// Created by dl on 2018/11/2.
//

#include "Cube.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>

#define RED { 0.835294f, 0, 0.062745f, 1 }
#define GREEN { 0, 0.623529f, 0.074510f, 1 }
#define YELLOW { 1, 1, 0, 1 }
#define ORANGE { 0.996078f, 0.541176f, 0.039216f, 1 }
#define BLUE { 0, 0.274510f, 0.623529f, 1 }
#define WHITE { 1, 1, 1, 1 }

Cube::Cube()
{
	// center
	center[0] = RED;
	center[1] = GREEN;
	center[2] = YELLOW;
	center[3] = ORANGE;
	center[4] = BLUE;
	center[5] = WHITE;
	// corner
	corner[0][0] = RED; corner[0][1] = GREEN; corner[0][2] = YELLOW;
	corner[1][0] = GREEN; corner[1][1] = ORANGE; corner[1][2] = YELLOW;
	corner[2][0] = ORANGE; corner[2][1] = BLUE; corner[2][2] = YELLOW;
	corner[3][0] = BLUE; corner[3][1] = RED; corner[3][2] = YELLOW;
	corner[4][0] = RED; corner[4][1] = GREEN; corner[4][2] = WHITE;
	corner[5][0] = GREEN; corner[5][1] = ORANGE; corner[5][2] = WHITE;
	corner[6][0] = ORANGE; corner[6][1] = BLUE; corner[6][2] = WHITE;
	corner[7][0] = BLUE; corner[7][1] = RED; corner[7][2] = WHITE;
	// edge
	edge[0][0] = RED; edge[0][1] = GREEN;
	edge[1][0] = GREEN; edge[1][1] = ORANGE;
	edge[2][0] = ORANGE; edge[2][1] = BLUE;
	edge[3][0] = BLUE; edge[3][1] = RED;
	edge[4][0] = RED; edge[4][1] = YELLOW;
	edge[5][0] = GREEN; edge[5][1] = YELLOW;
	edge[6][0] = ORANGE; edge[6][1] = YELLOW;
	edge[7][0] = BLUE; edge[7][1] = YELLOW;
	edge[8][0] = RED; edge[8][1] = WHITE;
	edge[9][0] = GREEN; edge[9][1] = WHITE;
	edge[10][0] = ORANGE; edge[10][1] = WHITE;
	edge[11][0] = BLUE; edge[11][1] = WHITE;
}

void calcCenterTriangles(v4 result[6], const POSITION& p)
{
	while (true)
	{
		if (p.x != 0)
		{
			result[0] = { 1.5f * p.x, 0.5f * p.x, 0.5f * p.x, 1 };
			result[(3 - p.x) / 2] = { 1.5f * p.x, -0.5f * p.x, 0.5f * p.x, 1 };
			result[(3 + p.x) / 2] = { 1.5f * p.x, -0.5f * p.x, -0.5f * p.x, 1 };
			result[3] = { 1.5f * p.x, -0.5f * p.x, -0.5f * p.x, 1 };
			result[(9 - p.x) / 2] = { 1.5f * p.x, 0.5f * p.x, -0.5f * p.x, 1 };
			result[(9 + p.x) / 2] = { 1.5f * p.x, 0.5f * p.x, 0.5f * p.x, 1 };
			break;
		}
		if (p.y != 0)
		{
			result[0] = { -0.5f * p.y, 1.5f * p.y, -0.5f * p.y, 1 };
			result[(3 - p.y) / 2] = { -0.5f * p.y, 1.5f * p.y, 0.5f * p.y, 1 };
			result[(3 + p.y) / 2] = { 0.5f * p.y, 1.5f * p.y, 0.5f * p.y, 1 };
			result[3] = { 0.5f * p.y, 1.5f * p.y, 0.5f * p.y, 1 };
			result[(9 - p.y) / 2] = { 0.5f * p.y, 1.5f * p.y, -0.5f * p.y, 1 };
			result[(9 + p.y) / 2] = { -0.5f * p.y, 1.5f * p.y, -0.5f * p.y, 1 };
			break;
		}
		if (p.z != 0)
		{
			result[0] = { -0.5f * p.z, 0.5f * p.z, 1.5f * p.z, 1 };
			result[(3 - p.z) / 2] = { -0.5f * p.z, -0.5f * p.z, 1.5f * p.z, 1 };
			result[(3 + p.z) / 2] = { 0.5f * p.z, -0.5f * p.z, 1.5f * p.z, 1 };
			result[3] = { 0.5f * p.z, -0.5f * p.z, 1.5f * p.z, 1 };
			result[(9 - p.z) / 2] = { 0.5f * p.z, 0.5f * p.z, 1.5f * p.z, 1 };
			result[(9 + p.z) / 2] = { -0.5f * p.z, 0.5f * p.z, 1.5f * p.z, 1 };
			break;
		}
	}
}

#define PushCenterTriangles(x, y, z) \
calcCenterTriangles(tempCenter, { x, y, z }); \
for (auto p : tempCenter) \
	result.push_back(p);

void calcCornerTriangles(v4 result[3][6], const POSITION& p)
{
	result[0][0] = { (1.5f - (float)(p.x * p.z + 1) / 2) * p.x, 1.5f * p.y, (0.5f + (float)(p.x * p.z + 1) / 2) * p.z, 1 };
	result[0][p.y == 1 ? 1 : 2] = { (1.5f - (float)(p.x * p.z + 1) / 2) * p.x, 0.5f * p.y, (0.5f + (float)(p.x * p.z + 1) / 2) * p.z, 1 };
	result[0][p.y == 1 ? 2 : 1] = { 1.5f * p.x, 0.5f * p.y, 1.5f * p.z, 1 };
	result[0][3] = { 1.5f * p.x, 0.5f * p.y, 1.5f * p.z, 1 };
	result[0][p.y == 1 ? 4 : 5] = { 1.5f * p.x, 1.5f * p.y, 1.5f * p.z, 1 };
	result[0][p.y == 1 ? 5 : 4] = { (1.5f - (float)(p.x * p.z + 1) / 2) * p.x, 1.5f * p.y, (0.5f + (float)(p.x * p.z + 1) / 2) * p.z, 1 };

	result[1][0] = { 1.5f * p.x, 1.5f * p.y, 1.5f * p.z, 1 };
	result[1][p.y == 1 ? 1 : 2] = { 1.5f * p.x, 0.5f * p.y, 1.5f * p.z, 1 };
	result[1][p.y == 1 ? 2 : 1] = { (0.5f + (float)(p.x * p.z + 1) / 2) * p.x, 0.5f * p.y, (1.5f - (float)(p.x * p.z + 1) / 2) * p.z, 1 };
	result[1][3] = { (0.5f + (float)(p.x * p.z + 1) / 2) * p.x, 0.5f * p.y, (1.5f - (float)(p.x * p.z + 1) / 2) * p.z, 1 };
	result[1][p.y == 1 ? 4 : 5] = { (0.5f + (float)(p.x * p.z + 1) / 2) * p.x, 1.5f * p.y, (1.5f - (float)(p.x * p.z + 1) / 2) * p.z, 1 };
	result[1][p.y == 1 ? 5 : 4] = { 1.5f * p.x, 1.5f * p.y, 1.5f * p.z, 1 };

	result[2][0] = { 1.5f * p.x, 1.5f * p.y, 1.5f * p.z, 1 };
	result[2][p.y == 1 ? 1 : 2] = { 0.5f * p.x, 1.5f * p.y, 0.5f * p.z, 1 };
	result[2][p.y == 1 ? 2 : 1] = { (1.5f - (float)(p.x * p.z + 1) / 2) * p.x, 1.5f * p.y, (0.5f + (float)(p.x * p.z + 1) / 2) * p.z, 1 };
	result[2][3] = { 0.5f * p.x, 1.5f * p.y, 0.5f * p.z, 1 };
	result[2][p.y == 1 ? 4 : 5] = { 1.5f * p.x, 1.5f * p.y, 1.5f * p.z, 1 };
	result[2][p.y == 1 ? 5 : 4] = { (0.5f + (float)(p.x * p.z + 1) / 2) * p.x, 1.5f * p.y, (1.5f - (float)(p.x * p.z + 1) / 2) * p.z, 1 };
}

#define PushCornerTriangles(x, y, z) \
calcCornerTriangles(tempCorner, { x, y, z }); \
for (int i = 0; i < 3; i++) \
	for (auto p : tempCorner[i]) \
		result.push_back(p);

void calcEdgeTriangles(v4 result[2][6], const POSITION& p)
{
	if (p.y == 0)
	{
		result[0][0] = { (1.5f - (float)(p.x * p.z + 1) / 2) * p.x, 0.5f, (0.5f + (float)(p.x * p.z + 1) / 2) * p.z, 1 };
		result[0][1] = { (1.5f - (float)(p.x * p.z + 1) / 2) * p.x, -0.5f, (0.5f + (float)(p.x * p.z + 1) / 2) * p.z, 1 };
		result[0][2] = { 1.5f * p.x, -0.5f, 1.5f * p.z, 1 };
		result[0][3] = { 1.5f * p.x, -0.5f, 1.5f * p.z, 1 };
		result[0][4] = { 1.5f * p.x, 0.5f, 1.5f * p.z, 1 };
		result[0][5] = { (1.5f - (float)(p.x * p.z + 1) / 2) * p.x, 0.5f, (0.5f + (float)(p.x * p.z + 1) / 2) * p.z, 1 };

		result[1][0] = { 1.5f * p.x, 0.5f, 1.5f * p.z, 1 };
		result[1][1] = { 1.5f * p.x, -0.5f, 1.5f * p.z, 1 };
		result[1][2] = { (0.5f + (float)(p.x * p.z + 1) / 2) * p.x, -0.5f, (1.5f - (float)(p.x * p.z + 1) / 2) * p.z, 1 };
		result[1][3] = { (0.5f + (float)(p.x * p.z + 1) / 2) * p.x, -0.5f, (1.5f - (float)(p.x * p.z + 1) / 2) * p.z, 1 };
		result[1][4] = { (0.5f + (float)(p.x * p.z + 1) / 2) * p.x, 0.5f, (1.5f - (float)(p.x * p.z + 1) / 2) * p.z, 1 };
		result[1][5] = { 1.5f * p.x, 0.5f, 1.5f * p.z, 1 };
	}
	else
	{
		if (p.x == 0)
		{
			result[0][0] = { 0.5f * (p.x + p.z), 1.5f * p.y, 1.5f * (p.z - p.x), 1 };
			result[0][p.y == 1 ? 1 : 2] = { 0.5f * (p.x - p.z), 1.5f * p.y, 1.5f * (p.z - p.x), 1 };
			result[0][p.y == 1 ? 2 : 1] = { 0.5f * (p.x - p.z), 0.5f * p.y, 1.5f * (p.z - p.x), 1 };
			result[0][3] = { 0.5f * (p.x - p.z), 0.5f * p.y, 1.5f * (p.z - p.x), 1 };
			result[0][p.y == 1 ? 4 : 5] = { 0.5f * (p.x + p.z), 0.5f * p.y, 1.5f * (p.z - p.x), 1 };
			result[0][p.y == 1 ? 5 : 4] = { 0.5f * (p.x + p.z), 1.5f * p.y, 1.5f * (p.z - p.x), 1 };

			result[1][0] = { 0.5f * (p.x + p.z), 1.5f * p.y, 1.5f * (p.z - p.x), 1 };
			result[1][p.y == 1 ? 1 : 2] = { 0.5f * (p.x + p.z), 1.5f * p.y, 0.5f * (p.z - p.x), 1 };
			result[1][p.y == 1 ? 2 : 1] = { 0.5f * (p.x - p.z), 1.5f * p.y, 0.5f * (p.z - p.x), 1 };
			result[1][3] = { 0.5f * (p.x - p.z), 1.5f * p.y, 0.5f * (p.z - p.x), 1 };
			result[1][p.y == 1 ? 4 : 5] = { 0.5f * (p.x - p.z), 1.5f * p.y, 1.5f * (p.z - p.x), 1 };
			result[1][p.y == 1 ? 5 : 4] = { 0.5f * (p.x + p.z), 1.5f * p.y, 1.5f * (p.z - p.x), 1 };
		}
		else
		{
			result[0][0] = { 1.5f * (p.x + p.z), 1.5f * p.y, 0.5f * (p.z - p.x), 1 };
			result[0][p.y == 1 ? 1 : 2] = { 1.5f * (p.x + p.z), 1.5f * p.y, 0.5f * (p.x - p.z), 1 };
			result[0][p.y == 1 ? 2 : 1] = { 1.5f * (p.x + p.z), 0.5f * p.y, 0.5f * (p.x - p.z), 1 };
			result[0][3] = { 1.5f * (p.x + p.z), 0.5f * p.y, 0.5f * (p.x - p.z), 1 };
			result[0][p.y == 1 ? 4 : 5] = { 1.5f * (p.x + p.z), 0.5f * p.y, 0.5f * (p.z - p.x), 1 };
			result[0][p.y == 1 ? 5 : 4] = { 1.5f * (p.x + p.z), 1.5f * p.y, 0.5f * (p.z - p.x), 1 };

			result[1][0] = { 1.5f * (p.x + p.z), 1.5f * p.y, 0.5f * (p.z - p.x), 1 };
			result[1][p.y == 1 ? 1 : 2] = { 0.5f * (p.x + p.z), 1.5f * p.y, 0.5f * (p.z - p.x), 1 };
			result[1][p.y == 1 ? 2 : 1] = { 0.5f * (p.x + p.z), 1.5f * p.y, 0.5f * (p.x - p.z), 1 };
			result[1][3] = { 0.5f * (p.x + p.z), 1.5f * p.y, 0.5f * (p.x - p.z), 1 };
			result[1][p.y == 1 ? 4 : 5] = { 1.5f * (p.x + p.z), 1.5f * p.y, 0.5f * (p.x - p.z), 1 };
			result[1][p.y == 1 ? 5 : 4] = { 1.5f * (p.x + p.z), 1.5f * p.y, 0.5f * (p.z - p.x), 1 };
		}
	}
}

#define PushEdgeTriangles(x, y, z) \
calcEdgeTriangles(tempEdge, { x, y, z }); \
for (int i = 0; i < 2; i++) \
	for (auto p : tempEdge[i]) \
		result.push_back(p);

std::vector<v4> Cube::GetTriangles()
{
	std::vector<v4> result;
	// center
	v4 tempCenter[6];
	PushCenterTriangles(0, 0, 1);
	PushCenterTriangles(1, 0, 0);
	PushCenterTriangles(0, 1, 0);
	PushCenterTriangles(0, 0, -1);
	PushCenterTriangles(-1, 0, 0);
	PushCenterTriangles(0, -1, 0);
	// corner
	v4 tempCorner[3][6];
	PushCornerTriangles(1, 1, 1);
	PushCornerTriangles(1, 1, -1);
	PushCornerTriangles(-1, 1, -1);
	PushCornerTriangles(-1, 1, 1);
	PushCornerTriangles(1, -1, 1);
	PushCornerTriangles(1, -1, -1);
	PushCornerTriangles(-1, -1, -1);
	PushCornerTriangles(-1, -1, 1);
	// edge
	v4 tempEdge[2][6];
	PushEdgeTriangles(1, 0, 1);
	PushEdgeTriangles(1, 0, -1);
	PushEdgeTriangles(-1, 0, -1);
	PushEdgeTriangles(-1, 0, 1);
	PushEdgeTriangles(0, 1, 1);
	PushEdgeTriangles(1, 1, 0);
	PushEdgeTriangles(0, 1, -1);
	PushEdgeTriangles(-1, 1, 0);
	PushEdgeTriangles(0, -1, 1);
	PushEdgeTriangles(1, -1, 0);
	PushEdgeTriangles(0, -1, -1);
	PushEdgeTriangles(-1, -1, 0);
	return result;
}

std::vector<v4> Cube::GetColors()
{
	std::vector<v4> result;
	// center
	for (auto p : center)
		result.insert(result.end(), 3 * 2, p);
	// corner
	for (int i = 0; i < 8; i++)
		for (auto p : corner[i])
			result.insert(result.end(), 3 * 2, p);
	// edge
	for (int i = 0; i < 12; i++)
		for (auto p : edge[i])
			result.insert(result.end(), 3 * 2, p);
	return result;
}

std::vector<v4> Cube::GetCenters()
{
	std::vector<v4> result;
	std::vector<v4> triangles = GetTriangles();
	for (int i = 0; i < triangles.size(); i+=3)
	{
		v4 a = triangles[i + 0], b = triangles[i + 1], c = triangles[i + 2];
		float x = (std::min(a.x, std::min(b.x, c.x)) + std::max(a.x, std::max(b.x, c.x))) / 2;
		float y = (std::min(a.y, std::min(b.y, c.y)) + std::max(a.y, std::max(b.y, c.y))) / 2;
		float z = (std::min(a.z, std::min(b.z, c.z)) + std::max(a.z, std::max(b.z, c.z))) / 2;
		result.push_back({ x, y, z, 1 });
		result.push_back({ x, y, z, 1 });
		result.push_back({ x, y, z, 1 });
	}
	return result;
}

std::vector<unsigned int> Cube::GetIndices()
{
	std::vector<unsigned int> result;
	for (unsigned int i = 0; i < (6 + 8 * 3 + 12 * 2) * 2; i++)
	{
		result.push_back(i * 3 + 0);
		result.push_back(i * 3 + 1);
		result.push_back(i * 3 + 2);
	}
	return result;
}

#define ROTATE_FUNC_IMPLEMENT(color) \
void Cube::Rotate##color##CCW() \
{ \
	Rotate##color##CW(); Rotate##color##CW(); Rotate##color##CW(); \
} \
\
void Cube::Rotate##color##CW()

ROTATE_FUNC_IMPLEMENT(Red)
{
	v4 t0 = corner[0][0], t1 = corner[0][1], t2 = corner[0][2];
	corner[0][0] = corner[3][1]; corner[0][1] = corner[3][2]; corner[0][2] = corner[3][0];
	corner[3][0] = corner[7][2]; corner[3][1] = corner[7][1]; corner[3][2] = corner[7][0];
	corner[7][0] = corner[4][2]; corner[7][1] = corner[4][0]; corner[7][2] = corner[4][1];
	corner[4][0] = t0; corner[4][1] = t2; corner[4][2] = t1;
	v4 e0 = edge[0][0], e1 = edge[0][1];
	edge[0][0] = edge[4][0]; edge[0][1] = edge[4][1];
	edge[4][0] = edge[3][1]; edge[4][1] = edge[3][0];
	edge[3][0] = edge[8][1]; edge[3][1] = edge[8][0];
	edge[8][0] = e0; edge[8][1] = e1;
}

ROTATE_FUNC_IMPLEMENT(Green)
{
	v4 t0 = corner[0][0], t1 = corner[0][1], t2 = corner[0][2];
	corner[0][0] = corner[4][2]; corner[0][1] = corner[4][1]; corner[0][2] = corner[4][0];
	corner[4][0] = corner[5][2]; corner[4][1] = corner[5][0]; corner[4][2] = corner[5][1];
	corner[5][0] = corner[1][0]; corner[5][1] = corner[1][2]; corner[5][2] = corner[1][1];
	corner[1][0] = t1; corner[1][1] = t2; corner[1][2] = t0;
	v4 e0 = edge[0][0], e1 = edge[0][1];
	edge[0][0] = edge[9][1]; edge[0][1] = edge[9][0];
	edge[9][0] = edge[1][0]; edge[9][1] = edge[1][1];
	edge[1][0] = edge[5][0]; edge[1][1] = edge[5][1];
	edge[5][0] = e1; edge[5][1] = e0;
}

ROTATE_FUNC_IMPLEMENT(Yellow)
{
	v4 t0 = corner[0][0], t1 = corner[0][1], t2 = corner[0][2];
	corner[0][0] = corner[1][0]; corner[0][1] = corner[1][1]; corner[0][2] = corner[1][2];
	corner[1][0] = corner[2][0]; corner[1][1] = corner[2][1]; corner[1][2] = corner[2][2];
	corner[2][0] = corner[3][0]; corner[2][1] = corner[3][1]; corner[2][2] = corner[3][2];
	corner[3][0] = t0; corner[3][1] = t1; corner[3][2] = t2;
	v4 e0 = edge[4][0], e1 = edge[4][1];
	edge[4][0] = edge[5][0]; edge[4][1] = edge[5][1];
	edge[5][0] = edge[6][0]; edge[5][1] = edge[6][1];
	edge[6][0] = edge[7][0]; edge[6][1] = edge[7][1];
	edge[7][0] = e0; edge[7][1] = e1;
}

ROTATE_FUNC_IMPLEMENT(Orange)
{
	v4 t0 = corner[1][0], t1 = corner[1][1], t2 = corner[1][2];
	corner[1][0] = corner[5][2]; corner[1][1] = corner[5][1]; corner[1][2] = corner[5][0];
	corner[5][0] = corner[6][2]; corner[5][1] = corner[6][0]; corner[5][2] = corner[6][1];
	corner[6][0] = corner[2][0]; corner[6][1] = corner[2][2]; corner[6][2] = corner[2][1];
	corner[2][0] = t1; corner[2][1] = t2; corner[2][2] = t0;
	v4 e0 = edge[1][0], e1 = edge[1][1];
	edge[1][0] = edge[10][1]; edge[1][1] = edge[10][0];
	edge[10][0] = edge[2][0]; edge[10][1] = edge[2][1];
	edge[2][0] = edge[6][0]; edge[2][1] = edge[6][1];
	edge[6][0] = e1; edge[6][1] = e0;
}

ROTATE_FUNC_IMPLEMENT(Blue)
{
	v4 t0 = corner[3][0], t1 = corner[3][1], t2 = corner[3][2];
	corner[3][0] = corner[2][1]; corner[3][1] = corner[2][2]; corner[3][2] = corner[2][0];
	corner[2][0] = corner[6][2]; corner[2][1] = corner[6][1]; corner[2][2] = corner[6][0];
	corner[6][0] = corner[7][2]; corner[6][1] = corner[7][0]; corner[6][2] = corner[7][1];
	corner[7][0] = t0; corner[7][1] = t2; corner[7][2] = t1;
	v4 e0 = edge[3][0], e1 = edge[3][1];
	edge[3][0] = edge[7][0]; edge[3][1] = edge[7][1];
	edge[7][0] = edge[2][1]; edge[7][1] = edge[2][0];
	edge[2][0] = edge[11][1]; edge[2][1] = edge[11][0];
	edge[11][0] = e0; edge[11][1] = e1;
}

ROTATE_FUNC_IMPLEMENT(White)
{
	v4 t0 = corner[4][0], t1 = corner[4][1], t2 = corner[4][2];
	corner[4][0] = corner[7][0]; corner[4][1] = corner[7][1]; corner[4][2] = corner[7][2];
	corner[7][0] = corner[6][0]; corner[7][1] = corner[6][1]; corner[7][2] = corner[6][2];
	corner[6][0] = corner[5][0]; corner[6][1] = corner[5][1]; corner[6][2] = corner[5][2];
	corner[5][0] = t0; corner[5][1] = t1; corner[5][2] = t2;
	v4 e0 = edge[8][0], e1 = edge[8][1];
	edge[8][0] = edge[11][0]; edge[8][1] = edge[11][1];
	edge[11][0] = edge[10][0]; edge[11][1] = edge[10][1];
	edge[10][0] = edge[9][0]; edge[10][1] = edge[9][1];
	edge[9][0] = e0; edge[9][1] = e1;
}

void Cube::Disrupt(const unsigned int& nTimes)
{
	srand((unsigned int)(time(nullptr)));
	for (unsigned int i = 0; i < nTimes; i++)
	{
		int rd = rand() % 12;
		switch (rd)
		{
		case 0:
			RotateRedCW();
			break;
		case 1:
			RotateRedCCW();
			break;
		case 2:
			RotateGreenCW();
			break;
		case 3:
			RotateGreenCCW();
			break;
		case 4:
			RotateYellowCW();
			break;
		case 5:
			RotateYellowCCW();
			break;
		case 6:
			RotateOrangeCW();
			break;
		case 7:
			RotateOrangeCCW();
			break;
		case 8:
			RotateBlueCW();
			break;
		case 9:
			RotateBlueCCW();
			break;
		case 10:
			RotateWhiteCW();
			break;
		case 11:
			RotateWhiteCCW();
			break;
		}
	}
}