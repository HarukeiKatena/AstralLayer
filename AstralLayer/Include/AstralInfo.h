/**********************************************************//**
 * @file Astralinfo.h
 *************************************************************/
#pragma once
#include"AstralRendererInterface.h"



/// @cond
/// 前方宣言
namespace AstralLayer
{
    class ATLIUnknown;
    class ATLICommandList;
    class ATLIPipeLine;
    class ATLIFence;
    class ATLICommandQueue;
    class ATLISwapChain;
    class ATLIResource;
    class ATLIRenderTargetView;
    class ATLIDepthStencilView;
}
/// @endcond


/****************************************************************//**
 * デフォルト値
 *******************************************************************/
#define ATL_DEFAULT_DEPTH_BIAS              (0)     //!< ATL_RASTRIZER_DESCにあるDepthBiasのデフォルト値
#define ATL_DEFAULT_DEPTH_BIAS_CLAMP        (0.0f)  //!< ATL_RASTRIZER_DESCにあるDepthBiasClampのデフォルト値
#define ATL_DEFAULT_SLOPE_SCALED_DEPTH_BIAS (0.0f)  //!< ATL_RASTRIZER_DESCにあるDepthBiasのデフォルト値
#define ATL_DEFAULT_STENCIL_READ_MASK       (0xff)  //!< ATL_DEPTH_STENCIL_DESCにあるStencilReadMaskのデフォルト値
#define ATL_DEFAULT_STENCIL_WRITE_MASK      (0xff)  //!< ATL_DEPTH_STENCIL_DESCにあるStencilWriteMaskのデフォルト値

/****************************************************************//**
 * リソースフラグ
 *******************************************************************/
enum class ATL_RESOURCE_FLAG : unsigned int
{
    UNKNOWN,        //!< 使ってはいけない
    CONSTANTBUFFER, //!< CBV
    VERTEXBUFFER,   //!< 頂点バッファー
    INDEXBUFFER,    //!< インデックスバッファー
    TEXTURE1D,      //!< テクスチャ1D　未対応
    TEXTURE2D,      //!< テクスチャ2D
    TEXTURE3D,      //!< テクスチャ3D　未対応
};

/****************************************************************//**
 * リソースタイプ
 *******************************************************************/
enum class ATL_RESOURCE_TYPE : unsigned int
{
    UNKNOWN,    //!< 使ってはいけない
    DEFAULT,    //!< 通常状態
    UPLOAD,     //!< 更新
    READBACK,   //!< 読み込み
};

/****************************************************************//**
 * ビューディメンジョン
 *******************************************************************/
enum class ATL_VIEW_DIMENSION : unsigned int
{
    UNKNOWN,        //!< 使ってはいけない
    //TEXTURE1D,    //!< テクスチャ1D
    TEXTURE2D,      //!< テクスチャ2D
    //TEXTURE3D,    //!< テクスチャ3D
};

/****************************************************************//**
 * フォーマット
 *******************************************************************/
enum class ATL_FORMAT : unsigned int
{
    UNKNOWN,                //!< 未設定

    R32G32B32A32_TYPELESS,  //!< 4成分128ビットでデータ型が定義されていない
    R32G32B32A32_FLOAT,     //!< 4成分128ビットのfloat
    R32G32B32A32_UINT,      //!< 4成分128ビットのunsigned int
    R32G32B32A32_SINT,      //!< 4成分128ビットのsigned int

    R32G32B32_TYPELESS,     //!< 3成分96ビットでデータ型が定義されていない
    R32G32B32_FLOAT,        //!< 3成分96ビットのfloat
    R32G32B32_UINT,         //!< 3成分96ビットのunsigned int
    R32G32B32_SINT,         //!< 4成分96ビットのsigned int

    R16G16B16A16_TYPELESS,  //!< 4成分64ビットでデータ型が定義されていない
    R16G16B16A16_UINT,      //!< 4成分64ビットのunsigned int
    R16G16B16A16_SINT,      //!< 4成分64ビットのsigned int

    R32G32_TYPELESS,        //!< 2成分64ビットでデータ型が定義されていない
    R32G32_FLOAT,           //!< 2成分64ビットのfloat
    R32G32_UINT,            //!< 2成分64ビットのunsigned int
    R32G32_SINT,            //!< 2成分64ビットのsigned int

