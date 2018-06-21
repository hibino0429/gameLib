/**
*	@file	win32debugstream.hpp
*	@author	takagi@kijineko.co.jp
*	@brief	Win32環境におけるデバッガ送信ストリームの宣言定義
*
*	OutputDebugString APIを用いたデバッガへの送信をストリームに結びつけるためのクラスを提供する。
*
*	@code
*	// 使用例
*	#include <win32debugstream.hpp>
*	int main()
*	{
*		owin32debugstream ostr;
*		ostr << "トレース文字列" << std::endl;
*	}
*	@endcode
*/
#ifndef	WIN32DEBUGSTREAM_HPP_
#define	WIN32DEBUGSTREAM_HPP_

#ifdef	_MSC_VER
#pragma	once
#endif

#include <windows.h>
#include <string>
#include <ostream>

/// 文字型に依存せずにOutputDebugStringを呼び出すためのラッパー関数（ナロー文字列版）
inline void win32debugout(char const* s)
{
	::OutputDebugStringA(s);
}
/// 文字型に依存せずにOutputDebugStringを呼び出すためのラッパー関数（ワイド文字列版）
inline void win32debugout(wchar_t const* s)
{
	::OutputDebugStringW(s);
}

/**
*	@class	basic_win32debugbuf	win32debugstream.hpp <win32debugstream.hpp>
*	@brief	デバッグ送信バッファクラステンプレート
*	@note	フィールドの途中でデバッグ文字列が途切れることを回避するため、この
*			実装ではoverflowではなくxsputnをオーバーライドすることにした。
*
*/
template <class charT, class traits = std::char_traits<charT> >
class basic_win32debugbuf : public std::basic_streambuf<charT, traits>
{
public:
	/// デフォルトコンストラクタ
	basic_win32debugbuf()
	{
		buffer_.reserve(256);	// 適当なサイズを予約
	}
protected:
	/// フィールド文字列の送信
	/**
	*	@note	OutputDebugStringを呼び出すためにはナル文字を付加する必要があるため、
	*			何らかの形でコピーを行う必要がある。\n
	*			この実装では、毎回バッファを再割付しなくても済むように、buffer_を
	*			データメンバとして持つことにした。
	*/
	std::streamsize xsputn(charT const* s, std::streamsize n)
	{
		buffer_.assign(s, n);
		std::streamsize size = static_cast<std::streamsize>(buffer_.size());
		win32debugout(buffer_.c_str());
		return n;
	}
private:
	std::basic_string<charT, traits> buffer_;
};

/**
*	@class	basic_owin32debugstream	win32debugstream.hpp <win32debugstream.hpp>
*	@brief	デバッグ送信ストリームクラステンプレート
*/
template <class charT, class traits = std::char_traits<charT> >
class basic_owin32debugstream : public std::basic_ostream<charT, traits>
{
public:
	/// デフォルトコンストラクタ
	basic_owin32debugstream()
		: std::basic_ostream<charT, traits>(&rdbuf_)
	{
	}
private:
	basic_win32debugbuf<charT, traits> rdbuf_;
};

// 型定義

/// ナロー文字版のデバッグ送信バッファクラス
typedef basic_win32debugbuf<char> win32debugbuf;
/// ワイド文字版のデバッグ送信バッファクラス
typedef basic_win32debugbuf<wchar_t> wwin32debugbuf;

/// ナロー文字版のデバッグ送信ストリームクラス
typedef basic_owin32debugstream<char> owin32debugstream;
/// ワイド文字版のデバッグ送信ストリームクラス
typedef basic_owin32debugstream<wchar_t> wowin32debugstream;

#endif	// WIN32DEBUGSTREAM_HPP_