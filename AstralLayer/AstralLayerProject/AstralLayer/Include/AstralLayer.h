/****************************************************************//**
 * @file AstralLayer.h
 *******************************************************************/
#pragma once
#include"AstralRendererInterface.h"
#include"AstralInfo.h"


namespace AstralLayer
{
	/// @cond
	/// 前方宣言
	class ATLICommandList;
	class ATLIPipeLine;
	class ATLIFence;
	class ATLICommandQueue;
	class ATLISwapChain;
	class ATLIRootSignature;
	class ATLIResource;
	class ATLIRenderTargetView;
	class ATLIDepthStencilView;
	/// @endcond
	

	/****************************************************************//**
	 * デバイスクラス
	 *******************************************************************/
	class ATLIDevice
	{
	public:
		/****************************************************************//**
		 *  リソースクラス作成関数
		 * 
		 * \param Desc [in] リソースクラス
		 * \param pSrcData [in] 初期化データ\n
		 *                      ATL_RESOURCE_DESCのByteStructure * Width * Heightを超えてはならない
		 * \return リソースクラス
		 *******************************************************************/
		virtual ATLIResource* CreateResource(
			ATL_RESOURCE_DESC& Desc ,
			const void* pSrcData
		) = 0;

		/****************************************************************//**
		 *  パイプラインクラス作成関数
		 * 
		 * \param pRootSignature [in] ルートシグネチャークラス
		 * \param Desc [in] グラフィクスパイプラインデスク
		 * \return パイプラインクラス
		 *******************************************************************/
		virtual ATLIPipeLine* CreatePipeLine(
			ATLIRootSignature* pRootSignature,
			ATL_GRAPHICS_PIPELINE_STATE_DESC& Desc
		) = 0;

		/****************************************************************//**
		 *  デプスステンシルビュークラス作成関数
		 * 
		 * \param Desc [in] デプスステンシルビューデスク
		 * \return デプスステンシルビュークラス
		 *******************************************************************/
		virtual ATLIDepthStencilView* CreateDepthStencilView(
			ATL_DEPTH_STENCIL_VIEW_DESC& Desc
		) = 0;

		/****************************************************************//**
		 *  コマンドリストクラス作成関数
		 * 
		 * \return コマンドリストクラス
		 *******************************************************************/
		virtual ATLICommandList* CreateCommandList() = 0;

		/****************************************************************//**
		 *  コマンドキュークラス作成関数
		 * 
		 * \return コマンドキュークラス
		 *******************************************************************/
		virtual ATLICommandQueue* CreateCommandQueue() = 0;

		/****************************************************************//**
		 *  スワップチェインクラス作成関数
		 * 
		 * \param Desc [in] スワップチェインデスク
		 * \param pCommandQueue [in] コマンドキュークラス 
		 * \return スワップチェインクラス
		 *******************************************************************/
		virtual ATLISwapChain* CreateSwapChain(
			ATL_SWAPCHAIN_DESC& Desc, 
			ATLICommandQueue* pCommandQueue
		) = 0;

		/****************************************************************//**
		 *  ルートシグネチャークラス作成関数
		 * 
		 * \param Desc [in] ルートシグネチャーデスク
		 * \return ルートシグネチャークラス
		 *******************************************************************/
		virtual ATLIRootSignature* CreateRootSignature(
			ATL_ROOT_SIGNATURE_DESC& Desc
		) = 0;

		/****************************************************************//**
		 *  フェンスクラス作成関数
		 * 
		 * \return フェンスクラス
		 *******************************************************************/
		virtual ATLIFence* CreateFence() = 0;

		//-------------------------------------------------------------------
		// レンダーターゲットビュー作成
		// [ATLISwapChain*] SwapChain : NULLの場合描画用ではないRTVを生成する
		// [unsigned int] ScreenWidth : 画面幅
		// [unsigned int] ScreenHeight : 画面高さ
		//-------------------------------------------------------------------

		/****************************************************************//**
		 *  レンダーターゲットビュークラス作成関数
		 * 
		 * \param pSwapChain [in] スワップチェインクラス\n
		 *                        nullではない場合スワップチェインからバッファを取得して作成する、nullの場合内部でバッファを作成してからRTVを作成する
		 * \param ScreenWidth [in] 画面幅
		 * \param ScreenHeight [in] 画面高さ
		 * \return レンダーターゲットビュークラス
		 *******************************************************************/
		virtual ATLIRenderTargetView* CreateRenderTargetView(
			ATLISwapChain* pSwapChain,
			unsigned int ScreenWidth,
			unsigned int ScreenHeight
		) = 0;

