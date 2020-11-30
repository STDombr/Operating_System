package locks;

import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Condition;

public class BakeryLock extends ImplementationFixNumLock {

    private List<Integer> numbers;
    private List<Boolean> choosing;
    Integer threadLimit;

    public BakeryLock(Integer threadLimit) {
        super(threadLimit);

        this.threadLimit = threadLimit;
        numbers = new LinkedList<Integer>(Collections.nCopies(threadLimit, 0));
        choosing = new LinkedList<Boolean>(Collections.nCopies(threadLimit, false));
    }

    @Override
    public void lock() {

        Integer thisIndex = getIndex();


        choosing.set(thisIndex, true);

        int maxNumber = 0;
        for (int i = 0; i < threadLimit; i++) {
            if (numbers.get(i) > maxNumber) {
                maxNumber = numbers.get(i);
            }
        }
        numbers.set(thisIndex, maxNumber + 1);

        choosing.set(thisIndex, false);



        for (int i = 0; i < threadLimit; i++){
            while (choosing.get(i)){
                //wait
            }

            while ((!numbers.get(i).equals(0)) &&
                   ((numbers.get(thisIndex) > numbers.get(i)) ||
                           (numbers.get(thisIndex).equals(numbers.get(i)) &&
                                   thisIndex > i))){
                //wait
            }
        }
    }

    @Override
    public void unlock() {
        numbers.set(getIndex(), 0);
    }

    @Override
    public void lockInterruptibly() throws InterruptedException {

    }

    @Override
    public boolean tryLock() {
        return false;
    }

    @Override
    public boolean tryLock(long time, TimeUnit unit) throws InterruptedException {
        return false;
    }

    @Override
    public Condition newCondition() {
        return null;
    }
}
