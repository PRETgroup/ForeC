/* BEGIN fs_math.h */
/*
** Portable freestanding code.
*/
#ifndef H_FS_MATH_H
#define H_FS_MATH_H

float fs_sqrt(float x);
float fs_log(float x);
float fs_log10(float x);
/*
** exp(x) = 1 + x + x^2/2! + x^3/3! + ...
*/
float fs_exp(float x);
float fs_modf(float value, float *iptr);
float fs_fmod(float x, float y);
float fs_pow(float x, float y);
float fs_cos(float x);
/*
** C99
*/
float fs_log2(float x);
float fs_exp2(float x);

#endif

/* END fs_math.h */
