#include "shape.h"

#include <cinder/app/AppScreenSaver.h>
#include <cinder/Rand.h>
#include <cinder/gl/gl.h>


using namespace ci;
using namespace ci::app;

const int NUM_SEGMENTS = 3;	// how many segments will every shape element use
const int NUM_BACKLOG = 10;	// how many trailing shapes to draw
const float RADIUS = 0.01f;	// pre-defined radius, smaller to avoid un-needed collisions between elements


Shape::Shape(b2::Sandbox* aSanbox, b2::Scale* aScale)
	: mSandbox(aSanbox)
	, mScale(aScale)
{
	mColor = Color(Rand::randFloat(1.f), Rand::randFloat(1.f), Rand::randFloat(1.f));

	init();
}

Shape::~Shape()
{
}

/* Init objects */
void
Shape::init()
{
	clear();

	// init physical entities to simulate
	for (int i = 0; i < NUM_SEGMENTS; ++i)
	{
		// generate random position (inside of window) and velocity (scaled to window' dimensions)
		vec2 randPos = vec2(Rand::randFloat(RADIUS, (float) getWindowWidth()), Rand::randFloat(RADIUS, (float) getWindowHeight()));
		mPoints.emplace_back(mSandbox->createCircle(mScale->toPhysics(randPos), RADIUS));
	}

	// set initial velocity on objects
	for (auto const& circle : mPoints)
	{
		b2Vec2 randVelocity = b2Vec2(Rand::randFloat(1.f, getWindowHeight() * 0.005f), Rand::randFloat(1.f, getWindowHeight() * 0.005f));
		circle->SetLinearDamping(0.f);
		circle->SetLinearVelocity(randVelocity);
	}
}

/* Clear all objects */
void
Shape::clear()
{
	mPoints.clear();
	mPositionsToDraw.clear();
}

void
Shape::update()
{
	vector<vec2> positions;
	for (auto const& point : mPoints)
	{
		vec2 pos = vec2(mScale->fromPhysics(point->GetPosition().x), mScale->fromPhysics(point->GetPosition().y));
		positions.push_back(pos);
	}

	// put obtained positions for shape elements into vector
	mPositionsToDraw.push_back(positions);

	// remove older data (no more than 10 elements in backlog)
	while (mPositionsToDraw.size() > NUM_BACKLOG)
		mPositionsToDraw.erase(mPositionsToDraw.begin());
}

void
Shape::draw()
{
	int counter = mPositionsToDraw.size();
	for (auto const& positions : mPositionsToDraw)
	{
		for (int i = 0; i < positions.size() - 1; ++i)
		{
			gl::color(ColorA(mColor, 1.f / (float) counter));	// transparency, smoothly fading out
			gl::drawLine(positions.at(i), positions.at(i + 1));
		}

		// draw last segment between last and first points
		gl::drawLine(positions.at(positions.size() - 1), positions.at(0));

		counter--;	// decrease counter, which will make it less transparent (0.f fully transparent, 1.f - fully drawn)
	}
}