// Transform.cpp: implementation of the Transform class.


#include "Transform.h"


//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	// YOUR CODE FOR HW1 HERE
  
    glm::mat3 R;
    glm::mat3 I = mat3(1.0);
    glm::mat3 Rotation_1 = glm::mat3(axis.x*axis.x, axis.x*axis.y, axis.x*axis.z,
                                axis.x*axis.y, axis.y*axis.y, axis.y*axis.z,
                                axis.x*axis.z, axis.y*axis.z, axis.z*axis.z);
    float cosValue = glm::cos(glm::radians(degrees));
    float sinValue = glm::sin(glm::radians(degrees));
    mat3 dualMatrix = glm::mat3(0.0, axis.z, -axis.y,
                           -axis.z, 0.0, axis.x,
                           axis.y, -axis.x, 0.0);
    R = glm::mat3(I * cosValue + Rotation_1 * (1-cosValue) + sinValue * dualMatrix);
    
	// You will change this return call
	return R;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
	// YOUR CODE FOR HW1 HERE
    glm::mat3 rotation = rotate(degrees, glm::normalize(up)); //rotate aroung up vector
    eye = rotation * eye;
    return;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	// YOUR CODE FOR HW1 HERE
    glm::vec3 axis = glm::normalize(glm::cross(eye,up));
    glm::mat3 rotation = rotate(degrees, axis);
    up = rotation * up;
    eye = rotation * eye;
    return;
    
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
	// YOUR CODE FOR HW1 HERE
    //assume center is at origin
    vec3 Zaxis = glm::normalize(eye);
    vec3 Yaxis = glm::normalize(glm::cross(up,eye));
    vec3 Xaxis = glm::normalize(glm::cross(Xaxis,Yaxis));
    //use these three orthnormal vectors to define a rotation matrix
    glm::mat4 rotation = glm::mat4(Xaxis.x, Xaxis.y, Xaxis.z, 0.0,
                         Yaxis.x, Yaxis.y, Yaxis.z, 0.0,
                         Zaxis.x, Zaxis.y, Zaxis.z, 0.0,
                         0.0, 0.0, 0.0, 1.0);
    rotation = glm::transpose(rotation);
    glm::mat4 transform = glm::mat4(1.0, 0.0, 0.0, -eye.x,
                                    0.0, 1.0, 0.0, -eye.y,
                                    0.0, 0.0, 1.0, -eye.z,
                                    0.0, 0.0, 0.0, 1.0);
    transform = glm::transpose(transform);
    glm::mat4 translation = glm::mat4(rotation * transform);

	// You will change this return call
	return translation;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
