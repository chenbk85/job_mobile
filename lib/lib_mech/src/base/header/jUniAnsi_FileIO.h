//********************************************************
//
//               Ansi/Unicode line I/O
//
//          Copyright ?2005 Jaroslav Klima
//

// 주의 사항 : 유니코드 프로젝트에서 LineFromFile() 사용시 파일저장을 유니코드-코드페이지1200 또는 울트라에디터에서 유니코드로 변환해줘야함.
//********************************************************

#ifndef _CONFIGSTRING_H_
#define _CONFIGSTRING_H_

#pragma once

#include <stdio.h>
#include <string>
#include <tchar.h>

//---------------------------------------------
// Functions for writing lines of text to files
//---------------------------------------------
namespace nMech
{
	namespace nUNI
	{
		struct jFile_UniAnsi
		{


			// To write an ANSI STL string
			inline bool LineToFile(FILE* f, const std::string& s, int eol = '\n')
			{
				return LineToFile(f, s.c_str(), eol, s.size());
			};

			// To write a Unicode STL string
			inline bool LineToFile(FILE* f, const std::wstring& s, wint_t eol = L'\n')
			{
				return LineToFile(f, s.c_str(), eol, s.size());
			};

			//-----------------------------------------------
			// Functions for reading lines of text from files
			//-----------------------------------------------





			// To write an ANSI zero-terminated string (please consider using STL instead)
			static bool LineToFile(FILE* f, const char* const s, int eol = '\n', size_t length = -1)
			{
				// check if the pointer is valid
				if (!s)
				{
					return false;
				};

				// calculate the string's length
				if (length==-1)
				{
					length = strlen(s);
				};

				// write the string to the file
				size_t n = fwrite(s, sizeof(char), length, f);

				// write line break to the file
				fputc(eol, f);

				// return whether the write operation was successful
				return (n == length);
			};

			// To write a Unicode zero-terminated string (please consider using STL instead)
			static bool LineToFile(FILE* f, const wchar_t* const s, wint_t eol = L'\n', size_t length = -1)
			{
				// check if the pointer is valid
				if (!s)
				{
					return false;
				};

				// calculate the string's length
				if (length==-1)
				{
					length = wcslen(s);
				};    

				// write the string to the file
				size_t n = fwrite(s, sizeof(wchar_t), length, f);

				// write line break to the file
				fputwc(eol, f);

				// return whether the write operation was successful
				return (n == length);
			};

			// To read an ANSI string
			static bool LineFromFile(FILE* f, std::string& s, int eol = '\n', int oef = EOF)
			{
				// reset string
				s.clear();

				// read one char at a time
				while (true)
				{
					// read char
					int c = fgetc(f);        

					// check for EOF
					if (/*c == eof() || */c == EOF) 
						return false;

					// check for EOL
					if (c == eol) 
						return true;

					// append this character to the string
					s += c;
				};
				return true;
			};

			static bool ReadLineFromFile(WCHAR* buf, int buf_size, FILE* pF)
			{
				if( jw_fgets( buf, buf_size-1, pF ) == NULL)
				{
					buf=NULL; return false;
				}
				size_t len = jw_strlen(buf);
				buf[len-1] = NULL; // 여기까지 file로 부터 한라인 읽어서 마지막 의 개행문자를 제거.
				return true;
			}

			// To read a Unicode string
			static bool LineFromFile(FILE* f, std::wstring& s, wint_t eol = '\n', wint_t oef = WEOF)
			{
				// reset string
				s.clear();
				// read one wide char at a time
				while (true)
				{
					// read wide char
					wint_t c = fgetwc(f);

					// check for EOF
					if (/*c == eof() || */c == WEOF) 
						return false;

					// check for EOL
					if (c == eol) 
						return true;

					// append the wide character to the string        
					s += c;
				};
				return true;
			};

		};
	}
}


#endif
