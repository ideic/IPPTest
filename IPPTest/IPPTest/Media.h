#pragma once
#include <mfxsession.h>
#include <mfxvideo++.h>
#include <mfxplugin.h>
class Media
{
private :
	mfxSession _mSession;
	MFXVideoENCODE* _encoder;
	mfxVideoParam _videoParam;

	void SetVideoParam();
public:
	Media();
	~Media();
	void Init();
};

