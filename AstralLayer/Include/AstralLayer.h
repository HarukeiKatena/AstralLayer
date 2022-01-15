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
	class ATLIResource;
	class ATLIRenderTargetView;
	class ATLIDepthStencilView;
	/// @endcond
	
	/****************************************************************//**
	 * 基底クラス
	 *******************************************************************/
	class ATLIUnknown
	{
	public:
		virtual void Release() = 0;
	};

	/****************************************************************//**
	 * デバイスクラス
	 *******************************************************************/
	class ATLIDevice : public ATLIUnknown
	{
	protected:
		ATL_GRAPHIC_INTERFACE m_gi = {};


	public:
		/****************************************************************//**
		 *  リソースクラス作成関数
		 * 
		 * \param [in] Desc		リソースクラス
		 * \param [in] pSrcData 初期化データ\n
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
		 * \param [in] Desc グラフィクスパイプラインデスク
		 * \return パイプラインクラス
		 *******************************************************************/
		virtual ATLIPipeLine* CreatePipeLine(
			ATL_GRAPHICS_PIPELINE_STATE_DESC& Desc
		) = 0;

		/****************************************************************//**
		 *  デプスステンシルビュークラス作成関数
		 * 
		 * \param [in] Desc デプスステンシルビューデスク
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
		 * \param [in] Desc スワップチェインデスク
		 * \param [in] pCommandQueue コマンドキュークラス 
		 * \return スワップチェインクラス
		 *******************************************************************/
		virtual ATLISwapChain* CreateSwapChain(
			ATL_SWAPCHAIN_DESC& Desc, 
			ATLICommandQueue* pCommandQueue
		) = 0;

		/****************************************************************//**
		 *  フェンスクラス作成関数
		 * 
		 * \return フェンスクラス
		 *******************************************************************/
		virtual ATLIFence* CreateFence() = 0;

		/****************************************************************//**
		 *  レンダーターゲットビュークラス作成関数
		 * 
		 * \param [in] pSwapChain	スワップチェインクラス\n
		 *							nullではない場合スワップチェインからバッファを取得して作成する、nullの場合内部でバッファを作成してからRTVを作成する
		 * \param [in] ScreenWidth	画面幅
		 * \param [in] ScreenHeight 画面高さ
		 * \return レンダーターゲットビュークラス
		 *******************************************************************/
		virtual ATLIRenderTargetView* CreateRenderTargetView(
			ATLISwapChain* pSwapChain,
			unsigned int ScreenWidth,
			unsigned int ScreenHeight
		) = 0;

		/****************************************************************//**
		 * 現在のグラフィクスインターフェースを取得
		 *******************************************************************/
		ATL_GRAPHIC_INTERFACE GetGraphics_Interface()const {return m_gi;}
	};

	/****************************************************************//**
	 * コマンドリストクラス
	 *******************************************************************/
	class ATLICommandList : public ATLIUnknown
	{
	public:
		/****************************************************************//**
		 *  コマンドリセットする関数
		 * 
		 * \param [in] pPipeLine		パイプラインクラス
		 * \param [in] pFence			フェンスクラス
		 * \return 結果の正負
		 *******************************************************************/
		virtual bool Reset(
			ATLIPipeLine* pPipeLine, 
			ATLIFence* pFence
		) = 0;

		/****************************************************************//**
		 *  リソースをセットする関数
		 * 
		 * \param [in] StartRootParametorIndex	ルートパラメーターで指定したパラメーターの番号
		 * \param [in] pResource				セットするリソースクラス
		 * \param [in] NumResourceIDs			リソースIDの数
		 * \param [in] pResourceIDs				ATLIResource::SetSubResource()の戻り値\n
		 *										pResourceで指定したリソースのATL_RESOURCE_DESCのNumObjectが1でTypeがATL_RESOURCE_TYPE::DEFAULTの場合はnullを指定
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
		 * \param [in] NumViewports ビューポートの数
		 * \param [in] pViewports	ビューポート
		 *******************************************************************/
		virtual void SetViewports(
			unsigned int NumViewports, 
			ATL_VIEWPORT* pViewports
		) = 0;

		/****************************************************************//**
		 *  レクトセットする関数
		 * 
		 * \param [in] NumRects レクトの数
		 * \param [in] pRects	レクト
		 *******************************************************************/
		virtual void SetScissorRects(
			unsigned int NumRects, 
			ATL_RECT* pRects
		) = 0;

		/****************************************************************//**
		 *  プリミティブトポロジーを指定
		 * 
		 * \param [in] Topology 利用するトポロジー
		 *******************************************************************/
		virtual void SetPrimitiveTopology(
			ATL_PRIMITIVE_TOPOLOGY Topology
		) = 0;

		/****************************************************************//**
		 *  頂点バッファーをセットする関数
		 * 
		 * \param [in] pVertexBuffer 頂点バッファー
		 * \param [in] ResourceID ATLIResource::SetSubResource()の戻り値\n
		 *                        pVertexBufferで指定したリソースのATL_RESOURCE_DESCのNumObjectが1でTypeがATL_RESOURCE_TYPE::DEFAULTの場合は0を指定
		 *******************************************************************/
		virtual void SetVertexBuffer(
			ATLIResource* pVertexBuffer, 
			unsigned int ResourceID
		) = 0;

		/****************************************************************//**
		 *  インデックスバッファーをセットする関数
		 * 
		 * \param [in] pIndexBuffer 頂点バッファー
		 * \param [in] ResourceID	ATLIResource::SetSubResource()の戻り値\n
		 *							pIndexBufferで指定したリソースのATL_RESOURCE_DESCのNumObjectが1でTypeがATL_RESOURCE_TYPE::DEFAULTの場合は0を指定
		 *******************************************************************/
		virtual void SetIndexBuffer(
			ATLIResource* pIndexBuffer, 
			unsigned int ResourceID
		) = 0;

		/****************************************************************//**
		 *  リソースバリアをセットする関数
		 * 
		 * \param [in] Barrier バリアー
		 *******************************************************************/
		virtual void ResourceBarrier(
			ATL_RESOURCE_BARRIER& Barrier
		) = 0;

		/****************************************************************//**
		 *  レンダーターゲットとデプスステンシルビューをセットする関数
		 * 
		 * \param [in] pRenderTargetView レンダーターゲットビュークラス
		 * \param [in] pDepthStencilView デプスステンシルビュークラス
		 *******************************************************************/
		virtual void SetRenderTargets(
			ATLIRenderTargetView* pRenderTargetView,
			ATLIDepthStencilView* pDepthStencilView
		) = 0;

		/****************************************************************//**
		 *  クリアするレンダーターゲットビューを指定する関数
		 * 
		 * \param [in] pRenderTargetView	レンダーターゲットビュークラス
		 * \param [in] ColorRGBA			画面クリアする色
		 *******************************************************************/
		virtual void ClearRenderTargetView(
			ATLIRenderTargetView* pRenderTargetView,
			const float ColorRGBA[4]
		) = 0;

		/****************************************************************//**
		 *  クリアするデプスステンシルビュー
		 * 
		 * \param [in] pDepthStencilView	デプスステンシルビュークラス
		 * \param [in] ClearFlags			クリアフラグ
		 * \param [in] Depth				深度バッファをクリアする。0～1の間でクランプされます
		 * \param [in] Stencil				クリアするステンシルバッファ
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
		 * \param [in] VertexCountParInstance	描画する頂点数
		 * \param [in] InstanceCount			描画するインスタンスの数
		 * \param [in] StartVertexLocation		最初の頂点インデックスの位置
		 * \param [in] StartInstanceLocation	頂点バッファからインスタンス単位のデータを読み込む前に、各インデックスに追加される値
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
		 * \param [in] IndexCountParInstance	描画するインデックス数
		 * \param [in] InstanceCount			描画するインスタンスの数
		 * \param [in] StartIndexLocation		最初のインデックスの位置
		 * \param [in] BaceVertexLocation		頂点バッファから頂点を読み込む前に各インデックスに追加される値
		 * \param [in] StartInstanceLocation	頂点バッファからインスタンス単位のデータを読み込む前に、各インデックスに追加される値
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
	};

	/****************************************************************//**
	 * パイプラインクラス
	 *******************************************************************/
	class ATLIPipeLine : public ATLIUnknown
	{
	};

	/****************************************************************//**
	 * コマンドキュークラス
	 *******************************************************************/
	class ATLICommandQueue : public ATLIUnknown
	{
	public:
		/****************************************************************//**
		 *  コマンドを書き込んだコマンドリストを実行する
		 * 
		 * \param [in] NumCommandLists	コマンドの数
		 * \param [in] ppCommandLists	コマンドリスト
		 * \return 結果の正負
		 *******************************************************************/
		virtual bool ExecuteCommandLists(
			unsigned int NumCommandLists,
			AstralLayer::ATLICommandList* const* ppCommandLists
		) = 0;

	};

	/****************************************************************//**
	 * フェンスクラス
	 *******************************************************************/
	class ATLIFence : public ATLIUnknown
	{
	public:
		/****************************************************************//**
		 *  描画完了を待つ
		 * 
		 * \param [in] pCommandQueue	コマンドキュークラス
		 * \param [in] pSwapChain		スワップチェインクラス
		 *******************************************************************/
		virtual void WaitDrawDone(
			ATLICommandQueue* pCommandQueue,
			ATLISwapChain* pSwapChain
		) = 0;
	};

	/****************************************************************//**
	 * スワップチェインクラス
	 *******************************************************************/
	class ATLISwapChain : public ATLIUnknown
	{
	public:
		/****************************************************************//**
		 *  レンダリング画像を画面に描画する
		 * 
		 * \param [in] SyncInterval	フレームの提示と垂直方向のブランクを同期させる方法。\n
		 *                          0   : 前に提示されたフレームの残り時間をキャンセルし、より新しいフレームがキューに入っている場合はこのフレームを破棄する。\n
		 *                          1~4 : 少なくともn個の垂直方向のブランクに対してプレゼンテーションを同期させる。
		 *******************************************************************/
		virtual void Present(
			unsigned int SyncInterval
		) = 0;
	};

	/****************************************************************//**
	 * リソースクラス
	 *******************************************************************/
	class ATLIResource : public ATLIUnknown
	{
	protected:
		ATL_RESOURCE_TYPE m_Type = ATL_RESOURCE_TYPE::UNKNOWN;
		ATL_RESOURCE_FLAG m_Flag = ATL_RESOURCE_FLAG::UNKNOWN;

	public:
		/****************************************************************//**
		 *  サブリソース情報をセット
		 * 
		 * \param [in] pData		セットするデータ
		 * \param [in] SetByteSize	セットするバイトサイズ
		 * \return セットしたID\n失敗した場合unsigned intの最大値が返ってくる
		 *******************************************************************/
		virtual unsigned int SetSubResource(
			const void* pData, 
			unsigned int SetByteSize
		) = 0;

		/****************************************************************//**
		 *  サブリソース更新
		 * 
		 * \param [in] SubResourceID	ATLIResource::SetSubResource()の戻り値
		 * \param [in] MoveByte			セットするデータの開始位置をずらすバイトサイズ
		 * \param [in] pData			セットするデータ
		 * \param [in] UpdateByteSize	更新するバイトサイズ
		 * \return 結果の正負
		 *******************************************************************/
		virtual bool UpdateSubResource(
			unsigned int SubResourceID,
			unsigned int MoveByte,
			const void* pData,
			unsigned int UpdateByteSize
		) = 0;

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
	class ATLIRenderTargetView : public ATLIUnknown
	{
	public:
		/****************************************************************//**
		 *  RTVにセットされたリソースを取得
		 * 
		 * ここで取得したリソースはRelease又はdeleteしないでください
		 * 
		 * \param [in] pFence フェンス
		 * \return リソースクラス
		 *******************************************************************/
		virtual ATLIResource* GetResource(
			ATLIFence* pFence
		) = 0;
	};

	/****************************************************************//**
	 * デプスステンシルビュークラス
	 *******************************************************************/
	class ATLIDepthStencilView : public ATLIUnknown
	{

	};
}