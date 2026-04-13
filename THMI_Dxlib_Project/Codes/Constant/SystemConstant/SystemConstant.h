#pragma once

// ウィンドウやシステム関連の定数等を作る
constexpr int WINDOW_WIDTH{ 1920 }; // 画面の横幅
constexpr int WINDOW_HEIGHT{ 1080 }; // 画面の縦幅
constexpr int COLOR_DEPTH{ 32 }; // 色の深度
constexpr int ONE_SEC_MICRO{ 1000000 }; //  1秒 = 1,000,000マイクロ秒
constexpr int ONE_SEC_MILLI{ 1000 }; // 1秒 = 1,000ミリ秒
constexpr int USE_FPS{ 60 }; // 目標FPS値
constexpr int SAMPLE_FRAME_COUNT{ 60 }; // FPS計算のためのサンプルフレーム数
constexpr float CAMERA_NEAR{ 1.0f }; // 視錐台の上面までの距離
constexpr float CAMERA_FAR{ 10000.0f }; // 視錐台の底面までの距離
constexpr float LIMIT_DELTA_TIME{ 0.05f }; // 処理落ちの際のデルタタイム制限
constexpr float FIXED_DELTA_TIME{ 1.0f / 60.0f }; // 物理計算用の固定時間ステップ
constexpr float LIMIT_ACCUMULATOR{ 0.2f }; // 物理更新で使う蓄算器
constexpr float SEAF_ZERO{ 0.0f }; // ポインタを0値で初期化するときに使う