		/****************************************************************//**
		 *  解放
		 *******************************************************************/
		virtual void Release() = 0;
	};

	/****************************************************************//**
	 * コマンドリストクラス
	 *******************************************************************/
	class ATLICommandList
	{
	public:
		/****************************************************************//**
		 *  コマンドリセットする関数
		 * 
		 * \param pPipeLine [in] パイプラインクラス
		 * \param pFence [in] フェンスクラス
		 * \return 結果の正負
		 *******************************************************************/
		virtual bool Reset(
			ATLIPipeLine* pPipeLine, 
			ATLIFence* pFence
		) = 0;

		/****************************************************************//**
		 *  ルートシグネチャーをセットする
		 * 
		 * \param pRootSignature [in] ルートシグネチャークラス
		 *******************************************************************/
		virtual void SetGraphicsRootSignature(
			ATLIRootSignature* pRootSignature
		) = 0;

		/****************************************************************//**
		 *  リソースをセットする関数
		 * 
		 * \param StartRootParametorIndex [in] ルートパラメーターで指定したパラメーターの番号
		 * \param pResource [in] セットするリソースクラス
		 * \param NumResourceIDs [in] リソースIDの数
		 * \param pResourceIDs [in] ATLIResource::SetSubResource()の戻り値\n
		 *                          pResourceで指定したリソースのATL_RESOURCE_DESCのNumObjectが1でTypeがATL_RESOURCE_TYPE::DEFAULTの場合はnullを指定
		 *******************************************************************/
		virtual void SetResource(
			unsigned int StartRootParametorIndex, 
			ATLIResource* pResource, 
			unsigned int NumResourceIDs,
			unsigned int* pResourceIDs
		) = 0;

		/****************************************************************//**
		 *  ビューポートをセットする関数
		 * 
		 * \param NumViewports [in] ビューポートの数
		 * \param pViewports [in] ビューポート
		 *******************************************************************/
		virtual void SetViewports(
			unsigned int NumViewports, 
			ATL_VIEWPORT* pViewports
		) = 0;

		/****************************************************************//**
		 *  レクトセットする関数
		 * 
		 * \param NumRects [in] レクトの数
		 * \param pRects [in] レクト
		 *******************************************************************/
		virtual void SetScissorRects(
			unsigned int NumRects, 
			ATL_RECT* pRects
		) = 0;

		/****************************************************************//**
		 *  プリミティブトポロジーを指定
		 * 
		 * \param Topology 利用するトポロジー
		 *******************************************************************/
		virtual void SetPrimitiveTopology(
			ATL_PRIMITIVE_TOPOLOGY Topology
		) = 0;

		/****************************************************************//**
		 *  頂点バッファーをセットする関数
		 * 
		 * \param pVertexBuffer [in] 頂点バッファー
		 * \param ResourceID [in] ATLIResource::SetSubResource()の戻り値\n
		 *                        pVertexBufferで指定したリソースのATL_RESOURCE_DESCのNumObjectが1でTypeがATL_RESOURCE_TYPE::DEFAULTの場合は0を指定
		 *******************************************************************/
		virtual void SetVertexBuffer(
			ATLIResource* pVertexBuffer, 
			unsigned int ResourceID
		) = 0;

		/****************************************************************//**
		 *  インデックスバッファーをセットする関数
		 * 
		 * \param pIndexBuffer [in] 頂点バッファー
		 * \param ResourceID [in] ATLIResource::SetSubResource()の戻り値\n
		 *                        pIndexBufferで指定したリソースのATL_RESOURCE_DESCのNumObjectが1でTypeがATL_RESOURCE_TYPE::DEFAULTの場合は0を指定
		 *******************************************************************/
		virtual void SetIndexBuffer(
			ATLIResource* pIndexBuffer, 
			unsigned int ResourceID
		) = 0;

		/****************************************************************//**
		 *  リソースバリアをセットする関数
		 * 
		 * \param Barrier
		 *******************************************************************/
		virtual void ResourceBarrier(
			ATL_RESOURCE_BARRIER& Barrier
		) = 0;

		/****************************************************************//**
		 *  レンダーターゲットとデプスステンシルビューをセットする関数
		 * 
		 * \param pRenderTargetView [in] レンダーターゲットビュークラス
		 * \param pDepthStencilView [in] デプスステンシルビュークラス
		 *******************************************************************/
		virtual void SetRenderTargets(
			ATLIRenderTargetView* pRenderTargetView,
			ATLIDepthStencilView* pDepthStencilView
		) = 0;

