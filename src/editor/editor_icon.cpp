#include "editor_icon.h"
#include "core/crc32.h"
#include "core/math_utils.h"
#include "core/matrix.h"
#include "graphics/irender_device.h"
#include "graphics/geometry.h"
#include "graphics/material.h"
#include "graphics/model.h"
#include "graphics/pipeline.h"
#include "graphics/renderer.h"

#include <gl/GL.h>

namespace Lux
{


	void EditorIcon::create(Renderer& renderer, Entity& entity, const Component&)
{
	m_entity = entity;
	m_model = renderer.getModel("models/icon.msh");
	m_is_visible = true;
}


void EditorIcon::destroy()
{
}


void EditorIcon::show()
{
	m_is_visible = true;
}


void EditorIcon::hide()
{
	m_is_visible = false;
}



float EditorIcon::hit(const Vec3& origin, const Vec3& dir) const
{
	if (m_is_visible)
	{
		RayCastModelHit hit = m_model->castRay(origin, dir, m_matrix, m_scale);
		return hit.m_is_hit ? hit.m_t : -1;
	}
	else
	{
		return -1;
	}
}


void EditorIcon::render(Renderer* renderer, IRenderDevice& render_device)
{
	if (m_is_visible)
	{
		Component camera = render_device.getPipeline().getCamera(0);
		Lux::Matrix mtx = camera.entity.getMatrix();

		float fov;
		renderer->getCameraFov(camera, fov);
		float scale = tan(fov * Math::PI / 180 * 0.5f) * (m_entity.getPosition() - mtx.getTranslation()).length() / 20;

		mtx.setTranslation(m_entity.getPosition());
		Matrix scale_mtx = Matrix::IDENTITY;
		m_matrix = mtx;
		scale_mtx.m11 = scale_mtx.m22 = scale_mtx.m33 = scale;
		mtx = mtx * scale_mtx;
		m_scale = scale;

		if (m_model->isReady())
		{
			renderer->renderModel(*m_model, mtx, render_device.getPipeline());
		}
	}
}


} // !namespace Lux