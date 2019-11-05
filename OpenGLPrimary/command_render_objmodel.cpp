#include "command/command_render_objmodel.h"


LH_NAMESPACE_BEGIN

void RenderObjModelCommand::Render()
{

}

void RenderObjModelCommand::Init_i()
{
	mObjModel.Init("./res/Quad.obj");
}

LH_NAMESPACE_END