		/****************************************************************//**
		 *  クリアするレンダーターゲットビューを指定する関数
		 * 
		 * \param pRenderTargetView [in] レンダーターゲットビュークラス
		 * \param ColorRGBA [in] 画面クリアする色
		 *******************************************************************/
		virtual void ClearRenderTargetView(
			ATLIRenderTargetView* pRenderTargetView,
			const float ColorRGBA[4]
		) = 0;

		/****************************************************************//**
		 *  クリアするデプスステンシルビュー
		 * 
		 * \param pDepthStencilView [in] デプスステンシルビュークラス
		 * \param ClearFlags [in] クリアフラグ
		 * \param Depth [in] 深度バッファをクリアする。0～1の間でクランプされます
		 * \param Stencil [in] クリアするステンシルバッファ
		 *******************************************************************/
		virtual void ClearDepthStencilView(
			ATLIDepthStencilView* pDepthStencilView,
			ATL_CLEAR_FLAG ClearFlags,
			float Depth,
			unsigned char Stencil
		) = 0;

		/****************************************************************//**
		 *  インデックスを持たない、インスタンス化されたプリミティブを描画する
		 * 
		 * \param VertexCountParInstance [in] 描画する頂点数
		 * \param InstanceCount [in] 描画するインスタンスの数
		 * \param StartVertexLocation [in] 最初の頂点インデックスの位置
		 * \param StartInstanceLocation [in] 頂点バッファからインスタンス単位のデータを読み込む前に、各インデックスに追加される値
		 *******************************************************************/
		virtual void DrawInstanced(
			unsigned int VertexCountParInstance,
			unsigned int InstanceCount,
			unsigned int StartVertexLocation,
			unsigned int StartInstanceLocation
		) = 0;

		/****************************************************************//**
		 *  インデックスを持っている、インスタンス化されたプリミティブを描画する
		 * 
		 * \param IndexCountParInstance [in] 描画するインデックス数
		 * \param InstanceCount [in] 描画するインスタンスの数
		 * \param StartIndexLocation [in] 最初のインデックスの位置
		 * \param BaceVertexLocation [in] 頂点バッファから頂点を読み込む前に各インデックスに追加される値
		 * \param StartInstanceLocation [in] 頂点バッファからインスタンス単位のデータを読み込む前に、各インデックスに追加される値
		 *******************************************************************/
		virtual void DrawIndexedInstanced(
			unsigned int IndexCountParInstance,
			unsigned int InstanceCount,
			unsigned int StartIndexLocation,
			unsigned int BaceVertexLocation,
			unsigned int StartInstanceLocation
		) = 0;

		/****************************************************************//**
		 *  コマンドを閉じる関数
		 * 
		 * \return 結果の正負
		 *******************************************************************/
		virtual bool Close() = 0;

		/****************************************************************//**
		 *  解放
		 *******************************************************************/
		virtual void Release() = 0;
	};

	/****************************************************************//**
	 * パイプラインクラス
	 *******************************************************************/
	class ATLIPipeLine
	{
	public:
		/****************************************************************//**
		 *  解放
		 *******************************************************************/
		virtual void Release() = 0;
	};

	/****************************************************************//**
	 * コマンドキュークラス
	 *******************************************************************/
	class ATLICommandQueue
	{
	public:
		/****************************************************************//**
		 *  コマンドを書き込んだコマンドリストを実行する
		 * 
		 * \param NumCommandLists [in] コマンドの数
		 * \param ppCommandLists [in] コマンドリスト
		 * \return 結果の正負
		 *******************************************************************/
		virtual bool ExecuteCommandLists(
			unsigned int NumCommandLists,
			AstralLayer::ATLICommandList* const* ppCommandLists
		) = 0;

		/****************************************************************//**
		 *  解放
		 *******************************************************************/
		virtual void Release() = 0;

	};

	/****************************************************************//**
	 * フェンスクラス
	 *******************************************************************/
	class ATLIFence
	{
	public:
		/****************************************************************//**
		 *  描画完了を待つ
		 * 
		 * \param pCommandQueue [in] コマンドキュークラス
		 * \param pSwapChain [in] スワップチェインクラス
		 *******************************************************************/
		virtual void WaitDrawDone(
			ATLICommandQueue* pCommandQueue,
			ATLISwapChain* pSwapChain
		) = 0;

