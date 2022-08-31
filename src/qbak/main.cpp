#include <iostream>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

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

    // create backups directory
    string bakLoc = "qbackup." + m_str + d_str + y_str + "_" + t_h_str + t_m_str + t_s_str;
    string dirCmd = "mkdir qbackups\\" + bakLoc;
    system(dirCmd.c_str());

    // create config reset
    ofstream crtRst;
    crtRst.open("qbak_reset.bat");
    crtRst << "@echo off\ncolor b\ndel /f \"qbackups\\qbak_cfg\" 2> nul\necho Config reset, you can now specify a new directory.\necho.\npause";
    crtRst.close();

    system("color a");

    // check if config exists
    string pthIn;
    ifstream chkCfg;
    chkCfg.open("qbackups\\qbak_cfg");
    if (!chkCfg)
    {
        // create config
        cout << "Specify a directory:\n> ";
        char pthIn[1024];
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

    // backup directory work
    string bakDest = "\"qbackups\\" + bakLoc + "\" ";
    string bakCmd = "robocopy \"" + cfg_str + "\" " + bakDest + "/e";
    system(bakCmd.c_str());
}