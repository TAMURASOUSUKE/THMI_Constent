#pragma once

// 各オブジェクトの生成クラス
#include "ObjectManager.h"

// オブジェクトの生成を行う
class ObjectFactory
{
public:
	static void BindManager(ObjectManager& _objManager); // 各シーンが持つObjectManagerを受け取るため


	// テスト用作成関数
	//static void CreateDebugObject(const Vector3& position, const Vector3& rotation, const Vector3& scale, const bool& isActive);
	//static void CreateDebugGround(const Vector3& position, const Vector3& rotation, const Vector3& scale, const bool& isActive);
	//static void CreateDebugGround(const Vector3& position, const Vector3& rotation, const Vector3& scale, const bool& isActive, const Vector3& boxSize);
private:
	static ObjectManager* targetManager; // どのシーンのオブジェクトマネージャーを使うかをバインドするための変数(参照に使うため生でよい)

};