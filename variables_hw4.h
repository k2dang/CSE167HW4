// This is the basic include file for the global variables in the program.  
// Since all files need access to it, we define EXTERN as either blank or 
// extern, depending on if included in the main program or not.  

#ifdef MAINPROGRAM 
#define EXTERN 
#else 
#define EXTERN extern 
#endif

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
const int maxobjects = 10 ;
EXTERN int numobjects ; 
EXTERN struct object { 
  float size ;
  float posn[3];
  mat4 transform ; 
} objects[maxobjects] ;
EXTERN int maxverts ;
EXTERN int numverts ;
EXTERN struct vertices {
	float posn[3];
	mat4 transform;
} vertices[maxverts];
EXTERN int maxnormverts ;
EXTERN int numnormverts ;
EXTERN struct normvertices {
	float posn[6];
	mat4 transform;
} normvertices[maxnormverts];
EXTERN int numtri;
EXTERN int numnormtri;
EXTERN struct triangle {
	vertices v1, v2, v3;
	mat4 transform;
} triangle[numobjects];
EXTERN struct normtriangle {
	normvertices v1, v2, v3;
	mat4 transform;
} normtriangle[numobjects];

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

