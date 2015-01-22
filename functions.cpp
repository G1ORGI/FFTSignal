void createMenuBar(HWND hwnd)
{
menuBar = CreateMenu();
hMenu=CreatePopupMenu();

AppendMenuW(menuBar, MF_STRING | MF_POPUP, (UINT_PTR)hMenu, L"Menu");
AppendMenuW(hMenu, MF_STRING, ID_OPEN, L"Open");
AppendMenuW(hMenu, MF_STRING, ID_EXIT, L"Exit");

SetMenu(hwnd, menuBar);
}

//returns size of double buffer
unsigned long convertCharsToDouble(char* data_buffer, int data_buffer_position, int data_buffer_size, double* dest_buffer)
{
//Logf(LOG_ON,L"convertCharsToDouble started...");
unsigned long k = 0;
unsigned short dest = 0;
	if(data_buffer && dest_buffer)
		for (unsigned long i = data_buffer_position; i < data_buffer_size; i+=2)
		{
		dest_buffer[k++] = mylib__2_byte_to_short(data_buffer + i);//(data_buffer[i]  + data_buffer[i+1] * 256);
		}
	//Logf(LOG_ON,L"convertCharsToDouble ended.");
return k;
}

//returns size of dest_buffer
int convertDoubleToChars(double* data_buffer, int data_buffer_position, int data_buffer_size, char* dest_buffer)
{
	//Logf(LOG_ON,L"convertDoubleToChars started...");
//TRANSFORM * t=(TRANSFORM *)transf;
int k = 0, i = 0;
	if(data_buffer && dest_buffer)
		for (i = data_buffer_position; i < data_buffer_position + data_buffer_size; i++)
		{
		mylib_short_to_2_byte(data_buffer[i], dest_buffer + k);
		/*dest_buffer[k] = (int)data_buffer[i] % 256;
		dest_buffer[k+1] = (int)data_buffer[i] / 256;*/
		k+=2;
		}	
		//Logf(LOG_ON,L"convertDoubleToChars ended.");
return k;
}

void paintDecarteSystem(HWND hwnd)
{
HDC hDC;
PAINTSTRUCT Ps;
HPEN		hPen;
RECT rect = {0};

GetClientRect(hwnd,&rect);

int width = rect.right - rect.left;
int height = rect.bottom - rect.top; 

GetClientRect(hwnd,&rect);
		
//GetClientRect(hwnd, &rect);
hPen = CreatePen(PS_SOLID , 2, RGB(255, 0, 0));
hDC = BeginPaint(hwnd, &Ps);
SelectObject(hDC, hPen);

MoveToEx(hDC, width/2, 0, NULL);
LineTo(hDC, width/2, height);

SetTextColor(hDC, RGB(255, 255, 255));
SetBkColor(hDC, RGB(0, 30, 0));
TextOutW(hDC,width/2 +5,0,L"Y",1);

MoveToEx(hDC, 0, height/2, NULL);
LineTo(hDC, width, height/2);

TextOutW(hDC,width - 12, height/2 + 5,L"X",1);

EndPaint(hwnd, &Ps);
ReleaseDC(hwnd,hDC);
DeleteObject(hPen);
}

//void circle(HDC dc, int x0, int y0, int radius)
//{
//	//int gd = DETECT, gm;
//	int i, r = radius, x, y, xc = x0, yc = y0;
//	float d;
//	/*clrscr();
//	initgraph(&gd, &gm, "c:\\tc\\");*/
//	/*printf("Enter Radius\n");
//	scanf("%d", &r);
//	printf("Enter Center of circle\n");*/
//
//	/*scanf("%d", &xc);
//	scanf("%d", &yc);*/
//	d = 1.25 - r;
//	x = 0;
//	y = r;
//	do
//	{
//		if (d<0)
//		{
//
//			x = x + 1;
//			d = d + 2 * x + 1;
//		}
//		else
//		{
//
//			x = x + 1;
//			y = y - 1;
//			d = d + 2 * x - 2 * y + 10;
//		}
//		SetPixel(dc, xc + x, yc + y, RGB(0, 255, 0));
//		SetPixel(dc, xc - y, yc - x, RGB(255, 255, 0));
//		SetPixel(dc, xc + y, yc - x, RGB(0, 255, 255));
//		SetPixel(dc, xc - y, yc + x, RGB(255, 0, 0));
//		SetPixel(dc, xc + y, yc + x, RGB(0, 0, 255));
//		SetPixel(dc, xc - x, yc - y, RGB(255, 0, 255));
//		SetPixel(dc, xc + x, yc - y, RGB(0, 0, 0));
//		SetPixel(dc, xc - x, yc + y, RGB(100, 0, 100));
//
//		//Sleep(20);
//
//	} while (x<y);
//
//}

void circle(HDC dc, int x0, int y0, int r)
{
	int x = 0, y = 0;
	for (y = 0; y < r; y++)
	{
		x = sqrt(abs((double)(r*r - y*y)));
		SetPixel(dc, x0 + x, y0 - y, RGB(0, 255, 0));
	}

	//test line
	/*for (size_t i = 0; i < 200; i++)
	{
		x = y = i;
		SetPixel(dc, x0 + x, y0 - y, RGB(0, 255, 0));
	}*/

	
}

