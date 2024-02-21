#include <COGE/editor/EditorCommandExecuter.h>
#include <COGE/Macros.h>

std::string getUntilSpace(std::string text)
{
	std::string result = "";
	for(unsigned int i = 0;i<text.size();i++)
		if(text[i]==' ' && result.size()!=0) return result;
		else if(text[i]!=' ') result+=text[i];
	return result;
}

std::string goFetchFirst(std::string line)
{

}


COGE::EditorCommandExecuter::EditorCommandExecuter(COGE::Editor* edt)
{
	editor = edt;
	pos = 0;
}

void COGE::EditorCommandExecuter::passSpaces()
{
	while((pos < workingLine.size()) || (workingLine[pos]==' ')) pos++;
}

unsigned int COGE::EditorCommandExecuter::matchKey(std::string command)
{
	std::string key = getUntilSpace(command);
	if(key == "load") return COGE_COMMAND_LOAD;
	else if(key == "save") return COGE_COMMAND_SAVE;
	return COGE_COMMAND_UNDEFINED;
}

void COGE::EditorCommandExecuter::handle(std::string line)
{
	workingLine = line; pos = 0;
	unsigned int command = matchKey(line);
	if(command == COGE_COMMAND_LOAD) LOG("LOADING!!!!");
}