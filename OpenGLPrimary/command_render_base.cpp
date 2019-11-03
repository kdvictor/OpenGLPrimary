#include "command/command_render_base.h"
#include "context/texture.h"
#include "context/context_helper.h"

LH_NAMESPACE_BEGIN

void RenderCommandBase::Render()
{

}

void RenderCommandBase::Init()
{
	glMatrixMode(GL_PROJECTION);//该函数可以设置当前矩阵，GL_PROJECTION:投影矩阵
	gluPerspective(50.0f /*角度*/, 800 / 600/*画布宽高比*/, 0.1f/*最近看到的距离*/, 1000.0f/*最远看到的距离*/);//该函数影响当前矩阵，也可以说设置了当前矩阵
	glMatrixMode(GL_MODELVIEW);//将当前矩阵设置成模型视口矩阵
	glLoadIdentity();//不对模型视口矩阵做设置，加载一个单位矩阵
}

void RenderCommandBase::InitTexture()
{
	Texture textture;
	textture.Init("text.bmp");
}

LH_NAMESPACE_END