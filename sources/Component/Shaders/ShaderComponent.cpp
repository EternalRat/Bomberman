//
// Created by cbihan on 03/06/2021.
//

#include "ShaderComponent.hpp"

#include <utility>
#include <Component/Renderer/Drawable3DComponent.hpp>

namespace BBM
{
	WAL::Component *ShaderComponent::clone(WAL::Entity &entity) const
	{
		return new ShaderComponent(*this);
	}

	RAY::Shader &ShaderComponent::getShader()
	{
		return this->shader;
	}

	ShaderComponent::ShaderComponent(WAL::Entity &entity,
	                                 const std::string &fragmentFilePath,
	                                 const std::string &vertexFilePath,
	                                 const WAL::Callback<WAL::Entity &, WAL::Wal &> &onFixedUpdate)
		: WAL::Component(entity),
		  shader(vertexFilePath, fragmentFilePath),
		  fragmentFilePath(fragmentFilePath),
		  vertexFilePath(vertexFilePath),
		  onFixedUpdate(onFixedUpdate)
	{
	}

	std::string ShaderComponent::getFragmentFilePath() const
	{
		return this->fragmentFilePath;
	}

	std::string ShaderComponent::getVertexFilePath() const
	{
		return this->vertexFilePath;
	}

	ShaderComponentModel::ShaderComponentModel(WAL::Entity &entity,
	                                           const std::string &fragmentFilePath,
	                                           const std::string &vertexFilePath,
	                                           const WAL::Callback<WAL::Entity &, WAL::Wal &> &onFixedUpdate)
		: ShaderComponent(entity, fragmentFilePath, vertexFilePath, onFixedUpdate)
	{
	}

	void ShaderComponentModel::onStart()
	{
		auto &drawable = this->_entity.getComponent<Drawable3DComponent>();
		this->model = dynamic_cast<RAY::Drawables::Drawables3D::Model *>(drawable.drawable.get());
		if (!this->model)
			throw std::runtime_error("No model available with a shader model component. This is unsupported.");
	}

	ShaderComponentDrawable2D::ShaderComponentDrawable2D(WAL::Entity &entity,
	                                                     const std::string &fragmentFilePath,
	                                                     const std::string &vertexFilePath,
	                                                     const WAL::Callback<WAL::Entity &, WAL::Wal &> &onFixedUpdate)
		: ShaderComponent(entity, fragmentFilePath, vertexFilePath, onFixedUpdate)
	{
	}
}