    R8G8B8A8_TYPELESS,      //!< 4成分32ビットでデータ型が定義されていない
    R8G8B8A8_UINT,          //!< 4成分32ビットのunsigned int
    R8G8B8A8_SINT,          //!< 4成分32ビットのsigned int

    R16G16_TYPELESS,        //!< 2成分32ビットでデータ型が定義されていない
    R16G16_UINT,            //!< 2成分32ビットのunsigned int
    R16G16_SINT,            //!< 2成分32ビットのsigned int

    R32_TYPELESS,           //!< 1成分32ビットでデータ型が定義されていない
    R32_FLOAT,              //!< 1成分32ビットのfloat
    R32_UINT,               //!< 1成分32ビットのunsigned int
    R32_SINT,               //!< 1成分32ビットのsigned int

    R8G8_TYPELESS,          //!< 2成分16ビットでデータ型が定義されていない
    R8G8_UINT,              //!< 2成分16ビットのunsigned int
    R8G8_SINT,              //!< 2成分16ビットのsigned int

    R16_TYPELESS,           //!< 1成分16ビットでデータ型が定義されていない
    R16_UINT,               //!< 1成分16ビットのunsigned int
    R16_SINT,               //!< 1成分16ビットのsigned int

    R8_TYPELESS,            //!< 1成分8ビットでデータ型が定義されていない
    R8_UINT,                //!< 1成分8ビットのunsigned int
    R8_SINT,                //!< 1成分8ビットのsigned int
};

/****************************************************************//**
 * セマンティクスフラグ
 *******************************************************************/
enum class ATL_SEMANTICS_FLAG : unsigned int
{
    POSITION,   //!< 座標
    NORMAL,     //!< 法線
    COLOR,      //!< カラー
    TEXCOORD,   //!< UV(テクスチャーコード)
};

/****************************************************************//**
 * シェーダービジビリティ
 *******************************************************************/
enum class ATL_SHADER_VISIBILITY : unsigned int
{
    ALL,    //!< すべて
    VERTEX, //!< 頂点シェーダー
    PIXEL,  //!< ピクセルシェーダー
    MAX     //!< 使ってはいけない
};

/****************************************************************//**
 * フィルター
 *******************************************************************/
enum class ATL_FILTER : unsigned int
{
    MIN_MAG_MIP_POINT,                          //!< 最小化、拡大、ミップレベルサンプリングにはポイントサンプリングを利用します
    MIN_MAG_POINT_MIP_LINEAR,                   //!< 最小化・拡大かにはポイントサンプリング、ミップレベルサンプリングには線形補完を利用します
    MIN_POINT_MAG_LINEAR_MIP_POINT,             //!< 最小化にはポイントサンプリング、拡大には線形補完、ミップレベルサンプリングにはポイントサンプリングを利用します
    MIN_POINT_MAG_MIP_LINEAR,                   //!< 最小化にはポイントサンプリング、拡大やミップレベルサンプリングには線形補間を使用します
    MIN_LINEAR_MAG_MIP_POINT,                   //!< 最小化には線形補間を、拡大・ミップレベルサンプリングにはポイントサンプリングを使用します
    MIN_LINEAR_MAG_POINT_MIP_LINEAR,            //!< 最小化には線形補間を、拡大にはポイントサンプリングを、ミップレベルサンプリングには線形補間を使用します
    MIN_MAG_LINEAR_MIP_POINT,                   //!< 最小化・拡大化には線形補間、ミップレベルサンプリングにはポイントサンプリングを使用します
    MIN_MAG_MIP_LINEAR,                         //!< 最小化、拡大、ミップレベルサンプリングには、線形補間を使用します
    ANISOTROPIC,                                //!< 最小化、拡大、ミップレベルサンプリングに異方性補間を使用します
    COMPARISON_MIN_MAG_MIP_POINT,               //!< 最小化、拡大、ミップレベルサンプリングには、ポイントサンプリングを使用します。結果を比較値と比較する
    COMPARISON_MIN_MAG_POINT_MIP_LINEAR,        //!< 最小化・拡大化にはポイントサンプリング、ミップレベルサンプリングには線形補間を使用します。結果を比較値と比較する
    COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT,  //!< 最小化にはポイントサンプリング、拡大には線形補間、ミップレベルサンプリングにはポイントサンプリングを使用します。結果を比較値と比較する
    COMPARISON_MIN_POINT_MAG_MIP_LINEAR,        //!< 最小化にはポイントサンプリング、拡大・ミップレベルサンプリングには線形補間を使用します。結果を比較値と比較する
    COMPARISON_MIN_LINEAR_MAG_MIP_POINT,        //!< 最小化には線形補間を、拡大にはポイントサンプリングを、ミップレベルサンプリングにはミップレベルサンプリングを使用します。結果を比較値と比較する
    COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR, //!< 最小化には線形補間を、拡大にはポイントサンプリングを、ミップレベルサンプリングには線形補間を使用します。結果を比較値と比較する
    COMPARISON_MIN_MAG_LINEAR_MIP_POINT,        //!< 最小化・拡大化には線形補間、ミップレベルサンプリングにはポイントサンプリングを使用します。結果を比較値と比較する
    COMPARISON_MIN_MAG_MIP_LINEAR,              //!< 最小化、拡大、ミップレベルサンプリングには、線形補間を使用します。結果を比較値と比較する
    COMPARISON_ANISOTROPIC,                     //!< 最小化、拡大、ミップレベルサンプリングに異方性補間を使用します。結果を比較値と比較する
};