void DrawFilledCircle(HDC dc, int x0, int y0, int radius)
{
	int x = radius;
	int y = 0;
	int xChange = 1 - (radius << 1);
	int yChange = 0;
	int radiusError = 0;

	while (x >= y)
	{
		for (int i = x0 - x; i <= x0 + x; i++)
		{
			SetPixel(dc, i, y0 + y, RGB(0, 255, 0));
			SetPixel(dc, i, y0 - y, RGB(0, 255, 0));
		}
		for (int i = x0 - y; i <= x0 + y; i++)
		{
			SetPixel(dc, i, y0 + x, RGB(0, 255, 0));
			SetPixel(dc, i, y0 - x, RGB(0, 255, 0));
		}

		y++;
		radiusError += yChange;
		yChange += 2;
		if (((radiusError << 1) + xChange) > 0)
		{
			x--;
			radiusError += xChange;
			xChange += 2;
		}
	}
}

void line(HWND hwnd, double *x, double *y, ULONG sz, int step)
{
HDC hDC;
PAINTSTRUCT Ps;
HPEN		hPen;
RECT rect = {0};

int i = 0, j = 0, k =0, m = 0, n =0;

GetClientRect(hwnd,&rect);

width = rect.right - rect.left;
height = rect.bottom - rect.top; 

centerX = width/2;
centerY = height/2;

GetClientRect(hwnd,&rect);
hDC = BeginPaint(hwnd, &Ps);


//paint decarte system---------------------------------------
hPen = CreatePen(PS_SOLID , 2, RGB(255, 0, 0));
SelectObject(hDC, hPen);
MoveToEx(hDC, width/2, 0, NULL);
//LineTo(hDC, width/2, height);

SetTextColor(hDC, RGB(255, 255, 255));
SetBkColor(hDC, RGB(0, 20, 0));
wchar_t pos[10] = {0};
//wsprintfW(pos,L"%d",centerX);
//TextOutW(hDC,centerX,centerY,pos,10);
//wsprintfW(pos,L"%d",centerX/2);

	//for (int i = 0; i < width; i+=50)
	//{
	//memset(pos,0,20);
	//wsprintfW(pos,L"|-%d",i);
	//TextOutW(hDC,i,centerY,pos,10);
	//}
step = 0;
wsprintfW(pos, L"|-%d Hz", maxfreq);
TextOutW(hDC,indexofmaxfreq,centerY,pos,10);


MoveToEx(hDC, 0, height/2, NULL);
//LineTo(hDC, width, height/2);

//TextOutW(hDC,width - 12, height/2 + 5,L"X",1);
//int radius = 100;
//	for (int y = -radius; y <= radius; y++)
//		for (int x = -radius; x <= radius; x++)
//			if (x*x + y*y <= radius*radius)
//				SetPixel(hDC, centerX + x, centerY + y, RGB(0, 255, 0));

//DrawFilledCircle(hDC, centerX, centerY, 100);
//circle(hDC, centerX, centerY, 200);
//------------------------------------------------------------	

	if(sz > 1)
	{
		if(x)
		{
		MoveToEx(hDC, sz/*width/2*/, 0, NULL);
		LineTo(hDC, sz, height);
		TextOutW(hDC,10,0,L"FFT Spectrum",12);
		TextOutW(hDC,sz+10,0,L"Real Time Spectrum",18);

		//paint lines
		hPen = CreatePen(PS_SOLID , 1, RGB(0, 200, 0));
		SelectObject(hDC, hPen);
 
			switch (t_type)
			{
				case FFT_T:
				{
					MoveToEx(hDC, centerX + (int)x[0], centerY - (int)y[0], NULL);
					TextOutW(hDC,centerX + (int)x[0] -10, centerY - (int)y[0],L"s",1);

					for (i = 1; i < sz; i += step)
					{
						LineTo(hDC, centerX + (x[i]/scale), centerY - (y[i] / scale));
					}

					TextOutW(hDC,centerX + (int)x[--i] + 10, centerY - (int)y[i],L"e",1);
				}
				break;

				case DRAW_FULL_FFT:
				case DEF_T:
				{
				//step = sz/width;
				//	if(step == 0)
				int	istep = 1;

				MoveToEx(hDC, 0, centerY, NULL);
				int ad = 0;
					for (i = 1; i < width; i += 1)
					{
						switch (paintmode)
						{
							
							case POINT_MODE:
							{
							SetPixel(hDC,i+ad,centerY - (int)(x[k]) / (int)scale,RGB(0, 255, 0));
							k += istep;
							}
							break;

							case LINE_MODE:
							{
							LineTo(hDC, i+ad, centerY - x[k] / scale);
							k += istep;
							}
							break;

							case AMPLITUDE_MODE:
							{
							MoveToEx(hDC, i+ad, centerY, NULL);
							LineTo(hDC, i+ad, centerY - x[k] / scale);
							k += istep;
							}
							break;

						default:
							break;
						}
					

					
				
					}
				k = 0;
				m = 0;
				n=0;
				}
				break;
			default:
				break;
			}
		}
	}
	else
	for (i = 0; i < width; i += 1)
	{
		SetPixel(hDC,j++,centerY,RGB(0, 255, 0));
	}
//MoveToEx(hDC, centerX + (-100), centerY - (-100), NULL);
//TextOutW(hDC,centerX + (-100 - 5), centerY - (-100),L"s",1);
//LineTo(hDC, centerX + (-100), centerY - (100));
//LineTo(hDC, centerX + (100), centerY - (100));
//LineTo(hDC, centerX + (100), centerY - (-100));
//LineTo(hDC, centerX + (-100), centerY - (-100));
//TextOutW(hDC,centerX + (-100+5), centerY - (-100),L"e",1);

EndPaint(hwnd, &Ps);
ReleaseDC(hwnd,hDC);
DeleteObject(hPen);
}

