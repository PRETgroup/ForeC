#define buffer_len 64

void scale_reorder_removeGB(const float input_I[buffer_len], const float input_Q[buffer_len], const float FFT_output_scale, const int CHE_flag, int CHE_input_I[104], int CHE_input_Q[104], int payload_output_I[52], int payload_output_Q[52]);
