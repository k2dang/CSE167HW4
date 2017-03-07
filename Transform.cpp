// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
	// YOUR CODE FOR HW2 HERE Finished and Likely Working
	// Likely the same as in HW 1.
	float rad = ((pi*degrees) / 180);
	mat3 I(1.0);
	vec3 normAxis = glm::normalize(axis);
	mat3 part1 = cosf(rad)*I;
	mat3 part2 = mat3(pow(normAxis[0], 2), normAxis[0] * normAxis[1], normAxis[0] * normAxis[2],
		normAxis[0] * normAxis[1], pow(normAxis[1], 2), normAxis[1] * normAxis[2],
		normAxis[0] * normAxis[2], normAxis[1] * normAxis[2], pow(normAxis[2], 2));
	part2 = part2*(1 - cosf(rad));
	mat3 part3 = mat3(0, normAxis[2], -normAxis[1], -normAxis[2], 0, normAxis[0],
		normAxis[1], -normAxis[0], 0);
	part3 = part3*sinf(rad);
	mat3 retVal = part1 + part2 + part3;
	return retVal;;
}

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
    // YOUR CODE FOR HW2 HERE Finished and Likely Working
    // Likely the same as in HW 1.
	mat3 rotMat = rotate(degrees, up);
	eye = rotMat*eye;
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
    // YOUR CODE FOR HW2 HERE Finished and Likely Working
    // Likely the same as in HW 1.
	vec3 rotVec = glm::cross(eye, up);
	mat3 rotMat = rotate(degrees, rotVec);
	eye = rotMat*eye;
	up = rotMat*up;
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
    // YOUR CODE FOR HW2 HERE Finished and Likely Working
    // Likely the same as in HW 1.  
	vec3 wVec = glm::normalize(eye);
	vec3 bxw = glm::cross(up, wVec);
	vec3 uVec = glm::normalize(bxw);
	vec3 vVec = glm::cross(wVec, uVec);
	mat4 rMat = mat4(uVec[0], vVec[0], wVec[0], 0, uVec[1], vVec[1], wVec[1], 0,
		uVec[2], vVec[2], wVec[2], 0, 0, 0, 0, 1);
	mat4 tMat = mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -eye[0], -eye[1], -eye[2], 1);

	mat4 retMat = rMat*tMat;
	return retMat;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
	// YOUR CODE FOR HW2 HERE Finished and Likely Working
	// New, to implement the perspective transform as well. 
	mat4 retMat = mat4(0.0);
	float rad = ((pi*fovy) / 180);
	float sCoord = 1 / (tanf(rad / 2));
	float zmap1 = -((zFar + zNear) / (zFar - zNear));
	float zmap2 = -((2 * zFar*zNear) / (zFar - zNear));
	retMat = mat4(sCoord/aspect, 0, 0, 0, 0, sCoord, 0, 0,
		0, 0, zmap1, -1, 0, 0, zmap2, 0);

    return retMat;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
	// YOUR CODE FOR HW2 HERE Finished and Likely Working
    // Implement scaling
    mat4 ret = mat4(0.0);
	ret = mat4(sx, 0, 0, 0, 0, sy, 0, 0, 0, 0, sz, 0, 0, 0, 0, 1);
    return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
    // YOUR CODE FOR HW2 HERE Finished and Likely Working
    // Implement translation 
	mat4 ret = mat4(0.0);
	ret = mat4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, tx, ty, tz, 1);
    return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
    vec3 x = glm::cross(up,zvec); 
    vec3 y = glm::cross(zvec,x); 
    vec3 ret = glm::normalize(y); 
    return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
