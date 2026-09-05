#include <math.h>
#include "core.h"

/* Return the smallest angle shared by the requested and feasible intervals. */
static int first_overlap(double low, double high, double feasibleLow,
                         double feasibleHigh, double *angle)
{
    double first = low > feasibleLow ? low : feasibleLow;
    double last = high < feasibleHigh ? high : feasibleHigh;
    if (first > last + 0.000000001) return 0;
    *angle = first <= last ? first : last;
    return 1;
}

/* Uses Pythagoras to find the straight-line distance between two ships. */
double position_distance(Position first, Position second)
{
    double xDifference = first.x - second.x;
    double yDifference = first.y - second.y;
    return hypot(xDifference, yDifference);
}

int find_shot(Position start, Position end, double minSpeed,
              double maxSpeed, double minAngle, double maxAngle,
              double *flightTime, double *usedAngle)
{
    double distance = position_distance(start, end);
    double low = minAngle > 0.0 ? minAngle : 0.0;
    double high = maxAngle < 90.0 ? maxAngle : 90.0;
    double minimumSine, maximumSine, alpha, beta, angle;
    double radians, speed;

    if (distance < 0.01 || minSpeed < 0.0 || maxSpeed <= 0.0 ||
        minSpeed > maxSpeed || low > high)
        return 0;
    minimumSine = distance * GRAVITY / (maxSpeed * maxSpeed);
    if (minimumSine > 1.0 + 0.000000001) return 0;
    if (minimumSine > 1.0) minimumSine = 1.0;
    maximumSine = minSpeed > 0.0
                  ? distance * GRAVITY / (minSpeed * minSpeed) : 1.0;
    if (maximumSine > 1.0) maximumSine = 1.0;
    if (minimumSine > maximumSine + 0.000000001) return 0;
    alpha = asin(minimumSine) * 90.0 / PI;
    beta = asin(maximumSine) * 90.0 / PI;
    /* Feasible shots form one low-arc and one high-arc angle interval. */
    if (!first_overlap(low, high, alpha, beta, &angle) &&
        !first_overlap(low, high, 90.0 - beta, 90.0 - alpha, &angle)) {
        return 0;
    }
    radians = angle * PI / 180.0;
    speed = sqrt(distance * GRAVITY / sin(2.0 * radians));
    *flightTime = 2.0 * speed * sin(radians) / GRAVITY;
    *usedAngle = angle;
    return 1;
}

double degraded_power(double startPower, double gamma, int shotNumber)
{
    /* Every new shot loses power according to exponential decay. */
    return startPower * exp(-gamma * shotNumber);
}
