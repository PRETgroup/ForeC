#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    ifstream in(argv[1]);

    if (!in)
    {
        cerr << "Cannot open input file: " << argv[2] << endl;
        return 1;
    }

    ofstream out("embed.h");

    if (!out)
    {
        cerr << "Cannot open output file: embed.h" << endl;
        return 2;
    }

    long begin, end;
    begin = in.tellg();
    in.seekg(0, ios::end);
    end = in.tellg();
    in.seekg(0, ios::beg);

    unsigned int c = in.get();
    out << "#define FILE_SIZE " << (end - begin) << "\n\n"
           "char archive[" << (end - begin) << "];\n\n"
           "char embedded[] = {\n"
           "    " << c;

    while (c = in.get(), !in.eof()) {
        out << ",\n"
             << "    " << c;
    }
    
    out << "\n};\n";
}
