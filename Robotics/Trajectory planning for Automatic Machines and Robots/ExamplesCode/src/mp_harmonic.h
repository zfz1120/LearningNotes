/*harmonic_rajectory*/
#ifndef MP_HAMONIC_H_
#define MP_HAMONIC_H_

#ifdef __cplusplus
extern "C" {
#endif // 
extern struct input_para;
extern struct mp_para;

int mp_harmonic_traj(const input_para *input,mp_para *output);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif