#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <Windows.h>

// FCFS를 위한 도착 시간 기준 정렬 함수
void sortByArrival(int at[], int bt[], int n, int id[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                // 도착 시간 기준으로 정렬
                std::swap(at[j], at[j + 1]);
                std::swap(bt[j], bt[j + 1]);
                std::swap(id[j], id[j + 1]); // 프로세스 ID도 같이 정렬
            }
        }
    }
}

int main() {
    int n, i, j;
    int at[10], bt[10], wt[10], tat[10], ct[10], id[10]; // 도착 시간, 실행 시간, 대기 시간, 반환 시간, 완료 시간, 프로세스 ID
    int h = 22; // ASCII 코드 22 → '-' 모양으로 Gantt 차트 표현
    float avg_wt = 0, avg_tat = 0;

    printf("\n \tJOB SCHEDULING ALGORITHM [FCFS]");
    printf("\n \t*************************************************\n");

    printf("\n 프로세스 개수를 입력하세요. : ");
    scanf_s("%d", &n);

    printf("\n Enter arrival time and burst time for each process:\n");
    for (i = 0; i < n; i++) {
        id[i] = i + 1; // 프로세스 번호 저장
        printf("Process %d 대기 시간 : ", i + 1);
        scanf_s("%d", &at[i]);
        printf("Process %d 실행 시간 : ", i + 1);
        scanf_s("%d", &bt[i]);
    }

    // 도착 시간 기준 정렬 (FCFS 유지)
    sortByArrival(at, bt, n, id);

    // FCFS 스케줄링 - 대기 시간 & 완료 시간 계산
    ct[0] = at[0] + bt[0]; // 첫 번째 프로세스 완료 시간
    wt[0] = 0; // 첫 번째 프로세스는 대기 시간이 없음
    tat[0] = bt[0];

    for (i = 1; i < n; i++) {
        if (ct[i - 1] < at[i]) {
            ct[i] = at[i] + bt[i]; // 도착 이후 실행
        }
        else {
            ct[i] = ct[i - 1] + bt[i]; // 이전 프로세스 종료 후 실행
        }
        wt[i] = ct[i - 1] - at[i]; // 대기 시간
        if (wt[i] < 0) wt[i] = 0;  // 음수 방지
        tat[i] = wt[i] + bt[i]; // 반환 시간
        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    avg_wt /= n;
    avg_tat /= n;

    // 결과 출력
    printf("\nProcess\t도착 시간\t실행 시간\t대기 시간\t\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\n", id[i], at[i], bt[i], wt[i]);
    }

    printf("\n평균 대기 시간 : %.2f", avg_wt);

    // Gantt Chart 출력 
    printf("\nGantt Chart\n");
    printf("******************************************\n\n");

    int time = 0;
    for (i = 0; i < n; i++) {
        // 도착 시간까지 기다리기
        if (time < at[i]) {
            printf("\n대기중 %dms...\n", at[i]);
            Sleep((at[i] - time) * 50);  // 도착 시간까지 대기
            time = at[i];
        }

        // 도착 알림 출력 (현재 실행 중인 시간과 도착 시간이 일치하면 메시지 표시)
        for (int k = 0; k < n; k++) {
            if (at[k] == time && k != i) {
                printf("\nP%d 도착! [%dms]\n", id[k], time);
            }
        }

        // 프로세스 실행
        printf("실행중 P%d: ", id[i]);
        for (j = 0; j < bt[i]; j++) {
            printf("%c", h); // 실행 시간만큼 '-' 출력
            Sleep(50);  // 하나씩 출력되도록 지연

            // 실행 중에도 새로운 프로세스가 도착하면 도착 메시지 출력
            for (int k = 0; k < n; k++) {
                if (at[k] == time + j + 1 && k != i) {
                    printf("\nP%d 도착! [%dms]\n", id[k], time + j + 1);
                }
            }
        }
        printf(" [%dms]\n", time + bt[i]);  // 현재 시간 표시
        time = ct[i]; // 현재 시간 업데이트
    }

    printf("\n프로세스 실행 완료.\n");
    _getch();
}
