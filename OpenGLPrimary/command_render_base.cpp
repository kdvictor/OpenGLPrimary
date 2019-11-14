#include "command/command_render_base.h"
#include "context/context_helper.h"
#include "common_macrosh.h"

LH_NAMESPACE_BEGIN


RenderCommandBase::RenderCommandBase()
{
}

RenderCommandBase::~RenderCommandBase()
{
}

void RenderCommandBase::Render()
{

}

void RenderCommandBase::Init()
{
	this->Init_i();
}

LH_NAMESPACE_END