class CharArgs
{
private:
char **l_argn;
int arg_num;

int wstrlen(_TCHAR * wstr)
{
    int l_idx = 0;
    while (((char*)wstr)[l_idx] != 0) l_idx += 2;
    return l_idx;
}

// Allocate char string and copy TCHAR->char->string
char *wstrdup(_TCHAR *wSrc)
{
    int l_idx = 0;
    int l_len = wstrlen(wSrc);
    char *l_nstr = (char *)malloc(l_len);
    if (l_nstr) {
        do {
            l_nstr[l_idx] = (char)wSrc[l_idx];
            l_idx++;
        } while ((char)wSrc[l_idx] != 0);
    }
    l_nstr[l_idx] = 0;
    return l_nstr;
}

char_args & operator=(const char_args&); // does not allow assignment of class
char_args(const char_args&); // does not allow copy construction

public:
char_args(int argcc, _TCHAR* argv[]) : arg_num(argcc)
{
    l_argn = (char **)malloc(argcc *sizeof(char*));
    for (int idx = 0; idx < argcc; idx++) l_argn[idx] = wstrdup(argv[idx]);
}

~char_args()
{
    for(int idx = 0; idx < arg_num; idx++) if (l_argn[idx]) free(l_argn[idx]);
    free(l_argn);
}

const char * operator[](const int &i)
{
    if (i < arg_num) return l_argn[i]; else return 0;
}

const int argc() { return arg_num; }
};