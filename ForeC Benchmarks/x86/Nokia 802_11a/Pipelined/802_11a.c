/*==============================================================
| Hardware architecture specific declarations:
| Cores, mutex and input/output information.
*=============================================================*/
#include <pthread.h>

// Mapping Pthreads to processor cores
pthread_t cores[1];
pthread_attr_t masterCoreAttribute;
pthread_attr_t slaveCoreAttribute;

// ForeC mutexes
unsigned int forec_mutex_value_stage6;

/*==============================================================
| ForeC type definitions:
| Defines the types of storage elements specific to ForeC.
*=============================================================*/
// Status values.
typedef enum {
	// PAR
	FOREC_PAR_OFF,				// 0
	FOREC_PAR_ON,				// 1

	// Core
	FOREC_CORE_REACTING,		// 2
	FOREC_CORE_REACTED,			// 3
	FOREC_CORE_TERMINATED,		// 4
	
	// Shared variables
	FOREC_SHARED_UNMODIFIED,	// 5
	FOREC_SHARED_MODIFIED,		// 6
	FOREC_SHARED_WAS_MODIFIED	// 7
} Status;

// Store child thread information.
typedef struct _Thread {
	void *programCounter;
	struct _Thread *nextThread;
	struct _Thread *prevThread;
} Thread;

// Store parent thread information
typedef struct {
	void *programCounter;
	int parStatus;
	int parId;
} Parent;

// Keep track of child threads executing on
// a processor core.
typedef struct {
	int sync;
	int activeThreads;
	int status;
	int reactionCounter;
} Core;

// Structure to pass input arguments into forecMain.
typedef struct {
	int coreId;
	int argc;
	char **argv;
} Arguments;


// Shared control variables for par(...)s -------------------------
// Thread main with par(...)s
volatile Parent mainParParent;
volatile Core mainParCore0;
volatile int mainParReactionCounter;

// Thread stage6 with par(...)s
volatile Parent stage6ParParent;
volatile Core stage6ParCore0;
volatile int stage6ParReactionCounter;


/*==============================================================
| Original global declarations:
| Global declarations in the original program code.
*=============================================================*/
// Original main function
void *forecMain(void *args);

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int printf(const char *format, ...);
int atoi(const char *str);
double atof(const char *str);
int stat(const char *path, struct stat *buf);

typedef int FILE__global_0_0;

#define FILE__global_0_0 FILE

FILE__global_0_0 *fopen(const char *filename, const char *mode);
int fclose(FILE__global_0_0 *stream);
int fprintf(FILE__global_0_0 *stream, const char *format, ...);
int feof(FILE__global_0_0 *stream);
char *fgets(char *str, int num, FILE__global_0_0 *stream);

FILE__global_0_0 *file_re_in__global_0_0, *file_im_in__global_0_0;

typedef struct {
	/* shared */ FILE__global_0_0 *value;
	int status;
} Shared_freq_sync_correl_2STS_out_I__global_0_0;
Shared_freq_sync_correl_2STS_out_I__global_0_0 freq_sync_correl_2STS_out_I__global_0_0;
typedef struct {
	/* shared */ FILE__global_0_0 *value;
	int status;
} Shared_freq_sync_correl_2STS_out_Q__global_0_0;
Shared_freq_sync_correl_2STS_out_Q__global_0_0 freq_sync_correl_2STS_out_Q__global_0_0;
typedef struct {
	/* shared */ FILE__global_0_0 *value;
	int status;
} Shared_FS_single_correl_I__global_0_0;
Shared_FS_single_correl_I__global_0_0 FS_single_correl_I__global_0_0;
typedef struct {
	/* shared */ FILE__global_0_0 *value;
	int status;
} Shared_FS_single_correl_Q__global_0_0;
Shared_FS_single_correl_Q__global_0_0 FS_single_correl_Q__global_0_0;
typedef struct {
	/* shared */ FILE__global_0_0 *value;
	int status;
} Shared_fft_re_reversed__global_0_0;
Shared_fft_re_reversed__global_0_0 fft_re_reversed__global_0_0;
typedef struct {
	/* shared */ FILE__global_0_0 *value;
	int status;
} Shared_fft_im_reversed__global_0_0;
Shared_fft_im_reversed__global_0_0 fft_im_reversed__global_0_0;
typedef struct {
	/* shared */ FILE__global_0_0 *value;
	int status;
} Shared_freq_est_phase_out_I__global_0_0;
Shared_freq_est_phase_out_I__global_0_0 freq_est_phase_out_I__global_0_0;
typedef struct {
	/* shared */ FILE__global_0_0 *value;
	int status;
} Shared_freq_est_phase_out_Q__global_0_0;
Shared_freq_est_phase_out_Q__global_0_0 freq_est_phase_out_Q__global_0_0;
typedef struct {
	/* shared */ FILE__global_0_0 *value;
	int status;
} Shared_CHE_out_I__global_0_0;
Shared_CHE_out_I__global_0_0 CHE_out_I__global_0_0;
typedef struct {
	/* shared */ FILE__global_0_0 *value;
	int status;
} Shared_CHE_out_Q__global_0_0;
Shared_CHE_out_Q__global_0_0 CHE_out_Q__global_0_0;
typedef struct {
	/* shared */ FILE__global_0_0 *value;
	int status;
} Shared_CHC_out_I__global_0_0;
Shared_CHC_out_I__global_0_0 CHC_out_I__global_0_0;
typedef struct {
	/* shared */ FILE__global_0_0 *value;
	int status;
} Shared_CHC_out_Q__global_0_0;
Shared_CHC_out_Q__global_0_0 CHC_out_Q__global_0_0;
typedef struct {
	/* shared */ FILE__global_0_0 *value;
	int status;
} Shared_fft_re_out__global_0_0;
Shared_fft_re_out__global_0_0 fft_re_out__global_0_0;
typedef struct {
	/* shared */ FILE__global_0_0 *value;
	int status;
} Shared_fft_im_out__global_0_0;
Shared_fft_im_out__global_0_0 fft_im_out__global_0_0;
typedef struct {
	/* shared */ int value;
	int status;
} Shared_debug__global_0_0;
Shared_debug__global_0_0 debug__global_0_0 = {.value = 1, .status = FOREC_SHARED_UNMODIFIED};

static const int buffer_len__global_0_0 = 64;
static const int cordic_steps_c__global_0_0 = 11;
static const int inter_reg_steps_c__global_0_0 = 3;
static const int INTMAX__global_0_0 = 2147483647;
static const unsigned int UINTMAX__global_0_0 = 4294967295u;
static const long arctanTable__global_0_0[32] = {0, 1267733622, 669835629, 340019024, 170669324, 85417861, 42719353, 21360980, 10680653, 5340347, 2670176, 1335088, 667544, 333772, 166886, 83443, 41722, 20861, 10430, 5215, 2608, 1304, 652, 326, 163, 81, 41, 20, 10, 5, 3, 1};
static const int arctan_divisor_y0__global_0_0[10] = {2, 8, 16, 64, 128, 512, 1024, 4096, 8192, 32768};
static const int arctan_divisor_y1__global_0_0[10] = {1, 4, 8, 32, 64, 256, 512, 2048, 4096, 16384};
static const int arctan_divisor_x0__global_0_0[10] = {2, 2, 4, 4, 8, 8, 16, 16, 32, 32};
static const int arctan_divisor_x1__global_0_0[10] = {1, 1, 2, 2, 4, 4, 8, 8, 16, 16};
static const int correl_sum_len__global_0_0 = 256;
static const int burst_threshold__global_0_0 = 300;
static const int FreqEstStartSlSum__global_0_0 = 16;
static const int FreqEstStopSlSum__global_0_0 = 240;
static const int Stages__global_0_0 = 12;
static const int FS_on__global_0_0 = 1;
static const int IntRegStages__global_0_0 = 3;
static const int fs_out_scale__global_0_0 = 6;
static const int cordic_turn_divisor0__global_0_0[12] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};
static const long arc_tan_array_c__global_0_0[31] = {1267733622, 669835629, 340019024, 170669324, 85417861, 42719353, 21360980, 10680653, 5340347, 2670176, 1335088, 667544, 333772, 166886, 83443, 41722, 20861, 10430, 5215, 2608, 1304, 652, 326, 163, 81, 41, 20, 10, 5, 3, 1};
static const int Searchwin_length__global_0_0 = 120;
static const int time_corr_long_thresh__global_0_0 = 2000;
static const int data_quant_trs_real__global_0_0[64] = {-7.000000, 1.000000, 4.000000, -4.000000, -1.000000, 4.000000, -6.000000, -5.000000, -2.000000, -3.000000, -3.000000, 3.000000, 4.000000, -6.000000, -3.000000, 2.000000, 3.000000, 5.000000, -1.000000, 3.000000, 1.000000, -6.000000, 1.000000, 3.000000, 4.000000, -2.000000, -5.000000, 3.000000, 1.000000, 4.000000, 2.000000, -1.000000, 7.000000, -1.000000, 2.000000, 4.000000, 1.000000, 3.000000, -5.000000, -2.000000, 4.000000, 3.000000, 1.000000, -6.000000, 1.000000, 3.000000, -1.000000, 5.000000, 3.000000, 2.000000, -3.000000, -6.000000, 4.000000, 3.000000, -3.000000, -3.000000, -2.000000, -5.000000, -6.000000, 4.000000, -1.000000, -4.000000, 4.000000, 1.000000};
static const int data_quant_trs_imag__global_0_0[64] = {0.000000, -4.000000, -5.000000, -5.000000, -3.000000, 3.000000, 1.000000, 1.000000, 7.000000, 1.000000, -4.000000, -1.000000, -4.000000, -3.000000, -2.000000, -4.000000, 3.000000, 1.000000, -7.000000, 1.000000, 3.000000, 2.000000, 5.000000, -1.000000, 2.000000, 5.000000, 3.000000, 4.000000, -2.000000, -4.000000, 5.000000, 5.000000, 0.000000, -5.000000, -5.000000, 4.000000, 2.000000, -4.000000, -3.000000, -5.000000, -2.000000, 1.000000, -5.000000, -2.000000, -3.000000, -1.000000, 7.000000, -1.000000, -3.000000, 4.000000, 2.000000, 3.000000, 4.000000, 1.000000, 4.000000, -1.000000, -7.000000, -1.000000, -1.000000, -3.000000, 3.000000, 5.000000, 5.000000, 4.000000};
static int long_pattern_array__global_0_0[52] = {1, 1, -1, -1, 1, 1, -1, 1, -1, 1, 1, 1, 1, 1, 1, -1, -1, 1, 1, -1, 1, -1, 1, 1, 1, 1, 1, -1, -1, 1, 1, -1, 1, -1, 1, -1, -1, -1, -1, -1, 1, 1, -1, -1, 1, -1, 1, -1, 1, 1, 1, 1};

typedef struct {
	/* shared */ int *value;
	int status;
} Shared_long_pattern__global_0_0;
Shared_long_pattern__global_0_0 long_pattern__global_0_0 = {.value = long_pattern_array__global_0_0, .status = FOREC_SHARED_UNMODIFIED};

static const int twiddle21_size__global_0_0 = 12;
static const float twiddle21_re__global_0_0[12] = {1.00000000e+00, 7.07106769e-01, -4.37113883e-08, -7.07106769e-01, 1.00000000e+00, 9.23879504e-01, 7.07106769e-01, 3.82683426e-01, 1.00000000e+00, 3.82683426e-01, -7.07106769e-01, -9.23879504e-01};
static const float twiddle21_im__global_0_0[12] = {0.00000000e+00, -7.07106769e-01, -1.00000000e+00, -7.07106769e-01, 0.00000000e+00, -3.82683456e-01, -7.07106769e-01, -9.23879504e-01, 0.00000000e+00, -9.23879504e-01, -7.07106769e-01, 3.82683426e-01};
static const int twiddle43_size__global_0_0 = 48;
static const float twiddle43_re__global_0_0[48] = {1.00000000e+00, 9.80785251e-01, 9.23879504e-01, 8.31469595e-01, 7.07106769e-01, 5.55570185e-01, 3.82683426e-01, 1.95090234e-01, -4.37113883e-08, -1.95090324e-01, -3.82683516e-01, -5.55570364e-01, -7.07106769e-01, -8.31469655e-01, -9.23879623e-01, -9.80785310e-01, 1.00000000e+00, 9.95184720e-01, 9.80785251e-01, 9.56940353e-01, 9.23879504e-01, 8.81921232e-01, 8.31469595e-01, 7.73010433e-01, 7.07106769e-01, 6.34393275e-01, 5.55570185e-01, 4.71396655e-01, 3.82683426e-01, 2.90284634e-01, 1.95090234e-01, 9.80171338e-02, 1.00000000e+00, 9.56940353e-01, 8.31469595e-01, 6.34393275e-01, 3.82683426e-01, 9.80171338e-02, -1.95090324e-01, -4.71396834e-01, -7.07106769e-01, -8.81921351e-01, -9.80785310e-01, -9.95184720e-01, -9.23879504e-01, -7.73010373e-01, -5.55570006e-01, -2.90284544e-01};
static const float twiddle43_im__global_0_0[48] = {0.00000000e+00, -1.95090324e-01, -3.82683456e-01, -5.55570245e-01, -7.07106769e-01, -8.31469655e-01, -9.23879504e-01, -9.80785310e-01, -1.00000000e+00, -9.80785251e-01, -9.23879504e-01, -8.31469536e-01, -7.07106769e-01, -5.55570185e-01, -3.82683277e-01, -1.95090309e-01, 0.00000000e+00, -9.80171412e-02, -1.95090324e-01, -2.90284663e-01, -3.82683456e-01, -4.71396744e-01, -5.55570245e-01, -6.34393334e-01, -7.07106769e-01, -7.73010433e-01, -8.31469655e-01, -8.81921291e-01, -9.23879504e-01, -9.56940353e-01, -9.80785310e-01, -9.95184720e-01, 0.00000000e+00, -2.90284663e-01, -5.55570245e-01, -7.73010433e-01, -9.23879504e-01, -9.95184720e-01, -9.80785251e-01, -8.81921232e-01, -7.07106769e-01, -4.71396625e-01, -1.95090309e-01, 9.80172679e-02, 3.82683426e-01, 6.34393394e-01, 8.31469774e-01, 9.56940353e-01};

typedef struct {
	int re;
	int im;
} icomplex__global_0_0;

typedef struct {
	float re;
	float im;
} fcomplex__global_0_0;

typedef struct {
	/* shared */ int value;
	int status;
} Shared_input_size__global_0_0;
Shared_input_size__global_0_0 input_size__global_0_0;
typedef struct {
	/* shared */ icomplex__global_0_0 *value;
	int status;
} Shared_inputData__global_0_0;
Shared_inputData__global_0_0 inputData__global_0_0;

void computeStage0(const icomplex__global_0_0 freq_sync_correl_2STS_input, int data_store_real_0[], int data_store_imag_0[], icomplex__global_0_0 *correlation_1ST, icomplex__global_0_0 *freq_sync_correl_2STS_output);

typedef struct {
	/* shared */ icomplex__global_0_0 value;
	int status;
} Shared_freq_sync_correl_2STS_output_stage_0_1__global_0_0;
Shared_freq_sync_correl_2STS_output_stage_0_1__global_0_0 freq_sync_correl_2STS_output_stage_0_1__global_0_0;
typedef struct {
	/* shared */ icomplex__global_0_0 value;
	int status;
} Shared_freq_sync_correl_2STS_output_stage_1_2__global_0_0;
Shared_freq_sync_correl_2STS_output_stage_1_2__global_0_0 freq_sync_correl_2STS_output_stage_1_2__global_0_0;
typedef struct {
	/* shared */ icomplex__global_0_0 value;
	int status;
} Shared_freq_sync_correl_2STS_output_stage_2_3__global_0_0;
Shared_freq_sync_correl_2STS_output_stage_2_3__global_0_0 freq_sync_correl_2STS_output_stage_2_3__global_0_0;
typedef struct {
	/* shared */ icomplex__global_0_0 value;
	int status;
} Shared_correlation_1ST_stage_0_1__global_0_0;
Shared_correlation_1ST_stage_0_1__global_0_0 correlation_1ST_stage_0_1__global_0_0;

void computeStage1(int *correlation_1ST_store_index, int *freq1_i, int *freq1_q, int *freq2_i, int *freq2_q, int correlation_1ST_store_real[], int correlation_1ST_store_imag[], int *burst_found_pulse_64d_index, int burst_found_pulse_64d[], icomplex__global_0_0 *freq_est_phase_out, icomplex__global_0_0 correlation_1ST, int *burst_found_out, int *burst_found_pulse_out, int *freq_est_norm_out, int *freq_est_norm_max_out, int *burst_found_pulse_for_FT);

typedef struct {
	/* shared */ int value;
	int status;
} Shared_burst_found_pulse_out_stage_1_2__global_0_0;
Shared_burst_found_pulse_out_stage_1_2__global_0_0 burst_found_pulse_out_stage_1_2__global_0_0;
typedef struct {
	/* shared */ icomplex__global_0_0 value;
	int status;
} Shared_freq_est_phase_out_stage_1_2__global_0_0;
Shared_freq_est_phase_out_stage_1_2__global_0_0 freq_est_phase_out_stage_1_2__global_0_0;

void computeStage2(int *act_angle, icomplex__global_0_0 freq_est_phase_out, int burst_found_pulse_out, int *angle);

typedef struct {
	/* shared */ int value;
	int status;
} Shared_angle_stage_2_3__global_0_0;
Shared_angle_stage_2_3__global_0_0 angle_stage_2_3__global_0_0;

void computeStage3(icomplex__global_0_0 *cordic_out, int angle, icomplex__global_0_0 freq_sync_correl_2STS_output);

typedef struct {
	/* shared */ icomplex__global_0_0 value;
	int status;
} Shared_cordic_out_stage_3_4__global_0_0;
Shared_cordic_out_stage_3_4__global_0_0 cordic_out_stage_3_4__global_0_0;

void computeStage4(int *downsampling_flag, int *maximum_found_main, int *maximum_found, int data_store_real[], int data_store_imag[], int *data_store_index, int data_quant_real[], int data_quant_imag[], int *data_quant_index, int *FTS_count, int *maximum, int *maximum_new, int *fine_time_est_int, int *fine_time_est_new, int *difference_in_fine_time_est, icomplex__global_0_0 cordic_out, icomplex__global_0_0 *data_out_FT, int burst_found_pulse_for_FT);

typedef struct {
	/* shared */ icomplex__global_0_0 value;
	int status;
} Shared_data_out_FT_stage_4_5__global_0_0;
Shared_data_out_FT_stage_4_5__global_0_0 data_out_FT_stage_4_5__global_0_0;
typedef struct {
	/* shared */ int value;
	int status;
} Shared_maximum_found_stage_4_5__global_0_0;
Shared_maximum_found_stage_4_5__global_0_0 maximum_found_stage_4_5__global_0_0;
typedef struct {
	/* shared */ int value;
	int status;
} Shared_maximum_found_stage_5_6__global_0_0;
Shared_maximum_found_stage_5_6__global_0_0 maximum_found_stage_5_6__global_0_0;
typedef struct {
	/* shared */ int value;
	int status;
} Shared_burst_found_pulse_for_FT_stage_1_2__global_0_0;
Shared_burst_found_pulse_for_FT_stage_1_2__global_0_0 burst_found_pulse_for_FT_stage_1_2__global_0_0;
typedef struct {
	/* shared */ int value;
	int status;
} Shared_burst_found_pulse_for_FT_stage_2_3__global_0_0;
Shared_burst_found_pulse_for_FT_stage_2_3__global_0_0 burst_found_pulse_for_FT_stage_2_3__global_0_0;
typedef struct {
	/* shared */ int value;
	int status;
} Shared_burst_found_pulse_for_FT_stage_3_4__global_0_0;
Shared_burst_found_pulse_for_FT_stage_3_4__global_0_0 burst_found_pulse_for_FT_stage_3_4__global_0_0;

void fft64Stage5(const int s, const int fifo_len_div2_5, const float fifo_stage5_i_reg, const float fifo_stage5_q_reg, float *bf2_n_stage5_i, float *bf2_n_stage5_q, int *nsample_5, float *fifo_i_tmp_5, float *fifo_q_tmp_5, float *bf2_fifo_stage5_i, float *bf2_fifo_stage5_q, float fifo_i_array_5[], float fifo_q_array_5[], icomplex__global_0_0 data_out_FT);
void fft64Stage4(const int s4, const int s5, const int fifo_len_div2_4, const float bf2_n_stage5_i, const float bf2_n_stage5_q, const float fifo_stage4_i_reg, const float fifo_stage4_q_reg, float *bf2_n_stage4_i, float *bf2_n_stage4_q, float *fifo_i_tmp_4, float *fifo_q_tmp_4, float *bf2_fifo_stage4_i, float *bf2_fifo_stage4_q, int *nsample_4, float fifo_i_array_4[], float fifo_q_array_4[]);
void fft64Stage3(const int s3, const int fifo_len_div2_3, const float fifo_stage3_i_reg, const float fifo_stage3_q_reg, const float mult_stage43_i, const float mult_stage43_q, float *bf2_n_stage3_i, float *bf2_n_stage3_q, float *fifo_i_tmp_3, float *fifo_q_tmp_3, float *bf2_fifo_stage3_i, float *bf2_fifo_stage3_q, int *nsample_3, float fifo_i_array_3[], float fifo_q_array_3[]);
void fft64Stage2(const int s2, const int s3, const int fifo_len_div2_2, const float bf2_n_stage3_i, const float bf2_n_stage3_q, const float fifo_stage2_i_reg, const float fifo_stage2_q_reg, float *bf2_n_stage2_i, float *bf2_n_stage2_q, int *nsample_2, float *bf2_fifo_stage2_i, float *bf2_fifo_stage2_q, float fifo_i_array_2[], float fifo_q_array_2[]);
void fft64Stage1(const int s1, const int fifo_len_div2_1, const float fifo_stage1_i_reg, const float fifo_stage1_q_reg, const float mult_stage21_i, const float mult_stage21_q, float *bf2_n_stage1_i, float *bf2_n_stage1_q, int *nsample_1, float *bf2_fifo_stage1_i, float *bf2_fifo_stage1_q, float fifo_i_array_1[], float fifo_q_array_1[]);
void fft64Stage0(const int s0, const int s1, const float bf2_n_stage1_i, const float bf2_n_stage1_q, const float fifo_stage0_i_reg, const float fifo_stage0_q_reg, float *bf2_n_stage0_i, float *bf2_n_stage0_q, float *bf2_fifo_stage0_i, float *bf2_fifo_stage0_q);

typedef struct {
	/* shared */ float value;
	int status;
} Shared_re_out__global_0_0;
Shared_re_out__global_0_0 re_out__global_0_0;
typedef struct {
	/* shared */ float value;
	int status;
} Shared_im_out__global_0_0;
Shared_im_out__global_0_0 im_out__global_0_0;

float array_re_array__global_0_0[64];
float array_im_array__global_0_0[64];
float real_out_demux_array__global_0_0[64];
float imag_out_demux_array__global_0_0[64];

typedef struct {
	/* shared */ float *value;
	int status;
} Shared_array_re__global_0_0;
Shared_array_re__global_0_0 array_re__global_0_0 = {.value = array_re_array__global_0_0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ float *value;
	int status;
} Shared_array_im__global_0_0;
Shared_array_im__global_0_0 array_im__global_0_0 = {.value = array_im_array__global_0_0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ float *value;
	int status;
} Shared_real_out_demux__global_0_0;
Shared_real_out_demux__global_0_0 real_out_demux__global_0_0 = {.value = real_out_demux_array__global_0_0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ float *value;
	int status;
} Shared_imag_out_demux__global_0_0;
Shared_imag_out_demux__global_0_0 imag_out_demux__global_0_0 = {.value = imag_out_demux_array__global_0_0, .status = FOREC_SHARED_UNMODIFIED};

int input_CHE_real_array__global_0_0[104];
int input_CHE_imag_array__global_0_0[104];
int data_remove_GI_reorder_real_array__global_0_0[52];
int data_remove_GI_reorder_imag_array__global_0_0[52];
int output_CHE_real_array__global_0_0[52];
int output_CHE_imag_array__global_0_0[52];
int output_CHC_real_array__global_0_0[52];
int output_CHC_imag_array__global_0_0[52];

typedef struct {
	/* shared */ int *value;
	int status;
} Shared_input_CHE_real__global_0_0;
Shared_input_CHE_real__global_0_0 input_CHE_real__global_0_0 = {.value = input_CHE_real_array__global_0_0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int *value;
	int status;
} Shared_input_CHE_imag__global_0_0;
Shared_input_CHE_imag__global_0_0 input_CHE_imag__global_0_0 = {.value = input_CHE_imag_array__global_0_0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int *value;
	int status;
} Shared_data_remove_GI_reorder_real__global_0_0;
Shared_data_remove_GI_reorder_real__global_0_0 data_remove_GI_reorder_real__global_0_0 = {.value = data_remove_GI_reorder_real_array__global_0_0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int *value;
	int status;
} Shared_data_remove_GI_reorder_imag__global_0_0;
Shared_data_remove_GI_reorder_imag__global_0_0 data_remove_GI_reorder_imag__global_0_0 = {.value = data_remove_GI_reorder_imag_array__global_0_0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int *value;
	int status;
} Shared_output_CHE_real__global_0_0;
Shared_output_CHE_real__global_0_0 output_CHE_real__global_0_0 = {.value = output_CHE_real_array__global_0_0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int *value;
	int status;
} Shared_output_CHE_imag__global_0_0;
Shared_output_CHE_imag__global_0_0 output_CHE_imag__global_0_0 = {.value = output_CHE_imag_array__global_0_0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int *value;
	int status;
} Shared_output_CHC_real__global_0_0;
Shared_output_CHC_real__global_0_0 output_CHC_real__global_0_0 = {.value = output_CHC_real_array__global_0_0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int *value;
	int status;
} Shared_output_CHC_imag__global_0_0;
Shared_output_CHC_imag__global_0_0 output_CHC_imag__global_0_0 = {.value = output_CHC_imag_array__global_0_0, .status = FOREC_SHARED_UNMODIFIED};
typedef struct {
	/* shared */ int value;
	int status;
} Shared_CHE_flag__global_0_0;
Shared_CHE_flag__global_0_0 CHE_flag__global_0_0 = {.value = 0, .status = FOREC_SHARED_UNMODIFIED};

// thread stage0__thread(void);
// thread stage1__thread(void);
// thread stage2__thread(void);
// thread stage3__thread(void);
// thread stage4__thread(void);
// thread stage5__thread(void);
// thread stage6__thread(void);
// thread demux0__thread(void);
// thread demux1__thread(void);
// thread demux2__thread(void);
// thread demux3__thread(void);
// thread removeReorder0__thread(void);
// thread removeReorder1__thread(void);
// thread inputChe0__thread(void);
// thread inputChe1__thread(void);
// thread inputChe2__thread(void);
// thread inputChe3__thread(void);
// thread outputChe0__thread(void);
// thread outputChe1__thread(void);
// thread outputChe2__thread(void);
// thread outputChe3__thread(void);
// thread outputChc0__thread(void);
// thread outputChc1__thread(void);
// thread outputChc2__thread(void);
// thread outputChc3__thread(void);

// Locally declared shared variables -------------------------------

// Global versions of local copies of shared variables -------------
// demux0
Shared_array_re__global_0_0 array_re__global_0_0_copy_demux0 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_array_im__global_0_0 array_im__global_0_0_copy_demux0 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_real_out_demux__global_0_0 real_out_demux__global_0_0_copy_demux0 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_imag_out_demux__global_0_0 imag_out_demux__global_0_0_copy_demux0 = {.status = FOREC_SHARED_UNMODIFIED};
// demux1
Shared_array_re__global_0_0 array_re__global_0_0_copy_demux1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_array_im__global_0_0 array_im__global_0_0_copy_demux1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_real_out_demux__global_0_0 real_out_demux__global_0_0_copy_demux1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_imag_out_demux__global_0_0 imag_out_demux__global_0_0_copy_demux1 = {.status = FOREC_SHARED_UNMODIFIED};
// demux2
Shared_array_re__global_0_0 array_re__global_0_0_copy_demux2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_array_im__global_0_0 array_im__global_0_0_copy_demux2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_real_out_demux__global_0_0 real_out_demux__global_0_0_copy_demux2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_imag_out_demux__global_0_0 imag_out_demux__global_0_0_copy_demux2 = {.status = FOREC_SHARED_UNMODIFIED};
// demux3
Shared_array_re__global_0_0 array_re__global_0_0_copy_demux3 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_array_im__global_0_0 array_im__global_0_0_copy_demux3 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_real_out_demux__global_0_0 real_out_demux__global_0_0_copy_demux3 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_imag_out_demux__global_0_0 imag_out_demux__global_0_0_copy_demux3 = {.status = FOREC_SHARED_UNMODIFIED};
// inputChe0
Shared_CHE_flag__global_0_0 CHE_flag__global_0_0_copy_inputChe0 = {.status = FOREC_SHARED_UNMODIFIED};
// inputChe1
Shared_CHE_flag__global_0_0 CHE_flag__global_0_0_copy_inputChe1 = {.status = FOREC_SHARED_UNMODIFIED};
// inputChe2
Shared_CHE_flag__global_0_0 CHE_flag__global_0_0_copy_inputChe2 = {.status = FOREC_SHARED_UNMODIFIED};
// inputChe3
Shared_CHE_flag__global_0_0 CHE_flag__global_0_0_copy_inputChe3 = {.status = FOREC_SHARED_UNMODIFIED};
// main
// outputChc0
Shared_output_CHE_real__global_0_0 output_CHE_real__global_0_0_copy_outputChc0 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_output_CHE_imag__global_0_0 output_CHE_imag__global_0_0_copy_outputChc0 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_output_CHC_real__global_0_0 output_CHC_real__global_0_0_copy_outputChc0 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_output_CHC_imag__global_0_0 output_CHC_imag__global_0_0_copy_outputChc0 = {.status = FOREC_SHARED_UNMODIFIED};
// outputChc1
Shared_output_CHE_real__global_0_0 output_CHE_real__global_0_0_copy_outputChc1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_output_CHE_imag__global_0_0 output_CHE_imag__global_0_0_copy_outputChc1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_output_CHC_real__global_0_0 output_CHC_real__global_0_0_copy_outputChc1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_output_CHC_imag__global_0_0 output_CHC_imag__global_0_0_copy_outputChc1 = {.status = FOREC_SHARED_UNMODIFIED};
// outputChc2
Shared_output_CHE_real__global_0_0 output_CHE_real__global_0_0_copy_outputChc2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_output_CHE_imag__global_0_0 output_CHE_imag__global_0_0_copy_outputChc2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_output_CHC_real__global_0_0 output_CHC_real__global_0_0_copy_outputChc2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_output_CHC_imag__global_0_0 output_CHC_imag__global_0_0_copy_outputChc2 = {.status = FOREC_SHARED_UNMODIFIED};
// outputChc3
Shared_output_CHE_real__global_0_0 output_CHE_real__global_0_0_copy_outputChc3 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_output_CHE_imag__global_0_0 output_CHE_imag__global_0_0_copy_outputChc3 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_output_CHC_real__global_0_0 output_CHC_real__global_0_0_copy_outputChc3 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_output_CHC_imag__global_0_0 output_CHC_imag__global_0_0_copy_outputChc3 = {.status = FOREC_SHARED_UNMODIFIED};
// outputChe0
Shared_output_CHE_real__global_0_0 output_CHE_real__global_0_0_copy_outputChe0 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_output_CHE_imag__global_0_0 output_CHE_imag__global_0_0_copy_outputChe0 = {.status = FOREC_SHARED_UNMODIFIED};
// outputChe1
Shared_output_CHE_real__global_0_0 output_CHE_real__global_0_0_copy_outputChe1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_output_CHE_imag__global_0_0 output_CHE_imag__global_0_0_copy_outputChe1 = {.status = FOREC_SHARED_UNMODIFIED};
// outputChe2
Shared_output_CHE_real__global_0_0 output_CHE_real__global_0_0_copy_outputChe2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_output_CHE_imag__global_0_0 output_CHE_imag__global_0_0_copy_outputChe2 = {.status = FOREC_SHARED_UNMODIFIED};
// outputChe3
Shared_output_CHE_real__global_0_0 output_CHE_real__global_0_0_copy_outputChe3 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_output_CHE_imag__global_0_0 output_CHE_imag__global_0_0_copy_outputChe3 = {.status = FOREC_SHARED_UNMODIFIED};
// removeReorder0
Shared_real_out_demux__global_0_0 real_out_demux__global_0_0_copy_removeReorder0 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_imag_out_demux__global_0_0 imag_out_demux__global_0_0_copy_removeReorder0 = {.status = FOREC_SHARED_UNMODIFIED};
// removeReorder1
Shared_real_out_demux__global_0_0 real_out_demux__global_0_0_copy_removeReorder1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_imag_out_demux__global_0_0 imag_out_demux__global_0_0_copy_removeReorder1 = {.status = FOREC_SHARED_UNMODIFIED};
// stage0
Shared_freq_sync_correl_2STS_out_I__global_0_0 freq_sync_correl_2STS_out_I__global_0_0_copy_stage0 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_freq_sync_correl_2STS_out_Q__global_0_0 freq_sync_correl_2STS_out_Q__global_0_0_copy_stage0 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_FS_single_correl_I__global_0_0 FS_single_correl_I__global_0_0_copy_stage0 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_FS_single_correl_Q__global_0_0 FS_single_correl_Q__global_0_0_copy_stage0 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_input_size__global_0_0 input_size__global_0_0_copy_stage0 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_inputData__global_0_0 inputData__global_0_0_copy_stage0 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_freq_sync_correl_2STS_output_stage_0_1__global_0_0 freq_sync_correl_2STS_output_stage_0_1__global_0_0_copy_stage0 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_correlation_1ST_stage_0_1__global_0_0 correlation_1ST_stage_0_1__global_0_0_copy_stage0 = {.status = FOREC_SHARED_UNMODIFIED};
// stage1
Shared_freq_est_phase_out_I__global_0_0 freq_est_phase_out_I__global_0_0_copy_stage1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_freq_est_phase_out_Q__global_0_0 freq_est_phase_out_Q__global_0_0_copy_stage1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_input_size__global_0_0 input_size__global_0_0_copy_stage1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_freq_sync_correl_2STS_output_stage_0_1__global_0_0 freq_sync_correl_2STS_output_stage_0_1__global_0_0_copy_stage1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_freq_sync_correl_2STS_output_stage_1_2__global_0_0 freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_correlation_1ST_stage_0_1__global_0_0 correlation_1ST_stage_0_1__global_0_0_copy_stage1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_burst_found_pulse_out_stage_1_2__global_0_0 burst_found_pulse_out_stage_1_2__global_0_0_copy_stage1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_freq_est_phase_out_stage_1_2__global_0_0 freq_est_phase_out_stage_1_2__global_0_0_copy_stage1 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_burst_found_pulse_for_FT_stage_1_2__global_0_0 burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage1 = {.status = FOREC_SHARED_UNMODIFIED};
// stage2
Shared_input_size__global_0_0 input_size__global_0_0_copy_stage2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_freq_sync_correl_2STS_output_stage_1_2__global_0_0 freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_freq_sync_correl_2STS_output_stage_2_3__global_0_0 freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_burst_found_pulse_out_stage_1_2__global_0_0 burst_found_pulse_out_stage_1_2__global_0_0_copy_stage2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_freq_est_phase_out_stage_1_2__global_0_0 freq_est_phase_out_stage_1_2__global_0_0_copy_stage2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_angle_stage_2_3__global_0_0 angle_stage_2_3__global_0_0_copy_stage2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_burst_found_pulse_for_FT_stage_1_2__global_0_0 burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage2 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_burst_found_pulse_for_FT_stage_2_3__global_0_0 burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage2 = {.status = FOREC_SHARED_UNMODIFIED};
// stage3
Shared_input_size__global_0_0 input_size__global_0_0_copy_stage3 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_freq_sync_correl_2STS_output_stage_2_3__global_0_0 freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage3 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_angle_stage_2_3__global_0_0 angle_stage_2_3__global_0_0_copy_stage3 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_cordic_out_stage_3_4__global_0_0 cordic_out_stage_3_4__global_0_0_copy_stage3 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_burst_found_pulse_for_FT_stage_2_3__global_0_0 burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage3 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_burst_found_pulse_for_FT_stage_3_4__global_0_0 burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage3 = {.status = FOREC_SHARED_UNMODIFIED};
// stage4
Shared_input_size__global_0_0 input_size__global_0_0_copy_stage4 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_cordic_out_stage_3_4__global_0_0 cordic_out_stage_3_4__global_0_0_copy_stage4 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_data_out_FT_stage_4_5__global_0_0 data_out_FT_stage_4_5__global_0_0_copy_stage4 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_maximum_found_stage_4_5__global_0_0 maximum_found_stage_4_5__global_0_0_copy_stage4 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_burst_found_pulse_for_FT_stage_3_4__global_0_0 burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage4 = {.status = FOREC_SHARED_UNMODIFIED};
// stage5
Shared_fft_re_reversed__global_0_0 fft_re_reversed__global_0_0_copy_stage5 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_fft_im_reversed__global_0_0 fft_im_reversed__global_0_0_copy_stage5 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_input_size__global_0_0 input_size__global_0_0_copy_stage5 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_data_out_FT_stage_4_5__global_0_0 data_out_FT_stage_4_5__global_0_0_copy_stage5 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_maximum_found_stage_4_5__global_0_0 maximum_found_stage_4_5__global_0_0_copy_stage5 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_maximum_found_stage_5_6__global_0_0 maximum_found_stage_5_6__global_0_0_copy_stage5 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_re_out__global_0_0 re_out__global_0_0_copy_stage5 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_im_out__global_0_0 im_out__global_0_0_copy_stage5 = {.status = FOREC_SHARED_UNMODIFIED};
// stage6
Shared_CHE_out_I__global_0_0 CHE_out_I__global_0_0_copy_stage6 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_CHE_out_Q__global_0_0 CHE_out_Q__global_0_0_copy_stage6 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_CHC_out_I__global_0_0 CHC_out_I__global_0_0_copy_stage6 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_CHC_out_Q__global_0_0 CHC_out_Q__global_0_0_copy_stage6 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_fft_re_out__global_0_0 fft_re_out__global_0_0_copy_stage6 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_fft_im_out__global_0_0 fft_im_out__global_0_0_copy_stage6 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_input_size__global_0_0 input_size__global_0_0_copy_stage6 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_maximum_found_stage_5_6__global_0_0 maximum_found_stage_5_6__global_0_0_copy_stage6 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_re_out__global_0_0 re_out__global_0_0_copy_stage6 = {.status = FOREC_SHARED_UNMODIFIED};
Shared_im_out__global_0_0 im_out__global_0_0_copy_stage6 = {.status = FOREC_SHARED_UNMODIFIED};

