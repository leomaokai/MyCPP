//test1.cpp
#include <iostream>
#include <memory>
using namespace std;

//抽象类
class VideoSite
{
public:
    virtual void freeMovie() = 0;
    virtual void vipMovie() = 0;
    virtual void ticketMovie() = 0;
};
//委托类
class FixBugVideoSite : public VideoSite
{
public:
    virtual void freeMovie()
    {
        cout << "free movie" << endl;
    }
    virtual void vipMovie()
    {
        cout << "vip movie" << endl;
    }
    virtual void ticketMovie()
    {
        cout << "ticket movie" << endl;
    }
};
//免费代理
class FreeProxy : public VideoSite
{
public:
    FreeProxy()
    {
        pVideo = new FixBugVideoSite();
    }
    ~FreeProxy()
    {
        delete pVideo;
    }
    virtual void freeMovie()
    {
        pVideo->freeMovie();
    }
    virtual void vipMovie()
    {
        cout << "no vip" << endl;
    }
    virtual void ticketMovie()
    {
        cout << "no ticket" << endl;
    }

private:
    VideoSite *pVideo;
};
//vip代理
class VipProxy : public VideoSite
{
public:
    VipProxy()
    {
        pVideo = new FixBugVideoSite();
    }
    ~VipProxy()
    {
        delete pVideo;
    }
    virtual void freeMovie()
    {
        pVideo->freeMovie();
    }
    virtual void vipMovie()
    {
        pVideo->vipMovie();
    }
    virtual void ticketMovie()
    {
        cout << "no ticket" << endl;
    }

private:
    VideoSite *pVideo;
};
void watchmovie(unique_ptr<VideoSite> &ptr)
{
    ptr->freeMovie();
    ptr->vipMovie();
    ptr->ticketMovie();
}
int main()
{
    //客户直接访问代理对象
    unique_ptr<VideoSite> p1(new FreeProxy());
    unique_ptr<VideoSite> p2(new VipProxy());
    watchmovie(p1);
    watchmovie(p2);

    return 0;
}