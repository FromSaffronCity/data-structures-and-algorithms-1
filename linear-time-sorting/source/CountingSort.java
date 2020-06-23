package source;

import java.util.Scanner;

public class CountingSort {
    public static int[] countingSort(int[] array) {
        int min, max;
        min = max = array[0];

        /* takes O(n) time */
        for(int item: array) {
            if(item < min) {
                min = item;
            }

            if(item > max) {
                max = item;
            }
        }

        int number = max-min+1;  // k here
        int[] countArr = new int[number];

        /* takes O(k) time */
        for(int i=0; i<number; i++) {
            countArr[i] = 0;
        }

        /* takes O(n) time */
        for(int item: array) {
            countArr[item-min]++;  // IMPORTANT: offsetting values here
        }

        /* takes O(k) time */
        for(int i=1; i<number; i++) {
            countArr[i] += countArr[i-1];
        }

        int[] outputArr = new int[array.length];

        /* takes O(n) time */
        for(int item: array) {
            countArr[item-min]--;
            outputArr[countArr[item-min]] = item;  /* NOTICE */
        }

        return outputArr;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int number = scanner.nextInt();  // n here

        if(number < 1) {
            return ;  // invalid input
        }

        int[] array = new int[number];

        /* takes O(n) time */
        for(int i=0; i<number; i++) {
            array[i] = scanner.nextInt();
        }

        /* NOTICE: takes O(n+k) time and space in total (linear) */
        int[] outputArr = countingSort(array);

        System.out.print("\n" + "sorted array:");

        /* takes O(n) time */
        for(int item: outputArr) {
            System.out.print(" " + item);
        }

        System.out.println("");

        return ;
    }
}