/****************************************************************//**
 * アドレッシングモード
 *******************************************************************/
enum class ATL_ADDRESS_MODE : unsigned int
{
    WRAP,           //!< 範囲[0,1]以外の値でも繰り返し表示される
    MIRROR,         //!< 0または1を境界に反転させる
    CLAMP,          //!< 範囲[0,1]でクランプします　列の最上部と行にあるカラーが範囲外のカラーになります
    BORDER,         //!< 範囲[0,1]を境界に任意のカラーを範囲外に適応します
};

/****************************************************************//**
 * 比較オプション
 *******************************************************************/
enum class ATL_COMPARISON_FUNC : unsigned int
{
    NEVER,          //!< 比較対象は絶対にパス
    LESS,           //!< 比較元データが比較先データより小さい場合、比較はパスする
    EQUAL,          //!< 比較元データと比較先データが等しい場合、比較は成功する
    LESS_EQUAL,     //!< 比較元データが比較先データより小さいか等しい場合、比較はパスする
    GREATER,        //!< 比較元データが比較先データより大きい場合、比較は成功する
    NOT_EQUAL,      //!< 比較元データと比較先データが等しくない場合、比較はパスする
    GREATER_EQUAL,  //!< 比較元データが比較先データより大きいか等しい場合、比較は成功する
    ALWAYS,         //!< 必ず比較をパスする
};

/****************************************************************//**
 * デスクリプターヒープのタイプ
 *******************************************************************/
enum class ATL_DESCRIPTOR_HEAP_TYPE : unsigned int
{
    CBV_SRV_UAV,    //!< 定数バッファー、シェーダーリソースビュー、アンオーダードアクセスビュー
    SAMPLER,        //!< サンプラー
    RTV,            //!< レンダーターゲットビュー
    DSV,            //!< デプスステンシルビュー
};

/****************************************************************//**
 * デスクリプターのタイプ
 *******************************************************************/
enum class ATL_DESCRIPTOR_TYPE : unsigned int
{
    CBV,    //!< 定数バッファー
    SRV,    //!< シェーダーリソースビュー
    UAV,    //!< アンオーダードアクセスビュー
};

/****************************************************************//**
 * ボーダーカラー
 *******************************************************************/
enum class ATL_BORDER_COLOR : unsigned int
{
    TRANSPARENT_BLACK,  //!< カラー黒 アルファ[0]
    OPAQUE_BLACK,       //!< カラー黒 アルファ[255]
    OPAQUE_WHITE,       //!< カラー白 アルファ[255]
};

/****************************************************************//**
 * 三角形の描画に使用する塗りつぶしモード
 *******************************************************************/
enum class ATL_FILL_MODE : unsigned int
{
    WIREFRAME,  //!< 頂点と頂点を結ぶ線
    SOLID,      //!< 三角形を塗りつぶす
};

/****************************************************************//**
 * カリングモード
 *******************************************************************/
enum class ATL_CULL_MODE : unsigned int
{
    NONE,   //!< すべての三角形を描画
    FRONT,  //!< 正面を向いた三角形を描画しない
    BACK    //!< 裏向きの三角形を描画しない
};

