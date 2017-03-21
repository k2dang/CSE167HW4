#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include <vector>
// #include "include/GL/glew.h"
// #include "include/GL/glut.h"
#include "Transform.h"
#include "include/FreeImage.h"
#include "scene.h"

using namespace std ; 

// Main variables in the program.  
#define MAINPROGRAM 
#include "variables.h" 
#include "readfile.h" // prototypes for readfile.cpp  
void display(void) ;  // prototype for display function.  

// // Reshapes the window
// void reshape(int width, int height){
//   w = width;
//   h = height;

//   glViewport(0, 0, w, h);

//   float aspect = (float) w / (float) h, zNear = 0.1, zFar = 99.0 ;
//   // I am changing the projection matrix to fit with the new window aspect ratio
//   if (useGlu) projection = glm::perspective(glm::radians(fovy),aspect,zNear,zFar) ; 
//   else {
// 	  projection = Transform::perspective(fovy,aspect,zNear,zFar) ;
//   }
//   // Now send the updated projection matrix to the shader
//   glUniformMatrix4fv(projectionPos, 1, GL_FALSE, &projection[0][0]);
// }

// void saveScreenshot(string fname) {
//   int pix = w * h;
//   BYTE *pixels = new BYTE[3*pix];	
//   glReadBuffer(GL_FRONT);
//   glReadPixels(0,0,w,h,GL_BGR,GL_UNSIGNED_BYTE, pixels);

//   FIBITMAP *img = FreeImage_ConvertFromRawBits(pixels, w, h, w * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);

//   std::cout << "Saving screenshot: " << fname << "\n";

//   FreeImage_Save(FIF_PNG, img, fname.c_str(), 0);
//   delete pixels;
// }


// void printHelp() {
//   std::cout << "\npress 'h' to print this message again.\n" 
//     << "press '+' or '-' to change the amount of rotation that\noccurs with each arrow press.\n" 
//     << "press 'i' to run image grader test cases\n"
//     << "press 'g' to switch between using glm::lookAt and glm::Perspective or your own LookAt.\n"       
//     << "press 'r' to reset the transformations.\n"
//     << "press 'v' 't' 's' to do view [default], translate, scale.\n"
//     << "press ESC to quit.\n" ;      
// }


// void keyboard(unsigned char key, int x, int y) {
//   switch(key) {
//     case '+':
//       amount++;
//       std::cout << "amount set to " << amount << "\n" ;
//       break;
//     case '-':
//       amount--;
//       std::cout << "amount set to " << amount << "\n" ; 
//       break;
//     case 'i':
//       if(useGlu) {
//         std::cout << "Please disable glm::LookAt by pressing 'g'"
//           << " before running tests\n";
//       }
//       else if(!allowGrader) {
//         std::cout << "Error: no input file specified for grader\n";
//       } else {
//         std::cout << "Running tests...\n";
//         grader.runTests();
//         std::cout << "Done! [ESC to quit]\n";
//       }
//       break;
//     case 'g':
//       useGlu = !useGlu;
//       reshape(w,h) ; 
//       std::cout << "Using glm::LookAt and glm::Perspective set to: " << (useGlu ? " true " : " false ") << "\n" ; 
//       break;
//     case 'h':
//       printHelp();
//       break;
//     case 27:  // Escape to quit
//       exit(0) ;
//       break ;
//     case 'r': // reset eye and up vectors, scale and translate. 
//       eye = eyeinit ; 
//       up = upinit ; 
//       amount = amountinit ;
//       transop = view ;
//       sx = sy = 1.0 ; 
//       tx = ty = 0.0 ; 
//       break ;   
//     case 'v': 
//       transop = view ;
//       std::cout << "Operation is set to View\n" ; 
//       break ; 
//     case 't':
//       transop = translate ; 
//       std::cout << "Operation is set to Translate\n" ; 
//       break ; 
//     case 's':
//       transop = scale ; 
//       std::cout << "Operation is set to Scale\n" ; 
//       break ; 
//   }
//   glutPostRedisplay();
// }

//  You will need to enter code for the arrow keys 
//  When an arrow key is pressed, it will call your transform functions

