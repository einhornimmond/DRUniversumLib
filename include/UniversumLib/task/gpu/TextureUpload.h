#ifndef __UNIVERSUM_LIB_TASK_GPU_TEXTURE_UPLOAD_H
#define __UNIVERSUM_LIB_TASK_GPU_TEXTURE_UPLOAD_H

#include "Task.h"
#include "UniversumLib/view/Texture.h"
#include "UniversumLib/type/GPUTaskSpeedType.h"

namespace UniLib {
	namespace task {
		namespace gpu {
			/*
			* upload geometrie data to gpu
			*/
			class UNIVERSUMLIB_EXPORT TextureUpload : public Task
			{
			public:
				TextureUpload(view::Texture* textureView) : Task(GPUTaskSpeedType::LOAD), mTextureView(textureView) {}
				virtual ~TextureUpload() {};

				virtual DRReturn run();
				virtual const char* getResourceType() const { return "task::gpu::TextureUpload"; }

			protected:
				view::Texture* mTextureView;
			};
		}
	}
}

#endif // __UNIVERSUM_LIB_TASK_GPU_GEOMETRIE_UPLOAD_H