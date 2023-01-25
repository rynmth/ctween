#include "tween.h"
#include "easing.h"
#include <pthread.h>
#include <stdlib.h>

static double min(double a, double b)
{
    return (a < b) ? a : b;
}

static bool allFinished(Tween* tween)
{
    for (int i = 0; i < tween->tweeners_count; i++)
    {
        if (!tween->tweeners[i]->finished) return false;
    }

    return true;
}

static void* Tween_update(void* arg)
{
    Tween* tween = (Tween*) arg;
    loop:;

    while (!allFinished(tween))
    {
        if (!tween->running) break;
        
        for (int i = 0; i < tween->tweeners_count; i++)
        {
            if (tween->tweeners[i]->finished) continue;
            if (!tween->tweeners[i]->started)
            {
                tween->tweeners[i]->time_start = clock();
                tween->tweeners[i]->started = true;
                tween->tweeners[i]->start = (tween->tweeners[i]->target != NULL) ? *tween->tweeners[i]->target : 0;
            }

            double elapsed = (double) (clock() - tween->tweeners[i]->time_start) / CLOCKS_PER_SEC;
            tween->tweeners[i]->step = min(elapsed / tween->tweeners[i]->duration, 1.0);
            double delta = tween->tweeners[i]->end - tween->tweeners[i]->start;

            if (tween->tweeners[i]->target != NULL)
                *tween->tweeners[i]->target = tween->tweeners[i]->ease(tween->tweeners[i]->step) * delta + tween->tweeners[i]->start;

            if (tween->tweeners[i]->step == 1.0) tween->tweeners[i]->finished = true;
            else if (!tween->parallel) break;
        }
    }

    if (tween->loops != 0)
    {
        for (int i = 0; i < tween->tweeners_count; i++)
        {
            tween->tweeners[i]->started = false;
            tween->tweeners[i]->finished = false;
        }

        if (tween->loops > 0) tween->loops--;
        goto loop;
    }

    if (tween->callback != NULL)
    {
        pthread_t thread;
        pthread_create(&thread, NULL, tween->callback, NULL);
        pthread_detach(thread);
    }

    tween->running = false;

    for (int i = 0; i < tween->tweeners_count; i++)
    {
        free(tween->tweeners[i]);
    }

    free(tween->tweeners);
    free(tween);
}

Tween* Tween_create(void)
{
    Tween* tween = (Tween*) malloc(sizeof(Tween));
    tween->tweeners = (Tweener**) malloc(sizeof(Tweener));
    tween->running = false;
    tween->tweeners_count = 0;
    tween->callback = NULL;
    tween->loops = 0;

    return tween;
}

void Tween_start(Tween* tween)
{
    if (tween->running) return;
    if (!tween->tweeners_count) return;

    pthread_t thread;
    pthread_create(&thread, NULL, Tween_update, (void*) tween);
    pthread_detach(thread);
    tween->running = true;
}

void Tween_destroy(Tween* tween)
{
    if (!tween->tweeners_count) free(tween);
    else tween->running = false;
}

