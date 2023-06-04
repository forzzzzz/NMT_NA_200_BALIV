#include <stdio.h>  // ���������� �������
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <sqlite3.h>
#include <math.h>


void split_string(char *str, int len) {  // �������, ��� ��������� ����� �� ������ ����� �� ����� �� ������ "|", ��� ��������� ������ ���������.
    int i = 0;
    while (i < strlen(str)) {
    int j = i + len;
        if (j >= strlen(str)) {
            j = strlen(str);
        } else {
            while (j > i && str[j] != ' ') {
                j--;
            }
            if (j == i) {
                j = i + len;
            }
        }
        int width = len+6;
        char temp = str[j];
        str[j] = '\0';
        printf("|      %-*s|\n", width, &str[i]);

        str[j] = temp;
        i = j + 1;
    }
}

int main()
{
    SetConsoleCP(1251); // ������������ ������� 1251 ��� ����������� ����������� ��������� ����
    SetConsoleOutputCP(1251);


    sqlite3 *db; // ���������� ���� �����
    int rc = sqlite3_open("database.db", &db);


    char* sql_create = "CREATE TABLE IF NOT EXISTS Custom_Tests (id INTEGER PRIMARY KEY, name TEXT);"; // ��������� ������� ��� ������ ������� �����
    rc = sqlite3_exec(db, sql_create, NULL, NULL, NULL);

    sql_create = "CREATE TABLE IF NOT EXISTS results (id INTEGER PRIMARY KEY, name_test TEXT, name_user TEXT, max_id TEXT, score TEXT, score_200 TEXT, score_12 TEXT);"; // ��������� ������� ��� ���������� ����������
    rc = sqlite3_exec(db, sql_create, NULL, NULL, NULL);







    sql_create = "CREATE TABLE IF NOT EXISTS Ukr (id INTEGER PRIMARY KEY, question_test TEXT, answer1_test TEXT, answer2_test TEXT, answer3_test TEXT, answer4_test TEXT, answer5_test TEXT, answer1 TEXT, answer2 TEXT, answer3 TEXT, answer4 TEXT, answer5 TEXT, answer_true TEXT);"; // ��������� ������� ��� ��� ����������
    rc = sqlite3_exec(db, sql_create, NULL, NULL, NULL);
    sql_create = "CREATE TABLE IF NOT EXISTS Math (id INTEGER PRIMARY KEY, question_test TEXT, answer1_test TEXT, answer2_test TEXT, answer3_test TEXT, answer4_test TEXT, answer5_test TEXT, answer1 TEXT, answer2 TEXT, answer3 TEXT, answer4 TEXT, answer5 TEXT, answer_true TEXT);";
    rc = sqlite3_exec(db, sql_create, NULL, NULL, NULL);
    sql_create = "CREATE TABLE IF NOT EXISTS History (id INTEGER PRIMARY KEY, question_test TEXT, answer1_test TEXT, answer2_test TEXT, answer3_test TEXT, answer4_test TEXT, answer5_test TEXT, answer6_test TEXT, answer7_test TEXT, answer1 TEXT, answer2 TEXT, answer3 TEXT, answer4 TEXT, answer5 TEXT, answer_true TEXT);";
    rc = sqlite3_exec(db, sql_create, NULL, NULL, NULL);

    sql_create = "CREATE TABLE IF NOT EXISTS Score_Ukr (id INTEGER, score INTEGER);"; // ��������� ������� ��� 200 ������ �������
    rc = sqlite3_exec(db, sql_create, NULL, NULL, NULL);
    sql_create = "CREATE TABLE IF NOT EXISTS Score_Math (id INTEGER, score INTEGER);";
    rc = sqlite3_exec(db, sql_create, NULL, NULL, NULL);
    sql_create = "CREATE TABLE IF NOT EXISTS Score_History (id INTEGER, score INTEGER);";
    rc = sqlite3_exec(db, sql_create, NULL, NULL, NULL);



    int menu() // �������, ��� ������ ������� ����
    {
        system("cls");
        printf("+-------------------------------------------+\n");
        printf("|                    ����                   |\n");
        printf("+-------------------------------------------+\n");
        printf("|                                           |\n");
        printf("|              ������ ���� - 1              |\n");
        printf("|              ���������� ��������� - 2     |\n");
        printf("|              ����������� - 3              |\n");
        printf("|                                           |\n");
        printf("|              ��� �������� - 4             |\n");
        printf("|              ����� - E                    |\n");
        printf("|                                           |\n");
        printf("+-------------------------------------------+\n");
    }

    int results_NMT(int score, int test, char name[1000], char name_test[1000]) // �������, ��� �������� ���������� ��������� ��� ��� ����������
    {
        int width_name_test = 15; // ���������� ������ ����� ��� ����������� ����������� ����������
        int width_name = 66;
        int width_score = 41;
        int width_score_200 = 33;
        int width_score_12 = 34;

        if (test == 1) { // ���� ���� ��������� ����
            int score_12 = round((float)score/45.0*12); // ����������� � 12 ������ �������

            sqlite3_stmt *stmt;
            rc = sqlite3_prepare_v2(db, "SELECT * FROM Score_Ukr", -1, &stmt, 0);
            int cols = sqlite3_column_count(stmt);

                
            while (sqlite3_step(stmt) == SQLITE_ROW) { // ���� ��� ��������� ����� ������� Score_Ukr
                const char *id = sqlite3_column_text(stmt, 0); // ����� ���������� �����
                int parsed = atoi(id);
                if (score == parsed) {
                    const char *score_200 = sqlite3_column_text(stmt, 1);
                    sqlite3_stmt *stmt;
                    rc = sqlite3_prepare_v2(db, "INSERT INTO results (name_test, name_user, max_id, score, score_200, score_12) VALUES (?, ?, '45', ?, ?, ?)", -1, &stmt, NULL); // ��������� ������ ���������� �� ������� results

                    sqlite3_bind_text(stmt, 1, name_test, -1, SQLITE_TRANSIENT);
                    sqlite3_bind_text(stmt, 2, name, -1, SQLITE_TRANSIENT);
                    char score_str[20];
                    snprintf(score_str, 20, "%d", score);
                    sqlite3_bind_text(stmt, 3, score_str, -1, SQLITE_TRANSIENT);
                    sqlite3_bind_text(stmt, 4, score_200, -1, SQLITE_TRANSIENT);
                    char score_12_str[20];
                    snprintf(score_12_str, 20, "%d", score_12);
                    sqlite3_bind_text(stmt, 5, score_12_str, -1, SQLITE_TRANSIENT);
                    
                    rc = sqlite3_step(stmt);
                    sqlite3_finalize(stmt);
                    while (TRUE) {
                        system("cls");
                                    
                        printf("+-----------------------------------------------------------------------------------------------------------+\n");
                        printf("|      %-*s                            ����������                                                |\n", width_name_test, name_test);
                        printf("+-----------------------------------------------------------------------------------------------------------+\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                            ���������� ���������                                           |\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                   ��'�: %-*s|\n", width_name, name);
                        printf("|                                                                                                           |\n");
                        printf("|                                              ��ز ����������                                              |\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                   ʳ������ ���� � 45 ��������: %-*d|\n", width_score, score);
                        printf("|                                   ʳ������ ���� � 200 ������ ������: %-*s|\n", width_score_200, score_200);
                        printf("|                                   ʳ������ ���� � 12 ������ ������: %-*d|\n", width_score_12, score_12);
                        printf("|                                                                                                           |\n");
                        printf("|                                                                                                           |\n");
                        printf("+-----------------------------------------------------------------------------------------------------------+\n");
                        printf("|                                                  ���� - E                                                 |\n");
                        printf("+-----------------------------------------------------------------------------------------------------------+\n");
                        printf("\n");
                        printf("���� �����: ");

                        char select_results[1000];
                        scanf("%s", &select_results);



                        if (select_results[0] == 'E' && strlen(select_results) == 1 || select_results[0] == 'e' && strlen(select_results) == 1 || select_results[0] == '�' && strlen(select_results) == 1 || select_results[0] == '�' && strlen(select_results) == 1) { // ���� ������ E, �� ����� � �������
                            return 0;
                        }
                                                        
                        else {
                            ;
                        }    
                    }
                }
            }
        }

        if (test == 2) { // ���� ���� ����������
            int score_12 = round((float)score/32.0*12); // ����������� � 12 ������ �������

            sqlite3_stmt *stmt;
            rc = sqlite3_prepare_v2(db, "SELECT * FROM Score_Math", -1, &stmt, 0);
            int cols = sqlite3_column_count(stmt);

                
            while (sqlite3_step(stmt) == SQLITE_ROW) { // ���� ��� ��������� ����� ������� Score_Math
                const char *id = sqlite3_column_text(stmt, 0); // ����� ���������� �����
                int parsed = atoi(id);
                if (score == parsed) {
                    const char *score_200 = sqlite3_column_text(stmt, 1);
                    sqlite3_stmt *stmt;
                    rc = sqlite3_prepare_v2(db, "INSERT INTO results (name_test, name_user, max_id, score, score_200, score_12) VALUES (?, ?, '32', ?, ?, ?)", -1, &stmt, NULL); // ��������� ������ ���������� �� ������� results

                    sqlite3_bind_text(stmt, 1, name_test, -1, SQLITE_TRANSIENT);
                    sqlite3_bind_text(stmt, 2, name, -1, SQLITE_TRANSIENT);
                    char score_str[20];
                    snprintf(score_str, 20, "%d", score);
                    sqlite3_bind_text(stmt, 3, score_str, -1, SQLITE_TRANSIENT);
                    sqlite3_bind_text(stmt, 4, score_200, -1, SQLITE_TRANSIENT);
                    char score_12_str[20];
                    snprintf(score_12_str, 20, "%d", score_12);
                    sqlite3_bind_text(stmt, 5, score_12_str, -1, SQLITE_TRANSIENT);
                    
                    rc = sqlite3_step(stmt);
                    sqlite3_finalize(stmt);
                    while (TRUE) {
                        system("cls");
                                    
                        printf("+-----------------------------------------------------------------------------------------------------------+\n");
                        printf("|      %-*s                            ����������                                                |\n", width_name_test, name_test);
                        printf("+-----------------------------------------------------------------------------------------------------------+\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                            ���������� ���������                                           |\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                   ��'�: %-*s|\n", width_name, name);
                        printf("|                                                                                                           |\n");
                        printf("|                                              ��ز ����������                                              |\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                   ʳ������ ���� � 32 ��������: %-*d|\n", width_score, score);
                        printf("|                                   ʳ������ ���� � 200 ������ ������: %-*s|\n", width_score_200, score_200);
                        printf("|                                   ʳ������ ���� � 12 ������ ������: %-*d|\n", width_score_12, score_12);
                        printf("|                                                                                                           |\n");
                        printf("|                                                                                                           |\n");
                        printf("+-----------------------------------------------------------------------------------------------------------+\n");
                        printf("|                                                  ���� - E                                                 |\n");
                        printf("+-----------------------------------------------------------------------------------------------------------+\n");
                        printf("\n");
                        printf("���� �����: ");

                        char select_results[1000];
                        scanf("%s", &select_results);



                        if (select_results[0] == 'E' && strlen(select_results) == 1 || select_results[0] == 'e' && strlen(select_results) == 1 || select_results[0] == '�' && strlen(select_results) == 1 || select_results[0] == '�' && strlen(select_results) == 1) { // ���� ������ E, �� ����� � �������
                            return 0;
                        }
                                                        
                        else {
                            ;
                        }    
                    }
                }
            }
        }

        if (test == 3) { // ���� ���� ������ ������
            int score_12 = round((float)score/54.0*12); // ����������� � 12 ������ �������

            sqlite3_stmt *stmt;
            rc = sqlite3_prepare_v2(db, "SELECT * FROM Score_History", -1, &stmt, 0);
            int cols = sqlite3_column_count(stmt);

                
            while (sqlite3_step(stmt) == SQLITE_ROW) { // ���� ��� ��������� ����� ������� Score_History
                const char *id = sqlite3_column_text(stmt, 0); // ����� ���������� �����
                int parsed = atoi(id);
                if (score == parsed) {
                    const char *score_200 = sqlite3_column_text(stmt, 1);
                    sqlite3_stmt *stmt;
                    rc = sqlite3_prepare_v2(db, "INSERT INTO results (name_test, name_user, max_id, score, score_200, score_12) VALUES (?, ?, '54', ?, ?, ?)", -1, &stmt, NULL); // ��������� ������ ���������� �� ������� results

                    sqlite3_bind_text(stmt, 1, name_test, -1, SQLITE_TRANSIENT);
                    sqlite3_bind_text(stmt, 2, name, -1, SQLITE_TRANSIENT);
                    char score_str[20];
                    snprintf(score_str, 20, "%d", score);
                    sqlite3_bind_text(stmt, 3, score_str, -1, SQLITE_TRANSIENT);
                    sqlite3_bind_text(stmt, 4, score_200, -1, SQLITE_TRANSIENT);
                    char score_12_str[20];
                    snprintf(score_12_str, 20, "%d", score_12);
                    sqlite3_bind_text(stmt, 5, score_12_str, -1, SQLITE_TRANSIENT);
                    
                    rc = sqlite3_step(stmt);
                    sqlite3_finalize(stmt);
                    while (TRUE) {
                        system("cls");
                                    
                        printf("+-----------------------------------------------------------------------------------------------------------+\n");
                        printf("|      %-*s                            ����������                                                |\n", width_name_test, name_test);
                        printf("+-----------------------------------------------------------------------------------------------------------+\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                            ���������� ���������                                           |\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                   ��'�: %-*s|\n", width_name, name);
                        printf("|                                                                                                           |\n");
                        printf("|                                              ��ز ����������                                              |\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                   ʳ������ ���� � 54 ��������: %-*d|\n", width_score, score);
                        printf("|                                   ʳ������ ���� � 200 ������ ������: %-*s|\n", width_score_200, score_200);
                        printf("|                                   ʳ������ ���� � 12 ������ ������: %-*d|\n", width_score_12, score_12);
                        printf("|                                                                                                           |\n");
                        printf("|                                                                                                           |\n");
                        printf("+-----------------------------------------------------------------------------------------------------------+\n");
                        printf("|                                                  ���� - E                                                 |\n");
                        printf("+-----------------------------------------------------------------------------------------------------------+\n");
                        printf("\n");
                        printf("���� �����: ");

                        char select_results[1000];
                        scanf("%s", &select_results);



                        if (select_results[0] == 'E' && strlen(select_results) == 1 || select_results[0] == 'e' && strlen(select_results) == 1 || select_results[0] == '�' && strlen(select_results) == 1 || select_results[0] == '�' && strlen(select_results) == 1) { // ���� ������ E, �� ����� � �������
                            return 0;
                        }
                                                        
                        else {
                            ;
                        }    
                    }
                }
            }
        } 
    }

    int results_custom_tests(int score, char name_user[1000], char name[255]) // �������, ��� �������� ���������� ��������� ������� �����
    {
        int width_name = 66; // ���������� ������ ����� ��� ����������� ����������� ����������
        int width_score = 41;
        int width_score_12 = 34;

        int max_id = 0; 

        char* query = NULL;
        int query_len = 0;
        sqlite3_stmt *stmt;

        query_len = snprintf(NULL, 0, "SELECT MAX(id) FROM '%s'", name); // ����� ������������� ���� �����
        query = malloc(query_len + 1);
        sprintf(query, "SELECT MAX(id) FROM '%s'", name);

        rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            max_id = sqlite3_column_int(stmt, 0);

            int count_id = max_id; // ���������� ������� ���� � ���� max_id(������������ ��� �����) ��� ����������� ����������� ����������
            int count = 0;

            while (count_id != 0) {
                count++;
                count_id /= 10;
            }
            if (count==1) { // ������������ ��������� ������ ����� ��� ����������� ����������� ����������
                width_score = width_score + 1;
            }
            if (count==3) {
                width_score = width_score - 1;
            }
            
            int score_12 = round((float)score/max_id*12); // ����������� � 12 ������ �������

            sqlite3_stmt *stmt;
            rc = sqlite3_prepare_v2(db, "INSERT INTO results (name_test, name_user, max_id, score, score_12) VALUES (?, ?, ?, ?, ?)", -1, &stmt, NULL); // ��������� ������ ���������� �� ������� results

            sqlite3_bind_text(stmt, 1, name, -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 2, name_user, -1, SQLITE_TRANSIENT);
            char max_id_str[20];
            snprintf(max_id_str, 20, "%d", max_id);
            sqlite3_bind_text(stmt, 3, max_id_str, -1, SQLITE_TRANSIENT);
            char score_str[20];
            snprintf(score_str, 20, "%d", score);
            sqlite3_bind_text(stmt, 4, score_str, -1, SQLITE_TRANSIENT);
            char score_12_str[20];
            snprintf(score_12_str, 20, "%d", score_12);
            sqlite3_bind_text(stmt, 5, score_12_str, -1, SQLITE_TRANSIENT);
                    
            rc = sqlite3_step(stmt);
            sqlite3_finalize(stmt);

            while (TRUE) {
                system("cls");
                            
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("|                                                 ����������                                                |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("|                                                                                                           |\n");
                printf("|                                                                                                           |\n");
                printf("|                                            ���������� ���������                                           |\n");
                printf("|                                                                                                           |\n");
                printf("|                                   ��'�: %-*s|\n", width_name, name_user);
                printf("|                                                                                                           |\n");
                printf("|                                              ��ز ����������                                              |\n");
                printf("|                                                                                                           |\n");
                printf("|                                                                                                           |\n");
                printf("|                                   ʳ������ ���� � %d ��������: %-*d|\n", max_id, width_score, score);
                printf("|                                   ʳ������ ���� � 12 ������ ������: %-*d|\n", width_score_12, score_12);
                printf("|                                                                                                           |\n");
                printf("|                                                                                                           |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("|                                                  ���� - E                                                 |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("\n");
                printf("���� �����: ");

                char select_results[1000];
                scanf("%s", &select_results);

                if (select_results[0] == 'E' && strlen(select_results) == 1 || select_results[0] == 'e' && strlen(select_results) == 1 || select_results[0] == '�' && strlen(select_results) == 1 || select_results[0] == '�' && strlen(select_results) == 1) { // ���� ������ E, �� ����� � �������
                    return 0;
                }
                                                
                else {
                    ;
                }
            }
        }


        
    }

    int results(){ // �������, ��� �������� ������ 5 ���� ���������
        while (TRUE) {
            system("cls");
            printf("+-------------------------------------------------------------------------+\n");
            printf("|                                 ����������                              |\n");
            printf("+-------------------------------------------------------------------------+\n");
            printf("|                                                                         |\n");
            printf("|                           ������ ���� ���������                        |\n");

            sqlite3_stmt *stmt;
            rc = sqlite3_prepare_v2(db, "SELECT * FROM results ORDER BY id DESC LIMIT 5;", -1, &stmt, 0); // sql ����� ��� ������ 5 ������� ������
            int cols = sqlite3_column_count(stmt);

            while (sqlite3_step(stmt) == SQLITE_ROW) { // ���� ��� ��������� ����� �������
                char *id = sqlite3_column_text(stmt, 0);
                char *name_test = sqlite3_column_text(stmt, 1);
                char *name_user = sqlite3_column_text(stmt, 2);
                char *max_id = sqlite3_column_text(stmt, 3);
                char *score = sqlite3_column_text(stmt, 4);
                char *score_200 = sqlite3_column_text(stmt, 5);
                char *score_12 = sqlite3_column_text(stmt, 6);

                printf("|                                                                         |\n");
                printf("|                                                                         |\n");

                strcat(id, ". ");
                strcat(id, name_test);
                split_string(id, 61);
                printf("|                                                                         |\n");
                char text1[256] = "����������: ";
                strcat(text1, name_user);
                split_string(text1, 61);
                printf("|                                                                         |\n");
                char text2[256] = "ʳ������ ���� � ";
                strcat(text2, max_id);
                strcat(text2, " ��������: ");
                strcat(text2, score);
                split_string(text2, 61);

                if (score_200 != NULL) { // ���� ���� �� ���������� � 200 ������ ������, �� �������� ��
                    char text3[256] = "ʳ������ ���� � 200 ������ ������: ";
                    strcat(text3, score_200);
                    split_string(text3, 61);
                }

                char text4[256] = "ʳ������ ���� � 12 ������ ������: ";
                strcat(text4, score_12);
                split_string(text4, 61);    
            }
            sqlite3_finalize(stmt);
            printf("|                                                                         |\n");
            printf("|                                                                         |\n");
            printf("+-------------------------------------------------------------------------+\n");
            printf("|                                 ���� - E                                |\n");
            printf("+-------------------------------------------------------------------------+\n");
            printf("\n");
            printf("���� �����: "); 

            char select_results[1000];
            scanf("%s", &select_results);

            if (select_results[0] == 'E' && strlen(select_results) == 1 || select_results[0] == 'e' && strlen(select_results) == 1 || select_results[0] == '�' && strlen(select_results) == 1 || select_results[0] == '�' && strlen(select_results) == 1) { // ���� ������ E, �� ����� � �������
                return 0;
            }
                                                
            else {
                ;
            }
        }
    }

    int constructor() // ����������� ��� ���������, ����������� �� ��������� �����
    {
        exit8:
        exit5:
        while (TRUE) { 
            exit13:
            system("cls");
            printf("+-------------------------------------------+\n");
            printf("|                 �����������               |\n");
            printf("+-------------------------------------------+\n");
            printf("|                                           |\n");
            printf("|              �������� ���� - 1            |\n");
            printf("|              ���������� ���� - 2          |\n");
            printf("|              �������� ���� - 3            |\n");
            printf("|                                           |\n");
            printf("|              ������ ��� ����������� - 4   |\n");
            printf("|              ���� - E                     |\n");
            printf("|                                           |\n");
            printf("+-------------------------------------------+\n");
            printf("\n");
            printf("���� �����: ");

            char select_constructor[1];
            scanf("%s", select_constructor);

            if (select_constructor[0] == '1' && strlen(select_constructor) == 1) { // ��������� �����
                system("cls");
                printf("+-------------------------------------------+\n");
                printf("|               ��������� �����             |\n");
                printf("+-------------------------------------------+\n");
                printf("|                                           |\n");
                printf("|                                           |\n");
                printf("|             ������ ����� �����           |\n");
                printf("|                                           |\n");
                printf("+-------------------------------------------+\n");
                printf("|                  ����� - E                |\n");
                printf("+-------------------------------------------+\n");
                printf("\n");
                printf("������ ����� �����: ");
                getchar();
                char select_name_test[255];
                fgets(select_name_test, 255, stdin); // ����� �����

                int len = strcspn(select_name_test, "\n"); // ��������� ������ �������� ��� ����������� ����������� ����������
                select_name_test[len] = '\0'; 

                if (select_name_test[0] == 'E' && strlen(select_name_test) == 1 || select_name_test[0] == 'e' && strlen(select_name_test) == 1 || select_name_test[0] == '�' && strlen(select_name_test) == 1 || select_name_test[0] == '�' && strlen(select_name_test) == 1) { // ���� ������ E, �� ���������� �����
                    goto exit2;
                }

                else {

                    char* sql_insert_select_name_test = "INSERT INTO Custom_Tests (name) VALUES(?);"; // ��������� ������ � ��'�� ���������� ����� �� ������� Custom_Tests(������ ������� �����)
                    sqlite3_stmt *stmt;
                    rc = sqlite3_prepare_v2(db, sql_insert_select_name_test, -1, &stmt, 0);

                    sqlite3_bind_text(stmt, 1, select_name_test, -1, SQLITE_STATIC);
                    rc = sqlite3_step(stmt);
                    sqlite3_finalize(stmt);

                    char* sql_create_select_name_test = sqlite3_mprintf("CREATE TABLE '%s' (id INTEGER PRIMARY KEY, question TEXT, answer1 TEXT, answer2 TEXT, answer3 TEXT, answer4 TEXT);", select_name_test); // ��������� �������, �� � ���� ����� ������
                    rc = sqlite3_exec(db, sql_create_select_name_test, NULL, NULL, NULL);

                    char select_name_question[1000];
                    char select_answer_question[1000];

                    for (int i=1; i<=100; i++) { // ����, ���� ������� ������ �� �������(������� ���������)
                        // ��������� ���������
                        int width = 4;
                        system("cls");
                        printf("+-------------------------------------------+\n");
                        printf("|               ��������� �����             |\n");
                        printf("+-------------------------------------------+\n");
                        printf("|                                           |\n");
                        printf("|                ��������� �%-*d            |\n", width, i);
                        printf("|                                           |\n");
                        printf("|              ������ ���������            |\n");
                        printf("|                                           |\n");
                        printf("|                                           |\n");
                        printf("+-------------------------------------------+\n");
                        printf("|                �������� - E              |\n");
                        printf("+-------------------------------------------+\n");
                        printf("\n");
                        printf("������ ���������: ");
                        fgets(select_name_question, 1000, stdin); // ���������

                        int len = strcspn(select_name_question, "\n"); // ��������� ������ �������� ��� ����������� ����������� ����������
                        select_name_question[len] = '\0';

                        if (select_name_question[0] == 'E' && strlen(select_name_question) == 1 || select_name_question[0] == 'e' && strlen(select_name_question) == 1 || select_name_question[0] == '�' && strlen(select_name_question) == 1 || select_name_question[0] == '�' && strlen(select_name_question) == 1) { // ���� ������ E, �� ���������� �����
                            goto exit2;
                        }

                        else {
                            while (TRUE) {
                                // ��������� ������� ��������
                                char text1[255] = "�������� 4 ������� �������� ����� ���� '|' ��� ��������.";
                                char text2[255] = "��� ���� ��� ������� ��������� �������, ��� �������� ������� �������� ��� ����� '+' ��� ��������. ";
                                char text3[255] = "������: 2+2=5|2+2=4+++|2+2=3|����� ��� �����???";
                                
                                system("cls");
                                printf("+-------------------------------------------------------------------------+\n");
                                printf("|                              ��������� �����                            |\n");
                                printf("+-------------------------------------------------------------------------+\n");
                                printf("|                                                                         |\n");
                                printf("|                               ��������� �%-*d                           |\n", width, i);
                                printf("|                                                                         |\n");
                                split_string(text1, 61);
                                split_string(text2, 61);
                                printf("|                                                                         |\n");
                                split_string(text3, 61);
                                printf("|                                                                         |\n");
                                printf("|                                                                         |\n");
                                printf("+-------------------------------------------------------------------------+\n");
                                printf("|                               �������� - E                             |\n");
                                printf("+-------------------------------------------------------------------------+\n");
                                printf("\n");
                                printf("������ ������� ��������: ");
                                fgets(select_answer_question, 1000, stdin); 

                                int len = strcspn(select_answer_question, "\n"); // ��������� ������ �������� ��� ����������� ����������� ����������
                                select_answer_question[len] = '\0';

                                if (select_answer_question[0] == 'E' && strlen(select_answer_question) == 1 || select_answer_question[0] == 'e' && strlen(select_answer_question) == 1 || select_answer_question[0] == '�' && strlen(select_answer_question) == 1 || select_answer_question[0] == '�' && strlen(select_answer_question) == 1) { // ���� ������ E, �� ���������� �����
                                    return 0;
                                }

                                int count = 0; // ��������� ������� ����� "|"

                                for (int i = 0; i < strlen(select_answer_question); i++) {
                                    if (select_answer_question[i] == '|') {
                                     count++;
                                    }
                                }

                                if (count == 3) { // ���� ����� "|" ������� 3
                                    char* token = strtok(select_answer_question, "|"); // ����������� ����� �� 4 ������� �������� �� ��������� ����� "|"
                                    char* question1 = token;
                                    token = strtok(NULL, "|");
                                    char* question2 = token;
                                    token = strtok(NULL, "|");
                                    char* question3 = token;
                                    token = strtok(NULL, "|");
                                    char* question4 = token;


                                    if (question1 != NULL && question2 != NULL && question3 != NULL && question4 != NULL) {

                                        char query[256];
                                        sprintf(query, "INSERT INTO '%s' (question, answer1, answer2, answer3, answer4) VALUES (?, ?, ?, ?, ?);", select_name_test); // ��������� ������ ��� ��������� �� ������ �������� �� �������(�����)

                                        sqlite3_stmt *stmt;
                                        rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);

                                        sqlite3_bind_text(stmt, 1, select_name_question, -1, SQLITE_STATIC);
                                        sqlite3_bind_text(stmt, 2, question1, -1, SQLITE_STATIC);
                                        sqlite3_bind_text(stmt, 3, question2, -1, SQLITE_STATIC);
                                        sqlite3_bind_text(stmt, 4, question3, -1, SQLITE_STATIC);
                                        sqlite3_bind_text(stmt, 5, question4, -1, SQLITE_STATIC);

                                        rc = sqlite3_step(stmt);
                                        sqlite3_finalize(stmt);
                                        break;
                                    }  
                                }
                            }
                        } 
                    }
                }
            }


            if (select_constructor[0] == '2' && strlen(select_constructor) == 1) { // ����������� �����
                exit6:
                while (TRUE) {
                    // ���� ������ �����
                    system("cls");
                    printf("+-------------------------------------------------------------------------+\n");
                    printf("|                                �����������                              |\n");
                    printf("+-------------------------------------------------------------------------+\n");
                    printf("|                                                                         |\n");
                    printf("|                               ������ �����                             |\n");
                    printf("|                                                                         |\n");
                    // ������ ������� Custom_Tests
                    sqlite3_stmt *stmt;
                    rc = sqlite3_prepare_v2(db, "SELECT * FROM Custom_Tests", -1, &stmt, 0);
                    int cols = sqlite3_column_count(stmt);

                    while (sqlite3_step(stmt) == SQLITE_ROW) {
                        char *id = sqlite3_column_text(stmt, 0);
                        char *name = sqlite3_column_text(stmt, 1);
                        strcat(id, ".  ");
                        strcat(id, name);
                        split_string(id, 61);
                    }

                    printf("|                                                                         |\n");
                    printf("|                                                                         |\n");
                    printf("+-------------------------------------------------------------------------+\n");
                    printf("|                                 ����� - E                               |\n");
                    printf("+-------------------------------------------------------------------------+\n");
                    printf("\n������ ������� ���� �������� ���� �����: ");
                    char select_test_change[100];
                    scanf("%s", select_test_change);

                    if (select_test_change[0] == 'E' && strlen(select_test_change) == 1 || select_test_change[0] == 'e' && strlen(select_test_change) == 1 || select_test_change[0] == '�' && strlen(select_test_change) == 1 || select_test_change[0] == '�' && strlen(select_test_change) == 1) { // ���� ������ E, �� ���������� �����
                        goto exit5;
                    }

                    else {
                        sqlite3_stmt *stmt;
                        rc = sqlite3_prepare_v2(db, "SELECT * FROM Custom_Tests", -1, &stmt, 0);
                        int cols = sqlite3_column_count(stmt);

                        while (sqlite3_step(stmt) == SQLITE_ROW) {
                            const char *id = sqlite3_column_text(stmt, 0);
                            const char *name = sqlite3_column_text(stmt, 1);
                            if (strcmp(id, select_test_change)==0) {
                                exit32:
                                exit31:
                                exit30:
                                exit9:
                                exit7:
                                while (TRUE) {
                                    // ���� ����������� �����
                                    system("cls");
                                    printf("+-------------------------------------------+\n");
                                    printf("|                 �����������               |\n");
                                    printf("+-------------------------------------------+\n");
                                    printf("|                                           |\n");
                                    printf("|              ������ ����� - 1            |\n");
                                    printf("|              ������ ��������� - 2        |\n");
                                    printf("|              ������ ��������� - 3         |\n");
                                    printf("|              �������� ��������� - 4       |\n");
                                    printf("|                                           |\n");
                                    printf("+-------------------------------------------+\n");
                                    printf("|                  ����� - E                |\n");
                                    printf("+-------------------------------------------+\n");

                                    printf("\n\n���� �����: ");
                                    char select_change_test[1];
                                    scanf("%s", select_change_test);

                                    if (select_change_test[0] == '1' && strlen(select_change_test) == 1) { // ���� �����
                                        system("cls");
                                        printf("+-------------------------------------------+\n");
                                        printf("|                 �̲�� �����               |\n");
                                        printf("+-------------------------------------------+\n");
                                        printf("|                                           |\n");
                                        printf("|                                           |\n");
                                        printf("|              ������ ���� �����           |\n");
                                        printf("|                                           |\n");
                                        printf("|                                           |\n");
                                        printf("+-------------------------------------------+\n");
                                        printf("|                  ����� - E                |\n");
                                        printf("+-------------------------------------------+\n");
                                        printf("\n");
                                        printf("������ ���� �����: ");
                                        getchar();
                                        char new_name_test[100];
                                        fgets(new_name_test, 255, stdin);

                                        int len = strcspn(new_name_test, "\n"); // ��������� ������ �������� ��� ����������� ����������� ����������
                                        new_name_test[len] = '\0';

                                        if (new_name_test[0] == 'E' && strlen(new_name_test) == 1 || new_name_test[0] == 'e' && strlen(new_name_test) == 1 || new_name_test[0] == '�' && strlen(new_name_test) == 1 || new_name_test[0] == '�' && strlen(new_name_test) == 1) { // ���� ������ E, �� ���������� �����
                                            goto exit7;
                                        }

                                        else {
                                            // ������ ������ ��� ���� ��� ������ ����� ����� ����� id
                                            sqlite3_stmt *stmt;
                                            rc = sqlite3_prepare_v2(db, "SELECT * FROM Custom_Tests", -1, &stmt, 0);
                                            int cols = sqlite3_column_count(stmt);

                                            while (sqlite3_step(stmt) == SQLITE_ROW) {
                                                const char *id = sqlite3_column_text(stmt, 0);
                                                if (strcmp(select_test_change, id)==0) {
                                                    const char *old_name = sqlite3_column_text(stmt, 1);
                                                    // ������� ����� �������(�����)
                                                    char sql_rename_table[256];
                                                    sprintf(sql_rename_table, "ALTER TABLE '%s' RENAME TO '%s';", old_name, new_name_test);
                                                    rc = sqlite3_exec(db, sql_rename_table, NULL, NULL, NULL);
                                                    // ������� ����� ������(�����) � ������� Custom_Tests
                                                    char sql_rename[256];
                                                    sprintf(sql_rename, "UPDATE Custom_Tests SET name = '%s' WHERE id = %s;", new_name_test, select_test_change);
                                                    rc = sqlite3_exec(db, sql_rename, NULL, NULL, NULL);
                                                }
                                            }
                                        }
                                    }

                                    if (select_change_test[0] == '2' && strlen(select_change_test) == 1) { // ���� ���������
                                        exit12:
                                        exit10:
                                        while (TRUE) {
                                            // ���� �������� �����
                                            system("cls");
                                            printf("+-------------------------------------------------------------------------+\n");
                                            printf("|                                �����������                              |\n");
                                            printf("+-------------------------------------------------------------------------+\n");
                                            printf("|                                                                         |\n");
                                            printf("|                                 ���������                               |\n");
                                            // ������ ������ ��� ���� ��� ������ ����� ����� ����� id
                                            sqlite3_stmt *stmt;
                                            rc = sqlite3_prepare_v2(db, "SELECT * FROM Custom_Tests", -1, &stmt, 0);
                                            int cols = sqlite3_column_count(stmt);

                                            while (sqlite3_step(stmt) == SQLITE_ROW) {
                                                const char *id = sqlite3_column_text(stmt, 0);
                                                if (strcmp(select_test_change, id)==0) {
                                                    const char *name_update = sqlite3_column_text(stmt, 1);

                                                    sqlite3_stmt *stmt;
                                                    char *sql_select_test = sqlite3_mprintf("SELECT * FROM '%s';", name_update);
                                                    rc = sqlite3_prepare_v2(db, sql_select_test, -1, &stmt, 0);
                                                    int cols = sqlite3_column_count(stmt);

                                                    while (sqlite3_step(stmt) == SQLITE_ROW) {
                                                        char *id = sqlite3_column_text(stmt, 0);
                                                        char *name = sqlite3_column_text(stmt, 1);
                                                        char *answer1 = sqlite3_column_text(stmt, 2);
                                                        char *answer2 = sqlite3_column_text(stmt, 3);
                                                        char *answer3 = sqlite3_column_text(stmt, 4);
                                                        char *answer4 = sqlite3_column_text(stmt, 5);
                                                        strcat(id, ". ");
                                                        strcat(id, name);
                                                        printf("|                                                                         |\n");
                                                        split_string(id, 61);
                                                        printf("|                                                                         |\n");
                                                        // ������ �� ������� �������� �����
                                                        char A[255] = "� ";
                                                        char B[255] = "� ";
                                                        char C[255] = "� ";
                                                        char D[255] = "� ";
                                                        strcat(A, answer1);
                                                        split_string(A, 61);
                                                        strcat(B, answer2);
                                                        split_string(B, 61);
                                                        strcat(C, answer3);
                                                        split_string(C, 61);
                                                        strcat(D, answer4);
                                                        split_string(D, 61);
                                                    }
                                                    printf("|                                                                         |\n");
                                                    printf("|                                                                         |\n");
                                                    printf("+-------------------------------------------------------------------------+\n");
                                                    printf("|                                 ����� - E                               |\n");
                                                    printf("+-------------------------------------------------------------------------+\n");
                                                    printf("\n������ ��������� �������� ���� �����: ");
                                                    char select_question[100];
                                                    scanf("%s", select_question);

                                                    if (select_question[0] == 'E' && strlen(select_question) == 1 || select_question[0] == 'e' && strlen(select_question) == 1 || select_question[0] == '�' && strlen(select_question) == 1 || select_question[0] == '�' && strlen(select_question) == 1) { // ���� ������ E, �� ���������� �����
                                                        goto exit9;
                                                    }
                                                    else {
                                                        // ��������� �� ����� ������ ��������� � � ���� ����� ������
                                                        sqlite3_stmt *stmt;
                                                        sql_select_test = sqlite3_mprintf("SELECT * FROM '%s';", name_update);
                                                        rc = sqlite3_prepare_v2(db, sql_select_test, -1, &stmt, 0);
                                                        int cols = sqlite3_column_count(stmt);

                                                        while (sqlite3_step(stmt) == SQLITE_ROW) {
                                                            char *id = sqlite3_column_text(stmt, 0);
                                                            if (strcmp(select_question, id)==0) {
                                                                while (TRUE) {
                                                                    // ������� ���������
                                                                    char *name = sqlite3_column_text(stmt, 1);
                                                                    char *answer1 = sqlite3_column_text(stmt, 2);
                                                                    char *answer2 = sqlite3_column_text(stmt, 3);
                                                                    char *answer3 = sqlite3_column_text(stmt, 4);
                                                                    char *answer4 = sqlite3_column_text(stmt, 5);
                                                                    strcat(id, ". ");
                                                                    strcat(id, name);
                                                                    exit11:
                                                                    system("cls");
                                                                    printf("+-------------------------------------------------------------------------+\n");
                                                                    printf("|                                �����������                              |\n");
                                                                    printf("+-------------------------------------------------------------------------+\n");
                                                                    printf("|                                                                         |\n");
                                                                    printf("|                                 ���������                               |\n");
                                                                    printf("|                                                                         |\n");
                                                                    split_string(id, 61);
                                                                    printf("|                                                                         |\n");
                                                                    char A[255] = "� ";
                                                                    char B[255] = "� ";
                                                                    char C[255] = "� ";
                                                                    char D[255] = "� ";
                                                                    strcat(A, answer1);
                                                                    split_string(A, 61);
                                                                    strcat(B, answer2);
                                                                    split_string(B, 61);
                                                                    strcat(C, answer3);
                                                                    split_string(C, 61);
                                                                    strcat(D, answer4);
                                                                    split_string(D, 61);
                                                                    printf("|                                                                         |\n");
                                                                    printf("|      �������� ���� ���������.                                           |\n");
                                                                    printf("|                                                                         |\n");
                                                                    printf("+-------------------------------------------------------------------------+\n");
                                                                    printf("|                                 ����� - E                               |\n");
                                                                    printf("+-------------------------------------------------------------------------+\n");
                                                                    printf("\n������ ���� �����: ");
                                                                    getchar();
                                                                    char new_name_question[1000];
                                                                    fgets(new_name_question, 1000, stdin);

                                                                    int len = strcspn(new_name_question, "\n");
                                                                    new_name_question[len] = '\0';

                                                                    if (new_name_question[0] == 'E' && strlen(new_name_question) == 1 || new_name_question[0] == 'e' && strlen(new_name_question) == 1 || new_name_question[0] == '�' && strlen(new_name_question) == 1 || new_name_question[0] == '�' && strlen(new_name_question) == 1) { // ���� ������ E, �� ���������� �����
                                                                        goto exit10;
                                                                    }

                                                                    else {
                                                                        sqlite3_stmt *stmt;
                                                                        char *sql_select_test = sqlite3_mprintf("SELECT * FROM '%s';", name_update);
                                                                        rc = sqlite3_prepare_v2(db, sql_select_test, -1, &stmt, 0);
                                                                        int cols = sqlite3_column_count(stmt);

                                                                        while (sqlite3_step(stmt) == SQLITE_ROW) {
                                                                            char *id = sqlite3_column_text(stmt, 0);
                                                                            if (strcmp(select_question, id)==0) {
                                                                                while (TRUE) {
                                                                                    // ������� ������� ��������
                                                                                    char *name = sqlite3_column_text(stmt, 1);
                                                                                    char *answer1 = sqlite3_column_text(stmt, 2);
                                                                                    char *answer2 = sqlite3_column_text(stmt, 3);
                                                                                    char *answer3 = sqlite3_column_text(stmt, 4);
                                                                                    char *answer4 = sqlite3_column_text(stmt, 5);
                                                                                    strcat(id, ". ");
                                                                                    strcat(id, new_name_question);
                                                                                    system("cls");
                                                                                    printf("+-------------------------------------------------------------------------+\n");
                                                                                    printf("|                                �����������                              |\n");
                                                                                    printf("+-------------------------------------------------------------------------+\n");
                                                                                    printf("|                                                                         |\n");
                                                                                    printf("|                                 ���������                               |\n");
                                                                                    printf("|                                                                         |\n");
                                                                                    split_string(id, 61);
                                                                                    printf("|                                                                         |\n");
                                                                                    char A[255] = "� ";
                                                                                    char B[255] = "� ";
                                                                                    char C[255] = "� ";
                                                                                    char D[255] = "� ";
                                                                                    strcat(A, answer1);
                                                                                    split_string(A, 61);
                                                                                    strcat(B, answer2);
                                                                                    split_string(B, 61);
                                                                                    strcat(C, answer3);
                                                                                    split_string(C, 61);
                                                                                    strcat(D, answer4);
                                                                                    split_string(D, 61);
                                                                                    printf("|                                                                         |\n");
                                                                                    char text1[255] = "�������� 4 ������� �������� ����� ���� '|' ��� ��������.";
                                                                                    char text2[255] = "��� ���� ��� ������� ��������� ������� ��� �������� ������� �������� ��� ����� '+' ��� ��������. ";
                                                                                    char text3[255] = "������: 2+2=5|2+2=4+++|2+2=3|����� ��� �����???";
                                                                                    split_string(text1, 61);
                                                                                    split_string(text2, 61);
                                                                                    printf("|                                                                         |\n");
                                                                                    split_string(text3, 61);
                                                                                    printf("|                                                                         |\n");
                                                                                    printf("|                                                                         |\n");
                                                                                    printf("+-------------------------------------------------------------------------+\n");
                                                                                    printf("|                                 ����� - E                               |\n");
                                                                                    printf("+-------------------------------------------------------------------------+\n");
                                                                                    printf("\n������ ��� ������� ��������: ");
                                                                                    char new_name_answer[1000];
                                                                                    fgets(new_name_answer, 1000, stdin);

                                                                                    int len = strcspn(new_name_answer, "\n"); // ��������� ������ �������� ��� ����������� ����������� ����������
                                                                                    new_name_answer[len] = '\0';

                                                                                    if (new_name_answer[0] == 'E' && strlen(new_name_answer) == 1 || new_name_answer[0] == 'e' && strlen(new_name_answer) == 1 || new_name_answer[0] == '�' && strlen(new_name_answer) == 1 || new_name_answer[0] == '�' && strlen(new_name_answer) == 1) { // ���� ������ ��������� E, �� ���������� �����
                                                                                        goto exit11;
                                                                                    }

                                                                                    int count = 0; // ��������� ������� ����� "|"

                                                                                    for (int i = 0; i < strlen(new_name_answer); i++) {
                                                                                        if (new_name_answer[i] == '|') {
                                                                                         count++;
                                                                                        }
                                                                                    }

                                                                                    if (count == 3) {
                                                                                        // ���� ��������� � �������(����)
                                                                                        char sql_rename_question[256];
                                                                                        sprintf(sql_rename_question, "UPDATE '%s' SET question = '%s' WHERE id = %s;", name_update, new_name_question, select_question);
                                                                                        rc = sqlite3_exec(db, sql_rename_question, NULL, NULL, NULL);

                                                                                        char* token = strtok(new_name_answer, "|"); // ����������� ����� �� 4 ������� �������� �� ��������� ����� "|"
                                                                                        char* new_answer1 = token;
                                                                                        token = strtok(NULL, "|");
                                                                                        char* new_answer2 = token;
                                                                                        token = strtok(NULL, "|");
                                                                                        char* new_answer3 = token;
                                                                                        token = strtok(NULL, "|");
                                                                                        char* new_answer4 = token;
                                                                                        // ���� ������� �������� � �������(����)
                                                                                        char sql_rename_answer1[256];
                                                                                        sprintf(sql_rename_answer1, "UPDATE '%s' SET answer1 = '%s' WHERE id = %s;", name_update, new_answer1, select_question);
                                                                                        rc = sqlite3_exec(db, sql_rename_answer1, NULL, NULL, NULL);

                                                                                        char sql_rename_answer2[256];
                                                                                        sprintf(sql_rename_answer2, "UPDATE '%s' SET answer2 = '%s' WHERE id = %s;", name_update, new_answer2, select_question);
                                                                                        rc = sqlite3_exec(db, sql_rename_answer2, NULL, NULL, NULL);

                                                                                        char sql_rename_answer3[256];
                                                                                        sprintf(sql_rename_answer3, "UPDATE '%s' SET answer3 = '%s' WHERE id = %s;", name_update, new_answer3, select_question);
                                                                                        rc = sqlite3_exec(db, sql_rename_answer3, NULL, NULL, NULL);

                                                                                        char sql_rename_answer4[256];
                                                                                        sprintf(sql_rename_answer4, "UPDATE '%s' SET answer4 = '%s' WHERE id = %s;", name_update, new_answer4, select_question);
                                                                                        rc = sqlite3_exec(db, sql_rename_answer4, NULL, NULL, NULL);
                                                                                        goto exit12;
                                                                                    }
                                                                                }
                                                                            }
                                                                        }
                                                                    }
                                                                }  
                                                            }   
                                                        }
                                                    }
                                                }
                                            }
                                        }   
                                    }

                                    if (select_change_test[0] == '3' && strlen(select_change_test) == 1) {
                                        char select_name_question[1000];
                                        char select_answer_question[1000];

                                        // ��������� ���������
                                        system("cls");
                                        printf("+-------------------------------------------+\n");
                                        printf("|             ��������� ���������           |\n");
                                        printf("+-------------------------------------------+\n");
                                        printf("|                                           |\n");
                                        printf("|                                           |\n");
                                        printf("|              ������ ���������            |\n");
                                        printf("|                                           |\n");
                                        printf("|                                           |\n");
                                        printf("+-------------------------------------------+\n");
                                        printf("|                �������� - E              |\n");
                                        printf("+-------------------------------------------+\n");
                                        printf("\n");
                                        printf("������ ���������: ");
                                        getchar();
                                        fgets(select_name_question, 1000, stdin); // ���������

                                        int len = strcspn(select_name_question, "\n"); // ��������� ������ �������� ��� ����������� ����������� ����������
                                        select_name_question[len] = '\0';

                                        if (select_name_question[0] == 'E' && strlen(select_name_question) == 1 || select_name_question[0] == 'e' && strlen(select_name_question) == 1 || select_name_question[0] == '�' && strlen(select_name_question) == 1 || select_name_question[0] == '�' && strlen(select_name_question) == 1) { // ���� ������ E, �� ���������� �����
                                            goto exit30;
                                        }

                                        else {
                                            while (TRUE) {
                                                // ��������� ������� ��������
                                                char text1[255] = "�������� 4 ������� �������� ����� ���� '|' ��� ��������.";
                                                char text2[255] = "��� ���� ��� ������� ��������� �������, ��� �������� ������� �������� ��� ����� '+' ��� ��������. ";
                                                char text3[255] = "������: 2+2=5|2+2=4+++|2+2=3|����� ��� �����???";
                                                    
                                                system("cls");
                                                printf("+-------------------------------------------------------------------------+\n");
                                                printf("|                            ��������� ���������                          |\n");
                                                printf("+-------------------------------------------------------------------------+\n");
                                                printf("|                                                                         |\n");
                                                printf("|                                                                         |\n");
                                                split_string(text1, 61);
                                                split_string(text2, 61);
                                                printf("|                                                                         |\n");
                                                split_string(text3, 61);
                                                printf("|                                                                         |\n");
                                                printf("|                                                                         |\n");
                                                printf("+-------------------------------------------------------------------------+\n");
                                                printf("|                               �������� - E                             |\n");
                                                printf("+-------------------------------------------------------------------------+\n");
                                                printf("\n");
                                                printf("������ ������� ��������: ");
                                                fgets(select_answer_question, 1000, stdin); 

                                                int len = strcspn(select_answer_question, "\n"); // ��������� ������ �������� ��� ����������� ����������� ����������
                                                select_answer_question[len] = '\0';

                                                if (select_answer_question[0] == 'E' && strlen(select_answer_question) == 1 || select_answer_question[0] == 'e' && strlen(select_answer_question) == 1 || select_answer_question[0] == '�' && strlen(select_answer_question) == 1 || select_answer_question[0] == '�' && strlen(select_answer_question) == 1) { // ���� ������ E, �� ���������� �����
                                                    return 0;
                                                }

                                                int count = 0; // ��������� ������� ����� "|"

                                                for (int i = 0; i < strlen(select_answer_question); i++) {
                                                    if (select_answer_question[i] == '|') {
                                                        count++;
                                                    }
                                                }

                                                if (count == 3) { // ���� ����� "|" ������� 3
                                                    char* token = strtok(select_answer_question, "|"); // ����������� ����� �� 4 ������� �������� �� ��������� ����� "|"
                                                    char* question1 = token;
                                                    token = strtok(NULL, "|");
                                                    char* question2 = token;
                                                    token = strtok(NULL, "|");
                                                    char* question3 = token;
                                                    token = strtok(NULL, "|");
                                                    char* question4 = token;

                                                    if (question1 != NULL && question2 != NULL && question3 != NULL && question4 != NULL) {

                                                        char query[256];
                                                        sprintf(query, "INSERT INTO '%s' (question, answer1, answer2, answer3, answer4) VALUES (?, ?, ?, ?, ?);", name); // ��������� ������ ��� ��������� �� ������ �������� �� �������(�����)

                                                        sqlite3_stmt *stmt;
                                                        rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);

                                                        sqlite3_bind_text(stmt, 1, select_name_question, -1, SQLITE_STATIC);
                                                        sqlite3_bind_text(stmt, 2, question1, -1, SQLITE_STATIC);
                                                        sqlite3_bind_text(stmt, 3, question2, -1, SQLITE_STATIC);
                                                        sqlite3_bind_text(stmt, 4, question3, -1, SQLITE_STATIC);
                                                        sqlite3_bind_text(stmt, 5, question4, -1, SQLITE_STATIC);

                                                        rc = sqlite3_step(stmt);
                                                        sqlite3_finalize(stmt);
                                                        break;
                                                    }
                                                }
                                            }
                                        } 
                                    }

                                    if (select_change_test[0] == '4' && strlen(select_change_test) == 1) {
                                        while (TRUE) {
                                            // ���� �������� �����
                                            system("cls");
                                            printf("+-------------------------------------------------------------------------+\n");
                                            printf("|                             ��������� ���������                         |\n");
                                            printf("+-------------------------------------------------------------------------+\n");
                                            printf("|                                                                         |\n");
                                            printf("|                                 ���������                               |\n");
                                            // ������ ������ ��� ���� ��� ������ ����� ����� ����� id
                                            sqlite3_stmt *stmt;
                                            rc = sqlite3_prepare_v2(db, "SELECT * FROM Custom_Tests", -1, &stmt, 0);
                                            int cols = sqlite3_column_count(stmt);

                                            while (sqlite3_step(stmt) == SQLITE_ROW) {
                                                const char *id = sqlite3_column_text(stmt, 0);
                                                if (strcmp(select_test_change, id)==0) {
                                                    const char *name_update = sqlite3_column_text(stmt, 1);

                                                    sqlite3_stmt *stmt;
                                                    char *sql_select_test = sqlite3_mprintf("SELECT * FROM '%s';", name_update);
                                                    rc = sqlite3_prepare_v2(db, sql_select_test, -1, &stmt, 0);
                                                    int cols = sqlite3_column_count(stmt);

                                                    while (sqlite3_step(stmt) == SQLITE_ROW) {
                                                        char *id = sqlite3_column_text(stmt, 0);
                                                        char *name = sqlite3_column_text(stmt, 1);
                                                        char *answer1 = sqlite3_column_text(stmt, 2);
                                                        char *answer2 = sqlite3_column_text(stmt, 3);
                                                        char *answer3 = sqlite3_column_text(stmt, 4);
                                                        char *answer4 = sqlite3_column_text(stmt, 5);
                                                        strcat(id, ". ");
                                                        strcat(id, name);
                                                        printf("|                                                                         |\n");
                                                        split_string(id, 61);
                                                        printf("|                                                                         |\n");
                                                        // ������ �� ������� �������� �����
                                                        char A[255] = "� ";
                                                        char B[255] = "� ";
                                                        char C[255] = "� ";
                                                        char D[255] = "� ";
                                                        strcat(A, answer1);
                                                        split_string(A, 61);
                                                        strcat(B, answer2);
                                                        split_string(B, 61);
                                                        strcat(C, answer3);
                                                        split_string(C, 61);
                                                        strcat(D, answer4);
                                                        split_string(D, 61);
                                                    }
                                                    printf("|                                                                         |\n");
                                                    printf("|                                                                         |\n");
                                                    printf("+-------------------------------------------------------------------------+\n");
                                                    printf("|                                 ����� - E                               |\n");
                                                    printf("+-------------------------------------------------------------------------+\n");
                                                    printf("\n������ ��������� �������� ���� �����: ");
                                                    char select_question[100];
                                                    scanf("%s", select_question);

                                                    if (select_question[0] == 'E' && strlen(select_question) == 1 || select_question[0] == 'e' && strlen(select_question) == 1 || select_question[0] == '�' && strlen(select_question) == 1 || select_question[0] == '�' && strlen(select_question) == 1) { // ���� ������ E, �� ���������� �����
                                                        goto exit31;
                                                    }
                                                    
                                                    // ��������, �� ������ ��������� ����� ���� ����� ������
                                                    sqlite3_stmt *stmt1;
                                                    rc = sqlite3_prepare_v2(db, sqlite3_mprintf("SELECT * FROM '%s'", name), -1, &stmt1, 0);
                                                    cols = sqlite3_column_count(stmt1);

                                                    while (sqlite3_step(stmt1) == SQLITE_ROW) {
                                                        const char *id = sqlite3_column_text(stmt1, 0);
                                                        if (strcmp(select_question, id)==0) {
                                                            // ��������� ��������� � �������
                                                            char sql_drop_in_table[256];
                                                            sprintf(sql_drop_in_table, "DELETE FROM '%s' WHERE id = %s;", name, select_question);
                                                            rc = sqlite3_exec(db, sql_drop_in_table, NULL, NULL, NULL);

                                                            goto exit32; // ���������� �����
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }

                                    if (select_change_test[0] == 'E' && strlen(select_change_test) == 1 || select_change_test[0] == 'e' && strlen(select_change_test) == 1 || select_change_test[0] == '�' && strlen(select_change_test) == 1 || select_change_test[0] == '�' && strlen(select_change_test) == 1) { // ���� ������ ��������� E, �� ���������� �����
                                        goto exit6;
                                    }

                                    else {
                                        ;
                                    }
                                }
                            }
                        }
                    }
                }     
            }


            if (select_constructor[0] == '3' && strlen(select_constructor) == 1) { // ��������� �����
                exit14:
                exit15:
                while (TRUE) {
                    // ���� ������ �����
                    system("cls");
                    printf("+-------------------------------------------------------------------------+\n");
                    printf("|                                 ���������                               |\n");
                    printf("+-------------------------------------------------------------------------+\n");
                    printf("|                                                                         |\n");
                    printf("|                               ������ �����                             |\n");
                    printf("|                                                                         |\n");

                    sqlite3_stmt *stmt;
                    rc = sqlite3_prepare_v2(db, "SELECT * FROM Custom_Tests", -1, &stmt, 0);
                    int cols = sqlite3_column_count(stmt);

                    while (sqlite3_step(stmt) == SQLITE_ROW) {
                        char *id = sqlite3_column_text(stmt, 0);
                        char *name = sqlite3_column_text(stmt, 1);
                        strcat(id, ".  ");
                        strcat(id, name);
                        split_string(id, 61);
                    }

                    printf("|                                                                         |\n");
                    printf("|                                                                         |\n");
                    printf("+-------------------------------------------------------------------------+\n");
                    printf("|                                 ����� - E                               |\n");
                    printf("+-------------------------------------------------------------------------+\n");
                    printf("\n������ ������� ���� �������� ���� �����: ");
                    char select_test_delete[100];
                    scanf("%s", select_test_delete);

                    if (select_test_delete[0] == 'E' && strlen(select_test_delete) == 1 || select_test_delete[0] == 'e' && strlen(select_test_delete) == 1 || select_test_delete[0] == '�' && strlen(select_test_delete) == 1 || select_test_delete[0] == '�' && strlen(select_test_delete) == 1) { // ���� ������ ��������� E, �� ���������� �����
                        goto exit13;
                    }

                    while (TRUE) {
                        // ��������, �� ������� ���� ����� ���� ����� ������
                        sqlite3_stmt *stmt;
                        rc = sqlite3_prepare_v2(db, "SELECT * FROM Custom_Tests", -1, &stmt, 0);
                        cols = sqlite3_column_count(stmt);

                        while (sqlite3_step(stmt) == SQLITE_ROW) {
                            const char *id = sqlite3_column_text(stmt, 0);
                            if (strcmp(select_test_delete, id)==0) {
                                // ������������ �� �� ��������� �����
                                char *name = sqlite3_column_text(stmt, 1);
                                system("cls");
                                printf("+-------------------------------------------------------------------------+\n");
                                printf("|                                 ���������                               |\n");
                                printf("+-------------------------------------------------------------------------+\n");
                                printf("|                                                                         |\n");
                                char text1[255] = "�� ����� ������ �������� ���� '";
                                strcat(text1, name);
                                strcat(text1, "'?");
                                split_string(text1, 61);
                                printf("|                                                                         |\n");
                                char text2[255] = "���� ��� �������� '���'.";
                                char text3[255] = "���� � - 'Ͳ'.";
                                split_string(text2, 61);
                                split_string(text3, 61);
                                printf("|                                                                         |\n");
                                printf("|                                                                         |\n");
                                printf("+-------------------------------------------------------------------------+\n");
                                printf("|                                 ����� - E                               |\n");
                                printf("+-------------------------------------------------------------------------+\n");
                                printf("\n������ �������: ");
                                char select_test_delete_confirm[100];
                                scanf("%s", select_test_delete_confirm);

                                if (strcmp(select_test_delete_confirm, "���")==0) { // ���� ������� ��������� 
                                    // ��������� �������(�����)
                                    char sql_drop[256];
                                    sprintf(sql_drop, "DROP TABLE '%s';", name);
                                    rc = sqlite3_exec(db, sql_drop, NULL, NULL, NULL);
                                    // ��������� ����� � ������� Custom_Tests(������ �����)
                                    char sql_drop_in_table[256];
                                    sprintf(sql_drop_in_table, "DELETE FROM Custom_Tests WHERE id = %s;", select_test_delete);
                                    rc = sqlite3_exec(db, sql_drop_in_table, NULL, NULL, NULL);

                                    goto exit15; // ���������� �����
                                }

                                if (strcmp(select_test_delete_confirm, "Ͳ")==0) { // ���� ������� ���������
                                    goto exit14; // ���������� �����
                                }
                            }
                        }                        
                    }   
                }
            }

            if (select_constructor[0] == '4' && strlen(select_constructor) == 1) { // ��� �����������
                while (TRUE) {
                    system("cls");
                    printf("+-------------------------------------------------------------------------+\n");
                    printf("|                              ��� �����������                            |\n");
                    printf("+-------------------------------------------------------------------------+\n");
                    printf("|                                                                         |\n");
                    char text[400] = "�� ��������� ������������ �� ������ ���������� ����� ����� �� ��������� �� � �������. ����������� ������� �� 100 �������� � 4 ������� ��������. �� ������ ���������� � �������� ��� �����, �������� �����, ��������� �� ������� ��������.";
                    split_string(text, 61);
                    printf("|                                                                         |\n");
                    char text1[400] = "���� ������ ��������� ����� ������ � ����� ����������� - ��� ���� �� ��� ������ �� ��������� ���� �����.";
                    split_string(text1, 61);
                    printf("|                                                                         |\n");
                    printf("+-------------------------------------------------------------------------+\n");
                    printf("|                                 ����� - E                               |\n");
                    printf("+-------------------------------------------------------------------------+\n");
                    printf("\n");
                    printf("���� �����: "); 

                    char select[100];
                    scanf("%s", &select);

                    if (select[0] == 'E' && strlen(select) == 1 || select[0] == 'e' && strlen(select) == 1 || select[0] == '�' && strlen(select) == 1 || select[0] == '�' && strlen(select) == 1) { // ���� ������ ��������� E, �� ���������� �����
                        break;
                    }
                                                        
                    else {
                        ;
                    }
                }
            }


            exit2:

            if (select_constructor[0] == 'E' && strlen(select_constructor) == 1 || select_constructor[0] == 'e' && strlen(select_constructor) == 1 || select_constructor[0] == '�' && strlen(select_constructor) == 1 || select_constructor[0] == '�' && strlen(select_constructor) == 1) { // ���� ������ ��������� E, �� ���������� �����
                return 0;
            }

            else {
                ;
            }
        }
    }





    int Ukr_NMT() // ���� ����� � ��������� ����
    {
        // ��������� ��� ��'�
        system("cls");
        printf("+-------------------------------------------+\n");
        printf("|                  ���� ��'�                |\n");
        printf("+-------------------------------------------+\n");
        printf("|                                           |\n");
        printf("|                                           |\n");
        printf("|                �� ��� �����?              |\n");
        printf("|                                           |\n");
        printf("|                                           |\n");
        printf("+-------------------------------------------+\n");
        printf("|                  ����� - E                |\n");
        printf("+-------------------------------------------+\n");
        printf("\n");
        printf("������ ���� ��'�: ");
        getchar();
        char name[1000];
        fgets(name, 1000, stdin);

        int len = strcspn(name, "\n"); // ��������� ������ �������� ��� ����������� ����������� ����������
        name[len] = '\0';

        if (name[0] == 'E' && strlen(name) == 1 || name[0] == 'e' && strlen(name) == 1 || name[0] == '�' && strlen(name) == 1 || name[0] == '�' && strlen(name) == 1) { // ���� ������ ��������� E, �� ���������� �����
            return 0;
        }

        system("cls");

        int test = 1; // ����������, �� ���� �� ��������� ����
        int score =0;

        char name_test[100] = "��������� ����";
        // ������ ������� � ��������� ����
        sqlite3_stmt *stmt;
        rc = sqlite3_prepare_v2(db, "SELECT * FROM Ukr", -1, &stmt, 0);
        int cols = sqlite3_column_count(stmt);

        
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            system("cls");
            // ��������� ������ ��� ������� ����
            char *id = sqlite3_column_text(stmt, 0);
            char *question_test = sqlite3_column_text(stmt, 1);
            char *answer1_test = sqlite3_column_text(stmt, 2);
            char *answer2_test = sqlite3_column_text(stmt, 3);
            char *answer3_test = sqlite3_column_text(stmt, 4);
            char *answer4_test = sqlite3_column_text(stmt, 5);
            char *answer5_test = sqlite3_column_text(stmt, 6);
            char *answer1 = sqlite3_column_text(stmt, 7);
            char *answer2 = sqlite3_column_text(stmt, 8);
            char *answer3 = sqlite3_column_text(stmt, 9);
            char *answer4 = sqlite3_column_text(stmt, 10);
            char *answer5 = sqlite3_column_text(stmt, 11);
            char *answer_true = sqlite3_column_text(stmt, 12);



            int width = 4;

            printf("+-----------------------------------------------------------------------------------------------------------+\n");
            printf("|                                       ��������� ���� | ��������� �%-*s                                   |\n", width, id);
            printf("+-----------------------------------------------------------------------------------------------------------+\n");
            printf("|                                                                                                           |\n");
            printf("|                                                                                                           |\n");
            split_string(question_test, 95);
            printf("|                                                                                                           |\n");
            printf("|                                                                                                           |\n"); 


            
            if (strcmp(id, "1") == 0 || strcmp(id, "2") == 0 || strcmp(id, "3") == 0 || strcmp(id, "4") == 0 || strcmp(id, "5") == 0 || strcmp(id, "6") == 0 || strcmp(id, "7") == 0 || strcmp(id, "8") == 0 || strcmp(id, "9") == 0 || strcmp(id, "10") == 0) { // ���� ����� ��������� �� 1 �� 10
                split_string(answer1_test, 95);
                split_string(answer2_test, 95);
                split_string(answer3_test, 95);
                split_string(answer4_test, 95);
                printf("|                                                                                                           |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("|                                         �������� ���������� - E                                          |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("\n");
                printf("������ �������: ");
                char answer[100];
                scanf("%s", answer);
                

                if (strlen(answer) == 1) { // ���� ������� ������� ������ �������
                    if (answer[0] == answer_true[0] || answer[0] == answer_true[1] || answer[0] == answer_true[2] || answer[0] == answer_true[3]) { // ���� ������� ���������
                        score++; // ������������ ���� ���
                    } 
                }
                if (answer[0] == 'E' && strlen(answer) == 1 || answer[0] == 'e' && strlen(answer) == 1 || answer[0] == '�' && strlen(answer) == 1 || answer[0] == '�' && strlen(answer) == 1) { // ���� ������ ��������� E, �� ��������� ����������
                    results_NMT(score, test, name, name_test); // �����e��� ���������� �� ���� ����������
                    return 0;
                }

            }


            if (strcmp(id, "11") == 0 || strcmp(id, "12") == 0 || strcmp(id, "13") == 0 || strcmp(id, "14") == 0 || strcmp(id, "15") == 0 || strcmp(id, "16") == 0 || strcmp(id, "17") == 0 || strcmp(id, "18") == 0 || strcmp(id, "19") == 0 || strcmp(id, "20") == 0 || strcmp(id, "21") == 0 || strcmp(id, "22") == 0 || strcmp(id, "23") == 0 || strcmp(id, "24") == 0 || strcmp(id, "25") == 0) { // ���� ����� ��������� �� 11 �� 25
                split_string(answer1_test, 95);
                split_string(answer2_test, 95);
                split_string(answer3_test, 95);
                split_string(answer4_test, 95);
                split_string(answer5_test, 95);
                printf("|                                                                                                           |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("|                                         �������� ���������� - E                                          |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("\n");
                printf("������ �������: ");
                char answer[100];
                scanf("%s", answer);


                if (strlen(answer) == 1) { // ���� ������� ������� ������ �������
                    if (answer[0] == answer_true[0] || answer[0] == answer_true[1] || answer[0] == answer_true[2] || answer[0] == answer_true[3]) { // ���� ������� ���������
                        score++; // ������������ ���� ���
                    } 
                }
                if (answer[0] == 'E' && strlen(answer) == 1 || answer[0] == 'e' && strlen(answer) == 1 || answer[0] == '�' && strlen(answer) == 1 || answer[0] == '�' && strlen(answer) == 1) { // ���� ������ ��������� E, �� ��������� ����������
                    results_NMT(score, test, name, name_test); // �����e��� ���������� �� ���� ����������
                    return 0;
                }
            }

            if (strcmp(id, "27") == 0) { // ���� ����� ��������� ������� 27
                split_string(answer1_test, 95);
                split_string(answer2_test, 95);
                split_string(answer3_test, 95);
                split_string(answer4_test, 95);
                split_string(answer5_test, 95);
                printf("|                                                                                                           |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("|                                         �������� ���������� - E                                          |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("\n");
                printf("������ ����� � ���������� �������: ");
                char answer[100];
                scanf("%s", answer);

                if  (answer[0] == answer_true[0] || answer[0] == answer_true[4] || answer[0] == answer_true[8] || answer[0] == answer_true[12]) { // ���� ����� ������� ���������
                    score++; // ������������ ���� ���
                }
                if  (answer[1] == answer_true[1] || answer[1] == answer_true[5] || answer[1] == answer_true[9] || answer[1] == answer_true[13]) { // ���� ����� ������� ���������
                    score++; // ������������ ���� ���
                }
                if  (answer[2] == answer_true[2] || answer[2] == answer_true[6] || answer[2] == answer_true[10] || answer[2] == answer_true[14]) { // ���� ����� ������� ���������
                    score++; // ������������ ���� ���
                }
                if  (answer[3] == answer_true[3] || answer[3] == answer_true[7] || answer[3] == answer_true[11] || answer[3] == answer_true[15]) { // ���� �������� ������� ���������
                    score++; // ������������ ���� ���
                }
                if (answer[0] == 'E' && strlen(answer) == 1 || answer[0] == 'e' && strlen(answer) == 1 || answer[0] == '�' && strlen(answer) == 1 || answer[0] == '�' && strlen(answer) == 1) { // ���� ������ ��������� E, �� ��������� ����������
                    results_NMT(score, test, name, name_test); // �����e��� ���������� �� ���� ����������
                    return 0;
                }
            }

            if (strcmp(id, "26") == 0 || strcmp(id, "28") == 0 || strcmp(id, "29") == 0 || strcmp(id, "30") == 0) { // ���� ����� ��������� ������� 26, 28-30
                split_string(answer1_test, 95);
                split_string(answer2_test, 95);
                split_string(answer3_test, 95);
                split_string(answer4_test, 95);
                printf("|                                                                                                           |\n");
                split_string(answer1, 95);
                split_string(answer2, 95);
                split_string(answer3, 95);
                split_string(answer4, 95);
                split_string(answer5, 95);
                printf("|                                                                                                           |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("|                                         �������� ���������� - E                                          |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("\n");
                printf("������ ����� � ���������� �������: ");
                char answer[100];
                scanf("%s", answer);

                if  (answer[0] == answer_true[0] || answer[0] == answer_true[4] || answer[0] == answer_true[8] || answer[0] == answer_true[12]) { // ���� ����� ������� ���������
                    score++; // ������������ ���� ���
                }
                if  (answer[1] == answer_true[1] || answer[1] == answer_true[5] || answer[1] == answer_true[9] || answer[1] == answer_true[13]) { // ���� ����� ������� ���������
                    score++; // ������������ ���� ���
                }
                if  (answer[2] == answer_true[2] || answer[2] == answer_true[6] || answer[2] == answer_true[10] || answer[2] == answer_true[14]) { // ���� ����� ������� ���������
                    score++; // ������������ ���� ���
                }
                if  (answer[3] == answer_true[3] || answer[3] == answer_true[7] || answer[3] == answer_true[11] || answer[3] == answer_true[15]) { // ���� �������� ������� ���������
                    score++; // ������������ ���� ���
                }
                if (answer[0] == 'E' && strlen(answer) == 1 || answer[0] == 'e' && strlen(answer) == 1 || answer[0] == '�' && strlen(answer) == 1 || answer[0] == '�' && strlen(answer) == 1) { // ���� ������ ��������� E, �� ��������� ����������
                    results_NMT(score, test, name, name_test); // �����e��� ���������� �� ���� ����������
                    return 0;
                }
            }
        }
        results_NMT(score, test, name, name_test); // �����e��� ���������� �� ���� ����������
    }


    int Math_NMT() // ���� ����� � ����������
    {
        // ��������� ��� ��'�
        system("cls");
        printf("+-------------------------------------------+\n");
        printf("|                  ���� ��'�                |\n");
        printf("+-------------------------------------------+\n");
        printf("|                                           |\n");
        printf("|                                           |\n");
        printf("|                �� ��� �����?              |\n");
        printf("|                                           |\n");
        printf("|                                           |\n");
        printf("+-------------------------------------------+\n");
        printf("|                  ����� - E                |\n");
        printf("+-------------------------------------------+\n");
        printf("\n");
        printf("������ ���� ��'�: ");
        getchar();
        char name[1000];
        fgets(name, 1000, stdin);

        // ��������� ������ �������� ��� ����������� ����������� ����������
        int len = strcspn(name, "\n");
        name[len] = '\0';

        if (name[0] == 'E' && strlen(name) == 1 || name[0] == 'e' && strlen(name) == 1 || name[0] == '�' && strlen(name) == 1 || name[0] == '�' && strlen(name) == 1) { // ���� ������ ��������� E, �� ���������� �����
            return 0;
        }

        system("cls");

        int test = 2; // ����������, �� ���� �� ����������
        int score =0;

        char name_test[100] = "����������";
        // ������ ������� � ����������
        sqlite3_stmt *stmt;
        rc = sqlite3_prepare_v2(db, "SELECT * FROM Math", -1, &stmt, 0);
        int cols = sqlite3_column_count(stmt);

        
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            // ��������� ������ ��� ������� ����
            system("cls");
            char *id = sqlite3_column_text(stmt, 0);
            char *question_test = sqlite3_column_text(stmt, 1);
            char *answer1_test = sqlite3_column_text(stmt, 2);
            char *answer2_test = sqlite3_column_text(stmt, 3);
            char *answer3_test = sqlite3_column_text(stmt, 4);
            char *answer4_test = sqlite3_column_text(stmt, 5);
            char *answer5_test = sqlite3_column_text(stmt, 6);
            char *answer1 = sqlite3_column_text(stmt, 7);
            char *answer2 = sqlite3_column_text(stmt, 8);
            char *answer3 = sqlite3_column_text(stmt, 9);
            char *answer4 = sqlite3_column_text(stmt, 10);
            char *answer5 = sqlite3_column_text(stmt, 11);
            char *answer_true = sqlite3_column_text(stmt, 12);



            int width = 4;

            printf("+-----------------------------------------------------------------------------------------------------------+\n");
            printf("|                                          ���������� | ��������� �%-*s                                     |\n", width, id);
            printf("+-----------------------------------------------------------------------------------------------------------+\n");
            printf("|                                                                                                           |\n");
            printf("|                                                                                                           |\n");
            split_string(question_test, 95);
            printf("|                                                                                                           |\n");
            printf("|                                                                                                           |\n"); 


            
            if (strcmp(id, "1") == 0 || strcmp(id, "2") == 0 || strcmp(id, "3") == 0 || strcmp(id, "4") == 0 || strcmp(id, "5") == 0 || strcmp(id, "6") == 0 || strcmp(id, "7") == 0 || strcmp(id, "8") == 0 || strcmp(id, "9") == 0 || strcmp(id, "10") == 0 || strcmp(id, "11") == 0 || strcmp(id, "12") == 0 || strcmp(id, "13") == 0 || strcmp(id, "14") == 0 || strcmp(id, "15") == 0) { // ���� ����� ��������� �� 1 �� 15
                split_string(answer1_test, 95);
                split_string(answer2_test, 95);
                split_string(answer3_test, 95);
                split_string(answer4_test, 95);
                split_string(answer5_test, 95);
                printf("|                                                                                                           |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("|                                         �������� ���������� - E                                          |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("\n");
                printf("������ �������: ");
                char answer[100];
                scanf("%s", answer);
                

                if (strlen(answer) == 1) { // ���� ������� ������� ������ �������
                    if (answer[0] == answer_true[0] || answer[0] == answer_true[1] || answer[0] == answer_true[2] || answer[0] == answer_true[3]) { // ���� ������� ���������
                        score++; // ������������ ���� ���
                    } 
                }
                if (answer[0] == 'E' && strlen(answer) == 1 || answer[0] == 'e' && strlen(answer) == 1 || answer[0] == '�' && strlen(answer) == 1 || answer[0] == '�' && strlen(answer) == 1) { // ���� ������ ��������� E, �� ��������� ����������
                    results_NMT(score, test, name, name_test); // �����e��� ���������� �� ���� ����������
                    return 0;
                }

            }


            if (strcmp(id, "16") == 0 || strcmp(id, "17") == 0 || strcmp(id, "18") == 0) { // ���� ����� ��������� �� 16 �� 18
                split_string(answer1_test, 95);
                split_string(answer2_test, 95);
                split_string(answer3_test, 95);
                printf("|                                                                                                           |\n");
                split_string(answer1, 95);
                split_string(answer2, 95);
                split_string(answer3, 95);
                split_string(answer4, 95);
                split_string(answer5, 95);
                printf("|                                                                                                           |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("|                                         �������� ���������� - E                                          |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("\n");
                printf("������ ����� � ���������� �������: ");
                char answer[100];
                scanf("%s", answer);


                if  (answer[0] == answer_true[0] || answer[0] == answer_true[3] || answer[0] == answer_true[6] || answer[0] == answer_true[9]) { // ���� ����� ������� ���������
                    score++; // ������������ ���� ���
                }
                if  (answer[1] == answer_true[1] || answer[1] == answer_true[4] || answer[1] == answer_true[7] || answer[1] == answer_true[10]) { // ���� ����� ������� ���������
                    score++; // ������������ ���� ���
                }
                if  (answer[2] == answer_true[2] || answer[2] == answer_true[5] || answer[2] == answer_true[8] || answer[2] == answer_true[11]) { // ���� ����� ������� ���������
                    score++; // ������������ ���� ���
                }
                if (answer[0] == 'E' && strlen(answer) == 1 || answer[0] == 'e' && strlen(answer) == 1 || answer[0] == '�' && strlen(answer) == 1 || answer[0] == '�' && strlen(answer) == 1) { // ���� ������ ��������� E, �� ��������� ����������
                    results_NMT(score, test, name, name_test); // �����e��� ���������� �� ���� ����������
                    return 0;
                }
            }

            if (strcmp(id, "19") == 0 || strcmp(id, "20") == 0 || strcmp(id, "21") == 0 || strcmp(id, "22") == 0) { // ���� ����� ��������� �� 19 �� 22
                printf("|      �������� ���� �����, ��� ��������. ���� ����� ������� �������������� ','.                           |\n");
                printf("|                                                                                                           |\n");
                printf("|                                                                                                           |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("|                                         �������� ���������� - E                                          |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("\n");
                printf("������ �����: ");
                char answer[100];
                scanf("%s", answer);

                if  (strcmp(answer, answer_true) == 0) { // ���� ����� ������� ���������
                    score = score + 2; // ������������ ��� ����
                }
                if (answer[0] == 'E' && strlen(answer) == 1 || answer[0] == 'e' && strlen(answer) == 1 || answer[0] == '�' && strlen(answer) == 1 || answer[0] == '�' && strlen(answer) == 1) { // ���� ������ ��������� E, �� ��������� ����������
                    results_NMT(score, test, name, name_test); // �����e��� ���������� �� ���� ����������
                    return 0;
                }
            }
        }
        results_NMT(score, test, name, name_test); // �����e��� ���������� �� ���� ����������
    }


    int History_NMT() // ���� ����� � ����� ������
    {
        // ��������� ��� ��'�
        system("cls");
        printf("+-------------------------------------------+\n");
        printf("|                  ���� ��'�                |\n");
        printf("+-------------------------------------------+\n");
        printf("|                                           |\n");
        printf("|                                           |\n");
        printf("|                �� ��� �����?              |\n");
        printf("|                                           |\n");
        printf("|                                           |\n");
        printf("+-------------------------------------------+\n");
        printf("|                  ����� - E                |\n");
        printf("+-------------------------------------------+\n");
        printf("\n");
        printf("������ ���� ��'�: ");
        getchar();
        char name[1000];
        fgets(name, 1000, stdin);

        // ��������� ������ �������� ��� ����������� ����������� ����������
        int len = strcspn(name, "\n");
        name[len] = '\0';

        if (name[0] == 'E' && strlen(name) == 1 || name[0] == 'e' && strlen(name) == 1 || name[0] == '�' && strlen(name) == 1 || name[0] == '�' && strlen(name) == 1) { // ���� ������ ��������� E, �� ��������� ����������
            return 0;
        }

        system("cls");

        int test = 3; // ����������, �� ���� �� ������ ������
        int score =0;

        char name_test[100] = "������ ������";
        // ������ ������� � ����� ������
        sqlite3_stmt *stmt;
        rc = sqlite3_prepare_v2(db, "SELECT * FROM History", -1, &stmt, 0);
        int cols = sqlite3_column_count(stmt);

        
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            // ��������� ������ ��� ������� ����
            system("cls");
            char *id = sqlite3_column_text(stmt, 0);
            char *question_test = sqlite3_column_text(stmt, 1);
            char *answer1_test = sqlite3_column_text(stmt, 2);
            char *answer2_test = sqlite3_column_text(stmt, 3);
            char *answer3_test = sqlite3_column_text(stmt, 4);
            char *answer4_test = sqlite3_column_text(stmt, 5);
            char *answer5_test = sqlite3_column_text(stmt, 6);
            char *answer6_test = sqlite3_column_text(stmt, 7);
            char *answer7_test = sqlite3_column_text(stmt, 8);
            char *answer1 = sqlite3_column_text(stmt, 9);
            char *answer2 = sqlite3_column_text(stmt, 10);
            char *answer3 = sqlite3_column_text(stmt, 11);
            char *answer4 = sqlite3_column_text(stmt, 12);
            char *answer5 = sqlite3_column_text(stmt, 13);
            char *answer_true = sqlite3_column_text(stmt, 14);



            int width = 4;

            printf("+-----------------------------------------------------------------------------------------------------------+\n");
            printf("|                                       ������ ������ | ��������� �%-*s                                   |\n", width, id);
            printf("+-----------------------------------------------------------------------------------------------------------+\n");
            printf("|                                                                                                           |\n");
            printf("|                                                                                                           |\n");
            split_string(question_test, 95);
            printf("|                                                                                                           |\n");
            printf("|                                                                                                           |\n"); 


            
            if (strcmp(id, "1") == 0 || strcmp(id, "2") == 0 || strcmp(id, "3") == 0 || strcmp(id, "4") == 0 || strcmp(id, "5") == 0 || strcmp(id, "6") == 0 || strcmp(id, "7") == 0 || strcmp(id, "8") == 0 || strcmp(id, "9") == 0 || strcmp(id, "10") == 0 || strcmp(id, "11") == 0 || strcmp(id, "12") == 0 || strcmp(id, "13") == 0 || strcmp(id, "14") == 0 || strcmp(id, "15") == 0 || strcmp(id, "16") == 0 || strcmp(id, "17") == 0 || strcmp(id, "18") == 0 || strcmp(id, "19") == 0 || strcmp(id, "20") == 0) { // ���� ����� ��������� �� 1 �� 20
                split_string(answer1_test, 95);
                split_string(answer2_test, 95);
                split_string(answer3_test, 95);
                split_string(answer4_test, 95);
                printf("|                                                                                                           |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("|                                         �������� ���������� - E                                          |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("\n");
                printf("������ �������: ");
                char answer[100];
                scanf("%s", answer);
                

                if (strlen(answer) == 1) { // ���� ������� ������� ������ �������
                    if (answer[0] == answer_true[0] || answer[0] == answer_true[1] || answer[0] == answer_true[2] || answer[0] == answer_true[3]) { // ���� ������� ���������
                        score++; // ������������ ���� ���
                    } 
                }
                if (answer[0] == 'E' && strlen(answer) == 1 || answer[0] == 'e' && strlen(answer) == 1 || answer[0] == '�' && strlen(answer) == 1 || answer[0] == '�' && strlen(answer) == 1) { // ���� ������ ��������� E, �� ��������� ����������
                    results_NMT(score, test, name, name_test); // �����e��� ���������� �� ���� ����������
                    return 0;
                }
            }


            if (strcmp(id, "21") == 0 || strcmp(id, "22") == 0 || strcmp(id, "23") == 0 || strcmp(id, "24") == 0) { // ���� ����� ��������� �� 21 �� 24
                split_string(answer1_test, 95);
                split_string(answer2_test, 95);
                split_string(answer3_test, 95);
                split_string(answer4_test, 95);
                printf("|                                                                                                           |\n");
                split_string(answer1, 95);
                split_string(answer2, 95);
                split_string(answer3, 95);
                split_string(answer4, 95);
                split_string(answer5, 95);
                printf("|                                                                                                           |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("|                                         �������� ���������� - E                                          |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("\n");
                printf("������ ����� � ���������� �������: ");
                char answer[100];
                scanf("%s", answer);

                if  (answer[0] == answer_true[0] || answer[0] == answer_true[4] || answer[0] == answer_true[8] || answer[0] == answer_true[12]) { // ���� ����� ������� ���������
                    score++; // ������������ ���� ���
                }
                if  (answer[1] == answer_true[1] || answer[1] == answer_true[5] || answer[1] == answer_true[9] || answer[1] == answer_true[13]) { // ���� ����� ������� ���������
                    score++; // ������������ ���� ���
                }
                if  (answer[2] == answer_true[2] || answer[2] == answer_true[6] || answer[2] == answer_true[10] || answer[2] == answer_true[14]) { // ���� ����� ������� ���������
                    score++; // ������������ ���� ���
                }
                if  (answer[3] == answer_true[3] || answer[3] == answer_true[7] || answer[3] == answer_true[11] || answer[3] == answer_true[15]) { // ���� �������� ������� ���������
                    score++; // ������������ ���� ���
                }
                if (answer[0] == 'E' && strlen(answer) == 1 || answer[0] == 'e' && strlen(answer) == 1 || answer[0] == '�' && strlen(answer) == 1 || answer[0] == '�' && strlen(answer) == 1) { // ���� ������ ��������� E, �� ��������� ����������
                    results_NMT(score, test, name, name_test); // �����e��� ���������� �� ���� ����������
                    return 0;
                }
            }


            if (strcmp(id, "25") == 0 || strcmp(id, "26") == 0 || strcmp(id, "27") == 0) { // ���� ����� ��������� �� 25 �� 27
                split_string(answer1_test, 95);
                split_string(answer2_test, 95);
                split_string(answer3_test, 95);
                split_string(answer4_test, 95);
                printf("|                                                                                                           |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("|                                         �������� ���������� - E                                          |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("\n");
                printf("������ ����� � ���������� �������: ");
                char answer[100];
                scanf("%s", answer);

                int i=0;

                if  (answer[0] == answer_true[0] || answer[0] == answer_true[4] || answer[0] == answer_true[8] || answer[0] == answer_true[12]) { // ���� ����� ������� ���������
                    score++; // ������������ ������ ���� ���
                    i++; // ������������ ������ ���� ���
                }
                if  (answer[1] == answer_true[1] || answer[1] == answer_true[5] || answer[1] == answer_true[9] || answer[1] == answer_true[13]) { // ���� ����� ������� ���������
                    score++; // ������������ ������ ���� ���
                    i++; // ������������ ������ ���� ���
                }
                if  (answer[2] == answer_true[2] || answer[2] == answer_true[6] || answer[2] == answer_true[10] || answer[2] == answer_true[14]) { // ���� ����� ������� ���������
                    score++; // ������������ ������ ���� ���
                    i++; // ������������ ������ ���� ���
                }
                if  (answer[3] == answer_true[3] || answer[3] == answer_true[7] || answer[3] == answer_true[11] || answer[3] == answer_true[15]) { // ���� �������� ������� ���������
                    score++; // ������������ ������ ���� ���
                    i++; // ������������ ������ ���� ���
                }
                if (answer[0] == 'E' && strlen(answer) == 1 || answer[0] == 'e' && strlen(answer) == 1 || answer[0] == '�' && strlen(answer) == 1 || answer[0] == '�' && strlen(answer) == 1) { // ���� ������ ��������� E, �� ��������� ����������
                    results_NMT(score, test, name, name_test); // �����e��� ���������� �� ���� ����������
                    return 0;
                }
                // ������������ ���������� ���
                if (i >= 1) {
                    score = score - 1;
                }
            }


            if (strcmp(id, "28") == 0 || strcmp(id, "29") == 0 || strcmp(id, "30") == 0) { // ���� ����� ��������� �� 28 �� 30
                split_string(answer1_test, 95);
                split_string(answer2_test, 95);
                split_string(answer3_test, 95);
                split_string(answer4_test, 95);
                split_string(answer5_test, 95);
                split_string(answer6_test, 95);
                split_string(answer7_test, 95);
                printf("|                                                                                                           |\n");
                printf("|      ������� ���� 3 ������(�����) � ���������� ������� ��� ��������, ��� � �.�.(���������, 267)     |\n");
                printf("|                                                                                                           |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("|                                         �������� ���������� - E                                          |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("\n");
                printf("������ �������: ");
                char answer[100];
                scanf("%s", answer);


                if (answer[0] == answer_true[0]) { // ���� ����� ������� ���������
                    score++; // ������������ ���� ���
                }
                if (answer[1] == answer_true[1]) { // ���� ����� ������� ���������
                    score++; // ������������ ���� ���
                }
                if (answer[2] == answer_true[2]) { // ���� ����� ������� ���������
                    score++; // ������������ ���� ���
                } 
                if (answer[0] == 'E' && strlen(answer) == 1 || answer[0] == 'e' && strlen(answer) == 1 || answer[0] == '�' && strlen(answer) == 1 || answer[0] == '�' && strlen(answer) == 1) { // ���� ������ ��������� E, �� ��������� ����������
                    results_NMT(score, test, name, name_test); // �����e��� ���������� �� ���� ����������
                    return 0;
                }
            }
        }
        results_NMT(score, test, name, name_test); // ��������� ���������� �� ���� ����������
    }




    int choice_of_test_custom() // �������, ��� ������� �� ���� ������ ������� ����� �� �������� ��
    {
        exit20:
        while (TRUE) {
            // ���� ������ ������� �����
            system("cls");
            printf("+-------------------------------------------------------------------------+\n");
            printf("|                               ����Ͳ �����                              |\n");
            printf("+-------------------------------------------------------------------------+\n");
            printf("|                                                                         |\n");
            printf("|                               ������ �����                             |\n");
            printf("|                                                                         |\n");
            // ������ ������� ������� �����
            sqlite3_stmt *stmt;
            rc = sqlite3_prepare_v2(db, "SELECT * FROM Custom_Tests", -1, &stmt, 0);
            int cols = sqlite3_column_count(stmt);

            while (sqlite3_step(stmt) == SQLITE_ROW) {
                char *id = sqlite3_column_text(stmt, 0);
                char *name = sqlite3_column_text(stmt, 1);
                strcat(id, ".  ");
                strcat(id, name);
                split_string(id, 61);
            }
            sqlite3_finalize(stmt);

            printf("|                                                                         |\n");
            printf("|                                                                         |\n");
            printf("+-------------------------------------------------------------------------+\n");
            printf("|                                 ����� - E                               |\n");
            printf("+-------------------------------------------------------------------------+\n");
            printf("\n������ ������� ���� �������� ���� �����: ");
            char select_custom_test[100];
            scanf("%s", select_custom_test);

            if (select_custom_test[0] == 'E' && strlen(select_custom_test) == 1 || select_custom_test[0] == 'e' && strlen(select_custom_test) == 1 || select_custom_test[0] == '�' && strlen(select_custom_test) == 1 || select_custom_test[0] == '�' && strlen(select_custom_test) == 1) { // ���� ������ ��������� E, �� ���������� �����
                return 0;
            }
            // ������� �� �� ������� ���� � � ��� ����� ����� ������
            sqlite3_stmt *stmt1;
            rc = sqlite3_prepare_v2(db, "SELECT * FROM Custom_Tests", -1, &stmt1, 0);
            cols = sqlite3_column_count(stmt1);

            while (sqlite3_step(stmt1) == SQLITE_ROW) {
                char *id = sqlite3_column_text(stmt1, 0);
                if (strcmp(id, select_custom_test)==0) { // ���� ������� ���� � � ������� 
                    char *name = sqlite3_column_text(stmt1, 1);
                    // ������ �������� �����
                    sqlite3_stmt *stmt2;
                    char* query = NULL;
                    int query_len = 0;

                    query_len = snprintf(NULL, 0, "SELECT * FROM '%s'", name);
                    query = malloc(query_len + 1);
                    sprintf(query, "SELECT * FROM '%s'", name);

                    rc = sqlite3_prepare_v2(db, query, -1, &stmt2, 0);

                    free(query);

                    cols = sqlite3_column_count(stmt2);
                    // ����� �� ��'�'
                    system("cls");
                    printf("+-------------------------------------------+\n");
                    printf("|                  ���� ��'�                |\n");
                    printf("+-------------------------------------------+\n");
                    printf("|                                           |\n");
                    printf("|                                           |\n");
                    printf("|                �� ��� �����?              |\n");
                    printf("|                                           |\n");
                    printf("|                                           |\n");
                    printf("+-------------------------------------------+\n");
                    printf("|                  ����� - E                |\n");
                    printf("+-------------------------------------------+\n");
                    printf("\n");
                    printf("������ ���� ��'�: ");
                    getchar();
                    char name_user[1000];
                    fgets(name_user, 1000, stdin);

                    // ��������� ������ �������� ��� ����������� ����������� ����������
                    int len = strcspn(name_user, "\n");
                    name_user[len] = '\0';

                    if (name_user[0] == 'E' && strlen(name_user) == 1 || name_user[0] == 'e' && strlen(name_user) == 1 || name_user[0] == '�' && strlen(name_user) == 1 || name_user[0] == '�' && strlen(name_user) == 1) { // ���� ������ ��������� E, �� ���������� �����
                        goto exit20;
                    }

                    int width = 4;
                    int score = 0;

                    while (sqlite3_step(stmt2) == SQLITE_ROW) {
                        // ��������� ������ ��� ������� ����
                        char *id = sqlite3_column_text(stmt2, 0);
                        char *question = sqlite3_column_text(stmt2, 1);
                        char *answer1 = sqlite3_column_text(stmt2, 2);
                        char *answer2 = sqlite3_column_text(stmt2, 3);
                        char *answer3 = sqlite3_column_text(stmt2, 4);
                        char *answer4 = sqlite3_column_text(stmt2, 5);

                        // ��������� ���� ��� ������� ����������� ������� ��������
                        char A[255] = "� ";
                        char B[255] = "� ";
                        char C[255] = "� ";
                        char D[255] = "� ";
                        strcat(A, answer1);
                        strcat(B, answer2);
                        strcat(C, answer3);
                        strcat(D, answer4);
                        // ������� ����� �� ���� � ����� "+++" ������� ����, ��� �� ���������� ��������� �������
                        char* substr = "+++";
                        char* match_A = strstr(A, substr);
                        if (match_A) {
                            memmove(match_A, match_A + strlen(substr), strlen(match_A + strlen(substr)) + 1);
                        }
                        char* match_B = strstr(B, substr);
                        if (match_B) {
                            memmove(match_B, match_B + strlen(substr), strlen(match_B + strlen(substr)) + 1);
                        }
                        char* match_C = strstr(C, substr);
                        if (match_C) {
                            memmove(match_C, match_C + strlen(substr), strlen(match_C + strlen(substr)) + 1);
                        }
                        char* match_D = strstr(D, substr);
                        if (match_D) {
                            memmove(match_D, match_D + strlen(substr), strlen(match_D + strlen(substr)) + 1);
                        }
                        // ���� ���������
                        system("cls");

                        printf("+-------------------------------------------------------------------------+\n");
                        printf("|                               ��������� �%-*s                           |\n", width, id);
                        printf("+-------------------------------------------------------------------------+\n");
                        printf("|                                                                         |\n");
                        split_string(question, 61);
                        printf("|                                                                         |\n");
                        split_string(A, 61);
                        split_string(B, 61);
                        split_string(C, 61);
                        split_string(D, 61);
                        printf("|                                                                         |\n");
                        printf("|                                                                         |\n");
                        printf("+-------------------------------------------------------------------------+\n");
                        printf("|                         �������� ���������� - E                        |\n");
                        printf("+-------------------------------------------------------------------------+\n");
                        printf("\n");
                        printf("������ �������: ");
                        char answer[100];
                        scanf("%s", answer);

                        // �������, �� ������� �������� ����� �� ���� ������� ���������
                        if (strcmp(answer, "�")==0 || strcmp(answer, "�")==0 || strcmp(answer, "F")==0 || strcmp(answer, "f")==0) {
                            char* answer_A = strstr(answer1, substr);
                            if (answer_A) {
                                score++; // ������������ ���� ���
                            }
                        }

                        if (strcmp(answer, "�")==0 || strcmp(answer, "�")==0 || strcmp(answer, "<")==0 || strcmp(answer, ",")==0) {
                            char* answer_B = strstr(answer2, substr);
                            if (answer_B) {
                                score++; // ������������ ���� ���
                            }
                        }

                        if (strcmp(answer, "�")==0 || strcmp(answer, "�")==0 || strcmp(answer, "D")==0 || strcmp(answer, "d")==0) {
                            char* answer_C = strstr(answer3, substr);
                            if (answer_C) {
                                score++; // ������������ ���� ���
                            }
                        }

                        if (strcmp(answer, "�")==0 || strcmp(answer, "�")==0 || strcmp(answer, "U")==0 || strcmp(answer, "u")==0) {
                            char* answer_D = strstr(answer4, substr);
                            if (answer_D!=0) {   
                                score++; // ������������ ���� ���
                            }
                        }

                        if (answer[0] == 'E' && strlen(answer) == 1 || answer[0] == 'e' && strlen(answer) == 1 || answer[0] == '�' && strlen(answer) == 1 || answer[0] == '�' && strlen(answer) == 1) { // ���� ������ ��������� E, �� ��������� ����������
                            results_custom_tests(score, name_user, name); // �����e��� ���������� �� ���� ����������
                            return 0;
                        }
                    }
                    results_custom_tests(score, name_user, name); // �����e��� ���������� �� ���� ����������
                    return 0;
                }
            }
        }
    }


    int about_program() { // �������, ��� �������� ���������� ��� ��������
        while (TRUE) {
            system("cls");
            printf("+-------------------------------------------------------------------------+\n");
            printf("|                                ��� ��������                             |\n");
            printf("+-------------------------------------------------------------------------+\n");
            printf("|                                                                         |\n");
            char text[400] = "�������� ���� ���������� ��������� 25 ����� - ��������� ������ ���������� ����� ������������� �. �������� ����� �������� � ���������� ����� �� ��������� �����. � ������� ��� �������� �� ������ ����� � ������ ���-2023 � ��������� ����, ���������� �� ����� ������. ��� ����, �������� �� �����������, �� ��������� ����� ����� ���������� ����� �����.";
            split_string(text, 61);
            printf("|                                                                         |\n");
            printf("+-------------------------------------------------------------------------+\n");
            printf("|                                  ���� - E                               |\n");
            printf("+-------------------------------------------------------------------------+\n");
            printf("\n");
            printf("���� �����: "); 

            char select[100];
            scanf("%s", &select);

            if (select[0] == 'E' && strlen(select) == 1 || select[0] == 'e' && strlen(select) == 1 || select[0] == '�' && strlen(select) == 1 || select[0] == '�' && strlen(select) == 1) { // ���� ������ ��������� E, �� ���������� �����
                return 0;
            }
                                                
            else {
                ;
            }
        }
        
    }

    int about_NMT() { // �������, ��� �������� �������� ��� ��� ����������
        while (TRUE) {
            system("cls");
            printf("+-------------------------------------------------------------------------+\n");
            printf("|                                  ��� ���                                |\n");
            printf("+-------------------------------------------------------------------------+\n");
            printf("|                                                                         |\n");
            char text[400] = "�������� �� �� ������ ����� � ��������� ����, ���������� �� ����� ������ � ������ ���-2023.";
            split_string(text, 61);
            printf("|                                                                         |\n");
            printf("|                                                                         |\n");
            char text1[400] = "��������� ����";
            split_string(text1, 61);
            printf("|                                                                         |\n");
            char text2[400] = "���� � ��������� ���� �� 30 �������. � ��� 10 ������� �� ���� ��������� ������� � ��������(0 ��� 1 ���), 15 � �� ���� ��������� ������� � �'���(0 ��� 1 ���), � 5 � �� ������������ ����������(0, 1, 2, 3 ��� 4 ����).";
            split_string(text2, 61);
            printf("|                                                                         |\n");
            printf("|                                                                         |\n");
            char text3[400] = "����������";
            split_string(text3, 61);
            printf("|                                                                         |\n");
            char text4[400] = "���� � ���������� �� 22 ��������. � ��� - 15 �����(0 ��� 1 ���), 3 �������� �� ������������ ����������(0, 1, 2 ��� 3 ����), �� 4 ��������, �� ������� ������� �������(0 ��� 2 ����).";
            split_string(text4, 61);
            printf("|                                                                         |\n");
            printf("|                                                                         |\n");
            char text5[400] = "������ ������";
            split_string(text5, 61);
            printf("|                                                                         |\n");
            char text6[400] = "���� � ����� ������ �� 30 �������. � ��� - 20 ����� � ���� ���������� ��������(0 ��� 1 ���), 4 �������� �� ������������ ����������(0, 1, 2, 3 ��� 4 ����), 3 - �� ������������ ����������� �����������(0, 1, 2 ��� 3 ����) �� 3 �������� � ������� ����� ���������� �������� �� ���� ��������������(0, 1, 2 ��� 3 ����).";
            split_string(text6, 61);
            printf("|                                                                         |\n");
            printf("+-------------------------------------------------------------------------+\n");
            printf("|                                 ����� - E                               |\n");
            printf("+-------------------------------------------------------------------------+\n");
            printf("\n");
            printf("���� �����: "); 

            char select[100];
            scanf("%s", &select);

            if (select[0] == 'E' && strlen(select) == 1 || select[0] == 'e' && strlen(select) == 1 || select[0] == '�' && strlen(select) == 1 || select[0] == '�' && strlen(select) == 1) { // ���� ������ ��������� E, �� ���������� �����
                return 0;
            }
                                                                    
            else {
                ;
            }
        }
    }






    // ��������� ��������� ���� �� ��������� ����� ����� ������������ �� ��������� �������
    while (TRUE) {
        menu(); // ���� ����
        printf("\n");
        printf("���� �����: ");
        // ���� ��� ������ �������� ������
        char select[100];
        scanf("%s", &select);

        if (select[0] == '1' && strlen(select) == 1) { // ���� �������� ������ ������� 1
            
            // ���� ������� ����� ������ ����
            while (TRUE) {
                system("cls");
                printf("+-------------------------------------------+\n");
                printf("|                 ����� �����               |\n");
                printf("+-------------------------------------------+\n");
                printf("|                                           |\n");
                printf("|              ��� ����� - 1                |\n");
                printf("|              ����� ����� - 2             |\n");
                printf("|                                           |\n");
                printf("|              ���� - E                     |\n");
                printf("|                                           |\n");
                printf("+-------------------------------------------+\n");
                printf("\n");
                printf("���� �����: ");
                // ���� ��� ������ �������� ������
                char select_choice_of_test[100];
                scanf("%s", &select_choice_of_test);

                if (select_choice_of_test[0] == '1' && strlen(select_choice_of_test) == 1) { // ���� �������� ������ ������� 1
                    // ���� ���� ��� ������ ��� �����
                    while (TRUE) {
                        system("cls");
                        printf("+-------------------------------------------+\n");
                        printf("|                ��� ����������             |\n");
                        printf("+-------------------------------------------+\n");
                        printf("|                                           |\n");
                        printf("|              ��������� ���� - 1          |\n");
                        printf("|              ���������� - 2               |\n");
                        printf("|              ������ ������ - 3          |\n");
                        printf("|                                           |\n");
                        printf("|              ������ ��� ��� - 4           |\n");
                        printf("|              ����� - E                    |\n");
                        printf("|                                           |\n");
                        printf("+-------------------------------------------+\n");
                        printf("\n");
                        printf("���� �����: ");
                        // ���� ��� ������ �������� ������
                        char select_choice_of_test_NMT[100];
                        scanf("%s", &select_choice_of_test_NMT);

                        if (select_choice_of_test_NMT[0] == '1' && strlen(select_choice_of_test_NMT) == 1) { // ���� �������� ������ ������� 1
                            Ukr_NMT(); // ���� ����� � ��������� ����
                        }

                        if (select_choice_of_test_NMT[0] == '2' && strlen(select_choice_of_test_NMT) == 1) { // ���� �������� ������ ������� 2
                            Math_NMT(); // ���� ����� � ����������
                        }

                        if (select_choice_of_test_NMT[0] == '3' && strlen(select_choice_of_test_NMT) == 1) { // ���� �������� ������ ������� 3
                            History_NMT(); // ���� ����� � ����� ������
                        }
                        if (select_choice_of_test_NMT[0] == '4' && strlen(select_choice_of_test_NMT) == 1) { // ���� �������� ������ ������� 4
                            about_NMT(); // ���� ���������� ��� ��� ���������� 
                        }
                        if (select_choice_of_test_NMT[0] == 'E' && strlen(select_choice_of_test_NMT) == 1 || select_choice_of_test_NMT[0] == 'e' && strlen(select_choice_of_test_NMT) == 1 || select_choice_of_test_NMT[0] == '�' && strlen(select_choice_of_test_NMT) == 1 || select_choice_of_test_NMT[0] == '�' && strlen(select_choice_of_test_NMT) == 1) { // ���� ������ ��������� E, �� ���������� �����
                            break;
                        }
                                            
                        else {
                            ;
                        }
                    }
                    


                }

                if (select_choice_of_test[0] == '2' && strlen(select_choice_of_test) == 1) { // ���� �������� ������ ������� 2
                    choice_of_test_custom(); // ���� ����� ���� ������� �����
                }
                       
                if (select_choice_of_test[0] == 'E' && strlen(select_choice_of_test) == 1 || select_choice_of_test[0] == 'e' && strlen(select_choice_of_test) == 1 || select_choice_of_test[0] == '�' && strlen(select_choice_of_test) == 1 || select_choice_of_test[0] == '�' && strlen(select_choice_of_test) == 1) { // ���� ������ ��������� E, �� ���������� �����
                    break;
                }
                                        
                else {
                    ;
                }
            }
        }
        if (select[0] == '2' && strlen(select) == 1) { // ���� �������� ������ ������� 2
            results(); // ���� ����������
        }
            
        if (select[0] == '3' && strlen(select) == 1) { // ���� �������� ������ ������� 3
            constructor(); // ���� ������������
        }

        if (select[0] == '4' && strlen(select) == 1) { // ���� �������� ������ ������� 4
            about_program(); // ���� ���������� ��� ��������
        }

        if (select[0] == 'E' && strlen(select) == 1 || select[0] == 'e' && strlen(select) == 1 || select[0] == '�' && strlen(select) == 1 || select[0] == '�' && strlen(select) == 1) { // ���� ������ ��������� E, �� ���������� �����
            exit(0);
        }

        else {
            ;
        }
    }

    return 0;
}