int powerof2(int x)
{
int  i = 0;
	while(x)
	{
	x>>=1;
	i++;
	}
return --i;
}

//HWND hwnd, double *x, double *y, ULONG sz, int step
DWORD WINAPI fftline(void *params)
{
line_status =1;
	long ** param = (long**)params, status = 0;
	HWND hwnd = (HWND)param[0];
	double *x = (double*)param[1];
	double*y = (double*)param[2];
	ULONG sz = (ULONG)param[3];
	int step = (int)param[4];

	HDC hDC;
	PAINTSTRUCT Ps;
	HPEN		hPen;
	RECT rect = {0};

	int i = 0, j = 0;

	GetClientRect(hwnd,&rect);

	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top; 

	int centerX = width/2;
	int centerY = height/2;

	GetClientRect(hwnd,&rect);
	hDC = BeginPaint(hwnd, &Ps);


	//paint decarte system---------------------------------------
	hPen = CreatePen(PS_SOLID , 2, RGB(255, 0, 0));
	SelectObject(hDC, hPen);
	MoveToEx(hDC, width/2, 0, NULL);
	LineTo(hDC, width/2, height);

	SetTextColor(hDC, RGB(255, 255, 255));
	SetBkColor(hDC, RGB(0, 20, 0));
	TextOutW(hDC,width/2 +5,0,L"Y",1);

	MoveToEx(hDC, 0, height/2, NULL);
	LineTo(hDC, width, height/2);

	TextOutW(hDC,width - 12, height/2 + 5,L"X",1);
	//------------------------------------------------------------	

		if(sz > 1)
		{
			if(x && y)
			{
			//paint lines
			hPen = CreatePen(PS_SOLID , 1, RGB(0, 200, 0));
			SelectObject(hDC, hPen);

			step = sz/width;

			MoveToEx(hDC, 0, centerY, NULL);

				for (i = 0; i < sz/2; i += step/2)
				{
				//SetPixel(hDC, i, centerY - x[i], RGB(0, 200, 0));
				LineTo(hDC, j, centerY - y[i]);
				MoveToEx(hDC, ++j, centerY, NULL);
				}
			}
		}

	EndPaint(hwnd, &Ps);
	ReleaseDC(hwnd,hDC);
	DeleteObject(hPen);

	if(params)
	GlobalFree(params);

	InvalidateRect(hwnd_main, 0, 1);
line_status = 0;
return 0;
}

//unsigned long convertCharsToDouble(char* data_buffer, int data_buffer_position, int data_buffer_size, double* dest_buffer)
//{
////Logf(LOG_ON,L"convertCharsToDouble started...");
//unsigned long k = 0;
//unsigned short dest = 0;
//	if(data_buffer && dest_buffer)
//		for (unsigned long i = data_buffer_position; i < data_buffer_size; i+=2)
//		{
//		dest_buffer[k++] = mylib__2_byte_to_short(data_buffer + i);//(data_buffer[i]  + data_buffer[i+1] * 256);
//		}
//	//Logf(LOG_ON,L"convertCharsToDouble ended.");
//return k;
//}

void runfftline(HWND hwnd, double *x, double *y, ULONG sz, int step)
{
	//Logf(LOG_ON,L"runTransformData started...");
//DWORD exit_code = 0;
//	if(thread_fftline)
//	{
//		if(GetExitCodeThread(thread_fftline, &exit_code))
//		{
//			if(!TerminateThread(thread_fftline, exit_code))
//			{
//			
//			get_error_str(0, GetLastError(),"win_error in runRippStream at TerminateThread. ",0,0,1,0,(ERR_CODES*)win_err_codes,MS_ERROR_COUNT);
//			return;
//			}
//			/*else
//			Log(log_wnd, L"thread_fftline terminated.\n");*/
//		}
//		else
//		{
//		//Log(log_wnd, L"error in runTransformData at GetExitCodeThread.\n");
//		get_error_str(0, GetLastError(),"win_error in runRippStream at GetExitCodeThread. ",0,0,1,0,(ERR_CODES*)win_err_codes,MS_ERROR_COUNT);
//		//return;
//		}
//	}
	if(line_status == 0)
	{
	fftline_params = (long**)GlobalAlloc(GPTR, sizeof(LONG) * 5);
		if(fftline_params)
		{
			fftline_params[0] = (LONG*)hwnd;
			fftline_params[1] = (LONG*)x;
			fftline_params[2] = (LONG*)y;
			fftline_params[3] = (LONG*)sz;
			fftline_params[4] = (LONG*)sz;

		thread_fftline = CreateThread(0,0,fftline,(void*)fftline_params,0,0);
			if(!thread_fftline)
			{
			//Log(log_wnd, L"Can't create thread of transform_data.\n");
			get_error_str(0, GetLastError(),"win_error in runRippStream at CreateThread. ",0,0,1,0,(ERR_CODES*)win_err_codes,MS_ERROR_COUNT);
			}
			//else
			//Log(log_wnd, L"thread_fftline begin.\n");
		}
		else
		{
			//Log(log_wnd, L"error in runTransformData at GlobalAlloc(fftline_params)");
		}
	}
//Logf(LOG_ON,L"runTransformData ended.");
}