/****************************************************************//**
 * ブレンドモード
 *******************************************************************/
enum class ATL_BLEND : unsigned int
{
    ZERO,               //!< ブレンドファクターは(0,0,0,0) 、プリブレンド操作は行わない
    ONE,                //!< ブレンドファクターは(1,1,1,1) 、プリブレンド操作は行わない
    SRC_COLOR,          //!< ブレンドファクターは(R,G,B,A) 、プリブレンド操作は行わない
    INV_SRC_COLOR,      //!< ブレンドファクターは(1-R,1-G,1-B,1-A)、プリブレンド処理によってデータが反転され、1-RGBが生成される
    SRC_ALPHA,          //!< ブレンドファクターは(A,A,A,A)、プリブレンド操作は行わない
    INV_SRC_ALPHA,      //!< ブレンドファクターは(1-A,1-A,1-A,1-A)、プリブレンド演算はデータを反転させ、1-Aを生成する
    DEST_ALPHA,         //!< ブレンドファクターは(A,A,A,A)、ブレンド前の操作はありません
    INV_DEST_ALPHA,     //!< ブレンドファクターは(1-A,1-A,1-A,1-A)、プリブレンド操作によってデータが反転され、1 - Aが生成される
    DEST_COLOR,         //!< ブレンドファクターは(Rd,Gd,Bd,Ad)、プリブレンド操作は行わない
    INV_DEST_COLOR,     //!< ブレンドファクターは(1-Rd,1-Gd,1-Bd,1-Ad)、プリブレンド操作によってデータが反転され、1-RGBが生成される
    SRC_ALPHA_SAT,      //!< ブレンドファクターは(f, f, f, 1)であり、f = min(A, 1)、プリブレンド操作により、データが1以下になるようにクランプされる
    SRC1_COLOR,         //!< ブレンドファクターはピクセルシェーダが出力するカラーデータとしてのデータソースの両方です。ブレンド前の操作はありません。このブレンドファクターはデュアルソースカラーブレンディングをサポートします
    INV_SRC1_COLOR,     //!< ブレンドファクターはピクセルシェーダーが出力するカラーデータとしての両方のデータソースです。プリブレンド操作によりデータが反転され、1-RGBが生成されます。このブレンドファクターはデュアルソースカラーブレンディングをサポートします
    SRC1_ALPHA,         //!< ブレンドファクターはピクセルシェーダーが出力するアルファデータとしてのデータソースです。プリブレンドの操作はありません。このブレンドファクターはデュアルソースカラーブレンディングをサポートします
    INV_SRC1_ALPHA,     //!< ブレンドファクターはピクセルシェーダーから出力されるアルファデータとしてのデータソースです。プリブレンド操作によってデータが反転され、1 - A が生成される。このブレンドファクターはデュアルソースカラーブレンディングをサポートする
};

/****************************************************************//**
 * RGBまたはアルファブレンディングの操作
 *******************************************************************/
enum class ATL_BLEND_OP : unsigned int
{
    ADD,            //!< ソース1、ソース2を加算します
    SUBTRACT,       //!< ソース2からソース1を減算します
    REV_SUBTRACT,   //!< ソース1からソース2を減算します
    MIN,            //!< ソース1とソース2の最小値を求めよ
    MAX,            //!< ソース1とソース2の最大値を求めよ
};

/****************************************************************//**
 * デプスデータを書き込む部分を特定する
 *******************************************************************/
enum class ATL_DEPTH_WRITE_MASK
{
    ZERO,   //!< デプスステンシルバッファへの書き込みをオフにします
    ALL,    //!< デプスステンシルバッファへの書き込みをオンにします
};

/****************************************************************//**
 * デプスステンシルのテスト時に実行可能なステンシル操作のこと
 *******************************************************************/
enum class ATL_STENCIL_OP
{
    KEEP,       //!< 既存のステンシルデータを保持します
    ZERO,       //!< ステンシルデータを0にする
    INCR_SAT,   //!< ステンシル値を1だけ増加させ、その結果をクランプする
    DECR_SAT,   //!< ステンシル値を1つ減らし、その結果をクランプする
    INVERT,     //!< ステンシルデータを反転させる
    INCR,       //!< ステンシル値を1増加させ、必要に応じて結果をラップする
    DECR,       //!< ステンシル値を1つ減らし、必要なら結果をラップする
};

