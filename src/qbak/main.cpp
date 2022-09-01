#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include <regex>
#include <algorithm>

using namespace std;

main()
{
     string head = "$       __        __  \n"
                   "$ ___ _/ /  ___ _/ /__\n"
                   "$/ _ `/ _ \\/ _ `/  '_/\n"
                   "$\\_, /_.__/\\_,_/_/\\_\\ \n"
                   "$ /_/                 ";
     string ver = "v1.0.1";
     string cred = "                     by o7q";

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

     // create backups directory
     string bakName = "qbackup." + m_str + d_str + y_str + "_" + t_h_str + t_m_str + t_s_str;
     string dirCmd = "mkdir qbackups\\" + bakName + "\\qbackup";
     system(dirCmd.c_str());

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
                 cred + "\n\n";

     // check if config exists
     string pthIn;
     ifstream chkCfg;
     chkCfg.open("qbackups\\qbak_cfg");
     if (!chkCfg)
     {
          // create config
          cout << "Specify a directory:\n> ";
          char pthIn[4096];
          cin.getline(pthIn, sizeof(pthIn));
          ofstream crtCfg;
          crtCfg.open("qbackups\\qbak_cfg");
          crtCfg << pthIn;
          crtCfg.close();
     }

     // read config
     string cfg_str;
     ifstream rdCfg("qbackups\\qbak_cfg");
     getline(rdCfg, cfg_str);
     rdCfg.close();

     // format config
     cfg_str.erase(remove(cfg_str.begin(), cfg_str.end(), '"'), cfg_str.end());
     cfg_str = "\"" + cfg_str + "\" ";

     // backup directory work
     string bakCmd = "powershell -command \"robocopy " + cfg_str + "\"qbackups\\" + bakName + "\\qbackup" + "\" " + "/e | tee-object " + "\"qbackups\\" + bakName + "\\qbackup.log\"";
     system(bakCmd.c_str());
     cout << "\n\n";
}