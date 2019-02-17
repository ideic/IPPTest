#include "pch.h"
#include "Media.h"


void Media::SetVideoParam()
{
	_videoParam.IOPattern = 
}

Media::Media()
{
}


Media::~Media()
{
}

void Media::Init()
{
	mfxVersion version{ 23, 1 };

	auto res = MFXInit(MFX_IMPL_AUTO | MFX_IMPL_VIA_D3D11, &version, &_mSession);

	res = MFXVideoUSER_Load(_mSession, &MFX_PLUGINID_HEVCD_SW, 1);

	// Query number of required surfaces for decoder
	mfxFrameAllocRequest request;
	res = MFXVideoENCODE_QueryIOSurf(_mSession, &_videoParam, &request);	//Allocate Surfaces	mfxU16 numSurfaces = request.NumFrameSuggested;

	mfxFrameAllocResponse mfxResponse;
	res = _allocator.Alloc(_allocator.pthis, &request, &mfxResponse);
	
	// Allocate surface headers (mfxFrameSurface1) for decoder
	mfxFrameSurface1** pmfxSurfaces = new mfxFrameSurface1 *[numSurfaces];
	for (int i = 0; i < numSurfaces; i++) {
		pmfxSurfaces[i] = new mfxFrameSurface1;
		memset(pmfxSurfaces[i], 0, sizeof(mfxFrameSurface1));
		memcpy(&(pmfxSurfaces[i]->Info), &(_videoParam.mfx.FrameInfo),
			sizeof(mfxFrameInfo));
		pmfxSurfaces[i]->Data.MemId = mfxResponse.mids[i];
	}

	res = MFXVideoENCODE_Init(_mSession, _videoParam);

}