int openFile(HWND hwnd, wchar_t* file_file_path)
{
//Logf(LOG_ON,L"openFile started...");
int status = 0;
wchar_t temp_buffer[MAX_PATH_FILE + 4] = {0};
wchar_t *mus_f_name = (wchar_t *)GlobalAlloc(GPTR, MAX_PATH_FILE);
	if(mus_f_name)
	{
	//Logf(LOG_ON,L"mylib_fileOpenDialog started...");
		if(mylib_fileOpenDialog(hwnd,mus_f_name))
		{//Logf(LOG_ON,L"mylib_fileOpenDialog ended.");
			//if(music_file_path)
			{

				if(*mus_f_name)
				{
				memcpy(file_file_path, mus_f_name, MAX_PATH_FILE);
					
				wsprintfW(temp_buffer, L"Opened: %s",  mus_f_name);
				//Log(log_wnd, temp_buffer);

					if(GlobalFree(mus_f_name))
					status = 1;
					//Log(log_wnd, L"error in openFile at GlobalFree(mus_f_name)");
						//if(mylib_writeInFile(cfg_file_name,music_file_path, wcslen(music_file_path)*2))
						//{
						///*ws//printfW(temp_buffer, L"Opened file path is saved.\n\r   \n");
						//Log(log_wnd, temp_buffer);*/
						//}
						//else
						//{
						//ws//printfW(temp_buffer, L"Opened file is not commited.\n\r   \n");
						//Log(log_wnd, temp_buffer);
						//}
				
				}
				else
				{
				//Log(log_wnd, L"openFile variable 'mus_f_name' is empty");
				}
			}
			//else
			//{
			//Log(log_wnd, L"File is not selected.");

			///*ws//printfW(temp_buffer, L"Current file is: %s\n\r   \n", music_file_path);
			//Log(log_wnd, temp_buffer);*/
			//}
		}
		else
		{
		//Logf(LOG_ON,L"mylib_fileOpenDialog ended.");
		}
	//Logf(LOG_ON,L"openFile ended...");
	}
return status;
}

