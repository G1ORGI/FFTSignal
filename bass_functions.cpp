void BASS_init(HWND hwnd)
{
	if (!BASS_Init(-1,44100,0,hwnd,NULL)) 
	{
	get_error_str(NULL, BASS_ErrorGetCode(),"in init : BASS_Init ",0,0,1,1,(ERR_CODES*)bass_err_codes,BASS_ERROR_COUNT);
	}
}

DWORD WINAPI decodeStream(STREAM_INFO *info, WAVE_HEADER *w_header_struct, BASS_CHANNELINFO* music_info, wchar_t *output, wchar_t *input)
{
//Logf(LOG_ON,L"decodeStream started...");
ULONG status = 0;
	if(output && input)
	{
		if(*output && *input)
		{
		info->hstream_decoded = BASS_StreamCreateFile(0,output,0,0,BASS_UNICODE|BASS_STREAM_DECODE|BASS_STREAM_PRESCAN);
			if(info->hstream_decoded)
			{
			QWORD full_data_size = 0, retrieved_data_size = 0, data_length = 0;

				if(BASS_ChannelGetInfo(info->hstream_decoded, music_info))
				{
					if((full_data_size = BASS_ChannelGetLength(info->hstream_decoded, BASS_POS_BYTE)) != -1)
					{
						if(info->init(full_data_size))
						{
							if(createWaveFile(input, music_info->freq, music_info->chans, 16, w_header_struct))
							{
								//if(!DeleteFileW(input))
								//get_error_str(hwnd_main, GetLastError(),"win_error in removeDirectory at DeleteFileW ",0,0,1,0,(ERR_CODES*)win_err_codes,MS_ERROR_COUNT);
							DWORD active = 0;
								while ((active = BASS_ChannelIsActive(info->hstream_decoded)) == BASS_ACTIVE_PLAYING)
								{
								data_length = BASS_ChannelGetData(info->hstream_decoded, info->data, 50000);
									if(data_length != -1 && data_length)
									{
									retrieved_data_size += data_length;
										if(!writeDataInWaveFile(input, info->data, data_length, retrieved_data_size))
										{
											status = 0;
											break;
										}
										else
										status = 1;
									}
									//
								}
							}
						info->clean();
						//if(!DeleteFileW(input))
						//get_error_str(hwnd_main, GetLastError(),"win_error in removeDirectory at DeleteFileW ",0,0,1,0,(ERR_CODES*)win_err_codes,MS_ERROR_COUNT);
						}
						//
					}
					else
					get_error_str(NULL, BASS_ErrorGetCode(),"bass error in rippStream at BASS_ChannelGetLength ",0,0,1,1,(ERR_CODES*)bass_err_codes,BASS_ERROR_COUNT);
				}
				else
				{
				//Log(log_wnd, L"Can't get channels info.\n");
				get_error_str(NULL, BASS_ErrorGetCode(),"bass error in rippStream at BASS_ChannelGetLength ",0,0,1,1,(ERR_CODES*)bass_err_codes,BASS_ERROR_COUNT);
				}
			}
			else
			get_error_str(NULL, BASS_ErrorGetCode(),"bass error in rippStream at BASS_StreamCreateURL ",0,0,1,1,(ERR_CODES*)bass_err_codes,BASS_ERROR_COUNT);

		}
	}
//Logf(LOG_ON,L"decodeStream ended.");
return status;
}

