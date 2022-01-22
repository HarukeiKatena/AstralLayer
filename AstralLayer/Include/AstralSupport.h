/****************************************************************//**
 * @file AstralSupport.h
 * @brief AstralLayerで利用できる竿ポート関数やクラス等
 *******************************************************************/
#pragma once
#include"AstralInfo.h"

namespace AstralLayer
{
	/****************************************************************//**
	 * @brief シェーダーバイナリ読み込みクラス
	 * シェーダーのバイナリファイルを読み込み管理するクラス
	 *******************************************************************/
	class ATLSShaderBinary
	{
	public:
		unsigned long m_Size = 0;			//!< バッファサイズ
		unsigned char* m_Buffer = nullptr;	//!< バッファー

		/****************************************************************//**
		 * デストラクタ
		 *******************************************************************/
		~ATLSShaderBinary();

		/****************************************************************//**
		 * シェーダーバイナリデータ読み込み関数
		 *
		 * \param [in] FilePath	バイナリファイルまでのパス(ファイル名混み)
		 * \return				結果の正負
		 *******************************************************************/
		bool LoadShaderBinary(const char* FilePath);

		/****************************************************************//**
		 * バッファー削除関数
		 *******************************************************************/
		void DeleteBuffer();

		/****************************************************************//**
		 * バッファーサイズ取得関数
		 * \return バッファーサイズ
		 *******************************************************************/
		unsigned long GetSize()const { return m_Size; }

		/****************************************************************//**
		 * バッファー取得関数
		 * \return バッファの先頭ポインタ
		 *******************************************************************/
		unsigned char* GetBuffer()const { return m_Buffer; }

		/****************************************************************//**
		 * ATL_SHADER_BYTECODEで取得
		 * \return ATL_SHADER_BYTECODEで取得する
		 *******************************************************************/
		ATL_SHADER_BYTECODE GetShaderByteCode() { return ATL_SHADER_BYTECODE{ m_Buffer, m_Size }; }
	};

	/****************************************************************//**
	 * @brief AstralLayerで使えるスマートポインタ
	 *******************************************************************/
	template<class ATLClass>
	class ATLS_Ptr
	{
	private:
		ATLClass* m_pATL = nullptr;//クラス
		int* m_pCounter = nullptr;//カウンター

	public:
		ATLS_Ptr() {}
		ATLS_Ptr(decltype(nullptr)) {}
		ATLS_Ptr(const ATLS_Ptr& atls)
		{
			copy(atls);
		}

		ATLS_Ptr(ATLClass* atl)
		{
			reset(atl);
		}

		virtual ~ATLS_Ptr()
		{
			release();
		}

		/****************************************************************//**
		 * 解放
		 *******************************************************************/
		int release()
		{
			if (m_pCounter != nullptr)
			{
				(*m_pCounter)--;

				if ((*m_pCounter) <= 0)//カウンターが0以下の場合
				{
					delete m_pCounter;
					m_pCounter = nullptr;

					if (m_pATL != nullptr)
						m_pATL->Release();
					m_pATL = nullptr;

					return 0;
				}

				return (*m_pCounter);
			}

			return 0;
		}

		/****************************************************************//**
		 * 指定されたクラスをセットする
		 * 中身がすでにある場合Releaseしてから入れる
		 *******************************************************************/
		void reset(ATLClass* atl)
		{
			release();

			m_pATL = atl;
			m_pCounter = new int;
			(*m_pCounter) = 0;

			(*m_pCounter)++;
		}
		void reset()
		{
			release();
		}

		/****************************************************************//**
		 * データをコピーして参照カウンタインクリメント
		 *******************************************************************/
		void copy(const ATLS_Ptr& atls)
		{
			release();

			m_pATL = atls.m_pATL;
			m_pCounter = atls.m_pCounter;

			(*m_pCounter)++;
		}

		/****************************************************************//**
		 * データが入っているかチェック
		 *******************************************************************/
		bool empty()noexcept { return m_pATL == nullptr; }

