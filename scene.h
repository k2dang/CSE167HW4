// The class that manages the entire process and holds the screen to 
// manipulate
// #include "variables.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

typedef glm::vec3 vec3;

class Scene {
public:
	// For our ray tracer 
	struct Ray {
		vec3 origin;
		vec3 direction; 
	};
	struct Intersection {
		vec3 position;
		vec3 normal;
    mat4 objTrans;
    vec3 amb;
		// material * mat;
		float distance;
	};
	struct Camera {
		vec3 eye;
		vec3 up; 
		vec3 center;
	};

	void Raytrace(Camera cam, int width, int height, float * filmPixel);
	Ray RayThruPixel(Camera cam, int height, int width);
  Ray RayTransform(Ray ray, mat4 trans);
	Intersection Intersect(Ray ray);
  vec3 FindColor(Camera cam, Intersection hit);

};
