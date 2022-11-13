#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct disjointSet{
    int parent, size;
} DisjointSet;

DisjointSet ds[1 << 24];
bool set[1 << 24] = {};

inline int nextint() {
	int x = 0, c = getchar(), neg = false;
	while(('0' > c || c > '9') && c!='-' && c!=EOF) c = getchar();
	if(c == '-') neg = true, c = getchar();
	while('0' <= c && c <= '9') x = x*10 + (c^'0'), c = getchar();
	if(neg) x = -x;
	return x; // returns 0 if EOF
}

int c2i(char c) { 
    if ('0' <= c && c <= '9') return c - '0';
    else if ('a' <= c && c <= 'z') return c - 'a' + 10;
    else if ('A' <= c && c <= 'Z') return c - 'A' + 36;
    return -1;
}

int hash(const char* s) {  
    int ret = 0;
    int mask = (1<<24)-1;
    int len = strlen(s);
    for (int i = 0; i < len; i++)
        ret = mask & (ret << 4) | c2i(s[i]);
    return ret;
}

void makeset(int v){
    ds[v].parent = v, ds[v].size = 1;
}

int find_set(int v) {
    if (v == ds[v].parent) return v;
    return ds[v].parent = find_set(ds[v].parent);
}

void group(int a, int b) {
    a = find_set(a), b = find_set(b);
    if (a != b)
    {
        if (ds[a].size < ds[b].size)
        {
            ds[a].parent = b;
            ds[b].size += ds[a].size;
        }
        else
        {
            ds[b].parent = a;
            ds[a].size += ds[b].size;           
        }
    }
}

bool same_set(int a, int b) {
    return find_set(a) == find_set(b);
}

int main() {
    
    int n;
    n = nextint();
    for (int i = 0; i < n; i++)
    {
        char cmd[6], a[15], b[15];
        scanf("%s %s %s", cmd, a, b);
        int hash_a = hash(a), hash_b = hash(b);
        if (!strcmp(cmd, "group"))
        {
            if (!set[hash_a]) {makeset(hash_a); set[hash_a] = 1;}
            if (!set[hash_b]) {makeset(hash_b); set[hash_b] = 1;}
            group(hash_a, hash_b);
        }
        else
        {
            same_set(hash_a, hash_b) ? puts("Positive") : puts("Negative");
        }
    }
}