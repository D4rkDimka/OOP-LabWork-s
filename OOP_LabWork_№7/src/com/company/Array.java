package com.company;

import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;

public class Array {
    private double[] array;
    private int sizeOfArray;

    public Array(int sizeOfArray) {
        this.sizeOfArray = sizeOfArray;
        this.array = new double[sizeOfArray];
    }

    public boolean isEmpty() {
        if (this.array.length == 0) return true;
        else return false;
    }

    public double findMinimalElement() {
        double minimalElement = array[0];
        if (this.array != null) {
            if (isEmpty() == false) {
                for (int i = 0; i < array.length; i++) {
                    if (array[i] < minimalElement ) minimalElement = array[i];
                }
            } else System.out.println("Array is null!");
        }

        return minimalElement;
    }

    public double findMaxElement() {
        double maxElement = array[0];
        if (this.array != null) {
            if (isEmpty() == false) {
                for (int i = 0; i < array.length; i++) {
                    if (array[i] > maxElement) maxElement = array[i];
                }
            } else System.out.println("Array is empty!");
        } else System.out.println("Array is null!\n");

        return maxElement;
    }

    public void displayArray() {
        if (array != null) {
            if (isEmpty() == false) System.out.println(Arrays.toString(array));
            else System.out.println("Array is empty!\n");
        }

    }

    public void fillArrayByRandomNumbers() {

        Random random = new Random();

        for (int i = 0; i < array.length; i++) {
            array[i] = random.nextDouble(5) + 15;
        }
    }

    public void fillArray() {
        Scanner in = new Scanner(System.in);

        for (int i = 0; i < array.length; i++) {
            boolean isWorking = true;
            int numberOfElement = i + 1;

            while (isWorking) {
                System.out.print("[" + numberOfElement + "] = ");

                if (in.hasNextDouble()) {
                    isWorking = false;
                    array[i] = in.nextDouble();
                } else {
                    System.out.println("There is incorrect input!,try again\n");
                    in.next();
                }
            }
        }
    }

    public double findMiddleValue() {
        double middleValue = 0;
        if (array != null) {
            if (isEmpty() == false) {
                for (double element : this.array) middleValue += element;
                middleValue/=this.sizeOfArray;
            } else System.out.println("Array is empty!\n");
        }

        return middleValue;
    }

    public void sortArray() {
        Arrays.sort(this.array);
    }

    public void findElementInArray() {
        if (isEmpty() == false) {
            double findingElement;
            System.out.println("Enter value of element you'd like to find: ");
            findingElement = getValue();
            boolean isFound = false;
            for (int i = 0; i<array.length;i++)
            {
                if(array[i] == findingElement) isFound = true;
            }
            if(isFound == true)
            {
                System.out.println("Element "+ findingElement+" exists in this array!");
            }
            else System.out.println("There is no "+findingElement+" in this array!");
        }
    }

    public void changePositionOfElement() {
        double maxElement = 0;
        int positionOfMax = 0;
        double minElement = 0;
        int positionOfMin = 0;

        displayArray();

        if (isEmpty() == false) {
            for (int i = 0; i < array.length; i++) {
                if (array[i] > maxElement) {
                    maxElement = array[i];
                    positionOfMax = i;
                }

                if (array[i] < minElement) {
                    minElement = array[i];
                    positionOfMin = i;
                }
            }

            double temp = array[positionOfMax];
            array[positionOfMax] =array[positionOfMin] ;
            array[positionOfMin] = temp;

        }

        displayArray();
    }

    public double getValue() {

        Scanner in = new Scanner(System.in);
        boolean isWorking = true;
        double userInput;

        do {
            System.out.println("Please enter value: ");
            while (!in.hasNextDouble()) {
                System.out.println("That not a number!");
                in.next();
            }
            userInput = in.nextDouble();
            isWorking = false;
        } while (isWorking);

        in.close();
        return userInput;

    }
}
