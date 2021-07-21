#include <stdio.h>
#include <omp.h>
#include <ompt.h>
#include <likwid-marker.h>

static void
on_ompt_callback_thread_begin(
    ompt_thread_t            thread_type,
    ompt_data_t             *thread
)
{
    int thread_id = omp_get_thread_num();
    LIKWID_MARKER_INIT;
}

static void
on_ompt_callback_thread_end(
    ompt_data_t             *thread
)
{
    int thread_id = omp_get_thread_num();
    LIKWID_MARKER_CLOSE;
}

#define register_callback_t(name, type)                       \
do{                                                           \
  type f_##name = &on_##name;                                 \
  if (ompt_set_callback(name, (ompt_callback_t)f_##name) ==   \
      ompt_set_never)                                         \
    printf("0: Could not register callback '" #name "'\n");   \
}while(0)

#define register_callback(name) register_callback_t(name, name##_t)

int ompt_initialize(
        ompt_function_lookup_t lookup,
        int initial_device_num,
        ompt_data_t *data)
{
  ompt_set_callback_t ompt_set_callback = (ompt_set_callback_t) lookup("ompt_set_callback"); // Used in macro above
  register_callback(ompt_callback_thread_begin);
  register_callback(ompt_callback_thread_end);
  printf("[INIT] init time: %f\n", omp_get_wtime()-*(double*)(data->ptr));
  return 1;
}

void ompt_finalize(ompt_data_t* data)
{
  printf("[FINAL] application runtime: %f\n", omp_get_wtime()-*(double*)(data->ptr));
}
  
ompt_start_tool_result_t* ompt_start_tool(
  unsigned int omp_version,
  const char *runtime_version)
{
  printf("[START] %s, OMP v. %u\n", runtime_version, omp_version);

  static double time=0;
  time=omp_get_wtime(); // The data pointer of the tool is initialiseD with time

  static ompt_start_tool_result_t ompt_start_tool_result = {&ompt_initialize,&ompt_finalize,{.ptr=&time}};
  return &ompt_start_tool_result;
}