		/****************************************************************//**
		 * データを交換する
		 * カウンターは増えない
		 *******************************************************************/
		void swap(ATLS_Ptr& atls)
		{
			ATLClass* atlswap = m_pATL;
			int* counterswap = m_pCounter;

			m_pATL = atls.m_pATL;
			m_pCounter = atls.m_pCounter;

			atls.m_pATL = atlswap;
			atls.m_pCounter = counterswap;
		}

		/****************************************************************//**
		 * 引数のデータを自分に渡す(所有権を受け取る)
		 * 自分がすでに持っていた場合はReleaseされる
		 * カウンターは増えない
		 *******************************************************************/
		void move(ATLS_Ptr& atls)
		{
			release();

			m_pATL = atls.m_pATL;
			m_pCounter = atls.m_pCounter;

			atls.release();
		}

		/****************************************************************//**
		 * ポインタを受け取る
		 *******************************************************************/
		ATLClass* get() const { return m_pATL; }
		ATLClass** get_doubleptr() { return &m_pATL; }

		/********************************************************************
		 * 演算子のオーバーロード関係
		 *******************************************************************/
		ATLClass* operator&() const { return m_pATL; }
		ATLClass* operator->() const { return m_pATL; }
		operator bool() const noexcept { return empty(); }
		bool operator!() const { return !static_cast<bool>(this); }

		ATLS_Ptr& operator= (ATLClass* atl) { reset(atl); return *this; }
		ATLS_Ptr& operator= (decltype(nullptr)) { release(); return *this; }
		ATLS_Ptr& operator= (const ATLS_Ptr& atls) { copy(atls); return *this; }

		bool operator==(ATLS_Ptr* atls)const		{ return this->m_pATL == atls->m_pATL; }
		bool operator==(ATLS_Ptr& atls)const		{ return this->m_pATL == atls.m_pATL; }
		bool operator==(ATLS_Ptr atls)const			{ return this->m_pATL == atls.m_pATL; }
		bool operator==(decltype(nullptr) atl)const { return this->m_pATL == nullptr; }

		bool operator!=(ATLS_Ptr* atls)const		{ return this->m_pATL != atls->m_pATL; }
		bool operator!=(ATLS_Ptr& atls)const		{ return this->m_pATL != atls.m_pATL; }
		bool operator!=(ATLS_Ptr atls)const			{ return this->m_pATL != atls.m_pATL; }
		bool operator!=(decltype(nullptr) atl)const { return this->m_pATL != nullptr; }
	};
}

/****************************************************************//**
 * @brief 定数バッファーのリソースデスク作成関数
 * 
 * @param [in] ByteStructure	構造体サイズ
 * @param [in] Width			幅
 * @param [in] ObjectNum		オブジェクト数
 * @param [in] Type				リソースタイプ
 * @return						リソースデスク
 *******************************************************************/
ATL_RESOURCE_DESC ATLSCreateConstantBufferResourceDesc(
	unsigned int ByteStructure,
	unsigned int Width,
	unsigned int ObjectNum,
	ATL_RESOURCE_TYPE Type
);

/****************************************************************//**
 * @brief 頂点バッファのリソースデスク作成関数
 * 
 * @param [in] ByteStructure	構造体サイズ
 * @param [in] Width			幅
 * @param [in] ObjectNum		オブジェクト数
 * @param [in] Type				リソースタイプ
 * @return						リソースデスク
 *******************************************************************/
ATL_RESOURCE_DESC ATLSCreateVertexBufferResourceDesc(
	unsigned int ByteStructure,
	unsigned int Width,
	unsigned int ObjectNum,
	ATL_RESOURCE_TYPE Type
);

/****************************************************************//**
 * @brief インデックスバッファのリソースデスク作成関数
 * 
 * @datails FormatはATL_FORMAT::R32_UINTで作成
 * 
 * @param [in] ByteStructure	構造体サイズ
 * @param [in] Width			幅
 * @param [in] ObjectNum		オブジェクト数
 * @param [in] Type				リソースタイプ
 * @return						リソースデスク
 *******************************************************************/
ATL_RESOURCE_DESC ATLSCreateIndexBufferResourceDesc(
	unsigned int ByteStructure,
	unsigned int Width,
	unsigned int ObjectNum,
	ATL_RESOURCE_TYPE Type
);

