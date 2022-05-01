#include <iostream>
#include <string.h>
#include <dirent.h>
#include <typeinfo>
#include <fstream>
using namespace std;

void show_dir(const char *s) {
    //cout << typeid(s).name() << endl;
        DIR *dir;
        struct dirent *ent;
        dir = opendir (s);
        if (dir != NULL) {
        /* print all the files and directories within directory */
            while ((ent = readdir (dir)) != NULL) {
                printf ("%s\n", ent->d_name);
            }
            closedir (dir);
        }
        else {
        /* could not open directory */
        perror ("");
        cout << "!!! " << EXIT_FAILURE << "!!! " <<endl;
        }
        cout << endl;
}
string get_word(string msg, int n) {
    int current = 0;
    string word ="";
    for(int i = 0; i < msg.length(); i++) {

        if(msg[i] == ' ') {
            if(current == n) {
                break;
            } else {
                word = "";
                current++;
            }
        } else if(msg[i] == '|') {
            word += ' ';
            i++;
        } else {
            word += msg[i];
        }
    }
    return word;
}

int main()
{
    char elem;
    ifstream infile;
    ofstream outfile;
/*



*/

    string input, command, copied_loc, paste_loc;
    char a[255] = "";
    while (1) {

        cout << ">>>> ";
        getline(cin, input);

        //command = get_command(a);
        command = get_word(input, 0);

        if (command == "dir") {
            strcpy(a, get_word(input, 1).c_str());
            show_dir(a);
        } else if (command == "copy") {
            copied_loc = get_word(input, 1);
        } else if (command == "paste") {
            paste_loc = get_word(input, 1);
            //cout << copied_loc << " is pasted to: " << get_word(input, 1) << endl;
            infile.open(copied_loc, ios::binary);
            outfile.open(paste_loc, ios::binary | ios::app);
            infile.seekg(0, ios::beg);
            while (infile.read((char*)&elem, sizeof(elem)))
            {
                outfile.write((char*)&elem, sizeof(elem));
            }
            infile.close();
            outfile.close();
        } else if(command == "read") {
            infile.open(get_word(input, 1), ios::binary);
            infile.seekg(0, ios::beg);
            while (infile.read((char*)&elem, sizeof(elem)))
            {
                cout << elem;
                //std::cout << std::hex << (int)a[i] << endl;
            }
            cout << endl;
            infile.close();

        } else if (command == "hex") {
            infile.open(get_word(input, 1), ios::binary);
            infile.seekg(0, ios::beg);
            while (infile.read((char*)&elem, sizeof(elem)))
            {
                //cout << elem;
                cout << hex << (int)elem << " ";
            }
            cout << endl;
            infile.close();

        } else if (command == "exit") {
            break;
        } else {
            cout << "Command not found!" << endl;
        }

    }
}
