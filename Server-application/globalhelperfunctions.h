#pragma once

static double map(double x, double x1, double x2, double y1, double y2)
{
 return (x - x1) * (y2 - y1) / (x2 - x1) + y1;
}
