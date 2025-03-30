#pragma once

// tests functions from module queue.c,
// if there are some errors, changes errorCode,
// else if tests failed changes error to -1
void queueTest(int *errorCode);

// tests scanCommentsFromFile,
// if there are some errors, changes errorCode,
// else if tests failed changes error to -1
void commentsScanTest(int *errorCode);
