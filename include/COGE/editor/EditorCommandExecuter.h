#ifndef COGE_EDITORCOMMANDEXECUTER_H
#define COGE_EDITORCOMMANDEXECUTER_H

#define COGE_COMMAND_UNDEFINED 99990
#define COGE_COMMAND_LOAD 0
#define COGE_COMMAND_OPEN 1
#define COGE_COMMAND_SAVE 2
#define COGE_COMMAND_SAVEAS 3
#define COGE_COMMAND_PRINT 4
#define COGE_COMMAND_USE 5
#define COGE_COMMAND_PACK 6

#define COGE_LOADTYPE_UNDEFINED 99990
#define COGE_LOADTYPE_FILE 0
#define COGE_LOADTYPE_PACKAGE 1

#include <string>
#include <vector>
#include <unordered_map>

namespace COGE
{
	class Editor;

	class EditorCommandExecuter
	{
	private:
		COGE::Editor* editor;
		unsigned int pos = 0;
		std::string workingLine;

		unsigned int matchKey(std::string);
		void passSpaces();
	public:
		EditorCommandExecuter(COGE::Editor* edt);
		void handle(std::string);
	};
}

#endif