/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: accsubsystem_1.h
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

#ifndef accsubsystem_1_h_
#define accsubsystem_1_h_
#ifndef accsubsystem_1_COMMON_INCLUDES_
#define accsubsystem_1_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* accsubsystem_1_COMMON_INCLUDES_ */

#include "accsubsystem_1_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"
#include "rtGetNaN.h"
#include <stddef.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T last_mv_DSTATE;               /* '<S13>/last_mv' */
  real_T last_x_PreviousInput[4];      /* '<S13>/last_x' */
  boolean_T Memory_PreviousInput[96];  /* '<S13>/Memory' */
} DW_accsubsystem_1_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T set_velocity;                 /* '<Root>/Set velocity' */
  real_T Timegap;                      /* '<Root>/Time gap' */
  real_T ego_velocity;                 /* '<Root>/Longitudinal velocity' */
  real_T relativedistance;             /* '<Root>/Relative distance' */
  real_T relative_velocity;            /* '<Root>/Relative velocity' */
} ExtU_accsubsystem_1_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T Longitudinalacceleration;     /* '<Root>/Longitudinal acceleration' */
} ExtY_accsubsystem_1_T;

/* Parameters (default storage) */
struct P_accsubsystem_1_T_ {
  real_T last_x_InitialCondition[4];   /* Expression: lastx+xoff
                                        * Referenced by: '<S13>/last_x'
                                        */
  real_T last_mv_InitialCondition;     /* Expression: lastu+uoff
                                        * Referenced by: '<S13>/last_mv'
                                        */
  real_T Defaultspacingconstant_Value;
                               /* Expression: accsubsystem_1_data.DefaultSpacing
                                * Referenced by: '<S1>/Default spacing constant'
                                */
  real_T Minimumlongitudinalacceleration;
                              /* Expression: accsubsystem_1_data.MinAcceleration
                               * Referenced by: '<S1>/Minimum longitudinal acceleration constant'
                               */
  real_T Maximumlongitudinalacceleration;
                              /* Expression: accsubsystem_1_data.MaxAcceleration
                               * Referenced by: '<S1>/Maximum longitudinal acceleration constant'
                               */
  real_T Minimumvelocityconstant_Value;
                                  /* Expression: accsubsystem_1_data.MinVelocity
                                   * Referenced by: '<S1>/Minimum velocity constant'
                                   */
  real_T Unconstrained_Value;          /* Expression: 0
                                        * Referenced by: '<S1>/Unconstrained'
                                        */
  real_T Maximumvelocityconstant_Value;
                                  /* Expression: accsubsystem_1_data.MaxVelocity
                                   * Referenced by: '<S1>/Maximum velocity constant'
                                   */
  real_T E_zero_Value;                 /* Expression: zeros(1,1)
                                        * Referenced by: '<S12>/E_zero'
                                        */
  real_T umin_scale4_Gain;         /* Expression: MVscale(:,ones(1,max(nCC,1)))'
                                    * Referenced by: '<S13>/umin_scale4'
                                    */
  real_T F_zero_Value[2];              /* Expression: zeros(1,2)
                                        * Referenced by: '<S12>/F_zero'
                                        */
  real_T ymin_scale1_Gain[2];       /* Expression: Yscale(:,ones(1,max(nCC,1)))'
                                     * Referenced by: '<S13>/ymin_scale1'
                                     */
  real_T G_zero_Value;                 /* Expression: zeros(1,1)
                                        * Referenced by: '<S12>/G_zero'
                                        */
  real_T S_zero_Value;                 /* Expression: zeros(1,1)
                                        * Referenced by: '<S12>/S_zero'
                                        */
  real_T ymin_scale2_Gain;         /* Expression: MDscale(:,ones(1,max(nCC,1)))'
                                    * Referenced by: '<S13>/ymin_scale2'
                                    */
  real_T Enableoptimizationconstant_Valu;/* Expression: 0
                                          * Referenced by: '<S1>/Enable optimization constant'
                                          */
  real_T extmv_zero_Value;             /* Expression: zeros(1,1)
                                        * Referenced by: '<S12>/ext.mv_zero'
                                        */
  real_T extmv_scale_Gain;             /* Expression: RMVscale
                                        * Referenced by: '<S13>/ext.mv_scale'
                                        */
  real_T mvtarget_zero_Value;          /* Expression: zeros(1,1)
                                        * Referenced by: '<S12>/mv.target_zero'
                                        */
  real_T extmv_scale1_Gain;            /* Expression: RMVscale
                                        * Referenced by: '<S13>/ext.mv_scale1'
                                        */
  real_T ywt_zero_Value[2];            /* Expression: zeros(2,1)
                                        * Referenced by: '<S12>/y.wt_zero'
                                        */
  real_T uwt_zero_Value;               /* Expression: zeros(1,1)
                                        * Referenced by: '<S12>/u.wt_zero'
                                        */
  real_T duwt_zero_Value;              /* Expression: zeros(1,1)
                                        * Referenced by: '<S12>/du.wt_zero'
                                        */
  real_T ecrwt_zero_Value;             /* Expression: zeros(1,1)
                                        * Referenced by: '<S12>/ecr.wt_zero'
                                        */
  real_T umin_scale1_Gain;             /* Expression: MVscale
                                        * Referenced by: '<S13>/umin_scale1'
                                        */
  real_T Externalcontrolsignalconstant_V;/* Expression: 0
                                          * Referenced by: '<S1>/External control signal constant'
                                          */
  boolean_T Memory_InitialCondition[96];/* Expression: iA
                                         * Referenced by: '<S13>/Memory'
                                         */
};