/****************************************************************//**
 * バリアータイプ
 *******************************************************************/
enum class ATL_BARRIER_TYPE
{
    RENDER_TARGET,  //!< RTV
    UAV,            //!< UAV
};

/****************************************************************//**
 * れソースステータス
 *******************************************************************/
enum class ATL_RESOURCE_STATE
{
    PRESENT,        //!< Present
    RENDER_TARGET,  //!< レンダーターゲット
};

/****************************************************************//**
 * プリミティブトポロジー
 *******************************************************************/
enum class ATL_PRIMITIVE_TOPOLOGY
{
    POINTLIST,      //!< ポイントリスト
    LINELIST,       //!< ラインリスト
    LINESTRIP,      //!< ラインストリップ
    TRIANGLELIST,   //!< トライアングルリスト
    TRIANGLESTRIP,  //!< トライアングルストリップ
};

/****************************************************************//**
 * レンダリングターゲットの各ピクセルのうち、ブレンディング中に書き込み可能なコンポーネントを特定する。
 *******************************************************************/
enum class ATL_COLOR_WRITE_ENABLE : unsigned char
{
    RED     = 1 << 0,   //!< 赤色コンポーネントをデータを格納できるようにする
    GREEN   = 1 << 1,   //!< 緑色色コンポーネントをデータを格納できるようにする
    BLUE    = 1 << 2,   //!< 青色コンポーネントをデータを格納できるようにする
    ALPHA   = 1 << 3,   //!< アルファコンポーネントをデータを格納できるようにする
    ALL     = RED | GREEN | BLUE | ALPHA,   //!< すべてコンポーネントをデータを格納できるようにする
};
constexpr ATL_COLOR_WRITE_ENABLE operator|(ATL_COLOR_WRITE_ENABLE a, ATL_COLOR_WRITE_ENABLE b)
{
    return static_cast<ATL_COLOR_WRITE_ENABLE>(static_cast<unsigned char>(a) | static_cast<unsigned char>(b));
}

/****************************************************************//**
 * ATLICommandList::ClearDepthStencilView()で指定する数値
 *******************************************************************/
enum class ATL_CLEAR_FLAG : unsigned int
{
    DEPTH   = 1 << 0,   //!< デプス
    STENCIL = 1 << 1,   //!< ステンシル
};
constexpr ATL_CLEAR_FLAG operator|(ATL_CLEAR_FLAG a, ATL_CLEAR_FLAG b)
{
    return static_cast<ATL_CLEAR_FLAG>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
}

/****************************************************************//**
 * DSVディメンション
 *******************************************************************/
enum class ATL_DSV_DIMENSION
{
    TEXTURE1D,      //!< 1次元のテクスチャとしてアクセスされる
    TEXTURE2D,      //!< 2次元のテクスチャとしてアクセスされる
    TEXTURE2DMS,    //!< マルチサンプリングの2次元テクスチャとしアクセスされる
};

/****************************************************************//**
 * サンプラーデスク
 *******************************************************************/
struct ATL_SAMPLE_DESC
{
    unsigned int Count;     //!< 1画素当たりのマルチサンプル数
    unsigned int Quality;   //!< 画質レベル
};

/****************************************************************//**
 * リソースデスク
 *******************************************************************/
struct ATL_RESOURCE_DESC
{
    unsigned int ByteStructure; //!< 構造体サイズ
    unsigned int Width;         //!< 横幅
    unsigned int Height;        //!< 縦幅
    unsigned int NumObject;     //!< オブジェクト数
    unsigned int MipLevel;      //!< ミップレベル
    ATL_FORMAT Format;          //!< フォーマット
    ATL_SAMPLE_DESC SampleDesc; //!< サンプルデスク
    ATL_RESOURCE_TYPE Type;     //!< タイプ
    ATL_RESOURCE_FLAG Flag;     //!< フラグ
};

/****************************************************************//**
 * シェーダーリソースビューデスク
 *******************************************************************/
struct ATL_SHADER_RESOURCE_VIEW_DESC
{
    ATL_VIEW_DIMENSION Dimension;   //!< ディメンジョン
    ATL_FORMAT Format;              //!< フォーマット
    unsigned int MipLevels;         //!< ミップレベル
};

