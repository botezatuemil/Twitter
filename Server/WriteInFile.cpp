#include "WriteInFile.h"
#include<fstream>
bool WriteInFile::IsEmpty(std::ifstream& pFile)
{
	return pFile.peek() == std::ifstream::traits_type::eof();;
}

void WriteInFile::WriteInFileLogin(User* user)
{
	std::ofstream out("../Server/server.out");
	std::ifstream fin("../Server/server.out");
	bool ok =true;// mai tarziu trebuie sa fac functia care imi returneaza daca exista sau nu
	while (true)
	{
		if (ok == true && IsEmpty(fin) == true)
		{
			out << user->GetUsername() << "\n";
			out << "TRUE";
			break;
		}
		else if(ok == false && IsEmpty(fin) == true)
		{
			out << user->GetUsername() << "\n";
			out << "FALSE";
		}
	}
	

}




