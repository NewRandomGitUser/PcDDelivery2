public class TrafficController {
    private boolean lock = false;

    public synchronized void enterLeft() {
        while (lock) {
            try {
                wait();
            } catch (InterruptedException e) {
                System.out.println(e.getMessage());
            }
        }
        lock = true;
    }

    public synchronized void enterRight() {
        while (lock) {
            try {
                wait();
            } catch (InterruptedException e) {
                System.out.println(e.getMessage());
            }
        }
        lock = true;
    }

    public synchronized void leaveLeft(){
        lock = false;
        notifyAll();
    }

    public synchronized void leaveRight(){
        lock = false;
        notifyAll();
    }
}

