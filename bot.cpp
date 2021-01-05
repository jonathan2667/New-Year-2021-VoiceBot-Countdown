#pragma warning(disable:4996)
#include <iostream>
#include <string>
#include <ctime>
#include <sapi.h>
#include <ctime>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>

using namespace std;

int HOUR, SEC, MIN, Min, Sec, Hour;

class RED {
private:
    string const& s;
public:
    RED(string const& s) : s(s) {}
    friend ostream& operator<<(ostream& os, RED const& b) {
        os << "\033[31m" << b.s << "\033[0m";
        return os;
    }
};

void gettime() {
    time_t currentTime;
    struct tm* localTime;

    time(&currentTime);                   // Get the current time
    localTime = localtime(&currentTime);  // Convert the current time to the local time

    Hour = localTime->tm_hour;
    Min = localTime->tm_min;
    Sec = localTime->tm_sec;

    std::cout << "The current time is : " << Hour << ":" << Min << ":" << Sec << std::endl;
     HOUR = 23 - Hour;
     MIN = 60 - Min;
     SEC = 60 - Sec;
     if (HOUR >= 0)
         std::cout << RED("2021 is in exactly : ");
     else
         cout << "It s been exactly ";
     cout << HOUR << ":" << MIN << ":" << SEC ;
     if (!(HOUR >= 0))
         cout << " since we hit 2021";

}

int act() {
    time_t currentTime;
    struct tm* localTime;

    time(&currentTime);                   // Get the current time
    localTime = localtime(&currentTime);
    Sec = localTime->tm_sec;
    return Sec;
}


int main(int argc, char* argv[])
{
    bool ok = 0;
    while (true) {


        ISpVoice* pVoice = NULL;

        if (FAILED(::CoInitialize(NULL)))
            return FALSE;

        HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
        if (SUCCEEDED(hr))
        {
            if (ok) {

                for (int i = 0; i < 5; ++i)
                    hr = pVoice->Speak(L"houraaaaaaa", 0, NULL);
                for (int i = 0; i < 5; i++)
                    hr = pVoice->Speak(L"HAPPY NEW YEAR WE ARE IN 2021 ", 0, NULL);

            }
            gettime();

            if (HOUR >= 0) {
                hr = pVoice->Speak(L"2021 is in exactly", 0, NULL);


                std::wstring input = std::to_wstring(HOUR) + L" hour";
                hr = pVoice->Speak(input.c_str(), 0, NULL);

                std::wstring input1 = std::to_wstring(MIN) + L" minutes and";
                hr = pVoice->Speak(input1.c_str(), 0, NULL);

                std::wstring input2 = std::to_wstring(SEC) + L" seconds";
                hr = pVoice->Speak(input2.c_str(), 0, NULL);

                hr = pVoice->Speak(L"HAPPY NEW YEAR!!!", 0, NULL);

                pVoice->Release();
                pVoice = NULL;
            }
            else {
                hr = pVoice->Speak(L"HAPPY NEW YEAR!!! It has been ", 0, NULL);

                std::wstring input = std::to_wstring(HOUR) + L" hour";
                hr = pVoice->Speak(input.c_str(), 0, NULL);

                std::wstring input1 = std::to_wstring(Min) + L" minutes and";
                hr = pVoice->Speak(input1.c_str(), 0, NULL);

                std::wstring input2 = std::to_wstring(Sec) + L" seconds";
                hr = pVoice->Speak(input2.c_str(), 0, NULL);

                hr = pVoice->Speak(L"secondes since we hit 2021. Once again Happy New Year! ", 0, NULL);

            }
        }
        ::CoUninitialize();
        gettime();
        if (ok == 0) {
            if (Min < 59 and Min >= 2)
                std::this_thread::sleep_for(std::chrono::seconds(45));
            else {
                if (Min == 59) {
                    while (true) {
                        int sec = act();
                        std::wstring input3 = std::to_wstring(sec) + L"";
                        hr = pVoice->Speak(input3.c_str(), 0, NULL);
                        if (sec == 0 or sec == 1 or sec == 2)
                            break;
                    }
                    ok = 1;
                }

            }
        }
        else 
            std::this_thread::sleep_for(std::chrono::seconds(60));
    }
    
}