/****************************************************************//**
 * デプスステンシルビューデスク
 *******************************************************************/
struct ATL_DEPTH_STENCIL_VIEW_DESC
{
    unsigned int Width;         //!< 幅
    unsigned int Height;        //!< 高さ
    ATL_SAMPLE_DESC SampleDesc; //!< サンプルデスク
    ATL_DSV_DIMENSION Dimension;//!< ディメンジョン
};

/****************************************************************//**
 * ビューポート
 *******************************************************************/
struct ATL_VIEWPORT
{
    float TopLeftX; //!< 左側のX
    float TopLeftY; //!< 上部のY
    float Width;    //!< 幅　　0以上
    float Height;   //!< 高さ　0以上
    float MinDepth; //!< 最小深度　0～1の範囲で指定
    float MaxDepth; //!< 最大深度　0～1の範囲で指定
};

/****************************************************************//**
 * レクト
 *******************************************************************/
struct ATL_RECT
{
    unsigned int left;  //!< 左上X
    unsigned int top;   //!< 上部Y
    unsigned int right; //!< 右上X
    unsigned int bottom;//!< 下部Y
};

#if defined(ASTRAL_WINDOWS)
/****************************************************************//**
 * スワップチェイン　(Windows用)
 *******************************************************************/
struct ATL_SWAPCHAIN_DESC
{
    unsigned int Width;         //!< バッファーカウント
    unsigned int Height;        //!< 幅
    ATL_SAMPLE_DESC Sample;     //!< マルチサンプリング
    bool Windowed;              //!< ウィンドウモードで表示するかしないか　trueはウィンドウモード falseはフルスクリーン
    HWND hWnd;                  //!< ウィンドウハンドル
};
#elif defined(ASTRAL_MAC)

#endif

/****************************************************************//**
 * ルートパラメーター
 *******************************************************************/
struct ATL_ROOT_PARAMETER
{
    ATL_DESCRIPTOR_TYPE Type;               //!< デスクリプターのタイプ
    ATL_SHADER_VISIBILITY ShaderVisibirity; //!< シェーダービジビリティ
    unsigned int ShaderRegister;            //!< レジスターの先頭番号
};

/****************************************************************//**
 * サンプラーデスク
 *******************************************************************/
struct ATL_SAMPLER_DESC
{
    ATL_FILTER Filter;                      //!< サンプリングする際の補完の方法
    ATL_ADDRESS_MODE AddressU;              //!< UVの値が0～1以外の場合の処理方法
    ATL_ADDRESS_MODE AddressV;              //!< UVの値が0～1以外の場合の処理方法
    ATL_ADDRESS_MODE AddressW;              //!< UVの値が0～1以外の場合の処理方法
    float MipLODBias;                       //!< 計算されたミップマップレベルのオフセット
    unsigned int MaxAnisotropy;             //!< FilterにANISOTROPIC,COMPARISON_ANISOTROPICが指定されている場合のクランプ値　範囲 1～16
    ATL_COMPARISON_FUNC ComparisionFunc;    //!< 既存のサンプリングデータに対してデータを比較する関数
    ATL_BORDER_COLOR BorderColor;           //!< AddressU,V,WにBORDERが指定されている場合に使用される境界の色
    float MinLOD;                           //!< クランプするミップマップ範囲の下限
    float MaxLOD;                           //!< クランプするミップマップ範囲の上限
    unsigned int ShaderRegister;            //!< レジスターの番号
    ATL_SHADER_VISIBILITY Visibility;       //!< シェーダービジビリティ
};

/****************************************************************//**
 * ルートシグネチャー
 *******************************************************************/
struct ATL_ROOT_SIGNATURE_DESC
{
    ATL_ROOT_PARAMETER* pRootParameters;//!< ルートパラメーター
    unsigned int NumRootParameters;     //!< ルートパラメーターの数
    ATL_SAMPLER_DESC* pSamplers;        //!< サンプラー
    unsigned int NumSamplers;           //!< サンプラーの数
};

/****************************************************************//**
 * インプットエレメント
 *******************************************************************/
struct ATL_INPUT_ELEMENT_DESC
{
    const char* SemanticsName;      //!< セマンティクスの名前
    ATL_FORMAT Format;              //!< フォーマット
    unsigned int AlignedByteOffset; //!< 頂点の開始点からこの要素までのオフセットをバイト単位で指定する
};

