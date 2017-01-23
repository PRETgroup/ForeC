void channel_estimation(const int input_I[104], const int input_Q[104], int output_I[52], int output_Q[52]);

void channel_correction(const int input_I[52], const int input_Q[52], const int output_CHE_I[52], const int output_CHE_Q[52], int output_CHC_I[52], int output_CHC_Q[52]);

