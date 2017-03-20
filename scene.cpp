#include "variables.h"
#include "scene.h"
#include <math.h>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

// If this doesn't work, PUT AT THE BOTTOM AND TRY
// The main processor of the ray tracing
// Output: filmPixel will be filled with proper color codes to write to file
void Scene::Raytrace(Camera cam, int width, int height, float * filmPixel) {
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
      /*else {
			  filmPixel[(i * width * 3) + ((j * 3) + 0)] = 0;
			  filmPixel[(i * width * 3) + ((j * 3) + 1)] = 0;
   		  filmPixel[(i * width * 3) + ((j * 3) + 2)] = 255;
      }*/
			vec3 color = FindColor(cam, hit);
			filmPixel[(i * width * 3) + ((j * 3) + 0)] = 255*color.z;
   		filmPixel[(i * width * 3) + ((j * 3) + 1)] = 255*color.y;
   		filmPixel[(i * width * 3) + ((j * 3) + 2)] = 255*color.x;
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

Scene::Ray Scene::RayTransform(Ray ray, mat4 trans) {
  Scene::Ray retRay;
  /*const float *psource = (const float*)glm::value_ptr(trans);
  for(int i = 0; i < 16; i++)
    std::cout<<psource[i] << "  ";
  std::cout<<"\n";*/
  
  // Convert ray components into vec4
  vec4 ray4Origin = vec4(ray.origin.x, ray.origin.y, ray.origin.z, 1);
  vec4 ray4Dirn = vec4(ray.direction.x, ray.direction.y, ray.direction.z, 0);
  // compute transform wiith inverse transform M and ray
  vec4 tempOrigin = inverse(trans)*ray4Origin;
  vec4 tempDirn = inverse(trans)*ray4Dirn;

  // convert ray components back to vec3
  vec3 retOrigin = vec3(tempOrigin.x, tempOrigin.y, tempOrigin.z);
  vec3 retDirn = vec3(tempDirn.x, tempDirn.y, tempDirn.z);

  // Return ray
  retRay.origin = retOrigin;
  retRay.direction = retDirn;
  return retRay;
  
}

// Finds closest intersection to an object (if the ray intersects an object)
// Compute intersections differently for spheres & triangles
// Output: Returns the intersection of closest object or null if none???
Scene::Intersection Scene::Intersect(Ray ray) {
	// vec3 origin = ray.origin;
	// vec3 dirn = ray.direction;
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
    Ray tRay = RayTransform(ray, sp->transform);
    vec3 origin = tRay.origin;
    vec3 dirn = tRay.direction;
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
    }

		// Check if t is smaller than min t
		if (t > minT) 
			continue;

		// Compute intersection point & normal
		minT = t;
		vec3 Pos3 = origin + (dirn * t);
		vec3 N3 = (Pos3 - center) / length(Pos3 - center);

    // Convert Intersect components to vec4 to forawrd transform
    vec4 tempPos = vec4(Pos3.x, Pos3.y, Pos3.z, 1.0);
    vec4 tempNorm = vec4(N3.x, N3.y, N3.z, 1.0);

    // Forward transform position and inverse transpose normal
    vec4 intersectPos4 = sp->transform * tempPos;
    vec4 normal4 = inverse(transpose(sp->transform)) * tempNorm;
    vec3 intersectPos = vec3(intersectPos4.x, intersectPos4.y, intersectPos4.z);
    vec3 normal = vec3(normal.x, normal.y, normal.z);
		// DONT FORGET ABOUT MATERIAL!!!!
		retIntersect.position = intersectPos;
		retIntersect.normal = normal;
    retIntersect.objTrans = sp->transform;
    retIntersect.amb = sp->ambient;
		retIntersect.distance = minT;
	}

	/* For each triangle, find intersection */
	for (std::vector<Triangle>::iterator tri = triangleVect.begin(); 
			 tri != triangleVect.end(); ++tri) {

		float t; 
		vec3 A = vec3(tri->v1.posn[0], tri->v1.posn[1], tri->v1.posn[2]);
		vec3 B = vec3(tri->v2.posn[0], tri->v2.posn[1], tri->v2.posn[2]);
		vec3 C = vec3(tri->v3.posn[0], tri->v3.posn[1], tri->v3.posn[2]);

		vec3 normal = cross((C - A), (B - A)) / length(cross((C - A), (B - A)));
    
    Ray tRay = RayTransform(ray, tri->transform);
    vec3 origin = tRay.origin;
    vec3 dirn = tRay.direction;
		

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

    // Convert Intersect components to vec4 to transform
    vec4 p4 = vec4(P.x, P.y, P.z, 1);
    vec4 n4 = vec4(normal.x, normal.y, normal.z, 1);

    // Forward transform pos and inverse transpose normal
    vec4 ipos4 = tri->transform * p4;
    vec4 norm4 = inverse(transpose(tri->transform)) * n4;

    // Convert back to vec3
    vec3 p3 = vec3(ipos4.x, ipos4.y, ipos4.z);
    vec3 n3 = vec3(norm4.x, norm4.y, norm4.z);

		// DONT FORGET ABOUT MATERIAL!!!!
		retIntersect.position = p3;
		retIntersect.normal = n3;
    retIntersect.objTrans = tri->transform;
    retIntersect.amb = tri->ambient;
		retIntersect.distance = minT;
	}
	
	return retIntersect;
}

