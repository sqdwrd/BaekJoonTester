#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <sys/stat.h>
#include "gumbo.h"


size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int gethtml(int problemNum)
{
    // 문제 url 완성
    char url[256];
    sprintf(url, "https://www.acmicpc.net/problem/%d", problemNum);


    // url의 페이지 다운로드
    char outf[64];
    sprintf(outf, "ProblemPage/%d", problemNum);
    printf("%s\n", url);

    CURL *curl = curl_easy_init();

    if (curl)
    {   
        mkdir("ProblemPage", 0777);
        mkdir(outf, 0777);
    sprintf(outf, "ProblemPage/%d/problem.html", problemNum);
        FILE *fp = fopen(outf, "w");

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "user-agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.182 Safari/537.36");

        int a = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }


    // 다운받은 페이지 파싱
    

    return 0;
}