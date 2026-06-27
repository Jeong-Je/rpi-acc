/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: accsubsystem_1.c
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
#include "rtwtypes.h"
#include "accsubsystem_1_private.h"
#include <string.h>
#include <math.h>
#include "rt_nonfinite.h"

/* Named constants for MATLAB Function: '<S33>/optimizer' */
#define accsubsystem_1_RMDscale        (2.8490028490028494)
#define accsubsystem_1_RMVscale        (1.25)
#define accsubsystem_1_degrees         (4)
#define accsubsystem_1_p               (30)

/* Block states (default storage) */
DW_accsubsystem_1_T accsubsystem_1_DW;

/* External inputs (root inport signals with default storage) */
ExtU_accsubsystem_1_T accsubsystem_1_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_accsubsystem_1_T accsubsystem_1_Y;

/* Real-time model */
static RT_MODEL_accsubsystem_1_T accsubsystem_1_M_;
RT_MODEL_accsubsystem_1_T *const accsubsystem_1_M = &accsubsystem_1_M_;

/* Forward declaration for local functions */
static real_T accsubsystem_1_norm(const real_T x[4]);
static real_T accsubsystem_1_maximum(const real_T x[4]);
static real_T accsubsystem_1_xnrm2(int32_T n, const real_T x[16], int32_T ix0);
static void accsubsystem_1_xgemv(int32_T b_m, int32_T n, const real_T b_A[16],
  int32_T ia0, const real_T x[16], int32_T ix0, real_T y[4]);
static void accsubsystem_1_xgerc(int32_T b_m, int32_T n, real_T alpha1, int32_T
  ix0, const real_T y[4], real_T b_A[16], int32_T ia0);
static real_T accsubsystem_1_KWIKfactor(const real_T b_Ac[384], const int32_T
  iC[96], int32_T nA, const real_T b_Linv[16], real_T RLinv[16], real_T D[16],
  real_T b_H[16], int32_T n);
static void accsubsystem_1_DropConstraint(int32_T kDrop, boolean_T iA[96],
  int32_T *nA, int32_T iC[96]);
static void accsubsystem_1_qpkwik(const real_T b_Linv[16], const real_T b_Hinv
  [16], const real_T f[4], const real_T b_Ac[384], const real_T b[96], boolean_T
  iA[96], int32_T maxiter, real_T FeasTol, real_T x[4], real_T lambda[96],
  int32_T *status);

/*
 * Output and update for atomic system:
 *    '<S1>/DataTypeConversion_L0'
 *    '<S1>/DataTypeConversion_amax'
 *    '<S1>/DataTypeConversion_amin'
 *    '<S1>/DataTypeConversion_atrack'
 */
