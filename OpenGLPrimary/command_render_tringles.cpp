#include "command/command_render_tringles.h"

LH_NAMESPACE_BEGIN

void RenderTringlesCommand::Render()
{
	glBegin(GL_TRIANGLES); //默认逆时针方向（ccw）
	glColor4ub(255.0, 0.0, 0.0, 255.0);//设置当前颜色
	glVertex3f(0.0f, 0.0f, -10.0f);
	glColor4ub(0.0, 255.0, 0.0, 255.0);
	glVertex3f(-3.0f, 0.0f, -10.0f);
	glColor4ub(0.0, 0.0, 255.0, 255.0);
	glVertex3f(-3.0f, -2.0f, -10.0f);
	glEnd();
}

LH_NAMESPACE_END