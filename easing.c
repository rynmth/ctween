#include "easing.h"
#include <math.h>

double easeLinear(double step)
{
    return step;
}

double easeInSine(double step)
{
    return 1.0 - cos((step * M_PI) / 2.0);
}

double easeOutSine(double step)
{
    return sin((step * M_PI) / 2.0);
}

double easeInOutSine(double step)
{
    return -(cos(M_PI * step) - 1.0) / 2.0;
}

double easeOutInSine(double step)
{
    return (step < 0.5)
        ? 0.5 * (1.0 - easeInSine(1.0 - 2.0 * step))
        : 0.5 * easeInSine(step * 2.0 - 1.0) + 0.5;
}

double easeInCubic(double step)
{
    return step * step * step;
}

double easeOutCubic(double step)
{
    return 1.0 - pow(1.0 - step, 3.0);
}

double easeInOutCubic(double step)
{
    return (step < 0.5) 
        ? 4.0 * step * step * step 
        : 1.0 - pow(-2.0 * step + 2.0, 3.0) / 2.0;
}

double easeOutInCubic(double step)
{
    return (step < 0.5)
        ? 0.5 * (1.0 - easeInCubic(1.0 - 2.0 * step))
        : 0.5 * easeInCubic(step * 2.0 - 1.0) + 0.5;
}

double easeInQuint(double step)
{
    return step * step * step * step * step;
}

double easeOutQuint(double step)
{
    return 1.0 - pow(1.0 - step, 5.0);
}

double easeInOutQuint(double step)
{
    return (step < 0.5) 
        ? 16.0 * step * step * step * step * step 
        : 1.0 - pow(-2.0 * step + 2.0, 5.0) / 2.0;
}

double easeOutInQuint(double step)
{
    return (step < 0.5)
        ? 0.5 * (1.0 - easeInQuint(1.0 - 2.0 * step))
        : 0.5 * easeInQuint(step * 2.0 - 1.0) + 0.5;
}

double easeInCirc(double step)
{
    return 1.0 - sqrt(1.0 - pow(step, 2.0));
}

double easeOutCirc(double step)
{
    return sqrt(1.0 - pow(step - 1.0, 2.0));
}

double easeInOutCirc(double step)
{
    return (step < 0.5) 
        ? (1.0 - sqrt(1.0 - pow(2.0 * step, 2.0))) / 2.0 
        : (sqrt(1.0 - pow(-2.0 * step + 2.0, 2.0)) + 1.0) / 2.0;
}

double easeOutInCirc(double step)
{
    return (step < 0.5)
        ? 0.5 * (1.0 - easeInCirc(1.0 - 2.0 * step))
        : 0.5 * easeInCirc(step * 2.0 - 1.0) + 0.5;
}

double easeInElastic(double step)
{
    const double c4 = (2.0 * M_PI) / 3.0;

    return (step == 0.0) 
        ? 0.0 
        : (step == 1.0) 
        ? 1.0 
        : -pow(2.0, 10.0 * step - 10.0) * sin((step * 10.0 - 10.75) * c4);
}

double easeOutElastic(double step)
{
    const double c4 = (2.0 * M_PI) / 3.0;

    return (step == 0.0) 
        ? 0.0 
        : (step == 1.0) 
        ? 1.0 
        : pow(2.0, -10.0 * step) * sin((step * 10.0 - 0.75) * c4) + 1.0;
}

double easeInOutElastic(double step)
{
    const double c5 = (2.0 * M_PI) / 4.5;

    return (step == 0.0) 
        ? 0.0 
        : (step == 1.0) 
        ? 1.0 
        : (step < 0.5) 
        ? -(pow(2.0, 20.0 * step - 10.0) * sin((20.0 * step - 11.125) * c5)) / 2.0 
        : (pow(2.0, -20.0 * step + 10.0) * sin((20.0 * step - 11.125) * c5)) / 2.0 + 1.0;
}

double easeOutInElastic(double step)
{
    return (step < 0.5)
        ? 0.5 * (1.0 - easeInElastic(1.0 - 2.0 * step))
        : 0.5 * easeInElastic(step * 2.0 - 1.0) + 0.5;
}