void accsubsys_DataTypeConversion_L0(real_T rtu_u, real_T *rty_y)
{
  *rty_y = rtu_u;
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/* Function for MATLAB Function: '<S33>/optimizer' */
static real_T accsubsystem_1_norm(const real_T x[4])
{
  real_T absxk;
  real_T scale;
  real_T t;
  real_T y;
  int32_T b_k;
  int32_T exitg1;
  scale = 3.312168642111238E-170;
  absxk = fabs(x[0]);
  if (absxk > 3.312168642111238E-170) {
    y = 1.0;
    scale = absxk;
  } else {
    t = absxk / 3.312168642111238E-170;
    y = t * t;
  }

  absxk = fabs(x[1]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  absxk = fabs(x[2]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  absxk = fabs(x[3]);
  if (absxk > scale) {
    t = scale / absxk;
    y = y * t * t + 1.0;
    scale = absxk;
  } else {
    t = absxk / scale;
    y += t * t;
  }

  y = scale * sqrt(y);
  if (rtIsNaN(y)) {
    b_k = 0;
    do {
      exitg1 = 0;
      if (b_k < 4) {
        if (rtIsNaN(x[b_k])) {
          exitg1 = 1;
        } else {
          b_k++;
        }
      } else {
        y = (rtInf);
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }

  return y;
}

/* Function for MATLAB Function: '<S33>/optimizer' */
static real_T accsubsystem_1_maximum(const real_T x[4])
{
  real_T ex;
  real_T x_0;
  int32_T idx;
  int32_T k;
  boolean_T exitg1;
  if (!rtIsNaN(x[0])) {
    idx = 1;
  } else {
    idx = 0;
    k = 2;
    exitg1 = false;
    while (!exitg1 && (k < 5)) {
      if (!rtIsNaN(x[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }

  if (idx == 0) {
    ex = x[0];
  } else {
    ex = x[idx - 1];
    for (k = idx + 1; k < 5; k++) {
      x_0 = x[k - 1];
      if (ex < x_0) {
        ex = x_0;
      }
    }
  }

  return ex;
}

/* Function for MATLAB Function: '<S33>/optimizer' */
static real_T accsubsystem_1_xnrm2(int32_T n, const real_T x[16], int32_T ix0)
{
  real_T absxk;
  real_T scale;
  real_T t;
  real_T y;
  int32_T exitg1;
  int32_T k;
  int32_T kend;
  y = 0.0;
  if (n >= 1) {
    if (n == 1) {
      y = fabs(x[ix0 - 1]);
    } else {
      scale = 3.312168642111238E-170;
      kend = ix0 + n;
      for (k = ix0; k < kend; k++) {
        absxk = fabs(x[k - 1]);
        if (absxk > scale) {
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * sqrt(y);
      if (rtIsNaN(y)) {
        k = ix0;
        do {
          exitg1 = 0;
          if (k <= kend - 1) {
            if (rtIsNaN(x[k - 1])) {
              exitg1 = 1;
            } else {
              k++;
            }
          } else {
            y = (rtInf);
            exitg1 = 1;
          }
        } while (exitg1 == 0);
      }
    }
  }

  return y;
}

real_T rt_hypotd_snf(real_T u0, real_T u1)
{
  real_T a;
  real_T b;
  real_T y;
  a = fabs(u0);
  b = fabs(u1);
  if (a < b) {
    a /= b;
    y = sqrt(a * a + 1.0) * b;
  } else if (a > b) {
    b /= a;
    y = sqrt(b * b + 1.0) * a;
  } else if (rtIsNaN(b)) {
    y = (rtNaN);
  } else {
    y = a * 1.4142135623730951;
  }

  return y;
}

/* Function for MATLAB Function: '<S33>/optimizer' */
static void accsubsystem_1_xgemv(int32_T b_m, int32_T n, const real_T b_A[16],
  int32_T ia0, const real_T x[16], int32_T ix0, real_T y[4])
{
  real_T c;
  int32_T b;
  int32_T b_iy;
  int32_T d;
  int32_T ia;
  if ((b_m != 0) && (n != 0)) {
    if (n - 1 >= 0) {
      memset(&y[0], 0, (uint32_T)n * sizeof(real_T));
    }

    b = ((n - 1) << 2) + ia0;
    for (b_iy = ia0; b_iy <= b; b_iy += 4) {
      c = 0.0;
      d = b_iy + b_m;
      for (ia = b_iy; ia < d; ia++) {
        c += x[((ix0 + ia) - b_iy) - 1] * b_A[ia - 1];
      }

      ia = (b_iy - ia0) / 4;
      y[ia] += c;
    }
  }
}

/* Function for MATLAB Function: '<S33>/optimizer' */
static void accsubsystem_1_xgerc(int32_T b_m, int32_T n, real_T alpha1, int32_T
  ix0, const real_T y[4], real_T b_A[16], int32_T ia0)
{
  real_T temp;
  int32_T b;
  int32_T ijA;
  int32_T j;
  int32_T jA;
  if (!(alpha1 == 0.0)) {
    jA = ia0;
    for (j = 0; j < n; j++) {
      temp = y[j];
      if (temp != 0.0) {
        temp *= alpha1;
        b = b_m + jA;
        for (ijA = jA; ijA < b; ijA++) {
          b_A[ijA - 1] += b_A[((ix0 + ijA) - jA) - 1] * temp;
        }
      }

      jA += 4;
    }
  }
}

/* Function for MATLAB Function: '<S33>/optimizer' */
static real_T accsubsystem_1_KWIKfactor(const real_T b_Ac[384], const int32_T
  iC[96], int32_T nA, const real_T b_Linv[16], real_T RLinv[16], real_T D[16],
  real_T b_H[16], int32_T n)
{
  real_T Q[16];
  real_T R[16];
  real_T TL[16];
  real_T b_A[16];
  real_T tau[4];
  real_T work[4];
  real_T RLinv_0;
  real_T RLinv_1;
  real_T RLinv_2;
  real_T Status;
  real_T tmp;
  real_T xnorm;
  int32_T b_lastv;
  int32_T c_lastc;
  int32_T e;
  int32_T exitg1;
  int32_T ii;
  int32_T k_i;
  int32_T knt;
  boolean_T exitg2;
  Status = 1.0;
  memset(&RLinv[0], 0, sizeof(real_T) << 4U);
  for (ii = 0; ii < nA; ii++) {
    b_lastv = iC[ii];
    xnorm = 0.0;
    RLinv_0 = 0.0;
    RLinv_1 = 0.0;
    RLinv_2 = 0.0;
    for (k_i = 0; k_i < 4; k_i++) {
      tmp = b_Ac[(96 * k_i + b_lastv) - 1];
      c_lastc = k_i << 2;
      xnorm += b_Linv[c_lastc] * tmp;
      RLinv_0 += b_Linv[c_lastc + 1] * tmp;
      RLinv_1 += b_Linv[c_lastc + 2] * tmp;
      RLinv_2 += b_Linv[c_lastc + 3] * tmp;
    }

    k_i = ii << 2;
    RLinv[k_i + 3] = RLinv_2;
    RLinv[k_i + 2] = RLinv_1;
    RLinv[k_i + 1] = RLinv_0;
    RLinv[k_i] = xnorm;
  }

  memcpy(&b_A[0], &RLinv[0], sizeof(real_T) << 4U);
  work[0] = 0.0;
  work[1] = 0.0;
  work[2] = 0.0;
  work[3] = 0.0;
  for (k_i = 0; k_i < 4; k_i++) {
    ii = (k_i << 2) + k_i;
    if (k_i + 1 < 4) {
      RLinv_0 = b_A[ii];
      b_lastv = ii + 2;
      tau[k_i] = 0.0;
      xnorm = accsubsystem_1_xnrm2(3 - k_i, b_A, ii + 2);
      if (xnorm != 0.0) {
        xnorm = rt_hypotd_snf(b_A[ii], xnorm);
        if (b_A[ii] >= 0.0) {
          xnorm = -xnorm;
        }

        if (fabs(xnorm) < 1.0020841800044864E-292) {
          knt = 0;
          e = (ii - k_i) + 4;
          do {
            knt++;
            for (c_lastc = b_lastv; c_lastc <= e; c_lastc++) {
              b_A[c_lastc - 1] *= 9.9792015476736E+291;
            }

            xnorm *= 9.9792015476736E+291;
            RLinv_0 *= 9.9792015476736E+291;
          } while ((fabs(xnorm) < 1.0020841800044864E-292) && (knt < 20));

          xnorm = rt_hypotd_snf(RLinv_0, accsubsystem_1_xnrm2(3 - k_i, b_A, ii +
            2));
          if (RLinv_0 >= 0.0) {
            xnorm = -xnorm;
          }

          tau[k_i] = (xnorm - RLinv_0) / xnorm;
          RLinv_0 = 1.0 / (RLinv_0 - xnorm);
          for (c_lastc = b_lastv; c_lastc <= e; c_lastc++) {
            b_A[c_lastc - 1] *= RLinv_0;
          }

          for (b_lastv = 0; b_lastv < knt; b_lastv++) {
            xnorm *= 1.0020841800044864E-292;
          }

          RLinv_0 = xnorm;
        } else {
          tau[k_i] = (xnorm - b_A[ii]) / xnorm;
          RLinv_0 = 1.0 / (b_A[ii] - xnorm);
          knt = (ii - k_i) + 4;
          for (c_lastc = b_lastv; c_lastc <= knt; c_lastc++) {
            b_A[c_lastc - 1] *= RLinv_0;
          }

          RLinv_0 = xnorm;
        }
      }

      b_A[ii] = RLinv_0;
      xnorm = b_A[ii];
      b_A[ii] = 1.0;
      if (tau[k_i] != 0.0) {
        b_lastv = 4 - k_i;
        c_lastc = (ii - k_i) + 3;
        while ((b_lastv > 0) && (b_A[c_lastc] == 0.0)) {
          b_lastv--;
          c_lastc--;
        }

        c_lastc = 3 - k_i;
        exitg2 = false;
        while (!exitg2 && (c_lastc > 0)) {
          knt = (((c_lastc - 1) << 2) + ii) + 4;
          e = knt;
          do {
            exitg1 = 0;
            if (e + 1 <= knt + b_lastv) {
              if (b_A[e] != 0.0) {
                exitg1 = 1;
              } else {
                e++;
              }
            } else {
              c_lastc--;
              exitg1 = 2;
            }
          } while (exitg1 == 0);

          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      } else {
        b_lastv = 0;
        c_lastc = 0;
      }

      if (b_lastv > 0) {
        accsubsystem_1_xgemv(b_lastv, c_lastc, b_A, ii + 5, b_A, ii + 1, work);
        accsubsystem_1_xgerc(b_lastv, c_lastc, -tau[k_i], ii + 1, work, b_A, ii
                             + 5);
      }

      b_A[ii] = xnorm;
    } else {
      tau[3] = 0.0;
    }
  }

  for (k_i = 0; k_i < 4; k_i++) {
    for (ii = 0; ii <= k_i; ii++) {
      b_lastv = k_i << 2;
      R[ii + b_lastv] = b_A[b_lastv + ii];
    }

    for (ii = k_i + 2; ii < 5; ii++) {
      R[(ii + (k_i << 2)) - 1] = 0.0;
    }

    work[k_i] = 0.0;
  }

  for (k_i = 3; k_i >= 0; k_i--) {
    ii = (k_i << 2) + k_i;
    if (k_i + 1 < 4) {
      b_A[ii] = 1.0;
      if (tau[k_i] != 0.0) {
        b_lastv = 4 - k_i;
        c_lastc = (ii - k_i) + 3;
        while ((b_lastv > 0) && (b_A[c_lastc] == 0.0)) {
          b_lastv--;
          c_lastc--;
        }

        c_lastc = 3 - k_i;
        exitg2 = false;
        while (!exitg2 && (c_lastc > 0)) {
          knt = (((c_lastc - 1) << 2) + ii) + 4;
          e = knt;
          do {
            exitg1 = 0;
            if (e + 1 <= knt + b_lastv) {
              if (b_A[e] != 0.0) {
                exitg1 = 1;
              } else {
                e++;
              }
            } else {
              c_lastc--;
              exitg1 = 2;
            }
          } while (exitg1 == 0);

          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      } else {
        b_lastv = 0;
        c_lastc = 0;
      }

      if (b_lastv > 0) {
        accsubsystem_1_xgemv(b_lastv, c_lastc, b_A, ii + 5, b_A, ii + 1, work);
        accsubsystem_1_xgerc(b_lastv, c_lastc, -tau[k_i], ii + 1, work, b_A, ii
                             + 5);
      }

      c_lastc = (ii - k_i) + 4;
      for (b_lastv = ii + 2; b_lastv <= c_lastc; b_lastv++) {
        b_A[b_lastv - 1] *= -tau[k_i];
      }
    }

    b_A[ii] = 1.0 - tau[k_i];
    for (b_lastv = 0; b_lastv < k_i; b_lastv++) {
      b_A[(ii - b_lastv) - 1] = 0.0;
    }
  }

  for (k_i = 0; k_i < 4; k_i++) {
    ii = k_i << 2;
    Q[ii] = b_A[ii];
    Q[ii + 1] = b_A[ii + 1];
    Q[ii + 2] = b_A[ii + 2];
    Q[ii + 3] = b_A[ii + 3];
  }

  k_i = 0;
  do {
    exitg1 = 0;
    if (k_i <= nA - 1) {
      if (fabs(R[(k_i << 2) + k_i]) < 1.0E-12) {
        Status = -2.0;
        exitg1 = 1;
      } else {
        k_i++;
      }
    } else {
      for (k_i = 0; k_i < n; k_i++) {
        for (ii = 0; ii < n; ii++) {
          b_lastv = k_i << 2;
          c_lastc = ii << 2;
          TL[k_i + c_lastc] = ((b_Linv[b_lastv + 1] * Q[c_lastc + 1] +
                                b_Linv[b_lastv] * Q[c_lastc]) + b_Linv[b_lastv +
                               2] * Q[c_lastc + 2]) + b_Linv[b_lastv + 3] *
            Q[c_lastc + 3];
        }
      }

      memset(&RLinv[0], 0, sizeof(real_T) << 4U);
      for (b_lastv = nA; b_lastv >= 1; b_lastv--) {
        k_i = (b_lastv - 1) << 2;
        ii = (b_lastv + k_i) - 1;
        RLinv[ii] = 1.0;
        for (c_lastc = b_lastv; c_lastc <= nA; c_lastc++) {
          e = (((c_lastc - 1) << 2) + b_lastv) - 1;
          RLinv[e] /= R[ii];
        }

        if (b_lastv > 1) {
          for (c_lastc = 0; c_lastc <= b_lastv - 2; c_lastc++) {
            for (knt = b_lastv; knt <= nA; knt++) {
              ii = (knt - 1) << 2;
              e = ii + c_lastc;
              RLinv[e] -= RLinv[(ii + b_lastv) - 1] * R[k_i + c_lastc];
            }
          }
        }
      }

      for (b_lastv = 0; b_lastv < n; b_lastv++) {
        for (c_lastc = b_lastv + 1; c_lastc <= n; c_lastc++) {
          k_i = ((c_lastc - 1) << 2) + b_lastv;
          b_H[k_i] = 0.0;
          for (knt = nA + 1; knt <= n; knt++) {
            ii = (knt - 1) << 2;
            b_H[k_i] -= TL[(ii + c_lastc) - 1] * TL[ii + b_lastv];
          }

          b_H[(c_lastc + (b_lastv << 2)) - 1] = b_H[k_i];
        }
      }

      for (b_lastv = 0; b_lastv < nA; b_lastv++) {
        for (c_lastc = 0; c_lastc < n; c_lastc++) {
          k_i = (b_lastv << 2) + c_lastc;
          D[k_i] = 0.0;
          for (knt = b_lastv + 1; knt <= nA; knt++) {
            ii = (knt - 1) << 2;
            D[k_i] += TL[ii + c_lastc] * RLinv[ii + b_lastv];
          }
        }
      }

      exitg1 = 1;
    }
  } while (exitg1 == 0);

  return Status;
}

/* Function for MATLAB Function: '<S33>/optimizer' */
static void accsubsystem_1_DropConstraint(int32_T kDrop, boolean_T iA[96],
  int32_T *nA, int32_T iC[96])
{
  int32_T i;
  if (kDrop > 0) {
    iA[iC[kDrop - 1] - 1] = false;
    if (kDrop < *nA) {
      for (i = kDrop; i < *nA; i++) {
        iC[i - 1] = iC[i];
      }
    }

    iC[*nA - 1] = 0;
    (*nA)--;
  }
}

/* Function for MATLAB Function: '<S33>/optimizer' */
static void accsubsystem_1_qpkwik(const real_T b_Linv[16], const real_T b_Hinv
  [16], const real_T f[4], const real_T b_Ac[384], const real_T b[96], boolean_T
  iA[96], int32_T maxiter, real_T FeasTol, real_T x[4], real_T lambda[96],
  int32_T *status)
{
  real_T cTol[96];
  real_T D[16];
  real_T RLinv[16];
  real_T U[16];
  real_T b_H[16];
  real_T Opt[8];
  real_T Rhs[8];
  real_T b_x[4];
  real_T r[4];
  real_T Xnorm0;
  real_T cMin;
  real_T cVal;
  real_T rMin;
  real_T rVal;
  real_T t;
  real_T t1;
  real_T z;
  real_T z_idx_2;
  real_T z_idx_3;
  real_T z_tmp;
  int32_T iC[96];
  int32_T U_tmp;
  int32_T U_tmp_0;
  int32_T b_exponent;
  int32_T exitg1;
  int32_T exitg3;
  int32_T exponent;
  int32_T i;
  int32_T iSave;
  int32_T nA;
  int32_T r_tmp;
  int32_T tmp;
  boolean_T ColdReset;
  boolean_T DualFeasible;
  boolean_T cTolComputed;
  boolean_T exitg2;
  boolean_T exitg4;
  boolean_T guard1;
  boolean_T guard2;
  x[0] = 0.0;
  x[1] = 0.0;
  x[2] = 0.0;
  x[3] = 0.0;
  *status = 1;
  r[0] = 0.0;
  r[1] = 0.0;
  r[2] = 0.0;
  r[3] = 0.0;
  rMin = 0.0;
  cTolComputed = false;
  for (i = 0; i < 96; i++) {
    lambda[i] = 0.0;
    cTol[i] = 1.0;
    iC[i] = 0;
  }

  nA = 0;
  for (i = 0; i < 96; i++) {
    if (iA[i]) {
      nA++;
      iC[nA - 1] = i + 1;
    }
  }

  guard1 = false;
  if (nA > 0) {
    memset(&Opt[0], 0, sizeof(real_T) << 3U);
    Rhs[0] = f[0];
    Rhs[4] = 0.0;
    Rhs[1] = f[1];
    Rhs[5] = 0.0;
    Rhs[2] = f[2];
    Rhs[6] = 0.0;
    Rhs[3] = f[3];
    Rhs[7] = 0.0;
    DualFeasible = false;
    tmp = (int32_T)rt_roundd_snf(0.3 * (real_T)nA);
    ColdReset = false;
    do {
      exitg3 = 0;
      if (!DualFeasible && (nA > 0) && (*status <= maxiter)) {
        Xnorm0 = accsubsystem_1_KWIKfactor(b_Ac, iC, nA, b_Linv, RLinv, D, b_H,
          accsubsystem_1_degrees);
        if (Xnorm0 < 0.0) {
          if (ColdReset) {
            *status = -2;
            exitg3 = 2;
          } else {
            nA = 0;
            memset(&iA[0], 0, 96U * sizeof(boolean_T));
            memset(&iC[0], 0, 96U * sizeof(int32_T));
            ColdReset = true;
          }
        } else {
          for (i = 0; i < nA; i++) {
            Rhs[i + 4] = b[iC[i] - 1];
            for (r_tmp = i + 1; r_tmp <= nA; r_tmp++) {
              U_tmp_0 = ((i << 2) + r_tmp) - 1;
              U[U_tmp_0] = 0.0;
              for (iSave = 0; iSave < nA; iSave++) {
                U_tmp = iSave << 2;
                U[U_tmp_0] += RLinv[(U_tmp + r_tmp) - 1] * RLinv[U_tmp + i];
              }

              U[i + ((r_tmp - 1) << 2)] = U[U_tmp_0];
            }
          }

          for (i = 0; i < 4; i++) {
            Opt[i] = ((b_H[i + 4] * Rhs[1] + b_H[i] * Rhs[0]) + b_H[i + 8] *
                      Rhs[2]) + b_H[i + 12] * Rhs[3];
            for (r_tmp = 0; r_tmp < nA; r_tmp++) {
              Opt[i] += D[(r_tmp << 2) + i] * Rhs[r_tmp + 4];
            }
          }

          Xnorm0 = -1.0E-12;
          i = -1;
          for (r_tmp = 0; r_tmp < nA; r_tmp++) {
            iSave = r_tmp << 2;
            Opt[r_tmp + 4] = ((D[iSave + 1] * Rhs[1] + D[iSave] * Rhs[0]) +
                              D[iSave + 2] * Rhs[2]) + D[iSave + 3] * Rhs[3];
            for (iSave = 0; iSave < nA; iSave++) {
              Opt[r_tmp + 4] += U[(iSave << 2) + r_tmp] * Rhs[iSave + 4];
            }

            cMin = Opt[r_tmp + 4];
            lambda[iC[r_tmp] - 1] = cMin;
            if ((cMin < Xnorm0) && (r_tmp + 1 <= nA)) {
              i = r_tmp;
              Xnorm0 = cMin;
            }
          }

          if (i + 1 <= 0) {
            DualFeasible = true;
            x[0] = Opt[0];
            x[1] = Opt[1];
            x[2] = Opt[2];
            x[3] = Opt[3];
          } else {
            (*status)++;
            if (tmp <= 5) {
              r_tmp = 5;
            } else {
              r_tmp = tmp;
            }

            if (*status > r_tmp) {
              nA = 0;
              memset(&iA[0], 0, 96U * sizeof(boolean_T));
              memset(&iC[0], 0, 96U * sizeof(int32_T));
              ColdReset = true;
            } else {
              lambda[iC[i] - 1] = 0.0;
              accsubsystem_1_DropConstraint(i + 1, iA, &nA, iC);
            }
          }
        }
      } else {
        if (nA <= 0) {
          memset(&lambda[0], 0, 96U * sizeof(real_T));
          Xnorm0 = f[1];
          cMin = f[0];
          cVal = f[2];
          z_idx_2 = f[3];
          for (tmp = 0; tmp < 4; tmp++) {
            x[tmp] = ((-b_Hinv[tmp + 4] * Xnorm0 + -b_Hinv[tmp] * cMin) +
                      -b_Hinv[tmp + 8] * cVal) + -b_Hinv[tmp + 12] * z_idx_2;
          }
        }

        exitg3 = 1;
      }
    } while (exitg3 == 0);

    if (exitg3 == 1) {
      guard1 = true;
    }
  } else {
    Xnorm0 = f[1];
    cMin = f[0];
    cVal = f[2];
    z_idx_2 = f[3];
    for (tmp = 0; tmp < 4; tmp++) {
      x[tmp] = ((-b_Hinv[tmp + 4] * Xnorm0 + -b_Hinv[tmp] * cMin) + -b_Hinv[tmp
                + 8] * cVal) + -b_Hinv[tmp + 12] * z_idx_2;
    }

    guard1 = true;
  }

  if (guard1) {
    Xnorm0 = accsubsystem_1_norm(x);
    exitg2 = false;
    while (!exitg2 && (*status <= maxiter)) {
      cMin = -FeasTol;
      tmp = -1;
      for (i = 0; i < 96; i++) {
        if (!cTolComputed) {
          b_x[0] = fabs(b_Ac[i] * x[0]);
          b_x[1] = fabs(b_Ac[i + 96] * x[1]);
          b_x[2] = fabs(b_Ac[i + 192] * x[2]);
          b_x[3] = fabs(b_Ac[i + 288] * x[3]);
          cVal = accsubsystem_1_maximum(b_x);
          if ((cTol[i] >= cVal) || rtIsNaN(cVal)) {
          } else {
            cTol[i] = cVal;
          }
        }

        if (!iA[i]) {
          cVal = ((((b_Ac[i + 96] * x[1] + b_Ac[i] * x[0]) + b_Ac[i + 192] * x[2])
                   + b_Ac[i + 288] * x[3]) - b[i]) / cTol[i];
          if (cVal < cMin) {
            cMin = cVal;
            tmp = i;
          }
        }
      }

      cTolComputed = true;
      if (tmp + 1 <= 0) {
        exitg2 = true;
      } else if (*status == maxiter) {
        *status = 0;
        exitg2 = true;
      } else {
        do {
          exitg1 = 0;
          if ((tmp + 1 > 0) && (*status < maxiter)) {
            guard2 = false;
            if (nA == 0) {
              cMin = 0.0;
              cVal = 0.0;
              z_idx_2 = 0.0;
              z_idx_3 = 0.0;
              for (r_tmp = 0; r_tmp < 4; r_tmp++) {
                t1 = b_Ac[96 * r_tmp + tmp];
                i = r_tmp << 2;
                cMin += b_Hinv[i] * t1;
                cVal += b_Hinv[i + 1] * t1;
                z_idx_2 += b_Hinv[i + 2] * t1;
                z_idx_3 += b_Hinv[i + 3] * t1;
              }

              guard2 = true;
            } else {
              cMin = accsubsystem_1_KWIKfactor(b_Ac, iC, nA, b_Linv, RLinv, D,
                b_H, accsubsystem_1_degrees);
              if (cMin <= 0.0) {
                *status = -2;
                exitg1 = 1;
              } else {
                for (r_tmp = 0; r_tmp < 16; r_tmp++) {
                  U[r_tmp] = -b_H[r_tmp];
                }

                cMin = 0.0;
                cVal = 0.0;
                z_idx_2 = 0.0;
                z_idx_3 = 0.0;
                for (r_tmp = 0; r_tmp < 4; r_tmp++) {
                  t1 = b_Ac[96 * r_tmp + tmp];
                  i = r_tmp << 2;
                  cMin += U[i] * t1;
                  cVal += U[i + 1] * t1;
                  z_idx_2 += U[i + 2] * t1;
                  z_idx_3 += U[i + 3] * t1;
                }

                for (i = 0; i < nA; i++) {
                  r_tmp = i << 2;
                  r[i] = ((D[r_tmp + 1] * b_Ac[tmp + 96] + D[r_tmp] * b_Ac[tmp])
                          + D[r_tmp + 2] * b_Ac[tmp + 192]) + D[r_tmp + 3] *
                    b_Ac[tmp + 288];
                }

                guard2 = true;
              }
            }

            if (guard2) {
              i = 0;
              t1 = 0.0;
              DualFeasible = true;
              ColdReset = true;
              if (nA > 0) {
                r_tmp = 0;
                exitg4 = false;
                while (!exitg4 && (r_tmp <= nA - 1)) {
                  if (r[r_tmp] >= 1.0E-12) {
                    ColdReset = false;
                    exitg4 = true;
                  } else {
                    r_tmp++;
                  }
                }
              }

              if ((nA != 0) && !ColdReset) {
                for (r_tmp = 0; r_tmp < nA; r_tmp++) {
                  rVal = r[r_tmp];
                  if (rVal > 1.0E-12) {
                    rVal = lambda[iC[r_tmp] - 1] / rVal;
                    if ((i == 0) || (rVal < rMin)) {
                      rMin = rVal;
                      i = r_tmp + 1;
                    }
                  }
                }

                if (i > 0) {
                  t1 = rMin;
                  DualFeasible = false;
                }
              }

              rVal = b_Ac[tmp + 96];
              t = b_Ac[tmp + 192];
              z_tmp = b_Ac[tmp + 288];
              z = ((rVal * cVal + cMin * b_Ac[tmp]) + t * z_idx_2) + z_tmp *
                z_idx_3;
              if (z <= 0.0) {
                rVal = 0.0;
                ColdReset = true;
              } else {
                rVal = (b[tmp] - (((rVal * x[1] + b_Ac[tmp] * x[0]) + t * x[2])
                                  + z_tmp * x[3])) / z;
                ColdReset = false;
              }

              if (DualFeasible && ColdReset) {
                *status = -1;
                exitg1 = 1;
              } else {
                if (ColdReset) {
                  t = t1;
                } else if (DualFeasible) {
                  t = rVal;
                } else if (t1 < rVal) {
                  t = t1;
                } else {
                  t = rVal;
                }

                for (r_tmp = 0; r_tmp < nA; r_tmp++) {
                  iSave = iC[r_tmp];
                  lambda[iSave - 1] -= t * r[r_tmp];
                  if ((iSave <= 96) && (lambda[iSave - 1] < 0.0)) {
                    lambda[iSave - 1] = 0.0;
                  }
                }

                lambda[tmp] += t;
                frexp(1.0, &exponent);
                if (fabs(t - t1) < 2.220446049250313E-16) {
                  accsubsystem_1_DropConstraint(i, iA, &nA, iC);
                }

                if (!ColdReset) {
                  x[0] += t * cMin;
                  x[1] += t * cVal;
                  x[2] += t * z_idx_2;
                  x[3] += t * z_idx_3;
                  frexp(1.0, &b_exponent);
                  if (fabs(t - rVal) < 2.220446049250313E-16) {
                    if (nA == accsubsystem_1_degrees) {
                      *status = -1;
                      exitg1 = 1;
                    } else {
                      nA++;
                      iC[nA - 1] = tmp + 1;
                      i = nA - 1;
                      exitg4 = false;
                      while (!exitg4 && (i + 1 > 1)) {
                        r_tmp = iC[i - 1];
                        if (iC[i] > r_tmp) {
                          exitg4 = true;
                        } else {
                          iSave = iC[i];
                          iC[i] = r_tmp;
                          iC[i - 1] = iSave;
                          i--;
                        }
                      }

                      iA[tmp] = true;
                      tmp = -1;
                      (*status)++;
                    }
                  } else {
                    (*status)++;
                  }
                } else {
                  (*status)++;
                }
              }
            }
          } else {
            cMin = accsubsystem_1_norm(x);
            if (fabs(cMin - Xnorm0) > 0.001) {
              Xnorm0 = cMin;
              for (tmp = 0; tmp < 96; tmp++) {
                cMin = fabs(b[tmp]);
                if (cMin >= 1.0) {
                  cTol[tmp] = cMin;
                } else {
                  cTol[tmp] = 1.0;
                }
              }

              cTolComputed = false;
            }

            exitg1 = 2;
          }
        } while (exitg1 == 0);

        if (exitg1 == 1) {
          exitg2 = true;
        }
      }
    }
  }
}

/* Model step function */
void accsubsystem_1_step(void)
{
  real_T Bc[96];
  real_T b_Mv[96];
  real_T b_Mx[96];
  real_T vseq[62];
  real_T rseq[60];
  real_T f[4];
  real_T rtb_xest[4];
  real_T xk[4];
  real_T rtb_TmpSignalConversionAtSFun_d[2];
  real_T rtb_TmpSignalConversionAtSFun_g[2];
  real_T rtb_TmpSignalConversionAtSFun_i[2];
  real_T ymax_incr[2];
  real_T ymin_incr[2];
  real_T rtb_xest_0;
  real_T rtb_y;
  real_T rtb_y_cs;
  real_T rtb_y_e;
  real_T rtb_y_fb;
  real_T rtb_y_gf;
  real_T rtb_y_j;
  real_T rtb_y_n;
  int32_T i;
  int32_T ii;
  uint8_T b_Mrows;
  boolean_T rtb_iAout[96];
  boolean_T ymax_incr_flag[2];
  boolean_T ymin_incr_flag[2];
  boolean_T b_Del_Save_Flag0;
  boolean_T umax_incr_flag;
  boolean_T umin_incr_flag;
  static const real_T a[8] = { -3.857254728744719E-18, 0.9009338063157754,
    -0.003098712804056809, -1.8018670797387843, 4.029097276714929,
    -0.001385786494524009, 0.0, 1.0 };

  static const real_T b_a[8] = { -0.014720277565527644, 0.05309352350095655,
    0.04089357637583845, 0.0748190402824622, -0.02539480596023034,
    -0.07345140698969144, -0.008536577743686952, 0.055502688090371274 };

  static const real_T b_Mx_0[384] = { -0.7376222137183269, -0.6039139905246534,
    -0.4944429562565782, -0.40481565393005137, -0.33143502519990614,
    -0.27135604777833855, -0.22216754134982342, -0.18189539843882407,
    -0.14892335654523747, -0.12192813185518253, -0.09982631121518452,
    -0.08173087095820446, -0.06691557752932953, -0.0547858411832355,
    -0.04485485300996055, -0.03672404758404663, -0.030067107134557586,
    -0.02461686526715214, -0.020154584638594132, -0.016501178259129543,
    -0.013510022102770596, -0.011061070570300993, -0.009056038637870677,
    -0.007414457333886603, -0.006070444236636988, -0.004970059381379139,
    -0.004069140460158274, -0.0033315304333249125, -0.002727626420577764,
    -0.0022331916334344757, -0.08165579629872391, 0.7376222137183269,
    -0.14850990789556037, 0.6039139905246534, -0.20324542502959766,
    0.4944429562565782, -0.24805907619286074, 0.40481565393005137,
    -0.284749390557933, 0.33143502519990614, -0.31478887926871657,
    0.27135604777833855, -0.3393831324829738, 0.22216754134982342,
    -0.35951920393847314, 0.18189539843882407, -0.3760052248852661,
    0.14892335654523747, -0.3895028372302933, 0.12192813185518253,
    -0.40055374755029205, 0.09982631121518452, -0.40960146767878175,
    0.08173087095820446, -0.41700911439321886, 0.06691557752932953,
    -0.42307398256626555, 0.0547858411832355, -0.4280394766529027,
    0.04485485300996055, -0.43210487936585934, 0.03672404758404663,
    -0.43543334959060354, 0.030067107134557586, -0.4381584705243059,
    0.02461686526715214, -0.44038961083858463, 0.020154584638594132,
    -0.4422163140283166, 0.016501178259129543, -0.4437118921064958,
    0.013510022102770596, -0.4449363678727303, 0.011061070570300993,
    -0.44593888383894514, 0.009056038637870677, -0.4467596744909369,
    0.007414457333886603, -0.4474316810395614, 0.006070444236636988,
    -0.44798187346719, 0.004970059381379139, -0.4484323329278001,
    0.004069140460158274, -0.44880113794121645, 0.0033315304333249125,
    -0.44910308994758974, 0.002727626420577764, -0.44935030734116105,
    0.0022331916334344757, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.8835228518882399,
    1.950376943713328, 2.0051124446596265, 2.04992608256949, 2.0866163860835965,
    2.1166558659103605, 2.141250111850998, 2.161386177351362, 2.1778721934225023,
    2.1913698017756826, 2.2024207088274332, 2.211468426280108,
    2.2188760708037734, 2.2249409371831677, 2.2299064298012867,
    2.2339718313119223, 2.2373003005522896, 2.240025420680052, 2.242256560334483,
    2.2440832629839775, 2.245578840619848, 2.2468033160239504, 2.247805831693677,
    2.248626622102925, 2.249298628452807, 2.2498488207177196, 2.2502992800451094,
    2.250668084949454, 2.250970036866527, 2.2512172541869853,
    0.18130678608856085, -1.8835228518882399, 0.37311312514336237,
    -1.950376943713328, 0.5709787596375584, -2.0051124446596265,
    0.773805325649972, -2.04992608256949, 0.980693558860264, -2.0866163860835965,
    1.1909072039142274, -2.1166558659103605, 1.403843465911254,
    -2.141250111850998, 1.6190088181284177, -2.161386177351362,
    1.835999195060193, -2.1778721934225023, 2.054483775850948,
    -2.1913698017756826, 2.274191707292418, -2.2024207088274332,
    2.494901233533426, -2.211468426280108, 2.7164307962389387,
    -2.2188760708037734, 2.9386317480165873, -2.2249409371831677,
    3.161382386674873, -2.2299064298012867, 3.3845830708869005,
    -2.2339718313119223, 3.608152221234062, -2.2373003005522896,
    3.8320230461375266, -2.240025420680052, 4.056140861277657,
    -2.242256560334483, 4.280460894920255, -2.2440832629839775,
    4.504946491069665, -2.245578840619848, 4.729567638334959,
    -2.2468033160239504, 4.954299765467442, -2.247805831693677,
    5.179122755230163, -2.248626622102925, 5.404020137022568, -2.249298628452807,
    5.628978425857457, -2.2498488207177196, 5.853986581161107,
    -2.2502992800451094, 6.07903556367628, -2.250668084949454,
    6.3041179726850896, -2.250970036866527, 6.529227748992205,
    -2.2512172541869853, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0014485866130882763,
    0.0015000030014537854, 0.0015420991798208287, 0.0015765646156369831,
    0.001604782527857904, 0.001627885400380827, 0.0016468004325997842,
    0.0016622867511729056, 0.0016749658764406827, 0.0016853466662195397,
    0.0016938457380527275, 0.0017008041895351773, 0.00170650128775766,
    0.0017111656772757125, 0.0017149845564184765, 0.0017181111902149456,
    0.0017206710614577278, 0.0017227669067681134, 0.0017244828397774206,
    0.001725887726902362, 0.0017270379511961549, 0.0017279796751984203,
    0.0017287506935999867, 0.0017293819500765382, 0.0017298987791669704,
    0.0017303219230373928, 0.001730668363937084, 0.001730952005755785,
    0.0017311842320356144, 0.0017313743628325838, 4.029239099967462,
    -0.0014485866130882763, 4.0293866150850945, -0.0015000030014537854,
    4.029538790307726, -0.0015420991798208287, 4.029694780901634,
    -0.0015765646156369831, 4.0298538952573395, -0.001604782527857904,
    4.030015567132893, -0.001627885400380827, 4.030179332928599,
    -0.0016468004325997842, 4.030344813081128, -0.0016622867511729056,
    4.03051169683031, -0.0016749658764406827, 4.030679729747236,
    -0.0016853466662195397, 4.030848703523135, -0.0016938457380527275,
    4.031018447609208, -0.0017008041895351773, 4.031188822371912,
    -0.00170650128775766, 4.0313597134889685, -0.0017111656772757125,
    4.031531027361213, -0.0017149845564184765, 4.03170268735613,
    -0.0017181111902149456, 4.031874630732324, -0.0017206710614577278,
    4.0320468061214845, -0.0017227669067681134, 4.032219171466795,
    -0.0017244828397774206, 4.0323916923350485, -0.001725887726902362,
    4.032564340534717, -0.0017270379511961549, 4.032737092984531,
    -0.0017279796751984203, 4.032909930787145, -0.0017287506935999867,
    4.0330828384707225, -0.0017293819500765382, 4.033255803367993,
    -0.0017298987791669704, 4.0334288151078725, -0.0017303219230373928,
    4.0336018651992385, -0.001730668363937084, 4.033774946690144,
    -0.001730952005755785, 4.03394805388882, -0.0017311842320356144,
    4.034121182135237, -0.0017313743628325838, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0,
    -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0,
    -1.0, -1.0, -1.0, -1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0,
    1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0,
    1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  static const real_T b_Mlim[96] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.37499999999999994, 0.37499999999999994, 0.37499999999999994, 0.625, 0.625,
    0.625 };

  static const real_T b_Mu1[96] = { -0.02134558755325669, -0.08013680459902119,
    -0.1695859100786657, -0.28413557164356146, -0.41923583039481116,
    -0.5711614950566466, -0.7368626369704987, -0.913842185748903,
    -1.100055713073042, -1.2938293826058362, -1.4937927730624996,
    -1.6988238783925047, -1.9080040777371454, -2.1205812679489804,
    -2.335939679051712, -2.5535751612289235, -2.7730749515217563,
    -2.994101108202061, -3.2163769479842537, -3.4396759417535634,
    -3.663812623157261, -3.8886351451887045, -4.114019186033794,
    -4.339862959600047, -4.566083130483313, -4.7926114694253945,
    -5.019392115034344, -5.246379331870664, -5.473535674923535,
    -5.700830486811046, -0.0007232176193835032, 0.02134558755325669,
    -0.005515643284535797, 0.08013680459902119, -0.017771147524770776,
    0.1695859100786657, -0.04026839651440278, 0.28413557164356146,
    -0.07528236970288049, 0.41923583039481116, -0.12467566272808799,
    0.5711614950566466, -0.18997323991930987, 0.7368626369704987,
    -0.27242363647027834, 0.913842185748903, -0.3730490665404021,
    1.100055713073042, -0.49268644829822084, 1.2938293826058362,
    -0.6320209923861277, 1.4937927730624996, -0.7916137018293865,
    1.6988238783925047, -0.9719238870573501, 1.9080040777371454,
    -1.1733275996437393, 2.1205812679489804, -1.396132724576703,
    2.335939679051712, -1.6405913367644491, 2.5535751612289235,
    -1.9069098176864074, 2.7730749515217563, -2.195257138206652,
    2.994101108202061, -2.5057716399679757, 3.2163769479842537,
    -2.8385665875277635, 3.4396759417535634, -3.1937347140623804,
    3.663812623157261, -3.571351943075147, 3.8886351451887045,
    -3.971480435473113, 4.114019186033794, -4.39417108430252, 4.339862959600047,
    -4.839465557265442, 4.566083130483313, -5.307397968990981,
    4.7926114694253945, -5.797996250175108, 5.019392115034344,
    -6.311283268537571, 5.246379331870664, -6.847277746583783, 5.473535674923535,
    -7.405995013004697, 5.700830486811046, -1.0, -1.0, -1.0, 1.0, 1.0, 1.0 };

  static const real_T b_Mv_0[5952] = { -0.0, -0.0, -0.0, -0.0,
    6.776263578034403E-21, 2.0328790734103208E-20, 2.0328790734103208E-20,
    1.3552527156068805E-20, 1.3552527156068805E-20, 6.776263578034403E-21, -0.0,
    -0.0, -6.776263578034403E-21, -6.776263578034403E-21, -6.776263578034403E-21,
    -1.3552527156068805E-20, -1.3552527156068805E-20, -2.0328790734103208E-20,
    -1.3552527156068805E-20, -1.3552527156068805E-20, -1.3552527156068805E-20,
    -1.3552527156068805E-20, -1.3552527156068805E-20, -2.710505431213761E-20,
    -2.710505431213761E-20, -2.710505431213761E-20, -3.3881317890172014E-20,
    -4.0657581468206416E-20, -4.0657581468206416E-20, -4.0657581468206416E-20,
    0.09999999999999999, 0.0, 0.09999999999999998, 0.0, 0.09999999999999998, 0.0,
    0.09999999999999996, 0.0, 0.09999999999999998, -6.776263578034403E-21,
    0.09999999999999999, -2.0328790734103208E-20, 0.09999999999999998,
    -2.0328790734103208E-20, 0.09999999999999996, -1.3552527156068805E-20,
    0.09999999999999998, -1.3552527156068805E-20, 0.09999999999999996,
    -6.776263578034403E-21, 0.09999999999999998, 0.0, 0.09999999999999998, 0.0,
    0.09999999999999995, 6.776263578034403E-21, 0.09999999999999995,
    6.776263578034403E-21, 0.09999999999999994, 6.776263578034403E-21,
    0.09999999999999996, 1.3552527156068805E-20, 0.09999999999999995,
    1.3552527156068805E-20, 0.09999999999999995, 2.0328790734103208E-20,
    0.09999999999999995, 1.3552527156068805E-20, 0.09999999999999994,
    1.3552527156068805E-20, 0.09999999999999995, 1.3552527156068805E-20,
    0.09999999999999995, 1.3552527156068805E-20, 0.09999999999999995,
    1.3552527156068805E-20, 0.09999999999999994, 2.710505431213761E-20,
    0.09999999999999992, 2.710505431213761E-20, 0.09999999999999994,
    2.710505431213761E-20, 0.09999999999999992, 3.3881317890172014E-20,
    0.09999999999999992, 4.0657581468206416E-20, 0.09999999999999992,
    4.0657581468206416E-20, 0.09999999999999992, 4.0657581468206416E-20, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 6.776263578034403E-21,
    2.0328790734103208E-20, 2.0328790734103208E-20, 1.3552527156068805E-20,
    1.3552527156068805E-20, 6.776263578034403E-21, -0.0, -0.0,
    -6.776263578034403E-21, -6.776263578034403E-21, -6.776263578034403E-21,
    -1.3552527156068805E-20, -1.3552527156068805E-20, -2.0328790734103208E-20,
    -1.3552527156068805E-20, -1.3552527156068805E-20, -1.3552527156068805E-20,
    -1.3552527156068805E-20, -1.3552527156068805E-20, -2.710505431213761E-20,
    -2.710505431213761E-20, -2.710505431213761E-20, -3.3881317890172014E-20,
    -4.0657581468206416E-20, -4.0657581468206416E-20, 0.0, 0.0,
    0.09999999999999999, 0.0, 0.09999999999999998, 0.0, 0.09999999999999998, 0.0,
    0.09999999999999996, 0.0, 0.09999999999999998, -6.776263578034403E-21,
    0.09999999999999999, -2.0328790734103208E-20, 0.09999999999999998,
    -2.0328790734103208E-20, 0.09999999999999996, -1.3552527156068805E-20,
    0.09999999999999998, -1.3552527156068805E-20, 0.09999999999999996,
    -6.776263578034403E-21, 0.09999999999999998, 0.0, 0.09999999999999998, 0.0,
    0.09999999999999995, 6.776263578034403E-21, 0.09999999999999995,
    6.776263578034403E-21, 0.09999999999999994, 6.776263578034403E-21,
    0.09999999999999996, 1.3552527156068805E-20, 0.09999999999999995,
    1.3552527156068805E-20, 0.09999999999999995, 2.0328790734103208E-20,
    0.09999999999999995, 1.3552527156068805E-20, 0.09999999999999994,
    1.3552527156068805E-20, 0.09999999999999995, 1.3552527156068805E-20,
    0.09999999999999995, 1.3552527156068805E-20, 0.09999999999999995,
    1.3552527156068805E-20, 0.09999999999999994, 2.710505431213761E-20,
    0.09999999999999992, 2.710505431213761E-20, 0.09999999999999994,
    2.710505431213761E-20, 0.09999999999999992, 3.3881317890172014E-20,
    0.09999999999999992, 4.0657581468206416E-20, 0.09999999999999992,
    4.0657581468206416E-20, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    6.776263578034403E-21, 2.0328790734103208E-20, 2.0328790734103208E-20,
    1.3552527156068805E-20, 1.3552527156068805E-20, 6.776263578034403E-21, -0.0,
    -0.0, -6.776263578034403E-21, -6.776263578034403E-21, -6.776263578034403E-21,
    -1.3552527156068805E-20, -1.3552527156068805E-20, -2.0328790734103208E-20,
    -1.3552527156068805E-20, -1.3552527156068805E-20, -1.3552527156068805E-20,
    -1.3552527156068805E-20, -1.3552527156068805E-20, -2.710505431213761E-20,
    -2.710505431213761E-20, -2.710505431213761E-20, -3.3881317890172014E-20,
    -4.0657581468206416E-20, 0.0, 0.0, 0.0, 0.0, 0.09999999999999999, 0.0,
    0.09999999999999998, 0.0, 0.09999999999999998, 0.0, 0.09999999999999996, 0.0,
    0.09999999999999998, -6.776263578034403E-21, 0.09999999999999999,
    -2.0328790734103208E-20, 0.09999999999999998, -2.0328790734103208E-20,
    0.09999999999999996, -1.3552527156068805E-20, 0.09999999999999998,
    -1.3552527156068805E-20, 0.09999999999999996, -6.776263578034403E-21,
    0.09999999999999998, 0.0, 0.09999999999999998, 0.0, 0.09999999999999995,
    6.776263578034403E-21, 0.09999999999999995, 6.776263578034403E-21,
    0.09999999999999994, 6.776263578034403E-21, 0.09999999999999996,
    1.3552527156068805E-20, 0.09999999999999995, 1.3552527156068805E-20,
    0.09999999999999995, 2.0328790734103208E-20, 0.09999999999999995,
    1.3552527156068805E-20, 0.09999999999999994, 1.3552527156068805E-20,
    0.09999999999999995, 1.3552527156068805E-20, 0.09999999999999995,
    1.3552527156068805E-20, 0.09999999999999995, 1.3552527156068805E-20,
    0.09999999999999994, 2.710505431213761E-20, 0.09999999999999992,
    2.710505431213761E-20, 0.09999999999999994, 2.710505431213761E-20,
    0.09999999999999992, 3.3881317890172014E-20, 0.09999999999999992,
    4.0657581468206416E-20, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    6.776263578034403E-21, 2.0328790734103208E-20, 2.0328790734103208E-20,
    1.3552527156068805E-20, 1.3552527156068805E-20, 6.776263578034403E-21, -0.0,
    -0.0, -6.776263578034403E-21, -6.776263578034403E-21, -6.776263578034403E-21,
    -1.3552527156068805E-20, -1.3552527156068805E-20, -2.0328790734103208E-20,
    -1.3552527156068805E-20, -1.3552527156068805E-20, -1.3552527156068805E-20,
    -1.3552527156068805E-20, -1.3552527156068805E-20, -2.710505431213761E-20,
    -2.710505431213761E-20, -2.710505431213761E-20, -3.3881317890172014E-20, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.09999999999999999, 0.0, 0.09999999999999998, 0.0,
    0.09999999999999998, 0.0, 0.09999999999999996, 0.0, 0.09999999999999998,
    -6.776263578034403E-21, 0.09999999999999999, -2.0328790734103208E-20,
    0.09999999999999998, -2.0328790734103208E-20, 0.09999999999999996,
    -1.3552527156068805E-20, 0.09999999999999998, -1.3552527156068805E-20,
    0.09999999999999996, -6.776263578034403E-21, 0.09999999999999998, 0.0,
    0.09999999999999998, 0.0, 0.09999999999999995, 6.776263578034403E-21,
    0.09999999999999995, 6.776263578034403E-21, 0.09999999999999994,
    6.776263578034403E-21, 0.09999999999999996, 1.3552527156068805E-20,
    0.09999999999999995, 1.3552527156068805E-20, 0.09999999999999995,
    2.0328790734103208E-20, 0.09999999999999995, 1.3552527156068805E-20,
    0.09999999999999994, 1.3552527156068805E-20, 0.09999999999999995,
    1.3552527156068805E-20, 0.09999999999999995, 1.3552527156068805E-20,
    0.09999999999999995, 1.3552527156068805E-20, 0.09999999999999994,
    2.710505431213761E-20, 0.09999999999999992, 2.710505431213761E-20,
    0.09999999999999994, 2.710505431213761E-20, 0.09999999999999992,
    3.3881317890172014E-20, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    6.776263578034403E-21, 2.0328790734103208E-20, 2.0328790734103208E-20,
    1.3552527156068805E-20, 1.3552527156068805E-20, 6.776263578034403E-21, -0.0,
    -0.0, -6.776263578034403E-21, -6.776263578034403E-21, -6.776263578034403E-21,
    -1.3552527156068805E-20, -1.3552527156068805E-20, -2.0328790734103208E-20,
    -1.3552527156068805E-20, -1.3552527156068805E-20, -1.3552527156068805E-20,
    -1.3552527156068805E-20, -1.3552527156068805E-20, -2.710505431213761E-20,
    -2.710505431213761E-20, -2.710505431213761E-20, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.09999999999999999, 0.0, 0.09999999999999998, 0.0,
    0.09999999999999998, 0.0, 0.09999999999999996, 0.0, 0.09999999999999998,
    -6.776263578034403E-21, 0.09999999999999999, -2.0328790734103208E-20,
    0.09999999999999998, -2.0328790734103208E-20, 0.09999999999999996,
    -1.3552527156068805E-20, 0.09999999999999998, -1.3552527156068805E-20,
    0.09999999999999996, -6.776263578034403E-21, 0.09999999999999998, 0.0,
    0.09999999999999998, 0.0, 0.09999999999999995, 6.776263578034403E-21,
    0.09999999999999995, 6.776263578034403E-21, 0.09999999999999994,
    6.776263578034403E-21, 0.09999999999999996, 1.3552527156068805E-20,
    0.09999999999999995, 1.3552527156068805E-20, 0.09999999999999995,
    2.0328790734103208E-20, 0.09999999999999995, 1.3552527156068805E-20,
    0.09999999999999994, 1.3552527156068805E-20, 0.09999999999999995,
    1.3552527156068805E-20, 0.09999999999999995, 1.3552527156068805E-20,
    0.09999999999999995, 1.3552527156068805E-20, 0.09999999999999994,
    2.710505431213761E-20, 0.09999999999999992, 2.710505431213761E-20,
    0.09999999999999994, 2.710505431213761E-20, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 6.776263578034403E-21,
    2.0328790734103208E-20, 2.0328790734103208E-20, 1.3552527156068805E-20,
    1.3552527156068805E-20, 6.776263578034403E-21, -0.0, -0.0,
    -6.776263578034403E-21, -6.776263578034403E-21, -6.776263578034403E-21,
    -1.3552527156068805E-20, -1.3552527156068805E-20, -2.0328790734103208E-20,
    -1.3552527156068805E-20, -1.3552527156068805E-20, -1.3552527156068805E-20,
    -1.3552527156068805E-20, -1.3552527156068805E-20, -2.710505431213761E-20,
    -2.710505431213761E-20, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.09999999999999999, 0.0, 0.09999999999999998, 0.0, 0.09999999999999998, 0.0,
    0.09999999999999996, 0.0, 0.09999999999999998, -6.776263578034403E-21,
    0.09999999999999999, -2.0328790734103208E-20, 0.09999999999999998,
    -2.0328790734103208E-20, 0.09999999999999996, -1.3552527156068805E-20,
    0.09999999999999998, -1.3552527156068805E-20, 0.09999999999999996,
    -6.776263578034403E-21, 0.09999999999999998, 0.0, 0.09999999999999998, 0.0,
    0.09999999999999995, 6.776263578034403E-21, 0.09999999999999995,
    6.776263578034403E-21, 0.09999999999999994, 6.776263578034403E-21,
    0.09999999999999996, 1.3552527156068805E-20, 0.09999999999999995,
    1.3552527156068805E-20, 0.09999999999999995, 2.0328790734103208E-20,
    0.09999999999999995, 1.3552527156068805E-20, 0.09999999999999994,
    1.3552527156068805E-20, 0.09999999999999995, 1.3552527156068805E-20,
    0.09999999999999995, 1.3552527156068805E-20, 0.09999999999999995,
    1.3552527156068805E-20, 0.09999999999999994, 2.710505431213761E-20,
    0.09999999999999992, 2.710505431213761E-20, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 6.776263578034403E-21,
    2.0328790734103208E-20, 2.0328790734103208E-20, 1.3552527156068805E-20,
    1.3552527156068805E-20, 6.776263578034403E-21, -0.0, -0.0,
    -6.776263578034403E-21, -6.776263578034403E-21, -6.776263578034403E-21,
    -1.3552527156068805E-20, -1.3552527156068805E-20, -2.0328790734103208E-20,
    -1.3552527156068805E-20, -1.3552527156068805E-20, -1.3552527156068805E-20,
    -1.3552527156068805E-20, -1.3552527156068805E-20, -2.710505431213761E-20,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.09999999999999999, 0.0, 0.09999999999999998, 0.0, 0.09999999999999998, 0.0,
    0.09999999999999996, 0.0, 0.09999999999999998, -6.776263578034403E-21,
    0.09999999999999999, -2.0328790734103208E-20, 0.09999999999999998,
    -2.0328790734103208E-20, 0.09999999999999996, -1.3552527156068805E-20,
    0.09999999999999998, -1.3552527156068805E-20, 0.09999999999999996,
    -6.776263578034403E-21, 0.09999999999999998, 0.0, 0.09999999999999998, 0.0,
    0.09999999999999995, 6.776263578034403E-21, 0.09999999999999995,
    6.776263578034403E-21, 0.09999999999999994, 6.776263578034403E-21,
    0.09999999999999996, 1.3552527156068805E-20, 0.09999999999999995,
    1.3552527156068805E-20, 0.09999999999999995, 2.0328790734103208E-20,
    0.09999999999999995, 1.3552527156068805E-20, 0.09999999999999994,
    1.3552527156068805E-20, 0.09999999999999995, 1.3552527156068805E-20,
    0.09999999999999995, 1.3552527156068805E-20, 0.09999999999999995,
    1.3552527156068805E-20, 0.09999999999999994, 2.710505431213761E-20, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    6.776263578034403E-21, 2.0328790734103208E-20, 2.0328790734103208E-20,
    1.3552527156068805E-20, 1.3552527156068805E-20, 6.776263578034403E-21, -0.0,
    -0.0, -6.776263578034403E-21, -6.776263578034403E-21, -6.776263578034403E-21,
    -1.3552527156068805E-20, -1.3552527156068805E-20, -2.0328790734103208E-20,
    -1.3552527156068805E-20, -1.3552527156068805E-20, -1.3552527156068805E-20,
    -1.3552527156068805E-20, -1.3552527156068805E-20, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.09999999999999999, 0.0,
    0.09999999999999998, 0.0, 0.09999999999999998, 0.0, 0.09999999999999996, 0.0,
    0.09999999999999998, -6.776263578034403E-21, 0.09999999999999999,
    -2.0328790734103208E-20, 0.09999999999999998, -2.0328790734103208E-20,
    0.09999999999999996, -1.3552527156068805E-20, 0.09999999999999998,
    -1.3552527156068805E-20, 0.09999999999999996, -6.776263578034403E-21,
    0.09999999999999998, 0.0, 0.09999999999999998, 0.0, 0.09999999999999995,
    6.776263578034403E-21, 0.09999999999999995, 6.776263578034403E-21,
    0.09999999999999994, 6.776263578034403E-21, 0.09999999999999996,
    1.3552527156068805E-20, 0.09999999999999995, 1.3552527156068805E-20,
    0.09999999999999995, 2.0328790734103208E-20, 0.09999999999999995,
    1.3552527156068805E-20, 0.09999999999999994, 1.3552527156068805E-20,
    0.09999999999999995, 1.3552527156068805E-20, 0.09999999999999995,
    1.3552527156068805E-20, 0.09999999999999995, 1.3552527156068805E-20, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, 6.776263578034403E-21, 2.0328790734103208E-20, 2.0328790734103208E-20,
    1.3552527156068805E-20, 1.3552527156068805E-20, 6.776263578034403E-21, -0.0,
    -0.0, -6.776263578034403E-21, -6.776263578034403E-21, -6.776263578034403E-21,
    -1.3552527156068805E-20, -1.3552527156068805E-20, -2.0328790734103208E-20,
    -1.3552527156068805E-20, -1.3552527156068805E-20, -1.3552527156068805E-20,
    -1.3552527156068805E-20, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.09999999999999999, 0.0, 0.09999999999999998,
    0.0, 0.09999999999999998, 0.0, 0.09999999999999996, 0.0, 0.09999999999999998,
    -6.776263578034403E-21, 0.09999999999999999, -2.0328790734103208E-20,
    0.09999999999999998, -2.0328790734103208E-20, 0.09999999999999996,
    -1.3552527156068805E-20, 0.09999999999999998, -1.3552527156068805E-20,
    0.09999999999999996, -6.776263578034403E-21, 0.09999999999999998, 0.0,
    0.09999999999999998, 0.0, 0.09999999999999995, 6.776263578034403E-21,
    0.09999999999999995, 6.776263578034403E-21, 0.09999999999999994,
    6.776263578034403E-21, 0.09999999999999996, 1.3552527156068805E-20,
    0.09999999999999995, 1.3552527156068805E-20, 0.09999999999999995,
    2.0328790734103208E-20, 0.09999999999999995, 1.3552527156068805E-20,
    0.09999999999999994, 1.3552527156068805E-20, 0.09999999999999995,
    1.3552527156068805E-20, 0.09999999999999995, 1.3552527156068805E-20, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, 6.776263578034403E-21, 2.0328790734103208E-20,
    2.0328790734103208E-20, 1.3552527156068805E-20, 1.3552527156068805E-20,
    6.776263578034403E-21, -0.0, -0.0, -6.776263578034403E-21,
    -6.776263578034403E-21, -6.776263578034403E-21, -1.3552527156068805E-20,
    -1.3552527156068805E-20, -2.0328790734103208E-20, -1.3552527156068805E-20,
    -1.3552527156068805E-20, -1.3552527156068805E-20, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.09999999999999999, 0.0, 0.09999999999999998, 0.0, 0.09999999999999998, 0.0,
    0.09999999999999996, 0.0, 0.09999999999999998, -6.776263578034403E-21,
    0.09999999999999999, -2.0328790734103208E-20, 0.09999999999999998,
    -2.0328790734103208E-20, 0.09999999999999996, -1.3552527156068805E-20,
    0.09999999999999998, -1.3552527156068805E-20, 0.09999999999999996,
    -6.776263578034403E-21, 0.09999999999999998, 0.0, 0.09999999999999998, 0.0,
    0.09999999999999995, 6.776263578034403E-21, 0.09999999999999995,
    6.776263578034403E-21, 0.09999999999999994, 6.776263578034403E-21,
    0.09999999999999996, 1.3552527156068805E-20, 0.09999999999999995,
    1.3552527156068805E-20, 0.09999999999999995, 2.0328790734103208E-20,
    0.09999999999999995, 1.3552527156068805E-20, 0.09999999999999994,
    1.3552527156068805E-20, 0.09999999999999995, 1.3552527156068805E-20, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, 6.776263578034403E-21, 2.0328790734103208E-20,
    2.0328790734103208E-20, 1.3552527156068805E-20, 1.3552527156068805E-20,
    6.776263578034403E-21, -0.0, -0.0, -6.776263578034403E-21,
    -6.776263578034403E-21, -6.776263578034403E-21, -1.3552527156068805E-20,
    -1.3552527156068805E-20, -2.0328790734103208E-20, -1.3552527156068805E-20,
    -1.3552527156068805E-20, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.09999999999999999, 0.0,
    0.09999999999999998, 0.0, 0.09999999999999998, 0.0, 0.09999999999999996, 0.0,
    0.09999999999999998, -6.776263578034403E-21, 0.09999999999999999,
    -2.0328790734103208E-20, 0.09999999999999998, -2.0328790734103208E-20,
    0.09999999999999996, -1.3552527156068805E-20, 0.09999999999999998,
    -1.3552527156068805E-20, 0.09999999999999996, -6.776263578034403E-21,
    0.09999999999999998, 0.0, 0.09999999999999998, 0.0, 0.09999999999999995,
    6.776263578034403E-21, 0.09999999999999995, 6.776263578034403E-21,
    0.09999999999999994, 6.776263578034403E-21, 0.09999999999999996,
    1.3552527156068805E-20, 0.09999999999999995, 1.3552527156068805E-20,
    0.09999999999999995, 2.0328790734103208E-20, 0.09999999999999995,
    1.3552527156068805E-20, 0.09999999999999994, 1.3552527156068805E-20, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, 6.776263578034403E-21, 2.0328790734103208E-20,
    2.0328790734103208E-20, 1.3552527156068805E-20, 1.3552527156068805E-20,
    6.776263578034403E-21, -0.0, -0.0, -6.776263578034403E-21,
    -6.776263578034403E-21, -6.776263578034403E-21, -1.3552527156068805E-20,
    -1.3552527156068805E-20, -2.0328790734103208E-20, -1.3552527156068805E-20,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.09999999999999999, 0.0,
    0.09999999999999998, 0.0, 0.09999999999999998, 0.0, 0.09999999999999996, 0.0,
    0.09999999999999998, -6.776263578034403E-21, 0.09999999999999999,
    -2.0328790734103208E-20, 0.09999999999999998, -2.0328790734103208E-20,
    0.09999999999999996, -1.3552527156068805E-20, 0.09999999999999998,
    -1.3552527156068805E-20, 0.09999999999999996, -6.776263578034403E-21,
    0.09999999999999998, 0.0, 0.09999999999999998, 0.0, 0.09999999999999995,
    6.776263578034403E-21, 0.09999999999999995, 6.776263578034403E-21,
    0.09999999999999994, 6.776263578034403E-21, 0.09999999999999996,
    1.3552527156068805E-20, 0.09999999999999995, 1.3552527156068805E-20,
    0.09999999999999995, 2.0328790734103208E-20, 0.09999999999999995,
    1.3552527156068805E-20, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 6.776263578034403E-21,
    2.0328790734103208E-20, 2.0328790734103208E-20, 1.3552527156068805E-20,
    1.3552527156068805E-20, 6.776263578034403E-21, -0.0, -0.0,
    -6.776263578034403E-21, -6.776263578034403E-21, -6.776263578034403E-21,
    -1.3552527156068805E-20, -1.3552527156068805E-20, -2.0328790734103208E-20,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.09999999999999999, 0.0,
    0.09999999999999998, 0.0, 0.09999999999999998, 0.0, 0.09999999999999996, 0.0,
    0.09999999999999998, -6.776263578034403E-21, 0.09999999999999999,
    -2.0328790734103208E-20, 0.09999999999999998, -2.0328790734103208E-20,
    0.09999999999999996, -1.3552527156068805E-20, 0.09999999999999998,
    -1.3552527156068805E-20, 0.09999999999999996, -6.776263578034403E-21,
    0.09999999999999998, 0.0, 0.09999999999999998, 0.0, 0.09999999999999995,
    6.776263578034403E-21, 0.09999999999999995, 6.776263578034403E-21,
    0.09999999999999994, 6.776263578034403E-21, 0.09999999999999996,
    1.3552527156068805E-20, 0.09999999999999995, 1.3552527156068805E-20,
    0.09999999999999995, 2.0328790734103208E-20, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, 6.776263578034403E-21, 2.0328790734103208E-20, 2.0328790734103208E-20,
    1.3552527156068805E-20, 1.3552527156068805E-20, 6.776263578034403E-21, -0.0,
    -0.0, -6.776263578034403E-21, -6.776263578034403E-21, -6.776263578034403E-21,
    -1.3552527156068805E-20, -1.3552527156068805E-20, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.09999999999999999, 0.0, 0.09999999999999998,
    0.0, 0.09999999999999998, 0.0, 0.09999999999999996, 0.0, 0.09999999999999998,
    -6.776263578034403E-21, 0.09999999999999999, -2.0328790734103208E-20,
    0.09999999999999998, -2.0328790734103208E-20, 0.09999999999999996,
    -1.3552527156068805E-20, 0.09999999999999998, -1.3552527156068805E-20,
    0.09999999999999996, -6.776263578034403E-21, 0.09999999999999998, 0.0,
    0.09999999999999998, 0.0, 0.09999999999999995, 6.776263578034403E-21,
    0.09999999999999995, 6.776263578034403E-21, 0.09999999999999994,
    6.776263578034403E-21, 0.09999999999999996, 1.3552527156068805E-20,
    0.09999999999999995, 1.3552527156068805E-20, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, 6.776263578034403E-21, 2.0328790734103208E-20,
    2.0328790734103208E-20, 1.3552527156068805E-20, 1.3552527156068805E-20,
    6.776263578034403E-21, -0.0, -0.0, -6.776263578034403E-21,
    -6.776263578034403E-21, -6.776263578034403E-21, -1.3552527156068805E-20, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.09999999999999999, 0.0, 0.09999999999999998, 0.0, 0.09999999999999998, 0.0,
    0.09999999999999996, 0.0, 0.09999999999999998, -6.776263578034403E-21,
    0.09999999999999999, -2.0328790734103208E-20, 0.09999999999999998,
    -2.0328790734103208E-20, 0.09999999999999996, -1.3552527156068805E-20,
    0.09999999999999998, -1.3552527156068805E-20, 0.09999999999999996,
    -6.776263578034403E-21, 0.09999999999999998, 0.0, 0.09999999999999998, 0.0,
    0.09999999999999995, 6.776263578034403E-21, 0.09999999999999995,
    6.776263578034403E-21, 0.09999999999999994, 6.776263578034403E-21,
    0.09999999999999996, 1.3552527156068805E-20, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, 6.776263578034403E-21, 2.0328790734103208E-20,
    2.0328790734103208E-20, 1.3552527156068805E-20, 1.3552527156068805E-20,
    6.776263578034403E-21, -0.0, -0.0, -6.776263578034403E-21,
    -6.776263578034403E-21, -6.776263578034403E-21, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.09999999999999999, 0.0,
    0.09999999999999998, 0.0, 0.09999999999999998, 0.0, 0.09999999999999996, 0.0,
    0.09999999999999998, -6.776263578034403E-21, 0.09999999999999999,
    -2.0328790734103208E-20, 0.09999999999999998, -2.0328790734103208E-20,
    0.09999999999999996, -1.3552527156068805E-20, 0.09999999999999998,
    -1.3552527156068805E-20, 0.09999999999999996, -6.776263578034403E-21,
    0.09999999999999998, 0.0, 0.09999999999999998, 0.0, 0.09999999999999995,
    6.776263578034403E-21, 0.09999999999999995, 6.776263578034403E-21,
    0.09999999999999994, 6.776263578034403E-21, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, 6.776263578034403E-21, 2.0328790734103208E-20,
    2.0328790734103208E-20, 1.3552527156068805E-20, 1.3552527156068805E-20,
    6.776263578034403E-21, -0.0, -0.0, -6.776263578034403E-21,
    -6.776263578034403E-21, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.09999999999999999, 0.0,
    0.09999999999999998, 0.0, 0.09999999999999998, 0.0, 0.09999999999999996, 0.0,
    0.09999999999999998, -6.776263578034403E-21, 0.09999999999999999,
    -2.0328790734103208E-20, 0.09999999999999998, -2.0328790734103208E-20,
    0.09999999999999996, -1.3552527156068805E-20, 0.09999999999999998,
    -1.3552527156068805E-20, 0.09999999999999996, -6.776263578034403E-21,
    0.09999999999999998, 0.0, 0.09999999999999998, 0.0, 0.09999999999999995,
    6.776263578034403E-21, 0.09999999999999995, 6.776263578034403E-21, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 6.776263578034403E-21,
    2.0328790734103208E-20, 2.0328790734103208E-20, 1.3552527156068805E-20,
    1.3552527156068805E-20, 6.776263578034403E-21, -0.0, -0.0,
    -6.776263578034403E-21, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.09999999999999999, 0.0,
    0.09999999999999998, 0.0, 0.09999999999999998, 0.0, 0.09999999999999996, 0.0,
    0.09999999999999998, -6.776263578034403E-21, 0.09999999999999999,
    -2.0328790734103208E-20, 0.09999999999999998, -2.0328790734103208E-20,
    0.09999999999999996, -1.3552527156068805E-20, 0.09999999999999998,
    -1.3552527156068805E-20, 0.09999999999999996, -6.776263578034403E-21,
    0.09999999999999998, 0.0, 0.09999999999999998, 0.0, 0.09999999999999995,
    6.776263578034403E-21, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, 6.776263578034403E-21, 2.0328790734103208E-20, 2.0328790734103208E-20,
    1.3552527156068805E-20, 1.3552527156068805E-20, 6.776263578034403E-21, -0.0,
    -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.09999999999999999, 0.0,
    0.09999999999999998, 0.0, 0.09999999999999998, 0.0, 0.09999999999999996, 0.0,
    0.09999999999999998, -6.776263578034403E-21, 0.09999999999999999,
    -2.0328790734103208E-20, 0.09999999999999998, -2.0328790734103208E-20,
    0.09999999999999996, -1.3552527156068805E-20, 0.09999999999999998,
    -1.3552527156068805E-20, 0.09999999999999996, -6.776263578034403E-21,
    0.09999999999999998, 0.0, 0.09999999999999998, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 6.776263578034403E-21,
    2.0328790734103208E-20, 2.0328790734103208E-20, 1.3552527156068805E-20,
    1.3552527156068805E-20, 6.776263578034403E-21, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.09999999999999999, 0.0, 0.09999999999999998, 0.0,
    0.09999999999999998, 0.0, 0.09999999999999996, 0.0, 0.09999999999999998,
    -6.776263578034403E-21, 0.09999999999999999, -2.0328790734103208E-20,
    0.09999999999999998, -2.0328790734103208E-20, 0.09999999999999996,
    -1.3552527156068805E-20, 0.09999999999999998, -1.3552527156068805E-20,
    0.09999999999999996, -6.776263578034403E-21, 0.09999999999999998, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    6.776263578034403E-21, 2.0328790734103208E-20, 2.0328790734103208E-20,
    1.3552527156068805E-20, 1.3552527156068805E-20, 6.776263578034403E-21, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.09999999999999999, 0.0,
    0.09999999999999998, 0.0, 0.09999999999999998, 0.0, 0.09999999999999996, 0.0,
    0.09999999999999998, -6.776263578034403E-21, 0.09999999999999999,
    -2.0328790734103208E-20, 0.09999999999999998, -2.0328790734103208E-20,
    0.09999999999999996, -1.3552527156068805E-20, 0.09999999999999998,
    -1.3552527156068805E-20, 0.09999999999999996, -6.776263578034403E-21, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, 6.776263578034403E-21, 2.0328790734103208E-20, 2.0328790734103208E-20,
    1.3552527156068805E-20, 1.3552527156068805E-20, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.09999999999999999, 0.0, 0.09999999999999998,
    0.0, 0.09999999999999998, 0.0, 0.09999999999999996, 0.0, 0.09999999999999998,
    -6.776263578034403E-21, 0.09999999999999999, -2.0328790734103208E-20,
    0.09999999999999998, -2.0328790734103208E-20, 0.09999999999999996,
    -1.3552527156068805E-20, 0.09999999999999998, -1.3552527156068805E-20, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, 6.776263578034403E-21, 2.0328790734103208E-20,
    2.0328790734103208E-20, 1.3552527156068805E-20, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.09999999999999999, 0.0,
    0.09999999999999998, 0.0, 0.09999999999999998, 0.0, 0.09999999999999996, 0.0,
    0.09999999999999998, -6.776263578034403E-21, 0.09999999999999999,
    -2.0328790734103208E-20, 0.09999999999999998, -2.0328790734103208E-20,
    0.09999999999999996, -1.3552527156068805E-20, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    6.776263578034403E-21, 2.0328790734103208E-20, 2.0328790734103208E-20, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.09999999999999999, 0.0, 0.09999999999999998, 0.0, 0.09999999999999998, 0.0,
    0.09999999999999996, 0.0, 0.09999999999999998, -6.776263578034403E-21,
    0.09999999999999999, -2.0328790734103208E-20, 0.09999999999999998,
    -2.0328790734103208E-20, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 6.776263578034403E-21,
    2.0328790734103208E-20, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.09999999999999999, 0.0,
    0.09999999999999998, 0.0, 0.09999999999999998, 0.0, 0.09999999999999996, 0.0,
    0.09999999999999998, -6.776263578034403E-21, 0.09999999999999999,
    -2.0328790734103208E-20, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 6.776263578034403E-21,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.09999999999999999, 0.0, 0.09999999999999998, 0.0,
    0.09999999999999998, 0.0, 0.09999999999999996, 0.0, 0.09999999999999998,
    -6.776263578034403E-21, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.09999999999999999, 0.0, 0.09999999999999998, 0.0,
    0.09999999999999998, 0.0, 0.09999999999999996, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.09999999999999999, 0.0,
    0.09999999999999998, 0.0, 0.09999999999999998, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.09999999999999999, 0.0, 0.09999999999999998, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.09999999999999999, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0,
    -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, -0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  static const uint8_T b_Mrows_0[96] = { 2U, 4U, 6U, 8U, 10U, 12U, 14U, 16U, 18U,
    20U, 22U, 24U, 26U, 28U, 30U, 32U, 34U, 36U, 38U, 40U, 42U, 44U, 46U, 48U,
    50U, 52U, 54U, 56U, 58U, 60U, 61U, 62U, 63U, 64U, 65U, 66U, 67U, 68U, 69U,
    70U, 71U, 72U, 73U, 74U, 75U, 76U, 77U, 78U, 79U, 80U, 81U, 82U, 83U, 84U,
    85U, 86U, 87U, 88U, 89U, 90U, 91U, 92U, 93U, 94U, 95U, 96U, 97U, 98U, 99U,
    100U, 101U, 102U, 103U, 104U, 105U, 106U, 107U, 108U, 109U, 110U, 111U, 112U,
    113U, 114U, 115U, 116U, 117U, 118U, 119U, 120U, 121U, 122U, 123U, 151U, 152U,
    153U };

  static const real_T b_Kr[180] = { 0.0, -0.00021345587553256695, 0.0,
    -0.000801368045990212, 0.0, -0.0016958591007866573, 0.0,
    -0.002841355716435615, 0.0, -0.0041923583039481125, 0.0,
    -0.005711614950566467, 0.0, -0.0073686263697049885, 0.0,
    -0.009138421857489032, 0.0, -0.011000557130730422, 0.0,
    -0.012938293826058364, 0.0, -0.014937927730624998, 0.0, -0.01698823878392505,
    0.0, -0.01908004077737146, 0.0, -0.02120581267948981, 0.0,
    -0.023359396790517125, 0.0, -0.02553575161228924, 0.0, -0.02773074951521757,
    0.0, -0.02994101108202062, 0.0, -0.03216376947984254, 0.0,
    -0.034396759417535644, 0.0, -0.036638126231572615, 0.0,
    -0.038886351451887055, 0.0, -0.041140191860337946, 0.0, -0.04339862959600047,
    0.0, -0.04566083130483314, 0.0, -0.04792611469425395, 0.0,
    -0.05019392115034345, 0.0, -0.05246379331870665, 0.0, -0.05473535674923536,
    0.0, -0.057008304868110475, -0.0, -0.0, 0.0, -0.00021345587553256695, 0.0,
    -0.000801368045990212, 0.0, -0.0016958591007866573, 0.0,
    -0.002841355716435615, 0.0, -0.0041923583039481125, 0.0,
    -0.005711614950566467, 0.0, -0.0073686263697049885, 0.0,
    -0.009138421857489032, 0.0, -0.011000557130730422, 0.0,
    -0.012938293826058364, 0.0, -0.014937927730624998, 0.0, -0.01698823878392505,
    0.0, -0.01908004077737146, 0.0, -0.02120581267948981, 0.0,
    -0.023359396790517125, 0.0, -0.02553575161228924, 0.0, -0.02773074951521757,
    0.0, -0.02994101108202062, 0.0, -0.03216376947984254, 0.0,
    -0.034396759417535644, 0.0, -0.036638126231572615, 0.0,
    -0.038886351451887055, 0.0, -0.041140191860337946, 0.0, -0.04339862959600047,
    0.0, -0.04566083130483314, 0.0, -0.04792611469425395, 0.0,
    -0.05019392115034345, 0.0, -0.05246379331870665, 0.0, -0.05473535674923536,
    -0.0, -0.0, -0.0, -0.0, 0.0, -0.00021345587553256695, 0.0,
    -0.000801368045990212, 0.0, -0.0016958591007866573, 0.0,
    -0.002841355716435615, 0.0, -0.0041923583039481125, 0.0,
    -0.005711614950566467, 0.0, -0.0073686263697049885, 0.0,
    -0.009138421857489032, 0.0, -0.011000557130730422, 0.0,
    -0.012938293826058364, 0.0, -0.014937927730624998, 0.0, -0.01698823878392505,
    0.0, -0.01908004077737146, 0.0, -0.02120581267948981, 0.0,
    -0.023359396790517125, 0.0, -0.02553575161228924, 0.0, -0.02773074951521757,
    0.0, -0.02994101108202062, 0.0, -0.03216376947984254, 0.0,
    -0.034396759417535644, 0.0, -0.036638126231572615, 0.0,
    -0.038886351451887055, 0.0, -0.041140191860337946, 0.0, -0.04339862959600047,
    0.0, -0.04566083130483314, 0.0, -0.04792611469425395, 0.0,
    -0.05019392115034345, 0.0, -0.05246379331870665 };

  static const real_T b_Kv[186] = { 1.5679996000010925E-20, 0.0,
    1.3963927151695095E-20, 0.0, 1.2149906206994494E-20, 0.0,
    1.023889121811525E-20, 0.0, 8.633379649499004E-21, 0.0,
    7.349429770080679E-21, 0.0, 6.001275509264406E-21, 0.0, 4.58935671322197E-21,
    0.0, 3.917459652815685E-21, 0.0, 3.213285145148845E-21, 0.0,
    2.4770848819322804E-21, 0.0, 1.7090649309099398E-21, 0.0,
    9.09394006081013E-22, 0.0, -3.235028388523115E-22, 0.0,
    -1.2015024235754952E-21, 0.0, -2.1108143156908524E-21, 0.0,
    -2.6496486960272475E-21, 0.0, -3.2042397442324026E-21, 0.0,
    -3.774530869411076E-21, 0.0, -3.958762661219565E-21, 0.0,
    -4.143194195947778E-21, 0.0, -3.9260761887096536E-21, 0.0,
    -3.2919629281812384E-21, 0.0, -2.627122004712541E-21, 0.0,
    -1.5298111041403382E-21, 0.0, -3.8630329992325835E-22, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.497912278479541E-20, 0.0,
    1.3362176200471376E-20, 0.0, 1.1646107352155545E-20, 0.0,
    9.832086407454943E-21, 0.0, 8.307374718498958E-21, 0.0, 7.08816644980597E-21,
    0.0, 5.8042165703876454E-21, 0.0, 4.456062309571373E-21, 0.0,
    3.816750113375453E-21, 0.0, 3.144853052969168E-21, 0.0,
    2.440678545302328E-21, 0.0, 1.7044782820857636E-21, 0.0,
    9.36458331063423E-22, 0.0, -2.495158936887621E-22, 0.0,
    -1.0961094386988282E-21, 0.0, -1.974109023422012E-21, 0.0,
    -2.497117615614111E-21, 0.0, -3.035951995950506E-21, 0.0,
    -3.590543044155661E-21, 0.0, -3.774530869411076E-21, 0.0,
    -3.958762661219565E-21, 0.0, -3.75689089602452E-21, 0.0,
    -3.153469588863137E-21, 0.0, -2.5193563283347216E-21, 0.0,
    -1.4682121049427659E-21, 0.0, -3.709012043705631E-22, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.4270110632961536E-20, 0.0,
    1.2753715558572033E-20, 0.0, 1.1136768974247998E-20, 0.0,
    9.420700125932166E-21, 0.0, 7.977580385602127E-21, 0.0,
    6.823769901016706E-21, 0.0, 5.604561632323717E-21, 0.0,
    4.320611752905393E-21, 0.0, 3.7142599008302465E-21, 0.0,
    3.074947704634327E-21, 0.0, 2.403050644228042E-21, 0.0,
    1.698876136561202E-21, 0.0, 9.626758733446375E-22, 0.0,
    -1.7624528204826632E-22, 0.0, -9.913183024298883E-22, 0.0,
    -1.8379118474399543E-21, 0.0, -2.345010227792575E-21, 0.0,
    -2.868018819984674E-21, 0.0, -3.406853200321069E-21, 0.0,
    -3.590543044155661E-21, 0.0, -3.774530869411076E-21, 0.0,
    -3.587861456849002E-21, 0.0, -3.015088487283393E-21, 0.0,
    -2.411667180122011E-21, 0.0, -1.4066527152230325E-21, 0.0,
    -3.5550849183107654E-22, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0 };

  static const real_T b_Kx[12] = { 0.024965491352746262, -1.7202219003200385,
    -0.001322994522655646, 0.7692929902713578, 0.020335782539653357,
    -1.5941350192750285, -0.001226023165082389, 0.7122846854032473,
    0.01654945337552345, -1.4727458865169443, -0.001132664768866769,
    0.6575493286540119 };

  static const real_T b_Ku1[3] = { 2.9224437155490834, 2.754097987517047,
    2.5872950360812346 };

  static const real_T b_Linv[16] = { 0.5839627665967825, -6.504222864713408,
    -2.504383334779896, 0.0, 0.0, 6.925413529441978, -4.328382328930197, 0.0,
    0.0, 0.0, 7.445904685803024, 0.0, 0.0, 0.0, 0.0, 0.001 };

  static const real_T b_Hinv[16] = { 48.91786347415533, -34.204504454663514,
    -18.64739960748463, 0.0, -34.204504454663514, 66.6962461391732,
    -32.22872226492836, 0.0, -18.64739960748463, -32.22872226492836,
    55.44149659006342, 0.0, 0.0, 0.0, 0.0, 1.0E-6 };

  static const real_T b_Ac[384] = { -0.02134558755325669, -0.08013680459902119,
    -0.1695859100786657, -0.28413557164356146, -0.41923583039481116,
    -0.5711614950566466, -0.7368626369704987, -0.913842185748903,
    -1.100055713073042, -1.2938293826058362, -1.4937927730624996,
    -1.6988238783925047, -1.9080040777371454, -2.1205812679489804,
    -2.335939679051712, -2.5535751612289235, -2.7730749515217563,
    -2.994101108202061, -3.2163769479842537, -3.4396759417535634,
    -3.663812623157261, -3.8886351451887045, -4.114019186033794,
    -4.339862959600047, -4.566083130483313, -4.7926114694253945,
    -5.019392115034344, -5.246379331870664, -5.473535674923535,
    -5.700830486811046, -0.0007232176193835032, 0.02134558755325669,
    -0.005515643284535797, 0.08013680459902119, -0.017771147524770776,
    0.1695859100786657, -0.04026839651440278, 0.28413557164356146,
    -0.07528236970288049, 0.41923583039481116, -0.12467566272808799,
    0.5711614950566466, -0.18997323991930987, 0.7368626369704987,
    -0.27242363647027834, 0.913842185748903, -0.3730490665404021,
    1.100055713073042, -0.49268644829822084, 1.2938293826058362,
    -0.6320209923861277, 1.4937927730624996, -0.7916137018293865,
    1.6988238783925047, -0.9719238870573501, 1.9080040777371454,
    -1.1733275996437393, 2.1205812679489804, -1.396132724576703,
    2.335939679051712, -1.6405913367644491, 2.5535751612289235,
    -1.9069098176864074, 2.7730749515217563, -2.195257138206652,
    2.994101108202061, -2.5057716399679757, 3.2163769479842537,
    -2.8385665875277635, 3.4396759417535634, -3.1937347140623804,
    3.663812623157261, -3.571351943075147, 3.8886351451887045,
    -3.971480435473113, 4.114019186033794, -4.39417108430252, 4.339862959600047,
    -4.839465557265442, 4.566083130483313, -5.307397968990981,
    4.7926114694253945, -5.797996250175108, 5.019392115034344,
    -6.311283268537571, 5.246379331870664, -6.847277746583783, 5.473535674923535,
    -7.405995013004697, 5.700830486811046, -1.0, -1.0, -1.0, 1.0, 1.0, 1.0, -0.0,
    -0.02134558755325669, -0.08013680459902119, -0.1695859100786657,
    -0.28413557164356146, -0.41923583039481116, -0.5711614950566466,
    -0.7368626369704987, -0.913842185748903, -1.100055713073042,
    -1.2938293826058362, -1.4937927730624996, -1.6988238783925047,
    -1.9080040777371454, -2.1205812679489804, -2.335939679051712,
    -2.5535751612289235, -2.7730749515217563, -2.994101108202061,
    -3.2163769479842537, -3.4396759417535634, -3.663812623157261,
    -3.8886351451887045, -4.114019186033794, -4.339862959600047,
    -4.566083130483313, -4.7926114694253945, -5.019392115034344,
    -5.246379331870664, -5.473535674923535, 0.0, 0.0, -0.0007232176193835032,
    0.02134558755325669, -0.005515643284535797, 0.08013680459902119,
    -0.017771147524770776, 0.1695859100786657, -0.04026839651440278,
    0.28413557164356146, -0.07528236970288049, 0.41923583039481116,
    -0.12467566272808799, 0.5711614950566466, -0.18997323991930987,
    0.7368626369704987, -0.27242363647027834, 0.913842185748903,
    -0.3730490665404021, 1.100055713073042, -0.49268644829822084,
    1.2938293826058362, -0.6320209923861277, 1.4937927730624996,
    -0.7916137018293865, 1.6988238783925047, -0.9719238870573501,
    1.9080040777371454, -1.1733275996437393, 2.1205812679489804,
    -1.396132724576703, 2.335939679051712, -1.6405913367644491,
    2.5535751612289235, -1.9069098176864074, 2.7730749515217563,
    -2.195257138206652, 2.994101108202061, -2.5057716399679757,
    3.2163769479842537, -2.8385665875277635, 3.4396759417535634,
    -3.1937347140623804, 3.663812623157261, -3.571351943075147,
    3.8886351451887045, -3.971480435473113, 4.114019186033794, -4.39417108430252,
    4.339862959600047, -4.839465557265442, 4.566083130483313, -5.307397968990981,
    4.7926114694253945, -5.797996250175108, 5.019392115034344,
    -6.311283268537571, 5.246379331870664, -6.847277746583783, 5.473535674923535,
    -0.0, -1.0, -1.0, 0.0, 1.0, 1.0, -0.0, -0.0, -0.02134558755325669,
    -0.08013680459902119, -0.1695859100786657, -0.28413557164356146,
    -0.41923583039481116, -0.5711614950566466, -0.7368626369704987,
    -0.913842185748903, -1.100055713073042, -1.2938293826058362,
    -1.4937927730624996, -1.6988238783925047, -1.9080040777371454,
    -2.1205812679489804, -2.335939679051712, -2.5535751612289235,
    -2.7730749515217563, -2.994101108202061, -3.2163769479842537,
    -3.4396759417535634, -3.663812623157261, -3.8886351451887045,
    -4.114019186033794, -4.339862959600047, -4.566083130483313,
    -4.7926114694253945, -5.019392115034344, -5.246379331870664, 0.0, 0.0, 0.0,
    0.0, -0.0007232176193835032, 0.02134558755325669, -0.005515643284535797,
    0.08013680459902119, -0.017771147524770776, 0.1695859100786657,
    -0.04026839651440278, 0.28413557164356146, -0.07528236970288049,
    0.41923583039481116, -0.12467566272808799, 0.5711614950566466,
    -0.18997323991930987, 0.7368626369704987, -0.27242363647027834,
    0.913842185748903, -0.3730490665404021, 1.100055713073042,
    -0.49268644829822084, 1.2938293826058362, -0.6320209923861277,
    1.4937927730624996, -0.7916137018293865, 1.6988238783925047,
    -0.9719238870573501, 1.9080040777371454, -1.1733275996437393,
    2.1205812679489804, -1.396132724576703, 2.335939679051712,
    -1.6405913367644491, 2.5535751612289235, -1.9069098176864074,
    2.7730749515217563, -2.195257138206652, 2.994101108202061,
    -2.5057716399679757, 3.2163769479842537, -2.8385665875277635,
    3.4396759417535634, -3.1937347140623804, 3.663812623157261,
    -3.571351943075147, 3.8886351451887045, -3.971480435473113,
    4.114019186033794, -4.39417108430252, 4.339862959600047, -4.839465557265442,
    4.566083130483313, -5.307397968990981, 4.7926114694253945,
    -5.797996250175108, 5.019392115034344, -6.311283268537571, 5.246379331870664,
    -0.0, -0.0, -1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  static const real_T c_a[16] = { 0.8187307530779818, 1.5586642783583002E-5,
    -0.02026651192367618, 0.0, -0.09063459665629994, 0.999964800261968,
    0.045768413407256126, 0.0, -6.970558560908948E-5, -2.7071542692617245E-8,
    1.0000351997380321, 0.0, 0.0, 0.0, 0.0, 1.0 };

  static const real_T d_a[4] = { -0.17869303344412357, -0.10119271714871694,
    -0.00025732433755852645, 0.0 };

  static const real_T e_a[8] = { -3.165179497547493E-20, -1.9088225808630127E-5,
    0.024819440679427797, 0.0, 0.0, 0.0, 0.0, 0.0 };

  static const real_T f_a[8] = { -0.016866904535001268, 0.05309142407607782,
    0.0436233508326553, 0.07481904028246217, -0.014133674914589466,
    -0.07344921710807803, -0.011383968451643583, 0.055502688090371254 };

  /* MATLAB Function: '<S1>/DataTypeConversion_reldist' incorporates:
   *  Inport: '<Root>/Relative distance'
   */
  accsubsys_DataTypeConversion_L0(accsubsystem_1_U.relativedistance, &rtb_y_n);

  /* MATLAB Function: '<S1>/DataTypeConversion_vego' incorporates:
   *  Inport: '<Root>/Longitudinal velocity'
   */
  accsubsys_DataTypeConversion_L0(accsubsystem_1_U.ego_velocity, &rtb_y_gf);

  /* MATLAB Function: '<S1>/DataTypeConversion_L0' incorporates:
   *  Constant: '<S1>/Default spacing constant'
   */
  accsubsys_DataTypeConversion_L0(accsubsystem_1_P.Defaultspacingconstant_Value,
    &rtb_y_j);

  /* MATLAB Function: '<S1>/DataTypeConversion_vset' incorporates:
   *  Inport: '<Root>/Set velocity'
   */
  accsubsys_DataTypeConversion_L0(accsubsystem_1_U.set_velocity, &rtb_y);

  /* MATLAB Function: '<S1>/DataTypeConversion_vlead' incorporates:
   *  Inport: '<Root>/Longitudinal velocity'
   *  Inport: '<Root>/Relative velocity'
   *  Sum: '<S1>/Sum6'
   */
  accsubsys_DataTypeConversion_L0(accsubsystem_1_U.ego_velocity +
    accsubsystem_1_U.relative_velocity, &rtb_y_cs);

  /* MATLAB Function: '<S1>/DataTypeConversion_amin' incorporates:
   *  Constant: '<S1>/Minimum longitudinal acceleration constant'
   */
  accsubsys_DataTypeConversion_L0
    (accsubsystem_1_P.Minimumlongitudinalacceleration, &rtb_y_e);

  /* MATLAB Function: '<S1>/DataTypeConversion_amax' incorporates:
   *  Constant: '<S1>/Maximum longitudinal acceleration constant'
   */
  accsubsys_DataTypeConversion_L0
    (accsubsystem_1_P.Maximumlongitudinalacceleration, &rtb_y_fb);

  /* SignalConversion generated from: '<S34>/ SFunction ' incorporates:
   *  Constant: '<S1>/Default spacing constant'
   *  Constant: '<S1>/Minimum velocity constant'
   *  Inport: '<Root>/Longitudinal velocity'
   *  Inport: '<Root>/Time gap'
   *  MATLAB Function: '<S1>/DataTypeConversion_dmin'
   *  MATLAB Function: '<S33>/optimizer'
   *  Product: '<S1>/Product2'
   *  Sum: '<S1>/Sum1'
   */
  accsubsys_DataTypeConversion_L0(accsubsystem_1_P.Defaultspacingconstant_Value
    + accsubsystem_1_U.ego_velocity * accsubsystem_1_U.Timegap,
    &rtb_TmpSignalConversionAtSFun_i[0]);
  rtb_TmpSignalConversionAtSFun_i[1] =
    accsubsystem_1_P.Minimumvelocityconstant_Value;

  /* SignalConversion generated from: '<S34>/ SFunction ' incorporates:
   *  Constant: '<S1>/Maximum velocity constant'
   *  Constant: '<S1>/Unconstrained'
   *  MATLAB Function: '<S33>/optimizer'
   */
  rtb_TmpSignalConversionAtSFun_g[0] = accsubsystem_1_P.Unconstrained_Value;
  rtb_TmpSignalConversionAtSFun_g[1] =
    accsubsystem_1_P.Maximumvelocityconstant_Value;

  /* MATLAB Function: '<S33>/optimizer' incorporates:
   *  Constant: '<S1>/Enable optimization constant'
   *  MATLAB Function: '<S1>/DataTypeConversion_optsgn'
   *  Memory: '<S13>/Memory'
   *  Memory: '<S13>/last_x'
   *  SignalConversion generated from: '<S34>/ SFunction '
   *  UnitDelay: '<S13>/last_mv'
   * */
  memset(&vseq[0], 0, 62U * sizeof(real_T));
  for (i = 0; i < 31; i++) {
    vseq[(i << 1) + 1] = 1.0;
  }

  for (i = 0; i < 30; i++) {
    ii = i << 1;
    rseq[ii] = rtb_y_j * 2.8490028490028494 - 0.8547008547008548;
    rseq[ii + 1] = rtb_y * 2.8490028490028494;
  }

  for (i = 0; i < 31; i++) {
    vseq[i << 1] = accsubsystem_1_RMDscale * rtb_y_cs;
  }

  rtb_TmpSignalConversionAtSFun_d[0] = vseq[0];
  rtb_TmpSignalConversionAtSFun_d[1] = vseq[1];
  xk[0] = accsubsystem_1_DW.last_x_PreviousInput[0];
  xk[1] = accsubsystem_1_DW.last_x_PreviousInput[1];
  xk[2] = accsubsystem_1_DW.last_x_PreviousInput[2];
  xk[3] = accsubsystem_1_DW.last_x_PreviousInput[3];
  rtb_y_cs = 0.0;
  rtb_y = 0.0;
  for (i = 0; i < 4; i++) {
    rtb_y_j = xk[i];
    ii = i << 1;
    rtb_y_cs += a[ii] * rtb_y_j;
    rtb_y += a[ii + 1] * rtb_y_j;
  }

  rtb_y_j = 0.0 * vseq[0] + 0.0 * vseq[1];
  rtb_y_n = (rtb_y_n * 2.8490028490028494 - 0.8547008547008548) - (rtb_y_j +
    rtb_y_cs);
  rtb_y_gf = rtb_y_gf * 2.8490028490028494 - (rtb_y_j + rtb_y);
  for (i = 0; i < 4; i++) {
    rtb_xest[i] = (b_a[i + 4] * rtb_y_gf + b_a[i] * rtb_y_n) + xk[i];
  }

  memset(&rtb_iAout[0], 0, 96U * sizeof(boolean_T));
  if (!(accsubsystem_1_P.Enableoptimizationconstant_Valu > 0.0) &&
      !(accsubsystem_1_P.Enableoptimizationconstant_Valu < 0.0)) {
    rtb_y_j = rtb_xest[1];
    rtb_y = rtb_xest[0];
    rtb_y_cs = rtb_xest[2];
    rtb_xest_0 = rtb_xest[3];
    for (i = 0; i < 96; i++) {
      b_Mx[i] = ((((b_Mx_0[i + 96] * rtb_y_j + b_Mx_0[i] * rtb_y) + b_Mx_0[i +
                   192] * rtb_y_cs) + b_Mx_0[i + 288] * rtb_xest_0) + b_Mlim[i])
        + b_Mu1[i] * accsubsystem_1_DW.last_mv_DSTATE;
      b_Mv[i] = 0.0;
    }

    for (i = 0; i < 62; i++) {
      rtb_y_j = vseq[i];
      for (ii = 0; ii < 96; ii++) {
        b_Mv[ii] += b_Mv_0[96 * i + ii] * rtb_y_j;
      }
    }

    ymax_incr_flag[0] = false;
    ymax_incr[0] = 0.0;
    ymin_incr_flag[0] = false;
    ymin_incr[0] = 0.0;
    ymax_incr_flag[1] = false;
    ymax_incr[1] = 0.0;
    ymin_incr_flag[1] = false;
    ymin_incr[1] = 0.0;
    umax_incr_flag = false;
    rtb_y_j = 0.0;
    umin_incr_flag = false;
    rtb_y = 0.0;
    for (i = 0; i < 96; i++) {
      rtb_y_cs = -(b_Mx[i] + b_Mv[i]);
      Bc[i] = rtb_y_cs;
      b_Mrows = b_Mrows_0[i];
      if (b_Mrows <= 60) {
        ii = (b_Mrows - (((b_Mrows - 1) >> 1) << 1)) - 1;
        b_Del_Save_Flag0 = ymax_incr_flag[ii];
        if (!ymax_incr_flag[ii]) {
          rtb_xest_0 = -(2.8490028490028494 * rtb_TmpSignalConversionAtSFun_g[ii]
                         - (-0.8547008547008548 * (real_T)ii +
                            0.8547008547008548)) - (-b_Mlim[i]);
          b_Del_Save_Flag0 = true;
        } else {
          rtb_xest_0 = ymax_incr[ii];
        }

        ymax_incr[ii] = rtb_xest_0;
        ymax_incr_flag[ii] = b_Del_Save_Flag0;
        Bc[i] = rtb_y_cs + rtb_xest_0;
      } else if (b_Mrows <= 120) {
        ii = (b_Mrows - (((b_Mrows - 61) >> 1) << 1)) - 61;
        b_Del_Save_Flag0 = ymin_incr_flag[ii];
        if (!ymin_incr_flag[ii]) {
          rtb_xest_0 = (2.8490028490028494 * rtb_TmpSignalConversionAtSFun_i[ii]
                        - (-0.8547008547008548 * (real_T)ii + 0.8547008547008548))
            - (-b_Mlim[i]);
          b_Del_Save_Flag0 = true;
        } else {
          rtb_xest_0 = ymin_incr[ii];
        }

        ymin_incr[ii] = rtb_xest_0;
        ymin_incr_flag[ii] = b_Del_Save_Flag0;
        Bc[i] = rtb_y_cs + rtb_xest_0;
      } else if (b_Mrows <= 150) {
        if (!umax_incr_flag) {
          rtb_y_j = -(accsubsystem_1_RMVscale * rtb_y_fb) - (-b_Mlim[i]);
          umax_incr_flag = true;
        }

        Bc[i] = rtb_y_cs + rtb_y_j;
      } else {
        if (!umin_incr_flag) {
          rtb_y = accsubsystem_1_RMVscale * rtb_y_e - (-b_Mlim[i]);
          umin_incr_flag = true;
        }

        Bc[i] = rtb_y_cs + rtb_y;
      }
    }

    f[0] = 0.0;
    f[1] = 0.0;
    f[2] = 0.0;
    f[3] = 0.0;
    for (ii = 0; ii < 3; ii++) {
      rtb_y_e = 0.0;
      for (i = 0; i < 60; i++) {
        rtb_y_e += b_Kr[60 * ii + i] * rseq[i];
      }

      rtb_y_fb = 0.0;
      for (i = 0; i < 62; i++) {
        rtb_y_fb += b_Kv[62 * ii + i] * vseq[i];
      }

      i = ii << 2;
      f[ii] = (((((b_Kx[i + 1] * rtb_xest[1] + b_Kx[i] * rtb_xest[0]) + b_Kx[i +
                  2] * rtb_xest[2]) + b_Kx[i + 3] * rtb_xest[3]) + rtb_y_e) +
               b_Ku1[ii] * accsubsystem_1_DW.last_mv_DSTATE) + rtb_y_fb;
    }

    memcpy(&rtb_iAout[0], &accsubsystem_1_DW.Memory_PreviousInput[0], 96U *
           sizeof(boolean_T));
    accsubsystem_1_qpkwik(b_Linv, b_Hinv, f, b_Ac, Bc, rtb_iAout, 400, 1.0E-6,
                          rtb_xest, b_Mx, &i);
    if ((i < 0) || (i == 0)) {
      rtb_xest[0] = 0.0;
    }

    accsubsystem_1_DW.last_mv_DSTATE += rtb_xest[0];
  }

  /* Outport: '<Root>/Longitudinal acceleration' incorporates:
   *  Gain: '<S13>/umin_scale1'
   *  MATLAB Function: '<S33>/optimizer'
   */
  accsubsystem_1_Y.Longitudinalacceleration = accsubsystem_1_P.umin_scale1_Gain *
    accsubsystem_1_DW.last_mv_DSTATE;

  /* MATLAB Function: '<S1>/DataTypeConversion_atrack' incorporates:
   *  Constant: '<S1>/External control signal constant'
   */
  accsubsys_DataTypeConversion_L0
    (accsubsystem_1_P.Externalcontrolsignalconstant_V, &rtb_y_e);

  /* MATLAB Function: '<S33>/optimizer' incorporates:
   *  Memory: '<S13>/last_x'
   */
  rtb_y_e = accsubsystem_1_DW.last_x_PreviousInput[1];
  rtb_y_fb = accsubsystem_1_DW.last_x_PreviousInput[0];
  rtb_y_j = accsubsystem_1_DW.last_x_PreviousInput[2];
  rtb_y = accsubsystem_1_DW.last_x_PreviousInput[3];
  for (i = 0; i < 4; i++) {
    xk[i] = (((c_a[i + 4] * rtb_y_e + c_a[i] * rtb_y_fb) + c_a[i + 8] * rtb_y_j)
             + c_a[i + 12] * rtb_y) + d_a[i] * accsubsystem_1_DW.last_mv_DSTATE;
  }

  rtb_y_e = 0.0;
  rtb_y_fb = 0.0;
  rtb_y = 0.0;
  rtb_y_cs = 0.0;
  for (i = 0; i < 2; i++) {
    rtb_y_j = rtb_TmpSignalConversionAtSFun_d[i];
    ii = i << 2;
    rtb_y_e += e_a[ii] * rtb_y_j;
    rtb_y_fb += e_a[ii + 1] * rtb_y_j;
    rtb_y += e_a[ii + 2] * rtb_y_j;
    rtb_y_cs += 0.0 * rtb_y_j;
  }

  rtb_xest[3] = rtb_y_cs;
  rtb_xest[2] = rtb_y;
  rtb_xest[1] = rtb_y_fb;
  rtb_xest[0] = rtb_y_e;

  /* Update for Memory: '<S13>/last_x' incorporates:
   *  MATLAB Function: '<S33>/optimizer'
   */
  for (i = 0; i < 4; i++) {
    accsubsystem_1_DW.last_x_PreviousInput[i] = (f_a[i + 4] * rtb_y_gf + f_a[i] *
      rtb_y_n) + (xk[i] + rtb_xest[i]);
  }

  /* End of Update for Memory: '<S13>/last_x' */

  /* Update for Memory: '<S13>/Memory' */
  memcpy(&accsubsystem_1_DW.Memory_PreviousInput[0], &rtb_iAout[0], 96U * sizeof
         (boolean_T));
}

/* Model initialize function */
void accsubsystem_1_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* InitializeConditions for Memory: '<S13>/last_x' */
  accsubsystem_1_DW.last_x_PreviousInput[0] =
    accsubsystem_1_P.last_x_InitialCondition[0];
  accsubsystem_1_DW.last_x_PreviousInput[1] =
    accsubsystem_1_P.last_x_InitialCondition[1];
  accsubsystem_1_DW.last_x_PreviousInput[2] =
    accsubsystem_1_P.last_x_InitialCondition[2];
  accsubsystem_1_DW.last_x_PreviousInput[3] =
    accsubsystem_1_P.last_x_InitialCondition[3];

  /* InitializeConditions for UnitDelay: '<S13>/last_mv' */
  accsubsystem_1_DW.last_mv_DSTATE = accsubsystem_1_P.last_mv_InitialCondition;

  /* InitializeConditions for Memory: '<S13>/Memory' */
  memcpy(&accsubsystem_1_DW.Memory_PreviousInput[0],
         &accsubsystem_1_P.Memory_InitialCondition[0], 96U * sizeof(boolean_T));
}

/* Model terminate function */
void accsubsystem_1_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
