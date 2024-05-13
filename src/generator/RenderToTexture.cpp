#include "UniversumLib/generator/RenderToTexture.h"
#include "UniversumLib/view/Geometrie.h"
#include "UniversumLib/view/Material.h"
#include "UniversumLib/view/FrameBuffer.h"
#include "UniversumLib/view/Texture.h"
#include "UniversumLib/manager/BaseGeometries.h"
#include "UniversumLib/controller/BindToRenderer.h"
#include "UniversumLib/model/UniformSet.h"
#include "UniversumLib/model/ShaderProgram.h"
#include "UniversumLib/type/BaseGeometrieType.h"

#include "DRCore2/DRCore2Main.h"

namespace UniLib {
	namespace generator {
		RenderToTexture::RenderToTexture(view::TexturePtr texture)
		 : mTexture(texture) 
		{
			mFrameBuffer = g_RenderBinder->newFrameBuffer(texture);
		}
		RenderToTexture::RenderToTexture()
		{
			mFrameBuffer = g_RenderBinder->newFrameBuffer();
		}

		RenderToTexture::~RenderToTexture()
		{
			DR_SAVE_DELETE(mFrameBuffer);
		}

		bool RenderToTexture::isReady()
		{
			view::GeometriePtr geo;
			if (mGeometrie) {
				geo = mGeometrie;
			}
			if (!geo) {
				geo = manager::BaseGeometries::getInstance()->getGeometrie(BaseGeometrieType::PLANE);
			}
#ifdef DEBUG
			bool textureReady = mTexture->checkLoadingState() == LoadingStateType::FULLY_LOADED;
			bool materialReady = mMaterial->checkLoadingState() == LoadingStateType::FULLY_LOADED;
#endif //DEBUG
			return 
				mTexture->checkLoadingState() == LoadingStateType::FULLY_LOADED
				&& mMaterial->checkLoadingState() == LoadingStateType::FULLY_LOADED
			;
		}

		void RenderToTexture::setMaterial(view::MaterialPtr mat)
		{
			mMaterial = mat;
			model::UniformSet* uniforms = mMaterial->getUniformSet();
			if (!uniforms) {
				uniforms = g_RenderBinder->newUniformSet();
				mMaterial->setUniformSet(uniforms);
			}

			DRMatrix projection = DRMatrix::ortho_projection(0.0f, 1.0f, 0.0f, 1.0f, -1.0, 1.0);
			uniforms->setUniform("proj", projection);
			uniforms->addLocationToUniform("proj", mMaterial->getShaderProgram());			
		}

		DRReturn RenderToTexture::run()
		{
			// bind shader and texture
			mMaterial->bind();
			if (mFrameBuffer->isReady()) mFrameBuffer->bind();
			else mFrameBuffer->setup();
			//return DR_OK;
			if (render()) LOG_ERROR("error by rendering", DR_ERROR);
			return DR_OK;
		}
		DRReturn RenderToTexture::render()
		{
			view::GeometriePtr geo = nullptr;
			if (mGeometrie) {
				geo = mGeometrie;
			}
			if (!geo) {
				geo = manager::BaseGeometries::getInstance()->getGeometrie(BaseGeometrieType::PLANE);
			}
			return geo->render();
		}
	}
}