#include "variables.h"
#include "scene.h"
#include <math.h>
#include <iostream>

// If this doesn't work, PUT AT THE BOTTOM AND TRY
// The main processor of the ray tracing
// Output: filmPixel will be filled with proper color codes to write to file
void Scene::Raytrace(Camera cam, int width, int height, int * filmPixel) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			Ray ray = RayThruPixel(cam, i, j);
			Intersection hit = Intersect(ray);
			// std::cerr << hit.distance << "\n";

			// Check if the ray hit anything (if not color is black)
			if (hit.distance == 0xFFFFFFFF) {
				filmPixel[(i * width * 3) + ((j * 3) + 0)] = 0;
				filmPixel[(i * width * 3) + ((j * 3) + 1)] = 0;
	   		filmPixel[(i * width * 3) + ((j * 3) + 2)] = 0;
			}

			// TEST: MAKE PTS THAT INTERSECT BLUE
      else {
			  filmPixel[(i * width * 3) + ((j * 3) + 0)] = 0;
			  filmPixel[(i * width * 3) + ((j * 3) + 1)] = 0;
   		  filmPixel[(i * width * 3) + ((j * 3) + 2)] = 255;
      }
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
	// vec3 wVec = glm::normalize(cam.eye);
	vec3 wVec = glm::normalize(cam.eye - cam.center);
	vec3 bxw = glm::cross(cam.up, wVec);
	vec3 uVec = glm::normalize(bxw);
	vec3 vVec = glm::cross(wVec, uVec);
	float pi = 3.1415926535;

	// Compute alpha & beta -> Use Radians
	float rad_fovy = ((pi * float(fovy)) / 180.0);
	float rad_fovx = rad_fovy  * (float(w) / float(h));
	float alpha = (tanf(rad_fovx / 2.0)) * ((float(width) - (float(w) / 2.0)) / (float(w) / 2.0)); 
	float beta = (tanf(rad_fovy / 2.0)) * (((float(h) / 2.0) - float(height)) / (float(h) / 2)); 

	// Create new Ray & return it
	vec3 origin = cam.eye;
	vec3 direction = ((alpha * uVec) + (beta * vVec) - wVec) /
									  (length((alpha * uVec) + (beta * vVec) - wVec));

	Scene::Ray r;
	r.origin = origin;
	r.direction = direction;
	return r; 
}


