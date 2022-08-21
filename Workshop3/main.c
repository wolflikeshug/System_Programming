// Workshop3.cpp: 定义应用程序的入口点。
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define EARTH_RADIUS_IN_METRES          6372797

double degrees_to_radians(double degrees)
{
	double radians = degrees / 180 * 3.1415926525;
	return radians;
}

bool valid_location(double latitude, double longitude)
{
	if (latitude < -90 || latitude > 90 || longitude < -180 || longitude > 180)
	{
		return false;
	}
	return true;
}

double haversine(double latitude1, double longitude1, double latitude2, double longitude2)
{
	double lat1 = degrees_to_radians(latitude1);
	double lon1 = degrees_to_radians(longitude1);
	double lat2 = degrees_to_radians(latitude2);
	double lon2 = degrees_to_radians(longitude2);
	double dlon = lon2 - lon1;
	double dlat = lat2 - lat1;
	double a = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlon / 2), 2);
	double c = 2 * atan2(sqrt(a), sqrt(1 - a));
	return c * EARTH_RADIUS_IN_METRES;
}

int main(int argc, char* argv[])
{
	double	lat1;
	double	lon1;
	double	lat2;
	double	lon2;
		
	if (argc == 5) 
	{
		lat1 = atof(argv[1]);
		lon1 = atof(argv[2]);
		lat2 = atof(argv[3]);
		lon2 = atof(argv[4]);
	}
	else
	{
		printf("Entering Location1: ");
		scanf("%lf%lf", &lon1, &lat1);
		printf("Entering Location2: ");
		scanf("%lf%lf", &lon2, &lat2);
		
	}
	if (!valid_location(lat1, lon1) || !valid_location(lat2, lon2))
	{
		printf("Boo!!!\n");
		system("pause");
		exit(EXIT_FAILURE);
	}
	else
	{
		double distant = haversine(lat1, lon1, lat2, lon2);
		printf("Distant between: %lfm\n", distant);
		system("pause");
		exit(EXIT_SUCCESS);
	}
	return 0;
}