void Tween_tween(Tween* tween, double* from, double to, double duration, TransitionType transition, EaseType ease)
{
    if (tween->running) return;
    Tweener* tweener = (Tweener*) malloc(sizeof(Tweener));

    tweener->target = from;
    tweener->end = to;
    tweener->duration = duration;
    tweener->finished = false;
    tweener->started = false;
    tweener->step = 0.0;
    tweener->ease = NULL;
    
    if (transition == TRANS_LINEAR)
    {
        tweener->ease = easeLinear;
    }
    else switch (ease)
    {
        case EASE_IN:
            switch (transition)
            {
                case TRANS_SINE:
                    tweener->ease = easeInSine;
                    break;

                case TRANS_CUBIC:
                    tweener->ease = easeInCubic;
                    break;

                case TRANS_QUINT:
                    tweener->ease = easeInQuint;
                    break;

                case TRANS_CIRC:
                    tweener->ease = easeInQuint;
                    break;

                case TRANS_ELASTIC:
                    tweener->ease = easeInElastic;
                    break;

                case TRANS_QUAD:
                    tweener->ease = easeInQuad;
                    break;

                case TRANS_QUART:
                    tweener->ease = easeInQuart;
                    break;

                case TRANS_EXPO:
                    tweener->ease = easeInExpo;
                    break;

                case TRANS_BACK:
                    tweener->ease = easeInBack;
                    break;

                case TRANS_BOUNCE:
                    tweener->ease = easeInBounce;
                    break;
            }

            break;

        case EASE_OUT:
            switch (transition)
            {
                case TRANS_SINE:
                    tweener->ease = easeOutSine;
                    break;

                case TRANS_CUBIC:
                    tweener->ease = easeOutCubic;
                    break;

                case TRANS_QUINT:
                    tweener->ease = easeOutQuint;
                    break;

                case TRANS_CIRC:
                    tweener->ease = easeOutQuint;
                    break;

                case TRANS_ELASTIC:
                    tweener->ease = easeOutElastic;
                    break;

                case TRANS_QUAD:
                    tweener->ease = easeOutQuad;
                    break;

                case TRANS_QUART:
                    tweener->ease = easeOutQuart;
                    break;

                case TRANS_EXPO:
                    tweener->ease = easeOutExpo;
                    break;

                case TRANS_BACK:
                    tweener->ease = easeOutBack;
                    break;

                case TRANS_BOUNCE:
                    tweener->ease = easeOutBounce;
                    break;
            }
            
            break;

        case EASE_IN_OUT:
            switch (transition)
            {
                case TRANS_SINE:
                    tweener->ease = easeInOutSine;
                    break;

                case TRANS_CUBIC:
                    tweener->ease = easeInOutCubic;
                    break;

                case TRANS_QUINT:
                    tweener->ease = easeInOutQuint;
                    break;

                case TRANS_CIRC:
                    tweener->ease = easeInOutQuint;
                    break;

                case TRANS_ELASTIC:
                    tweener->ease = easeInOutElastic;
                    break;

                case TRANS_QUAD:
                    tweener->ease = easeInOutQuad;
                    break;

                case TRANS_QUART:
                    tweener->ease = easeInOutQuart;
                    break;

                case TRANS_EXPO:
                    tweener->ease = easeInOutExpo;
                    break;

                case TRANS_BACK:
                    tweener->ease = easeInOutBack;
                    break;

                case TRANS_BOUNCE:
                    tweener->ease = easeInOutBounce;
                    break;
            }
            
            break;

        case EASE_OUT_IN:
            switch (transition)
            {
                case TRANS_SINE:
                    tweener->ease = easeOutInSine;
                    break;

                case TRANS_CUBIC:
                    tweener->ease = easeOutInCubic;
                    break;

                case TRANS_QUINT:
                    tweener->ease = easeOutInQuint;
                    break;

                case TRANS_CIRC:
                    tweener->ease = easeOutInQuint;
                    break;

                case TRANS_ELASTIC:
                    tweener->ease = easeOutInElastic;
                    break;

                case TRANS_QUAD:
                    tweener->ease = easeOutInQuad;
                    break;

                case TRANS_QUART:
                    tweener->ease = easeOutInQuart;
                    break;

                case TRANS_EXPO:
                    tweener->ease = easeOutInExpo;
                    break;

                case TRANS_BACK:
                    tweener->ease = easeOutInBack;
                    break;

                case TRANS_BOUNCE:
                    tweener->ease = easeOutInBounce;
                    break;
            }
            
            break;
    }

    tween->tweeners_count++;
    tween->tweeners = (Tweener**) realloc(tween->tweeners, sizeof(Tweener) * tween->tweeners_count);
    tween->tweeners[tween->tweeners_count - 1] = tweener;
}

void Tween_interval(Tween* tween, double duration)
{
    if (tween->running) return;
    Tweener* tweener = (Tweener*) malloc(sizeof(Tweener));

    tweener->target = NULL;
    tweener->duration = duration;
    tweener->finished = false;
    tweener->started = false;
    tweener->step = 0.0;
    tweener->ease = NULL;

    tween->tweeners_count++;
    tween->tweeners = (Tweener**) realloc(tween->tweeners, sizeof(Tweener) * tween->tweeners_count);
    tween->tweeners[tween->tweeners_count - 1] = tweener;
}
