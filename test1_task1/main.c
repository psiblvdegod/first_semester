#include "queue.h"
#include "test.h"
#include "maxDigitSum.h"

int main(void) {
    int errorCode = 0;
    queueTest(&errorCode);
    if (errorCode != 0) {
        return errorCode;
    }
    maxDigitSumTest(&errorCode);

}
