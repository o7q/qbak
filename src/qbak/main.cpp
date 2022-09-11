#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <regex>
#include <algorithm>

using namespace std;

namespace cmd
{
     string info = "$INFO";
     string pause = "$PAUSE";
     string disPause = "$!PAUSE";
     string cmdOut = "$CMDOUT";
     string disCmdOut = "$!CMDOUT";
     string purge = "$PURGE";
     string exit = "$EXIT";
}

void program();

// configure functions
void crtDir();
string strRep(string charIn, int amount);
void cinClr();
void clr();

// configure global variables
string head = "$       __        __  \n"
              "$ ___ _/ /  ___ _/ /__\n"
              "$/ _ `/ _ \\/ _ `/  '_/\n"
              "$\\_, /_.__/\\_,_/_/\\_\\ \n"
              "$ /_/                 ";
string ver = "v1.2.0";
string cred;
string bakNam;
int bakNum;
bool cmd_pause;
bool cmd_cmdout;

main()
{
     // configure time
     time_t n = time(NULL);
     tm *tm = localtime(&n);
     int m = 1 + tm->tm_mon;
     int d = tm->tm_mday;
     int y = 1900 + tm->tm_year;
     int t_h = tm->tm_hour;
     int t_m = tm->tm_min;
     int t_s = tm->tm_sec;
     string m_str = to_string(m);
     string d_str = to_string(d);
     string y_str = to_string(y);
     string t_h_str = to_string(t_h);
     string t_m_str = to_string(t_m);
     string t_s_str = to_string(t_s);

     // create backup name and directory
     bakNam = "qbackup." + m_str + d_str + y_str + "_" + t_h_str + t_m_str + t_s_str;
     crtDir();

     cred = strRep(" ", 21) + "by o7q";

     // start qbak
     program();

     return 1;
}

