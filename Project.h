#pragma once
#include "tests/tests.h"
#include "scene.h"

void loadTexture(GLuint& texture, std::string texturepath);
class Project : public scene {
	void init(void);

	int runTests(std::string value);

	
	float tPrev, LightAngle, lightRotationSpeed, Lightspeed, lightmovement;
	glm::vec4 LightPos;

	void setMatrices();
	void compile();
	void drawvfloor();
	void DrawSport(const glm::vec3& pos, float rough, int metal, const glm::vec3& color); // this is from a other project i did as well from comp3016 during my time of semsert 2

public:
	Project();
};