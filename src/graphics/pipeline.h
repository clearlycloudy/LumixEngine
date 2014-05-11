#pragma once

#include "core/lux.h"
#include "core/delegate_list.h"
#include "core/resource.h"
#include "core/resource_manager_base.h"

namespace Lux
{
	
struct Component;
class FrameBuffer;
class ISerializer;
class Renderer;
class RenderScene;


namespace FS
{

class FileSystem;
class IFile;

}


class LUX_ENGINE_API PipelineManager : public ResourceManagerBase
{
public:
	PipelineManager() : ResourceManagerBase() {}
	~PipelineManager() {}

protected:
	virtual Resource* createResource(const Path& path) override;
	virtual void destroyResource(Resource& resource) override;
};


class LUX_ENGINE_API Pipeline : public Resource
{
	public:
		Pipeline(const Path& path, ResourceManager& resource_manager);
		virtual ~Pipeline() {}

		virtual bool deserialize(ISerializer& serializer) = 0;

		static Pipeline* create(Renderer& renderer);
		static void destroy(Pipeline* pipeline);
};


class LUX_ENGINE_API PipelineInstance abstract
{
	public:
		virtual ~PipelineInstance() {}

		virtual void render() = 0;
		virtual void resize(int w, int h) = 0;
		virtual FrameBuffer* getShadowmapFramebuffer() = 0;

		static PipelineInstance* create(Pipeline& src);
		static void destroy(PipelineInstance* pipeline);

		virtual void setRenderer(Renderer& renderer) = 0;
		virtual void setScene(RenderScene* scene) = 0;
		virtual RenderScene* getScene() = 0;
};


}