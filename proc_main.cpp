 

LRESULT CALLBACK proc_main(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{


    switch(msg)
    {
		case WM_CREATE:
		{
		BASS_init(hwnd);
		createMenuBar(hwnd);
		x[0] = -100; y[0] = -100;
		x[1] = -100; y[1] = 100;
		x[2] = 100; y[2] = 100;
		x[3] = 100; y[3] = -100;
		x[4] = -100; y[4] = -100;

		initAudioDevice(hwnd);
		}
		break;

		case WM_COMMAND:
		{
			switch(LOWORD(wParam))
			{
			case 123:
				{
			   
				 
				   // Open waveform audio for input

				   //waveform.wFormatTag      = WAVE_FORMAT_PCM ;
				   //waveform.nChannels       = 1 ;
				   //waveform.nSamplesPerSec  = 11025 ;
				   //waveform.nAvgBytesPerSec = 11025 ;
				   //waveform.nBlockAlign     = 1 ;
				   //waveform.wBitsPerSample  = 8 ;
				   //waveform.cbSize          = 0 ;

				   //if (waveInOpen (&hWaveIn, WAVE_MAPPER, &waveform,
							//	   (DWORD) hwnd, 0, CALLBACK_WINDOW))
				   //{
					  // free (pBuffer1) ;
					  // free (pBuffer2) ;
				   //}
				   //// Set up headers and prepare them

				   //pWaveHdr1->lpData          =reinterpret_cast <CHAR*>( pBuffer1 ) ;
				   //pWaveHdr1->dwBufferLength  = INP_BUFFER_SIZE ;
				   //pWaveHdr1->dwBytesRecorded = 0 ;
				   //pWaveHdr1->dwUser          = 0 ;
				   //pWaveHdr1->dwFlags         = 0 ;
				   //pWaveHdr1->dwLoops         = 1 ;
				   //pWaveHdr1->lpNext          = NULL ;
				   //pWaveHdr1->reserved        = 0 ;

				   //waveInPrepareHeader (hWaveIn, pWaveHdr1, sizeof (WAVEHDR)) ;

				   //pWaveHdr2->lpData          = reinterpret_cast <CHAR*>(pBuffer2 ) ;
				   //pWaveHdr2->dwBufferLength  = INP_BUFFER_SIZE ;
				   //pWaveHdr2->dwBytesRecorded = 0 ;
				   //pWaveHdr2->dwUser          = 0 ;
				   //pWaveHdr2->dwFlags         = 0 ;
				   //pWaveHdr2->dwLoops         = 1 ;
				   //pWaveHdr2->lpNext          = NULL ;
				   //pWaveHdr2->reserved        = 0 ;

				   //waveInPrepareHeader (hWaveIn, pWaveHdr2, sizeof (WAVEHDR)) ;

				}
				break;
				case ID_OPEN:
				{
					if((BASS_ChannelIsActive(info.hstream_decoded) == BASS_ACTIVE_PLAYING))
					BASS_ChannelStop(info.hstream_decoded);
				//buffer_size = transform(doublebuffer, imaginaryBuffer);
					

						//printf("choose file...\n");
						if(mylib_fileOpenDialog(0,outputfilename))
						{
						t_type = DRAW_BY_CENTER;
						
							switch (t_type)
							{
								case FFT_T:
								{
								if(doublebuffer)
								GlobalFree(doublebuffer);
								if(imaginaryBuffer)
								GlobalFree(imaginaryBuffer);
								wchar_t resultfilename[MAX_PATH_FILE] = {0};//L"C:\\Users\\Gio\\Desktop\\result.wav";
								char *data = 0, *main_data = 0;
								//double ***doublebuffer = 0, *imaginaryBuffer;
								int i =0, j = 0, remax = 0, remin = 0, immax = 0, immin = 0;

								unsigned long doublesize = 0;
									//printf("file is choosen.\n");
								//printf("start decoding file...\n");
								decodeStream(&info, &w_header_struct, &music_info, outputfilename, decodedfilename);
						
						
								//printf("file is decoded.\n");

								//printf("start converting stereo to mono file...\n");
								convertStereoWaveToMonoWave(decodedfilename,monofilename);
								//printf("file converted to mono file.\n");

								printf("getting data from mono file...\n");
								int size = getSampleDataFromWaveFile(monofilename, &data);
									 if(data)
									 {
									 unsigned long poweroftwo = mylib_fromToPowerOfTwo(size);
									 //poweroftwo /= 2;
									 main_data = (char*)GlobalAlloc(GPTR, poweroftwo);

									 //data = (char*)GlobalReAlloc(data, poweroftwo,GMEM_ZEROINIT);
										if(main_data)
										{
										memcpy(main_data, data, size);
										//memset(main_data, 0, poweroftwo);
											if(data)
											{
												GlobalFree(data);
												//Log(log_wnd, L"\nerror in transform_data at GlobalFree(data)\n");
											}
										}

					
									int temp_size = sizeof(double)*((poweroftwo/2));
									doublebuffer = (double*)GlobalAlloc(GPTR, temp_size);

										if(doublebuffer)
										{
										//printf("converting data to double buffered data...\n");
										doublesize = convertCharsToDouble(main_data, 0, poweroftwo, doublebuffer);

										//printf("data is coverted to double buffer.\n");
										
										signal = new complex[doublesize];
										//CFourier FFT_SIZE;
									
										for ( i = 0; i < doublesize; i++)
										{
										signal[i] = complex(doublebuffer[i], 0);
										}

										int powof2 = powerof2(doublesize);


										imaginaryBuffer = (double*)GlobalAlloc(GPTR, sizeof(double)*doublesize);
				
											if(imaginaryBuffer)
											{
											//printf("start forward FFT_SIZE transform...\n");
											//runTransformData(signal, doublesize);

											CFFT::Forward(signal, doublesize);

											
											//---------------------------------------------------------------------------
											/*magnitude = (double*)GlobalAlloc(GPTR, sizeof(double) * powof2);

												for( i = 0; i < powof2/2; i++ )
												magnitude[i] = sqrt( signal[i].m_re * signal[i].m_re + signal[i].m_im * signal[i].m_im );

											NlogN = powof2;*/
											//---------------------------------------------------------------------------


											//FFT_SIZE(1, powof2,doublebuffer,imaginaryBuffer);
											//printf("Forward FFT_SIZE transform ended.\n");


												//printf("start parsing data...\n");
												for (i = 0; i < doublesize; i++)
												{
													doublebuffer[i] = signal[i].m_re / 10000; 
													imaginaryBuffer[i] =signal[i].m_im / 10000;

													/*if(imaginaryBuffer[i] > start || imaginaryBuffer[i] < -end)
													imaginaryBuffer[i]  = 0;

													if(doublebuffer[i] > start || doublebuffer[i] < -end)
													doublebuffer[i] = 0;*/

													/*if(imaginaryBuffer[i] < dip && imaginaryBuffer[i] > -dip)
													imaginaryBuffer[i]  *= 0;

													if(doublebuffer[i] < dip && doublebuffer[i] > -dip)
													doublebuffer[i] *= 0;*/

													/*if(imaginaryBuffer[i] == immax)
													imaginaryBuffer[i] = 0;

													if(imaginaryBuffer[i] == immin)
													imaginaryBuffer[i] = 0;*/
												}	
												//printf("parsing data ended.\n");
											//delete signal;

											buffer_size = doublesize;
											//wsprintfW(resultfilename, L"C:\\Users\\Gio\\Desktop\\result-%d.wav", 0);
											}
											else
											get_error_str(NULL, GetLastError(),"win error at globalalloc(imaginaryBuffer) ",0,0,1,1,(ERR_CODES*)win_err_codes,MS_ERROR_COUNT);
										}
										else
										get_error_str(NULL, GetLastError(),"win error at globalalloc(doublebuffer) ",0,0,1,1,(ERR_CODES*)win_err_codes,MS_ERROR_COUNT);
										GlobalFree(main_data);
									}
								}
								break;

								case DEF_T:
								{
								runTransformData(&info, &w_header_struct, &music_info, outputfilename, decodedfilename);
								}
								break;

								case DRAW_FULL_FFT:
								{
								fileisplaying = 1;

								int i = 0, k = 0;
								double *real = 0, *img = 0, numofcomplex = 0, *rreal = 0, *rimg = 0;
								numofcomplex = transformWaveFile(outputfilename,&real,&img);
								pglobalBuffer = GlobalAlloc(GPTR,sizeof(double)*numofcomplex);

								rreal = (double*)GlobalAlloc(GPTR,sizeof(double)*numofcomplex);
								rimg = (double*)GlobalAlloc(GPTR,sizeof(double)*numofcomplex);
									if(pglobalBuffer && real && img && numofcomplex)
									{
									float re, im;
										for (i = 0; i < numofcomplex/2 ; i += 1)
										{
										re = real[i];
										im = img[i];

										((double*)pglobalBuffer)[i] = (GetFrequencyIntensity(re, im))/500;
										}

									

									int imax = ((double*)pglobalBuffer)[0], maxi = 0;

										for (i = 0; i < numofcomplex/2; i++)
										{
											if (imax < ((double*)pglobalBuffer)[i])
											{
											imax = ((double*)pglobalBuffer)[i];
											maxi = i;
											}
										}

									float freq = maxi * 44100 / FFT_SIZE;
									maxfreq = freq;

									indexofmaxfreq = maxi;

										//null some samples and restore data
										/*for (i = 0; i < maxi + 150; i++)
										{
										real[i] = 0;
										img[i] = 0;
										((double*)pglobalBuffer)[i] = 0;
										}

										for (i = maxi + 150 + 150; i < maxi + 150 +150 + 400; i++)
										{
										real[i] = 0;
										img[i] = 0;
										((double*)pglobalBuffer)[i] = 0;
										}

										if(rreal&&rimg)
										{
										fft_double(FFT_SIZE,1,real,img,rreal,rimg);

										void *waveBuffer = GlobalAlloc(GPTR, sizeof(short) * FFT_SIZE);
											if(waveBuffer)
											{
												for (int i = 0; i < FFT_SIZE; i++)
												{
												((short*)waveBuffer)[i] = rreal[i];
												}
											WAVE_HEADER h = { 0 };
											createFullWaveFile(L"C:\\Users\\Gio\\Desktop\\Music\\Signals\\restored.wav", 44100, 1, 16, &h, waveBuffer, FFT_SIZE * 2);

											GlobalFree(waveBuffer);
											}
										}*/

									GlobalFree(real);
									GlobalFree(img);

									buffer_size = numofcomplex/2;//k;
									InvalidateRect(hwnd_main, 0, 1);
									}
								}
								break;

								case TEST:
								{
								double *real1 = 0, *img1 = 0, numofcomplex1 = 0, *real2 = 0, *img2 = 0, numofcomplex2 = 0, *real3 = 0, *img3 = 0, *dresult = 0, *imgresult = 0;
								int i  = 0;
								double* firstfilebuffer = 0, *onefilebuff =0, *secondfilebuff = 0, l1 = 0, l2 = 0;
								//plusSignals(L"C:\\Users\\Gio\\Desktop\\Music\\Signals\\440.wav", L"C:\\Users\\Gio\\Desktop\\Music\\Signals\\700.wav", L"C:\\Users\\Gio\\Desktop\\Music\\Signals\\3.wav", 1,0);
								//ULONG sizeoffirstdata = plusSignals(L"C:\\Users\\Gio\\Desktop\\Music\\Signals\\440.wav", L"C:\\Users\\Gio\\Desktop\\Music\\Signals\\700.wav", firstfilebuffer, 1,1);
								l1 = getSamplesFromWaveFile(L"C:\\Users\\Gio\\Desktop\\Music\\Signals\\smus.wav", &onefilebuff);
								l2 = getSamplesFromWaveFile(L"C:\\Users\\Gio\\Desktop\\Music\\Signals\\sxm.wav", &secondfilebuff);
								firstfilebuffer = (double*)GlobalAlloc(GPTR, sizeof(double)* l2);
								real1 = (double*)GlobalAlloc(GPTR, sizeof(double)* FFT_SIZE);
								img1 = (double*)GlobalAlloc(GPTR, sizeof(double)* FFT_SIZE);
									if(l1&&l2)
									{
										for (i = 0; i < FFT_SIZE; i++)
										{
										firstfilebuffer[i] = onefilebuff[i] + secondfilebuff[i];
										}

										if(firstfilebuffer)
										{
										fft_double(FFT_SIZE,0,firstfilebuffer,NULL,real1,img1);
										GlobalFree(firstfilebuffer);
										}
									}

								//numofcomplex1 = transformWaveFile(L"C:\\Users\\Gio\\Desktop\\Music\\Signals\\3.wav",&real1,&img1);
								numofcomplex2 = transformWaveFile(L"C:\\Users\\Gio\\Desktop\\Music\\Signals\\smus.wav",&real2,&img2);

									if(real1 && img1 /*&& numofcomplex1*/ && real2 && img2 && numofcomplex2)
									{
									real3 = (double*)GlobalAlloc(GPTR, sizeof(double)* FFT_SIZE);
									img3 = (double*)GlobalAlloc(GPTR, sizeof(double)* FFT_SIZE);
									dresult = (double*)GlobalAlloc(GPTR, sizeof(double)* FFT_SIZE);
									imgresult = (double*)GlobalAlloc(GPTR, sizeof(double)* FFT_SIZE);
										if(real3 && img3 && dresult && imgresult)
										{
											for (i = 0; i < numofcomplex2; i++)
											{
											real3[i] = real1[i] - real2[i];
											img3[i] = img1[i] - img2[i];
											}

										fft_double(FFT_SIZE,1,real3,img3,dresult,imgresult);

										GlobalFree(real1);
										GlobalFree(img1);
										GlobalFree(real2);
										GlobalFree(img2);
										GlobalFree(real3);
										GlobalFree(img3);
										GlobalFree(imgresult);

										void *waveBuffer = GlobalAlloc(GPTR, sizeof(short) * FFT_SIZE);
											if(waveBuffer)
											{
												for (int i = 0; i < FFT_SIZE; i++)
												{
												((short*)waveBuffer)[i] = dresult[i];
												}
											WAVE_HEADER h = { 0 };
											createFullWaveFile(L"C:\\Users\\Gio\\Desktop\\Music\\Signals\\result.wav", 44100, 1, 16, &h, waveBuffer, FFT_SIZE * 2);

											GlobalFree(waveBuffer);
											}

										GlobalFree(dresult);
										}
									}
								}
								break;

								case DRAW_BY_CENTER:
								{
								fileisplaying = 1;
								scale = 9000;

								int i = 0, k = 0;
								double *real = 0, *img = 0, numofcomplex = 0;
								numofcomplex = transformWaveFile(outputfilename,&real,&img);
								pReal = GlobalAlloc(GPTR,sizeof(double)*numofcomplex);
								pImg = GlobalAlloc(GPTR,sizeof(double)*numofcomplex);

									if(pReal && pImg && real && img && numofcomplex)
									{
										for (i = 0; i < numofcomplex/2 ; i += 1)
										{
										((double*)pReal)[i] = real[i];
										((double*)pImg)[i] = img[i];
										}

									/*int imax = ((double*)pglobalBuffer)[0], maxi = 0;

										for (i = 0; i < numofcomplex/2; i++)
										{
											if (imax < ((double*)pglobalBuffer)[i])
											{
											imax = ((double*)pglobalBuffer)[i];
											maxi = i;
											}
										}

									float freq = maxi * 44100 / FFT_SIZE;
									maxfreq = freq;

									indexofmaxfreq = maxi;*/

									GlobalFree(real);
									GlobalFree(img);

									buffer_size = numofcomplex/2;//k;
									InvalidateRect(hwnd_main, 0, 1);
									}
								}
								break;

								case DRAW_BY_CENTER_DYNAMICALY:
								{
								fileisplaying = 1;
								scale = 9000;

								int i = 0, k = 0;
								double *real = 0, *img = 0, numofcomplex = 0, *sampledata = 0;

								sampledata = (double*)GlobalAlloc(GPTR,sizeof(double)*44100);

								int retval = makeFreqSample(sampledata, 600, 44100,1,32767);
									if(retval)
									{
									numofcomplex = transformMemData(sampledata, 44100, &real,&img);

									pReal = GlobalAlloc(GPTR,sizeof(double)*numofcomplex);
									pImg = GlobalAlloc(GPTR,sizeof(double)*numofcomplex);

										if(pReal && pImg && real && img && numofcomplex)
										{
											for (i = 0; i < numofcomplex/2 ; i += 1)
											{
											((double*)pReal)[i] = real[i];
											((double*)pImg)[i] = img[i];
											}

										/*int imax = ((double*)pglobalBuffer)[0], maxi = 0;

											for (i = 0; i < numofcomplex/2; i++)
											{
												if (imax < ((double*)pglobalBuffer)[i])
												{
												imax = ((double*)pglobalBuffer)[i];
												maxi = i;
												}
											}

										float freq = maxi * 44100 / FFT_SIZE;
										maxfreq = freq;

										indexofmaxfreq = maxi;*/

										GlobalFree(real);
										GlobalFree(img);

										buffer_size = numofcomplex/2;//k;
										InvalidateRect(hwnd_main, 0, 1);
										}
									}
								}
								break;

							default:
								break;
							}
						
						}
					InvalidateRect(hwnd,0,1);
				}
				break;
			}
		}
		break;

		case WM_PAINT:
		{
		//paintDecarteSystem(hwnd);

			switch (t_type)
			{
				case FFT_T:
				{
				line(hwnd, doublebuffer, imaginaryBuffer, buffer_size, step);
				}
				break;

				case DEF_T:
				{
				line(hwnd, (double*)pglobalBuffer, 0, buffer_size, step);
				}
				break;

				case DRAW_FULL_FFT:
				{
				line(hwnd, (double*)pglobalBuffer, 0, buffer_size, step);
				}
				break;

				case DRAW_BY_CENTER_DYNAMICALY:
				case DRAW_BY_CENTER:
				{
				line(hwnd, (double*)pReal, (double*)pImg, buffer_size, step);
				}
				break;
			}

		
		}
		break;

		case WM_MOUSEWHEEL:
		{
		int fwKeys = GET_KEYSTATE_WPARAM(wParam);
		int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
		int i = 0, j = 1;

			
			
			/*for (i = 0; i < buffer_size; i++)
			{
				

			}*/

			if(zDelta < 0 )
			{
			//step /= 10;
			/*doublebuffer[i] /=2;
			imaginaryBuffer[i] /=2;*/
				//if(scale < 32767)
				scale *= 2;

				if(paintmode == LINE_MODE)
					paintmode = AMPLITUDE_MODE;
				else
				paintmode--;
			}
			else if(zDelta > 0)
			{
			//step *= 10;
			/*doublebuffer[i] *=2;
			imaginaryBuffer[i] *=2;*/
				//if(scale > -32768)
				scale /= 2;

				if(paintmode == AMPLITUDE_MODE)
					paintmode = LINE_MODE;
				else
				paintmode++;
			}
			
			if(scale <= 0)
			scale =1;
			

		//MessageBoxW(0,L"WHEEL",L"WHEEL",0);
		InvalidateRect(hwnd,0,1);
		}          
		break;  

		case WM_SIZE:
		{
		InvalidateRect(hwnd,0,1);
		}
		break;

		case WM_MOVE:
		{
		InvalidateRect(hwnd,0,1);
		}
		break;

		/* A buffer has been filled by the driver */
		case MM_WIM_DATA:
		{
		int i = 0, k = 0;
			/* msg.lParam contains a pointer to the WAVEHDR structure for the filled buffer.
				* NOTE: The WAVEHDR's dwBytesRecorded field specifies how many bytes of
				* audio data are in the buffer. It may not be full, as would be the case
				* if recording was stopped *while* this buffer was being filled. (ie, A
				* final, partial block of audio data may be returned)
				*/
			if(fileisplaying == 0)
			{
				if (((WAVEHDR *)lParam)->dwBytesRecorded)
				{
					if(pglobalBuffer)
					GlobalFree(pglobalBuffer);

					#define FFT_LEN	1024
				int sz = 0;
				pglobalBuffer = GlobalAlloc(GPTR, sizeof(double) * ((WAVEHDR *)lParam)->dwBytesRecorded / 2);
					if(pglobalBuffer)
					{
					k = 0;
						for (i = 0; i < ((WAVEHDR *)lParam)->dwBytesRecorded - 2; i+=4)
						{				
						((double*)pglobalBuffer)[k++] = (mylib__2_byte_to_short(((WAVEHDR *)lParam)->lpData + i) + mylib__2_byte_to_short(((WAVEHDR *)lParam)->lpData + i + 2)) / 2;
						}

						/*if(doublebuffer)
						GlobalFree(doublebuffer);
						if(imaginaryBuffer)
						GlobalFree(imaginaryBuffer);*/

					doublebuffer = (double*)GlobalAlloc(GPTR, sizeof(double) * k);
					imaginaryBuffer = (double*)GlobalAlloc(GPTR, sizeof(double) * k);

						if(doublebuffer && imaginaryBuffer)
						{
						fft_double(k,0,(double*)pglobalBuffer,NULL,doublebuffer,imaginaryBuffer);
				
						float re,im;
							for(i=0;i<k/2;i+=1)
							{
								re = doublebuffer[i];
								im = imaginaryBuffer[i];
								//get frequency intensity and scale to 0..256 range
								((double*)pglobalBuffer)[i]=(GetFrequencyIntensity(re,im))/20;
											
							}

							int imax = ((double*)pglobalBuffer)[0], maxi = 0;
							for (size_t i = 0; i < k / 2; i++)
							{
								if (imax < ((double*)pglobalBuffer)[i])
								{
									imax = ((double*)pglobalBuffer)[i];
									maxi = i;
								}

							}

							float freq = maxi * 11025 / k;
							maxfreq = freq;

							indexofmaxfreq = maxi;

							if(doublebuffer)
							GlobalFree(doublebuffer);
							if(imaginaryBuffer)
							GlobalFree(imaginaryBuffer);
						buffer_size = k/2;
						}
					InvalidateRect(hwnd,0,1);
					}


				

					//sz = convertCharsToDouble(((WAVEHDR *)lParam)->lpData, 0, ((WAVEHDR *)lParam)->dwBytesRecorded, (double*)pglobalBuffer);
				
				

				/* Let's write out this next block of data to our already open file. NOTE: The main
				* thread opened this file prior to starting recording, and stored its handle in
				* 'WaveFileHandle'
				*/
				//fullrecordeddatalenth += ((WAVEHDR *)lParam)->dwBytesRecorded;
				//writeDataInWaveFile(L"Recorded.wav", ((WAVEHDR *)lParam)->lpData,  ((WAVEHDR *)lParam)->dwBytesRecorded, fullrecordeddatalenth);
					//if (!WriteFile(WaveFileHandle, ((WAVEHDR *)lParam)->lpData, ((WAVEHDR *)lParam)->dwBytesRecorded, &msg.time, 0) ||

						/* Check for an error */
						//msg.time != ((WAVEHDR *)msg.lParam)->dwBytesRecorded)
					//{
						/* Normally you'd do something here like signal the main thread to have it stop recording and
							* display an error message about there being a problem writing the audio data to disk
							*/
					//}
				}

				/* Are we still recording? */
				//if (InRecord)
				//{
					/* Yes. Now we need to requeue this buffer so the driver can use it for another block of audio
						* data. NOTE: We shouldn't need to waveInPrepareHeader() a WAVEHDR that has already been prepared once
						*/
				waveInAddBuffer(WaveInHandle, (WAVEHDR *)lParam, sizeof(WAVEHDR));
				//}

			}

			/* We aren't recording, so another WAVEHDR has been returned to us after recording has stopped.
				* When we get all of them back, DoneAll will be equal to how many WAVEHDRs we queued
				*/
			//else
			//{
			//	++DoneAll;
			//}

			///* Keep waiting for more messages */
//            continue;
		}

		/* Our main thread is opening the WAVE device */
		case MM_WIM_OPEN:
		{
			/* Re-initialize 'DoneAll' */
			//DoneAll = 0;

			/* Keep waiting for more messages */
            //continue;
		}

		/* Our main thread is closing the WAVE device */
		case MM_WIM_CLOSE:
		{
			//fullrecordeddatalenth = 0;
			/* Terminate this thread (by return'ing) */
			break;
		}

        case WM_DESTROY:
		BASS_Free();
			if(info.data)
			GlobalFree(info.data);
			/*if(doublebuffer)
			GlobalFree(doublebuffer);*/
			if(magnitude)
			GlobalFree(magnitude);

			if(pReal)
			GlobalFree(pReal);

			if(pImg)
			GlobalFree(pImg);

		deInitAudioDEvice();
        PostQuitMessage(0);
        break;

        default:
            return DefWindowProcW(hwnd, msg, wParam, lParam);
    }
    return 0;
}