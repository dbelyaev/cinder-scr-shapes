#include "shape.h"

#include <cinder/app/AppScreenSaver.h>
#include <cinder/Rand.h>
#include <cinder/gl/gl.h>

using namespace ci;
using namespace ci::app;

Shape::Shape(b2::Sandbox* aSanbox, b2::Scale* aScale)
	: mSandbox(aSanbox)
	, mScale(aScale)
{
	mColor = Color(Rand::randFloat(1.f), Rand::randFloat(1.f), Rand::randFloat(1.f));

	float radius = 0.01f;
	mCircle1 = mSandbox->createCircle(mScale->toPhysics(vec2(Rand::randFloat(radius, getWindowWidth()), Rand::randFloat(radius, getWindowHeight()))), mScale->toPhysics(radius));
	mCircle1->SetLinearDamping(0.f);
	mCircle1->SetLinearVelocity(b2Vec2(Rand::randFloat(1.f, getWindowHeight() * 0.005f), Rand::randFloat(1.f, getWindowHeight() * 0.005f)));

	mCircle2 = mSandbox->createCircle(mScale->toPhysics(vec2(Rand::randFloat(radius, getWindowWidth()), Rand::randFloat(radius, getWindowHeight()))), mScale->toPhysics(radius));
	mCircle2->SetLinearDamping(0.f);
	mCircle2->SetLinearVelocity(b2Vec2(Rand::randFloat(1.f, getWindowHeight() * 0.005f), Rand::randFloat(1.f, getWindowHeight() * 0.005f)));

	mCircle3 = mSandbox->createCircle(mScale->toPhysics(vec2(Rand::randFloat(radius, getWindowWidth()), Rand::randFloat(radius, getWindowHeight()))), mScale->toPhysics(radius));
	mCircle3->SetLinearDamping(0.f);
	mCircle3->SetLinearVelocity(b2Vec2(Rand::randFloat(1.f, getWindowHeight() * 0.005f), Rand::randFloat(1.f, getWindowHeight() * 0.005f)));
}

Shape::~Shape()
{
}

void Shape::update()
{
	//counter++;

	//if (counter == 2)
	//{
	array<vec2, 3> pos;
	pos[0] = vec2(mScale->fromPhysics(mCircle1->GetPosition().x), mScale->fromPhysics(mCircle1->GetPosition().y));
	pos[1] = vec2(mScale->fromPhysics(mCircle2->GetPosition().x), mScale->fromPhysics(mCircle2->GetPosition().y));
	pos[2] = vec2(mScale->fromPhysics(mCircle3->GetPosition().x), mScale->fromPhysics(mCircle3->GetPosition().y));
	mPoints.push_back(pos);

	while (mPoints.size() > 10)
		mPoints.erase(mPoints.begin());

	//counter = 0;
	//}
}

void Shape::draw()
{
	int counter = mPoints.size();
	for (vector<array<vec2, 3>>::iterator it = mPoints.begin(); it != mPoints.end(); ++it)
	{
		gl::color(ColorA(mColor, 1.f / (float)counter));
		gl::drawLine(it->at(0), it->at(1));
		gl::drawLine(it->at(1), it->at(2));
		gl::drawLine(it->at(2), it->at(0));

		counter--;
	}
}