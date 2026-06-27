/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: accsubsystem_1_data.c
 *
 * Code generated for Simulink model 'accsubsystem_1'.
 *
 * Model version                  : 1.0
 * Simulink Coder version         : 26.1 (R2026a) 20-Nov-2025
 * C/C++ source code generated on : Sat Jun 27 22:46:45 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-A (64-bit)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "accsubsystem_1.h"

/* Block parameters (default storage) */
P_accsubsystem_1_T accsubsystem_1_P = {
  /* Expression: lastx+xoff
   * Referenced by: '<S13>/last_x'
   */
  { 0.0, 0.0, 0.0, 0.0 },

  /* Expression: lastu+uoff
   * Referenced by: '<S13>/last_mv'
   */
  0.0,

  /* Expression: accsubsystem_1_data.DefaultSpacing
   * Referenced by: '<S1>/Default spacing constant'
   */
  0.3,

  /* Expression: accsubsystem_1_data.MinAcceleration
   * Referenced by: '<S1>/Minimum longitudinal acceleration constant'
   */
  -0.5,

  /* Expression: accsubsystem_1_data.MaxAcceleration
   * Referenced by: '<S1>/Maximum longitudinal acceleration constant'
   */
  0.3,

  /* Expression: accsubsystem_1_data.MinVelocity
   * Referenced by: '<S1>/Minimum velocity constant'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<S1>/Unconstrained'
   */
  0.0,

  /* Expression: accsubsystem_1_data.MaxVelocity
   * Referenced by: '<S1>/Maximum velocity constant'
   */
  0.351,

  /* Expression: zeros(1,1)
   * Referenced by: '<S12>/E_zero'
   */
  0.0,

  /* Expression: MVscale(:,ones(1,max(nCC,1)))'
   * Referenced by: '<S13>/umin_scale4'
   */
  0.8,

  /* Expression: zeros(1,2)
   * Referenced by: '<S12>/F_zero'
   */
  { 0.0, 0.0 },

  /* Expression: Yscale(:,ones(1,max(nCC,1)))'
   * Referenced by: '<S13>/ymin_scale1'
   */
  { 0.351, 0.351 },

  /* Expression: zeros(1,1)
   * Referenced by: '<S12>/G_zero'
   */
  0.0,

  /* Expression: zeros(1,1)
   * Referenced by: '<S12>/S_zero'
   */
  0.0,

  /* Expression: MDscale(:,ones(1,max(nCC,1)))'
   * Referenced by: '<S13>/ymin_scale2'
   */
  0.351,

  /* Expression: 0
   * Referenced by: '<S1>/Enable optimization constant'
   */
  0.0,

  /* Expression: zeros(1,1)
   * Referenced by: '<S12>/ext.mv_zero'
   */
  0.0,

  /* Expression: RMVscale
   * Referenced by: '<S13>/ext.mv_scale'
   */
  1.25,

  /* Expression: zeros(1,1)
   * Referenced by: '<S12>/mv.target_zero'
   */
  0.0,

  /* Expression: RMVscale
   * Referenced by: '<S13>/ext.mv_scale1'
   */
  1.25,

  /* Expression: zeros(2,1)
   * Referenced by: '<S12>/y.wt_zero'
   */
  { 0.0, 0.0 },

  /* Expression: zeros(1,1)
   * Referenced by: '<S12>/u.wt_zero'
   */
  0.0,

  /* Expression: zeros(1,1)
   * Referenced by: '<S12>/du.wt_zero'
   */
  0.0,

  /* Expression: zeros(1,1)
   * Referenced by: '<S12>/ecr.wt_zero'
   */
  0.0,

  /* Expression: MVscale
   * Referenced by: '<S13>/umin_scale1'
   */
  0.8,

  /* Expression: 0
   * Referenced by: '<S1>/External control signal constant'
   */
  0.0,

  /* Expression: iA
   * Referenced by: '<S13>/Memory'
   */
  { false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false, false, false, false,
    false, false, false, false, false, false, false, false }
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
