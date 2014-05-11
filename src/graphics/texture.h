#pragma once


#include "core/string.h"
#include "core/resource.h"
#include "graphics/gl_ext.h"


namespace Lux
{
namespace FS
{
	class FileSystem;
}


class Texture : public Resource
{
	public:
		Texture(const Path& path, ResourceManager& resource_manager);
		~Texture();

		bool create(int w, int h);
		void apply(int unit = 0);

	private:
		void loaded(FS::IFile* file, bool success, FS::FileSystem& fs);
		bool loadDDS(FS::IFile& file);
		bool loadTGA(FS::IFile& file);

		virtual void doUnload(void) override;
		virtual FS::ReadCallback getReadCallback() override;

	private:
		GLuint m_id;
};


} // ~namespace Lux