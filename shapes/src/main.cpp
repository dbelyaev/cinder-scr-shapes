#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>
#include <cinder/Rand.h>

#include "suBox2D.h"

#include "shape.h"


using namespace ci;
using namespace ci::app;

const int AMOUNT = 3;


// in DEBUG mode run as normal app (Window)
// in RELEASE start as screen saver (full screen, exits on clicks\movement etc)
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
	void resize() override;

private:
	ci::Color mBackgroundColor;

	// Box2D
	b2::Sandbox mSandbox;	// wraps the b2World
	b2::Scale mScale;		// scale for mapping between physics and screen coordinates

	std::vector<std::unique_ptr<Shape>> mShapes;	// contains Shape instances
};

void
CinderApp::setup()
{
	ci::app::getWindow()->setTitle("cinder-scr-shapes");

	mBackgroundColor = Color(0, 0, 0);		// default background
	Rand::randSeed((int32_t) time(NULL));	// feed randomizer with seed

	// add boundary shape to simulation based on window' dimensions
	// (lifetime is managed by sandbox, will be destroyed when new boundary created)
	mSandbox.createBoundaryRect(mScale.toPhysics(Rectf{ getWindowBounds() }));
	mSandbox.setGravity(b2Vec2_zero);

	// initialize shape objects
	for (int i = 0; i < AMOUNT; i++)
		mShapes.push_back(std::unique_ptr<Shape>(new Shape(&mSandbox, &mScale)));
}

void
CinderApp::update()
{
	mSandbox.step();	// step in time

	for (auto const& shape : mShapes)
		shape->update();
}

void
CinderApp::draw()
{
	gl::clear(mBackgroundColor);

	for (auto const& shape : mShapes)
		shape->draw();
}

void
CinderApp::resize()
{
	// update boundaries corresponding to new window' dimensions
	mSandbox.createBoundaryRect(mScale.toPhysics(Rectf{ getWindowBounds() }));

	// re-init shape object according to new sandbox boundaries
	for (auto const& shape : mShapes)
		shape->init();
}

#ifdef  _DEBUG
CINDER_APP(CinderApp, RendererGl)
#else
CINDER_APP_SCREENSAVER(CinderApp, RendererGl)
#endif // _DEBUG