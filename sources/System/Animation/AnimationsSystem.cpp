//
// Created by cbihan on 01/06/2021.
//

#include <iostream>
#include "AnimationsSystem.hpp"
#include "Component/Animation/AnimationsComponent.hpp"
#include "Model/Model.hpp"
#include "Component/Renderer/Drawable3DComponent.hpp"

namespace BBM
{

	AnimationsSystem::AnimationsSystem(WAL::Wal &wal)
		: System(wal)
	{}

	void AnimationsSystem::onUpdate(WAL::ViewEntity<Drawable3DComponent, AnimationsComponent> &entity, std::chrono::nanoseconds)
	{
		auto &model = entity.get<Drawable3DComponent>();
		auto &anim = entity.get<AnimationsComponent>();

		if (anim.isDisabled())
			return;
		auto modelPtr = std::dynamic_pointer_cast<RAY::Drawables::Drawables3D::Model>(model.drawable);
		if (modelPtr) {
			modelPtr->setAnimation(anim.getCurrentModelAnim());
			anim.incCurrentAnimFrameCounter();
		}
	}
}