/* Real-time Model Data Structure */
struct tag_RTM_accsubsystem_1_T {
  const char_T * volatile errorStatus;
};

/* Block parameters (default storage) */
extern P_accsubsystem_1_T accsubsystem_1_P;

/* Block states (default storage) */
extern DW_accsubsystem_1_T accsubsystem_1_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_accsubsystem_1_T accsubsystem_1_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_accsubsystem_1_T accsubsystem_1_Y;

/* Model entry point functions */
extern void accsubsystem_1_initialize(void);
extern void accsubsystem_1_step(void);
extern void accsubsystem_1_terminate(void);

/* Real-time Model object */
extern RT_MODEL_accsubsystem_1_T *const accsubsystem_1_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S13>/Constant' : Unused code path elimination
 * Block '<S13>/Floor' : Unused code path elimination
 * Block '<S13>/Floor1' : Unused code path elimination
 * Block '<S14>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S15>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S16>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S17>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S18>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S19>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S20>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S21>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S22>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S23>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S24>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S25>/Matrix Dimension Check' : Unused code path elimination
 * Block '<S26>/Vector Dimension Check' : Unused code path elimination
 * Block '<S27>/Vector Dimension Check' : Unused code path elimination
 * Block '<S28>/Vector Dimension Check' : Unused code path elimination
 * Block '<S29>/Vector Dimension Check' : Unused code path elimination
 * Block '<S30>/Vector Dimension Check' : Unused code path elimination
 * Block '<S31>/Vector Dimension Check' : Unused code path elimination
 * Block '<S13>/Min' : Unused code path elimination
 * Block '<S13>/constant' : Unused code path elimination
 * Block '<S32>/Vector Dimension Check' : Unused code path elimination
 * Block '<S13>/umin_scale2' : Unused code path elimination
 * Block '<S13>/umin_scale3' : Unused code path elimination
 * Block '<S13>/umin_scale5' : Unused code path elimination
 * Block '<S13>/ym_zero' : Unused code path elimination
 * Block '<S12>/m_zero' : Unused code path elimination
 * Block '<S12>/p_zero' : Unused code path elimination
 * Block '<S13>/Reshape' : Reshape block reduction
 * Block '<S13>/Reshape1' : Reshape block reduction
 * Block '<S13>/Reshape2' : Reshape block reduction
 * Block '<S13>/Reshape3' : Reshape block reduction
 * Block '<S13>/Reshape4' : Reshape block reduction
 * Block '<S13>/Reshape5' : Reshape block reduction
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'accsubsystem_1'
 * '<S1>'   : 'accsubsystem_1/ACC subsystem'
 * '<S2>'   : 'accsubsystem_1/ACC subsystem/DataTypeConversion_L0'
 * '<S3>'   : 'accsubsystem_1/ACC subsystem/DataTypeConversion_amax'
 * '<S4>'   : 'accsubsystem_1/ACC subsystem/DataTypeConversion_amin'
 * '<S5>'   : 'accsubsystem_1/ACC subsystem/DataTypeConversion_atrack'
 * '<S6>'   : 'accsubsystem_1/ACC subsystem/DataTypeConversion_dmin'
 * '<S7>'   : 'accsubsystem_1/ACC subsystem/DataTypeConversion_optsgn'
 * '<S8>'   : 'accsubsystem_1/ACC subsystem/DataTypeConversion_reldist'
 * '<S9>'   : 'accsubsystem_1/ACC subsystem/DataTypeConversion_vego'
 * '<S10>'  : 'accsubsystem_1/ACC subsystem/DataTypeConversion_vlead'
 * '<S11>'  : 'accsubsystem_1/ACC subsystem/DataTypeConversion_vset'
 * '<S12>'  : 'accsubsystem_1/ACC subsystem/MPC'
 * '<S13>'  : 'accsubsystem_1/ACC subsystem/MPC/MPC'
 * '<S14>'  : 'accsubsystem_1/ACC subsystem/MPC/MPC/MPC Matrix Signal Check'
 * '<S15>'  : 'accsubsystem_1/ACC subsystem/MPC/MPC/MPC Matrix Signal Check1'
 * '<S16>'  : 'accsubsystem_1/ACC subsystem/MPC/MPC/MPC Matrix Signal Check2'
 * '<S17>'  : 'accsubsystem_1/ACC subsystem/MPC/MPC/MPC Preview Signal Check'
 * '<S18>'  : 'accsubsystem_1/ACC subsystem/MPC/MPC/MPC Preview Signal Check1'
 * '<S19>'  : 'accsubsystem_1/ACC subsystem/MPC/MPC/MPC Preview Signal Check2'
 * '<S20>'  : 'accsubsystem_1/ACC subsystem/MPC/MPC/MPC Preview Signal Check3'
 * '<S21>'  : 'accsubsystem_1/ACC subsystem/MPC/MPC/MPC Preview Signal Check4'
 * '<S22>'  : 'accsubsystem_1/ACC subsystem/MPC/MPC/MPC Preview Signal Check5'
 * '<S23>'  : 'accsubsystem_1/ACC subsystem/MPC/MPC/MPC Preview Signal Check6'
 * '<S24>'  : 'accsubsystem_1/ACC subsystem/MPC/MPC/MPC Preview Signal Check7'
 * '<S25>'  : 'accsubsystem_1/ACC subsystem/MPC/MPC/MPC Preview Signal Check8'
 * '<S26>'  : 'accsubsystem_1/ACC subsystem/MPC/MPC/MPC Scalar Signal Check'
 * '<S27>'  : 'accsubsystem_1/ACC subsystem/MPC/MPC/MPC Scalar Signal Check1'
 * '<S28>'  : 'accsubsystem_1/ACC subsystem/MPC/MPC/MPC Scalar Signal Check2'
 * '<S29>'  : 'accsubsystem_1/ACC subsystem/MPC/MPC/MPC Vector Signal Check'
 * '<S30>'  : 'accsubsystem_1/ACC subsystem/MPC/MPC/MPC Vector Signal Check1'
 * '<S31>'  : 'accsubsystem_1/ACC subsystem/MPC/MPC/MPC Vector Signal Check6'
 * '<S32>'  : 'accsubsystem_1/ACC subsystem/MPC/MPC/moorx'
 * '<S33>'  : 'accsubsystem_1/ACC subsystem/MPC/MPC/optimizer'
 * '<S34>'  : 'accsubsystem_1/ACC subsystem/MPC/MPC/optimizer/optimizer'
 */
#endif                                 /* accsubsystem_1_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
