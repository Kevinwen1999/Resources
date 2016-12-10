void kmpPreprocess()
{
    memset(b, 0, sizeof b);
    int i = 0, j = -1; b[0] = -1;
    while (i < m)
    {
        while (j >= 0 && match[i] != match[j]) j = b[j];
        i++; j++;
        b[i] = j;
    }
}
bool kmpSearch()
{
    int i = 0, j = 0;
    while (i < n)
    {
        while (j >=0 && tmp[i] != match[j]) j = b[j];
        i++; j++;
        if (j==m)
        {
            return true;
            // j = b[j];
        }
    }
    return false;
}
