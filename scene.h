// The class that manages the entire process and holds the screen to 
// manipulate

#include "readfile.h"
#include "variables.h"

class Scene {
public:

	float filmPixels[3 * w][h]; 				// to output colors into the scene

	void Raytrace(Camera cam, vec3 scene, int width, int height);
	Ray RayThruPixel(Camera cam, int height, int height);

}
