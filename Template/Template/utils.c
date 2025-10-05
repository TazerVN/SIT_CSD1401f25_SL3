#include <math.h>
#include "cprocessing.h"

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	if ((click_x >= area_center_x - area_width / 2 && click_x <= area_center_x + area_width / 2) &&
		click_y >= area_center_y - area_height / 2 && click_y <= area_center_y + area_height / 2) {
		return 1;
	}
	else {
		return 0;
	}
}


int squared(int x) {
	return x * x;
}


int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y)
{
	if (sqrt(squared(circle_center_x - click_x) + squared(circle_center_y - click_y)) <= diameter / 2) {
		return 1;
	}
	else {
		return 0;
	}
}



int AreCirclesIntersecting(float c1_x, float c1_y, float r1, float c2_x, float c2_y, float r2)
{
	if (sqrt(squared(c1_x - c2_x) + squared(c1_y - c2_y)) <= r1 + r2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}