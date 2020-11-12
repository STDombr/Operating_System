package locks;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.locks.Condition;

public class DekkerLock extends ImplementationFixNumLock {

    private AtomicLong turn;
    private AtomicInteger countOfWantsToEnterThreads;

    public DekkerLock() {
        super(2);

        turn = new AtomicLong();
        countOfWantsToEnterThreads = new AtomicInteger(0);
    }

    @Override
    public void lock() {
        long thisId = getId();

        if (countOfWantsToEnterThreads.get() == 0)
            turn.set(thisId);

        countOfWantsToEnterThreads.addAndGet(1);

        while (countOfWantsToEnterThreads.get() > 1) {
            if (turn.get() != thisId) {
                countOfWantsToEnterThreads.addAndGet(-1);

                while (countOfWantsToEnterThreads.get() > 0) {
                    //wait
                }

                countOfWantsToEnterThreads.addAndGet(1);
            }
        }
    }

    @Override
    public void unlock() {
        countOfWantsToEnterThreads.addAndGet(-1);
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
