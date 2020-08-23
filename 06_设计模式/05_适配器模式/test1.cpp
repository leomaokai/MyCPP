//test1.cpp
#include <iostream>
#include <memory>
using namespace std;
//接口VGA
class VGA
{
public:
    virtual void play() = 0;
};
class TV01 : public VGA
{
public:
    void play()
    {
        cout << "using VGA playing" << endl;
    }
};
//只支持VGA接口的电脑
class matebook
{
public:
    void playvideo(VGA *pvga)
    {
        pvga->play();
        delete pvga;
    }
};

//接口HDMI
class HDMI
{
public:
    virtual void play() = 0;
};
class TV02 : public HDMI
{
public:
    void play()
    {
        cout << "using HDMI playing" << endl;
    }
};
//1.换一个支持HDMI接口的电脑(代码重构)
//2.买一个转换头(适配器),将VGA接口转换成HDMI
class VGAtoHDMI : public VGA
{
public:
    VGAtoHDMI(HDMI *p) : phdmi(p) {}
    void play() //转换头
    {
        phdmi->play();
    }
    ~VGAtoHDMI()
    {
        delete phdmi;
    }

private:
    HDMI *phdmi;
};
int main()
{
    matebook mbook;
    mbook.playvideo(new TV01());
    mbook.playvideo(new VGAtoHDMI(new TV02()));

    return 0;
}