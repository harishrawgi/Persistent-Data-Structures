a.out : main.o PPSinglyList.o PPDoublyList.o PPStack.o PPCircularList.o PPQueue.o PPDEQueue.o PPSinglyListHelper.o PPDoublyListHelper.o PPCircularListHelper.o
	gcc main.o PPSinglyList.o PPDoublyList.o PPStack.o PPCircularList.o PPQueue.o PPDEQueue.o PPSinglyListHelper.o PPDoublyListHelper.o PPCircularListHelper.o

main.o: main.c PPSinglyList.h PPDoublyList.h PPStack.h PPCircularList.h PPQueue.h PPDEQueue.h
	gcc -c main.c

PPSinglyList.o: PPSinglyList.c PPSinglyList.h PPSinglyListHelper.h
	gcc -c PPSinglyList.c

PPSinglyListHelper.o: PPSinglyListHelper.c PPSinglyListHelper.h
	gcc -c PPSinglyListHelper.c

PPDoublyList.o: PPDoublyList.c PPDoublyList.h PPDoublyListHelper.h
	gcc -c PPDoublyList.c

PPDoublyListHelper.o: PPDoublyListHelper.c PPDoublyListHelper.h
	gcc -c PPDoublyListHelper.c

PPCircularList.o: PPCircularList.c PPCircularList.h PPCircularListHelper.h
	gcc -c PPCircularList.c

PPCircularListHelper.o: PPCircularListHelper.c PPCircularListHelper.h
	gcc -c PPCircularListHelper.c

PPStack.o: PPStack.c PPStack.h
	gcc -c PPStack.c

PPQueue.o: PPQueue.c PPQueue.h
	gcc -c PPQueue.c

PPDEQueue.o: PPDEQueue.c PPDEQueue.h
	gcc -c PPDEQueue.c
