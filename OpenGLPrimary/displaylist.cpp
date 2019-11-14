#include "context/displaylist.h"



LH_NAMESPACE_BEGIN

void DisplayList::Init(std::function<void()> foo)
{
	mDisplayList = glGenLists(1); //新建显示列表

	//定义显示列表执行的东西
	glNewList(mDisplayList, GL_COMPILE);
	foo();
	glEndList();
}

void DisplayList::Draw()
{
	glCallList(mDisplayList); //显示列表绘制
}


LH_NAMESPACE_END