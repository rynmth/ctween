#include "easing.h"
#include "tween.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool finished = false;

void* tweenFinished(void)
{
    printf("Finished.\n");
    finished = true;
}

int main(void)
{
    Tween* tween = Tween_create();
    double value = 69;
    
    tween->callback = tweenFinished;

    Tween_tween(tween, &value, -69, 1, TRANS_LINEAR, EASE_IN);
    Tween_interval(tween, 1);
    Tween_tween(tween, &value, 69, 1, TRANS_LINEAR, EASE_IN);
    Tween_start(tween);

    while (!finished)
    printf("%f\n", value);
    printf("%f\n", value);

    return 0;
}