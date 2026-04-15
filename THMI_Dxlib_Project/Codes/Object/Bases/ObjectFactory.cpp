#include <memory>
#include "ObjectFactory.h"

// 具体をインクルード
#include "../DebugObject/DebugBoxObject.h"


// static変数の実態を作る
ObjectManager* ObjectFactory::targetManager{ nullptr };


void ObjectFactory::BindManager(ObjectManager& _targetManager)
{
	targetManager = &_targetManager; // 引数で受け取ったObjectManagerのインスタンスをFactoryに登録
}


void ObjectFactory::CreateDebugObject(const VECTOR& _position, const int& _handle = -1)
{
	std::unique_ptr<WorldObjectBase> obj{ std::make_unique<DebugBoxObject>(_position, _handle) };
	targetManager->RegisterWorld(std::move(obj));
}

