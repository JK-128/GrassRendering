#pragma once
#include "Object.h"
#include "../Graphics/CubeMap.h"

class SkyBox : public Object
{
private:
	CubeMap* m_cubemap;

public:
	SkyBox(std::string path = "Content/Textures/skybox", std::string type = ".jpg");
	~SkyBox();

	void draw();
	void setTexture(CubeMap* cMap);
};