// forec:scheduler:boot:start
int main(int argc__main_0_0, char ** argv__main_0_0) {

/*==============================================================
| Multicore startup:
| Platform dependent code.  Core identifies itself and
| executes its corresponding start up code.
*=============================================================*/
	// Initialise ForeC specific values ---------------------------
	// Thread main with par(...)s
	mainParParent.parStatus = FOREC_PAR_OFF;
	mainParCore0.sync = 1;
	mainParCore0.status = FOREC_CORE_REACTING;
	mainParReactionCounter = 0;

	// Thread stage6 with par(...)s
	stage6ParParent.parStatus = FOREC_PAR_OFF;
	stage6ParCore0.sync = 1;
	stage6ParCore0.status = FOREC_CORE_REACTING;
	stage6ParReactionCounter = 0;


	// Reset ForeC mutex values
	forec_mutex_value_stage6 = -1;

	// Start core execution
	pthread_attr_init(&masterCoreAttribute);
	pthread_attr_init(&slaveCoreAttribute);
	pthread_attr_setdetachstate(&masterCoreAttribute, PTHREAD_CREATE_JOINABLE);
	pthread_attr_setdetachstate(&slaveCoreAttribute, PTHREAD_CREATE_DETACHED);
		
	// Master core
	Arguments arguments0 = {.coreId = 0, .argc = argc__main_0_0, .argv = argv__main_0_0};
	pthread_create(&cores[0], &masterCoreAttribute, forecMain, (void *)&arguments0);

	// End core execution
	pthread_attr_destroy(&masterCoreAttribute);
	pthread_attr_destroy(&slaveCoreAttribute);
	
	// Program termination
	pthread_join(cores[0], NULL);
}


