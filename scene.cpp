#include "variables.h"
#include "scene.h"
#include <iostream>

// If this doesn't work, PUT AT THE BOTTOM AND TRY
// The main processor of the ray tracing
// Output: filmPixel will be filled with proper color codes to write to file
void Scene::Raytrace(Camera cam, int width, int height, float ** filmPixel) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j + 3) {
			Ray ray = RayThruPixel(cam, i, j);
			Intersection hit = Intersect(ray);

			//vec3 color = FindColor(hit);
			// filmPixel->[j][i] = color[0];
			// filmPixel->[j + 1][i] = color[1];
			// filmPixel->[j + 2][i] = color[2];
		}
	}
}


// Generate the primary ray for a certain pixel
// Output: Returns the ray from the camera that goes through a certain pixel
Scene::Ray Scene::RayThruPixel(Camera cam, int height, int width) {
	// Compute u v & w
	vec3 wVec = glm::normalize(cam.eye);
	vec3 bxw = glm::cross(cam.up, wVec);
	vec3 uVec = glm::normalize(bxw);
	vec3 vVec = glm::cross(wVec, uVec);
	float pi = 3.1415926535;

	// Compute alpha & beta -> Use Radians
	float rad_fovy = ((pi * fovy) / 180);
	float rad_fovx = rad_fovy  * (float(w) / h);
	float alpha = (tanf(rad_fovx / 2.0)) * ((width - (w / 2.0)) / (w / 2.0)); 
	float beta = (tanf(rad_fovy / 2.0)) * (((h / 2.0) - height) / (h - 2)); 

	// Create new Ray & return it
	vec3 origin = cam.eye;
	vec3 direction = ((alpha * uVec) + (beta * vVec) - wVec) /
									  (abs((alpha * uVec) + (beta * vVec) - wVec));
	Scene::Ray r;
	r.origin = origin;
	r.direction = direction;
	return r; 
}


// Finds closest intersection to an object (if the ray intersects an object)
// Compute intersections differently for spheres & triangles
// Output: Returns the intersection of closest object or null if none???
Scene::Intersection Scene::Intersect(Ray ray) {

	// For each schere, find intersection
	for (std::vector<Sphere>::iterator sp = sphereVect.begin(); 
			 sp != sphereVect.end(); ++sp) {
		// Grab the radius and compute center of the sphere
		float radius = sp.radius;
		//vec3 center
	}




}


























