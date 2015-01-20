#define MAX_URL_SIZE				2048*2
#define MAX_PATH_FILE				2048*2



typedef struct
{
wchar_t artist_w[256];
wchar_t title_w[256];
wchar_t genre_w[256];
wchar_t album_w[256];

char artist[256];
char title[256];
char genre[256];
char album[256];

long duration;

}
TAG_INFO;

//---------------------------------------------------------

typedef struct
{
char szTitle[256];
char szArtist[256];
char szAlbum[256];
char szTrack[10];
}TAGINFO;

//---------------------------------------------------------

typedef struct
{
unsigned int SamplesPerSec;
unsigned int Channels;
unsigned int BitsPerSample;
}
TECH_INFO;

//---------------------------------------------------------

typedef struct
{
wchar_t url_w[MAX_URL_SIZE];
char url[MAX_URL_SIZE];

TAG_INFO tag_info;

TECH_INFO tech_info;

unsigned int net_timeout;
DWORD hstream;
DWORD hstream_decoded;
void* data;

	int init(QWORD size)
	{
	int status = 0;
	data = (char*)HeapAlloc(GetProcessHeap(), 0, (QWORD)size);
		if(data)
		status = 1;
	return status;
	}
	void clean()
	{
		if(HeapValidate(GetProcessHeap(),0, data))
		HeapFree(GetProcessHeap(), 0, data);
	}
}
STREAM_INFO;

//---------------------------------------------------------

typedef struct 
{
STREAM_INFO stream_info;

unsigned int file_count;
int file_duration;
DWORD read_buff_size;
wchar_t output_file_path[MAX_PATH_FILE];
}
STREAM_RIPP_INFO;