//ULONG transform(double *doublebuffer , double *imaginaryBuffer)
//{
//STREAM_INFO info = {0};
//WAVE_HEADER w_header_struct = {0};
//BASS_CHANNELINFO music_info = {0};
//
//wchar_t outputfilename[MAX_PATH_FILE] = {0};
//wchar_t decodedfilename[MAX_PATH_FILE] = L"C:\\Users\\Gio\\Desktop\\decoded.wav";
//wchar_t monofilename[MAX_PATH_FILE] = L"C:\\Users\\Gio\\Desktop\\mono.wav";
//wchar_t resultfilename[MAX_PATH_FILE] = {0};//L"C:\\Users\\Gio\\Desktop\\result.wav";
//char *data = 0, *main_data = 0;
////double ***doublebuffer = 0, *imaginaryBuffer;
//int i =0, j = 0, remax = 0, remin = 0, immax = 0, immin = 0;
//
//unsigned long doublesize = 0;
//
//	//printf("choose file...\n");
//	if(mylib_fileOpenDialog(0,outputfilename))
//	{
//	//printf("file is choosen.\n");
//	//printf("start decoding file...\n");
//	decodeStream(&info, &w_header_struct, &music_info, outputfilename, decodedfilename);
//	//printf("file is decoded.\n");
//
//	//printf("start converting stereo to mono file...\n");
//	convertStereoWaveToMonoWave(decodedfilename,monofilename);
//	//printf("file converted to mono file.\n");
//
//	//printf("getting data from mono file...\n");
//	int size = getSampleDataFromWaveFile(monofilename, &data);
//		 if(data)
//		 {
//		 unsigned long poweroftwo = mylib_fromToPowerOfTwo(size);
//		 //poweroftwo /= 2;
//		 main_data = (char*)GlobalAlloc(GPTR, poweroftwo);
//
//		 //data = (char*)GlobalReAlloc(data, poweroftwo,GMEM_ZEROINIT);
//			if(main_data)
//			{
//			memcpy(main_data, data, size);
//			//memset(main_data, 0, poweroftwo);
//				if(data)
//				{
//					GlobalFree(data);
//					//Log(log_wnd, L"\nerror in transform_data at GlobalFree(data)\n");
//				}
//			}
//
//		int temp_size = sizeof(double)*((poweroftwo/2));
//		doublebuffer = (double*)GlobalAlloc(GPTR, temp_size);
//
//			if(doublebuffer)
//			{
//			//printf("converting data to double buffered data...\n");
//			doublesize = convertCharsToDouble(main_data, 0, poweroftwo, doublebuffer);
//			//printf("data is coverted to double buffer.\n");
//			
//
//			int powof2 = powerof2(doublesize);
//			
//			imaginaryBuffer = (double*)GlobalAlloc(GPTR, sizeof(double)*doublesize);
//				
//				if(imaginaryBuffer)
//				{
//				//printf("start forward FFT transform...\n");
//				FFT(1, powof2,doublebuffer,imaginaryBuffer);
//				//printf("Forward FFT transform ended.\n");
//
//				//remax = remin = doublebuffer[0];
//				//immax = immin = imaginaryBuffer[0];
//				//for (i = 0; i < doublesize; i++)
//				//{
//				//	//if(doublebuffer[i] < 5000 && doublebuffer[i] > -5000)
//				//	//doublebuffer[i] = 0;
//				//	////printf("%f   ", doublebuffer[i]);
//				//	if(remax < doublebuffer[i])
//				//	remax = doublebuffer[i];
//				//	if(remin > doublebuffer[i])
//				//	remin = doublebuffer[i];
//
//				//	if(immax < imaginaryBuffer[i])
//				//	immax = imaginaryBuffer[i];
//				//	if(immin > imaginaryBuffer[i])
//				//	immin = imaginaryBuffer[i];
//				//}
//				//printf("remax freq = %d.\n", remax);
//				//printf("remin freq = %d.\n", remin);
//
//				//printf("immax freq = %d.\n", immax);
//				//printf("immin freq = %d.\n", immin);
//
//				int start = 50, end = 0;
//					//printf("start parsing data...\n");
//					for (i = 0; i < doublesize; i++)
//					{
//						/*if(imaginaryBuffer[i] > start || imaginaryBuffer[i] < -end)
//						imaginaryBuffer[i]  = 0;
//
//						if(doublebuffer[i] > start || doublebuffer[i] < -end)
//						doublebuffer[i] = 0;*/
//
//						/*if(imaginaryBuffer[i] < dip && imaginaryBuffer[i] > -dip)
//						imaginaryBuffer[i]  *= 0;
//
//						if(doublebuffer[i] < dip && doublebuffer[i] > -dip)
//						doublebuffer[i] *= 0;*/
//
//						/*if(imaginaryBuffer[i] == immax)
//						imaginaryBuffer[i] = 0;
//
//						if(imaginaryBuffer[i] == immin)
//						imaginaryBuffer[i] = 0;*/
//					}	
//					//printf("parsing data ended.\n");
//
//				wsprintfW(resultfilename, L"C:\\Users\\Gio\\Desktop\\result-%d.wav", start);
//
//				//printf("start reverse FFT transform...\n");
//				//FFT(-1, powof2,doublebuffer,imaginaryBuffer);
//				//printf("Reverse FFT transform ended.\n");
//
//				//GlobalFree(imaginaryBuffer);
//				}
//				else
//					get_error_str(NULL, GetLastError(),"win err ",0,0,1,1,(ERR_CODES*)win_err_codes,MS_ERROR_COUNT);
//
//			//memset(main_data, 0, poweroftwo);
//
//			////printf("converting double data to char buffered data...\n");
//			//int resultsize = convertDoubleToChars(doublebuffer, 0, doublesize, main_data);
//			////printf("double buffer is converted to char buffered data.\n");
//
//			////printf("creating result wav file...\n");
//			//createFullWaveFile(resultfilename, 44100, 1, 16, &w_header_struct, main_data,size);
//			////printf("result wav file created.\n");
//			}
//			else
//			get_error_str(NULL, GetLastError(),"win err ",0,0,1,1,(ERR_CODES*)win_err_codes,MS_ERROR_COUNT);
//		GlobalFree(main_data);
//		}
//	}
//	//else
//	//printf("file isn't choosen.\n");
//return doublesize;
//}

DWORD WINAPI transform_data(void* params)
{
long ** param = (long**)params, status = 0;
	if((complex*)param[0] && (ULONG)param[1])
	{
		if(CFFT::Forward((complex*)param[0], (ULONG)param[1]))
		status = 1;
	}
return status;
}

void runTransformData(STREAM_INFO *info, WAVE_HEADER *w_header_struct, BASS_CHANNELINFO* music_info, wchar_t *output, wchar_t *input)
{
//Logf(LOG_ON,L"runTransformData started...");
DWORD exit_code = 0;
	if(thread_transform_data)
	{
		if(GetExitCodeThread(thread_transform_data, &exit_code))
		{
			if(!TerminateThread(thread_transform_data, exit_code))
			{
			
			get_error_str(0, GetLastError(),"win_error in runRippStream at TerminateThread. ",0,0,1,0,(ERR_CODES*)win_err_codes,MS_ERROR_COUNT);
			return;
			}
			/*else
			Log(log_wnd, L"thread_transform_data terminated.\n");*/
		}
		else
		{
		//Log(log_wnd, L"error in runTransformData at GetExitCodeThread.\n");
		get_error_str(0, GetLastError(),"win_error in runRippStream at GetExitCodeThread. ",0,0,1,0,(ERR_CODES*)win_err_codes,MS_ERROR_COUNT);
		//return;
		}
	}

transform_thread_params = (long**)GlobalAlloc(GPTR, sizeof(LONG) * 5);
	if(transform_thread_params)
	{
		transform_thread_params[0] = (LONG*)info;
		transform_thread_params[1] = (LONG*)w_header_struct;
		transform_thread_params[2] = (LONG*)music_info;
		transform_thread_params[3] = (LONG*)output;
		transform_thread_params[4] = (LONG*)input;

	thread_transform_data = CreateThread(0,0,getFFTsamplesFromFile,(void*)transform_thread_params,0,0);
		if(!thread_transform_data)
		{
		//Log(log_wnd, L"Can't create thread of transform_data.\n");
		get_error_str(0, GetLastError(),"win_error in runRippStream at CreateThread. ",0,0,1,0,(ERR_CODES*)win_err_codes,MS_ERROR_COUNT);
		}
		//else
		//Log(log_wnd, L"thread_transform_data begin.\n");
	}
	else
	{
		//Log(log_wnd, L"error in runTransformData at GlobalAlloc(transform_thread_params)");
	}
//Logf(LOG_ON,L"runTransformData ended.");
}


