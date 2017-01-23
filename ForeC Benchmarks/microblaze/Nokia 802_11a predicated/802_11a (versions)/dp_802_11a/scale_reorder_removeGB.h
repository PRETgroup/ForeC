#define buffer_len 64

void scale_reorder_removeGB(float input_I[buffer_len], float input_Q[buffer_len], float FFT_output_scale, int CHE_input_I[104], int CHE_input_Q[104], int payload_output_I[52], int payload_output_Q[52], int CHE_flag);
