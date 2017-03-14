#include "scene.h"
#include "Ray.cpp"

// If this doesn't work, PUT AT THE BOTTOM AND TRY
// The main processor of the ray tracing
// Output: filmPixel will be filled with proper color codes to write to file
void scene::Raytrace(Camera cam, vec3 scene, int width, int height) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j + 3) {
			Ray ray = RayThruPixel(cam, i, j);
			// What if no intersection??
			Intersection hit = Intersect(ray);

			vec3 color = FindColor(hit);
			filmPixel[j][i] = color[0];
			filmPixel[j + 1][i] = color[1];
			filmPixel[j + 2][i] = color[2];
		}
	}
}


// Generate the primary ray for a certain pixel
// Output: Returns the ray from the camera that goes through a certain pixel
Ray scene::RayThruPixel(Camera cam, int height, int height) {
	// Compute u v & w
	vec3 wVec = glm::normalize(cam->eye);
	vec3 bxw = glm::cross(cam->up, wVec);
	vec3 uVec = glm::normalize(bxw);
	vec3 vVec = glm::cross(wVec, uVec);

	// Compute alpha & beta
	// Remember to use Radians
	// pi & fovx/fovy ?!?!??!?!?!?!!?!?!?!?!?!?!?!?!?!?!?!
	float rad_fovy = ((pi * fovy) / 180);
	float rad_fovx = rad_fovy  * (float(w) / h);
	vec3 alpha = (tanf(rad_fovx / 2.0)) * ((width - (w / 2.0)) / (w / 2.0)); 
	vec3 beta = (tanf(rad_fovy / 2.0)) * (((h / 2.0) - height) / (h - 2)); 

	// Create new Ray & return it
	vec3 origin = cam->eye;
	vec3 direction = ((alpha * uVec) + (beta * vVec) - wVec) /
									  (abs((alpha * uVec) + (beta * vVec) - wVec));
	r = new Ray;
	r->origin = origin;
	r->direction = direction;
	return r; 
}


// Finds closest intersection to an object (if the ray intersects an object)
// Compute intersections differently for spheres & triangles
// Output: Returns the intersection of closest object or null if none???
Intersection scene::Intersect(Ray ray) {

	// For each object
	// indent after you add the for loop!!!
	if ()



}


























