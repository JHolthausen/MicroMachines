#include "Camera.h"

using namespace Tmpl8;				// to use template classes
using namespace glm;				// to use glm vector stuff



Camera::Camera(RECT camView)
{
	this->camView = camView;

	width = camView.right - camView.left;
	height = camView.bottom - camView.top;




}


Camera::~Camera()
{

}
