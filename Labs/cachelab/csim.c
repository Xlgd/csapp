#include "cachelab.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <getopt.h>
#include <string.h>

int h, v, s, E, b, S;
int hit, miss, eviction;
char tracefile[1000];

// cache block consists of valid bit, tag and timestamp
typedef struct {
    int valid_bits; // Mark this block as valid or not
    int tag; // identifier to choose block
    int stamp; // LRU strategy counter
}cache_line, *Set, **Cache;

Cache cache = NULL; // the cache

// print the usage
void print_info() {
    printf("Usage: ./csim [-hv] -s <s> -E <E> -b <b> -t <tracefile>\n"
           "\t-h: Optional help flag that prints usage info.\n"
           "\t-v: Optional verbose flag that displays trace info.\n"
           "\t-s <s>: Number of set index bits (S = 2 ^ s is the number of sets.\n"
           "\t-E <num> Associativity (number of lines per set).\n"
           "\t-b <num> Number of block bits (B = 2 ^ b is the block size).\n"
           "\t-t <tracefile> Name of the valgrind trace to replay.\n");
}

// print the content of trace file
void print_trace() {
    FILE* tf = fopen(tracefile, "r");
    char content[100];
    if (tf == NULL) {
        printf("open tracefile error!\n");
        exit(-1);
    }
    while (fgets(content, sizeof(content), tf) != NULL) {
        fputs(content, stdout);
    }
    fclose(tf);
}

// Initialize cache
void cache_init() {
    cache = (Cache)malloc(sizeof(Set) * S);
    for (int i = 0; i < S; ++i) {
        cache[i] = (Set)malloc(sizeof(cache_line) * E);
        for (int j = 0; j < E; ++j) {
            cache[i][j].valid_bits = 0;
            cache[i][j].tag = -1;
            cache[i][j].stamp = -1;
        }
    }
}

// parse the trace file
void parse(unsigned int address) {
    // get the set index and tag from the address
    int index = (address >> b) & ((-1U) >> (64 - s));
    int tag = address >> (b + s);

    int max_stamp = INT_MIN;
    int max_stamp_index = -1;

    // hit
    for (int i = 0; i < E; ++i) {
        if (cache[index][i].tag == tag) {
            cache[index][i].stamp = 0;
            ++hit;
            return;
        }
    }

    // miss and the set is not full
    for (int i = 0; i < E; ++i) {
        if (cache[index][i].valid_bits == 0) {
            cache[index][i].valid_bits = 1;
            cache[index][i].tag = tag;
            cache[index][i].stamp = 0;
            ++miss;
            return;
        }
    }

    // miss and the set is full, need replacement
    ++eviction;
    ++miss;
    // find the least recently used block to evict
    for (int i = 0; i < E; ++i) {
        if (cache[index][i].stamp > max_stamp) {
            max_stamp = cache[index][i].stamp;
            max_stamp_index = i;
        }
    }
    cache[index][max_stamp_index].tag = tag;
    cache[index][max_stamp_index].stamp = 0;
    return;
}

// update all the timestamps of valid blocks
void update_stamp() {
    for (int i = 0; i < S; ++i) {
        for (int j = 0; j < E; ++j) {
            if (cache[i][j].valid_bits == 1) {
                ++cache[i][j].stamp;
            }
        }
    }
}

void parse_trace_file() {
    FILE* fp = fopen(tracefile, "r");
    if (fp == NULL) {
        printf("open error");
        exit(-1);
    }

    char operator; // save 'I', 'L', 'S' or 'M'
    unsigned int address;
    int size;
    while (fscanf(fp, " %c %xu,%d\n", &operator, &address, &size) > 0) {
        switch(operator) {
            case 'L':
                parse(address);
                break;
            case 'M':
                parse(address); // after the modification, you have to do a load
            case 'S':
                parse(address);    
        }
        update_stamp();
    }

    fclose(fp);
    // free the malloc memory
    for (int i = 0; i < S; ++i) {
        free(cache[i]);
    }

    free(cache);
}


int main(int argc, char* argv[])
{
    // initialization
    int opt;
    h = 0;
    v = 0;
    hit = miss = eviction = 0;

    while ((opt = getopt(argc, argv, "hvs:E:b:t:")) != -1) {
        switch(opt) {
            case 'h':
                h = 1;
                break;
            case 'v':
                v = 1;
                break;
            case 's':
                s = atoi(optarg);
                break;
            case 'E':
                E = atoi(optarg);
                break;
            case 'b':
                b = atoi(optarg);
                break;
            case 't':
                strcpy(tracefile, optarg);
                break;
            default:
                print_info();
                break;
        }
    }    

    if (h == 1) {
        print_info();
        return 0;
    }
    if (v == 1) {
        print_trace();
        return 0;
    }
    // handling illegal situations
    if (s <= 0 || E <= 0 || b <= 0 || tracefile == NULL) {
        printf("invalid parameters!\n");
        exit(-1);
    }
    S = 1 << s; // S = 2 ^ s
    
    cache_init();
    parse_trace_file();

    printSummary(hit, miss, eviction);
    return 0;
}