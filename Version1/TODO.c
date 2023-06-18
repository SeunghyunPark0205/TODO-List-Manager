
/* TODO list manager by Seunghyun Park  version: 1.0 */

#include <stdio.h>
#include <string.h>
#include <windows.h>

char buf[128];

typedef enum {
    _INSERT = 1,
    _DELETE = 2,
    _CHANGE = 3,
    _EXIT   = 4
} MODE;

int scan_file() {
    int n_line = 0;
    FILE* fin  = fopen("TODO.txt", "r");
    FILE* fout = fopen("TEMP.txt", "w");

    printf("\n************************************************************\n");
    printf("*************************   TODO   *************************\n\n");
    while( fgets(buf, sizeof(buf), fin) != NULL ) {
        printf("%s", buf);
        fprintf(fout, "%s", buf);
        n_line++;
    }
    printf("\n************************************************************\n");
    fclose(fin);
    fclose(fout);
    return n_line;
}

int get_mode() {
    int mode;

    printf("\n\nChoose option\n");
    printf("1.insert 2.delete 3.change 4.exit: ");
    scanf("%d", &mode);
    return mode;
}

void do_insert( int n_line ) {
    int i;
    int dest;
    int line = 1;
    char content[128];
    char temp[128];
    FILE* fin;
    FILE* fout;
    
    fin  = fopen("TEMP.txt", "r");
    fout = fopen("TODO.txt", "w");

    while( 1 ) {
        printf("\nEnter the index: ");
        scanf("%d", &dest);
        if( ( dest < 1 ) || ( dest > n_line + 1 ) ) {
            printf("Error! Check the value!\n");
            continue;
        }
        else break;
    }
    printf("\nEnter the content: ");
    fflush(stdin);
    scanf("%[^\n]s", content);
    printf("%s", content);

    while( 1 ) {
        fgets(buf, sizeof(buf), fin);
        if( line < dest )
            fprintf(fout, "%s", buf);
        else if( line == dest && dest != n_line + 1 ) {
            fprintf(fout, "%d. %s\n", dest, content);
        }
        else if( dest == n_line + 1 ) {
            fprintf(fout, "%d. %s\n", dest, content);
            break;
        }
        else if( line == n_line + 1 ) {
            fprintf(fout, "%d", line);
            for( i = 1; i < strlen(temp); i++ )
                fprintf(fout, "%c", temp[i]);
            break;
        }
        else if( line < n_line + 1 ) {
            fprintf(fout, "%d", line);
            for( i = 1; i < strlen(temp); i++ )
                fprintf(fout, "%c", temp[i]);
        }
        line++;
        strcpy(temp, buf);
    }
    fclose(fin);
    fclose(fout);
    return;
}

void do_delete( int n_line ) {
    int i;
    int dest;
    int line = 1;
    FILE* fin;
    FILE* fout;

    fin  = fopen("TEMP.txt", "r");
    fout = fopen("TODO.txt", "w");

    while( 1 ) {
        printf("\nEnter the index: ");
        scanf("%d", &dest);
        if( ( dest < 1 ) || ( dest > n_line ) ) {
            printf("Error! Check the value!\n");
            continue;
        }
        else break;
    }
    while( 1 ) {
        fgets(buf, sizeof(buf), fin);
        if( line < dest )
            fprintf(fout, "%s", buf);
        else if( line == dest ) ;
        else if( line == n_line + 1 )
            break;
        else {
            fprintf(fout, "%d", line-1);
            for( i = 1; i < strlen(buf); i++ )
                fprintf(fout, "%c", buf[i]);
        }
        line++;
    }
    fclose(fin);
    fclose(fout);
    return;
}

void do_change( int n_line ) {
    int i;
    int dest1;
    int dest2;
    int line = 1;
    char str1[128];
    char str2[128];
    FILE* fin;
    FILE* fout;

    fin  = fopen("TEMP.txt", "r");
    fout = fopen("TODO.txt", "w");

    while( 1 ) {
        printf("\nEnter the first index: ");
        scanf("%d", &dest1);
        if( ( dest1 < 1 ) || ( dest1 > n_line ) ) {
            printf("Error! Check the value!\n");
            continue;
        }
        else break;
    }
    while( 1 ) {
        printf("\nEnter the second index: ");
        scanf("%d", &dest2);
        if( ( dest2 < 1 ) || ( dest2 > n_line ) ) {
            printf("Error! Check the value!\n");
            continue;
        }
        else break;
    }
    while( fgets(buf, sizeof(buf), fin) != NULL ) {
        if( line == dest1 )
            strcpy(str1, buf);
        if( line == dest2 )
            strcpy(str2, buf);
        line++;
    }
    fseek(fin, 0, SEEK_SET);
    line = 1;
    while( fgets(buf, sizeof(buf), fin) != NULL ) {
        if( line == dest1 ) {
            fprintf(fout, "%d", line);
            for( i = 1; i < strlen(str2); i++ )
                fprintf(fout, "%c", str2[i]);
        }
        else if( line == dest2 ) {
            fprintf(fout, "%d", line);
            for( i = 1; i < strlen(str1); i++ )
                fprintf(fout, "%c", str1[i]);
        }
        else
            fprintf(fout, "%s", buf);
        line++;
    }
    fclose(fin);
    fclose(fout);
    return;
}

int main() {
    system("chcp 65001");
    int mode = 0;
    int n_line;

    while( mode != 4 ) {
        system("cls");
        n_line = scan_file();
        mode = get_mode();
        switch( mode ) {
            case _INSERT:
                do_insert( n_line );
                break;
            case _DELETE:
                do_delete( n_line );
                break;
            case _CHANGE:
                do_change( n_line );
                break;
            case _EXIT:
                break;
            default:
                break;
        }
        remove("TEMP.txt");
    }
    return 0;
}
