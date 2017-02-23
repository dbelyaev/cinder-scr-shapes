#ifndef SHAPE_H_
#define SHAPE_H_

#include <vector>

#include <glm/glm.hpp> // vec2

#include <cinder/Color.h>

#include "suBox2D.h"

using std::vector;
using std::array;
using glm::vec2;
using ci::Color;

class Shape
{
public:
	Shape(b2::Sandbox* aSanbox, b2::Scale* aScale);
	~Shape();

public:
	void update();
	void draw();

private:
	b2::Sandbox* mSandbox;
	b2::Scale* mScale;

	vector<b2::unique_body_ptr> mPoints;
	vector<vector<vec2>> mPositionsToDraw;

	Color mColor;
};

#endif // SHAPE_H_