void initAudioDevice(HWND hwnd)
{
	MMRESULT						err;
	WAVEFORMATEX					waveFormat;
	//MIXERLINE						mixerLine;
	HANDLE							waveInThread;
	unsigned long					n, numSrc;

	/* Clear out both of our WAVEHDRs. At the very least, waveInPrepareHeader() expects the dwFlags field to
	 * be cleared
	 */
	ZeroMemory(&WaveHeader[0], sizeof(WAVEHDR) * 2);

	/* Initialize the WAVEFORMATEX for 16-bit, 44KHz, stereo. That's what I want to record */
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nChannels = 2;
	waveFormat.nSamplesPerSec = 11025;//44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nBlockAlign = waveFormat.nChannels * (waveFormat.wBitsPerSample/8);
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	/* Open the default WAVE In Device, specifying my callback. Note that if this device doesn't
	 * support 16-bit, 44KHz, stereo recording, then Windows will attempt to open another device
	 * that does. So don't make any assumptions about the name of the device that opens. After
	 * waveInOpen returns the handle, use waveInGetID to fetch its ID, and then waveInGetDevCaps
	 * to retrieve the actual name
	 */
	err = waveInOpen(&WaveInHandle, WAVE_MAPPER, &waveFormat, (DWORD)hwnd, 0, CALLBACK_WINDOW);
	if (err)
	{
		MessageBoxW(hwnd_main, L"Can't open WAVE In Device!", 0,0);
		//return(-2);
	}
	else
	{
		/* Allocate, prepare, and queue two buffers that the driver can use to record blocks of audio data.
		* (ie, We're using double-buffering. You can use more buffers if you'd like, and you should do that
		* if you suspect that you may lag the driver when you're writing a buffer to disk and are too slow
		* to requeue it with waveInAddBuffer. With more buffers, you can take your time requeueing
		* each).
		*
		* I'll allocate 2 buffers large enough to hold 2 seconds worth of waveform data at 44Khz. NOTE:
		* Just to make it easy, I'll use 1 call to VirtualAlloc to allocate both buffers, but you can
		* use 2 separate calls since the buffers do NOT need to be contiguous. You should do the latter if
		* using many, large buffers
		*/
	WaveHeader[1].dwBufferLength = WaveHeader[0].dwBufferLength = 1024 * 4;//* 4;//(waveFormat.nAvgBytesPerSec / 40) << 1;
		if (!(WaveHeader[0].lpData = (char *)VirtualAlloc(0, WaveHeader[0].dwBufferLength * 2, MEM_COMMIT, PAGE_READWRITE)))
		{
		printf("ERROR: Can't allocate memory for WAVE buffer!\n");
		MessageBoxW(hwnd_main, L"ERROR: Can't allocate memory for WAVE buffer!\n", 0,0);
		}
		else
		{
			/* Fill in WAVEHDR fields for buffer starting address. We've already filled in the size fields above */
			WaveHeader[1].lpData = WaveHeader[0].lpData + WaveHeader[0].dwBufferLength;

			/* Leave other WAVEHDR fields at 0 */

			/* Prepare the 2 WAVEHDR's */
			if ((err = waveInPrepareHeader(WaveInHandle, &WaveHeader[0], sizeof(WAVEHDR))))
			{
				printf("Error preparing WAVEHDR 1! -- %08X\n", err);
				MessageBoxW(hwnd_main, L"Error preparing WAVEHDR 1! -- %08X\n", 0,0);
			}
			else
			{
				if ((err = waveInPrepareHeader(WaveInHandle, &WaveHeader[1], sizeof(WAVEHDR))))
				{
					printf("Error preparing WAVEHDR 2! -- %08X\n", err);
					MessageBoxW(hwnd_main, L"Error preparing WAVEHDR 2! -- %08X\n", 0,0);
				}
				else
				{
					/* Queue first WAVEHDR (recording hasn't started yet) */
					if ((err = waveInAddBuffer(WaveInHandle, &WaveHeader[0], sizeof(WAVEHDR))))
					{
						printf("Error queueing WAVEHDR 1! -- %08X\n", err);
						MessageBoxW(hwnd_main, L"Error queueing WAVEHDR 1! -- %08X\n", 0,0);
					}
					else
					{
						/* Queue second WAVEHDR */
						if ((err = waveInAddBuffer(WaveInHandle, &WaveHeader[1], sizeof(WAVEHDR))))
						{
							printf("Error queueing WAVEHDR 2! -- %08X\n", err);
							MessageBoxW(hwnd_main, L"Error queueing WAVEHDR 2! -- %08X\n", 0,0);
							//DoneAll = 1;
							//goto abort;
						}
						else
						{
							/* Start recording. Our secondary thread will now be receiving
								* and storing audio data to disk
								*/
							//InRecord = TRUE;

							//createWaveFile(L"Recorded.wav", waveFormat.nSamplesPerSec, waveFormat.nChannels, waveFormat.wBitsPerSample, &w_header_struct);

							if ((err = waveInStart(WaveInHandle)))
							{
								printf("Error starting record! -- %08X\n", err);
								MessageBoxW(hwnd_main, L"Error starting record! -- %08X\n", 0,0);
							}
							//else
							//{
							//	/* Wait for user to stop recording */
							//	printf("Recording has started. Press ENTER key to stop recording...\n");
							//	getchar();
							//}

							/* Tell our recording thread not to queue any WAVEHDRs it gets back via MM_WIM_DONE */
//abort:						InRecord = FALSE;
				

							/* Wait for the recording thread to receive the MM_WIM_DONE for each
							* of our queued WAVEHDRs. It will count them off, and after processing
							* them all, 'DoneAll' will be equal to how many WAVEHDRs we used. We
							* can then unprepare the WAVEHDRs, close our WAVE device and our disk
							* file, and free our buffers
							*/
							//while (DoneAll < 2) Sleep(100);
						}
					}

					
					
				}

				
			}
		}
	}
}

