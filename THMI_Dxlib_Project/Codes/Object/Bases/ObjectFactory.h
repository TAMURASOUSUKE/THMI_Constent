#pragma once

#ifdef _DEBUG

#include <Dxlib.h> // デバッグ時のみDxlibをインクルードする

#endif // _DEBUG


#include "ObjectManager.h"

// オブジェクトの生成を行う
class ObjectFactory
{
public:
	static void BindManager(ObjectManager& _objManager); // 各シーンが持つObjectManagerを受け取るため


	// テスト用作成関数
	static void CreateDebugObject(const VECTOR& _position, int _handle = -1);
private:
	static ObjectManager* targetManager; // どのシーンのオブジェクトマネージャーを使うかをバインドするための変数(参照に使うため生でよい)

};