/****************************************************************//**
 * インプットレイアウトデスク
 *******************************************************************/
struct ATL_INPUT_LAYOUT_DESC
{
    const ATL_INPUT_ELEMENT_DESC* pInputElementDescs;   //!< インプットエレメント
    unsigned int NumElements;                           //!< インプットエレメントの数
};

/****************************************************************//**
 * レジスターデスク
 *******************************************************************/
struct ATL_RASTERIZER_DESC
{
    ATL_FILL_MODE FillMode;     //!< フィルモード
    ATL_CULL_MODE CullMode;     //!< カリングモード
    bool FrontCounterClockwise; //!< 三角形が正面か背面向きかを決める　true反時計回り　false時計回り
    int DepthBias;              //!< ピクセルに追加される深度バイアス
    float DepthBiasClamp;       //!< ピクセルの最大深度バイアス
    float SlopeScaledDepthBias; //!< ピクセルの傾きのスカラー
    bool DepthClipEnable;       //!< 距離によるクリッピングを有効にするか
    bool MultisampleEnable;     //!< マルチサンプル・アンチエイリアシングで四辺形ラインとアルファラインのどちらを使うか true四辺形ライン　falseアルファライン
    bool AntialiasedLineEnable; //!< ラインアンチエイリアシングを有効にするか MultisampleEnableがfalseの時に適用される
};

/****************************************************************//**
 * @brief レンダーターゲット
 * 
 * - デフォルト値\n
 * BlendEnable           = false\n
 * SrcBlend              = ATL_BLEND::ONE\n
 * DestBlend             = ATL_BLEND::ZERO\n
 * BlendOp               = ATL_BLEND_OP::ADD\n
 * SrcBlendAlpha         = ATL_BLEND::ONE\n
 * DestBlendAlpha        = ATL_BLEND::ZERO\n
 * BlendOpAlpha          = ATL_BLEND_OP::ADD\n
 * RenderTargetWriteMask = ATL_COLOR_WRITE_ENABLE::ALL\n
 *******************************************************************/
struct ATL_RENDER_TARGET_BLEND_DESC
{
    bool BlendEnable;                               //!< ブレンドを有効にする際はtrue
    ATL_BLEND SrcBlend;                             //!< ピクセルシェーダーが出力するRGB値に対して行う操作を指定する
    ATL_BLEND DestBlend;                            //!< レンダーターゲットの現在のRGB値に対して実行する操作を指定する
    ATL_BLEND_OP BlendOp;                           //!< SrcBlendとDestBlendの組み合わせ方を定義する
    ATL_BLEND SrcBlendAlpha;                        //!< ピクセルシェーダーが出力するアルファ値に対して行う操作を指定する
    ATL_BLEND DestBlendAlpha;                       //!< レンダリングターゲットの現在のアルファ値に対して実行する操作を指定する
    ATL_BLEND_OP BlendOpAlpha;                      //!< SrcBlendAlphaとDestBlendAlphaの合成方法を定義する
    ATL_COLOR_WRITE_ENABLE RenderTargetWriteMask;   //!< 書き込みマスクを指定する　ATL_COLOR_WRITE_ENABLEの値をビット単位のOR演算で組み合わせたもの
};


/****************************************************************//**
 * ブレンドデスク
 *******************************************************************/
struct ATL_BLEND_DESC
{
    bool AlphaToCoverageEnable;                     //!< AlphaToCoverageを使用する場合はtrue
    bool IndependentBlendEnable;                    //!< 同時レンダリングターゲットで独立した有効にするかどうかを指定する falseはRenderTarget[0]のみ使う
    ATL_RENDER_TARGET_BLEND_DESC RenderTarget[8];   //!< レンダーターゲットブレンドデスク
};

/****************************************************************//**
 * シェーダーのバイナリ情報
 *******************************************************************/
struct ATL_SHADER_BYTECODE
{
    const void* pShaderBytecode;    //!< シェーダーのバイナリデータの先頭ポインタ
    unsigned int BytecodeLength;    //!< シェーダーのバイナリデータの長さ
};

/****************************************************************//**
 * デプスステンシルオペレーションデスク
 *******************************************************************/