void deInitAudioDEvice()
{
MMRESULT	err;
	/* Stop recording and tell the driver to unqueue/return all of our WAVEHDRs.
	* The driver will return any partially filled buffer that was currently
	* recording. Because we use waveInReset() instead of waveInStop(),
	* all of the other WAVEHDRs will also be returned via MM_WIM_DONE too
	*/
	waveInReset(WaveInHandle);

	/* Unprepare second WAVEHDR. NOTE: It should be ok to unprepare a WAVEHDR
	* that was never successfully prepared, as long as you initially cleared
	* out the dwFlags field (unless the audio driver is badly written)
	*/
	if ((err = waveInPrepareHeader(WaveInHandle, &WaveHeader[1], sizeof(WAVEHDR))))
	{
	printf("Error unpreparing WAVEHDR 2! -- %08X\n", err);
	MessageBoxW(hwnd_main, L"Error unpreparing WAVEHDR 2! -- %08X\n", 0,0);
	}
	/* Unprepare first WAVEHDR */
	if ((err = waveInPrepareHeader(WaveInHandle, &WaveHeader[0], sizeof(WAVEHDR))))
	{
		printf("Error unpreparing WAVEHDR 1! -- %08X\n", err);
		MessageBoxW(hwnd_main, L"Error unpreparing WAVEHDR 1! -- %08X\n", 0,0);
	}
}

void plusSignals(wchar_t* first_file_name, wchar_t* second_file_name, wchar_t* result_file_path, DWORD OPERATION)
{
DWORD size1 = 0, size2 = 0, size3 = 0, minsize=0, i = 0, z = 0;

char* first_data = 0, *second_data = 0, *result_data = 0;
double *first_double_data = 0, *second_double_data = 0, *result_double_data = 0;
size1 = getSampleDataFromWaveFile(first_file_name, &first_data);
size2 = getSampleDataFromWaveFile(second_file_name, &second_data);

	if(size1 && size2)
	{
		if(size1>=size2)
		{
		result_data = (char*)GlobalAlloc(GPTR, size1);
		size3 = size1;
		}
		else
		{
		result_data = (char*)GlobalAlloc(GPTR, size2);
		size3 = size2;
		}
			
		if(result_data)
		{

			if(size1 <= size2)
				minsize = size1;
			else
				minsize = size2;

		LONG sum = 0, minus = -1, result = 0;
		short firstshort = 0, secondshort = 0;
		char str[2024] = {0}, sign = 0; wchar_t logname[1024] = {0};
			/*for (i = 0; i < minsized3; i++)
			{
			sum = first_double_data[i] * 2;
				if(sum > 32767)
				sum = 32767;
				if(sum < 32768*(-1))
				sum = 32768*(-1);
			first_double_data[i] = sum;
			}
			sum = 0;*/
		wsprintfW(logname, L"Log_%d.txt", OPERATION);
		FILE *fp;
   
		fp = _wfopen(logname, L"wb");
		if (fp )
			for (i = 0; i < minsize; i+=2)
			{
			firstshort = mylib__2_byte_to_short(first_data + i);
			secondshort = mylib__2_byte_to_short(second_data + i);
				switch (OPERATION)
				{
					case 1: //plus
						//if(i>=20000)
						sign = '+';
						sum = firstshort + secondshort;
						
						//mylib_writeInFile(L"log.txt",str, strlen(str));
					break;

					case 2: //minus
					//sum = mylib__2_byte_to_short(first_data + i) - mylib__2_byte_to_short(second_data + i); //pow(minus,(int)i)*15000;
						sign = '-';
						sum = firstshort - secondshort;
					break;

					case 3: //multiple
					sign = '*';
					sum = firstshort * secondshort;
					//sum = mylib__2_byte_to_short(first_data + i) * mylib__2_byte_to_short(second_data + i);
					break;

					case 4: //devide
					sign = '/';
					sum = firstshort / secondshort;
					//sum = mylib__2_byte_to_short(first_data + i) / mylib__2_byte_to_short(second_data + i);
					break;

					default:
					break;
				}
					
				/*if(sum > 32767)
				{
				sum = 32767;
				sprintf(str,"%d\t%c\t%d\t=\t%d\t%d - %d\r\n", firstshort, sign, secondshort,sum, z++,i);
				fwrite(str, 1,strlen(str),fp);
				}
				if(sum < 32768*(-1))
				{
				sum = 32768*(-1);

				sprintf(str,"%d\t%c\t%d\t=\t%d\t%d - %d\r\n", firstshort, sign, secondshort,sum, z++,i);
				fwrite(str, 1,strlen(str),fp);
				}*/

			

			mylib_short_to_2_byte((short)sum, result_data+i);
			result = mylib__2_byte_to_short(result_data+i);
			}

			if(fp)
				if(fclose(fp))
				{
					MessageBoxA(0,"Error at closing file",0,0);
				//err_catch(MSWIN,&err_buffer,GetLastError);
				//status = 0;
				}

		WAVE_HEADER hdr = {0};
		createFullWaveFile(result_file_path, 44100, 2, 16, &hdr, result_data, size3);

		GlobalFree(first_data);
		GlobalFree(second_data);
		GlobalFree(result_data);

		GlobalFree(first_double_data);
		GlobalFree(second_double_data);
		GlobalFree(result_double_data);
		}
	}
}

