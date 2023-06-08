#include"head.h"
using namespace std;

void do_something();

int main() {
    SYSTEMTIME time;
    SYSTEMTIME my_time;
    cout << "设置my_time: " << endl;
    cin >> my_time.wHour;
    cin >> my_time.wMinute;
    cin >> my_time.wSecond;

    while (1) {
        GetLocalTime(&time);
        cout << time.wHour << ":" << time.wMinute << ":" << time.wSecond << endl;

        if (time.wHour == my_time.wHour &&
            time.wMinute == my_time.wMinute &&
            time.wSecond == my_time.wSecond) {
            thread t{ do_something };
            if (t.joinable()) {
                cout << "join" << endl;
                t.join();
            }
            break;
        }
        this_thread::sleep_for(chrono::seconds(1));
    }
    return 0;
}

void do_something() {
    AudioClip ac;
    cout << "时间到！" << endl;
    if (!ac.load("./src.mp3")) {
        cout << "local error!" << endl;
        exit(0);
    }
    if (!ac.play()) {
        cout << "play error!" << endl;
        exit(0);
    }
    system("pause");
}