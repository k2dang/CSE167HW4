// This is the basic include file for the global variables in the program.  
// Since all files need access to it, we define EXTERN as either blank or 
// extern, depending on if included in the main program or not.  

#ifdef MAINPROGRAM 
#define EXTERN 
#else 
#define EXTERN extern 
#endif

#include <vector>

EXTERN int amount; // The amount of rotation for each arrow press
EXTERN vec3 eye; // The (regularly updated) vector coordinates of the eye 
EXTERN vec3 up;  // The (regularly updated) vector coordinates of the up 

#ifdef MAINPROGRAM 
vec3 eyeinit(0.0,0.0,5.0) ; // Initial eye position, also for resets
vec3 upinit(0.0,1.0,0.0) ; // Initial up position, also for resets
vec3 center(0.0,0.0,0.0) ; // Center look at point 
int amountinit = 5;
int w = 500, h = 500 ; // width and height 
float fovy = 90.0 ; // For field of view
#else 
EXTERN vec3 eyeinit ; 
EXTERN vec3 upinit ; 
EXTERN vec3 center ; 
EXTERN int amountinit;
EXTERN int w, h, depth; 
EXTERN float fovy ; 
#endif 

EXTERN mat4 projection, modelview; // The mvp matrices
EXTERN int projectionPos, modelviewPos; // Uniform locations of the above matrices
static enum {view, translate, scale} transop ; // which operation to transform 
enum shape {cube, sphere, teapot} ;
EXTERN float sx, sy ; // the scale in x and y 
EXTERN float tx, ty ; // the translation in x and y

// Lighting parameter array, similar to that in the fragment shader
const int numLights = 10 ; 
EXTERN float dirlightposn [3*numLights] ; // Directional Light Positions
EXTERN float dirlightcol [3*numLights] ; // Directional Light Colors
EXTERN float poilightposn [3*numLights] ; // Point Light Positions
EXTERN float poilightcol [3*numLights] ;
//EXTERN GLfloat lightransf[4*numLights] ; // Lights transformed by modelview
EXTERN int numused ;                     // How many lights are used 

// Materials (read from file) 
// With multiple objects, these are colors for each.
EXTERN float ambient[3] ; 
EXTERN float diffuse[3] ; 
EXTERN float specular[3] ; 
EXTERN float emission[3] ; 
EXTERN float shininess[3] ; 
EXTERN float attenuation[3] ;

// For multiple objects, read from a file.  


// spheres
EXTERN int numobjects ; 
EXTERN struct sphere { 
  float size ;
  float posn[3];
  mat4 transform ; 
} ;
// vertices 
EXTERN int numverts ;
EXTERN int maxverts ; 
EXTERN struct vertice {
	float posn[3];
	mat4 transform;
};
EXTERN int numnormverts ;
EXTERN int maxnormverts;
EXTERN struct normvertice {
	float posn[6];
	mat4 transform;
};
// triangles
EXTERN int numtri;
EXTERN int numnormtri;
EXTERN struct triangle {
	struct vertice v1, v2, v3;
	mat4 transform;
};
EXTERN struct normtriangle {
	struct normvertice v1, v2, v3;
	mat4 transform;
};

EXTERN std::vector <sphere> sphereVect;
EXTERN std::vector <vertice> verticeVect; 
EXTERN std::vector <normvertice> normverticeVect;
EXTERN std::vector <triangle> triangleVect;
EXTERN std::vector <normtriangle> normtriVect;

// For our ray tracer 
EXTERN struct Ray {
	vec3 origin;
	vec3 direction; 
};
EXTERN struct Intersection {
	vec3 position;
	vec3 normal;
	// material * mat;
	float distance;
};
EXTERN struct Camera {
	vec3 eye;
	vec3 up; 
	vec3 center;
};

// Variables to set uniform params for lighting fragment shader 
EXTERN int lightcol ; 
EXTERN int lightpos ; 
EXTERN int numusedcol ; 
EXTERN int enablelighting ; 
EXTERN int ambientcol ; 
EXTERN int diffusecol ; 
EXTERN int specularcol ; 
EXTERN int emissioncol ; 
EXTERN int shininesscol ; 