// Finds closest intersection to an object (if the ray intersects an object)
// Compute intersections differently for spheres & triangles
// Output: Returns the intersection of closest object or null if none???
Scene::Intersection Scene::Intersect(Ray ray) {
	vec3 origin = ray.origin;
	vec3 dirn = ray.direction;
	// To check for smallest dist 
	float minT = 0xFFFFFFFF;
	Intersection retIntersect;
	// Initally set retIntersect.distance = max size and check for that if ever changed
	retIntersect.distance = 0xFFFFFFFF; 

	/* For each schere, find intersection */
	for (std::vector<Sphere>::iterator sp = sphereVect.begin(); 
			 sp != sphereVect.end(); ++sp) {

		// Grab the radius and compute center of the sphere
		float radius = sp->radius;
		vec3 spcenter = vec3(sp->x, sp->y, sp->z);
		float t; 

		// Check discriminant to see if there is an intersection
		// float discriminant, discriminant_pt1, discriminant_pt2;
		// float r_sq = radius * radius;
		// discriminant_pt1 = dot(dirn, (origin - center)) * dot(dirn, (origin - center));
		// discriminant_pt2 = dot((dirn - center), (origin - center)) - r_sq;
		// discriminant = discriminant_pt1 - discriminant_pt2;

		// // Check if discriminant is < 0, No intersection
		// if (discriminant < 0) {
		// 	continue;
		// }
		
		// // Calculate roots
		// float root1 = dot(-dirn, (origin - center)) + sqrt(discriminant);
		// float root2 = dot(-dirn, (origin - center)) - sqrt(discriminant);

		float r_sq = radius * radius;
		vec3 Z = origin - spcenter;
		float disc_pt1 = 2 * (dot(dirn, Z));
		float discriminant_pt1 = disc_pt1 * disc_pt1;
		float discriminant_pt2 = 4 * dot(dirn, dirn) * (dot(Z, Z) - r_sq);
		float discriminant = discriminant_pt1 - discriminant_pt2;

		if (discriminant < 0) {
			continue;
		}

		float root1 = (-2 * dot(dirn, Z) + sqrt(discriminant)) / (2 * dot(dirn, dirn));
		float root2 = (-2 * dot(dirn, Z) - sqrt(discriminant)) / (2 * dot(dirn, dirn));


		// Check for 2 positive roots - pick smaller
		if ((root1 > 0) && (root2 > 0)) {
			if (root1 > root2)
				t = root2;
			else
				t = root1;
		}
		// Check for tangency - choose either
		else if (root1 == root2) {
			t = root1;
		}
		// One positive and one negative - pick pos root
		else {
			// if (root1 > 0)
			if ((root1 * root2) < 0) {
				if (root1 > 0)
					t = root1;
				else
					t = root2;
		}

		// Check if t is smaller than min t
		if (t > minT) 
			continue;

		// Compute intersection point & normal
		minT = t;
		vec3 intersectPos = origin + (dirn * t);
		vec3 normal = (intersectPos - center) / length(intersectPos - center);

		// DONT FORGET ABOUT MATERIAL!!!!
		retIntersect.position = intersectPos;
		retIntersect.normal = normal;
		retIntersect.distance = t;
			}
	}

	/* For each triangle, find intersection */
	for (std::vector<Triangle>::iterator tri = triangleVect.begin(); 
			 tri != triangleVect.end(); ++tri) {

		float t; 
		vec3 A = vec3(tri->v1.posn[0], tri->v1.posn[1], tri->v1.posn[2]);
		vec3 B = vec3(tri->v2.posn[0], tri->v2.posn[1], tri->v2.posn[2]);
		vec3 C = vec3(tri->v3.posn[0], tri->v3.posn[1], tri->v3.posn[2]);

		vec3 normal = cross((C - A), (B - A)) / length(cross((C - A), (B - A)));

		// Check if denominator < 0 -> no intersection
		float denominator = dot(dirn, normal);
		if (denominator == 0) {
			continue;
		}

		// Comput t distance
		t = (dot(A, normal) - dot(origin, normal)) / denominator;
		// Check if t is smaller than min t
		if (t > minT) {
			continue;
		}

		// Compute P -> intersectPos
		vec3 P = origin + (dirn * t);

		// Check that it actually intersects triangle
		float alpha;
		float beta;
		float gamma;
		float _t;

		vec3 l_side = origin - C;
		vec3 pt1 = -dirn;
		vec3 pt2 = A - C;
		vec3 pt3 = B - C;

		mat3 r_side = mat3(pt1[0], pt1[1], pt1[2],
						 					 pt2[0], pt2[1], pt2[2],
						 					 pt3[0], pt3[1], pt3[2]);
		r_side = glm::inverse(glm::transpose(r_side));

		vec3 t_alpha_beta = l_side * r_side;
		_t = t_alpha_beta[0];
		alpha = t_alpha_beta[1];
		beta = t_alpha_beta[2];
		gamma = 1.0 - alpha - beta;
		// P = alpha * A + beta * B + gamma * C;

		// alpha = ((0.5*length(cross(B-P, C-P))) / (0.5*length(cross(B-A, C-A))));
		// beta = ((0.5*length(cross(A-P, C-P))) / (0.5*length(cross(B-A, C-A))));

		// Do checks to see if triangle intersected 
		float epsilon = 0.0001;

		// Should I check t and _t?

		if (_t < epsilon)
			continue;					// No intersection 

		if (((alpha < 0) || (alpha > 1)) || ((beta < 0) || (beta > 1)) || 
							(gamma > 1) || (gamma < 0) ) {
			// std::cerr << "bug" << std::endl;
			continue;					// No intersection
		}

		// std::cerr << "lol";

		// Check if t is smaller than min t
		if (_t > minT) 
			continue;

		// Compute intersection point & normal
		minT = _t;	

		// DONT FORGET ABOUT MATERIAL!!!!
		retIntersect.position = P;
		retIntersect.normal = normal;
		retIntersect.distance = minT;
	}
	
	return retIntersect;
}


























