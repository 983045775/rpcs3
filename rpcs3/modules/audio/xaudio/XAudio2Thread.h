#pragma once

#ifdef _WIN32

#include "rpcs3/audio/thread.h"

#include "XAudio2.h"

class XAudio2Thread : public AudioThread
{
	IXAudio2* m_xaudio2_instance;
	IXAudio2MasteringVoice* m_master_voice;
	IXAudio2SourceVoice* m_source_voice;

public:
	XAudio2Thread();
	virtual ~XAudio2Thread() override;

	virtual void Play() override;
	virtual void Open(const void* src, int size) override;
	virtual void Close() override;
	virtual void Stop() override;
	virtual void AddData(const void* src, int size) override;
};

#endif
