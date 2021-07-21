#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <likwid-marker.h>

#define N 10000

int main(int argc, char* argv[])
{
    int i;
    double data[N];
#pragma omp parallel
{
    LIKWID_MARKER_REGISTER("foo");
}
#pragma omp parallel
{
    LIKWID_MARKER_START("foo");
    #pragma omp for
    for(i = 0; i < N; i++)
    {
        data[i] = omp_get_thread_num();
    }
    LIKWID_MARKER_STOP("foo");
}

    return 0;
}
