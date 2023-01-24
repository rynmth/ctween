#pragma once
#include <stdbool.h>
#include <time.h>

typedef enum
{
    TRANS_LINEAR,
    TRANS_SINE,
    TRANS_CUBIC,
    TRANS_QUINT,
    TRANS_CIRC,
    TRANS_ELASTIC,
    TRANS_QUAD,
    TRANS_QUART,
    TRANS_EXPO,
    TRANS_BACK,
    TRANS_BOUNCE
} TransitionType;

typedef enum
{
    EASE_IN,
    EASE_OUT,
    EASE_IN_OUT,
    EASE_OUT_IN
} EaseType;

typedef struct
{
    double* target;
    double start;
    double end;
    double step;
    double duration;
    double(*ease)(double);
    bool finished;
    bool started;
    clock_t time_start;
} Tweener;

typedef struct
{
    Tweener** tweeners;
    int tweeners_count;
    void*(*callback)();
    bool parallel;
    int loops;
    bool running;
} Tween;

Tween* Tween_create(void);
void Tween_start(Tween*);
void Tween_destroy(Tween*);
void Tween_tween(Tween*, double* from, double to, double duration, TransitionType, EaseType);
void Tween_interval(Tween*, double duration);
