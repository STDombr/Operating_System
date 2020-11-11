package locks;

import java.util.concurrent.locks.Lock;

public interface FixNumLock extends Lock {

    boolean register();

    boolean unregister();

    Long getId();
}