// void specialKey(int key, int x, int y) {
//   switch(key) {
//     case 100: //left
//       if (transop == view) Transform::left(amount, eye,  up);
//       else if (transop == scale) sx -= amount * 0.01 ; 
//       else if (transop == translate) tx -= amount * 0.01 ; 
//       break;
//     case 101: //up
//       if (transop == view) Transform::up(amount,  eye,  up);
//       else if (transop == scale) sy += amount * 0.01 ; 
//       else if (transop == translate) ty += amount * 0.01 ; 
//       break;
//     case 102: //right
//       if (transop == view) Transform::left(-amount, eye,  up);
//       else if (transop == scale) sx += amount * 0.01 ; 
//       else if (transop == translate) tx += amount * 0.01 ; 
//       break;
//     case 103: //down
//       if (transop == view) Transform::up(-amount,  eye,  up);
//       else if (transop == scale) sy -= amount * 0.01 ; 
//       else if (transop == translate) ty -= amount * 0.01 ; 
//       break;
//   }
//   glutPostRedisplay();
// }

// void init() {
//   // Initialize shaders
//   vertexshader = initshaders(GL_VERTEX_SHADER, "shaders/light.vert.glsl") ;
//   fragmentshader = initshaders(GL_FRAGMENT_SHADER, "shaders/light.frag.glsl") ;
//   shaderprogram = initprogram(vertexshader, fragmentshader) ; 
//   // Get locations of all uniform variables.
//   enablelighting = glGetUniformLocation(shaderprogram,"enablelighting") ;
//   lightpos = glGetUniformLocation(shaderprogram,"lightposn") ;       
//   lightcol = glGetUniformLocation(shaderprogram,"lightcolor") ;       
//   numusedcol = glGetUniformLocation(shaderprogram,"numused") ;       
//   ambientcol = glGetUniformLocation(shaderprogram,"ambient") ;       
//   diffusecol = glGetUniformLocation(shaderprogram,"diffuse") ;       
//   specularcol = glGetUniformLocation(shaderprogram,"specular") ;       
//   emissioncol = glGetUniformLocation(shaderprogram,"emission") ;       
//   shininesscol = glGetUniformLocation(shaderprogram,"shininess") ;    
//   projectionPos = glGetUniformLocation(shaderprogram, "projection");
//   modelviewPos = glGetUniformLocation(shaderprogram, "modelview");
//   // Initialize geometric shapes
//   initBufferObjects();
//   initTeapot(); initCube(); initSphere();
// }

int main(int argc, char* argv[]) {
  // Read in the file to get variables
  readfile(argv[1]);

  FreeImage_Initialise();

  // Create the pixel array to store colors
  //nt filmPixels[w * 3][h] = new int[][];
  //int * filmP = &filmPixels;  
  
  int numpix = w*h;
  float * filmPixels = new float[3*numpix];
  BYTE *pixelss = new BYTE[3*numpix];

  Scene s;

  Scene::Camera cam;
  cam.eye = eye;
  cam.up = up;
  cam.center = center;

  // Have Raytrace do the work to fill the filmPixels
  s.Raytrace(cam, w, h, filmPixels);  

  // Convert pixel double array to a single array
  // std::vector <int> temp;
  // for (int i = 0; i < 3 * w; i++) {
  //   for (int j = 0; j < h; j++) 
  //     temp.push_back(filmPixels[i][j]);
  // }
  // int * pixels = &temp[0];

  for (int he = 0; he < h; he++){
    for (int wi = 0; wi < w; wi++){
      pixelss[(he * w * 3) + ((wi * 3) + 0)] = filmPixels[(he * w * 3) + ((wi * 3) + 0)];
      pixelss[(he * w * 3) + ((wi * 3) + 1)] = filmPixels[(he * w * 3) + ((wi * 3) + 1)];
      pixelss[(he * w * 3) + ((wi * 3) + 2)] = filmPixels[(he * w * 3) + ((wi * 3) + 2)];
    }
  }


  // for (int x = 0; x < numpix; x++){
  //   pixelss[x*3] = filmPixels[x];
  //   pixelss[x*3+1] = filmPixels[x+1];
  //   pixelss[x*3+2] = filmPixels[x+2];
  // }
  

  // for (int x = 0; x < numpix; x++) {
		// pixelss[x*3] = 0;
		// pixelss[x*3+1] = 0;
		// pixelss[x*3+2] = 255;
  // }
  FIBITMAP *img = FreeImage_ConvertFromRawBits(pixelss, w, h, w * 3, 24, 
                                               0xFF0000, 0x00FF00, 0x0000FF, true);
  if(FreeImage_Save(FIF_PNG, img, outputst.c_str(), 0))
	std::cout<<"\nImage saved successfully\n";    

  FreeImage_DeInitialise();
  return 0;
}
