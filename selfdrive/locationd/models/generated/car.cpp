#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                       Code generated with sympy 1.8                        *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_1543763515856100254) {
   out_1543763515856100254[0] = delta_x[0] + nom_x[0];
   out_1543763515856100254[1] = delta_x[1] + nom_x[1];
   out_1543763515856100254[2] = delta_x[2] + nom_x[2];
   out_1543763515856100254[3] = delta_x[3] + nom_x[3];
   out_1543763515856100254[4] = delta_x[4] + nom_x[4];
   out_1543763515856100254[5] = delta_x[5] + nom_x[5];
   out_1543763515856100254[6] = delta_x[6] + nom_x[6];
   out_1543763515856100254[7] = delta_x[7] + nom_x[7];
   out_1543763515856100254[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5322435719520533216) {
   out_5322435719520533216[0] = -nom_x[0] + true_x[0];
   out_5322435719520533216[1] = -nom_x[1] + true_x[1];
   out_5322435719520533216[2] = -nom_x[2] + true_x[2];
   out_5322435719520533216[3] = -nom_x[3] + true_x[3];
   out_5322435719520533216[4] = -nom_x[4] + true_x[4];
   out_5322435719520533216[5] = -nom_x[5] + true_x[5];
   out_5322435719520533216[6] = -nom_x[6] + true_x[6];
   out_5322435719520533216[7] = -nom_x[7] + true_x[7];
   out_5322435719520533216[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_3799576479346241340) {
   out_3799576479346241340[0] = 1.0;
   out_3799576479346241340[1] = 0.0;
   out_3799576479346241340[2] = 0.0;
   out_3799576479346241340[3] = 0.0;
   out_3799576479346241340[4] = 0.0;
   out_3799576479346241340[5] = 0.0;
   out_3799576479346241340[6] = 0.0;
   out_3799576479346241340[7] = 0.0;
   out_3799576479346241340[8] = 0.0;
   out_3799576479346241340[9] = 0.0;
   out_3799576479346241340[10] = 1.0;
   out_3799576479346241340[11] = 0.0;
   out_3799576479346241340[12] = 0.0;
   out_3799576479346241340[13] = 0.0;
   out_3799576479346241340[14] = 0.0;
   out_3799576479346241340[15] = 0.0;
   out_3799576479346241340[16] = 0.0;
   out_3799576479346241340[17] = 0.0;
   out_3799576479346241340[18] = 0.0;
   out_3799576479346241340[19] = 0.0;
   out_3799576479346241340[20] = 1.0;
   out_3799576479346241340[21] = 0.0;
   out_3799576479346241340[22] = 0.0;
   out_3799576479346241340[23] = 0.0;
   out_3799576479346241340[24] = 0.0;
   out_3799576479346241340[25] = 0.0;
   out_3799576479346241340[26] = 0.0;
   out_3799576479346241340[27] = 0.0;
   out_3799576479346241340[28] = 0.0;
   out_3799576479346241340[29] = 0.0;
   out_3799576479346241340[30] = 1.0;
   out_3799576479346241340[31] = 0.0;
   out_3799576479346241340[32] = 0.0;
   out_3799576479346241340[33] = 0.0;
   out_3799576479346241340[34] = 0.0;
   out_3799576479346241340[35] = 0.0;
   out_3799576479346241340[36] = 0.0;
   out_3799576479346241340[37] = 0.0;
   out_3799576479346241340[38] = 0.0;
   out_3799576479346241340[39] = 0.0;
   out_3799576479346241340[40] = 1.0;
   out_3799576479346241340[41] = 0.0;
   out_3799576479346241340[42] = 0.0;
   out_3799576479346241340[43] = 0.0;
   out_3799576479346241340[44] = 0.0;
   out_3799576479346241340[45] = 0.0;
   out_3799576479346241340[46] = 0.0;
   out_3799576479346241340[47] = 0.0;
   out_3799576479346241340[48] = 0.0;
   out_3799576479346241340[49] = 0.0;
   out_3799576479346241340[50] = 1.0;
   out_3799576479346241340[51] = 0.0;
   out_3799576479346241340[52] = 0.0;
   out_3799576479346241340[53] = 0.0;
   out_3799576479346241340[54] = 0.0;
   out_3799576479346241340[55] = 0.0;
   out_3799576479346241340[56] = 0.0;
   out_3799576479346241340[57] = 0.0;
   out_3799576479346241340[58] = 0.0;
   out_3799576479346241340[59] = 0.0;
   out_3799576479346241340[60] = 1.0;
   out_3799576479346241340[61] = 0.0;
   out_3799576479346241340[62] = 0.0;
   out_3799576479346241340[63] = 0.0;
   out_3799576479346241340[64] = 0.0;
   out_3799576479346241340[65] = 0.0;
   out_3799576479346241340[66] = 0.0;
   out_3799576479346241340[67] = 0.0;
   out_3799576479346241340[68] = 0.0;
   out_3799576479346241340[69] = 0.0;
   out_3799576479346241340[70] = 1.0;
   out_3799576479346241340[71] = 0.0;
   out_3799576479346241340[72] = 0.0;
   out_3799576479346241340[73] = 0.0;
   out_3799576479346241340[74] = 0.0;
   out_3799576479346241340[75] = 0.0;
   out_3799576479346241340[76] = 0.0;
   out_3799576479346241340[77] = 0.0;
   out_3799576479346241340[78] = 0.0;
   out_3799576479346241340[79] = 0.0;
   out_3799576479346241340[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_505757690443295894) {
   out_505757690443295894[0] = state[0];
   out_505757690443295894[1] = state[1];
   out_505757690443295894[2] = state[2];
   out_505757690443295894[3] = state[3];
   out_505757690443295894[4] = state[4];
   out_505757690443295894[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_505757690443295894[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_505757690443295894[7] = state[7];
   out_505757690443295894[8] = state[8];
}
void F_fun(double *state, double dt, double *out_8408676881083716623) {
   out_8408676881083716623[0] = 1;
   out_8408676881083716623[1] = 0;
   out_8408676881083716623[2] = 0;
   out_8408676881083716623[3] = 0;
   out_8408676881083716623[4] = 0;
   out_8408676881083716623[5] = 0;
   out_8408676881083716623[6] = 0;
   out_8408676881083716623[7] = 0;
   out_8408676881083716623[8] = 0;
   out_8408676881083716623[9] = 0;
   out_8408676881083716623[10] = 1;
   out_8408676881083716623[11] = 0;
   out_8408676881083716623[12] = 0;
   out_8408676881083716623[13] = 0;
   out_8408676881083716623[14] = 0;
   out_8408676881083716623[15] = 0;
   out_8408676881083716623[16] = 0;
   out_8408676881083716623[17] = 0;
   out_8408676881083716623[18] = 0;
   out_8408676881083716623[19] = 0;
   out_8408676881083716623[20] = 1;
   out_8408676881083716623[21] = 0;
   out_8408676881083716623[22] = 0;
   out_8408676881083716623[23] = 0;
   out_8408676881083716623[24] = 0;
   out_8408676881083716623[25] = 0;
   out_8408676881083716623[26] = 0;
   out_8408676881083716623[27] = 0;
   out_8408676881083716623[28] = 0;
   out_8408676881083716623[29] = 0;
   out_8408676881083716623[30] = 1;
   out_8408676881083716623[31] = 0;
   out_8408676881083716623[32] = 0;
   out_8408676881083716623[33] = 0;
   out_8408676881083716623[34] = 0;
   out_8408676881083716623[35] = 0;
   out_8408676881083716623[36] = 0;
   out_8408676881083716623[37] = 0;
   out_8408676881083716623[38] = 0;
   out_8408676881083716623[39] = 0;
   out_8408676881083716623[40] = 1;
   out_8408676881083716623[41] = 0;
   out_8408676881083716623[42] = 0;
   out_8408676881083716623[43] = 0;
   out_8408676881083716623[44] = 0;
   out_8408676881083716623[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_8408676881083716623[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_8408676881083716623[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8408676881083716623[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8408676881083716623[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_8408676881083716623[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_8408676881083716623[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_8408676881083716623[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_8408676881083716623[53] = -9.8000000000000007*dt;
   out_8408676881083716623[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_8408676881083716623[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_8408676881083716623[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8408676881083716623[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8408676881083716623[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_8408676881083716623[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_8408676881083716623[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_8408676881083716623[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8408676881083716623[62] = 0;
   out_8408676881083716623[63] = 0;
   out_8408676881083716623[64] = 0;
   out_8408676881083716623[65] = 0;
   out_8408676881083716623[66] = 0;
   out_8408676881083716623[67] = 0;
   out_8408676881083716623[68] = 0;
   out_8408676881083716623[69] = 0;
   out_8408676881083716623[70] = 1;
   out_8408676881083716623[71] = 0;
   out_8408676881083716623[72] = 0;
   out_8408676881083716623[73] = 0;
   out_8408676881083716623[74] = 0;
   out_8408676881083716623[75] = 0;
   out_8408676881083716623[76] = 0;
   out_8408676881083716623[77] = 0;
   out_8408676881083716623[78] = 0;
   out_8408676881083716623[79] = 0;
   out_8408676881083716623[80] = 1;
}
void h_25(double *state, double *unused, double *out_2421938134280317232) {
   out_2421938134280317232[0] = state[6];
}
void H_25(double *state, double *unused, double *out_2138941943651888845) {
   out_2138941943651888845[0] = 0;
   out_2138941943651888845[1] = 0;
   out_2138941943651888845[2] = 0;
   out_2138941943651888845[3] = 0;
   out_2138941943651888845[4] = 0;
   out_2138941943651888845[5] = 0;
   out_2138941943651888845[6] = 1;
   out_2138941943651888845[7] = 0;
   out_2138941943651888845[8] = 0;
}
void h_24(double *state, double *unused, double *out_2538555682541301931) {
   out_2538555682541301931[0] = state[4];
   out_2538555682541301931[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4765841301227063104) {
   out_4765841301227063104[0] = 0;
   out_4765841301227063104[1] = 0;
   out_4765841301227063104[2] = 0;
   out_4765841301227063104[3] = 0;
   out_4765841301227063104[4] = 1;
   out_4765841301227063104[5] = 0;
   out_4765841301227063104[6] = 0;
   out_4765841301227063104[7] = 0;
   out_4765841301227063104[8] = 0;
   out_4765841301227063104[9] = 0;
   out_4765841301227063104[10] = 0;
   out_4765841301227063104[11] = 0;
   out_4765841301227063104[12] = 0;
   out_4765841301227063104[13] = 0;
   out_4765841301227063104[14] = 1;
   out_4765841301227063104[15] = 0;
   out_4765841301227063104[16] = 0;
   out_4765841301227063104[17] = 0;
}
void h_30(double *state, double *unused, double *out_5471001360604206127) {
   out_5471001360604206127[0] = state[4];
}
void H_30(double *state, double *unused, double *out_2009602996508648775) {
   out_2009602996508648775[0] = 0;
   out_2009602996508648775[1] = 0;
   out_2009602996508648775[2] = 0;
   out_2009602996508648775[3] = 0;
   out_2009602996508648775[4] = 1;
   out_2009602996508648775[5] = 0;
   out_2009602996508648775[6] = 0;
   out_2009602996508648775[7] = 0;
   out_2009602996508648775[8] = 0;
}
void h_26(double *state, double *unused, double *out_2434215309159873442) {
   out_2434215309159873442[0] = state[7];
}
void H_26(double *state, double *unused, double *out_1602561375222167379) {
   out_1602561375222167379[0] = 0;
   out_1602561375222167379[1] = 0;
   out_1602561375222167379[2] = 0;
   out_1602561375222167379[3] = 0;
   out_1602561375222167379[4] = 0;
   out_1602561375222167379[5] = 0;
   out_1602561375222167379[6] = 0;
   out_1602561375222167379[7] = 1;
   out_1602561375222167379[8] = 0;
}
void h_27(double *state, double *unused, double *out_1478428281378654797) {
   out_1478428281378654797[0] = state[3];
}
void H_27(double *state, double *unused, double *out_165160315291776136) {
   out_165160315291776136[0] = 0;
   out_165160315291776136[1] = 0;
   out_165160315291776136[2] = 0;
   out_165160315291776136[3] = 1;
   out_165160315291776136[4] = 0;
   out_165160315291776136[5] = 0;
   out_165160315291776136[6] = 0;
   out_165160315291776136[7] = 0;
   out_165160315291776136[8] = 0;
}
void h_29(double *state, double *unused, double *out_7633875477219314926) {
   out_7633875477219314926[0] = state[1];
}
void H_29(double *state, double *unused, double *out_2519834340823040959) {
   out_2519834340823040959[0] = 0;
   out_2519834340823040959[1] = 1;
   out_2519834340823040959[2] = 0;
   out_2519834340823040959[3] = 0;
   out_2519834340823040959[4] = 0;
   out_2519834340823040959[5] = 0;
   out_2519834340823040959[6] = 0;
   out_2519834340823040959[7] = 0;
   out_2519834340823040959[8] = 0;
}
void h_28(double *state, double *unused, double *out_1558357770065677888) {
   out_1558357770065677888[0] = state[0];
}
void H_28(double *state, double *unused, double *out_4483464612388367210) {
   out_4483464612388367210[0] = 1;
   out_4483464612388367210[1] = 0;
   out_4483464612388367210[2] = 0;
   out_4483464612388367210[3] = 0;
   out_4483464612388367210[4] = 0;
   out_4483464612388367210[5] = 0;
   out_4483464612388367210[6] = 0;
   out_4483464612388367210[7] = 0;
   out_4483464612388367210[8] = 0;
}
void h_31(double *state, double *unused, double *out_3798439048566696737) {
   out_3798439048566696737[0] = state[8];
}
void H_31(double *state, double *unused, double *out_2169587905528849273) {
   out_2169587905528849273[0] = 0;
   out_2169587905528849273[1] = 0;
   out_2169587905528849273[2] = 0;
   out_2169587905528849273[3] = 0;
   out_2169587905528849273[4] = 0;
   out_2169587905528849273[5] = 0;
   out_2169587905528849273[6] = 0;
   out_2169587905528849273[7] = 0;
   out_2169587905528849273[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_1543763515856100254) {
  err_fun(nom_x, delta_x, out_1543763515856100254);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5322435719520533216) {
  inv_err_fun(nom_x, true_x, out_5322435719520533216);
}
void car_H_mod_fun(double *state, double *out_3799576479346241340) {
  H_mod_fun(state, out_3799576479346241340);
}
void car_f_fun(double *state, double dt, double *out_505757690443295894) {
  f_fun(state,  dt, out_505757690443295894);
}
void car_F_fun(double *state, double dt, double *out_8408676881083716623) {
  F_fun(state,  dt, out_8408676881083716623);
}
void car_h_25(double *state, double *unused, double *out_2421938134280317232) {
  h_25(state, unused, out_2421938134280317232);
}
void car_H_25(double *state, double *unused, double *out_2138941943651888845) {
  H_25(state, unused, out_2138941943651888845);
}
void car_h_24(double *state, double *unused, double *out_2538555682541301931) {
  h_24(state, unused, out_2538555682541301931);
}
void car_H_24(double *state, double *unused, double *out_4765841301227063104) {
  H_24(state, unused, out_4765841301227063104);
}
void car_h_30(double *state, double *unused, double *out_5471001360604206127) {
  h_30(state, unused, out_5471001360604206127);
}
void car_H_30(double *state, double *unused, double *out_2009602996508648775) {
  H_30(state, unused, out_2009602996508648775);
}
void car_h_26(double *state, double *unused, double *out_2434215309159873442) {
  h_26(state, unused, out_2434215309159873442);
}
void car_H_26(double *state, double *unused, double *out_1602561375222167379) {
  H_26(state, unused, out_1602561375222167379);
}
void car_h_27(double *state, double *unused, double *out_1478428281378654797) {
  h_27(state, unused, out_1478428281378654797);
}
void car_H_27(double *state, double *unused, double *out_165160315291776136) {
  H_27(state, unused, out_165160315291776136);
}
void car_h_29(double *state, double *unused, double *out_7633875477219314926) {
  h_29(state, unused, out_7633875477219314926);
}
void car_H_29(double *state, double *unused, double *out_2519834340823040959) {
  H_29(state, unused, out_2519834340823040959);
}
void car_h_28(double *state, double *unused, double *out_1558357770065677888) {
  h_28(state, unused, out_1558357770065677888);
}
void car_H_28(double *state, double *unused, double *out_4483464612388367210) {
  H_28(state, unused, out_4483464612388367210);
}
void car_h_31(double *state, double *unused, double *out_3798439048566696737) {
  h_31(state, unused, out_3798439048566696737);
}
void car_H_31(double *state, double *unused, double *out_2169587905528849273) {
  H_31(state, unused, out_2169587905528849273);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_init(car);
