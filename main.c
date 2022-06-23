#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <sys/stat.h>
#include "gumbo.h"
#include "gumbo-get-element-by-id.c/src/get-element-by-id.h"

#define MAX_LEN 65536

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int gethtml(int problemNum) {
    // 문제 url 완성
    char url[256];
    sprintf(url, "https://www.acmicpc.net/problem/%d", problemNum);

    // url의 페이지 다운로드
    char outf[64];
    printf("%s\n", url);

    CURL *curl = curl_easy_init();

    if (curl) {
        mkdir("ProblemPage", 0777);
        sprintf(outf, "ProblemPage/%d", problemNum);
        mkdir(outf, 0777);
        sprintf(outf, "ProblemPage/%d/problem.html", problemNum);
        FILE *fp = fopen(outf, "w");

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_USERAGENT,
                         "user-agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.182 Safari/537.36");

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }


    // 다운받은 페이지 파싱
    FILE *fp = fopen(outf, "r");
    char doc[MAX_LEN];
    fread(doc, 1, MAX_LEN, fp);
    fclose(fp);

    GumboNode *gumbo = gumbo_parse(doc)->root;
    GumboNode *example;

    char *examples[10][2]; //[예시 번호][0: 출력, 1: 입력]
    int exampleNum;
    char elemId[32];
    _Bool isInput = true, isEnd = false;
    unsigned int size;

    for (exampleNum = 0; 1; exampleNum++) {
        for (int i = 0; i <= 1; i++) {

            if (isInput) {
                sprintf(elemId, "sample-input-%d", exampleNum + 1);
            } else {
                sprintf(elemId, "sample-output-%d", exampleNum + 1);
            }

            example = gumbo_get_element_by_id(elemId, gumbo);
            if (example == NULL) {
                isEnd = true;
                break;
            }

            size = (example->v.element.end_pos.offset - example->v.element.start_pos.offset) -
                                example->v.element.original_tag.length - example->v.element.original_end_tag.length + 6;


            examples[exampleNum][isInput] = malloc(size + 32);
            strncpy(examples[exampleNum][isInput],
                    example->v.element.original_tag.data + example->v.element.original_tag.length,
                    size);

            sprintf(outf, "ProblemPage/%d/%d.%s", problemNum, exampleNum + 1, isInput? "in" : "out");

            fp = fopen(outf, "w");
            fputs(examples[exampleNum][isInput], fp);


            isInput = !isInput;
        }
        if (isEnd) break;
    }

    return 0;
}

int main() {
    return gethtml(4653);
}

