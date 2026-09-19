#include <stdio.h>
#include "TimeSlot.h"

#define INPUT_FILE "C:/data/timeslot.txt"

void InputTimeSlots(TimeSlot slots[], int &n)
{
    FILE *file = fopen(INPUT_FILE, "r");

    if (file == NULL)
    {
        printf("Khong mo duoc file: %s\n", INPUT_FILE);
        n = 0;
        return;
    }

    n = 0;

    while (n < MAX_TIMESLOT &&
           fscanf(file, "%[^,],%d,%[^,],%s\n",
                  slots[n].day,
                  &slots[n].slotNumber,
                  slots[n].startTime,
                  slots[n].endTime) == 4)
    {
        n++;
    }

    fclose(file);
}

void OutputTimeSlots(TimeSlot slots[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s - Slot %d - %s -> %s\n",
               slots[i].day,
               slots[i].slotNumber,
               slots[i].startTime,
               slots[i].endTime);
    }
}
