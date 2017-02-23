#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>

#include "suBox2D.h"

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

private:
	ci::Color mBackgroundColor;

	// Box2D
	b2::Sandbox mSandbox;	// wraps the b2World
	b2::Scale mScale;		// scale for mapping between physics and screen coordinates
};

void CinderApp::setup()
{
	mBackgroundColor = Color(0, 1, 0);

	// Add a boundary shape to the simulation.
	// This shape's lifetime is managed by the sandbox.
	// It will be destroyed if you create a new boundary rect.
	mSandbox.createBoundaryRect(mScale.toPhysics(Rectf{ getWindowBounds() }));
	mSandbox.setGravity(b2Vec2_zero);
}

void CinderApp::update()
{
	mSandbox.step();
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