vec3 ComputeLight (vec3 direction, vec3 normal,
    vec3 halfvec, vec3 mydiffuse, vec3 myspecular, float myshininess) {

  float nDotL = dot(normal, direction);
  float maxl, maxh;
  if(nDotL > 0) maxl = nDotL;
  else maxl = 0.0;
  vec3 lambert = mydiffuse * maxl;

  float nDotH = dot(normal, halfvec);
  if(nDotH > 0.0) maxh = nDotH;
  else maxh = 0.0;
  float maxp = pow(maxh, myshininess);
  vec3 phong = myspecular * maxp;
  
  vec3 retVal = lambert + phong;
  return retVal;
}

vec3 Scene::FindColor(Camera cam, Intersection hit) {
  
  vec3 finalcolor = vec3(0.0);

  vec3 diff = vec3(diffuse[0], diffuse[1], diffuse[2]);
  vec3 spec = vec3(specular[0], specular[1], specular[2]);
  vec3 emi = vec3(emission[0], emission[1], emission[2]);
  vec3 att = vec3(attenuation[0], attenuation[1], attenuation[2]);
  vec3 amb = hit.amb;
  
  mat4 modelview = hit.objTrans;
  vec4 myvertex = vec4(hit.position, 1.0f);
  vec4 _mypos =  modelview * myvertex;
  vec3 mypos = vec3(_mypos.x/_mypos.w, _mypos.y/_mypos.w, _mypos.z/_mypos.w);
  vec3 eyedirn = normalize(cam.eye - mypos);

  // Compute Normal
  vec4 _normal = transpose(inverse(modelview))*vec4(hit.normal, 0.0f);
  vec3 m_norm = vec3(_normal.x, _normal.y, _normal.z);
  vec3 normal = normalize(m_norm);

  for (std::vector<DLight>::iterator dl = dirLightVect.begin(); 
			 dl != dirLightVect.end(); ++dl) {
    vec3 col = vec3(0.0);
    vec3 lightDir = vec3(dl->x, dl->y, dl->z);
    vec3 curLCol = vec3(dl->i, dl->j, dl->k);;
    vec3 direction = normalize(lightDir);
    vec3 half = normalize(direction + eyedirn);
    vec3 at = vec3(1, 0,0);
    vec3 tcol = ComputeLight(direction, normal,
        half, diff, spec, shininess);
    vec3 tat = curLCol / at;
    col = tat * tcol;
    finalcolor = finalcolor + col;
  }
  for (std::vector<PLight>::iterator pl = poiLightVect.begin(); 
			 pl != poiLightVect.end(); ++pl) {
    vec3 col = vec3(0.0);
    vec3 position = vec3(pl->x, pl->y, pl->z);
    vec3 curLCol = vec3(pl->i, pl->j, pl->k);
    vec3 direction = normalize(position - mypos);
    vec3 half = normalize(direction + eyedirn);
    vec3 at = vec3(att[0], att[1]*hit.distance, att[2]*hit.distance*hit.distance);
    vec3 tcol = ComputeLight(direction, normal,
        half, diff, spec, shininess);
    vec3 tat = curLCol / at;
    col = tat * tcol;
    finalcolor = finalcolor + col;
  }

  finalcolor = amb + emi + finalcolor;

  return finalcolor;
}

























