package practiceAlgo;

import java.util.Scanner;

public class Kadane {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int number = scanner.nextInt();

        if(number < 1) {
            System.out.println("Invalid Input");
            return ;
        }

        int[] array = new int[number];
        boolean isAllNegative = true;

        for(int i=0; i<array.length; i++) {
            array[i] = scanner.nextInt();

            if(array[i] >= 0 && isAllNegative == true) {
                isAllNegative = false;
            }
        }

        int sum, max, head, tail, length;

        if(isAllNegative == true) {
            max = array[0];
            head = tail = 0;

            for(int i=1; i<array.length; i++) {
                if(array[i] > max) {
                    max = array[i];
                    head = tail = i;
                }
            }
        }
        else {
            sum = max = 0;
            head = tail = length = -1;

            for(int i=0 ; i<array.length; i++) {
                sum += array[i];
                length += 1;

                if(sum <= 0) {
                    sum = 0;
                    length = -1;
                }

                if(max < sum) {
                    max = sum;
                    tail = i;
                    head = tail - length;
                }
            }
        }

        System.out.println("Maximum Sum: " + max + "\n" + "Head: " + head + "\n" + "Tail: " + tail);
        return ;
    }
}
