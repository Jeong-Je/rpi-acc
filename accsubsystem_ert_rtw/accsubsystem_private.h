/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: accsubsystem_private.h
 *
 * Code generated for Simulink model 'accsubsystem'.
 *
 * Model version                  : 1.0
 * Simulink Coder version         : 26.1 (R2026a) 20-Nov-2025
 * C/C++ source code generated on : Sat Jun 27 22:55:04 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-A (64-bit)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef accsubsystem_private_h_
#define accsubsystem_private_h_
#include "rtwtypes.h"
#include "accsubsystem_types.h"
#include "accsubsystem.h"

extern real_T rt_roundd_snf(real_T u);
extern real_T rt_hypotd_snf(real_T u0, real_T u1);
extern void accsubsys_DataTypeConversion_L0(real_T rtu_u, real_T *rty_y);

#endif                                 /* accsubsystem_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
