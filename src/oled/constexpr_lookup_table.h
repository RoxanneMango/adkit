#ifndef CONSTEXPR_CALCS_H
#define CONSTEXPR_CALCS_H

#include <cmath>

constexpr float pi = 3.14159267;
constexpr int clock_center_x = 64;
constexpr int clock_center_y = 32;

constexpr int calc_angle(int len, int t, int i, const int center);

template<int size, int len, int t>
struct LookupTable_time
{
	int table[size][2];

	// 'constexpr' constructor:
	constexpr LookupTable_time() : table()
	{
		for(int i = 0; i < size; i++)
		{
			table[i][0] = calc_angle(len, t, i, clock_center_x);
			table[i][1] = calc_angle(len, t, i, clock_center_y);
		}
	}
};

template<int size>
struct LookupTable_clock_face
{
	int table[size][4];
	constexpr LookupTable_clock_face() : table()
	{
		for(int i = 0; i < size; i++)
		{
			table[i][0] = calc_angle(28, 12, i, clock_center_x);
			table[i][1] = calc_angle(28, 12, i, clock_center_y);
			//
			table[i][2] = calc_angle(32, 12, i, clock_center_x);
			table[i][3] = calc_angle(32, 12, i, clock_center_y);
		}
	}
};

constexpr int 
calc_angle(int len, int t, int i, const int center)
{
	return ((center == 64) ? (len*sin(pi-(2*pi)/t*i))+center : (len*cos(pi-(2*pi)/t*i))+center);
}

#endif // CONSTEXPR_CALCS_H