import locks.DekkerLock;
import org.junit.Assert;
import org.junit.Test;

public class DekkerTest {

    int counter = 0;
    DekkerLock lock = new DekkerLock();

    @Test
    public void dekkerCounterTest() throws InterruptedException {
        Runnable counterIncrementation = () -> {

            for(int i = 0; i < 10000; i++){
                lock.lock();

                counter++;

                lock.unlock();
            }
        };

        Thread thread1 = new Thread(counterIncrementation);
        Thread thread2 = new Thread(counterIncrementation);

        thread1.start();
        thread2.start();

        thread1.join();
        thread2.join();

        Assert.assertEquals(counter, 20000);
    }
}