double easeInQuad(double step)
{
    return step * step;
}

double easeOutQuad(double step)
{
    return 1.0 - (1.0 - step) * (1.0 - step);
}

double easeInOutQuad(double step)
{
    return (step < 0.5) 
        ? 2.0 * step * step 
        : 1.0 - pow(-2.0 * step + 2.0, 2.0) / 2.0;
}

double easeOutInQuad(double step)
{
    return (step < 0.5)
        ? 0.5 * (1.0 - easeInQuad(1.0 - 2.0 * step))
        : 0.5 * easeInQuad(step * 2.0 - 1.0) + 0.5;
}

double easeInQuart(double step)
{
    return step * step * step * step;
}

double easeOutQuart(double step)
{
    return 1.0 - pow(1.0 - step, 4.0);
}

double easeInOutQuart(double step)
{
    return (step < 0.5) 
        ? 8.0 * step * step * step * step 
        : 1.0 - pow(-2.0 * step + 2.0, 4.0) / 2.0;
}

double easeOutInQuart(double step)
{
    return (step < 0.5)
        ? 0.5 * (1.0 - easeInQuart(1.0 - 2.0 * step))
        : 0.5 * easeInQuart(step * 2.0 - 1.0) + 0.5;
}

double easeInExpo(double step)
{
    return (step == 0.0) 
        ? 0.0 
        : pow(2.0, 10.0 * step - 10.0);
}

double easeOutExpo(double step)
{
    return 1.0 - pow(2.0, -8.0 * step);
}

double easeInOutExpo(double step)
{
    return (step == 0.0) 
        ? 0.0 
        : (step == 1.0) 
        ? 1.0 
        : (step < 0.5) 
        ? pow(2.0, 20.0 * step - 10.0) / 2.0 
        : (2.0 - pow(2.0, -20.0 * step + 10.0)) / 2.0;
}

double easeOutInExpo(double step)
{
    return (step < 0.5)
        ? 0.5 * (1.0 - easeInExpo(1.0 - 2.0 * step))
        : 0.5 * easeInExpo(step * 2.0 - 1.0) + 0.5;
}

double easeInBack(double step)
{
    const double c1 = 1.70158;
    const double c3 = c1 + 1.0;

    return c3 * step * step * step - c1 * step * step;
}

double easeOutBack(double step)
{
    return 1.0 + (--step) * step * (2.70158 * step + 1.70158);
}

double easeInOutBack(double step)
{
    const double c1 = 1.70158;
    const double c2 = c1 + 1.525;

    return (step < 0.5) 
        ? (pow(2.0 * step, 2.0) * ((c2 + 1.0) * 2.0 * step - c2)) / 2.0
        : (pow(2.0 * step - 2.0, 2.0) * ((c2 + 1.0) * (step * 2.0 - 2.0) + c2) + 2.0) / 2.0;
}

double easeOutInBack(double step)
{
    return (step < 0.5)
        ? 0.5 * (1.0 - easeInBack(1.0 - 2.0 * step))
        : 0.5 * easeInBack(step * 2.0 - 1.0) + 0.5;
}

double easeOutBounce(double step)
{
    const double n1 = 7.5625;
    const double d1 = 2.75;

    if (step < 1.0 / d1) return n1 * step * step;
    if (step < 2.0 / d1) return n1 * (step -= 1.5 / d1) * step + 0.75;
    if (step < 2.5 / d1) return n1 * (step -= 2.25 / d1) * step + 0.9375;

    return n1 * (step -= 2.625 / d1) * step + 0.984375;
}

double easeInBounce(double step)
{
    return 1.0 - easeOutBounce(1.0 - step);
}

double easeInOutBounce(double step)
{
    return (step < 0.5)
        ? (1.0 - easeOutBounce(1.0 - 2.0 * step)) / 2.0
        : (1.0 + easeOutBounce(2.0 * step - 1.0)) / 2.0;
}

double easeOutInBounce(double step)
{
    return (step < 0.5)
        ? 0.5 * (1.0 - easeInBounce(1.0 - 2.0 * step))
        : 0.5 * easeInBounce(step * 2.0 - 1.0) + 0.5;
}