		/****************************************************************//**
		 *  解放
		 *******************************************************************/
		virtual void Release() = 0;
	};

	/****************************************************************//**
	 * スワップチェインクラス
	 *******************************************************************/
	class ATLISwapChain
	{
	public:
		//----------------------------------------------------------------------
		// プレゼント
		// [unsigned int] SyncInterval : フレームの提示と垂直方向のブランクを同期させる方法
		// 0   : 前に提示されたフレームの残り時間をキャンセルし、より新しいフレームがキューに入っている場合はこのフレームを破棄する。
		// 1~4 : 少なくともn個の垂直方向のブランクに対してプレゼンテーションを同期させる。
		//----------------------------------------------------------------------

		/****************************************************************//**
		 *  レンダリング画像を画面に描画する
		 * 
		 * \param SyncInterval [in] フレームの提示と垂直方向のブランクを同期させる方法。\n
		 *                           0   : 前に提示されたフレームの残り時間をキャンセルし、より新しいフレームがキューに入っている場合はこのフレームを破棄する。\n
		 *                           1~4 : 少なくともn個の垂直方向のブランクに対してプレゼンテーションを同期させる。
		 *******************************************************************/
		virtual void Present(
			unsigned int SyncInterval
		) = 0;

		/****************************************************************//**
		 *  解放
		 *******************************************************************/
		virtual void Release() = 0;
	};

	/****************************************************************//**
	 * ルートシグネチャークラス
	 *******************************************************************/
	class ATLIRootSignature
	{
	public:
		/****************************************************************//**
		 *  解放
		 *******************************************************************/
		virtual void Release() = 0;
	};

	/****************************************************************//**
	 * リソースクラス
	 *******************************************************************/
	class ATLIResource
	{
	protected:
		ATL_RESOURCE_TYPE m_Type = ATL_RESOURCE_TYPE::UNKNOWN;
		ATL_RESOURCE_FLAG m_Flag = ATL_RESOURCE_FLAG::UNKNOWN;

	public:
		/****************************************************************//**
		 *  サブリソース情報をセット
		 * 
		 * \param pData [in] セットするデータ
		 * \param SetByteSize [in] セットするバイトサイズ
		 * \return セットしたID\n失敗した場合unsigned intの最大値が返ってくる
		 *******************************************************************/
		virtual unsigned int SetSubResource(
			const void* pData, 
			unsigned int SetByteSize
		) = 0;

		/****************************************************************//**
		 *  サブリソース更新
		 * 
		 * \param SubResourceID [in] ATLIResource::SetSubResource()の戻り値
		 * \param MoveByte [in] セットするデータの開始位置をずらすバイトサイズ
		 * \param pData [in] セットするデータ
		 * \param UpdateByteSize [in] 更新するバイトサイズ
		 * \return 結果の正負
		 *******************************************************************/
		virtual bool UpdateSubResource(
			unsigned int SubResourceID,
			unsigned int MoveByte,
			const void* pData,
			unsigned int UpdateByteSize
		) = 0;

		/****************************************************************//**
		 *  解放
		 *******************************************************************/
		virtual void Release() = 0;

		/****************************************************************//**
		 *  タイプを取得
		 * 
		 * \return 自分のATL_RESOURCE_TYPE
		 *******************************************************************/
		ATL_RESOURCE_TYPE GetType()const { return m_Type; }

		/****************************************************************//**
		 *  フラグを取得
		 * 
		 * \return 自分のATL_RESOURCE_FLAG
		 *******************************************************************/
		ATL_RESOURCE_FLAG GetFlag()const { return m_Flag; }
	};

	/****************************************************************//**
	 * レンダーターゲットビュークラス
	 *******************************************************************/
	class ATLIRenderTargetView
	{
	public:
		/****************************************************************//**
		 *  RTVにセットされたリソースを取得
		 * 
		 * ここで取得したリソースは使用が終わった際Releaseしてくださいメモリリークの原因になります
		 * 
		 * \param pFence [in] フェンス
		 * \return リソースクラス
		 *******************************************************************/
		virtual ATLIResource* GetResource(
			ATLIFence* pFence
		) = 0;

		/****************************************************************//**
		 *  解放
		 *******************************************************************/
		virtual void Release() = 0;
	};

	/****************************************************************//**
	 * デプスステンシルビュークラス
	 *******************************************************************/
	class ATLIDepthStencilView
	{
	public:

		/****************************************************************//**
		 *  解放
		 *******************************************************************/
		virtual void Release() = 0;
	};
}