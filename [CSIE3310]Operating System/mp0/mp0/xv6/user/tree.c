#include "kernel/types.h"
#include "kernel/fs.h"
#include "kernel/stat.h"
#include "user/user.h"

int dir_num = -1, file_num = 0;

char *fmtname(char *path)
{
    static char buf[DIRSIZ + 1];
    char *p;

    // Find first character after last slash.
    for (p = path + strlen(path); p >= path && *p != '/'; p--)
        ;
    p++;

    // Return blank-padded name.
    if (strlen(p) >= DIRSIZ)
        return p;
    memmove(buf, p, strlen(p));
    memset(buf + strlen(p), 0, DIRSIZ - strlen(p));
    return buf;
}

void print(int level, int last)
{
    if (last & 1)
    {
        printf(" ");
    }
    else
    {
        printf("|");
    }
    for (int i = 1; i <= level; i++)
    {
        int bit = 1 & (last >> i);
        if (bit & 1)
        {
            printf("    ");
        }
        else
        {
            printf("   |");
        }
    }

    printf("\n");

    if (level == 0)
    {
        printf("+-- ");
    }
    else
    {
        if (last & 1)
        {
            printf(" ");
        }
        else
        {
            printf("|");
        }
        for (int i = 1; i < level; i++)
        {
            int bit = 1 & (last >> i);
            if (bit & 1)
            {
                printf("    ");
            }
            else
            {
                printf("   |");
            }
        }
        printf("   +-- ");
    }
}

void tree(char *path, int level, int last)
{
    char buf[512];
    char *p;
    int fd, id = 0, total = 0;
    struct dirent de;
    struct stat st;

    /* handling error cases */
    if ((fd = open(path, 0)) < 0)
    {
        printf("%s [error opening dir]\n", path);
        dir_num = 0;
        return;
    }

    if (fstat(fd, &st) < 0)
    {
        printf("%s [error opening dir]\n", path);
        dir_num = 0;
        close(fd);
        return;
    }

    /* differentiate file and directory */
    switch (st.type)
    {
    case T_FILE:
        file_num++;
        if (level == 0) // special cases for root
        {
            printf("%s [error opening dir]\n", path);
            dir_num = 0;
            file_num = 0;
            close(fd);
            return;
        }
        else
        {
            printf("%s\n", fmtname(path));
        }
        break;
    case T_DIR:
        dir_num++;
        if (level == 0) // root
        {
            printf("%s\n", path);
        }
        else
        {
            printf("%s\n", fmtname(path));
        }

        if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf)
        {
            printf("tree: path too long\n");
            break;
        }

        memset(buf, 0, sizeof(buf));
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';

        /* count how many files and directories are there*/
        while (read(fd, &de, sizeof(de)) == sizeof(de))
        {
            if (de.inum == 0)
            {
                continue;
            }
            if (stat(buf, &st) < 0)
            {
                printf("tree: cannot stat %s\n", buf);
                continue;
            }
            total++;
        }

        total -= 2;
        close(fd);
        fd = open(path, 0);

        while (read(fd, &de, sizeof(de)) == sizeof(de))
        {
            if (de.inum == 0)
            {
                continue;
            }
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            if (stat(buf, &st) < 0)
            {
                printf("tree: cannot stat %s\n", buf);
                continue;
            }
            char *name = fmtname(buf);
            if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0)
            {
                continue;
            }
            print(level, last);
            id++;
            if (id == total)
            {
                last += (1 << level);
                tree(buf, level + 1, last);
            }
            else
            {
                tree(buf, level + 1, last);
            }
        }
        break;
    }
    close(fd);
}

int main(int argc, char *argv[])
{
    int pfd[2];
    if (pipe(pfd) == -1)
    {
        fprintf(2, "Pipe failed.\n");
    }

    int p = fork();
    if (p == 0)
    {
        // child process
        close(pfd[0]);
        tree(argv[1], 0, 0);
        write(pfd[1], &dir_num, sizeof(dir_num));
        write(pfd[1], &file_num, sizeof(file_num));
        close(pfd[1]);
    }
    else
    {
        // parent process
        close(pfd[1]);
        read(pfd[0], &dir_num, sizeof(dir_num));
        read(pfd[0], &file_num, sizeof(file_num));
        close(pfd[0]);
        printf("\n");
        printf("%d directories, %d files\n", dir_num, file_num);
    }

    exit(0);
}
