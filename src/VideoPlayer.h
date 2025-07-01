/**
* @author   Suzuki N
* @date     24/2/25
* @note		VideoPlayerの定義ファイル
*/

#pragma once
#include "HandlerWaltanForDxLib.h"


/**
 * @enum	PlayStatus
 * @brief   動画の再生状況
 */
enum class PlayStatus
{
	//! 待機中
	Wait,
	//! 再生中
	Play,
	//! 再生停止
	Stop,
};


/**
 * @class	VideoPlayer
 * @brief   動画再生用クラス
 */
class VideoPlayer
{
	//
	// メンバ変数
	//

private:

	//! 透過処理を行う際に使用するスクリーンハンドル
	int screenHandle = -1;

public:

	//! 動画のハンドル
	int movieHandle;
	//! 再生方法
	int playType = DX_PLAYTYPE_BACK;
	//! 透過処理を行うか(グリーンバック)
	bool isTrans = true;
	//! 再生状況
	PlayStatus playStatus;
	//! 動画の横幅
	int wedth;
	//! 動画の立幅
	int height;
	//! 表示座標
	VECTOR position;


	//
	// メソッド
	//

public:

	/**
	 * @brief       コンストラクタ
	 * @param[in]	ファイルのパス
	 * @param[in]	再生方法
	 * @param[in]	透過処理を行うか
	 */
	VideoPlayer(const std::string& _path, int _playType = DX_PLAYTYPE_BACK, bool _isTrans = true)
		: movieHandle(LoadGraph(_path.c_str())), playType(_playType), isTrans(_isTrans), playStatus(PlayStatus::Wait),
		position({ 0,0,0 })
	{
		// モデルロード失敗時の例外error
		if (movieHandle == -1)
			throw std::runtime_error("Failed to load movie: " + _path);

		// 動画サイズを記録
		GetGraphSize(movieHandle, &wedth, &height);

		if (!isTrans) return;

		//
		// 透過処理を行う場合の処理
		//

		// 動画と同サイズのアルファチャンネル付きの画像を作成
		screenHandle = MakeScreen(wedth, height, TRUE);
	}

	/**
	 * @brief       明示的な更新処理
	 */
	void ManualUpdate()
	{
		// 再生状況の更新
		if (playStatus == PlayStatus::Stop) playStatus = PlayStatus::Wait;
		if (playStatus != PlayStatus::Play) return;

		//
		// 透過処理を行わない場合
		//

		if (!isTrans)
		{
			DrawGraph((int)position.x, (int)position.y, movieHandle, TRUE);
		}
		else
		{
			// Screen に Movie のRGBAの各チャンネルを置き換えたり反転したりして転送
			GraphBlendBlt(movieHandle, movieHandle, screenHandle, 255, DX_GRAPH_BLEND_RGBA_SELECT_MIX,
				DX_RGBA_SELECT_SRC_R,
				DX_RGBA_SELECT_SRC_G,
				DX_RGBA_SELECT_SRC_B,
				DX_RGBA_SELECT_SRC_INV_G	// Screen の透明度成分に Movie の緑成分を反転したものを転送
			);

			// Screen の内容を画面に描画
			DrawGraph((int)position.x, (int)position.y, screenHandle, TRUE);
		}

		//
		// 再生状況を更新
		//

		if (GetMovieStateToGraph(movieHandle) == 0)
			playStatus = PlayStatus::Stop;
	}

	/**
	 * @brief       再生
	 * @param[in]	再生状況をリセットするか
	 */
	void Play(bool _isReset = false)
	{
		if (!_isReset && playStatus == PlayStatus::Play) return;

		SeekMovieToGraph(movieHandle, 0);
		PlayMovieToGraph(movieHandle, playType);
		playStatus = PlayStatus::Play;
	}

	/**
	 * @brief       停止
	 * @param[in]	再生状況をリセットするか
	 */
	void Stop(bool _isReset = false)
	{
		PauseMovieToGraph(movieHandle, playType);
		if(_isReset)
			SeekMovieToGraph(movieHandle, 0);
		playStatus = PlayStatus::Stop;
	}
};