DWORD WINAPI getFFTsamplesFromFile(void *params)//STREAM_INFO *info, WAVE_HEADER *w_header_struct, BASS_CHANNELINFO* music_info, wchar_t *output, wchar_t *input)
{
long ** param = (long**)params, status = 0, i = 0, j = 0, k =0;
STREAM_INFO *info = (STREAM_INFO *)param[0]; WAVE_HEADER *w_header_struct = (WAVE_HEADER *)param[1];
BASS_CHANNELINFO* music_info = (BASS_CHANNELINFO*)param[2]; wchar_t *output = (wchar_t*)param[3], *input = (wchar_t*)param[4];
//Logf(LOG_ON,L"decodeStream started...");

	if(output && input)
	{
		if(*output && *input)
		{
		info->hstream_decoded = BASS_StreamCreateFile(0,output,0,0,BASS_UNICODE|BASS_STREAM_PRESCAN);
			if(info->hstream_decoded)
			{
			QWORD full_data_size = 0, retrieved_data_size = 0, data_length = 0;

				if(BASS_ChannelGetInfo(info->hstream_decoded, music_info))
				{
					if((full_data_size = BASS_ChannelGetLength(info->hstream_decoded, BASS_POS_BYTE)) != -1)
					{
						if(info->init(full_data_size))
						{
							//stop recording from device sound
							fileisplaying = 1;

							if(pglobalBuffer)
							GlobalFree(pglobalBuffer);
							pglobalBuffer = GlobalAlloc(GPTR, full_data_size);
							if(pglobalBuffer)
							if(BASS_ChannelPlay(info->hstream_decoded,0))
							if(createWaveFile(input, music_info->freq, music_info->chans, 16, w_header_struct))
							{
								//if(!DeleteFileW(input))
								//get_error_str(hwnd_main, GetLastError(),"win_error in removeDirectory at DeleteFileW ",0,0,1,0,(ERR_CODES*)win_err_codes,MS_ERROR_COUNT);
							DWORD active = 0;
								while ((active = BASS_ChannelIsActive(info->hstream_decoded)) == BASS_ACTIVE_PLAYING)
								{
								
								data_length = BASS_ChannelGetData(info->hstream_decoded, info->data, full_data_size); //8192
									if(data_length != -1 && data_length)
									{
									int powof2 = mylib_fromToPowerOfTwo(sizeof(double)*(data_length/4));
									//pglobalBuffer = GlobalAlloc(GPTR, powof2);
							
										/*if(doublebuffer)
										GlobalFree(doublebuffer);
										if(imaginaryBuffer)
										GlobalFree(imaginaryBuffer);*/

									signal = new complex[powof2];
									memset(signal, 0, sizeof(complex) * powof2);

										k = 0;
										for (i = 0; i < data_length - 4; i+=4)
										{
										
										((double*)pglobalBuffer)[k] = (mylib__2_byte_to_short((char*)info->data + i) + mylib__2_byte_to_short((char*)info->data + i + 2)) / 2;
										//signal[k] = complex(((double*)pglobalBuffer)[k], 0);
										k++;
										}
									
									k--;
									#define FFT_LEN 1024// * 2

									int stp = k/FFT_LEN;
										if(stp == 0) stp = 1;
										double damxmare[FFT_LEN] = {0};

									doublebuffer = (double*)GlobalAlloc(GPTR, sizeof(double) * FFT_LEN);
									imaginaryBuffer = (double*)GlobalAlloc(GPTR, sizeof(double) * FFT_LEN);

										//for ( i = 0; i < FFT_LEN; i++)
										//{ 
										//	for (j = 0; j < stp; j++)
										//	{
										//	//damxmare[i] += ((double*)pglobalBuffer)[j + i*stp];
										//	signal[i] += complex(((double*)pglobalBuffer)[j + i*stp], 0);
										//	}
										//signal[i].m_re /= stp;
										////damxmare[i] /= stp;
										//}

										for (int i = 0; i < FFT_LEN; i++)
										{
										signal[i] = complex(((double*)pglobalBuffer)[i], 0);
										//damxmare[i] = ((double*)pglobalBuffer)[i*stp];
										}
									

										if(doublebuffer && imaginaryBuffer)
										//fft_double(FFT_LEN,0,(double*)pglobalBuffer,NULL,doublebuffer,imaginaryBuffer);
										//fft_double(FFT_LEN,0,damxmare,NULL,doublebuffer,imaginaryBuffer);
										CFFT::Forward(signal, FFT_LEN);
										//FFT(1,FFT_LEN,(double*)doublebuffer, imaginaryBuffer);

										

										float re,im;
										for(int i=0;i<FFT_LEN/2;i+=1)
										{
											re = signal[i].m_re;
											im = signal[i].m_im;
											//re = doublebuffer[i];
											//im = imaginaryBuffer[i];
											//get frequency intensity and scale to 0..256 range
											((double*)pglobalBuffer)[i]=(GetFrequencyIntensity(re,im))/20;
											
										}

										if(doublebuffer)
										GlobalFree(doublebuffer);
										if(imaginaryBuffer)
										GlobalFree(imaginaryBuffer);
									
									buffer_size = FFT_LEN/2;//k;
									//line(hwnd_main, (double*)info->data, imaginaryBuffer, 512, step);
									//runfftline(hwnd_main, (double*)info->data, imaginaryBuffer, 512, step);
									InvalidateRect(hwnd_main, 0, 1);
									retrieved_data_size += data_length;
										/*if(!writeDataInWaveFile(input, info->data, data_length, retrieved_data_size))
										{
											status = 0;
											break;
										}
										else*/
									status = 1;
									delete signal;

										
										
									Sleep(33);
									}
								buffer_size = 0;
								//InvalidateRect(hwnd_main, 0, 1);
								}
							GlobalFree(pglobalBuffer);
							pglobalBuffer = NULL;
							}
						fileisplaying = 0;
						info->clean();
						//if(!DeleteFileW(input))
						//get_error_str(hwnd_main, GetLastError(),"win_error in removeDirectory at DeleteFileW ",0,0,1,0,(ERR_CODES*)win_err_codes,MS_ERROR_COUNT);
						}
						//
					}
					else
					get_error_str(NULL, BASS_ErrorGetCode(),"bass error in rippStream at BASS_ChannelGetLength ",0,0,1,1,(ERR_CODES*)bass_err_codes,BASS_ERROR_COUNT);
				}
				else
				{
				//Log(log_wnd, L"Can't get channels info.\n");
				get_error_str(NULL, BASS_ErrorGetCode(),"bass error in rippStream at BASS_ChannelGetLength ",0,0,1,1,(ERR_CODES*)bass_err_codes,BASS_ERROR_COUNT);
				}
			}
			else
			get_error_str(NULL, BASS_ErrorGetCode(),"bass error in rippStream at BASS_StreamCreateURL ",0,0,1,1,(ERR_CODES*)bass_err_codes,BASS_ERROR_COUNT);

		}
	}

	if(params)
	GlobalFree(params);
//Logf(LOG_ON,L"decodeStream ended.");
return status;
}

