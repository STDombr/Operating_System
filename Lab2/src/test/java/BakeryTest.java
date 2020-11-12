import locks.BakeryLock;
import org.junit.Assert;
import org.junit.Test;

public class BakeryTest {

    int counter = 0;
    BakeryLock lock = new BakeryLock(5);

    @Test
    public void backeryCounterTest() throws InterruptedException {

        Runnable counterIncrementation = () -> {
            lock.register();

            for(int i = 0; i < 20000; i++){
                lock.lock();

                counter++;

                lock.unlock();
            }
        };

        Thread thread1 = new Thread(counterIncrementation);
        Thread thread2 = new Thread(counterIncrementation);
        Thread thread3 = new Thread(counterIncrementation);
        //Thread thread4 = new Thread(counterIncrementation);
        //Thread thread5 = new Thread(counterIncrementation);

        thread1.start();
        thread2.start();
        thread3.start();
        //thread4.start();
        //thread5.start();

        thread1.join();
        thread2.join();
        thread3.join();
        //thread4.join();
        //thread5.join();

        Assert.assertEquals(counter, 60000);

        lock.reset();
    }
}
