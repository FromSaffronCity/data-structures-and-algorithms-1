#include<iostream>
#include<math.h>

#define INF 999999999
#define ABS(X) (X<0)? -X: X

using namespace std;


/* ********** Point class ************** */

class Point {

    double x;
    double y;

public:

    Point(): x(0), y(0) {}
    ~Point() { x = 0; y = 0; }

    double getX() const { return x; }
    double getY() const { return y; }

    double getDistance(Point& point);
    friend istream& operator>>(istream& in, Point& point);
    friend ostream& operator<<(ostream& out, Point& point);
};


double Point::getDistance(Point& point) {
    /* Not returning distance actually */
    return sqrt((this->x - point.x)*(this->x - point.x) + (this->y - point.y)*(this->y - point.y));
}

istream& operator>>(istream& in, Point& point) {
    return in >> point.x  >> point.y;  /* NOTICE - whitespace is normal separator character */
}

ostream& operator<<(ostream& out, Point& point) {
    return out << point.x << " " << point.y;
}

/* **************************************** */




/* ************ global functions ********** */

// structure for keeping track of the closest pair of points and minimum distance

struct ClosestPoints {
    Point point1;
    Point point2;

    double minDistance;
};


// implement merge sort for sorting purpose

void merge(Point* array, int start, int mid, int end, bool sortX);
void mergeSort(Point* array, int start, int end, bool sortX);

// implement closest point solve for O(nlogn) time

ClosestPoints getMin(ClosestPoints pair1, ClosestPoints pair2);
ClosestPoints getMinDistBrute(Point* array, int number);
ClosestPoints getClosestDist(Point* array, int number);
ClosestPoints findClosestDist(Point* sortedX, Point* sortedY, int number);
ClosestPoints stripClosestDist(Point* strip, int number, ClosestPoints minPair);

/* **************************************** */




/* ************** main function *************** */

int main() {
    int number;
    cin >> number;

    Point* array = new Point[number]; /* array of Point objects */

    for(int i=0; i<number; i++) {
        cin >> array[i];
    }

    cout << endl;

    if(number < 2) {
        cout << "Invalid Operation" << endl;
        return 0;
    }

    /*  main process here */
    ClosestPoints result = getClosestDist(array, number);

    cout << result.point1 << "\n" << result.point2 << endl;
    cout << result.minDistance << endl;

    delete[] array;
    return 0;
}

/* ****************************************** */




/* ************** function implementation of merge sort ************** */

void mergeSort(Point* array, int start, int end, bool sortX) {
    int mid;  // NOTICE

    if(start<end) {
        mid = (start+end)/2;

        mergeSort(array, start, mid, sortX);
        mergeSort(array, mid+1, end, sortX);

        merge(array, start, mid, end, sortX);
    }

    return ;
}


void merge(Point* array, int start, int mid, int end, bool sortX) {
    int number1 = mid - start + 1;
    int number2 = end - mid;

    Point* tempArray1 = new Point[number1];
    Point* tempArray2 = new Point[number2];

    /* Copying values to temporary arrays */
    for(int i=0; i<number1; i++) {
        tempArray1[i] = array[start+i];
    }
    for(int i=0; i<number2; i++) {
        tempArray2[i] = array[mid+1+i];
    }

    /*  Copying values to main array (merging) */
    int index1, index2, indexMerge = start;
    index1 = index2 = 0;

    if(sortX == true) {
        while(index1 < number1 && index2 < number2) {
            if(tempArray1[index1].getX() <= tempArray2[index2].getX()) {
                array[indexMerge++] = tempArray1[index1++];
            }
            else {
                array[indexMerge++] = tempArray2[index2++];
            }
        }
    }

    if(sortX == false) {
        while(index1 < number1 && index2 < number2) {
            if(tempArray1[index1].getY() <= tempArray2[index2].getY()) {
                array[indexMerge++] = tempArray1[index1++];
            }
            else {
                array[indexMerge++] = tempArray2[index2++];
            }
        }
    }

    /* copying remaining elements of tempArray1 */
    while(index1 < number1) {
        array[indexMerge++] = tempArray1[index1++];
    }

    /* copying remaining elements of tempArray2 */
    while(index2 < number2) {
        array[indexMerge++] = tempArray2[index2++];
    }

    delete[] tempArray1;
    delete[] tempArray2;
    return ;
}

