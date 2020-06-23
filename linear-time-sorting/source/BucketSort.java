package source;

import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

import java.lang.Double;
import java.lang.Math;

public class BucketSort {
    public static double[] bucketSort(double[] array) {
        /* ** step-1 (Creating Buckets) ** */
        ArrayList<ArrayList<Double>> buckets = new ArrayList<>(5);  // NOTICE: number of buckets is always 5

        /* NOTICE - IMPORTANT */
        for(int i=0; i<5; i++) {
            buckets.add(new ArrayList<>());
        }


        /* ** step-2 (Insertion - IMPORTANT) ** */
        double min, max, power;
        min = max = array[0];

        /* takes O(n) time */
        for(double item: array) {
            if(item < min) {
                min = item;
            }

            if(item > max) {
                max = item;
            }
        }

        if(min == max) {
            return array;  // all the items are same
        }

        /* takes O(n) time */
        for(int i=0; i<array.length; i++) {
            array[i] = array[i] - min;  // NOTICE - offsetting
        }

        power = Math.pow(10, Math.floor(Math.log10(max-min))+1);  // NOTICE - IMPORTANT

        /* takes O(n) time */
        for(int i=0; i<array.length; i++) {
            array[i] = array[i]/power;  // NOTICE - scaling
        }

        /* takes O(n) time (main part here) */
        for(double item: array) {
            int index = (int) Math.floor(5*item);
            buckets.get(index).add(item);
        }


        /* ** step-3 (Sorting - NOTICE) ** */
        for(int i=0; i<5; i++) {
            Collections.sort(buckets.get(i));  // NOTICE: mergeSort is done with linear time for nearly sorted inputs
        }


        /* ** step-4 (Concatenation, this step technically takes O(n) time) ** */
        double[] outputArr = new double[array.length];
        int index = 0;

        for(int i=0; i<5; i++) {
            for(int j=0; j<buckets.get(i).size(); j++) {
                outputArr[index++] = (buckets.get(i).get(j)*power) + min;  // NOTICE: reverse operation
            }
        }

        return outputArr;
    }


    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int number = scanner.nextInt();  // n here

        if(number < 1) {
            return ;
        }

        double[] array = new double[number];

        /* takes O(n) time */
        for(int i=0; i<number; i++) {
            array[i] = scanner.nextDouble();
        }

        /* NOTICE: takes linear time */
        double[] outputArr = bucketSort(array);

        System.out.print("\n" + "sorted array:");

        /* takes O(n) time */
        for(double item: outputArr) {
            System.out.print(" " + item);
        }

        System.out.println("");

        return ;
    }
}