/*==============================================================
| Original main(...) function:
*=============================================================*/
void *forecMain(void *args) {
	Arguments *arguments = (Arguments *)args;
	int coreId = arguments->coreId;
	int argc__main_0_0 = arguments->argc;
	char **argv__main_0_0 = arguments->argv;

	// Variables for par()s ----------------------------------------
	// par0
	Thread stage0__thread;
	Thread stage1__thread;
	Thread stage2__thread;
	Thread stage3__thread;
	Thread stage4__thread;
	Thread stage5__thread;
	Thread stage6__thread;
	Thread mainReactionStartMaster0;
	Thread mainReactionEndMaster0;
	Thread stage6ParHandlerMaster0;

	// par1
	Thread demux0__thread;
	Thread demux1__thread;
	Thread demux2__thread;
	Thread demux3__thread;
	Thread stage6ReactionStartMaster0;
	Thread stage6ReactionEndMaster0;

	// par2
	Thread removeReorder0__thread;
	Thread removeReorder1__thread;
	// Thread stage6ReactionStartMaster0;
	// Thread stage6ReactionEndMaster0;

	// par3
	Thread inputChe0__thread;
	Thread inputChe1__thread;
	Thread inputChe2__thread;
	Thread inputChe3__thread;
	// Thread stage6ReactionStartMaster0;
	// Thread stage6ReactionEndMaster0;

	// par4
	Thread outputChe0__thread;
	Thread outputChe1__thread;
	Thread outputChe2__thread;
	Thread outputChe3__thread;
	// Thread stage6ReactionStartMaster0;
	// Thread stage6ReactionEndMaster0;

	// par5
	Thread outputChc0__thread;
	Thread outputChc1__thread;
	Thread outputChc2__thread;
	Thread outputChc3__thread;
	// Thread stage6ReactionStartMaster0;
	// Thread stage6ReactionEndMaster0;


	// Let cores jump to their code segment ------------------------
	switch (coreId) {
		case (0):
			goto mainParCore0;

		default:
			// Terminate unused cores.
			pthread_exit(NULL);
	}
// forec:scheduler:boot:end

/*==============================================================
| Core specific instructions:
| Contains par, abort and synchronisation handlers.
*=============================================================*/
	/*--------------------------------------------------------------
	| Master core: core0
	| ForeC program's main() function:
	| Original main() function code with ForeC constructs
	| translated into C code.
	*-------------------------------------------------------------*/
	
	// Thread local declarations -----------------------------------
	struct timeval startTime__main_0_0, endTime__main_0_0;
	struct stat st__main_1_0;
	char re_in__main_2_0[20];
	char im_in__main_2_0[20];
	long seconds__main_0_0;
	int microseconds__main_0_0;

mainParCore0: {
	//--------------------------------------------------------------

	gettimeofday(&startTime__main_0_0, 0);
	file_re_in__global_0_0 = fopen("./CCSS_ref_data/rx_real_data.am", "r");
	file_im_in__global_0_0 = fopen("./CCSS_ref_data/rx_imag_data.am", "r");
	freq_sync_correl_2STS_out_I__global_0_0.value = fopen("./plainC_SimOutput/freq_sync_correl_2STS_out_I.am", "w");
	freq_sync_correl_2STS_out_Q__global_0_0.value = fopen("./plainC_SimOutput/freq_sync_correl_2STS_out_Q.am", "w");
	FS_single_correl_I__global_0_0.value = fopen("./plainC_SimOutput/FS_single_correl_I.am", "w");
	FS_single_correl_Q__global_0_0.value = fopen("./plainC_SimOutput/FS_single_correl_Q.am", "w");
	fft_re_reversed__global_0_0.value = fopen("./plainC_SimOutput/fft_reversed_re_out.am", "w");
	fft_im_reversed__global_0_0.value = fopen("./plainC_SimOutput/fft_reversed_im_out.am", "w");
	freq_est_phase_out_I__global_0_0.value = fopen("./plainC_SimOutput/freq_est_phase_out_I.am", "w");
	freq_est_phase_out_Q__global_0_0.value = fopen("./plainC_SimOutput/freq_est_phase_out_Q.am", "w");
	CHE_out_I__global_0_0.value = fopen("./plainC_SimOutput/CHE_out_I.am", "w");
	CHE_out_Q__global_0_0.value = fopen("./plainC_SimOutput/CHE_out_Q.am", "w");
	CHC_out_I__global_0_0.value = fopen("./plainC_SimOutput/CHC_out_I.am", "w");
	CHC_out_Q__global_0_0.value = fopen("./plainC_SimOutput/CHC_out_Q.am", "w");
	fft_re_out__global_0_0.value = fopen("./plainC_SimOutput/fft_re_out.am", "w");
	fft_im_out__global_0_0.value = fopen("./plainC_SimOutput/fft_im_out.am", "w");

	{
		stat("./CCSS_ref_data/rx_real_data.am", &st__main_1_0);
		input_size__global_0_0.value = st__main_1_0.st_size/10;
		inputData__global_0_0.value = (icomplex__global_0_0 *)malloc(input_size__global_0_0.value*sizeof(icomplex__global_0_0));
		input_size__global_0_0.value = 0;
		while (!feof(file_re_in__global_0_0) && !feof(file_im_in__global_0_0)) {
			fgets(re_in__main_2_0, 20, file_re_in__global_0_0);
			fgets(im_in__main_2_0, 20, file_im_in__global_0_0);
			inputData__global_0_0.value[input_size__global_0_0.value].re = (int)atof(re_in__main_2_0);
			inputData__global_0_0.value[input_size__global_0_0.value].im = (int)atof(im_in__main_2_0);
			input_size__global_0_0.value++;
		}
	}

	// par0(stage0__thread, stage1__thread, stage2__thread, stage3__thread, stage4__thread, stage5__thread, stage6__thread);
	// forec:statement:par:par0:start
	// Set the par(...) information.
	mainParParent.parId = 0;
	mainParParent.parStatus = FOREC_PAR_ON;

	// Link the threads and handlers together.
	mainReactionStartMaster0.programCounter = &&mainReactionStartMaster0;
	stage0__thread.programCounter = &&stage0__thread;
	mainReactionStartMaster0.nextThread = &stage0__thread;
	stage0__thread.prevThread = &mainReactionStartMaster0;
	stage1__thread.programCounter = &&stage1__thread;
	stage0__thread.nextThread = &stage1__thread;
	stage1__thread.prevThread = &stage0__thread;
	stage2__thread.programCounter = &&stage2__thread;
	stage1__thread.nextThread = &stage2__thread;
	stage2__thread.prevThread = &stage1__thread;
	stage3__thread.programCounter = &&stage3__thread;
	stage2__thread.nextThread = &stage3__thread;
	stage3__thread.prevThread = &stage2__thread;
	stage4__thread.programCounter = &&stage4__thread;
	stage3__thread.nextThread = &stage4__thread;
	stage4__thread.prevThread = &stage3__thread;
	stage5__thread.programCounter = &&stage5__thread;
	stage4__thread.nextThread = &stage5__thread;
	stage5__thread.prevThread = &stage4__thread;
	stage6__thread.programCounter = &&stage6__thread;
	stage5__thread.nextThread = &stage6__thread;
	stage6__thread.prevThread = &stage5__thread;
	stage6ParHandlerMaster0.programCounter = &&stage6ParHandlerMaster0;
	stage6__thread.nextThread = &stage6ParHandlerMaster0;
	stage6ParHandlerMaster0.prevThread = &stage6__thread;
	mainReactionEndMaster0.programCounter = &&mainReactionEndMaster0;
	stage6ParHandlerMaster0.nextThread = &mainReactionEndMaster0;
	mainReactionEndMaster0.prevThread = &stage6ParHandlerMaster0;

	// Link the last and first threads/handlers together.
	mainReactionEndMaster0.nextThread = &mainReactionStartMaster0;
	mainReactionStartMaster0.prevThread = &mainReactionEndMaster0;

	// Set the join address.
	mainParParent.programCounter = &&par0JoinAddress_mainParCore0;

	// Set the core information.
	mainParCore0.activeThreads = 8;
	mainParCore0.reactionCounter = mainParReactionCounter;

	// Go to the first thread.
	goto stage0__thread;
	par0JoinAddress_mainParCore0:;
	// forec:statement:par:par0:end

	fclose(file_re_in__global_0_0);
	fclose(file_im_in__global_0_0);
	fclose(freq_sync_correl_2STS_out_I__global_0_0.value);
	fclose(freq_sync_correl_2STS_out_Q__global_0_0.value);
	fclose(FS_single_correl_I__global_0_0.value);
	fclose(FS_single_correl_Q__global_0_0.value);
	fclose(fft_re_reversed__global_0_0.value);
	fclose(fft_im_reversed__global_0_0.value);
	fclose(fft_re_out__global_0_0.value);
	fclose(fft_im_out__global_0_0.value);
	fclose(freq_est_phase_out_I__global_0_0.value);
	fclose(freq_est_phase_out_Q__global_0_0.value);
	fclose(CHC_out_I__global_0_0.value);
	fclose(CHC_out_Q__global_0_0.value);
	fclose(CHE_out_I__global_0_0.value);
	fclose(CHE_out_Q__global_0_0.value);
	gettimeofday(&endTime__main_0_0, 0);
	seconds__main_0_0 = endTime__main_0_0.tv_sec - startTime__main_0_0.tv_sec;
	microseconds__main_0_0 = endTime__main_0_0.tv_usec - startTime__main_0_0.tv_usec;
	if (microseconds__main_0_0 < 0) {
		microseconds__main_0_0 += 1000000;
		seconds__main_0_0--;
	} else {
		// if0
	}
	printf("Runtime: %ld.%.6d\r\n", seconds__main_0_0, microseconds__main_0_0);
	return 0;

	//--------------------------------------------------------------


	// forec:scheduler:threadRemove:main:start
	pthread_exit(NULL);
	// forec:scheduler:threadRemove:main:end
} // mainParCore0
	// forec:thread:main:end

// forec:scheduler:parHandler:main:master:0:start
mainParHandlerMaster0: {
	if (mainParParent.parId == -2) {
		// Iteration
		// Wait for other cores to complete their reaction.

		mainParParent.parStatus = FOREC_PAR_OFF;
		mainParParent.parId = -1;

		// Set slave cores' status to reacting.

		// Increment the reaction counter for synchronisation.
		mainParReactionCounter++;

		// Return to thread main.
		goto *mainParParent.programCounter;
	}

	// Control should not reach here.
	goto mainParHandlerMaster0;
}
// forec:scheduler:parHandler:main:master:0:end


	// Nested par(...) handlers ------------------------------------
	// forec:scheduler:parHandler:stage6:master:0:start
	//-- Thread stage6 par(...) handlers
stage6ParHandlerMaster0: {
	// Check the execution status of the nested par(...)s.
	if (stage6ParParent.parStatus == FOREC_PAR_OFF) {
		// Release the mutex.
		forec_mutex_value_stage6 &= 0x7fffffff;

		goto *stage6ParHandlerMaster0.nextThread -> programCounter;
	}
	// Release the mutex.
	forec_mutex_value_stage6 &= 0x7fffffff;

	int parId = stage6ParParent.parId;

	// Check the par(...) ID.
	if (parId == 1) {
		asm ("# par1 begin");
		// Link the threads and handlers together.
		stage6ReactionStartMaster0.programCounter = &&stage6ReactionStartMaster0;
		demux0__thread.programCounter = &&demux0__thread;
		stage6ReactionStartMaster0.nextThread = &demux0__thread;
		demux0__thread.prevThread = &stage6ReactionStartMaster0;
		demux1__thread.programCounter = &&demux1__thread;
		demux0__thread.nextThread = &demux1__thread;
		demux1__thread.prevThread = &demux0__thread;
		demux2__thread.programCounter = &&demux2__thread;
		demux1__thread.nextThread = &demux2__thread;
		demux2__thread.prevThread = &demux1__thread;
		demux3__thread.programCounter = &&demux3__thread;
		demux2__thread.nextThread = &demux3__thread;
		demux3__thread.prevThread = &demux2__thread;
		stage6ReactionEndMaster0.programCounter = &&stage6ReactionEndMaster0;
		demux3__thread.nextThread = &stage6ReactionEndMaster0;
		stage6ReactionEndMaster0.prevThread = &demux3__thread;

		// Swap the nested par handler with the linked list.
		stage6ParHandlerMaster0.prevThread -> nextThread = &stage6ReactionStartMaster0;
		stage6ReactionStartMaster0.prevThread = stage6ParHandlerMaster0.prevThread;
		stage6ReactionEndMaster0.nextThread = stage6ParHandlerMaster0.nextThread;
		stage6ParHandlerMaster0.nextThread -> prevThread = &stage6ReactionEndMaster0;
		
		// Set the core information.
		stage6ParCore0.activeThreads = 4;
		stage6ParCore0.reactionCounter = stage6ParReactionCounter;
		
		// Go to the first thread.
		goto demux0__thread;
		asm ("# par1 end");
	} else if (parId == 2) {
		asm ("# par2 begin");
		// Link the threads and handlers together.
		stage6ReactionStartMaster0.programCounter = &&stage6ReactionStartMaster0;
		removeReorder0__thread.programCounter = &&removeReorder0__thread;
		stage6ReactionStartMaster0.nextThread = &removeReorder0__thread;
		removeReorder0__thread.prevThread = &stage6ReactionStartMaster0;
		removeReorder1__thread.programCounter = &&removeReorder1__thread;
		removeReorder0__thread.nextThread = &removeReorder1__thread;
		removeReorder1__thread.prevThread = &removeReorder0__thread;
		stage6ReactionEndMaster0.programCounter = &&stage6ReactionEndMaster0;
		removeReorder1__thread.nextThread = &stage6ReactionEndMaster0;
		stage6ReactionEndMaster0.prevThread = &removeReorder1__thread;

		// Swap the nested par handler with the linked list.
		stage6ParHandlerMaster0.prevThread -> nextThread = &stage6ReactionStartMaster0;
		stage6ReactionStartMaster0.prevThread = stage6ParHandlerMaster0.prevThread;
		stage6ReactionEndMaster0.nextThread = stage6ParHandlerMaster0.nextThread;
		stage6ParHandlerMaster0.nextThread -> prevThread = &stage6ReactionEndMaster0;
		
		// Set the core information.
		stage6ParCore0.activeThreads = 2;
		stage6ParCore0.reactionCounter = stage6ParReactionCounter;
		
		// Go to the first thread.
		goto removeReorder0__thread;
		asm ("# par2 end");
	} else if (parId == 3) {
		asm ("# par3 begin");
		// Link the threads and handlers together.
		stage6ReactionStartMaster0.programCounter = &&stage6ReactionStartMaster0;
		inputChe0__thread.programCounter = &&inputChe0__thread;
		stage6ReactionStartMaster0.nextThread = &inputChe0__thread;
		inputChe0__thread.prevThread = &stage6ReactionStartMaster0;
		inputChe1__thread.programCounter = &&inputChe1__thread;
		inputChe0__thread.nextThread = &inputChe1__thread;
		inputChe1__thread.prevThread = &inputChe0__thread;
		inputChe2__thread.programCounter = &&inputChe2__thread;
		inputChe1__thread.nextThread = &inputChe2__thread;
		inputChe2__thread.prevThread = &inputChe1__thread;
		inputChe3__thread.programCounter = &&inputChe3__thread;
		inputChe2__thread.nextThread = &inputChe3__thread;
		inputChe3__thread.prevThread = &inputChe2__thread;
		stage6ReactionEndMaster0.programCounter = &&stage6ReactionEndMaster0;
		inputChe3__thread.nextThread = &stage6ReactionEndMaster0;
		stage6ReactionEndMaster0.prevThread = &inputChe3__thread;

		// Swap the nested par handler with the linked list.
		stage6ParHandlerMaster0.prevThread -> nextThread = &stage6ReactionStartMaster0;
		stage6ReactionStartMaster0.prevThread = stage6ParHandlerMaster0.prevThread;
		stage6ReactionEndMaster0.nextThread = stage6ParHandlerMaster0.nextThread;
		stage6ParHandlerMaster0.nextThread -> prevThread = &stage6ReactionEndMaster0;
		
		// Set the core information.
		stage6ParCore0.activeThreads = 4;
		stage6ParCore0.reactionCounter = stage6ParReactionCounter;
		
		// Go to the first thread.
		goto inputChe0__thread;
		asm ("# par3 end");
	} else if (parId == 4) {
		asm ("# par4 begin");
		// Link the threads and handlers together.
		stage6ReactionStartMaster0.programCounter = &&stage6ReactionStartMaster0;
		outputChe0__thread.programCounter = &&outputChe0__thread;
		stage6ReactionStartMaster0.nextThread = &outputChe0__thread;
		outputChe0__thread.prevThread = &stage6ReactionStartMaster0;
		outputChe1__thread.programCounter = &&outputChe1__thread;
		outputChe0__thread.nextThread = &outputChe1__thread;
		outputChe1__thread.prevThread = &outputChe0__thread;
		outputChe2__thread.programCounter = &&outputChe2__thread;
		outputChe1__thread.nextThread = &outputChe2__thread;
		outputChe2__thread.prevThread = &outputChe1__thread;
		outputChe3__thread.programCounter = &&outputChe3__thread;
		outputChe2__thread.nextThread = &outputChe3__thread;
		outputChe3__thread.prevThread = &outputChe2__thread;
		stage6ReactionEndMaster0.programCounter = &&stage6ReactionEndMaster0;
		outputChe3__thread.nextThread = &stage6ReactionEndMaster0;
		stage6ReactionEndMaster0.prevThread = &outputChe3__thread;

		// Swap the nested par handler with the linked list.
		stage6ParHandlerMaster0.prevThread -> nextThread = &stage6ReactionStartMaster0;
		stage6ReactionStartMaster0.prevThread = stage6ParHandlerMaster0.prevThread;
		stage6ReactionEndMaster0.nextThread = stage6ParHandlerMaster0.nextThread;
		stage6ParHandlerMaster0.nextThread -> prevThread = &stage6ReactionEndMaster0;
		
		// Set the core information.
		stage6ParCore0.activeThreads = 4;
		stage6ParCore0.reactionCounter = stage6ParReactionCounter;
		
		// Go to the first thread.
		goto outputChe0__thread;
		asm ("# par4 end");
	} else if (parId == 5) {
		asm ("# par5 begin");
		// Link the threads and handlers together.
		stage6ReactionStartMaster0.programCounter = &&stage6ReactionStartMaster0;
		outputChc0__thread.programCounter = &&outputChc0__thread;
		stage6ReactionStartMaster0.nextThread = &outputChc0__thread;
		outputChc0__thread.prevThread = &stage6ReactionStartMaster0;
		outputChc1__thread.programCounter = &&outputChc1__thread;
		outputChc0__thread.nextThread = &outputChc1__thread;
		outputChc1__thread.prevThread = &outputChc0__thread;
		outputChc2__thread.programCounter = &&outputChc2__thread;
		outputChc1__thread.nextThread = &outputChc2__thread;
		outputChc2__thread.prevThread = &outputChc1__thread;
		outputChc3__thread.programCounter = &&outputChc3__thread;
		outputChc2__thread.nextThread = &outputChc3__thread;
		outputChc3__thread.prevThread = &outputChc2__thread;
		stage6ReactionEndMaster0.programCounter = &&stage6ReactionEndMaster0;
		outputChc3__thread.nextThread = &stage6ReactionEndMaster0;
		stage6ReactionEndMaster0.prevThread = &outputChc3__thread;

		// Swap the nested par handler with the linked list.
		stage6ParHandlerMaster0.prevThread -> nextThread = &stage6ReactionStartMaster0;
		stage6ReactionStartMaster0.prevThread = stage6ParHandlerMaster0.prevThread;
		stage6ReactionEndMaster0.nextThread = stage6ParHandlerMaster0.nextThread;
		stage6ParHandlerMaster0.nextThread -> prevThread = &stage6ReactionEndMaster0;
		
		// Set the core information.
		stage6ParCore0.activeThreads = 4;
		stage6ParCore0.reactionCounter = stage6ParReactionCounter;
		
		// Go to the first thread.
		goto outputChc0__thread;
		asm ("# par5 end");
	} else if (parId == -2) {
		// Iteration
		// Wait for other cores to complete their reaction.

		stage6ParParent.parStatus = FOREC_PAR_OFF;
		stage6ParParent.parId = -1;

		forec_mutex_value_stage6 = -1;

		// Set slave cores' status to reacting.

		// Increment the reaction counter for synchronisation.
		stage6ParReactionCounter++;

		// Return to thread stage6.
		goto *stage6ParParent.programCounter;
	} else if (parId == -3) {
		// Thread termination
		mainParCore0.activeThreads--;
		stage6ParCore0.activeThreads--;

		// Wait for other cores to complete their reaction.

		stage6ParParent.parStatus = FOREC_PAR_OFF;
		stage6ParParent.parId = -1;

		// Set slave cores' status to reacting.

		// Increment the reaction counter for synchronisation.
		stage6ParReactionCounter++;

		// Delete this par(...) handler.
		stage6ParHandlerMaster0.prevThread -> nextThread = stage6ParHandlerMaster0.nextThread;
		stage6ParHandlerMaster0.nextThread -> prevThread = stage6ParHandlerMaster0.prevThread;
			
		// Return to thread stage6.
		goto *stage6ParParent.programCounter;
	} else {
		// Unscheduled par(...)
		stage6ParCore0.reactionCounter = stage6ParReactionCounter;

		stage6ParHandlerMaster0.programCounter = &&wrongParId_stage6ParHandlerMaster0;
		wrongParId_stage6ParHandlerMaster0:;

		stage6ParCore0.status = FOREC_CORE_TERMINATED;

		// Wait for the next reaction.
		while (stage6ParCore0.reactionCounter == stage6ParReactionCounter);
		stage6ParCore0.reactionCounter++;

		// Wait for the par(...) to terminate.
		if (stage6ParParent.parStatus == FOREC_PAR_ON && stage6ParParent.parId == parId) {
			goto *stage6ParHandlerMaster0.nextThread -> programCounter;
		}
		
		// Go back to the top and wait for the next nested par(...)
		stage6ParHandlerMaster0.programCounter = &&stage6ParHandlerMaster0;
		
		goto stage6ParHandlerMaster0;
	}
	
	// Control should not reach here.
	goto stage6ParHandlerMaster0;
}
	// forec:scheduler:parHandler:stage6:master:0:end
 

	// Reaction start handlers ---------------------------------------
	// forec:scheduler:reactionStart:main:master:0:start
	//-- main:
mainReactionStartMaster0: {
	// Go to the next thread.
	goto *mainReactionStartMaster0.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:main:master:0:end
 
	// forec:scheduler:reactionStart:stage6:master:0:start
	//-- stage6:
stage6ReactionStartMaster0: {
	// Go to the next thread.
	goto *stage6ReactionStartMaster0.nextThread -> programCounter;
}
	// forec:scheduler:reactionStart:stage6:master:0:end
 


	// Reaction end handlers ---------------------------------------
	// forec:scheduler:reactionEnd:main:master:0:start
	//-- main:
mainReactionEndMaster0: {
	// Determine if the core can still react or not.
	if (mainParCore0.activeThreads) {
		mainParCore0.status = FOREC_CORE_REACTED;
	} else {
		mainParCore0.status = FOREC_CORE_TERMINATED;
	}
	
	// Wait for other cores to complete their reaction.

	// Reset the mutex.
	forec_mutex_value_stage6 = -1;

	// Combine shared variables.
	int parId = mainParParent.parId;
	if (parId == 0) {

		// freq_sync_correl_2STS_output_stage_0_1__global_0_0
		if (freq_sync_correl_2STS_output_stage_0_1__global_0_0_copy_stage0.status == FOREC_SHARED_MODIFIED) {
			freq_sync_correl_2STS_output_stage_0_1__global_0_0_copy_stage0.status = FOREC_SHARED_UNMODIFIED;
			freq_sync_correl_2STS_output_stage_0_1__global_0_0.value = freq_sync_correl_2STS_output_stage_0_1__global_0_0_copy_stage0.value;
		}

		// freq_sync_correl_2STS_output_stage_1_2__global_0_0
		if (freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage1.status == FOREC_SHARED_MODIFIED) {
			freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage1.status = FOREC_SHARED_UNMODIFIED;
			freq_sync_correl_2STS_output_stage_1_2__global_0_0.value = freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage1.value;
		}

		// freq_sync_correl_2STS_output_stage_2_3__global_0_0
		if (freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage2.status == FOREC_SHARED_MODIFIED) {
			freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage2.status = FOREC_SHARED_UNMODIFIED;
			freq_sync_correl_2STS_output_stage_2_3__global_0_0.value = freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage2.value;
		}

		// correlation_1ST_stage_0_1__global_0_0
		if (correlation_1ST_stage_0_1__global_0_0_copy_stage0.status == FOREC_SHARED_MODIFIED) {
			correlation_1ST_stage_0_1__global_0_0_copy_stage0.status = FOREC_SHARED_UNMODIFIED;
			correlation_1ST_stage_0_1__global_0_0.value = correlation_1ST_stage_0_1__global_0_0_copy_stage0.value;
		}

		// burst_found_pulse_out_stage_1_2__global_0_0
		if (burst_found_pulse_out_stage_1_2__global_0_0_copy_stage1.status == FOREC_SHARED_MODIFIED) {
			burst_found_pulse_out_stage_1_2__global_0_0_copy_stage1.status = FOREC_SHARED_UNMODIFIED;
			burst_found_pulse_out_stage_1_2__global_0_0.value = burst_found_pulse_out_stage_1_2__global_0_0_copy_stage1.value;
		}

		// freq_est_phase_out_stage_1_2__global_0_0
		if (freq_est_phase_out_stage_1_2__global_0_0_copy_stage1.status == FOREC_SHARED_MODIFIED) {
			freq_est_phase_out_stage_1_2__global_0_0_copy_stage1.status = FOREC_SHARED_UNMODIFIED;
			freq_est_phase_out_stage_1_2__global_0_0.value = freq_est_phase_out_stage_1_2__global_0_0_copy_stage1.value;
		}

		// angle_stage_2_3__global_0_0
		if (angle_stage_2_3__global_0_0_copy_stage2.status == FOREC_SHARED_MODIFIED) {
			angle_stage_2_3__global_0_0_copy_stage2.status = FOREC_SHARED_UNMODIFIED;
			angle_stage_2_3__global_0_0.value = angle_stage_2_3__global_0_0_copy_stage2.value;
		}

		// cordic_out_stage_3_4__global_0_0
		if (cordic_out_stage_3_4__global_0_0_copy_stage3.status == FOREC_SHARED_MODIFIED) {
			cordic_out_stage_3_4__global_0_0_copy_stage3.status = FOREC_SHARED_UNMODIFIED;
			cordic_out_stage_3_4__global_0_0.value = cordic_out_stage_3_4__global_0_0_copy_stage3.value;
		}

		// data_out_FT_stage_4_5__global_0_0
		if (data_out_FT_stage_4_5__global_0_0_copy_stage4.status == FOREC_SHARED_MODIFIED) {
			data_out_FT_stage_4_5__global_0_0_copy_stage4.status = FOREC_SHARED_UNMODIFIED;
			data_out_FT_stage_4_5__global_0_0.value = data_out_FT_stage_4_5__global_0_0_copy_stage4.value;
		}

		// maximum_found_stage_4_5__global_0_0
		if (maximum_found_stage_4_5__global_0_0_copy_stage4.status == FOREC_SHARED_MODIFIED) {
			maximum_found_stage_4_5__global_0_0_copy_stage4.status = FOREC_SHARED_UNMODIFIED;
			maximum_found_stage_4_5__global_0_0.value = maximum_found_stage_4_5__global_0_0_copy_stage4.value;
		}

		// maximum_found_stage_5_6__global_0_0
		if (maximum_found_stage_5_6__global_0_0_copy_stage5.status == FOREC_SHARED_MODIFIED) {
			maximum_found_stage_5_6__global_0_0_copy_stage5.status = FOREC_SHARED_UNMODIFIED;
			maximum_found_stage_5_6__global_0_0.value = maximum_found_stage_5_6__global_0_0_copy_stage5.value;
		}

		// burst_found_pulse_for_FT_stage_1_2__global_0_0
		if (burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage1.status == FOREC_SHARED_MODIFIED) {
			burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage1.status = FOREC_SHARED_UNMODIFIED;
			burst_found_pulse_for_FT_stage_1_2__global_0_0.value = burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage1.value;
		}

		// burst_found_pulse_for_FT_stage_2_3__global_0_0
		if (burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage2.status == FOREC_SHARED_MODIFIED) {
			burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage2.status = FOREC_SHARED_UNMODIFIED;
			burst_found_pulse_for_FT_stage_2_3__global_0_0.value = burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage2.value;
		}

		// burst_found_pulse_for_FT_stage_3_4__global_0_0
		if (burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage3.status == FOREC_SHARED_MODIFIED) {
			burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage3.status = FOREC_SHARED_UNMODIFIED;
			burst_found_pulse_for_FT_stage_3_4__global_0_0.value = burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage3.value;
		}

		// re_out__global_0_0
		if (re_out__global_0_0_copy_stage5.status == FOREC_SHARED_MODIFIED) {
			re_out__global_0_0_copy_stage5.status = FOREC_SHARED_UNMODIFIED;
			re_out__global_0_0.value = re_out__global_0_0_copy_stage5.value;
		}

		// im_out__global_0_0
		if (im_out__global_0_0_copy_stage5.status == FOREC_SHARED_MODIFIED) {
			im_out__global_0_0_copy_stage5.status = FOREC_SHARED_UNMODIFIED;
			im_out__global_0_0.value = im_out__global_0_0_copy_stage5.value;
		}
	} else {
		// Nothing.
	}

	// Return back to the parent thread if all the cores have terminated.
	if (1 && mainParCore0.status == FOREC_CORE_TERMINATED) {
		mainParParent.parStatus = FOREC_PAR_OFF;
		mainParParent.parId = -1;
		
		// Set slave cores' status to reacting

		// Increment the reaction counter for synchronization.
		mainParReactionCounter++;

		goto *mainParParent.programCounter;
	}

	// Set slave cores' status to reacting

	// Increment the reaction counter for synchronization.
	mainParReactionCounter++;

	// Go to the next thread.
	goto *mainReactionEndMaster0.nextThread -> programCounter;
}
	// forec:scheduler:reactionEnd:main:master:0:end
 
	// forec:scheduler:reactionEnd:stage6:master:0:start
	//-- stage6:
stage6ReactionEndMaster0: {
	// Determine if the core can still react or not.
	if (stage6ParCore0.activeThreads) {
		stage6ParCore0.status = FOREC_CORE_REACTED;
	} else {
		stage6ParCore0.status = FOREC_CORE_TERMINATED;
	}
	
	// Wait for other cores to complete their reaction.


	// Return back to the parent thread if all the cores have terminated.
	if (1 && stage6ParCore0.status == FOREC_CORE_TERMINATED) {
		forec_mutex_value_stage6 = -1;

		stage6ParParent.parStatus = FOREC_PAR_OFF;
		stage6ParParent.parId = -1;
		
		// Set slave cores' status to reacting

		// Increment the reaction counter for synchronization.
		stage6ParReactionCounter++;

		// Swap the reaction (start & end) handlers with (thread stage6 & nested par handler).
		stage6ReactionStartMaster0.prevThread -> nextThread = &stage6__thread;
		stage6__thread.prevThread = stage6ReactionStartMaster0.prevThread;
		stage6__thread.nextThread = &stage6ParHandlerMaster0;
		stage6ParHandlerMaster0.prevThread = &stage6__thread;
		stage6ParHandlerMaster0.nextThread = stage6ReactionEndMaster0.nextThread;
		stage6ReactionEndMaster0.nextThread -> prevThread = &stage6ParHandlerMaster0;

		goto *stage6ParParent.programCounter;
	}

	// Set slave cores' status to reacting

	// Increment the reaction counter for synchronization.
	stage6ParReactionCounter++;

	// Go to the next thread.
	goto *stage6ReactionEndMaster0.nextThread -> programCounter;
}
	// forec:scheduler:reactionEnd:stage6:master:0:end
 


	// Abort check handlers ----------------------------------------




/*==============================================================
| ForeC threads:
| Threads' code translated into C code.
*=============================================================*/
	// forec:thread:demux0:start
	/*--------------------------------------------------------------
	| Thread demux0
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_array_re__global_0_0 array_re__global_0_0_copy_demux0_local;
	Shared_array_im__global_0_0 array_im__global_0_0_copy_demux0_local;
	Shared_real_out_demux__global_0_0 real_out_demux__global_0_0_copy_demux0_local;
	Shared_imag_out_demux__global_0_0 imag_out_demux__global_0_0_copy_demux0_local;
	float *real_out_demux_ptr__demux0_0_0, *imag_out_demux_ptr__demux0_0_0;
	int i__demux0_0_0;

	// Thread body -------------------------------------------------
	demux0__thread: {
		// Initialise the local copies of shared variables.
		array_re__global_0_0_copy_demux0_local.value = array_re__global_0_0.value;
		array_re__global_0_0_copy_demux0_local.status = FOREC_SHARED_UNMODIFIED;
		array_im__global_0_0_copy_demux0_local.value = array_im__global_0_0.value;
		array_im__global_0_0_copy_demux0_local.status = FOREC_SHARED_UNMODIFIED;
		real_out_demux__global_0_0_copy_demux0_local.value = real_out_demux__global_0_0.value;
		real_out_demux__global_0_0_copy_demux0_local.status = FOREC_SHARED_UNMODIFIED;
		imag_out_demux__global_0_0_copy_demux0_local.value = imag_out_demux__global_0_0.value;
		imag_out_demux__global_0_0_copy_demux0_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		real_out_demux_ptr__demux0_0_0 = real_out_demux__global_0_0_copy_demux0_local.value;
		imag_out_demux_ptr__demux0_0_0 = imag_out_demux__global_0_0_copy_demux0_local.value;
		for (i__demux0_0_0 = 0; i__demux0_0_0 < 16; i__demux0_0_0++) {
			real_out_demux_ptr__demux0_0_0[i__demux0_0_0] = array_re__global_0_0_copy_demux0_local.value[i__demux0_0_0];
			imag_out_demux_ptr__demux0_0_0[i__demux0_0_0] = array_im__global_0_0_copy_demux0_local.value[i__demux0_0_0];
			// forec:iteration:for1_28:bound:16:16
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:demux0:start

		// Delete thread from the linked list and core.
		stage6ParCore0.activeThreads--;
		demux0__thread.nextThread -> prevThread = demux0__thread.prevThread;
		demux0__thread.prevThread -> nextThread = demux0__thread.nextThread;
		goto *demux0__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:demux0:end
	} // demux0__thread
	// forec:thread:demux0:end

	// forec:thread:demux1:start
	/*--------------------------------------------------------------
	| Thread demux1
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_array_re__global_0_0 array_re__global_0_0_copy_demux1_local;
	Shared_array_im__global_0_0 array_im__global_0_0_copy_demux1_local;
	Shared_real_out_demux__global_0_0 real_out_demux__global_0_0_copy_demux1_local;
	Shared_imag_out_demux__global_0_0 imag_out_demux__global_0_0_copy_demux1_local;
	float *real_out_demux_ptr__demux1_0_0, *imag_out_demux_ptr__demux1_0_0;
	int i__demux1_0_0;

	// Thread body -------------------------------------------------
	demux1__thread: {
		// Initialise the local copies of shared variables.
		array_re__global_0_0_copy_demux1_local.value = array_re__global_0_0.value;
		array_re__global_0_0_copy_demux1_local.status = FOREC_SHARED_UNMODIFIED;
		array_im__global_0_0_copy_demux1_local.value = array_im__global_0_0.value;
		array_im__global_0_0_copy_demux1_local.status = FOREC_SHARED_UNMODIFIED;
		real_out_demux__global_0_0_copy_demux1_local.value = real_out_demux__global_0_0.value;
		real_out_demux__global_0_0_copy_demux1_local.status = FOREC_SHARED_UNMODIFIED;
		imag_out_demux__global_0_0_copy_demux1_local.value = imag_out_demux__global_0_0.value;
		imag_out_demux__global_0_0_copy_demux1_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		real_out_demux_ptr__demux1_0_0 = real_out_demux__global_0_0_copy_demux1_local.value;
		imag_out_demux_ptr__demux1_0_0 = imag_out_demux__global_0_0_copy_demux1_local.value;
		for (i__demux1_0_0 = 16; i__demux1_0_0 < 32; i__demux1_0_0++) {
			real_out_demux_ptr__demux1_0_0[i__demux1_0_0] = array_re__global_0_0_copy_demux1_local.value[i__demux1_0_0];
			imag_out_demux_ptr__demux1_0_0[i__demux1_0_0] = array_im__global_0_0_copy_demux1_local.value[i__demux1_0_0];
			// forec:iteration:for1_29:bound:16:16
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:demux1:start

		// Delete thread from the linked list and core.
		stage6ParCore0.activeThreads--;
		demux1__thread.nextThread -> prevThread = demux1__thread.prevThread;
		demux1__thread.prevThread -> nextThread = demux1__thread.nextThread;
		goto *demux1__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:demux1:end
	} // demux1__thread
	// forec:thread:demux1:end

	// forec:thread:demux2:start
	/*--------------------------------------------------------------
	| Thread demux2
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_array_re__global_0_0 array_re__global_0_0_copy_demux2_local;
	Shared_array_im__global_0_0 array_im__global_0_0_copy_demux2_local;
	Shared_real_out_demux__global_0_0 real_out_demux__global_0_0_copy_demux2_local;
	Shared_imag_out_demux__global_0_0 imag_out_demux__global_0_0_copy_demux2_local;
	float *real_out_demux_ptr__demux2_0_0, *imag_out_demux_ptr__demux2_0_0;
	int i__demux2_0_0;

	// Thread body -------------------------------------------------
	demux2__thread: {
		// Initialise the local copies of shared variables.
		array_re__global_0_0_copy_demux2_local.value = array_re__global_0_0.value;
		array_re__global_0_0_copy_demux2_local.status = FOREC_SHARED_UNMODIFIED;
		array_im__global_0_0_copy_demux2_local.value = array_im__global_0_0.value;
		array_im__global_0_0_copy_demux2_local.status = FOREC_SHARED_UNMODIFIED;
		real_out_demux__global_0_0_copy_demux2_local.value = real_out_demux__global_0_0.value;
		real_out_demux__global_0_0_copy_demux2_local.status = FOREC_SHARED_UNMODIFIED;
		imag_out_demux__global_0_0_copy_demux2_local.value = imag_out_demux__global_0_0.value;
		imag_out_demux__global_0_0_copy_demux2_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		real_out_demux_ptr__demux2_0_0 = real_out_demux__global_0_0_copy_demux2_local.value;
		imag_out_demux_ptr__demux2_0_0 = imag_out_demux__global_0_0_copy_demux2_local.value;
		for (i__demux2_0_0 = 32; i__demux2_0_0 < 48; i__demux2_0_0++) {
			real_out_demux_ptr__demux2_0_0[i__demux2_0_0] = array_re__global_0_0_copy_demux2_local.value[i__demux2_0_0];
			imag_out_demux_ptr__demux2_0_0[i__demux2_0_0] = array_im__global_0_0_copy_demux2_local.value[i__demux2_0_0];
			// forec:iteration:for1_30:bound:16:16
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:demux2:start

		// Delete thread from the linked list and core.
		stage6ParCore0.activeThreads--;
		demux2__thread.nextThread -> prevThread = demux2__thread.prevThread;
		demux2__thread.prevThread -> nextThread = demux2__thread.nextThread;
		goto *demux2__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:demux2:end
	} // demux2__thread
	// forec:thread:demux2:end

	// forec:thread:demux3:start
	/*--------------------------------------------------------------
	| Thread demux3
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_array_re__global_0_0 array_re__global_0_0_copy_demux3_local;
	Shared_array_im__global_0_0 array_im__global_0_0_copy_demux3_local;
	Shared_real_out_demux__global_0_0 real_out_demux__global_0_0_copy_demux3_local;
	Shared_imag_out_demux__global_0_0 imag_out_demux__global_0_0_copy_demux3_local;
	float *real_out_demux_ptr__demux3_0_0, *imag_out_demux_ptr__demux3_0_0;
	int i__demux3_0_0;

	// Thread body -------------------------------------------------
	demux3__thread: {
		// Initialise the local copies of shared variables.
		array_re__global_0_0_copy_demux3_local.value = array_re__global_0_0.value;
		array_re__global_0_0_copy_demux3_local.status = FOREC_SHARED_UNMODIFIED;
		array_im__global_0_0_copy_demux3_local.value = array_im__global_0_0.value;
		array_im__global_0_0_copy_demux3_local.status = FOREC_SHARED_UNMODIFIED;
		real_out_demux__global_0_0_copy_demux3_local.value = real_out_demux__global_0_0.value;
		real_out_demux__global_0_0_copy_demux3_local.status = FOREC_SHARED_UNMODIFIED;
		imag_out_demux__global_0_0_copy_demux3_local.value = imag_out_demux__global_0_0.value;
		imag_out_demux__global_0_0_copy_demux3_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		real_out_demux_ptr__demux3_0_0 = real_out_demux__global_0_0_copy_demux3_local.value;
		imag_out_demux_ptr__demux3_0_0 = imag_out_demux__global_0_0_copy_demux3_local.value;
		for (i__demux3_0_0 = 48; i__demux3_0_0 < 64; i__demux3_0_0++) {
			real_out_demux_ptr__demux3_0_0[i__demux3_0_0] = array_re__global_0_0_copy_demux3_local.value[i__demux3_0_0];
			imag_out_demux_ptr__demux3_0_0[i__demux3_0_0] = array_im__global_0_0_copy_demux3_local.value[i__demux3_0_0];
			// forec:iteration:for1_31:bound:16:16
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:demux3:start

		// Delete thread from the linked list and core.
		stage6ParCore0.activeThreads--;
		demux3__thread.nextThread -> prevThread = demux3__thread.prevThread;
		demux3__thread.prevThread -> nextThread = demux3__thread.nextThread;
		goto *demux3__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:demux3:end
	} // demux3__thread
	// forec:thread:demux3:end

	// forec:thread:inputChe0:start
	/*--------------------------------------------------------------
	| Thread inputChe0
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_CHE_flag__global_0_0 CHE_flag__global_0_0_copy_inputChe0_local;
	int *input_CHE_real_ptr__inputChe0_0_0, *input_CHE_imag_ptr__inputChe0_0_0;
	int *data_remove_GI_reorder_real_ptr__inputChe0_0_0, *data_remove_GI_reorder_imag_ptr__inputChe0_0_0;
	int j__inputChe0_0_0;

	// Thread body -------------------------------------------------
	inputChe0__thread: {
		// Initialise the local copies of shared variables.
		CHE_flag__global_0_0_copy_inputChe0_local.value = CHE_flag__global_0_0.value;
		CHE_flag__global_0_0_copy_inputChe0_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		input_CHE_real_ptr__inputChe0_0_0 = input_CHE_real__global_0_0.value;
		input_CHE_imag_ptr__inputChe0_0_0 = input_CHE_imag__global_0_0.value;
		data_remove_GI_reorder_real_ptr__inputChe0_0_0 = data_remove_GI_reorder_real__global_0_0.value;
		data_remove_GI_reorder_imag_ptr__inputChe0_0_0 = data_remove_GI_reorder_imag__global_0_0.value;
		for (j__inputChe0_0_0 = 0; j__inputChe0_0_0 < 13; j__inputChe0_0_0++) {
			if (CHE_flag__global_0_0_copy_inputChe0_local.value == 1) {
				input_CHE_real_ptr__inputChe0_0_0[j__inputChe0_0_0 + ((CHE_flag__global_0_0_copy_inputChe0_local.value - 1)*52)] = (data_remove_GI_reorder_real_ptr__inputChe0_0_0[j__inputChe0_0_0]);
				input_CHE_imag_ptr__inputChe0_0_0[j__inputChe0_0_0 + ((CHE_flag__global_0_0_copy_inputChe0_local.value - 1)*52)] = (data_remove_GI_reorder_imag_ptr__inputChe0_0_0[j__inputChe0_0_0]);
			} else {
				// if87
			}
			if (CHE_flag__global_0_0_copy_inputChe0_local.value == 2) {
				input_CHE_real_ptr__inputChe0_0_0[j__inputChe0_0_0 + ((CHE_flag__global_0_0_copy_inputChe0_local.value - 1)*52)] = (data_remove_GI_reorder_real_ptr__inputChe0_0_0[j__inputChe0_0_0]);
				input_CHE_imag_ptr__inputChe0_0_0[j__inputChe0_0_0 + ((CHE_flag__global_0_0_copy_inputChe0_local.value - 1)*52)] = (data_remove_GI_reorder_imag_ptr__inputChe0_0_0[j__inputChe0_0_0]);
			} else {
				// if88
			}
			// forec:iteration:for1_34:bound:13:13
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:inputChe0:start

		// Delete thread from the linked list and core.
		stage6ParCore0.activeThreads--;
		inputChe0__thread.nextThread -> prevThread = inputChe0__thread.prevThread;
		inputChe0__thread.prevThread -> nextThread = inputChe0__thread.nextThread;
		goto *inputChe0__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:inputChe0:end
	} // inputChe0__thread
	// forec:thread:inputChe0:end

	// forec:thread:inputChe1:start
	/*--------------------------------------------------------------
	| Thread inputChe1
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_CHE_flag__global_0_0 CHE_flag__global_0_0_copy_inputChe1_local;
	int *input_CHE_real_ptr__inputChe1_0_0, *input_CHE_imag_ptr__inputChe1_0_0;
	int *data_remove_GI_reorder_real_ptr__inputChe1_0_0, *data_remove_GI_reorder_imag_ptr__inputChe1_0_0;
	int j__inputChe1_0_0;

	// Thread body -------------------------------------------------
	inputChe1__thread: {
		// Initialise the local copies of shared variables.
		CHE_flag__global_0_0_copy_inputChe1_local.value = CHE_flag__global_0_0.value;
		CHE_flag__global_0_0_copy_inputChe1_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		input_CHE_real_ptr__inputChe1_0_0 = input_CHE_real__global_0_0.value;
		input_CHE_imag_ptr__inputChe1_0_0 = input_CHE_imag__global_0_0.value;
		;
		data_remove_GI_reorder_real_ptr__inputChe1_0_0 = data_remove_GI_reorder_real__global_0_0.value;
		data_remove_GI_reorder_imag_ptr__inputChe1_0_0 = data_remove_GI_reorder_imag__global_0_0.value;
		for (j__inputChe1_0_0 = 13; j__inputChe1_0_0 < 26; j__inputChe1_0_0++) {
			if (CHE_flag__global_0_0_copy_inputChe1_local.value == 1) {
				input_CHE_real_ptr__inputChe1_0_0[j__inputChe1_0_0 + ((CHE_flag__global_0_0_copy_inputChe1_local.value - 1)*52)] = (data_remove_GI_reorder_real_ptr__inputChe1_0_0[j__inputChe1_0_0]);
				input_CHE_imag_ptr__inputChe1_0_0[j__inputChe1_0_0 + ((CHE_flag__global_0_0_copy_inputChe1_local.value - 1)*52)] = (data_remove_GI_reorder_imag_ptr__inputChe1_0_0[j__inputChe1_0_0]);
			} else {
				// if89
			}
			if (CHE_flag__global_0_0_copy_inputChe1_local.value == 2) {
				input_CHE_real_ptr__inputChe1_0_0[j__inputChe1_0_0 + ((CHE_flag__global_0_0_copy_inputChe1_local.value - 1)*52)] = (data_remove_GI_reorder_real_ptr__inputChe1_0_0[j__inputChe1_0_0]);
				input_CHE_imag_ptr__inputChe1_0_0[j__inputChe1_0_0 + ((CHE_flag__global_0_0_copy_inputChe1_local.value - 1)*52)] = (data_remove_GI_reorder_imag_ptr__inputChe1_0_0[j__inputChe1_0_0]);
			} else {
				// if90
			}
			// forec:iteration:for1_35:bound:13:13
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:inputChe1:start

		// Delete thread from the linked list and core.
		stage6ParCore0.activeThreads--;
		inputChe1__thread.nextThread -> prevThread = inputChe1__thread.prevThread;
		inputChe1__thread.prevThread -> nextThread = inputChe1__thread.nextThread;
		goto *inputChe1__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:inputChe1:end
	} // inputChe1__thread
	// forec:thread:inputChe1:end

	// forec:thread:inputChe2:start
	/*--------------------------------------------------------------
	| Thread inputChe2
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_CHE_flag__global_0_0 CHE_flag__global_0_0_copy_inputChe2_local;
	int *input_CHE_real_ptr__inputChe2_0_0, *input_CHE_imag_ptr__inputChe2_0_0;
	int *data_remove_GI_reorder_real_ptr__inputChe2_0_0, *data_remove_GI_reorder_imag_ptr__inputChe2_0_0;
	int j__inputChe2_0_0;

	// Thread body -------------------------------------------------
	inputChe2__thread: {
		// Initialise the local copies of shared variables.
		CHE_flag__global_0_0_copy_inputChe2_local.value = CHE_flag__global_0_0.value;
		CHE_flag__global_0_0_copy_inputChe2_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		input_CHE_real_ptr__inputChe2_0_0 = input_CHE_real__global_0_0.value;
		input_CHE_imag_ptr__inputChe2_0_0 = input_CHE_imag__global_0_0.value;
		data_remove_GI_reorder_real_ptr__inputChe2_0_0 = data_remove_GI_reorder_real__global_0_0.value;
		data_remove_GI_reorder_imag_ptr__inputChe2_0_0 = data_remove_GI_reorder_imag__global_0_0.value;
		for (j__inputChe2_0_0 = 26; j__inputChe2_0_0 < 39; j__inputChe2_0_0++) {
			if (CHE_flag__global_0_0_copy_inputChe2_local.value == 1) {
				input_CHE_real_ptr__inputChe2_0_0[j__inputChe2_0_0 + ((CHE_flag__global_0_0_copy_inputChe2_local.value - 1)*52)] = (data_remove_GI_reorder_real_ptr__inputChe2_0_0[j__inputChe2_0_0]);
				input_CHE_imag_ptr__inputChe2_0_0[j__inputChe2_0_0 + ((CHE_flag__global_0_0_copy_inputChe2_local.value - 1)*52)] = (data_remove_GI_reorder_imag_ptr__inputChe2_0_0[j__inputChe2_0_0]);
			} else {
				// if91
			}
			if (CHE_flag__global_0_0_copy_inputChe2_local.value == 2) {
				input_CHE_real_ptr__inputChe2_0_0[j__inputChe2_0_0 + ((CHE_flag__global_0_0_copy_inputChe2_local.value - 1)*52)] = (data_remove_GI_reorder_real_ptr__inputChe2_0_0[j__inputChe2_0_0]);
				input_CHE_imag_ptr__inputChe2_0_0[j__inputChe2_0_0 + ((CHE_flag__global_0_0_copy_inputChe2_local.value - 1)*52)] = (data_remove_GI_reorder_imag_ptr__inputChe2_0_0[j__inputChe2_0_0]);
			} else {
				// if92
			}
			// forec:iteration:for1_36:bound:13:13
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:inputChe2:start

		// Delete thread from the linked list and core.
		stage6ParCore0.activeThreads--;
		inputChe2__thread.nextThread -> prevThread = inputChe2__thread.prevThread;
		inputChe2__thread.prevThread -> nextThread = inputChe2__thread.nextThread;
		goto *inputChe2__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:inputChe2:end
	} // inputChe2__thread
	// forec:thread:inputChe2:end

	// forec:thread:inputChe3:start
	/*--------------------------------------------------------------
	| Thread inputChe3
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_CHE_flag__global_0_0 CHE_flag__global_0_0_copy_inputChe3_local;
	int *input_CHE_real_ptr__inputChe3_0_0, *input_CHE_imag_ptr__inputChe3_0_0;
	int *data_remove_GI_reorder_real_ptr__inputChe3_0_0, *data_remove_GI_reorder_imag_ptr__inputChe3_0_0;
	int j__inputChe3_0_0;

	// Thread body -------------------------------------------------
	inputChe3__thread: {
		// Initialise the local copies of shared variables.
		CHE_flag__global_0_0_copy_inputChe3_local.value = CHE_flag__global_0_0.value;
		CHE_flag__global_0_0_copy_inputChe3_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		input_CHE_real_ptr__inputChe3_0_0 = input_CHE_real__global_0_0.value;
		input_CHE_imag_ptr__inputChe3_0_0 = input_CHE_imag__global_0_0.value;
		;
		data_remove_GI_reorder_real_ptr__inputChe3_0_0 = data_remove_GI_reorder_real__global_0_0.value;
		data_remove_GI_reorder_imag_ptr__inputChe3_0_0 = data_remove_GI_reorder_imag__global_0_0.value;
		for (j__inputChe3_0_0 = 39; j__inputChe3_0_0 < 52; j__inputChe3_0_0++) {
			if (CHE_flag__global_0_0_copy_inputChe3_local.value == 1) {
				input_CHE_real_ptr__inputChe3_0_0[j__inputChe3_0_0 + ((CHE_flag__global_0_0_copy_inputChe3_local.value - 1)*52)] = (data_remove_GI_reorder_real_ptr__inputChe3_0_0[j__inputChe3_0_0]);
				input_CHE_imag_ptr__inputChe3_0_0[j__inputChe3_0_0 + ((CHE_flag__global_0_0_copy_inputChe3_local.value - 1)*52)] = (data_remove_GI_reorder_imag_ptr__inputChe3_0_0[j__inputChe3_0_0]);
			} else {
				// if93
			}
			if (CHE_flag__global_0_0_copy_inputChe3_local.value == 2) {
				input_CHE_real_ptr__inputChe3_0_0[j__inputChe3_0_0 + ((CHE_flag__global_0_0_copy_inputChe3_local.value - 1)*52)] = (data_remove_GI_reorder_real_ptr__inputChe3_0_0[j__inputChe3_0_0]);
				input_CHE_imag_ptr__inputChe3_0_0[j__inputChe3_0_0 + ((CHE_flag__global_0_0_copy_inputChe3_local.value - 1)*52)] = (data_remove_GI_reorder_imag_ptr__inputChe3_0_0[j__inputChe3_0_0]);
			} else {
				// if94
			}
			// forec:iteration:for1_37:bound:13:13
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:inputChe3:start

		// Delete thread from the linked list and core.
		stage6ParCore0.activeThreads--;
		inputChe3__thread.nextThread -> prevThread = inputChe3__thread.prevThread;
		inputChe3__thread.prevThread -> nextThread = inputChe3__thread.nextThread;
		goto *inputChe3__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:inputChe3:end
	} // inputChe3__thread
	// forec:thread:inputChe3:end

	// forec:thread:outputChc0:start
	/*--------------------------------------------------------------
	| Thread outputChc0
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_output_CHE_real__global_0_0 output_CHE_real__global_0_0_copy_outputChc0_local;
	Shared_output_CHE_imag__global_0_0 output_CHE_imag__global_0_0_copy_outputChc0_local;
	Shared_output_CHC_real__global_0_0 output_CHC_real__global_0_0_copy_outputChc0_local;
	Shared_output_CHC_imag__global_0_0 output_CHC_imag__global_0_0_copy_outputChc0_local;
	int *data_remove_GI_reorder_real_ptr__outputChc0_0_0, *data_remove_GI_reorder_imag_ptr__outputChc0_0_0;
	int *output_CHE_real_ptr__outputChc0_0_0, *output_CHE_imag_ptr__outputChc0_0_0;
	int *output_CHC_real_ptr__outputChc0_0_0, *output_CHC_imag_ptr__outputChc0_0_0;
	int i__outputChc0_0_0;
	long int mult_CHC_I__outputChc0_1_0;
	long int mult_CHC_Q__outputChc0_1_0;

	// Thread body -------------------------------------------------
	outputChc0__thread: {
		// Initialise the local copies of shared variables.
		output_CHE_real__global_0_0_copy_outputChc0_local.value = output_CHE_real__global_0_0.value;
		output_CHE_real__global_0_0_copy_outputChc0_local.status = FOREC_SHARED_UNMODIFIED;
		output_CHE_imag__global_0_0_copy_outputChc0_local.value = output_CHE_imag__global_0_0.value;
		output_CHE_imag__global_0_0_copy_outputChc0_local.status = FOREC_SHARED_UNMODIFIED;
		output_CHC_real__global_0_0_copy_outputChc0_local.value = output_CHC_real__global_0_0.value;
		output_CHC_real__global_0_0_copy_outputChc0_local.status = FOREC_SHARED_UNMODIFIED;
		output_CHC_imag__global_0_0_copy_outputChc0_local.value = output_CHC_imag__global_0_0.value;
		output_CHC_imag__global_0_0_copy_outputChc0_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		data_remove_GI_reorder_real_ptr__outputChc0_0_0 = data_remove_GI_reorder_real__global_0_0.value;
		data_remove_GI_reorder_imag_ptr__outputChc0_0_0 = data_remove_GI_reorder_imag__global_0_0.value;
		output_CHE_real_ptr__outputChc0_0_0 = output_CHE_real__global_0_0_copy_outputChc0_local.value;
		output_CHE_imag_ptr__outputChc0_0_0 = output_CHE_imag__global_0_0_copy_outputChc0_local.value;
		output_CHC_real_ptr__outputChc0_0_0 = output_CHC_real__global_0_0_copy_outputChc0_local.value;
		output_CHC_imag_ptr__outputChc0_0_0 = output_CHC_imag__global_0_0_copy_outputChc0_local.value;
		for (i__outputChc0_0_0 = 0; i__outputChc0_0_0 < 13; i__outputChc0_0_0++) {
			mult_CHC_I__outputChc0_1_0 = data_remove_GI_reorder_real_ptr__outputChc0_0_0[i__outputChc0_0_0]*output_CHE_real_ptr__outputChc0_0_0[i__outputChc0_0_0] + data_remove_GI_reorder_imag__global_0_0.value[i__outputChc0_0_0]*output_CHE_imag_ptr__outputChc0_0_0[i__outputChc0_0_0];
			mult_CHC_Q__outputChc0_1_0 = -data_remove_GI_reorder_real_ptr__outputChc0_0_0[i__outputChc0_0_0]*output_CHE_imag_ptr__outputChc0_0_0[i__outputChc0_0_0] + data_remove_GI_reorder_imag__global_0_0.value[i__outputChc0_0_0]*output_CHE_real_ptr__outputChc0_0_0[i__outputChc0_0_0];
			output_CHC_real_ptr__outputChc0_0_0[i__outputChc0_0_0] = (mult_CHC_I__outputChc0_1_0/1024);
			output_CHC_imag_ptr__outputChc0_0_0[i__outputChc0_0_0] = (mult_CHC_Q__outputChc0_1_0/1024);
			// forec:iteration:for1_42:bound:13:13
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:outputChc0:start

		// Delete thread from the linked list and core.
		stage6ParCore0.activeThreads--;
		outputChc0__thread.nextThread -> prevThread = outputChc0__thread.prevThread;
		outputChc0__thread.prevThread -> nextThread = outputChc0__thread.nextThread;
		goto *outputChc0__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:outputChc0:end
	} // outputChc0__thread
	// forec:thread:outputChc0:end

	// forec:thread:outputChc1:start
	/*--------------------------------------------------------------
	| Thread outputChc1
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_output_CHE_real__global_0_0 output_CHE_real__global_0_0_copy_outputChc1_local;
	Shared_output_CHE_imag__global_0_0 output_CHE_imag__global_0_0_copy_outputChc1_local;
	Shared_output_CHC_real__global_0_0 output_CHC_real__global_0_0_copy_outputChc1_local;
	Shared_output_CHC_imag__global_0_0 output_CHC_imag__global_0_0_copy_outputChc1_local;
	int *data_remove_GI_reorder_real_ptr__outputChc1_0_0, *data_remove_GI_reorder_imag_ptr__outputChc1_0_0;
	int *output_CHE_real_ptr__outputChc1_0_0, *output_CHE_imag_ptr__outputChc1_0_0;
	int *output_CHC_real_ptr__outputChc1_0_0, *output_CHC_imag_ptr__outputChc1_0_0;
	int i__outputChc1_0_0;
	long int mult_CHC_I__outputChc1_1_0;
	long int mult_CHC_Q__outputChc1_1_0;

	// Thread body -------------------------------------------------
	outputChc1__thread: {
		// Initialise the local copies of shared variables.
		output_CHE_real__global_0_0_copy_outputChc1_local.value = output_CHE_real__global_0_0.value;
		output_CHE_real__global_0_0_copy_outputChc1_local.status = FOREC_SHARED_UNMODIFIED;
		output_CHE_imag__global_0_0_copy_outputChc1_local.value = output_CHE_imag__global_0_0.value;
		output_CHE_imag__global_0_0_copy_outputChc1_local.status = FOREC_SHARED_UNMODIFIED;
		output_CHC_real__global_0_0_copy_outputChc1_local.value = output_CHC_real__global_0_0.value;
		output_CHC_real__global_0_0_copy_outputChc1_local.status = FOREC_SHARED_UNMODIFIED;
		output_CHC_imag__global_0_0_copy_outputChc1_local.value = output_CHC_imag__global_0_0.value;
		output_CHC_imag__global_0_0_copy_outputChc1_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		data_remove_GI_reorder_real_ptr__outputChc1_0_0 = data_remove_GI_reorder_real__global_0_0.value;
		data_remove_GI_reorder_imag_ptr__outputChc1_0_0 = data_remove_GI_reorder_imag__global_0_0.value;
		output_CHE_real_ptr__outputChc1_0_0 = output_CHE_real__global_0_0_copy_outputChc1_local.value;
		output_CHE_imag_ptr__outputChc1_0_0 = output_CHE_imag__global_0_0_copy_outputChc1_local.value;
		output_CHC_real_ptr__outputChc1_0_0 = output_CHC_real__global_0_0_copy_outputChc1_local.value;
		output_CHC_imag_ptr__outputChc1_0_0 = output_CHC_imag__global_0_0_copy_outputChc1_local.value;
		for (i__outputChc1_0_0 = 13; i__outputChc1_0_0 < 26; i__outputChc1_0_0++) {
			mult_CHC_I__outputChc1_1_0 = data_remove_GI_reorder_real_ptr__outputChc1_0_0[i__outputChc1_0_0]*output_CHE_real_ptr__outputChc1_0_0[i__outputChc1_0_0] + data_remove_GI_reorder_imag__global_0_0.value[i__outputChc1_0_0]*output_CHE_imag_ptr__outputChc1_0_0[i__outputChc1_0_0];
			mult_CHC_Q__outputChc1_1_0 = -data_remove_GI_reorder_real_ptr__outputChc1_0_0[i__outputChc1_0_0]*output_CHE_imag_ptr__outputChc1_0_0[i__outputChc1_0_0] + data_remove_GI_reorder_imag__global_0_0.value[i__outputChc1_0_0]*output_CHE_real_ptr__outputChc1_0_0[i__outputChc1_0_0];
			output_CHC_real_ptr__outputChc1_0_0[i__outputChc1_0_0] = (mult_CHC_I__outputChc1_1_0/1024);
			output_CHC_imag_ptr__outputChc1_0_0[i__outputChc1_0_0] = (mult_CHC_Q__outputChc1_1_0/1024);
			// forec:iteration:for1_43:bound:13:13
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:outputChc1:start

		// Delete thread from the linked list and core.
		stage6ParCore0.activeThreads--;
		outputChc1__thread.nextThread -> prevThread = outputChc1__thread.prevThread;
		outputChc1__thread.prevThread -> nextThread = outputChc1__thread.nextThread;
		goto *outputChc1__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:outputChc1:end
	} // outputChc1__thread
	// forec:thread:outputChc1:end

	// forec:thread:outputChc2:start
	/*--------------------------------------------------------------
	| Thread outputChc2
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_output_CHE_real__global_0_0 output_CHE_real__global_0_0_copy_outputChc2_local;
	Shared_output_CHE_imag__global_0_0 output_CHE_imag__global_0_0_copy_outputChc2_local;
	Shared_output_CHC_real__global_0_0 output_CHC_real__global_0_0_copy_outputChc2_local;
	Shared_output_CHC_imag__global_0_0 output_CHC_imag__global_0_0_copy_outputChc2_local;
	int *data_remove_GI_reorder_real_ptr__outputChc2_0_0, *data_remove_GI_reorder_imag_ptr__outputChc2_0_0;
	int *output_CHE_real_ptr__outputChc2_0_0, *output_CHE_imag_ptr__outputChc2_0_0;
	int *output_CHC_real_ptr__outputChc2_0_0, *output_CHC_imag_ptr__outputChc2_0_0;
	int i__outputChc2_0_0;
	long int mult_CHC_I__outputChc2_1_0;
	long int mult_CHC_Q__outputChc2_1_0;

	// Thread body -------------------------------------------------
	outputChc2__thread: {
		// Initialise the local copies of shared variables.
		output_CHE_real__global_0_0_copy_outputChc2_local.value = output_CHE_real__global_0_0.value;
		output_CHE_real__global_0_0_copy_outputChc2_local.status = FOREC_SHARED_UNMODIFIED;
		output_CHE_imag__global_0_0_copy_outputChc2_local.value = output_CHE_imag__global_0_0.value;
		output_CHE_imag__global_0_0_copy_outputChc2_local.status = FOREC_SHARED_UNMODIFIED;
		output_CHC_real__global_0_0_copy_outputChc2_local.value = output_CHC_real__global_0_0.value;
		output_CHC_real__global_0_0_copy_outputChc2_local.status = FOREC_SHARED_UNMODIFIED;
		output_CHC_imag__global_0_0_copy_outputChc2_local.value = output_CHC_imag__global_0_0.value;
		output_CHC_imag__global_0_0_copy_outputChc2_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		data_remove_GI_reorder_real_ptr__outputChc2_0_0 = data_remove_GI_reorder_real__global_0_0.value;
		data_remove_GI_reorder_imag_ptr__outputChc2_0_0 = data_remove_GI_reorder_imag__global_0_0.value;
		output_CHE_real_ptr__outputChc2_0_0 = output_CHE_real__global_0_0_copy_outputChc2_local.value;
		output_CHE_imag_ptr__outputChc2_0_0 = output_CHE_imag__global_0_0_copy_outputChc2_local.value;
		output_CHC_real_ptr__outputChc2_0_0 = output_CHC_real__global_0_0_copy_outputChc2_local.value;
		output_CHC_imag_ptr__outputChc2_0_0 = output_CHC_imag__global_0_0_copy_outputChc2_local.value;
		for (i__outputChc2_0_0 = 26; i__outputChc2_0_0 < 39; i__outputChc2_0_0++) {
			mult_CHC_I__outputChc2_1_0 = data_remove_GI_reorder_real_ptr__outputChc2_0_0[i__outputChc2_0_0]*output_CHE_real_ptr__outputChc2_0_0[i__outputChc2_0_0] + data_remove_GI_reorder_imag__global_0_0.value[i__outputChc2_0_0]*output_CHE_imag_ptr__outputChc2_0_0[i__outputChc2_0_0];
			mult_CHC_Q__outputChc2_1_0 = -data_remove_GI_reorder_real_ptr__outputChc2_0_0[i__outputChc2_0_0]*output_CHE_imag_ptr__outputChc2_0_0[i__outputChc2_0_0] + data_remove_GI_reorder_imag__global_0_0.value[i__outputChc2_0_0]*output_CHE_real_ptr__outputChc2_0_0[i__outputChc2_0_0];
			output_CHC_real_ptr__outputChc2_0_0[i__outputChc2_0_0] = (mult_CHC_I__outputChc2_1_0/1024);
			output_CHC_imag_ptr__outputChc2_0_0[i__outputChc2_0_0] = (mult_CHC_Q__outputChc2_1_0/1024);
			// forec:iteration:for1_44:bound:13:13
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:outputChc2:start

		// Delete thread from the linked list and core.
		stage6ParCore0.activeThreads--;
		outputChc2__thread.nextThread -> prevThread = outputChc2__thread.prevThread;
		outputChc2__thread.prevThread -> nextThread = outputChc2__thread.nextThread;
		goto *outputChc2__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:outputChc2:end
	} // outputChc2__thread
	// forec:thread:outputChc2:end

	// forec:thread:outputChc3:start
	/*--------------------------------------------------------------
	| Thread outputChc3
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_output_CHE_real__global_0_0 output_CHE_real__global_0_0_copy_outputChc3_local;
	Shared_output_CHE_imag__global_0_0 output_CHE_imag__global_0_0_copy_outputChc3_local;
	Shared_output_CHC_real__global_0_0 output_CHC_real__global_0_0_copy_outputChc3_local;
	Shared_output_CHC_imag__global_0_0 output_CHC_imag__global_0_0_copy_outputChc3_local;
	int *data_remove_GI_reorder_real_ptr__outputChc3_0_0, *data_remove_GI_reorder_imag_ptr__outputChc3_0_0;
	int *output_CHE_real_ptr__outputChc3_0_0, *output_CHE_imag_ptr__outputChc3_0_0;
	int *output_CHC_real_ptr__outputChc3_0_0, *output_CHC_imag_ptr__outputChc3_0_0;
	int i__outputChc3_0_0;
	long int mult_CHC_I__outputChc3_1_0;
	long int mult_CHC_Q__outputChc3_1_0;

	// Thread body -------------------------------------------------
	outputChc3__thread: {
		// Initialise the local copies of shared variables.
		output_CHE_real__global_0_0_copy_outputChc3_local.value = output_CHE_real__global_0_0.value;
		output_CHE_real__global_0_0_copy_outputChc3_local.status = FOREC_SHARED_UNMODIFIED;
		output_CHE_imag__global_0_0_copy_outputChc3_local.value = output_CHE_imag__global_0_0.value;
		output_CHE_imag__global_0_0_copy_outputChc3_local.status = FOREC_SHARED_UNMODIFIED;
		output_CHC_real__global_0_0_copy_outputChc3_local.value = output_CHC_real__global_0_0.value;
		output_CHC_real__global_0_0_copy_outputChc3_local.status = FOREC_SHARED_UNMODIFIED;
		output_CHC_imag__global_0_0_copy_outputChc3_local.value = output_CHC_imag__global_0_0.value;
		output_CHC_imag__global_0_0_copy_outputChc3_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		data_remove_GI_reorder_real_ptr__outputChc3_0_0 = data_remove_GI_reorder_real__global_0_0.value;
		data_remove_GI_reorder_imag_ptr__outputChc3_0_0 = data_remove_GI_reorder_imag__global_0_0.value;
		output_CHE_real_ptr__outputChc3_0_0 = output_CHE_real__global_0_0_copy_outputChc3_local.value;
		output_CHE_imag_ptr__outputChc3_0_0 = output_CHE_imag__global_0_0_copy_outputChc3_local.value;
		output_CHC_real_ptr__outputChc3_0_0 = output_CHC_real__global_0_0_copy_outputChc3_local.value;
		output_CHC_imag_ptr__outputChc3_0_0 = output_CHC_imag__global_0_0_copy_outputChc3_local.value;
		for (i__outputChc3_0_0 = 39; i__outputChc3_0_0 < 52; i__outputChc3_0_0++) {
			mult_CHC_I__outputChc3_1_0 = data_remove_GI_reorder_real_ptr__outputChc3_0_0[i__outputChc3_0_0]*output_CHE_real_ptr__outputChc3_0_0[i__outputChc3_0_0] + data_remove_GI_reorder_imag__global_0_0.value[i__outputChc3_0_0]*output_CHE_imag_ptr__outputChc3_0_0[i__outputChc3_0_0];
			mult_CHC_Q__outputChc3_1_0 = -data_remove_GI_reorder_real_ptr__outputChc3_0_0[i__outputChc3_0_0]*output_CHE_imag_ptr__outputChc3_0_0[i__outputChc3_0_0] + data_remove_GI_reorder_imag__global_0_0.value[i__outputChc3_0_0]*output_CHE_real_ptr__outputChc3_0_0[i__outputChc3_0_0];
			output_CHC_real_ptr__outputChc3_0_0[i__outputChc3_0_0] = (mult_CHC_I__outputChc3_1_0/1024);
			output_CHC_imag_ptr__outputChc3_0_0[i__outputChc3_0_0] = (mult_CHC_Q__outputChc3_1_0/1024);
			// forec:iteration:for1_45:bound:13:13
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:outputChc3:start

		// Delete thread from the linked list and core.
		stage6ParCore0.activeThreads--;
		outputChc3__thread.nextThread -> prevThread = outputChc3__thread.prevThread;
		outputChc3__thread.prevThread -> nextThread = outputChc3__thread.nextThread;
		goto *outputChc3__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:outputChc3:end
	} // outputChc3__thread
	// forec:thread:outputChc3:end

	// forec:thread:outputChe0:start
	/*--------------------------------------------------------------
	| Thread outputChe0
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_output_CHE_real__global_0_0 output_CHE_real__global_0_0_copy_outputChe0_local;
	Shared_output_CHE_imag__global_0_0 output_CHE_imag__global_0_0_copy_outputChe0_local;
	int *input_CHE_real_ptr__outputChe0_0_0, *input_CHE_imag_ptr__outputChe0_0_0;
	int *output_CHE_real_ptr__outputChe0_0_0, *output_CHE_imag_ptr__outputChe0_0_0;
	int i__outputChe0_0_0;

	// Thread body -------------------------------------------------
	outputChe0__thread: {
		// Initialise the local copies of shared variables.
		output_CHE_real__global_0_0_copy_outputChe0_local.value = output_CHE_real__global_0_0.value;
		output_CHE_real__global_0_0_copy_outputChe0_local.status = FOREC_SHARED_UNMODIFIED;
		output_CHE_imag__global_0_0_copy_outputChe0_local.value = output_CHE_imag__global_0_0.value;
		output_CHE_imag__global_0_0_copy_outputChe0_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		input_CHE_real_ptr__outputChe0_0_0 = input_CHE_real__global_0_0.value;
		input_CHE_imag_ptr__outputChe0_0_0 = input_CHE_imag__global_0_0.value;
		output_CHE_real_ptr__outputChe0_0_0 = output_CHE_real__global_0_0_copy_outputChe0_local.value;
		output_CHE_imag_ptr__outputChe0_0_0 = output_CHE_imag__global_0_0_copy_outputChe0_local.value;
		for (i__outputChe0_0_0 = 0; i__outputChe0_0_0 < 13; i__outputChe0_0_0++) {
			output_CHE_real_ptr__outputChe0_0_0[i__outputChe0_0_0] = ((input_CHE_real_ptr__outputChe0_0_0[i__outputChe0_0_0] + input_CHE_real_ptr__outputChe0_0_0[i__outputChe0_0_0 + 52])/2*long_pattern__global_0_0.value[i__outputChe0_0_0]);
			output_CHE_imag_ptr__outputChe0_0_0[i__outputChe0_0_0] = ((input_CHE_imag_ptr__outputChe0_0_0[i__outputChe0_0_0] + input_CHE_imag_ptr__outputChe0_0_0[i__outputChe0_0_0 + 52])/2*long_pattern__global_0_0.value[i__outputChe0_0_0]);
			// forec:iteration:for1_38:bound:13:13
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:outputChe0:start

		// Delete thread from the linked list and core.
		stage6ParCore0.activeThreads--;
		outputChe0__thread.nextThread -> prevThread = outputChe0__thread.prevThread;
		outputChe0__thread.prevThread -> nextThread = outputChe0__thread.nextThread;
		goto *outputChe0__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:outputChe0:end
	} // outputChe0__thread
	// forec:thread:outputChe0:end

	// forec:thread:outputChe1:start
	/*--------------------------------------------------------------
	| Thread outputChe1
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_output_CHE_real__global_0_0 output_CHE_real__global_0_0_copy_outputChe1_local;
	Shared_output_CHE_imag__global_0_0 output_CHE_imag__global_0_0_copy_outputChe1_local;
	int *input_CHE_real_ptr__outputChe1_0_0, *input_CHE_imag_ptr__outputChe1_0_0;
	int *output_CHE_real_ptr__outputChe1_0_0, *output_CHE_imag_ptr__outputChe1_0_0;
	int i__outputChe1_0_0;

	// Thread body -------------------------------------------------
	outputChe1__thread: {
		// Initialise the local copies of shared variables.
		output_CHE_real__global_0_0_copy_outputChe1_local.value = output_CHE_real__global_0_0.value;
		output_CHE_real__global_0_0_copy_outputChe1_local.status = FOREC_SHARED_UNMODIFIED;
		output_CHE_imag__global_0_0_copy_outputChe1_local.value = output_CHE_imag__global_0_0.value;
		output_CHE_imag__global_0_0_copy_outputChe1_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		input_CHE_real_ptr__outputChe1_0_0 = input_CHE_real__global_0_0.value;
		input_CHE_imag_ptr__outputChe1_0_0 = input_CHE_imag__global_0_0.value;
		output_CHE_real_ptr__outputChe1_0_0 = output_CHE_real__global_0_0_copy_outputChe1_local.value;
		output_CHE_imag_ptr__outputChe1_0_0 = output_CHE_imag__global_0_0_copy_outputChe1_local.value;
		for (i__outputChe1_0_0 = 13; i__outputChe1_0_0 < 26; i__outputChe1_0_0++) {
			output_CHE_real_ptr__outputChe1_0_0[i__outputChe1_0_0] = ((input_CHE_real_ptr__outputChe1_0_0[i__outputChe1_0_0] + input_CHE_real_ptr__outputChe1_0_0[i__outputChe1_0_0 + 52])/2*long_pattern__global_0_0.value[i__outputChe1_0_0]);
			output_CHE_imag_ptr__outputChe1_0_0[i__outputChe1_0_0] = ((input_CHE_imag_ptr__outputChe1_0_0[i__outputChe1_0_0] + input_CHE_imag_ptr__outputChe1_0_0[i__outputChe1_0_0 + 52])/2*long_pattern__global_0_0.value[i__outputChe1_0_0]);
			// forec:iteration:for1_39:bound:13:13
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:outputChe1:start

		// Delete thread from the linked list and core.
		stage6ParCore0.activeThreads--;
		outputChe1__thread.nextThread -> prevThread = outputChe1__thread.prevThread;
		outputChe1__thread.prevThread -> nextThread = outputChe1__thread.nextThread;
		goto *outputChe1__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:outputChe1:end
	} // outputChe1__thread
	// forec:thread:outputChe1:end

	// forec:thread:outputChe2:start
	/*--------------------------------------------------------------
	| Thread outputChe2
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_output_CHE_real__global_0_0 output_CHE_real__global_0_0_copy_outputChe2_local;
	Shared_output_CHE_imag__global_0_0 output_CHE_imag__global_0_0_copy_outputChe2_local;
	int *input_CHE_real_ptr__outputChe2_0_0, *input_CHE_imag_ptr__outputChe2_0_0;
	int *output_CHE_real_ptr__outputChe2_0_0, *output_CHE_imag_ptr__outputChe2_0_0;
	int i__outputChe2_0_0;

	// Thread body -------------------------------------------------
	outputChe2__thread: {
		// Initialise the local copies of shared variables.
		output_CHE_real__global_0_0_copy_outputChe2_local.value = output_CHE_real__global_0_0.value;
		output_CHE_real__global_0_0_copy_outputChe2_local.status = FOREC_SHARED_UNMODIFIED;
		output_CHE_imag__global_0_0_copy_outputChe2_local.value = output_CHE_imag__global_0_0.value;
		output_CHE_imag__global_0_0_copy_outputChe2_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		input_CHE_real_ptr__outputChe2_0_0 = input_CHE_real__global_0_0.value;
		input_CHE_imag_ptr__outputChe2_0_0 = input_CHE_imag__global_0_0.value;
		output_CHE_real_ptr__outputChe2_0_0 = output_CHE_real__global_0_0_copy_outputChe2_local.value;
		output_CHE_imag_ptr__outputChe2_0_0 = output_CHE_imag__global_0_0_copy_outputChe2_local.value;
		for (i__outputChe2_0_0 = 26; i__outputChe2_0_0 < 39; i__outputChe2_0_0++) {
			output_CHE_real_ptr__outputChe2_0_0[i__outputChe2_0_0] = ((input_CHE_real_ptr__outputChe2_0_0[i__outputChe2_0_0] + input_CHE_real_ptr__outputChe2_0_0[i__outputChe2_0_0 + 52])/2*long_pattern__global_0_0.value[i__outputChe2_0_0]);
			output_CHE_imag_ptr__outputChe2_0_0[i__outputChe2_0_0] = ((input_CHE_imag_ptr__outputChe2_0_0[i__outputChe2_0_0] + input_CHE_imag_ptr__outputChe2_0_0[i__outputChe2_0_0 + 52])/2*long_pattern__global_0_0.value[i__outputChe2_0_0]);
			// forec:iteration:for1_40:bound:13:13
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:outputChe2:start

		// Delete thread from the linked list and core.
		stage6ParCore0.activeThreads--;
		outputChe2__thread.nextThread -> prevThread = outputChe2__thread.prevThread;
		outputChe2__thread.prevThread -> nextThread = outputChe2__thread.nextThread;
		goto *outputChe2__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:outputChe2:end
	} // outputChe2__thread
	// forec:thread:outputChe2:end

	// forec:thread:outputChe3:start
	/*--------------------------------------------------------------
	| Thread outputChe3
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_output_CHE_real__global_0_0 output_CHE_real__global_0_0_copy_outputChe3_local;
	Shared_output_CHE_imag__global_0_0 output_CHE_imag__global_0_0_copy_outputChe3_local;
	int *input_CHE_real_ptr__outputChe3_0_0, *input_CHE_imag_ptr__outputChe3_0_0;
	int *output_CHE_real_ptr__outputChe3_0_0, *output_CHE_imag_ptr__outputChe3_0_0;
	int i__outputChe3_0_0;

	// Thread body -------------------------------------------------
	outputChe3__thread: {
		// Initialise the local copies of shared variables.
		output_CHE_real__global_0_0_copy_outputChe3_local.value = output_CHE_real__global_0_0.value;
		output_CHE_real__global_0_0_copy_outputChe3_local.status = FOREC_SHARED_UNMODIFIED;
		output_CHE_imag__global_0_0_copy_outputChe3_local.value = output_CHE_imag__global_0_0.value;
		output_CHE_imag__global_0_0_copy_outputChe3_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		input_CHE_real_ptr__outputChe3_0_0 = input_CHE_real__global_0_0.value;
		input_CHE_imag_ptr__outputChe3_0_0 = input_CHE_imag__global_0_0.value;
		output_CHE_real_ptr__outputChe3_0_0 = output_CHE_real__global_0_0_copy_outputChe3_local.value;
		output_CHE_imag_ptr__outputChe3_0_0 = output_CHE_imag__global_0_0_copy_outputChe3_local.value;
		for (i__outputChe3_0_0 = 39; i__outputChe3_0_0 < 52; i__outputChe3_0_0++) {
			output_CHE_real_ptr__outputChe3_0_0[i__outputChe3_0_0] = ((input_CHE_real_ptr__outputChe3_0_0[i__outputChe3_0_0] + input_CHE_real_ptr__outputChe3_0_0[i__outputChe3_0_0 + 52])/2*long_pattern__global_0_0.value[i__outputChe3_0_0]);
			output_CHE_imag_ptr__outputChe3_0_0[i__outputChe3_0_0] = ((input_CHE_imag_ptr__outputChe3_0_0[i__outputChe3_0_0] + input_CHE_imag_ptr__outputChe3_0_0[i__outputChe3_0_0 + 52])/2*long_pattern__global_0_0.value[i__outputChe3_0_0]);
			// forec:iteration:for1_41:bound:13:13
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:outputChe3:start

		// Delete thread from the linked list and core.
		stage6ParCore0.activeThreads--;
		outputChe3__thread.nextThread -> prevThread = outputChe3__thread.prevThread;
		outputChe3__thread.prevThread -> nextThread = outputChe3__thread.nextThread;
		goto *outputChe3__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:outputChe3:end
	} // outputChe3__thread
	// forec:thread:outputChe3:end

	// forec:thread:removeReorder0:start
	/*--------------------------------------------------------------
	| Thread removeReorder0
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_real_out_demux__global_0_0 real_out_demux__global_0_0_copy_removeReorder0_local;
	Shared_imag_out_demux__global_0_0 imag_out_demux__global_0_0_copy_removeReorder0_local;
	float FFT_output_scale__removeReorder0_0_0;
	float *real_out_demux_ptr__removeReorder0_0_0, *imag_out_demux_ptr__removeReorder0_0_0;
	int *data_remove_GI_reorder_real_ptr__removeReorder0_0_0, *data_remove_GI_reorder_imag_ptr__removeReorder0_0_0;
	int j__removeReorder0_0_0;

	// Thread body -------------------------------------------------
	removeReorder0__thread: {
		// Initialise the local copies of shared variables.
		real_out_demux__global_0_0_copy_removeReorder0_local.value = real_out_demux__global_0_0.value;
		real_out_demux__global_0_0_copy_removeReorder0_local.status = FOREC_SHARED_UNMODIFIED;
		imag_out_demux__global_0_0_copy_removeReorder0_local.value = imag_out_demux__global_0_0.value;
		imag_out_demux__global_0_0_copy_removeReorder0_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		FFT_output_scale__removeReorder0_0_0 = ((float)11.0)/((float)8.0);
		real_out_demux_ptr__removeReorder0_0_0 = real_out_demux__global_0_0_copy_removeReorder0_local.value;
		imag_out_demux_ptr__removeReorder0_0_0 = imag_out_demux__global_0_0_copy_removeReorder0_local.value;
		data_remove_GI_reorder_real_ptr__removeReorder0_0_0 = data_remove_GI_reorder_real__global_0_0.value;
		data_remove_GI_reorder_imag_ptr__removeReorder0_0_0 = data_remove_GI_reorder_imag__global_0_0.value;
		for (j__removeReorder0_0_0 = 0; j__removeReorder0_0_0 < 13; j__removeReorder0_0_0++) {
			data_remove_GI_reorder_real_ptr__removeReorder0_0_0[j__removeReorder0_0_0 + 26] = (int)(FFT_output_scale__removeReorder0_0_0*real_out_demux_ptr__removeReorder0_0_0[j__removeReorder0_0_0 + 1]);
			data_remove_GI_reorder_imag_ptr__removeReorder0_0_0[j__removeReorder0_0_0 + 26] = (int)(FFT_output_scale__removeReorder0_0_0*imag_out_demux_ptr__removeReorder0_0_0[j__removeReorder0_0_0 + 1]);
			data_remove_GI_reorder_real_ptr__removeReorder0_0_0[j__removeReorder0_0_0] = (int)(FFT_output_scale__removeReorder0_0_0*real_out_demux_ptr__removeReorder0_0_0[j__removeReorder0_0_0 + 38]);
			data_remove_GI_reorder_imag_ptr__removeReorder0_0_0[j__removeReorder0_0_0] = (int)(FFT_output_scale__removeReorder0_0_0*imag_out_demux_ptr__removeReorder0_0_0[j__removeReorder0_0_0 + 38]);
			// forec:iteration:for1_32:bound:13:13
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:removeReorder0:start

		// Delete thread from the linked list and core.
		stage6ParCore0.activeThreads--;
		removeReorder0__thread.nextThread -> prevThread = removeReorder0__thread.prevThread;
		removeReorder0__thread.prevThread -> nextThread = removeReorder0__thread.nextThread;
		goto *removeReorder0__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:removeReorder0:end
	} // removeReorder0__thread
	// forec:thread:removeReorder0:end

	// forec:thread:removeReorder1:start
	/*--------------------------------------------------------------
	| Thread removeReorder1
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_real_out_demux__global_0_0 real_out_demux__global_0_0_copy_removeReorder1_local;
	Shared_imag_out_demux__global_0_0 imag_out_demux__global_0_0_copy_removeReorder1_local;
	float FFT_output_scale__removeReorder1_0_0;
	float *real_out_demux_ptr__removeReorder1_0_0, *imag_out_demux_ptr__removeReorder1_0_0;
	int *data_remove_GI_reorder_real_ptr__removeReorder1_0_0, *data_remove_GI_reorder_imag_ptr__removeReorder1_0_0;
	int j__removeReorder1_0_0;

	// Thread body -------------------------------------------------
	removeReorder1__thread: {
		// Initialise the local copies of shared variables.
		real_out_demux__global_0_0_copy_removeReorder1_local.value = real_out_demux__global_0_0.value;
		real_out_demux__global_0_0_copy_removeReorder1_local.status = FOREC_SHARED_UNMODIFIED;
		imag_out_demux__global_0_0_copy_removeReorder1_local.value = imag_out_demux__global_0_0.value;
		imag_out_demux__global_0_0_copy_removeReorder1_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		FFT_output_scale__removeReorder1_0_0 = ((float)11.0)/((float)8.0);
		real_out_demux_ptr__removeReorder1_0_0 = real_out_demux__global_0_0_copy_removeReorder1_local.value;
		imag_out_demux_ptr__removeReorder1_0_0 = imag_out_demux__global_0_0_copy_removeReorder1_local.value;
		data_remove_GI_reorder_real_ptr__removeReorder1_0_0 = data_remove_GI_reorder_real__global_0_0.value;
		data_remove_GI_reorder_imag_ptr__removeReorder1_0_0 = data_remove_GI_reorder_imag__global_0_0.value;
		for (j__removeReorder1_0_0 = 13; j__removeReorder1_0_0 < 26; j__removeReorder1_0_0++) {
			data_remove_GI_reorder_real_ptr__removeReorder1_0_0[j__removeReorder1_0_0 + 26] = (int)(FFT_output_scale__removeReorder1_0_0*real_out_demux_ptr__removeReorder1_0_0[j__removeReorder1_0_0 + 1]);
			data_remove_GI_reorder_imag_ptr__removeReorder1_0_0[j__removeReorder1_0_0 + 26] = (int)(FFT_output_scale__removeReorder1_0_0*imag_out_demux_ptr__removeReorder1_0_0[j__removeReorder1_0_0 + 1]);
			data_remove_GI_reorder_real_ptr__removeReorder1_0_0[j__removeReorder1_0_0] = (int)(FFT_output_scale__removeReorder1_0_0*real_out_demux_ptr__removeReorder1_0_0[j__removeReorder1_0_0 + 38]);
			data_remove_GI_reorder_imag_ptr__removeReorder1_0_0[j__removeReorder1_0_0] = (int)(FFT_output_scale__removeReorder1_0_0*imag_out_demux_ptr__removeReorder1_0_0[j__removeReorder1_0_0 + 38]);
			// forec:iteration:for1_33:bound:13:13
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:removeReorder1:start

		// Delete thread from the linked list and core.
		stage6ParCore0.activeThreads--;
		removeReorder1__thread.nextThread -> prevThread = removeReorder1__thread.prevThread;
		removeReorder1__thread.prevThread -> nextThread = removeReorder1__thread.nextThread;
		goto *removeReorder1__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:removeReorder1:end
	} // removeReorder1__thread
	// forec:thread:removeReorder1:end

	// forec:thread:stage0:start
	/*--------------------------------------------------------------
	| Thread stage0
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_freq_sync_correl_2STS_out_I__global_0_0 freq_sync_correl_2STS_out_I__global_0_0_copy_stage0_local;
	Shared_freq_sync_correl_2STS_out_Q__global_0_0 freq_sync_correl_2STS_out_Q__global_0_0_copy_stage0_local;
	Shared_FS_single_correl_I__global_0_0 FS_single_correl_I__global_0_0_copy_stage0_local;
	Shared_FS_single_correl_Q__global_0_0 FS_single_correl_Q__global_0_0_copy_stage0_local;
	Shared_input_size__global_0_0 input_size__global_0_0_copy_stage0_local;
	Shared_inputData__global_0_0 inputData__global_0_0_copy_stage0_local;
	Shared_freq_sync_correl_2STS_output_stage_0_1__global_0_0 freq_sync_correl_2STS_output_stage_0_1__global_0_0_copy_stage0_local;
	Shared_correlation_1ST_stage_0_1__global_0_0 correlation_1ST_stage_0_1__global_0_0_copy_stage0_local;
	int data_store_real_0__stage0_0_0[32*2];
	int data_store_imag_0__stage0_0_0[32*2];
	int i__stage0_0_0;
	int k__stage0_0_0;
	icomplex__global_0_0 freq_sync_correl_2STS_input__stage0_1_1;
	icomplex__global_0_0 correlation_1ST__stage0_1_1, freq_sync_correl_2STS_output__stage0_1_1;

	// Thread body -------------------------------------------------
	stage0__thread: {
		// Initialise the local copies of shared variables.
		freq_sync_correl_2STS_out_I__global_0_0_copy_stage0_local.value = freq_sync_correl_2STS_out_I__global_0_0.value;
		freq_sync_correl_2STS_out_I__global_0_0_copy_stage0_local.status = FOREC_SHARED_UNMODIFIED;
		freq_sync_correl_2STS_out_Q__global_0_0_copy_stage0_local.value = freq_sync_correl_2STS_out_Q__global_0_0.value;
		freq_sync_correl_2STS_out_Q__global_0_0_copy_stage0_local.status = FOREC_SHARED_UNMODIFIED;
		FS_single_correl_I__global_0_0_copy_stage0_local.value = FS_single_correl_I__global_0_0.value;
		FS_single_correl_I__global_0_0_copy_stage0_local.status = FOREC_SHARED_UNMODIFIED;
		FS_single_correl_Q__global_0_0_copy_stage0_local.value = FS_single_correl_Q__global_0_0.value;
		FS_single_correl_Q__global_0_0_copy_stage0_local.status = FOREC_SHARED_UNMODIFIED;
		input_size__global_0_0_copy_stage0_local.value = input_size__global_0_0.value;
		input_size__global_0_0_copy_stage0_local.status = FOREC_SHARED_UNMODIFIED;
		inputData__global_0_0_copy_stage0_local.value = inputData__global_0_0.value;
		inputData__global_0_0_copy_stage0_local.status = FOREC_SHARED_UNMODIFIED;
		freq_sync_correl_2STS_output_stage_0_1__global_0_0_copy_stage0_local.value = freq_sync_correl_2STS_output_stage_0_1__global_0_0.value;
		freq_sync_correl_2STS_output_stage_0_1__global_0_0_copy_stage0_local.status = FOREC_SHARED_UNMODIFIED;
		correlation_1ST_stage_0_1__global_0_0_copy_stage0_local.value = correlation_1ST_stage_0_1__global_0_0.value;
		correlation_1ST_stage_0_1__global_0_0_copy_stage0_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		for (i__stage0_0_0 = 0; i__stage0_0_0 < 32*2; i__stage0_0_0++) {
			data_store_real_0__stage0_0_0[i__stage0_0_0] = 0;
			data_store_imag_0__stage0_0_0[i__stage0_0_0] = 0;
			// forec:iteration:for1_1:bound:64:64
		}

		for (k__stage0_0_0 = 0; k__stage0_0_0 < input_size__global_0_0_copy_stage0_local.value; ++k__stage0_0_0) {
			freq_sync_correl_2STS_input__stage0_1_1.re = inputData__global_0_0_copy_stage0_local.value[k__stage0_0_0].re;
			freq_sync_correl_2STS_input__stage0_1_1.im = inputData__global_0_0_copy_stage0_local.value[k__stage0_0_0].im;
			computeStage0(freq_sync_correl_2STS_input__stage0_1_1, data_store_real_0__stage0_0_0, data_store_imag_0__stage0_0_0, &correlation_1ST__stage0_1_1, &freq_sync_correl_2STS_output__stage0_1_1);
			correlation_1ST_stage_0_1__global_0_0_copy_stage0_local.value = correlation_1ST__stage0_1_1;
			correlation_1ST_stage_0_1__global_0_0_copy_stage0_local.status = FOREC_SHARED_MODIFIED;
			freq_sync_correl_2STS_output_stage_0_1__global_0_0_copy_stage0_local.value = freq_sync_correl_2STS_output__stage0_1_1;
			freq_sync_correl_2STS_output_stage_0_1__global_0_0_copy_stage0_local.status = FOREC_SHARED_MODIFIED;
			if (debug__global_0_0.value) {
				fprintf(freq_sync_correl_2STS_out_I__global_0_0_copy_stage0_local.value, "%d\n", freq_sync_correl_2STS_output_stage_0_1__global_0_0_copy_stage0_local.value.re);
				fprintf(freq_sync_correl_2STS_out_Q__global_0_0_copy_stage0_local.value, "%d\n", freq_sync_correl_2STS_output_stage_0_1__global_0_0_copy_stage0_local.value.im);
				fprintf(FS_single_correl_I__global_0_0_copy_stage0_local.value, "%d\n", correlation_1ST_stage_0_1__global_0_0_copy_stage0_local.value.re);
				fprintf(FS_single_correl_Q__global_0_0_copy_stage0_local.value, "%d\n", correlation_1ST_stage_0_1__global_0_0_copy_stage0_local.value.im);
			} else {
				// if1
			}

			// pause;
			// Write the local copy of shared variables back to their global copy.
			freq_sync_correl_2STS_output_stage_0_1__global_0_0_copy_stage0 = freq_sync_correl_2STS_output_stage_0_1__global_0_0_copy_stage0_local;
			correlation_1ST_stage_0_1__global_0_0_copy_stage0 = correlation_1ST_stage_0_1__global_0_0_copy_stage0_local;
			// forec:statement:pause:pause0:start
			stage0__thread.programCounter = &&pause0;
			goto *stage0__thread.nextThread -> programCounter;
			pause0:;
			// forec:statement:pause:pause0:end
			// Update the values of the used shared variables from their global copy.
			freq_sync_correl_2STS_out_I__global_0_0_copy_stage0_local = freq_sync_correl_2STS_out_I__global_0_0;
			freq_sync_correl_2STS_out_Q__global_0_0_copy_stage0_local = freq_sync_correl_2STS_out_Q__global_0_0;
			FS_single_correl_I__global_0_0_copy_stage0_local = FS_single_correl_I__global_0_0;
			FS_single_correl_Q__global_0_0_copy_stage0_local = FS_single_correl_Q__global_0_0;
			input_size__global_0_0_copy_stage0_local = input_size__global_0_0;
			inputData__global_0_0_copy_stage0_local = inputData__global_0_0;
			freq_sync_correl_2STS_output_stage_0_1__global_0_0_copy_stage0_local = freq_sync_correl_2STS_output_stage_0_1__global_0_0;
			correlation_1ST_stage_0_1__global_0_0_copy_stage0_local = correlation_1ST_stage_0_1__global_0_0;

			// forec:iteration:for1_2:bound:7:7
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		freq_sync_correl_2STS_output_stage_0_1__global_0_0_copy_stage0 = freq_sync_correl_2STS_output_stage_0_1__global_0_0_copy_stage0_local;
		correlation_1ST_stage_0_1__global_0_0_copy_stage0 = correlation_1ST_stage_0_1__global_0_0_copy_stage0_local;

		// forec:scheduler:threadRemove:stage0:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		stage0__thread.nextThread -> prevThread = stage0__thread.prevThread;
		stage0__thread.prevThread -> nextThread = stage0__thread.nextThread;
		goto *stage0__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:stage0:end
	} // stage0__thread
	// forec:thread:stage0:end

	// forec:thread:stage1:start
	/*--------------------------------------------------------------
	| Thread stage1
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_freq_est_phase_out_I__global_0_0 freq_est_phase_out_I__global_0_0_copy_stage1_local;
	Shared_freq_est_phase_out_Q__global_0_0 freq_est_phase_out_Q__global_0_0_copy_stage1_local;
	Shared_input_size__global_0_0 input_size__global_0_0_copy_stage1_local;
	Shared_freq_sync_correl_2STS_output_stage_0_1__global_0_0 freq_sync_correl_2STS_output_stage_0_1__global_0_0_copy_stage1_local;
	Shared_freq_sync_correl_2STS_output_stage_1_2__global_0_0 freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage1_local;
	Shared_correlation_1ST_stage_0_1__global_0_0 correlation_1ST_stage_0_1__global_0_0_copy_stage1_local;
	Shared_burst_found_pulse_out_stage_1_2__global_0_0 burst_found_pulse_out_stage_1_2__global_0_0_copy_stage1_local;
	Shared_freq_est_phase_out_stage_1_2__global_0_0 freq_est_phase_out_stage_1_2__global_0_0_copy_stage1_local;
	Shared_burst_found_pulse_for_FT_stage_1_2__global_0_0 burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage1_local;
	int freq2_i__stage1_0_0;
	int freq2_q__stage1_0_0;
	int freq1_i__stage1_0_0;
	int freq1_q__stage1_0_0;
	int correlation_1ST_store_real__stage1_0_0[256];
	int correlation_1ST_store_imag__stage1_0_0[256];
	int correlation_1ST_store_index__stage1_0_0;
	int burst_found_pulse_64d__stage1_0_0[64];
	int burst_found_pulse_64d_index__stage1_0_0;
	int i__stage1_0_0;
	int burst_found_out__stage1_0_0;
	int freq_est_norm_out__stage1_0_0;
	int freq_est_norm_max_out__stage1_0_0;
	int k__stage1_0_0;
	icomplex__global_0_0 freq_est_phase_out__stage1_1_2;
	int burst_found_pulse_out__stage1_1_2, burst_found_pulse_for_FT__stage1_1_2;

	// Thread body -------------------------------------------------
	stage1__thread: {
		// Initialise the local copies of shared variables.
		freq_est_phase_out_I__global_0_0_copy_stage1_local.value = freq_est_phase_out_I__global_0_0.value;
		freq_est_phase_out_I__global_0_0_copy_stage1_local.status = FOREC_SHARED_UNMODIFIED;
		freq_est_phase_out_Q__global_0_0_copy_stage1_local.value = freq_est_phase_out_Q__global_0_0.value;
		freq_est_phase_out_Q__global_0_0_copy_stage1_local.status = FOREC_SHARED_UNMODIFIED;
		input_size__global_0_0_copy_stage1_local.value = input_size__global_0_0.value;
		input_size__global_0_0_copy_stage1_local.status = FOREC_SHARED_UNMODIFIED;
		freq_sync_correl_2STS_output_stage_0_1__global_0_0_copy_stage1_local.value = freq_sync_correl_2STS_output_stage_0_1__global_0_0.value;
		freq_sync_correl_2STS_output_stage_0_1__global_0_0_copy_stage1_local.status = FOREC_SHARED_UNMODIFIED;
		freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage1_local.value = freq_sync_correl_2STS_output_stage_1_2__global_0_0.value;
		freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage1_local.status = FOREC_SHARED_UNMODIFIED;
		correlation_1ST_stage_0_1__global_0_0_copy_stage1_local.value = correlation_1ST_stage_0_1__global_0_0.value;
		correlation_1ST_stage_0_1__global_0_0_copy_stage1_local.status = FOREC_SHARED_UNMODIFIED;
		burst_found_pulse_out_stage_1_2__global_0_0_copy_stage1_local.value = burst_found_pulse_out_stage_1_2__global_0_0.value;
		burst_found_pulse_out_stage_1_2__global_0_0_copy_stage1_local.status = FOREC_SHARED_UNMODIFIED;
		freq_est_phase_out_stage_1_2__global_0_0_copy_stage1_local.value = freq_est_phase_out_stage_1_2__global_0_0.value;
		freq_est_phase_out_stage_1_2__global_0_0_copy_stage1_local.status = FOREC_SHARED_UNMODIFIED;
		burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage1_local.value = burst_found_pulse_for_FT_stage_1_2__global_0_0.value;
		burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage1_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		freq2_i__stage1_0_0 = 0;
		freq2_q__stage1_0_0 = 0;
		freq1_i__stage1_0_0 = 0;
		freq1_q__stage1_0_0 = 0;

		// pause;
		// Write the local copy of shared variables back to their global copy.
		freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage1 = freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage1_local;
		burst_found_pulse_out_stage_1_2__global_0_0_copy_stage1 = burst_found_pulse_out_stage_1_2__global_0_0_copy_stage1_local;
		freq_est_phase_out_stage_1_2__global_0_0_copy_stage1 = freq_est_phase_out_stage_1_2__global_0_0_copy_stage1_local;
		burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage1 = burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage1_local;
		// forec:statement:pause:pause1:start
		stage1__thread.programCounter = &&pause1;
		goto *stage1__thread.nextThread -> programCounter;
		pause1:;
		// forec:statement:pause:pause1:end
		// Update the values of the used shared variables from their global copy.
		freq_est_phase_out_I__global_0_0_copy_stage1_local = freq_est_phase_out_I__global_0_0;
		freq_est_phase_out_Q__global_0_0_copy_stage1_local = freq_est_phase_out_Q__global_0_0;
		input_size__global_0_0_copy_stage1_local = input_size__global_0_0;
		freq_sync_correl_2STS_output_stage_0_1__global_0_0_copy_stage1_local = freq_sync_correl_2STS_output_stage_0_1__global_0_0;
		freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage1_local = freq_sync_correl_2STS_output_stage_1_2__global_0_0;
		correlation_1ST_stage_0_1__global_0_0_copy_stage1_local = correlation_1ST_stage_0_1__global_0_0;
		burst_found_pulse_out_stage_1_2__global_0_0_copy_stage1_local = burst_found_pulse_out_stage_1_2__global_0_0;
		freq_est_phase_out_stage_1_2__global_0_0_copy_stage1_local = freq_est_phase_out_stage_1_2__global_0_0;
		burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage1_local = burst_found_pulse_for_FT_stage_1_2__global_0_0;


		for (i__stage1_0_0 = 0; i__stage1_0_0 < (correl_sum_len__global_0_0); i__stage1_0_0++) {
			correlation_1ST_store_real__stage1_0_0[i__stage1_0_0] = 0;
			correlation_1ST_store_imag__stage1_0_0[i__stage1_0_0] = 0;
			// forec:iteration:for1_4:bound:256:256
		}
		correlation_1ST_store_index__stage1_0_0 = 0;
		freq2_i__stage1_0_0 = 0;
		freq2_q__stage1_0_0 = 0;
		freq1_i__stage1_0_0 = 0;
		freq1_q__stage1_0_0 = 0;
		burst_found_out__stage1_0_0 = 0;
		freq_est_norm_out__stage1_0_0 = 0;
		freq_est_norm_max_out__stage1_0_0 = 0;
		freq_est_phase_out_stage_1_2__global_0_0_copy_stage1_local.value.re = 0;
		freq_est_phase_out_stage_1_2__global_0_0_copy_stage1_local.status = FOREC_SHARED_MODIFIED;
		freq_est_phase_out_stage_1_2__global_0_0_copy_stage1_local.value.im = 0;
		freq_est_phase_out_stage_1_2__global_0_0_copy_stage1_local.status = FOREC_SHARED_MODIFIED;
		burst_found_pulse_out_stage_1_2__global_0_0_copy_stage1_local.value = 0;
		burst_found_pulse_out_stage_1_2__global_0_0_copy_stage1_local.status = FOREC_SHARED_MODIFIED;
		for (i__stage1_0_0 = 0; i__stage1_0_0 < 64; i__stage1_0_0++) {
			burst_found_pulse_64d__stage1_0_0[i__stage1_0_0] = 0;
			// forec:iteration:for1_5:bound:64:64
		}
		burst_found_pulse_64d_index__stage1_0_0 = 0;
		burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage1_local.value = burst_found_pulse_64d__stage1_0_0[burst_found_pulse_64d_index__stage1_0_0];
		burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage1_local.status = FOREC_SHARED_MODIFIED;
		freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage1_local.value = freq_sync_correl_2STS_output_stage_0_1__global_0_0_copy_stage1_local.value;
		freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage1_local.status = FOREC_SHARED_MODIFIED;

		// pause;
		// Write the local copy of shared variables back to their global copy.
		freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage1 = freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage1_local;
		burst_found_pulse_out_stage_1_2__global_0_0_copy_stage1 = burst_found_pulse_out_stage_1_2__global_0_0_copy_stage1_local;
		freq_est_phase_out_stage_1_2__global_0_0_copy_stage1 = freq_est_phase_out_stage_1_2__global_0_0_copy_stage1_local;
		burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage1 = burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage1_local;
		// forec:statement:pause:pause2:start
		stage1__thread.programCounter = &&pause2;
		goto *stage1__thread.nextThread -> programCounter;
		pause2:;
		// forec:statement:pause:pause2:end
		// Update the values of the used shared variables from their global copy.
		freq_est_phase_out_I__global_0_0_copy_stage1_local = freq_est_phase_out_I__global_0_0;
		freq_est_phase_out_Q__global_0_0_copy_stage1_local = freq_est_phase_out_Q__global_0_0;
		input_size__global_0_0_copy_stage1_local = input_size__global_0_0;
		freq_sync_correl_2STS_output_stage_0_1__global_0_0_copy_stage1_local = freq_sync_correl_2STS_output_stage_0_1__global_0_0;
		freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage1_local = freq_sync_correl_2STS_output_stage_1_2__global_0_0;
		correlation_1ST_stage_0_1__global_0_0_copy_stage1_local = correlation_1ST_stage_0_1__global_0_0;
		burst_found_pulse_out_stage_1_2__global_0_0_copy_stage1_local = burst_found_pulse_out_stage_1_2__global_0_0;
		freq_est_phase_out_stage_1_2__global_0_0_copy_stage1_local = freq_est_phase_out_stage_1_2__global_0_0;
		burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage1_local = burst_found_pulse_for_FT_stage_1_2__global_0_0;


		for (k__stage1_0_0 = 0; k__stage1_0_0 < input_size__global_0_0_copy_stage1_local.value - 1; ++k__stage1_0_0) {
			freq_est_phase_out__stage1_1_2 = freq_est_phase_out_stage_1_2__global_0_0_copy_stage1_local.value;
			burst_found_pulse_out__stage1_1_2 = burst_found_pulse_out_stage_1_2__global_0_0_copy_stage1_local.value, burst_found_pulse_for_FT__stage1_1_2 = burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage1_local.value;
			computeStage1(&correlation_1ST_store_index__stage1_0_0, &freq1_i__stage1_0_0, &freq1_q__stage1_0_0, &freq2_i__stage1_0_0, &freq2_q__stage1_0_0, correlation_1ST_store_real__stage1_0_0, correlation_1ST_store_imag__stage1_0_0, &burst_found_pulse_64d_index__stage1_0_0, burst_found_pulse_64d__stage1_0_0, &freq_est_phase_out__stage1_1_2, correlation_1ST_stage_0_1__global_0_0_copy_stage1_local.value, &burst_found_out__stage1_0_0, &burst_found_pulse_out__stage1_1_2, &freq_est_norm_out__stage1_0_0, &freq_est_norm_max_out__stage1_0_0, &burst_found_pulse_for_FT__stage1_1_2);
			freq_est_phase_out_stage_1_2__global_0_0_copy_stage1_local.value = freq_est_phase_out__stage1_1_2;
			freq_est_phase_out_stage_1_2__global_0_0_copy_stage1_local.status = FOREC_SHARED_MODIFIED;
			burst_found_pulse_out_stage_1_2__global_0_0_copy_stage1_local.value = burst_found_pulse_out__stage1_1_2;
			burst_found_pulse_out_stage_1_2__global_0_0_copy_stage1_local.status = FOREC_SHARED_MODIFIED;
			burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage1_local.value = burst_found_pulse_for_FT__stage1_1_2;
			burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage1_local.status = FOREC_SHARED_MODIFIED;
			if (debug__global_0_0.value) {
				fprintf(freq_est_phase_out_I__global_0_0_copy_stage1_local.value, "%d\n", freq_est_phase_out_stage_1_2__global_0_0_copy_stage1_local.value.re);
				fprintf(freq_est_phase_out_Q__global_0_0_copy_stage1_local.value, "%d\n", freq_est_phase_out_stage_1_2__global_0_0_copy_stage1_local.value.im);
			} else {
				// if2
			}
			freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage1_local.value = freq_sync_correl_2STS_output_stage_0_1__global_0_0_copy_stage1_local.value;
			freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage1_local.status = FOREC_SHARED_MODIFIED;

			// pause;
			// Write the local copy of shared variables back to their global copy.
			freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage1 = freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage1_local;
			burst_found_pulse_out_stage_1_2__global_0_0_copy_stage1 = burst_found_pulse_out_stage_1_2__global_0_0_copy_stage1_local;
			freq_est_phase_out_stage_1_2__global_0_0_copy_stage1 = freq_est_phase_out_stage_1_2__global_0_0_copy_stage1_local;
			burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage1 = burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage1_local;
			// forec:statement:pause:pause3:start
			stage1__thread.programCounter = &&pause3;
			goto *stage1__thread.nextThread -> programCounter;
			pause3:;
			// forec:statement:pause:pause3:end
			// Update the values of the used shared variables from their global copy.
			freq_est_phase_out_I__global_0_0_copy_stage1_local = freq_est_phase_out_I__global_0_0;
			freq_est_phase_out_Q__global_0_0_copy_stage1_local = freq_est_phase_out_Q__global_0_0;
			input_size__global_0_0_copy_stage1_local = input_size__global_0_0;
			freq_sync_correl_2STS_output_stage_0_1__global_0_0_copy_stage1_local = freq_sync_correl_2STS_output_stage_0_1__global_0_0;
			freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage1_local = freq_sync_correl_2STS_output_stage_1_2__global_0_0;
			correlation_1ST_stage_0_1__global_0_0_copy_stage1_local = correlation_1ST_stage_0_1__global_0_0;
			burst_found_pulse_out_stage_1_2__global_0_0_copy_stage1_local = burst_found_pulse_out_stage_1_2__global_0_0;
			freq_est_phase_out_stage_1_2__global_0_0_copy_stage1_local = freq_est_phase_out_stage_1_2__global_0_0;
			burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage1_local = burst_found_pulse_for_FT_stage_1_2__global_0_0;

			// forec:iteration:for1_6:bound:7:7
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage1 = freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage1_local;
		burst_found_pulse_out_stage_1_2__global_0_0_copy_stage1 = burst_found_pulse_out_stage_1_2__global_0_0_copy_stage1_local;
		freq_est_phase_out_stage_1_2__global_0_0_copy_stage1 = freq_est_phase_out_stage_1_2__global_0_0_copy_stage1_local;
		burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage1 = burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage1_local;

		// forec:scheduler:threadRemove:stage1:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		stage1__thread.nextThread -> prevThread = stage1__thread.prevThread;
		stage1__thread.prevThread -> nextThread = stage1__thread.nextThread;
		goto *stage1__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:stage1:end
	} // stage1__thread
	// forec:thread:stage1:end

	// forec:thread:stage2:start
	/*--------------------------------------------------------------
	| Thread stage2
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_input_size__global_0_0 input_size__global_0_0_copy_stage2_local;
	Shared_freq_sync_correl_2STS_output_stage_1_2__global_0_0 freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage2_local;
	Shared_freq_sync_correl_2STS_output_stage_2_3__global_0_0 freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage2_local;
	Shared_burst_found_pulse_out_stage_1_2__global_0_0 burst_found_pulse_out_stage_1_2__global_0_0_copy_stage2_local;
	Shared_freq_est_phase_out_stage_1_2__global_0_0 freq_est_phase_out_stage_1_2__global_0_0_copy_stage2_local;
	Shared_angle_stage_2_3__global_0_0 angle_stage_2_3__global_0_0_copy_stage2_local;
	Shared_burst_found_pulse_for_FT_stage_1_2__global_0_0 burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage2_local;
	Shared_burst_found_pulse_for_FT_stage_2_3__global_0_0 burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage2_local;
	int act_angle__stage2_0_0;
	int k__stage2_0_0;
	int angle__stage2_1_0;

	// Thread body -------------------------------------------------
	stage2__thread: {
		// Initialise the local copies of shared variables.
		input_size__global_0_0_copy_stage2_local.value = input_size__global_0_0.value;
		input_size__global_0_0_copy_stage2_local.status = FOREC_SHARED_UNMODIFIED;
		freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage2_local.value = freq_sync_correl_2STS_output_stage_1_2__global_0_0.value;
		freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage2_local.status = FOREC_SHARED_UNMODIFIED;
		freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage2_local.value = freq_sync_correl_2STS_output_stage_2_3__global_0_0.value;
		freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage2_local.status = FOREC_SHARED_UNMODIFIED;
		burst_found_pulse_out_stage_1_2__global_0_0_copy_stage2_local.value = burst_found_pulse_out_stage_1_2__global_0_0.value;
		burst_found_pulse_out_stage_1_2__global_0_0_copy_stage2_local.status = FOREC_SHARED_UNMODIFIED;
		freq_est_phase_out_stage_1_2__global_0_0_copy_stage2_local.value = freq_est_phase_out_stage_1_2__global_0_0.value;
		freq_est_phase_out_stage_1_2__global_0_0_copy_stage2_local.status = FOREC_SHARED_UNMODIFIED;
		angle_stage_2_3__global_0_0_copy_stage2_local.value = angle_stage_2_3__global_0_0.value;
		angle_stage_2_3__global_0_0_copy_stage2_local.status = FOREC_SHARED_UNMODIFIED;
		burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage2_local.value = burst_found_pulse_for_FT_stage_1_2__global_0_0.value;
		burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage2_local.status = FOREC_SHARED_UNMODIFIED;
		burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage2_local.value = burst_found_pulse_for_FT_stage_2_3__global_0_0.value;
		burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage2_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		// pause;
		// Write the local copy of shared variables back to their global copy.
		freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage2 = freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage2_local;
		angle_stage_2_3__global_0_0_copy_stage2 = angle_stage_2_3__global_0_0_copy_stage2_local;
		burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage2 = burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage2_local;
		// forec:statement:pause:pause4:start
		stage2__thread.programCounter = &&pause4;
		goto *stage2__thread.nextThread -> programCounter;
		pause4:;
		// forec:statement:pause:pause4:end
		// Update the values of the used shared variables from their global copy.
		input_size__global_0_0_copy_stage2_local = input_size__global_0_0;
		freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage2_local = freq_sync_correl_2STS_output_stage_1_2__global_0_0;
		freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage2_local = freq_sync_correl_2STS_output_stage_2_3__global_0_0;
		burst_found_pulse_out_stage_1_2__global_0_0_copy_stage2_local = burst_found_pulse_out_stage_1_2__global_0_0;
		freq_est_phase_out_stage_1_2__global_0_0_copy_stage2_local = freq_est_phase_out_stage_1_2__global_0_0;
		angle_stage_2_3__global_0_0_copy_stage2_local = angle_stage_2_3__global_0_0;
		burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage2_local = burst_found_pulse_for_FT_stage_1_2__global_0_0;
		burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage2_local = burst_found_pulse_for_FT_stage_2_3__global_0_0;


		// pause;
		// Write the local copy of shared variables back to their global copy.
		freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage2 = freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage2_local;
		angle_stage_2_3__global_0_0_copy_stage2 = angle_stage_2_3__global_0_0_copy_stage2_local;
		burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage2 = burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage2_local;
		// forec:statement:pause:pause5:start
		stage2__thread.programCounter = &&pause5;
		goto *stage2__thread.nextThread -> programCounter;
		pause5:;
		// forec:statement:pause:pause5:end
		// Update the values of the used shared variables from their global copy.
		input_size__global_0_0_copy_stage2_local = input_size__global_0_0;
		freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage2_local = freq_sync_correl_2STS_output_stage_1_2__global_0_0;
		freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage2_local = freq_sync_correl_2STS_output_stage_2_3__global_0_0;
		burst_found_pulse_out_stage_1_2__global_0_0_copy_stage2_local = burst_found_pulse_out_stage_1_2__global_0_0;
		freq_est_phase_out_stage_1_2__global_0_0_copy_stage2_local = freq_est_phase_out_stage_1_2__global_0_0;
		angle_stage_2_3__global_0_0_copy_stage2_local = angle_stage_2_3__global_0_0;
		burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage2_local = burst_found_pulse_for_FT_stage_1_2__global_0_0;
		burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage2_local = burst_found_pulse_for_FT_stage_2_3__global_0_0;


		act_angle__stage2_0_0 = 0;
		freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage2_local.value = freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage2_local.value;
		freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage2_local.status = FOREC_SHARED_MODIFIED;
		burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage2_local.value = burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage2_local.value;
		burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage2_local.status = FOREC_SHARED_MODIFIED;

		// pause;
		// Write the local copy of shared variables back to their global copy.
		freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage2 = freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage2_local;
		angle_stage_2_3__global_0_0_copy_stage2 = angle_stage_2_3__global_0_0_copy_stage2_local;
		burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage2 = burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage2_local;
		// forec:statement:pause:pause6:start
		stage2__thread.programCounter = &&pause6;
		goto *stage2__thread.nextThread -> programCounter;
		pause6:;
		// forec:statement:pause:pause6:end
		// Update the values of the used shared variables from their global copy.
		input_size__global_0_0_copy_stage2_local = input_size__global_0_0;
		freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage2_local = freq_sync_correl_2STS_output_stage_1_2__global_0_0;
		freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage2_local = freq_sync_correl_2STS_output_stage_2_3__global_0_0;
		burst_found_pulse_out_stage_1_2__global_0_0_copy_stage2_local = burst_found_pulse_out_stage_1_2__global_0_0;
		freq_est_phase_out_stage_1_2__global_0_0_copy_stage2_local = freq_est_phase_out_stage_1_2__global_0_0;
		angle_stage_2_3__global_0_0_copy_stage2_local = angle_stage_2_3__global_0_0;
		burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage2_local = burst_found_pulse_for_FT_stage_1_2__global_0_0;
		burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage2_local = burst_found_pulse_for_FT_stage_2_3__global_0_0;


		for (k__stage2_0_0 = 0; k__stage2_0_0 < input_size__global_0_0_copy_stage2_local.value - 1; ++k__stage2_0_0) {
			computeStage2(&act_angle__stage2_0_0, freq_est_phase_out_stage_1_2__global_0_0_copy_stage2_local.value, burst_found_pulse_out_stage_1_2__global_0_0_copy_stage2_local.value, &angle__stage2_1_0);
			angle_stage_2_3__global_0_0_copy_stage2_local.value = angle__stage2_1_0;
			angle_stage_2_3__global_0_0_copy_stage2_local.status = FOREC_SHARED_MODIFIED;
			freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage2_local.value = freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage2_local.value;
			freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage2_local.status = FOREC_SHARED_MODIFIED;
			burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage2_local.value = burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage2_local.value;
			burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage2_local.status = FOREC_SHARED_MODIFIED;

			// pause;
			// Write the local copy of shared variables back to their global copy.
			freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage2 = freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage2_local;
			angle_stage_2_3__global_0_0_copy_stage2 = angle_stage_2_3__global_0_0_copy_stage2_local;
			burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage2 = burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage2_local;
			// forec:statement:pause:pause7:start
			stage2__thread.programCounter = &&pause7;
			goto *stage2__thread.nextThread -> programCounter;
			pause7:;
			// forec:statement:pause:pause7:end
			// Update the values of the used shared variables from their global copy.
			input_size__global_0_0_copy_stage2_local = input_size__global_0_0;
			freq_sync_correl_2STS_output_stage_1_2__global_0_0_copy_stage2_local = freq_sync_correl_2STS_output_stage_1_2__global_0_0;
			freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage2_local = freq_sync_correl_2STS_output_stage_2_3__global_0_0;
			burst_found_pulse_out_stage_1_2__global_0_0_copy_stage2_local = burst_found_pulse_out_stage_1_2__global_0_0;
			freq_est_phase_out_stage_1_2__global_0_0_copy_stage2_local = freq_est_phase_out_stage_1_2__global_0_0;
			angle_stage_2_3__global_0_0_copy_stage2_local = angle_stage_2_3__global_0_0;
			burst_found_pulse_for_FT_stage_1_2__global_0_0_copy_stage2_local = burst_found_pulse_for_FT_stage_1_2__global_0_0;
			burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage2_local = burst_found_pulse_for_FT_stage_2_3__global_0_0;

			// forec:iteration:for1_7:bound:7:7
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage2 = freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage2_local;
		angle_stage_2_3__global_0_0_copy_stage2 = angle_stage_2_3__global_0_0_copy_stage2_local;
		burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage2 = burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage2_local;

		// forec:scheduler:threadRemove:stage2:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		stage2__thread.nextThread -> prevThread = stage2__thread.prevThread;
		stage2__thread.prevThread -> nextThread = stage2__thread.nextThread;
		goto *stage2__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:stage2:end
	} // stage2__thread
	// forec:thread:stage2:end

	// forec:thread:stage3:start
	/*--------------------------------------------------------------
	| Thread stage3
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_input_size__global_0_0 input_size__global_0_0_copy_stage3_local;
	Shared_freq_sync_correl_2STS_output_stage_2_3__global_0_0 freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage3_local;
	Shared_angle_stage_2_3__global_0_0 angle_stage_2_3__global_0_0_copy_stage3_local;
	Shared_cordic_out_stage_3_4__global_0_0 cordic_out_stage_3_4__global_0_0_copy_stage3_local;
	Shared_burst_found_pulse_for_FT_stage_2_3__global_0_0 burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage3_local;
	Shared_burst_found_pulse_for_FT_stage_3_4__global_0_0 burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage3_local;
	int k__stage3_0_0;
	icomplex__global_0_0 cordic_out__stage3_1_0;

	// Thread body -------------------------------------------------
	stage3__thread: {
		// Initialise the local copies of shared variables.
		input_size__global_0_0_copy_stage3_local.value = input_size__global_0_0.value;
		input_size__global_0_0_copy_stage3_local.status = FOREC_SHARED_UNMODIFIED;
		freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage3_local.value = freq_sync_correl_2STS_output_stage_2_3__global_0_0.value;
		freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage3_local.status = FOREC_SHARED_UNMODIFIED;
		angle_stage_2_3__global_0_0_copy_stage3_local.value = angle_stage_2_3__global_0_0.value;
		angle_stage_2_3__global_0_0_copy_stage3_local.status = FOREC_SHARED_UNMODIFIED;
		cordic_out_stage_3_4__global_0_0_copy_stage3_local.value = cordic_out_stage_3_4__global_0_0.value;
		cordic_out_stage_3_4__global_0_0_copy_stage3_local.status = FOREC_SHARED_UNMODIFIED;
		burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage3_local.value = burst_found_pulse_for_FT_stage_2_3__global_0_0.value;
		burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage3_local.status = FOREC_SHARED_UNMODIFIED;
		burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage3_local.value = burst_found_pulse_for_FT_stage_3_4__global_0_0.value;
		burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage3_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		// pause;
		// Write the local copy of shared variables back to their global copy.
		cordic_out_stage_3_4__global_0_0_copy_stage3 = cordic_out_stage_3_4__global_0_0_copy_stage3_local;
		burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage3 = burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage3_local;
		// forec:statement:pause:pause8:start
		stage3__thread.programCounter = &&pause8;
		goto *stage3__thread.nextThread -> programCounter;
		pause8:;
		// forec:statement:pause:pause8:end
		// Update the values of the used shared variables from their global copy.
		input_size__global_0_0_copy_stage3_local = input_size__global_0_0;
		freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage3_local = freq_sync_correl_2STS_output_stage_2_3__global_0_0;
		angle_stage_2_3__global_0_0_copy_stage3_local = angle_stage_2_3__global_0_0;
		cordic_out_stage_3_4__global_0_0_copy_stage3_local = cordic_out_stage_3_4__global_0_0;
		burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage3_local = burst_found_pulse_for_FT_stage_2_3__global_0_0;
		burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage3_local = burst_found_pulse_for_FT_stage_3_4__global_0_0;


		// pause;
		// Write the local copy of shared variables back to their global copy.
		cordic_out_stage_3_4__global_0_0_copy_stage3 = cordic_out_stage_3_4__global_0_0_copy_stage3_local;
		burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage3 = burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage3_local;
		// forec:statement:pause:pause9:start
		stage3__thread.programCounter = &&pause9;
		goto *stage3__thread.nextThread -> programCounter;
		pause9:;
		// forec:statement:pause:pause9:end
		// Update the values of the used shared variables from their global copy.
		input_size__global_0_0_copy_stage3_local = input_size__global_0_0;
		freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage3_local = freq_sync_correl_2STS_output_stage_2_3__global_0_0;
		angle_stage_2_3__global_0_0_copy_stage3_local = angle_stage_2_3__global_0_0;
		cordic_out_stage_3_4__global_0_0_copy_stage3_local = cordic_out_stage_3_4__global_0_0;
		burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage3_local = burst_found_pulse_for_FT_stage_2_3__global_0_0;
		burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage3_local = burst_found_pulse_for_FT_stage_3_4__global_0_0;


		// pause;
		// Write the local copy of shared variables back to their global copy.
		cordic_out_stage_3_4__global_0_0_copy_stage3 = cordic_out_stage_3_4__global_0_0_copy_stage3_local;
		burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage3 = burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage3_local;
		// forec:statement:pause:pause10:start
		stage3__thread.programCounter = &&pause10;
		goto *stage3__thread.nextThread -> programCounter;
		pause10:;
		// forec:statement:pause:pause10:end
		// Update the values of the used shared variables from their global copy.
		input_size__global_0_0_copy_stage3_local = input_size__global_0_0;
		freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage3_local = freq_sync_correl_2STS_output_stage_2_3__global_0_0;
		angle_stage_2_3__global_0_0_copy_stage3_local = angle_stage_2_3__global_0_0;
		cordic_out_stage_3_4__global_0_0_copy_stage3_local = cordic_out_stage_3_4__global_0_0;
		burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage3_local = burst_found_pulse_for_FT_stage_2_3__global_0_0;
		burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage3_local = burst_found_pulse_for_FT_stage_3_4__global_0_0;


		burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage3_local.value = burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage3_local.value;
		burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage3_local.status = FOREC_SHARED_MODIFIED;

		// pause;
		// Write the local copy of shared variables back to their global copy.
		cordic_out_stage_3_4__global_0_0_copy_stage3 = cordic_out_stage_3_4__global_0_0_copy_stage3_local;
		burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage3 = burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage3_local;
		// forec:statement:pause:pause11:start
		stage3__thread.programCounter = &&pause11;
		goto *stage3__thread.nextThread -> programCounter;
		pause11:;
		// forec:statement:pause:pause11:end
		// Update the values of the used shared variables from their global copy.
		input_size__global_0_0_copy_stage3_local = input_size__global_0_0;
		freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage3_local = freq_sync_correl_2STS_output_stage_2_3__global_0_0;
		angle_stage_2_3__global_0_0_copy_stage3_local = angle_stage_2_3__global_0_0;
		cordic_out_stage_3_4__global_0_0_copy_stage3_local = cordic_out_stage_3_4__global_0_0;
		burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage3_local = burst_found_pulse_for_FT_stage_2_3__global_0_0;
		burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage3_local = burst_found_pulse_for_FT_stage_3_4__global_0_0;


		for (k__stage3_0_0 = 0; k__stage3_0_0 < input_size__global_0_0_copy_stage3_local.value - 1; ++k__stage3_0_0) {
			computeStage3(&cordic_out__stage3_1_0, angle_stage_2_3__global_0_0_copy_stage3_local.value, freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage3_local.value);
			cordic_out_stage_3_4__global_0_0_copy_stage3_local.value = cordic_out__stage3_1_0;
			cordic_out_stage_3_4__global_0_0_copy_stage3_local.status = FOREC_SHARED_MODIFIED;
			burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage3_local.value = burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage3_local.value;
			burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage3_local.status = FOREC_SHARED_MODIFIED;

			// pause;
			// Write the local copy of shared variables back to their global copy.
			cordic_out_stage_3_4__global_0_0_copy_stage3 = cordic_out_stage_3_4__global_0_0_copy_stage3_local;
			burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage3 = burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage3_local;
			// forec:statement:pause:pause12:start
			stage3__thread.programCounter = &&pause12;
			goto *stage3__thread.nextThread -> programCounter;
			pause12:;
			// forec:statement:pause:pause12:end
			// Update the values of the used shared variables from their global copy.
			input_size__global_0_0_copy_stage3_local = input_size__global_0_0;
			freq_sync_correl_2STS_output_stage_2_3__global_0_0_copy_stage3_local = freq_sync_correl_2STS_output_stage_2_3__global_0_0;
			angle_stage_2_3__global_0_0_copy_stage3_local = angle_stage_2_3__global_0_0;
			cordic_out_stage_3_4__global_0_0_copy_stage3_local = cordic_out_stage_3_4__global_0_0;
			burst_found_pulse_for_FT_stage_2_3__global_0_0_copy_stage3_local = burst_found_pulse_for_FT_stage_2_3__global_0_0;
			burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage3_local = burst_found_pulse_for_FT_stage_3_4__global_0_0;

			// forec:iteration:for1_10:bound:7:7
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		cordic_out_stage_3_4__global_0_0_copy_stage3 = cordic_out_stage_3_4__global_0_0_copy_stage3_local;
		burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage3 = burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage3_local;

		// forec:scheduler:threadRemove:stage3:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		stage3__thread.nextThread -> prevThread = stage3__thread.prevThread;
		stage3__thread.prevThread -> nextThread = stage3__thread.nextThread;
		goto *stage3__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:stage3:end
	} // stage3__thread
	// forec:thread:stage3:end

	// forec:thread:stage4:start
	/*--------------------------------------------------------------
	| Thread stage4
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_input_size__global_0_0 input_size__global_0_0_copy_stage4_local;
	Shared_cordic_out_stage_3_4__global_0_0 cordic_out_stage_3_4__global_0_0_copy_stage4_local;
	Shared_data_out_FT_stage_4_5__global_0_0 data_out_FT_stage_4_5__global_0_0_copy_stage4_local;
	Shared_maximum_found_stage_4_5__global_0_0 maximum_found_stage_4_5__global_0_0_copy_stage4_local;
	Shared_burst_found_pulse_for_FT_stage_3_4__global_0_0 burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage4_local;
	int data_store_real__stage4_0_0[64];
	int data_store_imag__stage4_0_0[64];
	int data_store_index__stage4_0_0;
	int data_quant_real__stage4_0_0[64];
	int data_quant_imag__stage4_0_0[64];
	int data_quant_index__stage4_0_0;
	int fine_time_est_int__stage4_0_0;
	int fine_time_est_new__stage4_0_0;
	int FTS_count__stage4_0_0;
	int difference_in_fine_time_est__stage4_0_0;
	int maximum__stage4_0_0;
	int maximum_new__stage4_0_0;
	int maximum_found__stage4_0_0;
	int downsampling_flag__stage4_0_0;
	int i__stage4_0_0;
	int k__stage4_0_0;
	int maximum_found_stage_4_5_copy__stage4_1_1;
	icomplex__global_0_0 data_out_FT__stage4_1_1;

	// Thread body -------------------------------------------------
	stage4__thread: {
		// Initialise the local copies of shared variables.
		input_size__global_0_0_copy_stage4_local.value = input_size__global_0_0.value;
		input_size__global_0_0_copy_stage4_local.status = FOREC_SHARED_UNMODIFIED;
		cordic_out_stage_3_4__global_0_0_copy_stage4_local.value = cordic_out_stage_3_4__global_0_0.value;
		cordic_out_stage_3_4__global_0_0_copy_stage4_local.status = FOREC_SHARED_UNMODIFIED;
		data_out_FT_stage_4_5__global_0_0_copy_stage4_local.value = data_out_FT_stage_4_5__global_0_0.value;
		data_out_FT_stage_4_5__global_0_0_copy_stage4_local.status = FOREC_SHARED_UNMODIFIED;
		maximum_found_stage_4_5__global_0_0_copy_stage4_local.value = maximum_found_stage_4_5__global_0_0.value;
		maximum_found_stage_4_5__global_0_0_copy_stage4_local.status = FOREC_SHARED_UNMODIFIED;
		burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage4_local.value = burst_found_pulse_for_FT_stage_3_4__global_0_0.value;
		burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage4_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		data_store_index__stage4_0_0 = 0;
		data_quant_index__stage4_0_0 = 0;
		fine_time_est_int__stage4_0_0 = 0;
		fine_time_est_new__stage4_0_0 = 0;
		FTS_count__stage4_0_0 = 0;
		downsampling_flag__stage4_0_0 = 1;
		for (i__stage4_0_0 = 0; i__stage4_0_0 < 37; i__stage4_0_0++) {
			data_store_real__stage4_0_0[i__stage4_0_0] = (float)0.0;
			data_store_imag__stage4_0_0[i__stage4_0_0] = (float)0.0;
			data_quant_real__stage4_0_0[i__stage4_0_0] = (float)0.0;
			data_quant_imag__stage4_0_0[i__stage4_0_0] = (float)0.0;
			// forec:iteration:for1_13:bound:37:37
		}

		// pause;
		// Write the local copy of shared variables back to their global copy.
		data_out_FT_stage_4_5__global_0_0_copy_stage4 = data_out_FT_stage_4_5__global_0_0_copy_stage4_local;
		maximum_found_stage_4_5__global_0_0_copy_stage4 = maximum_found_stage_4_5__global_0_0_copy_stage4_local;
		// forec:statement:pause:pause13:start
		stage4__thread.programCounter = &&pause13;
		goto *stage4__thread.nextThread -> programCounter;
		pause13:;
		// forec:statement:pause:pause13:end
		// Update the values of the used shared variables from their global copy.
		input_size__global_0_0_copy_stage4_local = input_size__global_0_0;
		cordic_out_stage_3_4__global_0_0_copy_stage4_local = cordic_out_stage_3_4__global_0_0;
		data_out_FT_stage_4_5__global_0_0_copy_stage4_local = data_out_FT_stage_4_5__global_0_0;
		maximum_found_stage_4_5__global_0_0_copy_stage4_local = maximum_found_stage_4_5__global_0_0;
		burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage4_local = burst_found_pulse_for_FT_stage_3_4__global_0_0;


		// pause;
		// Write the local copy of shared variables back to their global copy.
		data_out_FT_stage_4_5__global_0_0_copy_stage4 = data_out_FT_stage_4_5__global_0_0_copy_stage4_local;
		maximum_found_stage_4_5__global_0_0_copy_stage4 = maximum_found_stage_4_5__global_0_0_copy_stage4_local;
		// forec:statement:pause:pause14:start
		stage4__thread.programCounter = &&pause14;
		goto *stage4__thread.nextThread -> programCounter;
		pause14:;
		// forec:statement:pause:pause14:end
		// Update the values of the used shared variables from their global copy.
		input_size__global_0_0_copy_stage4_local = input_size__global_0_0;
		cordic_out_stage_3_4__global_0_0_copy_stage4_local = cordic_out_stage_3_4__global_0_0;
		data_out_FT_stage_4_5__global_0_0_copy_stage4_local = data_out_FT_stage_4_5__global_0_0;
		maximum_found_stage_4_5__global_0_0_copy_stage4_local = maximum_found_stage_4_5__global_0_0;
		burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage4_local = burst_found_pulse_for_FT_stage_3_4__global_0_0;


		// pause;
		// Write the local copy of shared variables back to their global copy.
		data_out_FT_stage_4_5__global_0_0_copy_stage4 = data_out_FT_stage_4_5__global_0_0_copy_stage4_local;
		maximum_found_stage_4_5__global_0_0_copy_stage4 = maximum_found_stage_4_5__global_0_0_copy_stage4_local;
		// forec:statement:pause:pause15:start
		stage4__thread.programCounter = &&pause15;
		goto *stage4__thread.nextThread -> programCounter;
		pause15:;
		// forec:statement:pause:pause15:end
		// Update the values of the used shared variables from their global copy.
		input_size__global_0_0_copy_stage4_local = input_size__global_0_0;
		cordic_out_stage_3_4__global_0_0_copy_stage4_local = cordic_out_stage_3_4__global_0_0;
		data_out_FT_stage_4_5__global_0_0_copy_stage4_local = data_out_FT_stage_4_5__global_0_0;
		maximum_found_stage_4_5__global_0_0_copy_stage4_local = maximum_found_stage_4_5__global_0_0;
		burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage4_local = burst_found_pulse_for_FT_stage_3_4__global_0_0;


		// pause;
		// Write the local copy of shared variables back to their global copy.
		data_out_FT_stage_4_5__global_0_0_copy_stage4 = data_out_FT_stage_4_5__global_0_0_copy_stage4_local;
		maximum_found_stage_4_5__global_0_0_copy_stage4 = maximum_found_stage_4_5__global_0_0_copy_stage4_local;
		// forec:statement:pause:pause16:start
		stage4__thread.programCounter = &&pause16;
		goto *stage4__thread.nextThread -> programCounter;
		pause16:;
		// forec:statement:pause:pause16:end
		// Update the values of the used shared variables from their global copy.
		input_size__global_0_0_copy_stage4_local = input_size__global_0_0;
		cordic_out_stage_3_4__global_0_0_copy_stage4_local = cordic_out_stage_3_4__global_0_0;
		data_out_FT_stage_4_5__global_0_0_copy_stage4_local = data_out_FT_stage_4_5__global_0_0;
		maximum_found_stage_4_5__global_0_0_copy_stage4_local = maximum_found_stage_4_5__global_0_0;
		burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage4_local = burst_found_pulse_for_FT_stage_3_4__global_0_0;


		// pause;
		// Write the local copy of shared variables back to their global copy.
		data_out_FT_stage_4_5__global_0_0_copy_stage4 = data_out_FT_stage_4_5__global_0_0_copy_stage4_local;
		maximum_found_stage_4_5__global_0_0_copy_stage4 = maximum_found_stage_4_5__global_0_0_copy_stage4_local;
		// forec:statement:pause:pause17:start
		stage4__thread.programCounter = &&pause17;
		goto *stage4__thread.nextThread -> programCounter;
		pause17:;
		// forec:statement:pause:pause17:end
		// Update the values of the used shared variables from their global copy.
		input_size__global_0_0_copy_stage4_local = input_size__global_0_0;
		cordic_out_stage_3_4__global_0_0_copy_stage4_local = cordic_out_stage_3_4__global_0_0;
		data_out_FT_stage_4_5__global_0_0_copy_stage4_local = data_out_FT_stage_4_5__global_0_0;
		maximum_found_stage_4_5__global_0_0_copy_stage4_local = maximum_found_stage_4_5__global_0_0;
		burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage4_local = burst_found_pulse_for_FT_stage_3_4__global_0_0;


		for (k__stage4_0_0 = 0; k__stage4_0_0 < input_size__global_0_0_copy_stage4_local.value - 1; ++k__stage4_0_0) {
			maximum_found_stage_4_5_copy__stage4_1_1 = maximum_found_stage_4_5__global_0_0_copy_stage4_local.value;
			computeStage4(&downsampling_flag__stage4_0_0, &maximum_found_stage_4_5_copy__stage4_1_1, &maximum_found__stage4_0_0, data_store_real__stage4_0_0, data_store_imag__stage4_0_0, &data_store_index__stage4_0_0, data_quant_real__stage4_0_0, data_quant_imag__stage4_0_0, &data_quant_index__stage4_0_0, &FTS_count__stage4_0_0, &maximum__stage4_0_0, &maximum_new__stage4_0_0, &fine_time_est_int__stage4_0_0, &fine_time_est_new__stage4_0_0, &difference_in_fine_time_est__stage4_0_0, cordic_out_stage_3_4__global_0_0_copy_stage4_local.value, &data_out_FT__stage4_1_1, burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage4_local.value);
			maximum_found_stage_4_5__global_0_0_copy_stage4_local.value = maximum_found_stage_4_5_copy__stage4_1_1;
			maximum_found_stage_4_5__global_0_0_copy_stage4_local.status = FOREC_SHARED_MODIFIED;
			data_out_FT_stage_4_5__global_0_0_copy_stage4_local.value = data_out_FT__stage4_1_1;
			data_out_FT_stage_4_5__global_0_0_copy_stage4_local.status = FOREC_SHARED_MODIFIED;

			// pause;
			// Write the local copy of shared variables back to their global copy.
			data_out_FT_stage_4_5__global_0_0_copy_stage4 = data_out_FT_stage_4_5__global_0_0_copy_stage4_local;
			maximum_found_stage_4_5__global_0_0_copy_stage4 = maximum_found_stage_4_5__global_0_0_copy_stage4_local;
			// forec:statement:pause:pause18:start
			stage4__thread.programCounter = &&pause18;
			goto *stage4__thread.nextThread -> programCounter;
			pause18:;
			// forec:statement:pause:pause18:end
			// Update the values of the used shared variables from their global copy.
			input_size__global_0_0_copy_stage4_local = input_size__global_0_0;
			cordic_out_stage_3_4__global_0_0_copy_stage4_local = cordic_out_stage_3_4__global_0_0;
			data_out_FT_stage_4_5__global_0_0_copy_stage4_local = data_out_FT_stage_4_5__global_0_0;
			maximum_found_stage_4_5__global_0_0_copy_stage4_local = maximum_found_stage_4_5__global_0_0;
			burst_found_pulse_for_FT_stage_3_4__global_0_0_copy_stage4_local = burst_found_pulse_for_FT_stage_3_4__global_0_0;

			// forec:iteration:for1_14:bound:7:7
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		data_out_FT_stage_4_5__global_0_0_copy_stage4 = data_out_FT_stage_4_5__global_0_0_copy_stage4_local;
		maximum_found_stage_4_5__global_0_0_copy_stage4 = maximum_found_stage_4_5__global_0_0_copy_stage4_local;

		// forec:scheduler:threadRemove:stage4:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		stage4__thread.nextThread -> prevThread = stage4__thread.prevThread;
		stage4__thread.prevThread -> nextThread = stage4__thread.nextThread;
		goto *stage4__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:stage4:end
	} // stage4__thread
	// forec:thread:stage4:end

	// forec:thread:stage5:start
	/*--------------------------------------------------------------
	| Thread stage5
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_fft_re_reversed__global_0_0 fft_re_reversed__global_0_0_copy_stage5_local;
	Shared_fft_im_reversed__global_0_0 fft_im_reversed__global_0_0_copy_stage5_local;
	Shared_input_size__global_0_0 input_size__global_0_0_copy_stage5_local;
	Shared_data_out_FT_stage_4_5__global_0_0 data_out_FT_stage_4_5__global_0_0_copy_stage5_local;
	Shared_maximum_found_stage_4_5__global_0_0 maximum_found_stage_4_5__global_0_0_copy_stage5_local;
	Shared_maximum_found_stage_5_6__global_0_0 maximum_found_stage_5_6__global_0_0_copy_stage5_local;
	Shared_re_out__global_0_0 re_out__global_0_0_copy_stage5_local;
	Shared_im_out__global_0_0 im_out__global_0_0_copy_stage5_local;
	int cnt_16__stage5_0_0;
	int cnt_64__stage5_0_0;
	int cnt_128__stage5_0_0;
	int downsampling_flag__stage5_0_0;
	int mk_test__stage5_0_0;
	int GI_Flag__stage5_0_0;
	float bf2_fifo_stage5_i__stage5_0_0;
	float bf2_fifo_stage5_q__stage5_0_0;
	float fifo_stage5_i_reg__stage5_0_0;
	float fifo_stage5_q_reg__stage5_0_0;
	float bf2_n_stage5_i__stage5_0_0;
	float bf2_n_stage5_q__stage5_0_0;
	float bf2_fifo_stage4_i__stage5_0_0;
	float bf2_fifo_stage4_q__stage5_0_0;
	float fifo_stage4_i_reg__stage5_0_0;
	float fifo_stage4_q_reg__stage5_0_0;
	float bf2_n_stage4_i__stage5_0_0;
	float bf2_n_stage4_q__stage5_0_0;
	float bf2_fifo_stage3_i__stage5_0_0;
	float bf2_fifo_stage3_q__stage5_0_0;
	float fifo_stage3_i_reg__stage5_0_0;
	float fifo_stage3_q_reg__stage5_0_0;
	float bf2_n_stage3_i__stage5_0_0;
	float bf2_n_stage3_q__stage5_0_0;
	float bf2_fifo_stage2_i__stage5_0_0;
	float bf2_fifo_stage2_q__stage5_0_0;
	float fifo_stage2_i_reg__stage5_0_0;
	float fifo_stage2_q_reg__stage5_0_0;
	float bf2_n_stage2_i__stage5_0_0;
	float bf2_n_stage2_q__stage5_0_0;
	float bf2_fifo_stage1_i__stage5_0_0;
	float bf2_fifo_stage1_q__stage5_0_0;
	float fifo_stage1_i_reg__stage5_0_0;
	float fifo_stage1_q_reg__stage5_0_0;
	float bf2_n_stage1_i__stage5_0_0;
	float bf2_n_stage1_q__stage5_0_0;
	float bf2_fifo_stage0_i__stage5_0_0;
	float bf2_fifo_stage0_q__stage5_0_0;
	float fifo_stage0_i_reg__stage5_0_0;
	float fifo_stage0_q_reg__stage5_0_0;
	float bf2_n_stage0_i__stage5_0_0;
	float bf2_n_stage0_q__stage5_0_0;
	int cnt_index__stage5_0_0;
	int multiple_streams_index__stage5_0_0;
	int fifo_len_div2_1__stage5_0_0;
	int nsample_1__stage5_0_0;
	float fifo_i_array_1__stage5_0_0[3];
	float fifo_q_array_1__stage5_0_0[3];
	int a__stage5_0_0;
	int fifo_len_div2_4__stage5_0_0;
	int nsample_4__stage5_0_0;
	float fifo_i_array_4__stage5_0_0[31];
	float fifo_q_array_4__stage5_0_0[31];
	float fifo_i_tmp_4__stage5_0_0;
	float fifo_q_tmp_4__stage5_0_0;
	int fifo_len_div2_5__stage5_0_0;
	int nsample_5__stage5_0_0;
	float fifo_i_array_5__stage5_0_0[63];
	float fifo_q_array_5__stage5_0_0[63];
	float fifo_i_tmp_5__stage5_0_0;
	float fifo_q_tmp_5__stage5_0_0;
	int fifo_len_div2_2__stage5_0_0;
	int nsample_2__stage5_0_0;
	float fifo_i_array_2__stage5_0_0[7];
	float fifo_q_array_2__stage5_0_0[7];
	int fifo_len_div2_3__stage5_0_0;
	int nsample_3__stage5_0_0;
	float fifo_i_array_3__stage5_0_0[15];
	float fifo_q_array_3__stage5_0_0[15];
	float fifo_i_tmp_3__stage5_0_0;
	float fifo_q_tmp_3__stage5_0_0;
	int k__stage5_0_0;
	int s__stage5_5_1[6];
	float mult_stage43_i__stage5_5_1, mult_stage43_q__stage5_5_1;
	int twiddle43_ptr__stage5_5_1;
	int twiddle_ptr_tmp__stage5_6_1;
	float calc1_re__stage5_6_1;
	float calc2_re__stage5_6_1;
	float calc1_im__stage5_6_1;
	float calc2_im__stage5_6_1;
	float mult_stage21_i__stage5_5_1, mult_stage21_q__stage5_5_1;
	int twiddle21_ptr__stage5_5_1;
	int twiddle_ptr_tmp__stage5_6_2;
	float calc1_re__stage5_6_2;
	float calc2_re__stage5_6_2;
	float calc1_im__stage5_6_2;
	float calc2_im__stage5_6_2;

	// Thread body -------------------------------------------------
	stage5__thread: {
		// Initialise the local copies of shared variables.
		fft_re_reversed__global_0_0_copy_stage5_local.value = fft_re_reversed__global_0_0.value;
		fft_re_reversed__global_0_0_copy_stage5_local.status = FOREC_SHARED_UNMODIFIED;
		fft_im_reversed__global_0_0_copy_stage5_local.value = fft_im_reversed__global_0_0.value;
		fft_im_reversed__global_0_0_copy_stage5_local.status = FOREC_SHARED_UNMODIFIED;
		input_size__global_0_0_copy_stage5_local.value = input_size__global_0_0.value;
		input_size__global_0_0_copy_stage5_local.status = FOREC_SHARED_UNMODIFIED;
		data_out_FT_stage_4_5__global_0_0_copy_stage5_local.value = data_out_FT_stage_4_5__global_0_0.value;
		data_out_FT_stage_4_5__global_0_0_copy_stage5_local.status = FOREC_SHARED_UNMODIFIED;
		maximum_found_stage_4_5__global_0_0_copy_stage5_local.value = maximum_found_stage_4_5__global_0_0.value;
		maximum_found_stage_4_5__global_0_0_copy_stage5_local.status = FOREC_SHARED_UNMODIFIED;
		maximum_found_stage_5_6__global_0_0_copy_stage5_local.value = maximum_found_stage_5_6__global_0_0.value;
		maximum_found_stage_5_6__global_0_0_copy_stage5_local.status = FOREC_SHARED_UNMODIFIED;
		re_out__global_0_0_copy_stage5_local.value = re_out__global_0_0.value;
		re_out__global_0_0_copy_stage5_local.status = FOREC_SHARED_UNMODIFIED;
		im_out__global_0_0_copy_stage5_local.value = im_out__global_0_0.value;
		im_out__global_0_0_copy_stage5_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		cnt_16__stage5_0_0 = 0;
		cnt_64__stage5_0_0 = 0;
		cnt_128__stage5_0_0 = 0;
		downsampling_flag__stage5_0_0 = 0;
		mk_test__stage5_0_0 = 0;
		GI_Flag__stage5_0_0 = 0;
		bf2_fifo_stage5_i__stage5_0_0 = (float)0.0;
		bf2_fifo_stage5_q__stage5_0_0 = (float)0.0;
		fifo_stage5_i_reg__stage5_0_0 = (float)0.0;
		fifo_stage5_q_reg__stage5_0_0 = (float)0.0;
		bf2_n_stage5_i__stage5_0_0 = (float)0.0;
		bf2_n_stage5_q__stage5_0_0 = (float)0.0;
		bf2_fifo_stage4_i__stage5_0_0 = (float)0.0;
		bf2_fifo_stage4_q__stage5_0_0 = (float)0.0;
		fifo_stage4_i_reg__stage5_0_0 = (float)0.0;
		fifo_stage4_q_reg__stage5_0_0 = (float)0.0;
		bf2_n_stage4_i__stage5_0_0 = (float)0.0;
		bf2_n_stage4_q__stage5_0_0 = (float)0.0;
		bf2_fifo_stage3_i__stage5_0_0 = (float)0.0;
		bf2_fifo_stage3_q__stage5_0_0 = (float)0.0;
		fifo_stage3_i_reg__stage5_0_0 = (float)0.0;
		fifo_stage3_q_reg__stage5_0_0 = (float)0.0;
		bf2_n_stage3_i__stage5_0_0 = (float)0.0;
		bf2_n_stage3_q__stage5_0_0 = (float)0.0;
		bf2_fifo_stage2_i__stage5_0_0 = (float)0.0;
		bf2_fifo_stage2_q__stage5_0_0 = (float)0.0;
		fifo_stage2_i_reg__stage5_0_0 = (float)0.0;
		fifo_stage2_q_reg__stage5_0_0 = (float)0.0;
		bf2_n_stage2_i__stage5_0_0 = (float)0.0;
		bf2_n_stage2_q__stage5_0_0 = (float)0.0;
		bf2_fifo_stage1_i__stage5_0_0 = (float)0.0;
		bf2_fifo_stage1_q__stage5_0_0 = (float)0.0;
		fifo_stage1_i_reg__stage5_0_0 = (float)0.0;
		fifo_stage1_q_reg__stage5_0_0 = (float)0.0;
		bf2_n_stage1_i__stage5_0_0 = (float)0.0;
		bf2_n_stage1_q__stage5_0_0 = (float)0.0;
		bf2_fifo_stage0_i__stage5_0_0 = (float)0.0;
		bf2_fifo_stage0_q__stage5_0_0 = (float)0.0;
		fifo_stage0_i_reg__stage5_0_0 = (float)0.0;
		fifo_stage0_q_reg__stage5_0_0 = (float)0.0;
		bf2_n_stage0_i__stage5_0_0 = (float)0.0;
		bf2_n_stage0_q__stage5_0_0 = (float)0.0;
		cnt_index__stage5_0_0 = 0;
		multiple_streams_index__stage5_0_0 = 0;
		fifo_len_div2_1__stage5_0_0 = 1;
		nsample_1__stage5_0_0 = 0;
		for (a__stage5_0_0 = 0; a__stage5_0_0 < 3; a__stage5_0_0++) {
			fifo_i_array_1__stage5_0_0[a__stage5_0_0] = (float)0.0;
			fifo_q_array_1__stage5_0_0[a__stage5_0_0] = (float)0.0;
			// forec:iteration:for1_16:bound:3:3
		}
		fifo_len_div2_4__stage5_0_0 = 15;
		nsample_4__stage5_0_0 = 0;
		for (a__stage5_0_0 = 0; a__stage5_0_0 < 31; a__stage5_0_0++) {
			fifo_i_array_4__stage5_0_0[a__stage5_0_0] = (float)0.0;
			fifo_q_array_4__stage5_0_0[a__stage5_0_0] = (float)0.0;
			// forec:iteration:for1_17:bound:31:31
		}
		fifo_i_tmp_4__stage5_0_0 = (float)0.0;
		fifo_q_tmp_4__stage5_0_0 = (float)0.0;
		fifo_len_div2_5__stage5_0_0 = 31;
		nsample_5__stage5_0_0 = 0;
		for (a__stage5_0_0 = 0; a__stage5_0_0 < 63; a__stage5_0_0++) {
			fifo_i_array_5__stage5_0_0[a__stage5_0_0] = (float)0.0;
			fifo_q_array_5__stage5_0_0[a__stage5_0_0] = (float)0.0;
			// forec:iteration:for1_18:bound:63:63
		}
		fifo_i_tmp_5__stage5_0_0 = (float)0.0;
		fifo_q_tmp_5__stage5_0_0 = (float)0.0;
		fifo_len_div2_2__stage5_0_0 = 3;
		nsample_2__stage5_0_0 = 0;
		for (a__stage5_0_0 = 0; a__stage5_0_0 < 7; a__stage5_0_0++) {
			fifo_i_array_2__stage5_0_0[a__stage5_0_0] = (float)0.0;
			fifo_q_array_2__stage5_0_0[a__stage5_0_0] = (float)0.0;
			// forec:iteration:for1_19:bound:7:7
		}
		fifo_len_div2_3__stage5_0_0 = 7;
		nsample_3__stage5_0_0 = 0;
		for (a__stage5_0_0 = 0; a__stage5_0_0 < 15; a__stage5_0_0++) {
			fifo_i_array_3__stage5_0_0[a__stage5_0_0] = (float)0.0;
			fifo_q_array_3__stage5_0_0[a__stage5_0_0] = (float)0.0;
			// forec:iteration:for1_20:bound:15:15
		}

		// pause;
		// Write the local copy of shared variables back to their global copy.
		maximum_found_stage_5_6__global_0_0_copy_stage5 = maximum_found_stage_5_6__global_0_0_copy_stage5_local;
		re_out__global_0_0_copy_stage5 = re_out__global_0_0_copy_stage5_local;
		im_out__global_0_0_copy_stage5 = im_out__global_0_0_copy_stage5_local;
		// forec:statement:pause:pause19:start
		stage5__thread.programCounter = &&pause19;
		goto *stage5__thread.nextThread -> programCounter;
		pause19:;
		// forec:statement:pause:pause19:end
		// Update the values of the used shared variables from their global copy.
		fft_re_reversed__global_0_0_copy_stage5_local = fft_re_reversed__global_0_0;
		fft_im_reversed__global_0_0_copy_stage5_local = fft_im_reversed__global_0_0;
		input_size__global_0_0_copy_stage5_local = input_size__global_0_0;
		data_out_FT_stage_4_5__global_0_0_copy_stage5_local = data_out_FT_stage_4_5__global_0_0;
		maximum_found_stage_4_5__global_0_0_copy_stage5_local = maximum_found_stage_4_5__global_0_0;
		maximum_found_stage_5_6__global_0_0_copy_stage5_local = maximum_found_stage_5_6__global_0_0;
		re_out__global_0_0_copy_stage5_local = re_out__global_0_0;
		im_out__global_0_0_copy_stage5_local = im_out__global_0_0;


		// pause;
		// Write the local copy of shared variables back to their global copy.
		maximum_found_stage_5_6__global_0_0_copy_stage5 = maximum_found_stage_5_6__global_0_0_copy_stage5_local;
		re_out__global_0_0_copy_stage5 = re_out__global_0_0_copy_stage5_local;
		im_out__global_0_0_copy_stage5 = im_out__global_0_0_copy_stage5_local;
		// forec:statement:pause:pause20:start
		stage5__thread.programCounter = &&pause20;
		goto *stage5__thread.nextThread -> programCounter;
		pause20:;
		// forec:statement:pause:pause20:end
		// Update the values of the used shared variables from their global copy.
		fft_re_reversed__global_0_0_copy_stage5_local = fft_re_reversed__global_0_0;
		fft_im_reversed__global_0_0_copy_stage5_local = fft_im_reversed__global_0_0;
		input_size__global_0_0_copy_stage5_local = input_size__global_0_0;
		data_out_FT_stage_4_5__global_0_0_copy_stage5_local = data_out_FT_stage_4_5__global_0_0;
		maximum_found_stage_4_5__global_0_0_copy_stage5_local = maximum_found_stage_4_5__global_0_0;
		maximum_found_stage_5_6__global_0_0_copy_stage5_local = maximum_found_stage_5_6__global_0_0;
		re_out__global_0_0_copy_stage5_local = re_out__global_0_0;
		im_out__global_0_0_copy_stage5_local = im_out__global_0_0;


		// pause;
		// Write the local copy of shared variables back to their global copy.
		maximum_found_stage_5_6__global_0_0_copy_stage5 = maximum_found_stage_5_6__global_0_0_copy_stage5_local;
		re_out__global_0_0_copy_stage5 = re_out__global_0_0_copy_stage5_local;
		im_out__global_0_0_copy_stage5 = im_out__global_0_0_copy_stage5_local;
		// forec:statement:pause:pause21:start
		stage5__thread.programCounter = &&pause21;
		goto *stage5__thread.nextThread -> programCounter;
		pause21:;
		// forec:statement:pause:pause21:end
		// Update the values of the used shared variables from their global copy.
		fft_re_reversed__global_0_0_copy_stage5_local = fft_re_reversed__global_0_0;
		fft_im_reversed__global_0_0_copy_stage5_local = fft_im_reversed__global_0_0;
		input_size__global_0_0_copy_stage5_local = input_size__global_0_0;
		data_out_FT_stage_4_5__global_0_0_copy_stage5_local = data_out_FT_stage_4_5__global_0_0;
		maximum_found_stage_4_5__global_0_0_copy_stage5_local = maximum_found_stage_4_5__global_0_0;
		maximum_found_stage_5_6__global_0_0_copy_stage5_local = maximum_found_stage_5_6__global_0_0;
		re_out__global_0_0_copy_stage5_local = re_out__global_0_0;
		im_out__global_0_0_copy_stage5_local = im_out__global_0_0;


		// pause;
		// Write the local copy of shared variables back to their global copy.
		maximum_found_stage_5_6__global_0_0_copy_stage5 = maximum_found_stage_5_6__global_0_0_copy_stage5_local;
		re_out__global_0_0_copy_stage5 = re_out__global_0_0_copy_stage5_local;
		im_out__global_0_0_copy_stage5 = im_out__global_0_0_copy_stage5_local;
		// forec:statement:pause:pause22:start
		stage5__thread.programCounter = &&pause22;
		goto *stage5__thread.nextThread -> programCounter;
		pause22:;
		// forec:statement:pause:pause22:end
		// Update the values of the used shared variables from their global copy.
		fft_re_reversed__global_0_0_copy_stage5_local = fft_re_reversed__global_0_0;
		fft_im_reversed__global_0_0_copy_stage5_local = fft_im_reversed__global_0_0;
		input_size__global_0_0_copy_stage5_local = input_size__global_0_0;
		data_out_FT_stage_4_5__global_0_0_copy_stage5_local = data_out_FT_stage_4_5__global_0_0;
		maximum_found_stage_4_5__global_0_0_copy_stage5_local = maximum_found_stage_4_5__global_0_0;
		maximum_found_stage_5_6__global_0_0_copy_stage5_local = maximum_found_stage_5_6__global_0_0;
		re_out__global_0_0_copy_stage5_local = re_out__global_0_0;
		im_out__global_0_0_copy_stage5_local = im_out__global_0_0;


		maximum_found_stage_5_6__global_0_0_copy_stage5_local.value = maximum_found_stage_4_5__global_0_0_copy_stage5_local.value;
		maximum_found_stage_5_6__global_0_0_copy_stage5_local.status = FOREC_SHARED_MODIFIED;

		// pause;
		// Write the local copy of shared variables back to their global copy.
		maximum_found_stage_5_6__global_0_0_copy_stage5 = maximum_found_stage_5_6__global_0_0_copy_stage5_local;
		re_out__global_0_0_copy_stage5 = re_out__global_0_0_copy_stage5_local;
		im_out__global_0_0_copy_stage5 = im_out__global_0_0_copy_stage5_local;
		// forec:statement:pause:pause23:start
		stage5__thread.programCounter = &&pause23;
		goto *stage5__thread.nextThread -> programCounter;
		pause23:;
		// forec:statement:pause:pause23:end
		// Update the values of the used shared variables from their global copy.
		fft_re_reversed__global_0_0_copy_stage5_local = fft_re_reversed__global_0_0;
		fft_im_reversed__global_0_0_copy_stage5_local = fft_im_reversed__global_0_0;
		input_size__global_0_0_copy_stage5_local = input_size__global_0_0;
		data_out_FT_stage_4_5__global_0_0_copy_stage5_local = data_out_FT_stage_4_5__global_0_0;
		maximum_found_stage_4_5__global_0_0_copy_stage5_local = maximum_found_stage_4_5__global_0_0;
		maximum_found_stage_5_6__global_0_0_copy_stage5_local = maximum_found_stage_5_6__global_0_0;
		re_out__global_0_0_copy_stage5_local = re_out__global_0_0;
		im_out__global_0_0_copy_stage5_local = im_out__global_0_0;


		for (k__stage5_0_0 = 0; k__stage5_0_0 < input_size__global_0_0_copy_stage5_local.value; ++k__stage5_0_0) {
			if (downsampling_flag__stage5_0_0 == 0) {
				if (maximum_found_stage_4_5__global_0_0_copy_stage5_local.value == 1) {
					if (mk_test__stage5_0_0 == 0) {
						cnt_128__stage5_0_0 = 0;
						cnt_64__stage5_0_0 = 0;
						cnt_16__stage5_0_0 = 0;
						GI_Flag__stage5_0_0 = 0;
					} else {
						// ifElse45
						if (cnt_128__stage5_0_0 < 127) {
							cnt_128__stage5_0_0++;
							GI_Flag__stage5_0_0 = 0;
						} else {
							// ifElse44
							if ((cnt_16__stage5_0_0 < 16) && (cnt_64__stage5_0_0 == 0)) {
								GI_Flag__stage5_0_0 = 1;
								cnt_16__stage5_0_0++;
							} else {
								// ifElse43
								if (cnt_64__stage5_0_0 < 63) {
									GI_Flag__stage5_0_0 = 0;
									cnt_64__stage5_0_0++;
								} else {
									// ifElse42
									cnt_64__stage5_0_0 = 0;
									cnt_16__stage5_0_0 = 0;
								}
							}
						}
					}

					if (GI_Flag__stage5_0_0 == 0) {
						mk_test__stage5_0_0 = 1;

						{
							re_out__global_0_0_copy_stage5_local.value = bf2_n_stage0_i__stage5_0_0;
							re_out__global_0_0_copy_stage5_local.status = FOREC_SHARED_MODIFIED;
							im_out__global_0_0_copy_stage5_local.value = bf2_n_stage0_q__stage5_0_0;
							im_out__global_0_0_copy_stage5_local.status = FOREC_SHARED_MODIFIED;
							s__stage5_5_1[0] = (cnt_index__stage5_0_0%2 > 0);
							s__stage5_5_1[1] = (cnt_index__stage5_0_0%4 > 1);
							s__stage5_5_1[2] = (cnt_index__stage5_0_0%8 > 3);
							s__stage5_5_1[3] = (cnt_index__stage5_0_0%16 > 7);
							s__stage5_5_1[4] = (cnt_index__stage5_0_0%32 > 15);
							s__stage5_5_1[5] = (cnt_index__stage5_0_0%64 > 31);
							fft64Stage5(s__stage5_5_1[5], fifo_len_div2_5__stage5_0_0, fifo_stage5_i_reg__stage5_0_0, fifo_stage5_q_reg__stage5_0_0, &bf2_n_stage5_i__stage5_0_0, &bf2_n_stage5_q__stage5_0_0, &nsample_5__stage5_0_0, &fifo_i_tmp_5__stage5_0_0, &fifo_q_tmp_5__stage5_0_0, &bf2_fifo_stage5_i__stage5_0_0, &bf2_fifo_stage5_q__stage5_0_0, fifo_i_array_5__stage5_0_0, fifo_q_array_5__stage5_0_0, data_out_FT_stage_4_5__global_0_0_copy_stage5_local.value);
							fifo_stage5_i_reg__stage5_0_0 = bf2_fifo_stage5_i__stage5_0_0;
							fifo_stage5_q_reg__stage5_0_0 = bf2_fifo_stage5_q__stage5_0_0;
							fft64Stage4(s__stage5_5_1[4], s__stage5_5_1[5], fifo_len_div2_4__stage5_0_0, bf2_n_stage5_i__stage5_0_0, bf2_n_stage5_q__stage5_0_0, fifo_stage4_i_reg__stage5_0_0, fifo_stage4_q_reg__stage5_0_0, &bf2_n_stage4_i__stage5_0_0, &bf2_n_stage4_q__stage5_0_0, &fifo_i_tmp_4__stage5_0_0, &fifo_q_tmp_4__stage5_0_0, &bf2_fifo_stage4_i__stage5_0_0, &bf2_fifo_stage4_q__stage5_0_0, &nsample_4__stage5_0_0, fifo_i_array_4__stage5_0_0, fifo_q_array_4__stage5_0_0);
							fifo_stage4_i_reg__stage5_0_0 = bf2_fifo_stage4_i__stage5_0_0;
							fifo_stage4_q_reg__stage5_0_0 = bf2_fifo_stage4_q__stage5_0_0;
							twiddle43_ptr__stage5_5_1 = multiple_streams_index__stage5_0_0%64;

							{
								if (twiddle43_ptr__stage5_5_1 < twiddle43_size__global_0_0) {
									twiddle_ptr_tmp__stage5_6_1 = twiddle43_ptr__stage5_5_1;
								} else {
									// ifElse46
									twiddle_ptr_tmp__stage5_6_1 = 0;
								}
								calc1_re__stage5_6_1 = bf2_n_stage4_i__stage5_0_0*twiddle43_re__global_0_0[twiddle_ptr_tmp__stage5_6_1];
								calc2_re__stage5_6_1 = bf2_n_stage4_q__stage5_0_0*twiddle43_im__global_0_0[twiddle_ptr_tmp__stage5_6_1];
								calc1_im__stage5_6_1 = bf2_n_stage4_i__stage5_0_0*twiddle43_im__global_0_0[twiddle_ptr_tmp__stage5_6_1];
								calc2_im__stage5_6_1 = bf2_n_stage4_q__stage5_0_0*twiddle43_re__global_0_0[twiddle_ptr_tmp__stage5_6_1];
								mult_stage43_i__stage5_5_1 = calc1_re__stage5_6_1 - calc2_re__stage5_6_1;
								mult_stage43_q__stage5_5_1 = calc1_im__stage5_6_1 + calc2_im__stage5_6_1;
							}

							fft64Stage3(s__stage5_5_1[3], fifo_len_div2_3__stage5_0_0, fifo_stage3_i_reg__stage5_0_0, fifo_stage3_q_reg__stage5_0_0, mult_stage43_i__stage5_5_1, mult_stage43_q__stage5_5_1, &bf2_n_stage3_i__stage5_0_0, &bf2_n_stage3_q__stage5_0_0, &fifo_i_tmp_3__stage5_0_0, &fifo_q_tmp_3__stage5_0_0, &bf2_fifo_stage3_i__stage5_0_0, &bf2_fifo_stage3_q__stage5_0_0, &nsample_3__stage5_0_0, fifo_i_array_3__stage5_0_0, fifo_q_array_3__stage5_0_0);
							fifo_stage3_i_reg__stage5_0_0 = bf2_fifo_stage3_i__stage5_0_0;
							fifo_stage3_q_reg__stage5_0_0 = bf2_fifo_stage3_q__stage5_0_0;
							fft64Stage2(s__stage5_5_1[2], s__stage5_5_1[3], fifo_len_div2_2__stage5_0_0, bf2_n_stage3_i__stage5_0_0, bf2_n_stage3_q__stage5_0_0, fifo_stage2_i_reg__stage5_0_0, fifo_stage2_q_reg__stage5_0_0, &bf2_n_stage2_i__stage5_0_0, &bf2_n_stage2_q__stage5_0_0, &nsample_2__stage5_0_0, &bf2_fifo_stage2_i__stage5_0_0, &bf2_fifo_stage2_q__stage5_0_0, fifo_i_array_2__stage5_0_0, fifo_q_array_2__stage5_0_0);
							fifo_stage2_i_reg__stage5_0_0 = bf2_fifo_stage2_i__stage5_0_0;
							fifo_stage2_q_reg__stage5_0_0 = bf2_fifo_stage2_q__stage5_0_0;
							twiddle21_ptr__stage5_5_1 = multiple_streams_index__stage5_0_0%16;

							{
								if (twiddle21_ptr__stage5_5_1 < twiddle21_size__global_0_0) {
									twiddle_ptr_tmp__stage5_6_2 = twiddle21_ptr__stage5_5_1;
								} else {
									// ifElse47
									twiddle_ptr_tmp__stage5_6_2 = 0;
								}
								calc1_re__stage5_6_2 = bf2_n_stage2_i__stage5_0_0*twiddle21_re__global_0_0[twiddle_ptr_tmp__stage5_6_2];
								calc2_re__stage5_6_2 = bf2_n_stage2_q__stage5_0_0*twiddle21_im__global_0_0[twiddle_ptr_tmp__stage5_6_2];
								calc1_im__stage5_6_2 = bf2_n_stage2_i__stage5_0_0*twiddle21_im__global_0_0[twiddle_ptr_tmp__stage5_6_2];
								calc2_im__stage5_6_2 = bf2_n_stage2_q__stage5_0_0*twiddle21_re__global_0_0[twiddle_ptr_tmp__stage5_6_2];
								mult_stage21_i__stage5_5_1 = calc1_re__stage5_6_2 - calc2_re__stage5_6_2;
								mult_stage21_q__stage5_5_1 = calc1_im__stage5_6_2 + calc2_im__stage5_6_2;
							}

							fft64Stage1(s__stage5_5_1[1], fifo_len_div2_1__stage5_0_0, fifo_stage1_i_reg__stage5_0_0, fifo_stage1_q_reg__stage5_0_0, mult_stage21_i__stage5_5_1, mult_stage21_q__stage5_5_1, &bf2_n_stage1_i__stage5_0_0, &bf2_n_stage1_q__stage5_0_0, &nsample_1__stage5_0_0, &bf2_fifo_stage1_i__stage5_0_0, &bf2_fifo_stage1_q__stage5_0_0, fifo_i_array_1__stage5_0_0, fifo_q_array_1__stage5_0_0);
							fifo_stage1_i_reg__stage5_0_0 = bf2_fifo_stage1_i__stage5_0_0;
							fifo_stage1_q_reg__stage5_0_0 = bf2_fifo_stage1_q__stage5_0_0;
							fft64Stage0(s__stage5_5_1[0], s__stage5_5_1[1], bf2_n_stage1_i__stage5_0_0, bf2_n_stage1_q__stage5_0_0, fifo_stage0_i_reg__stage5_0_0, fifo_stage0_q_reg__stage5_0_0, &bf2_n_stage0_i__stage5_0_0, &bf2_n_stage0_q__stage5_0_0, &bf2_fifo_stage0_i__stage5_0_0, &bf2_fifo_stage0_q__stage5_0_0);
							fifo_stage0_i_reg__stage5_0_0 = bf2_fifo_stage0_i__stage5_0_0;
							fifo_stage0_q_reg__stage5_0_0 = bf2_fifo_stage0_q__stage5_0_0;
							if (multiple_streams_index__stage5_0_0 < 63) {
								multiple_streams_index__stage5_0_0++;
							} else {
								// ifElse48
								multiple_streams_index__stage5_0_0 = 0;
							}
							if (cnt_index__stage5_0_0 < 63) {
								cnt_index__stage5_0_0++;
							} else {
								// ifElse49
								cnt_index__stage5_0_0 = 0;
							}
						}

						if (debug__global_0_0.value) {
							fprintf(fft_re_reversed__global_0_0_copy_stage5_local.value, "%12f\n", re_out__global_0_0_copy_stage5_local.value);
							fprintf(fft_im_reversed__global_0_0_copy_stage5_local.value, "%12f\n", im_out__global_0_0_copy_stage5_local.value);
						} else {
							// if50
						}
					} else {
						// if51
					}
				} else {
					// if52
				}

				downsampling_flag__stage5_0_0 = 1;
			} else {
				// ifElse53
				downsampling_flag__stage5_0_0 = 0;
			}

			maximum_found_stage_5_6__global_0_0_copy_stage5_local.value = maximum_found_stage_4_5__global_0_0_copy_stage5_local.value;
			maximum_found_stage_5_6__global_0_0_copy_stage5_local.status = FOREC_SHARED_MODIFIED;

			// pause;
			// Write the local copy of shared variables back to their global copy.
			maximum_found_stage_5_6__global_0_0_copy_stage5 = maximum_found_stage_5_6__global_0_0_copy_stage5_local;
			re_out__global_0_0_copy_stage5 = re_out__global_0_0_copy_stage5_local;
			im_out__global_0_0_copy_stage5 = im_out__global_0_0_copy_stage5_local;
			// forec:statement:pause:pause24:start
			stage5__thread.programCounter = &&pause24;
			goto *stage5__thread.nextThread -> programCounter;
			pause24:;
			// forec:statement:pause:pause24:end
			// Update the values of the used shared variables from their global copy.
			fft_re_reversed__global_0_0_copy_stage5_local = fft_re_reversed__global_0_0;
			fft_im_reversed__global_0_0_copy_stage5_local = fft_im_reversed__global_0_0;
			input_size__global_0_0_copy_stage5_local = input_size__global_0_0;
			data_out_FT_stage_4_5__global_0_0_copy_stage5_local = data_out_FT_stage_4_5__global_0_0;
			maximum_found_stage_4_5__global_0_0_copy_stage5_local = maximum_found_stage_4_5__global_0_0;
			maximum_found_stage_5_6__global_0_0_copy_stage5_local = maximum_found_stage_5_6__global_0_0;
			re_out__global_0_0_copy_stage5_local = re_out__global_0_0;
			im_out__global_0_0_copy_stage5_local = im_out__global_0_0;

			// forec:iteration:for1_21:bound:7:7
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.
		maximum_found_stage_5_6__global_0_0_copy_stage5 = maximum_found_stage_5_6__global_0_0_copy_stage5_local;
		re_out__global_0_0_copy_stage5 = re_out__global_0_0_copy_stage5_local;
		im_out__global_0_0_copy_stage5 = im_out__global_0_0_copy_stage5_local;

		// forec:scheduler:threadRemove:stage5:start

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		stage5__thread.nextThread -> prevThread = stage5__thread.prevThread;
		stage5__thread.prevThread -> nextThread = stage5__thread.nextThread;
		goto *stage5__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:stage5:end
	} // stage5__thread
	// forec:thread:stage5:end

	// forec:thread:stage6:start
	/*--------------------------------------------------------------
	| Thread stage6
	*-------------------------------------------------------------*/

	// Thread local declarations -----------------------------------
	Shared_CHE_out_I__global_0_0 CHE_out_I__global_0_0_copy_stage6_local;
	Shared_CHE_out_Q__global_0_0 CHE_out_Q__global_0_0_copy_stage6_local;
	Shared_CHC_out_I__global_0_0 CHC_out_I__global_0_0_copy_stage6_local;
	Shared_CHC_out_Q__global_0_0 CHC_out_Q__global_0_0_copy_stage6_local;
	Shared_fft_re_out__global_0_0 fft_re_out__global_0_0_copy_stage6_local;
	Shared_fft_im_out__global_0_0 fft_im_out__global_0_0_copy_stage6_local;
	Shared_input_size__global_0_0 input_size__global_0_0_copy_stage6_local;
	Shared_maximum_found_stage_5_6__global_0_0 maximum_found_stage_5_6__global_0_0_copy_stage6_local;
	Shared_re_out__global_0_0 re_out__global_0_0_copy_stage6_local;
	Shared_im_out__global_0_0 im_out__global_0_0_copy_stage6_local;
	int cnt_16__stage6_0_0;
	int cnt_64__stage6_0_0;
	int cnt_128__stage6_0_0;
	int inv_int__stage6_0_0;
	int mux_cnt__stage6_0_0;
	int a__stage6_0_0;
	int downsampling_flag__stage6_0_0;
	int mk_test__stage6_0_0;
	int GI_Flag__stage6_0_0;
	int i__stage6_0_0;
	int k__stage6_0_0;
	int index_int__stage6_5_1;
	int m_int__stage6_5_1;
	float *real_out_demux_ptr__stage6_6_2, *imag_out_demux_ptr__stage6_6_2;
	int j__stage6_6_2;
	int *output_CHE_real_ptr__stage6_7_3, *output_CHE_imag_ptr__stage6_7_3;
	int *output_CHC_real_ptr__stage6_7_4, *output_CHC_imag_ptr__stage6_7_4;

	// Thread body -------------------------------------------------
	stage6__thread: {
		// Initialise the local copies of shared variables.
		CHE_out_I__global_0_0_copy_stage6_local.value = CHE_out_I__global_0_0.value;
		CHE_out_I__global_0_0_copy_stage6_local.status = FOREC_SHARED_UNMODIFIED;
		CHE_out_Q__global_0_0_copy_stage6_local.value = CHE_out_Q__global_0_0.value;
		CHE_out_Q__global_0_0_copy_stage6_local.status = FOREC_SHARED_UNMODIFIED;
		CHC_out_I__global_0_0_copy_stage6_local.value = CHC_out_I__global_0_0.value;
		CHC_out_I__global_0_0_copy_stage6_local.status = FOREC_SHARED_UNMODIFIED;
		CHC_out_Q__global_0_0_copy_stage6_local.value = CHC_out_Q__global_0_0.value;
		CHC_out_Q__global_0_0_copy_stage6_local.status = FOREC_SHARED_UNMODIFIED;
		fft_re_out__global_0_0_copy_stage6_local.value = fft_re_out__global_0_0.value;
		fft_re_out__global_0_0_copy_stage6_local.status = FOREC_SHARED_UNMODIFIED;
		fft_im_out__global_0_0_copy_stage6_local.value = fft_im_out__global_0_0.value;
		fft_im_out__global_0_0_copy_stage6_local.status = FOREC_SHARED_UNMODIFIED;
		input_size__global_0_0_copy_stage6_local.value = input_size__global_0_0.value;
		input_size__global_0_0_copy_stage6_local.status = FOREC_SHARED_UNMODIFIED;
		maximum_found_stage_5_6__global_0_0_copy_stage6_local.value = maximum_found_stage_5_6__global_0_0.value;
		maximum_found_stage_5_6__global_0_0_copy_stage6_local.status = FOREC_SHARED_UNMODIFIED;
		re_out__global_0_0_copy_stage6_local.value = re_out__global_0_0.value;
		re_out__global_0_0_copy_stage6_local.status = FOREC_SHARED_UNMODIFIED;
		im_out__global_0_0_copy_stage6_local.value = im_out__global_0_0.value;
		im_out__global_0_0_copy_stage6_local.status = FOREC_SHARED_UNMODIFIED;
		//--------------------------------------------------------------

		cnt_16__stage6_0_0 = 0;
		cnt_64__stage6_0_0 = 0;
		cnt_128__stage6_0_0 = 0;
		inv_int__stage6_0_0 = 0;
		mux_cnt__stage6_0_0 = 0;
		for (a__stage6_0_0 = 0; a__stage6_0_0 < buffer_len__global_0_0; a__stage6_0_0++) {
			array_re__global_0_0.value[a__stage6_0_0] = (float)0.0;
			array_im__global_0_0.value[a__stage6_0_0] = (float)0.0;
			// forec:iteration:for1_22:bound:64:64
		}
		downsampling_flag__stage6_0_0 = 0;
		mk_test__stage6_0_0 = 0;
		GI_Flag__stage6_0_0 = 0;
		i__stage6_0_0 = 0;

		// pause;
		// forec:statement:pause:pause25:start
		stage6__thread.programCounter = &&pause25;
		goto *stage6__thread.nextThread -> programCounter;
		pause25:;
		// forec:statement:pause:pause25:end
		// Update the values of the used shared variables from their global copy.
		CHE_out_I__global_0_0_copy_stage6_local = CHE_out_I__global_0_0;
		CHE_out_Q__global_0_0_copy_stage6_local = CHE_out_Q__global_0_0;
		CHC_out_I__global_0_0_copy_stage6_local = CHC_out_I__global_0_0;
		CHC_out_Q__global_0_0_copy_stage6_local = CHC_out_Q__global_0_0;
		fft_re_out__global_0_0_copy_stage6_local = fft_re_out__global_0_0;
		fft_im_out__global_0_0_copy_stage6_local = fft_im_out__global_0_0;
		input_size__global_0_0_copy_stage6_local = input_size__global_0_0;
		maximum_found_stage_5_6__global_0_0_copy_stage6_local = maximum_found_stage_5_6__global_0_0;
		re_out__global_0_0_copy_stage6_local = re_out__global_0_0;
		im_out__global_0_0_copy_stage6_local = im_out__global_0_0;


		// pause;
		// forec:statement:pause:pause26:start
		stage6__thread.programCounter = &&pause26;
		goto *stage6__thread.nextThread -> programCounter;
		pause26:;
		// forec:statement:pause:pause26:end
		// Update the values of the used shared variables from their global copy.
		CHE_out_I__global_0_0_copy_stage6_local = CHE_out_I__global_0_0;
		CHE_out_Q__global_0_0_copy_stage6_local = CHE_out_Q__global_0_0;
		CHC_out_I__global_0_0_copy_stage6_local = CHC_out_I__global_0_0;
		CHC_out_Q__global_0_0_copy_stage6_local = CHC_out_Q__global_0_0;
		fft_re_out__global_0_0_copy_stage6_local = fft_re_out__global_0_0;
		fft_im_out__global_0_0_copy_stage6_local = fft_im_out__global_0_0;
		input_size__global_0_0_copy_stage6_local = input_size__global_0_0;
		maximum_found_stage_5_6__global_0_0_copy_stage6_local = maximum_found_stage_5_6__global_0_0;
		re_out__global_0_0_copy_stage6_local = re_out__global_0_0;
		im_out__global_0_0_copy_stage6_local = im_out__global_0_0;


		// pause;
		// forec:statement:pause:pause27:start
		stage6__thread.programCounter = &&pause27;
		goto *stage6__thread.nextThread -> programCounter;
		pause27:;
		// forec:statement:pause:pause27:end
		// Update the values of the used shared variables from their global copy.
		CHE_out_I__global_0_0_copy_stage6_local = CHE_out_I__global_0_0;
		CHE_out_Q__global_0_0_copy_stage6_local = CHE_out_Q__global_0_0;
		CHC_out_I__global_0_0_copy_stage6_local = CHC_out_I__global_0_0;
		CHC_out_Q__global_0_0_copy_stage6_local = CHC_out_Q__global_0_0;
		fft_re_out__global_0_0_copy_stage6_local = fft_re_out__global_0_0;
		fft_im_out__global_0_0_copy_stage6_local = fft_im_out__global_0_0;
		input_size__global_0_0_copy_stage6_local = input_size__global_0_0;
		maximum_found_stage_5_6__global_0_0_copy_stage6_local = maximum_found_stage_5_6__global_0_0;
		re_out__global_0_0_copy_stage6_local = re_out__global_0_0;
		im_out__global_0_0_copy_stage6_local = im_out__global_0_0;


		// pause;
		// forec:statement:pause:pause28:start
		stage6__thread.programCounter = &&pause28;
		goto *stage6__thread.nextThread -> programCounter;
		pause28:;
		// forec:statement:pause:pause28:end
		// Update the values of the used shared variables from their global copy.
		CHE_out_I__global_0_0_copy_stage6_local = CHE_out_I__global_0_0;
		CHE_out_Q__global_0_0_copy_stage6_local = CHE_out_Q__global_0_0;
		CHC_out_I__global_0_0_copy_stage6_local = CHC_out_I__global_0_0;
		CHC_out_Q__global_0_0_copy_stage6_local = CHC_out_Q__global_0_0;
		fft_re_out__global_0_0_copy_stage6_local = fft_re_out__global_0_0;
		fft_im_out__global_0_0_copy_stage6_local = fft_im_out__global_0_0;
		input_size__global_0_0_copy_stage6_local = input_size__global_0_0;
		maximum_found_stage_5_6__global_0_0_copy_stage6_local = maximum_found_stage_5_6__global_0_0;
		re_out__global_0_0_copy_stage6_local = re_out__global_0_0;
		im_out__global_0_0_copy_stage6_local = im_out__global_0_0;


		// pause;
		// forec:statement:pause:pause29:start
		stage6__thread.programCounter = &&pause29;
		goto *stage6__thread.nextThread -> programCounter;
		pause29:;
		// forec:statement:pause:pause29:end
		// Update the values of the used shared variables from their global copy.
		CHE_out_I__global_0_0_copy_stage6_local = CHE_out_I__global_0_0;
		CHE_out_Q__global_0_0_copy_stage6_local = CHE_out_Q__global_0_0;
		CHC_out_I__global_0_0_copy_stage6_local = CHC_out_I__global_0_0;
		CHC_out_Q__global_0_0_copy_stage6_local = CHC_out_Q__global_0_0;
		fft_re_out__global_0_0_copy_stage6_local = fft_re_out__global_0_0;
		fft_im_out__global_0_0_copy_stage6_local = fft_im_out__global_0_0;
		input_size__global_0_0_copy_stage6_local = input_size__global_0_0;
		maximum_found_stage_5_6__global_0_0_copy_stage6_local = maximum_found_stage_5_6__global_0_0;
		re_out__global_0_0_copy_stage6_local = re_out__global_0_0;
		im_out__global_0_0_copy_stage6_local = im_out__global_0_0;


		// pause;
		// forec:statement:pause:pause30:start
		stage6__thread.programCounter = &&pause30;
		goto *stage6__thread.nextThread -> programCounter;
		pause30:;
		// forec:statement:pause:pause30:end
		// Update the values of the used shared variables from their global copy.
		CHE_out_I__global_0_0_copy_stage6_local = CHE_out_I__global_0_0;
		CHE_out_Q__global_0_0_copy_stage6_local = CHE_out_Q__global_0_0;
		CHC_out_I__global_0_0_copy_stage6_local = CHC_out_I__global_0_0;
		CHC_out_Q__global_0_0_copy_stage6_local = CHC_out_Q__global_0_0;
		fft_re_out__global_0_0_copy_stage6_local = fft_re_out__global_0_0;
		fft_im_out__global_0_0_copy_stage6_local = fft_im_out__global_0_0;
		input_size__global_0_0_copy_stage6_local = input_size__global_0_0;
		maximum_found_stage_5_6__global_0_0_copy_stage6_local = maximum_found_stage_5_6__global_0_0;
		re_out__global_0_0_copy_stage6_local = re_out__global_0_0;
		im_out__global_0_0_copy_stage6_local = im_out__global_0_0;


		for (k__stage6_0_0 = 0; k__stage6_0_0 < input_size__global_0_0_copy_stage6_local.value; ++k__stage6_0_0) {
			if (downsampling_flag__stage6_0_0 == 0) {
				if (maximum_found_stage_5_6__global_0_0_copy_stage6_local.value == 1) {
					if (mk_test__stage6_0_0 == 0) {
						cnt_128__stage6_0_0 = 0;
						cnt_64__stage6_0_0 = 0;
						cnt_16__stage6_0_0 = 0;
						GI_Flag__stage6_0_0 = 0;
					} else {
						// ifElse77
						if (cnt_128__stage6_0_0 < 127) {
							cnt_128__stage6_0_0++;
							GI_Flag__stage6_0_0 = 0;
						} else {
							// ifElse76
							if ((cnt_16__stage6_0_0 < 16) && (cnt_64__stage6_0_0 == 0)) {
								GI_Flag__stage6_0_0 = 1;
								cnt_16__stage6_0_0++;
							} else {
								// ifElse75
								if (cnt_64__stage6_0_0 < 63) {
									GI_Flag__stage6_0_0 = 0;
									cnt_64__stage6_0_0++;
								} else {
									// ifElse74
									cnt_64__stage6_0_0 = 0;
									cnt_16__stage6_0_0 = 0;
								}
							}
						}
					}

					if (GI_Flag__stage6_0_0 == 0) {
						mk_test__stage6_0_0 = 1;

						{
							index_int__stage6_5_1 = inv_int__stage6_0_0 + mux_cnt__stage6_0_0;
							array_re__global_0_0.value[index_int__stage6_5_1] = re_out__global_0_0_copy_stage6_local.value;
							array_im__global_0_0.value[index_int__stage6_5_1] = im_out__global_0_0_copy_stage6_local.value;
							m_int__stage6_5_1 = 64 >> 1;
							if (inv_int__stage6_0_0 < 63) {
								while (m_int__stage6_5_1 >= 2 && inv_int__stage6_0_0 >= m_int__stage6_5_1) {
									inv_int__stage6_0_0 -= m_int__stage6_5_1;
									m_int__stage6_5_1 >>= 1;
									// forec:iteration:while_23:bound:0:5
								}
								inv_int__stage6_0_0 += m_int__stage6_5_1;
							} else {
								// ifElse78
								inv_int__stage6_0_0 = 0;
							}
						}

						if (i__stage6_0_0 < 63) {
							i__stage6_0_0++;
						} else {
							// ifElse83
							i__stage6_0_0 = 0;

							// par1(demux0__thread, demux1__thread, demux2__thread, demux3__thread);
							// Set the par(...) information.
							// forec:statement:par:par1:start
							stage6ParParent.parId = 1;
							stage6ParParent.parStatus = FOREC_PAR_ON;
							stage6ParParent.programCounter = &&par1JoinAddress_stage6ParParent;

							// Remove this thread from the linked list.
							stage6__thread.nextThread -> prevThread = stage6__thread.prevThread;
							stage6__thread.prevThread -> nextThread = stage6__thread.nextThread;
							goto stage6ParHandlerMaster0;
							par1JoinAddress_stage6ParParent:;
							// forec:statement:par:par1:end

							// par2(removeReorder0__thread, removeReorder1__thread);
							// Set the par(...) information.
							// forec:statement:par:par2:start
							stage6ParParent.parId = 2;
							stage6ParParent.parStatus = FOREC_PAR_ON;
							stage6ParParent.programCounter = &&par2JoinAddress_stage6ParParent;

							// Remove this thread from the linked list.
							stage6__thread.nextThread -> prevThread = stage6__thread.prevThread;
							stage6__thread.prevThread -> nextThread = stage6__thread.nextThread;
							goto stage6ParHandlerMaster0;
							par2JoinAddress_stage6ParParent:;
							// forec:statement:par:par2:end

							// par3(inputChe0__thread, inputChe1__thread, inputChe2__thread, inputChe3__thread);
							// Set the par(...) information.
							// forec:statement:par:par3:start
							stage6ParParent.parId = 3;
							stage6ParParent.parStatus = FOREC_PAR_ON;
							stage6ParParent.programCounter = &&par3JoinAddress_stage6ParParent;

							// Remove this thread from the linked list.
							stage6__thread.nextThread -> prevThread = stage6__thread.prevThread;
							stage6__thread.prevThread -> nextThread = stage6__thread.nextThread;
							goto stage6ParHandlerMaster0;
							par3JoinAddress_stage6ParParent:;
							// forec:statement:par:par3:end

							// par4(outputChe0__thread, outputChe1__thread, outputChe2__thread, outputChe3__thread);
							// Set the par(...) information.
							// forec:statement:par:par4:start
							stage6ParParent.parId = 4;
							stage6ParParent.parStatus = FOREC_PAR_ON;
							stage6ParParent.programCounter = &&par4JoinAddress_stage6ParParent;

							// Remove this thread from the linked list.
							stage6__thread.nextThread -> prevThread = stage6__thread.prevThread;
							stage6__thread.prevThread -> nextThread = stage6__thread.nextThread;
							goto stage6ParHandlerMaster0;
							par4JoinAddress_stage6ParParent:;
							// forec:statement:par:par4:end

							// par5(outputChc0__thread, outputChc1__thread, outputChc2__thread, outputChc3__thread);
							// Set the par(...) information.
							// forec:statement:par:par5:start
							stage6ParParent.parId = 5;
							stage6ParParent.parStatus = FOREC_PAR_ON;
							stage6ParParent.programCounter = &&par5JoinAddress_stage6ParParent;

							// Remove this thread from the linked list.
							stage6__thread.nextThread -> prevThread = stage6__thread.prevThread;
							stage6__thread.prevThread -> nextThread = stage6__thread.nextThread;
							goto stage6ParHandlerMaster0;
							par5JoinAddress_stage6ParParent:;
							// forec:statement:par:par5:end

							if (debug__global_0_0.value) {
								real_out_demux_ptr__stage6_6_2 = real_out_demux__global_0_0.value;
								imag_out_demux_ptr__stage6_6_2 = imag_out_demux__global_0_0.value;
								for (j__stage6_6_2 = 0; j__stage6_6_2 < 64; j__stage6_6_2++) {
									fprintf(fft_re_out__global_0_0_copy_stage6_local.value, "%12f\n", real_out_demux_ptr__stage6_6_2[j__stage6_6_2]);
									fprintf(fft_im_out__global_0_0_copy_stage6_local.value, "%12f\n", imag_out_demux_ptr__stage6_6_2[j__stage6_6_2]);
									// forec:iteration:for1_24:bound:64:64
								}
								if (CHE_flag__global_0_0.value == 3) {
									output_CHE_real_ptr__stage6_7_3 = output_CHE_real__global_0_0.value;
									output_CHE_imag_ptr__stage6_7_3 = output_CHE_imag__global_0_0.value;
									for (j__stage6_6_2 = 0; j__stage6_6_2 < 52; j__stage6_6_2++) {
										fprintf(CHE_out_I__global_0_0_copy_stage6_local.value, "%d \n", output_CHE_real_ptr__stage6_7_3[j__stage6_6_2]);
										fprintf(CHE_out_Q__global_0_0_copy_stage6_local.value, "%d \n", output_CHE_imag_ptr__stage6_7_3[j__stage6_6_2]);
										// forec:iteration:for1_25:bound:52:52
									}
								} else {
									// if79
								}
								if (CHE_flag__global_0_0.value >= 3) {
									output_CHC_real_ptr__stage6_7_4 = output_CHC_real__global_0_0.value;
									output_CHC_imag_ptr__stage6_7_4 = output_CHC_imag__global_0_0.value;
									for (j__stage6_6_2 = 0; j__stage6_6_2 < 52; j__stage6_6_2++) {
										fprintf(CHC_out_I__global_0_0_copy_stage6_local.value, "%d \n", (int)(output_CHC_real_ptr__stage6_7_4[j__stage6_6_2]));
										fprintf(CHC_out_Q__global_0_0_copy_stage6_local.value, "%d \n", (int)(output_CHC_imag_ptr__stage6_7_4[j__stage6_6_2]));
										// forec:iteration:for1_26:bound:52:52
									}
								} else {
									// if80
								}
							} else {
								// if81
							}
							if (CHE_flag__global_0_0.value < 5) {
								CHE_flag__global_0_0.value = CHE_flag__global_0_0.value + 1;
							} else {
								// if82
							}
						}
					} else {
						// if84
					}
				} else {
					// if85
				}

				downsampling_flag__stage6_0_0 = 1;
			} else {
				// ifElse86
				downsampling_flag__stage6_0_0 = 0;
			}

			// pause;
			// forec:statement:pause:pause31:start
			stage6__thread.programCounter = &&pause31;
			goto *stage6__thread.nextThread -> programCounter;
			pause31:;
			// forec:statement:pause:pause31:end
			// Update the values of the used shared variables from their global copy.
			CHE_out_I__global_0_0_copy_stage6_local = CHE_out_I__global_0_0;
			CHE_out_Q__global_0_0_copy_stage6_local = CHE_out_Q__global_0_0;
			CHC_out_I__global_0_0_copy_stage6_local = CHC_out_I__global_0_0;
			CHC_out_Q__global_0_0_copy_stage6_local = CHC_out_Q__global_0_0;
			fft_re_out__global_0_0_copy_stage6_local = fft_re_out__global_0_0;
			fft_im_out__global_0_0_copy_stage6_local = fft_im_out__global_0_0;
			input_size__global_0_0_copy_stage6_local = input_size__global_0_0;
			maximum_found_stage_5_6__global_0_0_copy_stage6_local = maximum_found_stage_5_6__global_0_0;
			re_out__global_0_0_copy_stage6_local = re_out__global_0_0;
			im_out__global_0_0_copy_stage6_local = im_out__global_0_0;


			// forec:scheduler:iterationEnd:for1_27:start
			// Synchronise end of iteration
			stage6ParParent.parId = -2;
			stage6ParParent.parStatus = FOREC_PAR_ON;
			stage6ParParent.programCounter = &&for1_27_endAddress;
			goto stage6ParHandlerMaster0;
			for1_27_endAddress:;
			// forec:scheduler:iterationEnd:for1_27:end
			// forec:iteration:for1_27:bound:7:7
		}

		//--------------------------------------------------------------
		// Write the defined shared variables back to their global copy.

		// forec:scheduler:threadRemove:stage6:start
		// Delete par handler
		stage6ParParent.parId = -3;
		stage6ParParent.parStatus = FOREC_PAR_ON;
		stage6ParParent.programCounter = &&stage6_endAddress;
		goto stage6ParHandlerMaster0;
		stage6_endAddress:;

		// Delete thread from the linked list and core.
		mainParCore0.activeThreads--;
		stage6__thread.nextThread -> prevThread = stage6__thread.prevThread;
		stage6__thread.prevThread -> nextThread = stage6__thread.nextThread;
		goto *stage6__thread.nextThread -> programCounter;
		// forec:scheduler:threadRemove:stage6:end
	} // stage6__thread
	// forec:thread:stage6:end


} // End of the main() function.

void computeStage0(const icomplex__global_0_0 freq_sync_correl_2STS_input__computeStage0_0_0, int data_store_real_0__computeStage0_0_0[], int data_store_imag_0__computeStage0_0_0[], icomplex__global_0_0 *correlation_1ST__computeStage0_0_0, icomplex__global_0_0 *freq_sync_correl_2STS_output__computeStage0_0_0) {
	const int oversampling_factor__computeStage0_0_0 = 2;
	int data_in_i1__computeStage0_0_0 = freq_sync_correl_2STS_input__computeStage0_0_0.re/4;
	int data_in_q1__computeStage0_0_0 = freq_sync_correl_2STS_input__computeStage0_0_0.im/4;
	int data_in_idel1__computeStage0_0_0 = data_store_real_0__computeStage0_0_0[32*oversampling_factor__computeStage0_0_0 - 1]/4;
	int data_in_qdel1__computeStage0_0_0 = data_store_imag_0__computeStage0_0_0[32*oversampling_factor__computeStage0_0_0 - 1]/4;
	int correlation_1ST_i_1__computeStage0_0_0 = data_in_i1__computeStage0_0_0*data_in_idel1__computeStage0_0_0;
	int correlation_1ST_i_2__computeStage0_0_0 = data_in_q1__computeStage0_0_0*data_in_qdel1__computeStage0_0_0;
	correlation_1ST__computeStage0_0_0->re = correlation_1ST_i_1__computeStage0_0_0 + correlation_1ST_i_2__computeStage0_0_0;
	int correlation_1ST_q_1__computeStage0_0_0 = data_in_q1__computeStage0_0_0*data_in_idel1__computeStage0_0_0;
	int correlation_1ST_q_2__computeStage0_0_0 = data_in_i1__computeStage0_0_0*data_in_qdel1__computeStage0_0_0;
	correlation_1ST__computeStage0_0_0->im = correlation_1ST_q_1__computeStage0_0_0 - correlation_1ST_q_2__computeStage0_0_0;
	freq_sync_correl_2STS_output__computeStage0_0_0->re = data_store_real_0__computeStage0_0_0[19];
	freq_sync_correl_2STS_output__computeStage0_0_0->im = data_store_imag_0__computeStage0_0_0[19];
	int i__computeStage0_0_0;
	for (i__computeStage0_0_0 = (32*oversampling_factor__computeStage0_0_0 - 1); i__computeStage0_0_0 > 0; i__computeStage0_0_0--) {
		data_store_real_0__computeStage0_0_0[i__computeStage0_0_0] = data_store_real_0__computeStage0_0_0[i__computeStage0_0_0 - 1];
		data_store_imag_0__computeStage0_0_0[i__computeStage0_0_0] = data_store_imag_0__computeStage0_0_0[i__computeStage0_0_0 - 1];
		// forec:iteration:for1_3:bound:63:63
	}
	data_store_real_0__computeStage0_0_0[0] = freq_sync_correl_2STS_input__computeStage0_0_0.re;
	data_store_imag_0__computeStage0_0_0[0] = freq_sync_correl_2STS_input__computeStage0_0_0.im;
}

void computeStage1(int *correlation_1ST_store_index__computeStage1_0_0, int *freq1_i__computeStage1_0_0, int *freq1_q__computeStage1_0_0, int *freq2_i__computeStage1_0_0, int *freq2_q__computeStage1_0_0, int correlation_1ST_store_real__computeStage1_0_0[], int correlation_1ST_store_imag__computeStage1_0_0[], int *burst_found_pulse_64d_index__computeStage1_0_0, int burst_found_pulse_64d__computeStage1_0_0[], icomplex__global_0_0 *freq_est_phase_out__computeStage1_0_0, icomplex__global_0_0 correlation_1ST__computeStage1_0_0, int *burst_found_out__computeStage1_0_0, int *burst_found_pulse_out__computeStage1_0_0, int *freq_est_norm_out__computeStage1_0_0, int *freq_est_norm_max_out__computeStage1_0_0, int *burst_found_pulse_for_FT__computeStage1_0_0) {
	int temp1_i__computeStage1_0_0 = correlation_1ST__computeStage1_0_0.re - correlation_1ST_store_real__computeStage1_0_0[* correlation_1ST_store_index__computeStage1_0_0];
	* freq1_i__computeStage1_0_0 += temp1_i__computeStage1_0_0;
	int temp1_q__computeStage1_0_0 = correlation_1ST__computeStage1_0_0.im - correlation_1ST_store_imag__computeStage1_0_0[* correlation_1ST_store_index__computeStage1_0_0];
	* freq1_q__computeStage1_0_0 += temp1_q__computeStage1_0_0;
	int temp2_i__computeStage1_0_0 = correlation_1ST_store_real__computeStage1_0_0[(* correlation_1ST_store_index__computeStage1_0_0 - FreqEstStartSlSum__global_0_0 - 1) & 255] - correlation_1ST_store_real__computeStage1_0_0[(* correlation_1ST_store_index__computeStage1_0_0 - FreqEstStopSlSum__global_0_0 - 1) & 255];
	* freq2_i__computeStage1_0_0 += temp2_i__computeStage1_0_0;
	int temp2_q__computeStage1_0_0 = correlation_1ST_store_imag__computeStage1_0_0[(* correlation_1ST_store_index__computeStage1_0_0 - FreqEstStartSlSum__global_0_0 - 1) & 255] - correlation_1ST_store_imag__computeStage1_0_0[(* correlation_1ST_store_index__computeStage1_0_0 - FreqEstStopSlSum__global_0_0 - 1) & 255];
	* freq2_q__computeStage1_0_0 += temp2_q__computeStage1_0_0;
	correlation_1ST_store_real__computeStage1_0_0[* correlation_1ST_store_index__computeStage1_0_0] = correlation_1ST__computeStage1_0_0.re;
	correlation_1ST_store_imag__computeStage1_0_0[* correlation_1ST_store_index__computeStage1_0_0] = correlation_1ST__computeStage1_0_0.im;
	* correlation_1ST_store_index__computeStage1_0_0 = ((* correlation_1ST_store_index__computeStage1_0_0 + 1) & 255);
	int freq1_i_tmp__computeStage1_0_0 = * freq1_i__computeStage1_0_0/8192;
	int freq1_q_tmp__computeStage1_0_0 = * freq1_q__computeStage1_0_0/8192;
	* freq_est_norm_out__computeStage1_0_0 = (freq1_i_tmp__computeStage1_0_0*freq1_i_tmp__computeStage1_0_0) + (freq1_q_tmp__computeStage1_0_0*freq1_q_tmp__computeStage1_0_0);
	if (* freq_est_norm_out__computeStage1_0_0 > burst_threshold__global_0_0 && * burst_found_out__computeStage1_0_0 == 0) {
		* burst_found_out__computeStage1_0_0 = 1;
		* freq_est_norm_max_out__computeStage1_0_0 = * freq_est_norm_out__computeStage1_0_0;
	} else {
		// if3
	}
	if (* burst_found_out__computeStage1_0_0 == 1) {
		if (* freq_est_norm_out__computeStage1_0_0 > * freq_est_norm_max_out__computeStage1_0_0) {
			* freq_est_norm_max_out__computeStage1_0_0 = * freq_est_norm_out__computeStage1_0_0;
			freq_est_phase_out__computeStage1_0_0->re = * freq2_i__computeStage1_0_0 >> 5;
			freq_est_phase_out__computeStage1_0_0->im = * freq2_q__computeStage1_0_0 >> 5;
			* burst_found_pulse_out__computeStage1_0_0 = 0;
		} else {
			// ifElse4
			* burst_found_pulse_out__computeStage1_0_0 = 1;
		}
	} else {
		// ifElse5
		* burst_found_pulse_out__computeStage1_0_0 = 0;
	}
	burst_found_pulse_64d__computeStage1_0_0[* burst_found_pulse_64d_index__computeStage1_0_0] = * burst_found_pulse_out__computeStage1_0_0;
	* burst_found_pulse_64d_index__computeStage1_0_0 = (* burst_found_pulse_64d_index__computeStage1_0_0 + 1) & 63;
	* burst_found_pulse_for_FT__computeStage1_0_0 = burst_found_pulse_64d__computeStage1_0_0[* burst_found_pulse_64d_index__computeStage1_0_0];
}

void computeStage2(int *act_angle__computeStage2_0_0, icomplex__global_0_0 freq_est_phase_out__computeStage2_0_0, int burst_found_pulse_out__computeStage2_0_0, int *angle__computeStage2_0_0) {
	const int Latency_on__computeStage2_0_0 = 0;
	unsigned int ExactAngle__computeStage2_0_0 = UINTMAX__global_0_0 - 1048575;
	unsigned int ExactInternal__computeStage2_0_0 = 4294963200u;
	unsigned int LSB_Ang__computeStage2_0_0 = 1048576;
	unsigned int LSB_Int__computeStage2_0_0 = 4096;
	unsigned int LSB_OutAng__computeStage2_0_0 = 2097152;
	long xin__computeStage2_0_0 = freq_est_phase_out__computeStage2_0_0.re;
	long yin__computeStage2_0_0 = freq_est_phase_out__computeStage2_0_0.im;
	xin__computeStage2_0_0 += (xin__computeStage2_0_0 == -131072);
	yin__computeStage2_0_0 += (yin__computeStage2_0_0 == -131072);
	long x_i_temp0__computeStage2_0_0 = xin__computeStage2_0_0*4096;
	long x_i_temp1__computeStage2_0_0 = yin__computeStage2_0_0*4096;
	if (x_i_temp0__computeStage2_0_0 < 0) {
		x_i_temp0__computeStage2_0_0 = -x_i_temp0__computeStage2_0_0;
	} else {
		// if6
	}
	if (x_i_temp1__computeStage2_0_0 < 0) {
		x_i_temp1__computeStage2_0_0 = -x_i_temp1__computeStage2_0_0;
	} else {
		// if7
	}
	signed int x_i__computeStage2_0_0 = x_i_temp0__computeStage2_0_0 + x_i_temp1__computeStage2_0_0;
	long y_i_temp0__computeStage2_0_0 = yin__computeStage2_0_0*4096;
	long y_i_temp1__computeStage2_0_0 = xin__computeStage2_0_0*4096;
	if (y_i_temp0__computeStage2_0_0 < 0) {
		y_i_temp0__computeStage2_0_0 = -y_i_temp0__computeStage2_0_0;
	} else {
		// if8
	}
	if (y_i_temp1__computeStage2_0_0 < 0) {
		y_i_temp1__computeStage2_0_0 = -y_i_temp1__computeStage2_0_0;
	} else {
		// if9
	}
	signed int y_i__computeStage2_0_0 = y_i_temp0__computeStage2_0_0 - y_i_temp1__computeStage2_0_0;
	signed int z_i__computeStage2_0_0 = 536870912;
	signed int i__computeStage2_0_0;
	signed int x_i_1__computeStage2_0_0, y_i_1__computeStage2_0_0, z_i_1__computeStage2_0_0;
	for (i__computeStage2_0_0 = 1; i__computeStage2_0_0 < cordic_steps_c__global_0_0; i__computeStage2_0_0++) {
		if (y_i__computeStage2_0_0 > 0) {
			x_i_1__computeStage2_0_0 = x_i__computeStage2_0_0 + (((y_i__computeStage2_0_0/arctan_divisor_y0__global_0_0[i__computeStage2_0_0 - 1]) & ExactInternal__computeStage2_0_0) + ((y_i__computeStage2_0_0/arctan_divisor_y1__global_0_0[i__computeStage2_0_0 - 1]) & LSB_Int__computeStage2_0_0));
			y_i_1__computeStage2_0_0 = y_i__computeStage2_0_0 - (((x_i__computeStage2_0_0/arctan_divisor_x0__global_0_0[i__computeStage2_0_0 - 1]) & ExactInternal__computeStage2_0_0) + ((x_i__computeStage2_0_0/arctan_divisor_x1__global_0_0[i__computeStage2_0_0 - 1]) & LSB_Int__computeStage2_0_0));
			z_i_1__computeStage2_0_0 = z_i__computeStage2_0_0 + (((arctanTable__global_0_0[i__computeStage2_0_0]/4) & ExactAngle__computeStage2_0_0) + ((arctanTable__global_0_0[i__computeStage2_0_0]/2) & LSB_Ang__computeStage2_0_0));
		} else {
			// ifElse10
			x_i_1__computeStage2_0_0 = x_i__computeStage2_0_0 - (((y_i__computeStage2_0_0/arctan_divisor_y0__global_0_0[i__computeStage2_0_0 - 1]) & ExactInternal__computeStage2_0_0) + ((y_i__computeStage2_0_0/arctan_divisor_y1__global_0_0[i__computeStage2_0_0 - 1]) & LSB_Int__computeStage2_0_0));
			y_i_1__computeStage2_0_0 = y_i__computeStage2_0_0 + (((x_i__computeStage2_0_0/arctan_divisor_x0__global_0_0[i__computeStage2_0_0 - 1]) & ExactInternal__computeStage2_0_0) + ((x_i__computeStage2_0_0/arctan_divisor_x1__global_0_0[i__computeStage2_0_0 - 1]) & LSB_Int__computeStage2_0_0));
			z_i_1__computeStage2_0_0 = z_i__computeStage2_0_0 - (((arctanTable__global_0_0[i__computeStage2_0_0]/4) & ExactAngle__computeStage2_0_0) + ((arctanTable__global_0_0[i__computeStage2_0_0]/2) & LSB_Ang__computeStage2_0_0));
		}
		x_i__computeStage2_0_0 = x_i_1__computeStage2_0_0 & ExactInternal__computeStage2_0_0;
		y_i__computeStage2_0_0 = y_i_1__computeStage2_0_0 & ExactInternal__computeStage2_0_0;
		z_i__computeStage2_0_0 = z_i_1__computeStage2_0_0 & ExactAngle__computeStage2_0_0;
		if (i__computeStage2_0_0/2 != i__computeStage2_0_0*((float)0.5)) {
			y_i__computeStage2_0_0 = y_i__computeStage2_0_0 << 1;
		} else {
			// if11
		}
		// forec:iteration:for1_8:bound:10:10
	}
	long angle_temp__computeStage2_0_0 = (z_i__computeStage2_0_0 + ((z_i__computeStage2_0_0*2) & LSB_OutAng__computeStage2_0_0))/2097152;
	if (xin__computeStage2_0_0 >= 0 && yin__computeStage2_0_0 < 0) {
		angle_temp__computeStage2_0_0 = -(angle_temp__computeStage2_0_0);
	} else {
		// ifElse15
		if (xin__computeStage2_0_0 < 0 && yin__computeStage2_0_0 >= 0) {
			angle_temp__computeStage2_0_0 = (INTMAX__global_0_0/2097152) + 1 - angle_temp__computeStage2_0_0;
		} else {
			// ifElse14
			if (xin__computeStage2_0_0 < 0 && yin__computeStage2_0_0 < 0) {
				angle_temp__computeStage2_0_0 = angle_temp__computeStage2_0_0 - (INTMAX__global_0_0/2097152) - 1;
			} else {
				// ifElse13
				if (xin__computeStage2_0_0 == 0 && yin__computeStage2_0_0 == 0) {
					angle_temp__computeStage2_0_0 = -1;
				} else {
					// if12
				}
			}
		}
	}
	if (angle_temp__computeStage2_0_0 == 1024) {
		angle_temp__computeStage2_0_0 = -angle_temp__computeStage2_0_0;
	} else {
		// if16
	}
	int alpha_out_latency__computeStage2_0_0[5];
	int alpha_out__computeStage2_0_0;
	if (Latency_on__computeStage2_0_0 == 0) {
		alpha_out__computeStage2_0_0 = (int)(angle_temp__computeStage2_0_0);
	} else {
		// ifElse17
		alpha_out__computeStage2_0_0 = (int)(alpha_out_latency__computeStage2_0_0[0]);
	}
	int rad_tmp__computeStage2_0_0 = -alpha_out__computeStage2_0_0;
	if (burst_found_pulse_out__computeStage2_0_0 == 0) {
		* act_angle__computeStage2_0_0 = 0;
	} else {
		// if18
	}
	* act_angle__computeStage2_0_0 += rad_tmp__computeStage2_0_0;
	if (* act_angle__computeStage2_0_0 < -65536) {
		* act_angle__computeStage2_0_0 = 131072 + * act_angle__computeStage2_0_0;
	} else {
		// ifElse20
		if (* act_angle__computeStage2_0_0 > 65535) {
			* act_angle__computeStage2_0_0 = -131072 + * act_angle__computeStage2_0_0;
		} else {
			// if19
		}
	}
	* angle__computeStage2_0_0 = * act_angle__computeStage2_0_0/64;
	for (i__computeStage2_0_0 = 1; i__computeStage2_0_0 < (cordic_steps_c__global_0_0/inter_reg_steps_c__global_0_0) + 2; i__computeStage2_0_0++) {
		alpha_out_latency__computeStage2_0_0[i__computeStage2_0_0 - 1] = alpha_out_latency__computeStage2_0_0[i__computeStage2_0_0];
		// forec:iteration:for1_9:bound:4:4
	}
	if (cordic_steps_c__global_0_0%inter_reg_steps_c__global_0_0 == 0) {
		alpha_out_latency__computeStage2_0_0[3] = * angle__computeStage2_0_0;
	} else {
		// ifElse21
		alpha_out_latency__computeStage2_0_0[4] = * angle__computeStage2_0_0;
	}
}

void computeStage3(icomplex__global_0_0 *cordic_out__computeStage3_0_0, int angle__computeStage3_0_0, icomplex__global_0_0 freq_sync_correl_2STS_output__computeStage3_0_0) {
	const int Latency_on__computeStage3_0_0 = 0;
	long x_in_reg__computeStage3_0_0 = (long)(freq_sync_correl_2STS_output__computeStage3_0_0.re*1);
	long y_in_reg__computeStage3_0_0 = (long)(freq_sync_correl_2STS_output__computeStage3_0_0.im*1);
	long angle_in_reg__computeStage3_0_0 = (long)angle__computeStage3_0_0;
	int msb_reg__computeStage3_0_0 = (int)(angle_in_reg__computeStage3_0_0/256);
	msb_reg__computeStage3_0_0 &= 7;
	long z_reg__computeStage3_0_0;
	if (((angle_in_reg__computeStage3_0_0/256) & 1) == 1) {
		z_reg__computeStage3_0_0 = -1;
	} else {
		// ifElse22
		z_reg__computeStage3_0_0 = 0;
	}
	z_reg__computeStage3_0_0 = z_reg__computeStage3_0_0*512 | (angle_in_reg__computeStage3_0_0 & ((long)(512) - 1));
	z_reg__computeStage3_0_0 = z_reg__computeStage3_0_0*32;
	long x_temp__computeStage3_0_0 = x_in_reg__computeStage3_0_0*4;
	long y_temp__computeStage3_0_0 = y_in_reg__computeStage3_0_0*4;
	long x_reg__computeStage3_0_0, y_reg__computeStage3_0_0;
	if (msb_reg__computeStage3_0_0 == 0 || msb_reg__computeStage3_0_0 == 7) {
		x_reg__computeStage3_0_0 = x_temp__computeStage3_0_0;
		y_reg__computeStage3_0_0 = y_temp__computeStage3_0_0;
	} else {
		// ifElse25
		if (msb_reg__computeStage3_0_0 == 5 || msb_reg__computeStage3_0_0 == 6) {
			x_reg__computeStage3_0_0 = y_temp__computeStage3_0_0;
			y_reg__computeStage3_0_0 = -x_temp__computeStage3_0_0;
		} else {
			// ifElse24
			if (msb_reg__computeStage3_0_0 == 3 || msb_reg__computeStage3_0_0 == 4) {
				x_reg__computeStage3_0_0 = -x_temp__computeStage3_0_0;
				y_reg__computeStage3_0_0 = -y_temp__computeStage3_0_0;
			} else {
				// ifElse23
				x_reg__computeStage3_0_0 = -y_temp__computeStage3_0_0;
				y_reg__computeStage3_0_0 = x_temp__computeStage3_0_0;
			}
		}
	}
	int i__computeStage3_0_0;
	for (i__computeStage3_0_0 = 1; i__computeStage3_0_0 < Stages__global_0_0; i__computeStage3_0_0++) {
		if (z_reg__computeStage3_0_0 < 0) {
			x_temp__computeStage3_0_0 = x_reg__computeStage3_0_0 + (y_reg__computeStage3_0_0/cordic_turn_divisor0__global_0_0[i__computeStage3_0_0]) + ((y_reg__computeStage3_0_0/cordic_turn_divisor0__global_0_0[i__computeStage3_0_0 - 1]) & 1);
			y_temp__computeStage3_0_0 = y_reg__computeStage3_0_0 - (x_reg__computeStage3_0_0/cordic_turn_divisor0__global_0_0[i__computeStage3_0_0]) - ((x_reg__computeStage3_0_0/cordic_turn_divisor0__global_0_0[i__computeStage3_0_0 - 1]) & 1);
			z_reg__computeStage3_0_0 = z_reg__computeStage3_0_0 + (arc_tan_array_c__global_0_0[i__computeStage3_0_0 - 1]/262144) + ((arc_tan_array_c__global_0_0[i__computeStage3_0_0 - 1]/131072) & 1);
		} else {
			// ifElse26
			x_temp__computeStage3_0_0 = x_reg__computeStage3_0_0 - (y_reg__computeStage3_0_0/cordic_turn_divisor0__global_0_0[i__computeStage3_0_0]) - ((y_reg__computeStage3_0_0/cordic_turn_divisor0__global_0_0[i__computeStage3_0_0 - 1]) & 1);
			y_temp__computeStage3_0_0 = y_reg__computeStage3_0_0 + (x_reg__computeStage3_0_0/cordic_turn_divisor0__global_0_0[i__computeStage3_0_0]) + ((x_reg__computeStage3_0_0/cordic_turn_divisor0__global_0_0[i__computeStage3_0_0 - 1]) & 1);
			z_reg__computeStage3_0_0 = z_reg__computeStage3_0_0 - (arc_tan_array_c__global_0_0[i__computeStage3_0_0 - 1]/262144) - ((arc_tan_array_c__global_0_0[i__computeStage3_0_0 - 1]/131072) & 1);
		}
		x_reg__computeStage3_0_0 = x_temp__computeStage3_0_0;
		y_reg__computeStage3_0_0 = y_temp__computeStage3_0_0;
		// forec:iteration:for1_11:bound:12:12
	}
	long res_x_latency__computeStage3_0_0[6];
	long res_y_latency__computeStage3_0_0[6];
	float res_x__computeStage3_0_0;
	float res_y__computeStage3_0_0;
	if (Latency_on__computeStage3_0_0 == 0) {
		res_x__computeStage3_0_0 = (float)(x_reg__computeStage3_0_0/4)/(float)1;
		res_y__computeStage3_0_0 = (float)(y_reg__computeStage3_0_0/4)/(float)1;
	} else {
		// ifElse27
		res_x__computeStage3_0_0 = (float)(res_x_latency__computeStage3_0_0[0]/4)/(float)1;
		res_y__computeStage3_0_0 = (float)(res_y_latency__computeStage3_0_0[0]/4)/(float)1;
	}
	int res_out_x__computeStage3_0_0 = (int)(res_x__computeStage3_0_0);
	int res_out_y__computeStage3_0_0 = (int)(res_y__computeStage3_0_0);
	if (FS_on__global_0_0 == 1) {
		cordic_out__computeStage3_0_0->re = (res_out_x__computeStage3_0_0*fs_out_scale__global_0_0)/16;
		cordic_out__computeStage3_0_0->im = (res_out_y__computeStage3_0_0*fs_out_scale__global_0_0)/16;
	} else {
		// ifElse28
		cordic_out__computeStage3_0_0->re = freq_sync_correl_2STS_output__computeStage3_0_0.re;
		cordic_out__computeStage3_0_0->im = freq_sync_correl_2STS_output__computeStage3_0_0.im;
	}
	for (i__computeStage3_0_0 = 1; i__computeStage3_0_0 < (Stages__global_0_0/IntRegStages__global_0_0) + 2; i__computeStage3_0_0++) {
		res_x_latency__computeStage3_0_0[i__computeStage3_0_0 - 1] = res_x_latency__computeStage3_0_0[i__computeStage3_0_0];
		res_y_latency__computeStage3_0_0[i__computeStage3_0_0 - 1] = res_y_latency__computeStage3_0_0[i__computeStage3_0_0];
		// forec:iteration:for1_12:bound:5:5
	}
	if (Stages__global_0_0%IntRegStages__global_0_0 == 0) {
		res_x_latency__computeStage3_0_0[4] = x_reg__computeStage3_0_0;
		res_y_latency__computeStage3_0_0[4] = y_reg__computeStage3_0_0;
	} else {
		// ifElse29
		res_x_latency__computeStage3_0_0[5] = x_reg__computeStage3_0_0;
		res_y_latency__computeStage3_0_0[5] = y_reg__computeStage3_0_0;
	}
}

void computeStage4(int *downsampling_flag__computeStage4_0_0, int *maximum_found_main__computeStage4_0_0, int *maximum_found__computeStage4_0_0, int data_store_real__computeStage4_0_0[], int data_store_imag__computeStage4_0_0[], int *data_store_index__computeStage4_0_0, int data_quant_real__computeStage4_0_0[], int data_quant_imag__computeStage4_0_0[], int *data_quant_index__computeStage4_0_0, int *FTS_count__computeStage4_0_0, int *maximum__computeStage4_0_0, int *maximum_new__computeStage4_0_0, int *fine_time_est_int__computeStage4_0_0, int *fine_time_est_new__computeStage4_0_0, int *difference_in_fine_time_est__computeStage4_0_0, icomplex__global_0_0 cordic_out__computeStage4_0_0, icomplex__global_0_0 *data_out_FT__computeStage4_0_0, int burst_found_pulse_for_FT__computeStage4_0_0) {
	if (* downsampling_flag__computeStage4_0_0 == 0) {
		if (* maximum_found__computeStage4_0_0 == 1) {
			data_out_FT__computeStage4_0_0->re = (int)(data_store_real__computeStage4_0_0[* data_store_index__computeStage4_0_0]);
			data_out_FT__computeStage4_0_0->im = (int)(data_store_imag__computeStage4_0_0[* data_store_index__computeStage4_0_0]);
			* maximum_found_main__computeStage4_0_0 = 1;
		} else {
			// ifElse30
			data_out_FT__computeStage4_0_0->re = 0;
			data_out_FT__computeStage4_0_0->im = 0;
			* maximum_found_main__computeStage4_0_0 = 0;
		}
		data_store_real__computeStage4_0_0[* data_store_index__computeStage4_0_0] = cordic_out__computeStage4_0_0.re;
		data_store_imag__computeStage4_0_0[* data_store_index__computeStage4_0_0] = cordic_out__computeStage4_0_0.im;
		* data_store_index__computeStage4_0_0 = (* data_store_index__computeStage4_0_0 + 1)%37;
		int data_in_sign_re__computeStage4_1_0;
		if (cordic_out__computeStage4_0_0.re > 0) {
			data_in_sign_re__computeStage4_1_0 = 1;
		} else {
			// ifElse32
			if (cordic_out__computeStage4_0_0.re < 0) {
				data_in_sign_re__computeStage4_1_0 = -1;
			} else {
				// ifElse31
				data_in_sign_re__computeStage4_1_0 = 0;
			}
		}
		int data_in_sign_im__computeStage4_1_0;
		if (cordic_out__computeStage4_0_0.im > 0) {
			data_in_sign_im__computeStage4_1_0 = 1;
		} else {
			// ifElse34
			if (cordic_out__computeStage4_0_0.im < 0) {
				data_in_sign_im__computeStage4_1_0 = -1;
			} else {
				// ifElse33
				data_in_sign_im__computeStage4_1_0 = 0;
			}
		}
		data_quant_real__computeStage4_0_0[* data_quant_index__computeStage4_0_0] = data_in_sign_re__computeStage4_1_0;
		data_quant_imag__computeStage4_0_0[* data_quant_index__computeStage4_0_0] = data_in_sign_im__computeStage4_1_0;
		* data_quant_index__computeStage4_0_0 = (* data_quant_index__computeStage4_0_0 + 1) & 63;
		int j__computeStage4_1_0;
		int time_corr_long_re__computeStage4_1_0 = 0;
		int time_corr_long_im__computeStage4_1_0 = 0;
		for (j__computeStage4_1_0 = 0; j__computeStage4_1_0 < 64; j__computeStage4_1_0++) {
			int time_corr_long_re_1__computeStage4_2_3 = (int)(data_quant_real__computeStage4_0_0[(* data_quant_index__computeStage4_0_0 + j__computeStage4_1_0) & 63]*data_quant_trs_real__global_0_0[j__computeStage4_1_0]);
			int time_corr_long_re_2__computeStage4_2_3 = (int)(data_quant_imag__computeStage4_0_0[(* data_quant_index__computeStage4_0_0 + j__computeStage4_1_0) & 63]*data_quant_trs_imag__global_0_0[j__computeStage4_1_0]);
			time_corr_long_re__computeStage4_1_0 += time_corr_long_re_1__computeStage4_2_3 + time_corr_long_re_2__computeStage4_2_3;
			int time_corr_long_im_1__computeStage4_2_3 = (int)(data_quant_imag__computeStage4_0_0[(* data_quant_index__computeStage4_0_0 + j__computeStage4_1_0) & 63]*data_quant_trs_real__global_0_0[j__computeStage4_1_0]);
			int time_corr_long_im_2__computeStage4_2_3 = (int)(data_quant_real__computeStage4_0_0[(* data_quant_index__computeStage4_0_0 + j__computeStage4_1_0) & 63]*data_quant_trs_imag__global_0_0[j__computeStage4_1_0]);
			time_corr_long_im__computeStage4_1_0 += time_corr_long_im_1__computeStage4_2_3 - time_corr_long_im_2__computeStage4_2_3;
			// forec:iteration:for1_15:bound:64:64
		}
		int time_corr_long_re_temp__computeStage4_1_0 = time_corr_long_re__computeStage4_1_0;
		if (time_corr_long_re_temp__computeStage4_1_0 < 0) {
			time_corr_long_re_temp__computeStage4_1_0 = -time_corr_long_re_temp__computeStage4_1_0;
		} else {
			// if35
		}
		time_corr_long_re_temp__computeStage4_1_0 = (time_corr_long_re_temp__computeStage4_1_0 >> 2);
		int time_corr_long_im_temp__computeStage4_1_0 = time_corr_long_im__computeStage4_1_0;
		if (time_corr_long_im_temp__computeStage4_1_0 < 0) {
			time_corr_long_im_temp__computeStage4_1_0 = -time_corr_long_im_temp__computeStage4_1_0;
		} else {
			// if36
		}
		time_corr_long_im_temp__computeStage4_1_0 = time_corr_long_im_temp__computeStage4_1_0 >> 2;
		int time_corr_long_norm__computeStage4_1_0 = time_corr_long_re_temp__computeStage4_1_0*time_corr_long_re_temp__computeStage4_1_0 + time_corr_long_im_temp__computeStage4_1_0*time_corr_long_im_temp__computeStage4_1_0;
		if (burst_found_pulse_for_FT__computeStage4_0_0 == 0) {
			* FTS_count__computeStage4_0_0 = 0;
			* maximum__computeStage4_0_0 = time_corr_long_thresh__global_0_0;
			* fine_time_est_int__computeStage4_0_0 = 0;
			* maximum_found__computeStage4_0_0 = 0;
		} else {
			// ifElse40
			if (* FTS_count__computeStage4_0_0 < Searchwin_length__global_0_0) {
				if (time_corr_long_norm__computeStage4_1_0 >= * maximum__computeStage4_0_0) {
					* maximum_new__computeStage4_0_0 = time_corr_long_norm__computeStage4_1_0;
					* fine_time_est_new__computeStage4_0_0 = * FTS_count__computeStage4_0_0;
					* difference_in_fine_time_est__computeStage4_0_0 = * fine_time_est_new__computeStage4_0_0 - * fine_time_est_int__computeStage4_0_0;
					if ((* difference_in_fine_time_est__computeStage4_0_0 < 60 || * difference_in_fine_time_est__computeStage4_0_0 > 68) || * maximum_found__computeStage4_0_0 == 0) {
						* fine_time_est_int__computeStage4_0_0 = * fine_time_est_new__computeStage4_0_0;
						* maximum_found__computeStage4_0_0 = 1;
					} else {
						// if37
					}
				} else {
					// if38
				}
				* FTS_count__computeStage4_0_0 = * FTS_count__computeStage4_0_0 + 1;
			} else {
				// if39
			}
		}
		* downsampling_flag__computeStage4_0_0 = 1;
	} else {
		// ifElse41
		* downsampling_flag__computeStage4_0_0 = 0;
	}
}

void fft64Stage5(const int s5__fft64Stage5_0_0, const int fifo_len_div2_5__fft64Stage5_0_0, const float fifo_stage5_i_reg__fft64Stage5_0_0, const float fifo_stage5_q_reg__fft64Stage5_0_0, float *bf2_n_stage5_i__fft64Stage5_0_0, float *bf2_n_stage5_q__fft64Stage5_0_0, int *nsample_5__fft64Stage5_0_0, float *fifo_i_tmp_5__fft64Stage5_0_0, float *fifo_q_tmp_5__fft64Stage5_0_0, float *bf2_fifo_stage5_i__fft64Stage5_0_0, float *bf2_fifo_stage5_q__fft64Stage5_0_0, float fifo_i_array_5__fft64Stage5_0_0[], float fifo_q_array_5__fft64Stage5_0_0[], icomplex__global_0_0 data_out_FT__fft64Stage5_0_0) {
	float bf2_ndiv2_stage5_i__fft64Stage5_0_0;
	float bf2_ndiv2_stage5_q__fft64Stage5_0_0;
	float data_out_FT_re__fft64Stage5_0_0 = (float)data_out_FT__fft64Stage5_0_0.re;
	float data_out_FT_im__fft64Stage5_0_0 = (float)data_out_FT__fft64Stage5_0_0.im;
	if (s5__fft64Stage5_0_0 == 1) {
		* bf2_n_stage5_i__fft64Stage5_0_0 = fifo_stage5_i_reg__fft64Stage5_0_0 + data_out_FT_re__fft64Stage5_0_0;
		* bf2_n_stage5_q__fft64Stage5_0_0 = fifo_stage5_q_reg__fft64Stage5_0_0 + data_out_FT_im__fft64Stage5_0_0;
		bf2_ndiv2_stage5_i__fft64Stage5_0_0 = fifo_stage5_i_reg__fft64Stage5_0_0 - data_out_FT_re__fft64Stage5_0_0;
		bf2_ndiv2_stage5_q__fft64Stage5_0_0 = fifo_stage5_q_reg__fft64Stage5_0_0 - data_out_FT_im__fft64Stage5_0_0;
	} else {
		// ifElse54
		bf2_ndiv2_stage5_i__fft64Stage5_0_0 = data_out_FT_re__fft64Stage5_0_0;
		bf2_ndiv2_stage5_q__fft64Stage5_0_0 = data_out_FT_im__fft64Stage5_0_0;
		* bf2_n_stage5_i__fft64Stage5_0_0 = fifo_stage5_i_reg__fft64Stage5_0_0;
		* bf2_n_stage5_q__fft64Stage5_0_0 = fifo_stage5_q_reg__fft64Stage5_0_0;
	}

	{
		* bf2_fifo_stage5_i__fft64Stage5_0_0 = * fifo_i_tmp_5__fft64Stage5_0_0;
		* bf2_fifo_stage5_q__fft64Stage5_0_0 = * fifo_q_tmp_5__fft64Stage5_0_0;
		int nsample_r__fft64Stage5_1_1;
		if (* nsample_5__fft64Stage5_0_0 < 1) {
			nsample_r__fft64Stage5_1_1 = 1;
		} else {
			// ifElse56
			if (* nsample_5__fft64Stage5_0_0 > fifo_len_div2_5__fft64Stage5_0_0 - 2) {
				nsample_r__fft64Stage5_1_1 = 0;
			} else {
				// ifElse55
				nsample_r__fft64Stage5_1_1 = * nsample_5__fft64Stage5_0_0 + 1;
			}
		}
		* fifo_i_tmp_5__fft64Stage5_0_0 = fifo_i_array_5__fft64Stage5_0_0[nsample_r__fft64Stage5_1_1];
		* fifo_q_tmp_5__fft64Stage5_0_0 = fifo_q_array_5__fft64Stage5_0_0[nsample_r__fft64Stage5_1_1];
		fifo_i_array_5__fft64Stage5_0_0[* nsample_5__fft64Stage5_0_0] = bf2_ndiv2_stage5_i__fft64Stage5_0_0;
		fifo_q_array_5__fft64Stage5_0_0[* nsample_5__fft64Stage5_0_0] = bf2_ndiv2_stage5_q__fft64Stage5_0_0;
		if (* nsample_5__fft64Stage5_0_0 < fifo_len_div2_5__fft64Stage5_0_0 - 1) {
			* nsample_5__fft64Stage5_0_0 = * nsample_5__fft64Stage5_0_0 + 1;
		} else {
			// ifElse57
			* nsample_5__fft64Stage5_0_0 = 0;
		}
	}
}

void fft64Stage4(const int s4__fft64Stage4_0_0, const int s5__fft64Stage4_0_0, const int fifo_len_div2_4__fft64Stage4_0_0, const float bf2_n_stage5_i__fft64Stage4_0_0, const float bf2_n_stage5_q__fft64Stage4_0_0, const float fifo_stage4_i_reg__fft64Stage4_0_0, const float fifo_stage4_q_reg__fft64Stage4_0_0, float *bf2_n_stage4_i__fft64Stage4_0_0, float *bf2_n_stage4_q__fft64Stage4_0_0, float *fifo_i_tmp_4__fft64Stage4_0_0, float *fifo_q_tmp_4__fft64Stage4_0_0, float *bf2_fifo_stage4_i__fft64Stage4_0_0, float *bf2_fifo_stage4_q__fft64Stage4_0_0, int *nsample_4__fft64Stage4_0_0, float fifo_i_array_4__fft64Stage4_0_0[], float fifo_q_array_4__fft64Stage4_0_0[]) {
	float bf2_ndiv2_stage4_i__fft64Stage4_0_0;
	float bf2_ndiv2_stage4_q__fft64Stage4_0_0;
	if (s4__fft64Stage4_0_0 == 0) {
		bf2_ndiv2_stage4_i__fft64Stage4_0_0 = bf2_n_stage5_i__fft64Stage4_0_0;
		bf2_ndiv2_stage4_q__fft64Stage4_0_0 = bf2_n_stage5_q__fft64Stage4_0_0;
		* bf2_n_stage4_i__fft64Stage4_0_0 = fifo_stage4_i_reg__fft64Stage4_0_0;
		* bf2_n_stage4_q__fft64Stage4_0_0 = fifo_stage4_q_reg__fft64Stage4_0_0;
	} else {
		// ifElse59
		float tmp2_real__fft64Stage4_1_0, tmp2_imag__fft64Stage4_1_0;
		if (s5__fft64Stage4_0_0 == 0) {
			tmp2_real__fft64Stage4_1_0 = bf2_n_stage5_q__fft64Stage4_0_0;
			tmp2_imag__fft64Stage4_1_0 = -bf2_n_stage5_i__fft64Stage4_0_0;
		} else {
			// ifElse58
			tmp2_real__fft64Stage4_1_0 = bf2_n_stage5_i__fft64Stage4_0_0;
			tmp2_imag__fft64Stage4_1_0 = bf2_n_stage5_q__fft64Stage4_0_0;
		}
		* bf2_n_stage4_i__fft64Stage4_0_0 = fifo_stage4_i_reg__fft64Stage4_0_0 + tmp2_real__fft64Stage4_1_0;
		* bf2_n_stage4_q__fft64Stage4_0_0 = fifo_stage4_q_reg__fft64Stage4_0_0 + tmp2_imag__fft64Stage4_1_0;
		bf2_ndiv2_stage4_i__fft64Stage4_0_0 = fifo_stage4_i_reg__fft64Stage4_0_0 - tmp2_real__fft64Stage4_1_0;
		bf2_ndiv2_stage4_q__fft64Stage4_0_0 = fifo_stage4_q_reg__fft64Stage4_0_0 - tmp2_imag__fft64Stage4_1_0;
	}

	{
		* bf2_fifo_stage4_i__fft64Stage4_0_0 = * fifo_i_tmp_4__fft64Stage4_0_0;
		* bf2_fifo_stage4_q__fft64Stage4_0_0 = * fifo_q_tmp_4__fft64Stage4_0_0;
		int nsample_r__fft64Stage4_1_1;
		if (* nsample_4__fft64Stage4_0_0 < 1) {
			nsample_r__fft64Stage4_1_1 = 1;
		} else {
			// ifElse61
			if (* nsample_4__fft64Stage4_0_0 > fifo_len_div2_4__fft64Stage4_0_0 - 2) {
				nsample_r__fft64Stage4_1_1 = 0;
			} else {
				// ifElse60
				nsample_r__fft64Stage4_1_1 = * nsample_4__fft64Stage4_0_0 + 1;
			}
		}
		* fifo_i_tmp_4__fft64Stage4_0_0 = fifo_i_array_4__fft64Stage4_0_0[nsample_r__fft64Stage4_1_1];
		* fifo_q_tmp_4__fft64Stage4_0_0 = fifo_q_array_4__fft64Stage4_0_0[nsample_r__fft64Stage4_1_1];
		fifo_i_array_4__fft64Stage4_0_0[* nsample_4__fft64Stage4_0_0] = bf2_ndiv2_stage4_i__fft64Stage4_0_0;
		fifo_q_array_4__fft64Stage4_0_0[* nsample_4__fft64Stage4_0_0] = bf2_ndiv2_stage4_q__fft64Stage4_0_0;
		if (* nsample_4__fft64Stage4_0_0 < fifo_len_div2_4__fft64Stage4_0_0 - 1) {
			* nsample_4__fft64Stage4_0_0 = * nsample_4__fft64Stage4_0_0 + 1;
		} else {
			// ifElse62
			* nsample_4__fft64Stage4_0_0 = 0;
		}
	}
}

void fft64Stage3(const int s3__fft64Stage3_0_0, const int fifo_len_div2_3__fft64Stage3_0_0, const float fifo_stage3_i_reg__fft64Stage3_0_0, const float fifo_stage3_q_reg__fft64Stage3_0_0, const float mult_stage43_i__fft64Stage3_0_0, const float mult_stage43_q__fft64Stage3_0_0, float *bf2_n_stage3_i__fft64Stage3_0_0, float *bf2_n_stage3_q__fft64Stage3_0_0, float *fifo_i_tmp_3__fft64Stage3_0_0, float *fifo_q_tmp_3__fft64Stage3_0_0, float *bf2_fifo_stage3_i__fft64Stage3_0_0, float *bf2_fifo_stage3_q__fft64Stage3_0_0, int *nsample_3__fft64Stage3_0_0, float fifo_i_array_3__fft64Stage3_0_0[], float fifo_q_array_3__fft64Stage3_0_0[]) {
	float bf2_ndiv2_stage3_i__fft64Stage3_0_0;
	float bf2_ndiv2_stage3_q__fft64Stage3_0_0;
	if (s3__fft64Stage3_0_0 == 1) {
		* bf2_n_stage3_i__fft64Stage3_0_0 = fifo_stage3_i_reg__fft64Stage3_0_0 + mult_stage43_i__fft64Stage3_0_0;
		* bf2_n_stage3_q__fft64Stage3_0_0 = fifo_stage3_q_reg__fft64Stage3_0_0 + mult_stage43_q__fft64Stage3_0_0;
		bf2_ndiv2_stage3_i__fft64Stage3_0_0 = fifo_stage3_i_reg__fft64Stage3_0_0 - mult_stage43_i__fft64Stage3_0_0;
		bf2_ndiv2_stage3_q__fft64Stage3_0_0 = fifo_stage3_q_reg__fft64Stage3_0_0 - mult_stage43_q__fft64Stage3_0_0;
	} else {
		// ifElse63
		bf2_ndiv2_stage3_i__fft64Stage3_0_0 = mult_stage43_i__fft64Stage3_0_0;
		bf2_ndiv2_stage3_q__fft64Stage3_0_0 = mult_stage43_q__fft64Stage3_0_0;
		* bf2_n_stage3_i__fft64Stage3_0_0 = fifo_stage3_i_reg__fft64Stage3_0_0;
		* bf2_n_stage3_q__fft64Stage3_0_0 = fifo_stage3_q_reg__fft64Stage3_0_0;
	}

	{
		* bf2_fifo_stage3_i__fft64Stage3_0_0 = * fifo_i_tmp_3__fft64Stage3_0_0;
		* bf2_fifo_stage3_q__fft64Stage3_0_0 = * fifo_q_tmp_3__fft64Stage3_0_0;
		int nsample_r__fft64Stage3_1_1;
		if (* nsample_3__fft64Stage3_0_0 < 1) {
			nsample_r__fft64Stage3_1_1 = 1;
		} else {
			// ifElse65
			if (* nsample_3__fft64Stage3_0_0 > fifo_len_div2_3__fft64Stage3_0_0 - 2) {
				nsample_r__fft64Stage3_1_1 = 0;
			} else {
				// ifElse64
				nsample_r__fft64Stage3_1_1 = * nsample_3__fft64Stage3_0_0 + 1;
			}
		}
		* fifo_i_tmp_3__fft64Stage3_0_0 = fifo_i_array_3__fft64Stage3_0_0[nsample_r__fft64Stage3_1_1];
		* fifo_q_tmp_3__fft64Stage3_0_0 = fifo_q_array_3__fft64Stage3_0_0[nsample_r__fft64Stage3_1_1];
		fifo_i_array_3__fft64Stage3_0_0[* nsample_3__fft64Stage3_0_0] = bf2_ndiv2_stage3_i__fft64Stage3_0_0;
		fifo_q_array_3__fft64Stage3_0_0[* nsample_3__fft64Stage3_0_0] = bf2_ndiv2_stage3_q__fft64Stage3_0_0;
		if (* nsample_3__fft64Stage3_0_0 < fifo_len_div2_3__fft64Stage3_0_0 - 1) {
			* nsample_3__fft64Stage3_0_0 = * nsample_3__fft64Stage3_0_0 + 1;
		} else {
			// ifElse66
			* nsample_3__fft64Stage3_0_0 = 0;
		}
	}
}

void fft64Stage2(const int s2__fft64Stage2_0_0, const int s3__fft64Stage2_0_0, const int fifo_len_div2_2__fft64Stage2_0_0, const float bf2_n_stage3_i__fft64Stage2_0_0, const float bf2_n_stage3_q__fft64Stage2_0_0, const float fifo_stage2_i_reg__fft64Stage2_0_0, const float fifo_stage2_q_reg__fft64Stage2_0_0, float *bf2_n_stage2_i__fft64Stage2_0_0, float *bf2_n_stage2_q__fft64Stage2_0_0, int *nsample_2__fft64Stage2_0_0, float *bf2_fifo_stage2_i__fft64Stage2_0_0, float *bf2_fifo_stage2_q__fft64Stage2_0_0, float fifo_i_array_2__fft64Stage2_0_0[], float fifo_q_array_2__fft64Stage2_0_0[]) {
	float bf2_ndiv2_stage2_i__fft64Stage2_0_0;
	float bf2_ndiv2_stage2_q__fft64Stage2_0_0;
	if (s2__fft64Stage2_0_0 == 0) {
		bf2_ndiv2_stage2_i__fft64Stage2_0_0 = bf2_n_stage3_i__fft64Stage2_0_0;
		bf2_ndiv2_stage2_q__fft64Stage2_0_0 = bf2_n_stage3_q__fft64Stage2_0_0;
		* bf2_n_stage2_i__fft64Stage2_0_0 = fifo_stage2_i_reg__fft64Stage2_0_0;
		* bf2_n_stage2_q__fft64Stage2_0_0 = fifo_stage2_q_reg__fft64Stage2_0_0;
	} else {
		// ifElse68
		float tmp2_real__fft64Stage2_1_0, tmp2_imag__fft64Stage2_1_0;
		if (s3__fft64Stage2_0_0 == 0) {
			tmp2_real__fft64Stage2_1_0 = bf2_n_stage3_q__fft64Stage2_0_0;
			tmp2_imag__fft64Stage2_1_0 = -bf2_n_stage3_i__fft64Stage2_0_0;
		} else {
			// ifElse67
			tmp2_real__fft64Stage2_1_0 = bf2_n_stage3_i__fft64Stage2_0_0;
			tmp2_imag__fft64Stage2_1_0 = bf2_n_stage3_q__fft64Stage2_0_0;
		}
		* bf2_n_stage2_i__fft64Stage2_0_0 = fifo_stage2_i_reg__fft64Stage2_0_0 + tmp2_real__fft64Stage2_1_0;
		* bf2_n_stage2_q__fft64Stage2_0_0 = fifo_stage2_q_reg__fft64Stage2_0_0 + tmp2_imag__fft64Stage2_1_0;
		bf2_ndiv2_stage2_i__fft64Stage2_0_0 = fifo_stage2_i_reg__fft64Stage2_0_0 - tmp2_real__fft64Stage2_1_0;
		bf2_ndiv2_stage2_q__fft64Stage2_0_0 = fifo_stage2_q_reg__fft64Stage2_0_0 - tmp2_imag__fft64Stage2_1_0;
	}

	{
		* bf2_fifo_stage2_i__fft64Stage2_0_0 = fifo_i_array_2__fft64Stage2_0_0[* nsample_2__fft64Stage2_0_0];
		* bf2_fifo_stage2_q__fft64Stage2_0_0 = fifo_q_array_2__fft64Stage2_0_0[* nsample_2__fft64Stage2_0_0];
		fifo_i_array_2__fft64Stage2_0_0[* nsample_2__fft64Stage2_0_0] = bf2_ndiv2_stage2_i__fft64Stage2_0_0;
		fifo_q_array_2__fft64Stage2_0_0[* nsample_2__fft64Stage2_0_0] = bf2_ndiv2_stage2_q__fft64Stage2_0_0;
		if (* nsample_2__fft64Stage2_0_0 < fifo_len_div2_2__fft64Stage2_0_0 - 1) {
			* nsample_2__fft64Stage2_0_0 = * nsample_2__fft64Stage2_0_0 + 1;
		} else {
			// ifElse69
			* nsample_2__fft64Stage2_0_0 = 0;
		}
	}
}

void fft64Stage1(const int s1__fft64Stage1_0_0, const int fifo_len_div2_1__fft64Stage1_0_0, const float fifo_stage1_i_reg__fft64Stage1_0_0, const float fifo_stage1_q_reg__fft64Stage1_0_0, const float mult_stage21_i__fft64Stage1_0_0, const float mult_stage21_q__fft64Stage1_0_0, float *bf2_n_stage1_i__fft64Stage1_0_0, float *bf2_n_stage1_q__fft64Stage1_0_0, int *nsample_1__fft64Stage1_0_0, float *bf2_fifo_stage1_i__fft64Stage1_0_0, float *bf2_fifo_stage1_q__fft64Stage1_0_0, float fifo_i_array_1__fft64Stage1_0_0[], float fifo_q_array_1__fft64Stage1_0_0[]) {
	float bf2_ndiv2_stage1_i__fft64Stage1_0_0;
	float bf2_ndiv2_stage1_q__fft64Stage1_0_0;
	if (s1__fft64Stage1_0_0 == 1) {
		* bf2_n_stage1_i__fft64Stage1_0_0 = fifo_stage1_i_reg__fft64Stage1_0_0 + mult_stage21_i__fft64Stage1_0_0;
		* bf2_n_stage1_q__fft64Stage1_0_0 = fifo_stage1_q_reg__fft64Stage1_0_0 + mult_stage21_q__fft64Stage1_0_0;
		bf2_ndiv2_stage1_i__fft64Stage1_0_0 = fifo_stage1_i_reg__fft64Stage1_0_0 - mult_stage21_i__fft64Stage1_0_0;
		bf2_ndiv2_stage1_q__fft64Stage1_0_0 = fifo_stage1_q_reg__fft64Stage1_0_0 - mult_stage21_q__fft64Stage1_0_0;
	} else {
		// ifElse70
		bf2_ndiv2_stage1_i__fft64Stage1_0_0 = mult_stage21_i__fft64Stage1_0_0;
		bf2_ndiv2_stage1_q__fft64Stage1_0_0 = mult_stage21_q__fft64Stage1_0_0;
		* bf2_n_stage1_i__fft64Stage1_0_0 = fifo_stage1_i_reg__fft64Stage1_0_0;
		* bf2_n_stage1_q__fft64Stage1_0_0 = fifo_stage1_q_reg__fft64Stage1_0_0;
	}

	{
		* bf2_fifo_stage1_i__fft64Stage1_0_0 = fifo_i_array_1__fft64Stage1_0_0[* nsample_1__fft64Stage1_0_0];
		* bf2_fifo_stage1_q__fft64Stage1_0_0 = fifo_q_array_1__fft64Stage1_0_0[* nsample_1__fft64Stage1_0_0];
		fifo_i_array_1__fft64Stage1_0_0[* nsample_1__fft64Stage1_0_0] = bf2_ndiv2_stage1_i__fft64Stage1_0_0;
		fifo_q_array_1__fft64Stage1_0_0[* nsample_1__fft64Stage1_0_0] = bf2_ndiv2_stage1_q__fft64Stage1_0_0;
		if (* nsample_1__fft64Stage1_0_0 < fifo_len_div2_1__fft64Stage1_0_0 - 1) {
			* nsample_1__fft64Stage1_0_0 = * nsample_1__fft64Stage1_0_0 + 1;
		} else {
			// ifElse71
			* nsample_1__fft64Stage1_0_0 = 0;
		}
	}
}

void fft64Stage0(const int s0__fft64Stage0_0_0, const int s1__fft64Stage0_0_0, const float bf2_n_stage1_i__fft64Stage0_0_0, const float bf2_n_stage1_q__fft64Stage0_0_0, const float fifo_stage0_i_reg__fft64Stage0_0_0, const float fifo_stage0_q_reg__fft64Stage0_0_0, float *bf2_n_stage0_i__fft64Stage0_0_0, float *bf2_n_stage0_q__fft64Stage0_0_0, float *bf2_fifo_stage0_i__fft64Stage0_0_0, float *bf2_fifo_stage0_q__fft64Stage0_0_0) {
	float bf2_ndiv2_stage0_i__fft64Stage0_0_0;
	float bf2_ndiv2_stage0_q__fft64Stage0_0_0;
	if (s0__fft64Stage0_0_0 == 0) {
		bf2_ndiv2_stage0_i__fft64Stage0_0_0 = bf2_n_stage1_i__fft64Stage0_0_0;
		bf2_ndiv2_stage0_q__fft64Stage0_0_0 = bf2_n_stage1_q__fft64Stage0_0_0;
		* bf2_n_stage0_i__fft64Stage0_0_0 = fifo_stage0_i_reg__fft64Stage0_0_0;
		* bf2_n_stage0_q__fft64Stage0_0_0 = fifo_stage0_q_reg__fft64Stage0_0_0;
	} else {
		// ifElse73
		float tmp2_real__fft64Stage0_1_0, tmp2_imag__fft64Stage0_1_0;
		if (s1__fft64Stage0_0_0 == 0) {
			tmp2_real__fft64Stage0_1_0 = bf2_n_stage1_q__fft64Stage0_0_0;
			tmp2_imag__fft64Stage0_1_0 = -bf2_n_stage1_i__fft64Stage0_0_0;
		} else {
			// ifElse72
			tmp2_real__fft64Stage0_1_0 = bf2_n_stage1_i__fft64Stage0_0_0;
			tmp2_imag__fft64Stage0_1_0 = bf2_n_stage1_q__fft64Stage0_0_0;
		}
		* bf2_n_stage0_i__fft64Stage0_0_0 = fifo_stage0_i_reg__fft64Stage0_0_0 + tmp2_real__fft64Stage0_1_0;
		* bf2_n_stage0_q__fft64Stage0_0_0 = fifo_stage0_q_reg__fft64Stage0_0_0 + tmp2_imag__fft64Stage0_1_0;
		bf2_ndiv2_stage0_i__fft64Stage0_0_0 = fifo_stage0_i_reg__fft64Stage0_0_0 - tmp2_real__fft64Stage0_1_0;
		bf2_ndiv2_stage0_q__fft64Stage0_0_0 = fifo_stage0_q_reg__fft64Stage0_0_0 - tmp2_imag__fft64Stage0_1_0;
	}

	{
		* bf2_fifo_stage0_i__fft64Stage0_0_0 = bf2_ndiv2_stage0_i__fft64Stage0_0_0;
		* bf2_fifo_stage0_q__fft64Stage0_0_0 = bf2_ndiv2_stage0_q__fft64Stage0_0_0;
	}
}

