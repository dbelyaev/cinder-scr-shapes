#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>

using namespace ci;
using namespace ci::app;

// in DEBUG mode run as normal app in a window
// in release start as screen saver
#ifdef  _DEBUG
#include "cinder/app/App.h"
class CinderApp : public App
#else
#include <cinder/app/AppScreenSaver.h>
class CinderApp : public AppScreenSaver
#endif // _DEBUG
{
public:
	void setup() override;
	void update() override;
	void draw() override;

protected:
	ci::Color mBackgroundColor;
};

void CinderApp::setup()
{
	mBackgroundColor = Color(0, 1, 0);
}

void CinderApp::update()
{
	// update routines here
}

void CinderApp::draw()
{
	gl::clear(mBackgroundColor);
}

#ifdef  _DEBUG
CINDER_APP(CinderApp, RendererGl)
#else
CINDER_APP_SCREENSAVER(CinderApp, RendererGl)
#endif // _DEBUG