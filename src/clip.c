#include <safe.h>
#include <stddef.h>
#include <stdio.h>
#if defined __unix__ || __APPLE__
#    include <magic.h>
#    include <string.h>
#endif
#ifdef _WIN32
#    include <string.h>
#    include <windows.h>

int cbcopy(const char* text)
{
    const size_t len = strlen(text) + 1;
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
    if (!hMem) {
        (void)safe_fprintf(stderr, "GlobalAlloc failed.\n");
        return 1;
    }

    safe_memcpy(GlobalLock(hMem), text, len);
    GlobalUnlock(hMem);

    if (!OpenClipboard(NULL)) {
        (void)safe_fprintf(stderr, "Failed to open clipboard.\n");
        GlobalFree(hMem);
        return 1;
    }

    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
    return 0;

    // Don't call GlobalFree. The clipboard owns the memory now.
}
#elif defined __linux__
int cbcopy(const char* text)
{
    if (!text) {
        return 1;
    }

    FILE* pipe = popen("xclip -selection clipboard", "w");
    if (!pipe) {
        perror("popen failed");
        return 1;
    }

    size_t len = strlen(text);
    size_t written = fwrite(text, 1, len, pipe);
    if (written < len) {
        (void)safe_fprintf(stderr, "Failed to write all data to xclip\n");
        pclose(pipe);
        return 1;
    }

    int status = pclose(pipe);
    if (status != 0) {
        (void)safe_fprintf(stderr, "xclip exited with status %d\n", status);
        return 1;
    }

    return 0;
}
#elif defined __APPLE__
int cbcopy(const char* text)
{
    if (!text) {
        return 1;
    }

    FILE* pipe = popen("pbcopy", "w");
    if (!pipe) {
        perror("popen failed");
        return 1;
    }

    size_t len = strlen(text);
    size_t written = fwrite(text, 1, len, pipe);
    if (written < len) {
        (void)safe_fprintf(stderr, "Failed to write all data to pbcopy\n");
        pclose(pipe);
        return 1;
    }

    int status = pclose(pipe);
    if (status != 0) {
        (void)safe_fprintf(stderr, "pbcopy exited with status %d\n", status);
        return 1;
    }

    return 0;
}
#endif