void program()
{
     // create config reset
     string head_script = regex_replace(head, regex("\\$"), "echo ");
     ofstream crtRst;
     crtRst.open("qbak_reset.bat");
     crtRst << "@echo off\n"
               "color a\necho.\n" +
                   head_script + ver +
                   "\necho " + cred +
                   "\ndel /f \"qbackups\\qbak_cfg\" 2> nul\n"
                   "echo.\n"
                   "echo Config reset, you can now specify a new directory.\n"
                   "echo.\n"
                   "pause";
     crtRst.close();

     // configure visuals
     system("color a");
     string head_display = regex_replace(head, regex("\\$"), "");
     cout << "\n" +
                 head_display + ver + "\n" +
                 cred + "\n";
     string n = cmd_pause == true || cmd_cmdout == true ? "\n" : "";
     cout << n;
     string pause0 = cmd_pause == true ? "- PAUSE: ON\n" : "";
     cout << pause0;
     string cmdout0 = cmd_cmdout == true ? "- CMDOUT: ON\n" : "";
     cout << cmdout0;
     cout << "\n";

     // command and directory input
     string in;
     ifstream chkCfg;
     chkCfg.open("qbackups\\qbak_cfg");
     if (!chkCfg)
     {
          cout << "Specify a directory or command:\n-> ";
          getline(cin, in);
          if (in != cmd::info && in != cmd::pause && in != cmd::disPause && in != cmd::cmdOut && in != cmd::disCmdOut && in != cmd::purge && in != cmd::exit)
          {
               if (in.find('$') < in.length())
               {
                    cout << "\nCommands:\n- INFO\n- PAUSE\n- CMDOUT\n- PURGE\n- EXIT\n\n\n";
                    system("pause");
                    clr();
               }
               ofstream crtCfg;
               crtCfg.open("qbackups\\qbak_cfg");
               crtCfg << in;
               crtCfg.close();
          }
     }

     // cmd_info
     if (in == cmd::info)
     {
          cout << "\nqbak by o7q\n"
                  "An ultra-simple and lightweight command-line based backup tool.\n\n"
                  "A list of commands can be accessed by inputting a \"$\" after the \"->\" pointer.\n\nOperating Components:\n"
                  "- robocopy\n\n"
                  "* Farther documentation can be found on the qbak GitHub page which can be accessed by inputting \"G\".\n"
                  "To quit, input any other key.\n\n";
          char g;
          cin >> g;
          if (g == 'G' || g == 'g')
          {
               system("start https://github.com/o7q/qbak");
          }
          cinClr();
          clr();
     }

     // cmd_pause
     if (in == cmd::pause)
     {
          cmd_pause = true;
          clr();
     }

     // cmd_!pause
     if (in == cmd::disPause)
     {
          cmd_pause = false;
          clr();
     }

     // cmd_cmdout
     if (in == cmd::cmdOut)
     {
          cmd_cmdout = true;
          clr();
     }

     // cmd_!cmdout
     if (in == cmd::disCmdOut)
     {
          cmd_cmdout = false;
          clr();
     }

     // cmd_purge
     if (in == cmd::purge)
     {
          cout << "\nAre you sure? (all backups will be destroyed!) [Y = Yes, N = No]\n-> ";
          char y;
          cin >> y;
          if (y == 'Y' || y == 'y')
          {
               system("del \"qbak_reset.bat\" /f");
               system("rmdir \"qbackups\" /s /q");
               bakNum = 0;
               if (cmd_cmdout == true)
               {
                    cout << "\nCMDOUT << del \"qbak_reset.bat\" /f\n";
                    cout << "CMDOUT << \"qbackups\" /s /q\n";
               }
               crtDir();
          }
          cinClr();
          clr();
     }

     // cmd_exit
     if (in == cmd::exit)
     {
          _Exit(0);
     }

     // read config
     string cfg_str;
     ifstream rdCfg("qbackups\\qbak_cfg");
     getline(rdCfg, cfg_str);
     rdCfg.close();

     // format config
     cfg_str.erase(remove(cfg_str.begin(), cfg_str.end(), '"'), cfg_str.end());
     cfg_str = "'" + cfg_str + "' ";

     // backup directory work
     string bakNum_str = to_string(bakNum);
     string bakDirCmd = "mkdir qbackups\\" + bakNam + "\\qbackup" + bakNum_str;
     system(bakDirCmd.c_str());
     string bakCmd = "powershell -command \"robocopy " + cfg_str + "'qbackups\\" + bakNam + "\\qbackup" + bakNum_str + "' " + "/e | tee-object " + "\"qbackups\\" + bakNam + "\\qbackup" + bakNum_str + ".log\"\"";
     system(bakCmd.c_str());
     bakNum += 1;
     cout << "\n\n";

     // run cmds
     string cmdout1 = cmd_cmdout == true ? "\n\nCMDOUT << mkdir qbackups\\" + bakNam + "\\qbackup" + bakNum_str + "\nCMDOUT << " + bakCmd : "";
     cout << cmdout1;
     if (cmd_pause == true)
     {
          cout << "\n\n";
          system("pause");
          system("del \"qbackups\\qbak_cfg\" /f");
          clr();
     }

     _Exit(0);
}

// create directory function
void crtDir()
{
     string dirCmd = "mkdir qbackups\\" + bakNam;
     system(dirCmd.c_str());

     // run cmds
     string cmdout = cmd_cmdout == true ? "CMDOUT << mkdir qbackups\\" + bakNam : "";
     cout << cmdout;
     string n = cmd_cmdout == true ? "\n\n" : "\n";
     if (cmd_pause == true)
     {
          cout << n;
          system("pause");
     }
}

//
string strRep(string charIn, int amount)
{
     string output;
     for (int i = 0; i < amount; i++)
     {
          output += charIn;
     }
     return output;
}

// cin clear function
void cinClr()
{
     cin.clear();
     cin.sync();
}

// clear function
void clr()
{
     system("color 2");
     system("cls");
     program();
}