#include "Debug.h"
#include "DxLib.h"

FILE* Debug::m_stream = nullptr;

void Debug::Initialize()
{
#ifdef _DEBUG
	// コンソールを作成
	AllocConsole();

	// ストリーム出力先を作成したコンソールにする
	freopen_s(&m_stream, "CONOUT$", "w+", stdout);

	// メインのゲーム画面をアクティブにする
	SetForegroundWindow(GetMainWindowHandle());
#endif
}

void Debug::Finalize()
{
#ifdef _DEBUG
	// ストリームを閉じる
	fclose(m_stream);
	m_stream = nullptr;

	// コンソールを閉じる
	FreeConsole();
#endif
}
