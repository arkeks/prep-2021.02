#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "masterwrite.h"
#include "transactionwrite.h"
#include "blackrecord.h"

int main(void) {
    int choice = 0;
    FILE *Ptr, *Ptr_2, *black_record;
    Data client_data = {0};
    Data transfer = {0};
    printf("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
        while (scanf("%d", &choice) != -1) {
            switch (choice) {
                case 1:
                    Ptr = fopen("record.dat", "r+");
                    if (Ptr == NULL) {
                        puts("No access");
                    } else {
                        masterWrite(Ptr, client_data);
                        fclose(Ptr);
                    }
                    break;
                case 2:
                    Ptr = fopen("transaction.dat", "r+");
                    if (Ptr == NULL) {
                    puts("Not access");
                    } else {
                    transactionWrite(Ptr, transfer);
                    fclose(Ptr);
                    }
                    break;
                case 3:
                Ptr = fopen("record.dat", "r");
                Ptr_2 = fopen("transaction.dat", "r");
                black_record = fopen("blackrecord.dat", "w");
                if (Ptr == NULL || Ptr_2 == NULL || black_record == NULL) {
                    puts("exit");
                    } else {
                        blackRecord(Ptr, Ptr_2, black_record, client_data, transfer);
                        fclose(Ptr);
                        fclose(Ptr_2);
                        fclose(black_record);
                        }
                      break;
                default:
                    puts("error");
                    break;
                    }
                    printf("%s\n%s\n%s\n%s\n", "please enter action",
                    "enter data client:",
                    "enter data transaction:",
                    "update base");
                    }
        return 0;
}