struct ATL_DEPTH_STENCILOP_DESC
{
    ATL_STENCIL_OP StencilFailOp;       //!< ステンシルテストに失敗したときに実行するステンシル操作
    ATL_STENCIL_OP StencilDepthFailOp;  //!< ステンシルテストが合格、デプステストが不合格の場合に実行するステンシル操作
    ATL_STENCIL_OP StencilPassOp;       //!< ステンシルテストと深度テストの両方が合格したときに実行するステンシル操作
    ATL_COMPARISON_FUNC StencilFunc;    //!< ステンシルデータと既存のステンシルデータを比較する機能を識別する
};

/****************************************************************//**
 * デプスステンシルデスク
 * 
 * - デフォルト値
 * DepthEnable                  : true
 * DepthWriteMask               : ATL_DEPTH_WRITE_MASK::ALL
 * DepthFunc                    : ATL_COMPARISON_FUNC::LESS
 * StencilEnable                : false
 * StencilReadMask              : ATL_DEFAULT_STENCIL_READ_MASK
 * StencilWriteMask             : ATL_DEFAULT_STENCIL_WRITE_MASK
 * 
 * FrontFace.StencilFailOp      : ATL_STENCIL_OP::KEEP
 * FrontFace.StencilDepthFailOp : ATL_STENCIL_OP::KEEP
 * FrontFace.StencilPassOp      : ATL_STENCIL_OP::KEEP
 * FrontFace.StencilFunc        : ATL_COMPARISON_FUNC::ALWAYS
 * 
 * BackFace.StencilFailOp       : ATL_STENCIL_OP::KEEP
 * BackFace.StencilDepthFailOp  : ATL_STENCIL_OP::KEEP
 * BackFace.StencilPassOp       : ATL_STENCIL_OP::KEEP
 * BackFace.StencilFunc         : ATL_COMPARISON_FUNC::ALWAYS
 *******************************************************************/
struct ATL_DEPTH_STENCIL_DESC
{
    bool DepthEnable;                       //!< 深度を利用するかしないか
    ATL_DEPTH_WRITE_MASK DepthWriteMask;    //!< 変更可能な深度ステンシルバッファの部分を指定する
    ATL_COMPARISON_FUNC DepthFunc;          //!< 深度データと既存の深度データを比較する関数を指定
    bool StencilEnable;                     //!< ステンシルを利用するかしないか
    unsigned char StencilReadMask;          //!< ステンシルデータを読み込むためのステンシルバッファを指定する
    unsigned char StencilWriteMask;         //!< ステンシルデータを書き込む部分を指定する
    ATL_DEPTH_STENCILOP_DESC FrontFace;     //!< 表面法線がカメラの方を向いているピクセル深度テストとステンシルテストの結果の使用方法を指定する
    ATL_DEPTH_STENCILOP_DESC BackFace;      //!< 表面法線がカメラの反対側を向いているピクセルに対する深度テストとステンシルテストの結果を使用する方法を指定する
};

/****************************************************************//**
 * グラフィクスパイプライン情報
 *******************************************************************/
struct ATL_GRAPHICS_PIPELINE_STATE_DESC
{
    ATL_SHADER_BYTECODE VS;                     //!< 頂点シェーダー
    ATL_SHADER_BYTECODE PS;                     //!< ピクセルシェーダー
    ATL_BLEND_DESC BlendState;                  //!< ブレンドステート
    ATL_RASTERIZER_DESC RasterizerState;        //!< ラスタライザーステート
    ATL_DEPTH_STENCIL_DESC DepthStencilState;   //!< デプスステンシルステート
    ATL_INPUT_LAYOUT_DESC InputLayout;          //!< インプットレイアウト 
    ATL_SAMPLE_DESC Sample;                     //!< サンプルデスク
    ATL_ROOT_SIGNATURE_DESC RootSignature;      //!< ルートシグネチャーデスク
};

/****************************************************************//**
 * リソースバリア
 *******************************************************************/
struct ATL_RESOURCE_BARRIER
{
    ATL_BARRIER_TYPE Type;                  //!< タイプ
    ATL_RESOURCE_STATE StateBefore;         //!< ステータス使用前
    ATL_RESOURCE_STATE StateAfter;          //!< ステータス使用後

    union
    {
        AstralLayer::ATLIResource* pResource;   //!< リソース
        AstralLayer::ATLIRenderTargetView* pRenderTargetView; //!< RTV
    };
};