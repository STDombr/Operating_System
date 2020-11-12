package locks;

import java.util.List;
import java.util.ArrayList;

public abstract class ImplementationFixNumLock implements FixNumLock {

    private List<Long> threads;

    private Integer threadLimit;

    public ImplementationFixNumLock(Integer threadLimit) {
        this.threadLimit = threadLimit;
        threads = new ArrayList<>();
    }

    public Integer getThreadLimit() {
        return threadLimit;
    }

    public List<Long> getThreads() {
        return threads;
    }

    @Override
    public Long getId() {
        return Thread.currentThread().getId();
    }

    @Override
    public synchronized boolean register() {

        if (threads.size() >= threadLimit) {
            return false;
        }

        Long threadId = Thread.currentThread().getId();

        if (threads.contains(threadId)) {
            return true;
        }

        threads.add(threadId);

        return true;
    }

    @Override
    public synchronized boolean unregister() {

        Long threadId = Thread.currentThread().getId();

        if (threads.contains(threadId)) {
            threads.remove(threadId);

            return true;
        }

        return false;
    }

    public Integer getThreadsCount() {
        return threads.size();
    }

    public Integer getIndex(){
        return threads.indexOf(getId());
    }

    public synchronized void reset() {
        threads.clear();
    }
}
