/**
*	@file	win32debugstream.hpp
*	@author	takagi@kijineko.co.jp
*	@brief	Win32���ɂ�����f�o�b�K���M�X�g���[���̐錾��`
*
*	OutputDebugString API��p�����f�o�b�K�ւ̑��M���X�g���[���Ɍ��т��邽�߂̃N���X��񋟂���B
*
*	@code
*	// �g�p��
*	#include <win32debugstream.hpp>
*	int main()
*	{
*		owin32debugstream ostr;
*		ostr << "�g���[�X������" << std::endl;
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

/// �����^�Ɉˑ�������OutputDebugString���Ăяo�����߂̃��b�p�[�֐��i�i���[������Łj
inline void win32debugout(char const* s)
{
	::OutputDebugStringA(s);
}
/// �����^�Ɉˑ�������OutputDebugString���Ăяo�����߂̃��b�p�[�֐��i���C�h������Łj
inline void win32debugout(wchar_t const* s)
{
	::OutputDebugStringW(s);
}

/**
*	@class	basic_win32debugbuf	win32debugstream.hpp <win32debugstream.hpp>
*	@brief	�f�o�b�O���M�o�b�t�@�N���X�e���v���[�g
*	@note	�t�B�[���h�̓r���Ńf�o�b�O�����񂪓r�؂�邱�Ƃ�������邽�߁A����
*			�����ł�overflow�ł͂Ȃ�xsputn���I�[�o�[���C�h���邱�Ƃɂ����B
*
*/
template <class charT, class traits = std::char_traits<charT> >
class basic_win32debugbuf : public std::basic_streambuf<charT, traits>
{
public:
	/// �f�t�H���g�R���X�g���N�^
	basic_win32debugbuf()
	{
		buffer_.reserve(256);	// �K���ȃT�C�Y��\��
	}
protected:
	/// �t�B�[���h������̑��M
	/**
	*	@note	OutputDebugString���Ăяo�����߂ɂ̓i��������t������K�v�����邽�߁A
	*			���炩�̌`�ŃR�s�[���s���K�v������B\n
	*			���̎����ł́A����o�b�t�@���Ċ��t���Ȃ��Ă��ςނ悤�ɁAbuffer_��
	*			�f�[�^�����o�Ƃ��Ď����Ƃɂ����B
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
*	@brief	�f�o�b�O���M�X�g���[���N���X�e���v���[�g
*/
template <class charT, class traits = std::char_traits<charT> >
class basic_owin32debugstream : public std::basic_ostream<charT, traits>
{
public:
	/// �f�t�H���g�R���X�g���N�^
	basic_owin32debugstream()
		: std::basic_ostream<charT, traits>(&rdbuf_)
	{
	}
private:
	basic_win32debugbuf<charT, traits> rdbuf_;
};

// �^��`

/// �i���[�����ł̃f�o�b�O���M�o�b�t�@�N���X
typedef basic_win32debugbuf<char> win32debugbuf;
/// ���C�h�����ł̃f�o�b�O���M�o�b�t�@�N���X
typedef basic_win32debugbuf<wchar_t> wwin32debugbuf;

/// �i���[�����ł̃f�o�b�O���M�X�g���[���N���X
typedef basic_owin32debugstream<char> owin32debugstream;
/// ���C�h�����ł̃f�o�b�O���M�X�g���[���N���X
typedef basic_owin32debugstream<wchar_t> wowin32debugstream;

#endif	// WIN32DEBUGSTREAM_HPP_