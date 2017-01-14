#pragma once

#include "Zeno/OpenGL.h"

#include "Zeno/Render/Texture.h"

#include "FreeImage.h"

class Texture : public Zeno::Texture
{
public:
	typedef std::shared_ptr< Texture > Ptr;

	static const Ptr s_kDefault;

	Texture();

	virtual ~Texture();

	virtual GLvoid Clear();

	static Ptr Create( GLenum Target, std::string FileName );

protected:
	virtual GLboolean LoadTexture();

private:
	FREE_IMAGE_FORMAT m_Format;

	FIBITMAP* m_pImage;

};