//returns length of sample data(amplitudes) filled in double dest_buffer
//free dest_buffer after using the function
ULONG getSamplesFromWaveFile(wchar_t* filename, double** dest_buffer)
{
int i = 0, k = 0;
WAVE_HEADER hdr = {0};
char* data = 0;
double doubledatasize = 0, retrievedsize = 0;

	if(hdr.inflatHeaderFromWaveFile(filename))
		if(!strcmp(hdr.Format, "WAVE"))
		{
			if(hdr.SubChunk2Size > 0)
			{
			data = (char*)GlobalAlloc(GPTR, hdr.SubChunk2Size);
				if(data)
				{
				//doubledatasize = hdr.SubChunk2Size / hdr.nChannels;
					if(hdr.SubChunk2Size == getSampleDataFromWaveFile(filename, &data))
					{
						if(hdr.nChannels == 2)
						{
							switch (hdr.wBitsPerSample)
							{
								case 8:
									for (i = 0; i < hdr.SubChunk2Size; i+=2)
									{
									*dest_buffer[k++] = ((double)data[i] + (double)data[i+1]) / 2;
									}
								break;

								case 16:
									for (i = 0; i < hdr.SubChunk2Size; i+=4)
									{
									*dest_buffer[k++] = (mylib__2_byte_to_short((char*)data + i) + mylib__2_byte_to_short((char*)data + i + 2)) / 2;
									}
								break;

								default:
								break;
							}
						}
						else if(hdr.nChannels == 1)
						{
							switch (hdr.wBitsPerSample)
							{
								case 8:
									for (i = 0; i < hdr.SubChunk2Size; i++)
									{
									*dest_buffer[k++] = (double)data[i];
									}
								break;

								case 16:
									for (i = 0; i < hdr.SubChunk2Size; i+=2)
									{
									*dest_buffer[k++] = mylib__2_byte_to_short((char*)data + i);
									}
								break;

								default:
								break;
							}
						}
					}
				GlobalFree(data);
				}
			}
		}
return k;
}

ULONG transformWaveFile(wchar_t *filename, double* realOut, double* imageOut)
{
#define FFT	1024

WAVE_HEADER hdr = {0};
int i = 0, k = 0, z= 0, counter = 0, datalength = 0, numofsample = 0;
char *data = 0;
double *doubledata = 0, doubledatalength = 0, real[FFT] = {0}, image[FFT] = {0};
ULONG realandimgoutsize = 0;
	if(hdr.inflatHeaderFromWaveFile(filename))
	{
		if(!strcmp(hdr.Format, "WAVE"))
		{
			if(hdr.SubChunk2Size)
			{
			data = (char*)GlobalAlloc(GPTR, hdr.SubChunk2Size);
				if(data)
				{
				datalength = getSampleDataFromWaveFile(filename, &data);
					if(hdr.SubChunk2Size == datalength)
					{
					doubledatalength = getSamplesFromWaveFile(filename, &doubledata);
					realandimgoutsize = sizeof(double)*doubledatalength;
					realOut = (double*)GlobalAlloc(GPTR, realandimgoutsize);
					imageOut = (double*)GlobalAlloc(GPTR, realandimgoutsize);

						if(realOut&&imageOut)
						{
							if(doubledatalength)
							{
								for (counter = 0; counter < doubledatalength / FFT; counter++)
								{
								k =  + counter*FFT;
								fft_double(FFT,0,doubledata + k,NULL,real,image);
									for (z = 0; z < FFT/2; z++)
									{
									realOut[k+z] = real[z];
									imageOut[k+z] = image[z];

									realOut[(realandimgoutsize/2)+(k+z)] = real[FFT/2+z];
									imageOut[(realandimgoutsize/2)+(k+z)] = image[FFT/2+z];
									}
								}
							}
						}
					}
				GlobalFree(data);
				}
			}
		}
	}
return realandimgoutsize;
}
