#include <math.h>

#include <vector.h>

t_mat4 *mat4_frustum(float left, float right, float bottom, float top, float near, float far, t_mat4 *dest) {
    float rl = (right - left);
    float tb = (top - bottom);
    float fn = (far - near);
    dest->raw[0] = (near * 2) / rl;
    dest->raw[1] = 0;
    dest->raw[2] = 0;
    dest->raw[3] = 0;
    dest->raw[4] = 0;
    dest->raw[5] = (near * 2) / tb;
    dest->raw[6] = 0;
    dest->raw[7] = 0;
    dest->raw[8] = (right + left) / rl;
    dest->raw[9] = (top + bottom) / tb;
    dest->raw[10] = -(far + near) / fn;
    dest->raw[11] = -1;
    dest->raw[12] = 0;
    dest->raw[13] = 0;
    dest->raw[14] = -(far * near * 2) / fn;
    dest->raw[15] = 0;
    return dest;
}

t_mat4 *mat4_perspective(float fovy, float aspect, float near, float far, t_mat4 *dest) {
    float top = near * tanf(fovy * 3.14159265358979323846f / 360.0f);
    float right = top * aspect;
    return mat4_frustum(-right, right, -top, top, near, far, dest);
}
