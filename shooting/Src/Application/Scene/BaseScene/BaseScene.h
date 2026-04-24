#pragma once

class C_BaseScene
{
public:

	C_BaseScene(){}
	virtual ~C_BaseScene(){}

	virtual void Init()=0;
	virtual void Update()=0;
	virtual void Draw()=0;


private:



};