unsigned __int64 getAudioFileData(STREAM_INFO *info)
{
BASS_CHANNELINFO music_info = {0};
unsigned __int64 full_data_size = 0, data_length = 0;

info->hstream_decoded = BASS_StreamCreateFile(0,info->url_w,0,0,BASS_UNICODE|BASS_STREAM_PRESCAN|BASS_STREAM_DECODE);
	if(info->hstream_decoded)
	{
		if(BASS_ChannelGetInfo(info->hstream_decoded, &music_info))
		{
		info->tech_info.BitsPerSample = 16; //default
			if(music_info.flags & BASS_SAMPLE_8BITS)
			info->tech_info.BitsPerSample = 8;
			else if (music_info.flags & BASS_SAMPLE_FLOAT)
			{
			info->tech_info.BitsPerSample = 32;
			}
			else
			{
			info->tech_info.BitsPerSample = 16;
			}

		info->tech_info.SamplesPerSec = music_info.freq;
		info->tech_info.Channels = music_info.chans;

			if((full_data_size = BASS_ChannelGetLength(info->hstream_decoded, BASS_POS_BYTE)) != -1)
			{
				if(info->init(full_data_size))
				{
				data_length = BASS_ChannelGetData(info->hstream_decoded, info->data, full_data_size);

				//WAVE_HEADER wh = {0};
				//createFullWaveFile(L"C:\\Users\\Gio\\Desktop\\spec\\recorded.wav", info->tech_info.SamplesPerSec, info->tech_info.Channels, info->tech_info.BitsPerSample, &wh, info->data, data_length);
				}
			}
		}
	}
return data_length;
}