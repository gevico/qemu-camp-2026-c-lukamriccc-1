#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50

typedef struct {
    char name[NAME_LEN];
    int score;
} Student;

Student students[MAX_STUDENTS];
Student temp[MAX_STUDENTS];

void merge_sort(int left, int right) {
    if (left >= right) {
        return;
    } else if (left == right - 1) {
        if(students[left].score > students[right].score) {
            temp[left] = students[left];
            temp[right] = students[right];
        } else {
            temp[left] = students[right];
            temp[right] = students[left];
        }
        students[left] = temp[left];
        students[right] = temp[right];
        return;
    }
    int mid = left + (right-left) / 2;
    merge_sort(left, mid);
    merge_sort(mid + 1, right);
    int l = left, r = mid + 1;
    int pos = left;
    while(l <= mid && r <= right) {
        if(students[l].score > students[r].score ) {
            temp[pos++] = students[l++];
        } else {
            temp[pos++] = students[r++];
        }
    }
    while(l <= mid) {
        temp[pos++] = students[l++];
    }
    while(r <= right) {
        temp[pos++] = students[r++];
    }
    memcpy(students + left, temp + left, sizeof(Student)*(right + 1 - left));
    return;
}

int main(void) {
    FILE *file = fopen("02_students.txt", "r");
    if (!file) {
        printf("错误：无法打开文件 02_students.txt\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);

    if (n <= 0 || n > MAX_STUDENTS) {
        printf("学生人数无效：%d\n", n);
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%s %d", students[i].name, &students[i].score);
    }
    fclose(file);

    merge_sort(0, n - 1);
    printf("\n归并排序后按成绩从高到低排序的学生名单：\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", students[i].name, students[i].score);
    }

    return 0;
}