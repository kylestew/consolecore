#ifndef MATH_LAYER_H
#define MATH_LAYER_H

#include "layer.h"

// function signature for math-based visual functions
typedef float (*MathFunc)(float x, float y, float t);

// create a math animation layer
Layer *create_math_layer(MathFunc func, float scale, float speed);
void destroy_math_layer(Layer *layer);

// example function: ripple rings
float math_func_sine_rings(float x, float y, float t);
float math_func_wave_interference(float x, float y, float t);
float math_func_spiral(float x, float y, float t);
float math_func_checker(float x, float y, float t);

#endif // MATH_LAYER_H
