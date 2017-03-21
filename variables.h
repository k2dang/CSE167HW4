// This is the basic include file for the global variables in the program.  
// Since all files need access to it, we define EXTERN as either blank or 
// extern, depending on if included in the main program or not.  

#ifdef MAINPROGRAM 
#define EXTERN 
#else 
#define EXTERN extern 
#endif

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
typedef glm::mat3 mat3;
typedef glm::mat4 mat4;

EXTERN int amount; // The amount of rotation for each arrow press
EXTERN vec3 eye; // The (regularly updated) vector coordinates of the eye 
EXTERN vec3 up;  // The (regularly updated) vector coordinates of the up 
// const float pi = 3.1415926535;

#ifdef MAINPROGRAM 
vec3 eyeinit(0.0,0.0,5.0) ; // Initial eye position, also for resets
vec3 upinit(0.0,1.0,0.0) ; // Initial up position, also for resets
vec3 center(0.0,0.0,0.0) ; // Center look at point 
int amountinit = 5;
int w = 500, h = 500 ; // width and height 
int depth = 5;
float fovy = 90.0 ; // For field of view
#else 
EXTERN vec3 eyeinit ; 
EXTERN vec3 upinit ; 
EXTERN vec3 center ; 
EXTERN int amountinit;
EXTERN int w, h;
EXTERN int depth; 
EXTERN float fovy ; 
#endif 

EXTERN std::string outputst;
EXTERN mat4 projection, modelview; // The mvp matrices
EXTERN int projectionPos, modelviewPos; // Uniform locations of the above matrices
static enum {view, translate, scale} transop ; // which operation to transform 
enum shape {cube, sphere, teapot} ;
EXTERN float sx, sy ; // the scale in x and y 
EXTERN float tx, ty ; // the translation in x and y

// Lighting parameter array, similar to that in the fragment shader
EXTERN int numdlights ; 
struct DLight { 
  float x, y, z;
  float i, j, k; 
};
EXTERN int numplights ; 
struct PLight { 
  float x, y, z;
  float i, j, k;
};

EXTERN std::vector <DLight> dirLightVect;
EXTERN std::vector <PLight> poiLightVect;
//EXTERN GLfloat lightransf[4*numLights] ; // Lights transformed by modelview

// Materials (read from file) 
// With multiple objects, these are colors for each.
EXTERN float ambient[3] ; 
EXTERN float diffuse[3] ; 
EXTERN float specular[3] ; 
EXTERN float emission[3] ; 
EXTERN float shininess ; 
EXTERN float attenuation[3] ;

// For multiple objects, read from a file.  
// vertices 
EXTERN int numverts ;
EXTERN int maxverts ; 
struct Vertice {
	float posn[3];
	mat4 transform;
};
EXTERN int numnormverts ;
EXTERN int maxnormverts;
struct NormVertice {
	float posn[6];
	mat4 transform;
};
// spheres
EXTERN int numobjects ; 
struct Sphere { 
  float radius;
  float x, y, z;
  mat4 transform; 
  vec3 ambient;
};
// triangles
EXTERN int numtri;
EXTERN int numnormtri;
struct Triangle {
	Vertice v1, v2, v3;
	mat4 transform;
  vec3 ambient;
};
struct NormTriangle {
	NormVertice v1, v2, v3;
	mat4 transform;
  vec3 ambient;
};

EXTERN std::vector <Sphere> sphereVect;
EXTERN std::vector <Vertice> verticeVect; 
EXTERN std::vector <NormVertice> normverticeVect;
EXTERN std::vector <Triangle> triangleVect;
EXTERN std::vector <NormTriangle> normtriVect;

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

