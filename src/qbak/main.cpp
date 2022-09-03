#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <regex>
#include <algorithm>

using namespace std;

void program();

// configure functions
void crtDir();
void clr();

// configure global variables
string head = "$       __        __  \n"
              "$ ___ _/ /  ___ _/ /__\n"
              "$/ _ `/ _ \\/ _ `/  '_/\n"
              "$\\_, /_.__/\\_,_/_/\\_\\ \n"
              "$ /_/                 ";
string ver = "v1.1.0";
string cred = "                     by o7q";
// program variables
string bakNam;
int logNum;
bool debug_pause;
bool debug_outcmd;

main()
{
     // configure time
     time_t n = time(NULL);
     tm *tm = localtime(&n);
     // create time integers
     int m = 1 + tm->tm_mon;
     int d = tm->tm_mday;
     int y = 1900 + tm->tm_year;
     int t_h = tm->tm_hour;
     int t_m = tm->tm_min;
     int t_s = tm->tm_sec;
     // ints -> strings
     string m_str = to_string(m);
     string d_str = to_string(d);
     string y_str = to_string(y);
     string t_h_str = to_string(t_h);
     string t_m_str = to_string(t_m);
     string t_s_str = to_string(t_s);

     // create backup name and directory
     bakNam = "qbackup." + m_str + d_str + y_str + "_" + t_h_str + t_m_str + t_s_str;
     crtDir();

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
                   head_script + ver + "\necho " +
                   cred +
                   "\ndel /f \"qbackups\\qbak_cfg\" 2> nul\n"
                   "echo.\n"
                   "echo Config reset, you can now specify a new directory.\n"
                   "echo.\n"
                   "echo.\n"
                   "pause";
     crtRst.close();

     // configure visuals
     system("color a");
     string head_display = regex_replace(head, regex("\\$"), "");
     cout << "\n" +
                 head_display + ver + "\n" +
                 cred + "\n";
     string n = debug_pause == true || debug_outcmd == true ? "\n" : "";
     cout << n;
     string pause0 = debug_pause == true ? "- DEBUG_PAUSE: ON\n" : "";
     cout << pause0;
     string outcmd0 = debug_outcmd == true ? "- DEBUG_OUTCMD: ON\n" : "";
     cout << outcmd0;
     cout << "\n";

     // check if config exists
     string in;
     ifstream chkCfg;
     chkCfg.open("qbackups\\qbak_cfg");
     if (!chkCfg)
     {
          // create config
          cout << "Specify a directory or command:\n-> ";
          getline(cin, in);
          if (in != "$DEBUG_PAUSE" && in != "$!DEBUG_PAUSE" && in != "$DEBUG_OUTCMD" && in != "$!DEBUG_OUTCMD" && in != "$DEBUG_PURGE" && in != "$DEBUG_EXIT")
          {
               ofstream crtCfg;
               crtCfg.open("qbackups\\qbak_cfg");
               crtCfg << in;
               crtCfg.close();
          }
     }

     // debug_pause
     if (in == "$DEBUG_PAUSE")
     {
          debug_pause = true;
          clr();
     }

     // debug_!pause
     if (in == "$!DEBUG_PAUSE")
     {
          debug_pause = false;
          clr();
     }

     // debug_outcmd
     if (in == "$DEBUG_OUTCMD")
     {
          debug_outcmd = true;
          clr();
     }

     // debug_!outcmd
     if (in == "$!DEBUG_OUTCMD")
     {
          debug_outcmd = false;
          clr();
     }

     // debug_purge
     if (in == "$DEBUG_PURGE")
     {
          cout << "\nAre you sure? (all backups will be destroyed!) [Y = Yes, N = No]\n-> ";
          char prompt;
          cin >> prompt;
          if (prompt == 'Y' || prompt == 'y')
          {
               system("del \"qbak_reset.bat\" /f");
               system("rmdir \"qbackups\" /s /q");
               logNum = 0;
               if (debug_outcmd == true)
               {
                    cout << "\nOUTCMD << del \"qbak_reset.bat\" /f\n";
                    cout << "OUTCMD << \"qbackups\" /s /q\n";
               }
               crtDir();
          }
          cin.clear();
          cin.sync();
          clr();
     }

     // debug_exit
     if (in == "$DEBUG_EXIT")
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
     string logNum_str = to_string(logNum);
     string bakCmd = "powershell -command \"robocopy " + cfg_str + "'qbackups\\" + bakNam + "\\qbackup" + "' " + "/e | tee-object " + "\"qbackups\\" + bakNam + "\\qbackup" + logNum_str + ".log\"\"";
     system(bakCmd.c_str());
     logNum += 1;
     cout << "\n\n";

     // debug
     string outcmd1 = debug_outcmd == true ? "\n\nOUTCMD << " + bakCmd : "";
     cout << outcmd1;
     if (debug_pause == true)
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
     string dirCmd = "mkdir qbackups\\" + bakNam + "\\qbackup";
     system(dirCmd.c_str());

     // debug
     string outcmd = debug_outcmd == true ? "OUTCMD << mkdir qbackups\\" + bakNam + "\\qbackup" : "";
     cout << outcmd;
     string n = debug_outcmd == true ? "\n\n" : "\n";
     if (debug_pause == true)
     {
          cout << n;
          system("pause");
     }
}

// clear function
void clr()
{
     system("cls");
     program();
}