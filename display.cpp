/*****************************************************************************/
/* This is the program skeleton for homework 2 in CSE167 by Ravi Ramamoorthi */
/* Extends HW 1 to deal with shading, more transforms and multiple objects   */
/*****************************************************************************/

// This file is display.cpp.  It includes the skeleton for the display routine

// Basic includes to get this file to work.  
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Transform.h"

using namespace std; 
#include "variables.h"
#include "readfile.h"


void display() 
{
  glClearColor(0, 0, 1, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Set up the camera view

  // Either use the built-in lookAt function or the lookAt implemented by the user.

  modelview = Transform::lookAt(eye,center,up); 

  // rather than use a uniform variable for that.
  mat4 temp = modelview;
  for (int i = 0 ; i < numobjects ; i++) {
    object* obj = &(objects[i]); // Grabs an object struct.

    // YOUR CODE FOR HW 2 HERE. 
    // Set up the object transformations 
    // And pass in the appropriate material properties
    // Again glUniform() related functions will be useful
	
	modelview = temp;
    // Actually draw the object
    // We provide the actual drawing functions for you.  
    // Remember that obj->type is notation for accessing struct fields
	modelview =modelview* obj->transform;
  }
}
