double x[1024] = {0};
double y[1024] = {0};

HMENU menuBar=0, hMenu=0, hPopup = 0;

#define ID_EXIT						301
#define ID_OPEN						302

wchar_t file_file_path[2048] = {0};
wchar_t outputfilename[MAX_PATH_FILE] = {0};

double *doublebuffer ,  *imaginaryBuffer, *magnitude = 0;

ULONG buffer_size =0;

int step = 100; double scale = 200;

HANDLE thread_transform_data = 0, thread_fftline = 0;

long **restore_thread_params = 0,
	 **transform_thread_params = 0,
	 **fftline_params = 0;

complex *signal = 0;
ULONG NlogN = 0;

STREAM_INFO info = {0};
HWND hwnd_main = 0;

int line_status = 0, fullrecordeddatalenth = 0;

wchar_t decodedfilename[MAX_PATH_FILE] = L"C:\\Users\\Gio\\Desktop\\decoded.wav";
wchar_t monofilename[MAX_PATH_FILE] = L"C:\\Users\\Gio\\Desktop\\mono.wav";

WAVE_HEADER w_header_struct = {0};
BASS_CHANNELINFO music_info = {0};
void *pglobalBuffer = 0;
void *pReal = 0;
void *pImg = 0;

#define FFT_T			1
#define DEF_T			2
#define DRAW_FULL_FFT	3
#define TEST			4
#define DRAW_BY_CENTER	5

int t_type = DEF_T, fileisplaying = 0;

#define LINE_MODE	1
#define POINT_MODE	2
#define AMPLITUDE_MODE	3

int paintmode = POINT_MODE;

static HWAVEIN      hWaveIn ;
static HWAVEOUT     hWaveOut ;
static PWAVEHDR     pWaveHdr1;
static WAVEFORMATEX waveform ;


/* Handle to the WAVE In Device */
HWAVEIN				WaveInHandle;

/* Handle to the disk file where we permanently store the recorded audio data */
HANDLE				WaveFileHandle = INVALID_HANDLE_VALUE;

/* We use two WAVEHDR's for recording (ie, double-buffering) in this example */
WAVEHDR				WaveHeader[2];

int indexofmaxfreq = 0, maxfreq = 0;

//**main window size
int width = 0;
int height = 0;

int centerX = 0;
int centerY = 0;