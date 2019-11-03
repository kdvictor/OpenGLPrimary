#include "context/texture.h"
#include "context/context_helper.h"

LH_NAMESPACE_BEGIN

void Texture::Init(const char* pImagePath)
{
	unsigned char* pImageContent = nullptr;
	pImageContent = ContextHelper::LoadFileContent(pImagePath);
	if (pImageContent == nullptr)
	{
		//log
		return;
	}


}

LH_NAMESPACE_END