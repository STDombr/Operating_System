package locks;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.Condition;

public class DekkerLock extends ImplementationFixNumLock {

    private int turn;
    private List<Boolean> wantsToEnter;

    public DekkerLock() {
        super(2);
        wantsToEnter = new ArrayList<Boolean>(Collections.nCopies(2, false));
    }

    @Override
    public void lock() {
        int otherId = turn;

        if (!wantsToEnter.get(turn)){
            if (!wantsToEnter.get(1 - turn)){
                otherId = 1 - turn;
                turn = otherId;
            } else{
                otherId = 1 - turn;
            }
        }

        int thisId = 1 - otherId;

        wantsToEnter.set(thisId, true);

        while (wantsToEnter.get(otherId)) {
            if (turn == otherId) {
                wantsToEnter.set(thisId, false);

                while (turn == otherId) {
                    System.out.println("B" + Thread.currentThread().getId());
                }

                wantsToEnter.set(thisId, true);
            }
        }
    }

    @Override
    public void unlock() {
        wantsToEnter.set(turn, false);
        turn = 1 - turn;
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