/****************************************************************//**
 * @brief
 * 
 * @param [in] ByteStructure	構造体サイズ
 * @param [in] Width			幅
 * @param [in] Height			高さ
 * @param [in] MipLevel			ミップレベル
 * @param [in] Format			フォーマット
 * @param [in] SamplerDesc		サンプラーデスク
 * @param [in] Type				リソースタイプ
 * @return						リソースデスク
 *******************************************************************/
ATL_RESOURCE_DESC ATLSCreateTexture2DBufferResourceDesc(
	unsigned int ByteStructure,
	unsigned int Width,
	unsigned int Height,
	unsigned int MipLevel,
	ATL_FORMAT Format,
	ATL_SAMPLE_DESC SamplerDesc,
	ATL_RESOURCE_TYPE Type
);

/****************************************************************//**
 * @brief サンプラーデスク作成関数
 * 
 * @param [in] Filter			フィルター
 * @param [in] AddressUVW		アドレスモード、UVWまとめて
 * @param [in] ShadeerRegister	シェーダーレジスター、初期は0
 * @param [in] Visibility		ビジビリティー、初期はATL_SHADER_VISIBILITY::PIXEL
 * @return						サンプラーデスク
 *******************************************************************/
ATL_SAMPLER_DESC ATLSCreateSamplerDesc(
	ATL_FILTER Filter,
	ATL_ADDRESS_MODE AddressUVW,
	unsigned int ShadeerRegister = 0,
	ATL_SHADER_VISIBILITY Visibility = ATL_SHADER_VISIBILITY::PIXEL
);

/****************************************************************//**
 * @brief デフォルト設定のブレンドデスク作成関数
 * @return ブレンドデスク
 *******************************************************************/
ATL_BLEND_DESC ATLSCreateBlendDesc();

/****************************************************************//**
 * @brief ラスタライザーデスク
 * 
 * @param [in] FillMode	三角形の描画に使用する塗りつぶしモード
 * @param [in] CullMode カリングモード
 * @return ラスタライザーデスク
 *******************************************************************/
ATL_RASTERIZER_DESC ATLSCreateRasterizerDesc(
	ATL_FILL_MODE FillMode,
	ATL_CULL_MODE CullMode
);

/****************************************************************//**
 * @brief グラフィクスパイプラインデスク作成関数
 * 
 * @param [in] VS				頂点シェーダー情報
 * @param [in] PS				ピクセルシェーダー情報
 * @param [in] BlendState		ブレンドステート
 * @param [in] RasterizerState	ラスタライザーステート
 * @param [in] DepthEnable		デプスを使うか使わないか
 * @param [in] StencilEnable	ステンシルを使うか使わないか
 * @param [in] InputLayout		インプットレイアウト
 * @param [in] SampleCount		1画素当たりのマルチサンプル数、初期は1
 * @param [in] SampleQuality	画質レベル、初期は0
 * @return
 *******************************************************************/
ATL_GRAPHICS_PIPELINE_STATE_DESC ATLSCreatePipeLineStateDesc(
	ATL_SHADER_BYTECODE VS,
	ATL_SHADER_BYTECODE PS,
	ATL_BLEND_DESC BlendState,
	ATL_RASTERIZER_DESC RasterizerState,
	bool DepthEnable,
	bool StencilEnable,
	ATL_INPUT_LAYOUT_DESC InputLayout,
	unsigned int SampleCount = 1,
	unsigned int SampleQuality = 0
);

/****************************************************************//**
 * @brief ビューポート作成関数
 * 
 * @param [in] ScreenWidth	画面幅
 * @param [in] ScreenHeight	画面高さ
 * @return					ビューポート
 *******************************************************************/
ATL_VIEWPORT ATLSCreateViewport(
	float ScreenWidth,
	float ScreenHeight
);

/****************************************************************//**
 * @brief レクト作成関数
 * 
 * @param [in] ScreenWidth  画面幅
 * @param [in] ScreenHeight 画面高さ
 * @return					レクト
 *******************************************************************/
ATL_RECT ATLSCreateRect(
	unsigned int ScreenWidth,
	unsigned int ScreenHeight
);