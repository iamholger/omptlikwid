# omptlikwid
A marriage of OpenMP tools interface and LIKWID.

We use the thread_begin and tread_end callbacks to intialise and close
the LIKWID Marker API.

# Build instructions
```
CC=clang  cmake .. -DLIKWID_DIR=/usr/local
```

# Running the example
```
OMP_TOOL_LIBRARIES=libomptlikwid.so likwid-perfctr -C 0 -g MEM -m ./simpleTest
```

compare with

```
likwid-perfctr -C 0 -g MEM -m ./simpleTest
```
