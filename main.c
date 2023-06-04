#include <stdio.h>  // підключення бібліотек
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <sqlite3.h>
#include <math.h>


void split_string(char *str, int len) {  // функція, яка розподіляє змінну по заданої ширині на рядки та ствить "|", щоб утворився гарний інтерфейс.
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
    SetConsoleCP(1251); // встановлення кодингу 1251 для корректного відображення української мови
    SetConsoleOutputCP(1251);


    sqlite3 *db; // підключення бази даних
    int rc = sqlite3_open("database.db", &db);


    char* sql_create = "CREATE TABLE IF NOT EXISTS Custom_Tests (id INTEGER PRIMARY KEY, name TEXT);"; // створення таблиці для списку власних тестів
    rc = sqlite3_exec(db, sql_create, NULL, NULL, NULL);

    sql_create = "CREATE TABLE IF NOT EXISTS results (id INTEGER PRIMARY KEY, name_test TEXT, name_user TEXT, max_id TEXT, score TEXT, score_200 TEXT, score_12 TEXT);"; // створення таблиці для збереження результатів
    rc = sqlite3_exec(db, sql_create, NULL, NULL, NULL);







    sql_create = "CREATE TABLE IF NOT EXISTS Ukr (id INTEGER PRIMARY KEY, question_test TEXT, answer1_test TEXT, answer2_test TEXT, answer3_test TEXT, answer4_test TEXT, answer5_test TEXT, answer1 TEXT, answer2 TEXT, answer3 TEXT, answer4 TEXT, answer5 TEXT, answer_true TEXT);"; // створення таблиць для НМТ тестування
    rc = sqlite3_exec(db, sql_create, NULL, NULL, NULL);
    sql_create = "CREATE TABLE IF NOT EXISTS Math (id INTEGER PRIMARY KEY, question_test TEXT, answer1_test TEXT, answer2_test TEXT, answer3_test TEXT, answer4_test TEXT, answer5_test TEXT, answer1 TEXT, answer2 TEXT, answer3 TEXT, answer4 TEXT, answer5 TEXT, answer_true TEXT);";
    rc = sqlite3_exec(db, sql_create, NULL, NULL, NULL);
    sql_create = "CREATE TABLE IF NOT EXISTS History (id INTEGER PRIMARY KEY, question_test TEXT, answer1_test TEXT, answer2_test TEXT, answer3_test TEXT, answer4_test TEXT, answer5_test TEXT, answer6_test TEXT, answer7_test TEXT, answer1 TEXT, answer2 TEXT, answer3 TEXT, answer4 TEXT, answer5 TEXT, answer_true TEXT);";
    rc = sqlite3_exec(db, sql_create, NULL, NULL, NULL);

    sql_create = "CREATE TABLE IF NOT EXISTS Score_Ukr (id INTEGER, score INTEGER);"; // створення таблиць для 200 бальної системи
    rc = sqlite3_exec(db, sql_create, NULL, NULL, NULL);
    sql_create = "CREATE TABLE IF NOT EXISTS Score_Math (id INTEGER, score INTEGER);";
    rc = sqlite3_exec(db, sql_create, NULL, NULL, NULL);
    sql_create = "CREATE TABLE IF NOT EXISTS Score_History (id INTEGER, score INTEGER);";
    rc = sqlite3_exec(db, sql_create, NULL, NULL, NULL);



    int menu() // функція, яка визиває головне меню
    {
        system("cls");
        printf("+-------------------------------------------+\n");
        printf("|                    МЕНЮ                   |\n");
        printf("+-------------------------------------------+\n");
        printf("|                                           |\n");
        printf("|              Пройти тест - 1              |\n");
        printf("|              Результати тестувань - 2     |\n");
        printf("|              Конструктор - 3              |\n");
        printf("|                                           |\n");
        printf("|              Про програму - 4             |\n");
        printf("|              Вихід - E                    |\n");
        printf("|                                           |\n");
        printf("+-------------------------------------------+\n");
    }

    int results_NMT(int score, int test, char name[1000], char name_test[1000]) // функція, яка виводить результати тестувань для НМТ тестування
    {
        int width_name_test = 15; // визначення ширини рядків для корректного відображення інтерфейсу
        int width_name = 66;
        int width_score = 41;
        int width_score_200 = 33;
        int width_score_12 = 34;

        if (test == 1) { // якщо тест українська мова
            int score_12 = round((float)score/45.0*12); // переведення в 12 бальну систему

            sqlite3_stmt *stmt;
            rc = sqlite3_prepare_v2(db, "SELECT * FROM Score_Ukr", -1, &stmt, 0);
            int cols = sqlite3_column_count(stmt);

                
            while (sqlite3_step(stmt) == SQLITE_ROW) { // цикл для вивидення рядків таблиці Score_Ukr
                const char *id = sqlite3_column_text(stmt, 0); // пошук відповідного рядка
                int parsed = atoi(id);
                if (score == parsed) {
                    const char *score_200 = sqlite3_column_text(stmt, 1);
                    sqlite3_stmt *stmt;
                    rc = sqlite3_prepare_v2(db, "INSERT INTO results (name_test, name_user, max_id, score, score_200, score_12) VALUES (?, ?, '45', ?, ?, ?)", -1, &stmt, NULL); // додавання записів результатів до таблиці results

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
                        printf("|      %-*s                            Результати                                                |\n", width_name_test, name_test);
                        printf("+-----------------------------------------------------------------------------------------------------------+\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                            ТЕСТУВАННЯ ЗАВЕРШЕНО                                           |\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                   Ім'я: %-*s|\n", width_name, name);
                        printf("|                                                                                                           |\n");
                        printf("|                                              ВАШІ РЕЗУЛЬТАТИ                                              |\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                   Кількість балів з 45 можливих: %-*d|\n", width_score, score);
                        printf("|                                   Кількість балів у 200 бальній системі: %-*s|\n", width_score_200, score_200);
                        printf("|                                   Кількість балів у 12 бальній системі: %-*d|\n", width_score_12, score_12);
                        printf("|                                                                                                           |\n");
                        printf("|                                                                                                           |\n");
                        printf("+-----------------------------------------------------------------------------------------------------------+\n");
                        printf("|                                                  Меню - E                                                 |\n");
                        printf("+-----------------------------------------------------------------------------------------------------------+\n");
                        printf("\n");
                        printf("Вибір опції: ");

                        char select_results[1000];
                        scanf("%s", &select_results);



                        if (select_results[0] == 'E' && strlen(select_results) == 1 || select_results[0] == 'e' && strlen(select_results) == 1 || select_results[0] == 'У' && strlen(select_results) == 1 || select_results[0] == 'у' && strlen(select_results) == 1) { // якщо клавіша E, то вихід з функції
                            return 0;
                        }
                                                        
                        else {
                            ;
                        }    
                    }
                }
            }
        }

        if (test == 2) { // якщо тест математика
            int score_12 = round((float)score/32.0*12); // переведення в 12 бальну систему

            sqlite3_stmt *stmt;
            rc = sqlite3_prepare_v2(db, "SELECT * FROM Score_Math", -1, &stmt, 0);
            int cols = sqlite3_column_count(stmt);

                
            while (sqlite3_step(stmt) == SQLITE_ROW) { // цикл для вивидення рядків таблиці Score_Math
                const char *id = sqlite3_column_text(stmt, 0); // пошук відповідного рядка
                int parsed = atoi(id);
                if (score == parsed) {
                    const char *score_200 = sqlite3_column_text(stmt, 1);
                    sqlite3_stmt *stmt;
                    rc = sqlite3_prepare_v2(db, "INSERT INTO results (name_test, name_user, max_id, score, score_200, score_12) VALUES (?, ?, '32', ?, ?, ?)", -1, &stmt, NULL); // додавання записів результатів до таблиці results

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
                        printf("|      %-*s                            Результати                                                |\n", width_name_test, name_test);
                        printf("+-----------------------------------------------------------------------------------------------------------+\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                            ТЕСТУВАННЯ ЗАВЕРШЕНО                                           |\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                   Ім'я: %-*s|\n", width_name, name);
                        printf("|                                                                                                           |\n");
                        printf("|                                              ВАШІ РЕЗУЛЬТАТИ                                              |\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                   Кількість балів з 32 можливих: %-*d|\n", width_score, score);
                        printf("|                                   Кількість балів у 200 бальній системі: %-*s|\n", width_score_200, score_200);
                        printf("|                                   Кількість балів у 12 бальній системі: %-*d|\n", width_score_12, score_12);
                        printf("|                                                                                                           |\n");
                        printf("|                                                                                                           |\n");
                        printf("+-----------------------------------------------------------------------------------------------------------+\n");
                        printf("|                                                  Меню - E                                                 |\n");
                        printf("+-----------------------------------------------------------------------------------------------------------+\n");
                        printf("\n");
                        printf("Вибір опції: ");

                        char select_results[1000];
                        scanf("%s", &select_results);



                        if (select_results[0] == 'E' && strlen(select_results) == 1 || select_results[0] == 'e' && strlen(select_results) == 1 || select_results[0] == 'У' && strlen(select_results) == 1 || select_results[0] == 'у' && strlen(select_results) == 1) { // якщо клавіша E, то вихід з функції
                            return 0;
                        }
                                                        
                        else {
                            ;
                        }    
                    }
                }
            }
        }

        if (test == 3) { // якщо тест Історія України
            int score_12 = round((float)score/54.0*12); // переведення в 12 бальну систему

            sqlite3_stmt *stmt;
            rc = sqlite3_prepare_v2(db, "SELECT * FROM Score_History", -1, &stmt, 0);
            int cols = sqlite3_column_count(stmt);

                
            while (sqlite3_step(stmt) == SQLITE_ROW) { // цикл для вивидення рядків таблиці Score_History
                const char *id = sqlite3_column_text(stmt, 0); // пошук відповідного рядка
                int parsed = atoi(id);
                if (score == parsed) {
                    const char *score_200 = sqlite3_column_text(stmt, 1);
                    sqlite3_stmt *stmt;
                    rc = sqlite3_prepare_v2(db, "INSERT INTO results (name_test, name_user, max_id, score, score_200, score_12) VALUES (?, ?, '54', ?, ?, ?)", -1, &stmt, NULL); // додавання записів результатів до таблиці results

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
                        printf("|      %-*s                            Результати                                                |\n", width_name_test, name_test);
                        printf("+-----------------------------------------------------------------------------------------------------------+\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                            ТЕСТУВАННЯ ЗАВЕРШЕНО                                           |\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                   Ім'я: %-*s|\n", width_name, name);
                        printf("|                                                                                                           |\n");
                        printf("|                                              ВАШІ РЕЗУЛЬТАТИ                                              |\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                                                                                           |\n");
                        printf("|                                   Кількість балів з 54 можливих: %-*d|\n", width_score, score);
                        printf("|                                   Кількість балів у 200 бальній системі: %-*s|\n", width_score_200, score_200);
                        printf("|                                   Кількість балів у 12 бальній системі: %-*d|\n", width_score_12, score_12);
                        printf("|                                                                                                           |\n");
                        printf("|                                                                                                           |\n");
                        printf("+-----------------------------------------------------------------------------------------------------------+\n");
                        printf("|                                                  Меню - E                                                 |\n");
                        printf("+-----------------------------------------------------------------------------------------------------------+\n");
                        printf("\n");
                        printf("Вибір опції: ");

                        char select_results[1000];
                        scanf("%s", &select_results);



                        if (select_results[0] == 'E' && strlen(select_results) == 1 || select_results[0] == 'e' && strlen(select_results) == 1 || select_results[0] == 'У' && strlen(select_results) == 1 || select_results[0] == 'у' && strlen(select_results) == 1) { // якщо клавіша E, то вихід з функції
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

    int results_custom_tests(int score, char name_user[1000], char name[255]) // функція, яка виводить результати тестувань власних тестів
    {
        int width_name = 66; // визначення ширини рядків для корректного відображення інтерфейсу
        int width_score = 41;
        int width_score_12 = 34;

        int max_id = 0; 

        char* query = NULL;
        int query_len = 0;
        sqlite3_stmt *stmt;

        query_len = snprintf(NULL, 0, "SELECT MAX(id) FROM '%s'", name); // пошук максимального балу тесту
        query = malloc(query_len + 1);
        sprintf(query, "SELECT MAX(id) FROM '%s'", name);

        rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            max_id = sqlite3_column_int(stmt, 0);

            int count_id = max_id; // визначення кількості цифр у числі max_id(максимальний бал тесту) для корректного відображення інтерфейсу
            int count = 0;

            while (count_id != 0) {
                count++;
                count_id /= 10;
            }
            if (count==1) { // встановлення корректної ширини рядків для корректного відображення інтерфейсу
                width_score = width_score + 1;
            }
            if (count==3) {
                width_score = width_score - 1;
            }
            
            int score_12 = round((float)score/max_id*12); // переведення в 12 бальну систему

            sqlite3_stmt *stmt;
            rc = sqlite3_prepare_v2(db, "INSERT INTO results (name_test, name_user, max_id, score, score_12) VALUES (?, ?, ?, ?, ?)", -1, &stmt, NULL); // додавання записів результатів до таблиці results

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
                printf("|                                                 Результати                                                |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("|                                                                                                           |\n");
                printf("|                                                                                                           |\n");
                printf("|                                            ТЕСТУВАННЯ ЗАВЕРШЕНО                                           |\n");
                printf("|                                                                                                           |\n");
                printf("|                                   Ім'я: %-*s|\n", width_name, name_user);
                printf("|                                                                                                           |\n");
                printf("|                                              ВАШІ РЕЗУЛЬТАТИ                                              |\n");
                printf("|                                                                                                           |\n");
                printf("|                                                                                                           |\n");
                printf("|                                   Кількість балів з %d можливих: %-*d|\n", max_id, width_score, score);
                printf("|                                   Кількість балів у 12 бальній системі: %-*d|\n", width_score_12, score_12);
                printf("|                                                                                                           |\n");
                printf("|                                                                                                           |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("|                                                  Меню - E                                                 |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("\n");
                printf("Вибір опції: ");

                char select_results[1000];
                scanf("%s", &select_results);

                if (select_results[0] == 'E' && strlen(select_results) == 1 || select_results[0] == 'e' && strlen(select_results) == 1 || select_results[0] == 'У' && strlen(select_results) == 1 || select_results[0] == 'у' && strlen(select_results) == 1) { // якщо клавіша E, то вихід з функції
                    return 0;
                }
                                                
                else {
                    ;
                }
            }
        }


        
    }

    int results(){ // функція, яка виводить останні 5 разів тестувань
        while (TRUE) {
            system("cls");
            printf("+-------------------------------------------------------------------------+\n");
            printf("|                                 РУЗУЛЬТАТИ                              |\n");
            printf("+-------------------------------------------------------------------------+\n");
            printf("|                                                                         |\n");
            printf("|                           Останні рази тестувань                        |\n");

            sqlite3_stmt *stmt;
            rc = sqlite3_prepare_v2(db, "SELECT * FROM results ORDER BY id DESC LIMIT 5;", -1, &stmt, 0); // sql запит для вибірки 5 останніх записів
            int cols = sqlite3_column_count(stmt);

            while (sqlite3_step(stmt) == SQLITE_ROW) { // цикл для вивидення рядків таблиці
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
                char text1[256] = "Виконавець: ";
                strcat(text1, name_user);
                split_string(text1, 61);
                printf("|                                                                         |\n");
                char text2[256] = "Кількість балів з ";
                strcat(text2, max_id);
                strcat(text2, " можливих: ");
                strcat(text2, score);
                split_string(text2, 61);

                if (score_200 != NULL) { // якщо тест має результати у 200 бальній системі, то виводить їх
                    char text3[256] = "Кількість балів у 200 бальній системі: ";
                    strcat(text3, score_200);
                    split_string(text3, 61);
                }

                char text4[256] = "Кількість балів у 12 бальній системі: ";
                strcat(text4, score_12);
                split_string(text4, 61);    
            }
            sqlite3_finalize(stmt);
            printf("|                                                                         |\n");
            printf("|                                                                         |\n");
            printf("+-------------------------------------------------------------------------+\n");
            printf("|                                 Меню - E                                |\n");
            printf("+-------------------------------------------------------------------------+\n");
            printf("\n");
            printf("Вибір опції: "); 

            char select_results[1000];
            scanf("%s", &select_results);

            if (select_results[0] == 'E' && strlen(select_results) == 1 || select_results[0] == 'e' && strlen(select_results) == 1 || select_results[0] == 'У' && strlen(select_results) == 1 || select_results[0] == 'у' && strlen(select_results) == 1) { // якщо клавіша E, то вихід з функції
                return 0;
            }
                                                
            else {
                ;
            }
        }
    }

    int constructor() // конструктор для створення, редагування та видалення тестів
    {
        exit8:
        exit5:
        while (TRUE) { 
            exit13:
            system("cls");
            printf("+-------------------------------------------+\n");
            printf("|                 КОНСТРУКТОР               |\n");
            printf("+-------------------------------------------+\n");
            printf("|                                           |\n");
            printf("|              Створити тест - 1            |\n");
            printf("|              Редагувати тест - 2          |\n");
            printf("|              Видалити тест - 3            |\n");
            printf("|                                           |\n");
            printf("|              Більше про конструктор - 4   |\n");
            printf("|              Меню - E                     |\n");
            printf("|                                           |\n");
            printf("+-------------------------------------------+\n");
            printf("\n");
            printf("Вибір опції: ");

            char select_constructor[1];
            scanf("%s", select_constructor);

            if (select_constructor[0] == '1' && strlen(select_constructor) == 1) { // створення тесту
                system("cls");
                printf("+-------------------------------------------+\n");
                printf("|               СТВОРЕННЯ ТЕСТУ             |\n");
                printf("+-------------------------------------------+\n");
                printf("|                                           |\n");
                printf("|                                           |\n");
                printf("|             Введіть назву тесту           |\n");
                printf("|                                           |\n");
                printf("+-------------------------------------------+\n");
                printf("|                  Назад - E                |\n");
                printf("+-------------------------------------------+\n");
                printf("\n");
                printf("Введіть назву тесту: ");
                getchar();
                char select_name_test[255];
                fgets(select_name_test, 255, stdin); // назва тесту

                int len = strcspn(select_name_test, "\n"); // видалення зайвих пропусків для корректного відображення інтрефейсу
                select_name_test[len] = '\0'; 

                if (select_name_test[0] == 'E' && strlen(select_name_test) == 1 || select_name_test[0] == 'e' && strlen(select_name_test) == 1 || select_name_test[0] == 'У' && strlen(select_name_test) == 1 || select_name_test[0] == 'у' && strlen(select_name_test) == 1) { // якщо клавіша E, то повернення назад
                    goto exit2;
                }

                else {

                    char* sql_insert_select_name_test = "INSERT INTO Custom_Tests (name) VALUES(?);"; // додавання запису з ім'ям створеного тесту до таблиці Custom_Tests(список власних тестів)
                    sqlite3_stmt *stmt;
                    rc = sqlite3_prepare_v2(db, sql_insert_select_name_test, -1, &stmt, 0);

                    sqlite3_bind_text(stmt, 1, select_name_test, -1, SQLITE_STATIC);
                    rc = sqlite3_step(stmt);
                    sqlite3_finalize(stmt);

                    char* sql_create_select_name_test = sqlite3_mprintf("CREATE TABLE '%s' (id INTEGER PRIMARY KEY, question TEXT, answer1 TEXT, answer2 TEXT, answer3 TEXT, answer4 TEXT);", select_name_test); // створення таблиці, це і буде нашим тестом
                    rc = sqlite3_exec(db, sql_create_select_name_test, NULL, NULL, NULL);

                    char select_name_question[1000];
                    char select_answer_question[1000];

                    for (int i=1; i<=100; i++) { // цикл, який створює записи до таблиці(створює запитання)
                        // додавання запитання
                        int width = 4;
                        system("cls");
                        printf("+-------------------------------------------+\n");
                        printf("|               СТВОРЕННЯ ТЕСТУ             |\n");
                        printf("+-------------------------------------------+\n");
                        printf("|                                           |\n");
                        printf("|                Запитання №%-*d            |\n", width, i);
                        printf("|                                           |\n");
                        printf("|              Введіть запитання            |\n");
                        printf("|                                           |\n");
                        printf("|                                           |\n");
                        printf("+-------------------------------------------+\n");
                        printf("|                Закінчити - E              |\n");
                        printf("+-------------------------------------------+\n");
                        printf("\n");
                        printf("Введіть запитання: ");
                        fgets(select_name_question, 1000, stdin); // запитання

                        int len = strcspn(select_name_question, "\n"); // видалення зайвих пропусків для корректного відображення інтрефейсу
                        select_name_question[len] = '\0';

                        if (select_name_question[0] == 'E' && strlen(select_name_question) == 1 || select_name_question[0] == 'e' && strlen(select_name_question) == 1 || select_name_question[0] == 'У' && strlen(select_name_question) == 1 || select_name_question[0] == 'у' && strlen(select_name_question) == 1) { // якщо клавіша E, то повернення назад
                            goto exit2;
                        }

                        else {
                            while (TRUE) {
                                // додавання варіантів відповідей
                                char text1[255] = "Напишіть 4 варіанти відповідей через знак '|' без пропусків.";
                                char text2[255] = "Для того щоб вказати правильну відповідь, біля обраного варіанту поставте три знаки '+' без пропусків. ";
                                char text3[255] = "Зразок: 2+2=5|2+2=4+++|2+2=3|Звідки мені знати???";
                                
                                system("cls");
                                printf("+-------------------------------------------------------------------------+\n");
                                printf("|                              СТВОРЕННЯ ТЕСТУ                            |\n");
                                printf("+-------------------------------------------------------------------------+\n");
                                printf("|                                                                         |\n");
                                printf("|                               Запитання №%-*d                           |\n", width, i);
                                printf("|                                                                         |\n");
                                split_string(text1, 61);
                                split_string(text2, 61);
                                printf("|                                                                         |\n");
                                split_string(text3, 61);
                                printf("|                                                                         |\n");
                                printf("|                                                                         |\n");
                                printf("+-------------------------------------------------------------------------+\n");
                                printf("|                               Закінчити - E                             |\n");
                                printf("+-------------------------------------------------------------------------+\n");
                                printf("\n");
                                printf("Введіть варіанти відповідей: ");
                                fgets(select_answer_question, 1000, stdin); 

                                int len = strcspn(select_answer_question, "\n"); // видалення зайвих пропусків для корректного відображення інтрефейсу
                                select_answer_question[len] = '\0';

                                if (select_answer_question[0] == 'E' && strlen(select_answer_question) == 1 || select_answer_question[0] == 'e' && strlen(select_answer_question) == 1 || select_answer_question[0] == 'У' && strlen(select_answer_question) == 1 || select_answer_question[0] == 'у' && strlen(select_answer_question) == 1) { // якщо клавіша E, то повернення назад
                                    return 0;
                                }

                                int count = 0; // виявлення кількості знаків "|"

                                for (int i = 0; i < strlen(select_answer_question); i++) {
                                    if (select_answer_question[i] == '|') {
                                     count++;
                                    }
                                }

                                if (count == 3) { // якщо знаків "|" дорівнює 3
                                    char* token = strtok(select_answer_question, "|"); // розподілення рядка на 4 варіанти відповідей за допомогою знака "|"
                                    char* question1 = token;
                                    token = strtok(NULL, "|");
                                    char* question2 = token;
                                    token = strtok(NULL, "|");
                                    char* question3 = token;
                                    token = strtok(NULL, "|");
                                    char* question4 = token;


                                    if (question1 != NULL && question2 != NULL && question3 != NULL && question4 != NULL) {

                                        char query[256];
                                        sprintf(query, "INSERT INTO '%s' (question, answer1, answer2, answer3, answer4) VALUES (?, ?, ?, ?, ?);", select_name_test); // додавання записів про запитання та варінти відповідей до таблиці(тесту)

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


            if (select_constructor[0] == '2' && strlen(select_constructor) == 1) { // редагування тесту
                exit6:
                while (TRUE) {
                    // вивід списку тестів
                    system("cls");
                    printf("+-------------------------------------------------------------------------+\n");
                    printf("|                                РЕДАГУВАННЯ                              |\n");
                    printf("+-------------------------------------------------------------------------+\n");
                    printf("|                                                                         |\n");
                    printf("|                               Список тестів                             |\n");
                    printf("|                                                                         |\n");
                    // вибірка таблиці Custom_Tests
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
                    printf("|                                 Назад - E                               |\n");
                    printf("+-------------------------------------------------------------------------+\n");
                    printf("\nВведіть бажаний тест вказавши його номер: ");
                    char select_test_change[100];
                    scanf("%s", select_test_change);

                    if (select_test_change[0] == 'E' && strlen(select_test_change) == 1 || select_test_change[0] == 'e' && strlen(select_test_change) == 1 || select_test_change[0] == 'У' && strlen(select_test_change) == 1 || select_test_change[0] == 'у' && strlen(select_test_change) == 1) { // якщо клавіша E, то повернення назад
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
                                    // меню редагування тесту
                                    system("cls");
                                    printf("+-------------------------------------------+\n");
                                    printf("|                 РЕДАГУВАННЯ               |\n");
                                    printf("+-------------------------------------------+\n");
                                    printf("|                                           |\n");
                                    printf("|              Змінити назву - 1            |\n");
                                    printf("|              Змінити запитання - 2        |\n");
                                    printf("|              Додати запитання - 3         |\n");
                                    printf("|              Видалити запитання - 4       |\n");
                                    printf("|                                           |\n");
                                    printf("+-------------------------------------------+\n");
                                    printf("|                  Назад - E                |\n");
                                    printf("+-------------------------------------------+\n");

                                    printf("\n\nВибір опції: ");
                                    char select_change_test[1];
                                    scanf("%s", select_change_test);

                                    if (select_change_test[0] == '1' && strlen(select_change_test) == 1) { // зміна назви
                                        system("cls");
                                        printf("+-------------------------------------------+\n");
                                        printf("|                 ЗМІНА НАЗВИ               |\n");
                                        printf("+-------------------------------------------+\n");
                                        printf("|                                           |\n");
                                        printf("|                                           |\n");
                                        printf("|              Введіть нову назву           |\n");
                                        printf("|                                           |\n");
                                        printf("|                                           |\n");
                                        printf("+-------------------------------------------+\n");
                                        printf("|                  Назад - E                |\n");
                                        printf("+-------------------------------------------+\n");
                                        printf("\n");
                                        printf("Введіть нову назву: ");
                                        getchar();
                                        char new_name_test[100];
                                        fgets(new_name_test, 255, stdin);

                                        int len = strcspn(new_name_test, "\n"); // видалення зайвих пропусків для корректного відображення інтрефейсу
                                        new_name_test[len] = '\0';

                                        if (new_name_test[0] == 'E' && strlen(new_name_test) == 1 || new_name_test[0] == 'e' && strlen(new_name_test) == 1 || new_name_test[0] == 'У' && strlen(new_name_test) == 1 || new_name_test[0] == 'у' && strlen(new_name_test) == 1) { // якщо клавіша E, то повернення назад
                                            goto exit7;
                                        }

                                        else {
                                            // робимо вибірку для того щоб знайти назву тесту через id
                                            sqlite3_stmt *stmt;
                                            rc = sqlite3_prepare_v2(db, "SELECT * FROM Custom_Tests", -1, &stmt, 0);
                                            int cols = sqlite3_column_count(stmt);

                                            while (sqlite3_step(stmt) == SQLITE_ROW) {
                                                const char *id = sqlite3_column_text(stmt, 0);
                                                if (strcmp(select_test_change, id)==0) {
                                                    const char *old_name = sqlite3_column_text(stmt, 1);
                                                    // змінюємо назву таблиці(тесту)
                                                    char sql_rename_table[256];
                                                    sprintf(sql_rename_table, "ALTER TABLE '%s' RENAME TO '%s';", old_name, new_name_test);
                                                    rc = sqlite3_exec(db, sql_rename_table, NULL, NULL, NULL);
                                                    // змінюємо назву запису(тесту) в таблиці Custom_Tests
                                                    char sql_rename[256];
                                                    sprintf(sql_rename, "UPDATE Custom_Tests SET name = '%s' WHERE id = %s;", new_name_test, select_test_change);
                                                    rc = sqlite3_exec(db, sql_rename, NULL, NULL, NULL);
                                                }
                                            }
                                        }
                                    }

                                    if (select_change_test[0] == '2' && strlen(select_change_test) == 1) { // зміна запитання
                                        exit12:
                                        exit10:
                                        while (TRUE) {
                                            // вивід запитань тесту
                                            system("cls");
                                            printf("+-------------------------------------------------------------------------+\n");
                                            printf("|                                РЕДАГУВАННЯ                              |\n");
                                            printf("+-------------------------------------------------------------------------+\n");
                                            printf("|                                                                         |\n");
                                            printf("|                                 Запитання                               |\n");
                                            // робимо вибірку для того щоб знайти назву тесту через id
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
                                                        // додаємо до варіантів відповідей букви
                                                        char A[255] = "А ";
                                                        char B[255] = "Б ";
                                                        char C[255] = "В ";
                                                        char D[255] = "Г ";
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
                                                    printf("|                                 Назад - E                               |\n");
                                                    printf("+-------------------------------------------------------------------------+\n");
                                                    printf("\nОберіть запитання вказавши його номер: ");
                                                    char select_question[100];
                                                    scanf("%s", select_question);

                                                    if (select_question[0] == 'E' && strlen(select_question) == 1 || select_question[0] == 'e' && strlen(select_question) == 1 || select_question[0] == 'У' && strlen(select_question) == 1 || select_question[0] == 'у' && strlen(select_question) == 1) { // якщо клавіша E, то повернення назад
                                                        goto exit9;
                                                    }
                                                    else {
                                                        // провіряємо чи дійсно обране запитання є в тесті через вибірку
                                                        sqlite3_stmt *stmt;
                                                        sql_select_test = sqlite3_mprintf("SELECT * FROM '%s';", name_update);
                                                        rc = sqlite3_prepare_v2(db, sql_select_test, -1, &stmt, 0);
                                                        int cols = sqlite3_column_count(stmt);

                                                        while (sqlite3_step(stmt) == SQLITE_ROW) {
                                                            char *id = sqlite3_column_text(stmt, 0);
                                                            if (strcmp(select_question, id)==0) {
                                                                while (TRUE) {
                                                                    // змінюємо запитання
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
                                                                    printf("|                                РЕДАГУВАННЯ                              |\n");
                                                                    printf("+-------------------------------------------------------------------------+\n");
                                                                    printf("|                                                                         |\n");
                                                                    printf("|                                 Запитання                               |\n");
                                                                    printf("|                                                                         |\n");
                                                                    split_string(id, 61);
                                                                    printf("|                                                                         |\n");
                                                                    char A[255] = "А ";
                                                                    char B[255] = "Б ";
                                                                    char C[255] = "В ";
                                                                    char D[255] = "Г ";
                                                                    strcat(A, answer1);
                                                                    split_string(A, 61);
                                                                    strcat(B, answer2);
                                                                    split_string(B, 61);
                                                                    strcat(C, answer3);
                                                                    split_string(C, 61);
                                                                    strcat(D, answer4);
                                                                    split_string(D, 61);
                                                                    printf("|                                                                         |\n");
                                                                    printf("|      Напишіть нове запитання.                                           |\n");
                                                                    printf("|                                                                         |\n");
                                                                    printf("+-------------------------------------------------------------------------+\n");
                                                                    printf("|                                 Назад - E                               |\n");
                                                                    printf("+-------------------------------------------------------------------------+\n");
                                                                    printf("\nВведіть нову назву: ");
                                                                    getchar();
                                                                    char new_name_question[1000];
                                                                    fgets(new_name_question, 1000, stdin);

                                                                    int len = strcspn(new_name_question, "\n");
                                                                    new_name_question[len] = '\0';

                                                                    if (new_name_question[0] == 'E' && strlen(new_name_question) == 1 || new_name_question[0] == 'e' && strlen(new_name_question) == 1 || new_name_question[0] == 'У' && strlen(new_name_question) == 1 || new_name_question[0] == 'у' && strlen(new_name_question) == 1) { // якщо клавіша E, то повернення назад
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
                                                                                    // змінюємо варіанти відповідей
                                                                                    char *name = sqlite3_column_text(stmt, 1);
                                                                                    char *answer1 = sqlite3_column_text(stmt, 2);
                                                                                    char *answer2 = sqlite3_column_text(stmt, 3);
                                                                                    char *answer3 = sqlite3_column_text(stmt, 4);
                                                                                    char *answer4 = sqlite3_column_text(stmt, 5);
                                                                                    strcat(id, ". ");
                                                                                    strcat(id, new_name_question);
                                                                                    system("cls");
                                                                                    printf("+-------------------------------------------------------------------------+\n");
                                                                                    printf("|                                РЕДАГУВАННЯ                              |\n");
                                                                                    printf("+-------------------------------------------------------------------------+\n");
                                                                                    printf("|                                                                         |\n");
                                                                                    printf("|                                 Запитання                               |\n");
                                                                                    printf("|                                                                         |\n");
                                                                                    split_string(id, 61);
                                                                                    printf("|                                                                         |\n");
                                                                                    char A[255] = "А ";
                                                                                    char B[255] = "Б ";
                                                                                    char C[255] = "В ";
                                                                                    char D[255] = "Г ";
                                                                                    strcat(A, answer1);
                                                                                    split_string(A, 61);
                                                                                    strcat(B, answer2);
                                                                                    split_string(B, 61);
                                                                                    strcat(C, answer3);
                                                                                    split_string(C, 61);
                                                                                    strcat(D, answer4);
                                                                                    split_string(D, 61);
                                                                                    printf("|                                                                         |\n");
                                                                                    char text1[255] = "Напишіть 4 варіанти відповідей через знак '|' без пропусків.";
                                                                                    char text2[255] = "Для того щоб вказати правильну відповідь біля обраного варіанту поставте три знаки '+' без пропусків. ";
                                                                                    char text3[255] = "Зразок: 2+2=5|2+2=4+++|2+2=3|Звідки мені знати???";
                                                                                    split_string(text1, 61);
                                                                                    split_string(text2, 61);
                                                                                    printf("|                                                                         |\n");
                                                                                    split_string(text3, 61);
                                                                                    printf("|                                                                         |\n");
                                                                                    printf("|                                                                         |\n");
                                                                                    printf("+-------------------------------------------------------------------------+\n");
                                                                                    printf("|                                 Назад - E                               |\n");
                                                                                    printf("+-------------------------------------------------------------------------+\n");
                                                                                    printf("\nВведіть нові варіанти відповідей: ");
                                                                                    char new_name_answer[1000];
                                                                                    fgets(new_name_answer, 1000, stdin);

                                                                                    int len = strcspn(new_name_answer, "\n"); // видалення зайвих пропусків для корректного відображення інтрефейсу
                                                                                    new_name_answer[len] = '\0';

                                                                                    if (new_name_answer[0] == 'E' && strlen(new_name_answer) == 1 || new_name_answer[0] == 'e' && strlen(new_name_answer) == 1 || new_name_answer[0] == 'У' && strlen(new_name_answer) == 1 || new_name_answer[0] == 'у' && strlen(new_name_answer) == 1) { // якщо клавіша натиснута E, то повернення назад
                                                                                        goto exit11;
                                                                                    }

                                                                                    int count = 0; // виявлення кількості знаків "|"

                                                                                    for (int i = 0; i < strlen(new_name_answer); i++) {
                                                                                        if (new_name_answer[i] == '|') {
                                                                                         count++;
                                                                                        }
                                                                                    }

                                                                                    if (count == 3) {
                                                                                        // зміна запитання в таблиці(тесті)
                                                                                        char sql_rename_question[256];
                                                                                        sprintf(sql_rename_question, "UPDATE '%s' SET question = '%s' WHERE id = %s;", name_update, new_name_question, select_question);
                                                                                        rc = sqlite3_exec(db, sql_rename_question, NULL, NULL, NULL);

                                                                                        char* token = strtok(new_name_answer, "|"); // розподілення рядка на 4 варіанти відповідей за допомогою знака "|"
                                                                                        char* new_answer1 = token;
                                                                                        token = strtok(NULL, "|");
                                                                                        char* new_answer2 = token;
                                                                                        token = strtok(NULL, "|");
                                                                                        char* new_answer3 = token;
                                                                                        token = strtok(NULL, "|");
                                                                                        char* new_answer4 = token;
                                                                                        // зміна варіантів відповідей в таблиці(тесті)
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

                                        // додавання запитання
                                        system("cls");
                                        printf("+-------------------------------------------+\n");
                                        printf("|             ДОДАВАННЯ ЗАПИТАННЯ           |\n");
                                        printf("+-------------------------------------------+\n");
                                        printf("|                                           |\n");
                                        printf("|                                           |\n");
                                        printf("|              Введіть запитання            |\n");
                                        printf("|                                           |\n");
                                        printf("|                                           |\n");
                                        printf("+-------------------------------------------+\n");
                                        printf("|                Закінчити - E              |\n");
                                        printf("+-------------------------------------------+\n");
                                        printf("\n");
                                        printf("Введіть запитання: ");
                                        getchar();
                                        fgets(select_name_question, 1000, stdin); // запитання

                                        int len = strcspn(select_name_question, "\n"); // видалення зайвих пропусків для корректного відображення інтрефейсу
                                        select_name_question[len] = '\0';

                                        if (select_name_question[0] == 'E' && strlen(select_name_question) == 1 || select_name_question[0] == 'e' && strlen(select_name_question) == 1 || select_name_question[0] == 'У' && strlen(select_name_question) == 1 || select_name_question[0] == 'у' && strlen(select_name_question) == 1) { // якщо клавіша E, то повернення назад
                                            goto exit30;
                                        }

                                        else {
                                            while (TRUE) {
                                                // додавання варіантів відповідей
                                                char text1[255] = "Напишіть 4 варіанти відповідей через знак '|' без пропусків.";
                                                char text2[255] = "Для того щоб вказати правильну відповідь, біля обраного варіанту поставте три знаки '+' без пропусків. ";
                                                char text3[255] = "Зразок: 2+2=5|2+2=4+++|2+2=3|Звідки мені знати???";
                                                    
                                                system("cls");
                                                printf("+-------------------------------------------------------------------------+\n");
                                                printf("|                            ДОДАВАННЯ ЗАПИТАННЯ                          |\n");
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
                                                printf("|                               Закінчити - E                             |\n");
                                                printf("+-------------------------------------------------------------------------+\n");
                                                printf("\n");
                                                printf("Введіть варіанти відповідей: ");
                                                fgets(select_answer_question, 1000, stdin); 

                                                int len = strcspn(select_answer_question, "\n"); // видалення зайвих пропусків для корректного відображення інтрефейсу
                                                select_answer_question[len] = '\0';

                                                if (select_answer_question[0] == 'E' && strlen(select_answer_question) == 1 || select_answer_question[0] == 'e' && strlen(select_answer_question) == 1 || select_answer_question[0] == 'У' && strlen(select_answer_question) == 1 || select_answer_question[0] == 'у' && strlen(select_answer_question) == 1) { // якщо клавіша E, то повернення назад
                                                    return 0;
                                                }

                                                int count = 0; // виявлення кількості знаків "|"

                                                for (int i = 0; i < strlen(select_answer_question); i++) {
                                                    if (select_answer_question[i] == '|') {
                                                        count++;
                                                    }
                                                }

                                                if (count == 3) { // якщо знаків "|" дорівнює 3
                                                    char* token = strtok(select_answer_question, "|"); // розподілення рядка на 4 варіанти відповідей за допомогою знака "|"
                                                    char* question1 = token;
                                                    token = strtok(NULL, "|");
                                                    char* question2 = token;
                                                    token = strtok(NULL, "|");
                                                    char* question3 = token;
                                                    token = strtok(NULL, "|");
                                                    char* question4 = token;

                                                    if (question1 != NULL && question2 != NULL && question3 != NULL && question4 != NULL) {

                                                        char query[256];
                                                        sprintf(query, "INSERT INTO '%s' (question, answer1, answer2, answer3, answer4) VALUES (?, ?, ?, ?, ?);", name); // додавання записів про запитання та варінти відповідей до таблиці(тесту)

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
                                            // вивід запитань тесту
                                            system("cls");
                                            printf("+-------------------------------------------------------------------------+\n");
                                            printf("|                             ВИДАЛЕННЯ ЗАПИТАННЯ                         |\n");
                                            printf("+-------------------------------------------------------------------------+\n");
                                            printf("|                                                                         |\n");
                                            printf("|                                 Запитання                               |\n");
                                            // робимо вибірку для того щоб знайти назву тесту через id
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
                                                        // додаємо до варіантів відповідей букви
                                                        char A[255] = "А ";
                                                        char B[255] = "Б ";
                                                        char C[255] = "В ";
                                                        char D[255] = "Г ";
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
                                                    printf("|                                 Назад - E                               |\n");
                                                    printf("+-------------------------------------------------------------------------+\n");
                                                    printf("\nОберіть запитання вказавши його номер: ");
                                                    char select_question[100];
                                                    scanf("%s", select_question);

                                                    if (select_question[0] == 'E' && strlen(select_question) == 1 || select_question[0] == 'e' && strlen(select_question) == 1 || select_question[0] == 'У' && strlen(select_question) == 1 || select_question[0] == 'у' && strlen(select_question) == 1) { // якщо клавіша E, то повернення назад
                                                        goto exit31;
                                                    }
                                                    
                                                    // перевірка, що обране запитання дійсно існує через вибірку
                                                    sqlite3_stmt *stmt1;
                                                    rc = sqlite3_prepare_v2(db, sqlite3_mprintf("SELECT * FROM '%s'", name), -1, &stmt1, 0);
                                                    cols = sqlite3_column_count(stmt1);

                                                    while (sqlite3_step(stmt1) == SQLITE_ROW) {
                                                        const char *id = sqlite3_column_text(stmt1, 0);
                                                        if (strcmp(select_question, id)==0) {
                                                            // видалення запитання з таблиці
                                                            char sql_drop_in_table[256];
                                                            sprintf(sql_drop_in_table, "DELETE FROM '%s' WHERE id = %s;", name, select_question);
                                                            rc = sqlite3_exec(db, sql_drop_in_table, NULL, NULL, NULL);

                                                            goto exit32; // повернення назад
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }

                                    if (select_change_test[0] == 'E' && strlen(select_change_test) == 1 || select_change_test[0] == 'e' && strlen(select_change_test) == 1 || select_change_test[0] == 'У' && strlen(select_change_test) == 1 || select_change_test[0] == 'у' && strlen(select_change_test) == 1) { // якщо клавіша натиснута E, то повернення назад
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


            if (select_constructor[0] == '3' && strlen(select_constructor) == 1) { // видалення тесту
                exit14:
                exit15:
                while (TRUE) {
                    // вивід список тестів
                    system("cls");
                    printf("+-------------------------------------------------------------------------+\n");
                    printf("|                                 ВИДАЛЕННЯ                               |\n");
                    printf("+-------------------------------------------------------------------------+\n");
                    printf("|                                                                         |\n");
                    printf("|                               Список тестів                             |\n");
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
                    printf("|                                 Назад - E                               |\n");
                    printf("+-------------------------------------------------------------------------+\n");
                    printf("\nВведіть бажаний тест вказавши його номер: ");
                    char select_test_delete[100];
                    scanf("%s", select_test_delete);

                    if (select_test_delete[0] == 'E' && strlen(select_test_delete) == 1 || select_test_delete[0] == 'e' && strlen(select_test_delete) == 1 || select_test_delete[0] == 'У' && strlen(select_test_delete) == 1 || select_test_delete[0] == 'у' && strlen(select_test_delete) == 1) { // якщо клавіша натиснута E, то повернення назад
                        goto exit13;
                    }

                    while (TRUE) {
                        // перевірка, що обраний тест дійсно існує через вибірку
                        sqlite3_stmt *stmt;
                        rc = sqlite3_prepare_v2(db, "SELECT * FROM Custom_Tests", -1, &stmt, 0);
                        cols = sqlite3_column_count(stmt);

                        while (sqlite3_step(stmt) == SQLITE_ROW) {
                            const char *id = sqlite3_column_text(stmt, 0);
                            if (strcmp(select_test_delete, id)==0) {
                                // попередження що до видалення тесту
                                char *name = sqlite3_column_text(stmt, 1);
                                system("cls");
                                printf("+-------------------------------------------------------------------------+\n");
                                printf("|                                 ВИДАЛЕННЯ                               |\n");
                                printf("+-------------------------------------------------------------------------+\n");
                                printf("|                                                                         |\n");
                                char text1[255] = "Ви точно хочете видалити тест '";
                                strcat(text1, name);
                                strcat(text1, "'?");
                                split_string(text1, 61);
                                printf("|                                                                         |\n");
                                char text2[255] = "Якщо так напишіть 'ТАК'.";
                                char text3[255] = "Якщо ні - 'НІ'.";
                                split_string(text2, 61);
                                split_string(text3, 61);
                                printf("|                                                                         |\n");
                                printf("|                                                                         |\n");
                                printf("+-------------------------------------------------------------------------+\n");
                                printf("|                                 Назад - E                               |\n");
                                printf("+-------------------------------------------------------------------------+\n");
                                printf("\nВведіть відповідь: ");
                                char select_test_delete_confirm[100];
                                scanf("%s", select_test_delete_confirm);

                                if (strcmp(select_test_delete_confirm, "ТАК")==0) { // якщо відповідь позитивна 
                                    // видалення таблиці(тесту)
                                    char sql_drop[256];
                                    sprintf(sql_drop, "DROP TABLE '%s';", name);
                                    rc = sqlite3_exec(db, sql_drop, NULL, NULL, NULL);
                                    // видалення тесту з таблиці Custom_Tests(список тестів)
                                    char sql_drop_in_table[256];
                                    sprintf(sql_drop_in_table, "DELETE FROM Custom_Tests WHERE id = %s;", select_test_delete);
                                    rc = sqlite3_exec(db, sql_drop_in_table, NULL, NULL, NULL);

                                    goto exit15; // повернення назад
                                }

                                if (strcmp(select_test_delete_confirm, "НІ")==0) { // якщо відповідь негативна
                                    goto exit14; // повернення назад
                                }
                            }
                        }                        
                    }   
                }
            }

            if (select_constructor[0] == '4' && strlen(select_constructor) == 1) { // про конструктор
                while (TRUE) {
                    system("cls");
                    printf("+-------------------------------------------------------------------------+\n");
                    printf("|                              ПРО КОНСТРУКТОР                            |\n");
                    printf("+-------------------------------------------------------------------------+\n");
                    printf("|                                                                         |\n");
                    char text[400] = "За допомогою конструктора ви можете створювати власні тести та проходити їх з легкістю. Конструктор підтримує до 100 запитань і 4 варіанти відповідей. Ви можете редагувати і видаляти свої тести, змінювати назву, запитання та варіанти відповідей.";
                    split_string(text, 61);
                    printf("|                                                                         |\n");
                    char text1[400] = "Весь процес створення тестів лежить у вашій компетенції - тож дійте на свій розсуд та створюйте якісні тести.";
                    split_string(text1, 61);
                    printf("|                                                                         |\n");
                    printf("+-------------------------------------------------------------------------+\n");
                    printf("|                                 Назад - E                               |\n");
                    printf("+-------------------------------------------------------------------------+\n");
                    printf("\n");
                    printf("Вибір опції: "); 

                    char select[100];
                    scanf("%s", &select);

                    if (select[0] == 'E' && strlen(select) == 1 || select[0] == 'e' && strlen(select) == 1 || select[0] == 'У' && strlen(select) == 1 || select[0] == 'у' && strlen(select) == 1) { // якщо клавіша натиснута E, то повернення назад
                        break;
                    }
                                                        
                    else {
                        ;
                    }
                }
            }


            exit2:

            if (select_constructor[0] == 'E' && strlen(select_constructor) == 1 || select_constructor[0] == 'e' && strlen(select_constructor) == 1 || select_constructor[0] == 'У' && strlen(select_constructor) == 1 || select_constructor[0] == 'у' && strlen(select_constructor) == 1) { // якщо клавіша натиснута E, то повернення назад
                return 0;
            }

            else {
                ;
            }
        }
    }





    int Ukr_NMT() // вивід тесту з української мови
    {
        // запитання про ім'я
        system("cls");
        printf("+-------------------------------------------+\n");
        printf("|                  ВАШЕ ІМ'Я                |\n");
        printf("+-------------------------------------------+\n");
        printf("|                                           |\n");
        printf("|                                           |\n");
        printf("|                Як вас звати?              |\n");
        printf("|                                           |\n");
        printf("|                                           |\n");
        printf("+-------------------------------------------+\n");
        printf("|                  Назад - E                |\n");
        printf("+-------------------------------------------+\n");
        printf("\n");
        printf("Введіть ваше ім'я: ");
        getchar();
        char name[1000];
        fgets(name, 1000, stdin);

        int len = strcspn(name, "\n"); // видалення зайвих пропусків для корректного відображення інтрефейсу
        name[len] = '\0';

        if (name[0] == 'E' && strlen(name) == 1 || name[0] == 'e' && strlen(name) == 1 || name[0] == 'У' && strlen(name) == 1 || name[0] == 'у' && strlen(name) == 1) { // якщо клавіша натиснута E, то повернення назад
            return 0;
        }

        system("cls");

        int test = 1; // позначення, що тест це українська мова
        int score =0;

        char name_test[100] = "Українська мова";
        // вибірка таблиці з української мови
        sqlite3_stmt *stmt;
        rc = sqlite3_prepare_v2(db, "SELECT * FROM Ukr", -1, &stmt, 0);
        int cols = sqlite3_column_count(stmt);

        
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            system("cls");
            // створення змінних для кожного поля
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
            printf("|                                       Українська мова | Запитання №%-*s                                   |\n", width, id);
            printf("+-----------------------------------------------------------------------------------------------------------+\n");
            printf("|                                                                                                           |\n");
            printf("|                                                                                                           |\n");
            split_string(question_test, 95);
            printf("|                                                                                                           |\n");
            printf("|                                                                                                           |\n"); 


            
            if (strcmp(id, "1") == 0 || strcmp(id, "2") == 0 || strcmp(id, "3") == 0 || strcmp(id, "4") == 0 || strcmp(id, "5") == 0 || strcmp(id, "6") == 0 || strcmp(id, "7") == 0 || strcmp(id, "8") == 0 || strcmp(id, "9") == 0 || strcmp(id, "10") == 0) { // якщо номер запитання від 1 до 10
                split_string(answer1_test, 95);
                split_string(answer2_test, 95);
                split_string(answer3_test, 95);
                split_string(answer4_test, 95);
                printf("|                                                                                                           |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("|                                         Закінчити тестування - E                                          |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("\n");
                printf("Введіть відповідь: ");
                char answer[100];
                scanf("%s", answer);
                

                if (strlen(answer) == 1) { // якщо відповідь дорівнює одному символу
                    if (answer[0] == answer_true[0] || answer[0] == answer_true[1] || answer[0] == answer_true[2] || answer[0] == answer_true[3]) { // якщо відповідь правильна
                        score++; // нараховується один бал
                    } 
                }
                if (answer[0] == 'E' && strlen(answer) == 1 || answer[0] == 'e' && strlen(answer) == 1 || answer[0] == 'У' && strlen(answer) == 1 || answer[0] == 'у' && strlen(answer) == 1) { // якщо клавіша натиснута E, то закінчення тестування
                    results_NMT(score, test, name, name_test); // закінчeння тестування та вивід результатів
                    return 0;
                }

            }


            if (strcmp(id, "11") == 0 || strcmp(id, "12") == 0 || strcmp(id, "13") == 0 || strcmp(id, "14") == 0 || strcmp(id, "15") == 0 || strcmp(id, "16") == 0 || strcmp(id, "17") == 0 || strcmp(id, "18") == 0 || strcmp(id, "19") == 0 || strcmp(id, "20") == 0 || strcmp(id, "21") == 0 || strcmp(id, "22") == 0 || strcmp(id, "23") == 0 || strcmp(id, "24") == 0 || strcmp(id, "25") == 0) { // якщо номер запитання від 11 до 25
                split_string(answer1_test, 95);
                split_string(answer2_test, 95);
                split_string(answer3_test, 95);
                split_string(answer4_test, 95);
                split_string(answer5_test, 95);
                printf("|                                                                                                           |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("|                                         Закінчити тестування - E                                          |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("\n");
                printf("Введіть відповідь: ");
                char answer[100];
                scanf("%s", answer);


                if (strlen(answer) == 1) { // якщо відповідь дорівнює одному символу
                    if (answer[0] == answer_true[0] || answer[0] == answer_true[1] || answer[0] == answer_true[2] || answer[0] == answer_true[3]) { // якщо відповідь правильна
                        score++; // нараховується один бал
                    } 
                }
                if (answer[0] == 'E' && strlen(answer) == 1 || answer[0] == 'e' && strlen(answer) == 1 || answer[0] == 'У' && strlen(answer) == 1 || answer[0] == 'у' && strlen(answer) == 1) { // якщо клавіша натиснута E, то закінчення тестування
                    results_NMT(score, test, name, name_test); // закінчeння тестування та вивід результатів
                    return 0;
                }
            }

            if (strcmp(id, "27") == 0) { // якщо номер запитання дорівнює 27
                split_string(answer1_test, 95);
                split_string(answer2_test, 95);
                split_string(answer3_test, 95);
                split_string(answer4_test, 95);
                split_string(answer5_test, 95);
                printf("|                                                                                                           |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("|                                         Закінчити тестування - E                                          |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("\n");
                printf("Введіть букви у відповідному порядку: ");
                char answer[100];
                scanf("%s", answer);

                if  (answer[0] == answer_true[0] || answer[0] == answer_true[4] || answer[0] == answer_true[8] || answer[0] == answer_true[12]) { // якщо перша відповідь правильна
                    score++; // нараховується один бал
                }
                if  (answer[1] == answer_true[1] || answer[1] == answer_true[5] || answer[1] == answer_true[9] || answer[1] == answer_true[13]) { // якщо друга відповідь правильна
                    score++; // нараховується один бал
                }
                if  (answer[2] == answer_true[2] || answer[2] == answer_true[6] || answer[2] == answer_true[10] || answer[2] == answer_true[14]) { // якщо третя відповідь правильна
                    score++; // нараховується один бал
                }
                if  (answer[3] == answer_true[3] || answer[3] == answer_true[7] || answer[3] == answer_true[11] || answer[3] == answer_true[15]) { // якщо четверта відповідь правильна
                    score++; // нараховується один бал
                }
                if (answer[0] == 'E' && strlen(answer) == 1 || answer[0] == 'e' && strlen(answer) == 1 || answer[0] == 'У' && strlen(answer) == 1 || answer[0] == 'у' && strlen(answer) == 1) { // якщо клавіша натиснута E, то закінчення тестування
                    results_NMT(score, test, name, name_test); // закінчeння тестування та вивід результатів
                    return 0;
                }
            }

            if (strcmp(id, "26") == 0 || strcmp(id, "28") == 0 || strcmp(id, "29") == 0 || strcmp(id, "30") == 0) { // якщо номер запитання дорівнює 26, 28-30
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
                printf("|                                         Закінчити тестування - E                                          |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("\n");
                printf("Введіть букви у відповідному порядку: ");
                char answer[100];
                scanf("%s", answer);

                if  (answer[0] == answer_true[0] || answer[0] == answer_true[4] || answer[0] == answer_true[8] || answer[0] == answer_true[12]) { // якщо перша відповідь правильна
                    score++; // нараховується один бал
                }
                if  (answer[1] == answer_true[1] || answer[1] == answer_true[5] || answer[1] == answer_true[9] || answer[1] == answer_true[13]) { // якщо друга відповідь правильна
                    score++; // нараховується один бал
                }
                if  (answer[2] == answer_true[2] || answer[2] == answer_true[6] || answer[2] == answer_true[10] || answer[2] == answer_true[14]) { // якщо третя відповідь правильна
                    score++; // нараховується один бал
                }
                if  (answer[3] == answer_true[3] || answer[3] == answer_true[7] || answer[3] == answer_true[11] || answer[3] == answer_true[15]) { // якщо четверта відповідь правильна
                    score++; // нараховується один бал
                }
                if (answer[0] == 'E' && strlen(answer) == 1 || answer[0] == 'e' && strlen(answer) == 1 || answer[0] == 'У' && strlen(answer) == 1 || answer[0] == 'у' && strlen(answer) == 1) { // якщо клавіша натиснута E, то закінчення тестування
                    results_NMT(score, test, name, name_test); // закінчeння тестування та вивід результатів
                    return 0;
                }
            }
        }
        results_NMT(score, test, name, name_test); // закінчeння тестування та вивід результатів
    }


    int Math_NMT() // вивід тесту з математики
    {
        // запитання про ім'я
        system("cls");
        printf("+-------------------------------------------+\n");
        printf("|                  ВАШЕ ІМ'Я                |\n");
        printf("+-------------------------------------------+\n");
        printf("|                                           |\n");
        printf("|                                           |\n");
        printf("|                Як вас звати?              |\n");
        printf("|                                           |\n");
        printf("|                                           |\n");
        printf("+-------------------------------------------+\n");
        printf("|                  Назад - E                |\n");
        printf("+-------------------------------------------+\n");
        printf("\n");
        printf("Введіть ваше ім'я: ");
        getchar();
        char name[1000];
        fgets(name, 1000, stdin);

        // видалення зайвих пропусків для корректного відображення інтрефейсу
        int len = strcspn(name, "\n");
        name[len] = '\0';

        if (name[0] == 'E' && strlen(name) == 1 || name[0] == 'e' && strlen(name) == 1 || name[0] == 'У' && strlen(name) == 1 || name[0] == 'у' && strlen(name) == 1) { // якщо клавіша натиснута E, то повернення назад
            return 0;
        }

        system("cls");

        int test = 2; // позначення, що тест це математика
        int score =0;

        char name_test[100] = "Математика";
        // вибірка таблиці з математики
        sqlite3_stmt *stmt;
        rc = sqlite3_prepare_v2(db, "SELECT * FROM Math", -1, &stmt, 0);
        int cols = sqlite3_column_count(stmt);

        
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            // створення змінних для кожного поля
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
            printf("|                                          Математика | Запитання №%-*s                                     |\n", width, id);
            printf("+-----------------------------------------------------------------------------------------------------------+\n");
            printf("|                                                                                                           |\n");
            printf("|                                                                                                           |\n");
            split_string(question_test, 95);
            printf("|                                                                                                           |\n");
            printf("|                                                                                                           |\n"); 


            
            if (strcmp(id, "1") == 0 || strcmp(id, "2") == 0 || strcmp(id, "3") == 0 || strcmp(id, "4") == 0 || strcmp(id, "5") == 0 || strcmp(id, "6") == 0 || strcmp(id, "7") == 0 || strcmp(id, "8") == 0 || strcmp(id, "9") == 0 || strcmp(id, "10") == 0 || strcmp(id, "11") == 0 || strcmp(id, "12") == 0 || strcmp(id, "13") == 0 || strcmp(id, "14") == 0 || strcmp(id, "15") == 0) { // якщо номер запитання від 1 до 15
                split_string(answer1_test, 95);
                split_string(answer2_test, 95);
                split_string(answer3_test, 95);
                split_string(answer4_test, 95);
                split_string(answer5_test, 95);
                printf("|                                                                                                           |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("|                                         Закінчити тестування - E                                          |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("\n");
                printf("Введіть відповідь: ");
                char answer[100];
                scanf("%s", answer);
                

                if (strlen(answer) == 1) { // якщо відповідь дорівнює одному символу
                    if (answer[0] == answer_true[0] || answer[0] == answer_true[1] || answer[0] == answer_true[2] || answer[0] == answer_true[3]) { // якщо відповідь правильна
                        score++; // нараховується один бал
                    } 
                }
                if (answer[0] == 'E' && strlen(answer) == 1 || answer[0] == 'e' && strlen(answer) == 1 || answer[0] == 'У' && strlen(answer) == 1 || answer[0] == 'у' && strlen(answer) == 1) { // якщо клавіша натиснута E, то закінчення тестування
                    results_NMT(score, test, name, name_test); // закінчeння тестування та вивід результатів
                    return 0;
                }

            }


            if (strcmp(id, "16") == 0 || strcmp(id, "17") == 0 || strcmp(id, "18") == 0) { // якщо номер запитання від 16 до 18
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
                printf("|                                         Закінчити тестування - E                                          |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("\n");
                printf("Введіть букви у відповідному порядку: ");
                char answer[100];
                scanf("%s", answer);


                if  (answer[0] == answer_true[0] || answer[0] == answer_true[3] || answer[0] == answer_true[6] || answer[0] == answer_true[9]) { // якщо перша відповідь правильна
                    score++; // нараховується один бал
                }
                if  (answer[1] == answer_true[1] || answer[1] == answer_true[4] || answer[1] == answer_true[7] || answer[1] == answer_true[10]) { // якщо друга відповідь правильна
                    score++; // нараховується один бал
                }
                if  (answer[2] == answer_true[2] || answer[2] == answer_true[5] || answer[2] == answer_true[8] || answer[2] == answer_true[11]) { // якщо третя відповідь правильна
                    score++; // нараховується один бал
                }
                if (answer[0] == 'E' && strlen(answer) == 1 || answer[0] == 'e' && strlen(answer) == 1 || answer[0] == 'У' && strlen(answer) == 1 || answer[0] == 'у' && strlen(answer) == 1) { // якщо клавіша натиснута E, то закінчення тестування
                    results_NMT(score, test, name, name_test); // закінчeння тестування та вивід результатів
                    return 0;
                }
            }

            if (strcmp(id, "19") == 0 || strcmp(id, "20") == 0 || strcmp(id, "21") == 0 || strcmp(id, "22") == 0) { // якщо номер запитання від 19 до 22
                printf("|      Напишіть лише число, без пропусків. Якщо число дробове використовуйте ','.                           |\n");
                printf("|                                                                                                           |\n");
                printf("|                                                                                                           |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("|                                         Закінчити тестування - E                                          |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("\n");
                printf("Введіть число: ");
                char answer[100];
                scanf("%s", answer);

                if  (strcmp(answer, answer_true) == 0) { // якщо перша відповідь правильна
                    score = score + 2; // нараховується два бали
                }
                if (answer[0] == 'E' && strlen(answer) == 1 || answer[0] == 'e' && strlen(answer) == 1 || answer[0] == 'У' && strlen(answer) == 1 || answer[0] == 'у' && strlen(answer) == 1) { // якщо клавіша натиснута E, то закінчення тестування
                    results_NMT(score, test, name, name_test); // закінчeння тестування та вивід результатів
                    return 0;
                }
            }
        }
        results_NMT(score, test, name, name_test); // закінчeння тестування та вивід результатів
    }


    int History_NMT() // вивід тесту з Історії України
    {
        // запитання про ім'я
        system("cls");
        printf("+-------------------------------------------+\n");
        printf("|                  ВАШЕ ІМ'Я                |\n");
        printf("+-------------------------------------------+\n");
        printf("|                                           |\n");
        printf("|                                           |\n");
        printf("|                Як вас звати?              |\n");
        printf("|                                           |\n");
        printf("|                                           |\n");
        printf("+-------------------------------------------+\n");
        printf("|                  Назад - E                |\n");
        printf("+-------------------------------------------+\n");
        printf("\n");
        printf("Введіть ваше ім'я: ");
        getchar();
        char name[1000];
        fgets(name, 1000, stdin);

        // видалення зайвих пропусків для корректного відображення інтрефейсу
        int len = strcspn(name, "\n");
        name[len] = '\0';

        if (name[0] == 'E' && strlen(name) == 1 || name[0] == 'e' && strlen(name) == 1 || name[0] == 'У' && strlen(name) == 1 || name[0] == 'у' && strlen(name) == 1) { // якщо клавіша натиснута E, то закінчення тестування
            return 0;
        }

        system("cls");

        int test = 3; // позначення, що тест це історія України
        int score =0;

        char name_test[100] = "Історія України";
        // вибірка таблиці з історії України
        sqlite3_stmt *stmt;
        rc = sqlite3_prepare_v2(db, "SELECT * FROM History", -1, &stmt, 0);
        int cols = sqlite3_column_count(stmt);

        
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            // створення змінних для кожного поля
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
            printf("|                                       Історія України | Запитання №%-*s                                   |\n", width, id);
            printf("+-----------------------------------------------------------------------------------------------------------+\n");
            printf("|                                                                                                           |\n");
            printf("|                                                                                                           |\n");
            split_string(question_test, 95);
            printf("|                                                                                                           |\n");
            printf("|                                                                                                           |\n"); 


            
            if (strcmp(id, "1") == 0 || strcmp(id, "2") == 0 || strcmp(id, "3") == 0 || strcmp(id, "4") == 0 || strcmp(id, "5") == 0 || strcmp(id, "6") == 0 || strcmp(id, "7") == 0 || strcmp(id, "8") == 0 || strcmp(id, "9") == 0 || strcmp(id, "10") == 0 || strcmp(id, "11") == 0 || strcmp(id, "12") == 0 || strcmp(id, "13") == 0 || strcmp(id, "14") == 0 || strcmp(id, "15") == 0 || strcmp(id, "16") == 0 || strcmp(id, "17") == 0 || strcmp(id, "18") == 0 || strcmp(id, "19") == 0 || strcmp(id, "20") == 0) { // якщо номер запитання від 1 до 20
                split_string(answer1_test, 95);
                split_string(answer2_test, 95);
                split_string(answer3_test, 95);
                split_string(answer4_test, 95);
                printf("|                                                                                                           |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("|                                         Закінчити тестування - E                                          |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("\n");
                printf("Введіть відповідь: ");
                char answer[100];
                scanf("%s", answer);
                

                if (strlen(answer) == 1) { // якщо відповідь дорівнює одному символу
                    if (answer[0] == answer_true[0] || answer[0] == answer_true[1] || answer[0] == answer_true[2] || answer[0] == answer_true[3]) { // якщо відповідь правильна
                        score++; // нараховується один бал
                    } 
                }
                if (answer[0] == 'E' && strlen(answer) == 1 || answer[0] == 'e' && strlen(answer) == 1 || answer[0] == 'У' && strlen(answer) == 1 || answer[0] == 'у' && strlen(answer) == 1) { // якщо клавіша натиснута E, то закінчення тестування
                    results_NMT(score, test, name, name_test); // закінчeння тестування та вивід результатів
                    return 0;
                }
            }


            if (strcmp(id, "21") == 0 || strcmp(id, "22") == 0 || strcmp(id, "23") == 0 || strcmp(id, "24") == 0) { // якщо номер запитання від 21 до 24
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
                printf("|                                         Закінчити тестування - E                                          |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("\n");
                printf("Введіть букви у відповідному порядку: ");
                char answer[100];
                scanf("%s", answer);

                if  (answer[0] == answer_true[0] || answer[0] == answer_true[4] || answer[0] == answer_true[8] || answer[0] == answer_true[12]) { // якщо перша відповідь правильна
                    score++; // нараховується один бал
                }
                if  (answer[1] == answer_true[1] || answer[1] == answer_true[5] || answer[1] == answer_true[9] || answer[1] == answer_true[13]) { // якщо друга відповідь правильна
                    score++; // нараховується один бал
                }
                if  (answer[2] == answer_true[2] || answer[2] == answer_true[6] || answer[2] == answer_true[10] || answer[2] == answer_true[14]) { // якщо третя відповідь правильна
                    score++; // нараховується один бал
                }
                if  (answer[3] == answer_true[3] || answer[3] == answer_true[7] || answer[3] == answer_true[11] || answer[3] == answer_true[15]) { // якщо четверта відповідь правильна
                    score++; // нараховується один бал
                }
                if (answer[0] == 'E' && strlen(answer) == 1 || answer[0] == 'e' && strlen(answer) == 1 || answer[0] == 'У' && strlen(answer) == 1 || answer[0] == 'у' && strlen(answer) == 1) { // якщо клавіша натиснута E, то закінчення тестування
                    results_NMT(score, test, name, name_test); // закінчeння тестування та вивід результатів
                    return 0;
                }
            }


            if (strcmp(id, "25") == 0 || strcmp(id, "26") == 0 || strcmp(id, "27") == 0) { // якщо номер запитання від 25 до 27
                split_string(answer1_test, 95);
                split_string(answer2_test, 95);
                split_string(answer3_test, 95);
                split_string(answer4_test, 95);
                printf("|                                                                                                           |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("|                                         Закінчити тестування - E                                          |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("\n");
                printf("Введіть букви у відповідному порядку: ");
                char answer[100];
                scanf("%s", answer);

                int i=0;

                if  (answer[0] == answer_true[0] || answer[0] == answer_true[4] || answer[0] == answer_true[8] || answer[0] == answer_true[12]) { // якщо перша відповідь правильна
                    score++; // нараховується уявний один бал
                    i++; // нараховується уявний один бал
                }
                if  (answer[1] == answer_true[1] || answer[1] == answer_true[5] || answer[1] == answer_true[9] || answer[1] == answer_true[13]) { // якщо друга відповідь правильна
                    score++; // нараховується уявний один бал
                    i++; // нараховується уявний один бал
                }
                if  (answer[2] == answer_true[2] || answer[2] == answer_true[6] || answer[2] == answer_true[10] || answer[2] == answer_true[14]) { // якщо третя відповідь правильна
                    score++; // нараховується уявний один бал
                    i++; // нараховується уявний один бал
                }
                if  (answer[3] == answer_true[3] || answer[3] == answer_true[7] || answer[3] == answer_true[11] || answer[3] == answer_true[15]) { // якщо четверта відповідь правильна
                    score++; // нараховується уявний один бал
                    i++; // нараховується уявний один бал
                }
                if (answer[0] == 'E' && strlen(answer) == 1 || answer[0] == 'e' && strlen(answer) == 1 || answer[0] == 'У' && strlen(answer) == 1 || answer[0] == 'у' && strlen(answer) == 1) { // якщо клавіша натиснута E, то закінчення тестування
                    results_NMT(score, test, name, name_test); // закінчeння тестування та вивід результатів
                    return 0;
                }
                // нараховується остаточний бал
                if (i >= 1) {
                    score = score - 1;
                }
            }


            if (strcmp(id, "28") == 0 || strcmp(id, "29") == 0 || strcmp(id, "30") == 0) { // якщо номер запитання від 28 до 30
                split_string(answer1_test, 95);
                split_string(answer2_test, 95);
                split_string(answer3_test, 95);
                split_string(answer4_test, 95);
                split_string(answer5_test, 95);
                split_string(answer6_test, 95);
                split_string(answer7_test, 95);
                printf("|                                                                                                           |\n");
                printf("|      Впишіть лише 3 відповіді(цифри) у відповідному порядку без прорусків, ком і т.д.(наприклад, 267)     |\n");
                printf("|                                                                                                           |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("|                                         Закінчити тестування - E                                          |\n");
                printf("+-----------------------------------------------------------------------------------------------------------+\n");
                printf("\n");
                printf("Введіть відповідь: ");
                char answer[100];
                scanf("%s", answer);


                if (answer[0] == answer_true[0]) { // якщо перша відповідь правильна
                    score++; // нараховується один бал
                }
                if (answer[1] == answer_true[1]) { // якщо друга відповідь правильна
                    score++; // нараховується один бал
                }
                if (answer[2] == answer_true[2]) { // якщо третя відповідь правильна
                    score++; // нараховується один бал
                } 
                if (answer[0] == 'E' && strlen(answer) == 1 || answer[0] == 'e' && strlen(answer) == 1 || answer[0] == 'У' && strlen(answer) == 1 || answer[0] == 'у' && strlen(answer) == 1) { // якщо клавіша натиснута E, то закінчення тестування
                    results_NMT(score, test, name, name_test); // закінчeння тестування та вивід результатів
                    return 0;
                }
            }
        }
        results_NMT(score, test, name, name_test); // закінчання тестування та вивід результатів
    }




    int choice_of_test_custom() // функція, яка відповідає за вивід списку власних тестів та виводить їх
    {
        exit20:
        while (TRUE) {
            // вивід списку власних тестів
            system("cls");
            printf("+-------------------------------------------------------------------------+\n");
            printf("|                               ВЛАСНІ ТЕСТИ                              |\n");
            printf("+-------------------------------------------------------------------------+\n");
            printf("|                                                                         |\n");
            printf("|                               Список тестів                             |\n");
            printf("|                                                                         |\n");
            // вибірка таблиці власних тестів
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
            printf("|                                 Назад - E                               |\n");
            printf("+-------------------------------------------------------------------------+\n");
            printf("\nВведіть бажаний тест вказавши його номер: ");
            char select_custom_test[100];
            scanf("%s", select_custom_test);

            if (select_custom_test[0] == 'E' && strlen(select_custom_test) == 1 || select_custom_test[0] == 'e' && strlen(select_custom_test) == 1 || select_custom_test[0] == 'У' && strlen(select_custom_test) == 1 || select_custom_test[0] == 'у' && strlen(select_custom_test) == 1) { // якщо клавіша натиснута E, то повернення назад
                return 0;
            }
            // провірка те що обраний тест є в базі даних через вибірку
            sqlite3_stmt *stmt1;
            rc = sqlite3_prepare_v2(db, "SELECT * FROM Custom_Tests", -1, &stmt1, 0);
            cols = sqlite3_column_count(stmt1);

            while (sqlite3_step(stmt1) == SQLITE_ROW) {
                char *id = sqlite3_column_text(stmt1, 0);
                if (strcmp(id, select_custom_test)==0) { // якщо обраний тест є в таблиці 
                    char *name = sqlite3_column_text(stmt1, 1);
                    // вибірка обраного тесту
                    sqlite3_stmt *stmt2;
                    char* query = NULL;
                    int query_len = 0;

                    query_len = snprintf(NULL, 0, "SELECT * FROM '%s'", name);
                    query = malloc(query_len + 1);
                    sprintf(query, "SELECT * FROM '%s'", name);

                    rc = sqlite3_prepare_v2(db, query, -1, &stmt2, 0);

                    free(query);

                    cols = sqlite3_column_count(stmt2);
                    // запит на ім'я'
                    system("cls");
                    printf("+-------------------------------------------+\n");
                    printf("|                  ВАШЕ ІМ'Я                |\n");
                    printf("+-------------------------------------------+\n");
                    printf("|                                           |\n");
                    printf("|                                           |\n");
                    printf("|                Як вас звати?              |\n");
                    printf("|                                           |\n");
                    printf("|                                           |\n");
                    printf("+-------------------------------------------+\n");
                    printf("|                  Назад - E                |\n");
                    printf("+-------------------------------------------+\n");
                    printf("\n");
                    printf("Введіть ваше ім'я: ");
                    getchar();
                    char name_user[1000];
                    fgets(name_user, 1000, stdin);

                    // видалення зайвих пропусків для корректного відображення інтрефейсу
                    int len = strcspn(name_user, "\n");
                    name_user[len] = '\0';

                    if (name_user[0] == 'E' && strlen(name_user) == 1 || name_user[0] == 'e' && strlen(name_user) == 1 || name_user[0] == 'У' && strlen(name_user) == 1 || name_user[0] == 'у' && strlen(name_user) == 1) { // якщо клавіша натиснута E, то повернення назад
                        goto exit20;
                    }

                    int width = 4;
                    int score = 0;

                    while (sqlite3_step(stmt2) == SQLITE_ROW) {
                        // створення змінних для кожного поля
                        char *id = sqlite3_column_text(stmt2, 0);
                        char *question = sqlite3_column_text(stmt2, 1);
                        char *answer1 = sqlite3_column_text(stmt2, 2);
                        char *answer2 = sqlite3_column_text(stmt2, 3);
                        char *answer3 = sqlite3_column_text(stmt2, 4);
                        char *answer4 = sqlite3_column_text(stmt2, 5);

                        // додавання бука для гарного відображення варіантів відповідей
                        char A[255] = "А ";
                        char B[255] = "Б ";
                        char C[255] = "В ";
                        char D[255] = "Г ";
                        strcat(A, answer1);
                        strcat(B, answer2);
                        strcat(C, answer3);
                        strcat(D, answer4);
                        // провіряє рядок та якщо є рядок "+++" видаляє його, щою не відображати правильну відповідь
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
                        // вивід запитання
                        system("cls");

                        printf("+-------------------------------------------------------------------------+\n");
                        printf("|                               ЗАПИТАННЯ №%-*s                           |\n", width, id);
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
                        printf("|                         Закінчити тестування - E                        |\n");
                        printf("+-------------------------------------------------------------------------+\n");
                        printf("\n");
                        printf("Введіть відповідь: ");
                        char answer[100];
                        scanf("%s", answer);

                        // провіряє, що введена коректна буква та якщо відповідь правильна
                        if (strcmp(answer, "А")==0 || strcmp(answer, "а")==0 || strcmp(answer, "F")==0 || strcmp(answer, "f")==0) {
                            char* answer_A = strstr(answer1, substr);
                            if (answer_A) {
                                score++; // нараховується один бал
                            }
                        }

                        if (strcmp(answer, "Б")==0 || strcmp(answer, "б")==0 || strcmp(answer, "<")==0 || strcmp(answer, ",")==0) {
                            char* answer_B = strstr(answer2, substr);
                            if (answer_B) {
                                score++; // нараховується один бал
                            }
                        }

                        if (strcmp(answer, "В")==0 || strcmp(answer, "в")==0 || strcmp(answer, "D")==0 || strcmp(answer, "d")==0) {
                            char* answer_C = strstr(answer3, substr);
                            if (answer_C) {
                                score++; // нараховується один бал
                            }
                        }

                        if (strcmp(answer, "Г")==0 || strcmp(answer, "г")==0 || strcmp(answer, "U")==0 || strcmp(answer, "u")==0) {
                            char* answer_D = strstr(answer4, substr);
                            if (answer_D!=0) {   
                                score++; // нараховується один бал
                            }
                        }

                        if (answer[0] == 'E' && strlen(answer) == 1 || answer[0] == 'e' && strlen(answer) == 1 || answer[0] == 'У' && strlen(answer) == 1 || answer[0] == 'у' && strlen(answer) == 1) { // якщо клавіша натиснута E, то закінчення тестування
                            results_custom_tests(score, name_user, name); // закінчeння тестування та вивід результатів
                            return 0;
                        }
                    }
                    results_custom_tests(score, name_user, name); // закінчeння тестування та вивід результатів
                    return 0;
                }
            }
        }
    }


    int about_program() { // функція, яка виводить інформацію про програму
        while (TRUE) {
            system("cls");
            printf("+-------------------------------------------------------------------------+\n");
            printf("|                                ПРО ПРОГРАМУ                             |\n");
            printf("+-------------------------------------------------------------------------+\n");
            printf("|                                                                         |\n");
            char text[400] = "Програма була розроблена студентом 25 групи - Ткаченком Марком Ігоровичем мовою програмування С. Головною метою програми є тестування знань за допомогою тестів. У програмі вже доступно по одному тесту у вигляді НМТ-2023 з української мови, математики та історії України. Крім того, програма має конструктор, за допомогою якого можна створювати власні тести.";
            split_string(text, 61);
            printf("|                                                                         |\n");
            printf("+-------------------------------------------------------------------------+\n");
            printf("|                                  Меню - E                               |\n");
            printf("+-------------------------------------------------------------------------+\n");
            printf("\n");
            printf("Вибір опції: "); 

            char select[100];
            scanf("%s", &select);

            if (select[0] == 'E' && strlen(select) == 1 || select[0] == 'e' && strlen(select) == 1 || select[0] == 'У' && strlen(select) == 1 || select[0] == 'у' && strlen(select) == 1) { // якщо клавіша натиснута E, то повернення назад
                return 0;
            }
                                                
            else {
                ;
            }
        }
        
    }

    int about_NMT() { // функція, яка виводить інфорцію про НМТ тестування
        while (TRUE) {
            system("cls");
            printf("+-------------------------------------------------------------------------+\n");
            printf("|                                  ПРО НМТ                                |\n");
            printf("+-------------------------------------------------------------------------+\n");
            printf("|                                                                         |\n");
            char text[400] = "Програма має по одному тесту з української мови, математики та історії України у вигляді НМТ-2023.";
            split_string(text, 61);
            printf("|                                                                         |\n");
            printf("|                                                                         |\n");
            char text1[400] = "Українська мова";
            split_string(text1, 61);
            printf("|                                                                         |\n");
            char text2[400] = "Тест з української мови має 30 завдань. З них 10 завдань на одну правильну відповідь з четверти(0 або 1 бал), 15 – на одну правильну відповідь з п'яти(0 або 1 бал), і 5 – на встановлення відповідності(0, 1, 2, 3 або 4 бали).";
            split_string(text2, 61);
            printf("|                                                                         |\n");
            printf("|                                                                         |\n");
            char text3[400] = "Математика";
            split_string(text3, 61);
            printf("|                                                                         |\n");
            char text4[400] = "Тест з математики має 22 завдання. З них - 15 тестів(0 або 1 бал), 3 завдання на встановлення відповідності(0, 1, 2 або 3 бали), та 4 завдання, де потрібно вписати відповідь(0 або 2 бали).";
            split_string(text4, 61);
            printf("|                                                                         |\n");
            printf("|                                                                         |\n");
            char text5[400] = "Історія України";
            split_string(text5, 61);
            printf("|                                                                         |\n");
            char text6[400] = "Тест з історії України має 30 завдань. З них - 20 тестів з однією правильною відповіддю(0 або 1 бал), 4 завдання на встановлення відповідності(0, 1, 2, 3 або 4 бали), 3 - на встановлення хронологічної послідовності(0, 1, 2 або 3 бали) та 3 завдання з вибором трьох правильних відповідей із семи запропонованих(0, 1, 2 або 3 бали).";
            split_string(text6, 61);
            printf("|                                                                         |\n");
            printf("+-------------------------------------------------------------------------+\n");
            printf("|                                 Назад - E                               |\n");
            printf("+-------------------------------------------------------------------------+\n");
            printf("\n");
            printf("Вибір опції: "); 

            char select[100];
            scanf("%s", &select);

            if (select[0] == 'E' && strlen(select) == 1 || select[0] == 'e' && strlen(select) == 1 || select[0] == 'У' && strlen(select) == 1 || select[0] == 'у' && strlen(select) == 1) { // якщо клавіша натиснута E, то повернення назад
                return 0;
            }
                                                                    
            else {
                ;
            }
        }
    }






    // структура головного меню за допомогую якого можна перемикатися між головними опціями
    while (TRUE) {
        menu(); // вивід меню
        printf("\n");
        printf("Вибір опції: ");
        // зміна яка отримує введений символ
        char select[100];
        scanf("%s", &select);

        if (select[0] == '1' && strlen(select) == 1) { // якщо введений символ дорівнює 1
            
            // вивід головної опції пройти тест
            while (TRUE) {
                system("cls");
                printf("+-------------------------------------------+\n");
                printf("|                 ВИБІР ТЕСТУ               |\n");
                printf("+-------------------------------------------+\n");
                printf("|                                           |\n");
                printf("|              НМТ тести - 1                |\n");
                printf("|              Власні тести - 2             |\n");
                printf("|                                           |\n");
                printf("|              Меню - E                     |\n");
                printf("|                                           |\n");
                printf("+-------------------------------------------+\n");
                printf("\n");
                printf("Вибір опції: ");
                // зміна яка отримує введений символ
                char select_choice_of_test[100];
                scanf("%s", &select_choice_of_test);

                if (select_choice_of_test[0] == '1' && strlen(select_choice_of_test) == 1) { // якщо введений символ дорівнює 1
                    // вивід вікна для вибору нмт теста
                    while (TRUE) {
                        system("cls");
                        printf("+-------------------------------------------+\n");
                        printf("|                НМТ ТЕСТУВАННЯ             |\n");
                        printf("+-------------------------------------------+\n");
                        printf("|                                           |\n");
                        printf("|              Українська мова - 1          |\n");
                        printf("|              Математика - 2               |\n");
                        printf("|              Історія України - 3          |\n");
                        printf("|                                           |\n");
                        printf("|              Більше про НМТ - 4           |\n");
                        printf("|              Назад - E                    |\n");
                        printf("|                                           |\n");
                        printf("+-------------------------------------------+\n");
                        printf("\n");
                        printf("Вибір опції: ");
                        // зміна яка отримує введений символ
                        char select_choice_of_test_NMT[100];
                        scanf("%s", &select_choice_of_test_NMT);

                        if (select_choice_of_test_NMT[0] == '1' && strlen(select_choice_of_test_NMT) == 1) { // якщо введений символ дорівнює 1
                            Ukr_NMT(); // вивід тесту з української мови
                        }

                        if (select_choice_of_test_NMT[0] == '2' && strlen(select_choice_of_test_NMT) == 1) { // якщо введений символ дорівнює 2
                            Math_NMT(); // вивід тесту з математики
                        }

                        if (select_choice_of_test_NMT[0] == '3' && strlen(select_choice_of_test_NMT) == 1) { // якщо введений символ дорівнює 3
                            History_NMT(); // вивід тесту з історії України
                        }
                        if (select_choice_of_test_NMT[0] == '4' && strlen(select_choice_of_test_NMT) == 1) { // якщо введений символ дорівнює 4
                            about_NMT(); // вивід інформації про НМТ тестування 
                        }
                        if (select_choice_of_test_NMT[0] == 'E' && strlen(select_choice_of_test_NMT) == 1 || select_choice_of_test_NMT[0] == 'e' && strlen(select_choice_of_test_NMT) == 1 || select_choice_of_test_NMT[0] == 'У' && strlen(select_choice_of_test_NMT) == 1 || select_choice_of_test_NMT[0] == 'у' && strlen(select_choice_of_test_NMT) == 1) { // якщо клавіша натиснута E, то повернення назад
                            break;
                        }
                                            
                        else {
                            ;
                        }
                    }
                    


                }

                if (select_choice_of_test[0] == '2' && strlen(select_choice_of_test) == 1) { // якщо введений символ дорівнює 2
                    choice_of_test_custom(); // вивід опції вибір власних тестів
                }
                       
                if (select_choice_of_test[0] == 'E' && strlen(select_choice_of_test) == 1 || select_choice_of_test[0] == 'e' && strlen(select_choice_of_test) == 1 || select_choice_of_test[0] == 'У' && strlen(select_choice_of_test) == 1 || select_choice_of_test[0] == 'у' && strlen(select_choice_of_test) == 1) { // якщо клавіша натиснута E, то повернення назад
                    break;
                }
                                        
                else {
                    ;
                }
            }
        }
        if (select[0] == '2' && strlen(select) == 1) { // якщо введений символ дорівнює 2
            results(); // вивід результатів
        }
            
        if (select[0] == '3' && strlen(select) == 1) { // якщо введений символ дорівнює 3
            constructor(); // вивід конструктора
        }

        if (select[0] == '4' && strlen(select) == 1) { // якщо введений символ дорівнює 4
            about_program(); // вивід інформації про програму
        }

        if (select[0] == 'E' && strlen(select) == 1 || select[0] == 'e' && strlen(select) == 1 || select[0] == 'У' && strlen(select) == 1 || select[0] == 'у' && strlen(select) == 1) { // якщо клавіша натиснута E, то повернення назад
            exit(0);
        }

        else {
            ;
        }
    }

    return 0;
}