/* ********************************************** */



/* *************** function implementation of closest pair finding ****************** */

ClosestPoints getMin(ClosestPoints pair1, ClosestPoints pair2) {
    return (pair1.minDistance < pair2.minDistance)? pair1: pair2;
}

ClosestPoints getMinDistBrute(Point* array, int number) {
    ClosestPoints minPair;
    minPair.minDistance = INF;

    for(int i=0; i<(number - 1); i++) {
        for(int count=(i+1); count<number; count++) {
            if(array[i].getDistance(array[count]) < minPair.minDistance) {
                minPair.point1 = array[i];
                minPair.point2 = array[count];
                minPair.minDistance = array[i].getDistance(array[count]);
            }
        }
    }

    return minPair;
}


ClosestPoints getClosestDist(Point* array, int number) {
    Point* sortedX = new Point[number];
    Point* sortedY = new Point[number];

    /* copying from original array */
    for(int i=0; i<number; i++) {
        sortedX[i] = array[i];
        sortedY[i] = array[i];
    }

    /* NOTICE - sort in ascending order according to x and y */
    mergeSort(sortedX, 0, number-1, true);
    mergeSort(sortedY, 0, number-1, false);

    /* returning minimum distance of all points*/
    ClosestPoints minPair = findClosestDist(sortedX, sortedY, number);

    delete[] sortedX;
    delete[] sortedY;
    return minPair;
}


ClosestPoints findClosestDist(Point* sortedX, Point* sortedY, int number) {
    if(number <= 3) {
        /* if there are not more than 3 points, brute force approach can be used to determine the minDist*/
        return getMinDistBrute(sortedX, number);
    }

    /* Finding the middle point (according to x) */
    int mid = number/2;
    Point midPoint = sortedX[mid];

    /* separating points in sortedY around the midPoint (vertical line) */
    Point* sortedYLeft = new Point[mid+1];
    Point* sortedYRight = new Point[number-(mid+1)];

    int leftIndex, rightIndex;
    leftIndex = rightIndex = 0;

    for(int i=0; i<number; i++) {
        if(sortedY[i].getX() <= midPoint.getX()) {
            sortedYLeft[leftIndex++] = sortedY[i];
        }
        else {
            sortedYRight[rightIndex++] = sortedY[i];
        }
    }

    /* NOTICE - finding minDist on each side */
    ClosestPoints leftMinPair = findClosestDist(sortedX, sortedYLeft, mid);
    ClosestPoints rightMinPair = findClosestDist(sortedX+mid, sortedYRight, number-mid);

    /* NOTICE - finding the smallest of two */
    ClosestPoints minPair = getMin(leftMinPair, rightMinPair);

    /* building an array containing points close to (closer than minDist determined earlier) midPoint (vertical line) */
    Point* strip = new Point[number];
    int stripIndex = 0;

    for(int i=0; i<number; i++) {
        if(ABS(sortedY[i].getX() - midPoint.getX()) < minPair.minDistance) {
            strip[stripIndex++] = sortedY[i];
        }
    }

    ClosestPoints minPairVertical = stripClosestDist(strip, stripIndex, minPair);

    /* NOTICE */
    delete[] sortedYLeft;
    delete[] sortedYRight;
    delete[] strip;

    return getMin(minPair, minPairVertical);
}

ClosestPoints stripClosestDist(Point* strip, int number, ClosestPoints minPair) {
    /* NOTICE */
    for(int i=0; i<(number-1); i++) {
        for(int count=(i+1); count<number; count++) {
            if((strip[count].getY() - strip[i].getY()) < minPair.minDistance) {
                if(strip[i].getDistance(strip[count]) < minPair.minDistance) {
                    minPair.point1 = strip[i];
                    minPair.point2 = strip[count];
                    minPair.minDistance = strip[i].getDistance(strip[count]);
                }
            }
        }
    }

    return minPair;
}
