#pragma once
#include"GameConstant/GameConstant.h"


// 各オブジェクトの基底クラスを作成する
class ObjectBase
{
public:
	// デフォルトデストラクタ
	virtual ~ObjectBase() = default;

	// 更新関数
	virtual void Update() = 0;

	// 描画関数
	virtual	 void Draw() = 0;

	// 生存フラグ取得
	bool GetIsActive() const { return isActive; }

	// オブジェクトを破棄する
	void Destroy() { isActive = false; }

	// 生存フラグを設定する
	void SetActive(bool _active) { isActive = _active; }

protected:
	ObjectBase(RenderLayer _layer) : layer{_layer} {} // レイヤーのみを初期化
	ObjectBase(int _handle, RenderLayer _layer) : handle{_handle}, layer { _layer } {} // ハンドルとレイヤーを設定
	ObjectBase(bool _isActive, RenderLayer _layer) : isActive{_isActive}, layer { _layer } {} // 生存フラグとレイヤー設定
	ObjectBase(int _handle, bool _isActive, RenderLayer _layer) :handle{ _handle }, isActive{ _isActive }, layer { _layer } {} // ハンドルと生存フラグとレイヤー設定

protected:

	// 各オブジェクトが持つレイヤー
	RenderLayer layer{ RenderLayer::None };
	//生存フラグ
	bool isActive{ false }; 
	// ハンドル
	int handle{ -1 };
 };