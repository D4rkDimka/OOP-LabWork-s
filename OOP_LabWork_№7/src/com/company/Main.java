package com.company;

import java.util.Scanner;


public class Main {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        boolean isWorking = true;
        boolean isInitialized = false;
        Array array = new Array(10);

        while (isWorking) {
            menu();

            int userChoice = in.nextInt();

            switch (userChoice) {
                case 1:
                    System.out.println("(1) - Random element's");
                    System.out.println("(2) - Enter element's");

                    System.out.print("\nYour choice>>");
                    userChoice = in.nextInt();

                    switch (userChoice) {
                        case 1:
                            array.fillArrayByRandomNumbers();
                            isInitialized = true;
                            break;
                        case 2:
                            array.fillArray();
                            isInitialized = true;
                            break;
                        default:
                            System.out.println("There is no case with such input!");
                    }
                    break;
                case 2:
                    if (isInitialized == true) array.displayArray();
                    else System.out.println("Array is empty!");
                    break;
                case 3:
                    if (isInitialized == true) {
                        System.out.println("(1) - Find max element");
                        System.out.println("(2) - Find minimal element");
                        System.out.println("(3) - Find middle value");
                        System.out.println("(4) - Find random element");

                        System.out.print("\nYour choice>>");
                        userChoice = in.nextInt();

                        switch (userChoice) {
                            case 1:
                                System.out.println(array.findMaxElement());
                                break;
                            case 2:
                                System.out.println(array.findMinimalElement());
                                break;
                            case 3:
                                System.out.println(array.findMiddleValue());
                                break;
                            case 4:
                                array.findElementInArray();
                                break;
                            default:
                                System.out.println("There is no case with such input!");
                        }
                    } else System.out.println("Array is empty!");
                    break;
                case 4:
                    if (isInitialized == true) {
                        array.changePositionOfElement();
                    } else System.out.println("Array is empty!");
                    break;
                case 5:
                    if (isInitialized == true) {
                        array.sortArray();
                        array.displayArray();
                    } else System.out.println("Array is empty!");
                    break;
                case 0:
                    isWorking = false;
                    break;
            }
        }
    }

    public static void menu() {
        System.out.println("\tMenu to work with array");
        System.out.println("(1) - Initialize array");
        System.out.println("(2) - Display array");
        System.out.println("(3) - Find element");
        System.out.println("(4) - Change positions of elements");
        System.out.println("(5) - Sort array");
        System.out.println("(0) - Exit");
        System.out.println("\nYour choice>>");
    }
}
