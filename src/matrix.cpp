#include "matrix.h"
#include <math.h>

//based on http://www.cs.cornell.edu/courses/cs4620/2012fa/lectures/05transformRotations.pdf
//and also https://www.cs.brandeis.edu/~cs155/Lecture_06.pdf
mat3 srotate(vec3 rot) {
	//first we make an orthonormal frame,
	//3 perpendicular unit vectors u, v, and w
	//u is parallell to rotation axis
	float a = length(rot);
	if (a == 0.0f) return mat3(1.0f);
	vec3 u = rot / a;
	vec3 v = normalize(cross(u, vec3(u[1], -u[0], u[2])));
	vec3 w = cross(v, u);
	
	mat3 F = transpose(mat3(u, v, w));
	//rotation around x-axis
	float cos = std::cos(a);
	float sin = std::sin(a);
	mat3 R(
		vec3(1.0f, 0.0f, 0.0f),
		vec3(0.0f, cos, sin),
		vec3(0.0f, -sin, cos)
	);
	
	//F sends u to x-axis
	return inverse(F) * R * F;
}

mat4 translateR(mat3 R, vec3 p) {
	mat4 result(0.0f);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result[i][j] = R[i][j];
		}
		result[3][i] = p[i];
	}
	result[3][3] = 1.0f;
	return result;
}