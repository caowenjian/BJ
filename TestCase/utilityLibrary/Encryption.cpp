#include "Encryption.h"
NAMESPACE_BEGIN_T(utilityLibrary)

static char base64_chars[] =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";





int	base64_encode(const char *data, int size, char **str)
{
    char *s, *p;
    int i;
    int c;
    const unsigned char *q;

    p = s = new char[size * 4 / 3 + 4];
    if (p == 0)
        return -1;
    q = (const unsigned char *) data;
    i = 0;
    for (i = 0; i < size;) {
        c = q[i++];
        c *= 256;
        if (i < size)
            c += q[i];
        i++;
        c *= 256;
        if (i < size)
            c += q[i];
        i++;
        p[0] = base64_chars[(c & 0x00fc0000) >> 18];
        p[1] = base64_chars[(c & 0x0003f000) >> 12];
        p[2] = base64_chars[(c & 0x00000fc0) >> 6];
        p[3] = base64_chars[(c & 0x0000003f) >> 0];
        if (i > size)
            p[3] = '=';
        if (i > size + 1)
            p[2] = '=';
        p += 4;
    }
    *p = 0;
    *str = s;
    return strlen(s);
}

VTT_VOID Base64Encode(const std::string& input,std::string& output)
{
	char* buff = 0;
	int length = base64_encode(input.c_str(),input.size(),&buff);
	if (length != -1&& buff !=0)
	{
		output = std::string(buff,length);
		delete []buff;
	}
	else
	{
		output.clear();
	}
}

NAMESPACE_END_T(utilityLibrary)